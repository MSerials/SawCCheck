#pragma once



#include "MotionCard.h"
#include "DMC1380Card.h"
#include <vector>
#include <mutex>
#include <atomic>

// SawChainMachine 命令目标
//这个机器的类，包含了动作，相机等等

#define g_MAX_CHAIN 64


enum
{
	STOP,PAUSE,START,SYS_STATE
};

class SawChainMachine : public CObject
{
public:
	SawChainMachine();
	virtual ~SawChainMachine();

	int Init();

	int InitCard();
	int InitCamera();
	//相机静态抓取和动态抓取

	int get_id_by_position(int counter, int position, int max_node);

	//检测字符,使用hog+svm
	//float check_charater();//input parameter and srouce
	//float check_charater_train();
	//float check_charater_predict();

	//检测连接片装反没有
	int check_inverse(const Halcon::Hobject&src, Halcon::Hobject ROI, double thresholdvar, double minarea, double maxarea, Halcon::HTuple& disp_hand, double *areares);

	//检测刀片磨了没有
	int check_knife(const Halcon::Hobject&src,
		Halcon::HTuple& disp_hand, 
		double r1, double c1, double r2, double c2,
		double MinLen, double MaxLen);
	//selection = 0是检测， selection = 1是创建
	int check_char(const Halcon::Hobject & src, Halcon::HTuple & disp_hand,double r1, double c1, double r2, double c2,std::vector<CString> fileName, double accuracy, int selection = 0);
	int check_bottom_char(const Halcon::Hobject & src, Halcon::HTuple & disp_hand, double r1, double c1, double r2, double c2, std::vector<CString> fileName, double accuracy, int selection = 0);
	int check_daji(const Halcon::Hobject&src, Halcon::HTuple& disp_hand, double r1, double c1, double r2, double c2);

	//
	//const Halcon::Hobject&src,Halcon::Hobject ROI, Halcon::HTuple& disp_hd,

	//action
	static UINT system_sensor(LPVOID lp);
	//int procedure();
	static UINT system_procedure(LPVOID lp);
	bool Present_Error_Infomation(int code);
	bool isErrorInfo;
	static UINT Error_Infomation_Thread(LPVOID lp);
	CString ErrorInfo;
	int system_start();
	int system_pause();
	int system_stop();
	int system_reset();
	//int get_system_state();

	//void Conveyor_running(int ChainNo);
	void Conveyor_running(int ChainNo); 
	UINT Procedure();
	static UINT TopCameraProcedure(LPVOID lp);
	CWinThread *pTopCamera; 
	static UINT BottomCameraProcedure(LPVOID lp);
	bool StartCamera_Thread();
	CWinThread *pBottomCamera;

	int push_button(int sel);

	bool StartCamera();
	void ScanAllSensor();
	bool CheckAllSensorState();
	void PushAllCylinderBack();
	void Break_chain_action();
	void DiedKnode_detection();
	bool DoubleKnifeSensor();
	bool BtDoubleKnifeSensor();
	bool UpDoubleKnifeSensor();
	bool UpDajiSensor();
	bool BtDajiSensor();
	bool DiedKnode2();
	void MarkAction();
	void Chain_Detection();
	bool isTopKnife();
	bool isBottomKnife();
	void ShowAlertInfo();

	int get_counter() { return m_counter; }
	int get_card_index() { return stack_index; }
	virtual CMotionCard * CurrentMotionCard();
	std::vector<CMotionCard*> mc_vector;
protected:
	DWORD m_TopDoubleKnifeSensor;
	DWORD m_BottomDoubleKnifeSensor;
	DWORD m_TopDaJiSensor;
	DWORD m_BottomDaJiSensor;
	DWORD m_DiedKnodeSensor;
	DWORD m_TopCameraResult; 
	DWORD m_BottomCameraResult;
	BOOL m_DiedKnodedRes;//结果的
	BOOL m_DiedKnodedState;//状态的

	//CMotionCard * mc;

	CString AlertInfo;
	CString AlertInfo1;
protected:
	
	std::atomic<bool> isTopDetOver;
	std::atomic<bool> isBottomDetOver;
	std::atomic<bool> isTopProc;
	std::atomic<bool> isBottomProc;
	std::atomic<bool> isPausePressed;
	std::atomic<int> m_max_knode;//这个数值等于链条长度乘以gMAX_CHAIN
private:
	//用于弹出对话框的锁
	std::mutex m_info_mtx;
	//锁住变量，防止多线程访问错误
	std::atomic<int> m_system_state = 0;
	//触发基数
	std::atomic<int> m_trigger_counter = 0;
	//检测计数
	std::atomic<int> m_counter = 0;
	std::atomic<int> m_ng_counter = 0;
	std::atomic<int> m_conveyorcounter = 0;
	//int ChainOrder;
	std::atomic<int> stack_index = 0;

	std::atomic<int>  memorise_conveyor_state = 0;

public:
	
	DMC1380Card * dmc1380;

	class Controller //控制信息
	{
	public:
		Controller() {};
		~Controller() {};
	};

	struct KNODE
	{
		int TopError; //存储连接片错误类型
		int BottomError;

		int TopKnife;  //为了触发相机检测刀口未磨
		int BottomKnife;

		int kind; //存储连接片是刀片还是传动片类型
	}*m_knode;
};


