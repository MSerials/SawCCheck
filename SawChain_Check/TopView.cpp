// TopView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SawChain_Check.h"
#include "TopView.h"


// TopView
TopView * pTview = NULL;

IMPLEMENT_DYNCREATE(TopView, CView)

TopView::TopView()
{
	pTview = this;
}

TopView::~TopView()
{
}

BEGIN_MESSAGE_MAP(TopView, CView)
END_MESSAGE_MAP()


// TopView ��ͼ

void TopView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  �ڴ���ӻ��ƴ���
}


// TopView ���

#ifdef _DEBUG
void TopView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void TopView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// TopView ��Ϣ�������
