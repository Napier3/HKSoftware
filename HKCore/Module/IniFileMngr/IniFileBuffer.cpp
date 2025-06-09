// IniFileBuffer.cpp: implementation of the CIniFileBuffer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniFileBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIniFileBuffer::CIniFileBuffer() : CEquationBuffer()
{

}

//������CEquationBuffer�Ĺؼ�������
CIniFileBuffer::CIniFileBuffer(const CString &strBuff) : CEquationBuffer()
{
	CBufferBase::InitBuffer(strBuff);
}

CIniFileBuffer::CIniFileBuffer(const char *pszBuff) : CEquationBuffer()
{
	CBufferBase::InitBuffer(pszBuff);
}

CIniFileBuffer::CIniFileBuffer(const CBufferBase *pBuffer) : CEquationBuffer()
{
	CBufferBase::InitBuffer(pBuffer);
}

CIniFileBuffer::CIniFileBuffer(const char *pBuffBegin,const char *pBuffEnd) : CEquationBuffer()
{
	CBufferBase::InitBuffer(pBuffBegin,pBuffEnd);
}


CIniFileBuffer::~CIniFileBuffer()
{

}

//��ʼ��������
void CIniFileBuffer::InitBuffer(const CString &strBuff)
{
	CBufferBase::InitBuffer(strBuff);
	FormatBufferEx();
}

void CIniFileBuffer::InitBuffer(const CBufferBase *pBuffer)
{
	CBufferBase::InitBuffer(pBuffer);
	FormatBufferEx();
}

void CIniFileBuffer::InitBuffer(const char *pBuffBegin,const char *pBuffEnd)
{
	CBufferBase::InitBuffer(pBuffBegin,pBuffEnd);
	FormatBufferEx();
}

void CIniFileBuffer::FormatBufferEx()
{
	FormatAroundSeparate(GetSeparateChar());
	FormatBuffer(VK_SPACE);	
	FormatBuffer(VK_TAB);	
	FormatBuffer('\r');	
	FormatBuffer('\n');	

	BOOL b = m_bFormartAllChar;
	m_bFormartAllChar = TRUE;
	FormatBuffer('\r');	
	FormatBuffer('\n');	

	ResetPointer();
}


BOOL CIniFileBuffer::ReadFromFile(const char *pszFile)
{
	DeleteAll();
	BOOL bTrue = CBufferBase::ReadFromFile(pszFile);
	
	return bTrue;
}

BOOL CIniFileBuffer::ReadFromFile(const CString &strFile)
{
	DeleteAll();
	BOOL bTrue = CBufferBase::ReadFromFile(strFile);
	
	return bTrue;
}

BOOL CIniFileBuffer::WriteToFile(const CString &strFile)
{
	CFile file;
	if (! file.Open(strFile,CFile::modeCreate | CFile::modeWrite) )
	{
		return FALSE;
	}
	
/*
	CEquationKey *pKey = NULL;
	POSITION pos = m_listEquationKey.GetHeadPosition();
	const char *pszTemp  =NULL;
	while (pos != NULL)
	{
		pKey = (CEquationKey*)m_listEquationKey.GetNext(pos);
		pszTemp = pKey->GetKeyName2();
		file.Write(pszTemp,strlen(pszTemp));
		file.Write("=",1);
		pszTemp = pKey->GetKeyValue2();
		file.Write(pszTemp,strlen(pszTemp));
		file.Write(";\r\n",3);
	}
*/
	
	file.Close();
	
	return TRUE;
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
BOOL CIniFileBuffer::IsIgnoreChar(char ch)
{
	return ( (ch == VK_TAB) || (ch == VK_SPACE) );
}

//�ж��ַ��Ƿ�Ϊ�ָ��ַ�
bool CIniFileBuffer::IsASeparateChar(char ch)
{
	return ( (ch == '[') || (ch == ']') 
		|| (ch == '=') || (ch == '\r') || (ch == '\n') );
}

BOOL CIniFileBuffer::IsCurrStringASection()
{
	BOOL bTrue = FALSE;

	char *pTemp = GetString();

	if (pTemp == NULL)
	{
		return bTrue;
	}

	long lLen = strlen(pTemp);

	if (IsPoiterInBuffer(pTemp))
	{
		if (*pTemp == '[' && pTemp[lLen-1] == ']')
		{
			bTrue = TRUE;
		}
	}
	return bTrue;
}

BOOL CIniFileBuffer::IsCurrStringAKey()
{
	BOOL bTrue = !IsCurrStringASection();

	//�ж��Ƿ��ڻ�����֮��
	char *pTemp = GetString();
	if (!IsPoiterInBuffer(pTemp))
	{
		bTrue = FALSE;
	}
	return bTrue;
}

BOOL CIniFileBuffer::GetIniSection(char *pszSectionName)
{
	ASSERT(pszSectionName != NULL);
	BOOL bTrue = FALSE;
	char *pTemp = NULL;
	long lLen = 0;

	if (IsCurrStringASection())
	{
		bTrue = TRUE;
		pTemp = GetString();
		lLen = strlen(pTemp);
		pTemp++;	//������[��
		strcpy(pszSectionName,pTemp);
		pszSectionName[lLen-2] = 0;	//ȥ����]��
	}
	NextString();
	
	return bTrue;
}

BOOL CIniFileBuffer::GetIniSection(CString &strSectionName)
{
	BOOL bTrue = FALSE;
	char pszBuff[MAX_PATH];
	memset(pszBuff,0,MAX_PATH);
	bTrue = GetIniSection(pszBuff);

	if (bTrue)
	{
		strSectionName = pszBuff;
	}

	return bTrue;
}

BOOL CIniFileBuffer::GetIniKey(char *pszKeyName,char *pszKeyValue)
{
	ASSERT(pszKeyName != NULL && pszKeyValue != NULL);
	BOOL bTrue = FALSE;
	char *pTemp = NULL;
	long lLen = 0;
	
	if (IsCurrStringAKey())
	{
		pTemp = GetString();
		bTrue = Part(pTemp,pszKeyName,pszKeyValue,GetSeparateChar(),0);
	}
	NextString();
	
	return bTrue;
}

BOOL CIniFileBuffer::GetIniKey(CString &strKeyName,CString &strKeyValue)
{
	BOOL bTrue = FALSE;
	char pszKeyName[MAX_PATH];
	char pszKeyValue[MAX_PATH*2];
	memset(pszKeyName,0,MAX_PATH);
	memset(pszKeyValue,0,MAX_PATH*2);

	bTrue = GetIniKey(pszKeyName,pszKeyValue);
	if (bTrue)
	{
		strKeyName = pszKeyName;
		strKeyValue = pszKeyValue;
	}

	return bTrue;
}

