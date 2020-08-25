#include "Thread.h"
#include<iostream>

//using namespace std;

void Task::set_id(int id)
{
	task_id=id;

}

int Task::get_id()
{
	return task_id;
}

deque<Task*> ThreadPool::task_list;
bool ThreadPool::shutdown=false;

pthread_mutex_t ThreadPool::mutex = PTHREAD_MUTEX_INITIALZER;
pthread_cond_t ThreadPool::condition= PTHREAD_COND_INITIALZER;

ThreadPool::ThreadPool(int thread_number)
{
	this->thread_num=thrad_number;
	cout<<"I will create "<<thread_num<<" threads"<<endl;
	create();
}

voide* ThreadPool::call_back(void* data)
{
	pthread_tid = pthread_self();
	while(1)
	{
		pthread_mutex_lock(&mutex);
		while(task_list.size()==0&&!shutdown)
		{
			pthread_cond_wait(&condition,&mutex);
			
		}
		if(shutdown)
		{
			pthread_mutex_unlock(&mutex);
			printf("thread_%lu will exit",pthread_self());
			pthread_exit(NULL);
		}
		printf("tid %lu run\n", tid);  
		
		Task* task = task_list.front();
		task_list.pop_front();

		task->run();
	}
	return (void*)0;
}

int ThreadPool::add_task(Task* task)
{
	pthread_mutex_lock(&mutex);
	task_list.push_back(task);
	pthread_mutex_unlock(&mutex);
	
	pthread_cond_signal(&condition);
	return 0;
		
}

int ThreadPool::create()
{
	pthread_id = (pthread_t*)malloc(sizeof(pthread_t)* thread_num);
	
	for(int i=0;i<thread_num;i++)
	{
		pthread_create(&pthread_id[i],NULL,call_back,NULL);
	}
	return 0;
}

int Thread::pool::stop_all()
{
	if(shutdown)
	{
		return -1;
	}
	printf("END ALL THREADS!!!\n");

	shutdown=true;
	pthread_cond_broadcast(&condition);
	
	for(int i=0;i<thread_num;i++)
	{
		pthread_join(pthread_id[i],NULL);
	}
	
	free(pthread_id);
	pthread_id=NULL;

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&condition);
	return 0;
}


int CThreadPool::getTaskSize()  
{  
    return m_deqTaskList.size();      
}  

