#include "stdafx.h"
#include "tmt_system_paras.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize(tmt_SystemParas *pSysParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("���������ģʽ", "DevOutputMode"," ","number",pSysParas->m_nOutputMode);
	pXmlSierialize->xml_serialize("���ѹֵ","NormVol","V","float",pSysParas->m_fVNom);
	pXmlSierialize->xml_serialize("�����ֵ", "NormCur","A","float",pSysParas->m_fINom);
	pXmlSierialize->xml_serialize("�Ƶ��", "NormFre","Hz","float",pSysParas->m_fFNom);
	pXmlSierialize->xml_serialize("����ʱ��","StabTime","s","float",pSysParas->m_fStabTime);
#else
  pXmlSierialize->xml_serialize(/* "���������ģʽ" */ g_sLangTxt_Native_TestOutMode.GetString(), "DevOutputMode", " ", "number", pSysParas->m_nOutputMode);
  pXmlSierialize->xml_serialize(/* "���ѹֵ" */ g_sLangTxt_Native_RatedVoltVal.GetString(), "NormVol", "V", "float", pSysParas->m_fVNom);
  pXmlSierialize->xml_serialize(/* "�����ֵ" */ g_sLangTxt_Native_RatedCurrVal.GetString(), "NormCur", "A", "float", pSysParas->m_fINom);
  pXmlSierialize->xml_serialize(/* "�Ƶ��" */ g_sLangTxt_Report_Fnom.GetString(), "NormFre", "Hz", "float", pSysParas->m_fFNom);
  pXmlSierialize->xml_serialize(/* "����ʱ��" */ g_sLangTxt_Report_AntiShakeTime.GetString(), "StabTime", "s", "float", pSysParas->m_fStabTime);
#endif
	CString strDesc;

	for (int nIndex = 0;nIndex<4;nIndex++)
	{
#ifdef NOT_USE_XLANGUAGE
		strDesc.Format("��%d��PTһ��ֵ",(nIndex+1));
		pXmlSierialize->xml_serialize(strDesc.GetString(),"PT_Primary","kV","float",pSysParas->m_fVPrimary[nIndex]);
		strDesc.Format("��%d��PT����ֵ",(nIndex+1));
		pXmlSierialize->xml_serialize(strDesc.GetString(),"PT_Secondary","V","float",pSysParas->m_fVSecondary[nIndex]);
		strDesc.Format("��%d��CTһ��ֵ",(nIndex+1));
		pXmlSierialize->xml_serialize(strDesc.GetString(),"CT_Primary","A","float",pSysParas->m_fIPrimary[nIndex]);
		strDesc.Format("��%d��CT����ֵ",(nIndex+1));
		pXmlSierialize->xml_serialize(strDesc.GetString(),"CT_Secondary","A","float",pSysParas->m_fISecondary[nIndex]);
#else
    strDesc.Format(/* "��%d��PTһ��ֵ" */ g_sLangTxt_Native_FirstPTVal, (nIndex + 1));
    pXmlSierialize->xml_serialize(strDesc.GetString(), "PT_Primary", "kV", "float", pSysParas->m_fVPrimary[nIndex]);
    strDesc.Format(/* "��%d��PT����ֵ" */ g_sLangTxt_Native_SecPTVal, (nIndex + 1));
    pXmlSierialize->xml_serialize(strDesc.GetString(), "PT_Secondary", "V", "float", pSysParas->m_fVSecondary[nIndex]);
    strDesc.Format(/* "��%d��CTһ��ֵ" */ g_sLangTxt_Native_FirstCTVal, (nIndex + 1));
    pXmlSierialize->xml_serialize(strDesc.GetString(), "CT_Primary", "A", "float", pSysParas->m_fIPrimary[nIndex]);
    strDesc.Format(/* "��%d��CT����ֵ" */ g_sLangTxt_Native_SecCTVal, (nIndex + 1));
    pXmlSierialize->xml_serialize(strDesc.GetString(), "CT_Secondary", "A", "float", pSysParas->m_fISecondary[nIndex]);
#endif
	}

#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("���������ʽ","PkgOutputMode"," ","number",pSysParas->m_nIecFormat);
	pXmlSierialize->xml_serialize("���ź��������","WSgnMode"," ","number",pSysParas->m_nWSgnMode);
	pXmlSierialize->xml_serialize("1588���չ��","Rev1588Port"," ","number",pSysParas->m_n588InPort);
	pXmlSierialize->xml_serialize("1588ͬ������","Syn1588"," ","number",pSysParas->m_n588Syn);
	pXmlSierialize->xml_serialize("��������ѡ��(0-һ��ֵ,1-����ֵ)","ParaSetMode"," ","number",pSysParas->m_nParaMode);
	pXmlSierialize->xml_serialize("�������ѡ��(0-һ��ֵ,1-����ֵ)","PkgOutSetMode"," ","number",pSysParas->m_nPkgOutMode);
	pXmlSierialize->xml_serialize("B���߼�(0-���߼�,1-���߼�)","BCodeMode"," ","number",pSysParas->m_nBCodeMode);
	pXmlSierialize->xml_serialize("�������ӷ�ʽ(0-˫��,1-����)","LoopMode"," ","number",pSysParas->m_nLoopMode);
#else
  pXmlSierialize->xml_serialize(/* "���������ʽ" */ g_sLangTxt_Native_MsgFormat.GetString(), "PkgOutputMode", " ", "number", pSysParas->m_nIecFormat);
  pXmlSierialize->xml_serialize(/* "���ź��������" */ g_sLangTxt_Native_WeakSigOutSet.GetString(), "WSgnMode", " ", "number", pSysParas->m_nWSgnMode);
  pXmlSierialize->xml_serialize(/* "1588���չ��" */ g_sLangTxt_Native_1588RecvOptPort.GetString(), "Rev1588Port", " ", "number", pSysParas->m_n588InPort);
  pXmlSierialize->xml_serialize(/* "1588ͬ������" */ g_sLangTxt_Native_1588SyncMech.GetString(), "Syn1588", " ", "number", pSysParas->m_n588Syn);
  pXmlSierialize->xml_serialize(/* "��������ѡ��(0-һ��ֵ,1-����ֵ)" */ g_sLangTxt_Native_ParamSel.GetString(), "ParaSetMode", " ", "number", pSysParas->m_nParaMode);
  pXmlSierialize->xml_serialize(/* "�������ѡ��(0-һ��ֵ,1-����ֵ)" */ g_sLangTxt_Native_MsgOutSel.GetString(), "PkgOutSetMode", " ", "number", pSysParas->m_nPkgOutMode);
  pXmlSierialize->xml_serialize(/* "B���߼�(0-���߼�,1-���߼�)" */ g_sLangTxt_Native_BCodeLogics.GetString(), "BCodeMode", " ", "number", pSysParas->m_nBCodeMode);
  pXmlSierialize->xml_serialize(/* "�������ӷ�ʽ(0-˫��,1-����)" */ g_sLangTxt_Native_FiberConn.GetString(), "LoopMode", " ", "number", pSysParas->m_nLoopMode);
#endif
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
