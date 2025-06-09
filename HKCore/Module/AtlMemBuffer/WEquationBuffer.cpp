  // EquationBuffer.cpp: implementation of the CWEquationBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WEquationBuffer.h"
#include "..\AtlBaseClass\atlfile.h"

#include "..\AtlBaseClass\ATLGloblaApi.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const long CWEqtnKey::g_nTempBufferLen = 32;

CWEqtnKey::CWEqtnKey()
{
	m_strKeyName = "";
	m_strKeyValue = "";	

// #ifdef _DEBUG
// 	ATLTRACE("new CWEqtnKey=0x%08X\r\n", (long)this);
// #endif
}

CWEqtnKey::CWEqtnKey(const CComBSTR &strKeyName,const CComBSTR &strValue)
{
	m_strKeyName = strKeyName;
	m_strKeyValue = strValue;	
// #ifdef _DEBUG
// 	ATLTRACE("new CWEqtnKey=0x%08X\r\n", (long)this);
// #endif
}

CWEqtnKey::CWEqtnKey(wchar_t* pszKeyName,wchar_t* pszValue)
{
	m_strKeyName = pszKeyName;
	m_strKeyValue = pszValue;		
#ifdef _DEBUG
	ATLTRACE("new CWEqtnKey=0x%08X\r\n", (long)this);
#endif
}

CWEqtnKey::CWEqtnKey(wchar_t* pszKeyNameBegin,wchar_t* pszKeyNameEnd
			 ,wchar_t* pszValueBegin,wchar_t* pszValueEnd)
{
	wchar_t_to_ComBSTR(pszKeyNameBegin, pszKeyNameEnd, m_strKeyName);
	wchar_t_to_ComBSTR(pszValueBegin, pszValueEnd, m_strKeyValue);
#ifdef _DEBUG
	ATLTRACE("new CWEqtnKey=0x%08X\r\n", (long)this);
#endif
}

CWEqtnKey::~CWEqtnKey()
{

}

void CWEqtnKey::GetKeyValue(CComBSTR &strValue)
{
	strValue = m_strKeyValue;
}

void CWEqtnKey::GetKeyValue(int *pVal)
{
	*pVal = _wtoi(m_strKeyValue);
}

void CWEqtnKey::GetKeyValue(long *pVal)
{
	*pVal = _wtol(m_strKeyValue);
}

void CWEqtnKey::GetKeyValue(float *pVal)
{
//	char pszBuff[g_nTempBufferLen];
//	memset(pszBuff, 0, g_nTempBufferLen);
//	WideCharToMultiByte(CP_ACP, 0, m_strKeyValue, wcslen(m_strKeyValue), pszBuff, g_nTempBufferLen, NULL, NULL); 
//	*pVal = (float)(atof(pszBuff));
	*pVal = _bstr_to_float(m_strKeyValue);
}

void CWEqtnKey::GetKeyValue(double *pVal)
{
	char pszBuff[g_nTempBufferLen];
	memset(pszBuff, 0, g_nTempBufferLen);
	WideCharToMultiByte(CP_ACP, 0, m_strKeyValue, wcslen(m_strKeyValue), pszBuff, g_nTempBufferLen, NULL, NULL); 
	*pVal = atof(pszBuff);
}

void CWEqtnKey::SetKeyValue(const CComBSTR &strValue)
{
	m_strKeyValue = strValue;
}

void CWEqtnKey::SetKeyValue(int nVal)
{
#ifdef _UNICODE
	wchar_t pszBuff[g_nTempBufferLen];
#else
	char pszBuff[g_nTempBufferLen];
#endif

	wsprintf(pszBuff, _T("%d"), nVal);
	SetKeyValue(CComBSTR(pszBuff));
}

void CWEqtnKey::SetKeyValue(long nVal)
{
#ifdef _UNICODE
	wchar_t pszBuff[g_nTempBufferLen];
#else
	char pszBuff[g_nTempBufferLen];
#endif

	wsprintf(pszBuff, _T("%d"), nVal);
	SetKeyValue(CComBSTR(pszBuff));
}

void CWEqtnKey::SetKeyValue(float fVal)
{
#ifdef _UNICODE
	wchar_t pszBuff[g_nTempBufferLen];
#else
	char pszBuff[g_nTempBufferLen];
#endif
	
	wsprintf(pszBuff, _T("%f"), fVal);
	SetKeyValue(CComBSTR(pszBuff));
}

void CWEqtnKey::SetKeyValue(double dVal)
{
#ifdef _UNICODE
	wchar_t pszBuff[g_nTempBufferLen];
#else
	char pszBuff[g_nTempBufferLen];
#endif
	
	wsprintf(pszBuff, _T("%f"), dVal);
	SetKeyValue(CComBSTR(pszBuff));
}

//判断字符是否为分隔字符
bool CWEqtnKey::IsASeparateChar(TCHAR ch)
{
	return ( (ch == _T(';')) || (ch == '=') || (ch == '\r') || (ch == '\n') );
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const wchar_t CWEquationBuffer::g_wchKeyEquation  = '=';
const wchar_t CWEquationBuffer::g_wchKeySeperator = ';';
const CComBSTR CWEquationBuffer::g_strKeyNewLine  = "\r\n";

CWEquationBuffer::CWEquationBuffer()
{
	m_listEquationKey.DeleteAll();
}

CWEquationBuffer::CWEquationBuffer(const CComBSTR &strBuff) : CWBufferBase(strBuff)
{
	m_listEquationKey.DeleteAll();
	InitEquationKeyList();
}

CWEquationBuffer::CWEquationBuffer(wchar_t* pszBuff) : CWBufferBase(pszBuff)
{
	m_listEquationKey.DeleteAll();
	InitEquationKeyList();
}

CWEquationBuffer::CWEquationBuffer(const CWBufferBase *pBuffer) : CWBufferBase(pBuffer)
{
	m_listEquationKey.DeleteAll();
	InitEquationKeyList();
}

CWEquationBuffer::CWEquationBuffer(wchar_t* pBuffBegin,wchar_t* pBuffEnd) : CWBufferBase(pBuffBegin,pBuffEnd)
{
	m_listEquationKey.DeleteAll();
	InitEquationKeyList();
}

CWEquationBuffer::~CWEquationBuffer()
{
	m_listEquationKey.DeleteAll();
}

//解析接口
/*************************************************
//函数名称：	operator[]
//描述：    	根据关键字的名称获取对应的值
//输入参数：  	
	strKeyName：	关键字名称
	pszKeyName：	关键字名称
//输出参数：     
	无
返回值：     	如果包含关键字名称，返回对应的数据，否则抛出异常。
*************************************************/
CComBSTR CWEquationBuffer::operator[](const CComBSTR &strKeyName)
{
	CWEqtnKey *pKeyFind = FindEquationKey(strKeyName);

	if (pKeyFind == NULL)
	{
		return "";
	}
	
	return pKeyFind->m_strKeyValue;
}

CComBSTR CWEquationBuffer::operator[](wchar_t* pszKeyName)
{
	CWEqtnKey *pKeyFind = FindEquationKey(pszKeyName);

	if (pKeyFind == NULL)
	{
		return "";
	}
	
	return pKeyFind->m_strKeyValue;
}

/*************************************************
//函数名称：	ParseInt
//描述：    	根据关键字的名称获取对应的整数值
//输入参数：  	
	pszKey：	关键字名称
	strKey：	关键字名称
//输出参数：     
	pVal		返回关键字对应的整数数据
返回值：     	成功返回TRUE，否则返回FALSE。
*************************************************/
BOOL CWEquationBuffer::ParseInt(wchar_t* pszKey, int *pVal)
{
	CWEqtnKey *pKeyFind = FindEquationKey(pszKey);
	BOOL bResult = FALSE;
	
	if (pKeyFind != NULL)
	{
		bResult = TRUE;
		pKeyFind->GetKeyValue(pVal);
	}

	return bResult;
}

BOOL CWEquationBuffer::ParseInt(const CComBSTR &strKey, int *pVal)
{
	CWEqtnKey *pKeyFind = FindEquationKey(strKey);
	BOOL bResult = FALSE;
	
	if (pKeyFind != NULL)
	{
		bResult = TRUE;
		pKeyFind->GetKeyValue(pVal);
	}
	
	return bResult;
}

/*************************************************
//函数名称：	ParseLong
//描述：    	根据关键字的名称获取对应的long整数值
//输入参数：  	
	pszKey：	关键字名称
	strKey：	关键字名称
//输出参数：     
	pVal		返回关键字对应的long整数数据
返回值：     	成功返回TRUE，否则返回FALSE。
*************************************************/
BOOL CWEquationBuffer::ParseLong(wchar_t* pszKey, long *pVal)
{
	CWEqtnKey *pKeyFind = FindEquationKey(pszKey);	
	BOOL bResult = FALSE;

	if (pKeyFind != NULL)
	{
		bResult = TRUE;
		pKeyFind->GetKeyValue(pVal);
	}
	
	return bResult;
}

BOOL CWEquationBuffer::ParseLong(const CComBSTR &strKey, long *pVal)
{
	CWEqtnKey *pKeyFind = FindEquationKey(strKey);
	BOOL bResult = FALSE;
	
	if (pKeyFind != NULL)
	{
		bResult = TRUE;
		pKeyFind->GetKeyValue(pVal);
	}
	
	return bResult;
}

/*************************************************
//函数名称：	ParseFloat
//描述：    	根据关键字的名称获取对应的浮点数值
//输入参数：  	
	pszKey：	关键字名称
	strKey：	关键字名称
//输出参数：     
	pVal		返回关键字对应的浮点数数据
返回值：     	成功返回TRUE，否则返回FALSE。
*************************************************/
BOOL CWEquationBuffer::ParseFloat(wchar_t* pszKey, float *pVal)
{
	CWEqtnKey *pKeyFind = FindEquationKey(pszKey);
	BOOL bResult = FALSE;
	
	if (pKeyFind != NULL)
	{
		bResult = TRUE;
		pKeyFind->GetKeyValue(pVal);
	}
	
	return bResult;
}

BOOL CWEquationBuffer::ParseFloat(const CComBSTR &strKey, float *pVal)
{
	CWEqtnKey *pKeyFind = FindEquationKey(strKey);
	BOOL bResult = FALSE;
	
	if (pKeyFind != NULL)
	{
		bResult = TRUE;
		pKeyFind->GetKeyValue(pVal);
	}
	
	return bResult;
}

BOOL CWEquationBuffer::ParseDouble(wchar_t* pszKey, double *pVal)
{
	CWEqtnKey *pKeyFind = FindEquationKey(pszKey);
	BOOL bResult = FALSE;
	
	if (pKeyFind != NULL)
	{
		bResult = TRUE;
		pKeyFind->GetKeyValue(pVal);
	}
	
	return bResult;
}

BOOL CWEquationBuffer::ParseDouble(const CComBSTR &strKey, double *pVal)
{
	CWEqtnKey *pKeyFind = FindEquationKey(strKey);
	BOOL bResult = FALSE;
	
	if (pKeyFind != NULL)
	{
		bResult = TRUE;
		pKeyFind->GetKeyValue(pVal);
	}
	
	return bResult;
}

/*************************************************
//函数名称：	ParseString
//描述：    	根据关键字的名称获取对应的字符串数据值
//输入参数：  	
	pszKey：	关键字名称
	strKey：	关键字名称
//输出参数：     
	pszVal		返回关键字对应的字符串数据
	strVal		返回关键字对应的字符串数据
返回值：     	成功返回TRUE，否则返回FALSE。
*************************************************/
BOOL CWEquationBuffer::ParseString(wchar_t* pszKey, wchar_t *pszVal)
{
	CComBSTR strVal("");
	BOOL bResult = ParseString(pszKey,strVal);
	wcscpy(pszVal,strVal);
	
	return bResult;
}

BOOL CWEquationBuffer::ParseString(wchar_t* pszKey, CComBSTR &strVal)
{
	CWEqtnKey *pKeyFind = FindEquationKey(pszKey);
	BOOL bResult = FALSE;

	if (pKeyFind != NULL)
	{
		bResult = TRUE;
		pKeyFind->GetKeyValue(strVal);
	}
	
	return bResult;
}

BOOL CWEquationBuffer::ParseString(const CComBSTR &strKey, wchar_t *pszVal)
{
	CComBSTR strVal("");

	BOOL bResult = ParseString(strKey,strVal);
	wcscpy(pszVal,strVal);

	return bResult;
}

BOOL CWEquationBuffer::ParseString(const CComBSTR &strKey, CComBSTR &strVal)
{
	CWEqtnKey *pKeyFind = FindEquationKey(strKey);
	BOOL bResult = FALSE;
	
	if (pKeyFind != NULL)
	{
		bResult = TRUE;
		pKeyFind->GetKeyValue(strVal);
	}
	
	return bResult;
}

/*************************************************
//函数名称：	FormatAroundSeparate
//描述：    	将分隔符号前后的可以忽略的字符去掉，实际的实现是向前拷贝数据
//输入参数：  	
	chSeparate：分隔字符
//输出参数：     
	无
返回值：     	无。
*************************************************/
void CWEquationBuffer::FormatAroundSeparate(wchar_t chSeparate)
{
	wchar_t *pTemp = m_pBuffer;
	wchar_t *pEqualPos = m_pBuffer;
	wchar_t *pBuffEndPos = GetBufferEndPos();
	wchar_t *pSrcBegin = m_pBuffer;
	wchar_t *pSrcEnd = NULL;
	wchar_t *pDest = m_pBuffer;

	while (IsIgnoreChar(*pSrcBegin))
	{
		pSrcBegin++;
	}

	pEqualPos = FindSeparateKey(m_pBuffer,chSeparate);

	while (IsPoiterInBuffer(pEqualPos))
	{
		//分隔符号前的有效数据的复制
		pSrcEnd = pEqualPos-1;
		OffsetBack(&pSrcEnd);
		Copy(&pDest,pSrcBegin,pSrcEnd);
		
		//复制分隔符号
		*pDest = *pEqualPos;
		pDest++;
		pEqualPos++;

		//分隔符号前的有效数据的复制
		while (IsIgnoreChar(*pEqualPos))
			pEqualPos++;

		pSrcBegin = pEqualPos;
		pEqualPos = FindSeparateKey(pEqualPos,chSeparate);
	}
	
	pSrcEnd = pBuffEndPos;
	Copy(&pDest,pSrcBegin,pSrcEnd);
	
	while (pDest < pBuffEndPos)
	{
		*pDest = 0;
		pDest++;
	}
}

//设置关键字的值，如果关键字不存在且bAddNew==1，则新建关键字  2005/07/18  李俊庆
long CWEquationBuffer::SetKeyValue(wchar_t* pszKey, wchar_t *pszVal,long bAddNew)
{
	CWEqtnKey *pKeyFind = FindEquationKey(pszKey);
	BOOL bResult = FALSE;
	
	if (pKeyFind == NULL)
	{
		if (bAddNew == 1)
		{
			if (wcslen(pszKey) > 0)
			{
				pKeyFind = new CWEqtnKey(pszKey,pszVal);
				m_listEquationKey.AddTail(pKeyFind);
			}
		}
	}
	else
	{
		bResult = TRUE;
		pKeyFind->SetKeyValue(pszVal);
	}
	
	return bResult;
}
long CWEquationBuffer::SetKeyValue(const CComBSTR &strKey, const CComBSTR &strVal,long bAddNew)
{
	CWEqtnKey *pKeyFind = FindEquationKey(strKey);
	BOOL bResult = FALSE;
	
	if (pKeyFind == NULL)
	{
		if (bAddNew == 1)
		{
			if (strKey.Length() > 0)
			{
				pKeyFind = new CWEqtnKey(strKey,strVal);
				m_listEquationKey.AddTail(pKeyFind);
			}
		}
	}
	else
	{
		bResult = TRUE;
		pKeyFind->SetKeyValue(strVal);
	}
	
	return bResult;
}

long CWEquationBuffer::SetKeyValueEx(const CComBSTR &strScript,long bAddNew)
{
	CWEquationBuffer buff;
	buff.InitBuffer(strScript);	
	CWEqtnKey *pKey = NULL;
	POS pos = buff.m_listEquationKey.GetHeadPosition();

	while (pos != NULL)
	{
		pKey = (CWEqtnKey*)buff.m_listEquationKey.GetNext(pos);
		SetKeyValue(pKey->m_strKeyName,pKey->m_strKeyValue,bAddNew);
	}
	
	return S_OK;
}

void CWEquationBuffer::GetEquationData(BSTR *pbstrEquationData)
{
//	IStringSerializeBuffInterface *pStrBuff = NULL;
//	CreateStringSerializeBuffInterface(&pStrBuff);
//	POS pos = m_listEquationKey.GetHeadPosition();
//	CWEqtnKey *pKey = NULL;
//	if (pStrBuff == NULL)
//	{
//		CComBSTR strEquationData;
//		CComBSTR strTemp ;
//		while (pos != NULL)
//		{
//			pKey = (CWEqtnKey*)m_listEquationKey.GetNext(pos);
//			strTemp.Format("%s=%s;\r\n",pKey->GetKeyName2(),pKey->GetKeyValue2());
//			strEquationData += strTemp;
//		}
//		*pbstrEquationData = strEquationData.AllocSysString();
//	}
//	else
//	{
//		GetEquationData(pStrBuff);
//		pStrBuff->GetBuffer2(pbstrEquationData);
//		pStrBuff->Release();
//	}
}

void CWEquationBuffer::GetEquationData(CComBSTR &strEquationData)
{
/*
	IStringSerializeBuffInterface *pStrBuff = NULL;
	CreateStringSerializeBuffInterface(&pStrBuff);
	POS pos = m_listEquationKey.GetHeadPosition();
	CWEqtnKey *pKey = NULL;
	if (pStrBuff == NULL)
	{
		CComBSTR strTemp ;
		while (pos != NULL)
		{
			pKey = (CWEqtnKey*)m_listEquationKey.GetNext(pos);
			strTemp.Format("%s=%s;\r\n",pKey->GetKeyName2(),pKey->GetKeyValue2());
			strEquationData += strTemp;
		}
	}
	else
	{
		BSTR bstrData;
		GetEquationData(pStrBuff);
		pStrBuff->GetBuffer2(&bstrData);
		strEquationData = bstrData;
		pStrBuff->Release();
	}
*/
}

/*
void CWEquationBuffer::GetEquationData(IStringSerializeBuffInterface *pStrBuff)
{
	POS pos = m_listEquationKey.GetHeadPosition();
	CWEqtnKey *pKey = NULL;
	if (pStrBuff == NULL)
	{
		return ;
	}

	pStrBuff->SetModeCalSize();
	pStrBuff->IncreaseBuffLen(4*m_listEquationKey.GetCount());
	while (pos != NULL)
	{
		pKey = (CWEqtnKey*)m_listEquationKey.GetNext(pos);
		pStrBuff->IncreaseBuffLen(wcslen(pKey->GetKeyName2()));
		pStrBuff->IncreaseBuffLen(wcslen(pKey->GetKeyValue2()));
	}
	pStrBuff->AllocMemBuff(10);
	pStrBuff->ResetBuffCurr();
	
	pStrBuff->SetModeWrite();
	pos = m_listEquationKey.GetHeadPosition();
	while (pos != NULL)
	{
		pKey = (CWEqtnKey*)m_listEquationKey.GetNext(pos);
		pStrBuff->WriteString(_bstr_t(pKey->GetKeyName2()));
		pStrBuff->WriteString(_bstr_t("="));
		pStrBuff->WriteString(_bstr_t(pKey->GetKeyValue2()));
		pStrBuff->WriteString(_bstr_t(";\r\n"));
	}
}
*/

//2006.05.22  获取等式的关键字的名称和数据
long CWEquationBuffer::GetKeyCount()
{
	return m_listEquationKey.GetCount();
}

BOOL CWEquationBuffer::GetKey(long nIndex,BSTR *pbstrName,BSTR *pbstrValue)
{
	POS pos = m_listEquationKey.FindIndex(nIndex);
	if (pos == NULL)
	{
		return FALSE;
	}

	CWEqtnKey *pKey = NULL;
	pKey = (CWEqtnKey*)m_listEquationKey.GetAt(pos);

	*pbstrName = pKey->m_strKeyName;
	*pbstrValue = pKey->m_strKeyValue;

	return TRUE;
}

BOOL CWEquationBuffer::GetKey(long nIndex,CComBSTR &strName,CComBSTR &strValue)
{
	POS pos = m_listEquationKey.FindIndex(nIndex);
	if (pos == NULL)
	{
		return FALSE;
	}
	
	CWEqtnKey *pKey = NULL;
	pKey = (CWEqtnKey*)m_listEquationKey.GetAt(pos);
	strName = pKey->m_strKeyName;
	strValue = pKey->m_strKeyValue;
	
	return TRUE;	
}

BOOL CWEquationBuffer::ReadFromFile(const CComBSTR &strFile)
{
	long nLen = strFile.Length();
	char pszFile[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, strFile, wcslen(strFile), pszFile, nLen, NULL, NULL); 	
	m_listEquationKey.DeleteAll();
	BOOL bTrue = CWBufferBase::ReadFromFile(pszFile);

	if (bTrue)
	{
		InitEquationKeyList();	
	}

	return bTrue;
}

BOOL CWEquationBuffer::WriteToFile(const CComBSTR &strFile)
{
	long nLen = strFile.Length();
#ifdef _UNICODE
	wchar_t pszFile[MAX_PATH];
	wcscpy(pszFile, strFile);
#else
	char pszFile[MAX_PATH];
	WideCharToMultiByte(CP_ACP, 0, strFile, wcslen(strFile), pszFile, nLen, NULL, NULL); 
#endif
	
	CAtlFile file;
	
	if (! file.Open(pszFile,CAtlFile::modeCreate | CAtlFile::modeWrite) )
	{
		return FALSE;
	}

	CWEqtnKey *pKey = NULL;
	POS pos = m_listEquationKey.GetHeadPosition();
	wchar_t* pszTemp  =NULL;

	while (pos != NULL)
	{
		pKey = (CWEqtnKey*)m_listEquationKey.GetNext(pos);
		file.Write(pKey->m_strKeyName,pKey->m_strKeyName.Length()*2);
		file.Write(&g_wchKeyEquation,sizeof(wchar_t));
		file.Write(pKey->m_strKeyValue,pKey->m_strKeyValue.Length()*2);
		file.Write(&g_wchKeySeperator,sizeof(wchar_t));
		file.Write(g_strKeyNewLine, 2*sizeof(wchar_t));
	}

	file.Close();
	
	return TRUE;
}

//初始化缓冲区
void CWEquationBuffer::InitBuffer(const CComBSTR &strBuff)
{
	m_listEquationKey.DeleteAll();
	CWBufferBase::InitBuffer(strBuff);
	InitEquationKeyList();
}

void CWEquationBuffer::InitBuffer(BSTR strBuff)
{
	m_listEquationKey.DeleteAll();
	CWBufferBase::InitBuffer(strBuff);
	InitEquationKeyList();
}

void CWEquationBuffer::InitBuffer(const CWBufferBase *pBuffer)
{
	m_listEquationKey.DeleteAll();
	CWBufferBase::InitBuffer(pBuffer);
	InitEquationKeyList();
}

void CWEquationBuffer::InitBuffer(wchar_t* pBuffBegin,wchar_t* pBuffEnd)
{
	m_listEquationKey.DeleteAll();
	CWBufferBase::InitBuffer(pBuffBegin,pBuffEnd);
	InitEquationKeyList();
}

void CWEquationBuffer::FormatBufferEx()
{
	FormatAroundSeparate(GetSeparateChar());
	FormatAroundSeparate(GetSeparateEndChar());
}

/*************************************************
//函数名称：	IsIgnoreChar
//描述：    	判断一个字符是不是可以被忽略的字符，主要针对等式而言
//输入参数：  	
	ch：		需要判断的字符
//输出参数：     
	无
返回值：     	是可以被忽略的字符返回TRUE，否则返回FALSE。
*************************************************/
BOOL CWEquationBuffer::IsIgnoreChar(wchar_t ch)
{
	return ( (ch == VK_TAB) || (ch == VK_SPACE) || (ch == '\r') || (ch == '\n') );
}

/*************************************************
//函数名称：	PartString
//描述：    	将一数据行进行分解，解析出关键字、数据
//输入参数：  	
	pszSrcBegin：	数据行的起始位置
	pszSrcEnd：		数据行的结束位置
	cPart：			分隔符号
	cEnd：			数据行的有效结束符号
//输出参数：     
	pszLeftBegin：	用于保存关键字的起始位置
	pszLeftEnd：	用于保存关键字的结束位置
	pszRightBegin：	用于保存数据的起始位置
	pszRightEnd：	用于保存数据的结束位置
返回值：     	如果数据行中包含有效的等式返回TRUE，否则返回FALSE。
*************************************************/
BOOL CWEquationBuffer::PartString(wchar_t* pszSrcBegin,wchar_t* pszSrcEnd
				,wchar_t **pszLeftBegin,wchar_t **pszLeftEnd
				,wchar_t **pszRightBegin,wchar_t **pszRightEnd
				,wchar_t cPart,wchar_t cEnd)
{
	BOOL bTrue = TRUE;

	if(pszSrcBegin == NULL || pszSrcEnd == NULL)
		return FALSE;
	
	wchar_t *pTemp = NULL;
	wchar_t* pCurr = NULL;
	pCurr = pszSrcBegin;
	
	//分隔符号左边
	while(TRUE)
	{
		//遇到结束符号或者到达字符串结尾
		if(*pCurr == 0 || *pCurr == cEnd)
		{
			bTrue = FALSE;
			break;
		}

		if(*pCurr == cPart)//分隔符号
			break;
		
		pCurr++;
	}

	//没有分隔符号或者超出缓冲区的范围，则返回
	if(!bTrue || !IsPoiterInBuffer(pCurr))
		return bTrue;

	//记录分隔符号前的位置
	*pszLeftBegin = (wchar_t*)pszSrcBegin;
	*pszLeftEnd = (wchar_t*)(pCurr - 1);
	
	//跳过分隔符号 cPart
	pCurr++;
	
	//分隔符号右边
	*pszRightBegin = (wchar_t*)pCurr;
	while(TRUE)
	{
		if(*pCurr == 0)
		{
			bTrue = FALSE;
			break;
		}
	
		if (*pCurr == cEnd)
		{
			break;
		}

		pCurr++;
	}

	if (0 == cEnd)
	{
		bTrue = TRUE;
	}

	//如果不包含结束字符，则不处理
	if (*pCurr != cEnd)
	{
		bTrue = FALSE;
	}
	else
	{
		*pszRightEnd = (wchar_t*)(pCurr - 1);
	}
	
	return bTrue;
}

/*************************************************
//函数名称：	FindSeparateKey
//描述：    	查找分隔字符所在的位置
//输入参数：  	
	pBeginPos：	查找的起始位置
	chSeparate：	分隔字符
//输出参数：     
	无
返回值：     	找到返回分隔字符所在的位置，否则返回NULL。
*************************************************/
wchar_t* CWEquationBuffer::FindSeparateKey(wchar_t *pBeginPos,wchar_t chSeparate)
{
	if (pBeginPos == NULL)
	{
		return NULL;
	}

	if (!IsPoiterInBuffer(pBeginPos))
	{
		return NULL;
	}

	wchar_t *pTemp = pBeginPos;
	wchar_t *pFind = NULL;
	wchar_t *pEnd = GetBufferEndPos();

	while (pTemp < pEnd)
	{
		if (*pTemp == chSeparate)
		{
			pFind = pTemp;
			break;
		}
		pTemp++;
	}

	return pFind;
}

/*************************************************
//函数名称：	OffsetBack
//描述：    	从当前位置开始，向后移动到第一个不可忽略的字符的位置
//输入参数：  	
	pPos：		起始位置，并返回
//输出参数：     
	无
返回值：     	无。
*************************************************/
void CWEquationBuffer::OffsetBack(wchar_t **pPos)
{
	wchar_t *pTemp = *pPos;

	while (IsIgnoreChar(*pTemp) && pTemp > m_pPointer)
	{
		pTemp--;
	}

	*pPos = pTemp;
}

/*************************************************
//函数名称：	Copy
//描述：    	将一段缓冲区拷贝到目标地址
//输入参数：  	
	pDestPos：	目标地址，拷贝完成后移动到最新的位置
	pSrcBegin：	源数据的起始地址
	pSrcEnd：	源数据的终止地址
//输出参数：     
	无
返回值：     	无。
*************************************************/
void CWEquationBuffer::Copy(wchar_t **pDestPos,wchar_t *pSrcBegin,wchar_t *pSrcEnd)
{
	//源地址和目标地址相同，则返回
	if (*pDestPos == pSrcBegin)
	{
		*pDestPos = pSrcEnd+1;
		return;
	}
	
	wchar_t *pDest = *pDestPos;

	while (pSrcBegin <= pSrcEnd)
	{
		*pDest = *pSrcBegin;
		pSrcBegin++;
		pDest++;
	}

	*pDestPos = pDest;
}

/*************************************************
//函数名称：	InitEquationKeyList
//描述：    	初始化等式关键字列表，创建各等式
//输入参数：  	
	无
//输出参数：     
	无
返回值：     	无
*************************************************/
void CWEquationBuffer::InitEquationKeyList()
{
	if (m_nLength <= 3)
	{
		return;
	}
	
	wchar_t *pLineBegin = NULL;
	wchar_t *pLineEnd = NULL;
	wchar_t *pLeftBegin = NULL;
	wchar_t *pLeftEnd = NULL;
	wchar_t *pRightBegin = NULL;
	wchar_t *pRightEnd = NULL;
	BOOL bLine = TRUE;
	BOOL bTrue = TRUE;
	CWEqtnKey *pKey = NULL;
	
	wchar_t chSeparate = GetSeparateChar();
	wchar_t chSeparateEnd = GetSeparateEndChar();
	FormatBufferEx();
	ResetPointer();
	bTrue = GetOneLine(&pLineBegin,&pLineEnd);
	
	while (bTrue)
	{
		pLeftBegin = NULL;
		pLeftEnd = NULL;
		pRightBegin = NULL;
		pRightEnd = NULL;

		bLine = PartString(pLineBegin,pLineEnd,&pLeftBegin,&pLeftEnd
			,&pRightBegin,&pRightEnd,chSeparate,chSeparateEnd);

		if (bLine)
		{
			if (pLeftBegin == NULL || pLeftEnd == NULL || pRightBegin == NULL || pRightEnd == NULL)
			{
			}
			else
			{
				if (pLeftEnd >= pLeftBegin)
				{
					pKey = new CWEqtnKey(pLeftBegin,pLeftEnd,pRightBegin,pRightEnd);

					if (pKey->IsLegal())
					{
						m_listEquationKey.AddTail(pKey);
					}
					else
					{
						delete pKey;
					}
				}
			}
		}

		bTrue = GetOneLine(&pLineBegin,&pLineEnd);
	}
}

/*************************************************
//函数名称：	GetOneLine
//描述：    	获取一有效的等式数据行，等式数据行的结束以“;”或换行符号“\r”、“\n”为标记
//输入参数：  	
	无
//输出参数：     
	pszLineBegin：	返回有效数据行的起始位置
	pszLineEnd：	返回有效数据行的结束位置
返回值：     	如果在缓冲区边界之内，返回TRUE，否则返回FALSE。
*************************************************/
BOOL CWEquationBuffer::GetOneLine(wchar_t **pszLineBegin,wchar_t **pszLineEnd)
{
	BOOL bTrue = FALSE;

	//跳过起始位置的可忽略的字符，记录行的起始位置
	while ((IsIgnoreChar(*m_pPointer) || 0 == *m_pPointer) && (IsPoiterInBuffer()) )
	{
		m_pPointer++;
	}
	
	if (!IsPoiterInBuffer())
	{
		return FALSE;
	}
	
	*pszLineBegin = m_pPointer;
	wchar_t chSeparate = GetSeparateChar();
	wchar_t chSeparateEnd = GetSeparateEndChar();
	
	//遇到“;”字符或者换行符号，表示结束
	while (TRUE)
	{
		if (chSeparateEnd == *m_pPointer || 0 == *m_pPointer
			|| '\r' == *m_pPointer || '\n' == *m_pPointer )
			break;
		
		m_pPointer++;
	}

	*pszLineEnd = m_pPointer;
	bTrue = IsPoiterInBuffer();

	if (chSeparateEnd == *m_pPointer)
	{
		m_pPointer++;
	}
	
	if (m_pPointer > m_pBuffer + m_nLength )
	{
		bTrue = FALSE;
	}
	
	return bTrue;
}

/*************************************************
//函数名称：	FindEquationKey
//描述：    	根据关键字的名称查找等式关键字对象
//输入参数：  	
	strKeyName：关键字名称
	pszKeyName：关键字名称
//输出参数：     
	无
返回值：     	找到则返回关键字对象，否则返回NULL
*************************************************/
CWEqtnKey* CWEquationBuffer::FindEquationKey(const CComBSTR &strKeyName)
{
	CWEqtnKey *pKeyFind = NULL;
	CWEqtnKey *pKey = NULL;
	POS pos = m_listEquationKey.GetHeadPosition();

	while (pos != NULL)
	{
		pKey = (CWEqtnKey*)m_listEquationKey.GetNext(pos);
		if (pKey->CompareName(strKeyName))
		{
			pKeyFind = pKey;
			break;
		}
	}

	return pKeyFind;
}

CWEqtnKey* CWEquationBuffer::FindEquationKey(wchar_t* pszKeyName)
{
	CWEqtnKey *pKeyFind = NULL;
	CWEqtnKey *pKey = NULL;
	POS pos = m_listEquationKey.GetHeadPosition();

	while (pos != NULL)
	{
		pKey = (CWEqtnKey*)m_listEquationKey.GetNext(pos);
		if (pKey->CompareName(pszKeyName))
		{
			pKeyFind = pKey;
			break;
		}
	}

	return pKeyFind;
}

CWEqtnKey* CWEquationBuffer::FindEquationKey(long nIndex)
{
	CWEqtnKey *pKeyFind = NULL;
	POS pos = m_listEquationKey.FindIndex(nIndex);
	
	if (pos != NULL)
	{
		pKeyFind = (CWEqtnKey*)m_listEquationKey.GetNext(pos);
	}
	
	return pKeyFind;
}

CWEqtnKey* CWEquationBuffer::FindEquationKey(const VARIANT &vIndex)
{
	long nIndex = 0;
	CComBSTR bstrIndex;
	CWEqtnKey *pKey = NULL;
	
	if (VARIANT_to_long(vIndex, nIndex))
	{
		pKey = FindEquationKey(nIndex);
	}
	else if (VARIANT_to_CComBSTR(vIndex, bstrIndex))
	{
		pKey = FindEquationKey(bstrIndex);
	}
	else
	{
	}

	return pKey;
}

