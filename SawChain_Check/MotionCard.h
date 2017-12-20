#pragma once

// CMotionCard 命令目标


#if !defined(AFX_MOTIONCARD_H__FAF08485_1C98_4A40_AA13_7EAAA74DD9B5__INCLUDED_)
#define AFX_MOTIONCARD_H__FAF08485_1C98_4A40_AA13_7EAAA74DD9B5__INCLUDED_




#include <iostream>
#include <string>
#include <math.h>




#define TOTAL_CARD_NUM           1
#define MAX_AXIS_LEN             5
#define MAX_IO_NUM               16
#define INPUT_NUM				 16
#define OUTPUT_NUM				 16
#define dwPortCount              2
#define dwPortBit                16
#define EXCUTE_OK				 0

#define STATUS_BIT_NUMS          32
#define RUN_STATUS_BIT           10
#define MIN_COMPAREA_VALUE       1E-6
#define MIN_REL_MOVE_MM          0.001

#define RETURN_OK                0
#define RETURN_CYL_ERROR         252
#define RETURN_ESTOP             254

#define POSDIR                   1
#define NEGDIR                   -1

#define MSG_MOTION_CARD          (WM_USER+100)
#define MSG_IO_CARD				 (WM_USER+101)


#ifndef UINT
#define UINT unsigned int
#endif


enum
{
	CONVEYOR_STOP,
	CONVEYOR_CW,
	CONVEYOR_CCW
};

class CMotionCard
{
public:
	CMotionCard();
	~CMotionCard();

	//纯虚函数，子类必须去实现这个东西

	LRESULT		   m_ErrCode;
	LONG		   m_DriverHandle;
	unsigned char  m_szErrorMsg[40];

	BOOL m_iInput[dwPortCount][dwPortBit];
	BOOL m_iOutput[dwPortCount][dwPortBit];

	USHORT m_mcInput[TOTAL_CARD_NUM];
	USHORT m_mcOutput[TOTAL_CARD_NUM];
	long lTargetPos;
	BOOL WriteLOUJ;

public:
	//初始化函数
	virtual UINT Init() = 0;
	//如果没找到任何卡，就调用这里显示none
	virtual std::string get_vendor() ;
	
	virtual BOOL WriteOutPutBit(short BitNo, short BitData) = 0;
	
	virtual void EStopMove(short axis) = 0;

	virtual void StartTMove(short axis, long Dist, long Vel, long MaxVel, double Tacc) = 0;

	virtual void StartTVMove(short axis, long strVel, long MaxVel, double Tacc) = 0;

	virtual int BackToOrigin(short axis, long strVel, long MaxVel, double Tacc) = 0;
	
	virtual long ReadPosition(short axis) = 0;

	virtual DWORD ReadOutPutBit(short BitNo) = 0;

	virtual DWORD ReadInPutBit(short BitNo) = 0;

	virtual UINT WaitSensorTimeOutPos(short ibit, DWORD dwSensorTime, DWORD dwOverTime = 1000) = 0;

	virtual bool WaitSensor(short Bits, DWORD TimeOut = 1000) = 0;

	virtual bool WaitSensorInv(short Bits, DWORD TimeOut = 1000) = 0;
	
	virtual UINT WaitSensorTimeOutNeg(short iPort, UINT iChanIN, DWORD dwSensorTime, DWORD dwOverTime = 1000) = 0;

	virtual UINT WaitMotorDoneTimeOut(short Axis, DWORD dwOverTime = 1000 ) = 0;

	virtual UINT StartOrigin() = 0;

	virtual bool CheckDone(short Aixs) = 0;

	virtual int GetCardQuantity() = 0;

	virtual void ConveyorSTOP() = 0;
	//传送带反转
	//override
	virtual void ConveyorCCW() = 0;
	//传送带正转
	//override
	virtual void ConveyorCW() = 0;
	//override
	virtual void board_close() = 0;

public:
	virtual void SetConveyorState(int state) { ConveyorState = state;};
	virtual int GetConveyorState() { return ConveyorState;}
	virtual void SetMotorState(int state) { MotorState = state; }
	virtual int GetMotorState() {return MotorState; }
private:
	int ConveyorState;
	int MotorState;
	BOOL m_bHomeStop;


	//motion card


	BOOL InitMotionCard(short iCardNum);
	BOOL ScanMotionCard(HWND hWnd, UINT iMsg);

	BOOL ResumeScanThread();
	BOOL SuspendScanThread();

	BOOL WaitMoveDone(short iAxis);

	BOOL  CheckEStop(DWORD dwOverTime = 0, short iCardID = 0, short iAxis = 0);

	long   UnitToPulse(short iAxis, const double dValue);
	double PulseToUnit(short iAxis, const long  dValue);







	CString GetErrorString();
	short   GetErrorID() { return m_nCardError; }














private:
	short m_nCardError;
	short m_nCardID;
	short m_nAxisID;
	long m_lTargetPos[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	long m_lCurrentPos[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	long m_lProfilePos[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	double m_dDefaultVel[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	double m_dDefaultAcc[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	double m_dDefaultJOGVel[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	double m_dDefaultJOGAcc[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	double m_dDefaultHomeVel[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	double m_dDefaultHomeAcc[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	double m_dScaleNumerator[MAX_AXIS_LEN];
	double m_dScaleDenominator[MAX_AXIS_LEN];
	bool m_bPosLimitLevel[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	bool m_bNegLimitLevel[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	bool m_bDrvAlarmLevel[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	bool m_bMotorHomeLevel[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	bool m_bMotorIndexLevel[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	bool m_bEStop[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	bool m_bStop[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	bool m_bMoveDone[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	CString m_strError;
	CEvent m_EventSkipScan;
	CEvent m_EventSkipScan1;
	CEvent m_EventEstop[TOTAL_CARD_NUM][MAX_AXIS_LEN];;
	CEvent m_EventMoveDone[TOTAL_CARD_NUM][MAX_AXIS_LEN];
	CCriticalSection m_CriticalCard;
	CCriticalSection m_CriticalIOCard;

};




#endif