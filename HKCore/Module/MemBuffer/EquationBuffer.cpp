  // EquationBuffer.cpp: implementation of the CEquationBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EquationBuffer.h"
#include "EquationKey.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEquationBuffer::CEquationBuffer()
{
	InitSeparateChar();
	SetSeparateChar('=');
	SetSeparateEndChar(';');
	DeleteAll();
}

void CEquationBuffer::InitSeparateChar()
{
	SetSeparateChar('=');
	SetSeparateEndChar(';');
	ZeroMemory(m_pszSeparateChar, EQUATION_SP_END_KEY_MAX_LEN);
	ZeroMemory(m_pszSeparateEndChar, EQUATION_SP_END_KEY_MAX_LEN);
}

CEquationBuffer::CEquationBuffer(const CString &strBuff) : CBufferBase(strBuff)
{
	InitSeparateChar();
	DeleteAll();
	InitEquationKeyList();
}

CEquationBuffer::CEquationBuffer(const char *pszBuff) : CBufferBase(pszBuff)
{
	InitSeparateChar();
// 	SetSeparateChar();
// 	SetSeparateEndChar();
	DeleteAll();
	InitEquationKeyList();
}

CEquationBuffer::CEquationBuffer(const CBufferBase *pBuffer) : CBufferBase(pBuffer)
{
	InitSeparateChar();
// 	SetSeparateChar();
// 	SetSeparateEndChar();
	DeleteAll();
	InitEquationKeyList();
}

CEquationBuffer::CEquationBuffer(const char *pBuffBegin,const char *pBuffEnd) : CBufferBase(pBuffBegin,pBuffEnd)
{
	InitSeparateChar();
// 	SetSeparateChar();
// 	SetSeparateEndChar();
	DeleteAll();
	InitEquationKeyList();
}

CEquationBuffer::~CEquationBuffer()
{
	DeleteAll();
}

void CEquationBuffer::SetSeparateChar(const CString &str)
{
	CString_to_char(str, m_pszSeparateChar);
}

void CEquationBuffer::SetSeparateEndChar(const CString &str)
{
	CString_to_char(str, m_pszSeparateEndChar);
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
CString CEquationBuffer::operator[](const CString &strKeyName)
{
	CEquationKey *pKeyFind = FindEquationKey(strKeyName);
	if (pKeyFind == NULL)
	{
		throw(-1);
	}
	
	CString strValue("");
	pKeyFind->GetKeyValue(strValue);
	return strValue;
}

CString CEquationBuffer::operator[](const char *pszKeyName)
{
	CEquationKey *pKeyFind = FindEquationKey(pszKeyName);
	if (pKeyFind == NULL)
	{
		throw(-1);
	}
	
	CString strValue("");
	pKeyFind->GetKeyValue(strValue);
	return strValue;
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
long CEquationBuffer::ParseInt(const char *pszKey, int *pVal)
{
	CEquationKey *pKeyFind = FindEquationKey(pszKey);
	
	long lResult = 0;
	if (pKeyFind != NULL)
	{
		lResult = 1;
		pKeyFind->GetKeyValue(pVal);
	}

	return lResult;
}

long CEquationBuffer::ParseInt(const CString &strKey, int *pVal)
{
	CEquationKey *pKeyFind = FindEquationKey(strKey);
	
	long lResult = 0;
	if (pKeyFind != NULL)
	{
		lResult = 1;
		pKeyFind->GetKeyValue(pVal);
	}
	
	return lResult;
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
long CEquationBuffer::ParseLong(const char *pszKey, long *pVal)
{
	CEquationKey *pKeyFind = FindEquationKey(pszKey);
	
	long lResult = 0;
	if (pKeyFind != NULL)
	{
		lResult = 1;
		pKeyFind->GetKeyValue(pVal);
	}
	
	return lResult;
}

long CEquationBuffer::ParseLong(const CString &strKey, long *pVal)
{
	CEquationKey *pKeyFind = FindEquationKey(strKey);
	
	long lResult = 0;
	if (pKeyFind != NULL)
	{
		lResult = 1;
		pKeyFind->GetKeyValue(pVal);
	}
	
	return lResult;
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
long CEquationBuffer::ParseFloat(const char *pszKey, float *pVal)
{
	CEquationKey *pKeyFind = FindEquationKey(pszKey);
	
	long lResult = 0;
	if (pKeyFind != NULL)
	{
		lResult = 1;
		pKeyFind->GetKeyValue(pVal);
	}
	
	return lResult;
}

long CEquationBuffer::ParseFloat(const CString &strKey, float *pVal)
{
	CEquationKey *pKeyFind = FindEquationKey(strKey);
	
	long lResult = 0;
	if (pKeyFind != NULL)
	{
		lResult = 1;
		pKeyFind->GetKeyValue(pVal);
	}
	
	return lResult;
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
long CEquationBuffer::ParseString(const char *pszKey, char *pszVal, int nMaxLen)
{
	CString strVal("");
	
	long lResult = ParseString(pszKey,strVal);

#ifdef _UNICODE
	CString_to_char(strVal, pszVal, nMaxLen);
#else
    strcpy(pszVal,strVal.GetString());
#endif
	
	return lResult;
}

long CEquationBuffer::ParseString(const char *pszKey, CString &strVal)
{
	CEquationKey *pKeyFind = FindEquationKey(pszKey);
	
	long lResult = 0;

	if (pKeyFind != NULL)
	{
		lResult = 1;
		pKeyFind->GetKeyValue(strVal);
	}
	
	return lResult;
}

long CEquationBuffer::ParseString(const CString &strKey, char *pszVal, int nMaxLen)
{
	CString strVal("");

	long lResult = ParseString(strKey,strVal);

#ifdef _UNICODE
	CString_to_char(strVal, pszVal,nMaxLen);
#else
    strcpy(pszVal,strVal.GetString());
#endif

	return lResult;
}

long CEquationBuffer::ParseString(const CString &strKey, CString &strVal)
{
	CEquationKey *pKeyFind = FindEquationKey(strKey);
	
	long lResult = 0;
	if (pKeyFind != NULL)
	{
		lResult = 1;
		pKeyFind->GetKeyValue(strVal);
	}
	
	return lResult;
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
void CEquationBuffer::FormatAroundSeparate(char chSeparate)
{
	char *pTemp = m_pBuffer;
	char *pEqualPos = m_pBuffer;
	char *pBuffEndPos = GetBufferEndPos();
	char *pSrcBegin = m_pBuffer;
	char *pSrcEnd = NULL;
	char *pDest = m_pBuffer;

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
void CEquationBuffer::FormatAroundSeparate(char *pszSeparate)
{
	char *pTemp = m_pBuffer;
	char *pEqualPos = m_pBuffer;
	char *pBuffEndPos = GetBufferEndPos();
	char *pSrcBegin = m_pBuffer;
	char *pSrcEnd = NULL;
	char *pDest = m_pBuffer;
	long nLen = strlen(pszSeparate);

	while (IsIgnoreChar(*pSrcBegin))
	{
		pSrcBegin++;
	}

	pEqualPos = FindSeparateKey(m_pBuffer, pszSeparate);

	while (IsPoiterInBuffer(pEqualPos))
	{
		//分隔符号前的有效数据的复制
		pSrcEnd = pEqualPos-1;
		OffsetBack(&pSrcEnd);
		Copy(&pDest,pSrcBegin,pSrcEnd);
		
		//复制分隔符号
		//*pDest = *pEqualPos;
		//pDest++;
		//pEqualPos++;
		memcpy(pDest, pEqualPos, nLen);
		pDest += nLen;
		pEqualPos += nLen;

		//分隔符号前的有效数据的复制
		while (IsIgnoreChar(*pEqualPos))
			pEqualPos++;

		pSrcBegin = pEqualPos;
		pEqualPos = FindSeparateKey(pEqualPos,pszSeparate);
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
long CEquationBuffer::SetKeyValue(const char *pszKey, char *pszVal,long bAddNew)
{
	CEquationKey *pKeyFind = FindEquationKey(pszKey);
	
	long lResult = 0;
	if (pKeyFind == NULL)
	{
		if (bAddNew == 1)
		{
			if (strlen(pszKey) > 0)
			{
				pKeyFind = new CEquationKey(pszKey,pszVal);
				AddTail(pKeyFind);
			}
		}
	}
	else
	{
		lResult = 1;
		pKeyFind->SetKeyValue(pszVal);
	}
	
	return lResult;
}
long CEquationBuffer::SetKeyValue(const CString &strKey, const CString &strVal,long bAddNew)
{
	CEquationKey *pKeyFind = FindEquationKey(strKey);
	
	long lResult = 0;
	if (pKeyFind == NULL)
	{
		if (bAddNew == 1)
		{
			if (strKey.GetLength() > 0)
			{
				pKeyFind = new CEquationKey(strKey,strVal);
				AddTail(pKeyFind);
			}
		}
	}
	else
	{
		lResult = 1;
		pKeyFind->SetKeyValue(strVal);
	}
	
	return lResult;
}

long CEquationBuffer::SetKeyValueEx(const CString &strScript,long bAddNew)
{
	CEquationBuffer buff;
	buff.InitBuffer(strScript);
	
	CEquationKey *pKey = NULL;
	POS pos = buff.GetHeadPosition();

	while (pos != NULL)
	{
		pKey = (CEquationKey*)buff.GetNext(pos);
		SetKeyValue(pKey->m_pszKeyName,pKey->m_pszKeyValue,bAddNew);
	}
	
    return 0;
}

void CEquationBuffer::GetEquationData(BSTR *pbstrEquationData)
{
	CString strEquation;
	POS pos = GetHeadPosition();
	CEquationKey *pKey = NULL;

	while (pos != NULL)
	{
		pKey = (CEquationKey*)GetNext(pos);
        strEquation.AppendFormat(_T("%s=%s;\r\n"),pKey->m_pszKeyName.GetString(), pKey->m_pszKeyValue.GetString());
	}

	*pbstrEquationData = strEquation.AllocSysString();

}

void CEquationBuffer::GetEquationData(CString &strEquationData)
{
	POS pos = GetHeadPosition();
	CEquationKey *pKey = NULL;
	strEquationData.Empty();

	while (pos != NULL)
	{
		pKey = (CEquationKey*)GetNext(pos);
        strEquationData.AppendFormat(_T("%s=%s;\r\n"),pKey->m_pszKeyName.GetString(), pKey->m_pszKeyValue.GetString());
	}

}
// 
// void CEquationBuffer::GetEquationData(IStringSerializeBuffInterface *pStrBuff)
// {
// 	POS pos = GetHeadPosition();
// 	CEquationKey *pKey = NULL;
// 	if (pStrBuff == NULL)
// 	{
// 		return ;
// 	}
// 
// 	pStrBuff->SetModeCalSize();
// 	pStrBuff->IncreaseBuffLen(4*GetCount());
// 	while (pos != NULL)
// 	{
// 		pKey = (CEquationKey*)GetNext(pos);
// 		pStrBuff->IncreaseBuffLen(strlen(pKey->GetKeyName2()));
// 		pStrBuff->IncreaseBuffLen(strlen(pKey->GetKeyValue2()));
// 	}
// 	pStrBuff->AllocMemBuff(10);
// 	pStrBuff->ResetBuffCurr();
// 	
// 	pStrBuff->SetModeWrite();
// 	pos = GetHeadPosition();
// 	while (pos != NULL)
// 	{
// 		pKey = (CEquationKey*)GetNext(pos);
// 		pStrBuff->WriteString(_bstr_t(pKey->GetKeyName2()));
// 		pStrBuff->WriteString(_bstr_t("="));
// 		pStrBuff->WriteString(_bstr_t(pKey->GetKeyValue2()));
// 		pStrBuff->WriteString(_bstr_t(";\r\n"));
// 	}
// }

//2006.05.22  获取等式的关键字的名称和数据
long CEquationBuffer::GetKeyCount()
{
	return GetCount();
}

BOOL CEquationBuffer::GetKey(long nIndex,BSTR *pbstrName,BSTR *pbstrValue)
{
	POS pos = FindIndex(nIndex);
	if (pos == NULL)
	{
		return FALSE;
	}

	CEquationKey *pKey = NULL;
	pKey = (CEquationKey*)GetAt(pos);

	CString strName = pKey->m_pszKeyName;
	CString strValue = pKey->m_pszKeyValue;
	*pbstrName = strName.AllocSysString();
	*pbstrValue = strValue.AllocSysString();

	return TRUE;
}

BOOL CEquationBuffer::GetKey(long nIndex,CString &strName,CString &strValue)
{
	POS pos = FindIndex(nIndex);
	if (pos == NULL)
	{
		return FALSE;
	}
	
	CEquationKey *pKey = NULL;
	pKey = (CEquationKey*)GetAt(pos);
	strName = pKey->m_pszKeyName;
	strValue = pKey->m_pszKeyValue;
	
	return TRUE;	
}

BOOL CEquationBuffer::ReadFromFile(const char *pszFile)
{
	DeleteAll();
	BOOL bTrue = CBufferBase::ReadFromFile(pszFile);
	if (bTrue)
	{
		InitEquationKeyList();	
	}

	return bTrue;
}

BOOL CEquationBuffer::ReadFromFile(const CString &strFile)
{
	DeleteAll();
	BOOL bTrue = CBufferBase::ReadFromFile(strFile);
	if (bTrue)
	{
		InitEquationKeyList();	
	}
	
	return bTrue;
}

BOOL CEquationBuffer::WriteToFile(const CString &strFile)
{
// 	CFile file;
// 	if (! file.Open(strFile,CFile::modeCreate | CFile::modeWrite) )
// 	{
// 		return FALSE;
// 	}
// 
// 	CEquationKey *pKey = NULL;
// 	POS pos = GetHeadPosition();
// 	const char *pszTemp  =NULL;
// 	while (pos != NULL)
// 	{
// 		pKey = (CEquationKey*)GetNext(pos);
// 		pszTemp = pKey->GetKeyName2();
// 		file.Write(pszTemp,strlen(pszTemp));
// 		file.Write("=",1);
// 		pszTemp = pKey->GetKeyValue2();
// 		file.Write(pszTemp,strlen(pszTemp));
// 		file.Write(";\r\n",3);
// 	}
// 
// 	file.Close();

	return TRUE;
}

//初始化缓冲区
void CEquationBuffer::InitBuffer(const CString &strBuff)
{
	DeleteAll();
	CBufferBase::InitBuffer(strBuff);
	InitEquationKeyList();
}

void CEquationBuffer::InitBuffer(const CBufferBase *pBuffer)
{
	DeleteAll();
	CBufferBase::InitBuffer(pBuffer);
	InitEquationKeyList();
}

void CEquationBuffer::InitBuffer(const char *pBuffBegin,const char *pBuffEnd)
{
	DeleteAll();
	CBufferBase::InitBuffer(pBuffBegin,pBuffEnd);
	InitEquationKeyList();
}

void CEquationBuffer::FormatBufferEx()
{
	if (m_pszSeparateChar[0] == 0)
	{
		FormatAroundSeparate(GetSeparateChar());
		FormatAroundSeparate(GetSeparateEndChar());
	}
	else
	{
		FormatAroundSeparate(GetSeparateCharEx());
		FormatAroundSeparate(GetSeparateEndCharEx());
	}
}

//分隔符号
/*
char CEquationBuffer::GetSeparateChar()
{
	return '=';
}

char CEquationBuffer::GetSeparateEndChar()
{
	return ';';
}
*/


/*************************************************
//函数名称：	IsIgnoreChar
//描述：    	判断一个字符是不是可以被忽略的字符，主要针对等式而言
//输入参数：  	
	ch：		需要判断的字符
//输出参数：     
	无
返回值：     	是可以被忽略的字符返回TRUE，否则返回FALSE。
*************************************************/
BOOL CEquationBuffer::IsIgnoreChar(char ch)
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
BOOL CEquationBuffer::PartString(const char *pszSrcBegin,const char *pszSrcEnd
				,char **pszLeftBegin,char **pszLeftEnd
				,char **pszRightBegin,char **pszRightEnd
				,char cPart,char cEnd)
{
	BOOL bTrue = TRUE;
	ASSERT(pszSrcBegin != NULL && pszSrcEnd != NULL);
	if(pszSrcBegin == NULL || pszSrcEnd == NULL)
		return FALSE;
	
	char *pTemp = NULL;
	const char *pCurr = NULL;
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
	*pszLeftBegin = (char*)pszSrcBegin;
	*pszLeftEnd = (char*)(pCurr - 1);
	
	//跳过分隔符号 cPart
	pCurr++;
	
	//分隔符号右边
	*pszRightBegin = (char*)pCurr;
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
		//2021-1-3  lijunqing 考虑末尾没有分隔符号的特殊情况
		if ((*pszRightBegin != NULL) && (*pCurr == 0))
		{
			bTrue = TRUE;
		}
		else
		{
			bTrue = FALSE;
		}
	}
	else
	{
		*pszRightEnd = (char*)(pCurr - 1);
	}
	
	return bTrue;
}

BOOL CEquationBuffer::PartString(const char *pszSrcBegin,const char *pszSrcEnd
				,char **pszLeftBegin,char **pszLeftEnd
				,char **pszRightBegin,char **pszRightEnd
				,char *pszPart,char *pszEnd)
{
	BOOL bTrue = TRUE;
	ASSERT(pszSrcBegin != NULL && pszSrcEnd != NULL);
	if(pszSrcBegin == NULL || pszSrcEnd == NULL)
		return FALSE;
	
	char *pTemp = NULL;
	const char *pCurr = NULL;
	pCurr = pszSrcBegin;
	long nLenPart = strlen(pszPart);
	long nLenEnd = strlen(pszEnd);
	
	//分隔符号左边
	while(TRUE)
	{
		//遇到结束符号或者到达字符串结尾
		if(*pCurr == 0 || (strncmp(pCurr, pszEnd, nLenEnd) == 0) )
		{
			bTrue = FALSE;
			break;
		}

		if(strncmp(pCurr, pszPart, nLenPart) == 0)//分隔符号
			break;

		pCurr++;
	}

	//没有分隔符号或者超出缓冲区的范围，则返回
	if(!bTrue || !IsPoiterInBuffer(pCurr))
		return bTrue;

	//记录分隔符号前的位置
	*pszLeftBegin = (char*)pszSrcBegin;
	*pszLeftEnd = (char*)(pCurr - 1);
	
	//跳过分隔符号 cPart
	pCurr += nLenPart;
	
	//分隔符号右边
	*pszRightBegin = (char*)pCurr;
	while(TRUE)
	{
		if(*pCurr == 0)
		{
//			bTrue = FALSE;
			break;
		}

		if (strncmp(pCurr, pszEnd, nLenEnd) == 0)
		{
			break;
		}

		if (*pCurr > 0)
		{//执行汉字处理
			pCurr++;
		}
		else
		{
			pCurr += 2;
		}
	}

	//如果不包含结束字符，则不处理
	if (strncmp(pCurr, pszEnd, nLenEnd) != 0 && *pCurr != 0)
	{
		bTrue = FALSE;
	}
	else
	{
		*pszRightEnd = (char*)(pCurr - 1);
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
char* CEquationBuffer::FindSeparateKey(char *pBeginPos,char chSeparate)
{
	if (pBeginPos == NULL)
	{
		return NULL;
	}

	if (!IsPoiterInBuffer(pBeginPos))
	{
		return NULL;
	}

	char *pTemp = pBeginPos;
	char *pFind = NULL;
	char *pEnd = GetBufferEndPos();

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
char* CEquationBuffer::FindSeparateKey(char *pBeginPos,char *pszSeparate)
{
	if (pBeginPos == NULL)
	{
		return NULL;
	}

	if (!IsPoiterInBuffer(pBeginPos))
	{
		return NULL;
	}

	char *pTemp = pBeginPos;
	char *pFind = NULL;
	char *pEnd = GetBufferEndPos();
	long nLen = strlen(pszSeparate);

	while (pTemp < pEnd)
	{
		if (strncmp(pTemp, pszSeparate, nLen) == 0)
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
void CEquationBuffer::OffsetBack(char **pPos)
{
	char *pTemp = *pPos;

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
	pDesPOS：	目标地址，拷贝完成后移动到最新的位置
	pSrcBegin：	源数据的起始地址
	pSrcEnd：	源数据的终止地址
//输出参数：     
	无
返回值：     	无。
*************************************************/
void CEquationBuffer::Copy(char **pDesPOS,char *pSrcBegin,char *pSrcEnd)
{
	//源地址和目标地址相同，则返回
	if (*pDesPOS == pSrcBegin)
	{
		*pDesPOS = pSrcEnd+1;
		return;
	}
	
	char *pDest = *pDesPOS;
	while (pSrcBegin <= pSrcEnd)
	{
		*pDest = *pSrcBegin;
		pSrcBegin++;
		pDest++;
	}
	*pDesPOS = pDest;
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
void CEquationBuffer::InitEquationKeyList()
{
	if (m_nLength <= 3)
	{
		return;
	}
	
	char *pLineBegin = NULL;
	char *pLineEnd = NULL;
	char *pLeftBegin = NULL;
	char *pLeftEnd = NULL;
	char *pRightBegin = NULL;
	char *pRightEnd = NULL;
	BOOL bLine = TRUE;
	BOOL bTrue = TRUE;
	CEquationKey *pKey = NULL;
	
	char chSeparate = GetSeparateChar();
	char chSeparateEnd = GetSeparateEndChar();
	char *pszSeparate = GetSeparateCharEx();
	char *pszSeparateEnd = GetSeparateEndCharEx();
	BOOL bUsePszSeparate = FALSE;

	if (m_pszSeparateChar[0] != 0)
	{
		bUsePszSeparate = TRUE;
	}

	FormatBufferEx();
	ResetPointer();
	bTrue = GetOneLine(&pLineBegin,&pLineEnd);
	while (bTrue)
	{
		pLeftBegin = NULL;
		pLeftEnd = NULL;
		pRightBegin = NULL;
		pRightEnd = NULL;

		if (bUsePszSeparate)
		{
			bLine = PartString(pLineBegin,pLineEnd,&pLeftBegin,&pLeftEnd
				,&pRightBegin,&pRightEnd,pszSeparate,pszSeparateEnd);
		}
		else
		{
			bLine = PartString(pLineBegin,pLineEnd,&pLeftBegin,&pLeftEnd
				,&pRightBegin,&pRightEnd,chSeparate,chSeparateEnd);
		}

		if (bLine)
		{
			//2021-1-3  lijunqing 考虑末尾没有分隔符号的特殊情况
			if (pLeftBegin == NULL || pLeftEnd == NULL || pRightBegin == NULL)// || pRightEnd == NULL)
			{
			}
			else
			{
				if (pLeftEnd >= pLeftBegin)
				{
					pKey = new CEquationKey(pLeftBegin,pLeftEnd,pRightBegin,pRightEnd);
					if (pKey->IsLegal())
					{
						AddTail(pKey);
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
BOOL CEquationBuffer::GetOneLine(char **pszLineBegin,char **pszLineEnd)
{
	BOOL bTrue = TRUE;

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
	char chSeparate = GetSeparateChar();
	char chSeparateEnd = GetSeparateEndChar();
	char *pszSeparateEnd = GetSeparateEndCharEx();
	long nLen = 1;
	
	//遇到“;”字符或者换行符号，表示结束
	if (pszSeparateEnd[0] == 0)
	{
		nLen = 1;

		while (TRUE)
		{
			if (chSeparateEnd == *m_pPointer || 0 == *m_pPointer
				|| '\r' == *m_pPointer || '\n' == *m_pPointer )
				break;
			m_pPointer++;
		}
	}
	else
	{
		nLen = strlen(pszSeparateEnd);

		while (TRUE)
		{
			if ( strncmp(pszSeparateEnd, m_pPointer, nLen) == 0
				|| 0 == *m_pPointer
				|| '\r' == *m_pPointer 
				|| '\n' == *m_pPointer )
				break;

			m_pPointer++;
		}
	}

	*pszLineEnd = m_pPointer;
	//bTrue = IsPoiterInBuffer();

	if (pszSeparateEnd[0] == 0)
	{
		if (chSeparateEnd == *m_pPointer)
		{
			m_pPointer++;
		}
	}
	else
	{
		if ( strncmp(pszSeparateEnd, m_pPointer, nLen) == 0)
		{
			m_pPointer += nLen;
		}
	}
	
	if (m_pPointer > m_pBuffer + m_nLength )
	{
		//bTrue = FALSE;
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
CEquationKey* CEquationBuffer::FindEquationKey(const CString &strKeyName)
{
	CEquationKey *pKeyFind = NULL;
	CEquationKey *pKey = NULL;
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		pKey = (CEquationKey*)GetNext(pos);
		if (pKey->CompareName(strKeyName))
		{
			pKeyFind = pKey;
			break;
		}
	}
	return pKeyFind;
}

CEquationKey* CEquationBuffer::FindEquationKey(const char *pszKeyName)
{
	CEquationKey *pKeyFind = NULL;
	CEquationKey *pKey = NULL;
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		pKey = (CEquationKey*)GetNext(pos);
		if (pKey->CompareName(pszKeyName))
		{
			pKeyFind = pKey;
			break;
		}
	}
	return pKeyFind;
}
