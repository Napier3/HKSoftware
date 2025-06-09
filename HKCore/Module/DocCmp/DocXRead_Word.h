//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//˽�г�Ա����
private:
	MSWord::_Application m_WordApp;

//˽�г�Ա�������ʷ���
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

