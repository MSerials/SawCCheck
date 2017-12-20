#include "globle.h"
#include "stdafx.h"






int g_UpTippedPos = -66;
//底部拱起检测
int g_BtTippedPos = -72;
//顶部相机位置
int g_UpCameraPos = 0;
//底部打机位置
int g_BtDaJiPos = 3;
//顶部打机位置
int g_UpDaJiPos = 3;
//顶部双刀粒位置
int g_DoubleKnifePos = 5;
//底部双刀粒位置
int g_DoubleKnifePos1 = -4;
//底部相机位置
int g_BtCameraPos = 8;
//Mark1气缸位置  
int g_Mark1CylinderPos = 11;
//Mark2气缸位置
int g_Mark2CylinderPos = 16;
//Mark位置
int g_MarkPos = 33;
//桌面死结感应器
int g_ThirdDiedKnodePos = -21;// = -21;

int g_RailLenght = 49;
//触发拍照感应器
int	IN_Start_Camera_SENSOR = 1;
//打断检测感应器
int	IN_CHECK_BREAK = 3;
//预先筛选向上打击和拱起来的
int	IN_Check_UP_TIPPEDUP = 6;
//吸扣气缸上限感应器
int	IN_CYL_Magnet_SENSOR = 7;
//预先筛选向上打击和拱起来的
int	IN_Check_BT_TIPPEDUP = 8;
//启动按钮
int	IN_START_BTN = 16;
//停止按钮
int	IN_BTN_STOP = 17;
//底部双刀粒感应器
int	IN_Check_Double_Sword2 = 18;
//Mark3气缸上限
int	IN_CYL_Mark3_UP_SENSOR = 19;
//死结感应器，进
int	IN_CHECK_SENSOR = 25;
//桌面死结感应器
int	IN_DIED_KNOED_SENSOR = 25;
//顶部双刀粒感应器
int	IN_Check_Double_Sword1 = 21;
//Mark1气缸感应器
int	IN_CYL_Mark1_UP_SENSOR = 22;
//接料按钮或者脚踏开关
int	IN_Foot_Switch = 23;
//Mark2气缸上限感应器
int	IN_CYL_Mark2_UP_SENSOR = 24;
//死结感应器，出
int	IN_CHECK_SENSOR1 = 20;
//上压气缸上限感应器
int	IN_CYL_Press_UP_SENSOR = 26;
//急停按钮
int	IN_ESTOP_BTN = 27;
//顶部打机感应器
int	IN_Check_UP_DaJi = 28;
//底部打机感应器
int	IN_Check_BT_DaJi = 29;
//推链气缸上限感应器
int IN_CYL_Push_UP_SENSOR = 30;



//消息传递时候用的
HWND TopCameraDlg = NULL;
HWND BottomCameraDlg = NULL;
HWND MainControlDlg = NULL;
//相机临界区
//CRITICAL_SECTION g_top_cs;
//CRITICAL_SECTION g_bottom_cs;

std::mutex g_top_lk;
std::mutex g_bottom_lk;
std::mutex g_capture_lk;

void CPPExpDefaultExceptionHandler(const Halcon::HException& except)
{
	throw except;
}
