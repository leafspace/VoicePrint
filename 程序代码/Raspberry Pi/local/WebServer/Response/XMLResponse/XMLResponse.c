#include "../../ServerCommon/ServerCommon.h"

/*
***********************************************************
*
*	函数名	: XMLResponse
*	功能	: 向请求服务的服务器发送xml文件数据
*	参数	: 无
*	返回值	: 【ret】isSuccess : 是否成功
*
***********************************************************
*/
bool XMLResponse(void)
{
    struct sockaddr_in server_addr;
    char message[BUFFERSIZE] = { 0 };
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(addressPort);
    
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    
    listen(server_socket, 5);
    
    int client_socket = accept(server_socket, NULL, NULL);
    
    char buf[BUFFERSIZE];
    read(client_socket, buf, BUFFERSIZE);
    printf("TIP : Receve the request : \n%s\n", buf);


    memset(message, 0, BUFFERSIZE);
    strcat(message, "HTTP/1.0 200 OK\r\n");
    strcat(message, "Server: DWBServer\r\n");
    strcat(message, "Content-Type: text/xml;charset=utf-8\r\n\r\n");
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
    close(server_socket);

    return true;
}