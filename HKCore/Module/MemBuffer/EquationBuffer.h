

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

	//�����ӿ�
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

	//���ùؼ��ֵ�ֵ������ؼ��ֲ�������bAddNew==1�����½��ؼ���  2005/07/18  ���
	long SetKeyValue(const char *pszKey, char *pszVal,long bAddNew);
	long SetKeyValue(const CString &strKey, const CString &strVal,long bAddNew);
	long SetKeyValueEx(const CString &strScript,long bAddNew);
	
	//��ȡ��ʽ��ȫ������
	void GetEquationData(CString &strEquationData);
	void GetEquationData(BSTR *pbstrEquationData);

	//2006.05.22  ��ȡ��ʽ�Ĺؼ��ֵ����ƺ�����
	long GetKeyCount();
	BOOL GetKey(long nIndex,BSTR *pbstrName,BSTR *pbstrValue);
	BOOL GetKey(long nIndex,CString &strName,CString &strValue);
	void FreeAllKeys()    {     DeleteAll();     }
	
public:
	virtual BOOL ReadFromFile(const char *pszFile);
	virtual BOOL ReadFromFile(const CString &strFile);
	virtual BOOL WriteToFile(const CString &strFile);

	//��ʼ��������
	virtual void InitBuffer(const CString &strBuff);
	virtual void InitBuffer(const CBufferBase *pBuffer);
	virtual void InitBuffer(const char *pBuffBegin,const char *pBuffEnd);
	
	//��ʼ�����������������Ĵ�С��ʵ�ʵĴ�
	virtual void FormatBufferEx();
	
	//�ָ�����
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
