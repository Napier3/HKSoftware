  // FormatTextBuffer.cpp: implementation of the CFormatTextBuffer class.
//
//////////////////////////////////////////////////////////////////////

/*  //解析例子
CString m_strTextFormat = _T("{*}{Text\"=\"}{*}{Binary\"0x0A\"}");
char pszData[MAX_PATH];
strcpy(pszData, "name=lijunqing\n");

CFormatTextBuffer oFTBuf(m_strTextFormat);
oFTBuf.ParseFormatBuffer((BYTE*)pszData, strlen(pszData));

BYTE pData[MAX_PATH]; 
ZeroMemory(pData, MAX_PATH);
long nLen = oFTBuf.GetData(0, pData);
ZeroMemory(pData, MAX_PATH);
nLen = oFTBuf.GetData(2, pData);
*/

/*  //构造文本的例子
	CFormatTextBuffer oFTBuf;
	oFTBuf.AddItem(FTITYPE_MULTI, _T(""));
	oFTBuf.AddItem(FTITYPE_TEXT, _T("="));
	oFTBuf.AddItem(FTITYPE_MULTI, _T(""));
	oFTBuf.AddItem(FTITYPE_BINARY, _T("0X0A"));
	oFTBuf.GetFormatBuffer(m_strDestText);
*/


#include "stdafx.h"
#include "FormatTextBuffer.h"
#include "EquationKey.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CFormatTextItem::CFormatTextItem()
{
	memset(m_pBuffer, 0, MAX_PATH);
	m_pValue = NULL;
	m_nType = FTITYPE_SINGLE;
	m_nBufferLength = 0;
	m_nValueLength = 0;
	m_nChildBuffCount = 0;
	ZeroMemory(m_nChildBufferLen, 10 * sizeof(long));
}

CFormatTextItem::~CFormatTextItem()
{
	FreeValueBuffer();
}

void CFormatTextItem::FreeValueBuffer()
{
	if (m_pValue != NULL)
	{
		delete m_pValue;
		m_pValue = NULL;
	}
}

void CFormatTextItem::SetItem(long nType, const char *pszText)
{
	m_nType = nType;

	if (m_nType == FTITYPE_TEXT)
	{
		strcpy((char*)m_pBuffer, pszText);
		m_nBufferLength = strlen(pszText);
		m_nValueLength = m_nBufferLength;
	}
	else if (m_nType == FTITYPE_BINARY)
	{
		//m_nBufferLength = HexToValue(pszText, m_pBuffer);
		//m_nValueLength = m_nBufferLength;
		SetItem_Binary(nType, pszText);
	}
	else
	{
		m_pBuffer[0] = 0;
		m_nBufferLength = 0;
	}
}

void CFormatTextItem::SetItem_Binary(long nType, const char *pszText)
{
	long n0X_Pos = 0;
	const char *p = pszText;
	m_nChildBuffCount = 0;
	long nHexPos[10];
	long nIndex = 0;

	char *pTemp = (char*)pszText;
	char *pWrite = (char*)pszText;
	
	while (*pTemp != 0)
	{
		if (*pTemp == '\"')
		{
			pTemp++;
		}
		else
		{
			if (pTemp != pWrite)
			{
				*pWrite = *pTemp;
			}

			pWrite++;
			pTemp++;
		}
	}

	if (pTemp != pWrite)
	{
		*pWrite = 0;
	}
	
	while (*p != 0)
	{
		if (*p=='0' && (*(p+1) == 'x' || *(p+1) == 'X'))
		{
			nHexPos[m_nChildBuffCount] = p - pszText;
			m_nChildBuffCount++;
			p += 2;
		}
		else
		{
			p++;
		}
	}

	nHexPos[m_nChildBuffCount] = p - pszText;

	if (m_nChildBuffCount <= 1)
	{
		m_nBufferLength = HexToValue(pszText, m_pBuffer);
		m_nValueLength = m_nBufferLength;
		return;
	}

	m_pBuffer[0] = '$';
	m_pBuffer[1] = '@';
	m_pBuffer[2] = (char)m_nChildBuffCount;

	p = pszText;
	BYTE *pDest = m_pBuffer + 3 + m_nChildBuffCount;
	long nLen = 0;

	for (nIndex=0; nIndex<m_nChildBuffCount; nIndex++)
	{
		p = pszText + nHexPos[nIndex];
		nLen = nHexPos[nIndex+1] - nHexPos[nIndex];
		m_nBufferLength = HexToValue(p, nLen , pDest);
		m_pBuffer[nIndex+3] = (CHAR)m_nBufferLength;
		m_nChildBufferLen[nIndex] = m_nBufferLength;
		pDest += m_nBufferLength;
	}
}

void CFormatTextItem::SetValue(BYTE *pBegin, BYTE *pEnd)
{
	FreeValueBuffer();

	m_nValueLength = pEnd - pBegin + 1;
	m_pValue = new BYTE [m_nValueLength+5];

	if (m_nValueLength > 0)
	{
		memcpy(m_pValue, pBegin, m_nValueLength);
	}

	m_pValue[m_nValueLength] = 0;
}

void CFormatTextItem::GetItemText(CString &strText)
{
	switch (m_nType)
	{
	case FTITYPE_MULTI:
		strText = _T("{*}");
		break;

	case FTITYPE_SINGLE:
		strText = _T("{&}");
		break;

	case FTITYPE_TEXT:
#ifdef _UNICODE
		strText.Format(_T("{%s\"%s\"}"), CString( CFormatTextBuffer::g_pszTextKey), CString(m_pBuffer));
#else
		strText.Format(_T("{%s\"%s\"}"), CFormatTextBuffer::g_pszTextKey, m_pBuffer);
#endif
		break;

	case FTITYPE_BINARY:
		{
			GetItemText_Binary(strText);
		}
		break;

	default:
		strText = _T("{&}");
		break;
	}
}

void CFormatTextItem::GetItemText_Binary(CString &strText)
{
	char pText[MAX_PATH];
	long nIndex = 0;

	if (m_pBuffer[0] == '$' && m_pBuffer[1] == '@')
	{
		m_nChildBuffCount = m_pBuffer[2];
		
		for (nIndex=0; nIndex<m_nChildBuffCount; nIndex++)
		{
			m_nChildBufferLen[nIndex] = m_pBuffer[nIndex+3];
		}

		BYTE *pBuffer = m_pBuffer+3+m_nChildBuffCount;
        strText.Format(_T("{%s"), CFormatTextBuffer::g_pszBinaryKey);

		for (nIndex=0; nIndex<m_nChildBuffCount; nIndex++)
		{
			ZeroMemory(pText,MAX_PATH);
			ValueToHex(pBuffer, m_nChildBufferLen[nIndex], pText);
			pBuffer += m_nChildBufferLen[nIndex];
            strText.AppendFormat(_T("\"%s\""), pText);
		}

		strText += _T("}");
	}
	else
	{
		ValueToHex(m_pBuffer, m_nBufferLength, pText);
        strText.Format(_T("{%s\"%s\"}"), CFormatTextBuffer::g_pszBinaryKey, pText);
	}
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char* CFormatTextBuffer::g_pszTextKey = "Text";
const char* CFormatTextBuffer::g_pszBinaryKey = "Binary";

CFormatTextBuffer::CFormatTextBuffer()
{
	m_pFormatDataBuffer = NULL;
	m_pFormatDataBufEnd = NULL;
	m_pFormatCurr = NULL;

	DeleteAll();
}

CFormatTextBuffer::CFormatTextBuffer(const CString &strBuff) : CBufferBase(strBuff)
{
	m_pFormatDataBuffer = NULL;
	m_pFormatDataBufEnd = NULL;
	m_pFormatCurr = NULL;

	DeleteAll();
	FormatTextBuffer();
}

CFormatTextBuffer::CFormatTextBuffer(const char *pszBuff) : CBufferBase(pszBuff)
{
	m_pFormatDataBuffer = NULL;
	m_pFormatDataBufEnd = NULL;
	m_pFormatCurr = NULL;

	DeleteAll();
	FormatTextBuffer();
}

CFormatTextBuffer::CFormatTextBuffer(const CBufferBase *pBuffer) : CBufferBase(pBuffer)
{
	m_pFormatDataBuffer = NULL;
	m_pFormatDataBufEnd = NULL;
	m_pFormatCurr = NULL;

	DeleteAll();
	FormatTextBuffer();
}

CFormatTextBuffer::CFormatTextBuffer(const char *pBuffBegin,const char *pBuffEnd) : CBufferBase(pBuffBegin,pBuffEnd)
{
	m_pFormatDataBuffer = NULL;
	m_pFormatDataBufEnd = NULL;
	m_pFormatCurr = NULL;

	DeleteAll();
	FormatTextBuffer();
}

CFormatTextBuffer::~CFormatTextBuffer()
{
	DeleteAll();
}


//初始化缓冲区
void CFormatTextBuffer::InitBuffer(const CString &strBuff)
{
	DeleteAll();
	CBufferBase::InitBuffer(strBuff);
	FormatTextBuffer();
}

void CFormatTextBuffer::InitBuffer(const CBufferBase *pBuffer)
{
	DeleteAll();
	CBufferBase::InitBuffer(pBuffer);
	FormatTextBuffer();
}

void CFormatTextBuffer::InitBuffer(const char *pBuffBegin,const char *pBuffEnd)
{
	DeleteAll();
	CBufferBase::InitBuffer(pBuffBegin,pBuffEnd);
	FormatTextBuffer();
}

void CFormatTextBuffer::FormatBufferEx()
{
	
}

//分隔符号
/*
char CFormatTextBuffer::GetSeparateChar()
{
	return '=';
}

char CFormatTextBuffer::GetSeparateEndChar()
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
BOOL CFormatTextBuffer::IsIgnoreChar(char ch)
{
	return ( (ch == VK_TAB) || (ch == VK_SPACE) || (ch == '\r') || (ch == '\n') );
}

long CFormatTextBuffer::GetLength()
{
	long nLength = 0;
	POS pos = GetHeadPosition();
	CFormatTextItem *p = NULL;

	while (pos != NULL)
	{
		p = (CFormatTextItem *)GetNext(pos);
		nLength += p->m_nValueLength;
	}

	return nLength;
}

long CFormatTextBuffer::GetData(long nIndex, BYTE *pDataDest)
{
	CFormatTextItem *p = (CFormatTextItem*)GetAtIndex(nIndex);

	if (p == NULL)
	{
		return 0;
	}

	if (p->m_pValue != NULL)
	{
		memcpy(pDataDest, p->m_pValue, p->m_nValueLength);
	}

	return p->m_nValueLength;
}

BOOL CFormatTextBuffer::ParseFormatBuffer(const BYTE *pBuffer, long nBufferLen)
{
	POS pos = GetHeadPosition();
	CFormatTextItem *pItem = NULL;
	CFormatTextItem *pNext = NULL;

	m_pFormatDataBuffer = (BYTE*)pBuffer;
	m_pFormatDataBufEnd = (BYTE*)(pBuffer + nBufferLen-1);
	m_pFormatCurr = (BYTE*)pBuffer;
	m_nFormatDataLength = 0;
	BOOL bTrue = FALSE;

	while (pos != NULL)
	{
		pItem = (CFormatTextItem *)GetNext(pos);

		switch (pItem->m_nType)
		{
		case FTITYPE_MULTI:
			if (pos != NULL)
			{
				pNext = (CFormatTextItem *)GetNext(pos);
				bTrue = ParseItemMulti(pItem, pNext);

				if (!bTrue)
				{
					break;
				}
			}
			else
			{
				bTrue = ParseItemMulti(pItem, NULL);
			}

			break;

		case FTITYPE_SINGLE:
			m_pFormatCurr++;
			break;

		case FTITYPE_TEXT:
			bTrue = FALSE;
			break;

		case FTITYPE_BINARY:
			bTrue = FALSE;
			break;

		default:
			break;
		}

		if (!bTrue)
		{
			break;
		}
	}

	return TRUE;
}

BOOL CFormatTextBuffer::GetFormatBuffer(CString &strText)
{
	if (GetCount() == 0)
	{
		return FALSE;
	}

	POS pos = GetHeadPosition();
	CFormatTextItem *p = NULL;
	strText.Empty();
	CString strTemp;

	while (pos != NULL)
	{
		p = (CFormatTextItem *)GetNext(pos);
		p->GetItemText(strTemp);
		strText += strTemp;
	}

	return TRUE;
}

BOOL CFormatTextBuffer::ParseItemMulti(CFormatTextItem *pItem, CFormatTextItem *pNext)
{
	if (pNext == NULL)
	{
		pItem->SetValue(m_pFormatCurr, m_pFormatDataBufEnd);
		return TRUE;
	}

	if (pNext->m_nType == FTITYPE_MULTI || pItem->m_nType == FTITYPE_SINGLE)
	{
		return FALSE;
	}

	BYTE *pBufferCurr = m_pFormatCurr;

	if (pNext->m_nType == FTITYPE_TEXT)
	{
		ParseItemText(pItem, pNext);
	}
	else if (pNext->m_nType == FTITYPE_BINARY)
	{
		ParseItemBinary(pItem, pNext);
	}
	else
	{
	}

	return TRUE;
}

BOOL CFormatTextBuffer::ParseItemSingle(CFormatTextItem *pItem)
{

	return TRUE;
}

BOOL CFormatTextBuffer::ParseItemText(CFormatTextItem *pPrev, CFormatTextItem *pItem)
{
	if (pPrev == NULL)
	{
		return FALSE;
	}

	BYTE *pCurr = m_pFormatCurr;
	BYTE *pEnd = m_pFormatDataBufEnd - pItem->m_nBufferLength;
	BOOL bTrue = FALSE;

	while (pCurr <= pEnd)
	{
		if (memcmp(pItem->m_pBuffer, pCurr, pItem->m_nBufferLength) == 0)
		{
			bTrue = TRUE;
			pPrev->SetValue(m_pFormatCurr, pCurr-1);
			m_pFormatCurr = pCurr + pItem->m_nBufferLength;
			break;
		}

		pCurr++;
	}

	return bTrue;
}

BOOL CFormatTextItem::MemCmp(BYTE *pBuffer)
{
	if (m_nChildBuffCount <= 1)
	{
		if (memcmp(m_pBuffer, pBuffer, m_nBufferLength) == 0)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	long nIndex = 0;
	BYTE *p = m_pBuffer + 3 + m_nChildBuffCount;
	m_nValueLength = 0;

	for (nIndex=0; nIndex<m_nChildBuffCount; nIndex++)
	{
		if (memcmp(p, pBuffer, m_nChildBufferLen[nIndex]) == 0)
		{
			m_nValueLength=m_nChildBufferLen[nIndex];
			return TRUE;
		}

		p+= m_nChildBufferLen[nIndex];
	}

	return FALSE;
}

BOOL CFormatTextBuffer::ParseItemBinary(CFormatTextItem *pPrev, CFormatTextItem *pItem)
{
	if (pPrev == NULL)
	{
		return FALSE;
	}

	BYTE *pCurr = m_pFormatCurr;
	BYTE *pEnd = m_pFormatDataBufEnd - pItem->m_nBufferLength;
	BOOL bTrue = FALSE;

	while (pCurr <= pEnd)
	{
		//if (memcmp(pItem->m_pBuffer, pCurr, pItem->m_nBufferLength) == 0)
		if (pItem->MemCmp(pCurr))
		{
			bTrue = TRUE;
			pPrev->SetValue(m_pFormatCurr, pCurr-1);
			m_pFormatCurr = pCurr + pItem->m_nBufferLength;
			break;
		}

		pCurr++;
	}

	return bTrue;
}

//Text()  Binary(0X######)}
BOOL CFormatTextBuffer::PartString(const char *pszSrcBegin,const char *pszSrcEnd, char *pString)
{
	*pString = 0;
	BOOL bTrue = TRUE;
	ASSERT(pszSrcBegin != NULL && pszSrcEnd != NULL);
	
	if(pszSrcBegin == NULL || pszSrcEnd == NULL)
		return FALSE;

	const char *pCurr = NULL;
	pCurr = pszSrcBegin;
	const char *pTextBegin = NULL;
	const char *pTextEnd = NULL;

	pCurr = OffsetString((char*)pCurr);

	//分隔符号左边
	while(pCurr <= pszSrcEnd)
	{
		if (*pCurr == '\"')
		{
			if (*(pCurr - 1) != '\\')
			{
				if (pTextBegin == NULL)
				{
					pTextBegin = pCurr;
				}
				else
				{
					pTextEnd = pCurr;
					break;
				}
			}
		}

		pCurr++;
	}

	if (pTextBegin == NULL || pTextEnd == NULL)
	{
		return FALSE;
	}

	//跳过 分割符号 "
	pTextBegin++;
	pTextEnd--;

	if (pTextBegin <= pTextEnd)
	{
		long nLen = pTextEnd - pTextBegin + 1;
		memcpy(pString, pTextBegin, nLen);
		*(pString + nLen) = 0;
	}

	return TRUE;
}
BOOL CFormatTextBuffer::PartString_Binary(const char *pszSrcBegin,const char *pszSrcEnd, char *pString)
{
	*pString = 0;
	BOOL bTrue = TRUE;
	ASSERT(pszSrcBegin != NULL && pszSrcEnd != NULL);
	
	if(pszSrcBegin == NULL || pszSrcEnd == NULL)
		return FALSE;

	const char *pCurr = NULL;
	pCurr = pszSrcBegin;
	const char *pTextBegin = NULL;
	const char *pTextEnd = NULL;

	pCurr = OffsetString((char*)pCurr);

	//分隔符号左边
	while(pCurr <= pszSrcEnd)
	{
		if (*pCurr == '\"')
		{
			if (*(pCurr - 1) != '\\')
			{
				if (pTextBegin == NULL)
				{
					pTextBegin = pCurr;
				}
				else
				{
					pTextEnd = pCurr;
				}
			}
		}

		pCurr++;
	}

	if (pTextBegin == NULL || pTextEnd == NULL)
	{
		return FALSE;
	}

	//跳过 分割符号 "
	pTextBegin++;
	pTextEnd--;

	if (pTextBegin <= pTextEnd)
	{
		long nLen = pTextEnd - pTextBegin + 1;
		memcpy(pString, pTextBegin, nLen);
		*(pString + nLen) = 0;
	}

	return TRUE;
}

CFormatTextItem* CFormatTextBuffer::AddItem(long nType, const char *pText)
{
	CFormatTextItem *pNew = new CFormatTextItem();
	pNew->SetItem(nType, pText);
	AddTail(pNew);

	return pNew;
}

CFormatTextItem* CFormatTextBuffer::AddItem(long nType, const CString &strText)
{
	CFormatTextItem *pNew = new CFormatTextItem();
	char *pText = NULL;
	CString_to_char(strText, &pText);
	pNew->SetItem(nType, pText);
	AddTail(pNew);
	delete pText;

	return pNew;
}

BOOL CFormatTextBuffer::PartBlock(const char *pszSrcBegin,const char *pszSrcEnd)
{
	if (pszSrcEnd == pszSrcBegin + 1)
	{
		AddItem(FTITYPE_MULTI, NULL);
	}
	else
	{
		const char *pBegin = pszSrcBegin+1;
		const char *pEnd = pszSrcEnd - 1;
		char pString[MAX_PATH];
		OffsetString((char*)pszSrcBegin);

		if (*pBegin == '*')
		{
			AddItem(FTITYPE_MULTI, NULL);
		}
		else if(*pBegin == '&')
		{
			AddItem(FTITYPE_SINGLE, NULL);
		}
		else if (IsTextKey(pBegin))
		{
			PartString(pBegin + strlen(g_pszTextKey), pEnd, pString);
			AddItem(FTITYPE_TEXT, pString);
		}
		else if (IsBinaryKey(pBegin))
		{
			PartString_Binary(pBegin + strlen(g_pszBinaryKey), pEnd, pString);
			AddItem(FTITYPE_BINARY, pString);
		}
	}
	 
	return TRUE;
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
void CFormatTextBuffer::FormatTextBuffer()
{
	if (m_nLength <= 2)
	{
		return;
	}
	
	char *pBegin = m_pBuffer;
	char *pCurr = m_pBuffer;
	char *pEnd = NULL;
	
	while(IsPoiterInBuffer(pCurr))
	{
		if (IsBlockBegin(pCurr))
		{
			pBegin = pCurr;
		}
		else if (IsBlockEnd(pCurr))
		{
			pEnd = pCurr;

			if (pBegin != NULL)
			{
				PartBlock(pBegin, pEnd);
				pBegin = NULL;
				pEnd = NULL;
			}
			else //错误的格式
			{
				break;
			}
		}

		pCurr++;
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
BOOL CFormatTextBuffer::GetOneLine(char **pszLineBegin,char **pszLineEnd)
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
	char chSeparate = GetSeparateChar();
	char chSeparateEnd = GetSeparateEndChar();
	
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
CFormatTextItem* CFormatTextBuffer::FindEquationKey(const CString &strKeyName)
{
	CFormatTextItem *pKeyFind = NULL;
	CFormatTextItem *pKey = NULL;
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		pKey = (CFormatTextItem*)GetNext(pos);
//		if (pKey->CompareName(strKeyName))
		{
			pKeyFind = pKey;
			break;
		}
	}
	return pKeyFind;
}

CFormatTextItem* CFormatTextBuffer::FindEquationKey(const char *pszKeyName)
{
	CFormatTextItem *pKeyFind = NULL;
	CFormatTextItem *pKey = NULL;
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		pKey = (CFormatTextItem*)GetNext(pos);
//		if (pKey->CompareName(pszKeyName))
		{
			pKeyFind = pKey;
			break;
		}
	}
	return pKeyFind;
}
