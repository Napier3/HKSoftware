#include "stdafx.h"
#include"SttAdjustTool.h"
#include "tmt_adjust_cal.h"
#include "../../SttGlobalDef.h"
#include "../../RecordTest/SttRcdSocketBufferZip.h"

CSttAdjustTool g_theSttAdjustTool;

#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
extern PTMT_ADJ_MODULE_OUTPUT g_theModuleOutPut;
//extern PTMT_ADJ_MODULECH_OUTPUT g_theModuleChOutPut;
#include "QTimer"
#include "QEventLoop"
#endif

CSttAdjustTool::CSttAdjustTool()
{
	m_nSwitchCtrl=0;
	m_pszAdjSysPara=(BYTE*)malloc(0x2000);
}

CSttAdjustTool::~CSttAdjustTool(void)
{
	delete m_pszAdjSysPara;
}


BOOL CSttAdjustTool::Adjust(const CString &strMacroID, CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport )
{
	if (strMacroID == STT_ADJUST_MACRO_ID_AdjustOne)
	{
		return Adjust_One(pMacroParas, pXmlSerializeReport);
	}

	if (strMacroID == STT_ADJUST_MACRO_ID_AdjustOne2Points)
	{
		return Adjust_One2Points(pMacroParas, pXmlSerializeReport);
	}

	if (strMacroID == STT_ADJUST_MACRO_ID_AdjustThree)
	{
		return Adjust_Three(pMacroParas, pXmlSerializeReport);
	}

	if (strMacroID == STT_ADJUST_MACRO_ID_AdjustSwitch)
	{
		Adjust_Switch(pMacroParas, pXmlSerializeReport);
		return TRUE;
	}

	if (strMacroID == STT_ADJUST_MACRO_ID_ReadModuleFlash)
	{
		Adjust_ReadModuleFlash(pMacroParas, pXmlSerializeReport);
		return TRUE;
	}

	if (strMacroID == STT_ADJUST_MACRO_ID_WriteModuleFlash)
	{
		Adjust_WriteModuleFlash(pMacroParas, pXmlSerializeReport);
		return TRUE;
	}

	if (strMacroID == STT_ADJUST_MACRO_ID_AdjustOneCopy)
	{
		Adjust_OneCopy(pMacroParas, pXmlSerializeReport);
		return TRUE;
	}

	if (strMacroID == STT_ADJUST_MACRO_ID_AdjustReboot)
	{
#ifdef _PSX_QT_LINUX_
		system("sync");
		system("reboot");
#endif
	}

	if (strMacroID == STT_CMD_TYPE_ADJUST_WriteFile)
	{
		g_bWriteHdInfor=TRUE;
		stt_xml_serialize_register_adjust();
		return TRUE;
	}

	return FALSE;
}

BOOL CheckModuleType(long nModule,long nModuleType)
{
	int nModulePos=nModule;//传入模块位置
	switch(nModuleType)
	{
	case STT_MODULE_TYPE_VOLT:
	case STT_MODULE_TYPE_CURRENT:
		break;
	default:
		return FALSE;//不支持校准的模块类型
	}

	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount;nIndex++)
	{
		STT_MODULE &oModule=g_theDeviceSystemParameter->m_oModules[nIndex];

		if(oModule.m_oModuleAttr.m_nModuleIndex==nModulePos&&
				oModule.m_oModuleAttr.m_nModuleType==nModuleType)
		{
			return TRUE;//传参ModulePos ModuleType有效
		}
	}

	return FALSE;
}

BOOL CSttAdjustTool::Adjust_One(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport )
{
#ifdef _PSX_QT_LINUX_
	if (g_theModuleOutPut == NULL)
	{
		return FALSE;
	}
#endif

	TMT_ADJUST_ONE oTmtOne;

	//传递过来的校准参数：测量值
	stt_xml_serialize(&oTmtOne.m_oParas, pMacroParas);

	if(!CheckModuleType(oTmtOne.m_oParas.m_nModule,oTmtOne.m_oParas.m_nModuleType))
		return FALSE;

	//计算校准系数
#ifdef _PSX_QT_LINUX_
	stt_adj_cal(g_theDeviceSystemParameter, g_theModuleOutPut, &oTmtOne);
#endif

	//结果
	stt_xml_serialize(&oTmtOne.m_oResult, pXmlSerializeReport);

	return TRUE;
}

BOOL CSttAdjustTool::Adjust_One2Points(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport )
{
#ifdef _PSX_QT_LINUX_
//	if (g_theModuleChOutPut == NULL)
	{
		return FALSE;
	}
#endif

	TMT_ADJUST_ONE2POINTS oTmtOne2Points;

	//传递过来的校准参数：测量值
	stt_xml_serialize(&oTmtOne2Points.m_oParas, pMacroParas);

	if(!CheckModuleType(oTmtOne2Points.m_oParas.m_nModule,oTmtOne2Points.m_oParas.m_nModuleType))
		return FALSE;

	//计算校准系数
#ifdef _PSX_QT_LINUX_
//	stt_adj_cal(g_theDeviceSystemParameter, g_theModuleChOutPut, &oTmtOne2Points);
#endif

	//结果
	stt_xml_serialize(&oTmtOne2Points.m_oResult, pXmlSerializeReport);

	return TRUE;
}

BOOL CSttAdjustTool::Adjust_Three(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport )
{
#ifdef _PSX_QT_LINUX_
	if (g_theModuleOutPut == NULL)
	{
		return FALSE;
	}
#endif
	TMT_ADJUST_THREE oTmtThree;

	//传递过来的校准参数：测量值
	stt_xml_serialize(&oTmtThree.m_oParas, pMacroParas);

	if(!CheckModuleType(oTmtThree.m_oParas.m_nModule,oTmtThree.m_oParas.m_nModuleType))
		return FALSE;

	//计算校准系数
#ifdef _PSX_QT_LINUX_
	stt_adj_cal(g_theDeviceSystemParameter, g_theModuleOutPut, &oTmtThree);
#endif

	//结果
	stt_xml_serialize(&oTmtThree.m_oResults, pXmlSerializeReport);

	return TRUE;
}

void CSttAdjustTool::Adjust_Switch(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport )
{
	TMT_ADJ_SWITCH_OUTPUT oTmtSwitch;

	//传递过来的开关切换参数
	stt_xml_serialize(&oTmtSwitch, pMacroParas);

	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Switch ModuleType=%d"),oTmtSwitch.m_nModuleType);
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Switch SwitchMode=%d"),oTmtSwitch.m_nSwitchMode);
	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T(""));

	if(oTmtSwitch.m_nSwitchMode==6)//1~3
	{
		m_nSwitchCtrl =SWITCH_GROUP_1;
		return;
	}

	if(oTmtSwitch.m_nSwitchMode==7)//4~6
	{
		m_nSwitchCtrl =SWITCH_GROUP_2;
		return;
	}

	if(oTmtSwitch.m_nModuleType==STT_MODULE_TYPE_VOLT)
	{
		switch(oTmtSwitch.m_nSwitchMode)
		{
		case 0:
			m_nSwitchCtrl =SWITCH_U_0;
			break;
		case 1:
			m_nSwitchCtrl = SWITCH_U_1;
			break;
		case 2:
			m_nSwitchCtrl = SWITCH_U_2;
			break;
		case 3:
			m_nSwitchCtrl = SWITCH_U_3;
			break;
		case 4:
			m_nSwitchCtrl = SWITCH_U_4;
			break;
		case 5:
			m_nSwitchCtrl = SWITCH_U_5;
			break;
		}

		return;
	}

	if(oTmtSwitch.m_nModuleType==STT_MODULE_TYPE_CURRENT)
	{
		switch(oTmtSwitch.m_nSwitchMode)
		{
		case 0:
			m_nSwitchCtrl = SWITCH_I_0;
			break;
		case 1:
			m_nSwitchCtrl = SWITCH_I_1;
			break;
		case 2:
			m_nSwitchCtrl = SWITCH_I_2;
			break;
		case 3:
			m_nSwitchCtrl = SWITCH_I_3;
			break;
		case 4:
			m_nSwitchCtrl = SWITCH_I_4;
			break;
		case 5:
			m_nSwitchCtrl = SWITCH_I_5;
			break;
		}
		return;
	}
}

CString CSttAdjustTool::Adjust_GetSwitch(int nSwitchCtrl)
{
	CString strRet=_T("");
	switch(nSwitchCtrl)
	{
	case SWITCH_U_0:
		strRet=_T("SWITCH_U_0");
		break;
	case SWITCH_U_1:
		strRet=_T("SWITCH_U_1");
		break;
	case SWITCH_U_2:
		strRet=_T("SWITCH_U_2");
		break;
	case SWITCH_U_3:
		strRet=_T("SWITCH_U_3");
		break;
	case SWITCH_U_4:
		strRet=_T("SWITCH_U_4");
		break;
	case SWITCH_U_5:
		strRet=_T("SWITCH_U_5");
		break;

	case SWITCH_I_0:
		strRet=_T("SWITCH_I_0");
		break;
	case SWITCH_I_1:
		strRet=_T("SWITCH_I_1");
		break;
	case SWITCH_I_2:
		strRet=_T("SWITCH_I_2");
		break;
	case SWITCH_I_3:
		strRet=_T("SWITCH_I_3");
		break;
	case SWITCH_I_4:
		strRet=_T("SWITCH_I_4");
		break;
	case SWITCH_I_5:
		strRet=_T("SWITCH_I_5");
		break;

	case SWITCH_GROUP_1:
		strRet=_T("SWITCH_GROUP_1");
		break;
	case SWITCH_GROUP_2:
		strRet=_T("SWITCH_GROUP_2");
		break;
	default:
		strRet=_T("SWITCH_ERROR");
		break;
	}

	return strRet;
}

void CSttAdjustTool::Adjust_OneCopy(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport )
{
	TMT_ADJUST_ONECOPY oTmtOneCopy;

	stt_xml_serialize(&oTmtOneCopy.m_oParas, pMacroParas);
	oTmtOneCopy.m_oResult.m_oResult.m_fCoef=-1;
	oTmtOneCopy.m_oResult.m_oResult.m_fZero=0;

	if(CheckModuleType(oTmtOneCopy.m_oParas.m_nModule,oTmtOneCopy.m_oParas.m_nModuleType)&&
			CheckModuleType(oTmtOneCopy.m_oParas.m_nModule2,oTmtOneCopy.m_oParas.m_nModuleType))
	{

	}
	else
	{
		stt_xml_serialize(&oTmtOneCopy.m_oResult, pXmlSerializeReport);
		return;
	}

#ifdef _PSX_QT_LINUX_
	TMT_ADJ_CAL_VECTOR oAdjCalVector;
	memset(&oAdjCalVector, 0, sizeof(TMT_ADJ_CAL_VECTOR));
	oAdjCalVector.m_oAdjParas.m_nModuleType=oTmtOneCopy.m_oParas.m_nModuleType;
	oAdjCalVector.m_oAdjParas.m_nModule=oTmtOneCopy.m_oParas.m_nModule;
	oAdjCalVector.m_oAdjParas.m_nFreqSel=oTmtOneCopy.m_oParas.m_nFreqSel;
	oAdjCalVector.m_oAdjParas.m_nChannel=oTmtOneCopy.m_oParas.m_nChannel;
	oAdjCalVector.m_oAdjParas.m_nTempretureID=oTmtOneCopy.m_oParas.m_nTempretureID;
	oAdjCalVector.m_oAdjParas.m_nGearID=oTmtOneCopy.m_oParas.m_nGearID;

	if (stt_adj_get_adjust_item_ref(g_theDeviceSystemParameter, oAdjCalVector))
	{
		float fCoef=oAdjCalVector.m_pAdjResults->m_fCoef;
		float fAngle=oAdjCalVector.m_pAdjResults->m_fAngle;

		memset(&oAdjCalVector, 0, sizeof(TMT_ADJ_CAL_VECTOR));
		oAdjCalVector.m_oAdjParas.m_nModuleType=oTmtOneCopy.m_oParas.m_nModuleType;
		oAdjCalVector.m_oAdjParas.m_nModule=oTmtOneCopy.m_oParas.m_nModule2;
		oAdjCalVector.m_oAdjParas.m_nFreqSel=oTmtOneCopy.m_oParas.m_nFreqSel;
		oAdjCalVector.m_oAdjParas.m_nChannel=oTmtOneCopy.m_oParas.m_nChannel2;
		oAdjCalVector.m_oAdjParas.m_nTempretureID=oTmtOneCopy.m_oParas.m_nTempretureID2;
		oAdjCalVector.m_oAdjParas.m_nGearID=oTmtOneCopy.m_oParas.m_nGearID2;

		if (stt_adj_get_adjust_item_ref(g_theDeviceSystemParameter, oAdjCalVector))
		{
			oAdjCalVector.m_pAdjResults->m_fCoef=fCoef;
			oAdjCalVector.m_pAdjResults->m_fAngle=fAngle;

			oTmtOneCopy.m_oResult.m_oResult.m_fCoef=fCoef;
			oTmtOneCopy.m_oResult.m_oResult.m_fAngle=fAngle;
		}
	}
#endif

	//结果
	stt_xml_serialize(&oTmtOneCopy.m_oResult, pXmlSerializeReport);
}

void CSttAdjustTool::Adjust_ReadModuleFlash(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport )
{
#ifdef _PSX_QT_LINUX_
	TMT_ADJ_MODULEFLASH oTmtModuleFlash;
	oTmtModuleFlash.init();
	stt_xml_serialize(&oTmtModuleFlash.m_oParas, pMacroParas);

	m_nDestLen = 0;

	//从二进制内存数据中，获取模块系数数据
	PSTT_MODULE pModule=stt_adj_find_module_byModulePos(g_theDeviceSystemParameter,
														oTmtModuleFlash.m_oParas.m_nModuleIndex,oTmtModuleFlash.m_oParas.m_nModuleType);
	if(pModule!=NULL)
	{
		int nOffset=0;

		CLogPrint::LogString(XLOGLEVEL_TRACE,_T("GetModuleFlash"));
		if(CSttDeviceBase::g_pSttDeviceBase->GetModuleFlash(pModule,m_pszAdjSysPara,nOffset))
		{
			if (stt_rcd_zip_buf_match_head(m_pszAdjSysPara+nOffset))
			{
				stt_binary_serialize_read(*pModule, m_pszAdjSysPara+nOffset, m_nDestLen, true);
				oTmtModuleFlash.m_oResult.m_nResult=STT_ADJUST_MODULEFLASH_RESULT_SUCCESS;
				g_bWriteHdInfor=TRUE;
				stt_xml_serialize_register_adjust();
			}
			else
			{

				QEventLoop loop;
				QTimer::singleShot(1000,&loop,SLOT(quit()));
				loop.exec();

				CLogPrint::LogString(XLOGLEVEL_TRACE,_T("GetModuleFlash_Again"));
				CSttDeviceBase::g_pSttDeviceBase->GetModuleFlash(pModule,m_pszAdjSysPara,nOffset);
				if (stt_rcd_zip_buf_match_head(m_pszAdjSysPara+nOffset))
				{
					stt_binary_serialize_read(*pModule, m_pszAdjSysPara+nOffset, m_nDestLen, true);
					oTmtModuleFlash.m_oResult.m_nResult=STT_ADJUST_MODULEFLASH_RESULT_SUCCESS;
					g_bWriteHdInfor=TRUE;
					stt_xml_serialize_register_adjust();
				}
				else
					oTmtModuleFlash.m_oResult.m_nResult=STT_ADJUST_MODULEFLASH_RESULT_DataHeadErr;
			}
		}
		else
			oTmtModuleFlash.m_oResult.m_nResult=STT_ADJUST_MODULEFLASH_RESULT_ModuleNoResponse;
	}
	else
		oTmtModuleFlash.m_oResult.m_nResult=STT_ADJUST_MODULEFLASH_RESULT_ModulePtrIsNull;

	stt_xml_serialize(&oTmtModuleFlash.m_oResult, pXmlSerializeReport);
#endif
}

void CSttAdjustTool::Adjust_WriteModuleFlash(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport )
{
#ifdef _PSX_QT_LINUX_
	TMT_ADJ_MODULEFLASH oTmtModuleFlash;
	oTmtModuleFlash.init();
	stt_xml_serialize(&oTmtModuleFlash.m_oParas, pMacroParas);

	m_nDestLen = 0;

	PSTT_MODULE pModule=stt_adj_find_module_byModulePos(g_theDeviceSystemParameter,
														oTmtModuleFlash.m_oParas.m_nModuleIndex,oTmtModuleFlash.m_oParas.m_nModuleType);
	if(pModule!=NULL)
	{
		BYTE *pAdjSysPara=NULL;
		//将选中的模块内存数据，串行化到缓冲区中，即返回到pszAdjSysPara中，nDestLen表示数据的长度
		stt_binary_serialize_write(*pModule, &pAdjSysPara, m_nDestLen, true);

		CSttDeviceBase::g_pSttDeviceBase->FormatFlashData(pModule,pAdjSysPara,m_nDestLen);
		//m_nDestLen+4 多写4字节保证数据结尾的完整性
		if(CSttDeviceBase::g_pSttDeviceBase->SetModuleFlash(pModule,pAdjSysPara,m_nDestLen+4)==(m_nDestLen+4))
		{
			QEventLoop loop;
			QTimer::singleShot(2000,&loop,SLOT(quit()));
			loop.exec();
		}
		else
			oTmtModuleFlash.m_oResult.m_nResult=STT_ADJUST_MODULEFLASH_RESULT_ModuleNoResponse;

		delete pAdjSysPara;
	}
	else
		oTmtModuleFlash.m_oResult.m_nResult=STT_ADJUST_MODULEFLASH_RESULT_ModulePtrIsNull;

	stt_xml_serialize(&oTmtModuleFlash.m_oResult, pXmlSerializeReport);
#endif
}
