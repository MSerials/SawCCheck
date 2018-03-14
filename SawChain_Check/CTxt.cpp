

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
4.调用函数时候直接          txt->WriteContent(ID);



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
	//AfxMessageBox(L"异常关闭");
}


void CTxt::WriteContent(int ID)
{
	CString str;
	str.Format(_T("%d,"),m_lastline );
	str = str + getCurrentTime();
	switch(ID)
	{
	case RTDAJI:			recordFile.WriteString(str+",打机,顶部\n");			break;
	case RTLIANJIEPIAN:		recordFile.WriteString(str+",连接片装反,顶部\n");	break;
	case RTDAOKOU:			recordFile.WriteString(str+",刀口,顶部\n");			break;
	case RTZIFU:			recordFile.WriteString(str+",混料,顶部\n");		break;
	case RTSHUANGDAOLI:		recordFile.WriteString(str+",双刀粒,顶部\n");		break;
	case RSIJIE1:			recordFile.WriteString(str+",死结进,顶部\n");		break;
	case RSIJIE2:			recordFile.WriteString(str+",死结出,顶部\n");		break;
	case RSIJIE3:			recordFile.WriteString(str + ",桌面死结,顶部\n");		break;
	case RBDAJI:			recordFile.WriteString(str+",打机,底部\n");			break;
	case RBLIANJIEPIAN:		recordFile.WriteString(str+",连接片装反,底部\n");	break;
	case RBDAOKOU:			recordFile.WriteString(str+",刀口,底部\n");			break;
	case RBZIFU:			recordFile.WriteString(str+",混料,底部\n");			break;
	default:break;
	}

	m_lastline += 1;
}

void CTxt::WriteContent(int ID, CString str)
{
	CString tstr;
	tstr.Format(_T("%d,"),m_lastline );
	tstr = tstr + getCurrentTime();
	switch(ID)
	{
	case RTDAJI:			recordFile.WriteString(tstr+",打机,顶部\n");		break;
	case RTLIANJIEPIAN:		recordFile.WriteString(tstr+",连接片装反" + str + ",顶部" + "\n");	break;
	case RTDAOKOU:			recordFile.WriteString(tstr+",刀口,顶部\n");		break;
	case RTZIFU:			recordFile.WriteString(tstr+",混料,顶部\n");	break;
	case RTSHUANGDAOLI:		recordFile.WriteString(tstr+",双刀粒,顶部\n");		break;
	case RSIJIE1:			recordFile.WriteString(tstr+",死结进,顶部\n");		break;
	case RSIJIE2:			recordFile.WriteString(tstr+",死结出,顶部\n");		break;
	case RSIJIE3:			recordFile.WriteString(tstr+",桌面死结,顶部\n");		break;
	case RBDAJI:			recordFile.WriteString(tstr+",打机,底部\n");		break;
	case RBLIANJIEPIAN:		recordFile.WriteString(tstr+",连接片装反" + str + ",底部" + "\n");	break;
	case RBDAOKOU:			recordFile.WriteString(tstr+",刀口,底部\n");		break;
	case RBZIFU:			recordFile.WriteString(tstr+",混料,底部\n");		break;
	case CLOSE :            recordFile.WriteString(tstr+",软件关闭,*****,\n");		break;
	default:break;
	}

	m_lastline += 1;
}

void CTxt::WriteContent(int ID, int ChainNum)
{
	CString tstr,nstr;
	tstr.Format(_T("%d,"),m_lastline );
	tstr = tstr + getCurrentTime();
	nstr.Format(L"%d",ChainNum);
	switch(ID)
	{
	case RTDAJI:			recordFile.WriteString(tstr+",打机,顶部\n");		break;
	case RTLIANJIEPIAN:		recordFile.WriteString(tstr+",连接片装反" + ",顶部" + "\n");	break;
	case RTDAOKOU:			recordFile.WriteString(tstr+",刀口,顶部\n");		break;
	case RTZIFU:			recordFile.WriteString(tstr+",混料,顶部\n");	break;
	case RTSHUANGDAOLI:		recordFile.WriteString(tstr+",双刀粒,顶部\n");		break;
	case RSIJIE1:			recordFile.WriteString(tstr+",死结进,顶部\n");		break;
	case RSIJIE2:			recordFile.WriteString(tstr+",死结出,顶部\n");		break;
	case RSIJIE3:			recordFile.WriteString(tstr + ",桌面死结,顶部\n");		break;
	case RBDAJI:			recordFile.WriteString(tstr+",打机,底部\n");		break;
	case RBLIANJIEPIAN:		recordFile.WriteString(tstr+",连接片装反" + ",底部" + "\n");	break;
	case RBDAOKOU:			recordFile.WriteString(tstr+",刀口,底部\n");		break;
	case RBZIFU:			recordFile.WriteString(tstr+",混料,底部\n");		break;
	case CLOSE :            recordFile.WriteString(tstr+",软件关闭,检测条数,"+nstr+"条"+"\n");		break;
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

	//ini->m_shutCorrectly = 0; //运行中
	//ini->SetIniDir("ini");
	//ini->SetIniFile(ini->prj_CurrentProject+".ini");
	//ini->SaveToFile(PARA_PRJ);	
}


//打开文件
BOOL CTxt::OpenFile()
{
	CFileFind finder;
	if (!CreateDirectory(m_strTxtPath, NULL)) ;
	if(!finder.FindFile(path))
	{
		recordFile.Open(path,CFile::typeText|CFile::modeCreate|CFile::modeReadWrite);
		CString str = L"编号,检测时间,不合格种类,顶部底部\n"; //统计:,总数,0,打机,0,顶部连接片装反,0,顶部刀口未磨,0,顶部打机,0,底部连接片装反,0,底部刀口未磨,0,混料,0,双刀粒,0,死结,0\n
		recordFile.WriteString(str);
		m_lastline = 1;
	//	if(!SetLineValue(str,3)) return FALSE;
		return TRUE;
	}
	else
	{
		recordFile.Open(path,CFile::typeText|CFile::modeReadWrite);
		m_lastline = GetLastLine();
		m_lastline--;
		return TRUE;
	}
	return FALSE;
}
//找到记录文件的最后一行
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

//获取当天日期
CString CTxt::GetCurrentDate()
{
	CString str;
    CTime time;
    time=CTime::GetCurrentTime();				//获取当前时间日期
    str=time.Format(_T("%Y-%m-%d"));			//格式化日期时间
	return str;
}

//获取当前时间
CString CTxt::getCurrentTime()
{
	CString str;
    CTime time;
    time=CTime::GetCurrentTime();             //获取当前时间日期
    str=time.Format(_T("%H:%M:%S"));   //格式化日期时间
	return str;
}

//获取程序已经运行的时间
CString CTxt::GetProgramRunTime()
{
	CString str;
	TickEnd = GetTickCount();
	str.Format(L"%d",TickEnd-TickStart);
	return str;
}

//获取当前程序路径名
CString CTxt::GetProgramPath()
{
	TCHAR szModulePath[MAX_PATH] = {0};
	CString strCurDir;
	::GetModuleFileName(NULL,szModulePath,_MAX_PATH);
	strCurDir  = szModulePath;
	strCurDir  = strCurDir.Left(strCurDir.ReverseFind(TEXT('\\')));
	return strCurDir;
}


