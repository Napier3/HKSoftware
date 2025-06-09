/*
 *  gsp_mms_client_connection.h
 *  mms层客户端链接API
 */

#ifndef GSP_MMS_CLIENT_CONNECTION_H_
#define GSP_MMS_CLIENT_CONNECTION_H_

#include "libdlt860_common_api.h"
#include "gsp_mms_common.h"
#include "gsp_mms_type_spec.h"
#include "gsp_mms_value.h"
#include "gsp_iso_connection_parameters.h"
#include "gsp_linked_list.h"
#include "gsp_tls_config.h"
#include "ACSIClass.h"
#include "dlt860_common.h"
#include "GetAllDataDefinitionRequestPDU.h"

using namespace GSP;

/**
 * mms 链接层的参数信息
 */
typedef struct sGspMmsConnectionParameters {
    int maxServOutstandingCalling;
    int maxServOutstandingCalled;
    int dataStructureNestingLevel;
    int maxAPDUSize;
    int maxASDUSize;
    uint8_t servicesSupported[11];
} GspMmsConnectionParameters;

/**
 * mms 服务识别信息
 */
typedef struct {
    char* vendorName;
    char* modelName;
    char* revision;
} GspMmsServerIdentity;

/**
 * mms 链接状态
 */
typedef enum {
    // 链接关闭
    GSP_MMS_CONNECTION_STATE_CLOSED,
    // 链接中
    GSP_MMS_CONNECTION_STATE_CONNECTING,
    // 已经链接
    GSP_MMS_CONNECTION_STATE_CONNECTED,
    // 链接关闭中
    GSP_MMS_CONNECTION_STATE_CLOSING
} GspMmsConnectionState;

/**
 * @brief mms 报告消息的处理回调
 * @param parameter 回调参数
 * @param reportID 报告ID
 * @param reportPDU 报告数据单元
 */
typedef void (*GspMmsInformationReportHandler) (void* parameter, GspLinkedList& reportPDU);

/**
 * mms 实例指针
 */
typedef struct sGspMmsConnection* GspMmsConnection;

/**
 * @brief ACSICLASS 对象类别
 */
typedef e_GSP_ACSIClass GspACSICLASS;

/**
 * @brief RefType ref 类别
 */
typedef enum{
    NOTHING = 0,
    LDNAME = 1,
    LNREFERENCE = 2
} GspRefType;

// 文件信息
typedef struct sGspFileFileAttribute* GspFileAttribute;
struct sGspFileFileAttribute {
    char* fileName;
    uint32_t fileSize;
    uint64_t lastModifyTime;
};

/*******************************************************************************
 * 链接管理类接口
 *******************************************************************************/

/**
 * @brief GspMmsConnection_create 创建一个 mms 链接
 * @return 链接对象
 */
LIB860_API GspMmsConnection GspMmsConnection_create(void);

/**
 * @brief MmsConnection_createSecure 创建一个 安全的 mms 链接
 * @param tlsConfig 证书信息
 * @return 链接对象
 */
LIB860_API GspMmsConnection GspMmsConnection_createSecure(GspTLSConfiguration tlsConfig);

/**
 * @brief MmsConnection_createNonThreaded 创建一个 non-threaded 模式的 mms 链接
 * 构造函数不会主动构造出来一个后台任务线程，使用者必须周期性的调用 MmsConnection_tick 确保任务被处理了
 * @param tlsConfig 认证信息
 * @return 链接对象
 */
LIB860_API GspMmsConnection GspMmsConnection_createNonThreaded(GspTLSConfiguration tlsConfig);


/**
 * 消息接受回调
 */
typedef void (*GspMmsRawMessageHandler) (void* parameter, uint8_t* message, int messageLength, bool received);

/**
 * @brief MmsConnection_setRawMessageHandler 设置原始数据处理回调
 * 该函数用来记录 原始 mms 消息，可用来调试或者开发一些调试工具， 该函数仅在stack_config.h中配置了 CONFIG_MMS_RAW_MESSAGE_LOGGING
 * 时才会起作用
 * @param self 链接对象
 * @param handler 处理函数
 * @param parameter 处理参数
 */
LIB860_API void GspMmsConnection_setRawMessageHandler(GspMmsConnection self,
                                                      GspMmsRawMessageHandler handler,
                                                      void* parameter);

/**
 * @brief MmsConnection_setFilestoreBasepath 设置虚拟文件存储的基础跟路径（文件服务使用）
 * 所有外部文件服务访问都将映射到相对于基目录的路径，只有在 stack_config.h 中设置了
 * CONFIG_SET_FILESTORE_BASEPATH_AT_RUNTIME 才可以起作用
 * @param self
 * @param basepath
 */
LIB860_API void GspMmsConnection_setFilestoreBasepath(GspMmsConnection self, const char* basepath);

/**
 * @brief MmsConnection_setRequestTimeout 设置链接请求的超时时间
 * @param self 链接对象
 * @param timeoutInMs 超时时间(毫秒)
 */
LIB860_API void GspMmsConnection_setRequestTimeout(GspMmsConnection self, uint32_t timeoutInMs);

/**
 * @brief MmsConnection_getRequestTimeout 获取链接请求的超时时间
 * @param self 链接对象
 * @return 超时时间(毫秒)
 */
LIB860_API uint32_t GspMmsConnection_getRequestTimeout(GspMmsConnection self);

/**
 * @brief MmsConnection_setConnectTimeout 设置链接超时时间
 * @param self 链接对象
 * @param timeoutInMs 超时时间(毫秒)
 */
LIB860_API void GspMmsConnection_setConnectTimeout(GspMmsConnection self, uint32_t timeoutInMs);

/**
 * @brief MmsConnection_setInformationReportHandler 设置链接的报告回调函数
 * 当mms链接接受到报告数据时，就会调用该函数设置的回调函数，使用者需要注意释放其中的 mmavalue
 * @param self 链接对象
 * @param handler 回调函数
 * @param parameter 回调函数的参数
 */
LIB860_API void GspMmsConnection_setInformationReportHandler(GspMmsConnection self,
                                                             GspMmsInformationReportHandler handler,
                                                             void* parameter);

/**
 * @brief MmsConnection_getIsoConnectionParameters 获取链接参数(tcp)
 * @param self 链接对象
 * @return 链接参数
 */
LIB860_API GspIsoConnectionParameters GspMmsConnection_getIsoConnectionParameters(GspMmsConnection self);

/**
 * @brief MmsConnection_getMmsConnectionParameters 获取链接参数(mms层面)
 * @param self 链接对象
 * @return 链接参数
 */
LIB860_API GspMmsConnectionParameters GspMmsConnection_getMmsConnectionParameters(GspMmsConnection self);

/**
 * mms 链接状态发生改变的回调函数
 */
typedef void (*GspMmsConnectionStateChangedHandler) (GspMmsConnection connection, void* parameter, GspMmsConnectionState newState);

/**
 * @brief MmsConnection_setConnectionStateChangedHandler 设置链接状态改变时的回调函数
 * @param self 链接对象
 * @param handler 回调函数指针
 * @param parameter 毁掉函数参数
 */
LIB860_API void GspMmsConnection_setConnectionStateChangedHandler(GspMmsConnection self,
                                                                  GspMmsConnectionStateChangedHandler handler,
                                                                  void* parameter);

/**
 * mms 链接丢失时的回调函数
 */
typedef void (*GspMmsConnectionLostHandler) (GspMmsConnection connection, void* parameter);

/**
 * @brief MmsConnection_setConnectionLostHandler 设置链接丢失时的回调函数
 * @param self 链接对象
 * @param handler 回调函数
 * @param handlerParameter 毁掉函数参数
 */
LIB860_API void GspMmsConnection_setConnectionLostHandler(GspMmsConnection self,
                                                          GspMmsConnectionLostHandler handler,
                                                          void* handlerParameter);

/**
 * @brief MmsConnection_destroy 销毁 mms 链接，并释放相关资源信息
 * @param self
 */
LIB860_API void GspMmsConnection_destroy(GspMmsConnection self);

/*******************************************************************************
 * 连接建立类接口
 *******************************************************************************/

/**
 * @brief MmsConnection_connect mms 建立链接到服务端(同步)
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param serverName 服务端名字
 * @param serverPort 服务端端口(如果是-1则用默认端口，mms 的端口是 8102, tls 服务的端口是 9102)
 * @return 链接结果
 */
LIB860_API bool GspMmsConnection_connect(GspMmsConnection self,
                                         GspMmsError* mmsError,
                                         const char* serverName,
                                         int serverPort,
										  const char* local_address = NULL);//zhouhj 20210929 增加客户端本地IP地址的绑定

/**
 * @brief MmsConnection_connectAsync mms 建立链接到服务端(异步)
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param serverName 服务名字
 * @param serverPort 服务端口
 */
LIB860_API void GspMmsConnection_connectAsync(GspMmsConnection self,
                                              GspMmsError* mmsError,
                                              const char* serverName,
                                              int serverPort,
											  const char* local_address = NULL);//zhouhj 20210929 增加客户端本地IP地址的绑定

/**
 * @brief MmsConnection_tick 链接状态机的处理流程
 * @param self 链接对象
 * @return true, 该链接处于等待 或者 挂起状态时， false, 该线程处于busy状态，应该尽快的再次调用该函数
 */
LIB860_API bool GspMmsConnection_tick(GspMmsConnection self);

/**
 * @brief MmsConnection_close 关闭 mms 链接
 * @param self 链接对象
 */
LIB860_API void GspMmsConnection_close(GspMmsConnection self);

/**
 * @brief MmsConnection_abort 立刻中断与服务端的链接
 * 构造报文并发送给服务端
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param reasonCode 中断错误码
 */
LIB860_API void GspMmsConnection_abort(GspMmsConnection self,
                                       GspMmsError* mmsError,
                                       uint8_t reasonCode,
                                       uint8_t* associationId);

/**
 * @brief MmsConnection_conclude 取消并释放链接(同步)
 * @param self 链接对象
 * @param mmsError 错误代码
 */
LIB860_API void GspMmsConnection_conclude(GspMmsConnection self,
                                          GspMmsError* mmsError,
                                          uint8_t* associationId);

/**
 * 异步取消链接
 */
typedef void (*GspMmsConcludeAbortHandler) (void* parameter, GspMmsError mmsError, bool success);


/**
 * @brief MmsConnection_concludeAsync 取消并释放链接(异步)
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param handler 回调函数
 * @param parameter 毁掉函数参数
 */
LIB860_API void GspMmsConnection_concludeAsync(GspMmsConnection self,
                                               GspMmsError* mmsError,
                                               uint8_t* associationId);

/**
 * 关联接口回调
 */
typedef void (*GspMmsAssocaiationHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief MmsConnection_association 关联服务
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramServerAccessPointReference 接入点信息
 */
LIB860_API char* GspMmsConnection_associationAsync(GspMmsConnection self,
                                                   GspMmsError* mmsError,
                                                   const char* paramServerAccessPointReference);


/**********************************************************************************************
** 模型数据类接口
************************************************************************************************/


/**
 * @brief MmsConnection_getServerDirectory 获取服务器上的所有 ld info
 * @param self 链接对象
 * @param mmsError 错误代码
 * @return 逻辑设备列表
 */
LIB860_API GspLinkedList GspMmsConnection_getServerDirectory(GspMmsConnection self, GspMmsError* mmsError);

/**
 * 获取数据定义的回调处理
 */
typedef void (*GspMmsGetDataDefinitionHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList nameList, bool moreFollows);

/**
 * 获取模型或者值信息回调处理
 */
typedef void (*GspMmsGetModelOrDataHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList nameList, bool moreFollows);

/**
 * @brief MmsConnection_getLogicDevices 获取服务器上的所有 ld info
 * @param self 链接对象
 * @param mmsError 错误代码
 * @return 逻辑节点列表
 */
LIB860_API GspLinkedList GspMmsConnection_getLogicDevices(GspMmsConnection self, GspMmsError* mmsError, const char* paramLDName);


/**
 * @brief MmsConnection_GetLogicalNodeDirectory 获取逻辑节点下的 DO
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramClass 对象类
 * @param reference 参引信息
 * @return DO信息列表
 */
LIB860_API GspLinkedList GspMmsConnection_getLogicalNodeDirectory(GspMmsConnection self,
                                                                  GspMmsError* mmsError,
                                                                  GspACSICLASS paramClass,
                                                                  const char* reference);

/**
 * @brief MmsConnection_getAllDataDefinition 获取所有数据定义
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramFc 功能约束
 * @param reference 参引串
 * @paramRefType 参引类型
 * @return DO信息列表
 */
LIB860_API GspLinkedList GspMmsConnection_getAllDataDefinition(GspMmsConnection self,
                                                               GspMmsError* mmsError,
                                                               GspFunctionalConstraint paramFc,
                                                               const char* reference,
                                                               GspRefType paramRefType);

/**********************************************************************************************
** 数据类接口
************************************************************************************************/

/**
 * @brief MmsConnection_getAllDataValues 获取所有数据值
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramFc 功能约束
 * @param reference 参引串
 * @param paramRefType 参引类型
 * @return 数据值
 */
LIB860_API GspLinkedList GspMmsConnection_getAllDataValues(GspMmsConnection self,
                                                           GspMmsError* mmsError,
                                                           GspFunctionalConstraint paramFc,
                                                           const char* reference,
                                                           GspRefType paramRefType);

/**
 * @brief MmsConnection_getAllCBValues 读所有控制块值
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramClass 对象类别
 * @param reference 参引串
 * @param paramRefType 餐饮类型
 * @return 数据列表
 */
LIB860_API GspLinkedList GspMmsConnection_getAllCBValues(GspMmsConnection self,
                                                         GspMmsError* mmsError,
                                                         GspACSICLASS paramClass,
                                                         const char* reference,
                                                         GspRefType paramRefType);


/**
 * 获取数据值回调接口
 */
typedef void (*GspMmsGetDataValuesHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief MmsConnection_getDataValues 获取数据值
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramFc 功能约束
 * @param reference 参引串
 * @return 数据值
 */
LIB860_API GspLinkedList GspMmsConnection_getDataValues(GspMmsConnection self,
                                                        GspMmsError* mmsError,
                                                        GspLinkedList refsFcList);

/**
 * 获取数据定义回调接口
 */
typedef void (*GspMmsDataDefinitionHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_getDataDefinition 获取数据定义
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramFc 功能约束
 * @param reference 参引串
 * @return 数据值
 */
LIB860_API GspLinkedList GspMmsConnection_getDataDefinition(GspMmsConnection self,
                                                            GspMmsError* mmsError,
                                                            GspLinkedList refsFcList);

/**
 * 写数据值回调接口
 */
typedef void (*GspMmsSetDataValuesHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief MmsConnection_setDataValues 设置数据值
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramFc 功能约束
 * @param reference 参引串
 * @return 数据值
 */
LIB860_API GspLinkedList GspMmsConnection_setDataValues(GspMmsConnection self,
                                                        GspMmsError* mmsError,
                                                        GspLinkedList dataRefsFcList);

/**********************************************************************************************
** 数据集类接口
************************************************************************************************/

/**
 * @brief GspMmsConnection_getDataSetDirectory 获取数据集目录
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramReference 数据集目录的refs
 * @return 数据集目录数据
 */
LIB860_API GspLinkedList GspMmsConnection_getDataSetDirectory(GspMmsConnection self,
                                                              GspMmsError* mmsError,
                                                              const char* paramReference);

/**
 * @brief GspMmsConnection_getDataSetValues 获取数据集值
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramReference 数据集目录的refs
 * @return 数据集目录数据
 */
LIB860_API GspLinkedList GspMmsConnection_getDataSetValues(GspMmsConnection self,
                                                           GspMmsError* mmsError,
                                                           const char* paramReference);

/**********************************************************************************************
** 文件类接口
************************************************************************************************/

/**
 * 获取文件目录回调
 */
typedef void (*GspMmsFileDirectoryHandler) (void* outputFiles, void* paramInputFiles);

/**
 * 获取文件目录回调(mmsconnection 层)
 */
typedef void (*GspMmsConnectionFileDirectoryHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, void* paramNewFileList, bool moreFollows);

/**
 * @brief MmsConnection_getFileDirectory 获取服务器文件目录(同步接口)
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param pathName 路径名字
 * @param startTime 开始时间
 * @param endTime 结束时间
 * @param fileAfter 目录位置
 * @param fileDirResHandler 数据返回的处理回调
 * @param paramHandlerParam 数据处理毁掉的参数
 * @return
 */
LIB860_API bool GspMmsConnection_getFileDirectory(GspMmsConnection self,
                                                  GspMmsError* mmsError,
                                                  const char* pathName,
                                                  const char* startTime,
                                                  const char* endTime,
                                                  const char* fileAfter,
                                                  GspMmsFileDirectoryHandler fileDirResHandler,
                                                  void* paramHandlerParam);

/**
 * @brief 读文件函数指针
 * @param parameter 上层传入的参数
 * @param buffer 文件数据
 * @param bytesReceived 收到的文件内容字节数
 */
typedef void (*GspMmsFileReadHandler) (void* parameter, uint8_t* buffer, uint32_t bytesReceived, bool endFlag);

/**
 * @brief 文件读回调(报文到达时回调)
 * @param invokeId 回应的invokid
 * @param parameter 回调参数
 * @param mmsError 错误描述信息
 * @param buffer 文件数据内容
 * @param byteReceived 文件长度
 * @param moreFollows 是否有后续的数据
 */
typedef void (*GspMmsConnectionFileReadHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList buffer, bool moreFollows);

/**
 * @brief 下载文件(mms层)
 * @param self mms链接对象
 * @param mmsError mms 错误信息
 * @param fileName 待下载的文件的绝对路径
 * @param startPostion 文件下载的开始位置
 * @param handler 文件数据回调指针
 * @param paramHandlerParam 文件数据回调指针数据
 */
LIB860_API bool GspMmsConnection_getFile(GspMmsConnection self,
                                         GspMmsError* mmsError,
                                         const char* fileName,
                                         uint32_t startPostion,
                                         GspMmsFileReadHandler handler,
                                         void* paramHandlerParam);

/**
 * @brief 写文件回调
 * @param invokeId 回应的invokid
 * @param parameter 请求时传入的参数
 * @param mmsError mms 错误信息
 * @param buffer 数据值
 */
typedef void (*GspMmsConnectionSetFileHandler)(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList buffer);

/**
 * @brief GspMmsConnection_setFile 写文件(mms层)
 * @param self mms链接对象
 * @param mmsError mms 错误信息
 * @param fileName 文件名字
 * @param startPostion 文件开始位置
 * @param fileData 文件数据
 * @param fileDataSize 文件尺寸
 * @param endFlag 是否是文件结尾
 * @return
 */
LIB860_API bool GspMmsConnection_setFile(GspMmsConnection self,
                                         GspMmsError* mmsError,
                                         const char* fileName,
                                         uint32_t startPostion,
                                         const char* fileData,
                                         uint32_t fileDataSize,
                                         bool endFlag);

/**********************************************************************************************
** 报告类接口
************************************************************************************************/

/**
 * @brief 获取缓存报告控制块的值(mms层)
 * @param self mms链接对象
 * @param mmsError mms 错误信息
 * @param brcbReference 报告refs链接
 * @return 缓存报告控制块的值
 */
LIB860_API GspLinkedList GspMmsConnection_getBRCBValues(GspMmsConnection self,
                                                        GspMmsError* mmsError,
                                                        const char* brcbReference);

/**
 * @brief 设置报告控制块值回调
 * @param invokeId 回应的invokid
 * @param parameter 请求时传入的参数
 * @param mmsError mms 错误信息
 * @param buffer 数据值
 */
typedef void (*GspSetRCBValuesHandler)(uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList buffer);

/**
 * @brief 设置缓存报告控制块的值(mms层)
 * @param self mms链接对象
 * @param mmsError mms 错误信息
 * @param brcbControlBlk 缓存报告控制块的值
 */
LIB860_API GspLinkedList GspMmsConnection_setBRCBValues(GspMmsConnection self,
                                                        GspMmsError* mmsError,
                                                        BRCBControlBlk brcbControlBlk);


/**
 * @brief 获取非缓存报告控制块的值(mms层)
 * @param self mms链接对象
 * @param mmsError mms 错误信息
 * @param brcbReference 报告refs链接
 * @return 缓存报告控制块的值
 */
LIB860_API GspLinkedList GspMmsConnection_getURCBValues(GspMmsConnection self,
                                                        GspMmsError* mmsError,
                                                        const char* brcbReference);

/**
 * @brief 设置非缓存报告控制块的值(mms层)
 * @param self mms链接对象
 * @param mmsError mms 错误信息
 * @param urcbControlBlk 缓存报告控制块的值
 */
LIB860_API GspLinkedList GspMmsConnection_setURCBValues(GspMmsConnection self,
                                                        GspMmsError* mmsError,
                                                        URCBControlBlk urcbControlBlk);


/**********************************************************************************************
** 定值类接口
************************************************************************************************/

/**
 * 选择定值类回调接口
 */
typedef void (*GspMmsSelectSGHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_selectActiveSG 选择激活定值组
 * @param self mms链接对象
 * @param mmsError 错误描述
 * @param sgcbReference 定值报告控制块 refs
 * @param settingGroupNumber 定值组号
 * @return 是否切换成功
 */
LIB860_API bool GspMmsConnection_selectActiveSG(GspMmsConnection self,
                                                GspMmsError* mmsError,
                                                const char* sgcbReference,
                                                uint8_t settingGroupNumber);

/**
 * @brief GspMmsConnection_selectEditSG 选择编辑定值组
 * @param self mms链接对象
 * @param mmsError 错误描述
 * @param sgcbReference 定值报告控制块 refs
 * @param settingGroupNumber 定值组号
 * @return 是否切换成功
 */
LIB860_API bool GspMmsConnection_selectEditSG(GspMmsConnection self,
                                              GspMmsError* mmsError,
                                              const char* sgcbReference,
                                              uint8_t settingGroupNumber);

/**
 * 获取定值组控制块回调接口
 */
typedef void (*GspMmsSGCBValuesHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_getSGCBValues 获取定值控制块值
 * @param self mms 链接对象
 * @param mmsError 错误描述
 * @param sgcbReference 定值报告控制块 refs
 * @return 控制块值信息
 */
LIB860_API GspLinkedList GspMmsConnection_getSGCBValues(GspMmsConnection self,
                                                        GspMmsError* mmsError,
                                                        const char* sgcbReference);

/**
 * 获取编辑定值组值回调接口
 */
typedef void (*GspMmsGetEditSGValuesHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_getEditSGValues 获取编辑定值组的值
 * @param self mms 链接对象
 * @param mmsError 错误描述
 * @param paramList 参数列表
 * @return 编辑区定值组的值
 */
LIB860_API GspLinkedList GspMmsConnection_getEditSGValues(GspMmsConnection self,
                                                          GspMmsError* mmsError,
                                                          GspLinkedList paramList);

/**
 * 修改编辑定值组值回调接口
 */
typedef void (*GspMmsSetEditSGValuesHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_setEditSGValues 修改编辑定值组的值
 * @param self mms 链接对象
 * @param mmsError 错误描述
 * @param paramList 参数列表
 * @return 是否修改成功
 */
LIB860_API bool GspMmsConnection_setEditSGValues(GspMmsConnection self,
                                                 GspMmsError* mmsError,
                                                 GspLinkedList paramList);

/**
 * 确认修改编辑定值组值回调接口
 */
typedef void (*GspMmsConfirmEditSGValuesHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_confirmEditSGValues 确认修改编辑定值组的值
 * @param self 链接对象
 * @param mmsError 错误描述
 * @param sgcbReference 定值的refs串
 * @return 是否确认成功
 */
LIB860_API bool GspMmsConnection_confirmEditSGValues(GspMmsConnection self,
                                                     GspMmsError* mmsError,
                                                     const char* sgcbReference);

/**********************************************************************************************
*  控制类接口
************************************************************************************************/
/**
 * 选择请求回调
 */
typedef void (*GspMmsSelectHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_select 控制选择
 * @param self 链接对象
 * @param mmsError 错误信息
 * @param controlReference 控制对象refs
 * @return 是否选择成功
 */
LIB860_API bool GspMmsConnection_select(GspMmsConnection self,
                                        GspMmsError* mmsError,
                                        const char* controlReference);

/**
 * 控制操作回调
 */
typedef void (*GspMmsOperateHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_operate 控制操作
 * @param self 链接对象
 * @param mmsError 错误描述
 * @param controlReference 控制对象 refs
 * @param paramValue 数据值
 * @param syncCheck 同期检查
 * @param lockCheck 锁控检查
 * @return 控制操作结果
 */
LIB860_API GspLinkedList GspMmsConnection_operate(GspMmsConnection self,
                                                  GspMmsError* mmsError,
                                                  const char* controlReference,
                                                  GspMmsValue* paramValue,
                                                  Originator__orCat paramOrCat,
                                                  const char* paramOrIdent,
                                                  bool syncCheck,
                                                  bool lockCheck,
                                                  bool test);

/**
 * 带值选择控制操作回调
 */
typedef void (*GspMmsSelectWithValueHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_selectWithValue 控制操作
 * @param self 链接对象
 * @param mmsError 错误描述
 * @param controlReference 控制对象 refs
 * @param paramValue 数据值
 * @param paramOrCat origin -> orcat
 * @param paramOrIdent origin -> orident
 * @return 控制操作结果
 */
LIB860_API GspLinkedList GspMmsConnection_selectWithValue(GspMmsConnection self,
                                                          GspMmsError* mmsError,
                                                          const char* controlReference,
                                                          GspMmsValue* paramValue,
                                                          Originator__orCat paramOrCat,
                                                          const char* paramOrIdent,
                                                          bool syncCheck,
                                                          bool lockCheck,
                                                          bool test);

/**********************************************************************************************
*  测试类接口
************************************************************************************************/

/**
 * 测试帧回调接口
 */
typedef void (*GspMmsTestHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError);

/**
 * @brief GspMmsConnection_test 测试帧数据
 * @param self 链接对象
 * @param mmsError 错误描述
 * @param reqFlag 请求还是回应
 * @return 是否发送成功
 */
LIB860_API bool GspMmsConnection_test(GspMmsConnection self, GspMmsError* mmsError, bool reqFlag);


/**********************************************************************************************
*  RPC类接口
************************************************************************************************/

/**
 * 获取RPC接口回调接口
 */
typedef void (*GspMmsGetRpcInterfaceDirectoryHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_getRpcInterfaceDirectory 获取数据值
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param reference 参引串
 * @return 数据值
 */
LIB860_API GspLinkedList GspMmsConnection_getRpcInterfaceDirectory(GspMmsConnection self,
                                                                   GspMmsError* mmsError,
                                                                   const char* paramRefsAfter);

/**
 * 获取RPC方法回调接口
 */
typedef void (*GspMmsGetRpcMethodDirectoryHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief MmsConnection_getDataValues 获取数据值
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramInterface 参引串
 * @param paramRefsAfter 参引串
 * @return 数据值
 */
LIB860_API GspLinkedList GspMmsConnection_getRpcMethodDirectory(GspMmsConnection self,
                                                                GspMmsError* mmsError,
                                                                const char* paramInterface,
                                                                const char* paramRefsAfter);


/**
 * 获取RPC接口定义接口
 */
typedef void (*GspMmsGetRpcInterfaceDefinitionHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_getRpcInterfaceDefinition 获取 RPC 接口定义
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramInterfaceRef 接口refs
 * @param paramRefsAfter refsAfter串
 * @return 数据值
 */
LIB860_API GspLinkedList GspMmsConnection_getRpcInterfaceDefinition(GspMmsConnection self,
                                                                    GspMmsError* mmsError,
                                                                    const char* paramInterfaceRef,
                                                                    const char* paramRefsAfter);

/**
 * 获取RPC接口定义接口
 */
typedef void (*GspMmsGetRpcMethodDefinitionHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_getRpcMethodDefinition 获取 RPC 方法定义
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramMethodRef 接口refs列表
 * @return 数据值
 */
LIB860_API GspLinkedList GspMmsConnection_getRpcMethodDefinition(GspMmsConnection self,
                                                                 GspMmsError* mmsError,
                                                                 GspLinkedList paramMethodRef);

/**
 * RPCCall 接口回调
 */
typedef void (*GspMmsRpcCallHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_getRpcMethodDefinition RPC 调用
 * @param self 链接对象
 * @param mmsError 错误代码
 * @param paramFuncation 方法名字
 * @param paramData 请求参数
 * @param paramCallID 回调ID
 * @return
 */
LIB860_API GspLinkedList GspMmsConnection_RpcCall(GspMmsConnection self,
                                                  GspMmsError* mmsError,
                                                  const char* paramFuncation,
                                                  GspMmsValue* paramData,
                                                  const char* paramCallID);

/**********************************************************************************************
*  log 类接口
************************************************************************************************/

/**
 * GetLCBValues 接口回调
 */
typedef void (*GspMmsGetLCBValuesHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_getLCBValues 获取日志控制块的值
 * @param self
 * @param mmsError
 * @param paramMethodRef
 * @return
 */
LIB860_API GspLinkedList GspMmsConnection_getLCBValues(GspMmsConnection self,
                                                       GspMmsError* mmsError,
                                                       GspLinkedList paramLCBRefsList);

/**
 * SetLCBValues 接口回调
 */
typedef void (*GspMmsSetLCBValuesHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_setLCBValues 获取日志控制块的值
 * @param self
 * @param mmsError
 * @param paramMethodRef
 * @return
 */
LIB860_API GspLinkedList GspMmsConnection_setLCBValues(GspMmsConnection self,
                                                       GspMmsError* mmsError,
                                                       GspLinkedList paramLCBRefsList);

/**
 * queryLogByTime 接口回调
 */
typedef void (*GspMmsQueryLogByTimeHandler) (uint32_t invokeId, void* parameter, GspMmsError mmsError, GspLinkedList retList);

/**
 * @brief GspMmsConnection_queryLogByTime
 * @param self 链接信息
 * @param error 错误描述
 * @param paramLogRefs 日志refs
 * @param startTime 开始时间
 * @param stopTime 结束时间
 * @param entryID afterID
 * @return 日志列表
 */
LIB860_API GspLinkedList GspMmsConnection_queryLogByTime(GspMmsConnection self,
                                                          GspMmsError* error,
                                                          const char* paramLogRefs,
                                                          const char* startTime,
                                                          const char* stopTime,
                                                          const char* afterEntryID);
#endif /* GSP_MMS_CLIENT_CONNECTION_H_ */
