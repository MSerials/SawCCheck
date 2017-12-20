#pragma once


// TopView ��ͼ
#ifndef _T_V_
#define _T_V_


class TopView : public CView
{
	DECLARE_DYNCREATE(TopView)

protected:
	TopView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~TopView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	HWND get_handle() { return this->m_hWnd; }
	CRect get_rect() {
		CRect rect;
		GetClientRect(&rect); return rect;
	}

protected:
	DECLARE_MESSAGE_MAP()
};

extern TopView* pTview;

#endif


