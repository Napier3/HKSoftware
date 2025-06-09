
#if !defined __WBUFFERBASE_H_
#define __WBUFFERBASE_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWBufferBase
{
protected:
	wchar_t *m_pBuffer;	     //存储区地址
	long m_nLength;          //长度
	long m_nBufferLength;    //当前缓冲区总长度
	wchar_t *m_pPointer;     //执行指针
	bool m_bFormartAllChar;  //是否格式化指定的全部字符
	
public:
	CWBufferBase();
	CWBufferBase(const CComBSTR &strBuff);
	CWBufferBase(wchar_t* pszBuff);
	CWBufferBase(const CWBufferBase *pBuffer);
	CWBufferBase(wchar_t* pBuffBegin,wchar_t* pBuffEnd);
	virtual ~CWBufferBase();

	wchar_t* GetString();
	wchar_t* NextString();
	wchar_t* GetBufferEndPos();
	wchar_t* GetBufferBeginPos();
	void ResetPointer();
	BOOL IsLegal();
	BOOL IsPoiterInBuffer();
	BOOL IsPoiterInBuffer(wchar_t* p);
	void FormatBuffer(wchar_t ch, wchar_t chReplace = 0);
	void EnableFormartAllChar(bool bEnable = true);

public:
	virtual BOOL ReadFromFile(const CComBSTR &strFile);
	virtual BOOL WriteToFile(const CComBSTR &strFile);
	//初始化缓冲区
	virtual void InitBuffer(BSTR strBuff);
	virtual void InitBuffer(const CComBSTR &strBuff);
	virtual void InitBuffer(const CWBufferBase *pBuffer);
	virtual void InitBuffer(wchar_t* pBuffBegin,wchar_t* pBuffEnd);
	
	//初始化缓冲区，缓冲区的大小比实际的大
	virtual void InitBufferEx(const CComBSTR &strBuff,long lSizeExpandRatio);	//
	virtual void InitBufferEx(const CWBufferBase *pBuffer,long lSizeExpandRatio);
	virtual void FormatBuffer();
	virtual void FormatBufferEx();

	BOOL Part(wchar_t *pszSrc,wchar_t *pszLeft,wchar_t *pszRight,wchar_t *pszPart,wchar_t *pszEnd=NULL);
	BOOL Part(wchar_t *pszSrc,wchar_t *pszLeft,wchar_t *pszRight,wchar_t cPart,wchar_t cEnd=0);
	
protected:
	void FormatBufferAroundSeparate(wchar_t ch,wchar_t chReplace = 0);
	virtual bool IsASeparateChar(wchar_t ch);
	
private:
	void Init();
	void Release();
	void SetZeroMemory()
	{
		ZeroMemory(m_pBuffer,m_nLength*sizeof(wchar_t));
	}
	void AllocMemBuffer(long nBufferLen);
};

void FormatBuffer(wchar_t *pBuffBegin,wchar_t *pBuffEnd,wchar_t ch,wchar_t chReplace);
inline void FormatBuffer(wchar_t *pBuff,long nLen,wchar_t ch,wchar_t chReplace)
{
	FormatBuffer(pBuff,pBuff+nLen,ch,chReplace);
}
inline BOOL IsPointInBuff(wchar_t *pBuff,wchar_t *pBuffEnd,wchar_t *pPoint)
{
	return ( (pPoint >= pBuff) && (pPoint < pBuffEnd));
}
inline BOOL IsPointInBuff(wchar_t *pBuff,long nLen, wchar_t *pPoint)
{
	return IsPointInBuff(pBuff,pBuff+nLen,pPoint);
}

inline wchar_t* GetString(wchar_t *pBuff,wchar_t *pEnd)
{
	wchar_t *pString = pBuff;
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
inline wchar_t* GetString(wchar_t *pBuff,long nLen)
{
	return GetString(pBuff,pBuff+nLen);
}

inline wchar_t* NextString(wchar_t *pBuff,wchar_t *pEnd)
{
	wchar_t *pString = pBuff;
	pString += wcslen(pString);
	return GetString(pString,pEnd);
}
inline wchar_t* NextString(wchar_t *pBuff,long nLen)
{
	return NextString(pBuff,pBuff+nLen);
}

inline wchar_t* OffsetString(wchar_t *pBuff)
{
	while ( (*pBuff == VK_TAB || *pBuff == VK_SPACE) && (*pBuff != 0) )
	{
		pBuff++;
	}

	return pBuff;
}

inline wchar_t* OffsetToNextNumberString(wchar_t *pBuff)
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

#endif