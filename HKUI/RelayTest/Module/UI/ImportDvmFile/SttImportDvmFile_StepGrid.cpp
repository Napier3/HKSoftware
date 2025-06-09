#include "SttImportDvmFile_StepGrid.h"
#include "../../UI/Module/CommonCtrl_QT/QIecWidgetDelegate.h"
#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../../XLangResource_Native.h"

#define IMPORTDVMFILE_STEP_COLS	2

#define IMPORTDVMFILE_STEP_SELECT   0
#define IMPORTDVMFILE_STEP_STEP		1

CSttImportDvmFile_StepGrid::CSttImportDvmFile_StepGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
	m_pSelect = NULL;
}

CSttImportDvmFile_StepGrid::~CSttImportDvmFile_StepGrid()
{

}

void CSttImportDvmFile_StepGrid::InitGrid()
{
 	QExBaseListGridBase::InitGrid();
	m_pSelect = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,m_pSelect);
}

void CSttImportDvmFile_StepGrid::InitGridTitle()
{
//	CString astrGridTitle[IMPORTDVMFILE_STEP_COLS] = {"选择", "功能"};
	CString astrGridTitle[IMPORTDVMFILE_STEP_COLS] = {g_sLangTxt_Select, g_sLangTxt_Native_function};
	int iGridWidth[IMPORTDVMFILE_STEP_COLS]={40, 120};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, IMPORTDVMFILE_STEP_COLS);
}

void CSttImportDvmFile_StepGrid::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	DisConnectAll_SigSlot();
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(0);
		return;
	}

	m_pDatas = pDatas;
	CExBaseObject *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt中不包括标题行
	long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行
	SetRowCount(nCalRows, bResetScrollBars);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nCalRows, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

void CSttImportDvmFile_StepGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CSttItems *pItems = (CSttItems *)pData;
	Show_Check(pItems, nRow, IMPORTDVMFILE_STEP_SELECT, &pItems->m_nSelect); 
	Show_StaticString(pItems, nRow, IMPORTDVMFILE_STEP_STEP, &pItems->m_strName);
	nRow++;
}

//bReset = 1：表示重新显示白色。
void CSttImportDvmFile_StepGrid::Update_ShowCurr(CExBaseObject *pData, BOOL bReset)
{
	long nRow = GetDataRow(pData);

	if (!bReset)
	{	
		QColor crBlue(0,255,255);  //青色
		SetItemBkColour(nRow, IMPORTDVMFILE_STEP_SELECT, crBlue);
		SetItemBkColour(nRow, IMPORTDVMFILE_STEP_STEP, crBlue);

		long nRowCount = rowCount();

		if (nRowCount >= nRow + 5)
		{
			nRow += 5;
		}

		QTableWidgetItem *pItem = item(nRow, 0);
		QModelIndex oIndex = indexFromItem(pItem);
		scrollTo(oIndex);
	}
	else
	{
		QColor crWhite(255,255,255);
		SetItemBkColour(nRow, IMPORTDVMFILE_STEP_SELECT, crWhite);
		SetItemBkColour(nRow, IMPORTDVMFILE_STEP_STEP, crWhite);
	}
}