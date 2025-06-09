#include "stdafx.h"
#include "tmt_replay_test.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"
#endif

void stt_xml_serialize_module(TMT_REPLAY_MODULE *pModule, int nIndex,CSttXmlSerializeBase *pXmlSierialize, int nHasAnalogMode, int nHasDigitalMode, int nHasWeekMode)
{
	char chName[MAX_PATH],chID[MAX_PATH];

#ifdef NOT_USE_XLANGUAGE
	sprintf(chName, "模块%d", nIndex+1);
#else
	sprintf(chName, /*"模块%d"*/g_sLangTxt_Native_ModReplace.GetString(), nIndex+1);
#endif
	sprintf(chID, "Module%d", nIndex+1);

    CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize(chName, chID, "Module", stt_ParaGroupKey());
    if (pSerialize == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
    pSerialize->xml_serialize("选择","Sel","","bool",pModule->m_nSel);
#else
	pSerialize->xml_serialize(/*"选择"*/g_sLangTxt_Select.GetString(),"Sel","","bool",pModule->m_nSel);
#endif
    pSerialize->xml_serialize("Index","Index","","number",pModule->m_nIndex);//模块位置 1-12
    pSerialize->xml_serialize("ChUseCount","ChUseCount","","number",pModule->m_nChUseCount);
	pSerialize->xml_serialize("ModuleType","ModuleType","","number",pModule->m_nModuleType);//模块类型

	CString strModuleType = _T("AnalogModule");

	if(pModule->m_nModuleType != REPLAY_MODULE_TYPE_BINARY)
	{
		if(pModule->m_nModuleType == REPLAY_MODULE_TYPE_DIGITAL)
		{
			strModuleType = _T("DigitalModule");
		}
		else if(pModule->m_nModuleType == REPLAY_MODULE_TYPE_WEEK)
		{
			strModuleType = _T("WeekModule");
		}

		pSerialize->xml_serialize("ModuleType","ModuleType","","string",strModuleType);
		for (int i=0; i<pModule->m_nChUseCount; i++)
		{
		sprintf(chName, "Ch%dID", i+1);
		sprintf(chID, "Ch%dID", i+1);
        pSerialize->xml_serialize(chName,chID,"","string",pModule->m_oChMap[i].m_strChID);
		sprintf(chName, "Ch%dSelected", i+1);
		sprintf(chID, "Ch%dSelected", i+1);        
		pSerialize->xml_serialize(chName,chID,"","bool",pModule->m_oChMap[i].m_nChSel);

#ifdef NOT_USE_XLANGUAGE
		sprintf(chName, "测试仪通道%d_A通道序号", i+1);
#else
		sprintf(chName, /*"测试仪通道%d_A通道序号"*/g_sLangTxt_Native_TIC_A_Chn_Num.GetString(), i+1);
#endif
		sprintf(chID, "Ch%d_RcdChAIndex", i+1);        
		pSerialize->xml_serialize(chName,chID,"","long",pModule->m_oChMap[i].m_nChA_Index);
#ifdef NOT_USE_XLANGUAGE
		sprintf(chName, "测试仪通道%d_B通道序号", i+1);
#else
		sprintf(chName, /*"测试仪通道%d_B通道序号"*/g_sLangTxt_Native_TIC_B_Chn_Num.GetString(), i+1);
#endif
		sprintf(chID, "Ch%d_RcdChBIndex", i+1);        
		pSerialize->xml_serialize(chName,chID,"","long",pModule->m_oChMap[i].m_nChB_Index);
#ifdef NOT_USE_XLANGUAGE
		sprintf(chName, "测试仪通道%d_变比", i+1);
#else
		sprintf(chName, /*"测试仪通道%d_变比"*/g_sLangTxt_Native_TIC_TransfRatio.GetString(), i+1);
#endif
		sprintf(chID, "Ch%d_Rate", i+1);        
		pSerialize->xml_serialize(chName,chID,"","float",pModule->m_oChMap[i].m_fChRate);

			if(pModule->m_nModuleType == REPLAY_MODULE_TYPE_WEEK)
			{
				sprintf(chName, "弱信号通道%d_电气类型(0-电压,1-电流)", i+1);
				sprintf(chID, "Ch%d_EleType", i+1);        
				pSerialize->xml_serialize(chName,chID,"","long",pModule->m_oChMap[i].m_nEeType);
			}
		}

		if(pModule->m_nModuleType == REPLAY_MODULE_TYPE_WEEK)
		{
#ifdef NOT_USE_XLANGUAGE
			pSerialize->xml_serialize("PT变比一次值","PT_Prim","","number",pModule->m_fPT_Prim);
			pSerialize->xml_serialize("PT变比二次值","PT_Second","","number",pModule->m_fPT_Second);
			pSerialize->xml_serialize("CT变比一次值","CT_Prim","","number",pModule->m_fCT_Prim);
			pSerialize->xml_serialize("CT变比二次值","CT_Second","","number",pModule->m_fCT_Second);
#else
			pSerialize->xml_serialize(/*"PT变比一次值"*/g_sLangTxt_Native_PT_TxRatio_Primary.GetString(),"PT_Prim","","number",pModule->m_fPT_Prim);
			pSerialize->xml_serialize(/*"PT变比二次值"*/g_sLangTxt_Native_PT_TxRatio_Secondary.GetString(),"PT_Second","","number",pModule->m_fPT_Second);
			pSerialize->xml_serialize(/*"CT变比一次值"*/g_sLangTxt_Native_CT_TxRatio_Primary.GetString(),"CT_Prim","","number",pModule->m_fCT_Prim);
			pSerialize->xml_serialize(/*"CT变比二次值"*/g_sLangTxt_Native_CT_TxRatio_Secondary.GetString(),"CT_Second","","number",pModule->m_fCT_Second);
#endif
		}
	}
	else
	{
		strModuleType = _T("BinaryModule");
		pSerialize->xml_serialize("ModuleType","ModuleType","","string",strModuleType);

		for (int i=0; i<pModule->m_nChUseCount; i++)
		{
			sprintf(chName, "开出量通道%d_闭合状态", i+1);
			sprintf(chID, "BinaryCh%dSelected", i+1);        
			pSerialize->xml_serialize(chName,chID,"","bool",pModule->m_oBinaryChMap[i].m_nBinaryChSel);

			sprintf(chName, "开出量通道%d_通道序号", i+1);
			sprintf(chID, "BinaryCh%d_ChIndex", i+1);        
			pSerialize->xml_serialize(chName,chID,"","long",pModule->m_oBinaryChMap[i].m_nBinaryCh_Index);
		}
	}
}

void stt_xml_serialize_module_Binary( TMT_REPLAY_MODULE_BINARY *pBinaryModule, CSttXmlSerializeBase *pXmlSierialize )
{		
	char chName[MAX_PATH],chID[MAX_PATH];
	sprintf(chName, "开出量模块");
	sprintf(chID, "BinaryModule");
	
	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize(chName, chID, "Module", stt_ParaGroupKey());
	if (pSerialize == NULL)
	{
		return;
	}
	pSerialize->xml_serialize("ChUseCount","ChUseCount","","number",pBinaryModule->m_nChUseCount);

	for (int i=0; i<pBinaryModule->m_nChUseCount; i++)
	{
		sprintf(chName, "开出量通道%d_闭合状态", i+1);
		sprintf(chID, "BinaryCh%dSelected", i+1);        
		pSerialize->xml_serialize(chName,chID,"","bool",pBinaryModule->m_oChMap[i].m_nBinaryChSel);

		sprintf(chName, "开出量通道%d_通道序号", i+1);
		sprintf(chID, "BinaryCh%d_ChIndex", i+1);        
		pSerialize->xml_serialize(chName,chID,"","long",pBinaryModule->m_oChMap[i].m_nBinaryCh_Index);
	}

}

void stt_xml_serialize_WaveEditParas( TMT_REPLAY_WAVEEDITPARA *pWaveEidtParas, CSttXmlSerializeBase *pXmlSierialize )
{
	char chName[MAX_PATH],chID[MAX_PATH];
	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize("波形编辑设置", "WaveEditParas", "WaveEditParas", stt_ParaGroupKey());

	if (pSerialize == NULL)
	{
		return;
	}
	pSerialize->xml_serialize("插入波形参考","Insert_Wave_Type","","number",pWaveEidtParas->m_nInsertWaveType);

	pSerialize->xml_serialize("插入波形起始时刻(s)","Insert_Wave_Begin","","number",pWaveEidtParas->m_oInsertWaveData.m_dBegin);
	pSerialize->xml_serialize("插入波形终点时刻(s)","Insert_Wave_End","","number",pWaveEidtParas->m_oInsertWaveData.m_dEnd);
	pSerialize->xml_serialize("插入波形起始点号","Insert_Wave_Begin_Point","","number",pWaveEidtParas->m_oInsertWaveData.m_nBeginPoint);
	pSerialize->xml_serialize("插入波形终止点号","Insert_Wave_End_Point","","number",pWaveEidtParas->m_oInsertWaveData.m_nEndPoint);
	pSerialize->xml_serialize("插入波形循环次数","Insert_Wave_Cycle_Num","","number",pWaveEidtParas->m_oInsertWaveData.m_nCycleIndex);

	pSerialize->xml_serialize("删除波形起始时刻(s)","Delete_Wave_Begin","","number",pWaveEidtParas->m_oDeleteWaveData.m_dBegin);
	pSerialize->xml_serialize("删除波形终点时刻(s)","Delete_Wave_End","","number",pWaveEidtParas->m_oDeleteWaveData.m_dEnd);

	pSerialize->xml_serialize("常态波形电压(V)","Normal_Wave_Voltage","","number",pWaveEidtParas->m_oInsertNormalWaveData.m_fVoltage);
	pSerialize->xml_serialize("常态波形电流(A)","Normal_Wave_Current","","number",pWaveEidtParas->m_oInsertNormalWaveData.m_fCurrent);
	pSerialize->xml_serialize("常态波形输出时间(s)","Normal_Wave_End","","number",pWaveEidtParas->m_oInsertNormalWaveData.m_dOutputTime);

}

void stt_xml_serialize(tmt_ReplayParas *pParas, CSttXmlSerializeBase *pXmlSierialize, int nHasAnalogMode, int nHasDigitalMode, int nHasWeekMode)
{
	if(!stt_xml_serialize_is_write(pXmlSierialize))
	{
	stt_xml_serialize_WaveEditParas(&pParas->m_oWaveEditPara,pXmlSierialize);
	}
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("采样频率","SampleFreq","Hz","number",pParas->m_nSampleFreq);
	pXmlSierialize->xml_serialize("PT变比一次值","PT_Prim","","number",pParas->m_fPT_Prim);
    pXmlSierialize->xml_serialize("PT变比二次值","PT_Second","","number",pParas->m_fPT_Second);
	pXmlSierialize->xml_serialize("CT变比一次值","CT_Prim","","number",pParas->m_fCT_Prim);
	pXmlSierialize->xml_serialize("CT变比二次值","CT_Second","","number",pParas->m_fCT_Second);

	pXmlSierialize->xml_serialize("模块数","ModuleCount","","number",pParas->m_nModuleCount);
	pXmlSierialize->xml_serialize("录波文件名称","ComtradeFilePath","","string",pParas->m_pszComtradeFilePath);
        pXmlSierialize->xml_serialize("录波文件大小","ComtradeFileSize","KB","number",pParas->m_nFileSize);
	
	pXmlSierialize->xml_serialize("全部循环次数","CycleIndex","","number",pParas->m_nCycleIndex);
	pXmlSierialize->xml_serialize("手动控制","ManualControl","","BOOL",pParas->m_bManualControl);
	pXmlSierialize->xml_serialize("时间间隔","ReplayInterval","s","number",pParas->m_dReplayInterval);
	
#else
	pXmlSierialize->xml_serialize(/*"采样频率"*/g_sLangTxt_Native_SampFreq.GetString(),"SampleFreq","Hz","number",pParas->m_nSampleFreq);
	pXmlSierialize->xml_serialize(/*"PT变比一次值"*/g_sLangTxt_Native_PT_TxRatio_Primary.GetString(),"PT_Prim","","number",pParas->m_fPT_Prim);
	pXmlSierialize->xml_serialize(/*"PT变比二次值"*/g_sLangTxt_Native_PT_TxRatio_Secondary.GetString(),"PT_Second","","number",pParas->m_fPT_Second);
	pXmlSierialize->xml_serialize(/*"CT变比一次值"*/g_sLangTxt_Native_CT_TxRatio_Primary.GetString(),"CT_Prim","","number",pParas->m_fCT_Prim);
	pXmlSierialize->xml_serialize(/*"CT变比二次值"*/g_sLangTxt_Native_CT_TxRatio_Secondary.GetString(),"CT_Second","","number",pParas->m_fCT_Second);
	pXmlSierialize->xml_serialize(/*"模块数"*/g_sLangTxt_Native_NumOfModules.GetString(),"ModuleCount","","number",pParas->m_nModuleCount);
	pXmlSierialize->xml_serialize(/*"录波文件名称"*/g_sLangTxt_Native_WaveFileName.GetString(),"ComtradeFilePath","","string",pParas->m_pszComtradeFilePath);
	
	pXmlSierialize->xml_serialize(/*"全部循环次数"*/g_sLangTxt_Native_CycleIndex.GetString(),"CycleIndex","","number",pParas->m_nCycleIndex);
	pXmlSierialize->xml_serialize(/*"手动控制"*/g_sLangTxt_Native_ManualControl.GetString(),"ManualControl","","BOOL",pParas->m_bManualControl);
	pXmlSierialize->xml_serialize(/*"时间间隔"*/g_sLangID_Native_ReplayInterval.GetString(),"ReplayInterval","s","number",pParas->m_dReplayInterval);
#endif

	int i = 0;
	char chName[MAX_PATH],chID[MAX_PATH];

	for (i=0; i<pParas->m_nModuleCount; i++)
	{
// #ifdef _STT_NOT_IN_TEST_SERVER_
		if(stt_xml_serialize_is_write(pXmlSierialize))
		{
			if((pParas->m_oModule[i].m_nModuleType == REPLAY_MODULE_TYPE_ANALOG && nHasAnalogMode)
				||(pParas->m_oModule[i].m_nModuleType == REPLAY_MODULE_TYPE_DIGITAL && nHasDigitalMode)
				||(pParas->m_oModule[i].m_nModuleType == REPLAY_MODULE_TYPE_WEEK && nHasWeekMode))
			{
				stt_xml_serialize_module(&pParas->m_oModule[i],i,pXmlSierialize);
			}
		}
		else
		{
			stt_xml_serialize_module(&pParas->m_oModule[i],i,pXmlSierialize);
		}
// #else
// 		stt_xml_serialize_module(&pParas->m_oModule[i],i,pXmlSierialize,nHasAnalogMode,nHasDigitalMode,nHasWeekMode);
// #endif
	}

	//开出量模块
	pXmlSierialize->xml_serialize("使用主板开出量","UseBinaryModule","","BOOL",pParas->m_bUseBinaryModule);
	
	if(stt_xml_serialize_is_write(pXmlSierialize))
	{
		if(pParas->m_bUseBinaryModule == 1)
		{
			stt_xml_serialize_module_Binary(&pParas->m_oBinaryModule,pXmlSierialize);
		}
	}
	else
	{
	stt_xml_serialize_module_Binary(&pParas->m_oBinaryModule,pXmlSierialize);
	}


#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("触发条件","TriggerType","","number",pParas->m_nTripType);

	pXmlSierialize->xml_serialize("GPS触发时刻（时）", "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize("GPS触发时刻（分）", "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize("GPS触发时刻（秒）", "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);

// 	pXmlSierialize->xml_serialize("触发时刻(秒)","TrigTimeS","","number",pParas->m_nTrigTimeS);
// 	pXmlSierialize->xml_serialize("触发时刻(纳秒)","TrigTimeNS","","number",pParas->m_nTrigTimeNS);
	pXmlSierialize->xml_serialize("周波数","CycleNum","","number",pParas->m_nStartCycleNum);
	pXmlSierialize->xml_serialize("触发后模式","TrigAfterMode","","number",pParas->m_nTrigAfterMode);
	pXmlSierialize->xml_serialize("开入逻辑", "_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/*"触发条件"*/g_sLangTxt_State_TrigerCondition.GetString(),"TriggerType","","number",pParas->m_nTripType);

	pXmlSierialize->xml_serialize(/*"GPS触发时刻（时）"*/g_sLangTxt_Native_GPSTriggerHour.GetString(), "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize(/*"GPS触发时刻（分）"*/g_sLangTxt_Native_GPSTriggerMinute.GetString(), "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize(/*"GPS触发时刻（秒）"*/g_sLangTxt_Native_GPSTriggerSecond.GetString(), "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);

	// 	pXmlSierialize->xml_serialize("触发时刻(秒)","TrigTimeS","","number",pParas->m_nTrigTimeS);
	// 	pXmlSierialize->xml_serialize("触发时刻(纳秒)","TrigTimeNS","","number",pParas->m_nTrigTimeNS);
	pXmlSierialize->xml_serialize(/*"周波数"*/g_sLangTxt_Native_NumCycles.GetString(),"CycleNum","","number",pParas->m_nStartCycleNum);
	pXmlSierialize->xml_serialize(/*"触发后模式"*/g_sLangTxt_Native_PostTrigMode.GetString(),"TrigAfterMode","","number",pParas->m_nTrigAfterMode);
	pXmlSierialize->xml_serialize(/*"开入逻辑"*/g_sLangTxt_Native_InLogic.GetString(), "_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#endif
    char pszBInName[MAX_BINARYIN_COUNT] = "ABCDEFGHIJKLMNOP";
    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

    for(i = 0; i < nCnt; i++)
	{
#ifdef NOT_USE_XLANGUAGE
		sprintf(chName, "开入%c选择", pszBInName[i]);
#else
		sprintf(chName, /*"开入%c选择"*/g_sLangTxt_Native_InputSelection.GetString(), pszBInName[i]);
#endif
		sprintf(chID, "BIn%c", pszBInName[i]);
		pXmlSierialize->xml_serialize(chName,chID,"","BOOL",pParas->m_binIn[i].nSelect);
	}

	pXmlSierialize->xml_serialize("动作时间开入逻辑", "ActionTimeAndOr","","ActionTimeInPutLogic",pParas->m_nActionTimeBinLogic);
	for(i = 0; i < nCnt; i++)
	{
		sprintf(chName, "动作时间开入%c选择", pszBInName[i]);
		sprintf(chID, "ActionTimeBIn%c", pszBInName[i]);
		pXmlSierialize->xml_serialize(chName,chID,"","BOOL",pParas->m_frActionTimebinIn[i].nSelect);
	}

	int nTimeZero[REPLAY_ACTIONTIMEZERO_COUNT] = {1,2,3,4};
	for(i = 0; i < REPLAY_ACTIONTIMEZERO_COUNT; i++)
	{
		sprintf(chName, "动作时间计时起点%d选择", nTimeZero[i]);
		sprintf(chID, "ActionTimeZero%ld", nTimeZero[i]);
		pXmlSierialize->xml_serialize(chName,chID,"s","number",pParas->m_frActionTimeZero[i]);
	}

	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);

	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Exbinary_out(pParas->m_binOutEx, pXmlSierialize);

}

#ifndef _STT_NOT_IN_TEST_SERVER_

void stt_xml_serialize_module_replay(TMT_REPLAY_MODULE *pModule, int nIndex,CSttXmlSerializeBase *pXmlSierialize)
{
	char chName[MAX_PATH],chID[MAX_PATH];

#ifdef NOT_USE_XLANGUAGE
	sprintf(chName, "模块%d", nIndex+1);
#else
	sprintf(chName, /*"模块%d"*/g_sLangTxt_Native_ModReplace.GetString(), nIndex+1);
#endif
	sprintf(chID, "Module%d", nIndex+1);

	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize(chName, chID, "Module", stt_ParaGroupKey());
	if (pSerialize == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pSerialize->xml_serialize("选择","Sel","","bool",pModule->m_nSel);
#else
	pSerialize->xml_serialize(/*"选择"*/g_sLangTxt_Select.GetString(),"Sel","","bool",pModule->m_nSel);
#endif
	pSerialize->xml_serialize("Index","Index","","number",pModule->m_nIndex);//模块位置 1-12
	pSerialize->xml_serialize("ChUseCount","ChUseCount","","number",pModule->m_nChUseCount);
	pSerialize->xml_serialize("ModuleType","ModuleType","","number",pModule->m_nModuleType);//模块类型

	if(pModule->m_nModuleType != REPLAY_MODULE_TYPE_BINARY)
	{
		for (int i=0; i<pModule->m_nChUseCount; i++)
		{
			sprintf(chName, "Ch%dSelected", i+1);
			sprintf(chID, "Ch%dSelected", i+1);
			pSerialize->xml_serialize(chName,chID,"","bool",pModule->m_oChMap[i].m_nChSel);
		}
	}
}

void stt_xml_serialize_replay(tmt_ReplayParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	int i = 0;
	char chName[MAX_PATH],chID[MAX_PATH];

	for (i = 0; i < MAX_MODULE_COUNT; i++)
	{
		stt_xml_serialize_module_replay(&pParas->m_oModule[i],i,pXmlSierialize);
	}

	//开出量模块
	pXmlSierialize->xml_serialize("使用主板开出量","UseBinaryModule","","BOOL",pParas->m_bUseBinaryModule);

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("触发条件","TriggerType","","number",pParas->m_nTripType);

	pXmlSierialize->xml_serialize("GPS触发时刻（时）", "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize("GPS触发时刻（分）", "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize("GPS触发时刻（秒）", "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);

	pXmlSierialize->xml_serialize("周波数","CycleNum","","number",pParas->m_nStartCycleNum);
	pXmlSierialize->xml_serialize("触发后模式","TrigAfterMode","","number",pParas->m_nTrigAfterMode);
	pXmlSierialize->xml_serialize("开入逻辑", "_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#else
	pXmlSierialize->xml_serialize(/*"触发条件"*/g_sLangTxt_State_TrigerCondition.GetString(),"TriggerType","","number",pParas->m_nTripType);

	pXmlSierialize->xml_serialize(/*"GPS触发时刻（时）"*/g_sLangTxt_Native_GPSTriggerHour.GetString(), "TrigFaultTimeH"," ","number",pParas->m_tGps.nHour);
	pXmlSierialize->xml_serialize(/*"GPS触发时刻（分）"*/g_sLangTxt_Native_GPSTriggerMinute.GetString(), "TrigFaultTimeM"," ","number",pParas->m_tGps.nMinutes);
	pXmlSierialize->xml_serialize(/*"GPS触发时刻（秒）"*/g_sLangTxt_Native_GPSTriggerSecond.GetString(), "TrigFaultTimeS"," ","number",pParas->m_tGps.nSeconds);

	pXmlSierialize->xml_serialize(/*"周波数"*/g_sLangTxt_Native_NumCycles.GetString(),"CycleNum","","number",pParas->m_nStartCycleNum);
	pXmlSierialize->xml_serialize(/*"触发后模式"*/g_sLangTxt_Native_PostTrigMode.GetString(),"TrigAfterMode","","number",pParas->m_nTrigAfterMode);
	pXmlSierialize->xml_serialize(/*"开入逻辑"*/g_sLangTxt_Native_InLogic.GetString(), "_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
#endif
	char pszBInName[MAX_BINARYIN_COUNT] = "ABCDEFGHIJKLMNOP";
	int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

	for(i = 0; i < nCnt; i++)
	{
#ifdef NOT_USE_XLANGUAGE
		sprintf(chName, "开入%c选择", pszBInName[i]);
#else
		sprintf(chName, /*"开入%c选择"*/g_sLangTxt_Native_InputSelection.GetString(), pszBInName[i]);
#endif
		sprintf(chID, "BIn%c", pszBInName[i]);
		pXmlSierialize->xml_serialize(chName,chID,"","BOOL",pParas->m_binIn[i].nSelect);
	}

	pXmlSierialize->xml_serialize("动作时间开入逻辑", "ActionTimeAndOr","","ActionTimeInPutLogic",pParas->m_nActionTimeBinLogic);
	for(i = 0; i < nCnt; i++)
	{
		sprintf(chName, "动作时间开入%c选择", pszBInName[i]);
		sprintf(chID, "ActionTimeBIn%c", pszBInName[i]);
		pXmlSierialize->xml_serialize(chName,chID,"","BOOL",pParas->m_frActionTimebinIn[i].nSelect);
	}

	int nTimeZero[REPLAY_ACTIONTIMEZERO_COUNT] = {1,2,3,4};
	for(i = 0; i < REPLAY_ACTIONTIMEZERO_COUNT; i++)
	{
		sprintf(chName, "动作时间计时起点%d选择", nTimeZero[i]);
		sprintf(chID, "ActionTimeZero%ld", nTimeZero[i]);
		pXmlSierialize->xml_serialize(chName,chID,"s","number",pParas->m_frActionTimeZero[i]);
	}

	stt_xml_serialize_Exbinary_in(pParas->m_binInEx,pXmlSierialize);

	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
	stt_xml_serialize_Exbinary_out(pParas->m_binOutEx, pXmlSierialize);
}

#endif

void stt_xml_serialize_act_rcd(tmt_ReplayResult *pResult, CSttXmlSerializeBase *pXmlSierialize)//动作记录,最大64次,根据实际动作情况,上送总的动作信息
{
    CSttXmlSerializeBase *pXmlActRcddata = pXmlSierialize->xml_serialize("ActRcd", "ActRcd", "ActRcd", stt_ParaGroupKey());

    if (pXmlActRcddata == NULL)
    {
        return;
    }

    CString strName,strID,strTemp,strTmp2;
#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("开入");
    CString str2 = _T("第");
    CString str3 = _T("次动作时间");
#else
	CString str1 = /*_T("开入")*/g_sLangTxt_Native_BinX;
	CString str2 = /*_T("第")*/g_sLangTxt_Native_Number;
	CString str3 = /*_T("次动作时间")*/g_sLangTxt_Native_NActionTime;
#endif
    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"),nIndex+1);

        for (int nIndexAct = 0;((nIndexAct<64)&&(nIndexAct<pResult->m_nrBinSwitchCount[nIndex]));nIndexAct++)
        {
            strTmp2.Format(_T("%d"),nIndexAct+1);
            strName = str1 + strTemp + str2 + strTmp2 + str3;
            strID.Format("Bin%dActCount%d",(nIndex+1),(nIndexAct+1));
            pXmlActRcddata->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResult->m_frTimeBinAct[nIndex][nIndexAct]);
        }
    }

    if (g_nBinExCount>0)
    {
        CSttXmlSerializeBase *pXmlActRcdExdata = pXmlSierialize->xml_serialize("ActRcdEx", "ActRcdEx", "ActRcdEx", stt_ParaGroupKey());

        if (pXmlActRcdExdata == NULL)
        {
            return;
        }

        for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
        {
#ifdef NOT_USE_XLANGUAGE
            strTemp.Format(_T("扩展%d"),nIndex+1);
#else
			strTemp.Format(/*_T("扩展%d")*/g_sLangTxt_Native_extend.GetString(),nIndex+1);
#endif
            for (int nIndexAct = 0;((nIndexAct<64)&&(nIndexAct<pResult->m_nrBinExSwitchCount[nIndex]));nIndexAct++)
            {
                strTmp2.Format(_T("%d"),nIndexAct+1);
                strName = str1 + strTemp + str2 + strTmp2 + str3;
                strID.Format("BinEx%dActCount%d",(nIndex+1),(nIndexAct+1));
                pXmlActRcdExdata->xml_serialize(strName.GetString(),strID.GetString(),"","number",pResult->m_frTimeBinExAct[nIndex][nIndexAct]);
            }
        }
    }
}

void stt_xml_serialize(tmt_ReplayResult *pResult,  CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("实验触发时间","TestInTime","","number",pResult->m_fTestInTime);
#else
	pXmlSierialize->xml_serialize(/*"实验触发时间"*/g_sLangTxt_Native_ExpTrigTime.GetString(),"TestInTime","","number",pResult->m_fTestInTime);
#endif
    CString strName,strID,strTemp;
#ifdef NOT_USE_XLANGUAGE
    CString str1 = _T("开入");
    CString str2 = _T("结果状态");
    CString strDesc = _T("动作描述");
#else
	CString str1 = /*_T("开入")*/g_sLangTxt_Native_BinX;
	CString str2 = /*_T("结果状态")*/g_sLangTxt_Native_result_status;
	CString strDesc = /*_T("动作描述")*/g_sLangTxt_Native_ActionDesc;
#endif
    int nAct[MAX_BINARYIN_COUNT];
    int nCnt = get_xml_serialize_binary_count(pXmlSierialize);

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);
        strName = str1 + strTemp + str2;
        strID.Format("StateBin%d", (nIndex + 1));
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResult->m_nrBinSwitchCount[nIndex]);
    }

    if(g_nBinExCount > 0)
    {
        CSttXmlSerializeBase *pXmlStateBinEx = pXmlSierialize->xml_serialize("StateBinEx", "StateBinEx", "StateBinEx", stt_ParaGroupKey());

        if(pXmlStateBinEx != NULL)
        {
            for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
            {

#ifdef NOT_USE_XLANGUAGE
                strTemp.Format(_T("扩展%d"), nIndex + 1);
#else
		strTemp.Format(/*_T("扩展%d")*/g_sLangTxt_Native_extend.GetString(), nIndex + 1);
#endif
                strName = str1 + strTemp + str2;
                strID.Format("StateBinEx%d", (nIndex + 1));
                pXmlStateBinEx->xml_serialize(strName.GetString(), strID.GetString(), "", "number", pResult->m_nrBinExSwitchCount[nIndex]);
            }
        }
    }

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"),nIndex+1);
        strName = str1 + strTemp + strDesc;
        strID.Format("ActBin%d",(nIndex+1));
        nAct[nIndex] = (pResult->m_nrBinSwitchCount[nIndex] > 1);
        pXmlSierialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",nAct[nIndex]);
    }
#ifdef NOT_USE_XLANGUAGE
    str2 = _T("翻转时刻");
#else
	    str2 = /*_T("翻转时刻")*/g_sLangTxt_Native_FlipMoment;
#endif
    float fTtripBin;

    for(int nIndex = 0; nIndex < nCnt; nIndex++)
    {
        strTemp.Format(_T("%d"),nIndex+1);
        strName = str1 + strTemp + str2;
        strID.Format("TtripBin%d",(nIndex+1));
        fTtripBin = 0;

        if(nAct[nIndex] == 1)
        {
            fTtripBin = pResult->m_frTimeBinAct[nIndex][0] - pResult->m_fTestInTime;

            for(int i = 0;i < pResult->m_nrBinSwitchCount[nIndex];i++)
            {                
                if(pResult->m_frTimeBinAct[nIndex][i] > pResult->m_fTestInTime)
                {
                    fTtripBin = pResult->m_frTimeBinAct[nIndex][i] - pResult->m_fTestInTime;
                    break;
                }
            }
        }

        pXmlSierialize->xml_serialize(strName.GetString(),strID.GetString(),"","number",fTtripBin);
    }

    if (g_nBinExCount>0)
    {
#ifdef NOT_USE_XLANGUAGE
        CString str1Ex = _T("开入扩展");
#else
		CString str1Ex = /*_T("开入扩展")*/g_sLangTxt_Native_InputExpand;
#endif
        CSttXmlSerializeBase *pXmlBinEx = pXmlSierialize->xml_serialize("BinEx", "BinEx", "BinEx", stt_ParaGroupKey());

        if (pXmlBinEx != NULL)
        {
#ifdef NOT_USE_XLANGUAGE
            CString strDesc = _T("动作描述");
#else
		CString strDesc = /*_T("动作描述")*/g_sLangTxt_Native_ActionDesc;
#endif
            int nBinExCount = g_nBinExCount;//20230409 zhouhj
            int nAct[MAX_ExBINARY_COUNT];

            if (nBinExCount>MAX_ExBINARY_COUNT)
            {
                nBinExCount = MAX_ExBINARY_COUNT;
            }

            for(int nIndex = 0;nIndex<nBinExCount;nIndex++)
            {
                strTemp.Format(_T("%d"),nIndex+1);
                strName = str1Ex + strTemp + strDesc;
                strID.Format("ActBinEx%d",(nIndex+1));
                nAct[nIndex] = (pResult->m_nrBinExSwitchCount[nIndex] > 1);
                pXmlBinEx->xml_serialize(strName.GetString(),strID.GetString(),"","number",nAct[nIndex]);
            }

            float fTtripBinEx;

            for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
            {
                strTemp.Format(_T("%d"),nIndex+1);
                strName = str1Ex + strTemp + str2;
                strID.Format("TtripBinEx%d",(nIndex+1));
                fTtripBinEx = 0;

                if(nAct[nIndex] == 1)
                {
                    fTtripBinEx = pResult->m_frTimeBinExAct[nIndex][0] - pResult->m_fTestInTime;

                    for(int i = 0;i < pResult->m_nrBinExSwitchCount[nIndex];i++)
                    {
                        if(pResult->m_frTimeBinExAct[nIndex][i] > pResult->m_fTestInTime)
                        {
                            fTtripBinEx = pResult->m_frTimeBinExAct[nIndex][i] - pResult->m_fTestInTime;
                            break;
                        }
                    }
                }

                pXmlBinEx->xml_serialize(strName.GetString(),strID.GetString(),"","number",fTtripBinEx);
            }
        }
    }

    stt_xml_serialize_act_rcd(pResult,pXmlSierialize);
}

CSttXmlSerializeBase* stt_xml_serialize( tmt_ReplayTest *pTests, CSttXmlSerializeBase *pXmlSerialize, int nHasAnalogMode, int nHasDigitalMode, int nHasWeekMode )
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        stt_xml_serialize(&(pTests->m_oReplayParas),  pXmlParas,nHasAnalogMode,nHasDigitalMode,nHasWeekMode);	//文件的读写
    }

    CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
		stt_xml_serialize(&pTests->m_oReplayResult,  pXmlResults);
    }

    return pXmlParas;
}


#include"../../SttCmd/SttTestCmd.h"
#include"../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_ReplayTest()
{
    tmt_ReplayParas oReplayTest;
	oReplayTest.m_nModuleCount = 2;
	oReplayTest.m_oModule[0].m_nChUseCount = 6;
	oReplayTest.m_oModule[1].m_nChUseCount = 6;
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oReplayTest, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("ReplayTest.xml");
    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
