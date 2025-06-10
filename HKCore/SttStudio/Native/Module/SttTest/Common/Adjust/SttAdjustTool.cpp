#include "stdafx.h"
#include"SttAdjustTool.h"
#include "tmt_adjust_cal.h"
#include "../../../SttGlobalDef.h"

CSttAdjustTool g_theSttAdjustTool;

#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/SttDeviceBase.h"
extern PTMT_ADJ_MODULE_OUTPUT g_theModuleOutPut;
#include "QTimer"
#include "QEventLoop"
#include "QDateTime"
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

    if (strMacroID == STT_ADJUST_MACRO_ID_AdjustOneAngle)
	{
		return Adjust_OneAngle(pMacroParas, pXmlSerializeReport);
	}

    if (strMacroID == STT_ADJUST_MACRO_ID_AdjustOneFreq)
	{
		return Adjust_OneFreq(pMacroParas, pXmlSerializeReport);
	}

    if (strMacroID == STT_ADJUST_MACRO_ID_AdjustOneDcZero)
	{
		return Adjust_OneDcZero(pMacroParas, pXmlSerializeReport);
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

	if(strMacroID == STT_ADJUST_MACRO_ID_SetMeasGear)
    {//采集模块校准前档位设置
		Adjust_SetMeasGear(pMacroParas);
		return TRUE;
	}

    if (strMacroID == STT_CMD_TYPE_ADJUST_WriteFile)
	{
        g_bWriteHdInfor=TRUE;
		stt_xml_serialize_register_adjust();
		return TRUE;
	}

    if (strMacroID == STT_ADJUST_MACRO_ID_SetUTCTime)
	{
		//设置LINUX系统软时钟
#ifdef _PSX_QT_LINUX_
	short nYear,nMonth,nDay,nHour,nMinute,nSecond;
        pMacroParas->xml_serialize("年", "Year","","long",nYear);
        pMacroParas->xml_serialize("月", "Month","","long",nMonth);
        pMacroParas->xml_serialize("日", "Day","","long",nDay);
        pMacroParas->xml_serialize("时", "Hour","","long",nHour);
        pMacroParas->xml_serialize("分", "Minute","","long",nMinute);
        pMacroParas->xml_serialize("秒", "Second","","long",nSecond);

		if(nYear > 2099 || nYear < 2023)
		{
			return FALSE;
		}
		if(nMonth > 12 || nMonth < 1)
		{
			return FALSE;
		}
		if(nDay > 31 || nDay < 1)
		{
			return FALSE;
		}
		if(nHour > 23 || nHour < 0)
		{
			return FALSE;
		}
		if(nMinute > 59 || nMinute < 0)
		{
			return FALSE;
		}
		if(nSecond > 59 || nSecond < 0)
		{
			return FALSE;
		}

		unsigned int nTime_t;
		TransTimer_To_t(nTime_t,nYear,nMonth,nDay,nHour,nMinute,nSecond);
		nTime_t -= 8*3600;//转成0时区时间,默认输入的是北京时间
		TransTimer_t(nTime_t,nYear,nMonth,nDay,nHour,nMinute,nSecond);

		CString strUTC;
		strUTC.Format(_T("date -u -s \"%d-%d-%d %d:%d:%d\""),
                      nYear,nMonth,nDay,nHour,nMinute,nSecond);
		system(strUTC.GetString());
		system("hwclock -u -w");//写入芯片
		Sleep(1000);
		system("hwclock -s");//从芯片同步到系统
#endif
		return TRUE;
	}

    if (strMacroID == STT_ADJUST_MACRO_ID_GetUTCTime)
	{
		//读取LINUX系统软时钟
#ifdef _PSX_QT_LINUX_
		QDateTime oDate = QDateTime::currentDateTimeUtc();
		short nYear,nMonth,nDay,nHour,nMinute,nSecond;
		nYear = oDate.date().year();
		nMonth = oDate.date().month();
		nDay = oDate.date().day();
		nHour = oDate.time().hour();
		nMinute = oDate.time().minute();
		nSecond = oDate.time().second();

		unsigned int nTime_t;
		TransTimer_To_t(nTime_t,nYear,nMonth,nDay,nHour,nMinute,nSecond);
		nTime_t += 8*3600;//转成北京时间
		TransTimer_t(nTime_t,nYear,nMonth,nDay,nHour,nMinute,nSecond);

        pXmlSerializeReport->xml_serialize("年","Year","","long",nYear);
        pXmlSerializeReport->xml_serialize("月","Month","","long",nMonth);
        pXmlSerializeReport->xml_serialize("日","Day","","long",nDay);
        pXmlSerializeReport->xml_serialize("时","Hour","","long",nHour);
        pXmlSerializeReport->xml_serialize("分","Minute","","long",nMinute);
        pXmlSerializeReport->xml_serialize("秒","Second","","long",nSecond);
#endif
		return TRUE;
	}

	return FALSE;
}

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
#include "../../../SttDevice/Module/PowerCtrl/SttPowerCtrlCom.h"
#endif
#endif

BOOL CheckModuleType(long nModule,long nModuleType)
{
    int nModulePos=nModule;//传入模块位置
	switch(nModuleType)
	{
		case STT_MODULE_TYPE_VOLT:
		case STT_MODULE_TYPE_CURRENT:
		case STT_MODULE_TYPE_DCVOLT:
		case STT_MODULE_TYPE_DCCURRENT:
		case STT_MODULE_TYPE_MEAS_VOLT:
		case STT_MODULE_TYPE_MEAS_CURRENT:
		case STT_MODULE_TYPE_VOLT_CURRENT:
		case STT_MODULE_TYPE_WEEK_EX:
		case STT_MODULE_TYPE_ADMU:
			break;

		default:
			return FALSE;//不支持校准的模块类型
	}

    for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount;nIndex++)
	{
        STT_MODULE &oModule=g_theDeviceSystemParameter->m_oModules[nIndex];

		if(oModule.m_oModuleAttr.m_nModuleType == nModuleType)
		{
			if(oModule.m_oModuleAttr.m_nModuleIndex == nModulePos)
			{
				return TRUE;//传参ModulePos ModuleType有效
			}

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
			if(oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D
					||oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
					||oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20
					||oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_6)
			{
				return TRUE;//传参ModulePos ModuleType有效
			}
#endif
#endif
		}
	}

	return FALSE;
}

void CSttAdjustTool::Adjust_SetMeasGear(CSttXmlSerializeBase *pMacroParas)
{
	TMT_ADJUST_MEAS_GEAR oMeasGear;
	stt_xml_serialize(oMeasGear, pMacroParas);
#ifdef _PSX_QT_LINUX_
    CSttDeviceBase::g_pSttDeviceBase->SetMeasModuleChanGear(oMeasGear.m_nModuleType,oMeasGear.m_nModulePos,
                                                            oMeasGear.m_nChannel,oMeasGear.m_nGearID);
#endif
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
	TMT_ADJUST_ONE2POINTS oTmtOne2Points;

	//传递过来的校准参数：测量值
	stt_xml_serialize(&oTmtOne2Points.m_oParas, pMacroParas);

    if(!CheckModuleType(oTmtOne2Points.m_oParas.m_nModule,oTmtOne2Points.m_oParas.m_nModuleType))
	{
		return FALSE;
	}

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount;nIndex++)
	{
        STT_MODULE &oModule=g_theDeviceSystemParameter->m_oModules[nIndex];

		if(oModule.m_oModuleAttr.m_nModuleType == oTmtOne2Points.m_oParas.m_nModuleType)
		{
			if(oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20
					||oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_6)
			{
				oTmtOne2Points.m_oParas.m_nModule = 16;
				break;
			}

			if(oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
			{
				oTmtOne2Points.m_oParas.m_nModule = 14;
				break;
			}
		}
	}
#endif
#endif

	//计算校准系数
#ifdef _PSX_QT_LINUX_
	stt_adj_cal(g_theDeviceSystemParameter, &oTmtOne2Points);
#endif

	//结果
	stt_xml_serialize(&oTmtOne2Points.m_oResult, pXmlSerializeReport);

	return TRUE;
}

BOOL CSttAdjustTool::Adjust_OneAngle(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport )
{
	TMT_ADJUST_ANGLE oTmtAngle;

	//传递过来的校准参数：测量值
	stt_xml_serialize(&oTmtAngle.m_oParas, pMacroParas);

    if(!CheckModuleType(oTmtAngle.m_oParas.m_nModule,oTmtAngle.m_oParas.m_nModuleType))
		return FALSE;

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount;nIndex++)
	{
        STT_MODULE &oModule=g_theDeviceSystemParameter->m_oModules[nIndex];

		if(oModule.m_oModuleAttr.m_nModuleType == oTmtAngle.m_oParas.m_nModuleType)
		{
			if(oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20
					||oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_6)
			{
				oTmtAngle.m_oParas.m_nModule = 16;
				break;
			}

			if(oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
			{
				oTmtAngle.m_oParas.m_nModule = 14;
				break;
			}
		}
	}
#endif
#endif

	//计算校准系数
#ifdef _PSX_QT_LINUX_
	stt_adj_cal(g_theDeviceSystemParameter, &oTmtAngle);
#endif

	//结果
	stt_xml_serialize(&oTmtAngle.m_oResult, pXmlSerializeReport);

	return TRUE;
}

BOOL CSttAdjustTool::Adjust_OneFreq(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport )
{
	TMT_ADJUST_FREQ oTmtFreq;

	//传递过来的校准参数：测量值
	stt_xml_serialize(&oTmtFreq.m_oParas, pMacroParas);

    if(!CheckModuleType(oTmtFreq.m_oParas.m_nModule,oTmtFreq.m_oParas.m_nModuleType))
		return FALSE;

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount;nIndex++)
	{
        STT_MODULE &oModule=g_theDeviceSystemParameter->m_oModules[nIndex];

		if(oModule.m_oModuleAttr.m_nModuleType == oTmtFreq.m_oParas.m_nModuleType)
		{
			if(oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20
					||oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_6)
			{
				oTmtFreq.m_oParas.m_nModule = 16;
				break;
			}

			if(oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
			{
				oTmtFreq.m_oParas.m_nModule = 14;
				break;
			}
		}
	}
#endif
#endif

	//计算校准系数
#ifdef _PSX_QT_LINUX_
	stt_adj_cal(g_theDeviceSystemParameter, &oTmtFreq);
#endif

	//结果
	stt_xml_serialize(&oTmtFreq.m_oResult, pXmlSerializeReport);

	return TRUE;
}

BOOL CSttAdjustTool::Adjust_OneDcZero(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport )
{
	TMT_ADJUST_DCZERO oTmtDcZero;

	//传递过来的校准参数：测量值
	stt_xml_serialize(&oTmtDcZero.m_oParas, pMacroParas);

    if(!CheckModuleType(oTmtDcZero.m_oParas.m_nModule,oTmtDcZero.m_oParas.m_nModuleType))
		return FALSE;

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
    for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount;nIndex++)
	{
        STT_MODULE &oModule=g_theDeviceSystemParameter->m_oModules[nIndex];

		if(oModule.m_oModuleAttr.m_nModuleType == oTmtDcZero.m_oParas.m_nModuleType)
		{
			if(oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
					|| oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20
					||oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_6)
			{
				oTmtDcZero.m_oParas.m_nModule = 16;
				break;
			}

			if(oModule.m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
			{
				oTmtDcZero.m_oParas.m_nModule = 14;
				break;
			}
		}
	}
#endif
#endif

	//计算校准系数
#ifdef _PSX_QT_LINUX_
	stt_adj_cal(g_theDeviceSystemParameter, &oTmtDcZero);
#endif

	//结果
	stt_xml_serialize(&oTmtDcZero.m_oResult, pXmlSerializeReport);

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
	oTmtModuleFlash.m_oParas.m_nModuleIndex += 1;//传参是0-11,m_oModuleAttr.m_nModuleIndex是1-12
	m_nDestLen = 0;
	//从二进制内存数据中，获取模块系数数据
	PSTT_MODULE pModule = NULL;

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount; i++)
	{
		if(oTmtModuleFlash.m_oParas.m_nModuleIndex ==
				g_theDeviceSystemParameter->m_oModules[i].m_oModuleAttr.m_nModuleIndex)
		{
			pModule = &g_theDeviceSystemParameter->m_oModules[i];
			break;
		}
	}

	BOOL bModuleIsAdd = FALSE;

	if(pModule == NULL)
	{
		//未查找到已有位置模块，创建新模块
		long nModuleCount = g_theDeviceSystemParameter->m_nModuleCount;

		if(nModuleCount < (ADJUST_MAX_MODULE_COUNT + 1) && oTmtModuleFlash.m_oParas.m_nModuleIndex <= 12)
		{
			pModule = &g_theDeviceSystemParameter->m_oModules[nModuleCount];
			pModule->init();
			pModule->m_oModuleAttr.m_nModuleIndex = oTmtModuleFlash.m_oParas.m_nModuleIndex;
			g_theDeviceSystemParameter->m_nModuleCount++;
			bModuleIsAdd = TRUE;
		}
		else
		{
			oTmtModuleFlash.m_oResult.m_nResult = STT_ADJUST_MODULEFLASH_RESULT_ModuleNoResponse;
			stt_xml_serialize(&oTmtModuleFlash.m_oResult, pXmlSerializeReport);
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("系数文件无法添加指定位置模块"));
			return;
		}
	}

	int nOffset = 0;

	if(CSttDeviceBase::g_pSttDeviceBase->GetModuleFlash(pModule, m_pszAdjSysPara, nOffset))
	{
		//nOffset 8+ChanSize*3*4,Max=584
		if(nOffset <= 584 && stt_rcd_zip_buf_match_head(m_pszAdjSysPara + nOffset))
		{
			BOOL bRet = stt_binary_serialize_read(*pModule, m_pszAdjSysPara + nOffset, m_nDestLen, true);

			if(bRet)
			{
				pModule->m_oModuleAttr.m_nModuleIndex = oTmtModuleFlash.m_oParas.m_nModuleIndex;
				oTmtModuleFlash.m_oResult.m_nResult = STT_ADJUST_MODULEFLASH_RESULT_SUCCESS;
				g_bWriteHdInfor = TRUE;				
				CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("读模块系数成功"));
				if(pModule->m_oModuleAttr.m_dwVersion < STT_ADJUST_MODULE_PARA_VERSION)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("当前模块系数版本 = %d，模块系数最新版本 = %d"),
											   pModule->m_oModuleAttr.m_dwVersion,STT_ADJUST_MODULE_PARA_VERSION);
					CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("请核对模块属性的具体内容"));
				}
				stt_xml_serialize_register_adjust();
				g_dwSttAdjSysParaCurrVersion = CSttDeviceBase::g_pSttDeviceBase->m_oSysUtc.tm_l;
			}
			else
			{
				if(bModuleIsAdd)
				{
					g_theDeviceSystemParameter->m_nModuleCount--;
				}

				oTmtModuleFlash.m_oResult.m_nResult = STT_ADJUST_MODULEFLASH_RESULT_UnZipErr;
				CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("读模块数据内容解压错误"));
			}
		}
		else
		{
			if(bModuleIsAdd)
			{
				g_theDeviceSystemParameter->m_nModuleCount--;
			}

			oTmtModuleFlash.m_oResult.m_nResult = STT_ADJUST_MODULEFLASH_RESULT_DataHeadErr;
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("返回数据内容头错误"));
		}
	}
	else
	{
		if(bModuleIsAdd)
		{
			g_theDeviceSystemParameter->m_nModuleCount--;
		}

		oTmtModuleFlash.m_oResult.m_nResult = STT_ADJUST_MODULEFLASH_RESULT_ModuleNoResponse;
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("读模块无响应"));
	}

	stt_xml_serialize(&oTmtModuleFlash.m_oResult, pXmlSerializeReport);
#endif
}

void CSttAdjustTool::Adjust_WriteModuleFlash(CSttXmlSerializeBase *pMacroParas, CSttXmlSerializeBase *pXmlSerializeReport )
{
#ifdef _PSX_QT_LINUX_
	TMT_ADJ_MODULEFLASH oTmtModuleFlash;
	oTmtModuleFlash.init();
	stt_xml_serialize(&oTmtModuleFlash.m_oParas, pMacroParas);
	oTmtModuleFlash.m_oParas.m_nModuleIndex += 1;//传参是0-11,m_oModuleAttr.m_nModuleIndex是1-12
	m_nDestLen = 0;
	PSTT_MODULE pModule = NULL;

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount; i++)
	{
		if(oTmtModuleFlash.m_oParas.m_nModuleIndex ==
				g_theDeviceSystemParameter->m_oModules[i].m_oModuleAttr.m_nModuleIndex)
		{
			pModule = &g_theDeviceSystemParameter->m_oModules[i];
			break;
		}
	}

	if(pModule == NULL)
	{
		oTmtModuleFlash.m_oResult.m_nResult = STT_ADJUST_MODULEFLASH_RESULT_ModulePtrIsNull;
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("模块写位置不对"));
		stt_xml_serialize(&oTmtModuleFlash.m_oResult, pXmlSerializeReport);
		return;
	}

	BYTE *pAdjSysPara = NULL;
	//将选中的模块内存数据，串行化到缓冲区中，即返回到pszAdjSysPara中，nDestLen表示数据的长度
	pModule->m_oModuleAttr.m_nModuleAddr = oTmtModuleFlash.m_oParas.m_nModuleAddr;
	stt_binary_serialize_write(*pModule, &pAdjSysPara, m_nDestLen, true);
	CSttDeviceBase::g_pSttDeviceBase->FormatFlashData(pModule, pAdjSysPara, m_nDestLen);

	//m_nDestLen+4 多写4字节保证数据结尾的完整性
	if(CSttDeviceBase::g_pSttDeviceBase->SetModuleFlash(pModule, pAdjSysPara, m_nDestLen + 4) == (m_nDestLen + 4))
	{
		QEventLoop loop;
		QTimer::singleShot(2000, &loop, SLOT(quit()));
		loop.exec();
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("写模块系数结束"));
	}
	else
	{
		oTmtModuleFlash.m_oResult.m_nResult = STT_ADJUST_MODULEFLASH_RESULT_ModuleResponseErr;
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("写模块返回错误"));
	}

	delete pAdjSysPara;
	stt_xml_serialize(&oTmtModuleFlash.m_oResult, pXmlSerializeReport);
#endif
}
