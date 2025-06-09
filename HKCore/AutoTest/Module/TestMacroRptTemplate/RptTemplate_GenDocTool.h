#pragma once
#include "RptTemp_TestMacroUiRpt.h"
#include "..\..\..\Module\Office\msword9.h"

class CRptTemplate_GenDocTool
{
public:
	CRptTemplate_GenDocTool(void);
	virtual ~CRptTemplate_GenDocTool(void);

	CString m_strXmlFile; //XML报告文件
	CString m_strSrcRptFile; //word或者wps报告文件的模板，源。带路径
	CString m_strDestRptFile; //word或者wps报告文件，目标。带路径

protected:
	CRptTemp_TestMacroUiRpt m_oRptTemp_TestMacroUiRpt;
	MSWord::_Application m_WordApp;
	MSWord::_Document m_oRptDoc;
	BOOL GetWordApp(BOOL bShow=FALSE);

public:
	void SetDestRptFile(const CString &strDestFile);
	void SetSrcRptFile(const CString &strSrcRptFile);
	void SetXmlFile(const CString &strXmlFile);

	BOOL OpenXmlRptFile(const CString &strXmlRptFile);
	BOOL OpenDocRptFile(const CString &strDocRptFile);
	BOOL SaveDocRptFile(const CString &strFilePath);
	BOOL GenRpt_Word();
	BOOL GenRpt_Word(const CString &strXmlFile, const CString &strDocRptFile);
	BOOL GenRpt_Word_TestMacroUiRpt(CRptTemp_TestMacroUiRpt *pRptRemp_TestMacroUiRpt);
	BOOL GenRpt_Word_Items(CRptTemp_Items *pRptTemp_Items);
	BOOL GenRpt_Word_MacroCharItems(CRptTemp_MacroCharItems *pRptTemp_MacroCharItems);
	BOOL GenRpt_Word_ReportTemplate(CRptTemp_ReportTemplate *pRptTemp_ReportTemplate);
	BOOL GenRpt_Word_Title(CRptTemp_Title *pRptTemp_Title);
	BOOL GenRpt_Word_Grid(CRptTemp_Grid *pRptTemp_Grid);
	BOOL GenRpt_Word_Grid_RowMode(CRptTemp_Grid *pRptTemp_Grid);
	BOOL GenRpt_Word_Grid_ColMode(CRptTemp_Grid *pRptTemp_Grid);

	//合并单元格
	BOOL GenRpt_Word_Grid_MergeCells_RowMode(CRptTemp_Grid *pRptTemp_Grid, MSWord::Table oTable);
	BOOL GenRpt_Word_Grid_MergeCells_ColMode(CRptTemp_Grid *pRptTemp_Grid, MSWord::Table oTable);
	BOOL GenRpt_Word_Grid_MergeCells_RowMode_Head(long nRow, CRptTemp_Head *pRptTemp_Head, MSWord::Table oTable);
	BOOL GenRpt_Word_Grid_MergeCells_RowMode_Row(long nRow, CRptTemp_Row *pRptTemp_Row, MSWord::Table oTable);
	BOOL GenRpt_Word_Grid_MergeCells_ColMode_Head(long nCol, CRptTemp_Head *pRptTemp_Head, MSWord::Table oTable);
	BOOL GenRpt_Word_Grid_MergeCells_ColMode_Col(long nCol, CRptTemp_Col *pRptTemp_Col, MSWord::Table oTable);
	BOOL GenRpt_Word_Grid_MergeCells_Cell(long nRow, long nCol, CRptTemp_Cell *pRptTemp_Cell, MSWord::Table oTable);

	BOOL GenRpt_Word_Head(long nRow, CRptTemp_Head *pRptTemp_Head, MSWord::Table oTable);
	BOOL GenRpt_Word_Row(long nRow, CRptTemp_Row *pRptTemp_Row, MSWord::Table oTable);
	BOOL GenRpt_Word_Col(long nCol, CRptTemp_Col *pRptTemp_Col, MSWord::Table oTable);

	BOOL GenRpt_Word_Cell(long nRow, long nCol, CRptTemp_Cell *pRptTemp_Cell, MSWord::Table oTable);

public:
	//word文档操作	
	BOOL InsertNewPage(); //ftt 2024.12.9
	BOOL InsertPng(const CString &strPngFile);
	BOOL InsertText(const CString &strText, const CString &strHAlignType, const CString &strFont=_T(""), long nBold=0, float fSize=10.5); //ftt 2024.12.19 add strAlignType
	BOOL InsertTitle(const CString &strTitleText, long nTitleLevel);
	MSWord::Table InsertGrid(long nRows, long nCols, long nShowBorders);

	//提示关闭word进程
	BOOL KillWordProgram(BOOL bShowMsg = TRUE);
	void GetTitleLevel(long nTitleLevel, CString &strTitleLevel);
};
