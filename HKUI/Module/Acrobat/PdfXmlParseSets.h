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

#define SETS_TITLE_ID_PARAMETER _T("�豸����")
#define SETS_TITLE_ID_SETTING     _T("������ֵ")
#define SETS_TITLE_ID_CTRL           _T("������")
#define SETS_TITLE_ID_ENA             _T("��ѹ��")
#define SETS_TITLE_ID_MATRIX       _T("��բ����")
#define SETS_TITLE_ID_PROT			_T("����")
#define SETS_TITLE_ID_SETTING2    _T("��ֵ")

BOOL range_IsIntersect(float fMin, float fMax, float fDestMin, float fDestMax);


class CPdfXmlStringRow : public CExBaseList
{
public:
	CPdfXmlStringRow();
	virtual ~CPdfXmlStringRow();

	float m_fVpos;  //�еĴ�ֱλ��
	float m_fHeight;	//��¼��һ�и�

	long m_nCols;

public:
	long InitHeadRow();

	void InitColIndex(CPdfXmlStringRow *HeadRow);
	void InitColIndex_1(CPdfXmlStringRow *HeadRow);

	void MergeCols(CPdfXmlStringRow *pHeadRow);  //�ϲ���
	void MergeCols_1(); 

	void AddEmptyCol(CPdfXmlStringRow *pHeadRow);  //���ӿյ���
	void AddEmptyCol_1(CPdfXmlStringRow *pHeadRow);  //���ӿյ���
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

	CString m_strIdentify;		//����
	CString m_strIndetName;		//��������,��բ����ͱ�����ֵ���಻ͬ���������������ͬ

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

	//ɾ�������ַ���
	void DelTilteRows();

	//ɾ����Ч�����б���
	void DelTilteName();
	void DelTilteRows(CString strTile);

	//ɾ����Ч�б���
	void DelRowName();
	void DelDataRows(CString strRow);

	void DelSameLine();		
	void DelSameTable();
	int IsHeadRowCheck(CPdfXmlStringRow *pHeadRow);

	void MergeRows();		//�ϲ�������
	void MergeCols();		//�ϲ�������

	CPdfXmlStringTables m_listTable;  //ȫ���ı��
	void AdjRowsToTables();  //�����ж������������

public:
	virtual UINT GetClassID() {    return PDFPCLASSID_TABLE;   }
	virtual BSTR GetXmlElementKey()  {      return CPdfParseXmlRWKeys::TableKey();     }

	void Debug_SaveRowsFile();
	void Debug_SaveTablesFile();
};

//20240312 huangliang ���ñ����
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
	CSetsFileManualConfirmInterface *m_pManualFrm;	//20240312 huangliang �û�ȷ�϶Ի���ָ��

public:
	virtual BOOL ParsePdfFile(const CString &strFile, BOOL bSaveTxtFile=TRUE);

protected:
	CStringArray m_astrDatasetTitle;	

	CPdfConfigData m_oPdfConfig;

	//����xml���ݵ���������
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
