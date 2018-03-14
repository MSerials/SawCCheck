

#include "stdafx.h"
#include "CTxt.h"
//#include "fstream.h"
//#include "IniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
/*
1.add txt = new CTxt();		to where to initial
2.add txt->Init();	        to where to initial
3.add #include "CTxt.h"                to where to use and where to initial
4.���ú���ʱ��ֱ��          txt->WriteContent(ID);



*/
//CTxt *txt = NULL;

CTxt::CTxt()
:TotalCheck(0)
{
	m_strTxtPath = GetProgramPath() + L"\\DefectiveRecord";
	TickStart = GetTickCount();
	m_CurrentDate = GetCurrentDate();
	FileName = m_strTxtPath + L"\\" + m_CurrentDate + L".csv";
	path = FileName;
	
}

CTxt::~CTxt()
{
	recordFile.Flush();
	recordFile.Close();
	m_strTxtPath = "";
	//AfxMessageBox(L"�쳣�ر�");
}


void CTxt::WriteContent(int ID)
{
	CString str;
	str.Format(L"%d,",m_lastline );
	str = str + getCurrentTime();
	switch(ID)
	{
	case RTDAJI:			recordFile.WriteString(str+L",���,����\n");			break;
	case RTLIANJIEPIAN:		recordFile.WriteString(str+L",����Ƭװ��,����\n");	break;
	case RTDAOKOU:			recordFile.WriteString(str+L",����,����\n");			break;
	case RTZIFU:			recordFile.WriteString(str+L",����,����\n");		break;
	case RTSHUANGDAOLI:		recordFile.WriteString(str+L",˫����,����\n");		break;
	case RSIJIE1:			recordFile.WriteString(str+L",�����,����\n");		break;
	case RSIJIE2:			recordFile.WriteString(str+L",�����,����\n");		break;
	case RSIJIE3:			recordFile.WriteString(str + L",��������,����\n");		break;
	case RBDAJI:			recordFile.WriteString(str+L",���,�ײ�\n");			break;
	case RBLIANJIEPIAN:		recordFile.WriteString(str+L",����Ƭװ��,�ײ�\n");	break;
	case RBDAOKOU:			recordFile.WriteString(str+L",����,�ײ�\n");			break;
	case RBZIFU:			recordFile.WriteString(str+L",����,�ײ�\n");			break;
	default:break;
	}

	m_lastline += 1;
}

void CTxt::WriteContent(int ID, CString str)
{
	CString tstr;
	tstr.Format(L"%d,",m_lastline );
	tstr = tstr + getCurrentTime();
	switch(ID)
	{
	case RTDAJI:			recordFile.WriteString(tstr+L",���,����\n");		break;
	case RTLIANJIEPIAN:		recordFile.WriteString(tstr+L",����Ƭװ��" + str + L",����\n");	break;
	case RTDAOKOU:			recordFile.WriteString(tstr+L",����,����\n");		break;
	case RTZIFU:			recordFile.WriteString(tstr+L",����,����\n");	break;
	case RTSHUANGDAOLI:		recordFile.WriteString(tstr+L",˫����,����\n");		break;
	case RSIJIE1:			recordFile.WriteString(tstr+L",�����,����\n");		break;
	case RSIJIE2:			recordFile.WriteString(tstr+L",�����,����\n");		break;
	case RSIJIE3:			recordFile.WriteString(tstr+L",��������,����\n");		break;
	case RBDAJI:			recordFile.WriteString(tstr+L",���,�ײ�\n");		break;
	case RBLIANJIEPIAN:		recordFile.WriteString(tstr+L",����Ƭװ��" + str + L",�ײ�");	break;
	case RBDAOKOU:			recordFile.WriteString(tstr+L",����,�ײ�\n");		break;
	case RBZIFU:			recordFile.WriteString(tstr+L",����,�ײ�\n");		break;
	case CLOSE :            recordFile.WriteString(tstr+L",����ر�,*****,\n");		break;
	default:break;
	}

	m_lastline += 1;
}

void CTxt::WriteContent(int ID, int ChainNum)
{
	CString tstr,nstr;
	tstr.Format(L"%d,",m_lastline );
	tstr = tstr + getCurrentTime();
	nstr.Format(L"%d",ChainNum);
	switch(ID)
	{
	case RTDAJI:			recordFile.WriteString(tstr+L",���,����\n");		break;
	case RTLIANJIEPIAN:		recordFile.WriteString(tstr+L",����Ƭװ��" + L",����\n");	break;
	case RTDAOKOU:			recordFile.WriteString(tstr+L",����,����\n");		break;
	case RTZIFU:			recordFile.WriteString(tstr+L",����,����\n");	break;
	case RTSHUANGDAOLI:		recordFile.WriteString(tstr+L",˫����,����\n");		break;
	case RSIJIE1:			recordFile.WriteString(tstr+L",�����,����\n");		break;
	case RSIJIE2:			recordFile.WriteString(tstr+L",�����,����\n");		break;
	case RSIJIE3:			recordFile.WriteString(tstr + L",��������,����\n");		break;
	case RBDAJI:			recordFile.WriteString(tstr+L",���,�ײ�\n");		break;
	case RBLIANJIEPIAN:		recordFile.WriteString(tstr+L",����Ƭװ��" + L",�ײ�\n");	break;
	case RBDAOKOU:			recordFile.WriteString(tstr+L",����,�ײ�\n");		break;
	case RBZIFU:			recordFile.WriteString(tstr+L",����,�ײ�\n");		break;
	case CLOSE :            recordFile.WriteString(tstr+L",����ر�,�������,"+nstr+L"��\n");		break;
	default:break;
	}

	m_lastline += 1;
}


void CTxt::WriteContent(CString str)
{	
	recordFile.WriteString(str);
	m_lastline += 1;
}

BOOL CTxt::Init(){

	if(!OpenFile()) return FALSE;
	return TRUE;
	//ini->LoadFromFile(PARA_PRJ);

	//if(ini->m_shutCorrectly)
	//{
	//	ini->m_TotalCheck = 0;
	//}

	//ini->m_shutCorrectly = 0; //������
	//ini->SetIniDir("ini");
	//ini->SetIniFile(ini->prj_CurrentProject+".ini");
	//ini->SaveToFile(PARA_PRJ);	
}


//���ļ�
BOOL CTxt::OpenFile()
{
	CFileFind finder;
	if (!CreateDirectory(m_strTxtPath, NULL)) ;
	if(!finder.FindFile(path))
	{
		recordFile.Open(path, CFile::modeCreate|CFile::modeReadWrite);
		setlocale(LC_CTYPE, "chs");
		CString str = L"���,���ʱ��,���ϸ�����,�����ײ�\n"; //ͳ��:,����,0,���,0,��������Ƭװ��,0,��������δĥ,0,�������,0,�ײ�����Ƭװ��,0,�ײ�����δĥ,0,����,0,˫����,0,����,0\n
		recordFile.WriteString(str);
		m_lastline = 1;
	//	if(!SetLineValue(str,3)) return FALSE;
		return TRUE;
	}
	else
	{
		recordFile.Open(path,CFile::modeReadWrite);
		setlocale(LC_CTYPE, "chs");
		m_lastline = GetLastLine();
		m_lastline--;
		return TRUE;
	}
	return FALSE;
}
//�ҵ���¼�ļ������һ��
int CTxt::GetLastLine()
{
	int line = 1;
	CString strContent;

	recordFile.SeekToBegin();

	while(recordFile.ReadString(strContent))
		line += 1;

	return line;
}

BOOL CTxt::SetLineValue(CString str, int line)
{
	recordFile.SeekToBegin();
	recordFile.WriteString(str);
	return TRUE;
}

/**
BOOL CTxt::SetCellValue(int row, int col, CString value)
{

	return TRUE;
}
*/

void CTxt::OpenTxtFile()
{
	::ShellExecute(NULL,L"open",path,NULL,NULL,SW_SHOW);
}

//��ȡ��������
CString CTxt::GetCurrentDate()
{
	CString str;
    CTime time;
    time=CTime::GetCurrentTime();				//��ȡ��ǰʱ������
    str=time.Format(_T("%Y-%m-%d"));			//��ʽ������ʱ��
	return str;
}

//��ȡ��ǰʱ��
CString CTxt::getCurrentTime()
{
	CString str;
    CTime time;
    time=CTime::GetCurrentTime();             //��ȡ��ǰʱ������
    str=time.Format(_T("%H:%M:%S"));   //��ʽ������ʱ��
	return str;
}

//��ȡ�����Ѿ����е�ʱ��
CString CTxt::GetProgramRunTime()
{
	CString str;
	TickEnd = GetTickCount();
	str.Format(L"%d",TickEnd-TickStart);
	return str;
}

//��ȡ��ǰ����·����
CString CTxt::GetProgramPath()
{
	TCHAR szModulePath[MAX_PATH] = {0};
	CString strCurDir;
	::GetModuleFileName(NULL,szModulePath,_MAX_PATH);
	strCurDir  = szModulePath;
	strCurDir  = strCurDir.Left(strCurDir.ReverseFind(TEXT('\\')));
	return strCurDir;
}


