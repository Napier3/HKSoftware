# gsp 开发者手册

## 1. 基本信息

|信息项|描述信息|
|:------|:------|
|开发包版本|V1.0.32|
|最后修改时间|2021-05-23|
|开发者系统|debian 10 或者 window 10|
|开发者cmake版本|3.13.4|
|支持最小cmake版本|2.8.12|
|开发者编译器版本|8.3.0 或者 msvc2017|

## 2. 接口目前支持情况

|服务码|所属模块|接口名字|服务端实现情况|客户端实现情况|
|:------|:------|:------|:------:|:------:|
|1|关联服务|Associate|已实现|已实现|
|2|关联服务|Abort|已实现|已实现|
|3|关联服务|Release|已实现|已实现|
|80|模型和数据服务|GetServerDirectory|已实现|已实现|
|81|模型和数据服务|GetLogicDeviceDirectory|已实现|已实现|
|82|模型和数据服务|GetLogicNodeDirectory|已实现|已实现|
|83|模型和数据服务|GetAllDataValues|已实现|已实现|
|155|模型和数据服务|GetAllDataDefinition|已实现|已实现|
|156|模型和数据服务|GetAllCBValues|已实现|已实现|
|48|模型和数据服务|GetDataValues|已实现|已实现|
|49|模型和数据服务|SetDataValues|已实现|已实现|
|50|模型和数据服务|GetDataDirectory|已实现|已实现|
|51|模型和数据服务|GetDataDefinition|已实现|已实现|
|54|数据集服务|CreateDataSet|已实现|暂未实现|
|55|数据集服务|DeleteDataSet|已实现|暂未实现|
|57|数据集服务|GetDataSetDirectory|已实现|已实现|
|58|数据集服务|GetDataSetValues|已实现|已实现|
|59|数据集服务|SetDataSetValues|已实现|暂未实现|
|68|控制服务|Select|已实现|已实现|
|69|控制服务|SelectWithValue|已实现|已实现|
|70|控制服务|Cancel|已实现|已实现|
|71|控制服务|Operate|已实现|已实现|
|72|控制服务|CommandTermination|暂未实现|暂未实现|
|73|控制服务|TimeActivatedOperate|暂未实现|暂未实现|
|74|控制服务|TimeActivatedOperateTermination|暂未实现|暂未实现|
|84|定值组服务|SelectActiveSG|已实现|已实现|
|85|定值组服务|SelectEditSG|已实现|已实现|
|86|定值组服务|SetEditSGValue|已实现|已实现|
|87|定值组服务|ConfirmEditSGValues|已实现|已实现|
|88|定值组服务|GetEditSGValue|已实现|已实现|
|89|定值组服务|GetSGCBValues|已实现|已实现|
|90|报告服务|Report|已实现|已实现|
|91|报告服务|GetBRCBValues|已实现|已实现|
|92|报告服务|SetBRCBValues|已实现|已实现|
|93|报告服务|GetURCBValues|已实现|已实现|
|94|报告服务|SetURCBValues|已实现|已实现|
|95|日志服务|GetLCBValues|暂未实现|暂未实现|
|96|日志服务|SetLCBValues|暂未实现|暂未实现|
|97|日志服务|QueryLogByTime|暂未实现|暂未实现|
|98|日志服务|QueryLogAfter|暂未实现|暂未实现|
|99|日志服务|GetLogStatusValues|暂未实现|暂未实现|
|102|GOOSE 控制块服务|GetGoCBValues|暂未实现|暂未实现|
|103|GOOSE 控制块服务|SetGoCBValues|暂未实现|暂未实现|
|105|SMV 控制块服务|GetMSVCBValues|暂未实现|暂未实现|
|106|SMV 控制块服务|SetMSVCBValues|暂未实现|暂未实现|
|128|文件服务|GetFile|已实现|已实现|
|129|文件服务|SetFile|已实现|已实现|
|130|文件服务|DeleteFile|已实现|已实现|
|131|文件服务|GetFileAttributeValues|已实现|已实现|
|132|文件服务|GetFileDirectory|已实现|已实现|
|110|远程过程调用|GetRpcInterfaceDirectory|已实现|已实现|
|111|远程过程调用|GetRpcMethodDIrectory|已实现|已实现|
|112|远程过程调用|GetRpcInterfaceDefinition|已实现|已实现|
|113|远程过程调用|GetRpcMethodDefinition|已实现|已实现|
|114|远程过程调用|RpcCall|已实现|已实现|
|153|测试|Test|已实现|已实现|
|154|关联协商|AssociateNegotiate|已实现|已实现|

## 3. 结构说明

```
    .
    ├── 3rd_lib(源码类的三方库)
    ├── CMakeLists.txt(项目工程文件)
    ├── conf(服务端配置)
    ├── config(客户端配置)
    ├── doc(文档手册)
    ├── examples(测试用例)
    ├── gui(图形化程序)
    ├── hal(平台抽象代码)
    ├── README.md(自述文件)
    ├── scd(测试SCD文件)
    ├── scripts(脚本)
    ├── sdk_release(SDK包)
    ├── src(逻辑类源码)
    ├── swig(python封装)
    ├── third_party(库文件类三方)
    └── tools(编辑器源码)
```

## 4. 服务端使用示例

详见examples 中 server 关键字

配置文件示例`server.json`

```json
{
    // 模型文件绝对路径
    "model": "/root/code/ngsp/scd/GWZK220.scd",
    // 文件服务映射根目录
    "file_root": "/tmp",
    // 定值存储位置
    "sg_storage": "/tmp/sg1.db",
    // 服务网络信息
    "network": {
        "bind": "0.0.0.0",
        "port": 8102
    }
}
```

## 5. 客户端使用示例

详见example 中 client 关键字中的例子

编译采用标准的cmake编译流程

修改定值示例代码:

```c++
#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>
#include "gsp_hal_thread.h"
#include <unistd.h>
#include "gsp_lib_memory.h"
#include "../config/example_config.h"


int main(int argc, char** argv) {

    char* hostname;
    int tcpPort = 8102;

    if (argc > 1) {
        hostname = argv[1];
    } else {
        hostname = HOSTNAME;
    }

    if (argc > 2)
        tcpPort = atoi(argv[2]);

    // 创建链接
    GspIedClientError error;
    GspIedConnection con = Gsp_IedConnection_Create();

    // 链接到服务器
    Gsp_IedConnection_Connect(con, &error, hostname, tcpPort);
    if (error == GSP_IED_ERROR_OK) {
        printf("链接到服务端成功\n");
    } else {
        printf("链接到服务端失败\n");

        // 销毁链接
        Gsp_IedConnection_Destroy(con);
        return -1;
    }

    // 发生关联
    Gsp_IedConnection_Associate(con, &error, "S1");

    // 定值修改业务流 001 -> 选择编辑定值组
    uint8_t testDemoNum = 2;
    const char* testSgcbRefs = "PE1001PROT/LLN0.SGCB";
    bool ret = Gsp_IedConnection_SelectEditSG(con, &error, testSgcbRefs, testDemoNum);

    // 调试信息
    if(ret){
        printf("****************** 选择编辑定值区成功，切换到 %d 区。\n", testDemoNum);
    } else {
        printf("****************** 选择编辑定值区失败，切换到 %d 区。失败, 错误代码: %d \n", testDemoNum, error);
    }

    // 读定值控制块的值
    char* testSGRefList[3] = {
        "PE1001PROT/phPTOC1.StrVal",
        "PE1001PROT/phPTOC1.Enable",
        "PE1001PROT/phPTOC1.OpDlTmms"
    };

    GspLinkedList demoSgRefList = GspLinkedList_create();

    // 定值01
    RefsFC tmpRefs01 = (RefsFC)GspMemory_calloc(1, sizeof(struct sRefsFc));
    tmpRefs01->fc = "SG";
    tmpRefs01->objRefs = testSGRefList[0];
    GspLinkedList_add(demoSgRefList, tmpRefs01);

    // 定值02
    RefsFC tmpRefs02 = (RefsFC)GspMemory_calloc(1, sizeof(struct sRefsFc));
    tmpRefs02->fc = "SG";
    tmpRefs02->objRefs = testSGRefList[1];
    GspLinkedList_add(demoSgRefList, tmpRefs02);

    // 定值03
    RefsFC tmpRefs03 = (RefsFC)GspMemory_calloc(1, sizeof(struct sRefsFc));
    tmpRefs03->fc = "SG";
    tmpRefs03->objRefs = testSGRefList[2];
    GspLinkedList_add(demoSgRefList, tmpRefs03);

    // 定值修改业务流 002 -> 读定值操作
    GspLinkedList sgvalues = Gsp_IedConnection_GetEditSGValue(con, &error, demoSgRefList);

    // 打印测试
    if(sgvalues){
        while (sgvalues->next) {
            sgvalues = sgvalues->next;
            GetEditSGValueResponsePDU_t* tmpSgItem = (GetEditSGValueResponsePDU_t*)sgvalues->data;
            for (int index=0; index<tmpSgItem->value.list.count; ++index) {
                GspMmsValue* sgValueItem = tmpSgItem->value.list.array[index];
                Data_PR dataType = GspMmsValue_getType(sgValueItem);
                switch (dataType) {
                case Data_PR_boolean:{
                    bool tmpValue = GspMmsValue_getBoolean(sgValueItem);
                    printf("读取到了 %s 的 bool 类型的定值: %d", testSGRefList[index], tmpValue);
                }
                    break;
                    // TODO 这里需要按照需求打印一些测试东西
                default:
                    printf("该种数据类型的定值, 在测试例子中没有进行解析 \n");
                }
            }
        }
    } else {
        printf("获取编辑区定值失败, 没有获取到数据\n");
    }

    // 写定值控制块的值
    GspLinkedList writeSgValues = GspLinkedList_create();

    // 修改 bool 类型的定值
    RefsData sgvalue = (RefsData)GspMemory_calloc(1, sizeof (sRefsData));
    sgvalue->objRefs = testSGRefList[1];
    sgvalue->data = GspMmsValue_newBoolean(true);

    GspLinkedList_add(writeSgValues, sgvalue);

    // 定值修改业务流 003 -> 写定值操作
    if(Gsp_IedConnection_SetEditSGValue(con, &error, writeSgValues)){
        printf("写定值成功!! \n");
    } else {
        printf("写定值失败!! \n");
    }

    // 定值修改业务流 004 -> 确认定值修改操作
    if(Gsp_IedConnection_ConfirmEditSGValues(con, &error, testSgcbRefs)){
        printf("确认写定值成功!! \n");
    } else {
        printf("确认写定值失败!! \n");
    }

    // 终止链接
    Gsp_IedConnection_Abort(con, &error, GSP_IED_ABORT_OTHER, "test");
}

```

示例 `example_config.h`

```c++
// 虚拟机测试
#define HOSTNAME "192.168.56.1"

// 鲁能智能设备
//#define HOSTNAME "172.20.0.156"

// 许继设备
//#define HOSTNAME "172.20.0.116"

// 南瑞设备
//#define HOSTNAME "172.20.5.2"

// 本地回环
//#define HOSTNAME "127.0.0.1"

#define PORT 8102

// 服务端测试配置文件
#define JSON_FILE "/root/code/ngsp/conf/server.json"
```