// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "SawChain_Check.h"

#include "Controller.h"
#include "MainFrm.h"
#include "Tool.h"
#include "ImageCard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_FILE_PRINT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnUpdateFilePrintPreview)
	ON_COMMAND(ID_BUTTON_SYSCTRL, &CMainFrame::OnButtonSysctrl)
	ON_COMMAND(ID_BUTTON_SHOWTABLE, &CMainFrame::OnButtonShowtable)
	ON_COMMAND(ID_BUTTON_MOVEBACKWARD, &CMainFrame::OnButtonMovebackward)
	//ON_COMMAND(ID_BUTTON_FOWARD, &CMainFrame::OnButtonFoward)
	ON_WM_CLOSE()
	ON_COMMAND(ID_BUTTON_FWD, &CMainFrame::OnButtonFwd)
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);


	HANDLE hObject = ::CreateMutex(NULL, FALSE, _T("SawChain_Check0.9.12"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hObject);
		AfxMessageBox(L"程序已经运行，请勿多开。如果前一个看不见，请打开任务管理器，将进程掐掉");
		exit(0);
	}

	pTopView = NULL;
	pBottomView = NULL;
	/*
	1.设置好文件夹 sys用于保存系统状态和log
	2.做好配置文件
	*/

	win_tool wt;
	CString AppPath = wt.AppPath();
	CString SysPath = AppPath + L"\\" + L"sys";
	sys.SetIniDir(SysPath, false);
	if (0 == sys.SetIniFile(L"PrgParameter.ini"))
	{
		sys.initData();
		sys.SaveParaFile(PARA_PRJ|PARA_IO);
	}
	sys.LoadParaFile(PARA_PRJ | PARA_IO);


	if (sys.m_Prj_Vector.IsEmpty()) { sys.m_Prj_Vector = L"example"; sys.SaveParaFile(PARA_PRJ); }
	vector<CString> strvec = wt.SplitCString(sys.m_Prj_Vector, L",");

	//bug??
	if (static_cast<size_t>(sys.m_Prj_Index) >= strvec.size()) { sys.m_Prj_Index = 0; sys.SaveParaFile(PARA_PRJ); }
	//sys.m_Prj_Name = strvec[sys.m_Prj_Index];	
	CString PrjPath = AppPath + L"\\" + strvec[sys.m_Prj_Index];

	ini.SetIniDir(PrjPath, false);
	if (0 == ini.SetIniFile(L"PrgParameter.ini"))
	{
		ini.initData();
		ini.SaveParaFile(PARA_IMAGE);
	}
	ini.LoadParaFile(PARA_IMAGE);

	//坑
	RefreshMotionCardDefination();
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	//
	if (!m_DockOperation.Create(_T("控制面板"), this, CRect(0, 0, 600, 1080), TRUE, 1001, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI
		, AFX_CBRS_REGULAR_TABS |  AFX_CBRS_RESIZE,  AFX_CBRS_FLOAT | AFX_CBRS_CLOSE  //| AFX_CBRS_AUTO_ROLLUP //| AFX_CBRS_FLOAT
	))
	{
		TRACE0("Failed to create LeftPane\n");
		return -1;
	}

	m_DockOperation.LoadState(FALSE);
	m_DockOperation.SetAutoHideMode(FALSE, NULL, NULL, NULL);
	m_DockOperation.EnableDocking(CBRS_ALIGN_RIGHT | CBRS_ALIGN_LEFT);
	DockPane(&m_DockOperation);
	m_TabCtrl.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 1920, 1080), &m_DockOperation, 125);
	m_TabCtrl.InitData();




#ifdef _TEST
#pragma warning(disable: 4996)
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif // DEBUG


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式




	


	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}


void CMainFrame::OnFilePrint()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CMainFrame::OnFilePrintPreview()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // 强制关闭“打印预览”模式
	}
}

void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(IsPrintPreview());
}


void CMainFrame::OnButtonSysctrl()
{
	// TODO: 在此添加命令处理程序代码
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(system_control::GetIns()->evt_process, 1))	return;
	Controller ctrldlg;
	SCM.system_pause();
	ctrldlg.DoModal();
}

void CMainFrame::RefreshMotionCardDefination()
{
	g_RailLenght = sys.g_RailLenght;
	IN_Start_Camera_SENSOR = sys.IN_Start_Camera_SENSOR;
	IN_CHECK_BREAK = sys.IN_CHECK_BREAK;
	IN_Check_UP_TIPPEDUP = sys.IN_Check_UP_TIPPEDUP;
	IN_CYL_Magnet_SENSOR = sys.IN_CYL_Magnet_SENSOR;
	IN_Check_BT_TIPPEDUP = sys.IN_Check_BT_TIPPEDUP;
	IN_START_BTN = sys.IN_START_BTN;
	IN_BTN_STOP = sys.IN_BTN_STOP;
	IN_Check_Double_Sword2 = sys.IN_Check_Double_Sword2;
	IN_CYL_Mark3_UP_SENSOR = sys.IN_CYL_Mark3_UP_SENSOR;
	IN_CHECK_SENSOR = sys.IN_CHECK_SENSOR;
	IN_DIED_KNOED_SENSOR = sys.IN_DIED_KNOED_SENSOR;
	IN_Check_Double_Sword1 = sys.IN_Check_Double_Sword1;
	IN_CYL_Mark1_UP_SENSOR = sys.IN_CYL_Mark1_UP_SENSOR;
	IN_Foot_Switch = sys.IN_Foot_Switch;
	IN_CYL_Mark2_UP_SENSOR = sys.IN_CYL_Mark2_UP_SENSOR;
	IN_CHECK_SENSOR1 = sys.IN_CHECK_SENSOR1;
	IN_CYL_Press_UP_SENSOR = sys.IN_CYL_Press_UP_SENSOR;
	IN_ESTOP_BTN = sys.IN_ESTOP_BTN;
	IN_Check_UP_DaJi = sys.IN_Check_UP_DaJi;
	IN_Check_BT_DaJi = sys.IN_Check_BT_DaJi;
	IN_CYL_Push_UP_SENSOR = sys.IN_CYL_Push_UP_SENSOR;

	g_UpTippedPos = sys.g_UpTippedPos;
	g_BtTippedPos = sys.g_BtTippedPos;
	g_UpCameraPos = sys.g_UpCameraPos;
	g_BtDaJiPos = sys.g_BtDaJiPos;
	g_UpDaJiPos = sys.g_UpDaJiPos;
	g_DoubleKnifePos = sys.g_DoubleKnifePos;
	g_DoubleKnifePos1 = sys.g_DoubleKnifePos1;
	g_BtCameraPos = sys.g_BtCameraPos;
	g_Mark1CylinderPos = sys.g_Mark1CylinderPos;
	g_Mark2CylinderPos = sys.g_Mark2CylinderPos;
	g_MarkPos = sys.g_MarkPos;
	g_ThirdDiedKnodePos = sys.g_ThirdDiedKnodePos;






	//选取任意两个参数进行比较
	if (0 == g_RailLenght
		|| g_MarkPos == g_ThirdDiedKnodePos
		) 
	{ AfxMessageBox(L"配置文件读取失败，请重新设置，设置方法可以删除sys文件夹，再打开文件，然后重新设置参数"); }
}

BOOL CMainFrame::Resize()
{
	CWnd * ClientCWnd = this;
	CRect rect;
	ClientCWnd->GetClientRect(&rect);
	int ControlWidth = 0;
	const int TotalWidth = rect.right;
	int ViewWidth = rect.Width();// (TotalWidth - ControlWidth) / 2;
	int ViewHeight = (rect.Height()-184) / 2;
	m_wndSplitter.SetRowInfo(0, ViewHeight, 0);
	m_wndSplitter.SetRowInfo(1, ViewHeight, 0);
	m_wndSplitter.SetColumnInfo(0, ViewWidth, 80);
	m_wndSplitter.SetColumnInfo(1, ViewWidth, 80);
	m_wndSplitter.RecalcLayout();
	CRect rt(0, 0, ViewWidth, ViewHeight);
	//因为要在得到图形后才能初始化相机
	CImageCard::GetIns()->InitWindow(pTview->m_hWnd, pTview->get_rect(), pBview->m_hWnd, pBview->get_rect());
	sccErrorCode error = SCM.Init();
	if (SCM.mc_vector.size() == 0) system_control::GetIns()->system_error |= NOCARD;
	return TRUE;
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (!m_wndSplitter.CreateStatic(this, 2, 1))
		return FALSE;
	m_DockOperation.ShowPane(TRUE, FALSE, TRUE);

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(TopView), CSize(100, 100), pContext)) return FALSE;
	if (!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(BottomView), CSize(100, 100), pContext)) return FALSE;

	if (!pTopView) pTopView = (CView*)this->m_wndSplitter.GetPane(0, 0);
	if (!pBottomView) pBottomView = (CView*)this->m_wndSplitter.GetPane(1, 0);
	return TRUE;
	return CFrameWndEx::OnCreateClient(lpcs, pContext);
}


void CMainFrame::OnButtonShowtable()
{
	// TODO: 在此添加命令处理程序代码
	m_DockOperation.ShowPane(TRUE,FALSE,TRUE);
}


void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (AfxMessageBox(L"退出应用程序？", MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)  return;
	system_control::GetIns()->is_top_grab = false;
	system_control::GetIns()->is_bottom_grab = false;
	//CImageCard::GetIns()->CloseCamera();
	if (nullptr != SCM.CurrentMotionCard())
	{
		system_control::GetIns()->isStopScan = true;
		SCM.CurrentMotionCard()->board_close();	
		Sleep(500);
	}
	//PostQuitMessage(0); 
	CFrameWndEx::OnClose();
}


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	static int isRun = 0;
	if (pMsg->message == WM_KEYDOWN)
	{
		//为脚踏开关增加暂停功能
		if (pMsg->wParam == VK_SPACE /*|| pMsg-> wParam == KEY_TABLE_1 || pMsg-> wParam == KEY_TABLE_1 */)
		{
			try {
				HWND hwnd = ::FindWindowEx(NULL, NULL, NULL, L"SawChain_Check");
				if (hwnd)	EndDialog(hwnd, FALSE);

				if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return TRUE; }
				int state = SCM.push_button(SYS_STATE);
				if (START != state) SCM.push_button(START);
				else SCM.push_button(PAUSE);
			}
			catch (...)
			{
				return TRUE;
			}
		}

	}
	return CFrameWndEx::PreTranslateMessage(pMsg);
}



void CMainFrame::OnButtonMovebackward()
{
	// TODO: 在此添加命令处理程序代码
	CMotionCard * mc = SCM.CurrentMotionCard();
	if (nullptr == mc)	return;
	Halcon::set_check("~give_error");
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(system_control::GetIns()->evt_process, 1))	return;
	mc->StartTMove(0, -ini.waves, 500, ini.MaxVel, ini.Tacc);
	if (mc->WaitMotorDoneTimeOut(0, 2000)) { Sleep(200); }
	try {
		CImageCard::GetIns()->Image1 = CImageCard::GetIns()->GetBottomImage();
		CImageCard::GetIns()->Image = CImageCard::GetIns()->GetTopImage();
		CImageCard::GetIns()->Bottom_Disp_Obj(CImageCard::GetIns()->Image1);
		CImageCard::GetIns()->Top_Disp_Obj(CImageCard::GetIns()->Image);
	}
	catch (Halcon::HException e)
	{
		printf("%s\n", e.message);
	}
	return;

	DWORD newbit = mc->ReadInPutBit(IN_Start_Camera_SENSOR);
	DWORD oldbit = newbit;
	DWORD tick = GetTickCount();

	mc->StartTVMove(0, -500, -ini.MaxVel, ini.Tacc);

	for (;;)
	{
		if ((GetTickCount() - tick) > 1000)
		{
			//system_control::GetIns()->system_error |= NEEDORIGIN;
			mc->EStopMove(0);
			AfxMessageBox(L"超时");
			break;
		}

		if (WAIT_OBJECT_0 == ::WaitForSingleObject(system_control::GetIns()->evt_EStop, 0))
		{
			//system_control::GetIns()->system_error |= NEEDORIGIN;
			mc->EStopMove(0);
			AfxMessageBox(L"急停按钮按下");
			break;
		}

		newbit = mc->ReadInPutBit(IN_Start_Camera_SENSOR);

		if (newbit != oldbit && newbit)
		{
			//system_control::GetIns()->system_error |= NEEDORIGIN;
			mc->EStopMove(0);
			//AfxMessageBox(L"回原点成功 ");
			break;
		}

		oldbit = newbit;
	}
}



void CMainFrame::OnButtonFwd()
{
	// TODO: 在此添加命令处理程序代码
	CMotionCard * mc = SCM.CurrentMotionCard();
	if (nullptr == mc)	return;
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(system_control::GetIns()->evt_process, 1))	return;
	Halcon::set_check("~give_error");
	if (mc->BackToOrigin(0, 500, ini.MaxVel, ini.Tacc))
		return;
	try
	{
		Halcon::set_check("~give_error");
		CImageCard::GetIns()->Image1 = CImageCard::GetIns()->GetBottomImage();
		CImageCard::GetIns()->Image = CImageCard::GetIns()->GetTopImage();
		CImageCard::GetIns()->Bottom_Disp_Obj(CImageCard::GetIns()->Image1);
		CImageCard::GetIns()->Top_Disp_Obj(CImageCard::GetIns()->Image);
	}
	catch (Halcon::HException e)
	{
		printf("%s\n", e.message);
	}
}


void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	// TODO: 在此添加专用代码和/或调用基类
	SetWindowText(L"爱易特智能技术有限公司-油锯链检测机");
	CFrameWndEx::OnUpdateFrameTitle(bAddToTitle);
}
