
#include "JuThread.h"
#include "JuSemaphore.h"
#include "JuCriticalSection.h"
#include "../Memory/JuThreadAllocator.h"
#include <functional>
#include <queue>

class JuThreadPool 
{
public:
	typedef std::function<void(JuThreadAllocator *)> JobFunction; 
public:
	JuThreadPool();
	~JuThreadPool();
	//添加工作线程
	void addWorker(int nCount=1);
	//加入一个函数让工作线程去执行
	inline void pushJob(JobFunction &fun);
	inline void pushJobs(vector<JobFunction> &funs);
	inline void waitJobComplete();
	//关闭线程池,会阻塞等待所有工作线程完成工作结束后返回
	void close();
private:
	static void work(void *pData);
	inline bool getJobToProcess(JobFunction &job);
private:
	CriticalSection m_funsLock;
	std::queue<JobFunction> m_funs;
	CriticalSection m_workerLock;
	std::vector<Thread> m_workers;
	Semaphore m_signal;
	int m_nCurJobs;
	int m_bRun;
};

inline void JuThreadPool::pushJob(JobFunction &fun)
{
	CriticalSection::ScopeLock lk(m_funsLock);
	m_funs.push(fun);
	CriticalSection::atomicAdd(&m_nCurJobs,1);
	m_signal.releaseSignal();
}

inline void JuThreadPool::pushJobs(vector<JobFunction> &funs)
{
	CriticalSection::ScopeLock lk(m_funsLock);
	for(uint_t i=0; i<funs.size(); ++i)
	{
		m_funs.push(funs[i]);
	}
	CriticalSection::atomicAdd(&m_nCurJobs,funs.size());
	m_signal.releaseSignal(funs.size());
}

inline bool JuThreadPool::getJobToProcess( JobFunction &job )
{
	CriticalSection::ScopeLock sl(m_funsLock);
	if(m_signal.waitSignal(500))
	{
		job = m_funs.front();
		m_funs.pop();
		return true;
	}
	return false;
}


inline void JuThreadPool::waitJobComplete()
{
	CriticalSection::waitForValueEqual(&m_nCurJobs,0);
}

#endif //_JUTHREADPOOL_H_