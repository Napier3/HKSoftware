#include "stdafx.h"
#include"SttChMapsConfig.h"

#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/Module/PowerCtrl/SttPowerCtrlCom.h"
#endif

CString CSttChMapsConfig::m_strMacroName = "通道映射";
CString CSttChMapsConfig::m_strMacroID = STT_MACRO_ID_ChMapsConfig;
CString CSttChMapsConfig::m_strFilePostFix = "chmap";
CString CSttChMapsConfig::m_strMacroVer ="1.0";

#include "tmt_adjust_sys_parameter.h"

CSttChMapsConfig::CSttChMapsConfig() : CSttTestBase()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttChMapsConfig::Init()
{
	/*TMT_ADJUST_ONE::init();*/
}

long CSttChMapsConfig::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	return 0;
}

CSttChMapsConfig::~CSttChMapsConfig(void)
{
}

void CSttChMapsConfig::AfterSetParameter()
{
}

double CSttChMapsConfig::GetTestTimeLong()
{
	float fTime = TIME_ONLINE_DELAY;

	//	fTime = m_oHarmParas.m_fOutPutTime;
	//	fTime += TIME_ONLINE_DELAY;

	return fTime;
}

long CSttChMapsConfig::CalReport(UINT nState)
{

	return 0;
}

long CSttChMapsConfig::SetParameter(DWORD dwState)
{
	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttChMapsConfig::SetParameter >>>>>>");
	return 0;
}

void CSttChMapsConfig::StartTest()
{
	CSttTestBase::StartTest();

	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttChMapsConfig::StartTest >>>>>>");
	ReturnTestStateEvent_TestStart(0, 0, FALSE);
#ifdef _PSX_QT_LINUX_
	Sleep(50);
#endif
	//时间标识置为0,自动测试处理此消息
	ReturnTestStateEvent_TestFinish(0, 0, FALSE);
}


void CSttChMapsConfig::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	CXmlRWElementBase *pElement = pXmlSerialize->GetElement();
	CXmlRWElementBase *pChildElement = (CXmlRWElementBase*)pElement->GetChildNode(_T("ch-maps"));//需要先查找到子节点
	//	CXmlRWElementBase *pChildElement = pElement->GetChildNode(_T("group"));
	ASSERT(pChildElement);
	
	CSttChMaps oSttChMaps;
	oSttChMaps.XmlRead(*pChildElement, CSttCmdDefineXmlRWKeys::g_pXmlKeys);
#ifdef _PSX_QT_LINUX_
	ChMapsConfig(oSttChMaps);
#endif
}

void ChMapConfig_Module_Module(CSttChMaps &oChMaps, PSTT_MODULE pModule)
{
	PST_MODULE_ATTR pModuleAttr = &pModule->m_oModuleAttr;
	long nChCount = pModuleAttr->m_nChannelNum;
	if(pModuleAttr->m_nModuleType==STT_MODULE_TYPE_DIGITAL_0G8M
			||pModuleAttr->m_nModuleType==STT_MODULE_TYPE_DIGITAL_2G6M
			||pModuleAttr->m_nModuleType==STT_MODULE_TYPE_DIGITAL_4G4M
			||pModuleAttr->m_nModuleType==STT_MODULE_TYPE_FT3)
	{
		nChCount = DIGITAL_CHANNEL_MAX;
	}
	
	//通道类型：analog、digital、weak、...
	CString strChType;
	strChType = stt_get_module_id_by_type(pModuleAttr->m_nModuleType);
	long nIndex = 0;

	//通道定义对象
	PSTT_MODULE_CH_DEFS pChDefs = &pModuleAttr->m_oChDefMap.m_oChDefs;
	CString strHdChID;
	CSttChMap *pSttChMap = NULL;
	float fHdChCoef = 1.0f;

	for (nIndex=0; nIndex<nChCount; nIndex++)
	{//遍历每个通道
		//硬件通道ID
		strHdChID = pChDefs->m_oChDef[nIndex].m_pszChId;
		fHdChCoef = 1.0f;
		pSttChMap = oChMaps.FindByHdCh(strChType, strHdChID,fHdChCoef); //在映射表中，查找本通道
		
		if (pSttChMap == NULL)
		{//当前硬件通道没有映射
			pChDefs->m_oChDef[nIndex].m_nChRsIndex = -1;
		}
		else
		{
			pChDefs->m_oChDef[nIndex].m_nChRsIndex = pSttChMap->m_nRsIndex-1;
			pModule->m_fChTmtCoef[nIndex] = fHdChCoef;//zhouhj 20210603 增加对系数的赋值

            if(pSttChMap->m_strID.Left(1)==_T("U"))
            {
                if(pSttChMap->m_nRsIndex > g_nRtDataVoltCnt)
                    g_nRtDataVoltCnt = pSttChMap->m_nRsIndex;
            }
            else
            {
                if(pSttChMap->m_nRsIndex > g_nRtDataCurrCnt)
                    g_nRtDataCurrCnt = pSttChMap->m_nRsIndex;
            }

            if(pSttChMap->m_strID.Left(1)==_T("U"))
                pChDefs->m_oChDef[nIndex].m_nEeType=STT_CH_EETYPE_VOLTAGE;
            else
                pChDefs->m_oChDef[nIndex].m_nEeType=STT_CH_EETYPE_CURRENT;

		}
	}

	if(pModuleAttr->m_nModuleType == STT_MODULE_TYPE_ADMU)
	{
		for (nIndex=0; nIndex<DIGITAL_CHANNEL_MAX; nIndex++)
		{//遍历每个通道
			//硬件通道ID
			strHdChID = pChDefs->m_oChDef[nIndex].m_pszChIdEx;
			pSttChMap = oChMaps.FindByHdCh(STT_MODULETYPE_ID_DIGITAL, strHdChID,fHdChCoef); //在映射表中，查找本通道

			if (pSttChMap == NULL)
			{//当前硬件通道没有映射
				pChDefs->m_oChDef[nIndex].m_nChRsIndexEx = -1;
			}
			else
			{
				pChDefs->m_oChDef[nIndex].m_nChRsIndexEx = pSttChMap->m_nRsIndex-1;

				if(pSttChMap->m_strID.Left(1)==_T("U"))
				{
					if(pSttChMap->m_nRsIndex > g_nRtDataVoltCnt)
						g_nRtDataVoltCnt = pSttChMap->m_nRsIndex;
				}
				else
				{
					if(pSttChMap->m_nRsIndex > g_nRtDataCurrCnt)
						g_nRtDataCurrCnt = pSttChMap->m_nRsIndex;
				}

				if(pSttChMap->m_strID.Left(1)==_T("U"))
					pChDefs->m_oChDef[nIndex].m_nEeTypeEx = STT_CH_EETYPE_VOLTAGE;
				else
					pChDefs->m_oChDef[nIndex].m_nEeTypeEx = STT_CH_EETYPE_CURRENT;
			}
		}
	}
}

void CSttChMapsConfig::ChMapsConfig(CSttChMaps &oChMaps)
{
	long nIndex = 0;

    g_nRtDataVoltCnt = 0;
    g_nRtDataCurrCnt = 0;
	for (nIndex=0; nIndex<g_theDeviceSystemParameter->m_nModuleCount; nIndex++)
	{
		if(g_theDeviceSystemParameter->m_oModules[nIndex].m_oModuleAttr.m_nModuleType==STT_MODULE_TYPE_MEAS_CURRENT
				||g_theDeviceSystemParameter->m_oModules[nIndex].m_oModuleAttr.m_nModuleType==STT_MODULE_TYPE_MEAS_VOLT
				||g_theDeviceSystemParameter->m_oModules[nIndex].m_oModuleAttr.m_nModuleType==STT_MODULE_TYPE_SWITCH)
			continue;

		ChMapConfig_Module_Module(oChMaps, & g_theDeviceSystemParameter->m_oModules[nIndex]);
		g_theDeviceSystemParameter->m_oModules[nIndex].InitChTmtPos();
	}

    if(g_nRtDataVoltCnt > MAX_VOLTAGE_COUNT)
        g_nRtDataVoltCnt = MAX_VOLTAGE_COUNT;
    if(g_nRtDataCurrCnt > MAX_CURRENT_COUNT)
        g_nRtDataCurrCnt = MAX_CURRENT_COUNT;
}

