#include "StdAfx.h"
#include "SttTestResourceMngr.h"
#include "../Engine/SttPowerTestEngineBase.h"
#include "../SttSystemConfig/SttSystemConfig.h"
#include "../AdjustTool/SttAdjModule.h"
#include "../SttTest/Common/tmt_adjust_sys_parameter.h"
#include "../SttTest/Common/tmt_test_paras_head.h"
#include "../SttTestSysGlobalPara.h"
#include <algorithm>
#include"../../../Module/Record/RecordGlobalDefine.h"

//2023/8/4 wjs修改键盘呢Func区域
#ifdef _USE_SoftKeyBoard_	
#include "../UI/SoftKeyboard/SoftKeyBoard.h"
#endif

//extern double g_dFixFreqCalValue;


#ifdef NOT_USE_XLANGUAGE
#else
#include "../XLangResource_Native.h"                              

#endif

#include "TestResource/SttTestResource_Async.h"
#include "TestResource/SttTestResource_Sync.h"
#include "TestResource/SttTestResource_6U6I.h"
#include "TestResource/SttTestResource_4U3I.h"

 CSttTestResourceMngr g_oSttTestResourceMngr;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttModuleTag::CSttModuleTag(void)
{
	m_nModulePos = 0;
	m_nChCountU = 0;
	m_nChCountI = 0;
	m_nChCountU_Week = 0;
	m_nChCountI_Week = 0;
	m_nModuleType=-1;
	m_nModuleIndex = 0;
}

long CSttModuleTag::GetTotalChCount()
{
	long nTotalNum = (m_nChCountU + m_nChCountI);

	if (nTotalNum <= 0)
	{
		nTotalNum = m_nChCountU_Week + m_nChCountI_Week;
	}

	return nTotalNum;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 CSttModuleTag* CSttModuleTags::AddModuleTag(long nModulePos,long nModuleType,long nChCount)
{
	 CSttModuleTag* pChild = new CSttModuleTag;
	 pChild->m_nModulePos = nModulePos;
	 pChild->m_nModuleType = nModuleType;
	 pChild->m_nChCountU = 0;
	 pChild->m_nChCountI = 0;
	 pChild->m_nChCountU_Week = 0;
	 pChild->m_nChCountI_Week = 0;

	 if (nModuleType == STT_MODULE_TYPE_VOLT)
	 {
		 pChild->m_nChCountU = nChCount;
	 }
	 else if (nModuleType == STT_MODULE_TYPE_CURRENT)
	 {
		 pChild->m_nChCountI = nChCount;
	 }
	 else if (nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
	 {
		 pChild->m_nChCountI = nChCount/2;
		 pChild->m_nChCountU = nChCount -  pChild->m_nChCountI;
	 }
	 else if ((nModuleType == STT_MODULE_TYPE_DIGITAL_0G8M)||(nModuleType == STT_MODULE_TYPE_DIGITAL_2G6M)||(nModuleType == STT_MODULE_TYPE_DIGITAL_4G4M))
	 {
		 pChild->m_nChCountI = 18;
		 pChild->m_nChCountU = 18;
	 }
	 else if ((nModuleType == STT_MODULE_TYPE_FT3)||(nModuleType == STT_MODULE_TYPE_Stable2M))
	 {
		 pChild->m_nChCountI = 18;
		 pChild->m_nChCountU = 12;
	 }
	 else if ((nModuleType == STT_MODULE_TYPE_ADMU))//zhouhj 2024.2.4
	 {
		 pChild->m_nChCountI = 18;
		 pChild->m_nChCountU = 12;
		 pChild->m_nChCountI_Week = nChCount/2;
		 pChild->m_nChCountU_Week = nChCount - pChild->m_nChCountI_Week;
	 }
	 else if ((nModuleType == STT_MODULE_TYPE_WEEK_EX)/*||(nModuleType == STT_MODULE_TYPE_WEEK_MAIN)*/)
	 {
		 pChild->m_nChCountI_Week = nChCount/2;
		 pChild->m_nChCountU_Week = nChCount - pChild->m_nChCountI_Week;
	 }

	 AddTail(pChild);
	 pChild->m_nModuleIndex = GetCount();
	 return pChild;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CSttTestResourceMngr::CSttTestResourceMngr(void)
{
	m_pTestResouce = NULL;
	m_strIecConfigFileName = IECCONFIG_FILE_NAME_TESTWIN;

	//2023/8/23 wjs 给键盘中的额定电压/电流赋初值
#ifdef _USE_SoftKeyBoard_
	g_oKeyBoardBtnDescs.m_pfVNom = &(g_oSystemParas.m_fVNom);
	g_oKeyBoardBtnDescs.m_pfINom = &(g_oSystemParas.m_fINom);
#endif
}

CSttTestResourceMngr::~CSttTestResourceMngr(void)
{
//    m_oIecDatasMngr.RemoveAll();
}

BOOL CSttTestResourceMngr::SelectDeviceFromLocalDB()
{
	CString strLocalDevicePath;
	strLocalDevicePath = GetCurSelRsDeviceFilePath();

	if (strLocalDevicePath.IsEmpty())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前设备编号为空."));
		return FALSE;
	}

	OpenSystemParasFile();

	if (!IsFileExist(strLocalDevicePath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前设备文件(%s)不存在."),strLocalDevicePath.GetString());
		return FALSE;
	}

//	stt_open_adjust_file_path(strLocalDevicePath.GetString());

	if (!m_oCurrDevice.OpenSttAdjFile(strLocalDevicePath))
	{
		return FALSE;
	}

	m_oCurrDevice.GetAttrs();
	CString strModel;
	strModel = g_oSttSystemConfig.GetDevModel();

	if (!m_oCurrDevice.m_strModel.IsEmpty())
	{
		strModel = m_oCurrDevice.m_strModel;
	}

//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("[问题查找](%s)."),strModel.GetString());

	if (strModel.Find(_T("PNS331")) >= 0 || strModel.Find(_T("PDU100")) >= 0 )//zhouhj 2023.8.3 //chenling20240418系统参数弱信号设置各通道的一次值与二次值变比默认值设置为1:1
	{
		g_nSttWeekUseMode = STT_WEEK_USE_MODE_DistriTerm;
	} 
	else
	{
		g_nSttWeekUseMode = STT_WEEK_USE_MODE_NORMAL;
	}

#ifdef _USE_SoftKeyBoard_
	UpdateSoftKeyboardType();
#endif
	m_oCurrDevice.SortModules();
	GetAllModuleTags();
	return TRUE;
}

BOOL CSttTestResourceMngr::OpenChMapsFile(CSttChMaps *pChMaps,CSttTestResourceBase *pTestResouce)
{
	ASSERT(pTestResouce);

	if (pTestResouce == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("OpenChMapsFile: Test Resource is null"));
		return FALSE;
	}

	CString strChMapFilePath;

#ifdef _PSX_QT_LINUX_
	strChMapFilePath = GetRsDirPath_Device();
#else
	strChMapFilePath = GetCurSelDirPath_SN();
#endif

	if (strChMapFilePath.IsEmpty())
	{
		return FALSE;
	}

	strChMapFilePath += pTestResouce->GetChMapFileName();

	if (!IsFileExist(strChMapFilePath))
	{
		return FALSE;
	}

	pChMaps->DeleteAll();
	return pChMaps->OpenChMapsFile(strChMapFilePath);
}

BOOL CSttTestResourceMngr::OpenChMapsFile(const CString &strChMapsFile)
{
	m_oChMaps.DeleteAll();
	return m_oChMaps.OpenChMapsFile(strChMapsFile);
}

BOOL CSttTestResourceMngr::OpenSystemParasFile(const CString &strSysParasPath)
{
	CString strActPath;

	if (strSysParasPath.IsEmpty())
	{
		strActPath = GetCurSelRsDeviceSysParasPath();

		if (strActPath.IsEmpty())
		{
			return FALSE;
		}
	}
	else
		strActPath = strSysParasPath;


	if(!IsFileExist(strActPath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("系统参数文件【%s】不存在."),strActPath.GetString());
		return FALSE;
	}

	CSttTestCmd oSttCmd;
	CSttMacro *pSttMacro = oSttCmd.GetSttMacro(TRUE,TRUE);

	CSttXmlSerializeTool oSttXmlSerializeTool;

	if (oSttXmlSerializeTool.CreateXmlSerializeRead(pSttMacro, strActPath) == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("解析系统参数文件失败【%s】"),strActPath.GetString());
		return FALSE;
	}

	pSttMacro->SetCreateMacroChild(TRUE);
	oSttXmlSerializeTool.SttXmlSerializeRead(pSttMacro);

	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetParas();

	//解析生成结构体
	stt_xml_serialize(&g_oSystemParas, pMacroParas);

	if ((g_dFixFreqCalValue>1.0f) && (g_oSystemParas.m_fFNom>1.0f))
	{
		g_dFixFreqCalValue = g_oSystemParas.m_fFNom;
	}

	return TRUE;
}

BOOL CSttTestResourceMngr::SaveSystemParasFile()
{
	CString strActPath;

	strActPath = GetCurSelRsDeviceSysParasPath();

	if (strActPath.IsEmpty())
	{
		return FALSE;
	}

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
 	pMacro->GetParas();
// 	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(pMacro);
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetParas();
	stt_xml_serialize(&g_oSystemParas, pMacroParas);
//	oSttXmlSerializeTool.Stt_WriteFile(strActPath);
	pMacro->SetCreateMacroChild(true);
	pMacro->DeleteAll();
	oSttXmlSerializeTool.SttXmlSerializeRead(pMacro);
	pMacro->SaveXmlFile(strActPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	return TRUE;
}

BOOL CSttTestResourceMngr::LoadDefaultIec61850Config()
{
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += m_strIecConfigFileName;	

	if (!IsFileExist(strPath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("IEC配置文件(%s)不存在."),strPath.GetString());
		return FALSE;
	}

#ifdef NOT_USE_TEST_RESOURCE_IECFG
	return TRUE;
#else
	if (m_oIecDatasMngr.OpenIecCfgFile(strPath))
	{
//		m_oIecDatasMngr.DelteteContrlBlocks_Unselected();  //zhouhj 20220305 在界面显示和下发数据时,处理只显示或只下发选择的控制块,打开配置文件时,不能直接删除未选的控制块
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
#endif
}

BOOL CSttTestResourceMngr::SaveDefaultIec61850Config(/*const CString &strFileName*/)
{
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += m_strIecConfigFileName;	
#ifdef NOT_USE_TEST_RESOURCE_IECFG
	return TRUE;
#else
	if (m_oIecDatasMngr.SaveAsIecCfgFile(strPath,FALSE))
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}
#endif
}

BOOL CSttTestResourceMngr::IsSyncMode()
{
	return (m_oRtDataMngr.m_nMode == STT_RT_DATA_MODE_SYN);
}

BOOL CSttTestResourceMngr::IsAsyncMode()
{
	return (m_oRtDataMngr.m_nMode == STT_RT_DATA_MODE_ASYN);
}

CString CSttTestResourceMngr::GetRsDirPath_Device()
{
	CString strPath;
	strPath = _P_GetDBPath();
	strPath.AppendFormat(_T("Device/"));
	return strPath;
}

CString CSttTestResourceMngr::GetRsDirPath_Model(CString strModel)
{
	if (strModel.IsEmpty())
	{
		strModel = g_oSttSystemConfig.GetDevModel();
	}

	CString strPath;
	strPath = GetRsDirPath_Device();
	strPath.AppendFormat(_T("%s/"),strModel.GetString());
	return strPath;
}

CString CSttTestResourceMngr::GetDevFilePath_Model(CString strModel)
{
	if (strModel.IsEmpty())
	{
		strModel = g_oSttSystemConfig.GetDevModel();
	}

	CString strPath;
	strPath = GetRsDirPath_Device();
	strPath += strModel;
	strPath.AppendFormat(_T("/%s.xml"),strModel.GetString());
	return strPath;
}

CString CSttTestResourceMngr::GetCurSelRsDeviceFilePath()
{
	CString strPath;
#ifdef _PSX_QT_LINUX_
    strPath = GetRsDirPath_Device();
#else
	strPath = GetCurSelDirPath_SN();
#endif

	if (strPath.IsEmpty())//如果当前选择的仪器编号为空，则返回路径为空，该文件不存在
	{
		return _T("");
	}

	strPath += _T("DeviceModel.xml");
	return strPath;
}

CString CSttTestResourceMngr::GetCurSelRsDeviceSysParasPath()
{
	CString strPath;

#ifdef _PSX_QT_LINUX_
	strPath = GetRsDirPath_Device();
 #else
 	strPath = GetCurSelDirPath_SN();
 #endif

	if (strPath.IsEmpty())//如果当前选择的仪器编号为空，则返回路径为空，该文件不存在
	{
		return _T("");
	}

	strPath += _T("SystemParas.sysxml");
	return strPath;
}

CString CSttTestResourceMngr::GetCurSelDirPath_SN()
{
	CString strModel;
	strModel = g_oSttSystemConfig.GetDevModel();

	if (m_oDevSN_List.m_strName != strModel)//SN链表的m_strName存储当前打开的型号，如果型号不匹配，需要打开对应型号下的该配置文件
	{
		CString strDevPath;
		strDevPath = GetDevFilePath_Model();

		if (!IsFileExist(strDevPath))//如果记录全部SN的设备文件不存在，则返回空
		{
			return _T("");
		}

		m_oDevSN_List.DeleteAll();
		m_oDevSN_List.OpenXmlFile(strDevPath,CDataMngrXmlRWKeys::g_pXmlKeys);
		m_oDevSN_List.m_strName = strModel;
	}

	if (m_oDevSN_List.m_strID.IsEmpty())//如果当前选择的仪器编号为空，则返回路径为空，该文件不存在
	{
		return _T("");
	}

	CString strCurSelDevSNPath;
	strCurSelDevSNPath = GetRsDirPath_Model();
	strCurSelDevSNPath.AppendFormat(_T("%s/"),m_oDevSN_List.m_strID.GetString());
	return strCurSelDevSNPath;
}

void CSttTestResourceMngr::SetCurSelDevice(const CString &strModel,const CString &strSN,BOOL bSaveCfg)
{
#ifdef _PSX_QT_LINUX_
	return;//在Linux下面固定型号方式,不支持切换
#endif
	BOOL bHasChanged = FALSE;

	if (m_oDevSN_List.m_strName != strModel)//SN链表的m_strName存储当前打开的型号，如果型号不匹配，需要打开对应型号下的该配置文件
	{
		g_oSttSystemConfig.SetCurDevModel(strModel);//修改系统配置中当前型号

		if (bSaveCfg)
		{
			g_oSttSystemConfig.SaveSystemConfig();//保存系统配置
		}

		CString strDevPath;
		strDevPath = GetDevFilePath_Model();
		m_oDevSN_List.DeleteAll();

		if (IsFileExist(strDevPath))//如果记录全部SN的设备文件存在，则打开该文件
		{
			m_oDevSN_List.OpenXmlFile(strDevPath,CDataMngrXmlRWKeys::g_pXmlKeys);
		}

		m_oDevSN_List.m_strName = strModel;
		bHasChanged = TRUE;
	}

	if (bHasChanged||(m_oDevSN_List.m_strID != strSN))//如果当前SN不同，则选择当前SN为此
	{
		bHasChanged = TRUE;
		CDvmData *pDvmData = (CDvmData*)m_oDevSN_List.FindByID(strSN);

		if (pDvmData == NULL)//如果当前SN不存在，则创建该型号对象
		{
			pDvmData= new CDvmData;
			pDvmData->m_strID = strSN;
			m_oDevSN_List.AddNewChild(pDvmData);
		}

		m_oDevSN_List.m_strName = strModel;
		m_oDevSN_List.m_strID = strSN;
		CString strSavePath;
		strSavePath = GetRsDirPath_Model();
		strSavePath.AppendFormat(_T("%s.xml"),strModel.GetString());

		if (bSaveCfg)
		{
		m_oDevSN_List.SaveXmlFile(strSavePath,CDataMngrXmlRWKeys::g_pXmlKeys);//保存型号对象配置文件
	}
	}

	if (bHasChanged)
	{
		m_oChMaps.DeleteAll();
		SelectDeviceFromLocalDB();
	}
}

CString CSttTestResourceMngr::GetRsDeviceFilePath(const CString &strModel,const CString &strSN)
{
	CString strPath;
	strPath = GetRsDirPath_Model(strModel);
	strPath.AppendFormat(_T("%s/DeviceModel.xml"),strSN.GetString());
	return strPath;
}

BOOL CSttTestResourceMngr::IsDeviceInLocalDB(const CString &strModel,const CString &strSN)
{
	CString strPath;
	strPath = GetRsDeviceFilePath(strModel,strSN);
	return IsFileExist(strPath);
}

BOOL CSttTestResourceMngr::HasLoadDevice()
{
	if (m_oCurrDevice.m_pSttAdjRef == NULL)
	{
		return FALSE;
	}

	return (m_oCurrDevice.GetModuleCount()>0);
}

BOOL CSttTestResourceMngr::HasLoadChMaps()
{
	return (m_oChMaps.GetCount()>0);
}

void CSttTestResourceMngr::GetAllModuleTags()
{
	if (m_oCurrDevice.m_pSttAdjRef == NULL)
	{
		return;
	}

	m_oCurrDevice.GetAttrs();

	if (m_oCurrDevice.m_strSN == m_strModuleTagsSN)
	{
		return;
	}

	m_oAnalogI_Tags.DeleteAll();
	m_oAnalogU_Tags.DeleteAll();
	m_oAnalogUI_Tags.DeleteAll();
//	m_oDigital_Tags.DeleteAll();
	m_oWeak_Tags.DeleteAll();
	m_strModuleTagsSN = m_oCurrDevice.m_strSN;

	CDataGroup *pDeviceGroup = m_oCurrDevice.m_pSttAdjRef;
	POS pos = pDeviceGroup->GetHeadPosition();
	CDataGroup *pModule = NULL;
	CSttAdjModule oAdjModule;
	CExBaseObject *p = NULL;
	long nModuleType = 0;
	long nModulePos = 0;
	long nChCount = 0;

	while(pos != NULL)
	{
		p = pDeviceGroup->GetNext(pos);

		if (!m_oCurrDevice.IsSttAdjModuleObj(p))
		{
			continue;
		}

		pModule = (CDataGroup *)p;
		oAdjModule.AttatchAdjRef(pModule);

		if (!oAdjModule.GetModuleType(nModuleType))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取模块类型失败(name=%s;id=%s;)"),pModule->m_strName.GetString(),pModule->m_strID.GetString());
			continue;
		}

		nModulePos = 0;
		nChCount = 0;
		oAdjModule.GetModulePos(nModulePos);
		oAdjModule.GetModuleDefChannelNum(nChCount);

 		if (nModuleType == STT_MODULE_TYPE_VOLT)
 		{
 			m_oAnalogU_Tags.AddModuleTag(nModulePos,nModuleType,nChCount);
 		}
 		else if (nModuleType == STT_MODULE_TYPE_CURRENT)
 		{
			m_oAnalogI_Tags.AddModuleTag(nModulePos,nModuleType,nChCount);
		}
		else if (nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
		{
			CSttModuleTag* pChildModuleTag = m_oAnalogUI_Tags.AddModuleTag(nModulePos,nModuleType,nChCount);
			oAdjModule.GetModuleChannelNum(pChildModuleTag->m_nChCountU,pChildModuleTag->m_nChCountI);
		}
 		else if ((nModuleType == STT_MODULE_TYPE_DIGITAL_0G8M)||(nModuleType == STT_MODULE_TYPE_DIGITAL_2G6M)||(nModuleType == STT_MODULE_TYPE_DIGITAL_4G4M))
 		{//数字量不需要考虑
//			m_oDigital_Tags.AddModuleTag(nModulePos,nModuleType,nChCount);
		}
 		else if ((nModuleType == STT_MODULE_TYPE_FT3))
 		{//数字量不需要考虑
//			m_oDigital_Tags.AddModuleTag(nModulePos,nModuleType,nChCount);
		}
 		else if ((nModuleType == STT_MODULE_TYPE_Stable2M))
 		{//数字量不需要考虑
//			m_oDigital_Tags.AddModuleTag(nModulePos,nModuleType,nChCount);
		} 
		else if ((nModuleType == STT_MODULE_TYPE_ADMU))
		{
			m_oWeak_Tags.AddModuleTag(nModulePos,nModuleType,nChCount);
		}
		else if ((nModuleType == STT_MODULE_TYPE_WEEK_EX)/*||(nModuleType == STT_MODULE_TYPE_WEEK_MAIN)*/)
 		{
			m_oWeak_Tags.AddModuleTag(nModulePos,nModuleType,nChCount);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("模块(name=%s;id=%s;),未映射的模块类型(%ld)."),pModule->m_strName.GetString(),pModule->m_strID.GetString(),nModuleType);
		}
	}
}

CString CSttTestResourceMngr::GetCurrSelSN()
{
#ifdef _PSX_QT_LINUX_
	m_oCurrDevice.GetAttrs();
	return m_oCurrDevice.m_strSN;
#else
	return m_oDevSN_List.m_strID;
#endif
}//获取当前选择型号装置的SN

CString CSttTestResourceMngr::GetCurrModel()
{
#ifdef _PSX_QT_LINUX_
	m_oCurrDevice.GetAttrs();
	return m_oCurrDevice.m_strModel;
#else
	return m_oDevSN_List.m_strName;
#endif
}



/*
第一步：
1）判断m_oCurrDevice对象中链表是否为空，如果为空则根据当前装置型号，读取本地硬件信息;
2）如果当前型号为空，则将当前型号初始化为PN466;
3）根据当前型号去查找“\DB\Device\型号\型号.xml”文件是否存在，如果不存在，则创建缺省4U3I软件资源及通道映射文件；
4）如果上述文件存在，则读取文件信息，找到上次打开的装置编号，根据装置编号，读取对应的Device文件；
5）如果缺省编号为空，或者对应Device文件不存在，则同上，创建缺省4U3I软件资源及通道映射文件；
第二步：（如果当前通道映射文件存在）
1）清空当前映射资源对象；
2）读取本地通道映射文件；
3）验证当前映射文件中所有硬件通道，是否在Device中都能找到，去除无硬件资源的映射关联；
*/
BOOL CSttTestResourceMngr::CreateChMaps()
{
	if (!HasLoadDevice())//如果没有加载通道映射文件,主动加载通道映射文件
	{
		SelectDeviceFromLocalDB();
	}

	if (OpenChMapsFile(&m_oChMaps, m_pTestResouce) && (HasMapHdResource()))//打开通道映射文件
	{
		return TRUE;
	}

	if (!CreateDefaultChMapsByDevice(&m_oChMaps, g_oSystemParas.m_nIecFormat, g_oSystemParas.m_nHasDigital))//如果打开通道映射文件失败,则根据硬件信息创建缺省通道映射文件
	{
		return FALSE;
	}

	SaveCurChMapsFile();
	return TRUE;
}

BOOL CSttTestResourceMngr::HasMapHdResource()
{
	return m_oChMaps.HasMapHdResource(g_oSystemParas.m_nHasAnalog,g_oSystemParas.m_nHasDigital,g_oSystemParas.m_nHasWeek);
}

BOOL CSttTestResourceMngr::ParseHdRsID(const CString &strHdRsID,long &nChType ,long &nModuleType,long &nModuleIndex,long &nChIndex)
{
	if (strHdRsID.Find(_T("U")) == 0)
	{
		nChType = STT_MACRO_CH_TYPE_VOL;
	}
	else
	{
		nChType = STT_MACRO_CH_TYPE_CUR;
	}

	CString strTmp,strTmp2;
	long nIndex = strHdRsID.Find(_T("_"));

	if (nIndex <0)
	{
		return FALSE;
	}

	strTmp = strHdRsID.Mid(nIndex+1);
	nChIndex = CString_To_long(strTmp);
	strTmp = strHdRsID.Left(nIndex);

	if (strTmp.Find(_T("d")) == 1)
	{
		if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8)
		{
			nModuleType = STT_MODULE_TYPE_FT3;
		}
		else if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
		{
			nModuleType = STT_MODULE_TYPE_FT3;
		}
		else 
		{
			nModuleType = STT_MODULE_TYPE_DIGITAL_0G8M;
		}

		strTmp2 = strTmp.Mid(2);
		nModuleIndex = CString_To_long(strTmp2);
	}
	else if (strTmp.Find(_T("w")) == 1)
	{
		nModuleType = STT_MODULE_TYPE_WEEK_EX;
		strTmp2 = strTmp.Mid(2);
		nModuleIndex = CString_To_long(strTmp2);
	}
	else if (strTmp.Find(_T("U")) == 0)
	{
		nModuleType = STT_MODULE_TYPE_VOLT;
		strTmp2 = strTmp.Mid(1);
		nModuleIndex = CString_To_long(strTmp2);
	}
	else if (strTmp.Find(_T("I")) == 0)
	{
		nModuleType = STT_MODULE_TYPE_CURRENT;
		strTmp2 = strTmp.Mid(1);
		nModuleIndex = CString_To_long(strTmp2);
	}
	else
		return FALSE;

	return TRUE;
}

CString CSttTestResourceMngr::GetModuleDefaultName(const CString &strText,long nChIndex)
{
	CString strName;
	long nGroupIndex = (nChIndex-1)/3;
	nGroupIndex++;//组号从1开始

	if (nChIndex%3 == 1)
	{
		strName.Format(_T("%sa%ld"),strText.GetString(),nGroupIndex);
	}
	else if (nChIndex%3 == 2)
	{
		strName.Format(_T("%sb%ld"),strText.GetString(),nGroupIndex);
	}
	else if (nChIndex%3 == 0)
	{
		strName.Format(_T("%sc%ld"),strText.GetString(),nGroupIndex);
	}

	return strName;
}

BOOL CSttTestResourceMngr::CreateDefaultChMapsByDevice(CSttChMaps *pCurChMaps,long nIecFormat,BOOL bHasDigital,BOOL bHasWeek)
{
	if (!HasLoadDevice())
	{
		return FALSE;
	}

	pCurChMaps->DeleteAll();
	pCurChMaps->CreateDefaultBinBoutMaps();		//20241011 huangliang 为开入开出设置默认值

	CreateDefaultChMapsByDevice_Analog(pCurChMaps);

	if (bHasDigital)
	{
		CreateDefaultChMapsByDevice_Digital(pCurChMaps,nIecFormat);
	}

	if (bHasWeek)
	{
		CreateDefaultChMapsByDevice_Weak(pCurChMaps);
	}

	if(m_pTestResouce ==NULL) //add wangtao 20240509 如果程序里不含通道映射，指针为空
	{
		if (pCurChMaps->GetCount() <= 0)//zhouhj 2024.5.22 在通道映射为空时,设置为此
		{
			pCurChMaps->SetChCountU(4);
			pCurChMaps->SetChCountI(3);
		}
	}
	else
	{
	if (m_pTestResouce->GetTestRsType() == STT_TEST_RESOURCE_TYPE_4U3I)
	{
		pCurChMaps->SetChCountU(4);
		pCurChMaps->SetChCountI(3);
	}
	else if (m_pTestResouce->GetTestRsType() == STT_TEST_RESOURCE_TYPE_6U6I)
	{
		pCurChMaps->SetChCountU(6);
		pCurChMaps->SetChCountI(6);
	}
	}

	UpdateChNames_UzIz(pCurChMaps,NULL);
	pCurChMaps->SortByRsIndex();
	return TRUE;
}

void CSttTestResourceMngr::UpdateChNames_UzIz(CExBaseList *pCurChMaps, CSttTestResourceBase *pTestResouce)
{
	if (pCurChMaps == NULL)
	{
		return;
	}
/*设置缺省值时：
	1）如果只有4通道，对应的最后一个通道名称改为U0\I0;
	2）如果不为4通道，对应的第4通道名称，不应该为U0\I0
	*/
	long nVolChNum = /*pCurChMaps->*/Global_GetChNum(pCurChMaps,_T("U"));
	long nCurrChNum = /*pCurChMaps->*/Global_GetChNum(pCurChMaps,_T("I"));
	CSttChMap *pSttChMap = (CSttChMap*)pCurChMaps->FindByID(_T("U4"));

	if (pSttChMap != NULL)
	{
		if (nVolChNum == 4)
		{
			pSttChMap->m_strName = _T("U0");
			pSttChMap->m_strAlias = _T("U0");
		}
		else if (pSttChMap->m_strName == _T("U0"))
		{
			pSttChMap->m_strName = _T("Ua2");
			pSttChMap->m_strAlias = _T("Ua2");
		}
	}

	pSttChMap = (CSttChMap*)pCurChMaps->FindByID(_T("I4"));

	if (pSttChMap != NULL)
	{
		if (nCurrChNum == 4)
		{
			pSttChMap->m_strName = _T("I0");
			pSttChMap->m_strAlias = _T("I0");
		}
		else if (pSttChMap->m_strName == _T("I0"))
		{
			pSttChMap->m_strName = _T("Ia2");
			pSttChMap->m_strAlias = _T("Ia2");
		}
	}

	if (pTestResouce == NULL)
	{
		return;
	}

	if ((nVolChNum == 4))
	{
		CSttChResource *pSttChResource = (CSttChResource*)pTestResouce->FindByID(_T("U4"));

		if (pSttChResource != NULL)
		{
			pSttChResource->m_strName = _T("U0");
		}
	}

	if ((nCurrChNum == 4))
	{
		CSttChResource *pSttChResource = (CSttChResource*)pTestResouce->FindByID(_T("I4"));

		if (pSttChResource != NULL)
		{
			pSttChResource->m_strName = _T("I0");
		}
	}
	
}

void CSttTestResourceMngr::InitLocalSysPara()
{
	if (!HasLoadDevice())
	{
		return;
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_oCurrDevice.GetAttrs();
	g_nStateCount = m_oCurrDevice.m_nStateCount;
	g_nBinCount = m_oCurrDevice.m_nBinCount;
	g_nBoutCount = m_oCurrDevice.m_nBoutCount;

	if (g_nStateCount<=20)
	{
		g_nStateCount = 20;
	}

	if (g_nBinCount< 0)
	{
		g_nBinCount = 0;
	}

	if (g_nBoutCount< 0)
	{
		g_nBoutCount = 0;
	}

	//从资源中取得开入数、开出数
// 	CDataGroup* pBoutGroup = m_oCurrDevice.GetBoutTrunOnValueDef();//zhouhj 20220401 主板开入开出数量及状态数,统一从一个位置获取
// 
// 	if (pBoutGroup)
// 	{
// 		g_oLocalSysPara.m_nCHBinOutNum = pBoutGroup->GetCount();
// 		if (g_oLocalSysPara.m_nCHBinOutNum == 0)
// 		{
// 			g_oLocalSysPara.m_nCHBinOutNum = BINOUT_NUM;	//8个
// 		}
// 	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	g_oLocalSysPara.InitMaxMinVolCurValue();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CExBaseList oCurModuleListRef;
	long nAnalogModuleNum = 0,nDigitalModuleNum = 0,nWeakModuleNum = 0,nExBinBoutModuleNum = 0;
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_VOLT);//获取全部电压模块
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_VOLT_CURRENT);//获取全部电压模块
	nAnalogModuleNum = oCurModuleListRef.GetCount();
	CDataGroup *pModule = NULL;
	CDataGroup *pModuleAttrs = NULL;
	CDvmData *pData = NULL;
	//	long nModulePower = -1;
	double dTmp = 0;
	POS pos = oCurModuleListRef.GetHeadPosition();

	while (pos != NULL)//在该循环中设置电压模块最大值,最小值
	{
		pModule = (CDataGroup *)oCurModuleListRef.GetNext(pos);
		Global_SetModuleMaxMinValue(pModule,&g_oLocalSysPara.m_fAC_VolMax,&g_oLocalSysPara.m_fAC_VolMin,&g_oLocalSysPara.m_fDC_VolMax,&g_oLocalSysPara.m_fDC_VolMin,TRUE);
		Global_GetMaxHarmCount((CDataGroup*)pModule->FindByID(_T("ModuleAttrs")));
	}

	if (g_oLocalSysPara.m_fAC_VolMax <= 0)
	{
		g_oLocalSysPara.m_fAC_VolMax = 130;
	}

	if(g_oLocalSysPara.m_fDC_VolMax <= 0)
	{
		g_oLocalSysPara.m_fDC_VolMax = 100;
	}

	oCurModuleListRef.RemoveAll();
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_CURRENT);
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_VOLT_CURRENT);
	tmt_GearSetCurModules *pGearSetCurModules = &g_oSystemParas.m_oGearSetCurModules;
	pGearSetCurModules->m_nCurModuleNum = oCurModuleListRef.GetCount();//设置电流模块总数量
	nAnalogModuleNum += pGearSetCurModules->m_nCurModuleNum;

	tmt_CurModuleGear *pCurGear = NULL;
	long nCurModuleIndex = -1;
	CString strChMergeMode;
	pos = oCurModuleListRef.GetHeadPosition();

	while (pos != NULL)//在该循环中设置电流模块最大值,最小值,电流模块功率档位等
	{
		pModule = (CDataGroup *)oCurModuleListRef.GetNext(pos);
		pModuleAttrs = (CDataGroup*)pModule->FindByID(_T("ModuleAttrs"));
		nCurModuleIndex++;
		pCurGear = &pGearSetCurModules->m_oCurModuleGear[nCurModuleIndex];

		if (pModuleAttrs == NULL)
		{
			pGearSetCurModules->m_oCurModuleGear[nCurModuleIndex].m_nModulePos = -1;
			pCurGear->m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_NOT_SUPPORT;
			pCurGear->m_nLargeCurOutTerm = STT_LARGE_CUR_OUT_NULL;
			continue;
		}

		Global_GetMaxHarmCount(pModuleAttrs);
		pGearSetCurModules->m_oCurModuleGear[nCurModuleIndex].m_nModulePos = Global_GetModulePos(pModuleAttrs);
		pGearSetCurModules->m_oCurModuleGear[nCurModuleIndex].m_nModuleType = Global_GetModuleType(pModuleAttrs);

//		if (pGearSetCurModules->m_oCurModuleGear[nCurModuleIndex].m_nModuleType != STT_MODULE_TYPE_VOLT_CURRENT)
		{
			Global_SetModuleMaxMinValue(pModule,&g_oLocalSysPara.m_fAC_CurMax,&g_oLocalSysPara.m_fAC_CurMin,&g_oLocalSysPara.m_fDC_CurMax,&g_oLocalSysPara.m_fDC_CurMin,FALSE);
		}

		if (stt_GetDataValueByID(pModuleAttrs,STT_ADJ_ID_ChMergeMode,strChMergeMode))//zhouhj 20211006 如果通道合并模式属性查找成功
		{
			if (strChMergeMode == _T("ChMerge_3Ch"))
			{
				if ((pCurGear->m_nMergeCurTerminal != STT_LARGE_CURRENT_MERGE_THREE_CH))//在大电流输出端子,不为合并为3通道时m固定初始化为不合并
				{
					pCurGear->m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_NOT_MERGE;
				}

				pCurGear->m_nLargeCurOutTerm = STT_LARGE_CUR_OUT_NULL;
				continue;
			}
			else if (strChMergeMode == _T("ChMerge_1Ch"))
			{
				if ((pCurGear->m_nMergeCurTerminal != STT_LARGE_CURRENT_MERGE_NOT_MERGE)&&(pCurGear->m_nMergeCurTerminal != STT_LARGE_CURRENT_MERGE_ONE_CH))
				{
					pCurGear->m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_NOT_MERGE;
				}

				if (pCurGear->m_nLargeCurOutTerm == STT_LARGE_CUR_OUT_NULL)//如果当前选择的为空,则需要对其进行初始化
				{
					pCurGear->m_nLargeCurOutTerm = STT_LARGE_CUR_OUT_TERM_A;
				}

				continue;
			}
		}

		pCurGear->m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_NOT_SUPPORT;//如果合并通道属性查找失败,或者非合并3相或合并单通道,则都默认设置为不支持合并
		pCurGear->m_nLargeCurOutTerm = STT_LARGE_CUR_OUT_NULL;
	}

	oCurModuleListRef.RemoveAll();

	if (g_oLocalSysPara.m_fAC_CurMax <= 0){
		g_oLocalSysPara.m_fAC_CurMax = 20;
	}

//	g_oLocalSysPara.m_fDC_CurMax = 15;

	if(g_oLocalSysPara.m_fDC_CurMax <= 0){
		g_oLocalSysPara.m_fDC_CurMax = 20;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_DIGITAL_0G8M);
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_DIGITAL_2G6M);
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_DIGITAL_4G4M);
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_FT3);
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_Stable2M);
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_ADMU);//zhouhj 2024.2.4
	nDigitalModuleNum = oCurModuleListRef.GetCount();
	oCurModuleListRef.RemoveAll();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_WEEK_EX);
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_ADMU);//zhouhj 2024.2.4
//	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_WEEK_MAIN);
/*	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_WEEK_EX_48);*/
	nWeakModuleNum = oCurModuleListRef.GetCount();
	oCurModuleListRef.RemoveAll();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_SWITCH);
	nExBinBoutModuleNum = oCurModuleListRef.GetCount();

	pos = oCurModuleListRef.GetHeadPosition();
	g_nBinExCount = 0;
	g_nBoutExCount = 0;

	while (pos != NULL)
	{
		pModule = (CDataGroup *)oCurModuleListRef.GetNext(pos);
		pModuleAttrs = (CDataGroup*)pModule->FindByID(_T("ModuleAttrs"));

		if (pModuleAttrs == NULL)
		{
			continue;
		}

		Global_GetBinBoutExNum(pModuleAttrs,g_nBinExCount,g_nBoutExCount);
	}

// 	g_oLocalSysPara.m_nCHBinInExNum = g_nBinExCount;
// 	g_oLocalSysPara.m_nCHBinOutExNum = g_nBoutExCount;
	oCurModuleListRef.RemoveAll();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_ADMU);
	nExBinBoutModuleNum += oCurModuleListRef.GetCount();

	pos = oCurModuleListRef.GetHeadPosition();

	while (pos != NULL)
	{
		pModule = (CDataGroup *)oCurModuleListRef.GetNext(pos);
		g_nBinExCount += 4;
		g_nBoutExCount += 8;
	}

	oCurModuleListRef.RemoveAll();
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	g_oLocalSysPara.m_nCHBinInExNum = g_nBinExCount;
	g_oLocalSysPara.m_nCHBinOutExNum = g_nBoutExCount;
	g_oLocalSysPara.m_nSupportAnalogOutput = 1;
	g_oLocalSysPara.m_nSupportDigitalOutput = 1;
	g_oLocalSysPara.m_nSupportWeakOutput = 1;

	if (nAnalogModuleNum == 0)
	{
		g_oSystemParas.m_nHasAnalog = 0;
		g_oLocalSysPara.m_nSupportAnalogOutput = 0;
	}

	if (nDigitalModuleNum == 0)
	{
		g_oSystemParas.m_nHasDigital = 0;
		g_oLocalSysPara.m_nSupportDigitalOutput = 0;
	}

	if (nWeakModuleNum == 0)
	{
		g_oSystemParas.m_nHasWeek = 0;
		g_oLocalSysPara.m_nSupportWeakOutput = 0;
	}

//	g_oLocalSysPara.m_nSTModeSet = m_oCurrDevice.m_nSTModeSet;

	UpdateParasMaxValuesByWeekRates();
	UpdateLC_ST_FibersNum();//根据硬件信息里标记的光口数量更新IEC配置界面显示的光口数量
	ValidIecParasSetSel();

	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 0)&&(g_oSystemParas.m_nHasWeek == 0))
	{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前输出类型选择为空,请先选择输出类型."));
	}

// 	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("最大交流电压输出值(%fV),最大交流电流输出值(%fA)."),g_oLocalSysPara.m_fAC_VolMax,g_oLocalSysPara.m_fAC_CurMax);
// 	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("最大直流电压输出值(%fV),最大直流电流输出值(%fA)."),g_oLocalSysPara.m_fDC_VolMax,g_oLocalSysPara.m_fDC_CurMax);
}

void CSttTestResourceMngr::UpdateLC_ST_FibersNum()
{
	long nGFiberLC_num = 1;//chenling 2024.5.22 初始化为0
	BOOL bUpdateParas = FALSE;//2024-9-12 wuxinyi 是否有更新光口数量，避免重复打印消息
	CExBaseList oCurModuleListRef;
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_DIGITAL_0G8M);
	long nModuleNum = oCurModuleListRef.GetCount();
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_DIGITAL_2G6M);

	if (oCurModuleListRef.GetCount() != nModuleNum)
	{
		nModuleNum = oCurModuleListRef.GetCount();
		nGFiberLC_num = 2;
	}

	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_DIGITAL_4G4M);

	if (oCurModuleListRef.GetCount() != nModuleNum)
	{
//		nModuleNum = oCurModuleListRef.GetCount();
		nGFiberLC_num = 4;
	}

    //add wangtao 20240509 对于多个插件的数字量测试仪应支持多组，不应按照一个数字插件限制 按照8/16/16一组
	if (oCurModuleListRef.GetCount() != 0)
	{
		g_nIecCfgSmvOut_91_92MaxNum = oCurModuleListRef.GetCount()*IecCfgSmvOut_91_92MaxNum;
		g_nIecCfgGoutMaxNum = oCurModuleListRef.GetCount()*IecCfgGoutData_MaxNum;
		g_nIecCfgGinMaxNum =  oCurModuleListRef.GetCount()*IecCfgGinData_MaxNum;     

		g_nIecCfgSmvOut_60044MaxNum = oCurModuleListRef.GetCount()*IecCfg6044COM_OUT_MaxNum;
		g_nIecCfgSmvIn_60044MaxNum = oCurModuleListRef.GetCount()*IecCfg6044COM_IN_MaxNum;
	}
	//end

	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_FT3);
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_ADMU);

	CDataGroup *pModule = NULL,*pModuleAttrs = NULL;
	POS pos = oCurModuleListRef.GetHeadPosition();
	long/* nTotalFiberNum_LC = 0,*/nCurrFiberNum = 0/*,nTotalFiberNum_STSend = 0,*//*nTotalFiberNum_STRecv = 0*/;
	g_oLocalSysPara.m_nTotalSTRecv_Num = m_oCurrDevice.m_nSTModeSet;

	m_nTotalFiberNum_LC = 0,m_nTotalFiberNum_STSend = 0;
	BOOL bHasFiberNumSTRecv_Paras = FALSE;

	while (pos != NULL)//在该循环中设置电流模块最大值,最小值,电流模块功率档位等
	{
		pModule = (CDataGroup *)oCurModuleListRef.GetNext(pos);
		pModuleAttrs = (CDataGroup*)pModule->FindByID(_T("ModuleAttrs"));

		if (pModuleAttrs->GetDataValue(_T("FiberPortNum_LC"),nCurrFiberNum))
		{
			m_nTotalFiberNum_LC += nCurrFiberNum;
		}

		if (pModuleAttrs->GetDataValue(_T("FiberPortNum_STSend"),nCurrFiberNum))
		{
			m_nTotalFiberNum_STSend += nCurrFiberNum;
		}
		
		if (pModuleAttrs->GetDataValue(_T("FiberPortNum_STRecv"),nCurrFiberNum))
		{
			g_oLocalSysPara.m_nTotalSTRecv_Num/*nTotalFiberNum_STRecv*/ += nCurrFiberNum;
			bHasFiberNumSTRecv_Paras = TRUE;
		}
	}

	if ((m_nTotalFiberNum_LC>1)&&(CCfgDataMngrConstGlobal::GetAppPortFiberNum_LC() != m_nTotalFiberNum_LC))
	{
		CCfgDataMngrConstGlobal::UpdataAppPortDataType_FiberNum(m_nTotalFiberNum_LC);
	}

	if ((m_nTotalFiberNum_LC > 0) && (g_oLocalSysPara.m_nTotalLC_Num != m_nTotalFiberNum_LC))
	{
		bUpdateParas = TRUE;
		g_oLocalSysPara.m_nTotalLC_Num = m_nTotalFiberNum_LC;
	}

	if ((m_nTotalFiberNum_STSend>0)&&(CCfgDataMngrConstGlobal::GetAppPortFT3Num_ST() != m_nTotalFiberNum_STSend))
	{
		CCfgDataMngrConstGlobal::UpdataAppPortDataType_FT3Num(m_nTotalFiberNum_STSend);
	}

	if (m_nTotalFiberNum_STSend>0 && g_oLocalSysPara.m_nTotalSTSend_Num != m_nTotalFiberNum_STSend)
	{
		bUpdateParas = TRUE;
		g_oLocalSysPara.m_nTotalSTSend_Num = m_nTotalFiberNum_STSend; 
	}

	if ((g_oLocalSysPara.m_nTotalSTRecv_Num/*nTotalFiberNum_STRecv*/>0)&&
		(CCfgDataMngrConstGlobal::GetAppPortFT3InNum_ST() != g_oLocalSysPara.m_nTotalSTRecv_Num/*nTotalFiberNum_STRecv*/))
	{
		bUpdateParas = TRUE;
		CCfgDataMngrConstGlobal::UpdataAppPortDataType_FT3InNum(g_oLocalSysPara.m_nTotalSTRecv_Num/*nTotalFiberNum_STRecv*/);
	}


// 	if (bHasFiberNumSTRecv_Paras)
// 	{
// 		g_oLocalSysPara.m_nTotalSTRecv_Num = nTotalFiberNum_STRecv; 
// 	}
	if (g_oLocalSysPara.m_nLC_GFiberNum != nGFiberLC_num)
	{
		bUpdateParas = TRUE;
	g_oLocalSysPara.m_nLC_GFiberNum = nGFiberLC_num;
	}
	
	if (bUpdateParas)
	{
#ifdef NOT_USE_XLANGUAGE
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前设备共包含LC光口%ld个,ST发送口%ld个,ST接收口%ld个,千兆光口%ld个."),m_nTotalFiberNum_LC,m_nTotalFiberNum_STSend,g_oLocalSysPara.m_nTotalSTRecv_Num/*nTotalFiberNum_STRecv*/,nGFiberLC_num);
#else
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("当前设备共包含LC光口%ld个,ST发送口%ld个,ST接收口%ld个,千兆光口%ld个.")*/g_sLangTxt_Native_LCSTSendportSTGigabit.GetString()
		,m_nTotalFiberNum_LC,m_nTotalFiberNum_STSend,g_oLocalSysPara.m_nTotalSTRecv_Num/*nTotalFiberNum_STRecv*/,nGFiberLC_num);                      
#endif
	}

	oCurModuleListRef.RemoveAll();
}

long CSttTestResourceMngr::GetDigitalModuleNum()
{
	CExBaseList oCurModuleListRef;
	m_oCurrDevice.GetAttrs();
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_DIGITAL_0G8M);
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_DIGITAL_2G6M);
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_DIGITAL_4G4M);
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_FT3);
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_ADMU);//zhouhj 2024.2.4
	long nNum = oCurModuleListRef.GetCount();
	oCurModuleListRef.RemoveAll();
	return nNum;
}

long CSttTestResourceMngr::GetUartCount()
{
	m_oCurrDevice.GetAttrs();
	long nUartCount = m_oCurrDevice.m_nUartCount;
	return nUartCount;
}


void CSttTestResourceMngr::UpdateParasMaxValuesByWeekRates()
{
	if (!g_oSystemParas.m_nHasWeek)
	{
		return;
	}

	double dMaxVol = g_oLocalSysPara.m_fAC_VolMax;
	double dMaxCur = g_oLocalSysPara.m_fAC_CurMax;
	//m_oChMaps.GetMaxValue_WeekRates(dMaxVol,dMaxCur);
	CExBaseList *pChMaps = &m_oChMaps;
	Global_GetMaxValue_WeekRates(pChMaps,dMaxVol, dMaxCur);//20240919 huangliang 仅模拟量使用

	if (dMaxVol > g_oLocalSysPara.m_fAC_VolMax)
	{
		g_oLocalSysPara.m_fAC_VolMax = dMaxVol;
	}

	if (dMaxCur > g_oLocalSysPara.m_fAC_CurMax)
	{
		g_oLocalSysPara.m_fAC_CurMax = dMaxCur;
	}

	if (dMaxVol > g_oLocalSysPara.m_fDC_VolMax)
	{
		g_oLocalSysPara.m_fDC_VolMax = dMaxVol;
	}

	if (dMaxCur > g_oLocalSysPara.m_fDC_CurMax)
	{
		g_oLocalSysPara.m_fDC_CurMax = dMaxCur;
	}
}

#ifdef _USE_SoftKeyBoard_
void CSttTestResourceMngr::InitKeyBoardFunc()
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("SoftKeyBoardConfig.xml");
	m_oKeyBoardFuncGroup.DeleteAll();
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	m_oKeyBoardFuncGroup.OpenXmlFile(strFile,CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
//	UpdateSoftKeyboardType();

	//2023/8/23 -wjs 初始化百分比键盘
	CDvmData *pDvmData = NULL;
	//取出NormalVolFunc的值
	pDvmData = (CDvmData*)m_oKeyBoardFuncGroup.FindByID(STT_KEYBOARD_PERCENTAGE);

	if(pDvmData != NULL)
	{
		pDvmData->GetValueByID(STT_KEYBOARD_PERCENTAGE_BTN0, g_oKeyBoardBtnDescs.m_strPercentageBtn0);
		pDvmData->GetValueByID(STT_KEYBOARD_PERCENTAGE_BTN1, g_oKeyBoardBtnDescs.m_strPercentageBtn1);
		pDvmData->GetValueByID(STT_KEYBOARD_PERCENTAGE_BTN2, g_oKeyBoardBtnDescs.m_strPercentageBtn2);
		pDvmData->GetValueByID(STT_KEYBOARD_PERCENTAGE_BTN3, g_oKeyBoardBtnDescs.m_strPercentageBtn3);
		pDvmData->GetValueByID(STT_KEYBOARD_PERCENTAGE_BTN4, g_oKeyBoardBtnDescs.m_strPercentageBtn4);
		pDvmData->GetValueByID(STT_KEYBOARD_PERCENTAGE_BTN5, g_oKeyBoardBtnDescs.m_strPercentageBtn5);
		pDvmData->GetValueByID(STT_KEYBOARD_PERCENTAGE_BTN6, g_oKeyBoardBtnDescs.m_strPercentageBtn6);
		pDvmData->GetValueByID(STT_KEYBOARD_PERCENTAGE_BTN7, g_oKeyBoardBtnDescs.m_strPercentageBtn7);
		pDvmData->GetValueByID(STT_KEYBOARD_PERCENTAGE_BTN8, g_oKeyBoardBtnDescs.m_strPercentageBtn8);
		pDvmData->GetValueByID(STT_KEYBOARD_PERCENTAGE_BTN9, g_oKeyBoardBtnDescs.m_strPercentageBtn9);
		pDvmData->GetValueByID(STT_KEYBOARD_PERCENTAGE_BTNDOT, g_oKeyBoardBtnDescs.m_strPercentageBtnDot);
//		pDvmData->GetValueByID(STT_KEYBOARD_PERCENTAGE_BTNMINUS, g_oKeyBoardBtnDescs.m_strPercentageBtnMinus);
	}
}

void CSttTestResourceMngr::UpdateSoftKeyboardType()
{
	if (m_oKeyBoardFuncGroup.GetCount()<= 0)
	{
		InitKeyBoardFunc();
	}

// 	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("[问题查找],[%ld],[%ld],[%ld],[%ld],[%ld]"),m_oKeyBoardFuncGroup.GetCount(),
// 		g_nSttWeekUseMode,g_oSystemParas.m_nHasWeek,g_oSystemParas.m_nHasAnalog,g_oSystemParas.m_nHasDigital);

	if ((g_nSttWeekUseMode == STT_WEEK_USE_MODE_DistriTerm)
		&&(g_oSystemParas.m_nHasWeek)&&(!g_oSystemParas.m_nHasAnalog)&&(!g_oSystemParas.m_nHasDigital))
	{
		ShowKeyBoardWeakFunc();
	}
	else
	{
		ShowKeyBoardNormalFunc();
	}
}

void CSttTestResourceMngr::ShowKeyBoardNormalFunc()
{
	CDvmData *pDvmData = NULL;
	//取出NormalVolFunc的值
	pDvmData = (CDvmData*)m_oKeyBoardFuncGroup.FindByID(STT_SOFTKEYBOARD_VOL_NORMAL);

	if (pDvmData != NULL)
	{
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC1_VALUE, g_oKeyBoardBtnDescs.m_strVolFunc1);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC2_VALUE, g_oKeyBoardBtnDescs.m_strVolFunc2);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC3_VALUE, g_oKeyBoardBtnDescs.m_strVolFunc3);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FuncMinus_VALUE, g_oKeyBoardBtnDescs.m_strVolMinus);
	}

	//取出NormalCur的值
	pDvmData = (CDvmData*)m_oKeyBoardFuncGroup.FindByID(STT_SOFTKEYBOARD_CUR_NORMAL);

	if (pDvmData != NULL)
	{
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC1_VALUE, g_oKeyBoardBtnDescs.m_strCurFunc1);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC2_VALUE, g_oKeyBoardBtnDescs.m_strCurFunc2);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC3_VALUE, g_oKeyBoardBtnDescs.m_strCurFunc3);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FuncMinus_VALUE, g_oKeyBoardBtnDescs.m_strCurMinus);
	}
}
		
void CSttTestResourceMngr::ShowKeyBoardWeakFunc()
{
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("切换到弱信号键盘."));
	CDvmData *pDvmData = NULL;
	//取出NormalVolFunc的值
	pDvmData = (CDvmData*)m_oKeyBoardFuncGroup.FindByID(STT_SOFTKEYBOARD_VOL_WEAK);

	if (pDvmData != NULL)
	{
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC1_VALUE, g_oKeyBoardBtnDescs.m_strVolFunc1);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC2_VALUE, g_oKeyBoardBtnDescs.m_strVolFunc2);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC3_VALUE, g_oKeyBoardBtnDescs.m_strVolFunc3);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FuncMinus_VALUE, g_oKeyBoardBtnDescs.m_strVolMinus);	
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("弱信号键盘电压通道映射数据(%s)查找失败."),STT_SOFTKEYBOARD_VOL_WEAK);
	}
		
	//取出NormalCur的值
	pDvmData = (CDvmData*)m_oKeyBoardFuncGroup.FindByID(STT_SOFTKEYBOARD_CUR_WEAK);

	if (pDvmData != NULL)
	{
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC1_VALUE, g_oKeyBoardBtnDescs.m_strCurFunc1);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC2_VALUE, g_oKeyBoardBtnDescs.m_strCurFunc2);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC3_VALUE, g_oKeyBoardBtnDescs.m_strCurFunc3);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FuncMinus_VALUE, g_oKeyBoardBtnDescs.m_strCurMinus);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("弱信号键盘电流通道映射数据(%s)查找失败."),STT_SOFTKEYBOARD_CUR_WEAK);
	}
}

#endif


// void CSttTestResourceMngr::ValidOutputSel()
// {
// 	if ((!g_oLocalSysPara.m_nSupportAnalogOutput)&&(!g_oLocalSysPara.m_nSupportDigitalOutput)&&(g_oLocalSysPara.m_nSupportWeakOutput))
// 	{
// 		g_oSystemParas.m_nHasWeek = 1;
// 	}
// 
// 	if ((!g_oLocalSysPara.m_nSupportAnalogOutput)&&(g_oLocalSysPara.m_nSupportDigitalOutput)&&(!g_oLocalSysPara.m_nSupportWeakOutput))
// 	{
// 		g_oSystemParas.m_nHasDigital = 1;
// 	}
// }

void CSttTestResourceMngr::ValidIecParasSetSel()
{
#ifdef NOT_USE_TEST_RESOURCE_IECFG
	return;
#else
	CIecCfgSysParas* pCIecCfgSysParas = m_oIecDatasMngr.GetSysParasMngr();

	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 1)&&(g_oSystemParas.m_nHasWeek == 0))//如果只有数字信号输出,界面电压电流输出单独设置
	{
		if (pCIecCfgSysParas->m_nPrimParas == 1)
		{
			g_oLocalSysPara.m_fAC_VolMax = 1000000;
			g_oLocalSysPara.m_fAC_VolMin = 1000000;
			g_oLocalSysPara.m_fDC_VolMax = 1000000;
			g_oLocalSysPara.m_fDC_VolMin = 1000000;

			g_oLocalSysPara.m_fAC_CurMax = 10000;
			g_oLocalSysPara.m_fAC_CurMin = 10000;
			g_oLocalSysPara.m_fDC_CurMax = 10000;
			g_oLocalSysPara.m_fDC_CurMin = 10000;
		} 
		else if (g_oSystemParas.m_nIecFormat == 2)
		{
			g_oLocalSysPara.m_fAC_VolMax = 100000;
			g_oLocalSysPara.m_fAC_VolMin = 100000;
			g_oLocalSysPara.m_fDC_VolMax = 100000;
			g_oLocalSysPara.m_fDC_VolMin = 100000;

			g_oLocalSysPara.m_fAC_CurMax = 10000;
			g_oLocalSysPara.m_fAC_CurMin = 10000;
			g_oLocalSysPara.m_fDC_CurMax = 10000;
			g_oLocalSysPara.m_fDC_CurMin = 10000;
		}
		else
		{
			g_oLocalSysPara.m_fAC_VolMax = 1200;
			g_oLocalSysPara.m_fAC_VolMin = 1200;
			g_oLocalSysPara.m_fDC_VolMax = 1200;
			g_oLocalSysPara.m_fDC_VolMin = 1200;

			g_oLocalSysPara.m_fAC_CurMax = 200;
			g_oLocalSysPara.m_fAC_CurMin = 200;
			g_oLocalSysPara.m_fDC_CurMax = 200;
			g_oLocalSysPara.m_fDC_CurMin = 200;
		}
	}
	else if (pCIecCfgSysParas->m_nPrimParas == 1)//只有在存数字量输出的情况下,才能将参数设置设置为一次值
	{
		pCIecCfgSysParas->m_nPrimParas = 0;
		SaveDefaultIec61850Config();//Iec61850配置修改后保存
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("参数设置强制选择为二次值,只有在纯数字量输出的情况下,才能将参数设置为一次值."));
	}
#endif
}

BOOL CSttTestResourceMngr::SaveCurChMapsFile()
{
	CString strSavePath;

#ifdef _PSX_QT_LINUX_
	strSavePath = GetRsDirPath_Device();
#else
	strSavePath = GetCurSelDirPath_SN();
#endif

	if (strSavePath.IsEmpty())
	{
		return FALSE;
	}

	long iSttTestResourceType = STT_TEST_RESOURCE_TYPE_SYNC;
	if (m_pTestResouce != NULL)
	{
		strSavePath += m_pTestResouce->GetChMapFileName();
		iSttTestResourceType = m_pTestResouce->GetTestRsType();
	}
	else//如果当前资源为空,则使用缺省通道映射保存
	{
		strSavePath += _T("ChMapConfig.sync");
		iSttTestResourceType = STT_TEST_RESOURCE_TYPE_SYNC;
	}

	//20240912 huangliang 将保存开入开出到其他文件中
	switch (iSttTestResourceType)
	{
	case STT_TEST_RESOURCE_TYPE_ASYNC:
		SaveAntherMapsFile(STT_TEST_RESOURCE_TYPE_SYNC, strSavePath);
		SaveAntherMapsFile(STT_TEST_RESOURCE_TYPE_4U3I, strSavePath);
		SaveAntherMapsFile(STT_TEST_RESOURCE_TYPE_6U6I, strSavePath);
		break;
	case STT_TEST_RESOURCE_TYPE_SYNC:
		SaveAntherMapsFile(STT_TEST_RESOURCE_TYPE_ASYNC, strSavePath);
		SaveAntherMapsFile(STT_TEST_RESOURCE_TYPE_4U3I, strSavePath);
		SaveAntherMapsFile(STT_TEST_RESOURCE_TYPE_6U6I, strSavePath);
		break;
	case STT_TEST_RESOURCE_TYPE_4U3I:
		SaveAntherMapsFile(STT_TEST_RESOURCE_TYPE_ASYNC, strSavePath);
		SaveAntherMapsFile(STT_TEST_RESOURCE_TYPE_SYNC, strSavePath);
		SaveAntherMapsFile(STT_TEST_RESOURCE_TYPE_6U6I, strSavePath);
		break;
	case STT_TEST_RESOURCE_TYPE_6U6I:
		SaveAntherMapsFile(STT_TEST_RESOURCE_TYPE_ASYNC, strSavePath);
		SaveAntherMapsFile(STT_TEST_RESOURCE_TYPE_SYNC, strSavePath);
		SaveAntherMapsFile(STT_TEST_RESOURCE_TYPE_6U6I, strSavePath);
		break;
	default:
		break;
	}

	return m_oChMaps.SaveChMapsFile(strSavePath);
}

void CSttTestResourceMngr::SaveAntherMapsFile(long iSttTestResourceType, const CString &strHeadPath)	//20240912 huangliang 保存开入开出到其他文件中
{
	//读取原文件
	CSttTestResourceBase *pTestResouce = NULL;
	switch (iSttTestResourceType)
	{
	case STT_TEST_RESOURCE_TYPE_ASYNC:
		pTestResouce = new CSttTestResource_Async;
		break;
	case STT_TEST_RESOURCE_TYPE_SYNC:
		pTestResouce = new CSttTestResource_Sync;
		break;
	case STT_TEST_RESOURCE_TYPE_4U3I:
		pTestResouce = new CSttTestResource_4U3I;
		break;
	case STT_TEST_RESOURCE_TYPE_6U6I:
		pTestResouce = new CSttTestResource_6U6I;
		break;
	default:
		return;
	}

	CSttChMaps oListMaps;
	if (!OpenChMapsFile(&oListMaps, pTestResouce))	//未读取成功，再加载默认值
	{
		//只添加模拟量的默认值，参照函数CreateDefaultChMapsByDevice添加,CreateDefaultChMapsByDevice中涉及了pTestResouce对象
		CreateDefaultChMapsByDevice_Analog(&oListMaps);
		if (g_oSystemParas.m_nHasDigital)
		{
			CreateDefaultChMapsByDevice_Digital(&oListMaps, g_oSystemParas.m_nIecFormat);
		}

		CreateDefaultChMapsByDevice_Weak(&oListMaps);
		if (pTestResouce->GetTestRsType() == STT_TEST_RESOURCE_TYPE_4U3I)
		{
			oListMaps.SetChCountU(4);
			oListMaps.SetChCountI(3);
		}
		else if (pTestResouce->GetTestRsType() == STT_TEST_RESOURCE_TYPE_6U6I)
		{
			oListMaps.SetChCountU(6);
			oListMaps.SetChCountI(6);
		}

		UpdateChNames_UzIz(&oListMaps, NULL);
		oListMaps.SortByRsIndex();
	}

	//删除原来的开入开出数据
	oListMaps.ClearBinBoutMaps();

	//把开入开出同步进来
	m_oChMaps.CopyBinBout(&oListMaps);

	//保存数据
	CString strSavePath = strHeadPath;
	strSavePath = ChangeFilePostfix(strSavePath, pTestResouce->GetChMapsFilePostfix());
	oListMaps.SaveChMapsFile(strSavePath);
	delete pTestResouce;
}

BOOL CSttTestResourceMngr::SaveCurDeviceFile()
{
	CString strSavePath;
#ifdef _PSX_QT_LINUX_
	strSavePath = GetRsDirPath_Device();
#else
	strSavePath = GetCurSelDirPath_SN();
#endif

	if (strSavePath.IsEmpty())
	{
		return FALSE;
	}

	strSavePath += _T("DeviceModel.xml");
	return m_oCurrDevice.SaveSttAdjFile(strSavePath);
}

void CSttTestResourceMngr::CreateDefaultChMapsByDevice_Analog(CSttChMaps *pCurChMaps)
{
	CSttChMap *pSttChMap = NULL;
	CSttModuleTag *pSttModuleTag = NULL;
	long nVolModuleIndex = 1,nCurModuleIndex = 1,nVolCurModuleIndex = 1,nVolChIndex = 1,nCurChIndex = 1;
	CString strSoftRsName,strSoftRsID,strHdRsID;
	POS pos = m_oAnalogU_Tags.GetHeadPosition();

	while(pos)//创建模拟量电压模块缺省通道映射
	{
		pSttModuleTag = (CSttModuleTag *)m_oAnalogU_Tags.GetNext(pos);

		for (int nIndex = 1;nIndex <= pSttModuleTag->m_nChCountU;nIndex++)
		{
			if (nVolChIndex>MAX_VOLTAGE_COUNT)//如果电压软件资源通道数超过了最大限制,则重新循环,将2个硬件资源,映射到同一个软件资源
			{
				nVolChIndex = 1;
			}

			strSoftRsID.Format(_T("U%ld"),nVolChIndex);
			pSttChMap = pCurChMaps->GetChMap(strSoftRsID);

			if (pSttChMap == NULL)
			{
				strSoftRsName = GetModuleDefaultName(_T("U"),nVolChIndex);
				pSttChMap = pCurChMaps->AddChMap(strSoftRsName,strSoftRsID);
			}

			strHdRsID.Format(_T("U%ld_%ld"),nVolModuleIndex,nIndex);
			pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_ANALOG,strHdRsID,strHdRsID);
			nVolChIndex++;
		}

		nVolModuleIndex++;
	}

	pos = m_oAnalogI_Tags.GetHeadPosition();

	while(pos)//创建模拟量电流模块缺省通道映射
	{
		pSttModuleTag = (CSttModuleTag *)m_oAnalogI_Tags.GetNext(pos);

		for (int nIndex = 1;nIndex <= pSttModuleTag->m_nChCountI;nIndex++)
		{
			if (nCurChIndex>MAX_CURRENT_COUNT)//如果电流软件资源通道数超过了最大限制,则重新循环,将2个硬件资源,映射到同一个软件资源
			{
				nCurChIndex = 1;
			}

			strSoftRsID.Format(_T("I%ld"),nCurChIndex);
			pSttChMap = pCurChMaps->GetChMap(strSoftRsID);

			if (pSttChMap == NULL)
			{
				strSoftRsName = GetModuleDefaultName(_T("I"),nCurChIndex);
				pSttChMap = pCurChMaps->AddChMap(strSoftRsName,strSoftRsID);
			}

			strHdRsID.Format(_T("I%ld_%ld"),nCurModuleIndex,nIndex);
			pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_ANALOG,strHdRsID,strHdRsID);
			nCurChIndex++;
		}

		nCurModuleIndex++;
	}

	if (nVolModuleIndex>nCurModuleIndex)//取独立电压电流模块中的较大的哪一个index
	{
		nVolCurModuleIndex = nVolModuleIndex;
	} 
	else
	{
		nVolCurModuleIndex = nCurModuleIndex;
	}

 	pos = m_oAnalogUI_Tags.GetHeadPosition();
 
 	while(pos)//创建模拟量电流模块缺省通道映射
 	{
 		pSttModuleTag = (CSttModuleTag *)m_oAnalogUI_Tags.GetNext(pos);

		for (int nIndex = 1;nIndex <= pSttModuleTag->m_nChCountU;nIndex++)
		{
			if (nVolChIndex>MAX_VOLTAGE_COUNT)//如果电压软件资源通道数超过了最大限制,则重新循环,将2个硬件资源,映射到同一个软件资源
			{
				nVolChIndex = 1;
			}

			strSoftRsID.Format(_T("U%ld"),nVolChIndex);
			pSttChMap = pCurChMaps->GetChMap(strSoftRsID);

			if (pSttChMap == NULL)
			{
				strSoftRsName = GetModuleDefaultName(_T("U"),nVolChIndex);
				pSttChMap = pCurChMaps->AddChMap(strSoftRsName,strSoftRsID);
			}

			strHdRsID.Format(_T("U%ld_%ld"),nVolCurModuleIndex,nIndex);
			pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_ANALOG,strHdRsID,strHdRsID);
			nVolChIndex++;
		}
 
 		for (int nIndex = 1;nIndex <= pSttModuleTag->m_nChCountI;nIndex++)
 		{
 			if (nCurChIndex>MAX_CURRENT_COUNT)//如果电流软件资源通道数超过了最大限制,则重新循环,将2个硬件资源,映射到同一个软件资源
 			{
 				nCurChIndex = 1;
 			}
 
 			strSoftRsID.Format(_T("I%ld"),nCurChIndex);
 			pSttChMap = pCurChMaps->GetChMap(strSoftRsID);
 
 			if (pSttChMap == NULL)
 			{
 				strSoftRsName = GetModuleDefaultName(_T("I"),nCurChIndex);
 				pSttChMap = pCurChMaps->AddChMap(strSoftRsName,strSoftRsID);
 			}
 
 			strHdRsID.Format(_T("I%ld_%ld"),nVolCurModuleIndex,nIndex);
 			pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_ANALOG,strHdRsID,strHdRsID);
 			nCurChIndex++;
 		}
 
 		nVolCurModuleIndex++;
 	}
};

void CSttTestResourceMngr::CreateDefaultChMapsByDevice_Digital(CSttChMaps *pCurChMaps,long nIecFormat)
{
	if (nIecFormat == STT_IEC_FORMAT_60044_8)
	{
		CreateDefaultChMapsByDevice_Digital_FT3(pCurChMaps);
	}
	else if (nIecFormat == STT_IEC_FORMAT_60044_8DC)
	{
		CreateDefaultChMapsByDevice_Digital_FT3DC(pCurChMaps);
	}
	else
	{
		CreateDefaultChMapsByDevice_Digital_IEC92(pCurChMaps);
	}
}

void CSttTestResourceMngr::CreateDefaultChMapsByDevice_Digital_FT3DC(CSttChMaps *pCurChMaps)
{
	CSttChMap *pSttChMap = NULL;
	CSttModuleTag *pSttModuleTag = NULL;
	CString strSoftRsName,strSoftRsID,strHdRsID;
	long nCurrentIndex = 1,nVoltageIndex = 1;
	long nModuleNum = GetDigitalModuleNum();

	if (nModuleNum<=0)
	{
		nModuleNum = 1;
	}

	for (int nGroupIndex = 1;nGroupIndex<=2;nGroupIndex++)
	{
		for (int nChIndex = 1; nChIndex<=3;nChIndex++)
		{
			strSoftRsName.Format(_T("U%ld-%ld"),nGroupIndex,nChIndex);
			strSoftRsID.Format(_T("U%ld"),nVoltageIndex);
			pSttChMap = pCurChMaps->AddChMap_FindByID(strSoftRsName,strSoftRsID);

			for (int nModuleIndex = 1;nModuleIndex <= nModuleNum;nModuleIndex++)
			{
				strHdRsID.Format(_T("Ud%d_%ld"),nModuleIndex,nVoltageIndex);
				pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
			}

// 			strHdRsID.Format(_T("Ud1_%ld"),nVoltageIndex);
// 			pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
			nVoltageIndex++;
		}
	}

	for (int nGroupIndex = 1;nGroupIndex<=4;nGroupIndex++)
	{
		for (int nChIndex = 1; nChIndex<=3;nChIndex++)
		{
			strSoftRsName.Format(_T("I%ld-%ld"),nGroupIndex,nChIndex);
			strSoftRsID.Format(_T("I%ld"),nCurrentIndex);
			pSttChMap = pCurChMaps->AddChMap_FindByID(strSoftRsName,strSoftRsID);

			for (int nModuleIndex = 1;nModuleIndex<=nModuleNum;nModuleIndex++)
			{
				strHdRsID.Format(_T("Id%d_%ld"),nModuleIndex,nCurrentIndex);
				pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
			}

// 			strHdRsID.Format(_T("Id1_%ld"),nCurrentIndex);
// 			pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
			nCurrentIndex++;
		}
	}

// 	for (int nGroupIndex = 1;nGroupIndex<=3;nGroupIndex++)
// 	{
// 		strSoftRsName.Format(_T("UdL%ld"),nGroupIndex);
// 		strSoftRsID.Format(_T("U%ld"),nVoltageIndex);
// 		pSttChMap = pCurChMaps->AddChMap_FindByID(strSoftRsName,strSoftRsID);
// 		strHdRsID.Format(_T("Ud1_%ld"),nVoltageIndex);
// 		pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
// 		nVoltageIndex++;
// 
// 		strSoftRsName.Format(_T("IdH%ld"),nGroupIndex);
// 		strSoftRsID.Format(_T("I%ld"),nCurrentIndex);
// 		pSttChMap = pCurChMaps->AddChMap_FindByID(strSoftRsName,strSoftRsID);
// 		strHdRsID.Format(_T("Id1_%ld"),nCurrentIndex);
// 		pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
// 		nCurrentIndex++;
// 
// 		strSoftRsName.Format(_T("IdN%ld"),nGroupIndex);
// 		strSoftRsID.Format(_T("I%ld"),nCurrentIndex);
// 		pSttChMap = pCurChMaps->AddChMap_FindByID(strSoftRsName,strSoftRsID);
// 		strHdRsID.Format(_T("Id1_%ld"),nCurrentIndex);
// 		pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
// 		nCurrentIndex++;
// 
// 		strSoftRsName.Format(_T("IdL%ld"),nGroupIndex);
// 		strSoftRsID.Format(_T("I%ld"),nCurrentIndex);
// 		pSttChMap = pCurChMaps->AddChMap_FindByID(strSoftRsName,strSoftRsID);
// 		strHdRsID.Format(_T("Id1_%ld"),nCurrentIndex);
// 		pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
// 		nCurrentIndex++;
// 
// 		strSoftRsName.Format(_T("IdE%ld"),nGroupIndex);
// 		strSoftRsID.Format(_T("I%ld"),nCurrentIndex);
// 		pSttChMap = pCurChMaps->AddChMap_FindByID(strSoftRsName,strSoftRsID);
// 		strHdRsID.Format(_T("Id1_%ld"),nCurrentIndex);
// 		pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
// 		nCurrentIndex++;
// 	}
// 
// 	for (int nGroupIndex = 1;nGroupIndex<=3;nGroupIndex++)
// 	{
// 		strSoftRsName.Format(_T("UdN%ld"),nGroupIndex);
// 		strSoftRsID.Format(_T("U%ld"),nVoltageIndex);
// 		pSttChMap = pCurChMaps->AddChMap_FindByID(strSoftRsName,strSoftRsID);
// 		strHdRsID.Format(_T("Ud1_%ld"),nVoltageIndex);
// 		pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
// 		nVoltageIndex++;
// 	}

	for (int nChIndex = 1;nChIndex<=6;nChIndex++)
	{
		strSoftRsID.Format(_T("U%ld"),nVoltageIndex);
		pSttChMap = pCurChMaps->GetChMap(strSoftRsID);

		if (pSttChMap == NULL)
		{
			strSoftRsName = GetModuleDefaultName(_T("U"),nChIndex);
			pSttChMap = pCurChMaps->AddChMap(strSoftRsName,strSoftRsID);
		}

		for (int nModuleIndex = 1;nModuleIndex <= nModuleNum;nModuleIndex++)
		{
			strHdRsID.Format(_T("Ud%d_%ld"),nModuleIndex,nVoltageIndex);
			pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
		}

// 		strHdRsID.Format(_T("Ud1_%ld"),nVoltageIndex);
// 		pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);

		strSoftRsID.Format(_T("I%ld"),nCurrentIndex);
		pSttChMap = pCurChMaps->GetChMap(strSoftRsID);

		if (pSttChMap == NULL)
		{
			strSoftRsName = GetModuleDefaultName(_T("I"),nChIndex);
			pSttChMap = pCurChMaps->AddChMap(strSoftRsName,strSoftRsID);
		}

		for (int nModuleIndex = 1;nModuleIndex<=nModuleNum;nModuleIndex++)
		{
			strHdRsID.Format(_T("Id%d_%ld"),nModuleIndex,nCurrentIndex);
			pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
		}

// 		strHdRsID.Format(_T("Id1_%ld"),nCurrentIndex);
// 		pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
		nCurrentIndex++;
		nVoltageIndex++;
	}
}

void CSttTestResourceMngr::CreateDefaultChMapsByDevice_Digital_FT3(CSttChMaps *pCurChMaps)
{
	CSttChMap *pSttChMap = NULL;
	CSttModuleTag *pSttModuleTag = NULL;
	CString strSoftRsName,strSoftRsID,strHdRsID;
	long nModuleNum = GetDigitalModuleNum();

	if (nModuleNum<=0)
	{
		nModuleNum = 1;
	}

	for (int nChIndex = 1;nChIndex<=18;nChIndex++)
	{
		strSoftRsID.Format(_T("U%ld"),nChIndex);
		pSttChMap = pCurChMaps->GetChMap(strSoftRsID);

		if (pSttChMap == NULL)
		{
			strSoftRsName = GetModuleDefaultName(_T("U"),nChIndex);
			pSttChMap = pCurChMaps->AddChMap(strSoftRsName,strSoftRsID);
		}

		for (int nModuleIndex = 1;nModuleIndex <= nModuleNum;nModuleIndex++)
		{
			strHdRsID.Format(_T("Ud%d_%ld"),nModuleIndex,nChIndex);
			pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
		}

// 		strHdRsID.Format(_T("Ud1_%ld"),nChIndex);
// 		pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);

		strSoftRsID.Format(_T("I%ld"),nChIndex);
		pSttChMap = pCurChMaps->GetChMap(strSoftRsID);

		if (pSttChMap == NULL)
		{
			strSoftRsName = GetModuleDefaultName(_T("I"),nChIndex);
			pSttChMap = pCurChMaps->AddChMap(strSoftRsName,strSoftRsID);
		}

		for (int nModuleIndex = 1;nModuleIndex<=nModuleNum;nModuleIndex++)
		{
			strHdRsID.Format(_T("Id%d_%ld"),nModuleIndex,nChIndex);
			pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
		}

// 		strHdRsID.Format(_T("Id1_%ld"),nChIndex);
// 		pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
	}
}

void CSttTestResourceMngr::CreateDefaultChMapsByDevice_Digital_IEC92(CSttChMaps *pCurChMaps)
{
	CSttChMap *pSttChMap = NULL;
	CSttModuleTag *pSttModuleTag = NULL;
	CString strSoftRsName,strSoftRsID,strHdRsID;
	long nModuleNum = GetDigitalModuleNum();

	if (nModuleNum<=0)
	{
		nModuleNum = 1;
	}

	for (int nChIndex = 1;nChIndex<=18;nChIndex++)
	{
		strSoftRsID.Format(_T("U%ld"),nChIndex);
		pSttChMap = pCurChMaps->GetChMap(strSoftRsID);

		if (pSttChMap == NULL)
		{
			strSoftRsName = GetModuleDefaultName(_T("U"),nChIndex);
			pSttChMap = pCurChMaps->AddChMap(strSoftRsName,strSoftRsID);
		}

		for (int nModuleIndex = 1;nModuleIndex <= nModuleNum;nModuleIndex++)
		{
			strHdRsID.Format(_T("Ud%d_%ld"),nModuleIndex,nChIndex);
			pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
		}

		strSoftRsID.Format(_T("I%ld"),nChIndex);
		pSttChMap = pCurChMaps->GetChMap(strSoftRsID);

		if (pSttChMap == NULL)
		{
			strSoftRsName = GetModuleDefaultName(_T("I"),nChIndex);
			pSttChMap = pCurChMaps->AddChMap(strSoftRsName,strSoftRsID);
		}

		for (int nModuleIndex = 1;nModuleIndex<=nModuleNum;nModuleIndex++)
		{
			strHdRsID.Format(_T("Id%d_%ld"),nModuleIndex,nChIndex);
			pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
		}
	}

// 	strSoftRsID = _T("U19");  //zhouhj 20211102
// 	pSttChMap = pCurChMaps->GetChMap(strSoftRsID);
// 
// 	if (pSttChMap == NULL)
// 	{
// 		strSoftRsName = _T("Uz");
// 		pSttChMap = pCurChMaps->AddChMap(strSoftRsName,strSoftRsID);
// 	}
// 
// 	strHdRsID = _T("Ud1_19");
// 	pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_DIGITAL,strHdRsID,strHdRsID);
}

void CSttTestResourceMngr::CreateDefaultChMapsByDevice_Weak(CSttChMaps *pCurChMaps)
{
	CSttChMap *pSttChMap = NULL;
	CSttHdCh* pSttHdCh = NULL;
	CSttModuleTag *pSttModuleTag = NULL;
	long nModuleIndex = 1,nChIndex = 1;
	CString strSoftRsName,strSoftRsID,strHdRsID;
	POS pos = m_oWeak_Tags.GetHeadPosition();

	while(pos)//创建弱信号模块缺省电压通道映射
	{
		pSttModuleTag = (CSttModuleTag *)m_oWeak_Tags.GetNext(pos);

		for (int nIndex = 1;nIndex <= pSttModuleTag->m_nChCountU_Week;nIndex++)
		{
			if (nChIndex>MAX_VOLTAGE_COUNT)//如果电压软件资源通道数超过了最大限制,则重新循环,将2个硬件资源,映射到同一个软件资源
			{
				nChIndex = 1;
			}

			strSoftRsID.Format(_T("U%ld"),nChIndex);
			pSttChMap = pCurChMaps->GetChMap(strSoftRsID);

			if (pSttChMap == NULL)
			{
				strSoftRsName = GetModuleDefaultName(_T("U"),nChIndex);
				pSttChMap = pCurChMaps->AddChMap(strSoftRsName,strSoftRsID);
			}

			strHdRsID.Format(_T("Uw%ld_%ld"),nModuleIndex,nIndex);
			pSttHdCh = pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_WEEK,strHdRsID,strHdRsID);

			if (g_nSttWeekUseMode == STT_WEEK_USE_MODE_DistriTerm)
			{
				pSttHdCh->SetTransRate_Weak(1.0f,1.0f);
			} 
			else
			{
				pSttHdCh->SetTransRate_Weak(120.0f,7.07f);
			}
			nChIndex++;
		}

		nModuleIndex++;
	}

	nModuleIndex = 1;
	nChIndex = 1;
	pos = m_oWeak_Tags.GetHeadPosition();

	while(pos)//创建弱信号模块缺省电流通道映射
	{
		pSttModuleTag = (CSttModuleTag *)m_oWeak_Tags.GetNext(pos);

		for (int nIndex = 1;nIndex <= pSttModuleTag->m_nChCountI_Week;nIndex++)
		{
			if (nChIndex>MAX_CURRENT_COUNT)//如果电压软件资源通道数超过了最大限制,则重新循环,将2个硬件资源,映射到同一个软件资源
			{
				nChIndex = 1;
			}

			strSoftRsID.Format(_T("I%ld"),nChIndex);
			pSttChMap = pCurChMaps->GetChMap(strSoftRsID);

			if (pSttChMap == NULL)
			{
				strSoftRsName = GetModuleDefaultName(_T("I"),nChIndex);
				pSttChMap = pCurChMaps->AddChMap(strSoftRsName,strSoftRsID);
			}

			strHdRsID.Format(_T("Uw%ld_%ld"),nModuleIndex,pSttModuleTag->m_nChCountU_Week+nIndex);
			pSttHdCh = pSttChMap->AddHdMapCh(STT_MODULETYPE_ID_WEEK,strHdRsID,strHdRsID);

			if (g_nSttWeekUseMode == STT_WEEK_USE_MODE_DistriTerm)
			{
				pSttHdCh->SetTransRate_Weak(1.0f,1.0f);
			} 
			else
			{
				pSttHdCh->SetTransRate_Weak(30.0f,7.07f);
			}

			nChIndex++;
		}

		nModuleIndex++;
	}
}

//检查该硬件资源通道是否为合并通道,如果是合并通道,并且是合并通道的第一个通道,则将剩余合并通道填入,并计算对应系数
//如果不是合并通道的第一个通道,则删除当前硬件通道
//对于非合并通道,其系数固定设置为1
BOOL CheckHdCh_Coef(CSttHdCh *pHdCh,const long &nChType,const long &nModuleType,const long &nModuleIndex,const long &nChIndex)
{
	CSttHdChs *pHdChs = (CSttHdChs*)pHdCh->GetParent();
	CSttHdCh *pHdChTmp = NULL;
	CString strTmp;

	if (nModuleType == STT_MODULE_TYPE_CURRENT)
	{
		tmt_GearSetCurModules *pGearSetCurModules = &g_oSystemParas.m_oGearSetCurModules;

		if (pGearSetCurModules->m_nCurModuleNum<nModuleIndex)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前电流模块编号(%ld)大于电流模块总数量(%ld)."),nModuleIndex,pGearSetCurModules->m_nCurModuleNum);
			return FALSE;
		}

		if (pGearSetCurModules->m_oCurModuleGear[nModuleIndex-1].m_nMergeCurTerminal == STT_LARGE_CURRENT_MERGE_ONE_CH)
		{
			if (nChIndex == 1)//首先判断是否为第一个通道,如果是第一个通道,需要将其它通道也合并进来
			{
				pHdCh->m_fCoef = 1.0f/6.0f;
				strTmp = pHdCh->m_strID;
				strTmp.Replace(_T("_1"),_T("_2"));
				pHdChs->FindAddHdCh(strTmp,strTmp,pHdCh->m_fCoef);
				strTmp.Replace(_T("_2"),_T("_3"));
				pHdChs->FindAddHdCh(strTmp,strTmp,pHdCh->m_fCoef);
				strTmp.Replace(_T("_3"),_T("_4"));
				pHdChs->FindAddHdCh(strTmp,strTmp,pHdCh->m_fCoef);
				strTmp.Replace(_T("_4"),_T("_5"));
				pHdChs->FindAddHdCh(strTmp,strTmp,pHdCh->m_fCoef);
				strTmp.Replace(_T("_5"),_T("_6"));
				pHdChs->FindAddHdCh(strTmp,strTmp,pHdCh->m_fCoef);
			}
			else if (!pHdChs->HasHdCh(pHdCh->m_strID.GetAt(0),nModuleIndex,1))//如果不是第一个通道则判断该硬件通道集合下是否包含第一个通道,如果不包含,则需要将该硬件通道删除
			{
				pHdChs->Delete(pHdCh);
			}
		}
 		else if (pGearSetCurModules->m_oCurModuleGear[nModuleIndex-1].m_nMergeCurTerminal == STT_LARGE_CURRENT_MERGE_THREE_CH)
 		{
 			pHdCh->m_fCoef = 0.5f;
 
 			if (nChIndex == 1)
 			{
 				strTmp = pHdCh->m_strID;
 				strTmp.Replace(_T("_1"),_T("_4"));
 				pHdChs->FindAddHdCh(strTmp,strTmp,pHdCh->m_fCoef);
 			}
 			else if (nChIndex == 2)
 			{
 				strTmp = pHdCh->m_strID;
 				strTmp.Replace(_T("_2"),_T("_5"));
 				pHdChs->FindAddHdCh(strTmp,strTmp,pHdCh->m_fCoef);
 			}
 			else if (nChIndex == 3)
 			{
 				strTmp = pHdCh->m_strID;
 				strTmp.Replace(_T("_3"),_T("_6"));
 				pHdChs->FindAddHdCh(strTmp,strTmp,pHdCh->m_fCoef);
 			}
 			else if (!pHdChs->HasHdCh(pHdCh->m_strID.GetAt(0),nModuleIndex,nChIndex-3))//如果不是第一个通道则判断该硬件通道集合下是否包含第一个通道,如果不包含,则需要将该硬件通道删除
 			{
 				pHdChs->Delete(pHdCh);
 			}
 		}
 		else
 			pHdCh->m_fCoef = 1.0f;
	}

	return TRUE;
}

BOOL CSttTestResourceMngr::GetAnalogCurrentMergeCoef(long &nCoef)
{
	nCoef = 1;
	BOOL bHas = FALSE;
	tmt_CurModuleGear *pCurModuleGear = g_oSystemParas.m_oGearSetCurModules.m_oCurModuleGear;

	CExBaseList *pChMaps = &m_oChMaps;
	for (int nIndex = 0;nIndex<g_oSystemParas.m_oGearSetCurModules.m_nCurModuleNum;nIndex++)
	{
		if ((pCurModuleGear[nIndex].m_nMergeCurTerminal == STT_LARGE_CURRENT_MERGE_THREE_CH) && (nCoef<2))
		{
			//if (m_oChMaps.HasAnalogCurrModuleHdCh(nIndex + 1))
			if (/*pChMaps->*/Global_HasAnalogCurrModuleHdCh(pChMaps,nIndex + 1))//20240904 huangliang 仅模拟量需要
			{
				nCoef = 2;
				bHas = TRUE;
			}
		}
		else if (pCurModuleGear[nIndex].m_nMergeCurTerminal == STT_LARGE_CURRENT_MERGE_ONE_CH)
		{
			//if (m_oChMaps.HasAnalogCurrModuleHdCh(nIndex + 1))
			if (/*pChMaps->*/Global_HasAnalogCurrModuleHdCh(pChMaps,nIndex + 1))//20240904 huangliang 仅模拟量需要
			{
				nCoef = 6;
				bHas = TRUE;
			}
		}
	}

	return bHas;
}

/*
1）遍历全部通道映射的硬件资源，并在实际硬件资源对象进行查找，如果未查找到，将该映射删除；
*/
BOOL CSttTestResourceMngr::ValidHardRsChMaps()
{
	if (!HasLoadDevice())
	{
		if (!SelectDeviceFromLocalDB())//如果打开本地Device文件失败，则需要创建缺省软件资源
		{
			return FALSE;
		}
	}

	if (!HasLoadChMaps())
	{
		return FALSE;
	}

	long nModuleType,nChType ,nModuleIndex,nChIndex = 0;
	CSttModuleTag *pModuleTag = NULL;
	CSttModuleTags *pCurModuleTags = NULL;
	CSttChMap *pChMap = NULL;
	CSttHdChs *pHdChs = NULL;
	CSttHdCh *pHdCh = NULL;
	POS pos_hd_chs = NULL;
	POS pos_hd_ch = NULL;
	BOOL bVolCurModule = FALSE;//是否为电压电流混合模块
	POS pos_map = m_oChMaps.GetHeadPosition();

	while(pos_map)
	{
		pChMap = (CSttChMap*)m_oChMaps.GetNext(pos_map);

		pos_hd_chs = pChMap->GetHeadPosition();

		while(pos_hd_chs)
		{
			pHdChs = (CSttHdChs *)pChMap->GetNext(pos_hd_chs);

			if (pHdChs->m_strID == STT_MODULETYPE_ID_DIGITAL)//数字信号不需要验证硬件资源
			{
				continue;
			}

			pos_hd_ch = pHdChs->GetHeadPosition();

			while(pos_hd_ch)
			{
				pHdCh = (CSttHdCh *)pHdChs->GetNext(pos_hd_ch);

				if (!ParseHdRsID(pHdCh->m_strID,nChType,nModuleType,nModuleIndex,nChIndex))//如果硬件资源通道ID解析失败，则删除该硬件资源映射
				{
					pHdChs->Delete(pHdCh);
					continue;
				}

				bVolCurModule = FALSE;

				if (nModuleType == STT_MODULE_TYPE_VOLT)
				{
					pCurModuleTags = &m_oAnalogU_Tags;
				}
				else if (nModuleType == STT_MODULE_TYPE_CURRENT)
				{
					pCurModuleTags = &m_oAnalogI_Tags;
				}
				else if ((nModuleType == STT_MODULE_TYPE_WEEK_EX)/*||(nModuleType == STT_MODULE_TYPE_WEEK_MAIN)*/)
				{
					pCurModuleTags = &m_oWeak_Tags;
				}
				else if ((nModuleType == STT_MODULE_TYPE_ADMU))//zhouhj 2024.2.4 
				{
					pCurModuleTags = &m_oWeak_Tags;
				}
				else
				{
					ASSERT(FALSE);
					continue;
				}

				pModuleTag = pCurModuleTags->GetAtIndex(nModuleIndex-1);//nModuleIndex从1开始编号，故要先减去1

				if (pModuleTag != NULL)//如果找到该模块,则进行后续验证
				{
				}
				else if (m_oAnalogUI_Tags.GetCount() == 0)//如果没有电压电流混合模块,并且当前模块也未找到,则当前硬件资源不存在
				{
					pHdChs->Delete(pHdCh);
					continue;
				}
				else if (m_oAnalogUI_Tags.GetCount() > 0)//如果存在电压电流混合模块
				{
					if (m_oAnalogU_Tags.GetCount()>m_oAnalogI_Tags.GetCount())
					{
						nModuleIndex -= m_oAnalogU_Tags.GetCount();
					} 
					else
					{
						nModuleIndex -= m_oAnalogI_Tags.GetCount();
					}

					pModuleTag = m_oAnalogUI_Tags.GetAtIndex(nModuleIndex-1);//nModuleIndex从1开始编号，故要先减去1

					if (pModuleTag == NULL)
					{
						pHdChs->Delete(pHdCh);
						continue;
					}

					bVolCurModule = TRUE;
				}

				if ((nModuleType == STT_MODULE_TYPE_WEEK_EX)/*||(nModuleType == STT_MODULE_TYPE_WEEK_MAIN)*/)//如果为弱信号通道
				{
					if ((pModuleTag->m_nChCountU_Week+pModuleTag->m_nChCountI_Week)<nChIndex)
					{
						pHdChs->Delete(pHdCh);
					}
				}
				else if ((nModuleType == STT_MODULE_TYPE_ADMU))//如果为ADMU(弱信号通道)
				{
					if ((pModuleTag->m_nChCountU_Week+pModuleTag->m_nChCountI_Week)<nChIndex)
					{
						pHdChs->Delete(pHdCh);
					}
				}
				else if (nChType == STT_MACRO_CH_TYPE_VOL)
				{
					if (pModuleTag->m_nChCountU<nChIndex)
					{
						pHdChs->Delete(pHdCh);
					}
				}
				else
				{
					if (pModuleTag->m_nChCountI<nChIndex)
					{
						pHdChs->Delete(pHdCh);
					}
				}

				if (!bVolCurModule)
				{
					CheckHdCh_Coef(pHdCh,nChType,nModuleType,nModuleIndex,nChIndex);
				}
			}
		}
	}

	return TRUE;
}

/*
1）首先判断Device对象是否为空，如果为空，则不需要软件资源验证，只需判断当前软件资源是否为空，如果为空，创建缺省4U3I软件资源；
2)判断当前通道映射文件是否为空，如果为空，根据Device，创建缺省通道映射文件；
3）遍历通道映射文件中所有软件资源，传入当前输出模式，判断该通道是否存在输出的硬件资源，如果不存在，则删除该软件资源；
4）只保留根据当前输出模式存在的软件资源，并对所有软件资源重新命名。
*/
void CSttTestResourceMngr::CreateSoftRsCh()
{
	ASSERT(m_pTestResouce);
	m_pTestResouce->ClearAll();

	if (!HasLoadDevice())//如果
	{
		m_pTestResouce->CreateSoftResource();
		SetCHVINum();
		m_pTestResouce->InitAfterCreated();
		return;
	}

	if (!HasLoadChMaps())
	{
		CreateDefaultChMapsByDevice(&m_oChMaps,g_oSystemParas.m_nIecFormat ,g_oSystemParas.m_nHasDigital);
		SaveCurChMapsFile();
	}

//	GetAllModuleTags();
	POS pos = m_oChMaps.GetHeadPosition();
	CSttChMap *pSttChMap = NULL;
	long nChIndexU = 1,nChIndexI = 1;
	CString strTmp;
	BOOL bModified = FALSE;

	while(pos)
	{
		pSttChMap = (CSttChMap *)m_oChMaps.GetNext(pos);

		if (!pSttChMap->HasMapHdResource(g_oSystemParas.m_nHasAnalog,g_oSystemParas.m_nHasDigital,g_oSystemParas.m_nHasWeek))
		{
			m_oChMaps.Delete(pSttChMap);
			bModified = TRUE;
			continue;
		}

		if (pSttChMap->IsVoltageCh())
		{
			pSttChMap->m_strID.Format(_T("U%ld"),nChIndexU);
			pSttChMap->m_nRsIndex = nChIndexU;
			nChIndexU++;
		}
		else if (pSttChMap->IsCurrentCh())
		{
			pSttChMap->m_strID.Format(_T("I%ld"),nChIndexI);
			pSttChMap->m_nRsIndex = nChIndexI;
			nChIndexI++;
		}
		else//如果既不是电压通道，也不是电流通道，则该通道是问题通道，理论上不应该存在，删除该通道
		{
			m_oChMaps.Delete(pSttChMap);
			bModified = TRUE;
			continue;
		}

		m_pTestResouce->AddNewData(pSttChMap->m_strName,pSttChMap->m_strID);
	}

	UpdateChNames_UzIz(&m_oChMaps,m_pTestResouce);
	m_pTestResouce->InitAfterCreated();
	SetCHVINum();

	if (bModified)
	{
		SaveCurChMapsFile();
	}
}

/*
1)根据当前软件资源映射m_oChMaps创建实时数据通道CmacroChannel；
*/
void CSttTestResourceMngr::CreateRtDataMngr()
{
	ASSERT(m_pTestResouce);
	m_oRtDataMngr.InitSoftResource(m_pTestResouce,&m_oChMaps);
}

void CSttTestResourceMngr::SetCHVINum()
{
	if (g_oSttTestResourceMngr.m_pTestResouce)
	{
		g_oLocalSysPara.m_nCHVNum = g_oSttTestResourceMngr.m_pTestResouce->m_oVolChRsListRef.GetCount();
		g_oLocalSysPara.m_nCHINum = g_oSttTestResourceMngr.m_pTestResouce->m_oCurChRsListRef.GetCount();
	}
}

BOOL CSttTestResourceMngr::HasContrlBlockSelected_IecConfig()
{
#ifdef NOT_USE_TEST_RESOURCE_IECFG
	return TRUE;
#else
	return m_oIecDatasMngr.HasContrlBlock_Selected();
#endif
}

/*
在装置型号选择改变后，需要进行如下操作：
1）CreateChMaps重新创建或打开映射文件；
2）ValidHardRsChMaps；
3）CreateSoftRsCh；
4）CreateRtDataMngr；
在联机读取Device后：
1）如果型号与当前不一致，则按照型号不一致处理；
2）如果型号一致，调用m_oCurrDevice成员函数验证硬件资源是否一致（或装置编号是否一致）；
3）如果不一致，则以读取的为准，创建m_oCurrDevice链表；
4）ValidHardRsChMaps；
5）CreateSoftRsCh；
6）CreateRtDataMngr；
在修改了软件资源映射关系后：
1）CreateSoftRsCh；
2）CreateRtDataMngr；
在修改了通道映射别名后：
1）只将通道映射文件中的别名赋值给软件资源m_strName
在同一个型号，切换了装置编号后：
1）调用m_oCurrDevice成员函数验证硬件资源是否一致；
3）如果不一致，则以读取的为准，创建m_oCurrDevice链表；
4）ValidHardRsChMaps；
5）CreateSoftRsCh；
6）CreateRtDataMngr；
*/

//zhouhj 2023.11.13 原定增加单独电压电流最大值方式，现改为上位机遍历全部通道查找对应最大值
BOOL Global_SetMaxMinValue_VolCurModule(CDataGroup *pAttrGroup,float *pfAC_MaxMax,float *pfAC_MaxMin,float *pfDC_MaxMax,float *pfDC_MaxMin,BOOL bVol)
{
	if (pAttrGroup == NULL)
	{
		return FALSE;
	}

	CDataGroup *pChMapDefGroup = (CDataGroup*)pAttrGroup->FindByID(STT_ADJ_ID_ChMapDef);

	if (pChMapDefGroup == NULL)
	{
		return FALSE;
	}

	CDataGroup *pChDefGroup = (CDataGroup*)pChMapDefGroup->FindByID(STT_ADJ_ID_ChDefine);

	if (pChDefGroup == NULL)
	{
		return FALSE;
	}

	CDataGroup *pChGroup =  NULL;
	POS pos = pChDefGroup->GetHeadPosition();
	CExBaseObject *pCurrObj = NULL;
	CString strEeType;
	double dCurrChACMaxValue = 0.0f,fActChACMaxValue = 0.0f;
	double dCurrChDCMaxValue = 0.0f,fActChDCMaxValue = 0.0f;

	while(pos)
	{
		pCurrObj = pChDefGroup->GetNext(pos);

   		if (pCurrObj->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pChGroup = (CDataGroup *)pCurrObj;

		if (pChGroup->m_strDataType != STT_ADJ_DATA_TYPE_HdCh)
		{
			continue;
		}

		strEeType = "";
		dCurrChACMaxValue = 0.0f;
		dCurrChDCMaxValue = 0.0f;
		pChGroup->GetDataValue(STT_ADJ_ID_EeType,strEeType);

		if ((strEeType == STT_ADJ_ID_EeType_Voltage)&&(bVol))
		{
		}
		else if ((strEeType == STT_ADJ_ID_EeType_Current)&&(!bVol))
		{
		}
		else
			continue;

		pChGroup->GetDataValue(_T("ChACMaxValue"),dCurrChACMaxValue);
		pChGroup->GetDataValue(_T("ChDCMaxValue"),dCurrChDCMaxValue);

		fActChACMaxValue = max(fActChACMaxValue,dCurrChACMaxValue);
		fActChDCMaxValue = max(fActChDCMaxValue,dCurrChDCMaxValue);
	}

	*pfAC_MaxMax = max(*pfAC_MaxMax,(float)fActChACMaxValue);
	*pfAC_MaxMin = min(*pfAC_MaxMin,(float)fActChACMaxValue);
	*pfDC_MaxMax = max(*pfDC_MaxMax,(float)fActChDCMaxValue);
	*pfDC_MaxMin = min(*pfDC_MaxMin,(float)fActChDCMaxValue);

// 	double dCurrValue_AC = *pfAC_MaxMin,dCurrValue_DC = *pfDC_MaxMin;
// 
// 	if (bVol)
// 	{
// 		pAttrGroup->GetDataValue(STT_ADJ_ID_VolChMaxValueAC,dCurrValue_AC);
// 		pAttrGroup->GetDataValue(STT_ADJ_ID_VolChMaxValueDC,dCurrValue_DC);
// 	} 
// 	else
// 	{
// 		pAttrGroup->GetDataValue(STT_ADJ_ID_CurChMaxValueAC,dCurrValue_AC);
// 		pAttrGroup->GetDataValue(STT_ADJ_ID_CurChMaxValueDC,dCurrValue_DC);
// 	}
// 
// 	*pfAC_MaxMax = max(*pfAC_MaxMax,(float)dCurrValue_AC);
// 	*pfAC_MaxMin = min(*pfAC_MaxMin,(float)dCurrValue_AC);
// 	*pfDC_MaxMax = max(*pfDC_MaxMax,(float)dCurrValue_DC);
// 	*pfDC_MaxMin = min(*pfDC_MaxMin,(float)dCurrValue_DC);
	return TRUE;
}

// BOOL Global_SetModuleMaxMinValue_ChDefine(CDataGroup *pChMapDefGroup,float *pfAC_MaxMax,float *pfAC_MaxMin,float *pfDC_MaxMax,float *pfDC_MaxMin,BOOL bVol)
// {
// 	if (pChMapDefGroup == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	CDataGroup *pChDefGroup = (CDataGroup*)pChMapDefGroup->FindByID(STT_ADJ_ID_ChDefine);
// 
// 	if (pChDefGroup == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	CDataGroup *pChGroup =  NULL;
// 	POS pos = pChDefGroup->GetHeadPosition();
// 	CExBaseObject *pCurrObj = NULL;
// 	CString strChID;
// 	double dCurrChACMaxValue = 0.0f,fActChACMaxValue = 0.0f;
// 	double dCurrChDCMaxValue = 0.0f,fActChDCMaxValue = 0.0f;
// 
// 	while(pos)
// 	{
// 		pCurrObj = pChDefGroup->GetNext(pos);
// 
// 		if (pCurrObj->GetClassID() != DTMCLASSID_CDATAGROUP)
// 		{
// 			continue;
// 		}
// 
// 		pChGroup = (CDataGroup *)pCurrObj;
// 
// 		if (pChGroup->m_strDataType != STT_ADJ_DATA_TYPE_HdCh)
// 		{
// 			continue;
// 		}
// 
// 		strChID = "";
// 		dCurrChACMaxValue = 0.0f;
// 		dCurrChDCMaxValue = 0.0f;
// 		pChGroup->GetDataValue(_T("ID"),strChID);
// 
// 		if ((strChID.Find(_T("U")) == 0)&&(bVol))
// 		{
// 		}
// 		else if ((strChID.Find(_T("I")) == 0)&&(!bVol))
// 		{
// 		}
// 		else
// 			continue;
// 
// 		pChGroup->GetDataValue(_T("ChACMaxValue"),dCurrChACMaxValue);
// 		pChGroup->GetDataValue(_T("ChDCMaxValue"),dCurrChDCMaxValue);
// 
//         fActChACMaxValue = max(fActChACMaxValue,dCurrChACMaxValue);
//         fActChDCMaxValue = max(fActChDCMaxValue,dCurrChDCMaxValue);
// 	}
// 
// 	*pfAC_MaxMax = max(*pfAC_MaxMax,(float)fActChACMaxValue);
// 	*pfAC_MaxMin = min(*pfAC_MaxMin,(float)fActChACMaxValue);
// 	*pfDC_MaxMax = max(*pfDC_MaxMax,(float)fActChDCMaxValue);
// 	*pfDC_MaxMin = min(*pfDC_MaxMin,(float)fActChDCMaxValue);
// 	return TRUE;
// }

BOOL Global_SetModuleMaxMinValueAC_ByHdGears(CDataGroup *pModuleAttrs,float *pfAC_MaxMax,float *pfAC_MaxMin)//单独提取到此函数中,暂时不用,从属性中AC最大值中获取结果
{
	CDataGroup *pHdGears = (CDataGroup*)pModuleAttrs->FindByID(_T("HdGears"));

	if (pHdGears == NULL)
	{
		return FALSE;
	}

	POS pos = pHdGears->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDataGroup *pGearGroup = NULL;
	CExBaseList *pCurObj = NULL;
	double dCurGearValue = 0.0f,dTmpValue = 0.0f,dCurChMaxDC = 10.0f;

	while(pos)
	{
		pCurObj = (CExBaseList*)pHdGears->GetNext(pos);

		if (pCurObj->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		pGearGroup = (CDataGroup *)pCurObj;

		if ((pGearGroup->m_strDataType != _T("HdGear")))
		{
			continue;
		}

		pDvmData = (CDvmData*)pCurObj->FindByID(_T("GearValue"));//zhouhj 交流最大值,取档位值,实际参数以档位值为参考

		if (pDvmData == NULL)
		{
			continue;
		}

		dTmpValue = CString_To_double(pDvmData->m_strValue);
		dCurGearValue = max(dCurGearValue,dTmpValue);
	}

	if (fabs(dCurGearValue)<=EPSINON)
	{
		return FALSE;
	}

	*pfAC_MaxMax = max(*pfAC_MaxMax,(float)dCurGearValue);
	*pfAC_MaxMin = min(*pfAC_MaxMin,(float)dCurGearValue);
	return TRUE;
}

BOOL Global_SetModuleMaxMinValue(CDataGroup *pModule,float *pfAC_MaxMax,float *pfAC_MaxMin,float *pfDC_MaxMax,float *pfDC_MaxMin,BOOL bVol)
{
	CDataGroup *pModuleAttrs = (CDataGroup*)pModule->FindByID(_T("ModuleAttrs"));

	if (pModuleAttrs == NULL)
	{
		return FALSE;
	}

	CString strModuleType;
	pModuleAttrs->GetDataValue(STT_ADJ_ID_ModuleType,strModuleType);

	if (strModuleType == STT_MODULE_TYPE_VOLT_CURRENT_ID)//交直流混合插件需要取通道内值
	{
		return Global_SetMaxMinValue_VolCurModule(pModuleAttrs,pfAC_MaxMax,pfAC_MaxMin,pfDC_MaxMax,pfDC_MaxMin,bVol);

// 		CDataGroup *pChMapDefGroup = (CDataGroup*)pModuleAttrs->FindByID(STT_ADJ_ID_ChMapDef);
// 		return Global_SetModuleMaxMinValue_ChDefine(pChMapDefGroup,pfAC_MaxMax,pfAC_MaxMin,pfDC_MaxMax,pfDC_MaxMin,bVol);
	}

	CExBaseList *pCurObj = NULL;
	double dCurGearValue = 0.0f,dTmpValue = 0.0f,dCurChMax = 5.0f;

	if (!pModuleAttrs->GetDataValue(_T("DefChDcMax"),dCurChMax))//zhouhj 2024.1.6 新增该属性用于实际开放给用户的最大值
	{
		//如果上述属性未找到，则为老版本底层,仍然采用原属性
		if (!pModuleAttrs->GetDataValue(_T("ChDcMax"),dCurChMax))
		{
			if (bVol)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前电压模块,缺少\"通道出直流最大值\"(ChDcMax)数据."));
			} 
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前电流模块,缺少\"通道出直流最大值\"(ChDcMax)数据."));
			}
		}
	}

    *pfDC_MaxMax = max(*pfDC_MaxMax,(float)dCurChMax);
    *pfDC_MaxMin = min(*pfDC_MaxMin,(float)dCurChMax);

//	Global_SetModuleMaxMinValueAC_ByHdGears(pModuleAttrs,pfAC_MaxMax,pfAC_MaxMin);

	dCurGearValue = 0.0f,dTmpValue = 0.0f,dCurChMax = 5.0f;

	if (!pModuleAttrs->GetDataValue(_T("DefChMax"),dCurChMax))//zhouhj 2024.1.6 新增该属性用于实际开放给用户的最大值
	{
		//如果上述属性未找到，则为老版本底层,仍然采用原属性
		if (!pModuleAttrs->GetDataValue(_T("ChMax"),dCurChMax))
		{
			if (bVol)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前电压模块,缺少\"通道出交流最大值\"(ChMax)数据."));
			} 
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前电流模块,缺少\"通道出交流最大值\"(ChMax)数据."));
			}
		}
	}

	*pfAC_MaxMax = max(*pfAC_MaxMax,(float)dCurChMax);
	*pfAC_MaxMin = min(*pfAC_MaxMin,(float)dCurChMax);
	return TRUE;

}

long Global_GetModulePos(CDataGroup *pModuleAttrs)
{
	CDvmData* pData = (CDvmData*)pModuleAttrs->FindByID(_T("ModulePos"));

	if (pData == NULL)
	{
		return -1;
	}

	return CString_To_long(pData->m_strValue);
}

void Global_GetMaxHarmCount(CDataGroup *pModuleAttrs)
{
	if (pModuleAttrs == NULL)
	{
		return;
	}

	CDvmData* pData = (CDvmData*)pModuleAttrs->FindByID(STT_ADJ_ID_HarmCount);

	if (pData == NULL)
	{
		return;
	}

	long nHarmCount = CString_To_long(pData->m_strValue);

	if (g_oLocalSysPara.m_nMaxHarmCount<nHarmCount)
	{
		g_oLocalSysPara.m_nMaxHarmCount = nHarmCount;
	}
}

long Global_GetModuleType(CDataGroup *pModuleAttrs)
{
	CDvmData* pData = (CDvmData*)pModuleAttrs->FindByID(STT_ADJ_ID_ModuleType);

	if (pData == NULL)
	{
		return -1;
	}

	CDataType *pFind = (CDataType*)g_pSttAdjSysParaDataTypes->FindByID(STT_ADJ_ID_ModuleType);

	if (pFind == NULL)
	{
		return -1;
	}

	CDataTypeValue *pValue = (CDataTypeValue*)pFind->FindByID(pData->m_strValue);

	if (pValue == NULL)
	{
		return -1;
	}

	return CString_To_long(pValue->m_strIndex);
}

BOOL Global_GetBinBoutExNum(CDataGroup *pModuleAttrs,int &nBinExNum,int &nBoutExNum)
{
	CString strTmp;
	CDvmData* pData = NULL;

	for (int nIndex = 0;nIndex<8;nIndex++)
	{
		strTmp.Format(_T("SwitchIn_%d"),nIndex);

		pData = (CDvmData*)pModuleAttrs->FindByID(strTmp);

		if (pData != NULL)
		{
			if (CString_To_long(pData->m_strValue) > 0)
			{
				nBinExNum += 8;
			} 
			else
			{
				nBoutExNum += 8;
			}
		}
	}

	return TRUE;
}
