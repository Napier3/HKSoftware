#include "SttIecSmvGrid_ChAttr.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/API/MathApi.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

#include <QApplication>

#include "SttIecRecordCbWidget.h"
#include "../../XLangResource_Native.h"
#include "../../../../Module/XLanguage/XLanguageResource.h"



#define  STT_SMVGRID_ChAttr_ColNum                      5
#define STT_SMVGRID_ChAttr_ColIndex_Desc                0
#define STT_SMVGRID_ChAttr_ColIndex_ChType              1
#define STT_SMVGRID_ChAttr_ColIndex_ChAngType           2
#define STT_SMVGRID_ChAttr_ColIndex_Coef                3
#define STT_SMVGRID_ChAttr_ColIndex_AmpValue            4


CSttIecSmvGrid_ChAttr::CSttIecSmvGrid_ChAttr(QWidget* pparent):CSttIecChsGridBase(pparent)
{
    m_pChType_DelegBase = NULL;
    m_bRunning = FALSE;
    m_pIecRcdFuncWidget = this;
    installEventFilter(this);
    LoadRefChPic();
}

CSttIecSmvGrid_ChAttr::~CSttIecSmvGrid_ChAttr()
{

}

void CSttIecSmvGrid_ChAttr::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
    CCapDeviceSmvBase *pCapDeviceSmvBase = NULL;

    if (m_pCapDevice != NULL)
    {
        pCapDeviceSmvBase = (CCapDeviceSmvBase*)m_pCapDevice;
        SetItemPic_RefCh(pCapDeviceSmvBase->m_nRefChIndex,0,FALSE);
    }

    m_pCapDevice = pCapDevice;
    CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();
    ShowDatas(pDvmDataset);

    if (m_pCapDevice != NULL)
    {
        pCapDeviceSmvBase = (CCapDeviceSmvBase*)m_pCapDevice;
        SetItemPic_RefCh(pCapDeviceSmvBase->m_nRefChIndex,0);
    }
}

void CSttIecSmvGrid_ChAttr::Release()
{
    delete this;
}

void CSttIecSmvGrid_ChAttr::InitGridTitle()
{
    CString astrGridTitle[STT_SMVGRID_ChAttr_ColNum];
    xlang_GetLangStrByFile(astrGridTitle[STT_SMVGRID_ChAttr_ColIndex_Desc], _T("IEC_ChDescription"));
    xlang_GetLangStrByFile(astrGridTitle[STT_SMVGRID_ChAttr_ColIndex_ChType], _T("IEC_ChType"));
    astrGridTitle[STT_SMVGRID_ChAttr_ColIndex_ChAngType] = /*_T("")*/g_sLangTxt_channelphase; //lcq
    xlang_GetLangStrByFile(astrGridTitle[STT_SMVGRID_ChAttr_ColIndex_Coef], _T("IEC_Coeff"));
    xlang_GetLangStrByFile(astrGridTitle[STT_SMVGRID_ChAttr_ColIndex_AmpValue], _T("Native_Amplitude"));
    //= {"", "","","",_T("")};
    int iGridWidth[STT_SMVGRID_ChAttr_ColNum]={350, 150, 150 ,150, 100};
    QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, STT_SMVGRID_ChAttr_ColNum);
    m_pChType_DelegBase = new QExBaseListComBoxDelegBase(this);
    setItemDelegateForColumn(STT_SMVGRID_ChAttr_ColIndex_ChType,m_pChType_DelegBase);
    m_pChAngType_DelegBase = new QExBaseListComBoxDelegBase(this);
    setItemDelegateForColumn(STT_SMVGRID_ChAttr_ColIndex_ChAngType,m_pChAngType_DelegBase);
}

void CSttIecSmvGrid_ChAttr::Config()
{
    CSttIecRcdFuncInterface::Config();
    UpdateCoefDatas();
}

void CSttIecSmvGrid_ChAttr::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
    CDvmData *pChData = (CDvmData*)pData;

    if (bInsertRow)
    {
        insertRow(NULL);
    }

    CCapDeviceSmvCh *pSmvCh = (CCapDeviceSmvCh*)((CCapDeviceBase*)m_pCapDevice)->FindByID(pChData->m_strID);

    if (pSmvCh == NULL)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("е(%s)δ.")*/g_sLangTxt_tablechannel.GetString(),pChData->m_strID.GetString()); //lcq
        return;
    }

    Show_StaticString(pSmvCh, nRow, STT_SMVGRID_ChAttr_ColIndex_Desc, &pChData->m_strName);
    Show_DataType_Val(pSmvCh, nRow, STT_SMVGRID_ChAttr_ColIndex_ChType, iecfg_Smv92ChDataType, &pSmvCh->m_nChType
        ,EndEditCell_Smv92ChSelChangged);
    Show_ChAngType(pSmvCh,nRow);
    Show_Double(pSmvCh, nRow, STT_SMVGRID_ChAttr_ColIndex_Coef, 6, &pSmvCh->m_fChRate, FALSE/*, EndEditCell_Value_Coef*/);
    ShowAttrValue(pChData, nRow, STT_SMVGRID_ChAttr_ColIndex_AmpValue, _T("$mag"), 3);
    setRowHeight(nRow,40);

    nRow++;
}


void CSttIecSmvGrid_ChAttr::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
    CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
    CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
    pXSttCap_61850->UpdateDvmDeviceDatas();

    UpdateDatas();
}

void CSttIecSmvGrid_ChAttr::EndEditCell_Value_Coef(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
    ASSERT (pVCellData != NULL);
    ASSERT (pVCellData->pString != NULL);

    if (pVCellData->nVt == VCD_DOUBLE)
    {
        double fValue = math_GetValueFromString(pCell->text());

        if (fabs(fValue-*(pVCellData->pdValue) ) > 0.00001)
        {
            *(pVCellData->pdValue) = fValue;
            //豸μ
            CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
            CRecordTest *pRecordTest = pXSttCap_61850->m_oCapDeviceChRecordMngr.m_pRecordTest;
            CCapDeviceSmvCh *pSmvCh = (CCapDeviceSmvCh *)pVCellData->pObj;
            long nChIndex = pRecordTest->m_pVariables->GetChIndexByID(pSmvCh->m_strID);

            if (nChIndex >= 0)
            {
                pRecordTest->g_pCoefValue[nChIndex]    = fValue;
                pRecordTest->m_pVariables->InitCalFuncPara(nChIndex);
            }
        }
    }
}

bool UpdateSingleChCoef(CCapDeviceSmvCh *pSmvCh,CRecordTest *pRecordTest)
{
    if ((pSmvCh == NULL)||(pRecordTest == NULL))
    {
        return false;
    }
    long nChIndex = pRecordTest->m_pVariables->GetChIndexByID(pSmvCh->m_strID);

    if (nChIndex < 0)
    {
        return false;
    }

    pSmvCh->InitAfterSetChType();
    pSmvCh->UpdateChDescByChTypeChAng();

    if (pSmvCh->GetParent() != NULL)
    {
        CExBaseObject *pParent = (CExBaseObject*)pSmvCh->GetParent();
        g_theXSmartCapMngr->m_pX61850Cap->SetName_DvmData(pParent->m_strID,pSmvCh->m_strID,pSmvCh->m_strName);
    }

    pRecordTest->g_pCoefValue[nChIndex] = pSmvCh->m_fChRate;
    pRecordTest->m_pVariables->InitCalFuncPara(nChIndex);
    return true;
}

void CSttIecSmvGrid_ChAttr::EndEditCell_Smv92ChSelChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
    ASSERT (pVCellData != NULL);
    ASSERT (pVCellData->pString != NULL);

    if (pVCellData->pExBaseList == NULL)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,/* _T("Row=%d  Col=%d  ")*/g_sLangTxt_DataTypeUnExist.GetString(), nRow, nCol); //lcq
        return;
    }

    CDataType *pDataType = (CDataType*)pVCellData->pExBaseList;
    ASSERT (pDataType != NULL);
    CString strTmp = pCell->text();

    CDataTypeValue *pValue = (CDataTypeValue*)pDataType->FindByName(strTmp);

    if (pValue == NULL)
    {
    }
    else
    {
        if (pVCellData->nVt == VCD_LONG)
        {
            long nValueIndex = pValue->GetIndex();
            *(pVCellData->pnValue) = nValueIndex;
            CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
            CRecordTest *pRecordTest = pXSttCap_61850->m_oCapDeviceChRecordMngr.m_pRecordTest;
            CCapDeviceSmvCh *pSmvCh = (CCapDeviceSmvCh *)pVCellData->pObj;

            if (UpdateSingleChCoef(pSmvCh,pRecordTest))
            {
                ((CSttIecSmvGrid_ChAttr*)pGrid)->UpdateChTypeChanged(nRow);
            }

            ((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
        }
        else
        {
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T(".")*/g_sLangTxt_faulttype.GetString()); //lcq
        }
    }
}

void CSttIecSmvGrid_ChAttr::EndEditCell_Smv92ChAngTypeChangged(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid)
{
    PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
    ASSERT (pVCellData != NULL);
    ASSERT (pVCellData->pString != NULL);

    if (pVCellData->pObj == NULL)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("Row=%d  Col=%d  ")*/g_sLangTxt_faulttype.GetString(), nRow, nCol); //lcq
        return;
    }

    CCapDeviceSmvCh *pSmvCh = (CCapDeviceSmvCh *)pVCellData->pObj;
    CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
    CRecordTest *pRecordTest = pXSttCap_61850->m_oCapDeviceChRecordMngr.m_pRecordTest;

    if (UpdateSingleChCoef(pSmvCh,pRecordTest))
    {
        ((CSttIecSmvGrid_ChAttr*)pGrid)->UpdateChAngTypeChanged(nRow);
    }

    ((QExBaseListGridBase*)pGrid)->SetModifiedFlag(pVCellData->pObj);
}

void CSttIecSmvGrid_ChAttr::UpdateCoefDatas()
{
    if ((m_pDatas == NULL)||(m_pCapDevice == NULL))
    {
        return;
    }

    DisConnectAll_SigSlot();
    CExBaseObject *pObj = NULL;
    POS pos = m_pDatas->GetHeadPosition();
    CCapDeviceSmvCh *pSmvCh = NULL;
    int nRowIndex = 0;

    while (pos != NULL)
    {
        pObj = m_pDatas->GetNext(pos);
        pSmvCh = (CCapDeviceSmvCh*)((CCapDeviceBase*)m_pCapDevice)->FindByID(pObj->m_strID);

        if (pSmvCh != NULL)
        {
            Show_Double(pSmvCh, nRowIndex, STT_SMVGRID_ChAttr_ColIndex_Coef, 6, &pSmvCh->m_fChRate, FALSE/*, EndEditCell_Value_Coef*/);
        }

        nRowIndex++;
    }

    ConnectAll_SigSlot();
}

void CSttIecSmvGrid_ChAttr::UpdateData(CExBaseObject *pData, int nRow)
{
    CDvmData *pChData = (CDvmData*)pData;

    ShowAttrValue(pChData, nRow, STT_SMVGRID_ChAttr_ColIndex_AmpValue, _T("$mag"));
}

void CSttIecSmvGrid_ChAttr::Show_ChAngType(CCapDeviceSmvCh *pSmvCh,int& nRow)
{
    if (pSmvCh->m_nChType == CAPDEVICE_CHTYPE_T)
    {
        Show_StaticString(pSmvCh, nRow, STT_SMVGRID_ChAttr_ColIndex_ChAngType, _T("--"));
    }
    else if (pSmvCh->m_nChType == CAPDEVICE_CHTYPE_I)
    {
        Show_DataType_Val(pSmvCh, nRow, STT_SMVGRID_ChAttr_ColIndex_ChAngType, iecfg_SmvChAngTypeI, &pSmvCh->m_nChAngType
            ,EndEditCell_Smv92ChAngTypeChangged);
    }
    else if (pSmvCh->m_nChType == CAPDEVICE_CHTYPE_U)
    {
        Show_DataType_Val(pSmvCh, nRow, STT_SMVGRID_ChAttr_ColIndex_ChAngType, iecfg_SmvChAngTypeU, &pSmvCh->m_nChAngType
            ,EndEditCell_Smv92ChAngTypeChangged);
    }
}

void CSttIecSmvGrid_ChAttr::UpdateChAngTypeChanged(int& nRow)
{
    if ((m_pDatas == NULL)||(m_pCapDevice == NULL))
    {
        return;
    }

    CExBaseObject *pObj = m_pDatas->GetAt(nRow);

    if (pObj == NULL)
    {
        return;
    }

    CCapDeviceBase *pCapDeviceBase = (CCapDeviceBase*)m_pCapDevice;
    CCapDeviceSmvCh *pSmvCh = (CCapDeviceSmvCh*)pCapDeviceBase->FindByID(pObj->m_strID);

    if (pSmvCh != NULL)
    {
        pCapDeviceBase->SetDeviceChMaps();
        DisConnectAll_SigSlot();
        Show_StaticString(pSmvCh, nRow, STT_SMVGRID_ChAttr_ColIndex_Desc, &pSmvCh->m_strName);
        Show_Double(pSmvCh, nRow, STT_SMVGRID_ChAttr_ColIndex_Coef, 6, &pSmvCh->m_fChRate, FALSE/*, EndEditCell_Value_Coef*/);
        ConnectAll_SigSlot();

        if (g_pSttIecRecordCbWidget != NULL)
        {
            g_pSttIecRecordCbWidget->UpdateSVDatasetsPowerVector();
        }
    }
}

void CSttIecSmvGrid_ChAttr::UpdateChTypeChanged(int& nRow)
{
    if ((m_pDatas == NULL)||(m_pCapDevice == NULL))
    {
        return;
    }

    CExBaseObject *pObj = m_pDatas->GetAt(nRow);

    if (pObj == NULL)
    {
        return;
    }

    CCapDeviceSmvCh *pSmvCh = (CCapDeviceSmvCh*)((CCapDeviceBase*)m_pCapDevice)->FindByID(pObj->m_strID);

    if (pSmvCh != NULL)
    {
        DisConnectAll_SigSlot();
        Show_StaticString(pSmvCh, nRow, STT_SMVGRID_ChAttr_ColIndex_Desc, &pSmvCh->m_strName);
        Show_ChAngType(pSmvCh,nRow);
        Show_Double(pSmvCh, nRow, STT_SMVGRID_ChAttr_ColIndex_Coef, 6, &pSmvCh->m_fChRate, FALSE/*, EndEditCell_Value_Coef*/);
        ConnectAll_SigSlot();

        if (g_pSttIecRecordCbWidget != NULL)
        {
            g_pSttIecRecordCbWidget->UpdateSVDatasetsPowerVector();
        }
    }

// 	QGV_ITEM *pCell = GetCell(nRow,STT_SMVGRID_ChAttr_ColIndex_Coef);
//
// 	if (pCell == NULL)
// 	{
// 		return;
// 	}
//
// 	PEXBASECELLDATA pVCellData = (_ExBaseCellData*)pCell->lParam;
// 	ASSERT (pVCellData != NULL);
//
// 	if (pVCellData->nVt == VCD_DOUBLE)
// 	{
// 		double fValue =  math_GetValueFromString(pCell->text());
// 		CString strTmp;
//
// 		if (fabs(fValue-*(pVCellData->pdValue) ) > 0.0000001)
// 		{
// 			long nPrecision = (pCell->dwValue >> 16) & 0xFFFF;
//
// 			if (nPrecision > 0 )
// 			{
// 				CString strFormat;
// 				strFormat.Format(_T("%%.%dlf"), nPrecision);
// 				strTmp.Format(strFormat.GetString(), *(pVCellData->pdValue));
// 				pCell->setText(strTmp);
// 			}
// 			else
// 			{
// 				math_GetStringFromValue(strTmp, *(pVCellData->pdValue), _T(""), pCell->dwValue);
// 				pCell->setText(strTmp);
// 			}
//
// 			SetModifiedFlag(pVCellData->pObj);
// 		}
// 	}
}

bool CSttIecSmvGrid_ChAttr::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        QMouseEvent *pMouseEvent = (QMouseEvent *)event;
        m_bRunning = TRUE;
        mouseDoubleClickEvent((QMouseEvent *)pMouseEvent);
        m_bRunning = FALSE;
        return  true;
    }

    return QExBaseListGridBase::eventFilter(obj,event);

}

void CSttIecSmvGrid_ChAttr::mousePressEvent(QMouseEvent * event)
{
    if (m_bRunning)
    {
        QExBaseListGridBase::mousePressEvent(event);
        return;
    }

    QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
    m_oTickCount.Enter();
    QApplication::postEvent(this,pEvent);
    QExBaseListGridBase::mousePressEvent(event);

}

void CSttIecSmvGrid_ChAttr::mouseReleaseEvent(QMouseEvent *event)
{
    mouseReleaseEventBase(event);
    QExBaseListGridBase::mouseReleaseEvent(event);
}

CExBaseList* CSttIecSmvGrid_ChAttr::GetCurrCapDevice()
{
    return  (CExBaseList*)m_pCapDevice;
}
