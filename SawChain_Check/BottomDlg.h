#pragma once


// CBottomDlg 对话框

class CBottomDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBottomDlg)

public:
	CBottomDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBottomDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BOTTOMCAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ButtonEnable();
	void ButtonUnable();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBtgrab();
	afx_msg void OnBnClickedButtonBtsnap();
	afx_msg void OnBnClickedButtonBtsave();
	afx_msg void OnBnClickedButtonBdrawrevrt();
	afx_msg void OnBnClickedButtonBshowrevrt();
	afx_msg void OnBnClickedButtonBsave();
	afx_msg void OnBnClickedButtonBshowresult();
	afx_msg void OnBnClickedButtonBdrawknifert();
	afx_msg void OnBnClickedButtonBshowknifert();
	afx_msg void OnBnClickedButtonBsaveknife();
	afx_msg void OnBnClickedButtonBshowresult3();
	afx_msg void OnBnClickedButtonBdrawchar();
	afx_msg void OnBnClickedButtonBshowchar();
	afx_msg void OnBnClickedButtonBsavecharpara();
	afx_msg void OnBnClickedButtonBstarttrain();
	afx_msg void OnBnClickedButtonBsavechar();
	afx_msg void OnBnClickedButtonBsavemodel();
	afx_msg void OnBnClickedButtonBmatch();
	afx_msg void OnBnClickedButtonBshowimg();
	//afx_msg void OnBnClickedButtonBshow();

private:
	static UINT grab(LPVOID lp);
	bool isGrab;
public:
	
	afx_msg void OnBnClickedButtonBdrawub();
	afx_msg void OnBnClickedButtonBshowub();
	afx_msg void OnBnClickedButtonBtestub();
};
