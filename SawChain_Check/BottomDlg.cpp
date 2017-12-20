// BottomDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SawChain_Check.h"
#include "BottomDlg.h"
#include "afxdialogex.h"
#include "ImageCard.h"
#include "MainFrm.h"
#include "Tool.h"


// CBottomDlg 对话框

IMPLEMENT_DYNAMIC(CBottomDlg, CDialogEx)

CBottomDlg::CBottomDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_BOTTOMCAM, pParent)
{
	isGrab = false;
}

CBottomDlg::~CBottomDlg()
{
	BottomCameraDlg = NULL;
}

void CBottomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBottomDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BTGRAB, &CBottomDlg::OnBnClickedButtonBtgrab)
	ON_BN_CLICKED(IDC_BUTTON_BTSNAP, &CBottomDlg::OnBnClickedButtonBtsnap)
	ON_BN_CLICKED(IDC_BUTTON_BTSAVE, &CBottomDlg::OnBnClickedButtonBtsave)
	ON_BN_CLICKED(IDC_BUTTON_BDRAWREVRT, &CBottomDlg::OnBnClickedButtonBdrawrevrt)
	ON_BN_CLICKED(IDC_BUTTON_BSHOWREVRT, &CBottomDlg::OnBnClickedButtonBshowrevrt)
	ON_BN_CLICKED(IDC_BUTTON_BSAVE, &CBottomDlg::OnBnClickedButtonBsave)
	ON_BN_CLICKED(IDC_BUTTON_BSHOWRESULT, &CBottomDlg::OnBnClickedButtonBshowresult)
	ON_BN_CLICKED(IDC_BUTTON_BDRAWKNIFERT, &CBottomDlg::OnBnClickedButtonBdrawknifert)
	ON_BN_CLICKED(IDC_BUTTON_BSHOWKNIFERT, &CBottomDlg::OnBnClickedButtonBshowknifert)
	ON_BN_CLICKED(IDC_BUTTON_BSAVEKNIFE, &CBottomDlg::OnBnClickedButtonBsaveknife)
	ON_BN_CLICKED(IDC_BUTTON_BSHOWRESULT3, &CBottomDlg::OnBnClickedButtonBshowresult3)
	ON_BN_CLICKED(IDC_BUTTON_BDRAWCHAR, &CBottomDlg::OnBnClickedButtonBdrawchar)
	ON_BN_CLICKED(IDC_BUTTON_BSHOWCHAR, &CBottomDlg::OnBnClickedButtonBshowchar)
	ON_BN_CLICKED(IDC_BUTTON_BSAVECHARPARA, &CBottomDlg::OnBnClickedButtonBsavecharpara)
	ON_BN_CLICKED(IDC_BUTTON_BSTARTTRAIN, &CBottomDlg::OnBnClickedButtonBstarttrain)
	ON_BN_CLICKED(IDC_BUTTON_BSAVECHAR, &CBottomDlg::OnBnClickedButtonBsavechar)
	ON_BN_CLICKED(IDC_BUTTON_BSAVEMODEL, &CBottomDlg::OnBnClickedButtonBsavemodel)
	ON_BN_CLICKED(IDC_BUTTON_BMATCH, &CBottomDlg::OnBnClickedButtonBmatch)
	ON_BN_CLICKED(IDC_BUTTON_BSHOWIMG, &CBottomDlg::OnBnClickedButtonBshowimg)
	ON_BN_CLICKED(IDC_BUTTON_BDRAWUB, &CBottomDlg::OnBnClickedButtonBdrawub)
	ON_BN_CLICKED(IDC_BUTTON_BSHOWUB, &CBottomDlg::OnBnClickedButtonBshowub)
	ON_BN_CLICKED(IDC_BUTTON_BTESTUB, &CBottomDlg::OnBnClickedButtonBtestub)
END_MESSAGE_MAP()


// CBottomDlg 消息处理程序
void CBottomDlg::ButtonEnable()
{
	GetDlgItem(IDC_BUTTON_BDRAWREVRT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BSHOWREVRT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BSHOWRESULT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BSAVE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BDRAWCHAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BSHOWCHAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BSAVECHAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BSTARTTRAIN)->EnableWindow(TRUE);
//	GetDlgItem(IDC_BUTTON_BSHOW)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BSAVE)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_BDRAWKNIFERT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BSHOWKNIFERT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BSAVEKNIFE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BSHOWRESULT3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BMATCH)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BSAVEMODEL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_BSAVECHARPARA)->EnableWindow(TRUE);
}

void CBottomDlg::ButtonUnable()
{
	GetDlgItem(IDC_BUTTON_BDRAWREVRT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BSHOWREVRT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BSHOWRESULT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BSAVE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BDRAWCHAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BSHOWCHAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BSAVECHAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BSTARTTRAIN)->EnableWindow(FALSE);
//	GetDlgItem(IDC_BUTTON_BSHOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BSAVE)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_BDRAWKNIFERT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BSHOWKNIFERT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BSAVEKNIFE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BSHOWRESULT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BMATCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BSAVEMODEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_BSAVECHARPARA)->EnableWindow(FALSE);
}

BOOL CBottomDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	BottomCameraDlg = this->m_hWnd;
	OnBnClickedButtonBstarttrain();
	CString str;
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
#ifndef para 
#define para pMainFrm->ini
#endif
	str.Format(L"%d", static_cast<int>(para.BottomPara.minarea));
	GetDlgItem(IDC_EDIT_BINVLIMITINF)->SetWindowText(str);
	str.Format(L"%d", static_cast<int>(para.BottomPara.maxarea));
	GetDlgItem(IDC_EDIT_BINVLIMITSUP)->SetWindowText(str);
	str.Format(L"%d", static_cast<int>(para.BottomPara.thresholdvalue));
	GetDlgItem(IDC_EDIT_BINVTHRESHOLD)->SetWindowText(str);

	str.Format(L"%d", static_cast<int>(pMainFrm->ini.BottomPara.knife_threshold));
	GetDlgItem(IDC_EDIT_BKNIFETHRESHOLD)->SetWindowText(str);

	str.Format(L"%d", static_cast<int>(pMainFrm->ini.BottomPara.maxlen));
	GetDlgItem(IDC_EDIT_BMAXLEN)->SetWindowText(str);

	str.Format(L"%d", static_cast<int>(pMainFrm->ini.BottomPara.minlen));
	GetDlgItem(IDC_EDIT_BMINLEN)->SetWindowText(str);

	str.Format(L"%f", pMainFrm->ini.BottomPara.match_acc);
	SetDlgItemText(IDC_EDIT_BPRESION, str);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CBottomDlg::OnBnClickedButtonBtgrab()
{
	// TODO: 在此添加控件通知处理程序代码
	if (BOTTOMCAMERANOTALREADY == (BOTTOMCAMERANOTALREADY & system_control::GetIns()->system_error))			return;
	if (isGrab
		|| WAIT_OBJECT_0 == ::WaitForSingleObject(system_control::GetIns()->evt_process, 1))	return;
	system_control::GetIns()->is_bottom_grab = true;
	CWinThread * t = AfxBeginThread(grab, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	if (t)
	{
		ButtonUnable();
	}
	else
	{
		system_control::GetIns()->is_bottom_grab = false;
	}
}


void CBottomDlg::OnBnClickedButtonBtsnap()
{
	// TODO: 在此添加控件通知处理程序代码
	
//	OnBnClickedButtonBtgrab();
//	system_control::GetIns()->is_bottom_grab = false;
//	return;
	if (BOTTOMCAMERANOTALREADY == (BOTTOMCAMERANOTALREADY & system_control::GetIns()->system_error))			return;
	if (system_control::GetIns()->is_bottom_grab) { ButtonEnable();  system_control::GetIns()->is_bottom_grab = false; return; }
	try {
		Halcon::set_check("~give_error");
		CImageCard::GetIns()->Image1 = CImageCard::GetIns()->GetBottomImage();
		CImageCard::GetIns()->Bottom_Disp_Obj(CImageCard::GetIns()->Image1);
	}
	catch (...)
	{
		Halcon::set_check("~give_error");
		return;
	}
	Halcon::set_check("~give_error");
}




void CBottomDlg::OnBnClickedButtonBtsave()
{
	// TODO: 在此添加控件通知处理程序代码
}

UINT CBottomDlg::grab(LPVOID lp)
{
	CBottomDlg* pDlg = (CBottomDlg*)lp;
	pDlg->isGrab = true;
	for (; system_control::GetIns()->is_bottom_grab;)
	{
		try {
			Halcon::set_check("~give_error");
			Halcon::Hobject obj = CImageCard::GetIns()->GetBottomImage();
			Hlong w, h;
			Halcon::get_image_pointer1(obj, NULL, NULL, &w, &h);
			Halcon::set_part(CImageCard::GetIns()->disp_hd1, NULL, NULL, h, w);
			Halcon::disp_obj(obj, CImageCard::GetIns()->disp_hd1);
		}
		catch (...)
		{
			system_control::GetIns()->is_bottom_grab = false;
			break;
		}
	}
	pDlg->isGrab = false;
	return 0;

}


void CBottomDlg::OnBnClickedButtonBdrawrevrt()
{
	// TODO: 在此添加控件通知处理程序代码
	system_control::GetIns()->is_bottom_grab = false;//强制结束顶部相机拍照
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::set_check("~give_error");
	try
	{
		system_control::GetIns()->rect_error = BINVRECT;
		double r1, c1, r2, c2;
		Halcon::Hobject hobj;
		Halcon::set_color(CImageCard::GetIns()->disp_hd1, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd1, "margin");
		Halcon::draw_rectangle1(CImageCard::GetIns()->disp_hd1, &r1, &c1, &r2, &c2);
		Halcon::gen_rectangle1(&hobj, r1, c1, r2, c2);
		Halcon::disp_obj(hobj, CImageCard::GetIns()->disp_hd1);
		pMainFrm->ini.bottom_inv.r1 = r1;
		pMainFrm->ini.bottom_inv.c1 = c1;
		pMainFrm->ini.bottom_inv.r2 = r2;
		pMainFrm->ini.bottom_inv.c2 = c2;
		pMainFrm->ini.SaveParaFile(PARA_IMAGE);
		system_control::GetIns()->rect_error = NORECT;
	}
	catch (Halcon::HException &except)
	{
		system_control::GetIns()->rect_error = NORECT;
		Halcon::set_check("give_error");
		TRACE(except.message);
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd1,0,1);
		Halcon::write_string(CImageCard::GetIns()->disp_hd1, except.message);
		AfxMessageBox(L"设定搜索范围失败！");
	}
}


void CBottomDlg::OnBnClickedButtonBshowrevrt()
{
	// TODO: 在此添加控件通知处理程序代码
	system_control::GetIns()->is_bottom_grab = false;//强制结束顶部相机拍照
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::Hobject invroi;
	Halcon::clear_window(CImageCard::GetIns()->disp_hd1);
	try
	{
		Halcon::set_check("~give_error");
		Halcon::set_color(CImageCard::GetIns()->disp_hd1, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd1, "margin");
		Halcon::gen_rectangle1(&invroi, pMainFrm->ini.bottom_inv.r1, pMainFrm->ini.bottom_inv.c1, pMainFrm->ini.bottom_inv.r2, pMainFrm->ini.bottom_inv.c2);
		Halcon::disp_obj(CImageCard::GetIns()->Image1, CImageCard::GetIns()->disp_hd1);
		Halcon::disp_obj(invroi, CImageCard::GetIns()->disp_hd1);
	}
	catch (...)
	{
		Halcon::set_check("~give_error");
		return;
	}
}


void CBottomDlg::OnBnClickedButtonBsave()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str;
	GetDlgItem(IDC_EDIT_BINVTHRESHOLD)->GetWindowText(str);
	pMainFrm->ini.BottomPara.thresholdvalue = _ttoi(str);

	GetDlgItem(IDC_EDIT_BINVLIMITSUP)->GetWindowText(str);
	pMainFrm->ini.BottomPara.maxarea = _ttoi(str);

	GetDlgItem(IDC_EDIT_BINVLIMITINF)->GetWindowText(str);
	pMainFrm->ini.BottomPara.minarea = _ttoi(str);

	if (pMainFrm->ini.BottomPara.maxarea < pMainFrm->ini.BottomPara.minarea)
	{
		double t = pMainFrm->ini.BottomPara.minarea; pMainFrm->ini.BottomPara.maxarea = pMainFrm->ini.BottomPara.minarea; pMainFrm->ini.BottomPara.maxarea = t;
		str.Format(L"%d", static_cast<int>(pMainFrm->ini.BottomPara.minarea));
		GetDlgItem(IDC_EDIT_BINVLIMITINF)->GetWindowText(str);
		str.Format(L"%d", static_cast<int>(pMainFrm->ini.BottomPara.maxarea));
		GetDlgItem(IDC_EDIT_BINVLIMITSUP)->GetWindowText(str);
	}
	pMainFrm->ini.SaveParaFile(PARA_IMAGE);
}


void CBottomDlg::OnBnClickedButtonBshowresult()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (isGrab)	return;
	CString str;
	GetDlgItem(IDC_EDIT_BINVTHRESHOLD)->GetWindowText(str);
	pMainFrm->ini.BottomPara.thresholdvalue = _ttoi(str);

	GetDlgItem(IDC_EDIT_BINVLIMITSUP)->GetWindowText(str);
	pMainFrm->ini.BottomPara.maxarea = _ttoi(str);

	GetDlgItem(IDC_EDIT_BINVLIMITINF)->GetWindowText(str);
	pMainFrm->ini.BottomPara.minarea = _ttoi(str);

	if (pMainFrm->ini.BottomPara.maxarea < pMainFrm->ini.BottomPara.minarea)
	{
		double t = pMainFrm->ini.BottomPara.minarea; pMainFrm->ini.BottomPara.maxarea = pMainFrm->ini.BottomPara.minarea; pMainFrm->ini.BottomPara.maxarea = t;
		str.Format(L"%d", static_cast<int>(pMainFrm->ini.BottomPara.minarea));
		GetDlgItem(IDC_EDIT_BINVLIMITINF)->GetWindowText(str);
		str.Format(L"%d", static_cast<int>(pMainFrm->ini.BottomPara.maxarea));
		GetDlgItem(IDC_EDIT_BINVLIMITSUP)->GetWindowText(str);
	}
	double area;
	try
	{
		Halcon::set_check("~give_error");
		Halcon::Hobject invroi;
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd1, 0, 1);
		CImageCard::GetIns()->Bottom_Disp_Obj(CImageCard::GetIns()->Image1);
		Halcon::gen_rectangle1(&invroi, pMainFrm->ini.bottom_inv.r1, pMainFrm->ini.bottom_inv.c1, pMainFrm->ini.bottom_inv.r2, pMainFrm->ini.bottom_inv.c2);
		pMainFrm->SCM.check_inverse(CImageCard::GetIns()->Image1, invroi, pMainFrm->ini.BottomPara.thresholdvalue, pMainFrm->ini.BottomPara.minarea, pMainFrm->ini.BottomPara.maxarea, CImageCard::GetIns()->disp_hd1, &area);
	}
	catch (...)
	{
		Halcon::set_check("~give_error");
	}
	}


void CBottomDlg::OnBnClickedButtonBdrawknifert()
{
	// TODO: 在此添加控件通知处理程序代码
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::set_check("~give_error");
	try
	{
		system_control::GetIns()->rect_error = BKNIFERECT;
		double r1, c1, r2, c2;
		Halcon::Hobject hobj;
		Halcon::set_color(CImageCard::GetIns()->disp_hd1, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd1, "margin");
		Halcon::draw_rectangle1(CImageCard::GetIns()->disp_hd1, &r1, &c1, &r2, &c2);
		Halcon::gen_rectangle1(&hobj, r1, c1, r2, c2);
		Halcon::disp_obj(hobj, CImageCard::GetIns()->disp_hd1);
		pMainFrm->ini.bottom_knife.r1 = r1;
		pMainFrm->ini.bottom_knife.c1 = c1;
		pMainFrm->ini.bottom_knife.r2 = r2;
		pMainFrm->ini.bottom_knife.c2 = c2;
		pMainFrm->ini.SaveParaFile(PARA_IMAGE);
		system_control::GetIns()->rect_error = NORECT;
	}
	catch (Halcon::HException &except)
	{
		system_control::GetIns()->rect_error = NORECT;
		Halcon::set_check("give_error");
		TRACE(except.message);
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd1, 0, 1);
		Halcon::write_string(CImageCard::GetIns()->disp_hd1, except.message);
		AfxMessageBox(L"设定搜索范围失败！");
	}
}


void CBottomDlg::OnBnClickedButtonBshowknifert()
{
	// TODO: 在此添加控件通知处理程序代码
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::Hobject roi;
	Halcon::clear_window(CImageCard::GetIns()->disp_hd1);
	try
	{
		Halcon::set_check("~give_error");
		Halcon::set_color(CImageCard::GetIns()->disp_hd1, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd1, "margin");
		Halcon::gen_rectangle1(&roi, pMainFrm->ini.bottom_knife.r1, pMainFrm->ini.bottom_knife.c1, pMainFrm->ini.bottom_knife.r2, pMainFrm->ini.bottom_knife.c2);
		Halcon::disp_obj(CImageCard::GetIns()->Image1, CImageCard::GetIns()->disp_hd1);
		Halcon::disp_obj(roi, CImageCard::GetIns()->disp_hd1);
	}
	catch (...)
	{
		return;
	}
}


void CBottomDlg::OnBnClickedButtonBsaveknife()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str;
	GetDlgItem(IDC_EDIT_BKNIFETHRESHOLD)->GetWindowText(str);
	pMainFrm->ini.BottomPara.knife_threshold = _ttoi(str);

	GetDlgItem(IDC_EDIT_BMAXLEN)->GetWindowText(str);
	pMainFrm->ini.BottomPara.maxlen = _ttoi(str);

	GetDlgItem(IDC_EDIT_BMINLEN)->GetWindowText(str);
	pMainFrm->ini.BottomPara.minlen = _ttoi(str);

	if (pMainFrm->ini.BottomPara.maxlen < pMainFrm->ini.BottomPara.minlen)
	{
		double t = pMainFrm->ini.BottomPara.minlen; pMainFrm->ini.BottomPara.maxlen = pMainFrm->ini.BottomPara.minlen; pMainFrm->ini.BottomPara.maxlen = t;
		str.Format(L"%d", static_cast<int>(pMainFrm->ini.BottomPara.minlen));
		GetDlgItem(IDC_EDIT_BMINLEN)->GetWindowText(str);
		str.Format(L"%d", static_cast<int>(pMainFrm->ini.BottomPara.maxlen));
		GetDlgItem(IDC_EDIT_BMAXLEN)->GetWindowText(str);
	}
	pMainFrm->ini.SaveParaFile(PARA_IMAGE);
}


void CBottomDlg::OnBnClickedButtonBshowresult3()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::set_check("~give_error");
	try {
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd1, 0, 1);
		CImageCard::GetIns()->Bottom_Disp_Obj(CImageCard::GetIns()->Image1);
		pMainFrm->SCM.check_knife(CImageCard::GetIns()->Image1, CImageCard::GetIns()->disp_hd1, pMainFrm->ini.bottom_knife.r1, pMainFrm->ini.bottom_knife.c1, pMainFrm->ini.bottom_knife.r2, pMainFrm->ini.bottom_knife.c2,
			pMainFrm->ini.BottomPara.minlen, pMainFrm->ini.BottomPara.maxlen);
	}
	catch (...)
	{
		Halcon::set_check("~give_error");
	}
}


void CBottomDlg::OnBnClickedButtonBdrawchar()
{
	// TODO: 在此添加控件通知处理程序代码
	system_control::GetIns()->is_top_grab = false;//强制结束顶部相机拍照
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::set_check("~give_error");
	Halcon::HTuple  Exception;
	try
	{
		system_control::GetIns()->rect_error = BCHARRECT;
		double r1, c1, r2, c2;
		Halcon::Hobject hobj;
		Halcon::set_color(CImageCard::GetIns()->disp_hd1, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd1, "margin");
		Halcon::draw_rectangle1(CImageCard::GetIns()->disp_hd1, &r1, &c1, &r2, &c2);
		Halcon::gen_rectangle1(&hobj, r1, c1, r2, c2);
		Halcon::disp_obj(hobj, CImageCard::GetIns()->disp_hd1);
		pMainFrm->ini.bottom_char.r1 = r1;
		pMainFrm->ini.bottom_char.c1 = c1;
		pMainFrm->ini.bottom_char.r2 = r2;
		pMainFrm->ini.bottom_char.c2 = c2;
		pMainFrm->ini.SaveParaFile(PARA_IMAGE);
		system_control::GetIns()->rect_error = NORECT;
	}
	catch (Halcon::HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&Exception);
		system_control::GetIns()->rect_error = NORECT;
		Halcon::set_check("give_error");
		TRACE(HDevExpDefaultException.message);
		AfxMessageBox(L"设定搜索范围失败！");
	}
}


void CBottomDlg::OnBnClickedButtonBshowchar()
{
	// TODO: 在此添加控件通知处理程序代码
	system_control::GetIns()->is_top_grab = false;//强制结束顶部相机拍照
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::Hobject invroi;
	Halcon::clear_window(CImageCard::GetIns()->disp_hd1);
	try
	{
		Halcon::set_check("~give_error");
		Halcon::set_color(CImageCard::GetIns()->disp_hd1, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd1, "margin");
		Halcon::gen_rectangle1(&invroi, pMainFrm->ini.bottom_char.r1, pMainFrm->ini.bottom_char.c1, pMainFrm->ini.bottom_char.r2, pMainFrm->ini.bottom_char.c2);
		Halcon::disp_obj(CImageCard::GetIns()->Image1, CImageCard::GetIns()->disp_hd1);
		Halcon::disp_obj(invroi, CImageCard::GetIns()->disp_hd1);
	}
	catch (...)
	{
		return;
	}
}


void CBottomDlg::OnBnClickedButtonBsavecharpara()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str;
	GetDlgItemText(IDC_EDIT_BPRESION, str);
	pMainFrm->ini.BottomPara.match_acc = _ttof(str);
	pMainFrm->ini.SaveParaFile(PARA_IMAGE);
}


void CBottomDlg::OnBnClickedButtonBstarttrain()
{
	// TODO: 在此添加控件通知处理程序代码
	win_tool wt;
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	std::vector<CString> NameVector = wt.SplitCString(pMainFrm->sys.m_Prj_Vector, L",");
	if (pMainFrm->sys.m_Prj_Index >= static_cast<int>(NameVector.size())) { AfxMessageBox(L"是不是删除了项目？请重新选择项目"); return; }
	CString prj_name = NameVector[pMainFrm->sys.m_Prj_Index];
	CString path = wt.AppPath() + L"\\" + prj_name + L"\\BottomModel";

	std::vector<CString> images;
	win_tool::CSelectFolderDlg DirPath;
	DirPath.ProcPicDir(path, images);

	try
	{
		GiveError;
		Halcon::Hobject obj;//训练时候不需要，只是做一个样子而已
		pMainFrm->SCM.check_bottom_char(obj, CImageCard::GetIns()->disp_hd1, pMainFrm->ini.bottom_char.r1, pMainFrm->ini.bottom_char.c1, pMainFrm->ini.bottom_char.r2, pMainFrm->ini.bottom_char.c2,
			images, 0.5, 1
		);

	}
	catch (...)
	{
		nGiveError;
	}
}


void CBottomDlg::OnBnClickedButtonBsavechar()
{
	// TODO: 在此添加控件通知处理程序代码
	win_tool wt;
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	std::vector<CString> NameVector = wt.SplitCString(pMainFrm->sys.m_Prj_Vector, L",");
	if (pMainFrm->sys.m_Prj_Index >= static_cast<int>(NameVector.size())) { AfxMessageBox(L"是不是删除了项目？请重新选择项目"); return; }
	CString prj_name = NameVector[pMainFrm->sys.m_Prj_Index];
	CString path = wt.AppPath() + L"\\" + prj_name + L"\\BottomModel";
	CreateDirectory(path, NULL);
	ShellExecute(NULL, L"open", _T("explorer.exe"), path, NULL, SW_SHOW);
}


void CBottomDlg::OnBnClickedButtonBsavemodel()
{
	// TODO: 在此添加控件通知处理程序代码
	win_tool wt;
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	std::vector<CString> NameVector = wt.SplitCString(pMainFrm->sys.m_Prj_Vector, L",");
	if (pMainFrm->sys.m_Prj_Index >= static_cast<int>(NameVector.size())) { AfxMessageBox(L"是不是删除了项目？请重新选择项目"); return; }
	CString prj_name = NameVector[pMainFrm->sys.m_Prj_Index];
	CString path = wt.AppPath() + L"\\" + prj_name + L"\\BottomModel";
	CreateDirectory(path, NULL);
	CString FileName = wt.AppPath() + L"\\" + prj_name + L"\\BottomModel\\" + wt.Get_Date_Time() + L".jpg";
	Halcon::Hobject Model_Image;
	try
	{
		GiveError;
		Halcon::write_image(CImageCard::GetIns()->Image1, "jpg", 0, (char*)(LPCSTR)(CStringA)FileName);
	}
	catch (...)
	{
		nGiveError;
		AfxMessageBox(L"请点击静态抓图进行抓取图片");
	}
}


void CBottomDlg::OnBnClickedButtonBmatch()
{
	// TODO: 在此添加控件通知处理程序代码
	win_tool wt;
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	try
	{
		GiveError;
		std::vector<CString> images; //测试时候不需要，
		CImageCard::GetIns()->Bottom_Disp_Obj(CImageCard::GetIns()->Image1);
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd1, 0, 1);
		pMainFrm->SCM.check_bottom_char(CImageCard::GetIns()->Image1, CImageCard::GetIns()->disp_hd1, pMainFrm->ini.bottom_char.r1, pMainFrm->ini.bottom_char.c1, pMainFrm->ini.bottom_char.r2, pMainFrm->ini.bottom_char.c2,
			images, pMainFrm->ini.BottomPara.match_acc, 0
		);

	}
	catch (...)
	{
		nGiveError;
	}
}

/*
void CBottomDlg::OnBnClickedButtonBshow()
{
	// TODO: 在此添加控件通知处理程序代码
	system_control::GetIns()->is_bottom_grab = false;
	CImageCard * im = CImageCard::GetIns();
	CFileDialog fileDlg(TRUE, (LPCTSTR)"BMP", L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"All Files (*.*)|*.*|位图文件 (*.bmp)|*.bmp||");	//打开读取文件对话框
	if (fileDlg.DoModal() != IDOK) return;
	Halcon::Hobject Image;
	try {
		Halcon::read_image(&CImageCard::GetIns()->Image1, (char*)(LPCSTR)CStringA(fileDlg.GetPathName()));
		im->Bottom_Disp_Obj(CImageCard::GetIns()->Image1);
	}
	catch (...)
	{
		Halcon::set_check("give_error");
		return;
	}
}
*/

void CBottomDlg::OnBnClickedButtonBshowimg()
{
	// TODO: 在此添加控件通知处理程序代码
	system_control::GetIns()->is_top_grab = false;
	CImageCard * im = CImageCard::GetIns();
	CFileDialog fileDlg(TRUE, (LPCTSTR)"BMP", L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"All Files (*.*)|*.*|位图文件 (*.bmp)|*.bmp||");	//打开读取文件对话框
	if (fileDlg.DoModal() != IDOK) return;
	Halcon::Hobject Image;
	try {
		Halcon::set_check("~give_error");
		Halcon::read_image(&CImageCard::GetIns()->Image1, (char*)(LPCSTR)CStringA(fileDlg.GetPathName()));
		im->Bottom_Disp_Obj(CImageCard::GetIns()->Image1);
	}
	catch (...)
	{
		Halcon::set_check("~give_error");
		return;
	}
}


void CBottomDlg::OnBnClickedButtonBdrawub()
{
	// TODO: 在此添加控件通知处理程序代码
	system_control::GetIns()->is_top_grab = false;//强制结束顶部相机拍照
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::set_check("~give_error");
	Halcon::HTuple  Exception;
	try
	{
		system_control::GetIns()->rect_error = BUNBOLT;
		double r1, c1, r2, c2;
		Halcon::Hobject hobj;
		Halcon::set_color(CImageCard::GetIns()->disp_hd1, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd1, "margin");
		Halcon::draw_rectangle1(CImageCard::GetIns()->disp_hd1, &r1, &c1, &r2, &c2);
		Halcon::gen_rectangle1(&hobj, r1, c1, r2, c2);
		Halcon::disp_obj(hobj, CImageCard::GetIns()->disp_hd1);
		pMainFrm->ini.bottom_unbolt.r1 = r1;
		pMainFrm->ini.bottom_unbolt.c1 = c1;
		pMainFrm->ini.bottom_unbolt.r2 = r2;
		pMainFrm->ini.bottom_unbolt.c2 = c2;
		pMainFrm->ini.SaveParaFile(PARA_IMAGE);
		system_control::GetIns()->rect_error = NORECT;
	}
	catch (Halcon::HException &HDevExpDefaultException)
	{
		HDevExpDefaultException.ToHTuple(&Exception);
		system_control::GetIns()->rect_error = NORECT;
		Halcon::set_check("~give_error");
		TRACE(HDevExpDefaultException.message);
		AfxMessageBox(L"设定搜索范围失败！");
	}
}


void CBottomDlg::OnBnClickedButtonBshowub()
{
	// TODO: 在此添加控件通知处理程序代码
	system_control::GetIns()->is_bottom_grab = false;//强制结束顶部相机拍照
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::Hobject invroi;
	Halcon::clear_window(CImageCard::GetIns()->disp_hd1);
	try
	{
		Halcon::set_check("~give_error");
		Halcon::set_color(CImageCard::GetIns()->disp_hd1, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd1, "margin");
		Halcon::gen_rectangle1(&invroi, pMainFrm->ini.bottom_unbolt.r1, pMainFrm->ini.bottom_unbolt.c1, pMainFrm->ini.bottom_unbolt.r2, pMainFrm->ini.bottom_unbolt.c2);
		Halcon::disp_obj(CImageCard::GetIns()->Image1, CImageCard::GetIns()->disp_hd1);
		Halcon::disp_obj(invroi, CImageCard::GetIns()->disp_hd1);
	}
	catch (...)
	{
		return;
	}
}


void CBottomDlg::OnBnClickedButtonBtestub()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::set_check("~give_error");
	try {
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd1, 0, 1);
		CImageCard::GetIns()->Bottom_Disp_Obj(CImageCard::GetIns()->Image1);
		pMainFrm->SCM.check_daji(CImageCard::GetIns()->Image1, CImageCard::GetIns()->disp_hd1, pMainFrm->ini.bottom_unbolt.r1, pMainFrm->ini.bottom_unbolt.c1, pMainFrm->ini.bottom_unbolt.r2, pMainFrm->ini.bottom_unbolt.c2);
	}
	catch (...)
	{
		Halcon::set_check("~give_error");
	}
}
