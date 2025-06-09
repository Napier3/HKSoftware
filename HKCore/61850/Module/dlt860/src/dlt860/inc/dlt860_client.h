#ifndef GSP_DLT860_CLIENT_H_
#define GSP_DLT860_CLIENT_H_

#include "dlt860_common.h"
#include "libdlt860_common_api.h"
#include "gsp_mms_value.h"
#include "gsp_mms_client_connection.h"
#include "gsp_linked_list.h"

namespace GSP {

/**
  * 860 协议客户端API
 **/

// ied 链接对象
typedef struct sGspIedConnection* GspIedConnection;

// 数据值(ref串 和 对应的值)
typedef struct sGspClientDataSet* GspClientDataSet;

// 文件目录条目
typedef struct sGspFileDirectoryEntry* GspFileDirectoryEntry;

// 控制对象
typedef struct sGspControlObjectClient* GspControlObjectClient;

// 最近一次的错误信息
typedef struct
{
    int ctlNum;
    GspControlLastApplError error;
    GspControlAddCause addCause;
} GspLastApplError;

// IED的链接状态
typedef enum
{
    // IED 链接关闭
    GSP_IED_STATE_CLOSED = 0,
    // IED 链接中
    GSP_IED_STATE_CONNECTING,
    // IED 链接成功
    GSP_IED_STATE_CONNECTED,
    // IED 链接关闭中
    GSP_IED_STATE_CLOSING
} GspIedConnectionState;

// 接口的错误代码
typedef enum {
    // **************************************************************  一般错误代码 ******************************************************************
    // 没有错误
    GSP_IED_ERROR_OK = 0,

    // 客户端未链接
    GSP_IED_ERROR_NOT_CONNECTED = 1,

    // 客户端已经处于链接状态
    GSP_IED_ERROR_ALREADY_CONNECTED = 2,

    // 客户端链接已经断开
    GSP_IED_ERROR_CONNECTION_LOST = 3,

    // 客户端不支持该服务, 或者不支持部分参数
    GSP_IED_ERROR_SERVICE_NOT_SUPPORTED = 4,

    // 服务端链接拒绝
    GSP_IED_ERROR_CONNECTION_REJECTED = 5,

    // 客户端链接异常,已经达到了未处理链接的上限值
    GSP_IED_ERROR_OUTSTANDING_CALL_LIMIT_REACHED = 6,

    // ************************************************************** 客户端错误代码 ****************************************************************

    // API 调用采用了无效的参数
    GSP_IED_ERROR_USER_PROVIDED_INVALID_ARGUMENT = 10,

    // 客户端使能报告失败,数据集不匹配
    GSP_IED_ERROR_ENABLE_REPORT_FAILED_DATASET_MISMATCH = 11,

    // 提供的对象引用无效 (语法错误)
    GSP_IED_ERROR_OBJECT_REFERENCE_INVALID = 12,

    // 收到了未期望的类型
    GSP_IED_ERROR_UNEXPECTED_VALUE_RECEIVED = 13,

    // 获取数据值发生错误
    GSP_IED_ERROR_GET_VALUE = 14,

    // ************************************************************* 服务端返回的错误代码 ************************************************************

    // 链接到服务端时超时
    GSP_IED_ERROR_TIMEOUT = 20,

    // 由于访问控制,服务端拒绝了该请求
    GSP_IED_ERROR_ACCESS_DENIED = 21,

    // 请求的对象不存在
    GSP_IED_ERROR_OBJECT_DOES_NOT_EXIST = 22,

    // 该对象已经存在了
    GSP_IED_ERROR_OBJECT_EXISTS = 23,

    // 该对象的请求不被支持
    GSP_IED_ERROR_OBJECT_ACCESS_UNSUPPORTED = 24,

    // 对象类型不匹配, 期望着另外一种数据类型
    GSP_IED_ERROR_TYPE_INCONSISTENT = 25,

    // 对象或者服务临时不可用
    GSP_IED_ERROR_TEMPORARILY_UNAVAILABLE = 26,

    // 指定的对象在服务端未被定义
    GSP_IED_ERROR_OBJECT_UNDEFINED = 27,

    // 指定的地址是无效的
    GSP_IED_ERROR_INVALID_ADDRESS = 28,

    // 由于硬件错误导致的错误
    GSP_IED_ERROR_HARDWARE_FAULT = 29,

    // 请求的数据类型不支持
    GSP_IED_ERROR_TYPE_UNSUPPORTED = 30,

    // 对象属性不匹配,期望这另外的属性
    GSP_IED_ERROR_OBJECT_ATTRIBUTE_INCONSISTENT = 31,

    // 对象值无效
    GSP_IED_ERROR_OBJECT_VALUE_INVALID = 32,

    // 对象无效
    GSP_IED_ERROR_OBJECT_INVALIDATED = 33,

    // 接受到服务端的无效消息
    GSP_IED_ERROR_MALFORMED_MESSAGE = 34,

    // 实例不可用 协议错误代码 1
    GSP_IED_ERROR_INSTANCE_NOT_AVAILABLE = 35,

    // 实例在使用 协议错误代码 2
    GSP_IED_ERROR_INSTANCE_IN_USE = 36,

    // 访问违例 协议错误代码 3
    GSP_IED_ERROR_ACCESS_VIOLATION = 37,

    // 当前状态不允许访问 协议错误代码 4
    GSP_IED_ERROR_ACCESS_NOT_ALLOWED_IN_CURRENT_STATE = 38,

    // 参数值不合适 协议错误代码 5
    GSP_IED_ERROR_PARAMETER_VALUE_INAPPROPRIATE = 39,

    // 参数值不一致 协议错误代码 6
    GSP_IED_ERROR_PARAMETER_VALUE_INCONSISTENT = 40,

    // 类不被支持 协议错误代码 7
    GSP_IED_ERROR_CLASS_NOT_SUPPORTED = 41,

    // 实例被其它客户锁定 协议错误代码 8
    GSP_IED_ERROR_INSTANCE_LOCKED_BY_OTHER_CLIENT = 42,

    // 控制必须被选择 协议错误代码 9
    GSP_IED_ERROR_CONTROL_MUST_BE_SELECTED = 43,

    // 类型冲突 协议错误代码 10
    GSP_IED_ERROR_TYPE_CONFLICT = 44,

    // 由于通信约束失败 协议错误代码 11
    GSP_IED_ERROR_FAILED_DUE_TO_COMM_CONSTRAINT = 45,

    // 由于服务器约束失败 协议错误代码 12
    GSP_IED_ERROR_FAILED_DUE_TO_SERVER_CONSTRAINT = 46,

    // 链接拒绝 协议错误代码 13
    GSP_IED_ERROR_ERROR_CONNECTION_REJECTED = 47,

    // 链接丢失 协议错误代码 14
    GSP_IED_ERROR_ERROR_CONNECTION_LOST = 48,

    // 服务超时 协议错误代码 15
    GSP_IED_ERROR_ERROR_SERVICE_TIMEOUT = 49,

    // 应答解析错误 协议错误代码 16
    GSP_IED_ERROR_ERROR_PARSING_RESPONSE = 50,

    // 硬件错误 协议错误代码 17
    GSP_IED_ERROR_ERROR_HARDWARE_FAULT = 51,

    // 终止拒绝 协议错误代码 18
    GSP_IED_ERROR_ERROR_CONCLUDE_REJECTED = 52,

    // 参数无效 协议错误代码 19
    GSP_IED_ERROR_ERROR_INVALID_ARGUMENTS = 53,

    // 超出调用限制 协议错误代码 20
    GSP_IED_ERROR_ERROR_OUTSTANDING_CALL_LIMIT = 54,

    // 其他错误 协议错误代码 21
    GSP_IED_ERROR_ERROR_OTHER = 55,

    // 该服务未实现 98
    GSP_IED_ERROR_SERVICE_NOT_IMPLEMENTED = 98,

    // 未知错误代码
    GSP_IED_ERROR_UNKNOWN = 99
} GspIedClientError;

// 接口的终止错误代码
typedef enum {
    // other
    GSP_IED_ABORT_OTHER = 0,
    // unrecognized-service
    GSP_IED_ABORT_UNRECOGNIZED_SERVICE = 1,
    // invalid-reqID
    GSP_IED_ABORT_INVAILD_REQID = 2,
    // invalid-argument
    GSP_IED_ABORT_INVAILD_ARGUMENT = 3,
    // invalid-result
    GSP_IED_ABORT_INVAILD_RESULT = 4,
    // max-serv-outstanding-exceeded
    GSP_IED_ABORT_MAX_SERV_EXCEEDED = 5
} GspAbortError;


/************************************************************ 链接相关接口操作 *********************************************************************/

/**
 * @brief Gsp_IedConnection 创建链接
 * @return 创建的链接指针
 */
LIB860_API GspIedConnection Gsp_IedConnection_Create(void);

/**
 * 链接关闭时的回调函数定义
 */
typedef void (*GspIedConnectionClosedHandler) (void* parameter, GspIedConnection connection);

/**
 * 链接状态发生改变时的回调函数定义
 */
typedef void (*GspIedConnectionIedConnection_StateChangedHandler) (void* parameter,
                                                                   GspIedConnection connection,
                                                                   GspIedConnectionState newState);

/**
 * @brief Gsp_IedConnection_InstallStateChangedHandler 注册状态改变时的回调函数
 * @param self 链接对象
 * @param handler 回调处理函数
 * @param parameter 回调处理函数的参数
 */
void Gsp_IedConnection_InstallStateChangedHandler(GspIedConnection self,
                                                  GspIedConnectionIedConnection_StateChangedHandler handler,
                                                  void* parameter);

/**
 * @brief IedConnection_installConnectionClosedHandler 注册链接关闭时的回调函数
 * @param self 链接对象
 * @param handler 回调处理函数
 * @param parameter 回调处理函数的参数
 */
void Gsp_IedConnection_InstallConnectionClosedHandler(GspIedConnection self,
                                                      GspIedConnectionClosedHandler handler,
                                                      void* parameter);

/**
 * @brief Gsp_IedConnection_destroy 关闭并销毁链接信息
 * @param self 链接对象
 */
LIB860_API void Gsp_IedConnection_Destroy(GspIedConnection self);

/**
 * @brief Gsp_IedConnection_setConnectTimeout 设置链接超时时间(链接到服务器时)
 * @param self 链接对象
 * @param timeoutInMs 链接超时时间(毫秒)
 */
LIB860_API void Gsp_IedConnection_SetConnectTimeout(GspIedConnection self,
                                                    uint32_t timeoutInMs);

/**
 * @brief Gsp_IedConnection_setRequestTimeout 设置链接的API操作的超时时间(请求操作)
 * 该函数可以随时调用，随时调整这个超时时间
 * @param self 链接对象
 * @param timeoutInMs 链接超时时间(毫秒)
 */
LIB860_API void Gsp_IedConnection_SetRequestTimeout(GspIedConnection self,
                                                    uint32_t timeoutInMs);

/**
 * @brief Gsp_IedConnection_getRequestTimeout 获取链接API接口的操作时间
 * @param self 链接对象
 * @return 超时时间
 */
LIB860_API uint32_t Gsp_IedConnection_GetRequestTimeout(GspIedConnection self);

/**
 * @brief Gsp_IedConnection_tick 消息处理 和 任务处理
 * 在非线程模式时，这个函数需要调用者手动
 * @param self
 * @return
 */
LIB860_API bool Gsp_IedConnection_Tick(GspIedConnection self);

/**
 * @brief Gsp_IedConnection_connect 建立 gsp 链接
 * @param self 链接对象
 * @param error 链接错误信息
 * @param hostname 服务端IP (例如："127.0.0.1")
 * @param tcpPort 服务端端口, 为-1时采用默认端口 mms - 8102, tls - 9102 (例如：8102)
 */
LIB860_API bool Gsp_IedConnection_Connect(GspIedConnection self,
                                          GspIedClientError* error,
                                          const char* hostname,
                                          int tcpPort,
										  const char* local_address = NULL);//zhouhj 20210929 增加客户端本地IP地址的绑定

/**
 * @brief Gsp_IedConnection_Associate 关联请求(SC 1)
 * @param self 链接对象
 * @param error 链接错误信息
 * @param paramServerAccessPointReference 接入点
 * @return 链接ID
 */
LIB860_API const char* Gsp_IedConnection_Associate(GspIedConnection self,
                                                   GspIedClientError* error,
                                                   const char* paramServerAccessPointReference);

/**
 * @brief Gsp_IedConnection_FreeAssociateID 释放关联ID
 * @param paramAssociatedID 关联ID信息
 */
LIB860_API void Gsp_IedConnection_FreeAssociateID(const char* paramAssociatedID);

/**
 * @brief Gsp_IedConnection_Abort 终止链接(SC 2)
 * @param self 链接对象
 * @param error 错误返回
 * @param reasonCode 终止原因
 */
LIB860_API void Gsp_IedConnection_Abort(GspIedConnection self,
                                        GspIedClientError* error,
                                        GspAbortError reasonCode,
                                        const char* associationId);

/**
 * @brief GspIedConnection_close 链接关闭(tcp层断掉)
 * @param self 链接对象
 */
LIB860_API void Gsp_IedConnection_Close(GspIedConnection self);

/**
 * @brief IedConnection_getState 获取链接状态
 * @param self 链接对象
 * @return 链接状态
 */
LIB860_API GspIedConnectionState Gsp_IedConnection_GetState(GspIedConnection self);

/**
 * @brief Gsp_IedConnection_release 释放链接（SC 3）
 * @param self 链接对象
 * @param error 链接错误信息
 */
LIB860_API void Gsp_IedConnection_Release(GspIedConnection self,
                                          GspIedClientError* error,
                                          const char* associationId);

/**************************************************************** 模型相关接口 **************************************************************/

/**
 * @brief Gsp_IedConnection_getServerDirectory 获取服务目录（SC 80）
 * @param self
 * @param error
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetServerDirectory(GspIedConnection self,
                                                              GspIedClientError* error);


/**
 * @brief Gsp_IedConnection_getLogicalDeviceList 获取逻辑设备列表（SC 81）
 * 获取逻辑设备下面的逻辑节点的信息
 * @param self 链接对象
 * @param error 链接错误信息
 * @param paramLDName 逻辑设备的名字
 * 如果请求时指定了 ldName，则响应的 lnReference 应为逻辑节点的名称。如果未指定 ldName，则应读取所有逻辑设备的逻辑节点，响应的 lnReference 应为逻辑节点的引用
 * @return 逻辑设备列表信息
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetLogicDeviceDirectory(GspIedConnection self,
                                                                   GspIedClientError* error,
                                                                   const char* paramLDName);

/**
 * @brief Gsp_IedConnection_getLogicNodeDirectory 获取LN下DO的列表（SC 82）
 * @param self 链接对象
 * @param error 链接错误信息
 * @param paramType 参数类型
 * @param reference 参引串
 * @return
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetLogicNodeDirectory(GspIedConnection self,
                                                                 GspIedClientError* error,
                                                                 GspACSICLASS paramType,
                                                                 const char* reference);


/**
 * @brief Gsp_IedConnection_getAllDataDefinition 获取所有数据定义(SC 155)
 * 如果参数 fc 为 XX 或空，应返回指定逻辑设备或逻辑节点内全部数据属性的定义（不包括功能约 束 SE）。
 * 仅当参数 fc 明确指定为 SE 时，服务器才返回功能约束 SE 的数据属性定义。
 * 功能约束 SE 的数据属性定义应与功能约束 SG 完全相同
 * @param self 链接对象
 * @param error 操作错误信息
 * @param fc 功能约束
 * @param reference 参引串
 * @param paramRefType 参引串类型
 * @return 结果列表
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetAllDataDefinition(GspIedConnection self,
                                                                GspIedClientError* error,
                                                                GspFunctionalConstraint fc,
                                                                const char* reference,
                                                                GspRefType paramRefType);

/**
 * @brief Gsp_FreeAllDataDefinition 释放数据定义的内存
 * @param paramAllDataDefinition 数据定义
 */
LIB860_API void Gsp_FreeAllDataDefinition(void* paramAllDataDefinition);

/**************************************************************** 数据(批量)相关接口 **************************************************************/

/**
 * @brief Gsp_IedConnection_getAllDataValues 获取所有数据值(逻辑设备或者逻辑节点下)
 * 附加说明参照 Gsp_IedConnection_getAllDataDefinition, 该接口获取到相关refs 和 对应的值
 * @param self 链接对象
 * @param error 操作错误信息
 * @param fc 功能约束
 * @param reference 参引串
 * @param paramRefType 参引串类型
 * @return 结果列表
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetAllDataValues(GspIedConnection self,
                                                            GspIedClientError* error,
                                                            GspFunctionalConstraint fc,
                                                            const char* reference,
                                                            GspRefType paramRefType);

/**
 * @brief Gsp_ClientDataSet_Create 创建数据
 * @param dataSetReference 数据参引串
 * @return 数据值信息
 */
LIB860_API GspClientDataSet Gsp_ClientDataSet_Create(const char* dataSetReference);

/**
 * @brief Gsp_ClientDataSet_Destroy 销毁数据
 * @param self 数据值
 */
LIB860_API void Gsp_ClientDataSet_Destroy(GspClientDataSet self);

/**
 * @brief Gsp_ClientDataSet_GetValues 获取数值部分
 * @param self 数据值
 * @return
 */
LIB860_API GspMmsValue* Gsp_ClientDataSet_GetValues(GspClientDataSet self);

/**
 * @brief Gsp_ClientDataSet_GetReference 获取数据参引部分
 * @param self 数据值
 * @return
 */
LIB860_API char* Gsp_ClientDataSet_GetReference(GspClientDataSet self);

/**
 * @brief Gsp_IedConnection_getAllCBValues 获取所有控制块值(逻辑设备或者逻辑节点下)
 * 读所有控制块值服务用于获取指定逻辑设备或逻辑节点下所有控制块的值，控制块类型由 acsiClass 指定，如缓存报告控制块、非缓存报告控制块、定值控制块等
 * @param self 链接对象
 * @param error 操作错误信息
 * @param paramClassType 对象类别
 * @param reference ref串
 * @param paramRefType ref类型
 * @return 结果列表
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetAllCBValues(GspIedConnection self,
                                                          GspIedClientError* error,
                                                          GspACSICLASS paramClassType,
                                                          const char* reference,
                                                          GspRefType paramRefType);

/**
 * @brief Gsp_FreeAllCBValue
 * @param paramAllCbValue
 */
LIB860_API void Gsp_FreeAllCBValue(void* paramAllCbValue);

/**************************************************************** 数据(单个或者多个)相关接口 ********************************************************/

/**
 * @brief Gsp_IedConnection_getDataValues 获取制定数据值
 * @param self 链接对象
 * @param error 错误信息
 * @param refsFcList 带有功能约束的refs列表
 * @return 结果列表
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetDataValues(GspIedConnection self,
                                                         GspIedClientError* error,
                                                         GspLinkedList refsFcList);

/**
 * @brief Gsp_IedConnection_SetValues 客户端批量写值
 * @param self 链接对象
 * @param error 错误信息
 * @param refsFcList 带有功能约束的数据值列表
 * @return 是否写成功
 */
LIB860_API GspLinkedList Gsp_IedConnection_SetDataValues(GspIedConnection self,
                                                         GspIedClientError* error,
                                                         GspLinkedList dataRefsFcList);

/**
 * @brief Gsp_IedConnection_GetDataDefinition 获取数据定义
 * @param self 链接对象
 * @param error 错误信息
 * @param refsFcList 带有功能约束的refs列表
 * @return 结果列表
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetDataDefinition(GspIedConnection self,
                                                             GspIedClientError* error,
                                                             GspLinkedList refsFcList);

/**************************************************************** 数据集相关接口 ******************************************************************/

/**
 * @brief Gsp_Gsp_IedConnection_GetDataSetDirectory 读数据集目录
 * @param datasetReference refs
 * @return 数据集目录信息
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetDataSetDirectory(GspIedConnection self,
                                                               GspIedClientError* error,
                                                               const char *datasetReference);

/**
 * @brief Gsp_GetDataSetDirectory_Destory 释放数据目录内存
 * @param self 数据目录信息
 */
LIB860_API void Gsp_GetDataSetDirectory_Destory(GspLinkedList self);

/**
 * @brief Gsp_Gsp_IedConnection_GetDataSetValue 读数据集值
 * @param datasetReference refs
 * @return 数据集值信息
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetDataSetValues(GspIedConnection self,
                                                            GspIedClientError* error,
                                                            const char *datasetReference);

/**
 * @brief Gsp_GetDataSetValues_Destory 释放数据值内存
 * @param self 数据目录信息
 */
LIB860_API void Gsp_GetDataSetValues_Destory(GspLinkedList self);

/**
 * @brief Gsp_RefsFCFree 释放RefsFC内存
 * @param paramData RefsFC
 */
LIB860_API void Gsp_RefsFCFree(RefsFC paramData);

/**************************************************************** 文件目录相关接口 **************************************************************/
/**
 * @brief Gsp_IedConnection_getFileDirectory 获取文件目录
 * @param self 链接对象
 * @param error 错误描述
 * @param pathName 目录路径
 * @param startTime 开始时间
 * @param endTime 结束时间
 * @param fileAfter 本次开始的文件名字(在该文件名字之后的文件信息)
 * @param morefollow 是否有后续的数据
 * @return 目录信息列表
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetFileDirectory(
        GspIedConnection self,
        GspIedClientError* error,
        const char* pathName,
        const char* startTime,
        const char* endTime,
        const char* fileAfter,
        bool &morefollow
        );

/**
 * @brief  GspFileDirEntry_GetFileName 获取文件名字
 * @param self 文件目录对象
 */
LIB860_API const char* Gsp_FileDirEntry_GetFileName(GspFileDirectoryEntry self);

/**
 * @brief  GspFileDirEntry_GetFileSize 获取文件尺寸
 * @param self 文件目录对象
 */
LIB860_API uint32_t Gsp_FileDirEntry_GetFileSize(GspFileDirectoryEntry self);

/**
 * @brief  GspFileDirEntry_GetLastModified 获取文件最后修改时间
 * @param self 文件目录对象
 */
LIB860_API uint64_t Gsp_FileDirEntry_GetLastModified(GspFileDirectoryEntry self);

/**
 * @brief Gsp_FileDirEntry_GetCheckSum 获取校验码
 * @param self 文件目录对象
 */
LIB860_API uint64_t Gsp_FileDirEntry_GetCheckSum(GspFileDirectoryEntry self);

/**
 * @brief FileDirEntry_destroy 释放文件目录信息
 * @param self 文件目录对象
 */
LIB860_API void Gsp_FileDirEntry_Destroy(GspFileDirectoryEntry self);

/**************************************************************** 通用相关接口 **************************************************************/

/**
 * @brief Gsp_BitString_print bitstring bitstring 打印测试
 * @param paramOther birstring 数据
 */
LIB860_API void Gsp_BitString_print(BIT_STRING_t* paramOther);

/**************************************************************** 文件相关接口 **************************************************************/

typedef bool (*GspClientGetFileHandler) (void* parameter, uint8_t* buffer, uint32_t bytesRead, bool endFLag);

/**
* @brief Gsp_IedConnection_getFile 下载文件
* @param self 链接对象
* @param error 错误描述
* @param fileName 文件名字
* @param startPostion 开始位置
* @param callback 文件数据到来时的回调
* @return 是否还有后续数据
*/
LIB860_API bool Gsp_IedConnection_GetFile(
        GspIedConnection self,
        GspIedClientError* error,
        const char* fileName,
        uint32_t* startPostion,
        GspClientGetFileHandler callback,
        void* handlerParameter
        );

/**
* @brief Gsp_IedConnection_setFile 上传文件(暂时放弃)
* @param self 链接对象
* @param error 错误描述
* @param fileName 文件名字
* @param startPostion 开始位置
* @param fileData 文件数据
* @param endOfFile 是否是文件结尾
* @return 本次数据是否上传成功
*/
LIB860_API bool Gsp_IedConnection_setFile(
        GspIedConnection self,
        GspIedClientError* error,
        const char* fileName,
        uint32_t startPostion,
        const char* fileData,
        uint32_t fileDataSize,
        bool endOfFile
        );

/**
* @brief Gsp_IedConnection_deleteFile 删除文件(暂时放弃)
* @param self 链接对象
* @param error 错误描述
* @param fileName 文件名字
* @return 本次删除是否成功
*/
//LIB860_API bool Gsp_IedConnection_deleteFile(
//        Gsp_IedConnection self,
//        GspIedClientError* error,
//        const char* fileName
//        );

/**
* @brief Gsp_IedConnection_getFileAttributeValues 获取文件属性(读文件已经有属性了)
* @param self 链接对象
* @param error 错误描述
* @param fileName 文件名字
* @return 文件属性信息
*/
//LIB860_API FileAttribute Gsp_IedConnection_getFileAttributeValues(
//        Gsp_IedConnection self,
//        GspIedClientError* error,
//        const char* fileName
//        );

/**************************************************************** 缓存报告相关接口 **************************************************************/

/**
 * @brief Gsp_IedConnection_GetBRCBValues 获取缓存报告控制块的值(使用者注释释放返回的控制块的内存)
 * @param self 链接对象
 * @param error 错误描述
 * @param brcbReference 缓存报告的控制块的refs
 * @return 控制块的值列表信息
 */
LIB860_API BRCBControlBlk Gsp_IedConnection_GetBRCBValues(GspIedConnection self,
                                                          GspIedClientError* error,
                                                          const char* brcbReference);

/**
 * @brief GspBRCBControlBlk_EnableRpt 打开或者关闭报告
 * @param brcbControlBlk 控制块信息
 * @param rptFlag 开启或者关闭报告
 */
LIB860_API void Gsp_BRCBControlBlk_EnableRpt(BRCBControlBlk brcbControlBlk,
                                             bool rptFlag);

/**
 * @brief GspBRCBControlBlk_Destory 销毁缓存的报告控制块
 * @param brcbControlBlk 控制块信息
 */
LIB860_API void Gsp_BRCBControlBlk_Destory(BRCBControlBlk brcbControlBlk);

/**
 * @brief GspBRCBControlBlk_SetBufTime 设置缓存
 * @param brcbControlBlk 控制块信息
 * @param paramBufTime 缓存时间
 */
LIB860_API void Gsp_BRCBControlBlk_SetBufTime(BRCBControlBlk brcbControlBlk,
                                              INT32U_t paramBufTime);

/**
 * @brief GspBRCBControlBlk_GI 总召（使能报告后，调用才会生效）
 * @param brcbControlBlk 控制块信息
 * @param paramGIFlag 总召标记
 */
LIB860_API void Gsp_BRCBControlBlk_GI(BRCBControlBlk brcbControlBlk,
                                      bool paramGIFlag);

/**
 * @brief GspBRCBControlBlk_IntgPd 设置周期上送的周期时间
 * @param brcbControlBlk 控制块信息
 * @param paramIntgPd 周期性上送时间(毫秒)
 */
LIB860_API void Gsp_BRCBControlBlk_IntgPd(BRCBControlBlk brcbControlBlk,
                                          INT32U_t paramIntgPd);

/**
 * @brief GspBRCBControlBlk_SetOptFlds 设置报告的操作选项
 * @param brcbControlBlk 控制块信息
 * @param brcbControlOptType 操作类型
 * @param paramValue 操作类型对应的值
 * @param isMulity 是否多个值一起设置(多个值一起设置时后面的调用设置为 true)
 */
LIB860_API void Gsp_BRCBControlBlk_SetOptFlds(BRCBControlBlk brcbControlBlk,
                                              RCBOptFldType brcbControlOptType,
                                              bool paramValue,
                                              bool isMulity = false);

/**
 * @brief Gsp_BRCBControlBlk_SetReportRefs 设置报告的 refs
 * @param brcbControlBlk 控制块信息
 * @param paramValue report的refs值
 */
LIB860_API void Gsp_BRCBControlBlk_SetReportRefs(BRCBControlBlk paramBrcbControlBlk,
                                                 const char* paramValue);

/**
 * @brief Gsp_BRCBControlBlk_SetRPTID 设置报告的 refs
 * @param brcbControlBlk 控制块信息
 * @param paramRptID report的id
 */
LIB860_API void Gsp_BRCBControlBlk_SetRPTID(BRCBControlBlk paramBrcbControlBlk,
                                            const char* paramRptID);

/**
 * @brief GspBRCBControlBlk_SetTriggerConditions 设置报告的触发选项
 * @param brcbControlBlk 控制块信息
 * @param brcbControlOptType 触发类型
 * @param paramValue 触发类型对应的值
 * @param isMulity 是否多个值一起设置(多个值一起设置时后面的调用设置为 true)
 */
LIB860_API void Gsp_BRCBControlBlk_SetTriggerConditions(BRCBControlBlk brcbControlBlk,
                                                        RCBTriggerType brcbControlTriggerType,
                                                        bool paramValue,
                                                        bool isMulity = false);
/**
 * @brief Gsp_BRCBControlBlk_SetEntryID 设置缓存报告的 EntryID
 * @param brcbControlBlk 缓存报告控制块
 * @param paramEntryID entryID值
 * @param idSize entryID 长度
 */
LIB860_API void Gsp_BRCBControlBlk_SetEntryID(BRCBControlBlk brcbControlBlk,
                                              const char* paramEntryID,
                                              int idSize);

/**
 * @brief GspGsp_IedConnection_SetBRCBValues 设置缓存报告控制块值
 * @param self 链接对象
 * @param error 错误描述
 * @param brcbControlBlk 缓存报告控制块值
 */
LIB860_API bool Gsp_IedConnection_SetBRCBValues(GspIedConnection self,
                                                GspIedClientError* error,
                                                BRCBControlBlk brcbControlBlk);

/**
 * @brief GspBRCBControlBlk_GetRptID 获取 rptid
 * @param brcbControlBlk 控制块信息
 */
LIB860_API char* Gsp_BRCBControlBlk_GetRptID(BRCBControlBlk brcbControlBlk);

/**
 * @brief Gsp_BRCBControlBlk_CleanBuffer 设置缓存报告控制块的缓存
 * @param brcbControlBlk 控制块信息
 */
LIB860_API void Gsp_BRCBControlBlk_CleanBuffer(BRCBControlBlk brcbControlBlk);

/**************************************************************** 非缓存报告相关接口 **************************************************************/

/**
 * @brief Gsp_IedConnection_GetURCBValues 获取非缓存报告控制块的值
 * @param self 链接对象
 * @param error 错误描述
 * @param brcbReference 缓存报告的控制块的refs
 * @return 控制块的值列表信息
 */
LIB860_API URCBControlBlk Gsp_IedConnection_GetURCBValues(GspIedConnection self,
                                                          GspIedClientError* error,
                                                          const char* brcbReference);


/**
 * @brief GspURCBControlBlk_EnableRpt 打开或者关闭报告
 * @param urcbControlBlk 控制块信息
 * @param rptFlag 开启或者关闭报告
 */
LIB860_API void Gsp_URCBControlBlk_EnableRpt(URCBControlBlk paramUrcbControlBlk,
                                             bool rptFlag);

/**
 * @brief URCBControlBlk_destory 销毁非缓存的报告控制块
 * @param urcbControlBlk 控制块信息
 */
LIB860_API void Gsp_URCBControlBlk_Destory(URCBControlBlk paramUrcbControlBlk);

/**
 * @brief GspURCBControlBlk_SetBufTime 设置缓存
 * @param urcbControlBlk 控制块信息
 * @param paramBufTime 缓存时间
 */
LIB860_API void Gsp_URCBControlBlk_SetBufTime(URCBControlBlk paramUrcbControlBlk,
                                              INT32U_t paramBufTime);

/**
 * @brief GspURCBControlBlk_GI 总召（使能报告后，调用才会生效）
 * @param urcbControlBlk 控制块信息
 * @param paramGIFlag 总召标记
 */
LIB860_API void Gsp_URCBControlBlk_GI(URCBControlBlk urcbControlBlk,
                                      bool paramGIFlag);

/**
 * @brief URCBControlBlk_IntgPd 设置周期上送的周期时间
 * @param urcbControlBlk 控制块信息
 * @param paramIntgPd 周期性上送时间(毫秒)
 */
LIB860_API void Gsp_URCBControlBlk_IntgPd(URCBControlBlk paramUrcbControlBlk,
                                          INT32U_t paramIntgPd);

/**
 * @brief URCBControlBlk_SetOptFlds 设置报告的操作选项
 * @param urcbControlBlk 控制块信息
 * @param urcbControlOptType 操作类型
 * @param paramValue 操作类型对应的值
 * @param isMulity 是否多个值一起设置(多个值一起设置时后面的调用设置为 true)
 */
LIB860_API void Gsp_URCBControlBlk_SetOptFlds(URCBControlBlk paramUrcbControlBlk,
                                              RCBOptFldType urcbControlOptType,
                                              bool paramValue,
                                              bool isMulity = false);

/**
 * @brief URCBControlBlk_SetTriggerConditions 设置报告的触发选项
 * @param paramUrcbControlBlk 控制块信息
 * @param urcbControlOptType 触发类型
 * @param paramValue 触发类型对应的值
 * @param isMulity 是否多个值一起设置(多个值一起设置时后面的调用设置为 true)
 */
LIB860_API void Gsp_URCBControlBlk_SetTriggerConditions(URCBControlBlk paramUrcbControlBlk,
                                                        RCBTriggerType urcbControlTriggerType,
                                                        bool paramValue,
                                                        bool isMulity = false);

/**
 * @brief URCBControlBlk_getRptID 获取 rptid
 * @param urcbControlBlk 控制块信息
 */
LIB860_API char* Gsp_URCBControlBlk_GetRptID(URCBControlBlk urcbControlBlk);

/**
 * @brief Gsp_URCBControlBlk_SetRPTID 设置rptid
 * @param paramUrcbControlBlk 报告控制块
 * @param paramRptID 报告ID
 */
LIB860_API void Gsp_URCBControlBlk_SetRPTID(URCBControlBlk paramUrcbControlBlk,
                                            const char* paramRptID);

/**
 * @brief Gsp_IedConnection_setURCBValues 设置缓存报告控制块值
 * @param self 链接对象
 * @param error 错误描述
 * @param urcbControlBlk 非缓存报告控制块值
 */
LIB860_API bool Gsp_IedConnection_SetURCBValues(GspIedConnection self,
                                                GspIedClientError* error,
                                                URCBControlBlk urcbControlBlk);

/**
 * @brief Gsp_URCBControlBlk_SetReportRefs 设置报告的 refs
 * @param brcbControlBlk 控制块信息
 * @param paramValue report的refs值
 */
LIB860_API void Gsp_URCBControlBlk_SetReportRefs(URCBControlBlk paramUrcbControlBlk,
                                                 const char* paramValue);

/**************************************************************** 报告回调相关接口 **************************************************************/

/**
 * @brief GSPReportCallbackFunction 报告回调函数
 * @param parameter 回调函数的参数
 * @param reportPDU 报告数据
 */
typedef void (*GSPReportCallbackFunction) (void* parameter, void* reportPDU);

/**
 * @brief Gsp_IedConnection_installReportCallBack 安装报告处理回调函数
 * @param self 链接对象
 * @param paramReportRefs 报告控制快的 refs 参数
 * @param paramReportID 报告ID RPTID
 * @param handler 回调函数指针
 * @param handlerParameter 回调函数参数
 */
LIB860_API void Gsp_IedConnection_InstallReportCallBack(GspIedConnection self,
                                                        const char* paramReportRefs,
                                                        const char* paramReportID,
                                                        GSPReportCallbackFunction handler,
                                                        void* handlerParameter);

/**
 * @brief Gsp_IedConnection_unInstallReportCallBack 卸载报告回调
 * @param self 链接对象
 * @param paramReportID 报告ID rptid
 */
LIB860_API void Gsp_IedConnection_UnInstallReportCallBack(GspIedConnection self,
                                                          const char* paramReportID);

/**************************************************************** 报告资源释放接口 **************************************************************/

/**
 * @brief Gsp_Report_Destory 释放报告资源
 * @param report 报告信息
 */
LIB860_API void Gsp_Report_Destory(void* report);

/**
 * @brief Gsp_IedConnection_ReleaseAllReportCallBack 释放所有的报告回调
 */
LIB860_API void Gsp_IedConnection_ReleaseAllReportCallBack(GspIedConnection self);

/**************************************************************** 报告资源获取接口 ************************************************************/

/**
 * @brief Gsp_ClientReport_getDataSetName 获取报告中的数据集的名字
 * @param self 报告数据
 * @return 数据集名字
 */
LIB860_API const char* Gsp_ClientReport_getDataSetName(void* self);

/**
 * @brief Gsp_ClientReport_getDataSetValues 获取报告中的数据集值
 * @param self 报告数据
 * @return 报告数值列表
 */
LIB860_API void* Gsp_ClientReport_getDataSetValueList(void* self);

/**
 * @brief Gsp_ClientReport_getReportTime 获取报告中的时间
 * @param self 报告数据
 * @return 报告时间(UTC毫秒)
 */
LIB860_API uint64_t Gsp_ClientReport_getReportTime(void* self);

/**
 * @brief Gsp_ClientReport_getDataSetValuesSize 获取报告中数据值个数
 * @param self 报告数值列表(Gsp_ClientReport_getDataSetValues接口获取的值)
 * @return 报告数值个数
 */
LIB860_API uint32_t Gsp_ClientReport_getDataSetValuesSize(void* self);

/**
 * @brief Gsp_ClientReport_getDataSetValuesSize 获取报告的指定位置数据值
 * @param self 报告数值列表
 * @param paramIndex 位置
 * @return 报告数值
 */
LIB860_API GspMmsValue* Gsp_ClientReport_getDataSetValue(void* self, int paramIndex);

/**
 * @brief Gsp_ClientReport_getDataSetValueRefs 获取报告的指定位置数据值的refs
 * @param self 报告数值列表
 * @param paramIndex 位置
 * @return refs
 */
LIB860_API const char* Gsp_ClientReport_getDataSetValueRefs(void* self, int paramIndex);

/**
 * @brief Gsp_ClientReport_getDataSetValueFC 获取报告的指定位置数据值的功能约束
 * @param self 报告数值列表
 * @param paramIndex 位置
 * @return fc
 */
LIB860_API const char* Gsp_ClientReport_getDataSetValueFC(void* self, int paramIndex);

/**
 * @brief Gsp_ClientReport_getDataSetValueFC 获取报告的指定位置数据值的ID
 * @param self 报告数值列表
 * @param paramIndex 位置
 * @return id
 */
LIB860_API uint16_t Gsp_ClientReport_getDataSetValueID(void* self, int paramIndex);

/**
 * @brief Gsp_ClientReport_getRptId 获取报告中的报告ID
 * @param self 报告数据
 * @return 报告ID
 */
LIB860_API const char* Gsp_ClientReport_getRptId(void* self);

/**
 * @brief Gsp_ClientReport_getEntryId 获取entryID
 * @param self 报告数据
 * @return entryid
 */
LIB860_API EntryID_t* Gsp_ClientReport_getEntryId(void* self);

/**
 * @brief Gsp_ClientReport_getReasonCode 获取报告中的上送原因
 * @param self 报告数据
 * @param paramIndex 位置
 * @return 报告上送原因
 */
LIB860_API GspReportReasonCode Gsp_ClientReport_getReasonCode(void* self, int paramIndex);

/**
 * @brief Gsp_ClientReport_getReasonCodeStr 获取报告中的上送原因
 * @param self 报告数据
 * @param paramIndex 位置
 * @return 报告上送原因
 */
LIB860_API const char* Gsp_ClientReport_getReasonCodeStr(void* self, int paramIndex);

/**************************************************************** 定值类相关接口 **************************************************************/

/**
 * @brief Gsp_IedConnection_SelectActiveSG 选择激活定值组
 * @param self 链接对象
 * @param error 错误描述
 * @param sgcbReference 定植控制块refs
 * @param settingGroupNumber 定制组号
 * @return 是否选择成功
 */
LIB860_API bool Gsp_IedConnection_SelectActiveSG(GspIedConnection self,
                                                 GspIedClientError* error,
                                                 const char* sgcbReference,
                                                 INT8U_t settingGroupNumber);


/**
 * @brief Gsp_IedConnection_SelectEditSG 选择编辑定值组
 * @param self 链接对象
 * @param error 错误描述
 * @param sgcbReference 定值控制块refs
 * @param settingGroupNumber 定值组号
 * @return 是否选择成功
 */
LIB860_API bool Gsp_IedConnection_SelectEditSG(GspIedConnection self,
                                               GspIedClientError* error,
                                               const char* sgcbReference,
                                               INT8U_t settingGroupNumber);


/**
 * @brief Gsp_IedConnection_SetEditSGValue 设置编辑定值组值
 * @param self 链接对象
 * @param error 错误描述
 * @param paramSgValueList 定值组值列表
 * @return 是否选择成功
 */
LIB860_API bool Gsp_IedConnection_SetEditSGValue(GspIedConnection self,
                                                 GspIedClientError* error,
                                                 GspLinkedList paramSgValueList);


/**
 * @brief Gsp_IedConnection_ConfirmEditSGValues 确认编辑定值组值
 * @param self 链接对象
 * @param error 错误描述
 * @param sgcbReference 定值控制块refs
 * @return 是否设置成功
 */
LIB860_API bool Gsp_IedConnection_ConfirmEditSGValues(GspIedConnection self,
                                                      GspIedClientError* error,
                                                      const char* sgcbReference);

/**
 * @brief Gsp_IedConnection_GetEditSGValue 获取编辑定值组值
 * @param self 链接对象
 * @param error 错误描述
 * @param sgcbReferenceList 请求的定值的da列表
 * @param count 定值 refs 个数
 * @return 获取的定值组值
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetEditSGValue(GspIedConnection self,
                                                          GspIedClientError* error,
                                                          GspLinkedList paramSgRefsList);

/**
 * @brief Gsp_FreeEditSGValues 释放定值的内存
 * @param paramEditSgValues 定值结果指针
 */
LIB860_API void Gsp_FreeEditSGValues(void* paramEditSgValues);

/**
 * @brief Gsp_IedConnection_GetSGCBValues 获取定值控制块的值
 * @param self 链接对象
 * @param error 错误描述
 * @param requestPDU 请求数据单元
 * @return 定值控制块信息
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetSGCBValues(GspIedConnection self,
                                                         GspIedClientError* error,
                                                         const char* sgcbReference);
/**
 * @brief Gsp_FreeSGCBValues 释放定值控制块的内存
 * @param paramSgCbValue 定值控制块指针
 */
LIB860_API void Gsp_FreeSGCBValues(void* paramSgCbValue);

/**************************************************************** 遥控相关接口 **************************************************************/

/**
 * @brief Gsp_ControlObjectClient_create 创建控制对象
 * @param paramCtlReference 控制对象 refs
 * @param connection 链接对象
 * @return 控制对象
 */
LIB860_API GspControlObjectClient Gsp_ControlObjectClient_Create(const char* paramCtlReference,
                                                                 GspIedConnection connection);

/**
 * @brief Gsp_ControlObjectClient_Destroy 销毁控制对象
 * @param self
 */
LIB860_API void Gsp_ControlObjectClient_Destroy(GspControlObjectClient self);

/**
 * @brief Gsp_IedConnection_SetControlModel 设置遥控模式
 * @param self 遥控对象
 * @param ctlModel 遥控模式
 */
LIB860_API void Gsp_ControlObjectClient_SetControlModel(GspControlObjectClient self,
                                                        GspControlModel paramCtlModel);

/**
 * @brief Gsp_ControlObjectClient_SetControlRefs 设置遥控对象的refs
 * @param self 遥控对象
 * @param paramControlRefs 遥控对象refs
 */
LIB860_API void Gsp_ControlObjectClient_SetControlRefs(GspControlObjectClient self,
                                                       const char* paramControlRefs);

/**
 * @brief Gsp_IedConnection_SetControlModel 设置遥控是否同期检查
 * @param self 遥控对象
 * @param checkFlag 是否同期检查
 */
LIB860_API void Gsp_ControlObjectClient_SetSyncCheck(GspControlObjectClient self,
                                                     bool checkFlag);

/**
 * @brief Gsp_IedConnection_SetControlModel 设置遥控是否锁控检查
 * @param self 遥控对象
 * @param checkFlag 是否锁控检查
 */
LIB860_API void Gsp_ControlObjectClient_SetLockCheck(GspControlObjectClient self,
                                                     bool checkFlag);

/**
 * @brief Gsp_ControlObjectClient_SetTestMode 设置 test 模式
 * @param self 遥控对象
 * @param value test 值
 */
LIB860_API void Gsp_ControlObjectClient_SetTestMode(GspControlObjectClient self,
                                                    bool paramValue);

/**
 * @brief Gsp_ControlObjectClient_SetMmsValue 设置控制值
 * @param self 遥控对象
 * @param value 控制值
 */
LIB860_API void Gsp_ControlObjectClient_SetMmsValue(GspControlObjectClient self,
                                                    GspMmsValue* paramValue);

/**
 * @brief Gsp_ControlObjectClient_SetMmsValue 设置控制 Originator
 * @param self 遥控对象
 * @param value 控制值
 */
LIB860_API void Gsp_ControlObjectClient_SetOriginator(GspControlObjectClient self,
                                                      Originator__orCat paramOrCat,
                                                      const char* paramOrIdent);

LIB860_API void Gsp_ControlObjectClientInit(GspControlObjectClient self,bool bTest,bool bSynCheck,bool bInterLockCheck,bool bHasTimeActive);//zhouhj 20210717 增加用于初始化

/**
 * @brief Gsp_IedConnection_Select 遥控选择操作
 * @param GspControlObjectClient 遥控对象
 * @return
 */
LIB860_API bool Gsp_IedConnection_Select(GspControlObjectClient self,
                                         GspIedClientError* outError);

/**
 * @brief Gsp_IedConnection_Operate 遥控操作
 * @param self 控制对象
 * @param ctlVal 遥控对象值
 * @param error 错误描述
 * @param operTime 操作时间
 * @return 操作结果
 */
LIB860_API bool Gsp_IedConnection_Operate(GspControlObjectClient self,
                                          GspIedClientError* error,
                                          GspMmsValue* ctlVal,
                                          uint64_t operTime);

/**
 * @brief Gsp_IedConnection_SelectWithValue 带值选择遥控操作
 * @param self 控制对象
 * @param error 错误描述
 * @param ctlVal 操作值
 * @return 操作结果
 */
LIB860_API bool Gsp_IedConnection_SelectWithValue(GspControlObjectClient self,
                                                  GspIedClientError* error,
                                                  GspMmsValue* ctlVal);

/**
 * @brief Gsp_IedConnection_cancel 遥控取消
 * @param self 遥控对象
 * @return 操作结果
 */
LIB860_API bool Gsp_IedConnection_Cancel(GspControlObjectClient self);

/**************************************************************** test 相关接口 **************************************************************/

/**
 * @brief Gsp_IedConnection_Test 测试对方的联通性
 * @param self 链接对象
 * @param error 错误描述
 * @return 是否发送成功
 */
LIB860_API bool Gsp_IedConnection_Test(GspIedConnection self,
                                       GspIedClientError* error);

/**************************************************************** RPC 相关接口 **************************************************************/

/**
 * @brief Gsp_IedConnection_GetRpcInterfaceDirectory 获取 RPC 接口目录
 * @param self 链接对象
 * @param error 错误描述
 * @return 接口列表
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetRpcInterfaceDirectory(GspIedConnection self,
                                                                    GspIedClientError* error);

/**
 * @brief Gsp_IedConnection_FreeRpcRpcInterfaceDirectory 释放 RPC 接口目录
 * @param paramData 接口定义信息
 */
LIB860_API void Gsp_IedConnection_FreeRpcInterfaceDirectory(GspLinkedList paramData);

/**
 * @brief Gsp_IedConnection_GetRpcMethodDirectory 获取 RPC 方法目录
 * @param self 链接对象
 * @param error 错误描述
 * @return 接口列表
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetRpcMethodDirectory(GspIedConnection self,
                                                                 GspIedClientError* error,
                                                                 const char* paramInterface);

/**
 * @brief Gsp_IedConnection_FreeRpcMethodDirectory 释放 RPC 方法目录
 * @param paramData 接口定义信息
 */
LIB860_API void Gsp_IedConnection_FreeRpcMethodDirectory(GspLinkedList paramData);


/**
 * @brief Gsp_IedConnection_GetRpcInterfaceDefinition 获取 RPC 接口定义
 * @param self 链接对象
 * @param error 错误描述
 * @param paramInterface 接口名字
 * @return 接口定义
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetRpcInterfaceDefinition(GspIedConnection self,
                                                                     GspIedClientError* error,
                                                                     const char* paramInterface);

/**
 * @brief Gsp_IedConnection_FreeRpcInterfaceDefinition 释放接口定义
 * @param paramData 接口定义信息
 */
LIB860_API void Gsp_IedConnection_FreeRpcInterfaceDefinition(GspLinkedList paramData);


/**
 * @brief Gsp_IedConnection_GetRpcMethodDefinition 获取 RPC 方法定义
 * @param self 链接对象
 * @param error 错误描述
 * @param paramMethodList 方法列表
 * @return 接口定义
 */
LIB860_API GspLinkedList Gsp_IedConnection_GetRpcMethodDefinition(GspIedConnection self,
                                                                  GspIedClientError* error,
                                                                  GspLinkedList paramMethodList);

/**
 * @brief Gsp_IedConnection_FreeRpcMethodDefinition 释放方法定义
 * @param paramData 接口定义信息
 */
LIB860_API void Gsp_IedConnection_FreeRpcMethodDefinition(GspLinkedList paramData);

/**
 * @brief Gsp_IedConnection_RPCCall RPC 调用
 * @param self 链接对象
 * @param error 错误描述
 * @param paramFuncation 方法名字
 * @param paramData 调用数据
 * @param paramCallID callid
 * @return 调用返回
 */
LIB860_API void* Gsp_IedConnection_RPCCall(GspIedConnection self,
                                           GspIedClientError* error,
                                           const char* paramFuncation,
                                           GspMmsValue* paramData,
                                           const char* paramCallID = nullptr);

/**
 * @brief Gsp_RPCCallResPonse_getData 获取 RPC 调用结果中的数据部分
 * @param paramResponse RPC调用回应
 * @return 回应中的数据部分
 */
LIB860_API GspMmsValue* Gsp_RPCCallResPonse_getData(void* paramResponse);

/**
 * @brief Gsp_RPCCallResPonse_getNextCallID 获取 RPC 调用结果中的 next call id
 * @param paramResponse RPC调用回应
 * @return 回应中的 callid 部分
 */
LIB860_API const char* Gsp_RPCCallResPonse_getNextCallID(void* paramResponse);

/**
 * @brief Gsp_IedConnection_RPCCall_freePDU 释放返回的信息
 * @param paramResponsePDU 返回的信息
 */
LIB860_API void Gsp_IedConnection_FreeRPCCallPDU(void* paramResponsePDU);

/**************************************************************** Log 相关接口 **************************************************************/

/**
 * @brief Gsp_IedConnection_GetLCBValues 获取日志控制块的值
 * @param self 链接信息
 * @param error 错误信息
 * @param paramLCBRefs 控制块refs
 * @return 调用返回
 */
LIB860_API void* Gsp_IedConnection_GetLCBValues(GspIedConnection self,
                                                GspIedClientError* error,
                                                const char* paramLCBRefs);

/**
 * @brief Gsp_LCBlock_isError 获取控制块的信息中是否包含错误
 * @param paramLCBInfo 日志控制块的信息
 * @return 是否含有错误信息
 */
LIB860_API bool Gsp_LCBlock_hasError(void* paramLCBInfo);

/**
 * @brief Gsp_LCBlock_getErrorCode 获取控制块信息中的错误代码
 * @param paramLCBInfo 日志控制块的信息
 * @return 错误代码
 */
LIB860_API GspIedClientError Gsp_LCBlock_getErrorCode(void* paramLCBInfo);

/**
 * @brief Gsp_LCBlock_getLogRef 获取日志控制块的 ref
 * @param paramLCBInfo 日志控制块信息
 * @return 是否启用
 */
LIB860_API const char* Gsp_LCBlock_getLogRef(void* paramLCBInfo);

/**
 * @brief Gsp_LCBlock_setLogRef 设置日志控制块的 ref
 * @param paramLCBInfo 日志控制块信息
 * @return 是否启用
 */
LIB860_API bool Gsp_LCBlock_setLogRef(void* paramLCBInfo, const char* paramLogRef);

/**
 * @brief Gsp_LCBlock_getLogEna 获取日志控制块是否启用的标记
 * @param paramLCBInfo 日志控制块信息
 * @return 是否启用
 */
LIB860_API bool Gsp_LCBlock_getLogEna(void* paramLCBInfo);

/**
 * @brief Gsp_LCBlock_setLogEna 设置日志控制块是否启用
 * @param paramLCBInfo 日志控制块信息
 * @param paramEna 是否启用
 */
LIB860_API bool Gsp_LCBlock_setLogEna(void* paramLCBInfo, bool paramEna);

/**
 * @brief Gsp_LCBlock_getDatset 获取日志控制块相关的数据集描述
 * @param paramLCBInfo 日志控制块信息
 * @return 数据集描述信息
 */
LIB860_API const char* Gsp_LCBlock_getDatset(void* paramLCBInfo);

/**
 * @brief Gsp_LCBlock_getIntgPd 获取日志控制块的周期数值
 * @param paramLCBInfo 日志控制块信息
 * @return 周期数值
 */
LIB860_API int Gsp_LCBlock_getIntgPd(void* paramLCBInfo);

/**
 * @brief Gsp_LCBlock_free 释放控制快的内存信息
 * @param paramLCBInfo 日志控制块信息
 */
LIB860_API void Gsp_LCBlock_free(void* paramLCBInfo);

/**
 * @brief Gsp_IedConnection_SetLCBValues 设置日志控制块
 * @param self 链接信息
 * @param error 错误描述
 * @param paramLCBRefs 日志控制块refs
 * @return 是否设置成功
 */
LIB860_API bool Gsp_IedConnection_SetLCBValues(GspIedConnection self,
                                               GspIedClientError* error,
                                               void* paramLCBRefs);

/**
 * @brief Gsp_IedConnection_QueryLogByTime 根据时间范围查询日志
 * @param self 链接信息
 * @param error 错误描述
 * @param paramLogRefs 日志refs
 * @param startTime 开始时间
 * @param stopTime 结束时间
 * @param entryID afterID
 * @return 日志列表
 */
LIB860_API GspLinkedList Gsp_IedConnection_QueryLogByTime(GspIedConnection self,
                                                          GspIedClientError* error,
                                                          const char* paramLogRefs,
                                                          const char* startTime,
                                                          const char* stopTime,
                                                          const char* afterEntryID);
}

#endif
