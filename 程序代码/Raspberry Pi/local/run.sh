#!/bin/sh
gcc ComCommon/ComCommon.c UserKeyword/CommonKeyword.c WebServer/getRequest.c MainCommon/MainCommon.c SourceMain.c -o voicePrinter
./voicePrinter