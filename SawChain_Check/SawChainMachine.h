#pragma once



#include "MotionCard.h"
#include "DMC1380Card.h"
#include <vector>
#include <mutex>
#include <atomic>

// SawChainMachine ����Ŀ��
//����������࣬�����˶���������ȵ�

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
	//�����̬ץȡ�Ͷ�̬ץȡ

	int get_id_by_position(int counter, int position, int max_node);

	//����ַ�,ʹ��hog+svm
	//float check_charater();//input parameter and srouce
	//float check_charater_train();
	//float check_charater_predict();

	//�������Ƭװ��û��
	int check_inverse(const Halcon::Hobject&src, Halcon::Hobject ROI, double thresholdvar, double minarea, double maxarea, Halcon::HTuple& disp_hand, double *areares);

	//��⵶Ƭĥ��û��
	int check_knife(const Halcon::Hobject&src,
		Halcon::HTuple& disp_hand, 
		double r1, double c1, double r2, double c2,
		double MinLen, double MaxLen);
	//selection = 0�Ǽ�⣬ selection = 1�Ǵ���
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
	BOOL m_DiedKnodedRes;//�����
	BOOL m_DiedKnodedState;//״̬��

	//CMotionCard * mc;

	CString AlertInfo;
	CString AlertInfo1;
protected:
	
	std::atomic<bool> isTopDetOver;
	std::atomic<bool> isBottomDetOver;
	std::atomic<bool> isTopProc;
	std::atomic<bool> isBottomProc;
	std::atomic<bool> isPausePressed;
	std::atomic<int> m_max_knode;//�����ֵ�����������ȳ���gMAX_CHAIN
private:
	//���ڵ����Ի������
	std::mutex m_info_mtx;
	//��ס��������ֹ���̷߳��ʴ���
	std::atomic<int> m_system_state = 0;
	//��������
	std::atomic<int> m_trigger_counter = 0;
	//������
	std::atomic<int> m_counter = 0;
	std::atomic<int> m_ng_counter = 0;
	std::atomic<int> m_conveyorcounter = 0;
	//int ChainOrder;
	std::atomic<int> stack_index = 0;

	std::atomic<int>  memorise_conveyor_state = 0;

public:
	
	DMC1380Card * dmc1380;

	class Controller //������Ϣ
	{
	public:
		Controller() {};
		~Controller() {};
	};

	struct KNODE
	{
		int TopError; //�洢����Ƭ��������
		int BottomError;

		int TopKnife;  //Ϊ�˴��������⵶��δĥ
		int BottomKnife;

		int kind; //�洢����Ƭ�ǵ�Ƭ���Ǵ���Ƭ����
	}*m_knode;
};


