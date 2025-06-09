#ifndef GSP_NLOGGING_H_
#define GSP_NLOGGING_H_

#include <string>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <fmt/color.h>
#include "stack_config.h"

using namespace std;

typedef void (*logCallBack)(const string &message);

extern logCallBack debugCallBackFunc;
extern logCallBack warnCallBackFunc;
extern logCallBack errorCallBackFunc;

bool is_debug();
void set_is_debug(bool debug);

inline void setDebugLogCallBack(logCallBack callBack)
{
    debugCallBackFunc = callBack;
}

inline void setWarnLogCallBack(logCallBack callBack)
{
    warnCallBackFunc = callBack;
}

inline void setErrorLogCallBack(logCallBack callBack)
{
    errorCallBackFunc = callBack;
}

#define NLOG_ERROR(...) {\
    if(errorCallBackFunc) \
    {\
        errorCallBackFunc(fmt::format(__VA_ARGS__));\
    }\
    else\
    {\
        string error = fmt::format(__VA_ARGS__);\
        error += "\n";\
        fmt::print(fg(fmt::color::crimson) | fmt::emphasis::bold, "{}", error);\
        assert(ERROR_JUST_LOG);\
    }\
}

#define NLOG_DEBUG(...) {\
    if(debugCallBackFunc) \
    {\
        debugCallBackFunc(fmt::format(__VA_ARGS__));\
    }\
    else\
    {\
        string error = fmt::format(__VA_ARGS__);\
        error += "\n";\
        fmt::print(fg(fmt::color::lime_green), "{}", error);\
    }\
}

#define NLOG_WARN(...) {\
    if(warnCallBackFunc) \
    {\
        warnCallBackFunc(fmt::format(__VA_ARGS__));\
    }\
    else\
    {\
        string error = fmt::format(__VA_ARGS__);\
        error += "\n";\
        fmt::print(fg(fmt::color::orange_red) | fmt::emphasis::bold, "{}", error);\
    }\
}
#endif
