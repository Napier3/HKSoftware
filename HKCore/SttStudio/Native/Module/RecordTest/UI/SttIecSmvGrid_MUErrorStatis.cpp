#include "SttIecSmvGrid_MUErrorStatis.h"
#include "../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../Module/SmartCap/XSttRcdInitChDvmData.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include <QHeaderView>
#include <QDesktopWidget>
#include <QApplication>
#include "../../../AutoTest/Module/XLanguageResourceAts.h"
#include "../../XLangResource_Native.h"


CSttIecSmvGrid_MUErrorStatis::CSttIecSmvGrid_MUErrorStatis(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
}

CSttIecSmvGrid_MUErrorStatis::~CSttIecSmvGrid_MUErrorStatis()
{

}

void CSttIecSmvGrid_MUErrorStatis::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
{
	DisConnectAll_SigSlot();
	m_pCurrData = NULL;

	if (pDatas == NULL)
	{
		SetRowCount(0);
		return;
	}

	m_pDatas = pDatas;
	CDvmData *pObj = NULL;	
	POS pos = pDatas->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt�в�����������
	long nCalRows = (GetDatasCount()-1)*3;//�̶�ȥ����һ����ʱͨ��

	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)m_pCapDevice;

	if ((pCapDevice != NULL)&&(pCapDevice->GetClassID() == CPDCLASSID_DEVICE6044))
	{
		nCalRows = (GetDatasCount())*3;
		SetRowCount(nCalRows, bResetScrollBars);
	}
	else
	{
		SetRowCount(nCalRows, bResetScrollBars);

		if (pos != NULL)
		{
			pDatas->GetNext(pos);
		}
	}

	while (pos != NULL)
	{
		pObj = (CDvmData*)pDatas->GetNext(pos);

		if (pObj->m_nChange == 0)
		{
			continue;
		}

		ShowData(pObj, nRowIndex, FALSE);
	}

	SetRowCount(nRowIndex, bResetScrollBars);
	AfterShowDatas(1, bResetScrollBars);
}

void CSttIecSmvGrid_MUErrorStatis::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;

	if (pCapDevice == NULL)
	{
		return;
	}

	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();  //dsSV1��dsSV2����
	ShowDatas(pDvmDataset);
}

void CSttIecSmvGrid_MUErrorStatis::Release()
{
	delete this;
}

void CSttIecSmvGrid_MUErrorStatis::InitGridTitle()
{
	CString astrGridTitle[SmvGrid_MUErrorStatis_MAX_ROW_NUM];
	astrGridTitle[0]= /*"ͨ������"*/ g_sLangTxt_channelname; //lcq
	astrGridTitle[1]=/*"������"*/g_sLangTxt_errorclass;
	astrGridTitle[2]=/*"���Դ���"*/g_sLangTxt_numbertest;
	astrGridTitle[3]=/*"ʵʱֵ"*/g_sLangTxt_realtime;
	astrGridTitle[4]=/*"���ֵ"*/g_sLangTxt_MaxValue;
	astrGridTitle[5]=/*"��Сֵ"*/g_sLangTxt_MinValue;
	astrGridTitle[6]=/*"ƽ��ֵ"*/g_sLangTxt_Average;

	int iGridWidth[SmvGrid_MUErrorStatis_MAX_ROW_NUM]={150, 150, 100, 100, 100, 100, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, SmvGrid_MUErrorStatis_MAX_ROW_NUM);

	//20230725 suyang ����ֱ��� 1024X768
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect rect = desktopWidget->screenGeometry();

	if (rect.width() > 1024)
	{
		horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//ƽ���ֲ�����
	}

}

void CSttIecSmvGrid_MUErrorStatis::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	UpdateDatas();
}

//һ��data��һ��
void CSttIecSmvGrid_MUErrorStatis::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pChData = (CDvmData*)pData;

	if (bInsertRow)
	{
		insertRow(NULL);
		insertRow(NULL);
		insertRow(NULL);
	}

	CString strRatErrorDesc,strAngErrorDesc,strCompErrorDesc;
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if (pXSttCap_61850->m_bIsZeroDriftTest)
	{
		strRatErrorDesc = /*"�Ȳ�"*/g_sLangTxt_ratioerror;  //lcq
	}
	else
	{
		strRatErrorDesc = /*"�Ȳ�(%)"*/g_sLangTxt_Gradient_DiffRatio;   //lcq
	}

	strAngErrorDesc = /*"�ǲ�(��)"*/g_sLangTxt_angle; //lcq
	strCompErrorDesc = /*"�������(%)"*/g_sLangTxt_Compound; //lcq

	Show_StaticString(pData, nRow, 0, &pChData->m_strName);
	setSpan(nRow,0,3,1);
	Show_StaticString(pData, nRow, 1, &strRatErrorDesc);
	ShowDataEx(pChData,nRow);
	nRow++;
	Show_StaticString(pData, nRow, 1, &strAngErrorDesc);
	nRow++;
	Show_StaticString(pData, nRow, 1, &strCompErrorDesc);
	nRow++;
}

void CSttIecSmvGrid_MUErrorStatis::ShowDataEx(CDvmData *pChData, int nRow)
{
	ShowAttrValue_ErrorStatis(pChData, nRow, 2, STT_RcdInit_DL_RatError/*_T("$RatError")*/,3);
 	ShowAttrValue_ErrorStatis(pChData, nRow+1, 2, STT_RcdInit_DL_AngError/*_T("$AngError")*/,3);
 	ShowAttrValue_ErrorStatis(pChData, nRow+2, 2, STT_RcdInit_DL_CompError/*_T("$CompError")*/,3);
}

void CSttIecSmvGrid_MUErrorStatis::UpdateDatas()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	CDvmData *pObj = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)m_pCapDevice;

	if ((pCapDevice != NULL)&&(pCapDevice->GetClassID() != CPDCLASSID_DEVICE6044))
	{
		if (pos != NULL)
		{
			m_pDatas->GetNext(pos);
		}
	}

	int nRowIndex = 0;

	while (pos != NULL)
	{
		pObj = (CDvmData*)m_pDatas->GetNext(pos);

		if (pObj->m_nChange == 0)
		{
			continue;
		}

		UpdateData(pObj, nRowIndex);
		nRowIndex += 3;
	}
}

void CSttIecSmvGrid_MUErrorStatis::UpdateData(CExBaseObject *pData, int nRow)
{
  	CDvmData *pChData = (CDvmData*)pData;
  
  	ShowDataEx(pChData, nRow);
}

void CSttIecSmvGrid_MUErrorStatis::ShowAttrValue_ErrorStatis(CDvmData *pData, int nRow, int nCol, const CString &strAttrID, long nPrecision)
{
	CString strID = pData->m_strID + strAttrID;
	CDvmValue *pFind = (CDvmValue*)pData->FindByID(strID);
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	BOOL bZeroDriftEmpty = FALSE;

	if (pXSttCap_61850->m_bIsZeroDriftTest && (strAttrID != STT_RcdInit_DL_RatError/*_T("$RatError")*/))
	{
		bZeroDriftEmpty = TRUE;
	}

	if ((pFind == NULL)||(bZeroDriftEmpty))
	{
		Update_StaticString(pData, nRow, nCol, &g_strEmptyString);
		Update_StaticString(pData, nRow, 3, &g_strEmptyString);
		Update_StaticString(pData, nRow, 4, &g_strEmptyString);
		Update_StaticString(pData, nRow, 5, &g_strEmptyString);
		Update_StaticString(pData, nRow, 6, &g_strEmptyString);
	}
	else
	{
		CString strTestCountID = pFind->m_strID + STT_RcdInit_DL_TestCount/*_T("$TestCount")*/;
		CDvmValue *pFindChild = (CDvmValue*)pFind->FindByID(strTestCountID);

		if (pFindChild == NULL)
		{
			Update_StaticString(pData, nRow, nCol, &g_strEmptyString);
		} 
		else
		{
			long nTestCount = CString_To_long(pFindChild->m_strValue);

			if (g_nUseCustomMUTestRpt && ((nTestCount-CAP_BEFORE_TEST_CALC_COUNT)>g_nMURptTestCount))
			{
				CString strTmp;
				strTmp.Format(_T("%d"),g_nMURptTestCount);
				Update_StaticString(pData, nRow, nCol, &strTmp);
			} 
			else
			{
				Update_StaticString(pData, nRow, nCol, &pFindChild->m_strValue);
			}
		}

		if (pFind == NULL)
		{
			Update_StaticString(pData, nRow, nCol, &g_strEmptyString);
		}

		if (nPrecision == -1)
		{
			Show_StaticDoubleString(pData, nRow, 3, pFind->m_strValue,3);
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
			Update_StaticString(pData, nRow, 3, &strValue);
		}

		ShowAttrValue(pFind, nRow, 4, STT_RcdInit_DL_MaxValue/*_T("$MaxValue")*/,3);
		ShowAttrValue(pFind, nRow, 5, STT_RcdInit_DL_MinValue/*_T("$MinValue")*/,3);
		ShowAttrValue(pFind, nRow, 6, STT_RcdInit_DL_AverageValue/*_T("$AverageValue")*/,3);
	}
}

void CSttIecSmvGrid_MUErrorStatis::Config()
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if (m_pDatas == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("��ǰ���ݼ�Ϊ��,������ͳ�ƽ��ʧ��.")*/g_sLangTxt_Gradient_CurNullFa.GetString()); //lcq
		return;
	}

	CDvmData *pDvmData = NULL;	
	POS pos = m_pDatas->GetHeadPosition();

	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)m_pCapDevice;

	if ((pCapDevice != NULL)&&(pCapDevice->GetClassID() != CPDCLASSID_DEVICE6044))
	{
		if (pos != NULL)
		{
			m_pDatas->GetNext(pos);
		}
	}

	CDvmValue *pCurrValue = NULL,*pChildValue = NULL;

	while (pos != NULL)
	{
		pDvmData = (CDvmData*)m_pDatas->GetNext(pos);

		POS pos_value = pDvmData->GetHeadPosition();

		while(pos_value)
		{
			pCurrValue = (CDvmValue *)pDvmData->GetNext(pos_value);

			POS pos_child_value = pCurrValue->GetHeadPosition();

			while(pos_child_value)
			{
				pChildValue = (CDvmValue *)pCurrValue->GetNext(pos_child_value);
				pChildValue->m_strValue = _T("");
			}
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("������ͳ�ƽ���ɹ�.")*/g_sLangTxt_statistic.GetString()); //lcq
}

void CSttIecSmvGrid_MUErrorStatis::UpdateChName()
{
	if (m_pCapDevice == NULL)
	{
		return;
	}

	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)m_pCapDevice;
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();  //dsSV1��dsSV2����
	DisConnectAll_SigSlot();

	POS pos = pDvmDataset->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt�в�����������
	CDvmData *pChData = NULL;

	if (pCapDevice->GetClassID() != CPDCLASSID_DEVICE6044)
	{
		//�̶�ȡ����һ����ʱͨ��
		if (pos != NULL)
		{
			pDvmDataset->GetNext(pos);
		}
	}

	while (pos != NULL)
	{
		pChData = (CDvmData*)pDvmDataset->GetNext(pos);

		if (pChData->m_nChange == 0)
		{
			continue;
		}

		Show_StaticString(pChData, nRowIndex, 0, &pChData->m_strName);
		nRowIndex += 3;
	}

	ConnectAll_SigSlot();
}
