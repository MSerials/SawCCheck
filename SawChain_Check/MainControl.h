#pragma once


// CMainControl 对话框

class CMainControl : public CDialogEx
{
	DECLARE_DYNAMIC(CMainControl)

public:
	CMainControl(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMainControl();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAINCONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAddnewprj();
	afx_msg void OnSelchangeComboSelPrj();
	afx_msg void OnBnClickedButtonChainlen();
	afx_msg void OnBnClickedButtonOrigin();
	afx_msg LRESULT ShowCounter(WPARAM wParam, LPARAM lParam);


	std::mutex lock;
	void UpdateUI();
	static UINT origin(LPVOID lp);
	bool isOrigin;
};
