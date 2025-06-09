/*
 *  string_utilities.h
 *  字符串操作封装
 */

#ifndef GSP_STRING_UTILITIES_H_
#define GSP_STRING_UTILITIES_H_

#include "libdlt860_common_api.h"
#include "gsp_linked_list.h"
#include <string>

using namespace std;

namespace GSP {

/**
 * @brief GspStringTrim 字符串移除空格
 * @param paramString
 * @return
 */
LIB860_INTERNAL string& GspStringTrim(string &paramString);

/**
 * @brief replace_all_distinct 字符串替换
 * @param paramSrcStr 原始字符串
 * @param paramOldStr 旧字符串
 * @param paramNewStr 新字符串
 * @return
 */
LIB860_API string& replace_all_distinct(string& paramSrcStr, const string& paramOldStr, const string& paramNewStr);

/**
 * @brief StringUtils_copyString 字符串拷贝(使用者释放)
 * @param string 源字符串
 * @return 拷贝后的字符串指针
 */
LIB860_INTERNAL char* StringUtils_copyString(const char* string);

/**
 * @brief StringUtils_copyStringToBuffer 字符串拷贝(拷贝到指定内存中)
 * @param string 源字符串
 * @param buffer 目的缓存
 * @return 拷贝后的字符串指针
 */
LIB860_INTERNAL char* StringUtils_copyStringToBuffer(const char* string, char* buffer);

/**
 * @brief StringUtils_copySubString 字符串拷贝(子串)
 * @param startPos 开始位置指针
 * @param endPos 结束位置指针
 * @return 拷贝后的字符串指针
 */
LIB860_INTERNAL char* StringUtils_copySubString(char* startPos, char* endPos);

/**
 * \brief 用给定的变参字符串构建字符串缓存
 * @param count 字符串数量
 */
LIB860_INTERNAL char* StringUtils_createString(int count, ...);

/**
 * \brief 用给定的变参字符串构建字符串缓存到指定的缓存中
 * @param count 字符串数量
 * @param buffer 目标缓存
 */
LIB860_INTERNAL char* StringUtils_createStringInBuffer(char* buffer, int count, ...);

/**
 * @brief StringUtils_createStringFromBuffer 把字节缓存转换成字符串
 * @param buf 字节缓存
 * @param size 字节缓存的大小
 * @return 转换后的字符串指针
 */
LIB860_INTERNAL char* StringUtils_createStringFromBuffer(const uint8_t* buf, int size);

/**
 * @brief StringUtils_createStringFromBufferInBuffer 把字节缓存转换成字符串并保存到指定的内存中
 * @param newString 目标字符串
 * @param buf 源内存
 * @param size 源内存大小
 * @return 转换后的字符串指针
 */
LIB860_INTERNAL char* StringUtils_createStringFromBufferInBuffer(char* newString, const uint8_t* buf, int size);

/**
 * @brief StringUtils_replace 替换字符串中的指定字符
 * @param string 字符串指针
 * @param oldChar 源字符
 * @param newChar 新字符
 */
LIB860_INTERNAL void StringUtils_replace(char* string, char oldChar, char newChar);

/**
 * @brief StringUtils_isDigit 制定字符是否是数字类型
 * @param character 待检测字符
 * @return true 是数字 false 不是数字
 */
LIB860_INTERNAL bool StringUtils_isDigit(char character);

/**
 * @brief StringUtils_digitToInt 单个正整数数字字符转整型
 * @param digit 数字字符
 * @return 转换后的数字 ,如果异常为 -1
 */
LIB860_INTERNAL int StringUtils_digitToInt(char digit);

/**
 * @brief StringUtils_digitsToInt 多个正整数字符转整型
 * @param digits 数字字符串
 * @param count 转换后的数字,如果异常为-1
 * @return
 */
LIB860_INTERNAL int StringUtils_digitsToInt(const char* digits, int count);

/**
 * @brief StringUtils_createBufferFromHexString 转换16进制数据串为字符串到指定内存中
 * @param hexString 十六进制数据串
 * @param buffer 目标内存
 * @return 转换后的字节数量,如果异常为-1
 */
LIB860_INTERNAL int StringUtils_createBufferFromHexString(char* hexString, uint8_t* buffer);

/**
 * @brief StringUtils_startsWith 字符串是否以指定字串开头
 * @param string 字符串指针
 * @param prefix 子串
 * @return 是否包含
 */
LIB860_INTERNAL bool StringUtils_startsWith(char* string, const char* prefix);

/**
 * @brief StringUtils_endsWith 字符串是否以指定字串结尾
 * @param str 字符串指针
 * @param suffix 子串
 * @return 是否包含
 */
LIB860_INTERNAL bool StringUtils_endsWith(const char* str, const char* suffix);

/**
 * \brief 字符比较
 *
 * \param a the first string
 * \param b the second string
 *
 * \returns 0 两个字符相等; 正数 b 大于 a; 负数 b 小于 a
 */
LIB860_INTERNAL int StringUtils_compareChars(char a, char b);

/**
 * \brief 字符串比较
 *
 * \param a the first string
 * \param b the second string
 *
 * \returns  0 两个字符相等; 正数 b 大于 a; 负数 b 小于 a
 */
LIB860_INTERNAL int StringUtils_compareStrings(const char* a, const char* b);

/**
 * \brief 对字符串列表进行排序 (according to the MMS identifier collation order)
 *
 * \param list 字符串列表,元素内容是字符串
 */
LIB860_INTERNAL void StringUtils_sortList(GSP::GspLinkedList list);

/**
 * \brief 把 IPv6 地址串转换到目标字节数组 (uint8_t array)
 *
 * \param addressString IPv6 地址的标准符号
 * \param ipV6Addr 存储转换后的地址 (has to be at least 16 bytes)
 *
 * \return true 解析成功 false 解析失败
 */
LIB860_INTERNAL bool StringUtils_convertIPv6AdddressStringToByteArray(const char* addressString, uint8_t ipV6Addr[]);

}

#endif /* GSP_STRING_UTILITIES_H_ */
