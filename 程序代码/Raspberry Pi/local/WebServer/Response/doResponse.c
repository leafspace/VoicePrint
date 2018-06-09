#include "ResponseCommon.h"
#include "../ServerCommon/ServerCommon.h"

/*
***********************************************************
*
*	函数名	: makeMessage
*	功能	: 制作要发送给mfc的报文
*	参数	: 
				【in】contentType   : 用户要请求的类型：例如text/html
				【out】message   : 做成的报文
*	返回值	: 无
*
***********************************************************
*/
void makeMessage(char* contentType, char* message)
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
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(addressPort);
    
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    do {
        listen(server_socket, 5);
        memset(message, 0, BUFFERSIZE);
        int client_socket = accept(server_socket, NULL, NULL);
        
        read(client_socket, message, BUFFERSIZE);
        printf("TIP : Receve the request : \n%s\n", message);


        memset(message, 0, BUFFERSIZE);
        makeMessage(CONTENT_TYPE_XML, message);
        write(client_socket, message, strlen(message));

        printf("%s\n", message);
        FILE *fp = fopen("../web/web/xml/scan.xml", "rb");
        do {
            int readNumber = fread(message, sizeof(char), BUFFERSIZE, fp);
            if (readNumber != BUFFERSIZE) {
                printf("WARNING : May lose data when sending xml ! \n");
            }
            write(client_socket, message, readNumber);
            printf("%s", message);
        } while (!feof(fp));
        close(client_socket);
    } while(keepListern);

    close(server_socket);

    return true;
}