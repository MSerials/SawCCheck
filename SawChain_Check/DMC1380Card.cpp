#include "stdafx.h"
#include "DMC1380Card.h"
#include "third_party\DMC1380\Dmc1380.h"

#ifdef _WIN64
#pragma comment(lib,"third_party/DMC1380/x64/Dmc1380.lib")
#else
#pragma comment(lib,"third_party/DMC1380/x86/Dmc1380.lib")
#endif

DMC1380Card::DMC1380Card()
	:m_card_quantity(0)
{
}


DMC1380Card::~DMC1380Card()
{

}

UINT DMC1380Card::Init()
{
	if (0 == (m_card_quantity = d1000_board_init())) return NOCARD;
	d1000_set_pls_outmode(0, 0);
	d1000_in_enable(0,3);
	//WriteOutPutBit(OUT_SV_ON, 0);
	ConveyorSTOP();
	if(!ReadInPutBit(IN_ESTOP_BTN)) AfxMessageBox(L"急停按钮按下!");
	return NoError;
}

std::string DMC1380Card::get_vendor()
{
	return "dmc1380";
}

BOOL DMC1380Card::WriteOutPutBit(short BitNo, short BitData)
{
	return (!d1000_out_bit(BitNo, BitData));
}

void DMC1380Card::EStopMove(short axis)
{
	SetMotorState(STOPING);
	d1000_immediate_stop(axis);
}

void DMC1380Card::StartTMove(short axis, long Dist, long Vel, long MaxVel, double Tacc)
{
	SetMotorState(RUNNING);
	d1000_start_t_move(axis, Dist, Vel, MaxVel, Tacc);
}

void DMC1380Card::StartTVMove(short axis, long strVel, long MaxVel, double Tacc)
{
	SetMotorState(RUNNING);
	d1000_start_tv_move(axis, strVel,MaxVel,Tacc);

}

int DMC1380Card::BackToOrigin(short axis, long strVel, long MaxVel, double Tacc)
{
#ifdef _TEST
	printf_s("已经开始启动 Max %d  Tacc %f\n",MaxVel, Tacc);
#endif
	DWORD newbit = ReadInPutBit(IN_Start_Camera_SENSOR);
	DWORD oldbit = newbit;
	DWORD tick = GetTickCount();
	StartTVMove(0, 500, MaxVel, Tacc);
	for (;;)
	{
		if ((GetTickCount() - tick) > 1500)
		{
			EStopMove(0);
			AfxMessageBox(L"运动超时");
			return 1;
		}

		if (WAIT_OBJECT_0 == ::WaitForSingleObject(system_control::GetIns()->evt_EStop, 0))
		{
			EStopMove(0);
			AfxMessageBox(L"急停按钮按下");
			return 2;
		}

		newbit = ReadInPutBit(IN_Start_Camera_SENSOR);

		if (newbit != oldbit && newbit)
		{
			//system_control::GetIns()->system_error |= NEEDORIGIN;
			EStopMove(0);
			//system_control::GetIns()->system_error &= ~NEEDORIGIN;
			return 0;
		}
		oldbit = newbit;
	}
}

long DMC1380Card::ReadPosition(short axis)
{
	return d1000_get_command_pos(axis);
}

DWORD DMC1380Card::ReadOutPutBit(short BitNo)
{
	return d1000_get_outbit(BitNo);
}

DWORD DMC1380Card::ReadInPutBit(short BitNo)
{
	return (!d1000_in_bit(BitNo));
}

bool DMC1380Card::WaitSensor(short Bits, DWORD TimeOut)
{
	DWORD tk = GetTickCount();
	for (; d1000_in_bit(Bits);)		
	{
		Sleep(1);
		if ((GetTickCount() - tk) > TimeOut)
			return false;
	}
	return true;
}

bool DMC1380Card::WaitSensorInv(short Bits, DWORD TimeOut)
{
	DWORD tk = GetTickCount();
	for (; !d1000_in_bit(Bits);)		//高电平状态
	{
		Sleep(1);
		if ((GetTickCount() - tk) > TimeOut)
			return false;
	}
	return true;
}

UINT DMC1380Card::WaitSensorTimeOutPos(short ibit, DWORD dwSensorTime, DWORD dwOverTime)
{
	return 0;
}

UINT DMC1380Card::WaitSensorTimeOutNeg(short iPort, UINT iChanIN, DWORD dwSensorTime, DWORD dwOverTime)
{
	return 0;
}

UINT DMC1380Card::WaitMotorDoneTimeOut(short Axis, DWORD dwOverTime)
{
	DWORD tk = GetTickCount();
	for (; !d1000_check_done(Axis);)		//高电平状态
	{
		
		Sleep(1);
		if ((GetTickCount() - tk) > dwOverTime)
			return false;
	}
	return true;
}

UINT DMC1380Card::StartOrigin()
{
	return 0;
	
}

bool DMC1380Card::CheckDone(short Aixs)
{
	bool res = !d1000_check_done(Aixs);
	return !res;
}

void DMC1380Card::ConveyorSTOP()
{
	LOOP d1000_out_bit(OUT_ConveyerCCW, 1);
	LOOP d1000_out_bit(OUT_ConveyerCW, 1);
	SetConveyorState(CONVEYOR_STOP);		
}

void DMC1380Card::ConveyorCCW()
{
	LOOP d1000_out_bit(OUT_ConveyerCCW, 0);
	LOOP d1000_out_bit(OUT_ConveyerCW, 1);
	SetConveyorState(CONVEYOR_CCW);
}

void DMC1380Card::ConveyorCW()
{
	LOOP d1000_out_bit(OUT_ConveyerCW, 0);
	LOOP d1000_out_bit(OUT_ConveyerCCW, 1);
	SetConveyorState(CONVEYOR_CW);
}

void DMC1380Card::board_close()
{
	ConveyorSTOP();
	EStopMove(0);
	WriteOutPutBit(OUT_SV_ON, 1);
	Sleep(100);
	d1000_board_close();
}
