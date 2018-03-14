// SawChainMachine.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SawChain_Check.h"
#include "SawChainMachine.h"
#include "globle.h"
#include "ImageCard.h"
#include "MainFrm.h"
#include "Lock.h"
#include "CTxt.h"

using namespace Halcon;

// SawChainMachine

SawChainMachine::SawChainMachine()
	:m_system_state(0)
	, m_counter(0)
	, stack_index(-1)
	
{
	m_system_state = STOP;
	m_knode = NULL;
	m_DiedKnodedState = FALSE;
	isTopProc = false;
	isBottomProc = false;
	isErrorInfo = false;
	m_TopCameraResult = 0;
	m_BottomCameraResult = 0;
	isPausePressed = false;
	isTopDetOver = true;
	isBottomDetOver = true;
	AlertInfo.Empty();
	AlertInfo1.Empty();
}

SawChainMachine::~SawChainMachine()
{
	free(m_knode);
	//no need delete
	if (dmc1380)
	{
		delete dmc1380;
		dmc1380 = NULL;
	}
}

int SawChainMachine::Init()
{
	sccErrorCode errorcode = InitCard();

	if (CImageCard::GetIns()->InitCamera())
		return 0;
	else
		return 0;
}

CMotionCard * SawChainMachine::CurrentMotionCard()
{
	if (stack_index < 0) return nullptr;
	return mc_vector[stack_index];
}



int SawChainMachine::InitCard()
{
	int CardQuantity = 0;
	dmc1380 = new DMC1380Card();
	if (0 == dmc1380->Init())
	{
		mc_vector.push_back((CMotionCard*)dmc1380);		//�����������¼��һ����ջ��
		stack_index++;									//ͳ�ƿ�������
		CardQuantity += dmc1380->GetCardQuantity();		//ͳ�ƿ�������
	}
	else
	{
		delete dmc1380;
		dmc1380 = NULL;
	}
	if (0 == CardQuantity) return NOCARD;
	//�п���ʱ�������߳�
	mc_vector[stack_index]->WriteOutPutBit(OUT_SV_ON, 0);
	StartCamera_Thread();
	CWinThread * t1 = AfxBeginThread(system_sensor, this, THREAD_PRIORITY_ABOVE_NORMAL, 0, 0, NULL);
	CWinThread * t2 = AfxBeginThread(system_procedure, this, THREAD_PRIORITY_ABOVE_NORMAL, 0, 0, NULL);
	return NoError;
}

int SawChainMachine::InitCamera()
{
	CImageCard::GetIns()->InitCamera();
	return NoError;
}




/**
//�Ժ��Ż�֮��

float SawChainMachine::check_charater()
{
	return 0.0f;
}

float SawChainMachine::check_charater_train()
{
	return 0.0f;
}

float SawChainMachine::check_charater_predict()
{
	return 0.0f;
}
*/

/********************************ͼ���ﺯ������****************************************/

//�������Ƭװ����û��
int SawChainMachine::check_inverse(const Halcon::Hobject&src,Halcon::Hobject ROI, double thresholdvar, double minarea, double maxarea, Halcon::HTuple& disp_hand, double *areares)
{
	Hobject Regions, ImageReduced, ConnectedRegions, SelectedRegions, RegionTrans, RegionUnion;
	HTuple Area, Row, Column;	char str[256] = { 0 };	
	try
	{	
		GiveError;
		//gen_rectangle1(&ConImage1_ROI_01, ini->image1_ConSearchX0, ini->image1_ConSearchY0, ini->image1_ConSearchH0, ini->image1_ConSearchW0);
		reduce_domain(src, ROI, &ImageReduced);
		threshold(ImageReduced, &Regions, thresholdvar, 255);
		connection(Regions, &ConnectedRegions);
		select_shape(ConnectedRegions, &SelectedRegions, "area", "and", minarea/4, maxarea*4);
		shape_trans(SelectedRegions, &RegionTrans, "convex");
		union1(RegionTrans, &RegionUnion);
		area_center(RegionUnion, &Area, &Row, &Column);
		bool isOK = (Area >= minarea&&Area <= maxarea) ? true : false;

		HDevWindowStack::Push(disp_hand);
		HDevWindowStack::SetActive(disp_hand);	

		set_draw(disp_hand, "margin");
		if(true == isOK)
		{
			set_color(disp_hand, "green");
			disp_obj(RegionUnion, disp_hand);
			disp_cross(disp_hand, Row, Column, 30, 0);
			set_tposition(disp_hand, 0, 1); write_string(disp_hand, "����Ƭ���������:"); write_string(disp_hand, Area);
			return IMAGEOK;
		}
		else
		{
			set_color(disp_hand, "red");
			disp_obj(RegionUnion, disp_hand);
			disp_cross(disp_hand, Row, Column, 30, 0);
			set_tposition(disp_hand, 0, 1); write_string(disp_hand, "����Ƭװ�������:"); write_string(disp_hand, Area);
			return INV_KNODE;
		}

	}
	catch (HException &except)
	{
		GiveError;
		write_string(disp_hand, except.message);
		return INV_KNODE;
	}
}


// SawChainMachine ��Ա����
//��⵶Ƭ��û��ĥ
int SawChainMachine::check_knife(const Halcon::Hobject&src,
	Halcon::HTuple& disp_hand, 
	double r1, double c1, double r2, double c2,
	double MinLen, double MaxLen)
{
	
		int SwordResult = NoError;
		Hobject ROI, ImageReduced, Region, SwordRegion, Line;
		HTuple Width, Height, Area, RowC, ColC, Phi, Row, Col, Length1, Length2, Tan, MeasureHandle, MeasureHandle1, MeasureHandle2;
		HTuple RowEdge, ColumnEdge, Amplitude, Distance, RowEdge1, ColumnEdge1, Amplitude1, Distance1;
		HTuple RowEdge2, ColumnEdge2, Amplitude2, Distance3, RowEdge3, ColumnEdge3, Amplitude3, Distance4;
		HTuple Length, maxLength, num, Rowdiff, Coldiff, Distance2;
		Hobject fillRegion, fillRegion1, ConnectedRegions, SelectedRegions;


		try
		{
			GiveError;
			get_image_size(src, &Width, &Height);
			gen_rectangle1(&ROI, r1, c1, r2, c2);
			reduce_domain(src, ROI, &ImageReduced);
			threshold(ImageReduced, &Region, 0, 220);
			//��ȡ����Ƭ����״����
			connection(Region, &ConnectedRegions);
			select_shape_std(ConnectedRegions, &SelectedRegions, "max_area", 70);
			fill_up(SelectedRegions, &fillRegion);
			closing_rectangle1(fillRegion, &SwordRegion, 20, 20);
			fill_up(SwordRegion, &fillRegion1);
			//�ҵ����������
			area_center(fillRegion1, &Area, &RowC, &ColC);
#if 0
			write_string(disp_hand, " Row:");
			write_string(disp_hand, RowC);
			write_string(disp_hand, " ColC:");
			write_string(disp_hand, ColC);
			gen_measure_rectangle2(820, ColC - 100, HTuple(90).Rad(), 140, 10, Width, Height,
				"nearest_neighbor", &MeasureHandle1);
			gen_measure_rectangle2(820, ColC + 100, HTuple(90).Rad(), 140, 10, Width, Height,
				"nearest_neighbor", &MeasureHandle2);
#else
			gen_measure_rectangle2(RowC+10, ColC - 100, HTuple(90).Rad(), 140, 10, Width, Height,
				"nearest_neighbor", &MeasureHandle1);
			gen_measure_rectangle2(RowC+10, ColC + 100, HTuple(90).Rad(), 140, 10, Width, Height,
				"nearest_neighbor", &MeasureHandle2);

#endif
			measure_pos(ImageReduced, MeasureHandle1, 1, 30, "negative", "first", &RowEdge2,
				&ColumnEdge2, &Amplitude2, &Distance3);
			measure_pos(ImageReduced, MeasureHandle2, 1, 30, "negative", "first", &RowEdge3,
				&ColumnEdge3, &Amplitude3, &Distance4);
			line_orientation(RowEdge2, ColumnEdge2, RowEdge3, ColumnEdge3, &Phi);
			Length1 = ColumnEdge2 - ColC;
			//������б��
			tuple_tan(Phi, &Tan);
			Length2 = Length1*Tan;
			RowC = (RowEdge2 - 105) + Length2;
			gen_measure_rectangle2(RowC, ColC, Phi, (c2 - c1) / 2, 5,
				Width, Height, "nearest_neighbor", &MeasureHandle);
			measure_pos(ImageReduced, MeasureHandle, 1, 30, "negative", "first", &RowEdge, &ColumnEdge,
				&Amplitude, &Distance);
			measure_pos(ImageReduced, MeasureHandle, 1, 30, "positive", "last", &RowEdge1,
				&ColumnEdge1, &Amplitude1, &Distance1);
			//��ø߶Ȳ�
			Rowdiff = RowEdge1 - RowEdge;
			//��ó��Ȳ�
			Coldiff = ColumnEdge1 - ColumnEdge;
			//���������
			tuple_sqrt((Rowdiff*Rowdiff) + (Coldiff*Coldiff), &Distance2);
			gen_region_line(&Line, RowEdge, ColumnEdge, RowEdge1, ColumnEdge1);

			close_measure(MeasureHandle);
			close_measure(MeasureHandle1);
			close_measure(MeasureHandle2);

			HDevWindowStack::Push(disp_hand);
			HDevWindowStack::SetActive(disp_hand);
			set_draw(disp_hand, "margin");
			if ((Distance2 < MaxLen) && (Distance2 > MinLen))
			{
				set_color(disp_hand, "green");
				write_string(disp_hand, " ��Ƭ��ĥ,����:");

				write_string(disp_hand, Distance2);
				disp_obj(Line, disp_hand);
				disp_obj(ROI, disp_hand);
				return NoError;
			}
			else
			{
				set_color(disp_hand, "red");
				write_string(disp_hand, " ��Ƭδĥ������:");
				write_string(disp_hand, Distance2);
				disp_obj(Line, disp_hand);
				disp_obj(ROI, disp_hand);
				return KNIFE;
			}
			
			write_string(disp_hand, Distance2);
			disp_obj(Line, disp_hand);
			disp_obj(ROI, disp_hand);

			close_measure(MeasureHandle);
			close_measure(MeasureHandle1);
			close_measure(MeasureHandle2);
			return SwordResult;
		}
		catch (HException & except)
		{
			GiveError;
			write_string(disp_hand, except.message);
			write_string(disp_hand, " û��⵽���� ");
			return KNIFE;
		}


}




//�ַ�ƥ��,ƥ�䵽�����쳣����Ϊ�߼���������������Ū��
int SawChainMachine::check_char(const Halcon::Hobject&src,Halcon::HTuple& disp_hand, double r1, double c1, double r2, double c2,std::vector<CString> fileName,  double accuracy, int selection)
{
	static std::vector<HTuple> ncc_model_id;
	static HTuple RowRef, ColumnRef;


	//1�Ǵ���nccģ��
	if (1 == selection)
	{
		//���ģ��
		for (size_t i = 0; i < ncc_model_id.size(); i++) { clear_ncc_model(ncc_model_id[i]); }
		ncc_model_id.clear();
		//����ģ��
		for(size_t i = 0;i<fileName.size();i++)
		{ 
			try
			{
				HTuple   ModelID;
				HTuple  Width, Height, Area;
				Hobject  Rectangle, Image, ImageReduced;
				GiveError;
				char* Filename = (char*)(LPCSTR)(CStringA)fileName[i];
				read_image(&Image, Filename);
				get_image_size(Image, &Width, &Height);
				gen_rectangle1(&Rectangle, r1, c1, r2, c2);
				area_center(Rectangle, &Area, &RowRef, &ColumnRef);
				reduce_domain(Image, Rectangle, &ImageReduced);
				create_ncc_model(ImageReduced, "auto", 0, 0, "auto", "use_polarity", &ModelID);
				ncc_model_id.push_back(ModelID);
			}
			catch (HException & except)
			{
				GiveError;
				write_string(disp_hand, except.message);
				AfxMessageBox(L"����ģ������Ƿ�ģ���ļ���û��ģ��");
				set_check("give_error");
			}
		}
		if (0 == ncc_model_id.size()) { AfxMessageBox(L"�������δ��ȡ��ģ�壬�Ƿ��ļ�����û��ͼƬ");  }
		return NoError;
	}
	//0�Ǽ��ncc
	else
	{
		HTuple lScore;
		Hobject  Rectangle;
		try
		{
			GiveError;
			gen_rectangle1(&Rectangle, r1, c1, r2, c2);
			for (size_t i = 0; i < ncc_model_id.size(); i++)
			{
				HTuple  HomMat2D,Angle,Score,Row,Column;
				Hobject RegionAffineTrans, ImageReduced;
				gen_rectangle1(&Rectangle, r1, c1, r2, c2);
				reduce_domain(src, Rectangle, &ImageReduced);
				find_ncc_model(ImageReduced, ncc_model_id[i], 0, 0, 0.5, 1, 0.5, "true", 0, &Row, &Column, &Angle,
					&Score);
				vector_angle_to_rigid(RowRef, ColumnRef, 0, Row, Column, 0, &HomMat2D);
				affine_trans_region(Rectangle, &RegionAffineTrans, HomMat2D, "false");
				//disp_obj(Image, disp_hd); already displayed in grab image funtion

				HDevWindowStack::Push(disp_hand);
				HDevWindowStack::SetActive(disp_hand);
				set_draw(disp_hand, "margin");
				disp_obj(RegionAffineTrans, disp_hand);
				if (lScore < Score) lScore = Score;
				if (Score > accuracy)
				{
					set_color(disp_hand, "red");
					write_string(disp_hand, "ƥ��OK,ƥ���:");
					write_string(disp_hand, Score);
					return MIXCHAR;
				}
			}
			set_color(disp_hand, "green");
			write_string(disp_hand, "ƥ��NG,ƥ���:");
			write_string(disp_hand, lScore);
			return NoError;
		}
		catch (HException & except)
		{
			GiveError;
			HDevWindowStack::Push(disp_hand);
			HDevWindowStack::SetActive(disp_hand);
			write_string(disp_hand, except.message);
			set_color(disp_hand, "green");
			write_string(disp_hand, "ƥ�䲻��ͼƬNG:");
			write_string(disp_hand, lScore);
			return NoError;
		}
	}
}



int SawChainMachine::check_bottom_char(const Halcon::Hobject&src, Halcon::HTuple& disp_hand,
	double r1, double c1, double r2, double c2,
	std::vector<CString> fileName, double accuracy, int selection)
{
	static std::vector<HTuple> ncc_model_id;
	static HTuple RowRef, ColumnRef;



	//1�Ǵ���nccģ��
	if (1 == selection)
	{
		//���ģ��
		for (size_t i = 0; i < ncc_model_id.size(); i++) { clear_ncc_model(ncc_model_id[i]); }
		ncc_model_id.clear();
		//����ģ��
		for (size_t i = 0; i<fileName.size(); i++)
		{
			try
			{
				GiveError;
				HTuple   ModelID;
				HTuple  Width, Height, Area;
				Hobject  Rectangle, Image, ImageReduced;
				set_check("~give_error");
				char* Filename = (char*)(LPCSTR)(CStringA)fileName[i];
				read_image(&Image, Filename);
				get_image_size(Image, &Width, &Height);
				gen_rectangle1(&Rectangle, r1, c1, r2, c2);
				area_center(Rectangle, &Area, &RowRef, &ColumnRef);
				reduce_domain(Image, Rectangle, &ImageReduced);
				create_ncc_model(ImageReduced, "auto", 0, 0, "auto", "use_polarity", &ModelID);
				ncc_model_id.push_back(ModelID);
			}
			catch (HException & except)
			{
				GiveError;
				write_string(disp_hand, except.message);
				AfxMessageBox(L"�ײ��������ģ������Ƿ��ļ�����û��ģ��");
			}
		}
		if (0 == ncc_model_id.size()) { AfxMessageBox(L"�ײ����δ��ȡ��ģ�壬�Ƿ��ļ�����û��ͼƬ"); }
		return NoError;
	}
	//0�Ǽ��ncc
	else
	{
		HTuple lScore;
		Hobject  Rectangle;
		try
		{
			GiveError;
			gen_rectangle1(&Rectangle, r1, c1, r2, c2);
			for (size_t i = 0; i < ncc_model_id.size(); i++)
			{
				HTuple  HomMat2D, Angle, Score, Row, Column;
				Hobject RegionAffineTrans, ImageReduced;

				gen_rectangle1(&Rectangle, r1, c1, r2, c2);
				reduce_domain(src, Rectangle, &ImageReduced);
				find_ncc_model(ImageReduced, ncc_model_id[i], 0, 0, 0.5, 1, 0.5, "true", 0, &Row, &Column, &Angle,
					&Score);
				vector_angle_to_rigid(RowRef, ColumnRef, 0, Row, Column, 0, &HomMat2D);
				affine_trans_region(Rectangle, &RegionAffineTrans, HomMat2D, "false");
				//disp_obj(Image, disp_hd); already displayed in grab image funtion


				HDevWindowStack::Push(disp_hand);
				HDevWindowStack::SetActive(disp_hand);
				set_draw(disp_hand, "margin");
				disp_obj(RegionAffineTrans, disp_hand);
				
				if (lScore < Score) lScore = Score;
				if (Score > accuracy)
				{
					set_color(disp_hand, "red");
					write_string(disp_hand, "ƥ��OK,ƥ���:");
					write_string(disp_hand, Score);
					return MIXCHAR;
				}
			}
			set_color(disp_hand, "green");
			write_string(disp_hand, "ƥ��NG,ƥ���:");
			write_string(disp_hand, lScore);
			return NoError;
		}
		catch (HException & except)
		{
			GiveError;
			HDevWindowStack::Push(disp_hand);
			HDevWindowStack::SetActive(disp_hand);
			set_color(disp_hand, "green");
			write_string(disp_hand, "ƥ�䲻��ͼƬNG:");
			write_string(disp_hand, lScore);
			write_string(disp_hand, except.message);
			return NoError;
		}
	}
}

int SawChainMachine::check_daji(const Halcon::Hobject&src, Halcon::HTuple& disp_hand,double r1, double c1, double r2, double c2)
{
	Hobject ROI_0, ImageReduced, Region, RegionClosing, ConnectedRegions, SelectedRegions;
	HTuple  Exception, Area, Row, Column;
	//HException::InstallHHandler(&CPPExpDefaultExceptionHandler);
	
	try
	{
		set_check("~give_error");
		gen_rectangle1(&ROI_0, r1, c1, r2, c2);
		reduce_domain(src, ROI_0, &ImageReduced);
		threshold(ImageReduced, &Region, 235, 255);
		closing_circle(Region, &RegionClosing, 10);
		connection(RegionClosing, &ConnectedRegions);
		select_shape(ConnectedRegions, &SelectedRegions, (HTuple("area").Append("circularity")),
			"and", (HTuple(5000).Append(0.45)), (HTuple(40000).Append(1)));
		area_center(SelectedRegions, &Area, &Row, &Column);
		//HDevWindowStack::Push(disp_hand);
		//HDevWindowStack::SetActive(disp_hand);
		set_draw(disp_hand, "margin");
		set_line_width(disp_hand, 2);
		if (Area>8000 && Area<30000)
		{
			disp_obj(SelectedRegions, disp_hand);
			set_color(disp_hand, "red");
			write_string(disp_hand, "����������");
			write_string(disp_hand, Area);
			return DAJI;
		}
		else
		{
			set_color(disp_hand, "green");
			write_string(disp_hand, "�����������");
			write_string(disp_hand, Area);
			return NoError;
		}
	}
	catch (HException & except)
	{
		set_check("~give_error");
		write_string(disp_hand, except.message);	
		return DAJI;
	}
}










/********************************ͼ���ﺯ������END****************************************/


















/*******************��������**************************/


UINT SawChainMachine::system_sensor(LPVOID lp)
{
	SawChainMachine * p = (SawChainMachine*)lp;
	CMotionCard * mc = p->mc_vector[p->stack_index];
	system_control * sc = system_control::GetIns();
	for (;;)
	{
		Sleep(2);
		if (sc->isStopScan)	continue;
		//��ͣ��ť���ض�ȡ��Ӧ��
		DWORD bt_emergency = mc->ReadInPutBit(IN_ESTOP_BTN);
		static DWORD old_bt_emergency = bt_emergency;
		DWORD bt_foot_sw = mc->ReadInPutBit(IN_Foot_Switch);	//��̤����
		//���ذ�ť��ȡ����
		DWORD bt_start = mc->ReadInPutBit(IN_START_BTN);
		DWORD bt_stop =  !mc->ReadInPutBit(IN_BTN_STOP);
		//�����Ӧ����Ҫ��ͣ��ɨ��
		p->DiedKnode_detection();
		//���������Ӧ����ȡ����
		//for a strange reason that maybe sensor not stable
		//p->procedure();
#if 1
		static int sensor_counter = 0;
		for (int i = 0; i < 3; i++)
		{
			if(mc->ReadInPutBit(IN_Start_Camera_SENSOR))
				sensor_counter++;
		}
		DWORD new_trigger_detect_state = sensor_counter > 1 ? TRUE : FALSE;
		sensor_counter = 0;
		static DWORD old_trigger_detect_state = new_trigger_detect_state;

		//������������������ж�
		if (old_trigger_detect_state != new_trigger_detect_state && new_trigger_detect_state
			&& WAIT_OBJECT_0 == ::WaitForSingleObject(sc->evt_process, 0)
			&& (false == sc->bTrigger)
			)
		{
			sc->bTrigger = true;
			p->m_trigger_counter++;
			sc->evt_Trigger.SetEvent();		
		}
		old_trigger_detect_state = new_trigger_detect_state;

#endif
		//�Լ�ͣ��ť���������ж�
		if (!bt_emergency && (old_bt_emergency != bt_emergency)) { sc->evt_EStop.SetEvent(); p->push_button(STOP); AfxMessageBox(L"��ͣ��ť����"); }
		else { sc->evt_EStop.ResetEvent(); }

		if (WAIT_OBJECT_0 != ::WaitForSingleObject(sc->evt_EStop, 1))
		{
			if (bt_start && !bt_stop)
			{
				HWND hwnd = ::FindWindowEx(NULL, NULL, NULL, L"SawChain_Check");
				if (hwnd)	EndDialog(hwnd, FALSE);
				p->isPausePressed = false;
				int res = p->push_button(START);
				if (res) p->Present_Error_Infomation(res);
			}
			else if (bt_stop)
			{
				p->push_button(PAUSE);
				p->isPausePressed = true;
			}
		}

		//��̤����
		if (bt_foot_sw)
		{
			HWND hwnd = ::FindWindowEx(NULL, NULL, NULL, L"SawChain_Check");
			if (hwnd) {
				EndDialog(hwnd, FALSE); Sleep(200);
			}
		}
	}
	return 0;
}
/**
int SawChainMachine::procedure()
{
	DiedKnode_detection();
	DWORD new_trigger_detect_state = CurrentMotionCard()->ReadInPutBit(IN_Start_Camera_SENSOR);
	static DWORD old_trigger_detect_state = new_trigger_detect_state;
	if (old_trigger_detect_state != new_trigger_detect_state && new_trigger_detect_state && (m_system_state == START))
	{
		static std::mutex lock;
		std::lock_guard<std::mutex> lck(lock);
		m_trigger_counter++;
		Procedure();
	}
	old_trigger_detect_state = new_trigger_detect_state;
	return 1;
}
*/

UINT SawChainMachine::system_procedure(LPVOID lp)
{
	SawChainMachine * p = (SawChainMachine*)lp;
	CMotionCard * mc = p->CurrentMotionCard();
	system_control * sc = system_control::GetIns();
	DWORD new_trigger_detect_state = mc->ReadInPutBit(IN_Start_Camera_SENSOR);
	DWORD old_trigger_detect_state = new_trigger_detect_state;
	for (;;)
	{

#if 0	
		new_trigger_detect_state = mc->ReadInPutBit(IN_Start_Camera_SENSOR);
		//int sensor_counter = 0;
		if (old_trigger_detect_state != new_trigger_detect_state && new_trigger_detect_state && (p->m_system_state == START))
		{
			p->m_trigger_counter++;
			static BOOL isdealover = true;
		
			isdealover = false;;
			p->Procedure();
			isdealover = true;
			
		}
		old_trigger_detect_state = new_trigger_detect_state;
#else
		::WaitForSingleObject(sc->evt_Trigger, INFINITE);
		p->Procedure();
		sc->evt_Trigger.ResetEvent();
		sc->bTrigger = false;

		/**
		//�Ѿ���ɨ��io���������ж�
		//if (WAIT_OBJECT_0 == ::WaitForSingleObject(sc->evt_process, 0))
		{
			if (sc->bTrigger)
			{
				//ע��˳��	
				p->Procedure();	
				sc->bTrigger = false;
			}
		}
		*/
#endif
		
	}
	return 0;
}

//���߳������°�ť�������ܹ���֤������
bool SawChainMachine::Present_Error_Infomation(int code)
{
	if (isErrorInfo) return false;
	if (UNBREAK == code) ErrorInfo += L"����û�д��";
	else if(CYLNOTPOSITION == code) ErrorInfo += "����û�е�λ";
	CWinThread * t1 = AfxBeginThread(Error_Infomation_Thread, this, THREAD_PRIORITY_ABOVE_NORMAL, 0, 0, NULL);
	return true;
}

UINT SawChainMachine::Error_Infomation_Thread(LPVOID lp)
{
	SawChainMachine * p = (SawChainMachine*)lp;
	p->isErrorInfo = true;
	if (!p->ErrorInfo.IsEmpty())
	{	
		AfxMessageBox(p->ErrorInfo);
		p->ErrorInfo.Empty();
		Sleep(300);
	}
	p->isErrorInfo = false;
	return 0;
}



int SawChainMachine::system_start()
{
	//std::lock_guard<std::mutex>	lck(m_info_mtx);///<������while(0)֮���ͷţ����������߳̿��ܻ�Ӱ��AfxMessageBox//
	CMotionCard * mc = CurrentMotionCard();
	system_control * sc = system_control::GetIns();
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (nullptr == mc) return 0;
/**	
	bool c1 = (0 == ((m_counter - 1) % pMainFrm->ini.m_ChainLength - g_RailLenght%pMainFrm->ini.m_ChainLength));
	bool c2 = (0 == ((m_counter ) % pMainFrm->ini.m_ChainLength - g_RailLenght%pMainFrm->ini.m_ChainLength));
	bool c3 = (0 == ((m_counter + 1) % pMainFrm->ini.m_ChainLength - g_RailLenght%pMainFrm->ini.m_ChainLength));

	if (mc->ReadInPutBit(IN_CHECK_BREAK)
		&& (c1 || c2 || c3)
		) {
		system_pause(); return UNBREAK;
	}
	*/
	if (isPausePressed) { isPausePressed = false; return 0; }
	if (START == m_system_state)	return 0;

	if (!CheckAllSensorState()) { push_button(PAUSE); return CYLNOTPOSITION; }

	if (0 != sc->runtime_error)  return 0;

	if (sc->system_error) { push_button(PAUSE); AfxMessageBox(sc->ErrorInfo(sc->system_error)); return 0; }

	if (WAIT_OBJECT_0 == ::WaitForSingleObject(sc->evt_EStop, 0)) { push_button(STOP); AfxMessageBox(L"��ͣ��ť����"); return 0; }

	if (sc->is_bottom_grab || sc->is_top_grab) { push_button(PAUSE); AfxMessageBox(L"���û�йرգ�������̬ץͼ��ť�ر�"); return 0; }

	sc->evt_process.SetEvent();
	//Sleep(10); //�ȴ��ź�ͬ��,û��һ���ã���Ϊ��ͬһ���߳�

#ifdef _TEST
	printf("system start 2\n");
#endif

	switch (memorise_conveyor_state)
	{
	case CONVEYOR_CW:mc->ConveyorCW(); break;
	case CONVEYOR_CCW:mc->ConveyorCCW(); break;
	case CONVEYOR_STOP:mc->ConveyorSTOP(); break;
	default:mc->ConveyorSTOP(); break;
	}

	mc->StartTVMove(0, 500, pMainFrm->ini.MaxVel, pMainFrm->ini.Tacc);
	LOOP mc->WriteOutPutBit(OUT_LAMP_START_BTN, 0);
	LOOP mc->WriteOutPutBit(OUT_LAMP_STOP_BTN, 1);
	m_system_state = START;
	return 0;
}

int SawChainMachine::system_pause()
{
	if (stack_index < 0) return 0;
	if (m_system_state == PAUSE) return 0;
	system_control * sc = system_control::GetIns();
	CMotionCard * mc = CurrentMotionCard();
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	mc->EStopMove(0);
	memorise_conveyor_state = mc->GetConveyorState();
	mc->ConveyorSTOP();
	mc->WaitMotorDoneTimeOut(0, 500);
	Sleep(50);
	sc->evt_process.ResetEvent();
	LOOP mc->WriteOutPutBit(OUT_LAMP_START_BTN, 1);
	LOOP mc->WriteOutPutBit(OUT_LAMP_STOP_BTN, 0);
	m_system_state = PAUSE;
	return 0;
}

int SawChainMachine::system_stop()
{
	if (stack_index < 0) return -1;
	system_control * sc = system_control::GetIns();
	CMotionCard * mc = CurrentMotionCard();

	mc->ConveyorSTOP();
	memorise_conveyor_state = mc->GetConveyorState();
	sc->evt_process.ResetEvent();
	//�ŷ����ֹͣ
	mc->EStopMove(0);
	LOOP mc->WriteOutPutBit(OUT_LAMP_START_BTN, 1);
	LOOP mc->WriteOutPutBit(OUT_LAMP_STOP_BTN, 1);

	m_system_state = STOP;
	return 0;
}

int SawChainMachine::system_reset()
{
	if (stack_index < 0) return -1;
	CMotionCard * mc = CurrentMotionCard();
	system_control * sc = system_control::GetIns();
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	push_button(STOP);
	if (WAIT_OBJECT_0 == ::WaitForSingleObject(sc->evt_EStop, 0)) { AfxMessageBox(L"��ͣ��ť����"); return 0; }
	//�������׻ص�ԭ��
	DWORD Tick = GetTickCount();
	while (!CheckAllSensorState()) {
		PushAllCylinderBack();
		if ((GetTickCount() - Tick) > 1000) { AfxMessageBox(L"���׸�Ӧ���������ǲ���ͨ����"); return 0; }
		Sleep(200);
	}

	//�ŷ������Զ��
	//�Ѿ��������ĺ�����д��

	//���ڼ���Ƿ��λ�ļ���
	m_conveyorcounter = 0;
	m_trigger_counter = 0;
	m_counter = 0;
	m_ng_counter = 0;

	//return;
	m_max_knode = g_MAX_CHAIN*pMainFrm->ini.m_ChainLength;
	if(NULL != m_knode) free(m_knode);
		m_knode = (KNODE*)malloc(m_max_knode * sizeof(KNODE));
	if (!m_knode) { AfxMessageBox(L"�����ڴ�ʧ��"); return -1; }
	for (int i = 0; i < m_max_knode; i++)
	{
		m_knode[i].BottomError = 0;
		m_knode[i].TopError = 0;
		m_knode[i].kind = 0;
		m_knode[i].TopKnife = 0;
		m_knode[i].BottomKnife = 0;
	}
	system_control::GetIns()->runtime_error = 0;
	return 0;
}

//int SawChainMachine::get_system_state()
//{
	//static std::mutex sys_lock;
	//std::lock_guard<std::mutex>	lck(sys_lock);
//	return m_system_state;
//}


/*******************��������END**************************/


/*******************�����˶�������**************************/

void SawChainMachine::Conveyor_running(int ChainNo)
{
	if (ChainNo<0) return;//Ϊ�˷�ֹ����
	static int older_chainno = ChainNo;
	CMotionCard * mc = CurrentMotionCard();
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	int l_begin = ChainNo*(pMainFrm->ini.m_ChainLength); //����������62�ڳ��ȣ���ô���˳��Ϊ0-61��62-123
	int l_end = l_begin + pMainFrm->ini.m_ChainLength - 1;//-1��Ϊ�������ӿ۲����

	bool isOK = true;
	for (; l_begin <= l_end; l_begin++)																				//���ӿ۲��ֲ����������û����ж�
	{
		if (m_knode[l_begin].TopError || m_knode[l_begin].BottomError)
		{
			isOK = false;													//m_ChainCounter%g_MAX_CHAIN��Ϊֻ����32��������ѭ��
			break;
		}
	}

	if (isOK)													//���ʹ���������״̬��������ת,CW = 1;
	{
		if (CONVEYOR_CCW == mc->GetConveyorState()) mc->ConveyorSTOP();//bug,�����æ�߼��ϸı����ʹ����򣬻ᵼ�����ʹ���е�ϲ���ı䷽��
		else mc->ConveyorCW();
	}
	else
	{
		if (CONVEYOR_CW == mc->GetConveyorState()) mc->ConveyorSTOP();//bug,�����æ�߼��ϸı����ʹ����򣬻ᵼ�����ʹ���е�ϲ���ı䷽��
		else mc->ConveyorCCW();
	}

	if (ChainNo != older_chainno)
	{
		if (!isOK)
		{
			system_control::GetIns()->ng_chain++;
		}
	}
	older_chainno = ChainNo;
}


//���̺���
UINT SawChainMachine::Procedure()
{	
	if (nullptr == CurrentMotionCard()) return NOCARD;//NoCard

	static std::mutex lock;
	std::lock_guard<std::mutex> lck(lock);
	CMotionCard * mc = CurrentMotionCard();
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	static int chain_order = 0;
	DWORD Tick = GetTickCount();
	int l_position = get_id_by_position(m_counter,-50,m_max_knode);
	m_knode[l_position].TopError = m_knode[l_position].BottomError = NoError;//���Ŀ����Ϊ�˽��г�ʼ�����Ѹս��������Ƭ״̬��0
	m_knode[l_position].TopKnife = m_knode[l_position].BottomKnife = NoActivateCamera;//���Ŀ����Ϊ�˽��г�ʼ�����Ѹս��������Ƭ״̬��0������ᴥ�����ȥ�жϵ���δĥ
	ScanAllSensor();						//��Ӧ������ɨ�裬Ҳ����˵��ɨ���������ٽ��д���
	StartCamera();					//��Ϊ����ӻ�ȡͼƬ������ͼƬ����ʱ�䳤������������ǰ��

	if (0 == (m_counter%pMainFrm->ini.m_ChainLength - g_RailLenght%pMainFrm->ini.m_ChainLength)) //�������������жϵ��˴�ϵ���һ�ڵ�,pMainFrm->m_KnodeCounter%pMainFrm->m_ChainLength��֤��ѭ�� //g_RailLenght%pMainFrm->m_ChainLength������ƫ�ƣ������������С��48��ǰ�������Ҳ���Խ��д�ϣ�������Ҫ�ȴ�49��
	{

		m_conveyorcounter = 0;
		//���������������������һ���ǵڼ���
		chain_order = ((m_counter - g_RailLenght) / pMainFrm->ini.m_ChainLength)  % g_MAX_CHAIN;//���㵱ǰ��������ĵڼ�����Ϊ���ô��ʹ�ͳ��
		//�����������
		Break_chain_action();
		push_button(START);
//		system_start();
	}
	//tdd/

	Chain_Detection();
	if (m_counter < /*g_RailLenght*/(g_RailLenght + pMainFrm->ini.m_ChainLength))
		mc->ConveyorCCW(); //����⻹û����49�ڵ�ʱ���������ʹ��ᷴת
						  //�ڴ��25�ں��ٽ����ж�������
	else if (m_conveyorcounter >= 20)
		Conveyor_running(chain_order);
	m_conveyorcounter++;
	m_counter++;
	ShowAlertInfo();
	::PostMessage(MainControlDlg, WM_MESSAGE_COUNTER, m_counter, m_ng_counter);
	return NoError;
}


int SawChainMachine::push_button(int sel)
{
	static std::mutex btn_lock;
	std::lock_guard<std::mutex>	lck(btn_lock);
	switch (sel)
	{
	case START:system_start(); return m_system_state; break;
	case PAUSE:system_pause(); return m_system_state; break;
	case STOP:system_stop(); return m_system_state; break;
	case SYS_STATE:return m_system_state; break;
	default:system_stop(); return m_system_state; break;
	}
}

UINT SawChainMachine::TopCameraProcedure(LPVOID lp)
{
	SawChainMachine *p = (SawChainMachine*)lp;
	system_control * sc = system_control::GetIns();
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	p->isTopProc = true;
	//�ɼ�һ��ͼƬ
	for (;;)
	{
		::WaitForSingleObject(system_control::GetIns()->evt_start_top_camera, INFINITE);
		system_control::GetIns()->evt_start_top_camera.ResetEvent();
		try 
		{
			Halcon::set_check("~give_error");
			CImageCard::GetIns()->Image = CImageCard::GetIns()->GetTopImage();
			p->m_TopCameraResult = NoError;
			//���ӿ۵ĵط������м�⣬ֻ����һ�ž͹���
			int l_position = p->get_id_by_position(p->m_counter, g_UpCameraPos, p->m_max_knode);
			int m_chain_length = pMainFrm->ini.m_ChainLength - 1;
			if ((m_chain_length == l_position%pMainFrm->ini.m_ChainLength))
			{
				CImageCard::GetIns()->Top_Disp_Obj(CImageCard::GetIns()->Image);
			}
			else
			{
				Halcon::Hobject invroi, kniferoi, charroi;
				Halcon::gen_rectangle1(&invroi, pMainFrm->ini.top_inv.r1, pMainFrm->ini.top_inv.c1, pMainFrm->ini.top_inv.r2, pMainFrm->ini.top_inv.c2);
				Halcon::gen_rectangle1(&kniferoi, pMainFrm->ini.top_knife.r1, pMainFrm->ini.top_knife.c1, pMainFrm->ini.top_knife.r2, pMainFrm->ini.top_knife.c2);
				Halcon::gen_rectangle1(&charroi, pMainFrm->ini.top_char.r1, pMainFrm->ini.top_char.c1, pMainFrm->ini.top_char.r2, pMainFrm->ini.top_char.c2);
				double area;
				CImageCard::GetIns()->Top_Disp_Obj(CImageCard::GetIns()->Image);
				p->m_TopCameraResult |= pMainFrm->SCM.check_inverse(CImageCard::GetIns()->Image, invroi, pMainFrm->ini.TopPara.thresholdvalue, pMainFrm->ini.TopPara.minarea, pMainFrm->ini.TopPara.maxarea, CImageCard::GetIns()->disp_hd, &area);
				if (p->isBottomKnife())
				{
					p->m_TopCameraResult |= pMainFrm->SCM.check_knife(CImageCard::GetIns()->Image, CImageCard::GetIns()->disp_hd, pMainFrm->ini.top_knife.r1, pMainFrm->ini.top_knife.c1, pMainFrm->ini.top_knife.r2, pMainFrm->ini.top_knife.c2,
						pMainFrm->ini.TopPara.minlen, pMainFrm->ini.TopPara.maxlen);
				}
				p->m_TopCameraResult |= pMainFrm->SCM.check_daji(CImageCard::GetIns()->Image, CImageCard::GetIns()->disp_hd, pMainFrm->ini.top_unbolt.r1, pMainFrm->ini.top_unbolt.c1, pMainFrm->ini.top_unbolt.r2, pMainFrm->ini.top_unbolt.c2);
				std::vector<CString> images;
				p->m_TopCameraResult |= pMainFrm->SCM.check_char(CImageCard::GetIns()->Image, CImageCard::GetIns()->disp_hd, pMainFrm->ini.top_char.r1, pMainFrm->ini.top_char.c1, pMainFrm->ini.top_char.r2, pMainFrm->ini.top_char.c2,
					images, pMainFrm->ini.TopPara.match_acc, 0);
				}
			}
			catch (HException e) {
				//Halcon::set_check("give_error");
			}
		sc->evt_TopCamDetect.SetEvent();
	}
	p->isTopProc = false;
	return 0;
}

UINT SawChainMachine::BottomCameraProcedure(LPVOID lp)
{
	SawChainMachine *p = (SawChainMachine*)lp;
	system_control * sc = system_control::GetIns();
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	p->isBottomProc = true;
	//�ɼ�һ��ͼƬ
	for (;;)
	{
		::WaitForSingleObject(system_control::GetIns()->evt_start_bottom_camera, INFINITE);
		system_control::GetIns()->evt_start_bottom_camera.ResetEvent();
		try
		{
			Halcon::set_check("~give_error");
			CImageCard::GetIns()->Image1 = CImageCard::GetIns()->GetBottomImage();

			p->m_TopCameraResult = NoError;
			//���ӿ۵ĵط������м�⣬ֻ����һ�ž͹���
			int l_position = p->get_id_by_position(p->m_counter, g_BtCameraPos, p->m_max_knode);
			int m_chain_length = pMainFrm->ini.m_ChainLength - 1;
			//(m_chain_length != l_position%m_ChainLength)�������ӿ۵�λ��
			if ((m_chain_length == l_position%pMainFrm->ini.m_ChainLength))
			{
				CImageCard::GetIns()->Bottom_Disp_Obj(CImageCard::GetIns()->Image1);
			}
			else {

				Halcon::Hobject invroi, kniferoi, charroi;
				Halcon::gen_rectangle1(&invroi, pMainFrm->ini.bottom_inv.r1, pMainFrm->ini.bottom_inv.c1, pMainFrm->ini.bottom_inv.r2, pMainFrm->ini.bottom_inv.c2);
				Halcon::gen_rectangle1(&kniferoi, pMainFrm->ini.bottom_knife.r1, pMainFrm->ini.bottom_knife.c1, pMainFrm->ini.bottom_knife.r2, pMainFrm->ini.bottom_knife.c2);
				Halcon::gen_rectangle1(&charroi, pMainFrm->ini.bottom_char.r1, pMainFrm->ini.bottom_char.c1, pMainFrm->ini.bottom_char.r2, pMainFrm->ini.bottom_char.c2);

				double area;
				CImageCard::GetIns()->Bottom_Disp_Obj(CImageCard::GetIns()->Image1);
				p->m_BottomCameraResult |= pMainFrm->SCM.check_inverse(CImageCard::GetIns()->Image1, invroi, pMainFrm->ini.BottomPara.thresholdvalue, pMainFrm->ini.BottomPara.minarea, pMainFrm->ini.BottomPara.maxarea, CImageCard::GetIns()->disp_hd1, &area);
				if (p->isTopKnife())
				{
					p->m_BottomCameraResult |= pMainFrm->SCM.check_knife(CImageCard::GetIns()->Image1, CImageCard::GetIns()->disp_hd1, pMainFrm->ini.bottom_knife.r1, pMainFrm->ini.bottom_knife.c1, pMainFrm->ini.bottom_knife.r2, pMainFrm->ini.bottom_knife.c2,
						pMainFrm->ini.BottomPara.minlen, pMainFrm->ini.BottomPara.maxlen);
				}
				p->m_BottomCameraResult |= pMainFrm->SCM.check_daji(CImageCard::GetIns()->Image1, CImageCard::GetIns()->disp_hd1, pMainFrm->ini.bottom_unbolt.r1, pMainFrm->ini.bottom_unbolt.c1, pMainFrm->ini.bottom_unbolt.r2, pMainFrm->ini.bottom_unbolt.c2);
				std::vector<CString> images;
				p->m_BottomCameraResult |= pMainFrm->SCM.check_bottom_char(CImageCard::GetIns()->Image1, CImageCard::GetIns()->disp_hd1, pMainFrm->ini.bottom_char.r1, pMainFrm->ini.bottom_char.c1, pMainFrm->ini.bottom_char.r2, pMainFrm->ini.bottom_char.c2,
					images, pMainFrm->ini.BottomPara.match_acc, 0
				);
			}
		}
		catch (HException e)
		{
			//Halcon::set_check("give_error");
		}

		sc->evt_BottomCamDetect.SetEvent();
	}//for end
	p->isBottomProc = false;
	return 0;
}

bool SawChainMachine::StartCamera_Thread()
{
	pTopCamera = NULL; pBottomCamera = NULL;
	pTopCamera = AfxBeginThread(TopCameraProcedure, this, THREAD_PRIORITY_ABOVE_NORMAL, 0, 0, NULL);
	pBottomCamera = AfxBeginThread(BottomCameraProcedure, this, THREAD_PRIORITY_ABOVE_NORMAL, 0, 0, NULL);
	if (!pTopCamera || !pBottomCamera)
		return false;
	else
		return true;
}


bool SawChainMachine::StartCamera()
{
	system_control::GetIns()->evt_start_top_camera.SetEvent();
	system_control::GetIns()->evt_start_bottom_camera.SetEvent();
	return true;
}

void SawChainMachine::ScanAllSensor()
{
	CMotionCard * mc = CurrentMotionCard();
	
	//���������ȶ�
	//for (int i = 0; i < 32; i++) {
		m_TopDoubleKnifeSensor = !mc->ReadInPutBit(IN_Check_Double_Sword1); //if (!m_TopDoubleKnifeSensor) break;
	//}
	//for (int i = 0; i < 32; i++) {
		m_BottomDoubleKnifeSensor = !mc->ReadInPutBit(IN_Check_Double_Sword2);// if (!m_BottomDoubleKnifeSensor) break;
	//}

	m_TopDaJiSensor = mc->ReadInPutBit(IN_Check_UP_DaJi);
	m_BottomDaJiSensor = mc->ReadInPutBit(IN_Check_BT_DaJi);
	
	//m_DiedKnodeSensor				= mc->ReadInPutBit(IN_CHECK_SENSOR1);
	m_DiedKnodedRes					= !m_DiedKnodedState;
	m_DiedKnodedState				= FALSE;
}

bool SawChainMachine::CheckAllSensorState()
{

	CMotionCard * mc = CurrentMotionCard();
	return (mc->ReadInPutBit(IN_CYL_Press_UP_SENSOR)			//26
		&& mc->ReadInPutBit(IN_CYL_Push_UP_SENSOR)				//30
		&& mc->ReadInPutBit(IN_CYL_Magnet_SENSOR)				//7
		);
}

void SawChainMachine::PushAllCylinderBack()
{
	CMotionCard * mc = CurrentMotionCard();
	mc->WriteOutPutBit(OUT_CYL_MARK, 1);
	mc->WriteOutPutBit(OUT_CYL_Press, 1);
	mc->WriteOutPutBit(OUT_CYL_Push, 1);
	mc->WriteOutPutBit(OUT_CYL_MAGNET, 1);
	mc->WriteOutPutBit(OUT_Magnet, 1);//�����ϵ�
}

void SawChainMachine::Break_chain_action()
{
	std::lock_guard<std::mutex>	lck(m_info_mtx);///<������while(0)֮���ͷţ����������߳̿��ܻ�Ӱ��AfxMessageBox//
	CMotionCard * mc = CurrentMotionCard();
	system_control * sc = system_control::GetIns();
	int convyoser_state = mc->GetConveyorState();
	system_control::GetIns()->runtime_error = 1;
	push_button(PAUSE);
//	system_pause();
	switch (convyoser_state) {
	case CONVEYOR_CCW: mc->ConveyorCCW(); break;
	case CONVEYOR_CW: mc->ConveyorCW(); break;
	case CONVEYOR_STOP: mc->ConveyorSTOP(); break;
	default:break;
	}
	LOOP mc->WriteOutPutBit(OUT_CYL_MAGNET, 0);
	LOOP mc->WriteOutPutBit(OUT_Magnet, 0);
	Sleep(100);
	LOOP mc->WriteOutPutBit(OUT_CYL_Press, 0);//��ѹ������ 
	Sleep(180);
	LOOP mc->WriteOutPutBit(OUT_CYL_Push, 0);
	Sleep(190);
	LOOP mc->WriteOutPutBit(OUT_CYL_Push, 1);
	Sleep(150);
	LOOP mc->WriteOutPutBit(OUT_CYL_Push, 0);
	Sleep(220);
	LOOP mc->WriteOutPutBit(OUT_CYL_MAGNET, 1); // ���õ����������������
	Sleep(350);
	LOOP mc->WriteOutPutBit(OUT_CYL_Push, 1);
	LOOP mc->WriteOutPutBit(OUT_CYL_Press, 1);//��ѹ������
	LOOP mc->WriteOutPutBit(OUT_Magnet, 1);
											  //������Ϣ��ʾ//
	
		
		LOOP mc->WriteOutPutBit(OUT_JOINT_INDICATOR, 0);
		AfxMessageBox(L"�����");
		Sleep(500);
		for (;;) {
			if (!mc->ReadInPutBit(IN_CHECK_BREAK)) break;
			system_control::GetIns()->runtime_error = 1;
			push_button(PAUSE);
			AfxMessageBox(L"����û�д��");
			Sleep(100);
		}
	system_control::GetIns()->runtime_error = 0;
	LOOP mc->WriteOutPutBit(OUT_JOINT_INDICATOR, 1);
}

void SawChainMachine::DiedKnode_detection()
{
	if (m_system_state != START)	return;//���Ǽ��״̬���Ƿ񲻽�������ļ��
	if (!m_DiedKnodedState && CurrentMotionCard()->ReadInPutBit(IN_DIED_KNOED_SENSOR))
	{
		m_DiedKnodedState = TRUE;
	}
}

bool SawChainMachine::DoubleKnifeSensor()
{
	int l_position;
	UpDoubleKnifeSensor();
	BtDoubleKnifeSensor();

	if (g_DoubleKnifePos1 > g_DoubleKnifePos)
		l_position = get_id_by_position(m_counter, g_DoubleKnifePos1, m_max_knode); //�ҵ�λ��������Ǹ����ж�
	else
		l_position = get_id_by_position(m_counter, g_DoubleKnifePos, m_max_knode); //�ҵ�λ��������Ǹ����ж�

	if (m_knode[l_position].BottomKnife &&
		m_knode[l_position].TopKnife)
	{
		m_knode[l_position].TopError |= DOUBLEKNIFE;
		AlertInfo += L" ˫���� ";
		return true;
	}
	return false;
}

bool SawChainMachine::BtDoubleKnifeSensor()
{
	int l_position = get_id_by_position(m_counter, g_DoubleKnifePos1, m_max_knode);
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	int m_chain_length = pMainFrm->ini.m_ChainLength - 1;
	if (m_BottomDoubleKnifeSensor || (m_chain_length == l_position%pMainFrm->ini.m_ChainLength))
		return false;

	m_knode[l_position].BottomKnife |= TRUE;
	return true;
}

bool SawChainMachine::UpDoubleKnifeSensor()
{
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	int m_chain_length = pMainFrm->ini.m_ChainLength - 1;
	int l_position = get_id_by_position(m_counter, g_DoubleKnifePos, m_max_knode);
	if (m_TopDoubleKnifeSensor || (m_chain_length == l_position%pMainFrm->ini.m_ChainLength))
		return false;

	m_knode[l_position].TopKnife |= TRUE;
	return true;
}

bool SawChainMachine::UpDajiSensor()
{
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	int m_chain_length = pMainFrm->ini.m_ChainLength - 1;
	int l_position = get_id_by_position(m_counter, g_UpDaJiPos, m_max_knode);
	if (m_TopDaJiSensor || (m_chain_length == l_position%pMainFrm->ini.m_ChainLength))
		return false;
	m_knode[l_position].TopError |= TDAJI;
	AlertInfo += L" ������� ";
	return true;
}

bool SawChainMachine::BtDajiSensor()
{
	//����true�������������
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	int m_chain_length = pMainFrm->ini.m_ChainLength - 1;
	int l_position = get_id_by_position(m_counter, g_BtDaJiPos, m_max_knode);
	int f_position = get_id_by_position(m_counter, g_BtDaJiPos + static_cast<int>(pMainFrm->ini.m_ChainLength-2), m_max_knode);
	int b_position = get_id_by_position(m_counter, g_BtDaJiPos - static_cast<int>(pMainFrm->ini.m_ChainLength-2), m_max_knode);
	//if(m_chain_length == l_position%m_ChainLength) (pImageCard->WindowHandle1,"����Ĵ��������¼");
	//������Ľڵ��ʱ����
#if 1
	//�ڴ��λ�ã�����Ҫ��⵽��ֵ���ǲ�������
	if (m_chain_length == l_position%pMainFrm->ini.m_ChainLength && m_BottomDaJiSensor)
	{
		m_knode[l_position].BottomError |= BDAJI;
		m_knode[f_position].BottomError |= BDAJI;
		m_knode[b_position].BottomError |= BDAJI;
		AlertInfo1 += L" ���ӵ���ܴ�λ ";
		return true;
	}	
#endif
	//��⵽û�д�������߸պ��ڴ��λ�ã���ֵ��
	if (m_BottomDaJiSensor || (m_chain_length == l_position%pMainFrm->ini.m_ChainLength))
		return false;
	m_knode[l_position].BottomError |= BDAJI;
	AlertInfo1 += L" �ײ���� ";
	return true;
}

bool SawChainMachine:: DiedKnode2()
{
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	int m_chain_length = pMainFrm->ini.m_ChainLength - 1;
	int l_position = get_id_by_position(m_counter, g_ThirdDiedKnodePos, m_max_knode);	
#if 0
	//ȥ������������
	int l_position1 = get_id_by_position(m_counter, g_ThirdDiedKnodePos-1, m_max_knode);
	int l_position2 = get_id_by_position(m_counter, g_ThirdDiedKnodePos+1, m_max_knode);
	if (m_DiedKnodedRes || (m_chain_length == l_position%pMainFrm->ini.m_ChainLength)
		|| (m_chain_length == l_position1%pMainFrm->ini.m_ChainLength)
		|| (m_chain_length == l_position2%pMainFrm->ini.m_ChainLength )
		)
		return false;
#else
	if (m_DiedKnodedRes || (m_chain_length == l_position%pMainFrm->ini.m_ChainLength))
		return false;
#endif
	m_knode[l_position].TopError |= DIEDKNODE;
	AlertInfo += L" ���� ";
	return true;
}

void SawChainMachine::MarkAction()
{
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CMotionCard * mc = CurrentMotionCard();
	if (!pMainFrm->sys.m_isNotMark)
	{
		int m_chain_length = pMainFrm->ini.m_ChainLength - 1;
		int l_position = get_id_by_position(m_counter, g_MarkPos, m_max_knode);
		if ((m_knode[l_position].TopError || m_knode[l_position].BottomError) && (m_chain_length != (l_position%pMainFrm->ini.m_ChainLength)))
		{
			//system_pause();
			push_button(PAUSE);
			system_control::GetIns()->runtime_error = 1;
			LOOP mc->WriteOutPutBit(OUT_CYL_MARK, 0);
			Sleep(230);
			LOOP mc->WriteOutPutBit(OUT_CYL_MARK, 1);
			Sleep(100);
			system_control::GetIns()->runtime_error = 0;
			push_button(START);
			//system_start();
		}
	}
}

void SawChainMachine::Chain_Detection()
{
	system_control * sc = system_control::GetIns();
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (UpDajiSensor()) { sc->tdaji++; Csv::GetIns()->WriteContent(RTDAJI);}	
	if (BtDajiSensor()) { sc->bdaji++; Csv::GetIns()->WriteContent(RBDAJI);}	
	if (DoubleKnifeSensor()) { sc->doubleknife++; Csv::GetIns()->WriteContent(RSHUANGDAOLI);}
	if (DiedKnode2()) { sc->diedknode++; Csv::GetIns()->WriteContent(RSIJIE3);}
	MarkAction();
	::WaitForSingleObject(sc->evt_TopCamDetect, INFINITE);				//���ǵ��������ʱ������ѵȴ��������,ע�⿪������ĵط���autorun���棬
	::WaitForSingleObject(sc->evt_BottomCamDetect, INFINITE);
	sc->evt_TopCamDetect.ResetEvent();
	sc->evt_BottomCamDetect.ResetEvent();
	

	//��ʵ�Ѿ�����Ҫȥ�ж�λ���ˣ���Ϊͼ���ﲿ���Ѿ��жϺ���
	int l_position =  get_id_by_position(m_counter, g_UpCameraPos, m_max_knode);
	int m_chain_length = pMainFrm->ini.m_ChainLength - 1;
	         //(m_chain_length != l_position%m_ChainLength)�������ӿ۵�λ��
	if (m_TopCameraResult && (m_chain_length != l_position%pMainFrm->ini.m_ChainLength))
	{
		m_knode[l_position].TopError |= m_TopCameraResult;
	}
	l_position = get_id_by_position(m_counter, g_BtCameraPos, m_max_knode);
	if (m_BottomCameraResult && (m_chain_length != l_position%pMainFrm->ini.m_ChainLength))
	{
		m_knode[l_position].BottomError |= m_BottomCameraResult;
	}

	if (!AlertInfo.IsEmpty())
	{
		CString Alert = AlertInfo;
		char * ErrorInfo = (char*)(LPCSTR)(CStringA)(CString)Alert;
		Halcon::set_color(CImageCard::GetIns()->disp_hd,"red");
		Halcon::write_string(CImageCard::GetIns()->disp_hd, ErrorInfo);
	}
	if (!AlertInfo1.IsEmpty())
	{
		CString Alert = AlertInfo1;
		char * ErrorInfo = (char*)(LPCSTR)(CStringA)(CString)Alert;
		Halcon::set_color(CImageCard::GetIns()->disp_hd1, "red");
		Halcon::write_string(CImageCard::GetIns()->disp_hd1, ErrorInfo);
	}

	if (INV_KNODE == (INV_KNODE& m_TopCameraResult)) {
		sc->tinv++; AlertInfo += L" ��������Ƭװ�� ";
		Csv::GetIns()->WriteContent(RTLIANJIEPIAN);
	}
	if (KNIFE == (KNIFE & m_TopCameraResult))
	{
		sc->tknife++; AlertInfo += L" ��������δĥ ";
		Csv::GetIns()->WriteContent(RTDAOKOU);
	}
	if (MIXCHAR == (MIXCHAR & m_TopCameraResult))
	{
		sc->tchar++; AlertInfo += L" �����ַ����� ";
		Csv::GetIns()->WriteContent(RTZIFU);
	}
	if (DAJI == (DAJI & m_TopCameraResult))
	{
		sc->tchar++; AlertInfo += L" ����ͼ���� ";
		Csv::GetIns()->WriteContent(RTDAJI);
	}
	m_TopCameraResult = NoError;

	if (INV_KNODE == (INV_KNODE& m_BottomCameraResult))
	{
		sc->binv++; AlertInfo1 += L" �ײ�����Ƭװ�� ";
		Csv::GetIns()->WriteContent(RBLIANJIEPIAN);
	}
	if (KNIFE == (KNIFE & m_BottomCameraResult))
	{
		sc->bknife++; AlertInfo1 += L" �ײ�����δĥ ";
		Csv::GetIns()->WriteContent(RBDAOKOU);
	}
	if (MIXCHAR == (MIXCHAR & m_BottomCameraResult))
	{
		sc->bchar++; AlertInfo1 += L" �ײ��ַ����� ";
		Csv::GetIns()->WriteContent(RBZIFU);
	}
	if (DAJI == (DAJI & m_BottomCameraResult))
	{
		sc->tchar++; AlertInfo += L" �ײ�ͼ���� ";
		Csv::GetIns()->WriteContent(RBDAJI);
	}
	m_TopCameraResult = NoError;
	m_BottomCameraResult = NoError;
	return;
}

bool SawChainMachine::isTopKnife()
{
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CMotionCard *mc = CurrentMotionCard();
	bool isKnife = false;
	static int top_sword_counter = 0;
	if (m_knode[get_id_by_position(m_counter, g_BtCameraPos, m_max_knode)].TopKnife)
	{
		isKnife = true;
		top_sword_counter = 0;
	}
	if (15 < (top_sword_counter++))
	{
		AlertInfo += L" ������Ӧ��û��⵽���� ";
	}
	return isKnife;
}

bool SawChainMachine::isBottomKnife()
{
	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CMotionCard *mc = CurrentMotionCard();
	bool isKnife = false;
	static int bottom_sword_counter = 0;
	if (m_knode[get_id_by_position(m_counter, g_UpCameraPos, m_max_knode)].BottomKnife)
	{
		isKnife = true;
		bottom_sword_counter = 0;
	}
	if (15 < (bottom_sword_counter++))
	{
		AlertInfo1 += L" �ײ���Ӧ��û��⵽���� ";
	}
	return isKnife;
}

void SawChainMachine::ShowAlertInfo()
{


	CMainFrame	* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CMotionCard *mc = CurrentMotionCard();
	if (!AlertInfo.IsEmpty() || !AlertInfo1.IsEmpty())
	{	
		m_ng_counter++;
		if (!pMainFrm->sys.m_isAlertStop)
		{
			CString str = AlertInfo + AlertInfo1;
			LOOP mc->WriteOutPutBit(OUT_LAMP_RED_TOWER, 0);
			push_button(PAUSE);
			system_control::GetIns()->runtime_error = 1;
			AfxMessageBox(L"������ϢΪ��"+str);
			system_control::GetIns()->runtime_error = 0;
			Sleep(20);
			push_button(START);
			LOOP mc->WriteOutPutBit(OUT_LAMP_RED_TOWER, 1);
		}
	}
	AlertInfo.Empty();
	AlertInfo1.Empty();


	if (m_counter != m_trigger_counter)
	{
		LOOP mc->WriteOutPutBit(OUT_LAMP_RED_TOWER, 0);
		push_button(PAUSE);
		system_control::GetIns()->runtime_error = 1;
		CString str;
		str.Format(L"���ܷ�����λ ����������%d ��������%d", m_trigger_counter, m_counter);
		AfxMessageBox(str);
		system_control::GetIns()->runtime_error = 0;
		Sleep(10);
		push_button(START);
		LOOP mc->WriteOutPutBit(OUT_LAMP_RED_TOWER, 1);
	}
	m_trigger_counter = static_cast<int>(m_counter);// m_counter;
}

int SawChainMachine::get_id_by_position(int counter, int position, int max_node)
{
	if (counter%max_node < position)
		return max_node + counter%max_node - position;
	else
		return (counter - position) % max_node;// - position;
}


/************************************��������END********************************************/


