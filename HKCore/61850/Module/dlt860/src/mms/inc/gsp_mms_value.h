/*
 *  gsp_mms_value.h
 *  mmsvalue 定义
 */

#ifndef GSP_MMS_VALUE_H_
#define GSP_MMS_VALUE_H_

#include "libdlt860_define.h"
#include "gsp_mms_common.h"
#include "gsp_mms_types.h"
#include "asn_inc.h"
#include <string>

using std::string;

// mmsvalue 操作错误代码表
typedef enum {
    // 没有回应(/* for server internal purposes only! */)
    GSP_DATA_ACCESS_ERROR_NO_RESPONSE = -2,
    // 正常
    GSP_DATA_ACCESS_ERROR_SUCCESS = -1,
    // 对象无效
    GSP_DATA_ACCESS_ERROR_OBJECT_INVALIDATED = 0,
    // 硬件错误
    GSP_DATA_ACCESS_ERROR_HARDWARE_FAULT = 1,
    // 数据临时不可用
    GSP_DATA_ACCESS_ERROR_TEMPORARILY_UNAVAILABLE = 2,
    // 对象操作拒绝
    GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_DENIED = 3,
    // 对象未定义
    GSP_DATA_ACCESS_ERROR_OBJECT_UNDEFINED = 4,
    // 地址无效
    GSP_DATA_ACCESS_ERROR_INVALID_ADDRESS = 5,
    // 数据类型不支持
    GSP_DATA_ACCESS_ERROR_TYPE_UNSUPPORTED = 6,
    // 数据类型不满足
    GSP_DATA_ACCESS_ERROR_TYPE_INCONSISTENT = 7,
    // 对象属性不满足
    GSP_DATA_ACCESS_ERROR_OBJECT_ATTRIBUTE_INCONSISTENT = 8,
    // 数据操作不支持
    GSP_DATA_ACCESS_ERROR_OBJECT_ACCESS_UNSUPPORTED = 9,
    // 数据对象不存在
    GSP_DATA_ACCESS_ERROR_OBJECT_NONE_EXISTENT = 10,
    // 对象值无效
    GSP_DATA_ACCESS_ERROR_OBJECT_VALUE_INVALID = 11,
    // 未知错误
    GSP_DATA_ACCESS_ERROR_UNKNOWN = 12
} GspMmsDataAccessError;

ServiceError_t GspMmsDataAccessErrorToServiceError(GspMmsDataAccessError dataError);

/**
 * MmsValue 结构
 */
typedef struct Data GspMmsValue;

/*************************************************************************************
 *  数据类的函数
 *************************************************************************************/

/**
 * \brief 创建一个数组类型，并设置默认值
 * \return 数组实例
 */
LIB860_API GspMmsValue* GspMmsValue_createArray(GspMmsVariableSpecification* elementType, int size);

/**
 * @brief GspMmsValue_getArraySize 获取数组尺寸
 * @param self 数据实例
 * @return 尺寸
 */
LIB860_API uint32_t GspMmsValue_getArraySize(const GspMmsValue* self);

/**
 * @brief GspMmsValue_getStructSize 获取结构体尺寸
 * @param self 数据实例
 * @return 尺寸
 */
LIB860_API uint32_t GspMmsValue_getStructSize(const GspMmsValue* self);

/**
 * @brief MmsValue_getElement 在数组或者对象类型中获取元素数据
 * @param array 数据实例
 * @param index 数据索引
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_getElement(const GspMmsValue* array, int index);

/**
 * @brief MmsValue_createEmptyArray 创建空的数组
 * @param size 尺寸
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_createEmptyArray(int size);

/**
 * @brief MmsValue_setElement 给对象数据或者数组设置指定索引的值
 * @param complexValue 数据对象
 * @param index 索引
 * @param elementValue 数据值
 */
LIB860_API void GspMmsValue_setElement(GspMmsValue* complexValue, int index, GspMmsValue* elementValue);


/*************************************************************************************
 * 基础数据类型
 *************************************************************************************/

/**
 * @brief MmsValue_getDataAccessError 获取数据操作错误代码
 * @param self 数据对象
 * @return 错误代码
 */
LIB860_API ServiceError_t GspMmsValue_getDataAccessError(const GspMmsValue* self);

/**
 * @brief MmsValue_toInt64 转换对象值为 int64 类型
 * @param self 数据对象
 * @return 转换后的值
 */
LIB860_API int64_t GspMmsValue_toInt64(const GspMmsValue* self);

/**
 * @brief MmsValue_toInt32 转换对象值为 int32 类型
 * @param self 数据对象
 * @return 转换后的值
 */
LIB860_API int32_t GspMmsValue_toInt32(const GspMmsValue* value);

/**
 * @brief MmsValue_toUInt64 转换对象值为 uint64 类型
 * @param self 数据对象
 * @return 转换后的值
 */
LIB860_API uint64_t GspMmsValue_toUInt64(const GspMmsValue* self);

/**
 * @brief MmsValue_toUint32 转换对象值为 uint32 类型
 * @param self 数据对象
 * @return 转换后的值
 */
LIB860_API uint32_t GspMmsValue_toUint32(const GspMmsValue* value);

/**
 * @brief MmsValue_toDouble 转换对象值为 double 类型
 * @param self 数据对象
 * @return 转换后的值
 */
LIB860_API double GspMmsValue_toDouble(const GspMmsValue* self);

/**
 * @brief MmsValue_toFloat 转换对象值为 float 类型
 * @param self 数据对象
 * @return 转换后的值
 */
LIB860_API float GspMmsValue_toFloat(const GspMmsValue* self);

/**
 * @brief MmsValue_toUnixTimestamp 转换对象值为 unix 时间戳
 * @param self 数据对象
 * @return 转换后的值
 */
LIB860_API uint32_t GspMmsValue_toUnixTimestamp(const GspMmsValue* self);

/**
 * @brief MmsValue_setFloat 设置对象的 float 值
 * @param self 数据对象
 * @param newFloatValue 需要设置的值
 */
LIB860_API void GspMmsValue_setFloat(GspMmsValue* self, float newFloatValue);

/**
 * @brief MmsValue_setDouble 设置对象的 double 值
 * @param self 数据对象
 * @param newFloatValue 需要设置的值
 */
LIB860_API void GspMmsValue_setDouble(GspMmsValue* self, double newFloatValue);

/**
 * @brief MmsValue_setInt8 设置对象的 int8 值
 * @param value 数据对象
 * @param integer 需要设置的值
 */
LIB860_API void GspMmsValue_setInt8(GspMmsValue* value, int8_t integer);

/**
 * @brief MmsValue_setInt16 设置对象的 int16 值
 * @param value 数据对象
 * @param integer 需要设置的值
 */
LIB860_API void GspMmsValue_setInt16(GspMmsValue* value, int16_t integer);

/**
 * @brief MmsValue_setInt32 设置对象的 int32 值
 * @param value 数据对象
 * @param integer 需要设置的值
 */
LIB860_API void GspMmsValue_setInt32(GspMmsValue* self, int32_t integer);

/**
 * @brief MmsValue_setInt64 设置对象的 int64 值
 * @param value 数据对象
 * @param integer 需要设置的值
 */
LIB860_API void GspMmsValue_setInt64(GspMmsValue* value, int64_t integer);

/**
 * @brief MmsValue_setUint8 设置对象的 int8 值
 * @param value 数据对象
 * @param integer 需要设置的值
 */
LIB860_API void GspMmsValue_setUint8(GspMmsValue* value, uint8_t integer);

/**
 * @brief MmsValue_setUint16 设置对象的 int16 值
 * @param value 数据对象
 * @param integer 需要设置的值
 */
LIB860_API void GspMmsValue_setUint16(GspMmsValue* value, uint16_t integer);

/**
 * @brief MmsValue_setUint32 设置对象的 int32 值
 * @param value 数据对象
 * @param integer 需要设置的值
 */
LIB860_API void GspMmsValue_setUint32(GspMmsValue* value, uint32_t integer);


/**
 * @brief MmsValue_setBoolean 设置对象的 bool 值
 * @param value 数据对象
 * @param integer 需要设置的值
 */
LIB860_API void GspMmsValue_setBoolean(GspMmsValue* value, bool boolValue);

/**
 * @brief MmsValue_getBoolean 获取对象的 bool 值
 * @param value 数据对象
 * @param integer 需要设置的值
 */
LIB860_API bool GspMmsValue_getBoolean(const GspMmsValue* value);

/**
 * @brief GspMmsValue_toBoolean 转换成Boolean类型
 * @param value 数据对象
 * @return 转换后的数值
 */
LIB860_API bool GspMmsValue_toBoolean(const GspMmsValue* value);

/**
 * @brief MmsValue_toString 转换成字符串类型 (MMS_UNICODE_STRING 或者 MMS_VISIBLE_STRING 类型)
 * @param self 数据对象
 * @return 转换后的字符串
 */
LIB860_API const char* GspMmsValue_toString(GspMmsValue* self);

/**
 * @brief MmsValue_getStringSize 获取字符串的尺寸(MMS_UNICODE_STRING 或者 MMS_VISIBLE_STRING 类型)
 * @param self 数据对象
 * @return 数据尺寸
 */
LIB860_API int GspMmsValue_getStringSize(GspMmsValue* self);

/**
 * @brief MmsValue_setVisibleString 设置可视化字符串
 * @param self 数据对象字符串信息
 * @param string
 */
LIB860_API void GspMmsValue_setVisibleString(GspMmsValue* self, const char* string);


/**
 * @brief MmsValue_setBitStringBit 设置 bitstring 的指定位置的值
 * @param self 数据对象
 * @param bitPos 指定位置
 * @param value 数据值 (true/false)
 */
LIB860_API void GspMmsValue_setBitStringBit(GspMmsValue* self, int bitPos, bool value);
LIB860_API uint8_t *GspMmsValue_getBitStringBuf(const GspMmsValue* self);

/**
 * @brief MmsValue_getBitStringBit 获取 bitstring 的指定位置的值
 * @param self 数据对象
 * @param bitPos 指定位置
 * @return 数据值 (true/false)
 */
LIB860_API bool GspMmsValue_getBitStringBit(const GspMmsValue* self, int bitPos);

/**
 * @brief MmsValue_deleteAllBitStringBits 重置 bitstring，使其所有位都是 0
 * @param self 数据对象
 */
LIB860_API void GspMmsValue_deleteAllBitStringBits(GspMmsValue* self);


/**
 * @brief MmsValue_getBitStringSize 获取 bitstring 大小
 * @param self 数据对象
 * @return 大小
 */
LIB860_API int GspMmsValue_getBitStringSize(const GspMmsValue* self);

/**
 * @brief MmsValue_getBitStringByteSize 获取bitstring的字节数
 * @param self 数据对象
 * @return 字节数
 */
LIB860_API int GspMmsValue_getBitStringByteSize(const GspMmsValue* self);

/**
 * @brief MmsValue_getNumberOfSetBits 获取有效的bit位数
 * @param self 数据对象
 * @return bit位数
 */
LIB860_API int GspMmsValue_getNumberOfSetBits(const GspMmsValue* self);

/**
 * @brief MmsValue_setAllBitStringBits 设置bitstring所有值为1
 * @param self
 */
LIB860_API void GspMmsValue_setAllBitStringBits(GspMmsValue* self);

/**
 * @brief MmsValue_getBitStringAsInteger 转换数据对象为无符号整数(小端序列)
 * @param self 数据对象
 * @return 整数值
 */
LIB860_API uint32_t GspMmsValue_getBitStringAsInteger(const GspMmsValue* self);

/**
 * @brief MmsValue_setBitStringFromInteger 从一个整型数据设置bit位串(小端序列)
 * @param self 数据对象
 * @param intValue 数据值
 */
LIB860_API void GspMmsValue_setBitStringFromInteger(GspMmsValue* self, uint32_t intValue);

/**
 * @brief MmsValue_getBitStringAsIntegerBigEndian 转换数据对象为无符号整数(大端序列)
 * @param self 数据对象
 * @return 整数值
 */
LIB860_API uint32_t GspMmsValue_getBitStringAsIntegerBigEndian(const GspMmsValue* self);

/**
 * @brief MmsValue_setBitStringFromIntegerBigEndian 从一个整型数据设置bit位串(大端序列)
 * @param self 数据对象
 * @return 整数值
 */
LIB860_API void GspMmsValue_setBitStringFromIntegerBigEndian(GspMmsValue* self, uint32_t intValue);

/**
 * @brief GspMmsValue_getBitStringStr 获取位串的可打印字符串(使用完后这里需要自己释放内存)
 * @param self 数据对象
 * @return 可打印串(需要使用 gspmem_free 释放内存)
 */
LIB860_API const char* GspMmsValue_getBitStringStr(const GspMmsValue* self);

/**
 * @brief MmsValue_setUtcTime 设置utc时间
 * @param self 数据对象
 * @param timeval utc时间戳 (1970/01/01 00:00 UTC)
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_setUtcTime(GspMmsValue* self, uint32_t timeval);

/**
 * @brief 新建一个 mmsvalue
 * @return 创建的数据对象
 */ 
LIB860_API GspMmsValue *GspMmsValue_new();

/**
 * @brief MmsValue_setUtcTimeMs 设置utc时间戳(毫秒)
 * @param self 数据对象
 * @param timeval utc时间戳 (1970/01/01 00:00 UTC)
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_setUtcTimeMs(GspMmsValue* self, uint64_t timeval);

/**
 * @brief MmsValue_setUtcTimeByBuffer 更新时间戳
 * @param self 数据对象
 * @param buffer The buffer must have a size of 8 bytes!(PER编码)
 */
LIB860_API void GspMmsValue_setUtcTimeByBuffer(GspMmsValue* self, const uint8_t* buffer);

/**
 * @brief MmsValue_getUtcTimeBuffer 获取UTC 时间的内存指针(array length is 8 byte.)
 * @param self 数据对象
 * @return 数据对象指针
 */
LIB860_API uint8_t* GspMmsValue_getUtcTimeBuffer(GspMmsValue* self);

/**
 * @brief MmsValue_getUtcTimeInMs 获取UTC时间戳(毫秒)
 * @param value 数据对象
 * @return 毫秒时间戳(1970/01/01 00:00 UTC)
 */
LIB860_API uint64_t GspMmsValue_getUtcTimeInMs(const GspMmsValue* value);

/**
 * @brief MmsValue_getUtcTimeInMsWithUs 获取 UTC 时间戳含有微妙的部分
 * @param self 数据对象
 * @param usec 传出参数(毫秒部分)
 * @return
 */
LIB860_API uint64_t GspMmsValue_getUtcTimeInMsWithUs(const GspMmsValue* self, uint32_t* usec);

/**
 * @brief MmsValue_setUtcTimeQuality 设置时间品质位
 * Meaning of the bits in the timeQuality byte:
 * bit 7 = leapSecondsKnown
 * bit 6 = clockFailure
 * bit 5 = clockNotSynchronized
 * bit 0-4 = subsecond time accuracy (number of significant bits of subsecond time)
 * @param self 时间对象
 * @param timeQuality 时间品质位
 */
LIB860_API void GspMmsValue_setUtcTimeQuality(GspMmsValue* self, uint8_t timeQuality);

/**
 * @brief MmsValue_getUtcTimeQuality 获取时间品质位
 * Meaning of the bits in the timeQuality byte:
 * bit 7 = leapSecondsKnown
 * bit 6 = clockFailure
 * bit 5 = clockNotSynchronized
 * bit 0-4 = subsecond time accuracy (number of significant bits of subsecond time)
 * @param self 时间对象
 * @return
 */
LIB860_API uint8_t GspMmsValue_getUtcTimeQuality(const GspMmsValue* self);

/**
 * @brief MmsValue_setBinaryTime 设置时间
 * @param self 时间对象
 * @param timestamp 毫秒时间戳(1970/01/01 00:00 UTC)
 */
LIB860_API void GspMmsValue_setBinaryTime(GspMmsValue* self, uint64_t timestamp);
LIB860_API void BinaryTime_newTimeFromTimeStamp(BinaryTime_t *time, uint64_t timestamp);
/**
 * @brief MmsValue_getBinaryTimeAsUtcMs 获取 UTC 时间戳
 * @param self 时间对象
 * @return 毫秒时间戳
 */
LIB860_API uint64_t GspMmsValue_getBinaryTimeAsUtcMs(const GspMmsValue* self);
LIB860_API uint64_t BinaryTime_getAsUtcMs(BinaryTime_t *time);
LIB860_API uint8_t *GspMmsValue_getBinaryTimeBuffer(GspMmsValue *self);
LIB860_API int GspMmsValue_getBinaryTimeSize(const GspMmsValue *self);

/**
 * @brief MmsValue_setOctetString 设置二进制流串
 * @param self 数据对象
 * @param buf 待拷贝的数据
 * @param size 待拷贝的数据尺寸
 */
LIB860_API void GspMmsValue_setOctetString(GspMmsValue* self, uint8_t* buf, int size);

/**
 * @brief MmsValue_getOctetStringSize 获取二进制流串的大小
 * @param self 数据对象
 * @return 流串大小
 */
LIB860_API uint16_t GspMmsValue_getOctetStringSize(const GspMmsValue* self);

/**
 * @brief MmsValue_getOctetStringMaxSize 获取二进制流串所在内存的大小
 * @param self 数据对象
 * @return 流串所在内存大小
 */
LIB860_API uint16_t GspMmsValue_getOctetStringMaxSize(GspMmsValue* self);

/**
 * @brief MmsValue_getOctetStringBuffer 获取二进制流串的内存
 * @param self 数据对象
 * @return 流传内存指针
 */
LIB860_API uint8_t* GspMmsValue_getOctetStringBuffer(GspMmsValue* self);

/**
 * @brief MmsValue_update mmsvalue 更新赋值(两个都具备内存)
 * @param self 数据对象
 * @param source 源对象
 * @return 是否更新成功
 */
LIB860_API bool GspMmsValue_update(GspMmsValue* self, const GspMmsValue* source);

/**
 * @brief MmsValue_equals 数据值和类型是否相等判断逻辑 (TODO 数据类型不全)
 * @param self 数据对象
 * @param otherValue 另一个数据对象
 * @return 是否相等
 */
LIB860_API bool GspMmsValue_equals(const GspMmsValue* self, const GspMmsValue* otherValue);

/**
 * @brief MmsValue_equalTypes 数据类型是否相等判断逻辑
 * @param self 数据对象
 * @param otherValue 另一个数据对象
 * @return 是否相等
 */
LIB860_API bool GspMmsValue_equalTypes(const GspMmsValue* self, const GspMmsValue* otherValue);


/*************************************************************************************
 * 构造和析构
 *************************************************************************************/

/**
 * @brief MmsValue_newDataAccessError 构造一个错误代码
 * @param accessError 错误代码
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_newDataAccessError(GspMmsDataAccessError accessError);

/**
 * @brief MmsValue_newInteger 构造一个整数类型
 * @param size 整数需要占用的 bit 位数
 * @return
 */
LIB860_API GspMmsValue* GspMmsValue_newInteger(int size);

/**
 * @brief MmsValue_newUnsigned 构造一个无符号整数类型
 * @param size 整数需要占用的 bit 位数
 * @return
 */
LIB860_API GspMmsValue* GspMmsValue_newUnsigned(int size);

/**
 * @brief MmsValue_newBoolean 构造一个bool类型
 * @param boolean 数据值
 * @return
 */
LIB860_API GspMmsValue* GspMmsValue_newBoolean(bool boolean);

/**
 * @brief MmsValue_newBitString 构造一个指定长度的 bitstring
 * @param bitSize bitstring 的数据长度
 * @return
 */
LIB860_API GspMmsValue* GspMmsValue_newBitString(int bitSize);

/**
 * 新建一个 品质串
 */ 
LIB860_API GspMmsValue* GspMmsValue_newQuality();

/**
 * @brief MmsValue_newOctetString 构造一个八进制数据流
 * @param size 数据大小
 * @param maxSize 内存大小
 * @return
 */
LIB860_API GspMmsValue* GspMmsValue_newOctetString(int size, int maxSize);

/**
 * @brief MmsValue_newStructure 构造一个数据结构对象
 * @param typeSpec 数据参数
 * @return
 */
LIB860_API GspMmsValue* GspMmsValue_newStructure(const GspMmsVariableSpecification* typeSpec);

/**
 * @brief MmsValue_createEmptyStructure 构造一个空的数据结构对象
 * @param size
 * @return
 */
LIB860_API GspMmsValue* GspMmsValue_createEmptyStructure(int size);

/**
 * @brief MmsValue_newDefaultValue 创建一个默认 mmsvalue 数据并给予默认值(TODO 数据类型可能不全)
 * @param typeSpec 数据参数
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_newDefaultValue(const GspMmsVariableSpecification* typeSpec);

/**
 * @brief MmsValue_newIntegerFromInt8 创建一个 int8 的 mmsvalue
 * @param integer 数值
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_newIntegerFromInt8(int8_t integer);

/**
 * @brief MmsValue_newIntegerFromInt16 创建一个 int16 的 mmsvalue
 * @param integer 数值
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_newIntegerFromInt16(int16_t integer);

/**
 * @brief MmsValue_newIntegerFromInt32 创建一个 int32 的 mmsvalue
 * @param integer 数值
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_newIntegerFromInt32(int32_t integer);

/**
 * @brief MmsValue_newIntegerFromInt64 创建一个 int64 的 mmsvalue
 * @param integer 数值
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_newIntegerFromInt64(int64_t integer);


/**
 * @brief MmsValue_newIntegerFromUint8 创建一个 uint8 的 mmsvalue
 * @param integer
 * @return
 */
LIB860_API GspMmsValue* GspMmsValue_newIntegerFromUint8(uint8_t integer);

/**
 * @brief MmsValue_newIntegerFromUint16 创建一个 uint16 的 mmsvalue
 * @param integer 数值
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_newIntegerFromUint16(uint16_t integer);

/**
 * @brief MmsValue_newUnsignedFromUint32 创建一个 uint32 的 mmsvalue
 * @param integer 数值
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_newUnsignedFromUint32(uint32_t integer);

/**
 * @brief MmsValue_newUnsignedFromUint64 创建一个 uint64 的 mmsvalue
 * @param integer 数值
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_newUnsignedFromUint64(uint64_t integer);

/**
 * @brief MmsValue_newFloat 创建一个32位 float 的 mmsvalue
 * @param value 数值
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_newFloat(float value);

/**
 * @brief MmsValue_newDouble 创建一个64位 double 的 mmsvalue
 * @param value 数值
 * @return 数据对象
 */
LIB860_API GspMmsValue* GspMmsValue_newDouble(double value);

/**
 * @brief fillMmsValueToBitString 转换 mmsvalue 成 bitstrng
 * @param bitString 需要接受转换后数据的 bitstring
 * @param value 待转换的 mmsvalue 数据
 */
LIB860_API void GspFillMmsValueToBitString(BIT_STRING_t &bitString, GspMmsValue *value);

/**
 * @brief fillMmsValueToBinaryTime 转换 mmsvalue 成 二进制时间
 * @param binaryTime 需要接受转换后数据的 binaryTime
 * @param value 待转换的 mmsvalue
 */
LIB860_API void GspFillMmsValueToBinaryTime(BinaryTime_t &binaryTime, GspMmsValue *value);

/**
 * @brief fillMmsValueToOctetString 转换 mmsvalue 成 八位串
 * @param octetString 需要接受转换后数据的 字符串
 * @param value 带转换的 mmsvalue
 */
LIB860_API void GspFillMmsValueToOctetString(OCTET_STRING_t &octetString, GspMmsValue *value);

/**
 * @brief fillMmsValueToUtcTime 转换 mmsvalue 成 UTC 时间
 * @param utcTime 需要接受转换后的时间串
 * @param value 带转换的 msvalue
 */
LIB860_API void GspFillMmsValueToUtcTime(UtcTime_t &utcTime, GspMmsValue *value);


/**
 * \brief 深层次克隆一个mmsvalue （使用者注意释放内存，此时类型不全)
 */
LIB860_API GspMmsValue* GspMmsValue_clone(const GspMmsValue* self);

/**
 * \brief 深层次的从一个mmsvalue 克隆 到一个已经存在内存分配的mmsvalue 对象中
 */ 
LIB860_API bool GspMmsValue_cloneFromOther(GspMmsValue* target, const GspMmsValue* source);

/**
 * \brief 获取 mmsvalue 的当前数据类型
 * \param self mmsvalue 实例
 */
LIB860_API Data_PR GspMmsValue_getType(const GspMmsValue* self);

/**
 * \brief 释放内存
 */
LIB860_API void GspMmsValue_delete(GspMmsValue* self);

/**
 * \brief 创建一个可视化字符串
 * \param string 原始字符串
 * \return 可视化字符串
 */
LIB860_API GspMmsValue* GspMmsValue_newVisibleString(const char* string);

/**
 * \brief 创建一个新的空值字符串对象。根据尺寸参数。该函数分配容纳字符串所需的内存
 *
 * \param size 该函数分配容纳字符串所需的内存
 *
 * \return 创建出来的字符串大小
 */
LIB860_API GspMmsValue* GspMmsValue_newVisibleStringWithSize(int size);
LIB860_API GspMmsValue *GspMmsValue_newMmsStringWithSize(int size);

/**
 * \brief 创建一个二进制时间串
 * \param timeOfDay 是否只显示天.
 * \return 创建的二进制时间
 */
LIB860_API GspMmsValue* GspMmsValue_newBinaryTime(bool timeOfDay);

/**
 * \brief 创建一个可视字符串
 * \param byteArray 原始字节传
 * \param size 原始字节串长度
 * \return 创建的可视字符串
 */
LIB860_API GspMmsValue* GspMmsValue_newVisibleStringFromByteArray(uint8_t* byteArray, int size);

/**
 * \brief 创建一个字符串value
 * \param string 原始字符串
 * \return 创建一个字符串
 */
LIB860_API GspMmsValue* GspMmsValue_newMmsString(const char* string);

/**
 * \brief 创建一个UTCs时间串
 * \param timeval 纪元时间(秒数)
 * \return 创建好的utc时间串
 */
LIB860_API GspMmsValue* GspMmsValue_newUtcTime(uint32_t timeval);

/**
 * \brief 创建一个UTCs时间串
 * \param timeval 纪元时间(毫秒数)
 * \return 创建好的utc时间串
 */
LIB860_API GspMmsValue* GspMmsValue_newUtcTimeByMsTime(uint64_t timeval);

/**
 * \brief 标记该数据值需要删除
 * \param self value指针
 */
LIB860_API void GspMmsValue_setDeletable(GspMmsValue* self);

/**
 * \brief 递归的标记该数据值需要删除
 * \param self value指针
 */ 
LIB860_API void GspMmsValue_setDeletableRecursive(GspMmsValue* value);

/**
 * \brief 获取双点值的尺寸
 * \param self value指针
 */ 
LIB860_API int GspMmsValue_getDbPosSize(GspMmsValue *self);

/**
 * \brief 创建 bitstrng
 * \param bitString 创建后的 bitstring 串
 * \param buf 原始串
 * \param size 数据串尺寸
 * \param bitUnused 多少位未使用
 */
LIB860_API void GspBIT_STRING_createBitString(BIT_STRING_t *bitString, const char *buf, int size, int bitUnused);

/**
 * \brief 设置bit串的值
 * \param bitString 设置后的bit串值
 * \param bit 第几位bit串
 * \param state 状态值
 */ 
LIB860_API void GspBIT_STRING_setBit(BIT_STRING_t *bitString, int bit, bool state);

/**
 * \brief 获取结构提类型的子素类型
 * \param self the MmsValue instance
 * \param varSpec - type specification if the MMS_STRUCTURE value
 * \param mmsPath - path (in MMS variable name syntax) to specify the sub element.
 * \return the sub elements MmsValue instance or NULL if the element does not exist
 */
LIB860_API GspMmsValue* GspMmsValue_getSubElement(GspMmsValue* self, GspMmsVariableSpecification* varSpec, char* mmsPath);

/**
 * \brief 打印数据到目标内存上
 * NOTE: 该函数仅用来调试. 他不能被用在嵌入式系统中。它需要snprintf函数的全特性的支持.
 * \param self mmsvalue 实例
 * \param buffer 待拷贝的内存的指针
 * \param bufferSize 提供的内存大小
 * \return 指向输出内存指针的开始位置
 */
LIB860_API void GspMmsValue_printToBuffer(const GspMmsValue* self);

LIB860_API string GspMmsValueToPrint(const GspMmsValue *self);

LIB860_API void GspMmsValue_setBitStringFromString(GspMmsValue *self, const char *value);
#endif /* GSP_MMS_VALUE_H_ */
