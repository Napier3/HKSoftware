//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocXRead_WPS.h  CDocXRead_WPS

#pragma once

#include "DocCmp.h"
#include "DocXReadInterface.h"
#include "../Office/WPS.h"

class CDocXRead_WPS : public CDocXReadInterface
{
public:
	CDocXRead_WPS();
	virtual ~CDocXRead_WPS();

	static void Create();
	static void Release();

//私有成员变量
private:
	WPS::_Application m_WordApp;

//私有成员变量访问方法
public:
	virtual BOOL GetWordApp(BOOL bShow=FALSE);
	virtual void QuitApp();
	virtual void ShowApp(long nShow);

	virtual BOOL ReadDocFile(CDocCmp *pDocCmp, const CString &strFile1, const CString strFile2);
	virtual BOOL DocToXml(const CString &strFile);

protected:
	BOOL OpenDocFile(CDocCmp *pDocCmp, const CString &strFile);
	BOOL OpenDocFile(CDocFile *pFile, const CString &strFile);
	void OpenDocFile(CDocFile *pFile, WPS::_Document &oDoc);
	void ReadTables(CDocFile *pFile, WPS::Tables &oTables, WPS::Paragraph  &oRetParagrap);
	void ReadTable(CDocTable *pTable, WPS::Table &oTable, WPS::Paragraph  &oRetParagrap);
	void ReadTable_Cells(CDocTable *pTable, WPS::Table &oTable, WPS::Paragraph  &oRetParagrap);
	void ReadRow(CDocRow *pRow, WPS::Row &oRow, WPS::Paragraph  &oRetParagraph);
	void ReadCel(CDocCel *pCell, WPS::Cell &oCell);

	void ReadText(CDocText *pText, WPS::Range &oRange);
	void GetParagraphPos(WPS::Paragraph  &oParagraph, long &nStart, long &nEnd);
};

