#include "../ServerCommon/ServerCommon.h"

int addressPort = 80;
char webAddressIP[BUFFERSIZE] = { 0 };
char webAddressPath[BUFFERSIZE] = { 0 };
char webAddressPara[BUFFERSIZE] = { 0 };
char webAddressPort[BUFFERSIZE] = { 0 };
char requestWebAddress[BUFFERSIZE] = { 0 };

/*
***********************************************************
*
*	函数名	: initWebAddress
*	功能	: 初始化网址的各个模块
*	参数	: 无
*	返回值	: 无
*
***********************************************************
*/
void initWebAddress(void)
{
	// 解析出访问地址的各个部分
	bool isSuccess = false;
	isSuccess = ResolveIP(requestWebAddress, webAddressIP);
	if (isSuccess == false) {
		strcpy(webAddressIP, "192.168.1.1");
	}
	isSuccess = ResolvePort(requestWebAddress, webAddressPort);
	if (isSuccess == false) {
		strcpy(webAddressPort, "80");
		addressPort = atoi(webAddressPort);
	}
	isSuccess = ResolvePath(requestWebAddress, webAddressPath);
	if (isSuccess == false) {
		strcpy(webAddressPath, "/index.html");
	}
	isSuccess = ResolveParameter(requestWebAddress, webAddressPara);
	if (isSuccess == false) {
		strcpy(webAddressPara, "addid=remoteDo");
	}
}

/*
***********************************************************
*
*	函数名	: makeMessage
*	功能	: 制作要发送给mfc的报文
*	参数	: 
				【in】requestWay   : 用户使用的请求方式：例如GET或POST
				【in】contentType   : 用户要请求的类型：例如text/html
				【out】message   : 做成的报文
*	返回值	: 无
*
***********************************************************
*/
void makeMessage(char* requestWay, char* contentType, char* message)
{
	// 制作报文信息
	memset(message, 0, BUFFERSIZE);
	if (strcmp(requestWay, REQUEST_POST) == 0) {
		sprintf(message, "%s %s HTTP/1.1\n", requestWay, webAddressPath);
	} else {
		sprintf(message, "%s %s HTTP/1.1\n", requestWay, requestWebAddress);
	}

	sprintf(message, "%sHost: %s\n", message, webAddressIP);
	sprintf(message, "%sContent-Type: %s\n", message, contentType);
	strcat(message, "Upgrade-Insecure-Requests: 1\n");
	strcat(message, "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/66.0.3359.181 Safari/537.36\n");
	strcat(message, "Accept-: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8\n");
	strcat(message, "Accept-Encoding: gzip, deflate\n");
	strcat(message, "Accept-Language: zh-CN,zh;q=0.9,en-US;q=0.8,en;q=0.7\n");
	if (strcmp(requestWay, REQUEST_POST) == 0) {
		sprintf(message, "%sContent-Length: %s\n", message, strlen(webAddressPara));
		strcat(message, "\n\n");
		strcat(message, webAddressPara);
	}
	strcat(message, "\r\n\r\n");
	printf("\n");
}

/*
***********************************************************
*
*	函数名	: doRequest
*	功能	: 向定义的目标主机发送get请求
*	参数	: 
				【in】requestWay   : 用户使用的请求方式：例如GET或POST
				【in】contentType   : 用户要请求的类型：例如text/html
				【in】keepRecive   : 用户是否要在发送结束后继续监听返回的数据
*	返回值	: 【ret】isSuccess : 是否成功
*
***********************************************************
*/
bool doRequest(char* requestWay, char* contentType, bool keepRecive)
{
	fd_set t_setFd;
	bool isSuccess;
	struct timeval timeValue;
	struct sockaddr_in servaddr;
	int sockfd = 0, ret = 0, i = 0, exceptionId = 0;
	char message[BUFFERSIZE] = { 0 }, lineBuffer[BUFFERSIZE] = { 0 };

	// 创建一个Socket套接字
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("ERROR : Can't create socket !\n");
		return false;
	};

	// 初始化IP地址结构
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(addressPort);

	// 绑定套接字与IP地址结构
	if (inet_pton(AF_INET, webAddressIP, &servaddr.sin_addr) <= 0) {
		printf("ERROR : Can't bind socket !\n");
		return false;
	};

	// 尝试与服务器进行连接
	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		printf("ERROR : Can't connect target !\n");
		return false;
	}

	makeMessage(requestWay, contentType, message);
	printf("TIP : Send message : \n%s\n", message);

	// 发送报文信息
	ret = write(sockfd, message, strlen(message));
	if (ret < 0) {
		printf("ERROR : Request message send failure ! CODE[%d]，MSG[%s] .\n", errno, strerror(errno));
		return false;
	}
	else {
		printf("TIP : Request send %d byte . \n\n", ret);
	}

	FD_ZERO(&t_setFd);
	FD_SET(sockfd, &t_setFd);

	// 如果用户不需要再获得服务器返回的消息则提前结束
	if (keepRecive != true) {
		close(sockfd);
		return true;
	}

	// 开始读取EWS服务器发过来的信息
	printf("TIP : Receive message : \n");
	while (true) {
		sleep(2);
		timeValue.tv_sec = 0;
		timeValue.tv_usec = 0;
		exceptionId = 0;
		exceptionId = select(sockfd + 1, &t_setFd, NULL, NULL, &timeValue);

		if (exceptionId < 0) {
			printf("...\n");
			printf("ERROR : Select a exception, over the thread ! \n");
			close(sockfd);
			return false;
		};

		if (exceptionId > 0) {
			memset(lineBuffer, 0, BUFFERSIZE);
			i = read(sockfd, lineBuffer, BUFFERSIZE);
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
	return true;
}