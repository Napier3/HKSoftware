#include "stdafx.h"
#include "StringToSystimeBuffer.h"
#include "../API/StringApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define MENBUFFERLENEX  50

CStringToSystimeBuffer::CStringToSystimeBuffer()
{
	Init(); 
}

CStringToSystimeBuffer::CStringToSystimeBuffer(const CString &strBuff)
		: CBufferBase(strBuff)
{
// 	Init();
// 	InitBuffer(strBuff);
	CString_To_SystemTime(m_tmSystem);
}

CStringToSystimeBuffer::CStringToSystimeBuffer(const BSTR &bstrBuff)
		: CBufferBase(bstrBuff)
{
// 	Init();
// 	InitBuffer(bstrBuff);
	CString_To_SystemTime(m_tmSystem);
}

CStringToSystimeBuffer::CStringToSystimeBuffer(const char *pszBuff)
		: CBufferBase(pszBuff)
{
// 	Init();
// 	InitBuffer(pszBuff);
	CString_To_SystemTime(m_tmSystem);
}


CStringToSystimeBuffer::CStringToSystimeBuffer(const char *pBuffBegin,const char *pBuffEnd)
		: CBufferBase(pBuffBegin, pBuffEnd)
{
// 	Init();
// 	InitBuffer(pBuffBegin,pBuffEnd);
	CString_To_SystemTime(m_tmSystem);
}

CStringToSystimeBuffer::~CStringToSystimeBuffer()
{
	Release();
}

//*********************************************************************
//InitBuffer				public
//*********************************************************************
//描述：	初始化缓冲区
//参数：	strBuff：文本数据
//返回：	无
void CStringToSystimeBuffer::InitBuffer(const CString &strBuff)
{
	CBufferBase::InitBuffer(strBuff);
	CString_To_SystemTime(m_tmSystem);
}

void CStringToSystimeBuffer::InitBuffer(const BSTR &bstrBuff)
{
	CBufferBase::InitBuffer(bstrBuff);
	CString_To_SystemTime(m_tmSystem);
}

void CStringToSystimeBuffer::InitBuffer(const char* pszBuff)
{
	CBufferBase::InitBuffer(pszBuff);
	CString_To_SystemTime(m_tmSystem);
}

void CStringToSystimeBuffer::InitBuffer(const char *pBuffBegin,const char *pBuffEnd)
{
	CBufferBase::InitBuffer(pBuffBegin, pBuffEnd);
	CString_To_SystemTime(m_tmSystem);
}

void CStringToSystimeBuffer::CString_To_SystemTime(const CString &strText, SYSTEMTIME &tm)
{
	InitBuffer(strText);
	CString_To_SystemTime(tm);
}

void CStringToSystimeBuffer::CString_To_SystemTime(SYSTEMTIME &time)
{
    memset(&time, 0, sizeof(time));
	FormatBuffer();
	FormatBuffer('-');
	FormatBuffer('T');
	FormatBuffer('Z');
	FormatBuffer(':');
	FormatBuffer(' ');
	FormatBuffer('/');

	ResetPointer();
	const char* pszTemp;

	pszTemp = GetString();
	if (IsPoiterInBuffer(pszTemp))
	{
		time.wYear = atoi(pszTemp);
	}

	pszTemp = NextString();
	if(IsPoiterInBuffer(pszTemp))
	{
		time.wMonth = atoi(pszTemp);
	}

	pszTemp = NextString();
	if(IsPoiterInBuffer(pszTemp))
	{
		time.wDay = atoi(pszTemp);
	}

	pszTemp = NextString();
	if(IsPoiterInBuffer(pszTemp))
	{
		time.wHour = atoi(pszTemp);
	}

	pszTemp = NextString();
	if(IsPoiterInBuffer(pszTemp))
	{
		time.wMinute = atoi(pszTemp);
	}

	pszTemp = NextString();
	if(IsPoiterInBuffer(pszTemp))
	{
		time.wSecond = atoi(pszTemp);
	}

	pszTemp = NextString();
	if(IsPoiterInBuffer(pszTemp))
	{
		time.wMilliseconds = atoi(pszTemp);
	}
}

