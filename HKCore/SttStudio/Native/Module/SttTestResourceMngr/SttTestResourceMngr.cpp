#include "stdafx.h"
#include "SttTestResourceMngr.h"
#include "../Engine/SttPowerTestEngineBase.h"
#include "../SttSystemConfig/SttSystemConfig.h"
#include "../AdjustTool/SttAdjModule.h"
#include "../SttTest/Common/tmt_adjust_sys_parameter.h"
#include "../SttTest/Common/tmt_test_paras_head.h"
#include "../SttTestSysGlobalPara.h"
#include <algorithm>

//2023/8/4 wjs�޸ļ�����Func����
#ifdef _USE_SoftKeyBoard_	
#include "../UI/SoftKeyboard/SoftKeyBoard.h"
#endif


#ifdef NOT_USE_XLANGUAGE
#else
#include "../XLangResource_Native.h"                              

#endif

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

	//2023/8/23 wjs �������еĶ��ѹ/��������ֵ
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ�豸���Ϊ��."));
		return FALSE;
	}

	OpenSystemParasFile();

	if (!IsFileExist(strLocalDevicePath))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ�豸�ļ�(%s)������."),strLocalDevicePath.GetString());
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

//	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("[�������](%s)."),strModel.GetString());

	if (strModel.Find(_T("PNS331")) >= 0 || strModel.Find(_T("PDU100")) >= 0 || strModel.Find(_T("PTU200L")) >= 0)//zhouhj 2023.8.3 //chenling20240418ϵͳ�������ź����ø�ͨ����һ��ֵ�����ֵ���Ĭ��ֵ����Ϊ1:1
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
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ϵͳ�����ļ���%s��������."),strActPath.GetString());
		return FALSE;
	}

	CSttTestCmd oSttCmd;
	CSttMacro *pSttMacro = oSttCmd.GetSttMacro(TRUE,TRUE);

	CSttXmlSerializeTool oSttXmlSerializeTool;

	if (oSttXmlSerializeTool.CreateXmlSerializeRead(pSttMacro, strActPath) == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("����ϵͳ�����ļ�ʧ�ܡ�%s��"),strActPath.GetString());
		return FALSE;
	}

	pSttMacro->SetCreateMacroChild(TRUE);
	oSttXmlSerializeTool.SttXmlSerializeRead(pSttMacro);

	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetParas();

	//�������ɽṹ��
	stt_xml_serialize(&g_oSystemParas, pMacroParas);
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
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("IEC�����ļ�(%s)������."),strPath.GetString());
		return FALSE;
	}

#ifdef NOT_USE_TEST_RESOURCE_IECFG
	return TRUE;
#else
	if (m_oIecDatasMngr.OpenIecCfgFile(strPath))
	{
//		m_oIecDatasMngr.DelteteContrlBlocks_Unselected();  //zhouhj 20220305 �ڽ�����ʾ���·�����ʱ,����ֻ��ʾ��ֻ�·�ѡ��Ŀ��ƿ�,�������ļ�ʱ,����ֱ��ɾ��δѡ�Ŀ��ƿ�
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

	if (strPath.IsEmpty())//�����ǰѡ����������Ϊ�գ��򷵻�·��Ϊ�գ����ļ�������
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

	if (strPath.IsEmpty())//�����ǰѡ����������Ϊ�գ��򷵻�·��Ϊ�գ����ļ�������
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

	if (m_oDevSN_List.m_strName != strModel)//SN�����m_strName�洢��ǰ�򿪵��ͺţ�����ͺŲ�ƥ�䣬��Ҫ�򿪶�Ӧ�ͺ��µĸ������ļ�
	{
		CString strDevPath;
		strDevPath = GetDevFilePath_Model();

		if (!IsFileExist(strDevPath))//�����¼ȫ��SN���豸�ļ������ڣ��򷵻ؿ�
		{
			return _T("");
		}

		m_oDevSN_List.DeleteAll();
		m_oDevSN_List.OpenXmlFile(strDevPath,CDataMngrXmlRWKeys::g_pXmlKeys);
		m_oDevSN_List.m_strName = strModel;
	}

	if (m_oDevSN_List.m_strID.IsEmpty())//�����ǰѡ����������Ϊ�գ��򷵻�·��Ϊ�գ����ļ�������
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
	return;//��Linux����̶��ͺŷ�ʽ,��֧���л�
#endif
	BOOL bHasChanged = FALSE;

	if (m_oDevSN_List.m_strName != strModel)//SN�����m_strName�洢��ǰ�򿪵��ͺţ�����ͺŲ�ƥ�䣬��Ҫ�򿪶�Ӧ�ͺ��µĸ������ļ�
	{
		g_oSttSystemConfig.SetCurDevModel(strModel);//�޸�ϵͳ�����е�ǰ�ͺ�

		if (bSaveCfg)
		{
			g_oSttSystemConfig.SaveSystemConfig();//����ϵͳ����
		}

		CString strDevPath;
		strDevPath = GetDevFilePath_Model();
		m_oDevSN_List.DeleteAll();

		if (IsFileExist(strDevPath))//�����¼ȫ��SN���豸�ļ����ڣ���򿪸��ļ�
		{
			m_oDevSN_List.OpenXmlFile(strDevPath,CDataMngrXmlRWKeys::g_pXmlKeys);
		}

		m_oDevSN_List.m_strName = strModel;
		bHasChanged = TRUE;
	}

	if (bHasChanged||(m_oDevSN_List.m_strID != strSN))//�����ǰSN��ͬ����ѡ��ǰSNΪ��
	{
		bHasChanged = TRUE;
		CDvmData *pDvmData = (CDvmData*)m_oDevSN_List.FindByID(strSN);

		if (pDvmData == NULL)//�����ǰSN�����ڣ��򴴽����ͺŶ���
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
		m_oDevSN_List.SaveXmlFile(strSavePath,CDataMngrXmlRWKeys::g_pXmlKeys);//�����ͺŶ��������ļ�
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ȡģ������ʧ��(name=%s;id=%s;)"),pModule->m_strName.GetString(),pModule->m_strID.GetString());
			continue;
		}

		nModulePos = 0;
		nChCount = 0;
		oAdjModule.GetModulePos(nModulePos);
		oAdjModule.GetModuleChannelNum(nChCount);

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
 		{//����������Ҫ����
//			m_oDigital_Tags.AddModuleTag(nModulePos,nModuleType,nChCount);
		}
 		else if ((nModuleType == STT_MODULE_TYPE_FT3))
 		{//����������Ҫ����
//			m_oDigital_Tags.AddModuleTag(nModulePos,nModuleType,nChCount);
		}
 		else if ((nModuleType == STT_MODULE_TYPE_Stable2M))
 		{//����������Ҫ����
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
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("ģ��(name=%s;id=%s;),δӳ���ģ������(%ld)."),pModule->m_strName.GetString(),pModule->m_strID.GetString(),nModuleType);
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
}//��ȡ��ǰѡ���ͺ�װ�õ�SN

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
��һ����
1���ж�m_oCurrDevice�����������Ƿ�Ϊ�գ����Ϊ������ݵ�ǰװ���ͺţ���ȡ����Ӳ����Ϣ;
2�������ǰ�ͺ�Ϊ�գ��򽫵�ǰ�ͺų�ʼ��ΪPN466;
3�����ݵ�ǰ�ͺ�ȥ���ҡ�\DB\Device\�ͺ�\�ͺ�.xml���ļ��Ƿ���ڣ���������ڣ��򴴽�ȱʡ4U3I�����Դ��ͨ��ӳ���ļ���
4����������ļ����ڣ����ȡ�ļ���Ϣ���ҵ��ϴδ򿪵�װ�ñ�ţ�����װ�ñ�ţ���ȡ��Ӧ��Device�ļ���
5�����ȱʡ���Ϊ�գ����߶�ӦDevice�ļ������ڣ���ͬ�ϣ�����ȱʡ4U3I�����Դ��ͨ��ӳ���ļ���
�ڶ������������ǰͨ��ӳ���ļ����ڣ�
1����յ�ǰӳ����Դ����
2����ȡ����ͨ��ӳ���ļ���
3����֤��ǰӳ���ļ�������Ӳ��ͨ�����Ƿ���Device�ж����ҵ���ȥ����Ӳ����Դ��ӳ�������
*/
BOOL CSttTestResourceMngr::CreateChMaps()
{
	if (!HasLoadDevice())//���û�м���ͨ��ӳ���ļ�,��������ͨ��ӳ���ļ�
	{
		SelectDeviceFromLocalDB();
	}

	if (OpenChMapsFile(&m_oChMaps,m_pTestResouce)&&(HasMapHdResource()))//��ͨ��ӳ���ļ�
	{
		return TRUE;
	}

	if (!CreateDefaultChMapsByDevice(&m_oChMaps,g_oSystemParas.m_nIecFormat,g_oSystemParas.m_nHasDigital))//�����ͨ��ӳ���ļ�ʧ��,�����Ӳ����Ϣ����ȱʡͨ��ӳ���ļ�
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
	nGroupIndex++;//��Ŵ�1��ʼ

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
	CreateDefaultChMapsByDevice_Analog(pCurChMaps);

	if (bHasDigital)
	{
		CreateDefaultChMapsByDevice_Digital(pCurChMaps,nIecFormat);
	}

	if (bHasWeek)
	{
		CreateDefaultChMapsByDevice_Weak(pCurChMaps);
	}

	if(m_pTestResouce ==NULL) //add wangtao 20240509 ��������ﲻ��ͨ��ӳ�䣬ָ��Ϊ��
	{
		if (pCurChMaps->GetCount() <= 0)//zhouhj 2024.5.22 ��ͨ��ӳ��Ϊ��ʱ,����Ϊ��
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

void CSttTestResourceMngr::UpdateChNames_UzIz(CSttChMaps *pCurChMaps,CSttTestResourceBase *pTestResouce)
{
	if (pCurChMaps == NULL)
	{
		return;
	}
/*����ȱʡֵʱ��
	1�����ֻ��4ͨ������Ӧ�����һ��ͨ�����Ƹ�ΪU0\I0;
	2�������Ϊ4ͨ������Ӧ�ĵ�4ͨ�����ƣ���Ӧ��ΪU0\I0
	*/
	long nVolChNum = pCurChMaps->GetChNum(_T("U"));
	long nCurrChNum = pCurChMaps->GetChNum(_T("I"));
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

	//����Դ��ȡ�ÿ�������������
// 	CDataGroup* pBoutGroup = m_oCurrDevice.GetBoutTrunOnValueDef();//zhouhj 20220401 ���忪�뿪��������״̬��,ͳһ��һ��λ�û�ȡ
// 
// 	if (pBoutGroup)
// 	{
// 		g_oLocalSysPara.m_nCHBinOutNum = pBoutGroup->GetCount();
// 		if (g_oLocalSysPara.m_nCHBinOutNum == 0)
// 		{
// 			g_oLocalSysPara.m_nCHBinOutNum = BINOUT_NUM;	//8��
// 		}
// 	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	g_oLocalSysPara.InitMaxMinVolCurValue();
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	CExBaseList oCurModuleListRef;
	long nAnalogModuleNum = 0,nDigitalModuleNum = 0,nWeakModuleNum = 0,nExBinBoutModuleNum = 0;
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_VOLT);//��ȡȫ����ѹģ��
	m_oCurrDevice.GetAllModules(&oCurModuleListRef,STT_MODULE_TYPE_VOLT_CURRENT);//��ȡȫ����ѹģ��
	nAnalogModuleNum = oCurModuleListRef.GetCount();
	CDataGroup *pModule = NULL;
	CDataGroup *pModuleAttrs = NULL;
	CDvmData *pData = NULL;
	//	long nModulePower = -1;
	double dTmp = 0;
	POS pos = oCurModuleListRef.GetHeadPosition();

	while (pos != NULL)//�ڸ�ѭ�������õ�ѹģ�����ֵ,��Сֵ
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
	pGearSetCurModules->m_nCurModuleNum = oCurModuleListRef.GetCount();//���õ���ģ��������
	nAnalogModuleNum += pGearSetCurModules->m_nCurModuleNum;

	tmt_CurModuleGear *pCurGear = NULL;
	long nCurModuleIndex = -1;
	CString strChMergeMode;
	pos = oCurModuleListRef.GetHeadPosition();

	while (pos != NULL)//�ڸ�ѭ�������õ���ģ�����ֵ,��Сֵ,����ģ�鹦�ʵ�λ��
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

		if (stt_GetDataValueByID(pModuleAttrs,STT_ADJ_ID_ChMergeMode,strChMergeMode))//zhouhj 20211006 ���ͨ���ϲ�ģʽ���Բ��ҳɹ�
		{
			if (strChMergeMode == _T("ChMerge_3Ch"))
			{
				if ((pCurGear->m_nMergeCurTerminal != STT_LARGE_CURRENT_MERGE_THREE_CH))//�ڴ�����������,��Ϊ�ϲ�Ϊ3ͨ��ʱm�̶���ʼ��Ϊ���ϲ�
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

				if (pCurGear->m_nLargeCurOutTerm == STT_LARGE_CUR_OUT_NULL)//�����ǰѡ���Ϊ��,����Ҫ������г�ʼ��
				{
					pCurGear->m_nLargeCurOutTerm = STT_LARGE_CUR_OUT_TERM_A;
				}

				continue;
			}
		}

		pCurGear->m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_NOT_SUPPORT;//����ϲ�ͨ�����Բ���ʧ��,���߷Ǻϲ�3���ϲ���ͨ��,��Ĭ������Ϊ��֧�ֺϲ�
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
	UpdateLC_ST_FibersNum();//����Ӳ����Ϣ���ǵĹ����������IEC���ý�����ʾ�Ĺ������
	ValidIecParasSetSel();

	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 0)&&(g_oSystemParas.m_nHasWeek == 0))
	{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ�������ѡ��Ϊ��,����ѡ���������."));
	}

// 	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�������ѹ���ֵ(%fV),������������ֵ(%fA)."),g_oLocalSysPara.m_fAC_VolMax,g_oLocalSysPara.m_fAC_CurMax);
// 	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("���ֱ����ѹ���ֵ(%fV),���ֱ���������ֵ(%fA)."),g_oLocalSysPara.m_fDC_VolMax,g_oLocalSysPara.m_fDC_CurMax);
}

void CSttTestResourceMngr::UpdateLC_ST_FibersNum()
{
	long nGFiberLC_num = 1;//chenling 2024.5.22 ��ʼ��Ϊ0
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

    //add wangtao 20240509 ���ڶ�������������������Ӧ֧�ֶ��飬��Ӧ����һ�����ֲ������ ����8/16/16һ��
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

	while (pos != NULL)//�ڸ�ѭ�������õ���ģ�����ֵ,��Сֵ,����ģ�鹦�ʵ�λ��
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

	if (m_nTotalFiberNum_LC>0)
	{
		g_oLocalSysPara.m_nTotalLC_Num = m_nTotalFiberNum_LC; 
	}

	if ((m_nTotalFiberNum_STSend>0)&&(CCfgDataMngrConstGlobal::GetAppPortFT3Num_ST() != m_nTotalFiberNum_STSend))
	{
		CCfgDataMngrConstGlobal::UpdataAppPortDataType_FT3Num(m_nTotalFiberNum_STSend);
	}

	if (m_nTotalFiberNum_STSend>0)
	{
		g_oLocalSysPara.m_nTotalSTSend_Num = m_nTotalFiberNum_STSend; 
	}

	if ((g_oLocalSysPara.m_nTotalSTRecv_Num/*nTotalFiberNum_STRecv*/>0)&&
		(CCfgDataMngrConstGlobal::GetAppPortFT3InNum_ST() != g_oLocalSysPara.m_nTotalSTRecv_Num/*nTotalFiberNum_STRecv*/))
	{
		CCfgDataMngrConstGlobal::UpdataAppPortDataType_FT3InNum(g_oLocalSysPara.m_nTotalSTRecv_Num/*nTotalFiberNum_STRecv*/);
	}


// 	if (bHasFiberNumSTRecv_Paras)
// 	{
// 		g_oLocalSysPara.m_nTotalSTRecv_Num = nTotalFiberNum_STRecv; 
// 	}

	g_oLocalSysPara.m_nLC_GFiberNum = nGFiberLC_num;

#ifdef NOT_USE_XLANGUAGE
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ǰ�豸������LC���%ld��,ST���Ϳ�%ld��,ST���տ�%ld��,ǧ�׹��%ld��."),m_nTotalFiberNum_LC,m_nTotalFiberNum_STSend,g_oLocalSysPara.m_nTotalSTRecv_Num/*nTotalFiberNum_STRecv*/,nGFiberLC_num);
#else
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("��ǰ�豸������LC���%ld��,ST���Ϳ�%ld��,ST���տ�%ld��,ǧ�׹��%ld��.")*/g_sLangTxt_Native_LCSTSendportSTGigabit.GetString()
		,m_nTotalFiberNum_LC,m_nTotalFiberNum_STSend,g_oLocalSysPara.m_nTotalSTRecv_Num/*nTotalFiberNum_STRecv*/,nGFiberLC_num);                      

#endif


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
	m_oChMaps.GetMaxValue_WeekRates(dMaxVol,dMaxCur);

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

	//2023/8/23 -wjs ��ʼ���ٷֱȼ���
	CDvmData *pDvmData = NULL;
	//ȡ��NormalVolFunc��ֵ
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

// 	CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("[�������],[%ld],[%ld],[%ld],[%ld],[%ld]"),m_oKeyBoardFuncGroup.GetCount(),
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
	//ȡ��NormalVolFunc��ֵ
	pDvmData = (CDvmData*)m_oKeyBoardFuncGroup.FindByID(STT_SOFTKEYBOARD_VOL_NORMAL);

	if (pDvmData != NULL)
	{
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC1_VALUE, g_oKeyBoardBtnDescs.m_strVolFunc1);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC2_VALUE, g_oKeyBoardBtnDescs.m_strVolFunc2);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FUNC3_VALUE, g_oKeyBoardBtnDescs.m_strVolFunc3);
		pDvmData->GetValueByID(STT_SOFTKEYBOARD_FuncMinus_VALUE, g_oKeyBoardBtnDescs.m_strVolMinus);
	}

	//ȡ��NormalCur��ֵ
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
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("�л������źż���."));
	CDvmData *pDvmData = NULL;
	//ȡ��NormalVolFunc��ֵ
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
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("���źż��̵�ѹͨ��ӳ������(%s)����ʧ��."),STT_SOFTKEYBOARD_VOL_WEAK);
	}
		
	//ȡ��NormalCur��ֵ
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
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("���źż��̵���ͨ��ӳ������(%s)����ʧ��."),STT_SOFTKEYBOARD_CUR_WEAK);
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

	if ((g_oSystemParas.m_nHasAnalog == 0)&&(g_oSystemParas.m_nHasDigital == 1)&&(g_oSystemParas.m_nHasWeek == 0))//���ֻ�������ź����,�����ѹ���������������
	{
		if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_61850_92)
		{
			if ((pCIecCfgSysParas->m_nPrimParas == 1)
				|| (pCIecCfgSysParas->m_nPrimParas == 0))
			{
				g_oLocalSysPara.m_fAC_VolMax = 1200000;
				g_oLocalSysPara.m_fAC_VolMin = 1200000;
				g_oLocalSysPara.m_fAC_CurMax = 120000;
				g_oLocalSysPara.m_fAC_CurMin = 120000;

			g_oLocalSysPara.m_fDC_VolMax = 1000000;
			g_oLocalSysPara.m_fDC_VolMin = 1000000;
			g_oLocalSysPara.m_fDC_CurMax = 10000;
			g_oLocalSysPara.m_fDC_CurMin = 10000;
			}
		}
		else if (g_oSystemParas.m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
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
// 		if (pCIecCfgSysParas->m_nPrimParas == 1)
// 		{
// 			g_oLocalSysPara.m_fAC_VolMax = 1000000;
// 			g_oLocalSysPara.m_fAC_VolMin = 1000000;
// 			g_oLocalSysPara.m_fDC_VolMax = 1000000;
// 			g_oLocalSysPara.m_fDC_VolMin = 1000000;
// 
// 			g_oLocalSysPara.m_fAC_CurMax = 10000;
// 			g_oLocalSysPara.m_fAC_CurMin = 10000;
// 			g_oLocalSysPara.m_fDC_CurMax = 10000;
// 			g_oLocalSysPara.m_fDC_CurMin = 10000;
// 		} 
// 		else if (g_oSystemParas.m_nIecFormat == 2)
// 		{
// 			g_oLocalSysPara.m_fAC_VolMax = 100000;
// 			g_oLocalSysPara.m_fAC_VolMin = 100000;
// 			g_oLocalSysPara.m_fDC_VolMax = 100000;
// 			g_oLocalSysPara.m_fDC_VolMin = 100000;
// 
// 			g_oLocalSysPara.m_fAC_CurMax = 10000;
// 			g_oLocalSysPara.m_fAC_CurMin = 10000;
// 			g_oLocalSysPara.m_fDC_CurMax = 10000;
// 			g_oLocalSysPara.m_fDC_CurMin = 10000;
// 		}
// 		else
// 		{
// 			g_oLocalSysPara.m_fAC_VolMax = 1200;
// 			g_oLocalSysPara.m_fAC_VolMin = 1200;
// 			g_oLocalSysPara.m_fDC_VolMax = 1200;
// 			g_oLocalSysPara.m_fDC_VolMin = 1200;
// 
// 			g_oLocalSysPara.m_fAC_CurMax = 200;
// 			g_oLocalSysPara.m_fAC_CurMin = 200;
// 			g_oLocalSysPara.m_fDC_CurMax = 200;
// 			g_oLocalSysPara.m_fDC_CurMin = 200;
// 		}
	}
	else if (pCIecCfgSysParas->m_nPrimParas == 1)//ֻ���ڴ�����������������,���ܽ�������������Ϊһ��ֵ
	{
		pCIecCfgSysParas->m_nPrimParas = 0;
		SaveDefaultIec61850Config();//Iec61850�����޸ĺ󱣴�
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��������ǿ��ѡ��Ϊ����ֵ,ֻ���ڴ�����������������,���ܽ���������Ϊһ��ֵ."));
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

	if (m_pTestResouce != NULL)
	{
		strSavePath += m_pTestResouce->GetChMapFileName();
	}
	else//�����ǰ��ԴΪ��,��ʹ��ȱʡͨ��ӳ�䱣��
	{
		strSavePath += _T("ChMapConfig.sync");
	}

	return m_oChMaps.SaveChMapsFile(strSavePath);
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

	while(pos)//����ģ������ѹģ��ȱʡͨ��ӳ��
	{
		pSttModuleTag = (CSttModuleTag *)m_oAnalogU_Tags.GetNext(pos);

		for (int nIndex = 1;nIndex <= pSttModuleTag->m_nChCountU;nIndex++)
		{
			if (nVolChIndex>MAX_VOLTAGE_COUNT)//�����ѹ�����Դͨ�����������������,������ѭ��,��2��Ӳ����Դ,ӳ�䵽ͬһ�������Դ
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

	while(pos)//����ģ��������ģ��ȱʡͨ��ӳ��
	{
		pSttModuleTag = (CSttModuleTag *)m_oAnalogI_Tags.GetNext(pos);

		for (int nIndex = 1;nIndex <= pSttModuleTag->m_nChCountI;nIndex++)
		{
			if (nCurChIndex>MAX_CURRENT_COUNT)//������������Դͨ�����������������,������ѭ��,��2��Ӳ����Դ,ӳ�䵽ͬһ�������Դ
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

	if (nVolModuleIndex>nCurModuleIndex)//ȡ������ѹ����ģ���еĽϴ����һ��index
	{
		nVolCurModuleIndex = nVolModuleIndex;
	} 
	else
	{
		nVolCurModuleIndex = nCurModuleIndex;
	}

 	pos = m_oAnalogUI_Tags.GetHeadPosition();
 
 	while(pos)//����ģ��������ģ��ȱʡͨ��ӳ��
 	{
 		pSttModuleTag = (CSttModuleTag *)m_oAnalogUI_Tags.GetNext(pos);

		for (int nIndex = 1;nIndex <= pSttModuleTag->m_nChCountU;nIndex++)
		{
			if (nVolChIndex>MAX_VOLTAGE_COUNT)//�����ѹ�����Դͨ�����������������,������ѭ��,��2��Ӳ����Դ,ӳ�䵽ͬһ�������Դ
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
 			if (nCurChIndex>MAX_CURRENT_COUNT)//������������Դͨ�����������������,������ѭ��,��2��Ӳ����Դ,ӳ�䵽ͬһ�������Դ
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

	while(pos)//�������ź�ģ��ȱʡ��ѹͨ��ӳ��
	{
		pSttModuleTag = (CSttModuleTag *)m_oWeak_Tags.GetNext(pos);

		for (int nIndex = 1;nIndex <= pSttModuleTag->m_nChCountU_Week;nIndex++)
		{
			if (nChIndex>MAX_VOLTAGE_COUNT)//�����ѹ�����Դͨ�����������������,������ѭ��,��2��Ӳ����Դ,ӳ�䵽ͬһ�������Դ
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

	while(pos)//�������ź�ģ��ȱʡ����ͨ��ӳ��
	{
		pSttModuleTag = (CSttModuleTag *)m_oWeak_Tags.GetNext(pos);

		for (int nIndex = 1;nIndex <= pSttModuleTag->m_nChCountI_Week;nIndex++)
		{
			if (nChIndex>MAX_CURRENT_COUNT)//�����ѹ�����Դͨ�����������������,������ѭ��,��2��Ӳ����Դ,ӳ�䵽ͬһ�������Դ
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

//����Ӳ����Դͨ���Ƿ�Ϊ�ϲ�ͨ��,����Ǻϲ�ͨ��,�����Ǻϲ�ͨ���ĵ�һ��ͨ��,��ʣ��ϲ�ͨ������,�������Ӧϵ��
//������Ǻϲ�ͨ���ĵ�һ��ͨ��,��ɾ����ǰӲ��ͨ��
//���ڷǺϲ�ͨ��,��ϵ���̶�����Ϊ1
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
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ����ģ����(%ld)���ڵ���ģ��������(%ld)."),nModuleIndex,pGearSetCurModules->m_nCurModuleNum);
			return FALSE;
		}

		if (pGearSetCurModules->m_oCurModuleGear[nModuleIndex-1].m_nMergeCurTerminal == STT_LARGE_CURRENT_MERGE_ONE_CH)
		{
			if (nChIndex == 1)//�����ж��Ƿ�Ϊ��һ��ͨ��,����ǵ�һ��ͨ��,��Ҫ������ͨ��Ҳ�ϲ�����
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
			else if (!pHdChs->HasHdCh(pHdCh->m_strID.GetAt(0),nModuleIndex,1))//������ǵ�һ��ͨ�����жϸ�Ӳ��ͨ���������Ƿ������һ��ͨ��,���������,����Ҫ����Ӳ��ͨ��ɾ��
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
 			else if (!pHdChs->HasHdCh(pHdCh->m_strID.GetAt(0),nModuleIndex,nChIndex-3))//������ǵ�һ��ͨ�����жϸ�Ӳ��ͨ���������Ƿ������һ��ͨ��,���������,����Ҫ����Ӳ��ͨ��ɾ��
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

	for (int nIndex = 0;nIndex<g_oSystemParas.m_oGearSetCurModules.m_nCurModuleNum;nIndex++)
	{
		if ((pCurModuleGear[nIndex].m_nMergeCurTerminal == STT_LARGE_CURRENT_MERGE_THREE_CH)&&(nCoef<2))
		{
			if (m_oChMaps.HasAnalogCurrModuleHdCh(nIndex+1))
			{
				nCoef = 2;
				bHas = TRUE;
			}
		}
		else if (pCurModuleGear[nIndex].m_nMergeCurTerminal == STT_LARGE_CURRENT_MERGE_ONE_CH)
		{
			if (m_oChMaps.HasAnalogCurrModuleHdCh(nIndex+1))
			{
				nCoef = 6;
				bHas = TRUE;
			}
		}
	}

	return bHas;
}

/*
1������ȫ��ͨ��ӳ���Ӳ����Դ������ʵ��Ӳ����Դ������в��ң����δ���ҵ�������ӳ��ɾ����
*/
BOOL CSttTestResourceMngr::ValidHardRsChMaps()
{
	if (!HasLoadDevice())
	{
		if (!SelectDeviceFromLocalDB())//����򿪱���Device�ļ�ʧ�ܣ�����Ҫ����ȱʡ�����Դ
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
	BOOL bVolCurModule = FALSE;//�Ƿ�Ϊ��ѹ�������ģ��
	POS pos_map = m_oChMaps.GetHeadPosition();

	while(pos_map)
	{
		pChMap = (CSttChMap*)m_oChMaps.GetNext(pos_map);

		pos_hd_chs = pChMap->GetHeadPosition();

		while(pos_hd_chs)
		{
			pHdChs = (CSttHdChs *)pChMap->GetNext(pos_hd_chs);

			if (pHdChs->m_strID == STT_MODULETYPE_ID_DIGITAL)//�����źŲ���Ҫ��֤Ӳ����Դ
			{
				continue;
			}

			pos_hd_ch = pHdChs->GetHeadPosition();

			while(pos_hd_ch)
			{
				pHdCh = (CSttHdCh *)pHdChs->GetNext(pos_hd_ch);

				if (!ParseHdRsID(pHdCh->m_strID,nChType,nModuleType,nModuleIndex,nChIndex))//���Ӳ����Դͨ��ID����ʧ�ܣ���ɾ����Ӳ����Դӳ��
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

				pModuleTag = pCurModuleTags->GetAtIndex(nModuleIndex-1);//nModuleIndex��1��ʼ��ţ���Ҫ�ȼ�ȥ1

				if (pModuleTag != NULL)//����ҵ���ģ��,����к�����֤
				{
				}
				else if (m_oAnalogUI_Tags.GetCount() == 0)//���û�е�ѹ�������ģ��,���ҵ�ǰģ��Ҳδ�ҵ�,��ǰӲ����Դ������
				{
					pHdChs->Delete(pHdCh);
					continue;
				}
				else if (m_oAnalogUI_Tags.GetCount() > 0)//������ڵ�ѹ�������ģ��
				{
					if (m_oAnalogU_Tags.GetCount()>m_oAnalogI_Tags.GetCount())
					{
						nModuleIndex -= m_oAnalogU_Tags.GetCount();
					} 
					else
					{
						nModuleIndex -= m_oAnalogI_Tags.GetCount();
					}

					pModuleTag = m_oAnalogUI_Tags.GetAtIndex(nModuleIndex-1);//nModuleIndex��1��ʼ��ţ���Ҫ�ȼ�ȥ1

					if (pModuleTag == NULL)
					{
						pHdChs->Delete(pHdCh);
						continue;
					}

					bVolCurModule = TRUE;
				}

				if ((nModuleType == STT_MODULE_TYPE_WEEK_EX)/*||(nModuleType == STT_MODULE_TYPE_WEEK_MAIN)*/)//���Ϊ���ź�ͨ��
				{
					if ((pModuleTag->m_nChCountU_Week+pModuleTag->m_nChCountI_Week)<nChIndex)
					{
						pHdChs->Delete(pHdCh);
					}
				}
				else if ((nModuleType == STT_MODULE_TYPE_ADMU))//���ΪADMU(���ź�ͨ��)
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
1�������ж�Device�����Ƿ�Ϊ�գ����Ϊ�գ�����Ҫ�����Դ��֤��ֻ���жϵ�ǰ�����Դ�Ƿ�Ϊ�գ����Ϊ�գ�����ȱʡ4U3I�����Դ��
2)�жϵ�ǰͨ��ӳ���ļ��Ƿ�Ϊ�գ����Ϊ�գ�����Device������ȱʡͨ��ӳ���ļ���
3������ͨ��ӳ���ļ������������Դ�����뵱ǰ���ģʽ���жϸ�ͨ���Ƿ���������Ӳ����Դ����������ڣ���ɾ���������Դ��
4��ֻ�������ݵ�ǰ���ģʽ���ڵ������Դ���������������Դ����������
*/
void CSttTestResourceMngr::CreateSoftRsCh()
{
	ASSERT(m_pTestResouce);
	m_pTestResouce->ClearAll();

	if (!HasLoadDevice())//���
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
		else//����Ȳ��ǵ�ѹͨ����Ҳ���ǵ���ͨ�������ͨ��������ͨ���������ϲ�Ӧ�ô��ڣ�ɾ����ͨ��
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
1)���ݵ�ǰ�����Դӳ��m_oChMaps����ʵʱ����ͨ��CmacroChannel��
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
��װ���ͺ�ѡ��ı����Ҫ�������²�����
1��CreateChMaps���´������ӳ���ļ���
2��ValidHardRsChMaps��
3��CreateSoftRsCh��
4��CreateRtDataMngr��
��������ȡDevice��
1������ͺ��뵱ǰ��һ�£������ͺŲ�һ�´���
2������ͺ�һ�£�����m_oCurrDevice��Ա������֤Ӳ����Դ�Ƿ�һ�£���װ�ñ���Ƿ�һ�£���
3�������һ�£����Զ�ȡ��Ϊ׼������m_oCurrDevice����
4��ValidHardRsChMaps��
5��CreateSoftRsCh��
6��CreateRtDataMngr��
���޸��������Դӳ���ϵ��
1��CreateSoftRsCh��
2��CreateRtDataMngr��
���޸���ͨ��ӳ�������
1��ֻ��ͨ��ӳ���ļ��еı�����ֵ�������Դm_strName
��ͬһ���ͺţ��л���װ�ñ�ź�
1������m_oCurrDevice��Ա������֤Ӳ����Դ�Ƿ�һ�£�
3�������һ�£����Զ�ȡ��Ϊ׼������m_oCurrDevice����
4��ValidHardRsChMaps��
5��CreateSoftRsCh��
6��CreateRtDataMngr��
*/

//zhouhj 2023.11.13 ԭ�����ӵ�����ѹ�������ֵ��ʽ���ָ�Ϊ��λ������ȫ��ͨ�����Ҷ�Ӧ���ֵ
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

BOOL Global_SetModuleMaxMinValueAC_ByHdGears(CDataGroup *pModuleAttrs,float *pfAC_MaxMax,float *pfAC_MaxMin)//������ȡ���˺�����,��ʱ����,��������AC���ֵ�л�ȡ���
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

		pDvmData = (CDvmData*)pCurObj->FindByID(_T("GearValue"));//zhouhj �������ֵ,ȡ��λֵ,ʵ�ʲ����Ե�λֵΪ�ο�

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

	if (strModuleType == STT_MODULE_TYPE_VOLT_CURRENT_ID)//��ֱ����ϲ����Ҫȡͨ����ֵ
	{
		return Global_SetMaxMinValue_VolCurModule(pModuleAttrs,pfAC_MaxMax,pfAC_MaxMin,pfDC_MaxMax,pfDC_MaxMin,bVol);

// 		CDataGroup *pChMapDefGroup = (CDataGroup*)pModuleAttrs->FindByID(STT_ADJ_ID_ChMapDef);
// 		return Global_SetModuleMaxMinValue_ChDefine(pChMapDefGroup,pfAC_MaxMax,pfAC_MaxMin,pfDC_MaxMax,pfDC_MaxMin,bVol);
	}

	CExBaseList *pCurObj = NULL;
	double dCurGearValue = 0.0f,dTmpValue = 0.0f,dCurChMax = 5.0f;

	if (!pModuleAttrs->GetDataValue(_T("DefChDcMax"),dCurChMax))//zhouhj 2024.1.6 ��������������ʵ�ʿ��Ÿ��û������ֵ
	{
		//�����������δ�ҵ�����Ϊ�ϰ汾�ײ�,��Ȼ����ԭ����
		if (!pModuleAttrs->GetDataValue(_T("ChDcMax"),dCurChMax))
		{
			if (bVol)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ��ѹģ��,ȱ��\"ͨ����ֱ�����ֵ\"(ChDcMax)����."));
			} 
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ����ģ��,ȱ��\"ͨ����ֱ�����ֵ\"(ChDcMax)����."));
			}
		}
	}

    *pfDC_MaxMax = max(*pfDC_MaxMax,(float)dCurChMax);
    *pfDC_MaxMin = min(*pfDC_MaxMin,(float)dCurChMax);

//	Global_SetModuleMaxMinValueAC_ByHdGears(pModuleAttrs,pfAC_MaxMax,pfAC_MaxMin);

	dCurGearValue = 0.0f,dTmpValue = 0.0f,dCurChMax = 5.0f;

	if (!pModuleAttrs->GetDataValue(_T("DefChMax"),dCurChMax))//zhouhj 2024.1.6 ��������������ʵ�ʿ��Ÿ��û������ֵ
	{
		//�����������δ�ҵ�����Ϊ�ϰ汾�ײ�,��Ȼ����ԭ����
		if (!pModuleAttrs->GetDataValue(_T("ChMax"),dCurChMax))
		{
			if (bVol)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ��ѹģ��,ȱ��\"ͨ�����������ֵ\"(ChMax)����."));
			} 
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ����ģ��,ȱ��\"ͨ�����������ֵ\"(ChMax)����."));
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
