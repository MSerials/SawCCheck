#pragma once


// CTopCamDlg 对话框

class CTopCamDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTopCamDlg)

public:
	CTopCamDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTopCamDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TOPCAM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonTgrab();
	afx_msg void OnBnClickedButtonTsnap();
	afx_msg void OnBnClickedButtonTshow();
	afx_msg void OnBnClickedButtonTsave();

public:
	
private:
	static UINT grab(LPVOID lp);
	bool isGrab;

public:
	afx_msg void OnBnClickedButtonTdrawrevrt();
	afx_msg void OnBnClickedButtonTshowrevrt();
	afx_msg void OnBnClickedButtonTshowresult();
	afx_msg void OnBnClickedButtonTsave1();
	afx_msg void OnBnClickedButtonTdrawchar();
	afx_msg void OnBnClickedButtonTshowchar();
	afx_msg void OnBnClickedButtonTsavechar();
	afx_msg void OnBnClickedButtonTstarttrain();
	void ButtonEnable();
	void ButtonUnable();
	afx_msg void OnBnClickedButtonTsaveknife();
	afx_msg void OnBnClickedButtonTshowarea();
	afx_msg void OnBnClickedButtonTshowresult3();
	afx_msg void OnBnClickedButtonTshowknifert();
	afx_msg void OnBnClickedButtonTsavemodel();
	afx_msg void OnBnClickedButtonTmatch();
	afx_msg void OnBnClickedButtonTsavecharpara();
	afx_msg void OnBnClickedButtonTdrawub();
	afx_msg void OnBnClickedButtonTshowub();
	afx_msg void OnBnClickedButtonTtestub();
};
