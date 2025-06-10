#include "stdafx.h"
#include "tmt_diff_cbop_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif


void stt_init_paras(tmt_DiffCBOpParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DiffCBOpParas));
	pParas->init();
}

void stt_init_results(tmt_DiffCBOpResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DiffCBOpResults));
    pResults->init();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize(tmt_DiffCBOpParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("故障类型","FaultType","","number",pParas->m_nFaultType);
	pXmlSierialize->xml_serialize("故障点位置","FaultLocation","","number",pParas->m_nFaultLocation);
	pXmlSierialize->xml_serialize("误差类型","ErrorType","","number",pParas->m_nErrorType);
	pXmlSierialize->xml_serialize("电流(A)","Current","","number",pParas->m_fCurrent);
	pXmlSierialize->xml_serialize("频率(Hz)","Freq","","number",pParas->m_fFreq);
    pXmlSierialize->xml_serialize("第一组电压常态输出值","Vg1","V","number",pParas->m_fVg1);
    pXmlSierialize->xml_serialize("第二组电压常态输出值","Vg2","V","number",pParas->m_fVg2);

    pXmlSierialize->xml_serialize("变压器额定容量", "SN", "", "number", pParas->m_fSN);
    pXmlSierialize->xml_serialize("设置平衡系数", "Kcal", "", "number", pParas->m_nKcal);

	pXmlSierialize->xml_serialize("变压器高压侧平衡系数", "Kph", "","number",pParas->m_fKph);
	pXmlSierialize->xml_serialize("变压器高压侧额定电压", "Uh", "","number",pParas->m_fUh);
    pXmlSierialize->xml_serialize("变压器高压侧额定电流", "Inh", "","number",pParas->m_fInh);
    pXmlSierialize->xml_serialize("变压器高压侧CT变比", "CTh", "","number",pParas->m_fCTh);

	pXmlSierialize->xml_serialize("变压器中压侧平衡系数","Kpm","","number",pParas->m_fKpm);
	pXmlSierialize->xml_serialize("变压器中压侧额定电压", "Um", "","number",pParas->m_fUm);
    pXmlSierialize->xml_serialize("变压器中压侧额定电流", "Inm", "","number",pParas->m_fInm);
    pXmlSierialize->xml_serialize("变压器中压侧CT变比","CTm","","number",pParas->m_fCTm);

    pXmlSierialize->xml_serialize("变压器低压侧平衡系数","Kpl","","number",pParas->m_fKpl);
    pXmlSierialize->xml_serialize("变压器低压侧额定电压", "Ul", "","number",pParas->m_fUl);
    pXmlSierialize->xml_serialize("变压器低压侧额定电流", "Inl", "","number",pParas->m_fInl);
    pXmlSierialize->xml_serialize("变压器低压侧CT变比","CTl","","number",pParas->m_fCTl);

	pXmlSierialize->xml_serialize("绝对误差(S) +", "AbsErrSum", "","number",pParas->m_fAbsErrSum);
	pXmlSierialize->xml_serialize("绝对误差(S) -", "AbsErrReduce", "","number",pParas->m_fAbsErrReduce);
	pXmlSierialize->xml_serialize("相对误差", "RelErr", "", "number", pParas->m_fRelErr);

	pXmlSierialize->xml_serialize("准备时间", "PrepareTime", "","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("故障前时间", "PreFaultTime", "","number",pParas->m_fPreFaultTime);
    pXmlSierialize->xml_serialize("故障时间", "FaultTime", "","number",pParas->m_fFaultTime);
	pXmlSierialize->xml_serialize("故障时间裕度", "FaultTimeMargin", "","number",pParas->m_fFaultTimeMargin);
    pXmlSierialize->xml_serialize("动作后保持时间", "ActionHoldTime", "","number",pParas->m_fActionHoldTime);
    pXmlSierialize->xml_serialize("高压侧绕组接线型式","WindH","","DiffConnectMode",pParas->m_nWindH);
    pXmlSierialize->xml_serialize("中压侧绕组接线型式","WindM","","DiffConnectMode",pParas->m_nWindM);
    pXmlSierialize->xml_serialize("低压侧绕组接线型式","WindL","","DiffConnectMode",pParas->m_nWindL);
    pXmlSierialize->xml_serialize("参与试验的绕组","AdoptWind","","TransHMLSel",pParas->m_nWindSide);
    pXmlSierialize->xml_serialize("保护内部相位校正方式","PhCorrectMode","","TransPhCorrectModePnv",pParas->m_nAngleMode);
    pXmlSierialize->xml_serialize("高-中绕组钟点数", "AroundClockNumHM", "","number",pParas->m_nAroundClockNumHM);
    pXmlSierialize->xml_serialize("高-低绕组钟点数", "AroundClockNumHL", "", "number", pParas->m_nAroundClockNumHL);
    pXmlSierialize->xml_serialize("平衡系数计算", "BalanceTerms", "","number",pParas->m_nBalanceTerms);
	pXmlSierialize->xml_serialize("CT极性", "CTStarPoint", "","number",pParas->m_bCTStarPoint);
	pXmlSierialize->xml_serialize("制动方程", "IbiasCal", "", "number", pParas->m_nIbiasCal);
	pXmlSierialize->xml_serialize("K1","Factor1","","number",pParas->m_fFactor1);
	pXmlSierialize->xml_serialize("K2", "Factor2", "","number",pParas->m_fFactor2);
	pXmlSierialize->xml_serialize("组合特性", "ComBineFeature", "","long",pParas->m_nComBineFeature);

	pXmlSierialize->xml_serialize("接地","Earthing","","number",pParas->m_nEarthing);
	pXmlSierialize->xml_serialize("断路器模拟  S1=不模拟,S2=模拟 0(0:不模拟,1:模拟)","CBSimulation","","",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize("分闸时间","CBTripTime","","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize("合闸时间","CBCloseTime","","number",pParas->m_fCBCloseTime);
	pXmlSierialize->xml_serialize("坐标","Coordinate","","number",pParas->m_nCoordinate);
    pXmlSierialize->xml_serialize("基准电流选择", "InSel", "", "CurrentSelPnv", pParas->m_nInSel);
    pXmlSierialize->xml_serialize("基准电流设定值", "InSet", "A", "number", pParas->m_fIbase);

	pXmlSierialize->xml_serialize("开入A","A","","DInputState",pParas->m_binIn[0]);
	pXmlSierialize->xml_serialize("开入B","B","","DInputState",pParas->m_binIn[1]);
	pXmlSierialize->xml_serialize("开入C","C","","DInputState",pParas->m_binIn[2]);
	pXmlSierialize->xml_serialize("开入R","R","","DInputState",pParas->m_binIn[3]);
	pXmlSierialize->xml_serialize("开入E","E","","DInputState",pParas->m_binIn[4]);
	pXmlSierialize->xml_serialize("开入F","F","","DInputState",pParas->m_binIn[5]);
	pXmlSierialize->xml_serialize("开入G","G","","DInputState",pParas->m_binIn[6]);
	pXmlSierialize->xml_serialize("开入H","H","","DInputState",pParas->m_binIn[7]);
    pXmlSierialize->xml_serialize("开入逻辑", "_AndOr", "","number",pParas->m_nBinLogic);

	pXmlSierialize->xml_serialize("常态开出1状态","_B01","","DOutputState",pParas->m_binOut[0][0]);
	pXmlSierialize->xml_serialize("常态开出2状态","_B02","","DOutputState",pParas->m_binOut[0][1]);
	pXmlSierialize->xml_serialize("常态开出3状态","_B03","","DOutputState",pParas->m_binOut[0][2]);
	pXmlSierialize->xml_serialize("常态开出4状态","_B04","","DOutputState",pParas->m_binOut[0][3]);
	pXmlSierialize->xml_serialize("常态开出5状态","_B05","","DOutputState",pParas->m_binOut[0][4]);
	pXmlSierialize->xml_serialize("常态开出6状态","_B06","","DOutputState",pParas->m_binOut[0][5]);
	pXmlSierialize->xml_serialize("常态开出7状态","_B07","","DOutputState",pParas->m_binOut[0][6]);
	pXmlSierialize->xml_serialize("常态开出8状态","_B08","","DOutputState",pParas->m_binOut[0][7]);
	pXmlSierialize->xml_serialize("故障态开出1状态","_FaultB01","","DOutputState",pParas->m_binOut[1][0]);
	pXmlSierialize->xml_serialize("故障态开出2状态","_FaultB02","","DOutputState",pParas->m_binOut[1][1]);
	pXmlSierialize->xml_serialize("故障态开出3状态","_FaultB03","","DOutputState",pParas->m_binOut[1][2]);
	pXmlSierialize->xml_serialize("故障态开出4状态","_FaultB04","","DOutputState",pParas->m_binOut[1][3]);
	pXmlSierialize->xml_serialize("故障态开出5状态","_FaultB05","","DOutputState",pParas->m_binOut[1][4]);
	pXmlSierialize->xml_serialize("故障态开出6状态","_FaultB06","","DOutputState",pParas->m_binOut[1][5]);
	pXmlSierialize->xml_serialize("故障态开出7状态","_FaultB07","","DOutputState",pParas->m_binOut[1][6]);
	pXmlSierialize->xml_serialize("故障态开出8状态","_FaultB08","","DOutputState",pParas->m_binOut[1][7]);


#else
	pXmlSierialize->xml_serialize("故障类型","FaultType","","number",pParas->m_nFaultType);
	pXmlSierialize->xml_serialize("误差类型","ErrorType","","number",pParas->m_nErrorType);
	pXmlSierialize->xml_serialize("故障点位置","FaultLocation","","number",pParas->m_nFaultLocation);
	pXmlSierialize->xml_serialize("电流(A)","Current","","number",pParas->m_fCurrent);
	pXmlSierialize->xml_serialize("频率(Hz)","Freq","","number",pParas->m_fFreq);

	pXmlSierialize->xml_serialize("变压器高压侧平衡系数", "Kph", "","number",pParas->m_fKph);
	pXmlSierialize->xml_serialize("变压器高压侧额定电压", "Uh", "","number",pParas->m_fUh);
	pXmlSierialize->xml_serialize("变压器高压侧额定电流", "TransfHvCur", "","number",pParas->m_fTransfHvCur);
	pXmlSierialize->xml_serialize("变压器高压侧CT变比", "TransfHvCT", "","number",pParas->m_fTransfHvCT);
	pXmlSierialize->xml_serialize("变压器高压侧额定容量", "TransfHvKVA", "", "number", pParas->m_fTransfHvKVA);

	pXmlSierialize->xml_serialize("变压器中压侧平衡系数","Kpm","","number",pParas->m_fKpm);
	pXmlSierialize->xml_serialize("变压器中压侧额定电压", "Um", "","number",pParas->m_fUm);
	pXmlSierialize->xml_serialize("变压器中压侧额定电流", "TransfMvCur", "","number",pParas->m_fTransfMvCur);
	pXmlSierialize->xml_serialize("变压器中压侧CT变比","TransfMvCT","","number",pParas->m_fTransfMvCT);

	pXmlSierialize->xml_serialize("变压器低压侧额定容量", "Kpl", "", "number",  pParas->m_fTransfLvKpl);
	pXmlSierialize->xml_serialize("变压器低压侧平衡系数","Ul","","number",pParas->m_fKpl);
	pXmlSierialize->xml_serialize("变压器低压侧额定电压", "TransfLvCur", "","number",pParas->m_fUl);
	pXmlSierialize->xml_serialize("变压器低压侧额定电流", "TransfLvCT", "","number",pParas->m_fTransfLvCT);

	pXmlSierialize->xml_serialize("绝对误差(S) +", "AbsErrSum", "","number",pParas->m_fAbsErrSum);
	pXmlSierialize->xml_serialize("绝对误差(S) -", "AbsErrReduce", "","number",pParas->m_fAbsErrReduce);
	pXmlSierialize->xml_serialize("相对误差", "RelErr", "", "number", pParas->m_fRelErr);

	pXmlSierialize->xml_serialize("准备时间", "PrepareTime", "","number",pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("故障前时间", "PreFaultTime", "","number",pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("故障时间裕度", "FaultTimeMargin", "","number",pParas->m_fFaultTimeMargin);
	pXmlSierialize->xml_serialize("高-中绕组钟点数", "AroundClockNumHM", "","number",pParas->m_fActionHoldTime);
	pXmlSierialize->xml_serialize("高-低绕组钟点数", "AroundClockNumHL", "", "number", pParas->m_nAroundClockNumHM);
	pXmlSierialize->xml_serialize("平衡系数计算", "BalanceTerms", "","number",pParas->m_nAroundClockNumHL);
	pXmlSierialize->xml_serialize("CT极性", "CTStarPoint", "","number",pParas->m_bCTStarPoint);
	pXmlSierialize->xml_serialize("制动方程", "IbiasCal", "", "number", pParas->m_nIbiasCal);
	pXmlSierialize->xml_serialize("K1","Factor1","","number",pParas->m_fFactor1);
	pXmlSierialize->xml_serialize("K2", "Factor2", "","number",pParas->m_fFactor2);
	pXmlSierialize->xml_serialize("组合特性", "ComBineFeature", "","long",pParas->m_nComBineFeature);

	pXmlSierialize->xml_serialize("接地","Earthing","","number",pParas->m_nEarthing);
	pXmlSierialize->xml_serialize("断路器模拟  S1=不模拟,S2=模拟 0(0:不模拟,1:模拟)","CBSimulation","","",pParas->m_bCBSimulation);
	pXmlSierialize->xml_serialize("分闸时间","CBTripTime","","number",pParas->m_fCBTripTime);
	pXmlSierialize->xml_serialize("合闸时间","CBCloseTime","","number",pParas->m_fCBCloseTime);
	pXmlSierialize->xml_serialize("坐标","Coordinate","","number",pParas->m_nCoordinate);

	pXmlSierialize->xml_serialize("开入A","A","","DInputState",pParas->m_binIn[0]);
	pXmlSierialize->xml_serialize("开入B","B","","DInputState",pParas->m_binIn[1]);
	pXmlSierialize->xml_serialize("开入C","C","","DInputState",pParas->m_binIn[2]);
	pXmlSierialize->xml_serialize("开入R","R","","DInputState",pParas->m_binIn[3]);
	pXmlSierialize->xml_serialize("开入E","E","","DInputState",pParas->m_binIn[4]);
	pXmlSierialize->xml_serialize("开入F","F","","DInputState",pParas->m_binIn[5]);
	pXmlSierialize->xml_serialize("开入G","G","","DInputState",pParas->m_binIn[6]);
	pXmlSierialize->xml_serialize("开入H","H","","DInputState",pParas->m_binIn[7]);
	pXmlSierialize->xml_serialize("开入逻辑", "BinLogic", "","number",pParas->m_nBinLogic);

	pXmlSierialize->xml_serialize("常态开出1状态","_B01","","DOutputState",pParas->m_binOut[0][0]);
	pXmlSierialize->xml_serialize("常态开出2状态","_B02","","DOutputState",pParas->m_binOut[0][1]);
	pXmlSierialize->xml_serialize("常态开出3状态","_B03","","DOutputState",pParas->m_binOut[0][2]);
	pXmlSierialize->xml_serialize("常态开出4状态","_B04","","DOutputState",pParas->m_binOut[0][3]);
	pXmlSierialize->xml_serialize("常态开出5状态","_B05","","DOutputState",pParas->m_binOut[0][4]);
	pXmlSierialize->xml_serialize("常态开出6状态","_B06","","DOutputState",pParas->m_binOut[0][5]);
	pXmlSierialize->xml_serialize("常态开出7状态","_B07","","DOutputState",pParas->m_binOut[0][6]);
	pXmlSierialize->xml_serialize("常态开出8状态","_B08","","DOutputState",pParas->m_binOut[0][7]);
	pXmlSierialize->xml_serialize("故障态开出1状态","_FaultB01","","DOutputState",pParas->m_binOut[1][0]);
	pXmlSierialize->xml_serialize("故障态开出2状态","_FaultB02","","DOutputState",pParas->m_binOut[1][1]);
	pXmlSierialize->xml_serialize("故障态开出3状态","_FaultB03","","DOutputState",pParas->m_binOut[1][2]);
	pXmlSierialize->xml_serialize("故障态开出4状态","_FaultB04","","DOutputState",pParas->m_binOut[1][3]);
	pXmlSierialize->xml_serialize("故障态开出5状态","_FaultB05","","DOutputState",pParas->m_binOut[1][4]);
	pXmlSierialize->xml_serialize("故障态开出6状态","_FaultB06","","DOutputState",pParas->m_binOut[1][5]);
	pXmlSierialize->xml_serialize("故障态开出7状态","_FaultB07","","DOutputState",pParas->m_binOut[1][6]);
	pXmlSierialize->xml_serialize("故障态开出8状态","_FaultB08","","DOutputState",pParas->m_binOut[1][7]);
#endif

}

void stt_xml_serialize(tmt_DiffCBOpResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSierialize->xml_serialize("动作时间", "TripTime", "s", "number",pResults->m_fTripTime);
    pXmlSierialize->xml_serialize("动作描述","ActFlag","","number",pResults->m_nActFlag);
#else
  pXmlSierialize->xml_serialize(/* "动作时间" */ g_sLangTxt_Gradient_ActionTime.GetString(), "TripTime", "s", "number", pResults->m_fTripTime);
  pXmlSierialize->xml_serialize(/* "动作描述" */ g_sLangTxt_Native_ActionDesc.GetString(), "ActFlag", "", "number", pResults->m_nActFlag);
#endif
}
CSttXmlSerializeBase* stt_xml_serialize( tmt_diff_cbop_Test *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

    if (pXmlParas != NULL)
    {
        stt_xml_serialize(&(pTests->m_oDiffProtectionParas),  pXmlParas);	//文件的读写
    }

    CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

    if (pXmlResults != NULL)
    {
        stt_xml_serialize(&pTests->m_oDiffProtectionResults,  pXmlResults);
    }

    return pXmlParas;
}

#include"../../../SttCmd/SttTestCmd.h"
#include"../../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_DiffCBOp()
{
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	//stt_xml_serialize(&oReplayTest, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("ReplayTest.xml");
	pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);
	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

