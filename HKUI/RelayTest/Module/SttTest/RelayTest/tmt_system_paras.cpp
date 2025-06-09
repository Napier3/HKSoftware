#include "stdafx.h"
#include "tmt_system_paras.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize(tmt_SystemParas *pSysParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("测试仪输出模式", "DevOutputMode"," ","number",pSysParas->m_nOutputMode);
    pXmlSierialize->xml_serialize("额定电压值","NormVol","V","float",pSysParas->m_fVNom);
    pXmlSierialize->xml_serialize("额定电流值", "NormCur","A","float",pSysParas->m_fINom);
    pXmlSierialize->xml_serialize("额定频率", "NormFre","Hz","float",pSysParas->m_fFNom);
    pXmlSierialize->xml_serialize("防抖时间","StabTime","s","float",pSysParas->m_fStabTime);

    CString strDesc;

	for (int nIndex = 0;nIndex<4;nIndex++)
	{
        strDesc.Format("第%d组PT一次值",(nIndex+1));
        pXmlSierialize->xml_serialize(strDesc.GetString(),"PT_Primary","kV","float",pSysParas->m_fVPrimary[nIndex]);
        strDesc.Format("第%d组PT二次值",(nIndex+1));
        pXmlSierialize->xml_serialize(strDesc.GetString(),"PT_Secondary","V","float",pSysParas->m_fVSecondary[nIndex]);
        strDesc.Format("第%d组CT一次值",(nIndex+1));
        pXmlSierialize->xml_serialize(strDesc.GetString(),"CT_Primary","A","float",pSysParas->m_fIPrimary[nIndex]);
        strDesc.Format("第%d组CT二次值",(nIndex+1));
        pXmlSierialize->xml_serialize(strDesc.GetString(),"CT_Secondary","A","float",pSysParas->m_fISecondary[nIndex]);
	}
	
	pXmlSierialize->xml_serialize("报文输出格式","PkgOutputMode"," ","number",pSysParas->m_nIecFormat);
	pXmlSierialize->xml_serialize("弱信号输出设置","WSgnMode"," ","number",pSysParas->m_nWSgnMode);
	pXmlSierialize->xml_serialize("1588接收光口","Rev1588Port"," ","number",pSysParas->m_n588InPort);
	pXmlSierialize->xml_serialize("1588同步机制","Syn1588"," ","number",pSysParas->m_n588Syn);
	pXmlSierialize->xml_serialize("参数设置选择(0-一次值,1-二次值)","ParaSetMode"," ","number",pSysParas->m_nParaMode);
	pXmlSierialize->xml_serialize("报文输出选择(0-一次值,1-二次值)","PkgOutSetMode"," ","number",pSysParas->m_nPkgOutMode);
	pXmlSierialize->xml_serialize("B码逻辑(0-正逻辑,1-负逻辑)","BCodeMode"," ","number",pSysParas->m_nBCodeMode);
	pXmlSierialize->xml_serialize("光纤连接方式(0-双回,1-单回)","LoopMode"," ","number",pSysParas->m_nLoopMode);

}


#include"../../SttCmd/SttSystemCmd.h"
#include"../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_SystemParas()
{
    tmt_SystemParas oSystemParas;
    oSystemParas.init();
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttSystemCmd oSttSystemCmd;
    CSttParas *pParas = oSttSystemCmd.GetSttParas();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttSystemCmd);
 //   CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetParas();
    stt_xml_serialize(&oSystemParas, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath.append("SystemParasDemo.xml");
//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
