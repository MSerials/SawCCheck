// Controller.cpp : 实现文件
//

#include "stdafx.h"
#include "SawChain_Check.h"
#include "Controller.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "Instruction.h"



// Controller 对话框

IMPLEMENT_DYNAMIC(Controller, CDialogEx)

Controller::Controller(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SYSCTRL, pParent)
{

}

Controller::~Controller()
{
}

void Controller::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Controller, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CONVEYORCW, &Controller::OnBnClickedButtonConveyorcw)
	ON_BN_CLICKED(IDC_BUTTON_CONVEYORCCW, &Controller::OnBnClickedButtonConveyorccw)
	ON_BN_CLICKED(IDC_BUTTON_CONVEYORSTOP, &Controller::OnBnClickedButtonConveyorstop)
	ON_BN_CLICKED(IDC_BUTTON_PRESS_CYL, &Controller::OnBnClickedButtonPressCyl)
	ON_BN_CLICKED(IDC_BUTTON_PUSH_CYL, &Controller::OnBnClickedButtonPushCyl)
	ON_BN_CLICKED(IDC_BUTTON_MAGNET_CYL, &Controller::OnBnClickedButtonMagnetCyl)
	ON_BN_CLICKED(IDC_BUTTON_MARK_CYL, &Controller::OnBnClickedButtonMarkCyl)
	ON_BN_CLICKED(IDC_BUTTON_MAGNET, &Controller::OnBnClickedButtonMagnet)
	ON_BN_CLICKED(IDC_BUTTON_ALERTSTOP, &Controller::OnBnClickedButtonAlertstop)
	ON_BN_CLICKED(IDC_BUTTON1, &Controller::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_CCW, &Controller::OnBnClickedButtonCcw)
	ON_BN_CLICKED(IDC_BUTTON_CW, &Controller::OnBnClickedButtonCw)
	ON_BN_CLICKED(IDC_BUTTON_INSTRUCTION, &Controller::OnBnClickedButtonInstruction)
	ON_BN_CLICKED(IDC_BUTTON_ISMARK, &Controller::OnBnClickedButtonIsmark)
END_MESSAGE_MAP()


// Controller 消息处理程序


void Controller::OnBnClickedButtonConveyorcw()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = NULL; mc = pMain->SCM.CurrentMotionCard();
	if ((NULL == mc) || (CONVEYOR_CW == mc->GetConveyorState()))	return;							//如果没有板卡，则尽量不发生错误
	if (CONVEYOR_CCW == mc->GetConveyorState())
	{
		mc->ConveyorSTOP();
		Sleep(500);
	}//输送带不能够急着改变方向
	mc->ConveyorCW();
}


void Controller::OnBnClickedButtonConveyorccw()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = NULL; mc = pMain->SCM.CurrentMotionCard();
	if ((NULL == mc) ||(CONVEYOR_CCW == mc->GetConveyorState()))	return;
	if (CONVEYOR_CW == mc->GetConveyorState())
	{
		mc->ConveyorSTOP();
		Sleep(500);
	}//输送带不能够急着改变方向									//输送带不能够急着改变方向
	mc->ConveyorCCW();
}


void Controller::OnBnClickedButtonConveyorstop()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc)	return;
	mc->ConveyorSTOP();
}


void Controller::OnBnClickedButtonPressCyl()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc) return;
	if (mc->ReadOutPutBit(OUT_CYL_Press))
	{
		GetDlgItem(IDC_BUTTON_PRESS_CYL)->SetWindowText(L"压紧气缸收回");
		LOOP mc->WriteOutPutBit(OUT_CYL_Press, 0);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PRESS_CYL)->SetWindowText(L"压紧气缸推出");
		LOOP mc->WriteOutPutBit(OUT_CYL_Press, 1);
	}
}


void Controller::OnBnClickedButtonPushCyl()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc) return;
	if (mc->ReadOutPutBit(OUT_CYL_Push))
	{
		GetDlgItem(IDC_BUTTON_PUSH_CYL)->SetWindowText(L"打断气缸收回");
		LOOP mc->WriteOutPutBit(OUT_CYL_Push, 0);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PUSH_CYL)->SetWindowText(L"打断气缸推出");
		LOOP mc->WriteOutPutBit(OUT_CYL_Push, 1);
	}
}


void Controller::OnBnClickedButtonMagnetCyl()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc) return;
	if (mc->ReadOutPutBit(OUT_CYL_MAGNET))
	{
		GetDlgItem(IDC_BUTTON_MAGNET_CYL)->SetWindowText(L"吸扣气缸收回");
		LOOP mc->WriteOutPutBit(OUT_CYL_MAGNET, 0);
		
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MAGNET_CYL)->SetWindowText(L"吸扣气缸推出");
		LOOP mc->WriteOutPutBit(OUT_CYL_MAGNET, 1);
	}
}


void Controller::OnBnClickedButtonMarkCyl()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc) return;
	if (mc->ReadOutPutBit(OUT_CYL_MARK))
	{
		
		GetDlgItem(IDC_BUTTON_MARK_CYL)->SetWindowText(L"打标气缸收回");
		LOOP mc->WriteOutPutBit(OUT_CYL_MARK, 0);
		
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MARK_CYL)->SetWindowText(L"打标气缸推出");
		LOOP mc->WriteOutPutBit(OUT_CYL_MARK, 1);
	}
}


void Controller::OnBnClickedButtonMagnet()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc) return;
	if (mc->ReadOutPutBit(OUT_Magnet))
	{
		GetDlgItem(IDC_BUTTON_MAGNET)->SetWindowText(L"磁铁断电");
		
		LOOP mc->WriteOutPutBit(OUT_Magnet, 0);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MAGNET)->SetWindowText(L"磁铁通电");
		LOOP mc->WriteOutPutBit(OUT_Magnet, 1);
	}

}


BOOL Controller::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateUI();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void Controller::UpdateUI()
{
	CString str;
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();


	if (!pMain->sys.m_isAlertStop)
		GetDlgItem(IDC_BUTTON_ALERTSTOP)->SetWindowText(L"已是报错停机测试状态");
	else
		GetDlgItem(IDC_BUTTON_ALERTSTOP)->SetWindowText(L"不是报警停机状态");


	if (pMain->sys.m_isNotMark)
	{
		GetDlgItem(IDC_BUTTON_ISMARK)->SetWindowText(L"不是打标状态");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_ISMARK)->SetWindowText(L"已是打标状态");
	}

	str.Format(L"%d", pMain->ini.MaxVel);
	GetDlgItem(IDC_EDIT_MAXVEL)->SetWindowText(str);
	str.Format(L"%f", pMain->ini.Tacc);
	GetDlgItem(IDC_EDIT_TACC)->SetWindowText(str);

	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc) {
		str = L"没有运动卡";
		GetDlgItem(IDC_BUTTON_PRESS_CYL)->SetWindowText(str);
		GetDlgItem(IDC_BUTTON_MAGNET_CYL)->SetWindowText(str);
		GetDlgItem(IDC_BUTTON_PUSH_CYL)->SetWindowText(str);
		GetDlgItem(IDC_BUTTON_MAGNET)->SetWindowText(str);
		GetDlgItem(IDC_BUTTON_MARK_CYL)->SetWindowText(str);
		GetDlgItem(IDC_EDIT_WAVES)->GetWindowText(str);
		return ;
	}

	str.Format(_T("%d"), pMain->ini.waves);
	GetDlgItem(IDC_EDIT_WAVES)->SetWindowText(str);

	if (mc->ReadOutPutBit(OUT_CYL_MAGNET))
	{
		GetDlgItem(IDC_BUTTON_MAGNET_CYL)->SetWindowText(L"吸扣气缸推出");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MAGNET_CYL)->SetWindowText(L"吸扣气缸收回 "); 
	}

	if (mc->ReadOutPutBit(OUT_CYL_MARK))
	{
		GetDlgItem(IDC_BUTTON_MARK_CYL)->SetWindowText(L"打标气缸推出");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MARK_CYL)->SetWindowText(L"打标气缸收回");
	}

	if (mc->ReadOutPutBit(OUT_Magnet))
	{
		GetDlgItem(IDC_BUTTON_MAGNET)->SetWindowText(L"磁铁通电");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MAGNET)->SetWindowText(L"磁铁断电");
	}

	if (mc->ReadOutPutBit(OUT_CYL_Press))
	{
		GetDlgItem(IDC_BUTTON_PRESS_CYL)->SetWindowText(L"压紧气缸推出");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PRESS_CYL)->SetWindowText(L"压紧气缸收回");
	}

	if (mc->ReadOutPutBit(OUT_CYL_Push))
	{
		GetDlgItem(IDC_BUTTON_PUSH_CYL)->SetWindowText(L"打断气缸推出");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PUSH_CYL)->SetWindowText(L"打断气缸收回");
	}
}


void Controller::OnBnClickedButtonAlertstop()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	if (!pMain->sys.m_isAlertStop)
	{ 
		GetDlgItem(IDC_BUTTON_ALERTSTOP)->SetWindowText(L"不是报警停机状态");
	
		pMain->sys.m_isAlertStop = TRUE;
	}
	else
	{
		GetDlgItem(IDC_BUTTON_ALERTSTOP)->SetWindowText(L"已是报错停机测试状态");
		pMain->sys.m_isAlertStop = FALSE;
	}
	pMain->sys.SaveParaFile(PARA_PRJ);
}


void Controller::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CString str;
	GetDlgItem(IDC_EDIT_MAXVEL)->GetWindowText(str);
	pMain->ini.MaxVel = _ttoi(str);
	if (pMain->ini.MaxVel > 52000)
	{
		pMain->ini.MaxVel = 52000;
		str.Format(_T("%d"), pMain->ini.MaxVel);
		GetDlgItem(IDC_EDIT_MAXVEL)->SetWindowText(str);
	}

	GetDlgItem(IDC_EDIT_TACC)->GetWindowText(str);
	pMain->ini.Tacc = _ttof(str);
	GetDlgItem(IDC_EDIT_WAVES)->GetWindowText(str);
	pMain->ini.waves = _ttoi(str);	
	pMain->ini.SaveParaFile(PARA_IMAGE);
}


void Controller::OnBnClickedButtonCcw()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CMotionCard * mc = pMainFrm->SCM.CurrentMotionCard();
	if (nullptr == mc)	return ;
	mc->StartTMove(0, pMainFrm->ini.waves, 500, pMainFrm->ini.MaxVel, pMainFrm->ini.Tacc);
	return;

	DWORD newbit = mc->ReadInPutBit(IN_Start_Camera_SENSOR);
	DWORD oldbit = newbit;
	DWORD tick = GetTickCount();

	mc->StartTVMove(0, 500, pMainFrm->ini.MaxVel, pMainFrm->ini.Tacc);

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
			mc->EStopMove(0);;
			break;
		}

		oldbit = newbit;
	}

}


void Controller::OnBnClickedButtonCw()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CMotionCard * mc = pMainFrm->SCM.CurrentMotionCard();
	if (nullptr == mc)	return ;
	mc->StartTMove(0, -pMainFrm->ini.waves, 500, pMainFrm->ini.MaxVel, pMainFrm->ini.Tacc);
	return;

	DWORD newbit = mc->ReadInPutBit(IN_Start_Camera_SENSOR);
	DWORD oldbit = newbit;
	DWORD tick = GetTickCount();

	mc->StartTVMove(0, -500, -pMainFrm->ini.MaxVel, pMainFrm->ini.Tacc);

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


void Controller::OnBnClickedButtonInstruction()
{
	// TODO: 在此添加控件通知处理程序代码
	Instruction ins;
	ins.DoModal();
}


void Controller::OnBnClickedButtonIsmark()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	if (!pMain->sys.m_isNotMark)
	{
		GetDlgItem(IDC_BUTTON_ISMARK)->SetWindowText(L"不是打标状态");
		pMain->sys.m_isNotMark = TRUE;
	}
	else
	{
		GetDlgItem(IDC_BUTTON_ISMARK)->SetWindowText(L"已是打标状态");
		pMain->sys.m_isNotMark = FALSE;
	}
	pMain->sys.SaveParaFile(PARA_PRJ);
}
