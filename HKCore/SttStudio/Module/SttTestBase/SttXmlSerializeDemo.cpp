#include "stdafx.h"
#include "SttXmlSerializeDemo.h"

#include "../SttCmd/SttTestCmd.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


void stt_init_paras(STT_XMLSERIALIZE_CHANNEL &oChannel, float fMag, float fAng, float fFreq)
{
	oChannel.fMag = fMag;
	oChannel.fAng = fAng;
	oChannel.fFreq = fFreq;
}

void stt_init_paras(STT_XMLSERIALIZE_STATE &oState)
{
	stt_init_paras(oState.UI[0], 57.735f, 0.0f, 50.0f);
	stt_init_paras(oState.UI[1], 57.735f, -120.0f, 50.0f);
	stt_init_paras(oState.UI[2], 57.735f, 120.0f, 50.0f);
	stt_init_paras(oState.UI[3], 0.0f, 0.0f, 50.0f);
	stt_init_paras(oState.UI[4], 0.0f, -120.0f, 50.0f);
	stt_init_paras(oState.UI[5], 0.0f, 120.0f, 50.0f);
}

void stt_init_paras(STT_XMLSERIALIZE_STATETEST &oStateTest)
{
	memset(&oStateTest, 0, sizeof(STT_XMLSERIALIZE_STATETEST));
	oStateTest.nStateCount = 1;

	long nIndex = 0;

	for (nIndex=0; nIndex<STT_XMLSERIALIZE_STATE_MAX; nIndex++)
	{
		stt_init_paras(oStateTest.state[nIndex]);
	}
}

//////////////////////////////////////////////////////////////////////////
//
void xml_serialize(STT_XMLSERIALIZE_CHANNEL &oChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pChannel =pXmlSierialize->xml_serialize(pszID, pszID, "channel", stt_ParaGroupKey());

	if (pChannel == NULL)
	{
		return;
	}

	pChannel->xml_serialize("幅值", "mag", "", "float", oChannel.fMag);
	pChannel->xml_serialize("相位", "ang", "", "float",  oChannel.fAng);
	pChannel->xml_serialize("频率", "freq", "", "float", oChannel.fFreq);
}

void xml_serialize(STT_XMLSERIALIZE_STATE &oState, long nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pState =pXmlSierialize->xml_serialize("状态", "state", nIndex, "State", stt_ParaGroupKey());

	if (pState == NULL)
	{
		return;
	}

	pState->xml_serialize("MaxTime", "MaxTime", "", "float", oState.fMaxTime);
	
	xml_serialize(oState.UI[0], "Ua", pState);
	xml_serialize(oState.UI[1], "Ub", pState);
	xml_serialize(oState.UI[2], "Uc", pState);
	xml_serialize(oState.UI[3], "Ia", pState);
	xml_serialize(oState.UI[4], "Ib", pState);
	xml_serialize(oState.UI[5], "Ic", pState);
}

void xml_serialize(STT_XMLSERIALIZE_STATETEST &oStateTest, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("StateCount", "StateCount", "", "int", oStateTest.nStateCount);

	long nIndex = 0;

	for (nIndex=0; nIndex<STT_XMLSERIALIZE_STATE_MAX; nIndex++)
	{
		xml_serialize(oStateTest.state[nIndex], nIndex, pXmlSierialize);
	}
}

//////////////////////////////////////////////////////////////////////////
//
STT_XMLSERIALIZE_STATETEST g_oStateTestDemo;

void xml_serialize_read_demo()
{
	CSttXmlSerializeTool oSttXmlSerializeTool;
	char *pszXmlData = "0123456789abcde<test-cmd name=\"\" id=\"StartTest\"><macro name=\"state\" id=\"state\"><paras><data name=\"StateCount\" id=\"StateCount\" value=\"4\"/><group id=\"state1\"><group id=\"Ua\"><data id=\"mag\" value=\"57.735\"/><data id=\"ang\" value=\"0\"/><data id=\"freq\" value=\"50\"/></group><group id=\"Ub\"><data id=\"mag\" value=\"57.735\"/><data id=\"ang\" value=\"-120\"/><data id=\"freq\" value=\"50\"/></group></group><group id=\"state3\"><group id=\"Ia\"><data id=\"mag\" value=\"5\"/></group><group id=\"Ic\"><data id=\"mag\" value=\"6\"/><data id=\"ang\" value=\"60\"/></group></group></paras></macro></test-cmd>";
	CSttTestCmd m_oSttTestCmd;
    m_oSttTestCmd.SetCreateMacroChild(false);
	char *pszPkgXml = m_oSttTestCmd.ParsePkgOnly((BYTE*)pszXmlData);
	oSttXmlSerializeTool.CreateXmlSerializeRead(&m_oSttTestCmd, pszPkgXml,sizeof(pszXmlData));
	CSttMacro *pSttMacro = m_oSttTestCmd.GetSttMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	memset(&g_oStateTestDemo, 0, sizeof(STT_XMLSERIALIZE_STATETEST));
	xml_serialize(g_oStateTestDemo, pMacroParas);
}

void xml_serialize_write_demo()
{
	stt_init_paras(g_oStateTestDemo);
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	xml_serialize(g_oStateTestDemo, pMacroParas);

	oSttXmlSerializeTool.Stt_WriteFile(_T("d:\\Stt_State.xml"));
}


void xml_serialize_register_demo()
{

}

