#include "stdafx.h"
#include "tmt_ulock_overcurrent_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

void stt_init_paras(tmt_ULockOverCurrentParas *pParas)
{
	memset(&pParas, 0, sizeof(tmt_ULockOverCurrentParas));
	pParas->init();
}

void stt_init_paras_ex(tmt_ULockOverCurrentParasEx *pParas)
{
	memset(&pParas, 0, sizeof(tmt_ULockOverCurrentParasEx));
	pParas->init();
}

void stt_init_results(tmt_ULockOverCurrentResults *pResults)
{
	memset(&pResults, 0, sizeof(tmt_ULockOverCurrentResults));
	pResults->init();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

void stt_xml_serialize(tmt_ULockOverCurrentParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "", "set",pParas->m_fStart);
	pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "", "set", pParas->m_fStop );
	pXmlSierialize->xml_serialize("���Ծ���", "Step", "", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize("����ʱ��", "StepTime", "s", "set", pParas->m_fStepTime);
	pXmlSierialize->xml_serialize("��������", "FaultType", "", "PsuFYBSFaultType",pParas->m_nULockFaultType);
	pXmlSierialize->xml_serialize("��·��ѹ", "VSet1", "V", "set", pParas->m_fSCVoltage);
	pXmlSierialize->xml_serialize("��·����", "ISet1", "A", "set",pParas->m_fSCCurrent);
	pXmlSierialize->xml_serialize("�迹��", "Z1Ph", "��", "number", pParas->m_fImpAngle);
	pXmlSierialize->xml_serialize("�Ƿ���Է���ֵ", "VaryMode", "", "number", pParas->m_nTestMode);

	pXmlSierialize->xml_serialize("�͵�ѹ(V)", "Vzd", "", "number", pParas->m_fVzd);
	pXmlSierialize->xml_serialize("�����ѹ(V)", "V2zd", "", "number", pParas->m_fV2zd);
	pXmlSierialize->xml_serialize("��������(A)", "Izd", "", "number", pParas->m_fIzd);
	pXmlSierialize->xml_serialize("��ʱʱ��(s)", "T1", "", "number", pParas->m_fT1);
	pXmlSierialize->xml_serialize("���������(��)", "Phimax", "", "number", pParas->m_fPhimax);
	pXmlSierialize->xml_serialize("��������С(��)", "PhiSize", "", "number", pParas->m_fPhiSize);
	pXmlSierialize->xml_serialize("��������", "IPoint", "", "number", pParas->m_nIPoint);
	pXmlSierialize->xml_serialize("�͵�ѹ����", "USetMode", "", "number", pParas->m_nUSetMode);
#else
  pXmlSierialize->xml_serialize(/* "�仯ʼֵ" */ g_sLangTxt_Gradient_Init.GetString(), "BeginVal", "", "set", pParas->m_fStart);
  pXmlSierialize->xml_serialize(/* "�仯��ֵ" */ g_sLangTxt_Gradient_Finish.GetString(), "EndVal", "", "set", pParas->m_fStop);
  pXmlSierialize->xml_serialize(/* "���Ծ���" */ g_sLangTxt_Native_TestPrecision.GetString(), "Step", "", "set", pParas->m_fStep);
  pXmlSierialize->xml_serialize(/* "����ʱ��" */ g_sLangTxt_Native_StepTimes.GetString(), "StepTime", "s", "set", pParas->m_fStepTime);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Gradient_FailType.GetString(), "FaultType", "", "PsuFYBSFaultType", pParas->m_nULockFaultType);
  pXmlSierialize->xml_serialize(/* "��·��ѹ" */ g_sLangTxt_Native_ShortCircuitV.GetString(), "VSet1", "V", "set", pParas->m_fSCVoltage);
  pXmlSierialize->xml_serialize(/* "��·����" */ g_sLangTxt_Native_ShortCircuit.GetString(), "ISet1", "A", "set", pParas->m_fSCCurrent);
  pXmlSierialize->xml_serialize(/* "�迹��" */ g_sLangTxt_Native_ImpedanceAngles.GetString(), "Z1Ph", "��", "number", pParas->m_fImpAngle);
  pXmlSierialize->xml_serialize(/* "�Ƿ���Է���ֵ" */ g_sLangTxt_Native_TestReturnValue.GetString(), "VaryMode", "", "number", pParas->m_nTestMode);

  pXmlSierialize->xml_serialize(/* "�͵�ѹ(V)" */ g_sLangTxt_Native_LowVoltagev.GetString(), "Vzd", "", "number", pParas->m_fVzd);
  pXmlSierialize->xml_serialize(/* "�����ѹ(V)" */ g_sLangTxt_Native_NegativeSeqVolt.GetString(), "V2zd", "", "number", pParas->m_fV2zd);
  pXmlSierialize->xml_serialize(/* "��������(A)" */ g_sLangTxt_Native_ActionCurrent.GetString(), "Izd", "", "number", pParas->m_fIzd);
  pXmlSierialize->xml_serialize(/* "��ʱʱ��(s)" */ g_sLangTxt_Native_DelayTimes.GetString(), "T1", "", "number", pParas->m_fT1);
  pXmlSierialize->xml_serialize(/* "���������(��)" */ g_sLangTxt_Gradient_MaxSenAngle.GetString(), "Phimax", "", "number", pParas->m_fPhimax);
  pXmlSierialize->xml_serialize(/* "��������С(��)" */ g_sLangTxt_Native_ActionAreaSize.GetString(), "PhiSize", "", "number", pParas->m_fPhiSize);
  pXmlSierialize->xml_serialize(/* "��������" */ g_sLangTxt_Native_ActDirection.GetString(), "IPoint", "", "number", pParas->m_nIPoint);
  pXmlSierialize->xml_serialize(/* "�͵�ѹ����" */ g_sLangTxt_Native_LowVoltageDef.GetString(), "USetMode", "", "number", pParas->m_nUSetMode);
#endif
	stt_xml_serialize_common(pParas,pXmlSierialize);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_ex(tmt_ULockOverCurrentParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSierialize->xml_serialize("�仯ʼֵ(���ʽ)", "BeginValExp", "", "string",pParas->m_pszStart);
	pXmlSierialize->xml_serialize("�仯��ֵ(���ʽ)", "EndValExp", "", "string", pParas->m_pszStop );
	pXmlSierialize->xml_serialize("����ʱ��(���ʽ)", "StepTimeExp", "", "string", pParas->m_pszStepTime);
	pXmlSierialize->xml_serialize("��·��ѹ(���ʽ)", "VSet1Exp", "", "string", pParas->m_pszSCVoltage);
	pXmlSierialize->xml_serialize("��·����(���ʽ)", "ISet1Exp", "", "string",pParas->m_pszSCCurrent);
	pXmlSierialize->xml_serialize("�迹��(���ʽ)", "Z1PhExp", "", "string", pParas->m_pszImpAngle);
#else
  pXmlSierialize->xml_serialize(/* "�仯ʼֵ(���ʽ)" */ g_sLangTxt_Native_VarStartValue.GetString(), "BeginValExp", "", "string", pParas->m_pszStart);
  pXmlSierialize->xml_serialize(/* "�仯��ֵ(���ʽ)" */ g_sLangTxt_Native_VarEndValue.GetString(), "EndValExp", "", "string", pParas->m_pszStop);
  pXmlSierialize->xml_serialize(/* "����ʱ��(���ʽ)" */ g_sLangTxt_Native_StepTime.GetString(), "StepTimeExp", "", "string", pParas->m_pszStepTime);
  pXmlSierialize->xml_serialize(/* "��·��ѹ(���ʽ)" */ g_sLangTxt_Native_ShortVolt.GetString(), "VSet1Exp", "", "string", pParas->m_pszSCVoltage);
  pXmlSierialize->xml_serialize(/* "��·����(���ʽ)" */ g_sLangTxt_Native_ShortCurr.GetString(), "ISet1Exp", "", "string", pParas->m_pszSCCurrent);
  pXmlSierialize->xml_serialize(/* "�迹��(���ʽ)" */ g_sLangTxt_Native_ImpedanceAnglexp.GetString(), "Z1PhExp", "", "string", pParas->m_pszImpAngle);
#endif
	stt_xml_serialize(pParas,pXmlSierialize);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void stt_xml_serialize(tmt_ULockOverCurrentResults *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize((tmt_GradientResult*)pResults,pXmlSierialize);
}

CSttXmlSerializeBase* stt_xml_serialize( tmt_ULockOverCurrentTest *pTests, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlParas = pXmlSerialize->xml_serialize("paras", "paras", "paras", stt_ParasKey());

	if (pXmlParas != NULL)
	{
		stt_xml_serialize_ex(&(pTests->m_oTmtParas),  pXmlParas);	//�ļ��Ķ�д
	}

	CSttXmlSerializeBase * pXmlResults = pXmlSerialize->xml_serialize("results", "results", "results", stt_ResultsKey());

	if (pXmlResults != NULL)
	{
		stt_xml_serialize(&pTests->m_oTmtResults,  pXmlResults);
	}

	return pXmlParas;
}

