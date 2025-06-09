/*
 *  mms_msg_internal.h
 *  mms 客户端内部使用接口
 */

#ifndef GSP_MMS_MSG_INTERNAL_H_
#define GSP_MMS_MSG_INTERNAL_H_
#include "gsp_linked_list.h"
#include "gsp_mms_client_connection.h"
#include "iso_client_connection.h"
#include "gsp_hal_thread.h"
#include "mms_common_internal.h"
#include "asn_inc.h"

#ifndef CONFIG_MMS_RAW_MESSAGE_LOGGING
#define CONFIG_MMS_RAW_MESSAGE_LOGGING 0
#endif

#ifndef DEBUG_MMS_CLIENT
#define DEBUG_MMS_CLIENT 1  //zhouhj 20220531 用于调试
#endif

// 链接激活状态
#define GSP_CONCLUDE_STATE_CONNECTION_ACTIVE 0
// 链接请求状态
#define GSP_CONCLUDE_STATE_REQUESTED 1
// 链接拒绝状态
#define GSP_CONCLUDE_STATE_REJECTED 2
// 链接接受状态
#define GSP_CONCLUDE_STATE_ACCEPTED 3


// mms 链接信息，内部使用
struct sGspMmsConnection {

    // 下一次 invokeid 的信号量
    GspSemaphore nextInvokeIdLock;

    // 下一次invokeid
    uint16_t nextInvokeId;

    // assocationid
    uint8_t* associationId;

    // 接口调用信号量
    GspSemaphore outstandingCallsLock;

    // 接口调用
    GspMmsOutstandingCall outstandingCalls;

    // 请求的超时时间
    uint32_t requestTimeout;
    
    // 链接到服务器时的超时时间
    uint32_t connectTimeout;

    // 链接客户端
    GspIsoClientConnection isoClient;

#if (CONFIG_MMS_THREADLESS_STACK == 0)
    // 链接处理线程
    GspThread connectionHandlingThread;
    // 是否创建线程
    bool createThread;
    // 线程是否在运行中
    bool connectionThreadRunning;
#endif

    // mms 的链接状态
    volatile GspMmsConnectionState connectionState;
    GspSemaphore associationStateLock;

    // mms链接相关参数
    GspMmsConnectionParameters parameters;
    GspIsoConnectionParameters isoParameters;

    // mms链接状态改变时的回调函数指针
    GspMmsConnectionStateChangedHandler stateChangedHandler;
    void* stateChangedHandlerParameter;

    // mms链接消息接受处理的回调函数指针
    GspMmsInformationReportHandler reportHandler;
    void* reportHandlerParameter;

    // mms链接关闭时的回调函数指针
    GspMmsConnectionLostHandler connectionLostHandler;
    void* connectionLostHandlerParameter;

    // mms链接终止的回调函数指针
    GspMmsConcludeAbortHandler concludeHandler;
    void* concludeHandlerParameter;
    uint64_t concludeTimeout;

#if (CONFIG_MMS_RAW_MESSAGE_LOGGING == 1)
    // mms 原始信息日志处理函数指针
    void* rawMmsMessageHandler;
    void* rawMmsMessageHandlerParameter;
#endif

#if (CONFIG_SET_FILESTORE_BASEPATH_AT_RUNTIME == 1)
    // 文件存储时基础路径
    char* filestoreBasepath;
#endif
	bool m_bResponseError;//zhouhj 20220110 增加用于标识服务端响应报文中是否标识Error

#endif /* (MMS_OBTAIN_FILE_SERVICE == 1) */
};

/********************************************* 链接相关底层接口 ***************************************************/

/**
 * @brief mmsClient_createAssociateNegotiateRequest 关联协商请求数据负载封装
 * @param self 链接对象
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramApduSize apdu 大小
 * @param paramAsduSize asdu 大小
 */
LIB860_INTERNAL bool mmsClient_createAssociateNegotiateRequest(GspMmsConnection self,
                                                               GspByteBuffer* outMessage,
                                                               uint16_t invokeId,
                                                               uint16_t paramApduSize,
                                                               uint32_t paramAsduSize);

/**
 * @brief mmsClient_parseAssociateNegotiateResponse 解析关联协商的回应
 * @param message 回应的原始消息
 * @param invokeId 消息ID
 */
LIB860_INTERNAL bool  mmsClient_parseAssociateNegotiateResponse(GspByteBuffer* message, 
                                                                uint16_t* invokeId);


/**
 * @brief mmsClient_createAssociateRequest 创建关联请求
 * @param self 链接诶对象
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramAccessPoint 接入点
 * @return 创建结果
 */
LIB860_INTERNAL bool mmsClient_createAssociateRequest(GspMmsConnection self,
                                                      GspByteBuffer* outMessage,
                                                      uint16_t invokeId,
                                                      uint8_t* paramAccessPoint);

/**
 * @brief mmsClient_parseAssociateResponse 解析关联的回应
 * @param message 回应的原始消息
 * @param outData 回复消息
 * @return
 */
LIB860_INTERNAL bool mmsClient_parseAssociateResponse(GspByteBuffer* message, 
                                                      GspLinkedList *outData);

/**
 * @brief MmsConnection_getFilestoreBasepath mms 链接获取文件存储路径的基础路径信息
 * @param self 链接对象
 * @return 路径信息
 */
LIB860_INTERNAL char* MmsConnection_getFilestoreBasepath(GspMmsConnection self);


/**
 * @brief mmsClient_parseServerErrorResponse 解析服务错误代码
 * @param message 消息信息
 * @param invokeId 消息ID
 * @return 错误代码
 */
LIB860_INTERNAL uint16_t mmsClient_parseServerErrorResponse(GspByteBuffer* message, 
                                                            uint16_t* invokeId);

/**
 * @brief mmsClient_createAbortRequest 创建终止链接数据负载
 * @param self 链接对象
 * @param outMessage 封装后的协议消息
 * @param invokeId invokId
 * @param reasonCode 终止原因
 */
LIB860_INTERNAL bool mmsClient_createAbortRequest(GspMmsConnection self,
                                                  GspByteBuffer* outMessage,
                                                  uint16_t invokeId,
                                                  uint8_t reasonCode,
                                                  uint8_t* associationId);

/**
 * @brief mmsClient_createConcludeRequest 创建释放链接请求
 * @param self 链接对象
 * @param message 封装后的协议消息
 * @param invokeId 消息id
 * @param associationId 关联ID
 * @return
 */
LIB860_INTERNAL bool mmsClient_createConcludeRequest(GspMmsConnection self,
                                                     GspByteBuffer* outMessage,
                                                     uint16_t invokeId,
                                                     uint8_t* associationId);

/********************************************* 模型相关底层接口 ***************************************************/

/**
 * @brief mmsClient_createGetServerDirectoryRequest 创建获取服务目录的请求帧
 * @param self 链接对象
 * @param message 封装后的协议消息
 * @param invokeId invokId
 * @param referenceAfter ref串(获取该对象名字的后续数据)
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsClient_createGetServerDirectoryRequest(GspMmsConnection self,
                                                               GspByteBuffer* outMessage,
                                                               uint16_t invokeId,
                                                               const char* referenceAfter);

/**
 * @brief mmsClient_parseGetServerDiecttoryResponse 解析获取逻辑目录的应答帧
 * @param message 原始消息
 * @param outServerDirectory 输出信息
 * @return 是否解析成功
 */
LIB860_INTERNAL bool mmsClient_parseGetServerDiecttoryResponse(GspByteBuffer* message,
                                                               GspLinkedList *outServerDirectory);


/**
 * @brief mmsClient_createGetLogicalDeviceDirectoryRequest 创建获获取逻辑设备的请求帧
 * @param self 链接对象
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramLDName 逻辑设备的名字
 * @param referenceAfter ref串(获取该对象名字的后续数据)
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsClient_createGetLogicalDeviceDirectoryRequest(GspMmsConnection self,
                                                                      GspByteBuffer* outMessage,
                                                                      uint16_t invokeId,
                                                                      const char* paramLDName,
                                                                      const char* referenceAfter);

/**
 * @brief mmsClient_parseGetLogicalDeviceDirectoryResponse 解析获取逻辑设备的应答帧
 * @param message 原始消息
 * @param outList 输出消息列表
 * @return 是否解析成功
 */
LIB860_INTERNAL bool mmsClient_parseGetLogicalDeviceDirectoryResponse(GspByteBuffer* message,
                                                                      GspLinkedList *outList);

/**
 * @brief mmsClient_createGetLogicalNodeRequest 创建逻辑节点请求帧
 * @param self 链接对象
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param reference 参引信息
 * @param referenceAfter ref串(获取该对象名字的后续数据)
 * @param paramType 对象类型
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsClient_createGetLogicalNodeRequest(GspMmsConnection self,
                                                           GspByteBuffer* outMessage,
                                                           uint16_t invokeId,
                                                           const char* reference,
                                                           const char* referenceAfter,
                                                           GspACSICLASS paramType);

/**
 * @brief mmsClient_parseLogicalNodeResponse 解析获取逻辑节点的应答帧
 * @param message 原始消息
 * @param outList 输出消息列表
 * @return
 */
bool mmsClient_parseLogicalNodeResponse (GspByteBuffer* message,
                                         GspLinkedList *outList);


/**
 * @brief mmsClient_createGetAllDataDefinition 创建获取数据定义的请求
 * @param self 链接对象
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param reference 参引信息
 * @param referenceAfter ref串(获取该对象名字的后续数据)
 * @param paramFC 功能约束
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsClient_createGetAllDataDefinitionRequest(GspMmsConnection self,
                                                                 GspByteBuffer* outMessage,
                                                                 uint16_t invokeId,
                                                                 const char* reference,
                                                                 const char* referenceAfter,
                                                                 GspFunctionalConstraint paramFC,
                                                                 GspRefType paramRefType);

/**
 * @brief mmsClient_parseGetAllDataDefinitionResponse 解析获取的所有数据定义
 * @param message 原始消息
 * @param outList 输出消息列表
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsClient_parseGetAllDataDefinitionResponse (GspByteBuffer* message,
                                                                  GspLinkedList *outList);

/********************************************* 读值相关底层接口 ***************************************************/

/**
 * @brief mmsClient_createGetAllDataValuesRequest 创建获取数据值的请求
 * @param self 链接对象
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param reference 参引信息
 * @param referenceAfter ref串(获取该对象名字的后续数据)
 * @param paramFC 功能约束
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsClient_createGetAllDataValuesRequest(GspMmsConnection self,
                                                             GspByteBuffer* outMessage,
                                                             uint16_t invokeId,
                                                             const char* reference,
                                                             const char* referenceAfter,
                                                             GspFunctionalConstraint paramFC,
                                                             GspRefType paramRefType);

/**
 * @brief mmsClient_parseGetAllDataValuesResponse 解析获取所有数据
 * @param message 原始消息
 * @param outList 输出消息列表
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsClient_parseGetAllDataValuesResponse(GspByteBuffer* message,
                                                             GspLinkedList *outList);


/**
 * @brief mmsCLient_createGetAllCBValuesRequest 获取所有控制块值
 * @param self 链接对象
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param reference 参引信息
 * @param referenceAfter ref串(获取该对象名字的后续数据)
 * @param paramRefType ref类型
 * @param paramType 类别类型
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsCLient_createGetAllCBValuesRequest(GspMmsConnection self,
                                                           GspByteBuffer* outMessage,
                                                           uint16_t invokeId,
                                                           const char* reference,
                                                           const char* referenceAfter,
                                                           GspRefType paramRefType,
                                                           GspACSICLASS paramType);

/**
 * @brief mmsClient_parseGetAllCBValuesResponse 解析获取所有控制块值
 * @param message 原始消息
 * @param outList 输出消息列表
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsClient_parseGetAllCBValuesResponse(GspByteBuffer* message,
                                                           GspLinkedList *outList);


/**
 * @brief mmsCLient_createGetDataValuesRequest 获取数据值
 * @param self 链接对象
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param refsFcList 带有功能约束的refs列表
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsCLient_createGetDataValuesRequest(GspMmsConnection self,
                                                          GspByteBuffer* outMessage,
                                                          uint16_t invokeId,
                                                          GspLinkedList refsFcList);

/**
 * @brief mmsClient_parseGetDataValuesResponse 解析获取所有数据
 * @param message 原始消息
 * @param outList 输出消息列表
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsClient_parseGetDataValuesResponse(GspByteBuffer* message,
                                                          GspLinkedList *outList);

/**
 * @brief mmsCLient_createGetDataDefinitionRequest 获取数据值
 * @param self 链接对象
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param refsFcList 带有功能约束的refs列表
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsCLient_createGetDataDefinitionRequest(GspMmsConnection self,
                                                              GspByteBuffer* outMessage,
                                                              uint16_t invokeId,
                                                              GspLinkedList refsFcList);

/**
 * @brief mmsClient_parseGetDataValuesResponse 解析获取所有数据
 * @param message 原始消息
 * @param outList 输出消息列表
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsClient_parseGetDataDefinitionResponse(GspByteBuffer* message,
                                                              GspLinkedList *outList);

/********************************************* 写值相关底层接口 ***************************************************/

/**
 * @brief mmsCLient_createSetDataValuesRequest 写数据值
 * @param self 链接对象
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param refsFcList 带有功能约束的数据列表
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsCLient_createSetDataValuesRequest(GspMmsConnection self,
                                                          GspByteBuffer* outMessage,
                                                          uint16_t invokeId,
                                                          GspLinkedList dataFcList);

/**
 * @brief mmsClient_parseGetDataValuesResponse 解析获取所有数据
 * @param message 原始消息
 * @param outList 输出消息列表
 * @return 是否封装成功
 */
LIB860_INTERNAL bool mmsClient_parseSetDataValuesResponse(GspByteBuffer* message,
                                                          GspLinkedList *outList);


/********************************************* 文件相关底层接口 ***************************************************/

/**
 * @brief mmsCLient_createGetDirectoryRequest 获取文件目录
 * @param self 链接对象
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param pathName 路径名字
 * @param startTime 开始时间
 * @param endTime 结束时间
 * @param fileAfter 在那个文件后
 * @return 是否编码成功
 */
LIB860_INTERNAL bool mmsCLient_createGetDirectoryRequest(GspMmsConnection self,
                                                         GspByteBuffer* outMessage,
                                                         uint16_t invokeId,
                                                         const char* pathName,
                                                         const char* startTime,
                                                         const char* endTime,
                                                         const char* fileAfter);

/**
 * @brief mmsClient_parseGetDirecttoryResponse 解析获取文件目录
 * @param message 原始消息
 * @param outServerDirectory 解析后的目录
 * @return 是否解析成功
 */
LIB860_INTERNAL bool mmsClient_parseGetDirecttoryResponse(GspByteBuffer* message,
                                                          GspLinkedList* outServerDirectory);

/**
 * @brief mmsCLient_createGetDirectoryRequest 获取文件目录
 * @param self 链接对象
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param fileName 文件名字
 * @param startPostion 开始位置
 * @return 是否编码成功
 */
LIB860_INTERNAL bool mmsClient_createGetFileRequest(GspMmsConnection self,
                                                    GspByteBuffer* outMessage,
                                                    uint16_t invokeId,
                                                    const char* fileName,
                                                    INT32U_t startPostion);

/**
 * @brief mmsCLient_parseGetFileResponse 获取文件内容
 * @param message 原始消息
 * @param fileData 文件数据
 */
LIB860_INTERNAL bool mmsCLient_parseGetFileResponse(GspByteBuffer* message,
                                                    GspLinkedList* outFileDataPtr);

/**
 * @brief mmsClient_createSetFileRequest 写文件内容请求
 * @param self 链接对象
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param startPostion 开始位置
 * @param fileData 文件内容
 * @return 是否是文件结束
 */
LIB860_INTERNAL bool mmsClient_createSetFileRequest(GspMmsConnection self,
                                                    GspByteBuffer* outMessage,
                                                    uint16_t invokeId,
                                                    const char* fileName,
                                                    uint32_t startPostion,
                                                    const char* fileData,
                                                    uint32_t fileDataSize,
                                                    bool endFlag);

/********************************************* 报告相关底层接口 ***************************************************/

/**
 * @brief mmsClient_createGetBRCBValues 获取缓存报告控制块值
 * @param outMessage 封装后的协议消息
 * @param brcbReference 缓存报告控制块的refs
 */
LIB860_INTERNAL bool mmsClient_createGetBRCBValuesRequest(GspMmsConnection self,
                                                          GspByteBuffer* outMessage,
                                                          uint16_t invokeId,
                                                          const char* brcbReference);

/**
 * @brief mmsClient_parseGetBRCBValuesResponse 获取缓存报告控制块值
 * @param message 原始消息
 * @param fileData 文件数据
 */
LIB860_INTERNAL bool mmsClient_parseGetBRCBValuesResponse(GspByteBuffer* message,
                                                          GspLinkedList* outFileDataPtr);

/**
 * @brief mmsClient_createGetBRCBValues 设置缓存报告控制块值
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param brcbControlBlk 缓存报告控制块的refs
 */
LIB860_INTERNAL bool mmsClient_createSetBRCBValuesRequest(GspMmsConnection self,
                                                          GspByteBuffer* outMessage,
                                                          uint16_t invokeId,
                                                          BRCBControlBlk brcbControlBlk);

/**
 * @brief mmsClient_parseSetBRCBValues 解析缓存报告控制块值回应
 * @param message 原始消息
 * @param fileData 文件数据
 */
LIB860_INTERNAL bool mmsClient_parseSetBRCBErrorValues(GspByteBuffer* message,
                                                       GspLinkedList* outData);

/**
 * @brief mmsClient_parseReportPDU 解析缓存报告
 * @param message 原始消息
 * @param fileData 文件数据
 */
LIB860_INTERNAL bool mmsClient_parseReportPDU(GspByteBuffer* message,
                                              GspLinkedList* outData);

/**
 * @brief mmsClient_createGetBRCBValuesRequest 获取非缓存报告控制块值
 * @param outMessage 封装后的协议消息
 * @param brcbReference 缓存报告控制块的refs
 */
LIB860_INTERNAL bool mmsClient_createGetURCBValuesRequest(GspMmsConnection self,
                                                          GspByteBuffer* outMessage,
                                                          uint16_t invokeId,
                                                          const char* brcbReference);

/**
 * @brief mmsCLient_parseGetURCBValuesResponse 获取缓存报告控制块值
 * @param message 原始消息
 * @param fileData 文件数据
 */
LIB860_INTERNAL bool mmsCLient_parseGetURCBValuesResponse(GspByteBuffer* message,
                                                          GspLinkedList* outList);


/**
 * @brief mmsClient_createGetURCBValues 设置缓存报告控制块值
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param brcbControlBlk 缓存报告控制块的refs
 */
LIB860_INTERNAL bool mmsClient_createSetURCBValuesRequest(GspMmsConnection self,
                                                          GspByteBuffer* outMessage,
                                                          uint16_t invokeId,
                                                          URCBControlBlk urcbControlBlk);

/**
 * @brief mmsClient_parseSetURCBValuesResponse 解析设置缓存报告控制块值回应
 * @param message 原始消息
 * @param fileData 文件数据
 */
LIB860_INTERNAL bool mmsClient_parseSetURCBValuesResponse(GspByteBuffer* message,
                                                          GspLinkedList* outData);

/********************************************* 定值相关底层接口 ***************************************************/

/**
 * @brief mmsClient_createSelectActiveSGRequest 选择激活定值组 请求
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param sgcbReference 定值控制块refs
 * @param settingGroupNumber 定值组号
 * @return 是否创建请求信息成功
 */
LIB860_INTERNAL bool mmsClient_createSelectActiveSGRequest(GspMmsConnection self,
                                                           GspByteBuffer* outMessage,
                                                           uint16_t invokeId,
                                                           const char* sgcbReference,
                                                           uint8_t settingGroupNumber);

/**
 * @brief mmsClient_parseSelectActiveSGResponse 解析选择激活定值组回应
 * @param message 原始消息
 * @param outData 解析后的数据
 */
LIB860_INTERNAL bool mmsClient_parseSelectActiveSGResponse(GspByteBuffer* message,
                                                           GspLinkedList* outData);


/**
 * @brief mmsClient_createSelectEditSGRequest 选择编辑定值组 请求
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param sgcbReference 定值控制块refs
 * @param settingGroupNumber 定值组号
 * @return 是否创建请求信息成功
 */
LIB860_INTERNAL bool mmsClient_createSelectEditSGRequest(GspMmsConnection self,
                                                         GspByteBuffer* outMessage,
                                                         uint16_t invokeId,
                                                         const char* sgcbReference,
                                                         uint8_t settingGroupNumber);

/**
 * @brief mmsClient_parseSelectEditSGResponse 解析选择编辑定制组回应
 * @param message 原始消息
 * @param outData 解析后的数据
 */
LIB860_INTERNAL bool mmsClient_parseSelectEditSGResponse(GspByteBuffer* message,
                                                         GspLinkedList* outData);

/**
 * @brief mmsClient_createSetEditSGValueRequest 获取编辑定值组值请求帧
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param sgRefs 带有约束的定值refs串链表
 * @return 是否创建请求信息成功
 */
LIB860_INTERNAL bool mmsClient_createSetEditSGValueRequest(GspMmsConnection self,
                                                           GspByteBuffer* outMessage,
                                                           uint16_t invokeId,
                                                           GspLinkedList sgRefsData);

/**
 * @brief mmsClient_parseSetEditSGValueResponse 解析获取编辑定值组值回应
 * @param message 原始消息
 * @param outData 解析后的数据
 * @param 是否有后续数据
 */
LIB860_INTERNAL bool mmsClient_parseSetEditSGValueResponse(GspByteBuffer* message,
                                                           GspLinkedList* outData);

/**
 * @brief mmsClient_createConfirmEditSGValuesRequest 确认编辑定值组值 请求
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param sgcbReference 定值控制块refs
 * @return 是否创建请求信息成功
 */
LIB860_INTERNAL bool mmsClient_createConfirmEditSGValuesRequest(GspMmsConnection self,
                                                                GspByteBuffer* outMessage,
                                                                uint16_t invokeId,
                                                                const char* sgcbReference);

/**
 * @brief mmsClient_parseConfirmEditSGValuesResponse 解析确认编辑定值组回应
 * @param message 原始消息
 * @param outData 解析后的数据
 */
LIB860_INTERNAL bool mmsClient_parseConfirmEditSGValuesResponse(GspByteBuffer* message,
                                                                GspLinkedList* outData);


/**
 * @brief mmsClient_createGetEditSGValueRequest 获取编辑定值组值请求帧
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param sgRefs 带有约束的定值refs串链表
 * @return 是否创建请求信息成功
 */
LIB860_INTERNAL bool mmsClient_createGetEditSGValueRequest(GspMmsConnection self,
                                                           GspByteBuffer* outMessage,
                                                           uint16_t invokeId,
                                                           GspLinkedList sgRefs);

/**
 * @brief mmsClient_parseGetEditSGValueResponse 解析获取编辑定值组值回应
 * @param message 原始消息
 * @param outData 解析后的数据
 * @param 是否有后续数据
 */
LIB860_INTERNAL bool mmsClient_parseGetEditSGValueResponse(GspByteBuffer* message,
                                                           GspLinkedList* outData);

/**
 * @brief mmsClient_createGetSGCBValuesRequest 获取定值控制块请求
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param sgRefs refs 串链表
 * @return 是否创建请求信息成功
 */
LIB860_INTERNAL bool mmsClient_createGetSGCBValuesRequest(GspMmsConnection self,
                                                          GspByteBuffer* outMessage,
                                                          uint16_t invokeId,
                                                          const char* sgcbReference);

/**
 * @brief mmsClient_parseGetSGCBValuesResponse 解析获取定值控制块回应
 * @param message 原始消息
 * @param outData 解析后的数据
 * @return 是否有后续数据
 */
LIB860_INTERNAL bool mmsClient_parseGetSGCBValuesResponse(GspByteBuffer* message,
                                                          GspLinkedList* outData);

/********************************************* 数据集相关底层接口 ***************************************************/

/**
 * @brief mmsClient_createGetDataSetDirectoryRequest 创建获取数据集目录的请求
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramDataSetRefs 数据集refs
 * @return 是否创建请求信息成功
 */
LIB860_INTERNAL bool mmsClient_createGetDataSetDirectoryRequest(GspMmsConnection self,
                                                                GspByteBuffer* outMessage,
                                                                uint16_t invokeId,
                                                                const char* paramDataSetRefs);

/**
 * @brief mmsClient_parseGetDataSetDirectoryResponse 解析数据集目录回应
 * @param message 原始消息
 * @param outDataSetDirectory 解析后的数据
 * @return 是否有后续数据
 */
LIB860_INTERNAL bool mmsClient_parseGetDataSetDirectoryResponse(GspByteBuffer* message,
                                                                GspLinkedList* outDataSetDirectory);

/**
 * @brief mmsClient_createGetDataSetValuesRequest 创建获取数据集目录的请求
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramDataSetRefs 数据集refs
 * @return 是否创建请求信息成功
 */
LIB860_INTERNAL bool mmsClient_createGetDataSetValuesRequest(GspMmsConnection self,
                                                             GspByteBuffer* outMessage,
                                                             uint16_t invokeId,
                                                             const char* paramDataSetRefs);

/**
 * @brief mmsClient_parseGetDataSetValuesResponse 解析数据集值的回应
 * @param message 原始消息
 * @param outDataSetValues 解析后的消息
 * @return 是否有后续数据
 */
LIB860_INTERNAL bool mmsClient_parseGetDataSetValuesResponse(GspByteBuffer* message,
                                                             GspLinkedList* outDataSetValues);

/********************************************* 控制 相关底层接口 ***************************************************/

/**
 * @brief mmsClient_createSelectRequest 创建选择帧
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramSelectRefs select refs
 * @return 是否创建请求信息成功
 */
LIB860_INTERNAL bool mmsClient_createSelectRequest(GspMmsConnection self,
                                                   GspByteBuffer* outMessage,
                                                   uint16_t invokeId,
                                                   const char* paramSelectRefs);

/**
 * @brief mmsClient_parseSelectResponse 解析select回应
 * @param message 原始消息
 * @param outSelect 解析后的消息
 */
LIB860_INTERNAL void mmsClient_parseSelectResponse(GspByteBuffer* message, GspLinkedList* outSelect);

/**
 * @brief mmsClient_createOpRequest 创建控制操作帧
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param controlReference 控制对象refs
 * @param paramValue 控制对象值
 * @param syncCheck 同期检查
 * @param lockCheck 锁控检查
 * @return
 */
LIB860_INTERNAL bool mmsClient_createOpRequest(GspMmsConnection self,
                                               GspByteBuffer* outMessage,
                                               uint16_t invokeId,
                                               const char* controlReference,
                                               GspMmsValue* paramValue,
                                               Originator__orCat paramOrCat,
                                               const char* paramOrIdent,
                                               bool syncCheck,
                                               bool lockCheck,
                                               bool test);

/**
 * @brief mmsClient_parseOpResponse 解析select回应
 * @param message 原始消息
 * @param outSelect 解析后的消息
 */
LIB860_INTERNAL void mmsClient_parseOpResponse(GspByteBuffer* message, GspLinkedList* outSelect);


/**
 * @brief mmsClient_createSelectWithValue 创建带值选择帧
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramSelectRefs 控制对象 refs
 * @param paramValue 控制对象值
 * @param paramOrCat origin -> orcat
 * @param paramOrIdent origin -> orident
 * @return 是否创建成功
 */
LIB860_INTERNAL bool mmsClient_createSelectWithValueRequest(GspMmsConnection self,
                                                            GspByteBuffer* outMessage,
                                                            uint16_t invokeId,
                                                            const char* paramSelectRefs,
                                                            GspMmsValue* paramValue,
                                                            int paramOrCat,
                                                            const char* paramOrIdent,
                                                            bool syncCheck,
                                                            bool lockCheck,
                                                            bool test);


/**
 * @brief mmsClient_parseSelectWithValueResponse 解析select回应
 * @param message 原始消息
 * @param outSelect 解析后的消息
 */
LIB860_INTERNAL void mmsClient_parseSelectWithValueResponse(GspByteBuffer* message, GspLinkedList* outSelect);

/********************************************* test 相关底层接口 ***************************************************/

/**
 * @brief mmsClient_createTestRequest 创建 test 请求帧
 * @param self
 */
void mmsClient_createTestRequest(GspMmsConnection self);

/**
 * @brief mmsClient_createTestResponse 创建 test 应答帧
 * @param self
 */
void mmsClient_createTestResponse(GspMmsConnection self);

/********************************************* rpc  相关底层接口 ***************************************************/

/**
 * @brief mmsClient_createGetRpcInterfaceDirectoryRequest 创建获取RPC接口目录
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramReferenceAfter reference串
 * @return 是否创建成功
 */
LIB860_INTERNAL bool mmsClient_createGetRpcInterfaceDirectoryRequest(GspMmsConnection self,
                                                                     GspByteBuffer* outMessage,
                                                                     uint16_t invokeId,
                                                                     const char* paramReferenceAfter);


/**
 * @brief mmsClient_parseGetRpcInterfaceDirectoryResponse 解析获取RPC接口目录
 * @param message 原始消息
 * @param outDataList 解析后的消息
 */
LIB860_INTERNAL bool mmsClient_parseGetRpcInterfaceDirectoryResponse(GspByteBuffer* message, GspLinkedList* outDataList);


/**
 * @brief mmsClient_createGetRpcMethodDirectoryRequest 创建获取RPC方法目录
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramInterface 接口refs
 * @param paramReferenceAfter reference串
 * @return 是否创建成功
 */
LIB860_INTERNAL bool mmsClient_createGetRpcMethodDirectoryRequest(GspMmsConnection self,
                                                                  GspByteBuffer* outMessage,
                                                                  uint16_t invokeId,
                                                                  const char* paramInterface,
                                                                  const char* paramReferenceAfter);


/**
 * @brief mmsClient_parseGetRpcMethodDirectoryResponse 解析获取RPC接口目录
 * @param message 原始消息
 * @param outDataList 解析后的消息
 */
LIB860_INTERNAL bool mmsClient_parseGetRpcMethodDirectoryResponse(GspByteBuffer* message, GspLinkedList* outDataList);


/**
 * @brief mmsClient_createGetRpcInterfaceDefinitionRequest 创建获取RPC接口定义
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramInterface 接口串
 * @return 是否创建成功
 */
LIB860_INTERNAL bool mmsClient_createGetRpcInterfaceDefinitionRequest(GspMmsConnection self,
                                                                      GspByteBuffer* outMessage,
                                                                      uint16_t invokeId,
                                                                      const char* paramInterface,
                                                                      const char* paramRefsAfter = nullptr);

/**
 * @brief mmsClient_parseGetRpcInterfaceDefinitionResponse 解析获取RPC接口定义
 * @param message 原始消息
 * @param outDataList 解析后的消息
 */
LIB860_INTERNAL bool mmsClient_parseGetRpcInterfaceDefinitionResponse(GspByteBuffer* message, GspLinkedList* outDataList);


/**
 * @brief mmsClient_createGetRpcMethodDefinitionRequest 创建获取RPC方法定义
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramRefList 接口串
 * @return 是否创建成功
 */
LIB860_INTERNAL bool mmsClient_createGetRpcMethodDefinitionRequest(GspMmsConnection self,
                                                                   GspByteBuffer* outMessage,
                                                                   uint16_t invokeId,
                                                                   GspLinkedList paramRefList);


/**
 * @brief mmsClient_parseGetRpcMethodDefinitionResponse 解析获取RPC方法定义
 * @param message 原始消息
 * @param outDataList 解析后的消息
 */
LIB860_INTERNAL bool mmsClient_parseGetRpcMethodDefinitionResponse(GspByteBuffer* message, GspLinkedList* outDataList);


/**
 * @brief mmsClient_createRpcCallRequest 创建 RPC 调用请求
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramFuncation 方法名字
 * @param paramData 调用数据
 * @param paramCallID 调用ID
 * @return 是否创建成功
 */
LIB860_INTERNAL bool mmsClient_createRpcCallRequest(GspMmsConnection self,
                                                    GspByteBuffer* outMessage,
                                                    uint16_t invokeId,
                                                    const char * paramFuncation,
                                                    GspMmsValue* paramData,
                                                    const char* paramCallID);

/**
 * @brief mmsClient_parseRpcCallResponse 解析RPCCall应答
 * @param message 原始消息
 * @param outDataList 解析后的消息
 */
LIB860_INTERNAL bool mmsClient_parseRpcCallResponse(GspByteBuffer* message, GspLinkedList* outDataList);

/********************************************* log  相关底层接口 ***************************************************/

/**
 * @brief mmsClient_createGetLCBValuesRequest 创建获取日志控制块的请求
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramRefsList 参数列表
 * @return 是否获取日志控制块成功
 */
LIB860_INTERNAL bool mmsClient_createGetLCBValuesRequest(GspMmsConnection self,
                                                         GspByteBuffer* outMessage,
                                                         uint16_t invokeId,
                                                         GspLinkedList paramRefsList);

/**
 * @brief mmsClient_parseGetLCBValuesResponse 解析日志控制块的应答
 * @param message 原始消息
 * @param outDataList 解析后的消息
 */
LIB860_INTERNAL bool mmsClient_parseGetLCBValuesResponse(GspByteBuffer* message, GspLinkedList* outDataList);


/**
 * @brief mmsClient_createSetLCBValuesRequest 创建设置日志控制块的请求
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param paramLCBList 日志控制块列表
 * @return 是否设置日志控制块成功
 */
LIB860_INTERNAL bool mmsClient_createSetLCBValuesRequest(GspMmsConnection self,
                                                         GspByteBuffer* outMessage,
                                                         uint16_t invokeId,
                                                         GspLinkedList paramLCBList);
/**
 * @brief mmsClient_parseSetLCBErrorValues 解析设置日志控制块的应答
 * @param message 原始消息
 * @param outDataList 解析后的消息
 */
LIB860_INTERNAL bool mmsClient_parseSetLCBErrorValues(GspByteBuffer* message,
                                                      GspLinkedList* outData);

/**
 * @brief mmsClient_createQueryLogByTimeRequest 创建查询日志的请求
 * @param self 链接信息
 * @param outMessage 封装后的协议消息
 * @param invokeId 消息ID
 * @param startTime 查询开始时间
 * @param endTime 查询结束时间
 * @param entryAfter 从该条目开始查询
 * @return
 */
LIB860_INTERNAL bool mmsClient_createQueryLogByTimeRequest(GspMmsConnection self,
                                                           GspByteBuffer* outMessage,
                                                           uint16_t invokeId,
                                                           const char* logRefs,
                                                           const char* startTime,
                                                           const char* endTime,
                                                           const char* entryAfter);

/**
 * @brief mmsClient_parseSetLCBErrorValues 解析设置日志控制块的应答
 * @param message 原始消息
 * @param outDataList 解析后的消息
 */
LIB860_INTERNAL bool mmsClient_parseQueryLogByTimeValues(GspByteBuffer* message,
                                                         GspLinkedList* outDataList);


extern void Global_LogString( const char *strFormat, ...);//zhouhj 20220107 增加用于打印日志信息
extern int  g_nLogGspDebugString;
