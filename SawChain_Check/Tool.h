//����
#pragma once
//
#include "stdafx.h"
#include <windows.h> //���ʺ�64λ����
#include <tlhelp32.h>












#ifndef __TOOLS__
#define __TOOLS__








class win_tool
{
public:
	win_tool() {};
	virtual ~win_tool() {};
	int GetProcessIDByName(PWSTR pname)
	{
		HANDLE SnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
		SHFILEINFO shSmall;
		BOOL Status = FALSE;
		PROCESSENTRY32 ProcessInfo;//����������Ϣ����
		DWORD pid = 0;
		if (SnapShot == NULL)
		{
			return -1;
		}

		ProcessInfo.dwSize = sizeof(ProcessInfo);//����ProcessInfo�Ĵ�С
												 //����ϵͳ�е�һ�����̵���Ϣ
		Status = Process32First(SnapShot, &ProcessInfo);

		while (Status)
		{
			//��ȡ�����ļ���Ϣ
			SHGetFileInfo(ProcessInfo.szExeFile, 0, &shSmall,
				sizeof(shSmall), SHGFI_ICON | SHGFI_SMALLICON);
			//���б�ؼ������ӳ������
			if (StrStrI(ProcessInfo.szExeFile, pname) != NULL)
			{
				pid = ProcessInfo.th32ProcessID;
				break;
			}
			//��ȡ��һ�����̵���Ϣ
			Status = Process32Next(SnapShot, &ProcessInfo);

		}
		return pid;
	}

	CString AppPath()
	{
		CString AppPath;
		::GetModuleFileName(GetModuleHandle(NULL), AppPath.GetBuffer(300), 300);
		AppPath.ReleaseBuffer();
		AppPath = AppPath.Left(AppPath.ReverseFind('\\'));
		return AppPath;
	}


	CString Get_Date()
	{
		SYSTEMTIME st;
		CString strDate;
		GetLocalTime(&st);
		strDate.Format(_T("%4d-%d-%d"), st.wYear, st.wMonth, st.wDay);
		return strDate;
	}

	CString Get_Time()
	{
		SYSTEMTIME st;
		CString strTime;
		GetLocalTime(&st);
		strTime.Format(_T("%d-%d-%d"), st.wHour, st.wMinute, st.wSecond);
		return  strTime;
	}

	CString Get_Date_Time()
	{
		CString str;
		SYSTEMTIME st;
		CString strDate, strTime;
		GetLocalTime(&st);
		strDate.Format(_T("%4d-%d-%d_"), st.wYear, st.wMonth, st.wDay);
		strTime.Format(_T("%d-%d-%d"), st.wHour, st.wMinute, st.wSecond);
		str = strDate + strTime;
		return str;
	}

	std::vector<CString> SplitCString(CString strSource, CString ch)
	{
		std::vector <CString> vecString;
		strSource.Replace(L" ", L"");
		if (strSource.IsEmpty()) return vecString;
		int iPos = 0;
		CString strTmp;
		strTmp = strSource.Tokenize(ch, iPos);
		while (strTmp.Trim() != _T(""))
		{
			vecString.push_back(strTmp);
			strTmp = strSource.Tokenize(ch, iPos);
		}
		return vecString;
	}


	class CSelectFolderDlg
	{

		/*
		std::vector<CString> images;
		win_tool::CSelectFolderDlg DirPath;
		DirPath.ProcPicDir(g.prjini.m_Prj_Name + L"\\TopError\\", images);
		
		*/
			
			
	public:
		//����һ��ѡ���ļ��еĶԻ��򣬷�����ѡ·��  
		static CString Show()
		{
			TCHAR           szFolderPath[MAX_PATH] = { 0 };
			CString         strFolderPath = TEXT("");

			BROWSEINFO      sInfo;
			::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
			sInfo.pidlRoot = 0;
			sInfo.lpszTitle = _T("��ѡ��һ���ļ��У�");
			sInfo.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_RETURNONLYFSDIRS;
			sInfo.lpfn = NULL;

			// ��ʾ�ļ���ѡ��Ի���  
			LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
			if (lpidlBrowse != NULL)
			{
				// ȡ���ļ�����  
				if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
				{
					strFolderPath = szFolderPath;
				}
			}
			if (lpidlBrowse != NULL)
			{
				::CoTaskMemFree(lpidlBrowse);
			}

			return strFolderPath;

		}

		bool ProcPicDir(CString strPicDir, vector<CString>& strPath)
		{
			strPath.clear();
			CFileFind fileFinder;

			if (strPicDir.Right(1) == TEXT("\\"))
			{
				int nPos = strPicDir.ReverseFind(TEXT('\\'));
				strPicDir = strPicDir.Left(nPos);
			}

			CString strPicFile = TEXT("");
			strPicFile.Format(TEXT("%s\\%s"), strPicDir, TEXT("*.*"));

			BOOL bWorking = fileFinder.FindFile(strPicFile);
			while (bWorking)
			{
				bWorking = fileFinder.FindNextFile();
				if (fileFinder.IsDots())
				{
					continue;
				}

				CString strFilePath = fileFinder.GetFilePath();
				//		if (fileFinder.IsDirectory())
				//		{
				//��������Ŀ¼
				//			ProcPicDir(strFilePath);
				//		}
				//		else
				//		{
				int nPos = strFilePath.ReverseFind(TEXT('.'));
				CString strExt = strFilePath.Right(strFilePath.GetLength() - nPos - 1);
				if (strExt.CompareNoCase(TEXT("jpg")) == 0 ||
					strExt.CompareNoCase(TEXT("jpeg")) == 0 ||
					strExt.CompareNoCase(TEXT("bmp")) == 0)
				{
					//����ͼƬ
					//...
					strPath.push_back(strFilePath);
				}
			}
			fileFinder.Close();
			return true;
		}

	};





};


#endif

