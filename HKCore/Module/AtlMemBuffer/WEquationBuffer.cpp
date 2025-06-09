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

//�ж��ַ��Ƿ�Ϊ�ָ��ַ�
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
//�������ƣ�	ParseInt
//������    	���ݹؼ��ֵ����ƻ�ȡ��Ӧ������ֵ
//���������  	
	pszKey��	�ؼ�������
	strKey��	�ؼ�������
//���������     
	pVal		���عؼ��ֶ�Ӧ����������
����ֵ��     	�ɹ�����TRUE�����򷵻�FALSE��
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
//�������ƣ�	ParseLong
//������    	���ݹؼ��ֵ����ƻ�ȡ��Ӧ��long����ֵ
//���������  	
	pszKey��	�ؼ�������
	strKey��	�ؼ�������
//���������     
	pVal		���عؼ��ֶ�Ӧ��long��������
����ֵ��     	�ɹ�����TRUE�����򷵻�FALSE��
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
//�������ƣ�	ParseFloat
//������    	���ݹؼ��ֵ����ƻ�ȡ��Ӧ�ĸ�����ֵ
//���������  	
	pszKey��	�ؼ�������
	strKey��	�ؼ�������
//���������     
	pVal		���عؼ��ֶ�Ӧ�ĸ���������
����ֵ��     	�ɹ�����TRUE�����򷵻�FALSE��
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
//�������ƣ�	FormatAroundSeparate
//������    	���ָ�����ǰ��Ŀ��Ժ��Ե��ַ�ȥ����ʵ�ʵ�ʵ������ǰ��������
//���������  	
	chSeparate���ָ��ַ�
//���������     
	��
����ֵ��     	�ޡ�
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

//���ùؼ��ֵ�ֵ������ؼ��ֲ�������bAddNew==1�����½��ؼ���  2005/07/18  ���
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

//2006.05.22  ��ȡ��ʽ�Ĺؼ��ֵ����ƺ�����
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

//��ʼ��������
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
//�������ƣ�	IsIgnoreChar
//������    	�ж�һ���ַ��ǲ��ǿ��Ա����Ե��ַ�����Ҫ��Ե�ʽ����
//���������  	
	ch��		��Ҫ�жϵ��ַ�
//���������     
	��
����ֵ��     	�ǿ��Ա����Ե��ַ�����TRUE�����򷵻�FALSE��
*************************************************/
BOOL CWEquationBuffer::IsIgnoreChar(wchar_t ch)
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
	*pszLeftBegin = (wchar_t*)pszSrcBegin;
	*pszLeftEnd = (wchar_t*)(pCurr - 1);
	
	//�����ָ����� cPart
	pCurr++;
	
	//�ָ������ұ�
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

	//��������������ַ����򲻴���
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
//�������ƣ�	FindSeparateKey
//������    	���ҷָ��ַ����ڵ�λ��
//���������  	
	pBeginPos��	���ҵ���ʼλ��
	chSeparate��	�ָ��ַ�
//���������     
	��
����ֵ��     	�ҵ����طָ��ַ����ڵ�λ�ã����򷵻�NULL��
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
//�������ƣ�	OffsetBack
//������    	�ӵ�ǰλ�ÿ�ʼ������ƶ�����һ�����ɺ��Ե��ַ���λ��
//���������  	
	pPos��		��ʼλ�ã�������
//���������     
	��
����ֵ��     	�ޡ�
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
//�������ƣ�	Copy
//������    	��һ�λ�����������Ŀ���ַ
//���������  	
	pDestPos��	Ŀ���ַ��������ɺ��ƶ������µ�λ��
	pSrcBegin��	Դ���ݵ���ʼ��ַ
	pSrcEnd��	Դ���ݵ���ֹ��ַ
//���������     
	��
����ֵ��     	�ޡ�
*************************************************/
void CWEquationBuffer::Copy(wchar_t **pDestPos,wchar_t *pSrcBegin,wchar_t *pSrcEnd)
{
	//Դ��ַ��Ŀ���ַ��ͬ���򷵻�
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
//�������ƣ�	InitEquationKeyList
//������    	��ʼ����ʽ�ؼ����б���������ʽ
//���������  	
	��
//���������     
	��
����ֵ��     	��
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
//�������ƣ�	GetOneLine
//������    	��ȡһ��Ч�ĵ�ʽ�����У���ʽ�����еĽ����ԡ�;�����з��š�\r������\n��Ϊ���
//���������  	
	��
//���������     
	pszLineBegin��	������Ч�����е���ʼλ��
	pszLineEnd��	������Ч�����еĽ���λ��
����ֵ��     	����ڻ������߽�֮�ڣ�����TRUE�����򷵻�FALSE��
*************************************************/
BOOL CWEquationBuffer::GetOneLine(wchar_t **pszLineBegin,wchar_t **pszLineEnd)
{
	BOOL bTrue = FALSE;

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
	wchar_t chSeparate = GetSeparateChar();
	wchar_t chSeparateEnd = GetSeparateEndChar();
	
	//������;���ַ����߻��з��ţ���ʾ����
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
//�������ƣ�	FindEquationKey
//������    	���ݹؼ��ֵ����Ʋ��ҵ�ʽ�ؼ��ֶ���
//���������  	
	strKeyName���ؼ�������
	pszKeyName���ؼ�������
//���������     
	��
����ֵ��     	�ҵ��򷵻عؼ��ֶ��󣬷��򷵻�NULL
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

