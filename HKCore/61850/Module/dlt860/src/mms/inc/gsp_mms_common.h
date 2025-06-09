/*
 *  gsp_mms_common.h
 *  mms 公用数据类型
 */
#ifndef GSP_MMS_COMMON_H_
#define GSP_MMS_COMMON_H_

#include "libdlt860_define.h"


// mms 链接相关的错误代码
typedef enum
{
    // *********************************************** 通用错误代码 *******************************************************
    // 没有错误
    GSP_MMS_ERROR_NONE = 0,
    // 实例不可用
    GSP_MMS_ERROR_INSTANCE_NOT_AVAILABLE = 1,
    // 实例在使用
    GSP_MMS_ERROR_INSTANCE_IN_USE = 2,
    // 访问违例
    GSP_MMS_ERROR_ACCESS_VIOLATION = 3,
    // 当前状态不允许访问
    GSP_MMS_ERROR_ACCESS_NOT_ALLOWED_IN_CURRENT_STATE = 4,
    // 参数值不合适
    GSP_MMS_PARAMETER_VALUE_INAPPROPRIATE = 5,
    // 参数值不一致
    GSP_MMS_PARAMETER_VALUE_INCONSISTENT = 6,
    // 类不被支持
    GSP_MMS_CLASS_NOT_SUPPORTED = 7,
    // 实例被其它客户锁定
    GSP_MMS_INSTANCE_LOCKED_BY_OTHER_CLIENT = 8,
    // 控制必须被选择
    GSP_MMS_CONTROL_MUST_BE_SELECTED = 9,
    // 类型冲突
    GSP_MMS_TYPE_CONFLICT = 10,
    // 由于通信约束失败
    GSP_MMS_FAILED_DUE_TO_COMM_CONSTRAINT = 11,
    // 由于服务器约束失败
    GSP_MMS_FAILED_DUE_TO_SERVER_CONSTRAINT = 12,
    // 链接拒绝
    GSP_MMS_ERROR_CONNECTION_REJECTED = 13,
    // 链接丢失
    GSP_MMS_ERROR_CONNECTION_LOST = 14,
    // 服务超时
    GSP_MMS_ERROR_SERVICE_TIMEOUT = 15,
    // 应答解析错误
    GSP_MMS_ERROR_PARSING_RESPONSE = 16,
    // 硬件错误
    GSP_MMS_ERROR_HARDWARE_FAULT = 17,
    // 终止拒绝
    GSP_MMS_ERROR_CONCLUDE_REJECTED = 18,
    // 参数无效
    GSP_MMS_ERROR_INVALID_ARGUMENTS = 19,
    // 超出调用限制
    GSP_MMS_ERROR_OUTSTANDING_CALL_LIMIT = 20,
    // 其他错误
    GSP_MMS_ERROR_OTHER = 21,
} GspMmsError;


// mmsvalue 数据类型
typedef enum
{
    // 服务错误代码
    GSP_MMS_SERVER_ERROR = 0,
    // 数组类型
    GSP_MMS_ARRAY = 1,
    // 结构体类型
    GSP_MMS_STRUCTURE = 2,
    // bool 类型
    GSP_MMS_BOOLEAN = 3,
    // int8 类型
    GSP_MMS_INT8 = 4,
    // int16 类型
    GSP_MMS_INT16 = 5,
    // int32 类型
    GSP_MMS_INT32 = 6,
    // int64 类型
    GSP_MMS_INT64 = 7,
    // 无符号 int8 类型
    GSP_MMS_UINT8 = 8,
    // 无符号 int16 类型
    GSP_MMS_UINT16 = 9,
    // 无符号 int32 类型
    GSP_MMS_UINT32 = 10,
    // 无符号 int64 类型
    GSP_MMS_UINT64 = 11,
    // 浮点 32 类型
    GSP_MMS_FLOAT32 = 12,
    // 浮点 64 类型
    GSP_MMS_FLOAT64 = 13,
    // bitstring 类型
    GSP_MMS_BIT_STRING = 14,
    // 8位元字符串(原始不可打印的)
    GSP_MMS_OCTET_STRING = 15,
    // 可打印的字符串
    GSP_MMS_VISIBLE_STRING = 16,
    // unicode 字符串
    GSP_MMS_UNICODE_STRING = 17,
    // UTC 时间串
    GSP_MMS_UTC_TIME = 18,
    // 二进制时间
    GSP_MMS_BINARY_TIME = 19,
    // 品质位
    GSP_MMS_QUALITY = 20,
    // 双点位置
    GSP_MMS_DBPOS = 21,
    // 档位
    GSP_MMS_TCMD = 22,
    // 心跳
    GSP_MMS_CHECK = 23,
    // enum
    GSP_MMS_ENUM = 24,
} GspMmsType;

// mms 域名
typedef struct sGspMmsDomain GspMmsDomain;

// mms 接入指定
typedef struct sGspMmsAccessSpecifier
{
    GspMmsDomain* domain;
    char* variableName;
    int arrayIndex; /* -1 --> no index present / ignore index */
    char* componentName;
} GspMmsAccessSpecifier;

typedef struct
{
    char* domainId;
    char* itemId;
    int32_t arrayIndex; /* -1 --> no index present / ignore index */
    char* componentName;
} GspMmsVariableAccessSpecification;

typedef struct sGspMmsNamedVariableList* GspMmsNamedVariableList;
typedef struct sGspMmsAccessSpecifier* GspMmsNamedVariableListEntry;

/**
 * \brief ITU (International Telecommunication Union) object identifier (OID)
 */
typedef struct {
    uint16_t arc[10];
    int arcCount;
} GspItuObjectIdentifier;

/**
 * \brief ISO application reference (specifies an ISO application endpoint)
 */
typedef struct {
    GspItuObjectIdentifier apTitle;
    int aeQualifier;
} GspIsoApplicationReference;

#endif /* GSP_MMS_COMMON_H_ */
