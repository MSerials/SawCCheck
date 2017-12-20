#pragma once

#include "TopCamDlg.h"
#include "BottomDlg.h"
#include "MainControl.h"
// CTabControl

class CTabControl : public CTabCtrl
{
	DECLARE_DYNAMIC(CTabControl)

public:
	CTabControl();
	virtual ~CTabControl();

	void InitData();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
private:
	CBottomDlg		m_BottomDlg;
	CTopCamDlg		m_TopDlg;
	CMainControl	m_MainCtrl;
};


