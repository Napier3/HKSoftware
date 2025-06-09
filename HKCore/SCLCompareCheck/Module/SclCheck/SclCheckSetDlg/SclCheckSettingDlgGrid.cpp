#include "StdAfx.h"
#include "SclCheckSettingDlgGrid.h"
#include "..\..\SclCheckDataMngr\SclCheckObjectsSet.h"

CSclDlgSetGridBase::CSclDlgSetGridBase()
{
	m_nOldSclIecCfgClassID = 0;
	m_nAdjustBeginCol = 1;
}

CSclDlgSetGridBase::~CSclDlgSetGridBase()
{

}

void CSclDlgSetGridBase::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CSclDlgSetGridBase::ShowDatas(CExBaseList *pDatas)
{
	CExBaseListGrid::ShowDatas(pDatas);
}

CDataType* CSclDlgSetGridBase::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CSclCheckMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}

const int g_nSclSchemaCols = 5;
CString g_astrSclSchemaTitle[g_nSclSchemaCols] = {_T("序号"),_T("选择"),_T("检测项目内容"),_T("版本选择") ,_T("xml解析方法")};
const int g_iSclSchemaWidth[g_nSclSchemaCols]={50 ,50 ,400 ,80 ,80 };

const int g_nSclVirLoopCols = 4;
CString g_astrSclVirLoopTitle[g_nSclVirLoopCols] = {_T("序号"),_T("选择"),_T("检测项目内容"),_T("标记方式")};
const int g_iSclVirLoopWidth[g_nSclVirLoopCols]={50,50, 400,80};

const int g_nAddTempsFileCols = 3;
CString g_astrAddTempsFileTitle[g_nAddTempsFileCols] = {_T("序号"),_T("文件夹名称"),_T("待入库文件路径")};
const int g_iAddTempsFileWidth[g_nAddTempsFileCols]={50,200, 1800};

const int g_nAddTempsDataTypeCols = 3;
CString g_astrAddTempsDataTypeTitle[g_nAddTempsDataTypeCols] = {_T("序号"),_T("选择"),_T("选择入库的数据类型")};
const int g_iAddTempsDataTypeWidth[g_nAddTempsDataTypeCols]={50,50, 400};

const int g_nSclCheckColsEmpty1 = 1;
const CString g_astrSclCheckTitleEmpty1[g_nSclCheckColsEmpty1] = {_T("无异常")};
const int g_iSclCheckWidthEmpty1[g_nSclCheckColsEmpty1]={60};

CSclCheckSettingDlgGrid::CSclCheckSettingDlgGrid()
{
	m_nAdjustBeginCol = 2;
}

CSclCheckSettingDlgGrid::~CSclCheckSettingDlgGrid()
{
}

void CSclCheckSettingDlgGrid::InitGridTitle()
{

	if (m_pDatas == NULL)
	{
		SetColumnCount(1);
		SetRowCount(1);
		return;
	}

	if (m_nOldSclIecCfgClassID == m_pDatas->GetClassID())
	{
		return;
	}

	m_nOldSclIecCfgClassID = m_pDatas->GetClassID();
	long nCols = 1;
	const CString *pstrTitle = NULL;
	const int *pnWidth = NULL;


	switch (m_nOldSclIecCfgClassID)
	{

	case SCLCLASSID_CSCHEMACHECKS:
		nCols = g_nSclSchemaCols;
		pstrTitle = g_astrSclSchemaTitle;
		pnWidth = g_iSclSchemaWidth;
		break;

	case SCLCLASSID_CDLT860MODELCHECKS:
		nCols = g_nSclVirLoopCols;
		pstrTitle = g_astrSclVirLoopTitle;
		pnWidth = g_iSclVirLoopWidth;
		break;

	case SCLCLASSID_CPROJAPPMODELCHECKS:
		nCols = g_nSclVirLoopCols;
		pstrTitle = g_astrSclVirLoopTitle;
		pnWidth = g_iSclVirLoopWidth;
		break;

	case SCLCLASSID_CVIRLOOPCHECKS:
		nCols = g_nSclVirLoopCols;
		pstrTitle = g_astrSclVirLoopTitle;
		pnWidth = g_iSclVirLoopWidth;
		break;

	case SCLCLASSID_ADDTEMPLATESFILES:
		nCols = g_nAddTempsFileCols;
		pstrTitle = g_astrAddTempsFileTitle;
		pnWidth = g_iAddTempsFileWidth;
		break;

	case SCLCLASSID_ADDTEMPLATESDATATYPES:
		nCols = g_nAddTempsDataTypeCols;
		pstrTitle = g_astrAddTempsDataTypeTitle;
		pnWidth = g_iAddTempsDataTypeWidth;
		break;


	default:
		nCols = g_nSclCheckColsEmpty1;
		pstrTitle = g_astrSclCheckTitleEmpty1;
		pnWidth = g_iSclCheckWidthEmpty1;
		break;
	}


	SetColumnCount(nCols);

	CExBaseListGrid::InitGridTitle(pstrTitle, pnWidth, nCols);
}

void CSclCheckSettingDlgGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	switch (nClassID)
	{
	case SCLCLASSID_CCHECKOBJECT:
		ShowData_CheckType((CExBaseList*)pData, nRow);
		break;
	case SCLCLASSID_SCHEMACCHECKOBJECT:
		ShowData_SchemaCheckType((CExBaseList*)pData, nRow);
		break;
	case SCLCLASSID_ADDTEMPLATESFILE:
		ShowData_AddFile((CExBaseList*)pData, nRow);
		break;
	case SCLCLASSID_ADDTEMPLATESELEMENT:
		ShowData_DataType((CExBaseList*)pData, nRow);
		break;
	}

	nRow++;
}

void CSclCheckSettingDlgGrid::ShowData_CheckType(CExBaseList *pCheckObjec,int nRow)
{
	//_T("序号")
	Show_Index(pCheckObjec, nRow, 0);

	//_T("选择")
	Show_Check(pCheckObjec, nRow, 1, &(((CCheckObject*)pCheckObjec)->m_nChoose));

	//_T("检测内容描述信息")
	Show_StaticString(pCheckObjec, nRow, 2, &(((CCheckObject*)pCheckObjec)->m_strName));

	// _T("标记类型")
	Show_DataType_Val(pCheckObjec, nRow, 3, "checkObjectSetDataTypeID",&(((CCheckObject*)pCheckObjec)->m_strErrorType) );

}

void CSclCheckSettingDlgGrid::ShowData_SchemaCheckType(CExBaseList *pCheckObjec,int nRow)
{
	//_T("序号")
	Show_Index(pCheckObjec, nRow, 0);

	//_T("选择")
	Show_Check(pCheckObjec, nRow, 1, &(((CSchemaCheckObject*)pCheckObjec)->m_nChoose));

	//_T("检测内容描述信息")
	Show_StaticString(pCheckObjec, nRow, 2, &(((CSchemaCheckObject*)pCheckObjec)->m_strName));

	// _T("SCL版本")
	Show_DataType_Val(pCheckObjec, nRow, 3, "schemaCheckVertionTypeID",&(((CSchemaCheckObject*)pCheckObjec)->m_strVertionType) );

	// _T("xml解析方法")
	Show_DataType_Val(pCheckObjec, nRow, 4, "schemaCheckMethodTypeID",&(((CSchemaCheckObject*)pCheckObjec)->m_strCheckType) );
}

void CSclCheckSettingDlgGrid::ShowData_AddFile(CExBaseList *pAddTempsFile,int nRow)
{
	//_T("序号")
	Show_Index(pAddTempsFile, nRow, 0);

	//_T("文件夹名称")
	Show_StaticString(pAddTempsFile, nRow, 1, &(pAddTempsFile->m_strName));

	//_T("待入库文件路径")
	Show_StaticString(pAddTempsFile, nRow, 2, &(pAddTempsFile->m_strID));

}

void CSclCheckSettingDlgGrid::ShowData_DataType(CExBaseList *pDataType,int nRow)
{
	//_T("序号")
	Show_Index(pDataType, nRow, 0);

	//_T("选择")
	Show_Check(pDataType, nRow, 1, &(((CAddTempsElement*)pDataType)->m_nChoose));

	//_T("选择入库的数据类型")
	Show_StaticString(pDataType, nRow, 2, &(((CAddTempsElement*)pDataType)->m_strID));
}

const int g_nSclImportCols = 3;
CString g_astrSclImportTitle[g_nSclImportCols] = {_T("序号"),_T("文件用途"),_T("文件路径")};
const int g_iSclImportWidth[g_nSclImportCols]={50 ,150 ,600 };


CSclImportDlgGrid::CSclImportDlgGrid()
{
	m_nAdjustBeginCol = 2;

}

CSclImportDlgGrid::~CSclImportDlgGrid()
{
}

void CSclImportDlgGrid::InitGridTitle()
{

	if (m_pDatas == NULL)
	{
		SetColumnCount(1);
		SetRowCount(1);
		return;
	}

	if (m_nOldSclIecCfgClassID == m_pDatas->GetClassID())
	{
		return;
	}

	m_nOldSclIecCfgClassID = m_pDatas->GetClassID();
	long nCols = 1;
	const CString *pstrTitle = NULL;
	const int *pnWidth = NULL;


	switch (m_nOldSclIecCfgClassID)
	{

	case SCLCLASSID_CCHECKPATHS:
		nCols = g_nSclImportCols;
		pstrTitle = g_astrSclImportTitle;
		pnWidth = g_iSclImportWidth;
		break;


	default:
		nCols = g_nSclCheckColsEmpty1;
		pstrTitle = g_astrSclCheckTitleEmpty1;
		pnWidth = g_iSclCheckWidthEmpty1;
		break;
	}


	SetColumnCount(nCols);

	CExBaseListGrid::InitGridTitle(pstrTitle, pnWidth, nCols);
}

void CSclImportDlgGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();

	switch (nClassID)
	{
	case SCLCLASSID_SINGLEPATH:
		ShowData_ImportPathType((CExBaseList*)pData, nRow);
		break;
	}

	nRow++;
}

void CSclImportDlgGrid::ShowData_ImportPathType(CExBaseList *pSinglePath,int nRow)
{
	//_T("序号")
	Show_Index(pSinglePath, nRow, 0);

	//_T("文件用途")
	Show_StaticString(pSinglePath, nRow, 1, &(((CSinglePath*)pSinglePath)->m_strName));

	//_T("文件路径")
	Show_StaticString(pSinglePath, nRow, 2, &(((CSinglePath*)pSinglePath)->m_strPath));

}