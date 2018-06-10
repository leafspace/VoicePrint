#include "ResponseCommon.h"
#include "../ServerCommon/ServerCommon.h"


/*
***********************************************************
*
*	函数名	: resolveMessage
*	功能	: 解析对象请求的报文
*	参数	: 
				【in】message   : 做成的报文
				【out】contentType   : 用户要请求的类型：例如text/html
				【out】requestPath   : 用户要请求的文件路径
*	返回值	: 无
*
***********************************************************
*/
void resolveMessage(char* message, char* contentType, char* requestPath)
{
    strcpy(contentType, CONTENT_TYPE_HTML);
    strcpy(requestPath, "../web/web/index.html");

    int i = 0;
    char *requestPathBeginPosition = NULL, *requestPathEndPosition = NULL;
    // 获取客户端请求的文件路径
    if ((requestPathBeginPosition = strstr(message, "GET")) == NULL) {
        if ((requestPathBeginPosition = strstr(message, "POST")) != NULL) {
            requestPathBeginPosition = requestPathBeginPosition + 5;    
        }
    } else {
        requestPathBeginPosition = requestPathBeginPosition + 4;
    }

    if ((requestPathEndPosition = strstr(message, "HTTP/")) != NULL) {
        requestPathEndPosition = requestPathEndPosition - 1;
    }
    
    // 如果取得的地址都成功
    if (requestPathBeginPosition && requestPathEndPosition) {
        for (i = 0; (requestPathBeginPosition + i) < requestPathEndPosition; ++i) {
            requestPath[i] = *(requestPathBeginPosition + i);
        }
        requestPath[i] = 0;

        if (strcmp(requestPath, "/") == 0) {
            strcpy(requestPath, "/index.html");
        }
        
        char fileContentType[BUFFERSIZE] = { 0 };
        char *tempBeginPosition = NULL, *tempEndPosition = NULL;
        strcpy(fileContentType, requestPath);
        tempBeginPosition = fileContentType;
        
        // 开始获取该文件类型
        tempBeginPosition = strstr(tempBeginPosition, ".") + 1;
        if ((tempEndPosition = strstr(tempBeginPosition, "?")) == NULL) {
            tempEndPosition = tempBeginPosition + strlen(tempBeginPosition);
        } else {
            tempEndPosition = tempEndPosition - 1;
        }

        for (i = 0; (tempBeginPosition + i) <= tempEndPosition; ++i) {
            fileContentType[i] = *(tempBeginPosition + i);
        }
        fileContentType[i] = 0;

        for (i = 0; i < CONTENT_TYPESIZE; ++i) {
            if (strncasecmp(fileContentType, contentTypeListReal[i], strlen(fileContentType)) == 0) {
                strcpy(contentType, contentTypeListDefine[i]);
                break;
            }
        }
    }

    char tempBuffer[BUFFERSIZE] =  { 0 };
    strcpy(tempBuffer, "../web/web");
    strcat(tempBuffer, requestPath);
    strcpy(requestPath, tempBuffer);

    printf("TIP : Resolve content type is [%s] . \n", contentType);
    printf("TIP : Resolve request path is [%s] . \n", requestPath);
}

/*
***********************************************************
*
*	函数名	: makeMessageHead
*	功能	: 制作要发送给mfc的报文
*	参数	: 
				【in】contentType   : 用户要请求的类型：例如text/html
				【out】message   : 做成的报文
*	返回值	: 无
*
***********************************************************
*/
void makeMessageHead(char* contentType, char* message)
{
	// 制作报文信息
	strcat(message, "HTTP/1.0 200 OK\r\n");
    strcat(message, "Server: DWBServer\r\n");
    sprintf(message, "%sContent-Type: %s;charset=utf-8\r\n\r\n", message, contentType);
}

/*
***********************************************************
*
*	函数名	: doResponse
*	功能	: 响应浏览器发送过来的请求
*	参数	: 
				【in】keepListern   : 用户是否要要在响应一次请求之后持续监听
*	返回值	: 【ret】isSuccess : 是否成功
*
***********************************************************
*/
bool doResponse(bool keepListern)
{
    struct sockaddr_in server_addr;
    char message[BUFFERSIZE] = { 0 };

    // 创建服务器socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // 创建服务器ip结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(addressPort);
    
    // 绑定服务器socket与ip结构
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    // 开始监听socket
    listen(server_socket, SIGNALVALUE);

    do {
        memset(message, 0, BUFFERSIZE);
        int client_socket = accept(server_socket, NULL, NULL);
        
        // 读取对象发过来的报文信息
        read(client_socket, message, BUFFERSIZE);
        printf("TIP : Receve the request : \n%s\n", message);
        char contentType[BUFFERSIZE], requestPath[BUFFERSIZE];
        resolveMessage(message, contentType, requestPath);

        // 制作将要返回的电文头信息
        memset(message, 0, BUFFERSIZE);
        makeMessageHead(contentType, message);
        write(client_socket, message, strlen(message));
        printf("%s\n", message);

        // 发送请求的path地址的数据
        FILE *fp = fopen(requestPath, "rb");
        if (fp == NULL) {
            printf("ERROR : [%s] Can't find this file ! \n", requestPath);
            continue;
        }

        do {
            int readNumber = fread(message, sizeof(char), BUFFERSIZE, fp);
            write(client_socket, message, readNumber);
            if (strncasecmp(contentType, "text", 4) == 0) {
                printf("%s", message);
            }
        } while (!feof(fp));
        printf("\n");
        close(client_socket);
    } while(keepListern);

    close(server_socket);

    return true;
}