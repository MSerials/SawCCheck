#pragma once


// Instruction �Ի���

class Instruction : public CDialogEx
{
	DECLARE_DYNAMIC(Instruction)

public:
	Instruction(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Instruction();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSTRUCTION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditIns();
};
