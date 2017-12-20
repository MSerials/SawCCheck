// MainControl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SawChain_Check.h"
#include "MainControl.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "Tool.h"
#include "MotionCard.h"
#include <vector>

// CMainControl �Ի���

IMPLEMENT_DYNAMIC(CMainControl, CDialogEx)

CMainControl::CMainControl(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MAINCONTROL, pParent)
{
	isOrigin = false;
}

CMainControl::~CMainControl()
{
	MainControlDlg = NULL;
}

void CMainControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMainControl, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADDNEWPRJ, &CMainControl::OnBnClickedButtonAddnewprj)
	ON_CBN_SELCHANGE(IDC_COMBO_SEL_PRJ, &CMainControl::OnSelchangeComboSelPrj)
	ON_BN_CLICKED(IDC_BUTTON_CHAINLEN, &CMainControl::OnBnClickedButtonChainlen)
	ON_BN_CLICKED(IDC_BUTTON_ORIGIN, &CMainControl::OnBnClickedButtonOrigin)
	ON_MESSAGE(WM_MESSAGE_COUNTER, &CMainControl::ShowCounter)
END_MESSAGE_MAP()


//��Ϣ����
LRESULT CMainControl::ShowCounter(WPARAM wParam, LPARAM lParam)
{
	

	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	


	int counter = static_cast<int>(wParam);
	int ng_counter = static_cast<int>(lParam);

	//
	static int detected_chain = 0;
	int new_chain_order = counter/ pMainFrm->ini.m_ChainLength;
	static int old_chain_order = new_chain_order;
	if (new_chain_order != old_chain_order)
	{
		detected_chain++;
	}
	old_chain_order = new_chain_order;



	CString str;
	str.Format(L"%d",counter);
	GetDlgItem(IDC_EDIT_DETECTED)->SetWindowText(str);
	str.Format(L"%d", ng_counter);
	GetDlgItem(IDC_EDIT_NGCOUNTER)->SetWindowText(str);


	str.Format(L"%d", detected_chain);
	GetDlgItem(IDC_EDIT_CHAINORDER)->SetWindowText(str);
	str.Format(L"%d", system_control::GetIns()->ng_chain);
	GetDlgItem(IDC_EDIT_NGCHAINORDER)->SetWindowText(str);


	str.Format(_T("��������Ƭװ����%d"), system_control::GetIns()->tinv);// = tchar = tknife = binv = bchar = bknife = diedknode = doubleknife = tdaji = bdaji = 0;)
	GetDlgItem(IDC_STATIC_TPINV)->SetWindowTextW(str);
	
	str.Format(_T("�����ַ����ϣ�%d"), system_control::GetIns()->tchar);
	GetDlgItem(IDC_STATIC_TPCHAR)->SetWindowTextW(str);

	str.Format(_T("������Ƭδĥ��%d"), system_control::GetIns()->tknife);
	GetDlgItem(IDC_STATIC_TPKNIFE)->SetWindowTextW(str);

	str.Format(_T("�ײ�����Ƭװ����%d"), system_control::GetIns()->binv);
	GetDlgItem(IDC_STATIC_BTINV)->SetWindowTextW(str);

	str.Format(_T("�ײ��ַ����ϣ�%d"), system_control::GetIns()->bchar);
	GetDlgItem(IDC_STATIC_BTCHAR)->SetWindowTextW(str);

	str.Format(_T("�ײ���Ƭδĥ��%d"), system_control::GetIns()->bknife);
	GetDlgItem(IDC_STATIC_BTKNIFE)->SetWindowTextW(str);
	
	str.Format(_T("���᣺%d"), system_control::GetIns()->diedknode);
	GetDlgItem(IDC_STATIC_DIEKNODE)->SetWindowTextW(str);

	str.Format(_T("˫������%d"), system_control::GetIns()->doubleknife);
	GetDlgItem(IDC_STATIC_DOUBLEKNIFE)->SetWindowTextW(str);
		
	str.Format(_T("���������δí:%d"), system_control::GetIns()->tdaji);
	GetDlgItem(IDC_STATIC_TPDAJI)->SetWindowTextW(str);

	str.Format(_T("�ײ������δí:%d"), system_control::GetIns()->bdaji);
	GetDlgItem(IDC_STATIC_BTDAJI)->SetWindowTextW(str);
	return 0;
}

// CMainControl ��Ϣ�������


BOOL CMainControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	MainControlDlg = this->m_hWnd;
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_SEL_PRJ);// ->AddString(L"1");
	win_tool wt;
	vector<CString> prj = wt.SplitCString(pMainFrm->sys.m_Prj_Vector, L",");
	for (size_t i = 0; i < prj.size(); i++)
	{
		pBox->AddString(prj[i]);
	}
	pBox->SetCurSel(pMainFrm->sys.m_Prj_Index);
	UpdateUI();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CMainControl::OnBnClickedButtonAddnewprj()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(system_control::GetIns()->evt_process,1))		return;
	win_tool  wt;
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str;
	CString newprjname;
	GetDlgItem(IDC_EDIT_DETECTED2)->GetWindowText(newprjname);
	if (-1 != str.ReverseFind(','))
	{
		AfxMessageBox(L"���ܰ������·���: ,");
		return;
	}
	if (str.IsEmpty()) return;

	std::vector<CString> s = wt.SplitCString(pMainFrm->sys.m_Prj_Vector, L",");
	for (size_t i = 0; i < s.size(); i++)
	{
		if (!str.Compare(s[i]))
		{
			AfxMessageBox(L"�������б�������");
			return;
		}
	}
	pMainFrm->sys.m_Prj_Name = str;
	CString NewPrj;
	if(s.size() == 0)
		NewPrj = str;
	else
		NewPrj = L"," + str;

	pMainFrm->sys.m_Prj_Vector += NewPrj;
	pMainFrm->sys.m_Prj_Index = (int)s.size(); //�պõ����һ����Ŀ����
	pMainFrm->sys.SaveParaFile(PARA_PRJ);

	CString AppPath = wt.AppPath();
	CString PrjPath = AppPath + L"\\" + L"sys";

	PrjPath += wt.AppPath()+ L"\\" + newprjname;
	pMainFrm->ini.SetIniDir(PrjPath, false);
	if (0 == pMainFrm->ini.SetIniFile(L"PrgParameter.ini"))
	{
		pMainFrm->ini.initData();
		pMainFrm->ini.SaveParaFile(PARA_ALL);
	}
	pMainFrm->ini.LoadParaFile(PARA_ALL);
	CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_SEL_PRJ);
	pBox->AddString(str);
	vector<CString> prj = wt.SplitCString(pMainFrm->sys.m_Prj_Vector, L",");
	pBox->SetCurSel(pMainFrm->sys.m_Prj_Index);
	system_control::GetIns()->system_error |= NEEDORIGIN;
	UpdateUI();
	system_control::GetIns()->system_error |= NEEDORIGIN;
	AfxMessageBox(L"�½���Ŀ���븴λ��");
	/*
	if (!g.img_deal.read_params(g.prjini.m_Prj_Name))
	{
		g.Controller.SysState |= SYSNEEDORIGIN;
		AfxMessageBox(L"δ���뵽���ݣ��������ƴ�����Ķ���ѡ�����ѵ��ͼƬ�͵ײ�ѡ����ѵ��ͼƬ��");
	}
	*/
}


void CMainControl::OnSelchangeComboSelPrj()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(system_control::GetIns()->evt_process, 1))		return;
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	win_tool wt;
	CComboBox* pBox = (CComboBox*)GetDlgItem(IDC_COMBO_SEL_PRJ);
	int nSel = pBox->GetCurSel();
	// ����ѡ����������ȡ�����ַ���
	CString str;
	pBox->GetLBText(nSel, str);
	//bug 1
	pMainFrm->sys.m_Prj_Index = nSel;
	pMainFrm->sys.m_Prj_Name = str;
	CString PrjPath = wt.AppPath();
	CString AppPath = PrjPath + L"\\" + L"sys";

	pMainFrm->sys.SaveParaFile(PARA_PRJ);
	PrjPath += L"\\" + pMainFrm->sys.m_Prj_Name;
	pMainFrm->ini.SetIniDir(PrjPath, false);
	if (0 == pMainFrm->ini.SetIniFile(L"PrgParameter.ini"))
	{
		pMainFrm->ini.initData();
		pMainFrm->ini.SaveParaFile(PARA_IMAGE);
		system_control::GetIns()->system_error |= NEEDORIGIN;
	}
	pMainFrm->ini.LoadParaFile(PARA_IMAGE);
	UpdateUI();
	system_control::GetIns()->system_error |= NEEDORIGIN;
	AfxMessageBox(L"������Ŀ���븴λ��");
}


void CMainControl::OnBnClickedButtonChainlen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str;
	GetDlgItem(IDC_EDIT_CHAINLEN)->GetWindowText(str);
	pMainFrm->ini.m_ChainLength = _ttoi(str);
	pMainFrm->ini.SaveParaFile(PARA_IMAGE);
	system_control::GetIns()->system_error |= NEEDORIGIN;
	AfxMessageBox(L"�����������ݺ��븴λ��");
}

void CMainControl::UpdateUI()
{
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str;
	str.Format(_T("%d"), pMainFrm->ini.m_ChainLength);
	GetDlgItem(IDC_EDIT_CHAINLEN)->SetWindowText(str);
}


void CMainControl::OnBnClickedButtonOrigin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (AfxMessageBox(L"ȷ�ϸ�λ��", MB_OKCANCEL | MB_ICONQUESTION) == IDCANCEL)  return;
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CMotionCard * mc = pMainFrm->SCM.CurrentMotionCard();
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(system_control::GetIns()->evt_process, 1))
	{
		return;
	}
	
	if (nullptr == mc)
	{
		AfxMessageBox(L"û�з����˶���");
		return;
	}
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(system_control::GetIns()->evt_EStop, 0))
	{
		AfxMessageBox(L"��ͣ��ť�Ѿ����£�");
		return;
	}

	int effect_factor = TOPCAMERANOTALREADY | BOTTOMCAMERANOTALREADY;
	effect_factor = effect_factor &	system_control::GetIns()->system_error;
	if (effect_factor)
	{
		AfxMessageBox(system_control::GetIns()->ErrorInfo(effect_factor));
		return;
	}

	if (isOrigin) return;
	CString str;
	GetDlgItem(IDC_EDIT_CHAINLEN)->GetWindowText(str);
	pMainFrm->ini.m_ChainLength = _ttoi(str);
	pMainFrm->ini.SaveParaFile(PARA_IMAGE);
	CWinThread * t = AfxBeginThread(origin, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
}

UINT CMainControl::origin(LPVOID lp)
{
	CMainControl * p = (CMainControl*)lp;
	p->isOrigin = true;
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CMotionCard * mc = pMainFrm->SCM.CurrentMotionCard();
	if (nullptr == mc)	return 0;

	pMainFrm->SCM.system_reset();
	Sleep(200);

	if (0 != mc->BackToOrigin(0, 500, pMainFrm->ini.MaxVel, pMainFrm->ini.Tacc))
	{
		system_control::GetIns()->system_error |= NEEDORIGIN;
	}
	else
	{
		system_control::GetIns()->system_error &= ~NEEDORIGIN;
		AfxMessageBox(L"��ԭ��ɹ� ");
	}
	p->isOrigin = false;
	return 0;
}


