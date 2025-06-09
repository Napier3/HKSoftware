#include "SttMacroParaEditViewHtml.h"
#include "../../Module/SttTestResourceMngr/TestResource/SttTestResource_6U6I.h"
#include "../../Module/SttTestResourceMngr/TestResource/SttTestResource_4U3I.h"
#include "../../Module/UI/Interface/SttMacroParaEditViewMngr.h"
#include "../SttTestCntrFrameBase.h"
#include "../../SttCmd/SttTestCmd.h"
#include "../../SttTestCtrl/SttTestAppBase.h"
#include "../../../../Module/OSInterface/QT/XMessageBox.h"

#include"../../Module/XLangResource_Native.h"

QSttMacroParaEditViewHtml::QSttMacroParaEditViewHtml(QWidget* parent)
: QSttWebViewBase(parent)
{
	QWidget *pWidget = this;
	m_pMacroParaEditWnd = pWidget;
	m_pRetParasRef = NULL;
	m_pHtmlSttTestResource = NULL;

	m_pHtmlSttTestResource = g_theTestCntrFrame->GetSttTestResource();
//	CreateTestResource();
	g_theTestCntrFrame->InitTestResource();
	m_nSysConfig_Mode = STT_HTML_SYSCONFIG_MODE_UPDATE;
	m_bHasClicked_OkCancel = false;
}

QSttMacroParaEditViewHtml::~QSttMacroParaEditViewHtml()
{
	QWebHistory *pHis = history();
	pHis->clear();
	QWebSettings::clearMemoryCaches();

// 	if (m_pHtmlSttTestResource != NULL)
// 	{
// 		delete m_pHtmlSttTestResource;
// 		m_pHtmlSttTestResource = NULL;
// 	}

//	CLogPrint::LogString(XLOGLEVEL_TRACE, "QSttMacroParaEditViewHtml::~QSttMacroParaEditViewHtml()");
	//stop();
	//close();
	//deleteLater();
}

CSttTestResourceBase* QSttMacroParaEditViewHtml::CreateTestResource()
{
// 	if (g_pTheSttTestApp->m_pTestMacroUI == NULL)
// 	{
// 		g_theTestCntrFrame->m_pSttTestResource = new CSttTestResource_4U3I();
// 		m_pHtmlSttTestResource = g_theTestCntrFrame->m_pSttTestResource;
// 		return g_theTestCntrFrame->m_pSttTestResource;
// 	}
// 
// 	if (g_pTheSttTestApp->m_pTestMacroUI->m_strHdRsFile == STT_TEST_RESOURCE_FILENAME_6U6I)
// 	{
// 		g_theTestCntrFrame->m_pSttTestResource = new CSttTestResource_6U6I();
// 	}
// 	else if (g_pTheSttTestApp->m_pTestMacroUI->m_strHdRsFile == STT_TEST_RESOURCE_FILENAME_4U3I)
// 	{
// 		g_theTestCntrFrame->m_pSttTestResource = new CSttTestResource_4U3I();
// 	}
// 	else
// 	{
// 		g_theTestCntrFrame->m_pSttTestResource = new CSttTestResource_4U3I();
// 	}
	
//	m_pHtmlSttTestResource = g_theTestCntrFrame->m_pSttTestResource;
	return g_theTestCntrFrame->GetSttTestResource();
}

bool g_bIsEmptyHtmlFile = false;

#include "../../SttTestCtrl/SttTestAppBase.h"
void QSttMacroParaEditViewHtml::OnHtmlLoadFinish(bool b)
{
//	CLogPrint::LogString(XLOGLEVEL_TRACE, "SttMacroParaEditViewHtml::OnHtmlLoadFinish");

	if (g_bIsEmptyHtmlFile)
	{
		g_bIsEmptyHtmlFile = false;
		return;
	}
	CDataGroup oSysParas;
	long nUseKeyBoard = 0;
	oSysParas.AddNewData(STT_SYSCONFIG_DATA_ID_USE_KEYBOARD,nUseKeyBoard);
	SysConfig(&oSysParas);

	if (m_strHtmlFile == STT_MACROPARA_HTML_NAME_SYSCONFIG)
	{
		CDataGroup oSetSysParas;
		CSttDataGroupSerializeRegister oRegister(&oSetSysParas);
		stt_xml_serialize(&g_oSystemParas, &oRegister);
		SetSysConfig(&oSetSysParas, &g_oSttTestResourceMngr.m_oChMaps);

		//2024-6- 27 wuxinyi 开启系统参数时不接受实时数据
		g_theTestCntrFrame->m_bUpdateHardCfgFromRealTime = false;

	}
	else if (m_strHtmlFile == STT_MACROPARA_HTML_NAME_POWERGEAR)
	{
		CDataGroup oPowerGear;
		CSttDataGroupSerializeRegister oRegister(&oPowerGear);
		stt_xml_serialize_ModulesGearSwitch(&g_oSystemParas.m_oGearSetCurModules, &oRegister);
		SetPowerGear(&oPowerGear);

		g_theTestCntrFrame->m_bUpdateOutputPowerFromRealTime = false;

	}
	else if (m_strHtmlFile == STT_MACROPARA_HTML_NAME_VERSIONINFOR)
	{
		CDataGroup oDeviceInfors;
		g_oSttTestResourceMngr.m_oCurrDevice.GetDeviceVersioninfors(oDeviceInfors);
		CDataGroup *pDeviceAttrs = (CDataGroup*)oDeviceInfors.FindByID(STT_CMD_PARA_DeviceAttrs);

		if (pDeviceAttrs != NULL)
		{
			CString strExeDateTime;
			strExeDateTime += __DATE__;
			strExeDateTime += " ";
			strExeDateTime += __TIME__;
			CDvmData *pExeVertionData = pDeviceAttrs->AddNewData("ExeVertionDate",strExeDateTime);
			pExeVertionData->m_strName = /*"TestCtrlCntrLinux生成日期"*/g_sLangTxt_State_TBuildDate;
		}

		SetVersionInfor(&oDeviceInfors);
	}
	else if (m_strHtmlFile == STT_MACROPARA_HTML_NAME_DEVCOMM)
	{
		CDvmLogicDevice oLDevice;
		CString strLDevicePath = _P_GetConfigPath();
		strLDevicePath += _T("DeviceComm.xml");

		if (!IsFileExist(strLDevicePath))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("调试使用的配置文件(%s)不存在.")*/g_sLangTxt_Gradient_TheUsedfordebuggingNOexist.GetString(),strLDevicePath.GetString());
			return;
		}

		oLDevice.OpenXmlFile(strLDevicePath,CDataMngrXmlRWKeys::g_pXmlKeys);
		SetDevComm(&oLDevice);
	}
	else
	{
		SetDatas(&g_pTheSttTestApp->m_pTestCtrlCntr->m_oTestMacroUI_Paras);
	}
}

//////////////////////////////////////////////////////////////////////////
void QSttMacroParaEditViewHtml::Debug()
{
	slot_Debug();
}

void QSttMacroParaEditViewHtml::SysConfig(CDataGroup *pSysConfig)
{
	slot_SysConfig(pSysConfig);
}

void QSttMacroParaEditViewHtml::SysConfig(CDvmDataset *pSysConfig)
{
}

void QSttMacroParaEditViewHtml::SysConfig(const CString &strSysConfig )
{
}

void QSttMacroParaEditViewHtml::SetDatas(CDvmDataset *pDataset)
{
	
}

void QSttMacroParaEditViewHtml::SetDatas(CDataGroup *pParas)
{
	slot_SetDatas(pParas);
}

void QSttMacroParaEditViewHtml::SetDatas(const CString &strDataset)
{
}

void QSttMacroParaEditViewHtml::GetDatas(CDvmDataset *pParas)
{
}

void QSttMacroParaEditViewHtml::GetDatas(CDataGroup *pParas)
{
	m_pRetParasRef = pParas;
	slot_GetDatas(pParas);
}

void QSttMacroParaEditViewHtml::GetDatas(CString& strParas)
{
}

void QSttMacroParaEditViewHtml::SetSysConfig(CDataGroup *pSysParas,CSttChMaps *pChMaps)
{
	char *pszSysParas = NULL,*pszChMaps = NULL;
	CDvmData *pDvmData = (CDvmData*)pSysParas->FindByID("StabTime");

	if (pDvmData != NULL)//zhouhj防抖时间界面显示单位ms,实际传参为s,网页端不好处理,在此处处理
	{
		double dStabTime = CString_To_double(pDvmData->m_strValue);
		long nStabTime = dStabTime*1000;
		pDvmData->m_strValue.Format(_T("%ld"),nStabTime);
	}

	pSysParas->AddNewData(_T("SupportAnalogOutput"),g_oLocalSysPara.m_nSupportAnalogOutput);
	pSysParas->AddNewData(_T("SupportDigitalOutput"),g_oLocalSysPara.m_nSupportDigitalOutput);
	pSysParas->AddNewData(_T("SupportWeakOutput"),g_oLocalSysPara.m_nSupportWeakOutput);
	

	CExBaseObject *pPeripheralObj = pSysParas->FindByID("Peripheral");//20220625 zhouhj 网页部分暂时不支持Group嵌套,将Group中内容提取到根节点下

	if ((pPeripheralObj != NULL)&&(pPeripheralObj->GetClassID() == DTMCLASSID_CDATAGROUP))
	{
		CDataGroup *pPeripheralGroup = (CDataGroup*)pPeripheralObj;
		pSysParas->Append(pPeripheralGroup);
		pPeripheralGroup->RemoveAll();
		pSysParas->Delete(pPeripheralObj);
	}

//	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value();  zhouhj 20220312 name属性在网页中需要用到
	pSysParas->GetXml_ASCII(CDataMngrXmlRWKeys::g_pXmlKeys, &pszSysParas, 0, _JSON_TYPE_);
//	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value();

	if (pszSysParas == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, "QSttMacroParaEditViewHtml::SetSysConfig pSysParas->GetXml error");
		return;
	}

	pChMaps->GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszChMaps, 0, _JSON_TYPE_);

	if (pszChMaps == NULL)
	{
		delete pszSysParas;
		CLogPrint::LogString(XLOGLEVEL_ERROR, "QSttMacroParaEditViewHtml::SetSysConfig pChMaps->GetXml error");
		return;
	}

	emit msg_SetSysConfig(QVariant(pszSysParas),QVariant(pszChMaps));
	delete pszSysParas;
	delete pszChMaps;
}

void QSttMacroParaEditViewHtml::SetChMaps(CDataGroup *pSysParas,CSttChMaps *pChMaps)
{
	char *pszSysParas = NULL,*pszChMaps = NULL;
	pSysParas->GetXml_ASCII(CDataMngrXmlRWKeys::g_pXmlKeys, &pszSysParas, 0, _JSON_TYPE_);

	if (pszSysParas == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, "QSttMacroParaEditViewHtml::SetChMaps pSysParas->GetXml error");
		return;
	}

	pChMaps->GetXml_ASCII(CSttCmdDefineXmlRWKeys::g_pXmlKeys, &pszChMaps, 0, _JSON_TYPE_);

	if (pszChMaps == NULL)
	{
		delete pszSysParas;
		CLogPrint::LogString(XLOGLEVEL_ERROR, "QSttMacroParaEditViewHtml::SetChMaps pChMaps->GetXml error");
		return;
	}

	emit msg_SetChMaps(QVariant(pszSysParas),QVariant(pszChMaps));
	delete pszSysParas;
	delete pszChMaps;
}

void QSttMacroParaEditViewHtml::SetPowerGear(CDataGroup *pSysParas)
{
	char *pszSysParas = NULL;
	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value(NULL, 0x1FFFF);
	pSysParas->GetXml_ASCII(CDataMngrXmlRWKeys::g_pXmlKeys, &pszSysParas, 0, _JSON_TYPE_);
	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value(NULL, 0x1FFFF);

	if (pszSysParas == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, "QSttMacroParaEditViewHtml::SetPowerGear pSysParas->GetXml error");
		return;
	}

	emit msg_SetPowerGear(QVariant(pszSysParas));
	delete pszSysParas;
}

void QSttMacroParaEditViewHtml::SetVersionInfor(CDataGroup *pDeviceModel)
{
	char *pszDeviceModel = NULL;

	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value(NULL, 0x1FFFF);
	pDeviceModel->GetXml_ASCII(CDataMngrXmlRWKeys::g_pXmlKeys, &pszDeviceModel, 0, _JSON_TYPE_);
	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value(NULL, 0x1FFFF);

	if (pszDeviceModel == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, "QSttMacroParaEditViewHtml::SetVersionInfor pDeviceModel->GetXml error");
		return;
	}

	emit msg_SetVersionInfor(QVariant(pszDeviceModel));
	delete pszDeviceModel;
}

void QSttMacroParaEditViewHtml::SetDevComm(CDvmLogicDevice *pLdevice)
{
	char *pszLdevice = NULL;
	pLdevice->GetXml_ASCII(CDataMngrXmlRWKeys::g_pXmlKeys, &pszLdevice, 0, _JSON_TYPE_);

	if (pszLdevice == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, "QSttMacroParaEditViewHtml::SetDevComm error");
		return;
	}

	emit msg_SetDevComm(QVariant(pszLdevice));
	delete pszLdevice;
}

void QSttMacroParaEditViewHtml::OnViewTestLink(BOOL b)
{

}

void QSttMacroParaEditViewHtml::OnViewTestStart()
{
	g_oSttTestResourceMngr.m_oRtDataMngr.m_pMacroChannels->ClearHisDatas();
	g_theTestCntrFrame->ClearInfoWidget();
	g_theTestCntrFrame->StartStateMonitor();
	g_theTestCntrFrame->StartVectorWidget();
	g_theTestCntrFrame->StartPowerWidget();
	g_theTestCntrFrame->slot_UpdateHtmlManuTrigerBtn_Testing();

// 	if (g_theTestCntrFrame->HasManuTrigerBtn())
// 	{
// 
// 		if (g_theTestCntrFrame->IsManuTriger_FaultTrigMode())
// 		{
// 			g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,true,true);
// 		} 
// 		else
// 		{
// 			g_theTestCntrFrame->UpdateButtonStateByID(STT_CNTR_CMD_ManuTriger,false,true);
// 		}
// 	}
}

void QSttMacroParaEditViewHtml::OnViewTestStop()
{
	g_theTestCntrFrame->OnViewTestStop_Common();
}


//APP ==>> HTML
void QSttMacroParaEditViewHtml::slot_SysConfig(CDataGroup *pSysConfig)
{
	char *pszDataset = NULL;
	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value();
	pSysConfig->GetXml_ASCII(CDataMngrXmlRWKeys::g_pXmlKeys, &pszDataset, 0, _JSON_TYPE_);
	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value();

	if (pszDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, "QSttMacroParaEditViewHtml::SysConfig error");
		return;
	}

	emit msg_SysConfig(QVariant(pszDataset));
	delete pszDataset;
}

void QSttMacroParaEditViewHtml::slot_SetDatas(CDvmDataset *pDataset)
{
	char *pszDataset = NULL;
	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value();
	pDataset->GetXml_ASCII(CDataMngrXmlRWKeys::g_pXmlKeys, &pszDataset, 0, _JSON_TYPE_);
	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value();

	if (pszDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, "QSttMacroParaEditViewHtml::SetDatas error");
		return;
	}

//	pszDataset[0] = '<';//zhouhj 20220313 已不需要加此处理
	emit msg_SetDatas(QVariant(pszDataset));
	delete pszDataset;
}

void QSttMacroParaEditViewHtml::slot_SetDatas(CDataGroup *pParas)
{
	char *pszDataset = NULL;
	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value();
	pParas->GetXml_ASCII(CDataMngrXmlRWKeys::g_pXmlKeys, &pszDataset, 0, _JSON_TYPE_);
	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value();

	if (pszDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, "QSttMacroParaEditViewHtml::SetDatas error");
		return;
	}

	//pszDataset[0] = ' ';
	emit msg_SetDatas(QVariant(pszDataset));
	delete pszDataset;
}

void QSttMacroParaEditViewHtml::slot_Debug()
{
	emit msg_Debug();
}

void QSttMacroParaEditViewHtml::slot_SysConfig(const CString &strSysConfig)
{
	emit msg_SysConfig(QVariant(strSysConfig.GetString()));
}

void QSttMacroParaEditViewHtml::slot_SetDatas(const CString &strDataset)
{
	emit msg_SetDatas(QVariant(strDataset));
}

void QSttMacroParaEditViewHtml::slot_GetDatas(CDvmDataset *pDataset)
{
	char *pszDataset = NULL;
	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value();
	pDataset->GetXml_ASCII(CDataMngrXmlRWKeys::g_pXmlKeys, &pszDataset, 0, _JSON_TYPE_);
	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value();

	if (pszDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, "QSttMacroParaEditViewHtml::GetDatas error");
		return;
	}

	emit msg_GetDatas(QVariant(pszDataset));
	delete pszDataset;
}

void QSttMacroParaEditViewHtml::slot_GetDatas(CDataGroup *pDatas)
{
	char *pszDataset = NULL;
	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value();
	pDatas->GetXml_ASCII(CDataMngrXmlRWKeys::g_pXmlKeys, &pszDataset, 0, _JSON_TYPE_);
	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value();

	if (pszDataset == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, "QSttMacroParaEditViewHtml::GetDatas error");
		return;
	}

	emit msg_GetDatas(QVariant(pszDataset));
	delete pszDataset;
}

void QSttMacroParaEditViewHtml::slot_SetHtml(const CString &strFile)
{
	char *pszHtml = stt_ui_OpenHtmlFile_GetChar(strFile);

	emit msg_SetHtml(QVariant(pszHtml));

	delete pszHtml;
}

//HTML ==>> APP
void QSttMacroParaEditViewHtml::UpdateDatas(QVariant strParas)
{
	//m_pRetParasRef->DeleteAll();  //2022-3-16  lijunqing 不删除，只进行赋值
	ToDataGroup(strParas,*m_pRetParasRef);

/*
	if (m_pRetParasRef != NULL)//zhouhj 20220126 增加用于打印显示当前获取的结果数据,比对各测试模块传参是否正确
	{
		CString strXmlParasString;
		m_pRetParasRef->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strXmlParasString, _PUGI_XML_TYPE_);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strXmlParasString);
	}
*/
}

void QSttMacroParaEditViewHtml::OnItemsChanged(QVariant strParas)
{
	CDvmDataset oDvmDataset;
	ToDvmDataset(strParas, oDvmDataset);
}

void QSttMacroParaEditViewHtml::UI_ExecCmd(QVariant strCmd, QVariant strParas)
{

}

void QSttMacroParaEditViewHtml::UI_OK_Click(QVariant strHtmlFileName,  QVariant strParas1, QVariant strParas2)
{
	if (m_bHasClicked_OkCancel)
	{
		return;
	}

	m_bHasClicked_OkCancel = true;

	if (g_nLogDebugInfor)
	{
		CLogPrint::LogString(XLOGLEVEL_RESULT, _T(">> begin UI_OK_Click >>"));
	}

	CString strHtmlFile = strHtmlFileName.toString();
	QByteArray oByteArray1 = strParas1.toByteArray();
	char *pszParas1 = oByteArray1.data();
	long nLen1 = oByteArray1.size();
	QByteArray oByteArray2 = strParas2.toByteArray();
	char *pszParas2 = oByteArray2.data();
	long nLen2= oByteArray2.size();

	if (strHtmlFile == STT_MACROPARA_HTML_NAME_SYSCONFIG)
	{
		//2022-9-19  lijunqing  同样的代码，出现了好几个地方
/*		CDataGroup oSysParas;
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
		oSysParas.SetXml_ASCII(pszParas1, nLen1, CDataMngrXmlRWKeys::g_pXmlKeys, _JSON_TYPE_);
		CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

		CDvmData *pDvmData = (CDvmData*)oSysParas.FindByID("StabTime");

		if (pDvmData != NULL)//zhouhj防抖时间界面显示单位ms,实际传参为s,网页端不好处理,在此处处理
		{
			double dStabTimeMs = CString_To_double(pDvmData->m_strValue);
			double dStabTimeS = dStabTimeMs/1000;
			pDvmData->m_strValue.Format(_T("%lf"),dStabTimeS);
		}

		CSttDataGroupSerializeRead oRead(&oSysParas);
		stt_xml_serialize(&g_oSystemParas, &oRead);
		stt_xml_serialize_Peripheral(&g_oSystemParas.m_oPeripheral,&oRead,FALSE);
*/
// 		CXMessageBox::information(NULL,/* tr("提示")*/g_sLangTxt_Message,QString("%1").arg(nLen1));
// 		CXMessageBox::information(NULL,/* tr("提示")*/g_sLangTxt_Message,pszParas1);
//		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,("UI_OK_Click pszParas1=%s"),pszParas1);
		stt_SystemParas_SetString(pszParas1, nLen1);  

		g_oSttTestResourceMngr.SaveSystemParasFile();

		if (nLen2>0)//zhouhj 如果当前传入的通道映射内容不为空,则更新通道映射
		{
			g_oSttTestResourceMngr.m_oChMaps.DeleteAll();
			g_oSttTestResourceMngr.m_oChMaps.SetXml_ASCII(pszParas2, nLen2, CSttCmdDefineXmlRWKeys::g_pXmlKeys, _JSON_TYPE_);
			g_oSttTestResourceMngr.m_oChMaps.UpdateWeekRateValue();
		}

		if (!g_oSystemParas.m_nHasWeek)//zhouhj 20220406 如果当前没有弱信号输出,在修改了系统参数后,统一对其进行缺省参数映射,防止数字、模拟切换后,当前映射的软件资源为空
		{
			if(m_pHtmlSttTestResource != NULL)//20231213 suyang 如果当前软件资源为空,则不设置当前通道映射
			{
				g_oSttTestResourceMngr.CreateDefaultChMapsByDevice(&g_oSttTestResourceMngr.m_oChMaps,g_oSystemParas.m_nIecFormat ,g_oSystemParas.m_nHasDigital);

			}
			g_oSttTestResourceMngr.SaveCurChMapsFile();
		}

		g_oSttTestResourceMngr.SaveCurChMapsFile();

		if (m_nSysConfig_Mode == STT_HTML_SYSCONFIG_MODE_UPDATE)
		{
			g_theTestCntrFrame->UpdateSysConfig();
		}
		else
		{
			g_theTestCntrFrame->New_SysConfig();
		}

#ifdef _USE_SoftKeyBoard_//zhouhj 2023.8.28 系统参数修改后,更新键盘
		g_oSttTestResourceMngr.UpdateSoftKeyboardType();
#endif
		
	}
	else if (m_strHtmlFile == STT_MACROPARA_HTML_NAME_POWERGEAR)
	{
		CDataGroup oPowerGear;
		oPowerGear.SetXml_ASCII(pszParas1, nLen1, CDataMngrXmlRWKeys::g_pXmlKeys, _JSON_TYPE_);
		CSttDataGroupSerializeRead oRead(&oPowerGear);
		stt_xml_serialize_ModulesGearSwitch(&g_oSystemParas.m_oGearSetCurModules, &oRead);
		g_oSttTestResourceMngr.SaveSystemParasFile();

		g_theTestCntrFrame->UpdatePowerGear();
	}
	else if (m_strHtmlFile == STT_MACROPARA_HTML_NAME_VERSIONINFOR)
	{
		
	}
	else if (m_strHtmlFile == STT_MACROPARA_HTML_NAME_DEVCOMM)
	{

	}

	g_theTestCntrFrame->ReturnPrevActiveWidget();

	if (g_nLogDebugInfor)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T(">> end UI_OK_Click >>"));
	}
}

void QSttMacroParaEditViewHtml::UI_Cancel_Click(QVariant strHtmlFileName)
{
	if (m_bHasClicked_OkCancel)
	{
		return;
	}

	m_bHasClicked_OkCancel = true;
	g_theTestCntrFrame->ReturnPrevActiveWidget();
}

