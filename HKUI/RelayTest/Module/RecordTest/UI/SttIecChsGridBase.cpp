#include "SttIecChsGridBase.h"
#include "../../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
#include "SttIecRcdFuncInterface.h"
#include "../../../../Module/API/GlobalConfigApi.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../XLangResource_Native.h"


CString CSttIecChsGridBase::g_strEmptyString = _T("--");

CSttIecChsGridBase::CSttIecChsGridBase(QWidget* pparent):QExBaseListGridBase(pparent)
{
	
}

CSttIecChsGridBase::~CSttIecChsGridBase()
{

}

void CSttIecChsGridBase::ShowAttrValue(CDvmData *pData, int nRow, int nCol, const CString &strAttrID, long nPrecision)
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
			CString strValue/*, strFormat*/;
			//用这种动态的精度，存在问题，strValue格式化完成之后为0.000
			//strFormat.Format(_T("%%.%df"), nPrecision);
			//strValue.Format(strFormat, dValue);

			//固定采用保留三位有效数字
			strValue.Format(_T("%.3f"), dValue);
			Update_StaticString(pData, nRow, nCol, &strValue);
		}
	}
}

void CSttIecChsGridBase::UpdateAttrValue(CDvmData *pData, int nRow, int nCol, const CString &strAttrID)
{
	CString strID = pData->m_strID + strAttrID;
	CDvmValue *pFind = (CDvmValue*)pData->FindByID(strID);

	if (pFind == NULL)
	{
		Show_ItemString(nRow, nCol, &g_strEmptyString);
	}
	else
	{
		Show_ItemString(nRow, nCol, &pFind->m_strValue);
	}
}

void CSttIecChsGridBase::ShowAttrValue(CDvmValue *pData, int nRow, int nCol, const CString &strAttrID, long nPrecision)
{
	CString strID = pData->m_strID + strAttrID;
	CDvmValue *pFind = (CDvmValue*)pData->FindByID(strID);
	
	if (pFind == NULL)
	{
		Show_StaticString(pData, nRow, nCol, &g_strEmptyString);
	}
	else
	{
		if (nPrecision == -1)
		{
			Show_StaticString(pData, nRow, nCol, &pFind->m_strValue);
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
			Show_StaticString(pData, nRow, nCol, strValue);
		}
	}
}

void CSttIecChsGridBase::UpdateAttrValue(CDvmValue *pData, int nRow, int nCol, const CString &strAttrID)
{
	CString strID = pData->m_strID + strAttrID;
	CDvmValue *pFind = (CDvmValue*)pData->FindByID(strID);

	if (pFind == NULL)
	{
		Show_ItemString(nRow, nCol, &g_strEmptyString);
	}
	else
	{
		Show_ItemString(nRow, nCol, &pFind->m_strValue);
	}
}

void CSttIecChsGridBase::UpdateDatas()
{
	if (m_pDatas == NULL)
	{
		return;
	}

	CExBaseObject *pObj = NULL;	
	POS pos = m_pDatas->GetHeadPosition();
	int nRowIndex = 0;

	while (pos != NULL)
	{
		pObj = m_pDatas->GetNext(pos);
		UpdateData(pObj, nRowIndex);
		nRowIndex++;
	}
}

void CSttIecChsGridBase::UpdateData(CExBaseObject *pData, int nRow)
{
	
}

CDataType* CSttIecChsGridBase::FindDataType(const CString &strDataType)
{
	CDataType *pDataType = CCfgDataMngrConstGlobal::FindIecRtdDataType(strDataType);

	return pDataType;
}

void CSttIecChsGridBase::Show_StaticDoubleString(CExBaseObject *pData, const int& nRow, const int& nCol, const CString &strString,long nPrecision)
{
	CString strDoubleString;
	double dValue = CString_To_double(strString);
	strDoubleString = stt_iec_rcd_get_double_string(dValue,nPrecision);
	Update_StaticString(pData, nRow, nCol, &strDoubleString);
}

void CSttIecChsGridBase::SetItemPic_RefCh(int nRow,int nCol,BOOL bUsePic)
{
	QGV_ITEM* pGV_ITEM = GetCell(nRow,nCol);

	if (pGV_ITEM == NULL)
	{
		return;
	}

	if (bUsePic)
	{
		pGV_ITEM->setIcon(m_oRefChPic_Icon);
	} 
	else
	{
		pGV_ITEM->setIcon(QIcon(""));
	}
}

void CSttIecChsGridBase::LoadRefChPic()
{
	CString strPicPath;
#ifdef _PSX_QT_WINDOWS_
	strPicPath = _P_GetResourcePath();
	strPicPath += _T("ReferPhase.png");
	m_oRefChPic_Icon.addFile(strPicPath);
#else
    strPicPath = ":/ctrls/images/ReferPhase.png";
    m_oRefChPic_Icon.addFile(strPicPath);
#endif
}

CExBaseList* CSttIecChsGridBase::GetCurrCapDevice()
{
	return NULL;
}

void CSttIecChsGridBase::mouseReleaseEventBase(QMouseEvent *ev)
{
	long nTimeLong = m_oTickCount.GetTickCountLong();
// 	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,/*_T("当前用时%ldms.")*/g_sLangTxt_currenttime.GetString(),nTimeLong); //lcq //2023-12-14 suyang 不需要打印当前用时信息，只显示重要信息

#ifdef _PSX_QT_LINUX_
	if ((nTimeLong>500)&&(!IsScrollMoving()))
#else
	if (nTimeLong>500)
#endif
	{
		CExBaseList *pCurrDev = GetCurrCapDevice();
		if ((pCurrDev != NULL)&&(g_theXSmartCapMngr->m_pX61850Cap))
		{
			CCapDeviceSmvBase *pCapDeviceSmvBase = (CCapDeviceSmvBase*)pCurrDev;
			long nCurrCh = currentRow();

			if (nCurrCh != pCapDeviceSmvBase->m_nRefChIndex)
			{
				g_bSmartCap_RecordNow = FALSE;
				SetItemPic_RefCh(pCapDeviceSmvBase->m_nRefChIndex,0,FALSE);
				pCapDeviceSmvBase->m_nRefChIndex = nCurrCh;
				SetItemPic_RefCh(nCurrCh,0,TRUE);
				g_theXSmartCapMngr->m_pX61850Cap->m_oCapDeviceChRecordMngr.UpdateAllRefRtVariable();
				g_bSmartCap_RecordNow = TRUE;

			}
		}
	}
}

void CSttIecChsGridBase::Update_StaticStringColor(CExBaseObject *pData, const int& nRow, const int& nCol, CString *pString)
{
	QGV_ITEM *pItem = GetCell(nRow,nCol);

	if (pItem != NULL)
	{
		CString strOldText;
		strOldText = pItem->text();
		pItem->setText(*pString);

		if (strOldText == (*pString))
		{
			pItem->setTextColor(Qt::black);
		} 
		else
		{
			pItem->setTextColor(Qt::red);
		}

		return;
	}

	pItem = new QGV_ITEM(*pString);
	pItem->setTextColor(Qt::black);
	pItem->nDataType = QT_GVET_NOEDIT;
	pItem->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	pItem->setFlags((Qt::ItemIsEnabled));

	PEXBASECELLDATA pVCellData = CreateExBaseCellData(pItem->lParam, (CString*)NULL, pData,NULL, NULL);
	pItem->lParam = (LPARAM)pVCellData;
	pVCellData->nVt = VCD_STRING;

	setItem(nRow,nCol,pItem);
}