/*
 *  gsp_mms_types.h
 */

#ifndef GSP_MMS_TYPES_H_
#define GSP_MMS_TYPES_H_

#include "libdlt860_common_api.h"
#include "gsp_mms_common.h"

// 值标识
typedef enum  {
    // 无回应
    GSP_MMS_VALUE_NO_RESPONSE,
    // 正常
    GSP_MMS_VALUE_OK,
    // 操作拒绝
    GSP_MMS_VALUE_ACCESS_DENIED,
    // 值无效
    GSP_MMS_VALUE_VALUE_INVALID,
    // 值临时不可用
    GSP_MMS_VALUE_TEMPORARILY_UNAVAILABLE,
    // 值操作不支持
    GSP_MMS_VALUE_OBJECT_ACCESS_UNSUPPORTED
} GspMmsValueIndication;

/**
 * 命名变量的类型定义
 */
typedef struct sGspMmsVariableSpecification GspMmsVariableSpecification;

/**
 * @brief The sGspMmsVariableSpecification struct 类型定义结构
 */
struct ATTRIBUTE_PACKED sGspMmsVariableSpecification {
    // 数据类型
    GspMmsType type;
    // 数据类型名字
    char* name;
    // 具体的数据类型的参数值
    union uMmsTypeSpecification
    {
        // 数组类型参数值
        struct sMmsArray {
            int elementCount; /* number of array elements */
            GspMmsVariableSpecification* elementTypeSpec;
        } array;

        // 结构体类型相关参数值
        struct sMmsStructure {
            int elementCount;
            GspMmsVariableSpecification** elements;
        } structure;
        // dummy - not required
        int boolean;

        // dummy - not required
        int int8;

        // dummy - not required
        int int16;

        // dummy - not required
        int int32;

        // dummy - not required
        int int64;

        // dummy - not required
        int uint8;

        // dummy - not required
        int uint16;

        // dummy - not required
        int uint32;

        // dummy - not required
        int uint64;

        // 浮点类型参数
        struct sMmsFloat
        {
            uint8_t exponentWidth;
            uint8_t formatWidth;
        } floatingpoint;

        // Number of bits in bitstring
        int bitString;

        // Number of octets in octet string
        int octetString;

        // Maximum size of string
        int visibleString;

        //  Number of unicode in octet string
        int unicodeString;

        // Number of bits in dbpos
        int dbpos;

        // Number of bits in tcmd
        int tcmd;

        // Number of bits in check
        int check;

        // dummy - not required
        int utctime;

        // size: either 4 or 6
        int binaryTime;
    } typeSpec;
};


#endif /* GSP_MMS_TYPES_H_ */
