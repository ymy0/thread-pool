
/**********************
** FileName: Service.cpp
** Dscribe: 服务端程序
** Date:2018.7.19
** @author: xionglei
***/



#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <assert.h>
#include "Thread.h"
//#include "BookInfo.h"
//#include "StrInfo.h"

class CMyTask : public Task
{
public:
	CMyTask() = default;
	int run()
	{
		//printf("%s\n", (char*)m_ptrData);
		//int x = rand()%4 + 1;
		//sleep(x);   
		//return 0;

		int connfd = get_id();
		while (1)
		{
			char recvbuf[1024];
			char sendbuf[1024];
			// Book book= new Book;

			 //BookInfo bf=book.find_book("茶花女");
			 //sprintf(sendbuf,"res: %d,%s",bf.book_no,bf.book_name);

			memset(recvbuf, 0x00, sizeof(recvbuf));
			memset(sendbuf, 0x00, sizeof(sendbuf));

			//printf("function run test.\n");
			int len = recv(connfd, recvbuf, sizeof(recvbuf), 0);
			if (len <= 0)
				printf("no buf.\n");
			printf("%s \n", recvbuf);
			printf("Please input: ");
			fflush(stdout);
			fgets(sendbuf, 1024, stdin);
			if (strncmp(sendbuf, "end", 3) == 0)
			{
				close(connfd);
				break;
			}
			send(connfd, sendbuf, sizeof(sendbuf), 0);

		}
		close(connfd);
		return 0;
	}
};





int main(int argc, char* argv[])
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	assert(sockfd != -1);
	struct sockaddr_in ser, cli;
	memset(&ser, 0, sizeof(ser));
	ser.sin_family = AF_INET;
	inet_aton("127.0.0.1", &ser.sin_addr);
	ser.sin_port = htons(6500);

	int res = bind(sockfd, (struct sockaddr*) & ser, sizeof(ser));
	assert(res != -1);

	listen(sockfd, 5);
	//创建线程池
	ThreadPool Pool(5);

	//for(int i=0;i<5;i++)
	//{
	  // Task* ta=new Task;
	   //Pool.AddTask(ta);
	//}

	while (1)
	{
		socklen_t len = sizeof(cli);
		int connectfd = accept(sockfd, (struct sockaddr*) & cli, &len);
		if (connectfd < 0)
		{
			printf("cli connect failed.");
			// throw  std::exception();

		}
		//收到客户端请求，即添加到任务队列去
		else
		{
			Task* ta = new CMyTask;
			ta->set_id(connectfd);
			Pool.add_task(ta);
		}



	}
	close(sockfd);
	return 0;


}


