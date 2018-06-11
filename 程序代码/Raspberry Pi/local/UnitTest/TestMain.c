#include "../Thread/Listener/ThreadListerner.h"

int main()
{
	int isSuccess = 0;

	isSuccess = createWebListener(true);
	if (isSuccess == false) {
		printf("ERROR : Create web listener thread failue !\n");
	}

	// 睡眠20秒，用来设置参数
	sleep(20);

	cancelWebListerner();
	initWebAddress();
	isSuccess = doRequest(REQUEST_GET, CONTENT_TYPE_HTML, false);
	if (isSuccess == false) {
		printf("ERROR : Send <GET> request failue !\n");
	}

	isSuccess = createWebListener(true);
	if (isSuccess == false) {
		printf("ERROR : Create web listener thread failue !\n");
	}
	pthread_join(webListernerThreadId, NULL);
	return 0;
}