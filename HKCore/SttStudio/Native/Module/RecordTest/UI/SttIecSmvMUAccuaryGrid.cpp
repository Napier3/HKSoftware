#include "SttIecSmvMUAccuaryGrid.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../../Module/SmartCap/XSttRcdInitChDvmData.h"
#include "../../XLangResource_Native.h"
#include <QHeaderView>
CSttIecSmvMUAccuracyGrid::CSttIecSmvMUAccuracyGrid(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pCapDevice = NULL;
	m_bOutPutValueMode = FALSE;
	m_bOutPutPhaseMode = FALSE;
	m_bChannelDelayMode = FALSE;
	m_bZeroDriftMode =FALSE;
}

CSttIecSmvMUAccuracyGrid::~CSttIecSmvMUAccuracyGrid()
{

}

void CSttIecSmvMUAccuracyGrid::InitGrid()
{
	InitGridTitle();
	SetEditable(FALSE);
}

void CSttIecSmvMUAccuracyGrid::InitGridTitle()
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	if (!pXSttCap_61850->m_bIsZeroDriftTest)
	{
		m_bZeroDriftMode = FALSE;
		m_astrGridTitle[4]=/*"�Ȳ�"*/ g_sLangTxt_ratioerror; //lcq
	} 
	else
	{
		m_bZeroDriftMode = TRUE;
		m_astrGridTitle[4]=/*"��Ư"*/ g_sLangTxt_Gradient_ZeroDrift; //lcq
	}
	
	m_astrGridTitle[0]= /*"ͨ������"*/g_sLangTxt_IEC_ChDescription;
	m_astrGridTitle[1]=/*"���ֵ"*/g_sLangTxt_Gradient_ValueOutP;
	m_astrGridTitle[2]=/*"�����λ"*/g_sLangTxt_Gradient_PhaseOutP;
	m_astrGridTitle[3]=/*"ʵ���ֵ"*/g_sLangTxt_Gradient_MeasurAmp;
	//m_astrGridTitle[4]="�Ȳ�";
	m_astrGridTitle[5]=/*"�ǲ�"*/g_sLangTxt_angle;
	m_astrGridTitle[6]=/*"ͨ����ʱ"*/g_sLangTxt_Gradient_ChanDelay;
	m_astrGridTitle[7]=/*"�������"*/g_sLangTxt_Gradient_CompError;
	m_astrGridTitle[8]=/*"ʵ����λ"*/g_sLangTxt_Gradient_MeaPhase;
	m_astrGridTitle[9]=/*"Ƶ��"*/g_sLangTxt_Gradient_FrequencyDiff;
	
	int iGridWidth[10]={150, 130, 130,130, 130, 120, 100, 120, 100,120};
	QExBaseListGridBase::InitGridTitle(m_astrGridTitle, iGridWidth, 10);	
	
	if (!m_bOutPutValueMode)
	{
		setColumnHidden(1,TRUE);
	}
	if (!m_bOutPutPhaseMode)
	{
		setColumnHidden(2,TRUE);
	}
	if (!m_bChannelDelayMode)
	{
		setColumnHidden(6,TRUE);
	}
}

void CSttIecSmvMUAccuracyGrid::UpdataGridHeaders()
{
	if (!m_bZeroDriftMode)
	{
		m_bZeroDriftMode = FALSE;
		m_astrGridTitle[4]=/*"�Ȳ�"*/g_sLangTxt_ratioerror;
	} 
	else
	{
		m_bZeroDriftMode = TRUE;
		m_astrGridTitle[4]=/*"��Ư"*/g_sLangTxt_Gradient_ZeroDrift; 
	}

	QStringList headers;

	for (int nIndex = 0;nIndex<10;nIndex++)
	{
		headers<<m_astrGridTitle[nIndex];
	}

	setHorizontalHeaderLabels(headers);
//	horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);//��Ӧ������� chenling20230707
}

void CSttIecSmvMUAccuracyGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
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
	nRow++;
}

void CSttIecSmvMUAccuracyGrid::ShowDataEx(CDvmData *pChData, int nRow)
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
		ShowValueString(pChData,nRow,1,pChData->m_strValue);//���ֵ
	}

	ShowValueString(pChData,nRow,2,pChData->m_strFormat);//�����λ
	ShowAttrValueRatError(pChData, nRow);//�Ȳ�

	if (!pXSttCap_61850->m_bIsZeroDriftTest)
	{
		ShowAttrValueAngError(pChData, nRow);//�ǲ�
		ShowAttrValueCompError(pChData, nRow);//�������
	} 
	else
	{
		Show_StaticString(pChData, nRow, 5, _T("---"));
		Show_StaticString(pChData, nRow, 7, _T("---"));
	}	
	
	ShowValueString(pChData,nRow,6,pChData->m_strValue);//ͨ����ʱ	

	ShowAttrValue(pChData, nRow, 3, _T("$mag"),3);//ʵ���ֵ
	ShowAttrValue(pChData, nRow, 8, _T("$ang"),3);//ʵ����λ
	ShowAttrValue(pChData, nRow, 9, _T("$FreqError"),3);//Ƶ��
}

void CSttIecSmvMUAccuracyGrid::resizeEvent(QResizeEvent *pReSizeEvent)
{
	long nColNum = GetColCount();

	if (nColNum>0)
	{
		setColumnWidth(nColNum,120);
	}

	CSttIecChsGridBase::resizeEvent(pReSizeEvent);
}

void CSttIecSmvMUAccuracyGrid::ShowAttrValueRatError(CDvmData *pData, int nRow)
{
	CString strID = pData->m_strID + STT_RcdInit_DL_RatError;
	CDvmValue *pFind = (CDvmValue*)pData->FindByID(strID);

	if (pFind == NULL)
	{
		Update_StaticString(pData, nRow, 4, &g_strEmptyString);//�Ȳ�
	}
	else
	{
		double dValue = CString_To_double(pFind->m_strValue);
		long nColor = GetCurrItemColor(pData,dValue/100,MUAccuracy_ErrorType_RatError);
		CString strValue;
		if (!m_bZeroDriftMode)
		{
			strValue.Format(_T("%.3f%"), dValue);
		}
		else
		{
			strValue.Format(_T("%.3fdB"), dValue);
		}
		
		Update_StaticStringColor(pData, nRow, 4, &strValue,nColor);
	}
}

void CSttIecSmvMUAccuracyGrid::ShowAttrValue(CDvmData *pData, int nRow, int nCol, const CString &strAttrID, long nPrecision)
{
	CString strID = pData->m_strID + strAttrID;
	CDvmValue *pFind = (CDvmValue*)pData->FindByID(strID);

	if (pFind == NULL)
	{
		Update_StaticString(pData, nRow, nCol, &g_strEmptyString);
	}
	else
	{
		if (nPrecision == -1)
		{
			Show_StaticDoubleString(pData, nRow, nCol, pFind->m_strValue,3);
		}
		else
		{
			double dValue = CString_To_double(pFind->m_strValue);
			CString strValue;

			if(pFind->m_strID.Find("$mag") > 0) //2024.5.27 chenling ʵ���ֵ��ȷ�ȱ�����λ
			{
				if (pData->m_strDataType== /*_T("��ѹ")*/g_sLangTxt_Native_Voltage) //lcq
				{
					strValue.Format(_T("%.5fV"), dValue);
				}
				else if (pData->m_strDataType ==/*_T("����")*/g_sLangTxt_Native_Current)
				{
					strValue.Format(_T("%.5fA"), dValue);
				}	
			}	
			else if (pFind->m_strID.Find("$ang") > 0)
			{
				strValue.Format(_T("%.2f"), dValue);
				strValue += "��";
			}
			else if (pFind->m_strID.Find("$FreqError") > 0)
			{
				strValue.Format(_T("%.3fHz"), dValue);
			}
			Update_StaticString(pData, nRow, nCol, &strValue);
		}
	}
}
void CSttIecSmvMUAccuracyGrid::ShowAttrValueAngError(CDvmData *pData, int nRow)
{
	CString strID = pData->m_strID + STT_RcdInit_DL_AngError;
	CDvmValue *pFind = (CDvmValue*)pData->FindByID(strID);

	if (pFind == NULL)
	{
		Update_StaticString(pData, nRow, 5, &g_strEmptyString);
	}
	else
	{
		double dValue = CString_To_double(pFind->m_strValue);
		long nColor = GetCurrItemColor(pData,dValue,MUAccuracy_ErrorType_AngError);
		CString strValue;	
		strValue.Format(_T("%.1f"), dValue);
		strValue += "��";
		Update_StaticStringColor(pData, nRow, 5, &strValue,nColor);
	}
}

void CSttIecSmvMUAccuracyGrid::ShowAttrValueCompError(CDvmData *pData, int nRow)
{
	CString strID = pData->m_strID + STT_RcdInit_DL_CompError;
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
		strValue.Format(_T("%.3f%"), dValue);
		Update_StaticStringColor(pData, nRow, 7, &strValue,nColor);
	}
}

void CSttIecSmvMUAccuracyGrid::UpdateData(CExBaseObject *pData, int nRow)
{
	CDvmData *pChData = (CDvmData*)pData;

	ShowDataEx(pChData, nRow);
}

void CSttIecSmvMUAccuracyGrid::ShowValueString(CDvmData *pChData, int nRow, int nCol, CString strValue)
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

void CSttIecSmvMUAccuracyGrid::Update_StaticStringColor(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString,long nResult)
{
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if ((*pString == "nan%")||(*pString == "inf%")||(*pString == "nandB")||(*pString == "infdB"))
	{
		*pString = "---";
		nResult = Qt::red;
	}

	if (pItem != NULL)
	{
		pItem->setTextColor((Qt::GlobalColor)nResult);
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

long CSttIecSmvMUAccuracyGrid::GetCurrItemColor(CDvmData *pData,double dValue,long nErrorType)
{
	long nColor = Qt::black;

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if (pXSttCap_61850->m_bIsZeroDriftTest)//��Ư����,�򲻽����б�
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


void CSttIecSmvMUAccuracyGrid::UpdateChName()
{
	if (m_pCapDevice == NULL)
	{
		return;
	}

	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)m_pCapDevice;
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();  

	DisConnectAll_SigSlot();

	POS pos = pDvmDataset->GetHeadPosition();
	int nRowIndex = 0;
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

void CSttIecSmvMUAccuracyGrid::UpdateDatas()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();

	if (pXSttCap_61850 != NULL)
	{
		if (pXSttCap_61850->m_bIsZeroDriftTest != m_bZeroDriftMode)//�ϲ���Ԫ�Զ����Թ�����,��Ư��ʶ�����
		{
			m_bZeroDriftMode = pXSttCap_61850->m_bIsZeroDriftTest;
			UpdataGridHeaders();
		} 
	}

	CDvmData *pChData = NULL;
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
