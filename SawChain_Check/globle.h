#ifndef __GOLBAL__
#define __GOLBAL__


#include "Lock.h"



#include <mutex>

#define _HALCON
#ifdef _HALCON
//#include "HVDevice.h"
#include "HalconCpp.h"
#ifdef _TEST
#include <iostream>
#include <vector>
using namespace std;
#endif

#endif




#ifdef _WIN64
#pragma comment(lib,"third_party/lib/halcon/x64/halconcpp.lib")

#pragma comment(lib,"third_party/basler/lib/x64/PylonC_MD_VC120.lib")
#else
#pragma comment(lib,"third_party\\basler\\lib\\Win32\\PylonC_MD_VC120.lib")

#pragma comment(lib,"third_party\\lib\\halcon\\x86\\halconcpp.lib")
#endif



#define	WM_MESSAGE_COUNTER			(WM_USER+1010)



#ifndef sccErrorCode
#define sccErrorCode	int
#endif // !ErrorCode

#ifndef NoError	
#define NoError		0
#endif // NoError	

#define NoActivateCamera				0
#define NOCARD							1
#define NOCAMERA					(1<<1)
#define NOPRESSURE					(1<<2)
#define TOPCAMERANOTALREADY			(1<<3)
#define BOTTOMCAMERANOTALREADY		(1<<4)
#define NEEDORIGIN					(1<<5)
#define TIME_OUT					(1<<6)

#define MAX_COUNTER						128

//链条没有打断
#define UNBREAK				1
//气缸没有到位
#define	CYLNOTPOSITION		(1<<1)
//不允许往下执行
#define RUNFORBIDDEN		(1<<2)
//



enum
{
	NORECT,TINVRECT,BINVRECT,TCHARRECT,BCHARRECT,TKNIFERECT,BKNIFERECT,TUNBOLT,BUNBOLT
};

enum
{
	STOPING = 0, RUNNING = 1
};

enum
{
	IMAGEOK = 0,		//图像正常
	INV_KNODE = 1,			//连接片装反
	KNIFE = 2,				//刀片没有磨过或者什么的
	DOUBLEKNIFE = 4,		//双刀粒
	UNBOLT = 8,				//未铆
	MIXCHAR = 16,			//混字符
	TDAJI = 32,				//上打击感应器
	BDAJI = 64,				//底部打击感应器
	DAJI	=	128,		//图像打击
	DIEDKNODE = 256
//	IMAGEABNORMAL = 512,		
//	IMAGENOTEXIST = 1024,
//	RECORDERROR = 2048
};






//我很讨厌随意改IO口定义的行为,搞得必须做一个变量配置，操尼玛的


extern int g_RailLenght;







//刀片为4个一循环
//const short Period                      = 4;
//顶部拱起检测
extern int g_UpTippedPos ;
//底部拱起检测
extern int g_BtTippedPos ;
//顶部相机位置
extern int g_UpCameraPos;
//底部打机位置
extern int g_BtDaJiPos ;
//顶部打机位置
extern int g_UpDaJiPos ;
//顶部双刀粒位置
extern int g_DoubleKnifePos ;
//底部双刀粒位置
extern int g_DoubleKnifePos1 ;
//底部相机位置
extern int g_BtCameraPos;
//Mark1气缸位置  
extern int g_Mark1CylinderPos ;
//Mark2气缸位置
extern int g_Mark2CylinderPos ;
//Mark位置
extern int g_MarkPos ;
//桌面死结感应器
extern int g_ThirdDiedKnodePos ;// = -21;


#if 0
//死结感应器进位置
const int g_FirstDiedKnodePos = 20;
//死结感应器出位置
const int g_SecondDiedKnodePos = 21;
#endif



//触发拍照感应器
extern int	IN_Start_Camera_SENSOR;
//打断检测感应器
extern int	IN_CHECK_BREAK;
//预先筛选向上打击和拱起来的
extern int	IN_Check_UP_TIPPEDUP;
//吸扣气缸上限感应器
extern int	IN_CYL_Magnet_SENSOR;
//预先筛选向上打击和拱起来的
extern int	IN_Check_BT_TIPPEDUP;
//启动按钮
extern int	IN_START_BTN;
//停止按钮
extern int	IN_BTN_STOP;
//底部双刀粒感应器
extern int	IN_Check_Double_Sword2;
//Mark3气缸上限
extern int	IN_CYL_Mark3_UP_SENSOR;
//死结感应器，进
extern int	IN_CHECK_SENSOR;
//桌面死结感应器
extern int	IN_DIED_KNOED_SENSOR;
//顶部双刀粒感应器
extern int	IN_Check_Double_Sword1;
//Mark1气缸感应器
extern int	IN_CYL_Mark1_UP_SENSOR;
//接料按钮或者脚踏开关
extern int	IN_Foot_Switch;
//Mark2气缸上限感应器
extern int	IN_CYL_Mark2_UP_SENSOR;
//死结感应器，出
extern int	IN_CHECK_SENSOR1;
//上压气缸上限感应器
extern int	IN_CYL_Press_UP_SENSOR;
//急停按钮
extern int	IN_ESTOP_BTN;
//顶部打机感应器
extern int	IN_Check_UP_DaJi;
//底部打机感应器
extern int	IN_Check_BT_DaJi;
//推链气缸上限感应器
extern int IN_CYL_Push_UP_SENSOR;





	
//启动按钮
#define OUT_LAMP_START_BTN					9
//停止按钮
#define OUT_LAMP_STOP_BTN					10
//电磁铁
#define OUT_Magnet							11
//报警红灯
#define OUT_LAMP_RED_TOWER					12
//#define OUT_LAMP_GREEN_TOWER				13
//桌面上的绿色的启动按钮灯
#define OUT_JOINT_INDICATOR					13
//输送带正转继电器
#define OUT_ConveyerCW						14
//输送带反转继电器
#define OUT_ConveyerCCW						15
//打标继电器
#define OUT_CYL_MARK						16

//#define OUT_CYL_Mark2						17
//压紧气缸
#define OUT_CYL_Press						18
//吸扣气缸
#define OUT_CYL_MAGNET						19
//推料气缸
#define OUT_CYL_Push						20

//#define OUT_CYL_METER						21
//伺服使能
#define	OUT_SV_ON							22

//#define OUT_CYL_Mark3						24

//#region global variable use for function autorun
#define uchar unsigned char





extern void CPPExpDefaultExceptionHandler(const Halcon::HException& except);

//用于控制面板的消息传递
extern HWND TopCameraDlg;
extern HWND BottomCameraDlg;
extern HWND MainControlDlg;

//用于相机的互斥量，免得多个线程冲突
extern std::mutex g_top_lk;
extern std::mutex g_bottom_lk;
extern std::mutex g_capture_lk;

//全局系统变量，用于整个系统的控制变量,采用单例模式
class system_control
{
private:
	system_control()
		:evt_EStop(FALSE, TRUE)
		, evt_top_grab(FALSE, TRUE)
		, evt_bottom_grab(FALSE, TRUE)
		//, evt_Trigger(FALSE,TRUE)
		, bTrigger(false)
		, evt_TopCamDetect(FALSE, TRUE)
		, evt_BottomCamDetect(FALSE, TRUE)
		, evt_start_top_camera(FALSE, TRUE)
		, evt_start_bottom_camera(FALSE,TRUE)
		, evt_process(FALSE,TRUE)
		, evt_trigger(FALSE,TRUE)
		, system_error(0)
		,rect_error(0)
	{
		system_error |= (TOPCAMERANOTALREADY | BOTTOMCAMERANOTALREADY | NEEDORIGIN);
		is_top_grab = false;
		is_bottom_grab = false;
		isStopScan = false;
		isBreakChain = true;
		runtime_error = 0;
		system_control::GetIns()->evt_start_top_camera.ResetEvent();
		system_control::GetIns()->evt_start_bottom_camera.ResetEvent();
		tinv = tchar= tknife = binv = bchar= bknife= diedknode=doubleknife=tdaji = bdaji = 0;
		ng_chain = 0;
	};
	
public:
	~system_control() {};
	static system_control* GetIns() { static system_control m_sc; return &m_sc; }

	int tinv;
	int tchar;
	int tknife;
	int binv;
	int bchar;
	int bknife;
	int diedknode;
	int doubleknife;
	int tdaji;
	int bdaji;
	//不良品的链条数目
	int ng_chain;

	//急停按钮
	CEvent evt_EStop;
	//停止扫描
	bool isStopScan;
	bool isBreakChain;
	//检测中发现的错误，使得机器不可能被开启，比如检测到刀粒没有等
	int runtime_error;
	//CEvent evt_Trigger;
	bool bTrigger;
	CEvent evt_TopCamDetect;
	CEvent evt_BottomCamDetect;
	//相机拍摄
	bool is_top_grab;
	bool is_bottom_grab;
	CEvent evt_top_grab;
	CEvent evt_bottom_grab;


	CEvent evt_start_top_camera;
	CEvent evt_start_bottom_camera;
	//系统运动状态
	//CEvent evt_sys_process;//
	CEvent evt_process;
	CEvent evt_trigger;
	int system_error;
	int rect_error;

	CString RectInfo(int code)
	{

		switch (code)
		{
		case TINVRECT:	return L"请画顶部连接片正反检测框";
		case BINVRECT: return L"请画底部连接片正反检测框";
		case TCHARRECT: return L"请画顶部连接片字符检测框";
		case BCHARRECT: return L"请画底部连接片字符检测框";
		case TKNIFERECT: return L"请画顶部连接片刀片检测框";
		case BKNIFERECT:return L"请画顶部连接片刀片检测框";
		case TUNBOLT:return L"请画顶部打机测试框";
		case BUNBOLT:return L"请画底部打机测试框";
		default :
			return L"选择框未知错误";
		}
	}

	CString ErrorInfo(int code)
	{
		CString str;
		str.Format(_T("错误代码:%d"), code);
		if (NOCARD == (NOCARD&code)) { str += L"没找到控制卡 "; }
		if (NOCAMERA == (NOCAMERA&code)) { str += L"没有找到相机 "; }
		if (NOPRESSURE == (NOPRESSURE&code)) { str += L"气压可能不够 "; }
		if (NEEDORIGIN == (NEEDORIGIN &code)) { str += L"需要复位 "; }
		if (TOPCAMERANOTALREADY == (TOPCAMERANOTALREADY&code)) { str += L"顶部相机没准备好 "; }
		if (BOTTOMCAMERANOTALREADY == (BOTTOMCAMERANOTALREADY&code)) { str += L"底部相机没准备好 "; }
		if (TIME_OUT == (TIME_OUT&code)) { str +=L"超时 "; }
		return str;
	}
};





//#define _TEST


#ifdef _TEST 
#define nGiveError Halcon::set_check("~give_error")
#define GiveError  Halcon::set_check("give_error")
#else
#define nGiveError Halcon::set_check("give_error")
#define GiveError  Halcon::set_check("~give_error")
#endif



#endif

#define LOOP for(size_t i=0; i<128;i++)