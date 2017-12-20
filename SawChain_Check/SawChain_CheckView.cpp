// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ������� 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// SawChain_CheckView.cpp : CSawChain_CheckView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SawChain_Check.h"
#endif

#include "SawChain_CheckDoc.h"
#include "SawChain_CheckView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSawChain_CheckView

IMPLEMENT_DYNCREATE(CSawChain_CheckView, CView)

BEGIN_MESSAGE_MAP(CSawChain_CheckView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSawChain_CheckView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CSawChain_CheckView ����/����

CSawChain_CheckView::CSawChain_CheckView()
{
	// TODO: �ڴ˴���ӹ������

}

CSawChain_CheckView::~CSawChain_CheckView()
{
}

BOOL CSawChain_CheckView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSawChain_CheckView ����

void CSawChain_CheckView::OnDraw(CDC* /*pDC*/)
{
	CSawChain_CheckDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CSawChain_CheckView ��ӡ


void CSawChain_CheckView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSawChain_CheckView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSawChain_CheckView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSawChain_CheckView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CSawChain_CheckView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSawChain_CheckView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSawChain_CheckView ���

#ifdef _DEBUG
void CSawChain_CheckView::AssertValid() const
{
	CView::AssertValid();
}

void CSawChain_CheckView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSawChain_CheckDoc* CSawChain_CheckView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSawChain_CheckDoc)));
	return (CSawChain_CheckDoc*)m_pDocument;
}
#endif //_DEBUG


// CSawChain_CheckView ��Ϣ�������
