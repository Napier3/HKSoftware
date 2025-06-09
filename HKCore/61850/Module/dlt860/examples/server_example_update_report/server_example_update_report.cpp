#include "dlt860_server_interface.h"
#include "gsp_hal_thread.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include "gsp_lib_memory.h"
#include "dlt860_client.h"
#ifdef __linux
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <execinfo.h>
#include <link.h>
#endif

/**
 * 服务端启动例子(报告更新值)
 */

#ifdef _MSC_VER
#include <Windows.h>
#endif

using namespace std;
static int running = 0;

// 异常堆栈信息记录
#ifdef __linux
void out_stack(const char *sig);

void signal_exit(int dunno)
{
    const char* signal_str = "";
    char dunno_str[10] = {0};
    sprintf(dunno_str, "%d", dunno);
    switch (dunno)
    {
    case 1:
        signal_str = "SIGHUP(1)";
        break;
    case 2:
        signal_str = "SIGINT(2:CTRL_C)"; //CTRL_C
        break;
    case 3:
        signal_str = "SIGQUIT(3)";
        break;
    case 6:
    {
        signal_str = "SIGABRT(6)";
        out_stack(signal_str);
    }
        break;
    case 9:
        signal_str = "SIGKILL(9)";
        break;
    case 15:
        signal_str = "SIGTERM(15 KILL)"; //kill
        break;
    case 11:
    {
        signal_str = "SIGSEGV(11)"; //SIGSEGV
        out_stack(signal_str);
    }
        break;
    default:
        signal_str = "OTHER";
        break;
    }
    running = 0;
}

static size_t convertToVma(size_t addr)
{
    Dl_info info;
    link_map* link_map;
    dladdr1((void*)addr,&info,(void**)&link_map,RTLD_DL_LINKMAP);
    return addr-link_map->l_addr;
}

void out_stack(const char *sig)
{
    pid_t pid = getpid();

    string stackFileName = "stack_info_" + std::to_string(pid) + ".log";

    auto stackFile = fopen(stackFileName.c_str(), "w+");
    void *array[128];
    char **strings;
    int i;

    fprintf(stackFile, "%s\n", sig);
    size_t size = backtrace (array, 128);
    strings = backtrace_symbols (array, size);
    if (NULL == strings)
    {
        fprintf(stackFile, "backtrace_symbols\n");
        return ;
    }

    for (i = 0; i < size; i++)
    {
        char location[1024];
        Dl_info info;
        if(dladdr(array[i],&info))
        {
            // use addr2line; dladdr itself is rarely useful (see doc)
            char command[256];
            fprintf(stackFile, strings[i]);
            size_t vmaAddr = convertToVma((size_t)array[i]);
            vmaAddr-=1;
            snprintf(command,sizeof(command),"addr2line -e %s -Ci %zx",info.dli_fname,vmaAddr);

            char line[256];
            FILE *file = popen(command, "r");
            if(NULL != fgets(line, 256, file))
            {
                fprintf(stackFile, "%s\n", line);
            }
            pclose(file);
        }

        fprintf(stackFile, "%s",strings[i]);
    }

    free(strings);
    fclose(stackFile);
    exit(0);
}
#endif

void sigint_handler(int signalId)
{
#ifdef __linux
    signal_exit(signalId);
#endif
    running = 0;
}

int main(int argc, char** argv) {

#ifdef __linux
    signal(SIGHUP, sigint_handler);
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigint_handler);
    signal(SIGABRT, sigint_handler);
    signal(SIGKILL, sigint_handler);
    signal(SIGTERM, sigint_handler);
    signal(SIGSEGV, sigint_handler);
#endif
    const char *configPath = nullptr;
#ifdef _MSC_VER
    SetConsoleOutputCP(CP_UTF8);
#endif
    if(argc > 1)
    {
        configPath = argv[1];
    } else {
        return -1;
    }
    
    // 启动服务端
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    auto iedServer = GspIedServer_startWithJsonFile(configPath);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;

    // 服务状态判断
    if(!iedServer)
    {
        //NLOG_ERROR("基于[{}]创建服务端失败，请检查配置文件", configPath);
        return -1;
    }

    if(GspIedServer_isError(iedServer))
    {
        printf("启动服务失败，请检查网络配置.\n");
        GspIedServer_destroy(iedServer);
        exit(-1);
    }

    if (!GspIedServer_isRunning(iedServer)) {
        printf("服务未能正常启动.\n");
        GspIedServer_destroy(iedServer);
        exit(-1);
    }

    running = 1;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    using std::chrono::system_clock;
    while (running) {

#if defined(__linux__)
        try{
            /************************** 报告变动测试 ******************************/

            // 构造报告数据
            ReportPDU_t *report = (ReportPDU_t*)GspMemory_calloc(1, sizeof (ReportPDU_t));

            // 变动标记
            static int flag = 0;
            flag = !flag;

            // 要模拟的数据集的名字
            const char* dataSetStr = "P_L2211DLD0/LLN0.dsDeviceState";
            report->datSet = OCTET_STRING_new_fromBuf(&asn_DEF_OCTET_STRING, dataSetStr, strlen(dataSetStr));

            // 要模拟的报告条目
            ReportPDU__entry__entryData__Member *entry = (ReportPDU__entry__entryData__Member*)GspMemory_calloc(1, sizeof (ReportPDU__entry__entryData__Member));

            // 要模拟的数据条目ID
            entry->id = 1;

            // 要模拟的refs
            const char* refs = "P_L2211DLD0/StaGGIO2.Ind2";
            entry->reference = OCTET_STRING_new_fromBuf(&asn_DEF_ObjectReference, refs, strlen(refs));

            // 要模拟变动的数值
            auto itemValue = GspMmsValue_newBoolean(flag);
            auto q = GspMmsValue_newQuality();

            // 要模拟的时间
            milliseconds ms = duration_cast< milliseconds >( system_clock::now().time_since_epoch());
            auto t = GspMmsValue_newUtcTimeByMsTime(ms.count());

            // 要模拟的数据条目
            entry->value.present = Data_PR_structure;
            ASN_SEQUENCE_ADD(&entry->value.choice.structure.list, itemValue);
            ASN_SEQUENCE_ADD(&entry->value.choice.structure.list, q);
            ASN_SEQUENCE_ADD(&entry->value.choice.structure.list, t);
            ASN_SEQUENCE_ADD(&report->entry.entryData.list, entry);

            // 变动触发测试(id的更新方式)
            auto t1 = high_resolution_clock::now();
            GspServer_updateDataSetValue(iedServer, *report, true);
            auto t2 = high_resolution_clock::now();
            auto ms_int = duration_cast<milliseconds>(t2 - t1);
            std::cout << "报告数据变动测试:" << report->datSet->buf << " " << flag << " 花费时间:" << ms_int.count() << "ms" << std::endl;

            // 休眠时间
            GspThread_sleep(3000);

            // 报告资源释放
            Gsp_Report_Destory(report);

        } catch(const exception& error){
            printf("自动变换测试出错:%s\n", error.what());
            GspThread_sleep(1000);
        }
#endif
    }

    // 停止服务关闭所有链接
    GspIedServer_stop(iedServer);

    // 清理资源
    GspIedServer_destroy(iedServer);
    return 0;
} /* main() */
