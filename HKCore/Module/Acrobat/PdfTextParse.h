#pragma once

#include "../MemBuffer/ExpandMemBuf.h"
#include "../DataMngr/DvmLogicDevice.h"
#include "PdfTextLine.h"

#define PDEF_PARSE_MAX_KEY_COUNT  200

class CPdfTextParse : public CExBaseList
{
public:
	CPdfTextParse();
	virtual ~CPdfTextParse();

public:
	virtual BOOL ParsePdfFile(const CString &strFile, BOOL bSaveTxtFile=TRUE);
	virtual void Parse(CExpandMemBuf *pBuffer);

protected:
	virtual BOOL IsLineDatasetTitle(CPdfTextLine *pLine, CString &strKey)	{	return FALSE;	}

	void ProcessTextData();
	void ProcessTextData(CPdfTextLine *pLine);
	CPdfTextData* ProcessTextData(CPdfTextData *pData);
	BOOL IsKey(const CString &strText);

protected:
	long m_nKeyCount;
	char m_ppszGlobalKey[PDEF_PARSE_MAX_KEY_COUNT][24];
	long m_nInvalidKeyCount;
	char m_ppszInvalidGlobalKey[PDEF_PARSE_MAX_KEY_COUNT][24];
	long m_nFormatKeyCount;
	char m_ppszFormatGlobalKey[PDEF_PARSE_MAX_KEY_COUNT][24];
	long m_nMergeKeyCount;
	char m_ppszMergeGlobalKey[PDEF_PARSE_MAX_KEY_COUNT][24];

public:
	void OpenKeyTextFile(const CString &strFile);
	void OpenInvalidKeyTextFile(const CString &strFile);
	void OpenFormatKeyTextFile(const CString &strFile);
	void OpenMergeKeyTextFile(const CString &strFile);

protected:
	void OpenKeyTextFile(const CString &strFile, char ppKey[PDEF_PARSE_MAX_KEY_COUNT][24], long &nKeyCount);

protected:
	virtual void FormatEx(CBufferBase *pBuffer);

};
