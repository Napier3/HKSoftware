

#if !defined(_EQUATIONBUFFER_H__)
#define _EQUATIONBUFFER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BufferBase.h"
#include "EquationKey.h"

#define EQUATION_SP_END_KEY_MAX_LEN  32

class CEquationBuffer : public CBufferBase, public CBaseList
{
public:
	CEquationBuffer();
	CEquationBuffer(const CString &strBuff);
	CEquationBuffer(const char *pszBuff);
	CEquationBuffer(const CBufferBase *pBuffer);
	CEquationBuffer(const char *pBuffBegin,const char *pBuffEnd);
	virtual ~CEquationBuffer();

	//解析接口
	CString operator[](const CString &strKeyName);
	CString operator[](const char *pszKeyName);
	long ParseInt(const char *pszKey, int *pVal);
	long ParseInt(const CString &strKey, int *pVal);
	long ParseLong(const char *pszKey, long *pVal);
	long ParseLong(const CString &strKey, long *pVal);
	long ParseFloat(const char *pszKey, float *pVal);
	long ParseFloat(const CString &strKey, float *pVal);
	long ParseString(const char *pszKey, char *pszVal, int nMaxLen);
	long ParseString(const char *pszKey, CString &strVal);
	long ParseString(const CString &strKey, char *pszVal, int nMaxLen);
	long ParseString(const CString &strKey, CString &strVal);
	void FormatAroundSeparate(char chSeparate);
	void FormatAroundSeparate(char *pszSeparate);

	//设置关键字的值，如果关键字不存在且bAddNew==1，则新建关键字  2005/07/18  李俊庆
	long SetKeyValue(const char *pszKey, char *pszVal,long bAddNew);
	long SetKeyValue(const CString &strKey, const CString &strVal,long bAddNew);
	long SetKeyValueEx(const CString &strScript,long bAddNew);
	
	//获取等式的全部数据
	void GetEquationData(CString &strEquationData);
	void GetEquationData(BSTR *pbstrEquationData);

	//2006.05.22  获取等式的关键字的名称和数据
	long GetKeyCount();
	BOOL GetKey(long nIndex,BSTR *pbstrName,BSTR *pbstrValue);
	BOOL GetKey(long nIndex,CString &strName,CString &strValue);
	void FreeAllKeys()    {     DeleteAll();     }
	
public:
	virtual BOOL ReadFromFile(const char *pszFile);
	virtual BOOL ReadFromFile(const CString &strFile);
	virtual BOOL WriteToFile(const CString &strFile);

	//初始化缓冲区
	virtual void InitBuffer(const CString &strBuff);
	virtual void InitBuffer(const CBufferBase *pBuffer);
	virtual void InitBuffer(const char *pBuffBegin,const char *pBuffEnd);
	
	//初始化缓冲区，缓冲区的大小比实际的大
	virtual void FormatBufferEx();
	
	//分隔符号
	virtual char GetSeparateChar()					{	return m_chSeparateChar;	}
	virtual char GetSeparateEndChar()				{	return m_chSeparateEndChar;	}
	virtual char* GetSeparateCharEx()					{	return m_pszSeparateChar;	}
	virtual char* GetSeparateEndCharEx()				{	return m_pszSeparateEndChar;	}
	virtual void SetSeparateChar(char ch)		{	m_chSeparateChar = ch;		}
	virtual void SetSeparateEndChar(char ch)	{	m_chSeparateEndChar = ch;	}
	virtual void SetSeparateChar(char *ch)		{	strcpy(m_pszSeparateChar, ch);		}
	virtual void SetSeparateEndChar(char *ch)	{	strcpy(m_pszSeparateEndChar, ch);	}
	virtual void SetSeparateChar(const CString &str);
	virtual void SetSeparateEndChar(const CString &str);

protected:
	virtual BOOL IsIgnoreChar(char ch);
	virtual BOOL PartString(const char *pszSrcBegin,const char *pszSrcEnd
		,char **pszLeftBegin,char **pszLeftEnd
		,char **pszRightBegin,char **pszRightEnd
		,char cPart,char cEnd);
	virtual BOOL PartString(const char *pszSrcBegin,const char *pszSrcEnd
		,char **pszLeftBegin,char **pszLeftEnd
		,char **pszRightBegin,char **pszRightEnd
		,char *pszPart,char *pszEnd);
	
	char m_chSeparateChar;
	char m_chSeparateEndChar;
	char m_pszSeparateChar[EQUATION_SP_END_KEY_MAX_LEN];
	char m_pszSeparateEndChar[EQUATION_SP_END_KEY_MAX_LEN];

	void InitSeparateChar();
protected:
	char* FindSeparateKey(char *pBeginPos,char chSeparate);
	char* FindSeparateKey(char *pBeginPos,char *pszSeparate);
	void OffsetBack(char **pPos);
	void Copy(char **pDesPOS,char *pSrcBegin,char *pSrcEnd);

	void InitEquationKeyList();
	BOOL GetOneLine(char **pszLineBegin,char **pszLineEnd);
	CEquationKey* FindEquationKey(const char *pszKeyName);

public:
	CEquationKey* FindEquationKey(const CString &strKeyName);
};

#endif // !defined(_EQUATIONBUFFER_H__)
