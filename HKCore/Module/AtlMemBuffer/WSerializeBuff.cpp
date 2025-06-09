// SerializeBuff.cpp: implementation of the CWSerializeBuff class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WSerializeBuff.h"
#include "..\AtlBaseClass\AtlFile.h"


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const long CWSerializeBuff::DEFAULT_BUFF_LENGTH = 512;
CWSerializeBuff::CWSerializeBuff()
{
	m_bAttach = FALSE;
	Init();
	AllocDefaultBuffer();//SetBufferLength(DEFAULT_BUFF_LENGTH);
	m_nOperation = MODE_WRITE;
	m_nBufCurLen = 0;
}

CWSerializeBuff::CWSerializeBuff(int nLen)
{
	m_bAttach = FALSE;
	Init();
	SetBufferLength(nLen);
	m_nOperation = MODE_WRITE;
	m_nBufCurLen = 0;
}

CWSerializeBuff::CWSerializeBuff(wchar_t *pBuff,int nLen)
{
	m_bAttach = FALSE;
	Init();
	SetBufferLength(nLen);
	memcpy(m_pchData, pBuff, nLen*2);
	m_nBufCurLen = 0;
}

CWSerializeBuff::CWSerializeBuff(char *pBuff,int nLen)
{
	m_bAttach = FALSE;
	Init();
	SetBufferLength(nLen);
	memcpy(m_pchData, pBuff, nLen);
	m_nBufCurLen = 0;
}

CWSerializeBuff::~CWSerializeBuff()
{
	FreeBuff();
}

void CWSerializeBuff::GetBuffer(wchar_t** pBuffer, long *nBufferLen)
{
	*pBuffer = (wchar_t*)m_pchData;
	*nBufferLen = m_nBufCurLen;
}

void CWSerializeBuff::GetBuffer(char** pBuffer, long *nBufferLen)
{
	*pBuffer = m_pchData;
	*nBufferLen = m_nBufCurLen;
}

void CWSerializeBuff::AttachBuffer(wchar_t *pBuffer, long nBufferLen)
{
	FreeBuff();
	m_bAttach = TRUE;
	m_pchData = (char*)pBuffer;
	m_nBufCurLen = nBufferLen*2;
	m_nBufferLength = m_nBufCurLen;
	m_lpBufCur = m_pchData;
	m_lpBufMax = m_pchData + m_nBufCurLen;
	ResetBufferPointer();
}

void CWSerializeBuff::AttachBuffer(char *pBuffer, long nBufferLen)
{
	FreeBuff();
	m_bAttach = TRUE;
	m_pchData = (char*)pBuffer;
	m_nBufCurLen = nBufferLen;
	m_lpBufCur = m_pchData;
	m_nBufferLength = m_nBufCurLen;
	m_lpBufMax = m_pchData + m_nBufCurLen;
	ResetBufferPointer();
}

void CWSerializeBuff::DettachBuffer()
{
	m_bAttach = FALSE;
	m_pchData = NULL;
}

BOOL CWSerializeBuff::ReadFromFile(const CComBSTR &strFile)
{
	USES_CONVERSION;   
	LPCTSTR   szFile;   
	szFile   =   W2T(strFile);
	
	CAtlFile file;
	BOOL bOpen = file.Open(szFile, CAtlFile::modeRead);

	if (bOpen)
	{
		long nLen = file.GetLength();
		m_nBufCurLen = nLen;
		AllocBuffer(0);
		file.ReadHuge(m_pchData,nLen);
		m_pchData[nLen] = 0;
		file.Close();
	}

	return bOpen;
}


BOOL CWSerializeBuff::WriteToFile(const CComBSTR &strFile)	
{
	USES_CONVERSION;   
	LPCTSTR   szFile;   
	szFile   =   W2T(strFile);

	long nLen = 0;
	CAtlFile file;
    BOOL bOpen = file.Open(szFile,CAtlFile::modeCreate | CAtlFile::modeWrite);
	if (bOpen)
	{
		nLen = GetBufferLength();
		file.WriteHuge(m_pchData,nLen);
		file.Close();
	}
	return bOpen;
}

void CWSerializeBuff::Init()
{
	m_pchData = NULL;
	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
	m_nBufCurLen = 0;
	m_nBufferLength = 0;
}

void CWSerializeBuff::FreeBuff()
{
	m_nBufCurLen = 0;
	m_nBufferLength = 0;
	if (m_bAttach)
	{
		m_pchData = NULL;
		m_bAttach = FALSE;
	}
	else
	{
		if (m_pchData != NULL)
		{
			delete m_pchData;
			m_pchData = NULL;
		}
	}
	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
}

BOOL CWSerializeBuff::AllocDefaultBuffer()
{
	FreeBuff();
	m_nBufCurLen = DEFAULT_BUFF_LENGTH;
	m_nBufferLength = DEFAULT_BUFF_LENGTH;
	m_pchData = new char[m_nBufCurLen];

	if (m_pchData != NULL)
	{
		memset(m_pchData,0,m_nBufferLength);
		m_lpBufCur = m_pchData;
		m_lpBufMax = m_pchData + m_nBufferLength;
	}
	
	return (m_pchData != NULL);
}

 BOOL CWSerializeBuff::AllocBuffer(long lExpandPercent)
 {
	 long nBufferLen = m_nBufCurLen + m_nBufCurLen * lExpandPercent / 100;
	 
	 if (m_nBufferLength < nBufferLen /*|| nBufferLen <= 0 */|| m_pchData == NULL)
	 {//需要的缓冲区大于缓冲区最大长度  缓冲区没有分配
		 FreeBuff();
		 m_nBufferLength = nBufferLen + DEFAULT_BUFF_LENGTH; //缓冲区最大长度
		 m_nBufCurLen = nBufferLen;  //当前使用的缓冲区长度
		 m_pchData = new char[m_nBufferLength];
		 m_lpBufMax = m_pchData + m_nBufferLength;
		 m_lpBufCur = m_pchData;
	 }
	 else
	 {
	 }
	 

	 if (m_pchData != NULL)
	 {
		 memset(m_pchData,0,m_nBufCurLen);
		 m_lpBufCur = m_pchData;
	 }

	 return (m_pchData != NULL);
 }
 
BOOL CWSerializeBuff::SetBufferLength(int nLen)
{
	m_nBufCurLen = nLen;
	return AllocBuffer(0);	
}

int  CWSerializeBuff::GetBufferLength()
{
	if (MODE_CALSIZE == m_nOperation)
	{
		return 	m_nBufCurLen;
	}
	else if (MODE_READ == m_nOperation)
	{
		return m_nBufCurLen;//m_lpBufMax - m_pchData;
	}
	else
	{
		return m_lpBufCur - m_pchData;//m_nBufCurLen;//m_lpBufCur - m_pchData;
	}
}

void CWSerializeBuff::ResetBufferPointer()
{
	m_lpBufCur = m_pchData;
}

void CWSerializeBuff::SetReadMode()
{
	m_nOperation = MODE_READ;
}

void CWSerializeBuff::SetWriteMode()
{
	m_nBufCurLen = 0;
	m_nOperation = MODE_WRITE;
}

void CWSerializeBuff::SetCalSizeMode()
{
	m_nOperation = MODE_CALSIZE;
}

BOOL CWSerializeBuff::IsReadMode()
{
	return (m_nOperation == MODE_READ);
}

BOOL CWSerializeBuff::IsWriteMode()
{
	return (m_nOperation == MODE_WRITE);
}

BOOL CWSerializeBuff::IsCalSizeMode()
{
	return (m_nOperation == MODE_CALSIZE);
}

long CWSerializeBuff::SetBuffer(VARIANT *pvarBuff)
{
	long lLBound = 0;
	long lUBound = 0;
	
	long lIndex = 0;
	SAFEARRAY *pFilter = V_ARRAY(pvarBuff); 
	if (SafeArrayGetLBound(pFilter,1,&lLBound) != S_OK)
		return -1;
	if (SafeArrayGetUBound(pFilter,1,&lUBound) != S_OK)
		return -1;
	
	SetBufferLength(lUBound-lLBound+1);

	for(int i=lLBound;i<=lUBound;i++)
	{
		SafeArrayGetElement(pFilter,&lIndex,&m_pchData[lIndex]);
		lIndex++;
	}		

	return lIndex;
}

long CWSerializeBuff::GetBuffer(VARIANT *pvarBuff)
{
	SAFEARRAYBOUND bound;
	SAFEARRAY * pFilter = NULL; 
	long lIndex = 0;

	bound.cElements = m_nBufCurLen;
	bound.lLbound=0;
	pFilter = SafeArrayCreate(VT_UI1,1,&bound);
	unsigned char uc = 0;
	for(int i = 0; i < m_nBufCurLen; i++)
	{
		uc = (unsigned char)m_pchData[i];
		SafeArrayPutElement(pFilter,&lIndex,(void*)&uc);
		lIndex++;
	}		

	V_VT(pvarBuff) = VT_UI1 | VT_ARRAY; 
	V_ARRAY(pvarBuff) = pFilter; 
	
	return lIndex;
}

//缓冲区写方法
long CWSerializeBuff::Char(char ch)
{
	*this << ch;
	return (m_lpBufCur - m_pchData);
}

long CWSerializeBuff::Byte(BYTE by)
{
	*this << by;
	return (m_lpBufCur - m_pchData);
}

long CWSerializeBuff::Word(WORD w)
{
	*this << w;
	return (m_lpBufCur - m_pchData);	
}

long CWSerializeBuff::Long (LONG l)
{
	*this << l;
	return (m_lpBufCur - m_pchData);
}

long CWSerializeBuff::DWord(DWORD dw)
{
	*this << dw;
	return (m_lpBufCur - m_pchData);
}

long CWSerializeBuff::Float(float f)
{
	*this << f;
	return (m_lpBufCur - m_pchData);
}

long CWSerializeBuff::Double(double d)
{
	*this << d;
	return (m_lpBufCur - m_pchData);
}

long CWSerializeBuff::Int(int i)
{
	*this << i;
	return (m_lpBufCur - m_pchData);
}

long CWSerializeBuff::Short(short w)
{
	*this << w;
	return (m_lpBufCur - m_pchData);
}

long CWSerializeBuff::Wchar(wchar_t wch)
{
	*this << wch;
	return (m_lpBufCur - m_pchData);
}

long CWSerializeBuff::Unsigned(unsigned u)
{
	*this << u;
	return (m_lpBufCur - m_pchData);
}

long CWSerializeBuff::String(const CComBSTR &strData)
{
	*this << strData;
	return (m_lpBufCur - m_pchData);
}

long CWSerializeBuff::String(BSTR strData)
{
	*this << strData;
	return (m_lpBufCur - m_pchData);
}

long CWSerializeBuff::Currency(const CURRENCY &cy)
{
	*this << cy;
	return (m_lpBufCur - m_pchData);
}


//缓冲区读方法
long CWSerializeBuff::Char(char *ch)
{
	*this >> *ch;
	return 0;
}

long CWSerializeBuff::Byte(BYTE *by)
{
	*this >> *by;
	return 0;
}

long CWSerializeBuff::Word(WORD *w)
{
	*this >> *w;
	return 0;
}

long CWSerializeBuff::Long (LONG *l)
{
	*this >> *l;
	return 0;
}

long CWSerializeBuff::DWord(DWORD *dw)
{
	*this >> *dw;
	return 0;
}

long CWSerializeBuff::Float(float *f)
{
	*this >> *f;
	return 0;
}

long CWSerializeBuff::Double(double *d)
{
	*this >> *d;
	return 0;
}

long CWSerializeBuff::Int(int *i)
{
	*this >> *i;
	return 0;
}

long CWSerializeBuff::Short(short *w)
{
	*this >> *w;
	return 0;
}

long CWSerializeBuff::Wchar(wchar_t *ch)
{
	*this >> *ch;
	return 0;
}

long CWSerializeBuff::Unsigned(unsigned *u)
{
	*this >> *u;
	return 0;
}

long CWSerializeBuff::RString(CComBSTR &strData)
{
	*this >> strData;
	return 0;
}

long CWSerializeBuff::String(BSTR *strData)
{
	*this >> strData;
	return 0;
}

long CWSerializeBuff::Currency(CURRENCY *cy)
{
	*this >> *cy;
	return 0;
}

//增加缓冲区的长度
long CWSerializeBuff::AddBufferLength(long lLen)
{

	m_nBufCurLen += lLen;
	return m_nBufCurLen;	
}

