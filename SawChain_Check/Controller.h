#pragma once


// Controller 对话框

class Controller : public CDialogEx
{
	DECLARE_DYNAMIC(Controller)

public:
	Controller(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Controller();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SYSCTRL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonConveyorcw();
	afx_msg void OnBnClickedButtonConveyorccw();
	afx_msg void OnBnClickedButtonConveyorstop();
	afx_msg void OnBnClickedButtonPressCyl();
	afx_msg void OnBnClickedButtonPushCyl();
	afx_msg void OnBnClickedButtonMagnetCyl();
	afx_msg void OnBnClickedButtonMarkCyl();
	afx_msg void OnBnClickedButtonMagnet();
	virtual BOOL OnInitDialog();
	void UpdateUI();
	afx_msg void OnBnClickedButtonAlertstop();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonCcw();
	afx_msg void OnBnClickedButtonCw();
	afx_msg void OnBnClickedButtonInstruction();
	afx_msg void OnBnClickedButtonIsmark();
};
