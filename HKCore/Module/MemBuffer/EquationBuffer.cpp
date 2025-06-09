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

//�����ӿ�
/*************************************************
//�������ƣ�	operator[]
//������    	���ݹؼ��ֵ����ƻ�ȡ��Ӧ��ֵ
//���������  	
	strKeyName��	�ؼ�������
	pszKeyName��	�ؼ�������
//���������     
	��
����ֵ��     	��������ؼ������ƣ����ض�Ӧ�����ݣ������׳��쳣��
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
//�������ƣ�	ParseInt
//������    	���ݹؼ��ֵ����ƻ�ȡ��Ӧ������ֵ
//���������  	
	pszKey��	�ؼ�������
	strKey��	�ؼ�������
//���������     
	pVal		���عؼ��ֶ�Ӧ����������
����ֵ��     	�ɹ�����TRUE�����򷵻�FALSE��
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
//�������ƣ�	ParseLong
//������    	���ݹؼ��ֵ����ƻ�ȡ��Ӧ��long����ֵ
//���������  	
	pszKey��	�ؼ�������
	strKey��	�ؼ�������
//���������     
	pVal		���عؼ��ֶ�Ӧ��long��������
����ֵ��     	�ɹ�����TRUE�����򷵻�FALSE��
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
//�������ƣ�	ParseFloat
//������    	���ݹؼ��ֵ����ƻ�ȡ��Ӧ�ĸ�����ֵ
//���������  	
	pszKey��	�ؼ�������
	strKey��	�ؼ�������
//���������     
	pVal		���عؼ��ֶ�Ӧ�ĸ���������
����ֵ��     	�ɹ�����TRUE�����򷵻�FALSE��
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
//�������ƣ�	ParseString
//������    	���ݹؼ��ֵ����ƻ�ȡ��Ӧ���ַ�������ֵ
//���������  	
	pszKey��	�ؼ�������
	strKey��	�ؼ�������
//���������     
	pszVal		���عؼ��ֶ�Ӧ���ַ�������
	strVal		���عؼ��ֶ�Ӧ���ַ�������
����ֵ��     	�ɹ�����TRUE�����򷵻�FALSE��
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
//�������ƣ�	FormatAroundSeparate
//������    	���ָ�����ǰ��Ŀ��Ժ��Ե��ַ�ȥ����ʵ�ʵ�ʵ������ǰ��������
//���������  	
	chSeparate���ָ��ַ�
//���������     
	��
����ֵ��     	�ޡ�
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
		//�ָ�����ǰ����Ч���ݵĸ���
		pSrcEnd = pEqualPos-1;
		OffsetBack(&pSrcEnd);
		Copy(&pDest,pSrcBegin,pSrcEnd);
		
		//���Ʒָ�����
		*pDest = *pEqualPos;
		pDest++;
		pEqualPos++;

		//�ָ�����ǰ����Ч���ݵĸ���
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
		//�ָ�����ǰ����Ч���ݵĸ���
		pSrcEnd = pEqualPos-1;
		OffsetBack(&pSrcEnd);
		Copy(&pDest,pSrcBegin,pSrcEnd);
		
		//���Ʒָ�����
		//*pDest = *pEqualPos;
		//pDest++;
		//pEqualPos++;
		memcpy(pDest, pEqualPos, nLen);
		pDest += nLen;
		pEqualPos += nLen;

		//�ָ�����ǰ����Ч���ݵĸ���
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

//���ùؼ��ֵ�ֵ������ؼ��ֲ�������bAddNew==1�����½��ؼ���  2005/07/18  ���
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

//2006.05.22  ��ȡ��ʽ�Ĺؼ��ֵ����ƺ�����
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

//��ʼ��������
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

//�ָ�����
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
//�������ƣ�	IsIgnoreChar
//������    	�ж�һ���ַ��ǲ��ǿ��Ա����Ե��ַ�����Ҫ��Ե�ʽ����
//���������  	
	ch��		��Ҫ�жϵ��ַ�
//���������     
	��
����ֵ��     	�ǿ��Ա����Ե��ַ�����TRUE�����򷵻�FALSE��
*************************************************/
BOOL CEquationBuffer::IsIgnoreChar(char ch)
{
	return ( (ch == VK_TAB) || (ch == VK_SPACE) || (ch == '\r') || (ch == '\n') );
}

/*************************************************
//�������ƣ�	PartString
//������    	��һ�����н��зֽ⣬�������ؼ��֡�����
//���������  	
	pszSrcBegin��	�����е���ʼλ��
	pszSrcEnd��		�����еĽ���λ��
	cPart��			�ָ�����
	cEnd��			�����е���Ч��������
//���������     
	pszLeftBegin��	���ڱ���ؼ��ֵ���ʼλ��
	pszLeftEnd��	���ڱ���ؼ��ֵĽ���λ��
	pszRightBegin��	���ڱ������ݵ���ʼλ��
	pszRightEnd��	���ڱ������ݵĽ���λ��
����ֵ��     	����������а�����Ч�ĵ�ʽ����TRUE�����򷵻�FALSE��
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
	
	//�ָ��������
	while(TRUE)
	{
		//�����������Ż��ߵ����ַ�����β
		if(*pCurr == 0 || *pCurr == cEnd)
		{
			bTrue = FALSE;
			break;
		}
		if(*pCurr == cPart)//�ָ�����
			break;
		pCurr++;
	}

	//û�зָ����Ż��߳����������ķ�Χ���򷵻�
	if(!bTrue || !IsPoiterInBuffer(pCurr))
		return bTrue;

	//��¼�ָ�����ǰ��λ��
	*pszLeftBegin = (char*)pszSrcBegin;
	*pszLeftEnd = (char*)(pCurr - 1);
	
	//�����ָ����� cPart
	pCurr++;
	
	//�ָ������ұ�
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
	//��������������ַ����򲻴���
	if (*pCurr != cEnd)
	{
		//2021-1-3  lijunqing ����ĩβû�зָ����ŵ��������
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
	
	//�ָ��������
	while(TRUE)
	{
		//�����������Ż��ߵ����ַ�����β
		if(*pCurr == 0 || (strncmp(pCurr, pszEnd, nLenEnd) == 0) )
		{
			bTrue = FALSE;
			break;
		}

		if(strncmp(pCurr, pszPart, nLenPart) == 0)//�ָ�����
			break;

		pCurr++;
	}

	//û�зָ����Ż��߳����������ķ�Χ���򷵻�
	if(!bTrue || !IsPoiterInBuffer(pCurr))
		return bTrue;

	//��¼�ָ�����ǰ��λ��
	*pszLeftBegin = (char*)pszSrcBegin;
	*pszLeftEnd = (char*)(pCurr - 1);
	
	//�����ָ����� cPart
	pCurr += nLenPart;
	
	//�ָ������ұ�
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
		{//ִ�к��ִ���
			pCurr++;
		}
		else
		{
			pCurr += 2;
		}
	}

	//��������������ַ����򲻴���
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
//�������ƣ�	FindSeparateKey
//������    	���ҷָ��ַ����ڵ�λ��
//���������  	
	pBeginPos��	���ҵ���ʼλ��
	chSeparate��	�ָ��ַ�
//���������     
	��
����ֵ��     	�ҵ����طָ��ַ����ڵ�λ�ã����򷵻�NULL��
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
//�������ƣ�	OffsetBack
//������    	�ӵ�ǰλ�ÿ�ʼ������ƶ�����һ�����ɺ��Ե��ַ���λ��
//���������  	
	pPos��		��ʼλ�ã�������
//���������     
	��
����ֵ��     	�ޡ�
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
//�������ƣ�	Copy
//������    	��һ�λ�����������Ŀ���ַ
//���������  	
	pDesPOS��	Ŀ���ַ��������ɺ��ƶ������µ�λ��
	pSrcBegin��	Դ���ݵ���ʼ��ַ
	pSrcEnd��	Դ���ݵ���ֹ��ַ
//���������     
	��
����ֵ��     	�ޡ�
*************************************************/
void CEquationBuffer::Copy(char **pDesPOS,char *pSrcBegin,char *pSrcEnd)
{
	//Դ��ַ��Ŀ���ַ��ͬ���򷵻�
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
//�������ƣ�	InitEquationKeyList
//������    	��ʼ����ʽ�ؼ����б���������ʽ
//���������  	
	��
//���������     
	��
����ֵ��     	��
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
			//2021-1-3  lijunqing ����ĩβû�зָ����ŵ��������
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
//�������ƣ�	GetOneLine
//������    	��ȡһ��Ч�ĵ�ʽ�����У���ʽ�����еĽ����ԡ�;�����з��š�\r������\n��Ϊ���
//���������  	
	��
//���������     
	pszLineBegin��	������Ч�����е���ʼλ��
	pszLineEnd��	������Ч�����еĽ���λ��
����ֵ��     	����ڻ������߽�֮�ڣ�����TRUE�����򷵻�FALSE��
*************************************************/
BOOL CEquationBuffer::GetOneLine(char **pszLineBegin,char **pszLineEnd)
{
	BOOL bTrue = TRUE;

	//������ʼλ�õĿɺ��Ե��ַ�����¼�е���ʼλ��
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
	
	//������;���ַ����߻��з��ţ���ʾ����
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
//�������ƣ�	FindEquationKey
//������    	���ݹؼ��ֵ����Ʋ��ҵ�ʽ�ؼ��ֶ���
//���������  	
	strKeyName���ؼ�������
	pszKeyName���ؼ�������
//���������     
	��
����ֵ��     	�ҵ��򷵻عؼ��ֶ��󣬷��򷵻�NULL
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
