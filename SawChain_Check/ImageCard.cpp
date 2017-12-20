#include "stdafx.h"
#include "ImageCard.h"
#include "MainFrm.h"
#include "TopView.h"
#include "BottomView.h"
#include "Lock.h"
using namespace Halcon;


CImageCard::CImageCard()
	:evt_TopTrigger(FALSE,TRUE)
	,evt_BottomTrigger(FALSE,TRUE)
{
	m_errorinfo = TOPCAMERANOTALREADY | BOTTOMCAMERANOTALREADY;
	disp_hd = NULL;
	disp_hd1 = NULL;
	WindowHandle = NULL;
	WindowHandle1 = NULL;
	Halcon::set_system("do_low_error", "false");
	basler = new Basler();
}

CImageCard::~CImageCard()
{
	delete basler;
}

CImageCard * CImageCard::GetIns()
{
	static CImageCard Ins;
	return &Ins;	
}

bool CImageCard::InitCamera()
{
	CWinThread* pTopCam = AfxBeginThread(TopGrab, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	if (pTopCam)
		return true;
	return false;
}



int CImageCard::InitWindow(HWND Top, CRect TopRt, HWND Bottom, CRect BottomR)
{
	if (Bottom == NULL || Top == NULL) return 1;
	try {
		WindowHandle = (Hlong)Top;
			
		WindowHandle1 = (Hlong)Bottom;
			
		set_check("give_error");
		set_check("~father");
		Halcon::open_window(0, 0, TopRt.Width(), TopRt.Height(), WindowHandle, "visible", "", &disp_hd);;
		set_check("father");

		set_check("~father");
		Halcon::open_window(0, 0, BottomR.Width(), BottomR.Height(), WindowHandle1, "visible", "", &disp_hd1);
		set_check("father");

		HDevWindowStack::Push(WindowHandle);
		HDevWindowStack::Push(WindowHandle1);
	}
	catch (HException &except)
	{
		TRACE(except.message);
		CString str = (CString)(CStringA)(LPCSTR)except.message;
		AfxMessageBox(L"错误代码：" + str);
		return 1;
	}
	return 0;
}


void CImageCard::Top_Disp_Obj(const Halcon::Hobject & obj)
{
	try
	{
		GiveError;
		Hlong w, h;
		Halcon::get_image_pointer1(obj, NULL, NULL, &w, &h);
		HDevWindowStack::Push(disp_hd);
		HDevWindowStack::SetActive(disp_hd);
		Halcon::set_part(disp_hd, NULL, NULL, h, w);
		disp_obj(obj, disp_hd);
	}
	catch (HException &except)
	{
		TRACE(except.message);
		Halcon::set_tposition(disp_hd,0,1);
		Halcon::write_string(disp_hd, except.message);
	}
}

void CImageCard::Bottom_Disp_Obj(const Halcon::Hobject & obj)
{
	try
	{
		GiveError;
		HDevWindowStack::Push(disp_hd1);
		HDevWindowStack::SetActive(disp_hd1);
		Hlong w, h;
		Halcon::get_image_pointer1(obj, NULL, NULL, &w, &h);
		Halcon::set_part(disp_hd1, NULL, NULL, h, w);
		Halcon::disp_obj(obj, disp_hd1);
	}
	catch (HException &except)
	{
		TRACE(except.message);
		Halcon::set_tposition(disp_hd1, 0, 1);
		Halcon::write_string(disp_hd1, except.message);
	}
}


UINT CImageCard::ErrorInfo()
{
	return m_errorinfo;
}

Halcon::Hobject CImageCard::GetTopImage()
{
	try {
		Halcon::set_check("~give_error");
		int w = 0, h = 0; unsigned char *img = NULL;
		g_camera_lock.lock();
		if (basler->TopGrab(&img, w, h))
			Halcon::gen_image1(&Image, "byte", (Hlong)w, (Hlong)h, (Hlong)img);
		free(img);
		g_camera_lock.unlock();
		return Image;
	}
	catch (Halcon::HException &e)
	{
		printf("%s\n",e.message);
		return Halcon::Hobject();
	}
	
}

Halcon::Hobject CImageCard::GetBottomImage()
{
	try {
		Halcon::set_check("~give_error");
		int w, h; unsigned char *img = NULL;
		g_camera_lock.lock();
		if (basler->BottomGrab(&img, w, h))
			Halcon::gen_image1(&Image1, "byte", (Hlong)w, (Hlong)h, (Hlong)img);
		free(img);
		g_camera_lock.unlock();
		return Image1;
	}
	catch (Halcon::HException &e)
	{
		printf("%s\n", e.message);
		return Halcon::Hobject();
	}
	
}

UINT CImageCard::TopGrab(LPVOID lp)
{
	CImageCard * pC = (CImageCard*)lp;
	int res = pC->basler->CameraInit();// BaslerInit();
	CString ErrorStr;
	if (2 != (2 & res))	
		ErrorStr += L"  未能找到顶部相机 ";
	else
	{
		system_control::GetIns()->system_error &= ~TOPCAMERANOTALREADY;//消除相机错误，如果没有找到相机，则一直保留这个信号
	}
	if (1 != (1 & res))
		ErrorStr += L"  未能找到底部相机 ";
	else
	{
		system_control::GetIns()->system_error &= ~BOTTOMCAMERANOTALREADY;
	}
	if (!ErrorStr.IsEmpty())
	{
		AfxMessageBox(ErrorStr);
		return 1;
	}
	return 0;
}

UINT CImageCard::BottomGrab(LPVOID lp)
{
	return 0;
}

void CImageCard::CloseCamera()
{
	
}