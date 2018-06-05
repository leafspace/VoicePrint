#include "ServerCommon.h"

int getRequest(void)
{
	int sockfd, ret, i, h;
	struct sockaddr_in servaddr;
	char str1[4096], str2[4096], buf[BUFSIZE], *str;
	socklen_t len;
	fd_set t_set1;
	struct timeval  tv;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		exit(0);
	};

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	if (inet_pton(AF_INET, IPSTR, &servaddr.sin_addr) <= 0) {
		exit(0);
	};

	if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
		exit(0);
	}
	
	//memset(str2, 0, 4096);
	//strcat(str2, "theDataToPost");
	//str = (char *)malloc(128);
	//len = strlen(str2);
	//sprintf(str, "%d", len);

	memset(str1, 0, 4096);
	strcat(str1, "GET /ymnets/p/6255674.html HTTP/1.1\n");
	strcat(str1, "Host: www.cnblogs.com\n");
	strcat(str1, "Content-Type: text/html\n");
	//strcat(str1, "Content-Length: ");
	//strcat(str1, str);
	strcat(str1, "\n\n");

	//strcat(str1, str2);
	//strcat(str1, "\r\n\r\n");
	printf("%s\n", str1);

	ret = write(sockfd, str1, strlen(str1));
	if (ret < 0) {
		printf("发送失败！错误代码是%d，错误信息是'%s'\n", errno, strerror(errno));
		exit(0);
	}
	else {
		printf("消息发送成功，共发送了%d个字节！\n\n", ret);
	}
	close(sockfd);
	return 0;
}