// Controller.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SawChain_Check.h"
#include "Controller.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "Instruction.h"



// Controller �Ի���

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


// Controller ��Ϣ�������


void Controller::OnBnClickedButtonConveyorcw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = NULL; mc = pMain->SCM.CurrentMotionCard();
	if ((NULL == mc) || (CONVEYOR_CW == mc->GetConveyorState()))	return;							//���û�а忨����������������
	if (CONVEYOR_CCW == mc->GetConveyorState())
	{
		mc->ConveyorSTOP();
		Sleep(500);
	}//���ʹ����ܹ����Ÿı䷽��
	mc->ConveyorCW();
}


void Controller::OnBnClickedButtonConveyorccw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = NULL; mc = pMain->SCM.CurrentMotionCard();
	if ((NULL == mc) ||(CONVEYOR_CCW == mc->GetConveyorState()))	return;
	if (CONVEYOR_CW == mc->GetConveyorState())
	{
		mc->ConveyorSTOP();
		Sleep(500);
	}//���ʹ����ܹ����Ÿı䷽��									//���ʹ����ܹ����Ÿı䷽��
	mc->ConveyorCCW();
}


void Controller::OnBnClickedButtonConveyorstop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc)	return;
	mc->ConveyorSTOP();
}


void Controller::OnBnClickedButtonPressCyl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc) return;
	if (mc->ReadOutPutBit(OUT_CYL_Press))
	{
		GetDlgItem(IDC_BUTTON_PRESS_CYL)->SetWindowText(L"ѹ�������ջ�");
		LOOP mc->WriteOutPutBit(OUT_CYL_Press, 0);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PRESS_CYL)->SetWindowText(L"ѹ�������Ƴ�");
		LOOP mc->WriteOutPutBit(OUT_CYL_Press, 1);
	}
}


void Controller::OnBnClickedButtonPushCyl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc) return;
	if (mc->ReadOutPutBit(OUT_CYL_Push))
	{
		GetDlgItem(IDC_BUTTON_PUSH_CYL)->SetWindowText(L"��������ջ�");
		LOOP mc->WriteOutPutBit(OUT_CYL_Push, 0);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PUSH_CYL)->SetWindowText(L"��������Ƴ�");
		LOOP mc->WriteOutPutBit(OUT_CYL_Push, 1);
	}
}


void Controller::OnBnClickedButtonMagnetCyl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc) return;
	if (mc->ReadOutPutBit(OUT_CYL_MAGNET))
	{
		GetDlgItem(IDC_BUTTON_MAGNET_CYL)->SetWindowText(L"���������ջ�");
		LOOP mc->WriteOutPutBit(OUT_CYL_MAGNET, 0);
		
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MAGNET_CYL)->SetWindowText(L"���������Ƴ�");
		LOOP mc->WriteOutPutBit(OUT_CYL_MAGNET, 1);
	}
}


void Controller::OnBnClickedButtonMarkCyl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc) return;
	if (mc->ReadOutPutBit(OUT_CYL_MARK))
	{
		
		GetDlgItem(IDC_BUTTON_MARK_CYL)->SetWindowText(L"��������ջ�");
		LOOP mc->WriteOutPutBit(OUT_CYL_MARK, 0);
		
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MARK_CYL)->SetWindowText(L"��������Ƴ�");
		LOOP mc->WriteOutPutBit(OUT_CYL_MARK, 1);
	}
}


void Controller::OnBnClickedButtonMagnet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc) return;
	if (mc->ReadOutPutBit(OUT_Magnet))
	{
		GetDlgItem(IDC_BUTTON_MAGNET)->SetWindowText(L"�����ϵ�");
		
		LOOP mc->WriteOutPutBit(OUT_Magnet, 0);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MAGNET)->SetWindowText(L"����ͨ��");
		LOOP mc->WriteOutPutBit(OUT_Magnet, 1);
	}

}


BOOL Controller::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UpdateUI();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

void Controller::UpdateUI()
{
	CString str;
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();


	if (!pMain->sys.m_isAlertStop)
		GetDlgItem(IDC_BUTTON_ALERTSTOP)->SetWindowText(L"���Ǳ���ͣ������״̬");
	else
		GetDlgItem(IDC_BUTTON_ALERTSTOP)->SetWindowText(L"���Ǳ���ͣ��״̬");


	if (pMain->sys.m_isNotMark)
	{
		GetDlgItem(IDC_BUTTON_ISMARK)->SetWindowText(L"���Ǵ��״̬");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_ISMARK)->SetWindowText(L"���Ǵ��״̬");
	}

	str.Format(L"%d", pMain->ini.MaxVel);
	GetDlgItem(IDC_EDIT_MAXVEL)->SetWindowText(str);
	str.Format(L"%f", pMain->ini.Tacc);
	GetDlgItem(IDC_EDIT_TACC)->SetWindowText(str);

	CMotionCard * mc = pMain->SCM.CurrentMotionCard();
	if (nullptr == mc) {
		str = L"û���˶���";
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
		GetDlgItem(IDC_BUTTON_MAGNET_CYL)->SetWindowText(L"���������Ƴ�");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MAGNET_CYL)->SetWindowText(L"���������ջ� "); 
	}

	if (mc->ReadOutPutBit(OUT_CYL_MARK))
	{
		GetDlgItem(IDC_BUTTON_MARK_CYL)->SetWindowText(L"��������Ƴ�");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MARK_CYL)->SetWindowText(L"��������ջ�");
	}

	if (mc->ReadOutPutBit(OUT_Magnet))
	{
		GetDlgItem(IDC_BUTTON_MAGNET)->SetWindowText(L"����ͨ��");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_MAGNET)->SetWindowText(L"�����ϵ�");
	}

	if (mc->ReadOutPutBit(OUT_CYL_Press))
	{
		GetDlgItem(IDC_BUTTON_PRESS_CYL)->SetWindowText(L"ѹ�������Ƴ�");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PRESS_CYL)->SetWindowText(L"ѹ�������ջ�");
	}

	if (mc->ReadOutPutBit(OUT_CYL_Push))
	{
		GetDlgItem(IDC_BUTTON_PUSH_CYL)->SetWindowText(L"��������Ƴ�");
	}
	else
	{
		GetDlgItem(IDC_BUTTON_PUSH_CYL)->SetWindowText(L"��������ջ�");
	}
}


void Controller::OnBnClickedButtonAlertstop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	if (!pMain->sys.m_isAlertStop)
	{ 
		GetDlgItem(IDC_BUTTON_ALERTSTOP)->SetWindowText(L"���Ǳ���ͣ��״̬");
	
		pMain->sys.m_isAlertStop = TRUE;
	}
	else
	{
		GetDlgItem(IDC_BUTTON_ALERTSTOP)->SetWindowText(L"���Ǳ���ͣ������״̬");
		pMain->sys.m_isAlertStop = FALSE;
	}
	pMain->sys.SaveParaFile(PARA_PRJ);
}


void Controller::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
			mc->EStopMove(0);;
			break;
		}

		oldbit = newbit;
	}

}


void Controller::OnBnClickedButtonCw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


void Controller::OnBnClickedButtonInstruction()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Instruction ins;
	ins.DoModal();
}


void Controller::OnBnClickedButtonIsmark()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame * pMain = (CMainFrame *)AfxGetMainWnd();
	if (!pMain->sys.m_isNotMark)
	{
		GetDlgItem(IDC_BUTTON_ISMARK)->SetWindowText(L"���Ǵ��״̬");
		pMain->sys.m_isNotMark = TRUE;
	}
	else
	{
		GetDlgItem(IDC_BUTTON_ISMARK)->SetWindowText(L"���Ǵ��״̬");
		pMain->sys.m_isNotMark = FALSE;
	}
	pMain->sys.SaveParaFile(PARA_PRJ);
}
