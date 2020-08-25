#ifndef __THREAD_H
#define __THREAD_H

/*
	filename:Thread.h
	author:ymy
*/

#include<deque>
#include<pthread.h>
#include<string>
using namespace std;
class Task
{
	protected:
		string task_name;
		int task_id;
	
	public:
		Task() = default;
		Task(string &task_name):task_name(task_name),task_id(0){}
		virtual int run()=0;
		void set_id(int id);
		int get_id();
		virtual ~Task(){}
};

class ThreadPool
{
	private:
		static deque<Task*> task_list;
		static bool shutdown;//线程退出标志
		int thread_num;
		pthread_t *pthread_id;
		 
		static pthread_mutex_t mutex;
		static pthread_cond_t condition;
	
	protected:
		static void* call_back(void* data);
		static int move_to_idle(pthread_t tid);
		static int move_to_busy(pthread_t tid);
		int create();
	public:
		ThreadPool(int thread_number=10);
		int add_task(Task *task);
		int stop_all();
		int get_task_size();

};

#endif
