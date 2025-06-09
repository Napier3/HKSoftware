
#if !defined BUFFERBASE_H_
#define BUFFERBASE_H_

#include "../OSInterface/OSInterface.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBufferBase
{
protected:
	CString m_pszFileName;	//文件名
	char	*m_pBuffer;	//文件存储区地址
	long	m_nLength;		//文件长度
	long    m_nCurrBuffLen;     //当前缓冲区长度
	char	*m_pPointer;		//文件执行指针
	long	m_nLengthEx;	//扩展长度
	bool	m_bFormartAllChar;	//是否格式化指定的全部字符
	bool   m_bAttatch;  //2021-5-16  lijunqing 

public:
	CBufferBase();
	CBufferBase(const CString &strBuff);
	CBufferBase(const BSTR &bstrBuff);
	CBufferBase(const char *pszBuff);
	CBufferBase(const CBufferBase *pBuffer);
	CBufferBase(const char *pBuffBegin,const char *pBuffEnd);
	virtual ~CBufferBase();

	//2021-5-16  lijunqing 
	void Attatch(char *pszBuff);
	char* Dettatch();

	long GetLength()	{	return m_nLength;		}
	char* GetString();
	char* NextString();
	char* GetBufferEndPos();
	char* GetBufferBeginPos();
	void ResetPointer();
	BOOL IsLegal();
	BOOL IsPoiterInBuffer();
	BOOL IsPoiterInBuffer(const char *p);
	void FormatBuffer(char ch,char chReplace = 0);
	void FormatBuffer(char *pszText,char chReplace = 0);
	void EnableFormartAllChar(bool bEnable = true);
	void OffsetPointer(long nOffset)	{	m_pPointer += nOffset;	}
	char* GetPointer()		{	return m_pPointer;		}
	long GetOffsetFromEnd(char *pPoint);

public:
	virtual BOOL ReadFromFile(const char *pszFile);
	virtual BOOL ReadFromFile(const CString &strFile);
	virtual BOOL WriteToFile(const char *pszFile);
	virtual BOOL WriteToFile(const CString &strFile);
	//初始化缓冲区
	virtual void InitBuffer(long nBufferLength);
	virtual void InitBuffer(const CString &strBuff);
	virtual void InitBuffer(const BSTR &bstrBuff);
	virtual void InitBuffer(const char* pszBuff);
	virtual void InitBuffer(const CBufferBase *pBuffer);
	virtual void InitBuffer(const char *pBuffBegin,const char *pBuffEnd);
	
	//初始化缓冲区，缓冲区的大小比实际的大
	virtual void InitBufferEx(const CString &strBuff,long lSizeExpandRatio);	//
	virtual void InitBufferEx(const CBufferBase *pBuffer,long lSizeExpandRatio);
	virtual void FormatBuffer();
	virtual void FormatBufferEx();

	BOOL Part(char *pszSrc,char *pszLeft,char *pszRight,char *pszPart,char *pszEnd=NULL);
	BOOL Part(char *pszSrc,char *pszLeft,char *pszRight,char cPart,char cEnd=0);
	
protected:
	void FormatBufferAroundSeparate(char ch,char chReplace = 0);
	virtual bool IsASeparateChar(char ch);
	
protected:
	void Init();
	virtual void Release();
	void SetZeroMemory()
	{
                memset(m_pBuffer,0, m_nLength*sizeof(char));
	}
};

class CBufferBaseEx : public CBufferBase
{
public:
	CBufferBaseEx();
	virtual ~CBufferBaseEx();

public:
	virtual BOOL ReadFromFile(const CString &strFile, long nMaxBufferLen=1048576);//1M
	void SetBufferLength(long nLen);

protected:
	long m_nBufferMaxLength;
	virtual void Release();

};

void FormatBuffer(char *pBuffBegin,char *pBuffEnd,char ch,char chReplace);
inline void FormatBuffer(char *pBuff,long nLen,char ch,char chReplace)
{
	FormatBuffer(pBuff,pBuff+nLen,ch,chReplace);
}
inline BOOL IsPointInBuff(char *pBuff,char *pBuffEnd,char *pPoint)
{
	return ( (pPoint >= pBuff) && (pPoint < pBuffEnd));
}
inline BOOL IsPointInBuff(char *pBuff,long nLen,char *pPoint)
{
	return IsPointInBuff(pBuff,pBuff+nLen,pPoint);
}

inline char* GetString(char *pBuff,char *pEnd)
{
	char *pString = pBuff;
	while(*pString == 0)
		pString++;
	if (IsPointInBuff(pBuff,pEnd,pString))
	{
		return pString;
	}
	else
	{
		return NULL;
	}
}
inline char* GetString(char *pBuff,long nLen)
{
	return GetString(pBuff,pBuff+nLen);
}

inline char* NextString(char *pBuff,char *pEnd)
{
	char *pString = pBuff;
	pString += strlen(pString);
	return GetString(pString,pEnd);
}
inline char* NextString(char *pBuff,long nLen)
{
	return NextString(pBuff,pBuff+nLen);
}

inline char* OffsetString(char *pBuff)
{
	while ( (*pBuff == VK_TAB || *pBuff == VK_SPACE) && (*pBuff != 0) )
	{
		pBuff++;
	}

	return pBuff;
}

inline char* OffsetToNextNumberString(char *pBuff)
{
	while ( *pBuff != 0 )
	{
		if ('0' <= *pBuff && *pBuff <= '9')
		{
			pBuff++;
		}
		else
		{
			break;
		}
	}
	
	return pBuff;
}

void StringToSystemTime(const CString &strTime, SYSTEMTIME &tmSys);


#endif
