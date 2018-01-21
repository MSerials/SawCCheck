#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <map>

#ifndef __TXT_EDIT__
#define __TXT_EDIT__

#define MAX_PATH 260

enum{
	RESERVED,TOTAL,RDAJI, RLIANJIEPIAN, RDAOKOU, RZIFU, RSHUANGDAOLI, RSIJIE1, RSIJIE2,	RSIJIE3, RTDAJI, RTLIANJIEPIAN, RTDAOKOU, RTZIFU, RTSHUANGDAOLI, RTSIJIE, RBDAJI, RBLIANJIEPIAN, RBDAOKOU, RBZIFU, RBSHUANGDAOLI, RBSIJIE,QUIT,SAVE,XLSVISABLE,FIX,CLOSE
	}; 

class CTxt
{
	public:
	CTxt();
	~CTxt();
	BOOL Init();

	CStdioFile recordFile;
	private:

	CString m_strTxtPath;
	long TickStart;
	long TickEnd;


	CString GetProgramPath();
	CString GetCurrentDate();
	CString getCurrentTime();
	CString GetProgramRunTime();
	int GetLastLine();
	int m_lastline;
	int DefectiveRecord[RBSIJIE+1];
	CString strDefRec[RBSIJIE+1];

	public:
	void WriteContent(int ID);
	void WriteContent(int ID, CString str);
	void WriteContent(int ID, int ChainNum);
	void WriteContent(CString str);
	int TotalCheck;//记录了今天检测了多少链条

	//all keys are of this time
	struct key
	{
		//list of values in key
		CArray<CString, CString> values; 
		//corresponding list of value names
		CArray<CString, CString> names;
	public:
		
	};
	//list of keys in ini
	CArray<key, key> keys; 
	//corresponding list of key names
	CArray<CString, CString> names; 		
	//all private functions
	
	public:
		CFileException fileException;
		CStdioFile TxtFile;
		CString error;
		CString m_CurrentDate;
		CString FileName1;
		CString FileName;
		CString path;

		void OpenTxtFile();
		BOOL OpenFile();
		BOOL SetLineValue(CString str, int line);
	
	/**
	//CFile TxtFile;
	//BOOL SetCellValue(int row, int col, CString value);
	CString GetCellValue(int row, int col);
	void CreateTxtFile();
	BOOL ReadTxtFile();
	BOOL CreateMultipleDirectory(CString szPath);
	BOOL ReadFile();
	BOOL ReadFile(CString FileName);
	void FirstWrite();
	*/


	
	
	
	
	
	//CString m_strBuffer;
	
	
	
};

class Csv
{
private:
	Csv() {};
	virtual ~Csv() {};
	CTxt txt;
public:
	static Csv * GetIns() { static Csv _csv; return &_csv; }
	void Init() { txt.Init(); std::cout << "csv init" << std::endl; }
	void WriteContent(int ID) { txt.WriteContent(ID); }
	void WriteContent(int ID, CString str) { txt.WriteContent(ID,str); };
	void WriteContent(int ID, int ChainNum) { txt.WriteContent(ID,ChainNum); };
	void WriteContent(CString str) { txt.WriteContent(str); };
};
//extern CTxt *txt;

#endif