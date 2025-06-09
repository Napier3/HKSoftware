

#if !defined(_WEQUATIONBUFFER_H__)
#define _WEQUATIONBUFFER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WBufferBase.h"
#include "..\AtlBaseClass\AtlBaseObjectList.h"


class CWEqtnKey : public CAtlBaseObject
{
public:
	CWEqtnKey();
	CWEqtnKey(wchar_t* pszKeyName,wchar_t* pszValue);
	CWEqtnKey(const CComBSTR &strKeyName,const CComBSTR &strValue);
	CWEqtnKey(wchar_t* pszKeyNameBegin,wchar_t* pszKeyNameEnd
		,wchar_t* pszValueBegin,wchar_t* pszValueEnd);
	virtual ~CWEqtnKey();
	
	CComBSTR m_strKeyName;
	CComBSTR m_strKeyValue;
	
public:
	BOOL IsLegal()
	{
		return ((m_strKeyName.Length()>0) && (m_strKeyValue.Length() > 0));
	}
	
	BOOL CompareName(const CComBSTR &strName)
	{
		if ( !IsLegal())
			return FALSE;
		
		return (m_strKeyName == strName);
	}
	
	void GetKeyValue(CComBSTR &strValue);
	void GetKeyValue(int *pVal);
	void GetKeyValue(long *pVal);
	void GetKeyValue(float *pVal);
	void GetKeyValue(double *pVal);
	void SetKeyValue(const CComBSTR &strValue);
	void SetKeyValue(int nVal);
	void SetKeyValue(long nVal);
	void SetKeyValue(float fVal);
	void SetKeyValue(double dVal);
	
protected:
	virtual bool IsASeparateChar(TCHAR ch);
	
	static const long g_nTempBufferLen;
};

class CWEquationBuffer : public CWBufferBase  
{
public:
	CWEquationBuffer();
	CWEquationBuffer(const CComBSTR &strBuff);
	CWEquationBuffer(wchar_t* pszBuff);
	CWEquationBuffer(const CWBufferBase *pBuffer);
	CWEquationBuffer(wchar_t* pBuffBegin, wchar_t* pBuffEnd);
	virtual ~CWEquationBuffer();

	//解析接口
	CComBSTR operator[](const CComBSTR &strKeyName);
	CComBSTR operator[](wchar_t* pszKeyName);
	BOOL ParseInt(wchar_t* pszKey, int *pVal);
	BOOL ParseInt(const CComBSTR &strKey, int *pVal);
	BOOL ParseLong(wchar_t* pszKey, long *pVal);
	BOOL ParseLong(const CComBSTR &strKey, long *pVal);
	BOOL ParseFloat(wchar_t* pszKey, float *pVal);
	BOOL ParseFloat(const CComBSTR &strKey, float *pVal);
	BOOL ParseDouble(wchar_t* pszKey, double *pVal);
	BOOL ParseDouble(const CComBSTR &strKey, double *pVal);
	BOOL ParseString(wchar_t* pszKey, wchar_t *pszVal);
	BOOL ParseString(wchar_t* pszKey, CComBSTR &strVal);
	BOOL ParseString(const CComBSTR &strKey, wchar_t *pszVal);
	BOOL ParseString(const CComBSTR &strKey, CComBSTR &strVal);
	void FormatAroundSeparate(wchar_t chSeparate);

	//设置关键字的值，如果关键字不存在且bAddNew==1，则新建关键字  2005/07/18  李俊庆
	long SetKeyValue(wchar_t* pszKey, wchar_t *pszVal,long bAddNew);
	long SetKeyValue(const CComBSTR &strKey, const CComBSTR &strVal,long bAddNew);
	long SetKeyValueEx(const CComBSTR &strScript,long bAddNew);
	
	//获取等式的全部数据
	void GetEquationData(CComBSTR &strEquationData);
	void GetEquationData(BSTR *pbstrEquationData);

	//2006.05.22  获取等式的关键字的名称和数据
	long GetKeyCount();
	BOOL GetKey(long nIndex,BSTR *pbstrName,BSTR *pbstrValue);
	BOOL GetKey(long nIndex,CComBSTR &strName,CComBSTR &strValue);
	void FreeAllKeys()    {     m_listEquationKey.DeleteAll();     }
	
public:
	virtual BOOL ReadFromFile(const CComBSTR &strFile);
	virtual BOOL WriteToFile(const CComBSTR &strFile);

	//初始化缓冲区
	virtual void InitBuffer(const CComBSTR &strBuff);
	virtual void InitBuffer(BSTR strBuff);
	virtual void InitBuffer(const CWBufferBase *pBuffer);
	virtual void InitBuffer(wchar_t* pBuffBegin, wchar_t* pBuffEnd);
	
	//初始化缓冲区，缓冲区的大小比实际的大
	virtual void FormatBufferEx();
	
	//分隔符号
	virtual wchar_t GetSeparateChar(){return '=';}
	virtual wchar_t GetSeparateEndChar(){return ';';}
	CAtlBaseObjectList* GetList()
	{
		return &m_listEquationKey;
	}

protected:
	virtual BOOL IsIgnoreChar(wchar_t ch);
	virtual BOOL PartString(wchar_t* pszSrcBegin,wchar_t* pszSrcEnd
		,wchar_t **pszLeftBegin,wchar_t **pszLeftEnd
		,wchar_t **pszRightBegin,wchar_t **pszRightEnd
		,wchar_t cPart,wchar_t cEnd);
	
protected:
	wchar_t* FindSeparateKey(wchar_t *pBeginPos,wchar_t chSeparate);
	void OffsetBack(wchar_t **pPos);
	void Copy(wchar_t **pDestPos,wchar_t *pSrcBegin,wchar_t *pSrcEnd);

	//解析部分
	CAtlBaseObjectList m_listEquationKey;//等式关键字表

	void InitEquationKeyList();
	BOOL GetOneLine(wchar_t **pszLineBegin,wchar_t **pszLineEnd);

	static const wchar_t g_wchKeyEquation;
	static const wchar_t g_wchKeySeperator;
	static const CComBSTR g_strKeyNewLine;

public:
	CWEqtnKey* FindEquationKey(const CComBSTR &strKeyName);
	CWEqtnKey* FindEquationKey(wchar_t* pszKeyName);
	CWEqtnKey* FindEquationKey(long nIndex);
	CWEqtnKey* FindEquationKey(const VARIANT &vIndex);
	
};

#endif // !defined(_WEQUATIONBUFFER_H__)
