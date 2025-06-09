#include "nlogging.h"


logCallBack debugCallBackFunc = nullptr;
logCallBack warnCallBackFunc = nullptr;
logCallBack errorCallBackFunc = nullptr;
bool isDebug = false;

bool is_debug()
{
    return isDebug;
}

void set_is_debug(bool debug)
{
    isDebug = debug;
}
