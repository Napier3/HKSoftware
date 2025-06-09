#ifndef GSP_SERVER_INTERFACE_H
#define GSP_SERVER_INTERFACE_H

#include "libdlt860_define.h"
#include "gsp_mms_value.h"
#include "dlt860_model.h"
#include "asn_inc.h"
#include <set>
#include <string>
#include <stdexcept>
#include <functional>

using namespace std;

#define GSP_Select 68
#define GSP_SelectWithValue 69
#define GSP_Cancel 70
#define GSP_Operate 71
#define GSP_CommandTermination 72
#define GSP_TimeActivatedOperate 73
#define GSP_TimeActivatedOperateTermination 74


struct sGspIedServer;
struct sGspClientConnection;

/**
 * @brief GspIedServer 服务对象指针
 */
typedef struct sGspIedServer* GspIedServer;

/**
 * @brief GspClientConnection 链接到服务端的客户端链接指针
 */
typedef struct sGspClientConnection* GspClientConnection;

/**
 * @brief GspIedServer_startWithJsonFile 启动服务
 * @param jsonFile 服务配置文件
 * @return 服务对象指针
 */
LIB860_API GspIedServer GspIedServer_startWithJsonFile (const char *configFilePath);
LIB860_API GspIedServer GspIedServer_startWithJsonAndModels(const char *configContent, GspIedModel **model, GspIedServer server);
/**
 * @brief GspIedServer_startWithJson 启动服务
 * @param configContnet 服务配置字符串
 * @return 服务对象指针
 */
LIB860_API GspIedServer GspIedServer_startWithJson (const char *configContnet);

/**
 * @brief GspIedServer_isRunning 服务运行状态判断
 * @param server 服务对象指针
 * @return 是否正在运行
 */
LIB860_API bool GspIedServer_isRunning(GspIedServer self);

/**
 * @brief GspIedServer_isError 服务运行错误判断
 * @param server服务对象指针
 * @return 是否在运行过程中存在错误
 */
LIB860_API bool GspIedServer_isError(GspIedServer self);

/**
 * @brief GspIedServer_destroy 服务销毁
 * @param server 服务对象指针
 */
LIB860_API void GspIedServer_destroy(GspIedServer self);

/**
 * @brief GspIedServer_stop 停止服务
 * @param self 服务对象指针
 */
LIB860_API void GspIedServer_stop(GspIedServer self);

/**
 * @brief GspIedServer_getReferValue 获取服务端模型中的值
 * @param server 服务对象指针
 * @param daRef DA 或者 DO 的refs
 * @param fc 功能约束
 * @return 获取到的数据值
 */
LIB860_API GspMmsValue *GspIedServer_getReferValue(GspIedServer server, const char *daRef, const char *fc);

/**
 * @brief GspIedServer_updateReferValue 更新服务端模型中的值
 * @param server 服务对象指针
 * @param daRef DA 或者 DO 的refs
 * @param fc 功能约束
 * @param value 将要更新的数据值
 */ 
LIB860_API void GspIedServer_updateReferValue(GspIedServer server, const char *daRef, const char *fc, GspMmsValue *value);
LIB860_API bool GspIedServer_updateReferValueByStr(GspIedServer server, const char *daRef, const char *fc, const char *value);
/**
 * @brief GspServer_updateDataSetValue 更新服务端模型中的值
 * @param server 服务对象指针
 * @param report 报告数据
 * @param paramMode 报告更新模式 0-ID的方式更新 1-refs的更新方式
 */
LIB860_API void GspServer_updateDataSetValue(GspIedServer server, const ReportPDU_t &report, bool paramMode);

/**
 * 服务端链接处理回调
 */
typedef void (*GspIedConnectionIndicationHandler) (GspIedServer self, GspClientConnection connection, bool connected, void* parameter);

/**
 * @brief GspIedServer_setConnectionIndicationHandler 设置服务端链接回调(当有新链接到来或者断开时回调对应的函数)
 * @param server 服务对象指针
 * @param handler 链接的回调函数
 * @param parameter 回调函数的参数
 */
LIB860_API void GspIedServer_setConnectionIndicationHandler(GspIedServer server, GspIedConnectionIndicationHandler handler, void* parameter);

/**
 * @brief GspClientConnection_getPeerAddress 获取客户端对端的地址和端口 （例如 192.168.175.133:2345）
 * @param self 客户端链接指针
 * @return 客户端链接信息
 */
LIB860_API const char* GspClientConnection_getPeerAddress(GspClientConnection self);

/**
 * @brief GspClientConnection_getLocalAddress 获取客户端的本端地址和端口 (例如: 17.0.0.1:1234)
 * @param self 客户端链接指针
 * @return 客户端链接信息
 */
LIB860_API const char* GspClientConnection_getLocalAddress(GspClientConnection self);

/**
 * @brief GspClientConnection_getSecurityToken 获取客户端的唯一 token 码
 * @param self 客户端链接指针
 * @return 唯一服务 token 码
 */
LIB860_API void* GspClientConnection_getSecurityToken(GspClientConnection self);

LIB860_API uint64_t GspClientConnection_getConnectID(GspClientConnection self);

/**
 * @brief GspIedServer_setIgnoreIeds 设置服务端模型不对外暴露的IED
 * @param iedNames IED名字列表
 */
LIB860_API void GspIedServer_setIgnoreIeds(const set<string> &iedNames);

/*
 * 参数
 *  server： 服务对象
 *  clientConn: 客户端连接对象（目前仅可以用来获取对应ip，判断客户端唯一标识）
 *  request: 请求原始报文
 *  type: 请求类型
 *  param: 自定义参数
 *  response: 正常时，如不需要再执行服务端逻辑，需要直接返回，则返回正常回应报文，如需要继续执行，则返回nullptr，
 *            异常时，请直接返回对应错误信息报文数据，将会直接发出
 * 返回值
 *  执行正常，返回0
 *  执行异常，返回-1，同时response应带有错误帧信息
 */
typedef int (*ServerFunctionHook)(GspIedServer server, GspClientConnection clientConn, void* request, int type, void* param, void **response);

/**
 * @brief GspServer_setFunctionHookFunc 设置服务端回调服务函数
 * @param server 服务指针
 * @param func 回调函数
 * @param param 回调函数的参数
 */
LIB860_API void GspServer_setFunctionHookFunc(GspIedServer server, ServerFunctionHook func, void *param);

/**
 * @brief GspServer_getModelNodeByReferAndFc 获取指定refer的模型相关信息
 * 返回modelnode对象，可根据对象内modelType成员，判断具体的model类型，model类型包括
 *  GspLogicalDeviceModelType,
    GspLogicalNodeModelType,
    GspDataObjectModelType,
    GspDataAttributeModelType
 * 根据类型，可以将GspModelNode *强制转换为
 * GspLogicalDevice *
 * GspLogicalNode *
 * GspDataObject *
 * GspDataAttribute
 * 从而获取node具体信息
 * @param server 服务对象指针
 * @param rerfer da的refs
 * @param fc 功能约束
 * @return 数据属性对象指针
 */
LIB860_API GspModelNode *GspServer_getModelNodeByReferAndFc(GspIedServer server, const char *rerfer, const char *fc);

typedef bool (*GspActiveSettingGroupChangedHandler) (void* parameter,
                                                     GspSettingGroupControlBlock* sgcb,
                                                     uint8_t newActSg,
                                                     GspClientConnection connection);

LIB860_API void GspIedServer_setActiveSettingGroupChangedHandler(GspIedServer self,
                                                                 GspSettingGroupControlBlock* sgcb,
                                                                 GspActiveSettingGroupChangedHandler handler,
                                                                 void* parameter);

typedef bool (*GspEditSettingGroupChangedHandler) (void* parameter,
                                                   GspSettingGroupControlBlock* sgcb,
                                                   uint8_t newEditSg,
                                                   GspClientConnection connection);

LIB860_API void GspIedServer_setEditSettingGroupChangedHandler(GspIedServer self,
                                                               GspSettingGroupControlBlock* sgcb,
                                                               GspEditSettingGroupChangedHandler handler,
                                                               void* parameter);

typedef bool (*GspEditSettingGroupConfirmationHandler) (void* parameter,
                                                        GspSettingGroupControlBlock* sgcb,
                                                        uint8_t editSg);

LIB860_API void GspIedServer_setEditSettingGroupConfirmationHandler(GspIedServer self,
                                                                    GspSettingGroupControlBlock* sgcb,
                                                                    GspEditSettingGroupConfirmationHandler handler,
                                                                    void* parameter);


using RpcFunc = std::function<GspMmsValue *(GspMmsValue *req, string &nextCallId)>;
struct RpcInfo {
    RpcFunc func;
    string name;
    int timeout;
    int version;
    DataDefinition_t requestDefine;
    DataDefinition_t responseDefine;
};

LIB860_API void GspIedServer_addRpcFunc(const string &interface, const string &method, RpcInfo *rcpInfo);

LIB860_API void GspIedServer_addMockRpcFunc(const string &interface, const string &method, const string &resp, bool hasNextCallId);

LIB860_API void GspIedServer_delMockRpcFunc(const string &interface, const string &method);

#endif

