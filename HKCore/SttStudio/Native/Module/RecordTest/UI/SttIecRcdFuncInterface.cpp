#include "SttIecRcdFuncInterface.h"

#include "SttIecRecordSysSetDlg.h"
#include "MUTest/SttMUTestChsSetDlg.h"
#include "../../Module/SmartCap/XSmartCapMngr.h"
#include "../../Module/SmartCap/61850Cap/CapDevice/CapDeviceGoose.h"
#include "../../UI/SttTestCntrFrameBase.h"
#include "SttIecRecordCbWidget.h"
#include "MUTest/SttMUTestIecCbSelWidget.h"
#include "../../XLangResource_Native.h"

#ifdef _USE_SoftKeyBoard_
#include"../../UI/SoftKeyboard/SoftKeyBoard.h"
#endif


CSttIecRcdFuncInterface::CSttIecRcdFuncInterface()
{
	m_pIecRcdFuncWidget = NULL;
	m_pCapDevice = NULL;
	m_bMUTestMode = FALSE;
}

CSttIecRcdFuncInterface::~CSttIecRcdFuncInterface()
{

}


void CSttIecRcdFuncInterface::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
}

void CSttIecRcdFuncInterface::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	
}

BOOL CSttIecRcdFuncInterface::NeedNextAndPrev()
{
	return FALSE;
}

BOOL CSttIecRcdFuncInterface::NeedAddToSubPub()
{
	return FALSE;
}

void CSttIecRcdFuncInterface::NextPage()
{

}

void CSttIecRcdFuncInterface::PrevPage()
{

}

BOOL CSttIecRcdFuncInterface::IsToSubBtn()
{
	if (m_pCapDevice == NULL)
	{
		return TRUE;
	}

	if (m_pCapDevice->GetClassID() == CPDCLASSID_DEVICEGOOSE)
	{
		CCapDeviceGoose *pCapDeviceGs = (CCapDeviceGoose*)m_pCapDevice;
		CIecCfgGinDatas* pIecCfgGinDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGinMngr();
		CIecCfgGinData* pIecCfgGinData = (CIecCfgGinData*)pIecCfgGinDatas->FindByAppIDFiber(pCapDeviceGs->m_dwAppID,pCapDeviceGs->m_nFiberIndex);

		if (pIecCfgGinData == NULL)
		{
			return TRUE;
		}

		return FALSE;

	}
	return TRUE;

}


void CSttIecRcdFuncInterface::AddToSub()
{
	if (m_pCapDevice == NULL)
	{
		return;
	}

	CCapDeviceBase *pCapDeviceBase = (CCapDeviceBase*)m_pCapDevice;
	if (pCapDeviceBase->m_oAnalysisResults.nPkgNum<=0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,/*_T("当前解析的报文帧数为0,需收到报文后,才能关联.")*/g_sLangTxt_Native_CurrPsdM0AssocAftRcvM.GetString());
		return;
	}

	if (m_pCapDevice->GetClassID() == CPDCLASSID_DEVICEGOOSE)
	{
		CCapDeviceGoose *pCapDeviceGs = (CCapDeviceGoose*)m_pCapDevice;
		CIecCfgGinDatas* pIecCfgGinDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGinMngr();
		CIecCfgGinData* pIecCfgGinData = (CIecCfgGinData*)pIecCfgGinDatas->FindByAppIDFiber(pCapDeviceGs->m_dwAppID,pCapDeviceGs->m_nFiberIndex);

		if (pIecCfgGinData != NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("GOOSE控制块(AppID=0X%04X),已添加订阅到光口%ld,无需重复添加.")*/g_sLangTxt_Gradient_Appscribed.GetString(),pCapDeviceGs->m_dwAppID,
				pCapDeviceGs->m_nFiberIndex+1); //lcq
			return;
		}
// 		else if (pCapDeviceGs->m_pIecCfgData != NULL)
// 		{
// 			pIecCfgGinData = (CIecCfgGinData*)pCapDeviceGs->m_pIecCfgData->Clone();
// 			pIecCfgGinData->m_nUseFlag = 1;
// 			pIecCfgGinData->m_nFiberIndex = pCapDeviceGs->m_nFiberIndex;
// 			return;
// 		}

		pIecCfgGinData = (CIecCfgGinData*)pIecCfgGinDatas->AddNewIecCfgData();
		pCapDeviceGs->SetIecCfgGin_ByCapDevice(pIecCfgGinData);
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("GOOSE控制块(AppID=0X%04X),添加订阅到光口%ld成功.")*/g_sLangTxt_Gradient_SEcontrolSus.GetString(),pCapDeviceGs->m_dwAppID,
			pCapDeviceGs->m_nFiberIndex+1); //lcq
		g_oSttTestResourceMngr.SaveDefaultIec61850Config();
	}

}

void CSttIecRcdFuncInterface::AddToPub()
{
	if (m_pCapDevice == NULL)
	{
		return;
	}

	CCapDeviceBase *pCapDeviceBase = (CCapDeviceBase*)m_pCapDevice;
	if (pCapDeviceBase->m_oAnalysisResults.nPkgNum<=0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ASSIST,/*_T("当前解析的报文帧数为0,需收到报文后,才能关联.")*/g_sLangTxt_Native_CurrPsdM0AssocAftRcvM.GetString());
		return;
	}

	if (m_pCapDevice->GetClassID() == CPDCLASSID_DEVICEGOOSE)
	{
		CCapDeviceGoose *pCapDeviceGs = (CCapDeviceGoose*)m_pCapDevice;
		CIecCfgGoutDatas* pIecCfgGoutDatas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetGoutMngr();
		CIecCfgGoutData* pIecCfgGoutData = (CIecCfgGoutData*)pIecCfgGoutDatas->FindByAppIDFiber(pCapDeviceGs->m_dwAppID,pCapDeviceGs->m_nFiberIndex);

		if (pIecCfgGoutData != NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("GOOSE控制块(AppID=0X%04X),已添加发布到光口%ld,无需重复添加.")*/g_sLangTxt_Gradient_AppscribedFa.GetString(),pCapDeviceGs->m_dwAppID,
				pCapDeviceGs->m_nFiberIndex+1);  //lcq
			return;
		}

		CIecCfgGinData* pIecCfgGinData = (CIecCfgGinData*)pCapDeviceGs->GetIecCfgData();

		if (pIecCfgGinData != NULL)
		{
			pIecCfgGoutData = (CIecCfgGoutData*)pIecCfgGoutDatas->AddNewIecCfgData();
			pIecCfgGinData->CopyToGoutData(pIecCfgGoutData);
			pIecCfgGoutData->m_nUseFlag = 1;
			pIecCfgGoutData->m_nFiberIndex = pCapDeviceGs->m_nFiberIndex;
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("GOOSE控制块(AppID=0X%04X),添加发布到光口%ld成功.")*/g_sLangTxt_Gradient_AppFascribedFa.GetString(),pCapDeviceGs->m_dwAppID,
				pCapDeviceGs->m_nFiberIndex+1);
		}	
		else
		{
			pIecCfgGoutData = (CIecCfgGoutData*)pIecCfgGoutDatas->AddNewIecCfgData();
			pCapDeviceGs->SetIecCfgGout_ByCapDevice(pIecCfgGoutData);
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("GOOSE控制块(AppID=0X%04X),添加发布到光口%ld成功.")*/g_sLangTxt_Gradient_AppFascribedFa.GetString(),pCapDeviceGs->m_dwAppID,
				pCapDeviceGs->m_nFiberIndex+1);
		}

		g_oSttTestResourceMngr.SaveDefaultIec61850Config();
	}
}

BOOL CSttIecRcdFuncInterface::NeedConfig()
{
	return FALSE;
}

void CSttIecRcdFuncInterface::Config()
{
	QWidget *pParent = m_pIecRcdFuncWidget;

	if (m_pIecRcdFuncWidget != NULL)
	{
		pParent = (QWidget*)m_pIecRcdFuncWidget->parent();
	}

	BOOL bIsFT3Device = FALSE;

	if (m_pCapDevice != NULL)
	{
		if (m_pCapDevice->GetClassID() == CPDCLASSID_DEVICE6044)
		{
			bIsFT3Device = TRUE;
		}
	}

//#ifndef _PSX_QT_LINUX_
	if (m_bMUTestMode)
	{
		CIecCfgDataBase *pIecCfgData =NULL;

		if (m_pCapDevice != NULL)
		{
			pIecCfgData = ((CCapDeviceBase*)m_pCapDevice)->GetIecCfgData();
		}

		QSttMUTestChsSetDlg oSttMUTestChsSetDlg(pParent,g_pSttMUTestIecCbSelWidget->IsFT3MUTest());
		oSttMUTestChsSetDlg.setWindowModality(Qt::WindowModal);
		oSttMUTestChsSetDlg.setFont(*g_pSttGlobalFont);
		CIecCfgSysParas* pIecCfgSysParas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSysParasMngr();
		oSttMUTestChsSetDlg.InitData(pIecCfgData,&g_oCapAnalysisConfig,pIecCfgSysParas->GetPrimRatesIn());

		//2023/9/7 wjs 加入键盘
#ifdef _USE_SoftKeyBoard_
		Global_SoftKeyBoardAttachObj(&oSttMUTestChsSetDlg);
#endif

		if (oSttMUTestChsSetDlg.exec() == QDialog::Accepted)
		{
			if (oSttMUTestChsSetDlg.m_nParasModifyType == STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc)
			{
				g_pSttIecRecordCbWidget->UpdateFirstCirclePlot(STT_MUTEST_CHSSET_MODIFY_TYPE_RateAccLevelDesc);
//  				QSttMUTestRecordCbWidget *pWidget = (QSttMUTestRecordCbWidget*)g_pSttIecRecordCbWidget;
// 				pWidget->m_pSttFirstCwWidget->updatePlots();
				g_oSttTestResourceMngr.SaveDefaultIec61850Config();
				g_oCapAnalysisConfig.Save();
				((CXSttCap_61850*)g_theXSmartCapMngr->m_pX61850Cap)->SetPT_CT_Rates(pIecCfgSysParas->GetPrimRatesIn(),bIsFT3Device);
				g_theXSmartCapMngr->m_pX61850Cap->UpdateAfterMUChsSet();//20220612 在设备完变比后,更新SMV通道的Rate
				UpdateChName();

				//名称、通道选择及准确度修改会影响到通讯模型,故此处保存模型
				CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
				CString strFile;
				strFile += _P_GetDBPath();
				strFile += _T("SttIecRecordDetectDvm.xml");
				pXSttCap_61850->m_pDvmDevice->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
			}
			else if (oSttMUTestChsSetDlg.m_nParasModifyType == STT_MUTEST_CHSSET_MODIFY_TYPE_ChTypeMap)
			{
				g_pSttIecRecordCbWidget->BtnBack();//通道映射修改后,需要重新进入探测界面
				g_pSttIecRecordCbWidget->UpdateFirstCirclePlot(STT_MUTEST_CHSSET_MODIFY_TYPE_ChTypeMap);
				//zhouhj 2023.11.2 
// 				QSttMUTestRecordCbWidget *pWidget = (QSttMUTestRecordCbWidget*)g_pSttIecRecordCbWidget;
// 				pWidget->m_pSttFirstCwWidget->updatePlots();
				//如果是Tab模式,则调用刷新接口
				if (g_pSttIecRecordCbWidget->IsTabUI_Mode())
				{
					if (g_pSttMUTestIecCbSelWidget != NULL)
					{
						g_pSttMUTestIecCbSelWidget->Refresh_MUTest();
					}
				}
			}
		}
		
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::ReAttachObj();
#endif
		
		//添加当接收通道窗口关闭时，更新主界面
		IecRcdFunc((CCapDeviceBase *)m_pCapDevice);
		
	} 
	else
//#endif
	{
		QSttIecRecordSysSetDlg oIecRecordSysSetDlg(pParent);
		oIecRecordSysSetDlg.setWindowModality(Qt::WindowModal);
		oIecRecordSysSetDlg.setFont(*g_pSttGlobalFont);
		CIecCfgSysParas* pIecCfgSysParas = g_oSttTestResourceMngr.m_oIecDatasMngr.GetSysParasMngr();
		oIecRecordSysSetDlg.InitData(&g_oCapAnalysisConfig,pIecCfgSysParas->GetPrimRatesIn());

		Global_SoftKeyBoardAttachObj(&oIecRecordSysSetDlg);
		oIecRecordSysSetDlg.exec();
#ifdef _USE_SoftKeyBoard_
		QSoftKeyBoard::ReAttachObj();
#endif
		g_oSttTestResourceMngr.SaveDefaultIec61850Config();
		g_oCapAnalysisConfig.Save();
		((CXSttCap_61850*)g_theXSmartCapMngr->m_pX61850Cap)->SetPT_CT_Rates(pIecCfgSysParas->GetPrimRatesIn(),bIsFT3Device);
		g_theXSmartCapMngr->m_pX61850Cap->UpdateCapDevicesRecordSmvChRates();//20220612 在设备完变比后,更新SMV通道的Rate
	}
}

void CSttIecRcdFuncInterface::UpdateChName()
{

}


//2022-5-28  lijunqing
//数据集下以DvmData展示的控制块分析结果：根据CapDevice，获取DvmData
BOOL CSttIecRcdFuncInterface::FindDvmDataForCtrl(CCapDeviceBase *pCapDevice, const CString &strDatasetID, CDvmDataset **ppDsRet, CDvmData **ppDataRet)
{
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();
	CString strID = pDvmDataset->m_strID.Mid(2);

	CDvmLogicDevice *pLDevice = (CDvmLogicDevice *)pDvmDataset->GetParent();
	CDvmDataset *pDataset = (CDvmDataset *)pLDevice->FindByID(strDatasetID);
	*ppDsRet = pDataset;

	if (pDataset != NULL)
	{
		*ppDataRet = (CDvmData*)pDataset->FindByID(strID);
	}
	else
	{
		*ppDataRet = NULL;
	}

	return (*ppDataRet !=NULL);
}

CString stt_iec_rcd_get_ch_value_string(CDvmValue *pCh, BOOL bWithUnit,const CString &strUnit)
{
	CString strText;
	CString strMag = pCh->GetAttrByID_MmsAttr(_T("$mag"));
	CString strAng = pCh->GetAttrByID_MmsAttr(_T("$ang"));

	if (bWithUnit)
	{
		strText =  strMag + strUnit + _T("  ") +  strAng + _T("°");
	}
	else
	{
		strText =  strMag + _T("  ") +  strAng;
	}

	return strText;
}


CString stt_iec_rcd_get_ch_value_string(CDvmValue *pCh, BOOL bWithUnit, double &dMag, double &dAng,const CString &strUnit,long nPrecision)
{
	CString strText;
	CString strMag = pCh->GetAttrByID_MmsAttr(_T("$mag"));
	CString strAng = pCh->GetAttrByID_MmsAttr(_T("$ang"));

	if (nPrecision > 0)
	{
		double dValue = CString_To_double(strMag);
		strMag = stt_iec_rcd_get_double_string(dValue,nPrecision);
	}

	dMag = CString_To_double(strMag);
	dAng = CString_To_double(strAng);

	if (strMag == _T("nan"))//当前获取的幅值或相位值非法时,将其浮点值设置为0,防止矢量图显示异常
	{
		dMag = 0;
		strMag = _T("--");
	}

	if (strAng == _T("nan"))
	{
		dAng = 0;
		strAng = _T("--");
	}

	if (bWithUnit)
	{
		strText =  strMag + strUnit + _T("  ") +  strAng + _T("°");
	}
	else
	{
		strText =  strMag + _T("  ") +  strAng;
	}

	return strText;
}

CString stt_iec_rcd_get_double_string(double dValue,long nPrecision)
{
	CString strDoubleString;

	switch (nPrecision)
	{
	case 1:
		strDoubleString.Format(_T("%.01lf"),dValue);
		break;
	case 2:
		strDoubleString.Format(_T("%.02lf"),dValue);
		break;
	case 3:
		strDoubleString.Format(_T("%.03lf"),dValue);
		break;
	case 4:
		strDoubleString.Format(_T("%.04lf"),dValue);
		break;
	case 5:
		strDoubleString.Format(_T("%.05lf"),dValue);
		break;
	case 6:
		strDoubleString.Format(_T("%.06lf"),dValue);
		break;
	case 7:
		strDoubleString.Format(_T("%.07lf"),dValue);
		break;
	case 8:
		strDoubleString.Format(_T("%.08lf"),dValue);
		break;
	default:
		strDoubleString.Format(_T("%lf"),dValue);
		break;
	}

	return strDoubleString;
}

