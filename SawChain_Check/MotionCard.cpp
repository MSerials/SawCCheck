// MotionCard.cpp : ʵ���ļ�
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


// CMotionCard ��Ա����
std::string CMotionCard::get_vendor()
{
	return "none";
}
