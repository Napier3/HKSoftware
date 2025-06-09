//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XKeyBase.h  CXKeyBase

#pragma once

#include "XKeyBase.h"

BOOL xkey_IsCharNumChar(wchar_t xChar);

//////////////////////////////////////////////////////////////////////////
//CStringParser
class CXKeyStringBlock
{
public:
	CXKeyStringBlock();
	virtual ~CXKeyStringBlock();

	void SetKeyArrayIndex(long nNumber);
public:
	long  m_nBeginPos;
	long  m_nEndPos;
	CXKeyMatchRef *m_pKeyRef;
	BOOL  m_nType;
    BOOL  m_nSubscriptUsed;
	long  m_nNumber;

	BOOL IsSubBlock(CXKeyStringBlock *pBlock);
	long GetLength();
	BOOL IsArrayKey();
	BOOL IsArrayTypeBefore();
	BOOL IsArrayTypeAfter();
	BOOL IsArrayTypeAll();

	BOOL IsNumber()	{	return m_pKeyRef == NULL;	}
	BOOL IsNumberUse()	{	return m_nSubscriptUsed;	}
	BOOL IsNumberNoUse()	{	return !m_nSubscriptUsed;	}
	void SetNumberUse(BOOL bUse)	{	m_nSubscriptUsed = bUse;	}
};

class CXKeyStringNumberBlock
{
public:
	CXKeyStringNumberBlock(long  nBeginPos, long  nEndPos, long nNumber);
	CXKeyStringNumberBlock();
	virtual ~CXKeyStringNumberBlock();

public:
	long  m_nBeginPos;
	long  m_nEndPos;
	long m_nNumber;
};

typedef CTLinkListEx<CXKeyStringNumberBlock> CXKeyStringNumberBlocks;

typedef CTLinkListEx<CXKeyStringBlock> CXKeyStringBlocks;

class CXKeyStringParser : public CXKeyStringBlocks
{
public:
	CXKeyStringParser();
	virtual ~CXKeyStringParser();

	static bool g_bRemoveSubKeys;

	//2022-5-10  lijunqing
	static void SetRemoveSubKeys(bool b)	{	g_bRemoveSubKeys = b;	}

public:
	void Parser(const CString &strText, CXKeyMatchRefList *pListKeys);
	void QueryKey(const CString &strText, CXKeyBase *pXKey, CXKeyMatchRefList *pListKeys);

protected:
	CXKeyStringNumberBlocks m_listGapBlocks;

	void ParseKey(CXKeyMatchRef *pXKeyRef,  const CString &strText);
	void ParseKeys(CXKeyMatchRefList *pListKeys,  const CString &strText);
	void SortByPosition();
	void RemoveSubBlock();
	BOOL IsSubBlock(CXKeyStringBlock *pStringKeyBlock);
// 	void ParseGapBlockNumber(const CString &strText);
// 	void ParseGapBlockNumber(CStringNumberBlock *pBlock, const CString &strText);
	void InitNumberBlocks(const CString &strText);
// 	long GetNumber(const CString &strText, long nBeginPos, long nEndPos, CString &strNumber);
	void InitArrayKeyIndex();

	long xkey_get_arabic_number(const CString &strText, long nBeginPos, long nEndPos);
	void AddNumberBlock(long nBeginPos, long nEndPos, long nNumber);
	BOOL SetArrayIndex(CXKeyStringBlock *pNumber, CXKeyStringBlock *pKey);
	
	void RemoveSubKeys(CXKeyMatchRefList *pListKeys);
	CXKeyStringBlock* FindByXKeyMatchRef(CXKeyMatchRef *pXKeyRef);

	void AddNumberXKeys(CXKeyMatchRefList *pListKeys);
};


//2023-2-7  lijunqing
class CXCharNumConfig : public CXKeyMngr
{
private:
	CXCharNumConfig();
	virtual ~CXCharNumConfig();

	static CXCharNumConfig* g_pXCharNumConfig;
	static long g_nXCharNumConfigRef;

public:
	static void Create();
	static void Release();
	static wchar_t* GetRoma();
	static wchar_t* GetChn();
	
public:
	wchar_t m_strRomaKey[40];
	wchar_t m_strChnKey[40];

//XKeyNumConfig.xml
public:
	virtual void InitAfterRead();
	void OpenXKeyNumConfigFile();
};