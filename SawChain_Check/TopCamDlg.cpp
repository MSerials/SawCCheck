// TopCamDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SawChain_Check.h"
#include "TopCamDlg.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ImageCard.h"
#include "Tool.h"


// CTopCamDlg 对话框

IMPLEMENT_DYNAMIC(CTopCamDlg, CDialogEx)

CTopCamDlg::CTopCamDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_TOPCAM, pParent)
{
	isGrab = false;
}

CTopCamDlg::~CTopCamDlg()
{
	TopCameraDlg = NULL;
	
}

void CTopCamDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTopCamDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_TGRAB, &CTopCamDlg::OnBnClickedButtonTgrab)
	ON_BN_CLICKED(IDC_BUTTON_TSNAP, &CTopCamDlg::OnBnClickedButtonTsnap)
	ON_BN_CLICKED(IDC_BUTTON_TSHOW, &CTopCamDlg::OnBnClickedButtonTshow)
	ON_BN_CLICKED(IDC_BUTTON_TSAVE, &CTopCamDlg::OnBnClickedButtonTsave)
	ON_BN_CLICKED(IDC_BUTTON_TDRAWREVRT, &CTopCamDlg::OnBnClickedButtonTdrawrevrt)
	ON_BN_CLICKED(IDC_BUTTON_TSHOWREVRT, &CTopCamDlg::OnBnClickedButtonTshowrevrt)
	ON_BN_CLICKED(IDC_BUTTON_TSHOWRESULT, &CTopCamDlg::OnBnClickedButtonTshowresult)
	ON_BN_CLICKED(IDC_BUTTON_TSAVE1, &CTopCamDlg::OnBnClickedButtonTsave1)
	ON_BN_CLICKED(IDC_BUTTON_TDRAWCHAR, &CTopCamDlg::OnBnClickedButtonTdrawchar)
	ON_BN_CLICKED(IDC_BUTTON_TSHOWCHAR, &CTopCamDlg::OnBnClickedButtonTshowchar)
	ON_BN_CLICKED(IDC_BUTTON_TSAVECHAR, &CTopCamDlg::OnBnClickedButtonTsavechar)
	ON_BN_CLICKED(IDC_BUTTON_TSTARTTRAIN, &CTopCamDlg::OnBnClickedButtonTstarttrain)
	ON_BN_CLICKED(IDC_BUTTON_TSAVEKNIFE, &CTopCamDlg::OnBnClickedButtonTsaveknife)
	ON_BN_CLICKED(IDC_BUTTON_TSHOWAREA, &CTopCamDlg::OnBnClickedButtonTshowarea)
	ON_BN_CLICKED(IDC_BUTTON_TSHOWRESULT3, &CTopCamDlg::OnBnClickedButtonTshowresult3)
	ON_BN_CLICKED(IDC_BUTTON_TSHOWKNIFERT, &CTopCamDlg::OnBnClickedButtonTshowknifert)
	ON_BN_CLICKED(IDC_BUTTON_TSAVEMODEL, &CTopCamDlg::OnBnClickedButtonTsavemodel)
	ON_BN_CLICKED(IDC_BUTTON_TMATCH, &CTopCamDlg::OnBnClickedButtonTmatch)
	ON_BN_CLICKED(IDC_BUTTON_TSAVECHARPARA, &CTopCamDlg::OnBnClickedButtonTsavecharpara)
	ON_BN_CLICKED(IDC_BUTTON_TDRAWUB, &CTopCamDlg::OnBnClickedButtonTdrawub)
	ON_BN_CLICKED(IDC_BUTTON_TSHOWUB, &CTopCamDlg::OnBnClickedButtonTshowub)
	ON_BN_CLICKED(IDC_BUTTON_TTESTUB, &CTopCamDlg::OnBnClickedButtonTtestub)
END_MESSAGE_MAP()


// CTopCamDlg 消息处理程序


BOOL CTopCamDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	TopCameraDlg = this->m_hWnd;
	OnBnClickedButtonTstarttrain();
	CString str;
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
#ifndef para 
#define para pMainFrm->ini
#endif
	str.Format(L"%d", static_cast<int>(para.TopPara.minarea));
	GetDlgItem(IDC_EDIT_TINVLIMITINF)->SetWindowText(str);
	str.Format(L"%d", static_cast<int>(para.TopPara.maxarea));
	GetDlgItem(IDC_EDIT_TINVLIMITSUP)->SetWindowText(str);
	str.Format(L"%d", static_cast<int>(para.TopPara.thresholdvalue));
	GetDlgItem(IDC_EDIT_TINVTHRESHOLD)->SetWindowText(str);

	str.Format(L"%d", static_cast<int>(pMainFrm->ini.TopPara.knife_threshold));
	GetDlgItem(IDC_EDIT_TKNIFETHRESHOLD)->SetWindowText(str);

	str.Format(L"%d", static_cast<int>(pMainFrm->ini.TopPara.maxlen));
	GetDlgItem(IDC_EDIT_TMAXLEN)->SetWindowText(str);

	str.Format(L"%d", static_cast<int>(pMainFrm->ini.TopPara.minlen));
	GetDlgItem(IDC_EDIT_TMINLEN)->SetWindowText(str);

	str.Format(L"%f", pMainFrm->ini.TopPara.match_acc);
	SetDlgItemText(IDC_EDIT_TPRESION, str);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CTopCamDlg::ButtonEnable()
{
	GetDlgItem(IDC_BUTTON_TDRAWREVRT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TSHOWREVRT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TSHOWRESULT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TSAVE1)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TDRAWCHAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TSHOWCHAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TSAVECHAR)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TSTARTTRAIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TSHOW)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TSAVE)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON_TSHOWAREA)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TSHOWKNIFERT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TSAVEKNIFE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TSHOWRESULT3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TMATCH)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TSAVEMODEL)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_TSAVECHARPARA)->EnableWindow(TRUE);
	
}

void CTopCamDlg::ButtonUnable()
{
	GetDlgItem(IDC_BUTTON_TDRAWREVRT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TSHOWREVRT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TSHOWRESULT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TSAVE1)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TDRAWCHAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TSHOWCHAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TSAVECHAR)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TSTARTTRAIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TSHOW)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TSAVE)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON_TSHOWAREA)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TSHOWKNIFERT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TSAVEKNIFE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TSHOWRESULT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TMATCH)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TSAVEMODEL)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_TSAVECHARPARA)->EnableWindow(FALSE);
	
}

void CTopCamDlg::OnBnClickedButtonTgrab()
{
	// TODO: 在此添加控件通知处理程序代码 

	if (TOPCAMERANOTALREADY == (TOPCAMERANOTALREADY & system_control::GetIns()->system_error)
		||isGrab 
		|| WAIT_OBJECT_0 == ::WaitForSingleObject(system_control::GetIns()->evt_process, 1)
		)	
		return;
	system_control::GetIns()->is_top_grab = true;
	CWinThread * t = AfxBeginThread(grab, this, THREAD_PRIORITY_NORMAL, 0, 0, NULL);
	if (t)
	{
		ButtonUnable();
	}
	else
	{
		system_control::GetIns()->is_top_grab = false;
	}
}


void CTopCamDlg::OnBnClickedButtonTsnap()
{
	// TODO: 在此添加控件通知处理程序代码
//	OnBnClickedButtonTgrab();
//		system_control::GetIns()->is_top_grab = false;
//	return;
	if (TOPCAMERANOTALREADY == (TOPCAMERANOTALREADY & system_control::GetIns()->system_error))						return;
	if (system_control::GetIns()->is_top_grab) { ButtonEnable(); system_control::GetIns()->is_top_grab = false;   return; }
	try {
		Halcon::set_check("~give_error");
		CImageCard::GetIns()->Image = CImageCard::GetIns()->GetTopImage();
		CImageCard::GetIns()->Top_Disp_Obj(CImageCard::GetIns()->Image);
	}
	catch (...)
	{
		Halcon::set_check("give_error");
		return;
	}
	Halcon::set_check("give_error");
}


void CTopCamDlg::OnBnClickedButtonTshow()
{
	system_control::GetIns()->is_top_grab = false;
	CImageCard * im = CImageCard::GetIns();
	CFileDialog fileDlg(TRUE, (LPCTSTR)"BMP", L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"All Files (*.*)|*.*|位图文件 (*.bmp)|*.bmp||");	//打开读取文件对话框
	if (fileDlg.DoModal() != IDOK) return;
	Halcon::Hobject Image;
	try {
		Halcon::set_check("~give_error");
		Halcon::read_image(&CImageCard::GetIns()->Image, (char*)(LPCSTR)CStringA(fileDlg.GetPathName()));
		im->Top_Disp_Obj(CImageCard::GetIns()->Image);
	}
	catch (...)
	{
		Halcon::set_check("give_error");
		return;
	}
	// TODO: 在此添加控件通知处理程序代码
}


void CTopCamDlg::OnBnClickedButtonTsave()
{
	// TODO: 在此添加控件通知处理程序代码
}

UINT CTopCamDlg::grab(LPVOID lp)
{
	CTopCamDlg* pDlg = (CTopCamDlg*)lp;
	pDlg->isGrab = true;
	CImageCard *ImgCard = CImageCard::GetIns();
	for(; system_control::GetIns()->is_top_grab;)
	{	
			try {
				Halcon::set_check("~give_error");
				Halcon::set_check("~give_error");
				Halcon::Hobject obj = CImageCard::GetIns()->GetTopImage();
				Hlong w, h;
				Halcon::get_image_pointer1(obj, NULL, NULL, &w, &h);
				Halcon::set_part(CImageCard::GetIns()->disp_hd, NULL, NULL, h, w);
				Halcon::disp_obj(obj, CImageCard::GetIns()->disp_hd);
			}
			catch (...)
			{
				system_control::GetIns()->is_top_grab = false;
				break;
			}
	}
	pDlg->isGrab = false;
	return 0;
}


void CTopCamDlg::OnBnClickedButtonTdrawrevrt()
{
	// TODO: 在此添加控件通知处理程序代码
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::set_check("~give_error");
	try
	{
		system_control::GetIns()->rect_error = TINVRECT;
		double r1, c1, r2, c2;
		Halcon::Hobject hobj;
		Halcon::set_color(CImageCard::GetIns()->disp_hd, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd, "margin");
		Halcon::draw_rectangle1(CImageCard::GetIns()->disp_hd, &r1, &c1, &r2, &c2);
		Halcon::gen_rectangle1(&hobj, r1, c1, r2, c2);
		Halcon::HDevWindowStack::Push(CImageCard::GetIns()->disp_hd);
		Halcon::HDevWindowStack::SetActive(CImageCard::GetIns()->disp_hd);
		Halcon::disp_obj(hobj, CImageCard::GetIns()->disp_hd);
		pMainFrm->ini.top_inv.r1 = r1;
		pMainFrm->ini.top_inv.c1 = c1;
		pMainFrm->ini.top_inv.r2 = r2;
		pMainFrm->ini.top_inv.c2 = c2;
		pMainFrm->ini.SaveParaFile(PARA_IMAGE);
		system_control::GetIns()->rect_error = NORECT;
	}
	catch (Halcon::HException &except)
	{
		system_control::GetIns()->rect_error = NORECT;
		write_string(CImageCard::GetIns()->disp_hd, except.message);
		GiveError;	
		//TRACE(except.message);
		AfxMessageBox(L"设定搜索范围失败！");
	}
}


void CTopCamDlg::OnBnClickedButtonTshowrevrt()
{
	// TODO: 在此添加控件通知处理程序代码
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::Hobject invroi;
	Halcon::clear_window(CImageCard::GetIns()->disp_hd);
	try
	{
		Halcon::set_check("~give_error");
		Halcon::set_color(CImageCard::GetIns()->disp_hd, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd, "margin");
		Halcon::gen_rectangle1(&invroi, pMainFrm->ini.top_inv.r1, pMainFrm->ini.top_inv.c1, pMainFrm->ini.top_inv.r2, pMainFrm->ini.top_inv.c2);
		Halcon::disp_obj(CImageCard::GetIns()->Image, CImageCard::GetIns()->disp_hd);
		Halcon::disp_obj(invroi, CImageCard::GetIns()->disp_hd);
	}
	catch (...)
	{
		return;
	}
}


void CTopCamDlg::OnBnClickedButtonTshowresult()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (isGrab)	return;
	CString str;
	GetDlgItem(IDC_EDIT_TINVTHRESHOLD)->GetWindowText(str);
	pMainFrm->ini.TopPara.thresholdvalue = _ttoi(str);

	GetDlgItem(IDC_EDIT_TINVLIMITSUP)->GetWindowText(str);
	pMainFrm->ini.TopPara.maxarea = _ttoi(str);

	GetDlgItem(IDC_EDIT_TINVLIMITINF)->GetWindowText(str);
	pMainFrm->ini.TopPara.minarea = _ttoi(str);

	if (pMainFrm->ini.TopPara.maxarea < pMainFrm->ini.TopPara.minarea)
	{
		double t = pMainFrm->ini.TopPara.minarea; pMainFrm->ini.TopPara.maxarea = pMainFrm->ini.TopPara.minarea; pMainFrm->ini.TopPara.maxarea = t;
		str.Format(L"%d", static_cast<int>(pMainFrm->ini.TopPara.minarea));
		GetDlgItem(IDC_EDIT_TINVLIMITINF)->GetWindowText(str);
		str.Format(L"%d", static_cast<int>(pMainFrm->ini.TopPara.maxarea));
		GetDlgItem(IDC_EDIT_TINVLIMITSUP)->GetWindowText(str);
	}
	double area;
	Halcon::set_check("~give_error");
	try{
	Halcon::Hobject invroi;
	Halcon::set_tposition(CImageCard::GetIns()->disp_hd, 0, 1);
	CImageCard::GetIns()->Top_Disp_Obj(CImageCard::GetIns()->Image);
	Halcon::gen_rectangle1(&invroi, pMainFrm->ini.top_inv.r1, pMainFrm->ini.top_inv.c1, pMainFrm->ini.top_inv.r2, pMainFrm->ini.top_inv.c2);
	pMainFrm->SCM.check_inverse(CImageCard::GetIns()->Image, invroi, pMainFrm->ini.TopPara.thresholdvalue, pMainFrm->ini.TopPara.minarea, pMainFrm->ini.TopPara.maxarea, CImageCard::GetIns()->disp_hd, &area);
	}
	catch (...)
	{
		Halcon::set_check("give_error");
	}
}


void CTopCamDlg::OnBnClickedButtonTsave1()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str;
	GetDlgItem(IDC_EDIT_TINVTHRESHOLD)->GetWindowText(str);
	pMainFrm->ini.TopPara.thresholdvalue = _ttoi(str);

	GetDlgItem(IDC_EDIT_TINVLIMITSUP)->GetWindowText(str);
	pMainFrm->ini.TopPara.maxarea = _ttoi(str);

	GetDlgItem(IDC_EDIT_TINVLIMITINF)->GetWindowText(str);
	pMainFrm->ini.TopPara.minarea = _ttoi(str);

	if (pMainFrm->ini.TopPara.maxarea < pMainFrm->ini.TopPara.minarea)
	{
		double t = pMainFrm->ini.TopPara.minarea; pMainFrm->ini.TopPara.maxarea = pMainFrm->ini.TopPara.minarea; pMainFrm->ini.TopPara.maxarea = t;
		str.Format(L"%d", static_cast<int>(pMainFrm->ini.TopPara.minarea));
		GetDlgItem(IDC_EDIT_TINVLIMITINF)->GetWindowText(str);
		str.Format(L"%d", static_cast<int>(pMainFrm->ini.TopPara.maxarea));
		GetDlgItem(IDC_EDIT_TINVLIMITSUP)->GetWindowText(str);
	}
	pMainFrm->ini.SaveParaFile(PARA_IMAGE);
}


void CTopCamDlg::OnBnClickedButtonTdrawchar()
{
	// TODO: 在此添加控件通知处理程序代码
	system_control::GetIns()->is_top_grab = false;//强制结束顶部相机拍照
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::set_check("~give_error");
	Halcon::HTuple  Exception;
	try
	{
		system_control::GetIns()->rect_error = TCHARRECT;
		double r1, c1, r2, c2;
		Halcon::Hobject hobj;
		Halcon::set_color(CImageCard::GetIns()->disp_hd, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd, "margin");
		Halcon::draw_rectangle1(CImageCard::GetIns()->disp_hd, &r1, &c1, &r2, &c2);
		Halcon::gen_rectangle1(&hobj, r1, c1, r2, c2);
		Halcon::disp_obj(hobj, CImageCard::GetIns()->disp_hd);
		pMainFrm->ini.top_char.r1 = r1;
		pMainFrm->ini.top_char.c1 = c1;
		pMainFrm->ini.top_char.r2 = r2;
		pMainFrm->ini.top_char.c2 = c2;
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


void CTopCamDlg::OnBnClickedButtonTshowchar()
{
	// TODO: 在此添加控件通知处理程序代码
	system_control::GetIns()->is_top_grab = false;//强制结束顶部相机拍照
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::Hobject invroi;
	Halcon::clear_window(CImageCard::GetIns()->disp_hd);
	try
	{
		Halcon::set_check("~give_error");
		Halcon::set_color(CImageCard::GetIns()->disp_hd, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd, "margin");
		Halcon::gen_rectangle1(&invroi, pMainFrm->ini.top_char.r1, pMainFrm->ini.top_char.c1, pMainFrm->ini.top_char.r2, pMainFrm->ini.top_char.c2);
		Halcon::HDevWindowStack::Push(CImageCard::GetIns()->disp_hd);
		Halcon::HDevWindowStack::SetActive(CImageCard::GetIns()->disp_hd);
		Halcon::disp_obj(CImageCard::GetIns()->Image, CImageCard::GetIns()->disp_hd);
		Halcon::disp_obj(invroi, CImageCard::GetIns()->disp_hd);
	}
	catch (Halcon::HException &HDevExpDefaultException)
	{
		write_string(CImageCard::GetIns()->disp_hd, HDevExpDefaultException.message);
		return;
	}
}

void CTopCamDlg::OnBnClickedButtonTsavecharpara()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str;
	GetDlgItemText(IDC_EDIT_TPRESION,str);
	pMainFrm->ini.TopPara.match_acc = _ttof(str);
	pMainFrm->ini.SaveParaFile(PARA_IMAGE);
}


void CTopCamDlg::OnBnClickedButtonTsavechar()
{
	// TODO: 在此添加控件通知处理程序代码
	win_tool wt;
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	std::vector<CString> NameVector = wt.SplitCString(pMainFrm->sys.m_Prj_Vector,L",");
	if (pMainFrm->sys.m_Prj_Index >= static_cast<int>(NameVector.size())) { AfxMessageBox(L"是不是删除了项目？请重新选择项目"); return; }
	CString prj_name = NameVector[pMainFrm->sys.m_Prj_Index];
	CString path = wt.AppPath() + L"\\" + prj_name + L"\\TopModel";
	CreateDirectory(path, NULL);
	ShellExecute(NULL, L"open", _T("explorer.exe"), path, NULL, SW_SHOW);
}

void CTopCamDlg::OnBnClickedButtonTsavemodel()
{
	// TODO: 在此添加控件通知处理程序代码
	win_tool wt;
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	std::vector<CString> NameVector = wt.SplitCString(pMainFrm->sys.m_Prj_Vector, L",");
	if (pMainFrm->sys.m_Prj_Index >= static_cast<int>(NameVector.size())) { AfxMessageBox(L"是不是删除了项目？请重新选择项目"); return; }
	CString prj_name = NameVector[pMainFrm->sys.m_Prj_Index];
	CString path = wt.AppPath() + L"\\" + prj_name + L"\\TopModel";
	CreateDirectory(path, NULL);
	CString FileName = wt.AppPath() + L"\\" + prj_name + L"\\TopModel\\" + wt.Get_Date_Time()+L".jpg";
	Halcon::Hobject Model_Image;
	try
	{
		GiveError;
		Halcon::write_image(CImageCard::GetIns()->Image, "jpg", 0, (char*)(LPCSTR)(CStringA)FileName);
	}
	catch (...)
	{
		nGiveError;
		AfxMessageBox(L"请点击静态抓图进行抓取图片");
	}
}

void CTopCamDlg::OnBnClickedButtonTmatch()
{
	// TODO: 在此添加控件通知处理程序代码
	win_tool wt;
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	try
	{
		GiveError;
		std::vector<CString> images; //测试时候不需要，做个样子而已
		CImageCard::GetIns()->Top_Disp_Obj(CImageCard::GetIns()->Image);
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd, 0, 1);
		pMainFrm->SCM.check_char(CImageCard::GetIns()->Image, CImageCard::GetIns()->disp_hd, pMainFrm->ini.top_char.r1, pMainFrm->ini.top_char.c1, pMainFrm->ini.top_char.r2, pMainFrm->ini.top_char.c2,
			images, pMainFrm->ini.TopPara.match_acc, 0
		);

	}
	catch (...)
	{
		nGiveError;
	}
}


void CTopCamDlg::OnBnClickedButtonTstarttrain()
{
	// TODO: 在此添加控件通知处理程序代码
	win_tool wt;
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	std::vector<CString> NameVector = wt.SplitCString(pMainFrm->sys.m_Prj_Vector, L",");
	if (pMainFrm->sys.m_Prj_Index >= static_cast<int>(NameVector.size())) { AfxMessageBox(L"是不是删除了项目？请重新选择项目"); return; }
	CString prj_name = NameVector[pMainFrm->sys.m_Prj_Index];
	CString path = wt.AppPath() + L"\\" + prj_name + L"\\TopModel";

	std::vector<CString> images;
	win_tool::CSelectFolderDlg DirPath;
	DirPath.ProcPicDir(path, images);

	try
	{
		GiveError;
		Halcon::Hobject obj;//训练时候不需要，只是做一个样子而已
		pMainFrm->SCM.check_char(obj, CImageCard::GetIns()->disp_hd, pMainFrm->ini.top_char.r1, pMainFrm->ini.top_char.c1, pMainFrm->ini.top_char.r2, pMainFrm->ini.top_char.c2,
			images,0.5,1
			);

	}
	catch (...)
	{
		nGiveError;
	}
}




void CTopCamDlg::OnBnClickedButtonTsaveknife()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString str;
	GetDlgItem(IDC_EDIT_TKNIFETHRESHOLD)->GetWindowText(str);
	pMainFrm->ini.TopPara.knife_threshold= _ttoi(str);

	GetDlgItem(IDC_EDIT_TMAXLEN)->GetWindowText(str);
	pMainFrm->ini.TopPara.maxlen = _ttoi(str);

	GetDlgItem(IDC_EDIT_TMINLEN)->GetWindowText(str);
	pMainFrm->ini.TopPara.minlen = _ttoi(str);

	if (pMainFrm->ini.TopPara.maxlen < pMainFrm->ini.TopPara.minlen)
	{
		double t = pMainFrm->ini.TopPara.minlen; pMainFrm->ini.TopPara.maxlen = pMainFrm->ini.TopPara.minlen; pMainFrm->ini.TopPara.maxlen = t;
		str.Format(L"%d", static_cast<int>(pMainFrm->ini.TopPara.minlen));
		GetDlgItem(IDC_EDIT_TMINLEN)->GetWindowText(str);
		str.Format(L"%d", static_cast<int>(pMainFrm->ini.TopPara.maxlen));
		GetDlgItem(IDC_EDIT_TMAXLEN)->GetWindowText(str);
	}
	pMainFrm->ini.SaveParaFile(PARA_IMAGE);

}


void CTopCamDlg::OnBnClickedButtonTshowarea()
{
	// TODO: 在此添加控件通知处理程序代码
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::set_check("~give_error");
	try
	{
		system_control::GetIns()->rect_error = TKNIFERECT;
		double r1, c1, r2, c2;
		Halcon::Hobject hobj;
		Halcon::set_color(CImageCard::GetIns()->disp_hd, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd, "margin");
		Halcon::draw_rectangle1(CImageCard::GetIns()->disp_hd, &r1, &c1, &r2, &c2);
		Halcon::gen_rectangle1(&hobj, r1, c1, r2, c2);
		Halcon::disp_obj(hobj, CImageCard::GetIns()->disp_hd);
		pMainFrm->ini.top_knife.r1 = r1;
		pMainFrm->ini.top_knife.c1 = c1;
		pMainFrm->ini.top_knife.r2 = r2;
		pMainFrm->ini.top_knife.c2 = c2;
		pMainFrm->ini.SaveParaFile(PARA_IMAGE);
		system_control::GetIns()->rect_error = NORECT;
	}
	catch (Halcon::HException &except)
	{
		GiveError;
		system_control::GetIns()->rect_error = NORECT;
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd, 0, 1);
		Halcon::write_string(CImageCard::GetIns()->disp_hd, except.message);
		AfxMessageBox(L"设定搜索范围失败！");
	} 
}


void CTopCamDlg::OnBnClickedButtonTshowresult3()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::set_check("~give_error");
	try {
		GiveError;
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd, 0, 1);
		CImageCard::GetIns()->Top_Disp_Obj(CImageCard::GetIns()->Image);
		pMainFrm->SCM.check_knife(CImageCard::GetIns()->Image, CImageCard::GetIns()->disp_hd, pMainFrm->ini.top_knife.r1, pMainFrm->ini.top_knife.c1, pMainFrm->ini.top_knife.r2, pMainFrm->ini.top_knife.c2,
			pMainFrm->ini.TopPara.minlen, pMainFrm->ini.TopPara.maxlen);
	}
	catch (Halcon::HException &except)
	{
		GiveError;
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd, 0, 1);
		Halcon::write_string(CImageCard::GetIns()->disp_hd, except.message);
		return;
	}
}


void CTopCamDlg::OnBnClickedButtonTshowknifert()
{
	// TODO: 在此添加控件通知处理程序代码
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::Hobject roi;
	Halcon::clear_window(CImageCard::GetIns()->disp_hd);
	try
	{
		GiveError;
		Halcon::set_color(CImageCard::GetIns()->disp_hd, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd, "margin");
		Halcon::gen_rectangle1(&roi, pMainFrm->ini.top_knife.r1, pMainFrm->ini.top_knife.c1, pMainFrm->ini.top_knife.r2, pMainFrm->ini.top_knife.c2);
		Halcon::HDevWindowStack::Push(CImageCard::GetIns()->disp_hd);
		Halcon::HDevWindowStack::SetActive(CImageCard::GetIns()->disp_hd);
		Halcon::disp_obj(CImageCard::GetIns()->Image, CImageCard::GetIns()->disp_hd);
		Halcon::disp_obj(roi, CImageCard::GetIns()->disp_hd);
	}
	catch (Halcon::HException &except)
	{
		GiveError;
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd, 0, 1);
		Halcon::write_string(CImageCard::GetIns()->disp_hd,except.message);
		return;
	}

}








void CTopCamDlg::OnBnClickedButtonTdrawub()
{
	// TODO: 在此添加控件通知处理程序代码
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame * pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::set_check("~give_error");
	try
	{
		system_control::GetIns()->rect_error = TUNBOLT;
		double r1, c1, r2, c2;
		Halcon::Hobject hobj;
		Halcon::set_color(CImageCard::GetIns()->disp_hd, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd, "margin");
		Halcon::draw_rectangle1(CImageCard::GetIns()->disp_hd, &r1, &c1, &r2, &c2);
		Halcon::gen_rectangle1(&hobj, r1, c1, r2, c2);
		Halcon::disp_obj(hobj, CImageCard::GetIns()->disp_hd);
		pMainFrm->ini.top_unbolt.r1 = r1;
		pMainFrm->ini.top_unbolt.c1 = c1;
		pMainFrm->ini.top_unbolt.r2 = r2;
		pMainFrm->ini.top_unbolt.c2 = c2;
		pMainFrm->ini.SaveParaFile(PARA_IMAGE);
		system_control::GetIns()->rect_error = NORECT;
	}
	catch (Halcon::HException &except)
	{
		GiveError;
		system_control::GetIns()->rect_error = NORECT;
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd, 0, 1);
		Halcon::write_string(CImageCard::GetIns()->disp_hd, except.message);
		AfxMessageBox(L"设定搜索范围失败！");
	}
}


void CTopCamDlg::OnBnClickedButtonTshowub()
{
	// TODO: 在此添加控件通知处理程序代码
	if (system_control::GetIns()->rect_error) { AfxMessageBox(system_control::GetIns()->RectInfo(system_control::GetIns()->rect_error)); return; }
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::Hobject roi;
	Halcon::clear_window(CImageCard::GetIns()->disp_hd);
	try
	{
		GiveError;
		Halcon::set_color(CImageCard::GetIns()->disp_hd, "yellow");
		Halcon::set_draw(CImageCard::GetIns()->disp_hd, "margin");
		Halcon::gen_rectangle1(&roi, pMainFrm->ini.top_unbolt.r1, pMainFrm->ini.top_unbolt.c1, pMainFrm->ini.top_unbolt.r2, pMainFrm->ini.top_unbolt.c2);
		Halcon::HDevWindowStack::Push(CImageCard::GetIns()->disp_hd);
		Halcon::HDevWindowStack::SetActive(CImageCard::GetIns()->disp_hd);
		Halcon::disp_obj(CImageCard::GetIns()->Image, CImageCard::GetIns()->disp_hd);
		Halcon::disp_obj(roi, CImageCard::GetIns()->disp_hd);
	}
	catch (Halcon::HException &except)
	{
		GiveError;
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd, 0, 1);
		Halcon::write_string(CImageCard::GetIns()->disp_hd, except.message);
		return;
	}
}


void CTopCamDlg::OnBnClickedButtonTtestub()
{
	// TODO: 在此添加控件通知处理程序代码
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	Halcon::set_check("~give_error");
	try {
		GiveError;
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd, 0, 1);
		CImageCard::GetIns()->Top_Disp_Obj(CImageCard::GetIns()->Image);
		pMainFrm->SCM.check_daji(CImageCard::GetIns()->Image, CImageCard::GetIns()->disp_hd, pMainFrm->ini.top_unbolt.r1, pMainFrm->ini.top_unbolt.c1, pMainFrm->ini.top_unbolt.r2, pMainFrm->ini.top_unbolt.c2);
	}
	catch (Halcon::HException &except)
	{
		GiveError;
		Halcon::set_tposition(CImageCard::GetIns()->disp_hd, 0, 1);
		Halcon::write_string(CImageCard::GetIns()->disp_hd, except.message);
		return;
	}
}
