#include "SttIecSmvGrid_MUAccuracy.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/SmartCap/XSttRcdInitChDvmData.h"
#include "../../XLangResource_Native.h"

CSttIecSmvGrid_MUAccuracy::CSttIecSmvGrid_MUAccuracy(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pCapDevice = NULL;
	m_pCurrLevelDataType = NULL;
	m_pVolLevelDataType = NULL;
	m_bZeroDriftMode = FALSE;
	m_astrGridTitle[0]= /*"通道名称"*/g_sLangTxt_channelname; //lcq
	m_astrGridTitle[1]=/*"输出值(A/V)"*/g_sLangTxt_outputvalue; //lcq
	m_astrGridTitle[2]=/*"输出相位(°)"*/g_sLangTxt_Outputphase; //lcq
	m_astrGridTitle[3]=/*"实测幅值(A/V)"*/g_sLangTxt_Measureampl; //lcq
	m_astrGridTitle[4]=/*"实测相位(°)"*/g_sLangTxt_Measuredphase; //lcq
//	m_astrGridTitle[5]="实测频率(Hz)";
	m_astrGridTitle[6]=/*"角差(′)"*/g_sLangTxt_angle; //lcq
//	m_astrGridTitle[7]="频差(Hz)";
	m_astrGridTitle[7]=/*"复合误差(%)"*/g_sLangTxt_Compound; //lcq
	//m_astrGridTitle[8]="准确级";
}

CSttIecSmvGrid_MUAccuracy::~CSttIecSmvGrid_MUAccuracy()
{

}

void CSttIecSmvGrid_MUAccuracy::InitGridTitle()
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	

	if (!pXSttCap_61850->m_bIsZeroDriftTest)
	{
		m_bZeroDriftMode = FALSE;
		m_astrGridTitle[5]=/*"比差(%)"*/g_sLangTxt_Gradient_DiffRatio; //lcq
	} 
	else
	{
		m_bZeroDriftMode = TRUE;
		m_astrGridTitle[5]= /*"零漂(dB)"*/g_sLangTxt_zerodrift; //lcq
	}

	int iGridWidth[SmvGrid_MUAccuracy_MAX_ROW_NUM]={140, 120, 120, 130, 110,/* 120,*/ 90, 90, /*100*//*90,*/ 120};
	QExBaseListGridBase::InitGridTitle(m_astrGridTitle, iGridWidth, SmvGrid_MUAccuracy_MAX_ROW_NUM);
	m_pCurrLevelDataType = FindDataType(iecfg_SmvInAppChAccLevelDataType_I);
	m_pVolLevelDataType = FindDataType(iecfg_SmvInAppChAccLevelDataType_U);
}

void CSttIecSmvGrid_MUAccuracy::UpdataGridHeaders()
{
	if (!m_bZeroDriftMode)
	{
		m_bZeroDriftMode = FALSE;
		m_astrGridTitle[5]=/*"比差(%)"*/g_sLangTxt_Gradient_DiffRatio; //lcq
	} 
	else
	{
		m_bZeroDriftMode = TRUE;
		m_astrGridTitle[5]= /*"零漂(dB)"*/g_sLangTxt_zerodrift; //lcq
	}

	QStringList headers;

	for (int nIndex = 0;nIndex<SmvGrid_MUAccuracy_MAX_ROW_NUM;nIndex++)
	{
		headers<<m_astrGridTitle[nIndex];
	}

	setHorizontalHeaderLabels(headers);
}

void CSttIecSmvGrid_MUAccuracy::UpdateChName()
{
	if (m_pCapDevice == NULL)
	{
		return;
	}

	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)m_pCapDevice;
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();  //dsSV1、dsSV2……

	DisConnectAll_SigSlot();

	POS pos = pDvmDataset->GetHeadPosition();
	int nRowIndex = 0;//zhouhj Qt中不包括标题行
	CDvmData *pChData = NULL;

	while (pos != NULL)
	{
		pChData = (CDvmData*)pDvmDataset->GetNext(pos);

		if (pChData->m_nChange == 0)
		{
			continue;
		}

		Show_StaticString(pChData, nRowIndex, 0, &pChData->m_strName);
		nRowIndex++;
	}

	ConnectAll_SigSlot();
}

//一个data是一行
void CSttIecSmvGrid_MUAccuracy::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pChData = (CDvmData*)pData;

	if (bInsertRow)
	{
		insertRow(NULL);
	}

	if (pChData->m_nChange == 0)
	{
		return;
	}

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	Show_StaticString(pData, nRow, 0, &pChData->m_strName);
	ShowDataEx(pChData,nRow);

	//CString strAccurLevel;
	//strAccurLevel = _T("---");

	//if (m_pCapDevice != NULL)
	//{
	//	CCapDeviceSmvCh *pCh = (CCapDeviceSmvCh*)m_pCapDevice->FindByID(pData->m_strID);

	//	if (pCh != NULL)
	//	{
	//		pChData->m_nIndex = pCh->m_nAccurLevel;
	//		CDataTypeValue* pDataTypeValue = NULL;

	//		if ((pChData->m_strDataType == "Curr")&&(m_pCurrLevelDataType != NULL))
	//		{
	//			 pDataTypeValue = m_pCurrLevelDataType->FindByIndex(pChData->m_nIndex);

	//			 if (pDataTypeValue != NULL)
	//			 {
	//				 if (pXSttCap_61850->m_bIsZeroDriftTest)
	//				 {
	//					 strAccurLevel = pDataTypeValue->m_strName;
	//				 } 
	//				 else
	//				 {
	//					 strAccurLevel = pDataTypeValue->m_strName + GetCurrChStdErrorValueDesc(pCh->m_nAccurLevel);
	//				 }
	//			 }
	//		}
	//		else if ((pChData->m_strDataType == "Vol")&&(m_pVolLevelDataType != NULL))
	//		{
	//			pDataTypeValue = m_pVolLevelDataType->FindByIndex(pChData->m_nIndex);

	//			if (pDataTypeValue != NULL)
	//			{
	//				if (pXSttCap_61850->m_bIsZeroDriftTest)
	//				{
	//					strAccurLevel = pDataTypeValue->m_strName;
	//				} 
	//				else
	//				{
	//					strAccurLevel = pDataTypeValue->m_strName + GetVolChStdErrorValueDesc(pCh->m_nAccurLevel);
	//				}
	//			}
	//		}
	//	}
	//} 

	//Show_StaticString(pData, nRow, 8, strAccurLevel);
	nRow++;
}

void CSttIecSmvGrid_MUAccuracy::ShowValueString(CDvmData *pChData, int nRow, int nCol, CString strValue)
{
	if (pChData->m_nChange == 0)
	{
		return;
	}

	double dValue = CString_To_double(strValue);
	CString strValueEx;
	strValueEx.Format(_T("%.3f"), dValue);
	Show_StaticString(pChData, nRow, nCol, strValueEx);
	SetItemBkColour(nRow, nCol, 0, 255, 255);
}

void CSttIecSmvGrid_MUAccuracy::ShowDataEx(CDvmData *pChData, int nRow)
{
	if (pChData->m_nChange == 0)
	{
		return;
	}
	
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if (pXSttCap_61850->m_bIsZeroDriftTest)
	{
		Show_StaticString(pChData, nRow, 1, _T("0.000"));
	}
	else
	{
		ShowValueString(pChData,nRow,1,pChData->m_strValue);
	}
	
	ShowValueString(pChData,nRow,2,pChData->m_strFormat);
	ShowAttrValue(pChData, nRow, 3, _T("$mag"),3);
	ShowAttrValue(pChData, nRow, 4, _T("$ang"),3);
//	ShowAttrValue(pChData, nRow, 5, _T("$freq"),3);
	ShowAttrValueRatError(pChData, nRow);

	if (!pXSttCap_61850->m_bIsZeroDriftTest)
	{
		ShowAttrValueAngError(pChData, nRow);
//		ShowAttrValue(pChData, nRow, 7, _T("$FreqError"),3);
		ShowAttrValueCompError(pChData, nRow);
	} 
	else
	{
		Show_StaticString(pChData, nRow, 6, _T("---"));
//		Show_StaticString(pChData, nRow, 7, _T("---"));
		Show_StaticString(pChData, nRow, 7, _T("---"));
	}
}

void CSttIecSmvGrid_MUAccuracy::UpdateData(CExBaseObject *pData, int nRow)
{
 	CDvmData *pChData = (CDvmData*)pData;
 
 	ShowDataEx(pChData, nRow);
}

void CSttIecSmvGrid_MUAccuracy::UpdateDatas()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if (pXSttCap_61850 != NULL)
	{
		if (pXSttCap_61850->m_bIsZeroDriftTest != m_bZeroDriftMode)//合并单元自动测试过程中,零漂标识会更新
		{
			m_bZeroDriftMode = pXSttCap_61850->m_bIsZeroDriftTest;
			UpdataGridHeaders();
		} 
	}

	CDvmData *pChData = NULL;
//	CExBaseObject *pObj = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 0;

	while (pos != NULL)
	{
		pChData = (CDvmData*)m_pDatas->GetNext(pos);

		if (pChData->m_nChange == 0)
		{
			continue;
		}

		UpdateData(pChData, nRowIndex);
		nRowIndex++;
	}
}

void CSttIecSmvGrid_MUAccuracy::ShowAttrValueRatError(CDvmData *pData, int nRow)
{
	CString strID = pData->m_strID + STT_RcdInit_DL_RatError/*_T("$RatError")*/;
	CDvmValue *pFind = (CDvmValue*)pData->FindByID(strID);

	if (pFind == NULL)
	{
		Update_StaticString(pData, nRow, 5, &g_strEmptyString);
	}
	else
	{
		double dValue = CString_To_double(pFind->m_strValue);
		long nColor = GetCurrItemColor(pData,dValue/100,MUAccuracy_ErrorType_RatError);
		CString strValue;
		strValue.Format(_T("%.3f"), dValue);
		Update_StaticStringColor(pData, nRow, 5, &strValue,nColor);
	}
}

void CSttIecSmvGrid_MUAccuracy::ShowAttrValueAngError(CDvmData *pData, int nRow)
{
	CString strID = pData->m_strID + STT_RcdInit_DL_AngError/*_T("$AngError")*/;
	CDvmValue *pFind = (CDvmValue*)pData->FindByID(strID);

	if (pFind == NULL)
	{
		Update_StaticString(pData, nRow, 6, &g_strEmptyString);
	}
	else
	{
		double dValue = CString_To_double(pFind->m_strValue);
		long nColor = GetCurrItemColor(pData,dValue,MUAccuracy_ErrorType_AngError)/*Qt::black*/;
		CString strValue;
		strValue.Format(_T("%.3f"), dValue);
		Update_StaticStringColor(pData, nRow, 6, &strValue,nColor);
	}
}

void CSttIecSmvGrid_MUAccuracy::Update_StaticStringColor(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString,long nResult)
{
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if ((*pString == "nan")||(*pString == "inf"))
	{
		*pString = "---";
		nResult = Qt::red;
	}

	if (pItem != NULL)
	{
		pItem->setTextColor((Qt::GlobalColor)nResult/*nResult*/);
		pItem->setText(*pString);
		return;
	}

	pItem = new QGV_ITEM(*pString);
	pItem->setTextColor((Qt::GlobalColor)nResult);
	pItem->nDataType = QT_GVET_NOEDIT;
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags((Qt::ItemIsEnabled));

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, (CString*)NULL, pData,NULL, NULL);
	pItem->lParam = (LPARAM)pVCellData;
	pVCellData->nVt = VCD_STRING;

	setItem(nRow,nCol,pItem);
}

void CSttIecSmvGrid_MUAccuracy::ShowAttrValueCompError(CDvmData *pData, int nRow)
{
	CString strID = pData->m_strID + STT_RcdInit_DL_CompError/*_T("$CompError")*/;
	CDvmValue *pFind = (CDvmValue*)pData->FindByID(strID);

	if (pFind == NULL)
	{
		Update_StaticString(pData, nRow, 7, &g_strEmptyString);
	}
	else
	{
		double dValue = CString_To_double(pFind->m_strValue);
		long nColor = GetCurrItemColor(pData,dValue/100,MUAccuracy_ErrorType_CompError);
		CString strValue;
		strValue.Format(_T("%.3f"), dValue);
		Update_StaticStringColor(pData, nRow, 7, &strValue,nColor);

// 		if (nRow == 0)
// 		{
// 			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("表格显示复合误差值(%s)."),strValue.GetString());
// 		}
	}
}

CString CSttIecSmvGrid_MUAccuracy::GetVolChStdErrorValueDesc(long nAccurLevel)
{
	CString strDesc;

	if (nAccurLevel == IECCFG_VOLCH_AccLevel_Prot3P)
	{
		strDesc = _T("[3%, 120′]");
	}
	else if (nAccurLevel == IECCFG_VOLCH_AccLevel_Prot6P)
	{
		strDesc = _T("[6%, 240′]");
	}
	else if (nAccurLevel == IECCFG_VOLCH_AccLevel_Meas0_1)
	{
		strDesc = _T("[0.1%, 5′]");
	}
	else if (nAccurLevel == IECCFG_VOLCH_AccLevel_Meas0_2)
	{
		strDesc = _T("[0.2%, 10′]");
	}
	else if (nAccurLevel == IECCFG_VOLCH_AccLevel_Meas0_5)
	{
		strDesc = _T("[0.5%, 20′]");
	}
	else if (nAccurLevel == IECCFG_VOLCH_AccLevel_Meas1)
	{
		strDesc = _T("[1.0%, 40′]");
	}

	return strDesc;
}

CString CSttIecSmvGrid_MUAccuracy::GetCurrChStdErrorValueDesc(long nAccurLevel)
{
	CString strDesc;

	if (nAccurLevel == IECCFG_CURRCH_AccLevel_Prot5P30)
	{
		strDesc = _T("[1%, 60′, 5%]");
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Prot5P)
	{
		strDesc = _T("[1%, 60′, 5%]");
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Prot10P)
	{
		strDesc = _T("[3%, 120′, 10%]");
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Meas0_1)
	{
		strDesc = _T("[0.1%, 5′]");
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Meas0_2S)
	{
		strDesc = _T("[0.2%, 10′]");
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Meas0_2)
	{
		strDesc = _T("[0.2%, 10′]");
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Meas0_5S)
	{
		strDesc = _T("[0.5%, 30′]");
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Meas0_5)
	{
		strDesc = _T("[0.5%, 30′]");
	}
	else if (nAccurLevel == IECCFG_CURRCH_AccLevel_Meas1)
	{
		strDesc = _T("[1.0%, 60′]");
	}

	return strDesc;
}

long CSttIecSmvGrid_MUAccuracy::GetCurrItemColor(CDvmData *pData,double dValue,long nErrorType)
{
	long nColor = Qt::black;

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if (pXSttCap_61850->m_bIsZeroDriftTest)//零漂测试,则不进行判别
		return nColor;

	if (pData->m_strDataType == "Curr")
	{
		if ((fabs(dValue)>cap_MUAccuracy_GetCurrChStdErrorValue(pData->m_nIndex,nErrorType)))
		{
			nColor = Qt::red;
		}
	}
	else if (pData->m_strDataType == "Vol")
	{
		if (fabs(dValue)>cap_MUAccuracy_GetVolChStdErrorValue(pData->m_nIndex,nErrorType))
		{
			nColor = Qt::red;
		}
	}

	return nColor;
}