#include "IecCfgGooseDataGrid.h"
#include "..\..\61850\Module\CfgDataMngr\IecCfgGinData.h"

CIecCfgGooseDataGrid::CIecCfgGooseDataGrid( QWidget* pparent ):CIecCfgGinDataGrid(pparent)
{

}

CIecCfgGooseDataGrid::~CIecCfgGooseDataGrid()
{

}

void CIecCfgGooseDataGrid::InitGrid()
{
	QExBaseListGridBase::InitGrid();
	pCtrlBlockSelectDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(0,pCtrlBlockSelectDelegate);
	m_pFiberSelected_DelegBase = new QExBaseListComBoxDelegBase(this);
	setItemDelegateForColumn(2,m_pFiberSelected_DelegBase);
	m_pNdsComCheckDelegate = new QExBaseListCheckBoxDelegate(this);
	setItemDelegateForColumn(4,m_pNdsComCheckDelegate);
	SetEditable(TRUE);
}

void CIecCfgGooseDataGrid::InitGridTitle()
{
	CString astrGridTitle[5];
	//	= {"ѡ��", "���ƿ���������-IED","������","APPID","���ޱ�־"};
	xlang_GetLangStrByFile(astrGridTitle[0],_T("sSelect"));
	//xlang_GetLangStrByFile(astrGridTitle[1],_T("State_Description"));
	xlang_GetLangStrByFile(astrGridTitle[2],_T("IEC_FI"));
	astrGridTitle[1] = _T("���ƿ���������-IED");
	astrGridTitle[3] = "APPID";
	astrGridTitle[4] = _T("���ޱ�־");
	//xlang_GetLangStrByFile(astrGridTitle[4],_T("���ޱ�־"));

#ifdef _PSX_QT_LINUX_
	int iGridWidth[5]={80, 200, 300, 450, 100};
#else
	int iGridWidth[5]={80, 200, 300, 200, 100};
#endif
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 5);
}

void CIecCfgGooseDataGrid::ShowData( CExBaseObject *pData, int& nRow, BOOL bInsertRow/*=TRUE*/ )
{
	if ((pData->GetClassID() == CFGCLASSID_CIECCFGGINDATA) || (pData->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA))
	{
		CIecCfgGinData *pIecCfgGinData = (CIecCfgGinData*)pData;
		Show_Check(pData,nRow,0,&pIecCfgGinData->m_nUseFlag,EndEditCell_CheckChanged);//ѡ��
		Show_StaticString(pData,nRow,1,&pIecCfgGinData->m_strIedRefDesc);//���ƿ���������-IED
		Show_DataType_Val(pData,nRow,2,g_strAppPortDataType_Fiber,&pIecCfgGinData->m_nFiberIndex,EndEditCell_DataType_Val); //������
		Show_Hex(pData,nRow,3,&pIecCfgGinData->m_dwAppID,2,false); //APPID
		Show_Check(pData,nRow,4,&pIecCfgGinData->m_bNdsCom);//���ޱ�־
		nRow++;
	}
	else
	{
		return;
	}
}

void CIecCfgGooseDataGrid::OnDataSelChanged( QTableWidget *pGridCtrl, int nRow, int nCol )
{
	CExBaseList *pCurrSelData =  (CExBaseList*)this->GetCurrSelData();

	if (pCurrSelData == NULL)
	{
		return;
	}

	emit sig_Update_ChDatas(pCurrSelData);//���¿��ƿ�ͨ������
}
