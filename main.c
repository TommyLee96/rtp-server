#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Utils.h"
#include "RTPEnc.h"
#include "Network.h"

int main() {

    int len = 0;
    int res;
    uint8_t *stream = NULL;
    const char *fileName = "../Sample.h264";

    RTPMuxContext rtpMuxContext;//rtp包
    UDPContext udpContext = {.dstIp = "192.168.31.242",.dstPort = 1234};

    res = readFile(&stream, &len, fileName);
    if (res){
        printf("读取失败.\n");
        return -1;
    }

    res = udpInit(&udpContext);
    if (res){
        printf("初始化UDP socket.\n");
        return -1;
    }

    initRTPMuxContext(&rtpMuxContext);
    rtpSendH264HEVC(&rtpMuxContext, &udpContext, stream, len);

    free(stream);

    return 0;
}