#include "stdafx.h"
#include "tmt_dc_failureprot_test.h"
// #ifdef NOT_USE_XLANGUAGE
// #else
//#include "../../../XLangResource_Native.h"                              

/*#endif*/

void stt_init_paras(tmt_DCFailureProtParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_DCFailureProtParas));
	pParas->init();
}

void stt_init_results(tmt_DCFailureProtResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_DCFailureProtResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize_Common(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("��α仯��������ֵ" , "DidtActValue", "number", "string",  pParas->m_fActValue_Setting[1]);
	pXmlSierialize->xml_serialize("��ζ���ʱ��" , "DidtActTime", "��", "number",  pParas->m_fActTime_Setting[1]);
	pXmlSierialize->xml_serialize("��ζ���������ֵ" , "ActValue", "��", "number",  pParas->m_fActValue_Setting[0]);
	pXmlSierialize->xml_serialize("��ζ���ʱ��" , "ActTime", "��", "number",  pParas->m_fActTime_Setting[0]);

	pXmlSierialize->xml_serialize("����ǰʱ��" , "PreDowntime", "��", "number",  pParas->m_fPreFaultTime);
	pXmlSierialize->xml_serialize("����ʱ��ԣ��" , "MarginTime", "��", "number",  pParas->m_fMarginTime);
	pXmlSierialize->xml_serialize("����ǰ��ѹ" , "PreFaultVoltage", "��", "number",  pParas->m_fPreFaultVol);
	pXmlSierialize->xml_serialize("����ǰ����" , "PreFaultCurrent", "��", "number",  pParas->m_fPreFaultCur);
	//pXmlSierialize->xml_serialize("����ʱ��" , "Holdtime", "��", "number",  pParas->m_fHoldTime);
	pXmlSierialize->xml_serialize("����ͨ��ѡ��" , "CurChanSelect", "��", "number",  pParas->m_nIChanSelect);
	pXmlSierialize->xml_serialize("����Aѡ��" , "_BinSelectA", "��", "BOOL",  pParas->m_binIn[0].nSelect);
	pXmlSierialize->xml_serialize("����Bѡ��" , "_BinSelectB", "��", "BOOL",  pParas->m_binIn[1].nSelect);
	pXmlSierialize->xml_serialize("����Cѡ��" , "_BinSelectC", "��", "BOOL",  pParas->m_binIn[2].nSelect);
	pXmlSierialize->xml_serialize("����Dѡ��" , "_BinSelectD", "��", "BOOL",  pParas->m_binIn[3].nSelect);
	pXmlSierialize->xml_serialize("����Eѡ��" , "_BinSelectE", "��", "BOOL",  pParas->m_binIn[4].nSelect);
	pXmlSierialize->xml_serialize("����Fѡ��" , "_BinSelectF", "��", "BOOL",  pParas->m_binIn[5].nSelect);
	pXmlSierialize->xml_serialize("����Gѡ��" , "_BinSelectG", "��", "BOOL",  pParas->m_binIn[6].nSelect);
	pXmlSierialize->xml_serialize("����Hѡ��" , "_BinSelectH", "��", "BOOL",  pParas->m_binIn[7].nSelect);
	pXmlSierialize->xml_serialize("�߼�ѡ��" , "LogicSelect", "��", "BOOL",   pParas->m_nBinLogic);
    pXmlSierialize->xml_serialize("����1״̬" , "_BoutSelect1", "��", "DOutputState",  pParas->m_nStateBOut[0]);
    pXmlSierialize->xml_serialize("����2״̬" , "_BoutSelect2", "��", "DOutputState",  pParas->m_nStateBOut[1]);
    pXmlSierialize->xml_serialize("����3״̬" , "_BoutSelect3", "��", "DOutputState",  pParas->m_nStateBOut[2]);
    pXmlSierialize->xml_serialize("����4״̬" , "_BoutSelect4", "��", "DOutputState",  pParas->m_nStateBOut[3]);
    pXmlSierialize->xml_serialize("����5״̬" , "_BoutSelect5", "��", "DOutputState",  pParas->m_nStateBOut[4]);
    pXmlSierialize->xml_serialize("����6״̬" , "_BoutSelect6", "��", "DOutputState",  pParas->m_nStateBOut[5]);
    pXmlSierialize->xml_serialize("����7״̬" , "_BoutSelect7", "��", "DOutputState",  pParas->m_nStateBOut[6]);
    pXmlSierialize->xml_serialize("����8״̬" , "_BoutSelect8", "��", "DOutputState",  pParas->m_nStateBOut[7]);
	pXmlSierialize->xml_serialize("������ת������ʽ" , "BoutSwitchMode", "��", "number",  pParas->m_nOutputSwitchMode);
	pXmlSierialize->xml_serialize("��������ʱ��" , "BoutHoldTime", "��", "number",  pParas->m_fBoutHoldTime);
	pXmlSierialize->xml_serialize("������תʱ��" , "BoutTimeTrig", "��", "number",  pParas->m_fBoutTimeTrig);

	stt_xml_serialize_binary_in(pParas->m_binIn,pXmlSierialize);
//	stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_FailureProtDidtActValue(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
   pXmlSierialize->xml_serialize("����ʱ��" , "Holdtime", "��", "number",  pParas->m_fHoldTime);
   pXmlSierialize->xml_serialize("�����仯ʼֵ" , "SecCurStart", "��", "number",  pParas->m_fIstart);
   pXmlSierialize->xml_serialize("�����仯��ֵ" , "SecCurEnd", "��", "number",  pParas->m_fIend);
   pXmlSierialize->xml_serialize("����������ʼֵ" , "SecCurDidtStart", "��", "number",  pParas->m_fDidtStart);
   pXmlSierialize->xml_serialize("����������ֵֹ" , "SecCurDidtEnd", "��", "number",  pParas->m_fDidtEnd);
   pXmlSierialize->xml_serialize("��������仯����" , "SecCurStep", "��", "number",  pParas->m_fDidtStep);

   stt_xml_serialize_Common(pParas,pXmlSierialize);

}
void stt_xml_serialize_FailureProtDidtActTime(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("����ʱ��" , "Holdtime", "��", "number",  pParas->m_fHoldTime);
	pXmlSierialize->xml_serialize("��������" , "SecCurDidt", "��", "number",  pParas->m_fDidt);
	pXmlSierialize->xml_serialize("�����仯ʼֵ" , "SecCurStart", "��", "number",  pParas->m_fIstart);
	pXmlSierialize->xml_serialize("�����仯��ֵ" , "SecCurEnd", "��", "number",  pParas->m_fIend);

	 stt_xml_serialize_Common(pParas,pXmlSierialize);
}
void stt_xml_serialize_FailureProtActValue(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{   

	pXmlSierialize->xml_serialize("��ε����仯ʼֵ" , "FirCurStart", "��", "number",  pParas->m_fFIstart);
	pXmlSierialize->xml_serialize("��ε����仯��ֵ" , "FirCurEnd", "��", "number",  pParas->m_fFIend);
	pXmlSierialize->xml_serialize("��ε����仯����" , "FirCurStep", "��", "number",  pParas->m_fFIstep);
	pXmlSierialize->xml_serialize("��������ʱ��" , "TunActionTime", "��", "number",  pParas->m_fFActionTime);

	 stt_xml_serialize_Common(pParas,pXmlSierialize);
}
void stt_xml_serialize_FailureProtActTime(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("��ε���" , "FirCurrent", "��", "number",  pParas->m_fFI);
	pXmlSierialize->xml_serialize("����" , "Multiple", "��", "number",  pParas->m_fMul);
	pXmlSierialize->xml_serialize("��������ʱ��" , "TunActionTime", "��", "number",  pParas->m_fFActionTime);

	 stt_xml_serialize_Common(pParas,pXmlSierialize);
}

void stt_xml_serialize_FailureProtDidtActValue_ex(tmt_DCFailureProtParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("�����仯ʼֵ(���ʽ)" , "SecCurStartExp", "��", "string",  pParas->m_pszIstart);
	pXmlSierialize->xml_serialize("�����仯��ֵ(���ʽ)" , "SecCurEndExp", "��", "string",  pParas->m_pszIend);
	pXmlSierialize->xml_serialize("����������ʼֵ(���ʽ)" , "SecCurDidtStartExp", "��", "string",  pParas->m_pszDidtStart);
	pXmlSierialize->xml_serialize("����������ֵֹ(���ʽ)" , "SecCurDidtEndExp", "��", "string",  pParas->m_pszDidtEnd);
	pXmlSierialize->xml_serialize("��������仯����(���ʽ)" , "SecCurStepExp", "��", "string",  pParas->m_pszDidtStep);
	pXmlSierialize->xml_serialize("����ʱ��(���ʽ)" , "HoldtimeExp", "��", "string",  pParas->m_pszHoldTime);

	stt_xml_serialize_FailureProtDidtActValue(pParas,pXmlSierialize);
}
void stt_xml_serialize_FailureProtDidtActTime_ex(tmt_DCFailureProtParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("��������(���ʽ)" , "SecCurDidtExp", "��", "string",  pParas->m_pszDidt);
	pXmlSierialize->xml_serialize("�����仯ʼֵ(���ʽ)" , "SecCurStartExp", "��", "string",  pParas->m_pszIstart);
	pXmlSierialize->xml_serialize("�����仯��ֵ(���ʽ)" , "SecCurEndExp", "��", "string",  pParas->m_pszIend);
	pXmlSierialize->xml_serialize("����ʱ��(���ʽ)" , "HoldtimeExp", "��", "string",  pParas->m_pszHoldTime);

	 stt_xml_serialize_FailureProtDidtActTime(pParas,pXmlSierialize);
}
void stt_xml_serialize_FailureProtActValue_ex(tmt_DCFailureProtParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("��ζ���������ֵ(���ʽ)" , "ActValueExp", "��", "string",  pParas->m_fActValue_Setting[0]);
	pXmlSierialize->xml_serialize("��ε����仯ʼֵ(���ʽ)" , "FirCurStartExp", "��", "string",  pParas->m_pszFIstart);
	pXmlSierialize->xml_serialize("��ε����仯��ֵ(���ʽ)" , "FirCurEndExp", "��", "string",  pParas->m_pszFIend);
	pXmlSierialize->xml_serialize("��ε����仯����(���ʽ)" , "FirCurStepExp", "��", "string",  pParas->m_pszFIstep);
	pXmlSierialize->xml_serialize("��������ʱ��(���ʽ)" , "TunActionTimeExp", "��", "string",  pParas->m_pszFActionTime);

	stt_xml_serialize_FailureProtActValue(pParas,pXmlSierialize);

}
void stt_xml_serialize_FailureProtActTime_ex(tmt_DCFailureProtParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("��ε���(���ʽ)" , "FirCurrentExp", "��", "string",  pParas->m_pszFI);
	pXmlSierialize->xml_serialize("����(���ʽ)" , "MultipleExp", "��", "string",  pParas->m_pszMul);
	pXmlSierialize->xml_serialize("��������ʱ��(���ʽ)" , "TunActionTimeExp", "��", "string",  pParas->m_pszFActionTime);

	stt_xml_serialize_FailureProtActTime(pParas,pXmlSierialize);

}

void stt_xml_serialize_FailureProtDidtActValue(tmt_DCFailureProtResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
   pXmlSierialize->xml_serialize( "��ε���ʵ�ʱ仯��" , "SecActionCurrent", "��", "number", pResults->m_fResSACValue);
}
void stt_xml_serialize_FailureProtDidtActTime(tmt_DCFailureProtResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize( "��ζ���ʵ��ʱ��" , "SecActionTime", "��", "number", pResults->m_fResSATime);
}
void stt_xml_serialize_FailureProtActValue(tmt_DCFailureProtResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
   pXmlSierialize->xml_serialize("��ε���ʵ�ʶ���ֵ", "FirActionCurrent", "��", "number", pResults->m_fResFACurValue);
}
void stt_xml_serialize_FailureProtActTime(tmt_DCFailureProtResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
   pXmlSierialize->xml_serialize("��ζ���ʵ��ʱ��", "FirActionTime", "��", "number", pResults->m_fResFATime);
}

CSttXmlSerializeBase* stt_xml_serialize(tmt_DCFailureDidtActValueTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtDidtActValue) == 0)
		{
			stt_xml_serialize_FailureProtDidtActValue_ex(&(pTests->m_oFailureProtTestParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtDidtActTime) == 0)
		{
			stt_xml_serialize_FailureProtDidtActTime_ex(&(pTests->m_oFailureProtTestParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtActValue) == 0)
		{
			stt_xml_serialize_FailureProtActValue_ex(&(pTests->m_oFailureProtTestParas), pXmlParas);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtActTime) == 0)
		{
			stt_xml_serialize_FailureProtActTime_ex(&(pTests->m_oFailureProtTestParas), pXmlParas);
		}
	}

	CSttXmlSerializeBase *pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{ 
		if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtDidtActValue) == 0)
		{
			stt_xml_serialize_FailureProtDidtActValue(&(pTests->m_oFailureProtTestResults), pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtDidtActTime) == 0)
		{
			stt_xml_serialize_FailureProtDidtActTime(&(pTests->m_oFailureProtTestResults), pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtActValue) == 0)
		{
			stt_xml_serialize_FailureProtActValue(&(pTests->m_oFailureProtTestResults), pXmlResults);
		}
		else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtActTime) == 0)
		{
			stt_xml_serialize_FailureProtActTime(&(pTests->m_oFailureProtTestResults), pXmlResults);
		}
		
	}

	return pXmlParas;
}

void stt_xml_serialize_ex(tmt_DCFailureDidtActValueTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly)
{
	if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtDidtActValue) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_FailureProtDidtActValue_ex(&(pTests->m_oFailureProtTestParas), pXmlSerialize);
		}

		stt_xml_serialize_FailureProtDidtActValue(&(pTests->m_oFailureProtTestResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtDidtActTime) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_FailureProtDidtActTime_ex(&(pTests->m_oFailureProtTestParas), pXmlSerialize);
		}

		stt_xml_serialize_FailureProtDidtActTime(&(pTests->m_oFailureProtTestResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtActValue) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_FailureProtActValue_ex(&(pTests->m_oFailureProtTestParas), pXmlSerialize);
		}

		stt_xml_serialize_FailureProtActValue(&(pTests->m_oFailureProtTestResults), pXmlSerialize);
	}
	else if (strcmp(pTests->m_pszMacroID,STT_MACRO_ID_FailureProtActTime) == 0)
	{
		if(!bResultOnly)
		{
			stt_xml_serialize_FailureProtActTime_ex(&(pTests->m_oFailureProtTestParas), pXmlSerialize);
		}

		stt_xml_serialize_FailureProtActTime(&(pTests->m_oFailureProtTestResults), pXmlSerialize);
	}
}
