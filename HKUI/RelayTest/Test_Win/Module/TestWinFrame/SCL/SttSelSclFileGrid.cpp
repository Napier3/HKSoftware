#include "SttSelSclFileGrid.h"
#include "../../../../61850/Module/SCL/SclFileMngr/XSclFileMngr.h"
#include "../../../../Module/API//FileApi.h"
#include"../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../ReportView/XLangResource_PowerTestWin.h"
CSttSelSclFileGrid::CSttSelSclFileGrid(QWidget* pparent):QExBaseListGridBase(pparent)
{
}

CSttSelSclFileGrid::~CSttSelSclFileGrid()
{

}

void CSttSelSclFileGrid::InitGrid()
{
 	InitGridTitle();
	m_pSelectSclFileDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,m_pSelectSclFileDelegate);

#ifdef _PSX_QT_LINUX_
	SetDefaultRowHeight(50);
#endif
	SetEditable(TRUE);
	setWordWrap(true);
}

void CSttSelSclFileGrid::InitGridTitle()
{
	CString astrGridTitle[STTSELSCLFILE_GRID_COLS];
	int iGridWidth[STTSELSCLFILE_GRID_COLS]={60, 200,350, 100};
	astrGridTitle[0] = /*_T("选择")*/g_sLangTxt_Select;
	xlang_GetLangStrByFile(astrGridTitle[0],"sSelect");
	astrGridTitle[1] = /*_T("文件名称")*/g_sLangTxt_Native_FileName;
	xlang_GetLangStrByFile(astrGridTitle[1],"sFileName");
	astrGridTitle[2] = /*_T("文件路径")*/g_sLangTxt_FilePath;
	xlang_GetLangStrByFile(astrGridTitle[2],"FilePath");
	astrGridTitle[3] = /*_T("文件大小")*/g_sLangTxt_FileSize;
	xlang_GetLangStrByFile(astrGridTitle[3],"FileSize");
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STTSELSCLFILE_GRID_COLS);
}

void CSttSelSclFileGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != MNGRCLASSID_CXSCLFILEOBJ)
	{
		return;
	}

 	CXSclFileObj *pXSclFileObj = (CXSclFileObj*)pData;

	if (!IsFileExist(pXSclFileObj->m_strSsclPath))
	{
		pXSclFileObj->m_nUse = 0;
		return;
	}

	long nKB_Size = pXSclFileObj->m_nSize / 1024;
	long nM = nKB_Size / 1024;
	long nK = nKB_Size - nM * 1024;
	CString strSize;

	if (nM > 0)
	{
		strSize.Format(_T("%d,%d KB"), nM, nK);
	} 
	else if (nK > 0)
	{
		strSize.Format(_T("%d KB"), nK);
	}
	else
	{
		strSize.Format(_T("%d B"), pXSclFileObj->m_nSize);
	}

	Show_Check(pData,nRow,0,&pXSclFileObj->m_nUse,EndEditCell_SclFileSel);
	Show_StaticString(pData,nRow,1,pXSclFileObj->m_strName);
	Show_StaticString(pData,nRow,2,pXSclFileObj->m_strSclPath);
 	Show_StaticString(pData,nRow,3,strSize);
   	nRow++;
}

void CSttSelSclFileGrid::EndEditCell_SclFileSel(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	CSttSelSclFileGrid *pOwnGrid = (CSttSelSclFileGrid*)pGrid;
	CXSclFileMngr *pCXSclFileMngr = (CXSclFileMngr*)pOwnGrid->GetDatas();

	if (!pCXSclFileMngr->ValidSetSelectState((CXSclFileObj*)pVCellData->pObj))
	{
		emit pOwnGrid->sig_UpdateSelectState();
	} 

	pCXSclFileMngr->SaveSclFileMngrCfg();
}

void CSttSelSclFileGrid::slot_UpdateSelectState()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	DisConnectAll_SigSlot();
	CXSclFileObj *pXSclFileObj = NULL;	
	int nRowIndex = 0;
	POS pos = m_pDatas->GetHeadPosition();

	while (pos != NULL)
	{
		pXSclFileObj = (CXSclFileObj*)m_pDatas->GetNext(pos);
		Show_Check(pXSclFileObj,nRowIndex,0,&pXSclFileObj->m_nUse,EndEditCell_SclFileSel);
		nRowIndex++;
	}

	ConnectAll_SigSlot();
}

void CSttSelSclFileGrid::DisConnectAll_SigSlot()
{
	QExBaseListGridBase::DisConnectAll_SigSlot();
	disconnect(SIGNAL(sig_UpdateSelectState()),this,SLOT(slot_UpdateSelectState()));
}

void CSttSelSclFileGrid::ConnectAll_SigSlot()
{
	if (m_bHasConnectAll_SigSlot)
	{
		return;
	}

	QExBaseListGridBase::ConnectAll_SigSlot();
	connect(this,SIGNAL(sig_UpdateSelectState()),SLOT(slot_UpdateSelectState()));
}