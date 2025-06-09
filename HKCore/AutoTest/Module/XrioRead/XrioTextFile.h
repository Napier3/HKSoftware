#pragma once

#include "XrioCfgMngrGlobal.h"
#include "../../../Module/MemBuffer/BufferBase.h"

#define XRIO_TEXT_WORD_MAX_LEN  64

#define RIO_TEXT_FILE_FILTER     _T("rio file(*.rio)|*.rio||")
#define RIO_TEXT_FILE_POSTFIX   _T("rio")

class CXrioAttr : public CExBaseObject
{
public:
	CXrioAttr(){};
	CXrioAttr(const char *pszText);
	virtual ~CXrioAttr();

public:
	virtual UINT GetClassID() {    return XRIOCLASSID_RIO_ATTR;   }

};


class CXrioData : public CExBaseList
{
public:
	CXrioData(){};
	CXrioData(const char *pszText);
	virtual ~CXrioData();

public:
	virtual UINT GetClassID() {    return XRIOCLASSID_RIO_DATA;   }
	CString operator[](long nIndex)	{	return GetAttr(nIndex);	}
	CString GetAttr(long nIndex);
	BOOL GetAttr(long nIndex, CString &strValue);

};

class CXrioGroup : public CExBaseList
{
public:
	CXrioGroup(){};
	CXrioGroup(const char *pszText);
	virtual ~CXrioGroup();

	CString GetData(const CString &strID);
	BOOL GetData(const CString &strID, CString &strValue);

public:
	virtual UINT GetClassID() {    return XRIOCLASSID_RIO_GROUP;   }
};

class CXrioTextFile : public CXrioGroup
{
public:
	CXrioTextFile();
	virtual ~CXrioTextFile();

	CString m_strRioFile;

public:
	virtual UINT GetClassID() {    return XRIOCLASSID_RIO_TEXTFILE;   }
	
	BOOL ReadXrioTextFile(CWnd *pParentWnd);
	BOOL WriteXrioTextFile(CWnd *pParentWnd);

	BOOL ReadXrioTextFile(const CString &strTextFile);
	BOOL WriteXrioTextFile(const CString &strTextFile);

protected:
	CExBaseObject* ParseLine(char *pszLine);
	void ParseGroupChildren(CBufferBase &oBuffer, CXrioGroup *pGroup);
	void ParseData(CXrioData *pData, char *pszLine);
	BOOL ReadOneTextWord(char **ppszLine, char *pszTextWord);
	void Offset(char **ppszLine);
};

