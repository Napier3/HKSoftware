#pragma once

#include "PdfTextParse.h"
#include "../DataMngr/DvmLogicDevice.h"
#include "../DataMngr/DvmDataset.h"
#include "ReadXmlData.h"
#include "PdfXmlData.h"
#include "PdfConfigData.h"
#include "PdfDBInfo.h"
#include <vector>
#include "SetsFileManualConfirmInterface.h"

#define SETS_TITLE_ID_PARAMETER _T("设备参数")
#define SETS_TITLE_ID_SETTING     _T("保护定值")
#define SETS_TITLE_ID_CTRL           _T("控制字")
#define SETS_TITLE_ID_ENA             _T("软压板")
#define SETS_TITLE_ID_MATRIX       _T("跳闸矩阵")
#define SETS_TITLE_ID_PROT			_T("保护")
#define SETS_TITLE_ID_SETTING2    _T("定值")

BOOL range_IsIntersect(float fMin, float fMax, float fDestMin, float fDestMax);


class CPdfXmlStringRow : public CExBaseList
{
public:
	CPdfXmlStringRow();
	virtual ~CPdfXmlStringRow();

	float m_fVpos;  //行的垂直位置
	float m_fHeight;	//记录第一行高

	long m_nCols;

public:
	long InitHeadRow();

	void InitColIndex(CPdfXmlStringRow *HeadRow);
	void InitColIndex_1(CPdfXmlStringRow *HeadRow);

	void MergeCols(CPdfXmlStringRow *pHeadRow);  //合并列
	void MergeCols_1(); 

	void AddEmptyCol(CPdfXmlStringRow *pHeadRow);  //增加空的列
	void AddEmptyCol_1(CPdfXmlStringRow *pHeadRow);  //增加空的列
	void AddEmptyCol_Data(int iStart, int iCount, CPdfXmlData *pNext, CPdfXmlStringRow *pHeadRow, bool bAfter);

	BOOL IsSameLine(CPdfXmlStringRow *pOneRow);
	BOOL IsInvalidLine(CString strKey);

	BOOL IsLineData(CPdfXmlData *pData);
	BOOL AddSameLineData(CPdfXmlData *pData);

	void SplitKey(vector<CString> *pVecKey, const CString &strKey, const CString strSpace);

	void ReSetRowRang(CPdfXmlStringRow *pRow);
	BOOL IsHeadRowLeft(CPdfXmlStringRow *pRow);

public:
	virtual UINT GetClassID() {    return PDFPCLASSID_ROW;   }
	virtual BSTR GetXmlElementKey()  {      return CPdfParseXmlRWKeys::RowKey();     }
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual long ValCmp(CBaseObject* pRightObj);

};

class CPdfXmlStringTable : public CExBaseList
{
public:
	CPdfXmlStringTable();
	virtual ~CPdfXmlStringTable();

public:
	void ParseTable();

	CString m_strIdentify;		//归类
	CString m_strIndetName;		//归类名称,跳闸矩阵和保护定值归类不同，但归类的名称相同

	int m_iNameHeadCol;
	int m_iDWHeadCol;
	int m_iValueHeadCol;
	
	BOOL m_AddTile;

private:
	long m_nCols;

	void ProssHeadRow();
	BOOL IsHeadRowLeft();

public:
	virtual UINT GetClassID() {    return PDFPCLASSID_TABLE;   }
	virtual BSTR GetXmlElementKey()  {      return CPdfParseXmlRWKeys::TableKey();     }
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

};

class CPdfXmlStringTables : public CExBaseList
{
public:
	CPdfXmlStringTables();
	virtual ~CPdfXmlStringTables();

	
public:
	virtual UINT GetClassID() {    return PDFPCLASSID_TABLES;   }
	virtual BSTR GetXmlElementKey()  {      return CPdfParseXmlRWKeys::TablesKey();     }

};


class CPdfXmlStringTableParse : public CExBaseList
{
public:
	CPdfXmlStringTableParse();
	virtual ~CPdfXmlStringTableParse();

	void InitRows(CExBaseList *pStringList);
	void ProssRows();

	void ParseTableData();

	CExBaseList *GetAllTable(){ return &m_listTable; }

	CPdfConfigData *m_pPdfConfig;

protected:
	CPdfXmlStringRow *m_LastRow;
	BOOL AddToRow(CPdfXmlData *pData);	
	CPdfXmlStringRow * FindRow(CPdfXmlData *pData);

	//删除特殊字符行
	void DelTilteRows();

	//删除无效标题行标题
	void DelTilteName();
	void DelTilteRows(CString strTile);

	//删除无效行标题
	void DelRowName();
	void DelDataRows(CString strRow);

	void DelSameLine();		
	void DelSameTable();
	int IsHeadRowCheck(CPdfXmlStringRow *pHeadRow);

	void MergeRows();		//合并行数据
	void MergeCols();		//合并列数据

	CPdfXmlStringTables m_listTable;  //全部的表格
	void AdjRowsToTables();  //将各行都调整到表格中

public:
	virtual UINT GetClassID() {    return PDFPCLASSID_TABLE;   }
	virtual BSTR GetXmlElementKey()  {      return CPdfParseXmlRWKeys::TableKey();     }

	void Debug_SaveRowsFile();
	void Debug_SaveTablesFile();
};

//20240312 huangliang 设置表归属
inline void set_table_identify(CPdfXmlStringTable *pXmlTable, const CString &strKey)
{
	pXmlTable->m_strIdentify = strKey;
	pXmlTable->m_strIndetName = strKey;
	if(strKey == TALBE_TYPE_MATRIX)
	{
		pXmlTable->m_strIndetName = SETS_TITLE_ID_SETTING;
	}
}

class CPdfXmlParseSets : public CPdfTextParse
{
public:
	CPdfXmlParseSets(void);
	virtual ~CPdfXmlParseSets(void);

	CPdfXmlStringTableParse m_oPdfTable;  //lijunqing 2023-7-19

	CDvmLogicDevice *m_pDestLogicDevice;

	void AddDatasetTitle(const CString &strTitle)
	{
		m_astrDatasetTitle.Add(strTitle);
	}

	void InitKeys();

	bool m_bCorrect;
	CSetsFileManualConfirmInterface *m_pManualFrm;	//20240312 huangliang 用户确认对话框指针

public:
	virtual BOOL ParsePdfFile(const CString &strFile, BOOL bSaveTxtFile=TRUE);

protected:
	CStringArray m_astrDatasetTitle;	

	CPdfConfigData m_oPdfConfig;

	//解析xml数据到缓存表格中
	void ParseLineData(CExBaseList* pStringList);

	void SetTableIdentify();

	void ParseInDestLogicDevice();

	void ParseTableHead(CPdfXmlStringTable* pXmlTable);
	void ParseTableHeadRow(CExBaseList* listXmlRow);

	void ParseTableInDestLogicDevice(CPdfXmlStringTable* pXmlTable);

	int ParseTableNameHead(CPdfXmlStringRow* listXmlRow);
	int ParseTableDWHead(CPdfXmlStringRow* listXmlRow);
	int ParseTableValueHead(CPdfXmlStringRow* listXmlRow);
	int ParseTableColHead(CPdfXmlStringRow* listXmlRow, const CString &strKey);

	void ParseTableColData(CPdfXmlStringTable* pXmlTable);

protected:
	CDvmDataset *m_pCurrDataset;
	CPdfDBInfo m_PdfDBInfos;
	CPdfDBTable *m_PdfDBInfo;

	BOOL CheckTableIdentify(CPdfXmlStringTable* pXmlTable);
	void QueTableHead(CPdfXmlStringTable* pXmlTable);
	BOOL IsWow64();


};
