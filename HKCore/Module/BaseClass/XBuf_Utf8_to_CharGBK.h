//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XUser.h  CXUser

#pragma once

#include "../API/StringApi.h"

class CXBuf_Utf8_to_CharGBK
{
public:
	CXBuf_Utf8_to_CharGBK();
	virtual ~CXBuf_Utf8_to_CharGBK();

	wchar_t* charUtf8_to_charGBK(char *pStrUtf8, long nLen);
	long GetUseLen_DestGBK(){return m_nUseLen_DestGBK;}//zhouhj 20211012 �������ڻ�ȡʵ��ʹ�ó���
protected:
	char *m_pBuf_SrcUtf8;
	long m_nLen_SrcUtf8_Buf;

	wchar_t *m_pBuf_DestCharGBK;
	long m_nLen_DestCharGBK;//zhouhj 20211012  Ŀ���ַ�������ڴ�ռ䳤��
	long m_nUseLen_DestGBK;//ʵ��ʹ�ó���

	long CopyToSrcUtf8(char *pStrUtf8, long nLen);

};

