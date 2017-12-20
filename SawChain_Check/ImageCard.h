#pragma once
#include "globle.h"
#include "third_party\basler\basler.h"
//#include <mutex>


#ifndef ___IMAGE__CARD___
#define ___IMAGE__CARD___



class CImageCard
{
private:
	CImageCard();
	
	//static UINT DelayInit(LPVOID lp);
	static UINT TopGrab(LPVOID lp);
	static UINT BottomGrab(LPVOID lp);
	
	//Halcon::Hobject TopSnap();
	//Halcon::Hobject BottomSnap();

	UINT m_errorinfo;
	struct _Controller
	{
		_Controller() {
			isGrab = false;
			isGrab1 = false;
		}
		bool isGrab;
		bool isGrab1;

	};

	Basler * basler;

public:
	~CImageCard();
	static CImageCard * GetIns();
	bool InitCamera();
	int InitWindow(HWND Top, CRect TopRt, HWND Bottom, CRect BottomR);
	void Top_Disp_Obj(const Halcon::Hobject& obj);
	void Bottom_Disp_Obj(const Halcon::Hobject& obj);
	void CloseCamera();
	UINT ErrorInfo();

	CEvent evt_TopTrigger;
	CEvent evt_BottomTrigger;

	Halcon::Hobject GetTopImage();// { return Image; }
	Halcon::Hobject GetBottomImage();// { return Image1; }
	Halcon::Hobject	Image, Image1;
	
	Halcon::HTuple disp_hd, disp_hd1;
private:
	Halcon::HTuple AcqHandle, AcqHandle1;
	Halcon::HTuple WindowHandle, WindowHandle1;

	_Controller	Controller;
};



#endif // !___IMAGE__CARD___

