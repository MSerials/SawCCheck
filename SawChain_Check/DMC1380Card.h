
#if !defined(AFX_DMC1380_)
#define AFX_DMC1380_
#pragma once

#include "MotionCard.h"

class DMC1380Card : CMotionCard
{
public:
	DMC1380Card();
	~DMC1380Card();

	//override
	UINT Init();
	//override
	std::string get_vendor();
	//override
	BOOL WriteOutPutBit(short BitNo, short BitData);
	//override
	void EStopMove(short axis);
	//override
	void StartTMove(short axis, long Dist, long Vel, long MaxVel, double Tacc);
	//override
	void StartTVMove(short axis, long strVel, long MaxVel, double Tacc);
	int BackToOrigin(short axis, long strVel, long MaxVel, double Tacc);
	//override
	inline long ReadPosition(short axis);
	//override
	inline DWORD ReadOutPutBit(short BitNo);
	//override
	inline DWORD ReadInPutBit(short BitNo);

	bool WaitSensor(short Bits, DWORD TimeOut = 1000);

	bool WaitSensorInv(short Bits, DWORD TimeOut = 1000);

	//override
	UINT WaitSensorTimeOutPos(short ibit, DWORD dwSensorTime, DWORD dwOverTime = 1000);
	//override
	UINT WaitSensorTimeOutNeg(short iPort, UINT iChanIN, DWORD dwSensorTime, DWORD dwOverTime = 1000);
	//override
	UINT WaitMotorDoneTimeOut(short Axis, DWORD dwOverTime = 1000);
	//override
	UINT StartOrigin();

	bool CheckDone(short Aixs);
	//传送带停止
	//override
	void ConveyorSTOP();
	//传送带反转
	//override
	void ConveyorCCW();
	//传送带正转
	//override
	void ConveyorCW();

	void board_close();

	int GetCardQuantity() { return m_card_quantity; }
private:
	int m_card_quantity;

};


#endif
