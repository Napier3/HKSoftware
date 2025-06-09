//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DocXRead_Word.h  CDocXRead_Word

#pragma once

#include "DocCmp.h"
#include "DocXReadInterface.h"
#include "../Office/msword9.h"

class CDocXRead_Word : public CDocXReadInterface
{
public:
	CDocXRead_Word();
	virtual ~CDocXRead_Word();

	static void Create();
	static void Release();

//私有成员变量
private:
	MSWord::_Application m_WordApp;

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
	void OpenDocFile(CDocFile *pFile, MSWord::_Document &oDoc);
	void ReadTables(CDocFile *pFile, MSWord::Tables &oTables, MSWord::Paragraph  &oRetParagrap);
	void ReadTable(CDocTable *pTable, MSWord::Table &oTable, MSWord::Paragraph  &oRetParagrap);
	void ReadTable_Cells(CDocTable *pTable, MSWord::Table &oTable, MSWord::Paragraph  &oRetParagrap);

	void ReadRow(CDocRow *pRow, MSWord::Row &oRow, MSWord::Paragraph  &oRetParagraph);
	void ReadCel(CDocCel *pCell, MSWord::Cell &oCell);

	void ReadText(CDocText *pText, MSWord::Range &oRange);
	void GetParagraphPos(MSWord::Paragraph  &oParagraph, long &nStart, long &nEnd);
};

