#include "stdafx.h"
#include "WBufferBase.h"
// #include "..\AtlBaseClass\AtlFile.h"
//#include "..\AtlBaseClass\ATLGloblaApi.h"

#define MENBUFFERLENEX  50

CWBufferBase::CWBufferBase()
{
	Init();
}

CWBufferBase::CWBufferBase(const CComBSTR &strBuff)
{
	Init();

	InitBuffer(strBuff);
}

CWBufferBase::CWBufferBase(wchar_t* pszBuff)
{
	Init();
	InitBuffer(pszBuff);
}

CWBufferBase::CWBufferBase(const CWBufferBase *pBuffer)
{
	Init();
	InitBuffer(pBuffer);
}

CWBufferBase::CWBufferBase(wchar_t* pBuffBegin,wchar_t* pBuffEnd)
{
	Init();
	InitBuffer(pBuffBegin,pBuffEnd);
}

CWBufferBase::~CWBufferBase()
{
	Release();
}

void CWBufferBase::Init()
{
	m_nBufferLength = 0;

	m_pBuffer = NULL;		//�ļ��洢����ַ
	m_nLength = 0;			//�ļ�����
	m_pPointer = NULL;		//�ļ�ִ��ָ��
	m_bFormartAllChar = true;
}

//*********************************************************************
//ReadFromFile				public
//*********************************************************************
//������	���ļ��л�ȡ����
//������	strFile���ļ�����
//���أ�	��
BOOL CWBufferBase::ReadFromFile(const CComBSTR &strFile)
{
	Release();

	USES_CONVERSION;   
	LPCTSTR   szFile;   
	szFile   =   W2T(strFile);
	
	CFile file;
	BOOL bTrue = file.Open(szFile, CFile::modeRead);
	if(bTrue)
	{
		m_nLength = file.GetLength();
		AllocMemBuffer(m_nLength);
		file.Read(m_pBuffer,m_nLength*sizeof(wchar_t));
		m_pBuffer[m_nLength] = 0;
		file.Close();

		FormatBufferEx();
		ResetPointer();
	}

	return bTrue;
}

BOOL CWBufferBase::WriteToFile(const CComBSTR &strFile)
{
	CFile file;
	USES_CONVERSION;   
	LPCTSTR   szFile;   
	szFile   =   W2T(strFile);
    BOOL bOpen = file.Open(szFile, CFile::modeCreate|CFile::modeWrite);

	if (bOpen)
	{
		file.Write(m_pBuffer,m_nLength*sizeof(wchar_t));
		file.Close();
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
//*********************************************************************
//InitBuffer				public
//*********************************************************************
//������	��ʼ��������
//������	strBuff���ı�����
//���أ�	��
void CWBufferBase::InitBuffer(const CComBSTR &strBuff)
{
	long nLen = strBuff.Length();
	
	AllocMemBuffer(nLen);
	wcscpy(m_pBuffer,strBuff);
	ResetPointer();
}

void CWBufferBase::InitBuffer(BSTR strBuff)
{
	long nLen = wcslen(strBuff);
	
	AllocMemBuffer(nLen);
	wcscpy(m_pBuffer,strBuff);
	ResetPointer();
}

void CWBufferBase::AllocMemBuffer(long nBufferLen)
{
	if (m_nBufferLength < nBufferLen || nBufferLen <= 0)
	{
		Release();
		m_nBufferLength = nBufferLen + MENBUFFERLENEX;
		m_pBuffer = new wchar_t [m_nBufferLength];
	}
	else
	{
	}

	m_nLength = nBufferLen;	
	ZeroMemory(m_pBuffer,(m_nBufferLength)*sizeof(wchar_t));
}

void CWBufferBase::InitBuffer(const CWBufferBase *pBuffer)
{
	AllocMemBuffer(pBuffer->m_nLength);
	CopyMemory(m_pBuffer,pBuffer->m_pBuffer, m_nLength*sizeof(wchar_t));
	m_pBuffer[m_nLength] = 0;
	ResetPointer();
}

void CWBufferBase::InitBuffer(wchar_t* pBuffBegin,wchar_t* pBuffEnd)
{
	if (pBuffBegin == NULL || pBuffEnd == NULL)
		return;

	long nLen = pBuffEnd - pBuffBegin+1;
	AllocMemBuffer(nLen);
	CopyMemory(m_pBuffer,pBuffBegin,m_nLength);
	m_pBuffer[m_nLength] = 0;
	ResetPointer();
}

void CWBufferBase::InitBufferEx(const CComBSTR &strBuff,long lSizeExpandRatio)
{
	long nLenEx = strBuff.Length();
	nLenEx = (long)(nLenEx * (100 + lSizeExpandRatio) / 100.f);
	AllocMemBuffer(nLenEx);
	wcscpy(m_pBuffer,strBuff);
	ResetPointer();
}

void CWBufferBase::InitBufferEx(const CWBufferBase *pBuffer,long lSizeExpandRatio)
{
	long nLenEx = pBuffer->m_nLength;
	nLenEx = (long)(nLenEx * (100 + lSizeExpandRatio) / 100.f);
	AllocMemBuffer(nLenEx);
	CopyMemory(m_pBuffer, pBuffer->m_pBuffer, pBuffer->m_nLength);
	
	ResetPointer();
}

//*********************************************************************
//FormatBuffer				public
//*********************************************************************
//������	��ʽ��������
//������	��
//���أ�	��
void CWBufferBase::FormatBuffer()
{
	//��ʽ��
	int i = 0;
	int iTemp = 0;
	for (i=0;i<m_nLength;i++)
	{
		//���Ե�ע����
		if ((m_pBuffer[i]=='/') && (m_pBuffer[i+1]=='/'))
		{
			iTemp = i;
			while((i<m_nLength) && (m_pBuffer[i]!=10 && m_pBuffer[i]!=13))
			{
				m_pBuffer[i]=0;
				i++;
			}
		}
	}
}

//*********************************************************************
//FormatBuffer				public
//*********************************************************************
//������	��ʽ��������
//������	ch����ʽ���ַ�
//���أ�	��
void CWBufferBase::FormatBuffer(wchar_t ch, wchar_t chReplace)
{
	if(ch == 0)
	{
		return;
	}

	if (m_bFormartAllChar)
	{
		//��ʽ��
		int i = 0;
		int iTemp = 0;
		for (i=0; i<m_nLength; i++)
		{
			if (m_pBuffer[i] == ch)
				m_pBuffer[i] = chReplace;
		}
	}
	else
	{
		FormatBufferAroundSeparate(ch,chReplace);
	}
}

void CWBufferBase::EnableFormartAllChar(bool bEnable)
{
	m_bFormartAllChar = bEnable;
}

void CWBufferBase::FormatBufferEx()
{
	//FormatBuffer('\r');
	//FormatBuffer('\n');
}

BOOL CWBufferBase::Part(wchar_t *pszSrc,wchar_t *pszLeft,wchar_t *pszRight,wchar_t *pszPart,wchar_t *pszEnd)
{
	BOOL bTrue = TRUE;
	if (pszSrc==NULL || pszLeft==NULL || pszRight==NULL || pszPart==NULL)
	{
		return FALSE;
	}

	long lLenPart = wcslen(pszPart);
	long lLenEnd = wcslen(pszEnd);
	wchar_t *pTemp = NULL;
	wchar_t *pCurr = NULL;
	pCurr = pszSrc;

	//�ָ��������
	while(TRUE)
	{
		if(*pCurr == 0)
		{
			bTrue = FALSE;
			break;
		}
		
		if(wcsncmp(pCurr, pszEnd, lLenEnd))
		{
			bTrue = FALSE;
			break;
		}

		if(wcsncmp(pCurr, pszPart, lLenPart))
			break;

		pCurr++;
	}

	if(!bTrue)
		return bTrue;

	pTemp = pszSrc;
	while(pTemp < pCurr)
	{
		*pszLeft = *pTemp;
		pszLeft++;
		pTemp++;
	}

	*pszLeft = 0;
	pCurr += lLenPart;	//�����ָ����� pszPart

	//�ָ������ұ�
	if(pszEnd == NULL)
	{
		while(*pCurr!= 0)
		{
			*pszRight = *pCurr;
			pszRight++;
			pCurr++;
		}
	}
	else
	{
		while(TRUE)
		{
			if(*pCurr == 0)
				break;

			if(wcsncmp(pCurr,pszPart,lLenPart))
				break;

			*pszRight = *pCurr;
			pszRight++;
			pCurr++;
		}
	}
	
	*pszRight = 0;
	return bTrue;
}

BOOL CWBufferBase::Part(wchar_t *pszSrc,wchar_t *pszLeft,wchar_t *pszRight,wchar_t cPart,wchar_t cEnd)
{
	BOOL bTrue = TRUE;
	if (pszSrc == NULL || pszLeft==NULL || pszRight==NULL)
	{
		return FALSE;
	}

	wchar_t *pTemp = NULL;
	wchar_t *pCurr = NULL;
	pCurr = pszSrc;
	pTemp = pszLeft;
	
	//�ָ��������
	while(TRUE)
	{
		if(*pCurr == 0)
		{
			bTrue = FALSE;
			break;
		}

		if(*pCurr == cEnd)
		{
			bTrue = FALSE;
			break;
		}

		if(*pCurr == cPart)
			break;

		pCurr++;
	}
	
	if(!bTrue)
		return bTrue;
	
	pTemp = pszSrc;
	while(pTemp < pCurr)
	{
		*pszLeft = *pTemp;
		pszLeft++;
		pTemp++;
	}

	*pszLeft = 0;
	pCurr++;	//�����ָ����� cPart

	//�ָ������ұ�
	while(TRUE)
	{
		if(*pCurr == cEnd)
			break;

		*pszRight = *pCurr;
		pszRight++;
		pCurr++;
	}
	
	*pszRight = 0;

	return bTrue;
}

void CWBufferBase::FormatBufferAroundSeparate(wchar_t ch,wchar_t chReplace)
{
	wchar_t *pTemp = m_pBuffer;
	wchar_t *pEqualPos = m_pBuffer;
	wchar_t *pBuffEndPos = GetBufferEndPos();
	wchar_t *pSrcBegin = m_pBuffer;
	wchar_t *pSrcEnd = NULL;
	wchar_t *pDest = m_pBuffer;
	
	//��ʼλ�����ݵĸ�ʽ��
	while (*pSrcBegin == ch)
	{
		*pSrcBegin = chReplace;
		pSrcBegin++;
	}
	
	while (IsPoiterInBuffer(pSrcBegin))
	{
		if (IsASeparateChar(*pSrcBegin))
		{
			//�ָ�����ǰ�����ַ���ʽ��
			pTemp = pSrcBegin - 1;
			while (IsPoiterInBuffer(pTemp) && *pTemp == ch)
			{
				*pTemp = chReplace;
				pTemp--;
			}

			//�ָ����ź󲿵��ַ���ʽ��
			pTemp = pSrcBegin + 1;
			while (IsPoiterInBuffer(pTemp) && *pTemp == ch)
			{
				*pTemp = chReplace;
				pTemp++;
			}
			pSrcBegin = pTemp;
		}
		else
		{
			pSrcBegin++;
		}
	}
}

//�ж��ַ��Ƿ�Ϊ�ָ��ַ�
bool CWBufferBase::IsASeparateChar(wchar_t ch)
{
	return false;
}

//*********************************************************************
//Release				private
//*********************************************************************
//������	�ͷ�CWBufferBase��̬����Ļ������ڴ�ռ�
//������	��
//���أ�	��
void CWBufferBase::Release()
{
	m_nBufferLength = 0;
	m_nLength = 0;
	m_pPointer = NULL;
	
	if(m_pBuffer != NULL)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}
}

wchar_t* CWBufferBase::GetString()
{
	while(!*m_pPointer)
		m_pPointer++;

	return m_pPointer;
}

wchar_t* CWBufferBase::NextString() 
{
	m_pPointer += wcslen(m_pPointer);
	return GetString();
}

wchar_t* CWBufferBase::GetBufferEndPos()
{
	return m_pBuffer + m_nLength;
}

wchar_t* CWBufferBase::GetBufferBeginPos()
{
	return m_pBuffer;
}

void CWBufferBase::ResetPointer()
{
	m_pPointer = m_pBuffer;
}

BOOL CWBufferBase::IsLegal()
{
	return (m_pBuffer != NULL);
}

BOOL CWBufferBase::IsPoiterInBuffer()
{
	return IsPoiterInBuffer(m_pPointer);
}

BOOL CWBufferBase::IsPoiterInBuffer(wchar_t* p)
{
	return (p >= m_pBuffer && p < m_pBuffer + m_nLength);
}

void FormatBuffer(wchar_t *pBuffBegin,wchar_t *pBuffEnd,wchar_t ch,wchar_t chReplace)
{
	wchar_t *pTemp = pBuffBegin;

	while(pTemp<=pBuffEnd)
	{
		if (*pTemp == ch)
			*pTemp = chReplace;

		pTemp++;
	}
}
