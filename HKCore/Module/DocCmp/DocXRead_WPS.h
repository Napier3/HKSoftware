//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//˽�г�Ա����
private:
	WPS::_Application m_WordApp;

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
	void OpenDocFile(CDocFile *pFile, WPS::_Document &oDoc);
	void ReadTables(CDocFile *pFile, WPS::Tables &oTables, WPS::Paragraph  &oRetParagrap);
	void ReadTable(CDocTable *pTable, WPS::Table &oTable, WPS::Paragraph  &oRetParagrap);
	void ReadTable_Cells(CDocTable *pTable, WPS::Table &oTable, WPS::Paragraph  &oRetParagrap);
	void ReadRow(CDocRow *pRow, WPS::Row &oRow, WPS::Paragraph  &oRetParagraph);
	void ReadCel(CDocCel *pCell, WPS::Cell &oCell);

	void ReadText(CDocText *pText, WPS::Range &oRange);
	void GetParagraphPos(WPS::Paragraph  &oParagraph, long &nStart, long &nEnd);
};

