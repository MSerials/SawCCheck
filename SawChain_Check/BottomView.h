#pragma once


// BottomView 视图
#ifndef _B_V_
#define _B_V_
class BottomView : public CView
{
	DECLARE_DYNCREATE(BottomView)

protected:
	BottomView();           // 动态创建所使用的受保护的构造函数
	virtual ~BottomView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
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
extern BottomView * pBview;

#endif

