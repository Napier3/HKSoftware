

#if !defined(_FormatTextBuffer_H__)
#define _FormatTextBuffer_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
	{*|& | Text(����) | Binary(0X######)}-{*|& | T(����) | Binary(0X######)}-{*|& | T(����) | Binary(0X######)}
*/

#define FTITYPE_MULTI   0
#define FTITYPE_SINGLE  1
#define FTITYPE_TEXT    2
#define FTITYPE_BINARY  3

#include "BufferBase.h"
#include "../BaseClass/BaseList.h"

class CFormatTextItem : public CBaseObject
{
public:
	CFormatTextItem();
	virtual ~CFormatTextItem();

	long m_nType;   //���ͣ�0=* �� 1=&   2=Text  3= Binary
//	CString m_strText;   //�ı���Text("000000")�е����ݣ�Binary("0x00000000")�е�����
	unsigned char m_pBuffer[MAX_PATH]; //Text��Binary�е�����ת���ɻ����ı�
	long m_nBufferLength;
	unsigned char *m_pValue;
	long m_nValueLength;

	//2018-12-4  ��������Ĺ�ϵ
	long m_nChildBuffCount;
	long m_nChildBufferLen[10];
public:
	void SetItem(long nType, const char *pszText);
	void SetItem_Binary(long nType, const char *pszText);
	void GetItemText(CString &strText);
	void GetItemText_Binary(CString &strText);
	void SetValue(BYTE *pBegin, BYTE *pEnd);

	BOOL MemCmp(BYTE *pBuffer);
private:
	void FreeValueBuffer();
};

class CFormatTextBuffer : public CBufferBase, public CBaseList
{
public:
	CFormatTextBuffer();
	CFormatTextBuffer(const CString &strBuff);
	CFormatTextBuffer(const char *pszBuff);
	CFormatTextBuffer(const CBufferBase *pBuffer);
	CFormatTextBuffer(const char *pBuffBegin,const char *pBuffEnd);
	virtual ~CFormatTextBuffer();

	static const char *g_pszTextKey;
	static const char *g_pszBinaryKey;

public:
	//��ʼ��������
	virtual void InitBuffer(const CString &strBuff);
	virtual void InitBuffer(const CBufferBase *pBuffer);
	virtual void InitBuffer(const char *pBuffBegin,const char *pBuffEnd);
	
	//��ʼ�����������������Ĵ�С��ʵ�ʵĴ�
	virtual void FormatBufferEx();
	
	//�ָ�����
	virtual char GetSeparateChar(){return '=';}
	virtual char GetSeparateEndChar(){return ';';}

	BOOL ParseFormatBuffer(const BYTE *pBuffer, long nBufferLen);
	BOOL GetFormatBuffer(CString &strText);
	long GetLength();
	long GetData(long nIndex, BYTE *pDataDest);

	CFormatTextItem* AddItem(long nType, const char *pText);
	CFormatTextItem* AddItem(long nType, const CString &strText);

protected:
	virtual BOOL IsIgnoreChar(char ch);

	BOOL IsBlockBegin(const char *pBuffer)	{	return (*pBuffer == '{');	}
	BOOL IsBlockEnd(const char *pBuffer)	{	return (*pBuffer == '}');	}
	BOOL IsTextKey(const char *pBuffer)		{	return ( strncmp(pBuffer, g_pszTextKey, strlen(g_pszTextKey)) == 0 );	}
	BOOL IsBinaryKey(const char *pBuffer)	{	return ( strncmp(pBuffer, g_pszBinaryKey, strlen(g_pszBinaryKey)) == 0 );	}


	BOOL PartString(const char *pszSrcBegin,const char *pszSrcEnd, char *pString);
	BOOL PartString_Binary(const char *pszSrcBegin,const char *pszSrcEnd, char *pString);
	BOOL PartBlock(const char *pszSrcBegin,const char *pszSrcEnd);
	void FormatTextBuffer();
	BOOL GetOneLine(char **pszLineBegin,char **pszLineEnd);
	CFormatTextItem* FindEquationKey(const CString &strKeyName);
	CFormatTextItem* FindEquationKey(const char *pszKeyName);


	//////////////////////////////////////////////////////////////////////////
	BYTE *m_pFormatDataBuffer;
	BYTE *m_pFormatDataBufEnd;
	BYTE *m_pFormatCurr;
	long m_nFormatDataLength;
	BOOL ParseItemMulti(CFormatTextItem *pItem, CFormatTextItem *pNext);
	BOOL ParseItemSingle(CFormatTextItem *pItem);
	BOOL ParseItemText(CFormatTextItem *pPrev, CFormatTextItem *pItem);
	BOOL ParseItemBinary(CFormatTextItem *pPrev, CFormatTextItem *pItem);
};

#endif // !defined(_FormatTextBuffer_H__)
