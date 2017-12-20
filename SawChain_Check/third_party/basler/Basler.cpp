#include "../../stdafx.h"
#include"..\\..\\globle.h"
#include "../../Lock.h"
/*

This sample illustrates how to use the PylonDeviceGrabSingleFrame() convenience
method for grabbing images in a loop. PylonDeviceGrabSingleFrame() grabs one
single frame in single frame mode.

Grabbing in single frame acquisition mode is the easiest way to grab images. Note: in single frame
mode the maximum frame rate of the camera can't be achieved. The full frame
rate can be achieved by setting the camera to the continuous frame acquisition
mode and by grabbing in overlapped mode, i.e., image acquisition is done in parallel
with image processing. This is illustrated in the OverlappedGrab sample program.

*/



#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include "Basler.h"


/* Simple error handling. */
#ifndef _TEST
#define CHECK(errc) if( GENAPI_E_OK != errc )\
 {\
CString _str;\
_str.Format(L"相机错误代码:%d",errc);\
AfxMessageBox(_str);\
exit(0);\
}\

#else
#define CHECK( errc ) if ( GENAPI_E_OK != errc ) printf("error %d",errc);
#endif


/* This function can be used to wait for user input at the end of the sample program. */

/* This method demonstrates how to retrieve the error message
for the last failed function call. */

#ifdef _TEST
//void printErrorAndExit(GENAPIC_RESULT errc);
#else

#endif // _TEST

Basler::~Basler()
{
#ifdef _TEST
	AfxMessageBox(L"相机关闭中");
#endif
		
		if(NULL != hTopDev)
		{ 
		res = PylonDeviceClose(hTopDev);
		CHECK(res);
		res = PylonDestroyDevice(hTopDev);
		CHECK(res);
		hTopDev = NULL;
		}

		if(NULL != hBottomDev)
		{ 
		res = PylonDeviceClose(hBottomDev);
		CHECK(res);
		res = PylonDestroyDevice(hBottomDev);
		CHECK(res);
		hBottomDev = NULL;
		}

		/* Free memory for grabbing. */

		if (TopimgBuf)
		{
			TopimgBuf;
			TopimgBuf = NULL;
		}
		
		if(BottomimgBuf)
		{ 
			free(BottomimgBuf);
			BottomimgBuf = NULL;
		}
		PylonTerminate();
		//bug？
	//	PylonTerminate();

		//pressEnterToExit();

		/* Shut down the pylon runtime system. Don't call any pylon method after
		calling PylonTerminate(). */
		
}

bool Basler::Grab(PYLON_DEVICE_HANDLE &hDev, unsigned char** imgBuf, int& width, int& height)
{
//	unsigned char min, max;
	PylonGrabResult_t grabResult;
	_Bool bufferReady;

	/* Grab one single frame from stream channel 0. The
	camera is set to single frame acquisition mode.
	Wait up to 500 ms for the image to be grabbed. */
	res = PylonDeviceGrabSingleFrame(hDev, 0, *imgBuf, payloadSize,
		&grabResult, &bufferReady, 500);
	if (GENAPI_E_OK == res && !bufferReady)
	{
		/* Timeout occurred. */
		width = 0;
		height = 0;
		return false;
	}
	width = grabResult.SizeX;
	height = grabResult.SizeY;
	return true;

}


/* Calculating the minimum and maximum gray value of an image buffer */
int Basler::InitCamera(PYLON_DEVICE_HANDLE &hDev, char * DevName, unsigned char** imgBuf, int index)
{
	//return 0;
	res = PylonCreateDeviceByIndex(index, &hDev);
	CHECK(res);

	/* Before using the device, it must be opened. Open it for configuring
	parameters and for grabbing images. */
	res = PylonDeviceOpen(hDev, PYLONC_ACCESS_MODE_CONTROL | PYLONC_ACCESS_MODE_STREAM);
	CHECK(res);

	/* Print out the name of the camera we are using. */
	{
		char buf[256];
		size_t siz = sizeof(buf);
		_Bool isReadable;

		isReadable = PylonDeviceFeatureIsReadable(hDev, DevName);
		if (isReadable)
		{
			res = PylonDeviceFeatureToString(hDev, DevName, buf, &siz);
			CHECK(res);
		}
	}

	/* Set the pixel format to Mono8, where gray values will be output as 8 bit values for each pixel. */
	/* ... Check first to see if the device supports the Mono8 format. */
	isAvail = PylonDeviceFeatureIsAvailable(hDev, "EnumEntry_PixelFormat_Mono8");
	if (!isAvail)
	{
		/* Feature is not available. */
		fprintf(stderr, "Device doesn't support the Mono8 pixel format.");
		PylonTerminate();
		//pressEnterToExit();
		AfxMessageBox(L"相机不可访问");
		exit(EXIT_FAILURE);
	}
	/* ... Set the pixel format to Mono8. */
	res = PylonDeviceFeatureFromString(hDev, "PixelFormat", "Mono8");
	CHECK(res);

	/* Disable acquisition start trigger if available */
	isAvail = PylonDeviceFeatureIsAvailable(hDev, "EnumEntry_TriggerSelector_AcquisitionStart");
	if (isAvail)
	{
		res = PylonDeviceFeatureFromString(hDev, "TriggerSelector", "AcquisitionStart");
		CHECK(res);
		res = PylonDeviceFeatureFromString(hDev, "TriggerMode", "Off");
		CHECK(res);
	}

	/* Disable frame burst start trigger if available. */
	isAvail = PylonDeviceFeatureIsAvailable(hDev, "EnumEntry_TriggerSelector_FrameBurstStart");
	if (isAvail)
	{
		res = PylonDeviceFeatureFromString(hDev, "TriggerSelector", "FrameBurstStart");
		CHECK(res);
		res = PylonDeviceFeatureFromString(hDev, "TriggerMode", "Off");
		CHECK(res);
	}

	/* Disable frame start trigger if available */
	isAvail = PylonDeviceFeatureIsAvailable(hDev, "EnumEntry_TriggerSelector_FrameStart");
	if (isAvail)
	{
		res = PylonDeviceFeatureFromString(hDev, "TriggerSelector", "FrameStart");
		CHECK(res);
		res = PylonDeviceFeatureFromString(hDev, "TriggerMode", "Off");
		CHECK(res);
	}

	/* For GigE cameras, we recommend increasing the packet size for better
	performance. If the network adapter supports jumbo frames, set the packet
	size to a value > 1500, e.g., to 8192. In this sample, we only set the packet size
	to 1500. */
	/* ... Check first to see if the GigE camera packet size parameter is supported
	and if it is writable. */
	isAvail = PylonDeviceFeatureIsWritable(hDev, "GevSCPSPacketSize");
	if (isAvail)
	{
		/* ... The device supports the packet size feature. Set a value. */
		res = PylonDeviceSetIntegerFeature(hDev, "GevSCPSPacketSize", 1500);
		CHECK(res);
	}

	/* Determine the required size of the grab buffer. */
	res = PylonDeviceGetIntegerFeatureInt32(hDev, "PayloadSize", &payloadSize);
	CHECK(res);

	/* Allocate memory for grabbing. */
	*imgBuf = (unsigned char*)malloc(payloadSize*sizeof(char));
#ifdef _TEST
	printf("image size is %d\n", payloadSize);
#endif
	if (NULL == *imgBuf)
	{
		fprintf(stderr, "Out of memory.\n");
		//PylonTerminate();
		//pressEnterToExit();
		AfxMessageBox(L"内存分配失败");
		exit(EXIT_FAILURE);
	}
	return res;
}


int Basler::CameraInit()
{
	/* Before using any pylon methods, the pylon runtime must be initialized. */

	size_t			DevNum;

	PylonInitialize();
	/* Enumerate all camera devices. You must call
	PylonEnumerateDevices() before creating a device! */

	res = PylonEnumerateDevices(&DevNum);

	if(0!= DevNum)
	{
		PylonDeviceInfo_t pDi;
		for (int i = 0; i < static_cast<int>(DevNum); i++)
		{
			PylonGetDeviceInfo(i,&pDi);
			pDi.UserDefinedName;
			if (!strcmp("UPCamera", pDi.UserDefinedName))	id[0] = i;
			if (!strcmp("BottomCamera", pDi.UserDefinedName))	id[1] = i;
		}
	}
	if (0 == DevNum)	return 0;
	if (1 == DevNum) { id[0] = 0; }
	else if (-1 == id[0] || -1 == id[1]) { AfxMessageBox(L"是不是相机没有取名好，分别为UPCamera, BottomCamera"); return 0; }
	CHECK(res);

	int flag = 3; //3 is equal to binanry 11
	if (0 == DevNum)
	{
		PylonTerminate();
		//pressEnterToExit();
		return 0;
		exit(EXIT_FAILURE);
	}	

	else if (1 == DevNum)
	{
		res = InitCamera(hTopDev, "UPCamera", &TopimgBuf, 0);
		if (GENAPI_E_OK == res)
		{
			return 2;
		}
		else
		{
			res = InitCamera(hBottomDev, "BottomCamera", &BottomimgBuf, 0);
			if (GENAPI_E_OK == res) return 1;
			else return 0;
		}
	}

	else if (2 == DevNum)
	{
		res = InitCamera(hTopDev, "UPCamera", &TopimgBuf, id[0]);
		if (GENAPI_E_OK != res) { flag &= ~2; }
		res = InitCamera(hBottomDev, "BottomCamera", &BottomimgBuf, id[1]);
		if (GENAPI_E_OK != res) { flag &= ~1; }
		return flag;
	}

	else
		return 0;
}


bool Basler::TopGrab(unsigned char** imgBuf, int& width, int& height)		//注意,源地址会被修改，目的是为了加快速度，如果多线程都使用这个指针会发生崩溃
{
	if (2 != (2 & CameraAlive))
	{
		*imgBuf = NULL;
		width = 0;
		height = 0;
		return false;
	}
	
	std::lock_guard<std::mutex> l_lock(g_top_lk);
	if (!Grab(hTopDev, &TopimgBuf, width, height))
	{
		*imgBuf = NULL;
		width = 0;
		height = 0;
		return false;
	}
	*imgBuf = (unsigned char*)malloc(width*height*sizeof(char));
	memcpy(*imgBuf, TopimgBuf, width*height);
	return true;
}

bool Basler::BottomGrab(unsigned char** imgBuf, int& width, int& height)
{
	if (1 != (1 & CameraAlive))
	{
		*imgBuf = NULL;
		width = 0;
		height = 0;
		return false;
	}

	std::lock_guard<std::mutex> l_lock(g_bottom_lk);	//线程锁，只让一个线程调用这个函数
	if (!Grab(hBottomDev, &BottomimgBuf, width, height))
	{
		*imgBuf = NULL;
		width = 0;
		height = 0;
		return false;
	}
	*imgBuf = (unsigned char*)malloc(width*height * sizeof(char));
	memcpy(*imgBuf, BottomimgBuf, width*height);
	//*imgBuf = BottomimgBuf;
	return true;
}

































/* This function demonstrates how to retrieve the error message for the last failed
function call. */
void Basler::printErrorAndExit(GENAPIC_RESULT errc)
{
	char *errMsg;
	size_t length;

	/* Retrieve the error message.
	... Find out first how big the buffer must be, */
	GenApiGetLastErrorMessage(NULL, &length);
	errMsg = (char*)malloc(length);
	/* ... and retrieve the message. */
	GenApiGetLastErrorMessage(errMsg, &length);

	fprintf(stderr, "%s (%#08x).\n", errMsg, (unsigned int)errc);
	free(errMsg);

	/* Retrieve more details about the error.
	... Find out first how big the buffer must be, */
	GenApiGetLastErrorDetail(NULL, &length);
	errMsg = (char*)malloc(length);
	/* ... and retrieve the message. */
	GenApiGetLastErrorDetail(errMsg, &length);

	fprintf(stderr, "%s\n", errMsg);
	free(errMsg);

	PylonTerminate();  /* Releases all pylon resources. */

	exit(EXIT_FAILURE);
}



/* Simple "image processing" function returning the minimum and maximum gray
value of an 8 bit gray value image. */
void Basler::getMinMax(const unsigned char* pImg, int32_t width, int32_t height,
	unsigned char* pMin, unsigned char* pMax)
{
	unsigned char min = 255;
	unsigned char max = 0;
	unsigned char val;
	const unsigned char *p;

	for (p = pImg; p < pImg + width * height; p++)
	{
		val = *p;
		if (val > max)
			max = val;
		if (val < min)
			min = val;
	}
	*pMin = min;
	*pMax = max;
}

/* This function can be used to wait for user input at the end of the sample program. */
/**
void Basler::pressEnterToExit(void)
{
	//fprintf(stderr, "\nPress enter to exit.\n");
	//while (getchar() != '\n');
	return;
}
*/

