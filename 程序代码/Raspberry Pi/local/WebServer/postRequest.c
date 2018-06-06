#include "ServerCommon.h"

#define IPSTR "10.244.4.27"
#define PORT 80
#define BUFSIZE 4096

/*
***********************************************************
*
*	函数名	: postRequest
*	功能	: 向定义的目标主机发送post请求
*	参数	: 无
*	返回值	: 【ret】isSuccess : 是否成功
*
***********************************************************
*/
int postRequest(void)
{
	fd_set t_setFd;
	struct timeval tv;
	int sockfd = 0, ret = 0, i = 0, exceptionId = 0;
	struct sockaddr_in servaddr;
	char message[BUFSIZE] = { 0 }, lineBuffer[BUFSIZE] = { 0 };

	// 创建一个Socket套接字
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("ERROR : Can't create socket !\n");
		return -1;
	};

	// 初始化IP地址结构
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);

	// 绑定套接字与IP地址结构
	if (inet_pton(AF_INET, IPSTR, &servaddr.sin_addr) <= 0) {
		printf("ERROR : Can't bind socket !\n");
		return -1;
	};

	// 尝试与服务器进行连接
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		printf("ERROR : Can't connect target !\n");
		return -1;
	}

	// 制作报文信息
	memset(message, 0, BUFSIZE);
	strcat(message, "POST /openinterface/kickapp HTTP/1.1\n");
	strcat(message, "Host: 10.244.4.27\n");
	strcat(message, "Content-Type: text/html\n");
	strcat(message, "Upgrade-Insecure-Requests: 1\n");
	strcat(message, "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.181 Safari/537.36\n");
	strcat(message, "Accept-: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\n");
	strcat(message, "Accept-Encoding: gzip, deflate\n");
	strcat(message, "Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7\n");
	strcat(message, "Content-Length: 11\n");                                // 11指的是参数的长度
	strcat(message, "\n\n");
	strcat(message, "appid=iojob");
	strcat(message, "\r\n\r\n");
	printf("\n");
	printf("TIP : Send message : \n%s\n", message);

	// 发送报文信息
	ret = write(sockfd, message, strlen(message));
	if (ret < 0) {
		printf("ERROR : Request message send failure ! CODE[%d]，MSG[%s] .\n", errno, strerror(errno));
		return -1;
	}
	else {
		printf("TIP : Request send %d byte . \n\n", ret);
	}

	FD_ZERO(&t_setFd);
	FD_SET(sockfd, &t_setFd);

	// 开始读取EWS服务器发过来的信息
	printf("TIP : Receive message : \n");
	while (1) {
		sleep(2);
		tv.tv_sec = 0;
		tv.tv_usec = 0;
		exceptionId = 0;
		exceptionId = select(sockfd + 1, &t_setFd, NULL, NULL, &tv);

		if (exceptionId < 0) {
			printf("...\n");
			printf("ERROR : Select a exception, over the thread ! \n");
			close(sockfd);
			return -1;
		};

		if (exceptionId > 0) {
			memset(lineBuffer, 0, BUFSIZE);
			i = read(sockfd, lineBuffer, BUFSIZE);
			if (i == 0) {
				printf("...\n");
				printf("TIP : Link over ! \n");
				break;
			}
			printf("%s", lineBuffer);
		}
	}
	printf("\n");
	close(sockfd);
	return 0;
}