#include "globle.h"
#include "stdafx.h"






int g_UpTippedPos = -66;
//�ײ�������
int g_BtTippedPos = -72;
//�������λ��
int g_UpCameraPos = 0;
//�ײ����λ��
int g_BtDaJiPos = 3;
//�������λ��
int g_UpDaJiPos = 3;
//����˫����λ��
int g_DoubleKnifePos = 5;
//�ײ�˫����λ��
int g_DoubleKnifePos1 = -4;
//�ײ����λ��
int g_BtCameraPos = 8;
//Mark1����λ��  
int g_Mark1CylinderPos = 11;
//Mark2����λ��
int g_Mark2CylinderPos = 16;
//Markλ��
int g_MarkPos = 33;
//���������Ӧ��
int g_ThirdDiedKnodePos = -21;// = -21;

int g_RailLenght = 49;
//�������ո�Ӧ��
int	IN_Start_Camera_SENSOR = 1;
//��ϼ���Ӧ��
int	IN_CHECK_BREAK = 3;
//Ԥ��ɸѡ���ϴ���͹�������
int	IN_Check_UP_TIPPEDUP = 6;
//�����������޸�Ӧ��
int	IN_CYL_Magnet_SENSOR = 7;
//Ԥ��ɸѡ���ϴ���͹�������
int	IN_Check_BT_TIPPEDUP = 8;
//������ť
int	IN_START_BTN = 16;
//ֹͣ��ť
int	IN_BTN_STOP = 17;
//�ײ�˫������Ӧ��
int	IN_Check_Double_Sword2 = 18;
//Mark3��������
int	IN_CYL_Mark3_UP_SENSOR = 19;
//�����Ӧ������
int	IN_CHECK_SENSOR = 25;
//���������Ӧ��
int	IN_DIED_KNOED_SENSOR = 25;
//����˫������Ӧ��
int	IN_Check_Double_Sword1 = 21;
//Mark1���׸�Ӧ��
int	IN_CYL_Mark1_UP_SENSOR = 22;
//���ϰ�ť���߽�̤����
int	IN_Foot_Switch = 23;
//Mark2�������޸�Ӧ��
int	IN_CYL_Mark2_UP_SENSOR = 24;
//�����Ӧ������
int	IN_CHECK_SENSOR1 = 20;
//��ѹ�������޸�Ӧ��
int	IN_CYL_Press_UP_SENSOR = 26;
//��ͣ��ť
int	IN_ESTOP_BTN = 27;
//���������Ӧ��
int	IN_Check_UP_DaJi = 28;
//�ײ������Ӧ��
int	IN_Check_BT_DaJi = 29;
//�����������޸�Ӧ��
int IN_CYL_Push_UP_SENSOR = 30;



//��Ϣ����ʱ���õ�
HWND TopCameraDlg = NULL;
HWND BottomCameraDlg = NULL;
HWND MainControlDlg = NULL;
//����ٽ���
//CRITICAL_SECTION g_top_cs;
//CRITICAL_SECTION g_bottom_cs;

std::mutex g_top_lk;
std::mutex g_bottom_lk;
std::mutex g_capture_lk;

void CPPExpDefaultExceptionHandler(const Halcon::HException& except)
{
	throw except;
}
