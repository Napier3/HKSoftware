#include "QCapDeviceDatasGrid.h"
#include "..\DataMngr\DvmDataset.h"

QCapDeviceDatasGrid::QCapDeviceDatasGrid(QWidget *pparent):QExBaseListGridBase(pparent)
{

}

QCapDeviceDatasGrid::~QCapDeviceDatasGrid()
{

}

void QCapDeviceDatasGrid::InitGrid()
{
	verticalHeader()->setVisible(false);
	InitGridTitle();
}

void QCapDeviceDatasGrid::InitGridTitle()
{
	CString astrGridTitle[QCAPDEVDATASGRID_COLS] = {_T("编号"),_T("名称"),_T("ID"),_T("条目号"),_T("数值"),_T("修改"),_T("数据类型"),_T("单位"),_T("最小值"),_T("最大值"),_T("")};
	int  iColType[QCAPDEVDATASGRID_COLS]={QT_GVET_NOEDIT, QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT,QT_GVET_NOEDIT};
	int iGridWidth[QCAPDEVDATASGRID_COLS]={100, 300, 150, 150, 150,150,150,150,150,150,100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, QCAPDEVDATASGRID_COLS);
}

void QCapDeviceDatasGrid::UpdateDatas()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	DisConnectAll_SigSlot();
	BOOL bResetScrollBars=TRUE;
	CExBaseObject *pObj = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt中不包括标题行
	long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行
	SetRowCount(nCalRows, bResetScrollBars);

	while (pos != NULL)
	{
		pObj = m_pDatas->GetNext(pos);
		if (m_pDatas->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			ShowData(pObj, nRowIndex, FALSE);
		}
		else if (m_pDatas->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			ShowChannelData(pObj, nRowIndex, FALSE);
		}
	}
	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

void QCapDeviceDatasGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow/*=TRUE*/)
{
	ASSERT(pData);
	CString strMagValue = "";
	strMagValue = _T("$mag");
	CDvmData *pDvmData = (CDvmData *)pData;
	Show_Index(pDvmData, nRow, 0);//编号
	Show_StaticString(pDvmData, nRow, 1, pDvmData->m_strName);//名称
	Show_StaticString(pDvmData, nRow, 2, pDvmData->m_strID);//ID
	Show_Long(pDvmData, nRow, 3, &pDvmData->m_nIndex, FALSE);//条目号
	CDvmDataset *pDvmDataset = (CDvmDataset *)pData->GetParent();
	if (pDvmDataset->m_strID == "dsSV1")
	{
		ShowAttrValue(pDvmData, nRow, 4, strMagValue, 3);//数值
	}
	else
	{
		Show_StaticString(pDvmData, nRow, 4, pDvmData->m_strValue);//数值
	}
	Show_Long(pDvmData, nRow, 5, &pDvmData->m_nChange, FALSE);//修改
	Show_StaticString(pDvmData, nRow, 6, pDvmData->m_strDataType);//数据类型
	Show_StaticString(pDvmData, nRow, 7, pDvmData->m_strUnit);//单位
	Show_StaticString(pDvmData, nRow, 8, pDvmData->m_strMin);//最小值
	Show_StaticString(pDvmData, nRow, 9, pDvmData->m_strMax);//最大值
	nRow++;
}

void QCapDeviceDatasGrid::ShowAttrValue(CDvmData *pData, int nRow, int nCol, CString &strAttrID, long nPrecision)
{
	CString strID = pData->m_strID + strAttrID;
	CDvmValue *pFind = (CDvmValue*)pData->FindByID(strID);

	CString strEmpty = _T("--");
	if (pFind == NULL)
	{
		Update_StaticString(pData, nRow, nCol, &strEmpty);
	}
	else
	{

		double dValue = CString_To_double(pFind->m_strValue);
		CString strValue/*, strFormat*/;
		//用这种动态的精度，存在问题，strValue格式化完成之后为0.000
		//strFormat.Format(_T("%%.%df"), nPrecision);
		//strValue.Format(strFormat, dValue);
		//固定采用保留三位有效数字
		strValue.Format(_T("%.3f"), dValue);
		Update_StaticString(pData, nRow, nCol, &strValue);
	}
}

void QCapDeviceDatasGrid::ShowChannelDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
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
	int nRowIndex = 0;//Qt中不包括标题行
	long nCalRows = GetDatasCount();//Qt中不包括标题行
	SetRowCount(nCalRows, bResetScrollBars);

	while (pos != NULL)
	{
		pObj = pDatas->GetNext(pos);
		ShowChannelData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

void QCapDeviceDatasGrid::ShowChannelData(CExBaseObject *pData, int& nRow, BOOL bInsertRow/*=TRUE*/)
{
	ASSERT(pData);
	CDvmValue *pDvmValue = (CDvmValue*)pData;
	Show_Index(pDvmValue, nRow, 0);//编号
	Show_StaticString(pDvmValue, nRow, 1, pDvmValue->m_strName);//名称
	Show_StaticString(pDvmValue, nRow, 2, pDvmValue->m_strID);//ID
	Show_StaticString(pDvmValue, nRow, 4, pDvmValue->m_strValue);//数值
	Show_StaticString(pDvmValue, nRow, 6, pDvmValue->m_strDataType);//数据类型
	nRow++;
}
