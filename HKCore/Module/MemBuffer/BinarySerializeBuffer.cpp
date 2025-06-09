// BinarySerializeBuffer.cpp : implementation file
//

#include "stdafx.h"
#include "BinarySerializeBuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBinarySerializeBuffer

const long CBinarySerializeBuffer::DEFAULT_BUFF_LENGTH = 1024;

CBinarySerializeBuffer::CBinarySerializeBuffer()
{
	m_nOperation = OPERMODE_WRITE;
	m_lBufCurLen = 0;
	_Init();
	m_nBufferMaxLen = 0;
	m_nBufferWriteLen = 0;
}

CBinarySerializeBuffer::~CBinarySerializeBuffer()
{
	_FreeBuff();
}

BOOL CBinarySerializeBuffer::_ReadFromFile(const CString &strFile)
{
	_FreeBuff();
	
	long nLen = 0;
	CFile file;
	BOOL bOpen = file.Open(strFile,CFile::modeRead);
	
	if (bOpen)
	{
		nLen = file.GetLength();
		m_pchData = new char [nLen+10];
		file.ReadHuge(m_pchData,nLen);
		m_pchData[nLen] = 0;
		file.Close();
		m_lpBufCur = m_pchData;
		m_lpBufMax = m_lpBufCur + nLen;
		m_lBufCurLen = nLen;
		m_nBufferWriteLen = nLen;
	}
	
	return bOpen;
}

BOOL CBinarySerializeBuffer::_ReadFromFile(const char *pszFile)
{
	return _ReadFromFile(CString(pszFile));
}


BOOL CBinarySerializeBuffer::_WriteToFile(const CString &strFile)	
{
	long nLen = 0;
	CFile file;
	BOOL bOpen = file.Open(strFile,CFile::modeCreate | CFile::modeWrite);
	
	if (bOpen)
	{
		nLen = m_nBufferWriteLen;//_GetBufferLen();
		file.WriteHuge(m_pchData,nLen);
		file.Close();
	}
	
	return bOpen;
}

BOOL CBinarySerializeBuffer::_WriteToFile(const char *pszFile)	
{
	return _WriteToFile(CString(pszFile));
}

void CBinarySerializeBuffer::_Init()
{
	m_pchData = NULL;
	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
}

void CBinarySerializeBuffer::_FreeBuff()
{
	if (m_pchData != NULL)
	{
		delete m_pchData;
		m_pchData = NULL;
	}
	m_lpBufCur = NULL;
	m_lpBufMax = NULL;
	m_nBufferMaxLen = 0;
}

void CBinarySerializeBuffer::_AllocMemBuffer(long lExpandPercent)
{
	m_nBufferWriteLen = 0;
	
	if (m_lBufCurLen <= 0)
	{
		m_lBufCurLen = DEFAULT_BUFF_LENGTH;
	}
	
	m_lBufCurLen = m_lBufCurLen + m_lBufCurLen * lExpandPercent / 100;
	
	if (m_nBufferMaxLen < m_lBufCurLen)
	{
		_FreeBuff();
		m_nBufferMaxLen = m_lBufCurLen;
		m_pchData = new char [m_nBufferMaxLen];
	}
	
	memset(m_pchData,0,m_lBufCurLen);
	m_lpBufCur = m_pchData;
	m_lpBufMax = m_pchData + m_lBufCurLen;
}

void CBinarySerializeBuffer::_SetBufferLen(int nLen)
{
	m_lBufCurLen = nLen;
	_AllocMemBuffer(0);	
}

int  CBinarySerializeBuffer::_GetBufferLen()
{
	if (OPERMODE_CALSIZE == m_nOperation)
	{
		return 	m_lBufCurLen;
	}
	else
	{
		return m_lpBufMax - m_pchData;
	}
}

void CBinarySerializeBuffer::_ResetBuffer()
{
	m_lpBufCur = m_pchData;
}

void CBinarySerializeBuffer::_SetModeRead()
{
	m_nOperation = OPERMODE_READ;
}

void CBinarySerializeBuffer::_SetModeWrite()
{
	m_nOperation = OPERMODE_WRITE;
}

void CBinarySerializeBuffer::_SetModeCalSize()
{
	m_nOperation = OPERMODE_CALSIZE;
}

BOOL CBinarySerializeBuffer::_IsModeRead()
{
	return (m_nOperation == OPERMODE_READ);
}

BOOL CBinarySerializeBuffer::_IsModeWrite()
{
	return (m_nOperation == OPERMODE_WRITE);
}

BOOL CBinarySerializeBuffer::_IsModeCalSize()
{
	return (m_nOperation == OPERMODE_CALSIZE);
}


long CBinarySerializeBuffer::_SetBuffer(VARIANT *pvarBuff)
{
	long lLBound = 0;
	long lUBound = 0;
	
	long lIndex = 0;
	SAFEARRAY *pFilter = V_ARRAY(pvarBuff); 
	if (SafeArrayGetLBound(pFilter,1,&lLBound) != TRUE)
		return -1;
	if (SafeArrayGetUBound(pFilter,1,&lUBound) != TRUE)
		return -1;
	
	_SetBufferLen(lUBound-lLBound+1);
	m_nBufferWriteLen = lUBound-lLBound+1;
	
	for(int i=lLBound;i<=lUBound;i++)
	{
		SafeArrayGetElement(pFilter,&lIndex,&m_pchData[lIndex]);
		lIndex++;
	}		
	return lIndex;
}

long CBinarySerializeBuffer::_GetBuffer(VARIANT *pvarBuff)
{
	SAFEARRAYBOUND bound[1];
	SAFEARRAY * pFilter = NULL; 
	long lIndex = 0;
	
	bound[0].lLbound=0;
	bound[0].cElements = m_lBufCurLen;
	pFilter = SafeArrayCreate(VT_UI1, 1, bound);
	unsigned char uc = 0;
	for(long i = 0; i < m_lBufCurLen; i++)
	{
		uc = (unsigned char)m_pchData[i];
		SafeArrayPutElement(pFilter,&i,&uc);
	}		
	
	(*pvarBuff).vt = VT_ARRAY | VT_UI1;					///将varBLOB的类型设置为BYTE类型的数组
	(*pvarBuff).parray = pFilter; 							///为varBLOB变量赋值 
	
	return m_lBufCurLen;
}

//缓冲区写方法
long CBinarySerializeBuffer::_WriteByte(BYTE by)
{
	*this << by;
	return (m_lpBufCur - m_pchData);
}

long CBinarySerializeBuffer::_WriteWord(WORD w)
{
	*this << w;
	return (m_lpBufCur - m_pchData);	
}

long CBinarySerializeBuffer::_WriteLong (LONG l)
{
	*this << l;
	return (m_lpBufCur - m_pchData);
}

long CBinarySerializeBuffer::_WriteDWord(DWORD dw)
{
	*this << dw;
	return (m_lpBufCur - m_pchData);
}

long CBinarySerializeBuffer::_WriteFloat(float f)
{
	*this << f;
	return (m_lpBufCur - m_pchData);
}

long CBinarySerializeBuffer::_WriteDouble(double d)
{
	*this << d;
	return (m_lpBufCur - m_pchData);
}

long CBinarySerializeBuffer::_WriteInt(int i)
{
	*this << i;
	return (m_lpBufCur - m_pchData);
}

long CBinarySerializeBuffer::_WriteShort(short w)
{
	*this << w;
	return (m_lpBufCur - m_pchData);
}

long CBinarySerializeBuffer::_WriteChar(char ch)
{
	*this << ch;
	return (m_lpBufCur - m_pchData);
}

long CBinarySerializeBuffer::_WriteUnsigned(unsigned u)
{
	*this << u;
	return (m_lpBufCur - m_pchData);
}

long CBinarySerializeBuffer::_WriteCharStr(const char *pData)
{
	*this << pData;
	return (m_lpBufCur - m_pchData);
}

long CBinarySerializeBuffer::_WriteCString(const CString &strData)
{
	*this << strData;
	return (m_lpBufCur - m_pchData);
}

//缓冲区读方法
long CBinarySerializeBuffer::_ReadByte(BYTE *by)
{
	*this >> *by;
	return 0;
}

long CBinarySerializeBuffer::_ReadWord(WORD *w)
{
	*this >> *w;
	return 0;
}

long CBinarySerializeBuffer::_ReadLong (LONG *l)
{
	*this >> *l;
	return 0;
}

long CBinarySerializeBuffer::_ReadDWord(DWORD *dw)
{
	*this >> *dw;
	return 0;
}

long CBinarySerializeBuffer::_ReadFloat(float *f)
{
	*this >> *f;
	return 0;
}

long CBinarySerializeBuffer::_ReadDouble(double *d)
{
	*this >> *d;
	return 0;
}

long CBinarySerializeBuffer::_ReadInt(int *i)
{
	*this >> *i;
	return 0;
}

long CBinarySerializeBuffer::_ReadShort(short *w)
{
	*this >> *w;
	return 0;
}

long CBinarySerializeBuffer::_ReadChar(char *ch)
{
	*this >> *ch;
	return 0;
}

long CBinarySerializeBuffer::_ReadUnsigned(unsigned *u)
{
	*this >> *u;
	return 0;
}

long CBinarySerializeBuffer::_ReadCharStr(char *pData)
{
	*this >> pData;
	return 0;
}

long CBinarySerializeBuffer::_ReadCString(CString *strData)
{
	*this >> *strData;
	return 0;
}

//增加缓冲区的长度
long CBinarySerializeBuffer::_IncreaseBuffLen(long lLen)
{
	m_lBufCurLen += lLen;
	return m_lBufCurLen;	
}

long CBinarySerializeBuffer::AllocMemBuffer(long nExpandPercent) 
{
	_AllocMemBuffer(nExpandPercent);
	return TRUE;
}

long CBinarySerializeBuffer::SetBufferLen(long nLen) 
{
	_SetBufferLen(nLen);
	return TRUE;
}

long CBinarySerializeBuffer::GetBufferLen() 
{
	return _GetBufferLen();
}

long CBinarySerializeBuffer::ResetBuffer() 
{
	_ResetBuffer();
	return TRUE;
}

long CBinarySerializeBuffer::SetModeRead() 
{
	_SetModeRead();
	return TRUE;
}

long CBinarySerializeBuffer::SetModeWrite() 
{
	_SetModeWrite();
	return TRUE;
}

long CBinarySerializeBuffer::SetModeCalSize() 
{
	_SetModeCalSize();
	return TRUE;
}

BOOL CBinarySerializeBuffer::IsModeRead() 
{
	return _IsModeRead();
}

BOOL CBinarySerializeBuffer::IsModeWrite() 
{
	return _IsModeWrite();
}

BOOL CBinarySerializeBuffer::IsModeCalSize() 
{
	return _IsModeCalSize();
}

long CBinarySerializeBuffer::IncreaseBufferLen(long nLen) 
{
	return _IncreaseBuffLen(nLen);
}

long CBinarySerializeBuffer::SetBuffer(VARIANT FAR* pvarBuffer) 
{
	return _SetBuffer(pvarBuffer);
}

long CBinarySerializeBuffer::GetBuffer(VARIANT FAR* pvarBuffer) 
{
	return _GetBuffer(pvarBuffer);
}

long CBinarySerializeBuffer::WriteChar(char val) 
{
	long nResult = TRUE;
	try
	{
		_WriteChar(val);
	}
	catch (...)
	{
		nResult = FALSE;
	}
	return nResult;
}

long CBinarySerializeBuffer::WriteShort(short val) 
{
	long nResult = TRUE;
	try
	{
		_WriteShort(val);
	}
	catch (...)
	{
		nResult = FALSE;
	}
	return nResult;
}

long CBinarySerializeBuffer::WriteLong(long val) 
{
	long nResult = TRUE;
	try
	{
		_WriteLong(val);
	}
	catch (...)
	{
		nResult = FALSE;
	}
	return nResult;
}

long CBinarySerializeBuffer::WriteFloat(float val) 
{
	long nResult = TRUE;
	try
	{
		_WriteFloat(val);
	}
	catch (...)
	{
		nResult = FALSE;
	}
	return nResult;
}

long CBinarySerializeBuffer::WriteDouble(double val) 
{
	long nResult = TRUE;
	try
	{
		_WriteDouble(val);
	}
	catch (...)
	{
		nResult = FALSE;
	}
	return nResult;
}

long CBinarySerializeBuffer::WriteString(LPCTSTR val) 
{
	long nResult = TRUE;
	try
	{
		_WriteCharStr(val);
	}
	catch (...)
	{
		nResult = FALSE;
	}
	return nResult;
}

long CBinarySerializeBuffer::WriteString(const CString &val) 
{
	long nResult = TRUE;
	try
	{
		_WriteCharStr(val);
	}
	catch (...)
	{
		nResult = FALSE;
	}
	return nResult;
}

long CBinarySerializeBuffer::ReadChar(char FAR* val) 
{
	long nResult = TRUE;
	try
	{
		_ReadChar(val);
	}
	catch (...)
	{
		nResult = FALSE;
	}
	return nResult;
}


long CBinarySerializeBuffer::ReadShort(short FAR* val) 
{
	long nResult = TRUE;
	try
	{
		_ReadShort(val);
	}
	catch (...)
	{
		nResult = FALSE;
	}
	return nResult;
}

long CBinarySerializeBuffer::ReadLong(long FAR* val) 
{
	long nResult = TRUE;
	try
	{
		_ReadLong(val);
	}
	catch (...)
	{
		nResult = FALSE;
	}
	return nResult;
}

long CBinarySerializeBuffer::ReadFloat(float FAR* val) 
{
	long nResult = TRUE;
	try
	{
		_ReadFloat(val);
	}
	catch (...)
	{
		nResult = FALSE;
	}
	return nResult;
}

long CBinarySerializeBuffer::ReadDouble(double FAR* val) 
{
	long nResult = TRUE;
	try
	{
		_ReadDouble(val);
	}
	catch (...)
	{
		nResult = FALSE;
	}
	return nResult;	
}

long CBinarySerializeBuffer::ReadString(CString &val) 
{
	long nResult = TRUE;
	try
	{
		_ReadCString(&val);
	}
	catch (...)
	{
		nResult = FALSE;
	}
	return nResult;	
}

long CBinarySerializeBuffer::WriteToFile(LPCTSTR strFile) 
{
	if(_WriteToFile(strFile))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

long CBinarySerializeBuffer::ReadFromFile(LPCTSTR strFile) 
{
	if(_ReadFromFile(strFile))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
