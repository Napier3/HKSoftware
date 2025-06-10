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
	CString astrGridTitle[QCAPDEVDATASGRID_COLS] = {_T("���"),_T("����"),_T("ID"),_T("��Ŀ��"),_T("��ֵ"),_T("�޸�"),_T("��������"),_T("��λ"),_T("��Сֵ"),_T("���ֵ"),_T("")};
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
	int nRowIndex = 0;//zhouhj Qt�в�����������
	long nCalRows = GetDatasCount();//zhouhj Qt�в�����������
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
	Show_Index(pDvmData, nRow, 0);//���
	Show_StaticString(pDvmData, nRow, 1, pDvmData->m_strName);//����
	Show_StaticString(pDvmData, nRow, 2, pDvmData->m_strID);//ID
	Show_Long(pDvmData, nRow, 3, &pDvmData->m_nIndex, FALSE);//��Ŀ��
	CDvmDataset *pDvmDataset = (CDvmDataset *)pData->GetParent();
	if (pDvmDataset->m_strID == "dsSV1")
	{
		ShowAttrValue(pDvmData, nRow, 4, strMagValue, 3);//��ֵ
	}
	else
	{
		Show_StaticString(pDvmData, nRow, 4, pDvmData->m_strValue);//��ֵ
	}
	Show_Long(pDvmData, nRow, 5, &pDvmData->m_nChange, FALSE);//�޸�
	Show_StaticString(pDvmData, nRow, 6, pDvmData->m_strDataType);//��������
	Show_StaticString(pDvmData, nRow, 7, pDvmData->m_strUnit);//��λ
	Show_StaticString(pDvmData, nRow, 8, pDvmData->m_strMin);//��Сֵ
	Show_StaticString(pDvmData, nRow, 9, pDvmData->m_strMax);//���ֵ
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
		//�����ֶ�̬�ľ��ȣ��������⣬strValue��ʽ�����֮��Ϊ0.000
		//strFormat.Format(_T("%%.%df"), nPrecision);
		//strValue.Format(strFormat, dValue);
		//�̶����ñ�����λ��Ч����
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
	int nRowIndex = 0;//Qt�в�����������
	long nCalRows = GetDatasCount();//Qt�в�����������
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
	Show_Index(pDvmValue, nRow, 0);//���
	Show_StaticString(pDvmValue, nRow, 1, pDvmValue->m_strName);//����
	Show_StaticString(pDvmValue, nRow, 2, pDvmValue->m_strID);//ID
	Show_StaticString(pDvmValue, nRow, 4, pDvmValue->m_strValue);//��ֵ
	Show_StaticString(pDvmValue, nRow, 6, pDvmValue->m_strDataType);//��������
	nRow++;
}
