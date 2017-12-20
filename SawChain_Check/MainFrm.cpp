// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ������� 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// MainFrm.cpp : CMainFrame ���ʵ��
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

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);


	HANDLE hObject = ::CreateMutex(NULL, FALSE, _T("SawChain_Check0.9.12"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hObject);
		AfxMessageBox(L"�����Ѿ����У�����࿪�����ǰһ����������������������������������");
		exit(0);
	}

	pTopView = NULL;
	pBottomView = NULL;
	/*
	1.���ú��ļ��� sys���ڱ���ϵͳ״̬��log
	2.���������ļ�
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

	//��
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
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// ���� Visual Studio 2005 ��ʽͣ��������Ϊ
	CDockingManager::SetDockingMode(DT_SMART);
	// ���� Visual Studio 2005 ��ʽͣ�������Զ�������Ϊ
	EnableAutoHidePanes(CBRS_ALIGN_ANY);
	// ���ڳ־�ֵ�����Ӿ�����������ʽ
	OnApplicationLook(theApp.m_nAppLook);

	//
	if (!m_DockOperation.Create(_T("�������"), this, CRect(0, 0, 600, 1080), TRUE, 1001, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI
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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ




	


	return TRUE;
}

// CMainFrame ���

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


// CMainFrame ��Ϣ�������

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
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // ǿ�ƹرա���ӡԤ����ģʽ
	}
}

void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(IsPrintPreview());
}


void CMainFrame::OnButtonSysctrl()
{
	// TODO: �ڴ���������������
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






	//ѡȡ���������������бȽ�
	if (0 == g_RailLenght
		|| g_MarkPos == g_ThirdDiedKnodePos
		) 
	{ AfxMessageBox(L"�����ļ���ȡʧ�ܣ����������ã����÷�������ɾ��sys�ļ��У��ٴ��ļ���Ȼ���������ò���"); }
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
	//��ΪҪ�ڵõ�ͼ�κ���ܳ�ʼ�����
	CImageCard::GetIns()->InitWindow(pTview->m_hWnd, pTview->get_rect(), pBview->m_hWnd, pBview->get_rect());
	sccErrorCode error = SCM.Init();
	if (SCM.mc_vector.size() == 0) system_control::GetIns()->system_error |= NOCARD;
	return TRUE;
}


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ���������������
	m_DockOperation.ShowPane(TRUE,FALSE,TRUE);
}


void CMainFrame::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (AfxMessageBox(L"�˳�Ӧ�ó���", MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)  return;
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
	// TODO: �ڴ����ר�ô����/����û���
	static int isRun = 0;
	if (pMsg->message == WM_KEYDOWN)
	{
		//Ϊ��̤����������ͣ����
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
	// TODO: �ڴ���������������
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
			AfxMessageBox(L"��ʱ");
			break;
		}

		if (WAIT_OBJECT_0 == ::WaitForSingleObject(system_control::GetIns()->evt_EStop, 0))
		{
			//system_control::GetIns()->system_error |= NEEDORIGIN;
			mc->EStopMove(0);
			AfxMessageBox(L"��ͣ��ť����");
			break;
		}

		newbit = mc->ReadInPutBit(IN_Start_Camera_SENSOR);

		if (newbit != oldbit && newbit)
		{
			//system_control::GetIns()->system_error |= NEEDORIGIN;
			mc->EStopMove(0);
			//AfxMessageBox(L"��ԭ��ɹ� ");
			break;
		}

		oldbit = newbit;
	}
}



void CMainFrame::OnButtonFwd()
{
	// TODO: �ڴ���������������
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
	// TODO: �ڴ����ר�ô����/����û���
	SetWindowText(L"���������ܼ������޹�˾-�;�������");
	CFrameWndEx::OnUpdateFrameTitle(bAddToTitle);
}
