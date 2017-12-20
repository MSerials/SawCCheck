// Instruction.cpp : 实现文件
//

#include "stdafx.h"
#include "SawChain_Check.h"
#include "Instruction.h"
#include "afxdialogex.h"


// Instruction 对话框

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


// Instruction 消息处理程序


BOOL Instruction::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	TEXTMETRIC tm;
	CRect rect;
	GetDlgItem(IDC_EDIT_INS)->GetClientRect(&rect);
	CDC* pdc = GetDlgItem(IDC_EDIT_INS)->GetDC();
	::GetTextMetrics(pdc->m_hDC, &tm);
	GetDlgItem(IDC_EDIT_INS)->ReleaseDC(pdc);
	long m_nLineCount = static_cast<long>(rect.bottom / (tm.tmHeight - 1.5));
	//

	CString str = L"\
	浙江爱易特智能技术有限公司\r\n\
	Author:U238 Time:2017/5/30\r\n\
一 机器默认参数\r\n\
   1.相机的曝光度均为750微秒\r\n\
   2.伺服电机的参数为，每一圈需要的脉冲数目为:7000\r\n\
   3.走一节的脉冲数目为:1600\r\n\
   4.伺服电机速度默认为:34000\r\n\
   5.balser相机的DeviceID应该分别设置成\"UPCamera\"和\"BottomCamera\"否则无法读取相机\r\n\
	\r\n\
二 异常状态处里\r\n\
   1.输送带不会改变方向：a.请打开电控箱，看输送带的继电器是否会变换，如果会，那么请调慢输送带速度\r\n\
                         b.如果继电器不会变化，请查看是否程序检测链条是否正确\r\n\
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
				  // 异常: OCX 属性页应返回 FALSE
}


void Instruction::OnEnChangeEditIns()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
