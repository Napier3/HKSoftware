#include "SttIecFT3Grid_RT.h"
#include "../../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../../XLangResource_Native.h"
#include "../../../UI/Module/CommonMethod/commonMethod.h"
#include "../../../../../Module/SmartCap/61850Cap/CapDevice/CapDevice6044.h"
#include <QApplication>

CSttIecFT3Grid_RT::CSttIecFT3Grid_RT(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
	m_pCfgChsRef = NULL;
	
	m_bRunning = FALSE;
	installEventFilter(this);
	LoadRefChPic();
}

CSttIecFT3Grid_RT::~CSttIecFT3Grid_RT()
{

}

void CSttIecFT3Grid_RT::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	CCapDeviceSmvBase *pCapDeviceSmvBase = NULL;

	if (m_pCapDevice != NULL)
	{
		pCapDeviceSmvBase = (CCapDeviceSmvBase*)m_pCapDevice;
		SetItemPic_RefCh(pCapDeviceSmvBase->m_nRefChIndex,0,FALSE);
	}

	SetEditable(FALSE);//设置下拉框不可编辑
	m_pCapDevice = pCapDevice;
	CIecCfgDataBase *pCfgDataBase = pCapDevice->GetIecCfgData();
	m_pCfgChsRef = pCfgDataBase->m_pCfgChs;
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();
	ShowDatas(pDvmDataset);

	if (m_pCapDevice != NULL)
	{
		pCapDeviceSmvBase = (CCapDeviceSmvBase*)m_pCapDevice;
		SetItemPic_RefCh(pCapDeviceSmvBase->m_nRefChIndex,0);
	}
}

void CSttIecFT3Grid_RT::Release()
{
	delete this;
}

void CSttIecFT3Grid_RT::mousePressEvent(QMouseEvent * event)
{
	m_oTickCount.Enter();
// 	QExBaseListGridBase::mousePressEvent(event);
	if (m_bRunning)
	{
		QExBaseListGridBase::mousePressEvent(event);
		return;
	}

	QMouseEvent *pEvent = new QMouseEvent(QEvent::MouseButtonDblClick,event->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);
	QApplication::postEvent(this,pEvent);
	QExBaseListGridBase::mousePressEvent(event);

}

void CSttIecFT3Grid_RT::mouseReleaseEvent(QMouseEvent *event)
{
	mouseReleaseEventBase(event);
	QExBaseListGridBase::mouseReleaseEvent(event);
}

bool CSttIecFT3Grid_RT::eventFilter(QObject *obj, QEvent *event)
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



CExBaseList* CSttIecFT3Grid_RT::GetCurrCapDevice()
{
	return (CExBaseList*)m_pCapDevice;
}

void CSttIecFT3Grid_RT::InitGridTitle()
{
	CString astrGridTitle[5];
	xlang_GetLangStrByFile(astrGridTitle[0], _T("Native_Channel"));
	xlang_GetLangStrByFile(astrGridTitle[1], _T("IEC_ChType"));
	xlang_GetLangStrByFile(astrGridTitle[2], _T("IEC_ChMaps"));
	xlang_GetLangStrByFile(astrGridTitle[3], _T("IEC_ChByteLen"));
	/*astrGridTitle[1] = "通道类型";
	astrGridTitle[2] = "通道映射";
	astrGridTitle[3] = "字节长度";*/
	xlang_GetLangStrByFile(astrGridTitle[4], _T("sValue"));
	//= {"通道描述", "通道类型","通道映射","字节长度","数值"};
	int iGridWidth[5]={200, 150, 150, 150, 150};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 5);
}

void CSttIecFT3Grid_RT::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pChData = (CDvmData*)pData;

	if (bInsertRow)
	{
		insertRow(NULL);
	}

	ShowDataEx(pChData, nRow);
	nRow++;
}

void CSttIecFT3Grid_RT::ShowDataEx(CDvmData *pData, int nRow)
{
	if (m_pCfgChsRef == NULL)
	{
		return;
	}

	CIecCfg6044CommonCh *pIecCfgFT3Ch = (CIecCfg6044CommonCh *)m_pCfgChsRef->FindByID(pData->m_strID);

	Update_StaticString(pData,nRow,0,&pIecCfgFT3Ch->m_strName);
//	Update_StaticString(pData, nRow, 1, &pData->m_strChType);

	if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
	{
		Show_DataType_Val(pData,nRow,1,iecfg_SmvCommon6044DCChDataType,&pIecCfgFT3Ch->m_strChType);
	}
	else
	{
		Show_DataType_Val(pData,nRow,1,iecfg_SmvCommon6044ChInDataType,&pIecCfgFT3Ch->m_strChType);
	}

//	Show_DataType_Val(pData, nRow, 1, iecfg_SmvCommon6044DCChDataType, &pIecCfgFT3Ch->m_strChType);
	UpdateData_ByDataType(pData, pIecCfgFT3Ch,nRow);
	Show_Long(pData,nRow,3,&pIecCfgFT3Ch->m_nChLenth);

	SetItemEnable(nRow,1,FALSE);
	SetItemEnable(nRow,2,FALSE);
	SetItemEnable(nRow,3,FALSE);
	SetItemEnable(nRow,4,FALSE);

}

void CSttIecFT3Grid_RT::UpdateData_ByDataType(CDvmData *pData, CIecCfg6044CommonCh *pIecCfgFT3Ch,int nRow)
 {
	if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_DCCur)
	{
		Show_DataType_Val(pData, nRow, 2,iecfg_SmvAppChDataType_DCI, &pIecCfgFT3Ch->m_strAppChID);
		Show_Long(pData,nRow,4,&pIecCfgFT3Ch->m_nValue);
	} 
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_DCVol)
	{
		Show_DataType_Val(pData, nRow, 2,iecfg_SmvAppChDataType_DCU, &pIecCfgFT3Ch->m_strAppChID);
		Show_Long(pData,nRow,4,&pIecCfgFT3Ch->m_nValue);
	} 
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_NeutralU)
	{
		Show_DataType_Val(pData, nRow, 2,iecfg_SmvAppChDataType_NeutralU, &pIecCfgFT3Ch->m_strAppChID);
		Show_Long(pData,nRow,4,&pIecCfgFT3Ch->m_nValue);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_StateValue)
{
		Show_DataType_Val(pData, nRow, 2,iecfg_SmvAppChDataType_StateValue, &pIecCfgFT3Ch->m_strAppChID);

		CString strTempDataType = GetDataTypeValue(iecfg_SmvAppChDataType_StateValue,&pIecCfgFT3Ch->m_strAppChID);
		if (strTempDataType == /*_T("单点")*/g_sLangTxt_GOOSE_Single.GetString())
	{
		CString strTemp;
			/*if (!pIecCfgFT3Ch->m_nValue)
		{
				Update_StaticStringColor(pIecCfgFT3Ch, nRow, 4, &g_strEmptyString);
		}
			else*/ if (pIecCfgFT3Ch->m_nValue == 0)
		{
			strTemp = _T("FALSE");
				Update_StaticStringColor(pData, nRow, 4, &strTemp);
			}
			else if(pIecCfgFT3Ch->m_nValue == 1)
			{
				strTemp = _T("TRUE");
				Update_StaticStringColor(pData, nRow, 4, &strTemp);
			}
			else
			{
				Update_StaticStringColor(pData, nRow, 4, &g_strEmptyString);
			}
		}
		else
		{
			//Update_StaticStringColor(pData, nRow, 4, &pIecCfgFT3Ch->m_nValue);
			Show_DataType_Val(pData,nRow,4,g_strGsChDtID_goose_out_ch_double_def_value,&pIecCfgFT3Ch->m_nValue);
		}
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Other)
	{
		Show_DataType_Val(pData, nRow, 2,iecfg_SmvAppChDataType_Other, &pIecCfgFT3Ch->m_strAppChID);

		//两个都是“其它”时,可以独立设置  zhouhj 2023.9.13
		if (pIecCfgFT3Ch->m_strAppChID == iecfg_SmvChDataType_Val_Other)
		{
			Show_Long(pData,nRow,4,&pIecCfgFT3Ch->m_nValue);
		} 
		else
		{
			Show_StaticString(pData,nRow,4,_T("--"));
		}
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6Vol)
	{
		Show_DataType_Val(pData, nRow, 2,iecfg_SmvAppChDataType_6U, &pIecCfgFT3Ch->m_strAppChID);
		Show_Long(pData,nRow,4,&pIecCfgFT3Ch->m_nValue);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Vol)
	{
		Show_DataType_Val(pData, nRow, 2,iecfg_SmvAppChDataType_U, &pIecCfgFT3Ch->m_strAppChID);
		Show_Long(pData,nRow,4,&pIecCfgFT3Ch->m_nValue);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrProt)
	{
		Show_DataType_Val(pData, nRow, 2,iecfg_SmvAppChDataType_6I, &pIecCfgFT3Ch->m_strAppChID);
		Show_Long(pData,nRow,4,&pIecCfgFT3Ch->m_nValue);
	}
	else if ((pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Curr)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure))
	{
		Show_DataType_Val(pData, nRow, 2,iecfg_SmvAppChDataType_I, &pIecCfgFT3Ch->m_strAppChID);
		Show_Long(pData,nRow,4,&pIecCfgFT3Ch->m_nValue);
		}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrMeasure)
	{
		Show_DataType_Val(pData, nRow, 2,iecfg_SmvAppChDataType_6I,&pIecCfgFT3Ch->m_strAppChID);
		Show_Long(pData,nRow,4,&pIecCfgFT3Ch->m_nValue);
	}
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前SMVFT3通道映射出错(%s)."),pIecCfgFT3Ch->m_strChType.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_CurSmvErr.GetString(),pIecCfgFT3Ch->m_strChType.GetString());
	}
}

double CSttIecFT3Grid_RT::GetChValue(CDvmData *pDvmData,CIecCfg6044CommonCh *pIecCfgFT3Ch)
{
	CString strID = pDvmData->m_strID + _T("$mag");
	CDvmValue *pFind = (CDvmValue*)pDvmData->FindByID(strID);

	if (pFind != NULL)
	{
		double dValue = CString_To_double(pFind->m_strValue);
		dValue *= st_GetCapDeviceSVRate(pIecCfgFT3Ch,g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC);
		return dValue;
	}

	return 0.0f;
}


CString CSttIecFT3Grid_RT::GetDataTypeValue(CString strDataType, CString *pstrValue)
{
	CDataType *pDataType = FindDataType(strDataType);
	CDataTypeValue *pValue = NULL;

	if (pDataType != NULL)
	{
		pValue = (CDataTypeValue*)pDataType->FindByID( *pstrValue );

		if (pValue == NULL)
		{
			pValue = (CDataTypeValue*)pDataType->GetHead();

			if (pValue != NULL)
			{
				*pstrValue = pValue->m_strID;
			}
		}
	}
	return pValue->m_strName;
}

void CSttIecFT3Grid_RT::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	//pXCapPkgBufferMngr->LogBufferPos();
	pXSttCap_61850->UpdateDvmDeviceDatas();
	//pCapDevice->UpdateDvmDeviceDatas();

	/*CIecCfgDataBase *pIecCfgData = pCapDevice->GetIecCfgData();
	ShowDatas((CExBaseList*)pIecCfgData->GetHead());*/
	UpdateDatas();

// 	CCapDeviceSmvCh *pCapDevFT3Ch = (CCapDeviceSmvCh *)pCapDevice->GetAt(2);
// 
// 	if (pCapDevFT3Ch != NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%s,m_nChRateIndex=%u,m_fChRate=%lf"),pCapDevFT3Ch->m_strName.GetString(),
// 			pCapDevFT3Ch->m_nChRateIndex,pCapDevFT3Ch->m_fChRate);
// 	}
}

void CSttIecFT3Grid_RT::ShowData_AnalogChValue(CDvmData *pChData, int nRow,CIecCfg6044CommonCh *pIecCfgFT3Ch,BOOL bIsDcCh)
{
	double dMagValue = 0.0f,dAngValue = 0.0f;
	CString strID,strText;
	CDvmValue *pDvmValue = NULL;

	//zhouhj 2024.4.9 删除对第一列的特殊处理
// 	if (nRow == 0)
// 	{
// 		dMagValue = GetChValue(pChData,pIecCfgFT3Ch);
// 	} 
// 	else
	{
		strID = pChData->m_strID + _T("$mag");
		pChData->GetChildValueByID(strID,dMagValue);
	}

	strID = pChData->m_strID + _T("$ang");
	pChData->GetChildValueByID(strID,dAngValue);

	if (bIsDcCh)
	{
		strText.Format(_T("%.03lf"),dMagValue);
	} 
	else
	{
		//2024-10-23 wuxinyi 修改乱码
#ifdef _PSX_QT_WINDOWS_
		CString strMagValue, strAngValue;
		strMagValue.Format(_T("%.03lf"),dMagValue);
		strAngValue.Format(_T("%.03lf"),dAngValue);
		strText = strMagValue;
		strText += QString::fromLocal8Bit("∠");
		strText += strAngValue;
		strText += QString::fromLocal8Bit("°");
#else
		strText.Format(_T("%.03lf ∠%.03lf°"),dMagValue,dAngValue);
#endif // _PSX_QT_WINDOWS_
	}

	Show_StaticString(pChData,nRow,4,strText);
}

void CSttIecFT3Grid_RT::UpdateData(CExBaseObject *pData, int nRow)
{
	if (m_pCfgChsRef == NULL)
	{
		return;
	}

	CDvmData *pChData = (CDvmData*)pData;
	CCapDevice6044 *pCapDevice = (CCapDevice6044 *)m_pCapDevice;
	CIecCfg6044CommonCh *pIecCfgFT3Ch = (CIecCfg6044CommonCh *)m_pCfgChsRef->FindByID(pChData->m_strID);

	if ((pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6Vol)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Vol)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrProt)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Curr)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_CurrMeasure)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrMeasure))
	{
		ShowData_AnalogChValue(pChData,nRow,pIecCfgFT3Ch,FALSE);
	}
	else if ((pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_DCCur)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_DCVol)
		||(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_NeutralU))
	{
		ShowData_AnalogChValue(pChData,nRow,pIecCfgFT3Ch,TRUE);
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_StateValue)
	{

		CString strTemp;
		strTemp = GetDataTypeValue(iecfg_SmvAppChDataType_StateValue,&pIecCfgFT3Ch->m_strAppChID);

		if (strTemp == /*_T("单点")*/g_sLangTxt_GOOSE_Single.GetString())
		{
			if (pCapDevice->m_oPrevDatas.pDatas[nRow].dwValue == 0)
			{
				strTemp = _T("FALSE");
			}
			else if(pCapDevice->m_oPrevDatas.pDatas[nRow].dwValue == 1)
			{
				strTemp = _T("TRUE");
			}
			else
			{
				strTemp = g_strEmptyString;
			}

			Update_StaticStringColor(pData, nRow, 4, &strTemp);
		}
		else
		{
            Show_Long(pData,nRow,4,&pCapDevice->m_oPrevDatas.pDatas[nRow].dwValue);
		}
	}
	else if (pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Other)
	{
		//两个都是“其它”时,可以独立设置  zhouhj 2023.9.13
		if (pIecCfgFT3Ch->m_strAppChID == iecfg_SmvChDataType_Val_Other)
		{
            Show_Long(pData,nRow,4,&pCapDevice->m_oPrevDatas.pDatas[nRow].dwValue);
		} 
		else
		{
			Show_StaticString(pData,nRow,4,_T("--"));
		}
	}
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前SMVFT3通道映射出错(%s)."),pIecCfgFT3Ch->m_strChType.GetString());
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_Gradient_CurSmvErr.GetString(),pIecCfgFT3Ch->m_strChType.GetString());
	}
}

