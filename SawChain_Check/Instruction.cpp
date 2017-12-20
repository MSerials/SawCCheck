// Instruction.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SawChain_Check.h"
#include "Instruction.h"
#include "afxdialogex.h"


// Instruction �Ի���

IMPLEMENT_DYNAMIC(Instruction, CDialogEx)

Instruction::Instruction(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INSTRUCTION, pParent)
{

}

Instruction::~Instruction()
{
}

void Instruction::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Instruction, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_INS, &Instruction::OnEnChangeEditIns)
END_MESSAGE_MAP()


// Instruction ��Ϣ�������


BOOL Instruction::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	TEXTMETRIC tm;
	CRect rect;
	GetDlgItem(IDC_EDIT_INS)->GetClientRect(&rect);
	CDC* pdc = GetDlgItem(IDC_EDIT_INS)->GetDC();
	::GetTextMetrics(pdc->m_hDC, &tm);
	GetDlgItem(IDC_EDIT_INS)->ReleaseDC(pdc);
	long m_nLineCount = static_cast<long>(rect.bottom / (tm.tmHeight - 1.5));
	//

	CString str = L"\
	�㽭���������ܼ������޹�˾\r\n\
	Author:U238 Time:2017/5/30\r\n\
һ ����Ĭ�ϲ���\r\n\
   1.������ع�Ⱦ�Ϊ750΢��\r\n\
   2.�ŷ�����Ĳ���Ϊ��ÿһȦ��Ҫ��������ĿΪ:7000\r\n\
   3.��һ�ڵ�������ĿΪ:1600\r\n\
   4.�ŷ�����ٶ�Ĭ��Ϊ:34000\r\n\
   5.balser�����DeviceIDӦ�÷ֱ����ó�\"UPCamera\"��\"BottomCamera\"�����޷���ȡ���\r\n\
	\r\n\
�� �쳣״̬����\r\n\
   1.���ʹ�����ı䷽��a.��򿪵���䣬�����ʹ��ļ̵����Ƿ��任������ᣬ��ô��������ʹ��ٶ�\r\n\
                         b.����̵�������仯����鿴�Ƿ�����������Ƿ���ȷ\r\n\
		";


	SetDlgItemText(IDC_EDIT_INS, (LPCTSTR)str);
	int nLine = ((CEdit*)GetDlgItem(IDC_EDIT_INS))->GetLineCount();
	if (nLine > m_nLineCount)
	{
		GetDlgItem(IDC_EDIT_INS)->ShowScrollBar(SB_VERT, TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_INS)->ShowScrollBar(SB_VERT, FALSE);
	}





















	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void Instruction::OnEnChangeEditIns()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
