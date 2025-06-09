/*
 *  conversions.h
 *  数据转换接口
 */

#ifndef GSP_CONVERSIONS_H_
#define GSP_CONVERSIONS_H_

#include "libdlt860_common_api.h"

/**
 * @brief Conversions_intToStringBuffer 十进制数字转换成字符串
 * @param intValue 整型数字
 * @param numberOfDigits 数字位数
 * @param buffer 转换后的缓存
 */
LIB860_INTERNAL void Conversions_intToStringBuffer(int intValue, int numberOfDigits, uint8_t* buffer);

/**
 * @brief Conversions_msTimeToGeneralizedTime 转换时间戳成字符串
 * @param msTime 时间戳,毫秒(距离1900的时间)
 * @param buffer 转换后的数据串
 */
LIB860_INTERNAL void Conversions_msTimeToGeneralizedTime(uint64_t msTime, uint8_t* buffer);

/**
 * @brief Conversions_generalizedTimeToMsTime 转换时间到毫秒数
 * @param gtString 距离1900的时间串
 * @return
 */
LIB860_INTERNAL uint64_t Conversions_generalizedTimeToMsTime(const char* gtString);

/**
 * @brief memcpyReverseByteOrder 转换字节顺序
 * @param dst 目地
 * @param src 源
 * @param size 需要转换的字节数量
 */
LIB860_INTERNAL void memcpyReverseByteOrder(uint8_t* dst, const uint8_t* src, int size);

/**
 * @brief convertUtcTimeToMs 转换UTC时间到毫秒
 */ 
LIB860_INTERNAL uint64_t convertUtcTimeToMs(UtcTime_t &utcTime);

/**
 * @brief BRCB_Clone 缓存的报告控制块克隆(新分配内存)
 */ 
LIB860_INTERNAL BRCB_t* BRCB_Clone(BRCB_t* paramOther);

/**
 * @brief URCB_Clone 非缓存的报告控制块克隆(新分配内存)
 */
LIB860_INTERNAL URCB_t* URCB_Clone(URCB_t* paramOther);

/**
 * @brief GRCB_Clean 清空控制块的所有值（并释放内存）
 * @param paramother 控制块指针
 */
LIB860_INTERNAL void GRCB_Clean(GSPRCB paramother);

/**
 * @brief GRCB_Clean_Without_Reference 清空控制块的值, 保留控制块参引串
 * @param paramother 控制块指针
 */
LIB860_INTERNAL void GRCB_Clean_Without_Reference(GSPRCB paramother);

/**
 * @brief GRCB_Clean_Without_SetReport 清空控制块的值, 保留设置选项外的一些内容
 * @param paramother
 */
LIB860_INTERNAL void GRCB_Clean_Without_SetReport(GSPRCB paramother);

/**
 * @brief BRCB_convert 缓存的报告控制快转换为gsp报告控制块的形式
 * @param paramOther 缓存的报告控制块
 * @return gsp 报告控制块的值
 */
LIB860_INTERNAL GSPRCB BRCB_convert(BRCB_t* paramOther);

/**
 * @brief URCB_convert 非缓存的报告控制快转换为gsp报告控制块的形式
 * @param paramOther 缓存的报告控制块
 * @return gsp 报告控制块的值
 */
LIB860_INTERNAL GSPRCB URCB_convert(URCB_t* paramOther);

/**
 * @brief Reference_GetReportNumber 获取报告实例号(使用者注意释放内存)
 */ 
LIB860_INTERNAL char* Reference_GetReportNumber(const char* brcbReference);

/**
 * @brief BitString_Clone bitstrng 克隆
 */ 
LIB860_INTERNAL BIT_STRING_s* BitString_Clone(BIT_STRING_t* paramOther);

/**
 * @brief BitString_Update bitstring 更新
 */ 
LIB860_INTERNAL bool BitString_Update(BIT_STRING_t* &paramTarget, BIT_STRING_t* paramOther);
LIB860_INTERNAL bool BitString_Update(BIT_STRING_t &paramTarget, BIT_STRING_t* paramOther);

/**
 * @brief BitString_Printf 打印bitString 方便调试
 */
LIB860_INTERNAL void BitString_Printf(BIT_STRING_t* paramOther);

/**
 * @brief BitString_getBitSize 获取bitString 的有效位长度
 */ 
LIB860_INTERNAL int BitString_getBitSize(BIT_STRING_t* paramOther);

/**
 * @brief BitString_getBitValue 获取指定位置的 bit 值
 */ 
LIB860_INTERNAL bool BitString_getBitValue(BIT_STRING_t* paramOther, int bitPos);

/**
 * @brief BitString_setBitValue 设置指定位置的 bit 值
 */ 
LIB860_INTERNAL bool BitString_setBitValue(BIT_STRING_t* paramOther, int bitPos, bool bitValue);


#endif /* GSP_CONVERSIONS_H_ */
