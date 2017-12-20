#pragma once

#include "include\pylonc\PylonC.h"


#ifndef _BASLER_CAM_
#define _BASLER_CAM_


class Basler{
private:
	//为了获取每个相机的index顺序
	int id[256];
	GENAPIC_RESULT          res;           /* Return value of pylon methods. */
	size_t                  numDevices;    /* Number of available devices. */
	PYLON_DEVICE_HANDLE     hDev;          /* Handle for the pylon device. */
	PYLON_DEVICE_HANDLE     hTopDev;          /* Handle for the pylon device. */
	PYLON_DEVICE_HANDLE     hBottomDev;          /* Handle for the pylon device. */
	const int				numGrabs; /* Number of images to grab. */
	int32_t                 payloadSize;   /* Size of an image frame in bytes. */
	unsigned char *			ImgBuff;
	unsigned char*          TopimgBuf;        /* Buffer used for grabbing. */
	unsigned char*			BottomimgBuf;
	BOOL                   isAvail;			//_Bool
	int                     i;
	int						CameraAlive;			//which camera is linked      10 is a binary and suggest that the first camera is alive but the second is not
	//这个函数不能对外开放，否则可能会卡死
	bool Grab(PYLON_DEVICE_HANDLE & hDev, unsigned char ** imgBuf, int& width, int& height);
public:
	Basler() 
		:numGrabs(10)
	{
		CameraAlive = 3;
		hTopDev = NULL;
		hBottomDev = NULL;
		TopimgBuf = NULL;
		BottomimgBuf = NULL;
		for (int i = 0; i < 256; i++) id[i] = -1;
	};
	
	~Basler();

	void printErrorAndExit(GENAPIC_RESULT errc);

	//void pressEnterToExit(void);
	//void printErrorAndExit(GENAPIC_RESULT errc);
	void getMinMax(const unsigned char* pImg, int32_t width, int32_t height,
		unsigned char* pMin, unsigned char* pMax);

	int InitCamera(PYLON_DEVICE_HANDLE & hDev, char * DevName, unsigned char** imgBuf, int index = 0);

	int CameraInit();

	bool TopGrab(unsigned char** imgBuf, int& width, int& height);

	bool BottomGrab(unsigned char** imgBuf, int& width, int& height);
};







#endif 


