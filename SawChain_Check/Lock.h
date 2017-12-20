#pragma once





#ifndef __LOCK__
#define __LOCK__

class _CMutexLock
{
public:
	_CMutexLock();
	~_CMutexLock();
	void init();
	void release();
	void lock();
	void unlock();// ��Ƶ�ʱ�򣬲�Ҫunwaite���õ�unlock����ȥ������ᵼ��ְ�𲻷�����������ڲ����ƵĻ��ᵼ���޷����ѡ�  
	void waite();// ����ȡ�������ݣ���ôwaite�����̣߳��ȴ������߳�֪ͨ�ͷ�  
	void unwaite();// ������������ô��Ҫ����unwaite.  
private:
#ifdef _MSC_VER 
	HANDLE m_mutex;
	HANDLE m_event;//�¼�������ź���ô��������ִ�У�������ź���ôֻ�ܵȴ�  
#else  
	HANDLE m_mutex;
	HANDLE m_event;//�¼�������ź���ô��������ִ�У�������ź���ôֻ�ܵȴ� 
	pthread_mutex_t m_mutex;
	pthread_cond_t m_condition;
	pthread_mutexattr_t m_mutexAttr;
#endif  
};

#endif

extern _CMutexLock g_camera_lock;