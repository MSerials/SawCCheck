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

//����û�д��
#define UNBREAK				1
//����û�е�λ
#define	CYLNOTPOSITION		(1<<1)
//����������ִ��
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
	IMAGEOK = 0,		//ͼ������
	INV_KNODE = 1,			//����Ƭװ��
	KNIFE = 2,				//��Ƭû��ĥ������ʲô��
	DOUBLEKNIFE = 4,		//˫����
	UNBOLT = 8,				//δí
	MIXCHAR = 16,			//���ַ�
	TDAJI = 32,				//�ϴ����Ӧ��
	BDAJI = 64,				//�ײ������Ӧ��
	DAJI	=	128,		//ͼ����
	DIEDKNODE = 256
//	IMAGEABNORMAL = 512,		
//	IMAGENOTEXIST = 1024,
//	RECORDERROR = 2048
};






//�Һ����������IO�ڶ������Ϊ,��ñ�����һ���������ã��������


extern int g_RailLenght;







//��ƬΪ4��һѭ��
//const short Period                      = 4;
//����������
extern int g_UpTippedPos ;
//�ײ�������
extern int g_BtTippedPos ;
//�������λ��
extern int g_UpCameraPos;
//�ײ����λ��
extern int g_BtDaJiPos ;
//�������λ��
extern int g_UpDaJiPos ;
//����˫����λ��
extern int g_DoubleKnifePos ;
//�ײ�˫����λ��
extern int g_DoubleKnifePos1 ;
//�ײ����λ��
extern int g_BtCameraPos;
//Mark1����λ��  
extern int g_Mark1CylinderPos ;
//Mark2����λ��
extern int g_Mark2CylinderPos ;
//Markλ��
extern int g_MarkPos ;
//���������Ӧ��
extern int g_ThirdDiedKnodePos ;// = -21;


#if 0
//�����Ӧ����λ��
const int g_FirstDiedKnodePos = 20;
//�����Ӧ����λ��
const int g_SecondDiedKnodePos = 21;
#endif



//�������ո�Ӧ��
extern int	IN_Start_Camera_SENSOR;
//��ϼ���Ӧ��
extern int	IN_CHECK_BREAK;
//Ԥ��ɸѡ���ϴ���͹�������
extern int	IN_Check_UP_TIPPEDUP;
//�����������޸�Ӧ��
extern int	IN_CYL_Magnet_SENSOR;
//Ԥ��ɸѡ���ϴ���͹�������
extern int	IN_Check_BT_TIPPEDUP;
//������ť
extern int	IN_START_BTN;
//ֹͣ��ť
extern int	IN_BTN_STOP;
//�ײ�˫������Ӧ��
extern int	IN_Check_Double_Sword2;
//Mark3��������
extern int	IN_CYL_Mark3_UP_SENSOR;
//�����Ӧ������
extern int	IN_CHECK_SENSOR;
//���������Ӧ��
extern int	IN_DIED_KNOED_SENSOR;
//����˫������Ӧ��
extern int	IN_Check_Double_Sword1;
//Mark1���׸�Ӧ��
extern int	IN_CYL_Mark1_UP_SENSOR;
//���ϰ�ť���߽�̤����
extern int	IN_Foot_Switch;
//Mark2�������޸�Ӧ��
extern int	IN_CYL_Mark2_UP_SENSOR;
//�����Ӧ������
extern int	IN_CHECK_SENSOR1;
//��ѹ�������޸�Ӧ��
extern int	IN_CYL_Press_UP_SENSOR;
//��ͣ��ť
extern int	IN_ESTOP_BTN;
//���������Ӧ��
extern int	IN_Check_UP_DaJi;
//�ײ������Ӧ��
extern int	IN_Check_BT_DaJi;
//�����������޸�Ӧ��
extern int IN_CYL_Push_UP_SENSOR;





	
//������ť
#define OUT_LAMP_START_BTN					9
//ֹͣ��ť
#define OUT_LAMP_STOP_BTN					10
//�����
#define OUT_Magnet							11
//�������
#define OUT_LAMP_RED_TOWER					12
//#define OUT_LAMP_GREEN_TOWER				13
//�����ϵ���ɫ��������ť��
#define OUT_JOINT_INDICATOR					13
//���ʹ���ת�̵���
#define OUT_ConveyerCW						14
//���ʹ���ת�̵���
#define OUT_ConveyerCCW						15
//���̵���
#define OUT_CYL_MARK						16

//#define OUT_CYL_Mark2						17
//ѹ������
#define OUT_CYL_Press						18
//��������
#define OUT_CYL_MAGNET						19
//��������
#define OUT_CYL_Push						20

//#define OUT_CYL_METER						21
//�ŷ�ʹ��
#define	OUT_SV_ON							22

//#define OUT_CYL_Mark3						24

//#region global variable use for function autorun
#define uchar unsigned char





extern void CPPExpDefaultExceptionHandler(const Halcon::HException& except);

//���ڿ���������Ϣ����
extern HWND TopCameraDlg;
extern HWND BottomCameraDlg;
extern HWND MainControlDlg;

//��������Ļ���������ö���̳߳�ͻ
extern std::mutex g_top_lk;
extern std::mutex g_bottom_lk;
extern std::mutex g_capture_lk;

//ȫ��ϵͳ��������������ϵͳ�Ŀ��Ʊ���,���õ���ģʽ
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
	//����Ʒ��������Ŀ
	int ng_chain;

	//��ͣ��ť
	CEvent evt_EStop;
	//ֹͣɨ��
	bool isStopScan;
	bool isBreakChain;
	//����з��ֵĴ���ʹ�û��������ܱ������������⵽����û�е�
	int runtime_error;
	//CEvent evt_Trigger;
	bool bTrigger;
	CEvent evt_TopCamDetect;
	CEvent evt_BottomCamDetect;
	//�������
	bool is_top_grab;
	bool is_bottom_grab;
	CEvent evt_top_grab;
	CEvent evt_bottom_grab;


	CEvent evt_start_top_camera;
	CEvent evt_start_bottom_camera;
	//ϵͳ�˶�״̬
	//CEvent evt_sys_process;//
	CEvent evt_process;
	CEvent evt_trigger;
	int system_error;
	int rect_error;

	CString RectInfo(int code)
	{

		switch (code)
		{
		case TINVRECT:	return L"�뻭��������Ƭ��������";
		case BINVRECT: return L"�뻭�ײ�����Ƭ��������";
		case TCHARRECT: return L"�뻭��������Ƭ�ַ�����";
		case BCHARRECT: return L"�뻭�ײ�����Ƭ�ַ�����";
		case TKNIFERECT: return L"�뻭��������Ƭ��Ƭ����";
		case BKNIFERECT:return L"�뻭��������Ƭ��Ƭ����";
		case TUNBOLT:return L"�뻭����������Կ�";
		case BUNBOLT:return L"�뻭�ײ�������Կ�";
		default :
			return L"ѡ���δ֪����";
		}
	}

	CString ErrorInfo(int code)
	{
		CString str;
		str.Format(_T("�������:%d"), code);
		if (NOCARD == (NOCARD&code)) { str += L"û�ҵ����ƿ� "; }
		if (NOCAMERA == (NOCAMERA&code)) { str += L"û���ҵ���� "; }
		if (NOPRESSURE == (NOPRESSURE&code)) { str += L"��ѹ���ܲ��� "; }
		if (NEEDORIGIN == (NEEDORIGIN &code)) { str += L"��Ҫ��λ "; }
		if (TOPCAMERANOTALREADY == (TOPCAMERANOTALREADY&code)) { str += L"�������û׼���� "; }
		if (BOTTOMCAMERANOTALREADY == (BOTTOMCAMERANOTALREADY&code)) { str += L"�ײ����û׼���� "; }
		if (TIME_OUT == (TIME_OUT&code)) { str +=L"��ʱ "; }
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