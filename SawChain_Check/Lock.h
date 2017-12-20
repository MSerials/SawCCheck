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
	void unlock();// 设计的时候，不要unwaite放置到unlock里面去，否则会导致职责不分明，如果有内部控制的还会导致无法唤醒。  
	void waite();// 当获取不到数据，那么waite挂起线程，等待其它线程通知释放  
	void unwaite();// 生产了数据那么需要调用unwaite.  
private:
#ifdef _MSC_VER 
	HANDLE m_mutex;
	HANDLE m_event;//事件如果有信号那么可以正常执行，如果无信号那么只能等待  
#else  
	HANDLE m_mutex;
	HANDLE m_event;//事件如果有信号那么可以正常执行，如果无信号那么只能等待 
	pthread_mutex_t m_mutex;
	pthread_cond_t m_condition;
	pthread_mutexattr_t m_mutexAttr;
#endif  
};

#endif

extern _CMutexLock g_camera_lock;