#include "stdafx.h"
#include "tmt_shake_test.h"

void stt_init_paras(tmt_ShakeParas *pParas)
{
    memset(&pParas, 0, sizeof(tmt_ShakeParas));
    pParas->init();
}

void stt_init_results(tmt_ShakeResults *pResults)
{
    memset(&pResults, 0, sizeof(tmt_ShakeResults));
    pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
///
///
///
///
///

void stt_xml_serialize_binary_out(tmt_BinaryOut *pOutPara, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pOutSerialize =pXmlSierialize->xml_serialize("����", "BOout", "BOUT", stt_ParaGroupKey());

    if (pOutSerialize == NULL)
    {
        return;
    }

    pOutSerialize->xml_serialize("������ת��ʱ","BoutDelayT","s","number", pOutPara[0].fTimeTrig);

    CString strName, strID;
    for(int nIndex = 0;nIndex<8;nIndex++)
    {
        strName.Format("����%d״̬",(nIndex+1));
        strID.Format("Bout%dState");
        pOutSerialize->xml_serialize(strName.GetString(),strID.GetString(),"","DOutputState", pOutPara[nIndex].nState);
    }
}

void stt_xml_serialize_fault_set(tmt_ShakeParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pFaultSetSerialize =pXmlSierialize->xml_serialize("��������", "FaultSet", "FaultSet", stt_ParaGroupKey());

    if (pFaultSetSerialize == NULL)
    {
        return;
    }

    pFaultSetSerialize->xml_serialize("��������","FaultType","","FaultType", pParas->m_nFaultType);
    pFaultSetSerialize->xml_serialize("��·�迹","FaultImp","","number", pParas->m_fImpedance);
    pFaultSetSerialize->xml_serialize("���ϵ���","FaultCur","","number", pParas->m_fFaultCur);
    pFaultSetSerialize->xml_serialize("���Ϸ���ʱ��","FaultTime","","number", pParas->m_fFaultTime);
    pFaultSetSerialize->xml_serialize("��﷽ʽ","K0Mode","","K0Mode", pParas->m_nK0Mode);
    pFaultSetSerialize->xml_serialize("���򲹳�����ϵ��Kr","Kr","","number", pParas->m_fKoOrRe);
    pFaultSetSerialize->xml_serialize("������λ����ϵ��Kx","Kx","","number", pParas->m_fPhiOrIm);
}

void stt_xml_serialize_common_set(tmt_ShakeParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pCommonSetSerialize =pXmlSierialize->xml_serialize("ͨ�ò���", "CommonSet", "CommonSet", stt_ParaGroupKey());

    if (pCommonSetSerialize == NULL)
    {
        return;
    }

    pCommonSetSerialize->xml_serialize("��ߵ�ѹ","Unom","","number", pParas->oCommonPara.m_fUNom);
    pCommonSetSerialize->xml_serialize("�����","Inom","","number", pParas->oCommonPara.m_fINom);
    pCommonSetSerialize->xml_serialize("�Ƶ��","Fnom","","number", pParas->oCommonPara.m_fFreqNom);
    pCommonSetSerialize->xml_serialize("��ǰʱ��","PreShakeTime","","number", pParas->m_fPreFaultTime);
    pCommonSetSerialize->xml_serialize("TA������","TA","","TA", (int &)pParas->m_nCTPoint);
    pCommonSetSerialize->xml_serialize("ϵͳ���迹|Zs|","ZS","","number", pParas->m_fZS);
    pCommonSetSerialize->xml_serialize("ϵͳ���迹��(Zs)","PhiZs","","number", pParas->m_fPhisS);
    pCommonSetSerialize->xml_serialize("��ѹ���迹|Zt|","ZT","","K0Mode", pParas->m_fZT);
    pCommonSetSerialize->xml_serialize("��ѹ���迹��(Zt)","PhiZt","","number", pParas->m_fPhisT);
    pCommonSetSerialize->xml_serialize("�������̬�翹","XD","","number", pParas->m_fXD);
}

void stt_xml_serialize(tmt_ShakeParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("����ʼֵ", "AngleStart"," ","number",pParas->m_fPowerAngStart);
    pXmlSierialize->xml_serialize("������ֵ","AngleEnd","","number",pParas->m_fPowerAngEnd);
    pXmlSierialize->xml_serialize("������", "ShakeCycle","","number",pParas->m_fCycle);
    pXmlSierialize->xml_serialize("�񵴴���", "ShakeNum"," ","number",pParas->m_nShakeNum);
    pXmlSierialize->xml_serialize("EMEN","EMEN","","number",pParas->m_fRate);
    pXmlSierialize->xml_serialize("��բ�ӵ�", "TripPt"," ","TripPt",(int &)pParas->m_nTripPt);
    pXmlSierialize->xml_serialize("�����źŽӵ�","SpdupPt","","SpdupPt",(int &)pParas->m_nTripSpeedupPt);
    pXmlSierialize->xml_serialize("�����źŽӵ�", "SpddnPt","","SpddnPt",(int &)pParas->m_nTripSpeedDnPt);
    pXmlSierialize->xml_serialize("Ƶ��", "Freq"," ","number",pParas->m_fFreq);

    pXmlSierialize->xml_serialize("�Ƿ�DZDT", "bDZDT"," ","BOOL",pParas->m_bDzDt);
    pXmlSierialize->xml_serialize("DZDT","DZDT","","number",pParas->m_fDzDt);
    pXmlSierialize->xml_serialize("������", "bReciprocate","","BOOL",pParas->m_bReciprocating);
    pXmlSierialize->xml_serialize("������", "bAccelerate"," ","BOOL",pParas->m_bAccelerate);
    pXmlSierialize->xml_serialize("�����ٹ���","bExtarFault","","BOOL",pParas->m_bExtraFault);

    stt_xml_serialize_fault_set(pParas, pXmlSierialize);
    stt_xml_serialize_common_set(pParas, pXmlSierialize);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include"../../SttCmd/SttTestCmd.h"
#include"tmt_shake_test.h"
#include"../../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_ShakeTest()
{
    tmt_ShakeTest oShakeTest;
    oShakeTest.init();
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oShakeTest.m_oShakeParas, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("ShakeTest.xml");
//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
