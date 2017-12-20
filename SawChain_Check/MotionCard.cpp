// MotionCard.cpp : 实现文件
//

#include "stdafx.h"
#include "SawChain_Check.h"
#include "MotionCard.h"


// CMotionCard

CMotionCard::CMotionCard()
{
	MotorState = STOPING;
}

CMotionCard::~CMotionCard()
{
}


// CMotionCard 成员函数
std::string CMotionCard::get_vendor()
{
	return "none";
}
