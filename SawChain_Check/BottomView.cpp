// BottomView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SawChain_Check.h"
#include "BottomView.h"


// BottomView
BottomView * pBview = NULL;
IMPLEMENT_DYNCREATE(BottomView, CView)

BottomView::BottomView()
{
	pBview = this;
}

BottomView::~BottomView()
{
}

BEGIN_MESSAGE_MAP(BottomView, CView)
END_MESSAGE_MAP()


// BottomView ��ͼ

void BottomView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  �ڴ���ӻ��ƴ���
}


// BottomView ���

#ifdef _DEBUG
void BottomView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void BottomView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// BottomView ��Ϣ�������
