// WordQueryTool.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_WORDQUERYTOOL_H__)
#define _WORDQUERYTOOL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WordBaseClass.h"
#include "..\MemBuffer\BufferBase.h"
#include "..\BaseClass\ExBaseList.h"

#define WQCLASSID_BASECLASS          (CLASSID_BASECLASS   + 0X00100000)
#define WQCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00100000)

#define WQCLASSID_STRING               (WQCLASSID_BASECLASS   + 0X00000000)
#define WQCLASSID_STRINGS             (WQCLASSID_EXLISTCLASS + 0X00000001)
#define WQCLASSID_TABLE                (WQCLASSID_EXLISTCLASS + 0X00000002)
#define WQCLASSID_DOCQUERY         (WQCLASSID_EXLISTCLASS + 0X00000003)

class CWordString : public CExBaseObject
{
public:
	CWordString()	{};
	virtual ~CWordString()	{};

public:
	virtual UINT GetClassID() {        return WQCLASSID_STRING;                               }
};

class CWordStrings : public CExBaseList
{
public:
	CWordStrings(long nStart, long nEnd);
	CWordStrings();
	virtual ~CWordStrings();
	
public:
	virtual UINT GetClassID() {        return WQCLASSID_STRINGS;                               }

public:
	void SetStringPos(long nStart, long nEnd)		{	m_nStart = nStart;	m_nEnd = nEnd;	}
	void GetStringPos(long &nStart, long &nEnd)	{	nStart = m_nStart;	nEnd = m_nEnd;	}
	long GetStart()											{	return m_nStart;								}
	long GetEnd()												{	return m_nEnd;								}
	void GetStringBuffer(MSWord::_Document &doc, CBufferBase &oBuffer);
	
protected:
	long m_nStart;
	long m_nEnd;

};

class CWordTable : public CExBaseList
{
public:
	CWordTable(long nTableIndex);
	CWordTable();
	virtual ~CWordTable();
	
public:
	virtual UINT GetClassID() {        return WQCLASSID_TABLE;                               }

public:
	void SetTableIndex(long nTableIndex)		{	m_nTableIndex = nTableIndex;	}
	void GetTableIndex(long &nTableIndex)		{	nTableIndex = m_nTableIndex;	}
	long GetTableIndex()								{	return m_nTableIndex;				}
	
protected:
	long m_nTableIndex;

};

class CWordDocQueryTool : public CExBaseList
{
public:
	CWordDocQueryTool(MSWord::_Document &oDoc);
	CWordDocQueryTool();
	virtual ~CWordDocQueryTool();

public:
	virtual UINT GetClassID() {        return WQCLASSID_DOCQUERY;                               }

public:
	virtual BOOL DocQuery(MSWord::_Document &oDoc);

protected:
	MSWord::_Document m_oDoc;
	virtual CWordStrings* CreateWordStrings(long nStart, long nEnd);
	virtual CWordTable* CreateWordTable(long nIndex);

};


#endif // !defined(_WORDQUERYTOOL_H__)
