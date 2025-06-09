//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XUser.h  CXUser

#pragma once

#include "../API/StringApi.h"

class CXBuf_Utf8_to_CharGBK
{
public:
	CXBuf_Utf8_to_CharGBK();
	virtual ~CXBuf_Utf8_to_CharGBK();

	wchar_t* charUtf8_to_charGBK(char *pStrUtf8, long nLen);
	long GetUseLen_DestGBK(){return m_nUseLen_DestGBK;}//zhouhj 20211012 增加用于获取实际使用长度
protected:
	char *m_pBuf_SrcUtf8;
	long m_nLen_SrcUtf8_Buf;

	wchar_t *m_pBuf_DestCharGBK;
	long m_nLen_DestCharGBK;//zhouhj 20211012  目标字符申请的内存空间长度
	long m_nUseLen_DestGBK;//实际使用长度

	long CopyToSrcUtf8(char *pStrUtf8, long nLen);

};

