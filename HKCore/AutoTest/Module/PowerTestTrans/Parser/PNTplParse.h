#pragma once

#include "..\..\..\..\Module\MemBuffer\EquationBuffer.h"
#include "PNTplRoot.h"
#include "PNTplElement.h"

class CPNTplParse
{
public:
	CPNTplParse();
	virtual ~CPNTplParse();

public:
	BOOL GetTempFilePath(CString &strPath);
	BOOL ReadFromTemplate(const CString &strFile);
	CPNTplRoot* GetRoot()	{	return &m_oRoot;	}
	BOOL Save_PNTpleFile();

protected:
	CBufferBase m_oBuffer;
	CPNTplRoot m_oRoot;

	long m_nCurrParsePos;
	char *m_pBuffer;


protected:
	void ParseElement(int iLeft, int iRight, CExBaseList *m_pCurrElement, char *_pTplBuff, int nLen);

	UINT GetElementKey(CStringA &strKey, char *_pBuff);
	BOOL IsChar(char ch);
	void Offset(char* _pBuffer);
	void ParseElement_Ex(CExBaseList *_pCurrElement, char* _pBuffer, long nLen);
	void ParseElement_CDATA(CExBaseList *_pCurrElement, char* _pBuffer, long nLen);
	BOOL IsKey_Name(const CStringA &strText);
	void ParseGroup(CPNTplGroup *pGroup, long nBegin, long nEnd, char* _pBuffer);

	void Parse_Text(long &iLeft, CPNTplElement *pCurrElement, char* _pBuffer);
	void Parse_GroupAndEquation(long &iLeft, long &iRight, CPNTplElement *pCurrElement, char* _pBuffer);
	void NewEquation(CExBaseList *pParentElement, const CStringA &strName, char *pBuffer, long nLen );
	void AdjustAllGroupKeys(CPNTplRoot *pPNTplRoot); //解析完成后，调整格式
	BOOL IsNeedAdjust(CExBaseObject *pElement);
	void AdjustElementKeys(CPNTplElement *pElement);

protected:
	BOOL Parse_PN_Tpl(char *_pTplBuff);
	BOOL Parse_PN_Tpl_ex(char *_pTplBuff, long nLen);
};
