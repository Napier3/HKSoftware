#include "stdafx.h"
#include "tmt_adjust_test.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif
void stt_xml_serialize(TMT_ADJUST_MEAS_GEAR &pPara, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
	stt_xml_serialize_data_type(pXmlSierialize, "ģ������","ModuleType","","ModuleType", pPara.m_nModuleType);
	pXmlSierialize->xml_serialize("�ɼ�ģ��λ��","ModulePos","","ModulePos",pPara.m_nModulePos);
	pXmlSierialize->xml_serialize("ͨ�����", "Channel","","number",pPara.m_nChannel);
	pXmlSierialize->xml_serialize("�ɼ���λ", "GearID","","number",pPara.m_nGearID);
#else
  stt_xml_serialize_data_type(pXmlSierialize, /* "ģ������" */ g_sLangTxt_Gradient_ModuleType.GetString(), "ModuleType", "", "ModuleType", pPara.m_nModuleType);
  pXmlSierialize->xml_serialize(/* "�ɼ�ģ��λ��" */ g_sLangTxt_Native_CollectModPos.GetString(), "ModulePos", "", "ModulePos", pPara.m_nModulePos);
  pXmlSierialize->xml_serialize(/* "ͨ�����" */ g_sLangTxt_ChannelIndex.GetString(), "Channel", "", "number", pPara.m_nChannel);
  pXmlSierialize->xml_serialize(/* "�ɼ���λ" */ g_sLangTxt_Native_CollectGear.GetString(), "GearID", "", "number", pPara.m_nGearID);
#endif
}

void stt_init_paras(TMT_ADJUST_ONE pParas)
{

}

void stt_xml_serialize(PTMT_ADJUST_ONE_PARAS pPara, CSttXmlSerializeBase *pXmlSerialize)
{
    // pXmlSerialize->xml_serialize("ģ������", "ModuleType"," ","ModuleType",pPara->m_nModuleType);
    //2021-5-4  lijunqing  ��������  ��׼ID������֮���ת��
#ifdef NOT_USE_XLANGUAGE
    stt_xml_serialize_data_type(pXmlSerialize, "ģ������","ModuleType","","ModuleType", pPara->m_nModuleType);

    pXmlSerialize->xml_serialize("ģ��λ��","ModuleIndex","s","ModuleIndex",pPara->m_nModule);
    pXmlSerialize->xml_serialize("����","TempretureID","","TempretureID",pPara->m_nTempretureID);
    pXmlSerialize->xml_serialize("ͨ�����", "Channel","s","number",pPara->m_nChannel);

    pXmlSerialize->xml_serialize("��ֵ", "Mag","s","number",pPara->m_fMag);
    pXmlSerialize->xml_serialize("��λ", "Ang"," ","number",pPara->m_fAng);
    pXmlSerialize->xml_serialize("Ƶ��", "Freq"," ","number",pPara->m_fFreq);
    pXmlSerialize->xml_serialize("������", "Deviation"," ","number",pPara->m_fDeviation);
#else
  stt_xml_serialize_data_type(pXmlSerialize, /* "ģ������" */ g_sLangTxt_Gradient_ModuleType.GetString(), "ModuleType", "", "ModuleType", pPara->m_nModuleType);

  pXmlSerialize->xml_serialize(/* "ģ��λ��" */ g_sLangTxt_Native_ModPos.GetString(), "ModuleIndex", "s", "ModuleIndex", pPara->m_nModule);
  pXmlSerialize->xml_serialize(/* "����" */ g_sLangTxt_Native_TempZone.GetString(), "TempretureID", "", "TempretureID", pPara->m_nTempretureID);
  pXmlSerialize->xml_serialize(/* "ͨ�����" */ g_sLangTxt_ChannelIndex.GetString(), "Channel", "s", "number", pPara->m_nChannel);

  pXmlSerialize->xml_serialize(/* "��ֵ" */ g_sLangTxt_Native_Amplitude.GetString(), "Mag", "s", "number", pPara->m_fMag);
  pXmlSerialize->xml_serialize(/* "��λ" */ g_sLangTxt_Native_Phase.GetString(), "Ang", " ", "number", pPara->m_fAng);
  pXmlSerialize->xml_serialize(/* "Ƶ��" */ g_sLangTxt_Native_Freq.GetString(), "Freq", " ", "number", pPara->m_fFreq);
  pXmlSerialize->xml_serialize(/* "������" */ g_sLangTxt_Native_MeterError.GetString(), "Deviation", " ", "number", pPara->m_fDeviation);
#endif
}

void stt_xml_serialize(PTMT_ADJUST_ONE_RESULTS pPara, CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_AdjItem(&pPara->m_oResult,  pXmlSerialize);
}

void stt_init_paras(TMT_ADJUST_ONE2POINTS pParas)
{
    pParas.init();
}

void stt_xml_serialize(PTMT_ADJUST_ONE2POINTS_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    stt_xml_serialize_data_type(pXmlSierialize, "ģ������","ModuleType","","ModuleType", pPara->m_nModuleType);
    pXmlSierialize->xml_serialize("ģ��λ��","ModuleIndex","s","ModuleIndex",pPara->m_nModule);
    pXmlSierialize->xml_serialize("����","TempretureID","","TempretureID",pPara->m_nTempretureID);
    pXmlSierialize->xml_serialize("ͨ�����","Channel","","Channel",pPara->m_nChannel);
    pXmlSierialize->xml_serialize("�ο�Ƶ��","FreqSel","","FreqSel",pPara->m_nFreqSel);

	pXmlSierialize->xml_serialize("��1�ο���ֵ", "OutValue1","s","number",pPara->m_fPoint1RefMag);
	pXmlSierialize->xml_serialize("��2�ο���ֵ", "OutValue2","s","number",pPara->m_fPoint2RefMag);
	pXmlSierialize->xml_serialize("��1������ֵ", "MeasValue1","s","number",pPara->m_fPoint1MeasMag);
	pXmlSierialize->xml_serialize("��2������ֵ", "MeasValue2","s","number",pPara->m_fPoint2MeasMag);

    pXmlSierialize->xml_serialize("������", "Deviation"," ","number",pPara->m_fDeviation);
#else
  stt_xml_serialize_data_type(pXmlSierialize, /* "ģ������" */ g_sLangTxt_Gradient_ModuleType.GetString(), "ModuleType", "", "ModuleType", pPara->m_nModuleType);
  pXmlSierialize->xml_serialize(/* "ģ��λ��" */ g_sLangTxt_Native_ModPos.GetString(), "ModuleIndex", "s", "ModuleIndex", pPara->m_nModule);
  pXmlSierialize->xml_serialize(/* "����" */ g_sLangTxt_Native_TempZone.GetString(), "TempretureID", "", "TempretureID", pPara->m_nTempretureID);
  pXmlSierialize->xml_serialize(/* "ͨ�����" */ g_sLangTxt_ChannelIndex.GetString(), "Channel", "", "Channel", pPara->m_nChannel);
  pXmlSierialize->xml_serialize(/* "�ο�Ƶ��" */ g_sLangTxt_Native_RefFreq.GetString(), "FreqSel", "", "FreqSel", pPara->m_nFreqSel);

  pXmlSierialize->xml_serialize(/* "��1�ο���ֵ" */ g_sLangTxt_Native_Point1RefAmp.GetString(), "OutValue1", "s", "number", pPara->m_fPoint1RefMag);
  pXmlSierialize->xml_serialize(/* "��2�ο���ֵ" */ g_sLangTxt_Native_Point2RefAmp.GetString(), "OutValue2", "s", "number", pPara->m_fPoint2RefMag);
  pXmlSierialize->xml_serialize(/* "��1������ֵ" */ g_sLangTxt_Native_Point1MeasAmp.GetString(), "MeasValue1", "s", "number", pPara->m_fPoint1MeasMag);
  pXmlSierialize->xml_serialize(/* "��2������ֵ" */ g_sLangTxt_Native_Point2MeasAmp.GetString(), "MeasValue2", "s", "number", pPara->m_fPoint2MeasMag);

  pXmlSierialize->xml_serialize(/* "������" */ g_sLangTxt_Native_MeterError.GetString(), "Deviation", " ", "number", pPara->m_fDeviation);
#endif

}

void stt_xml_serialize(PTMT_ADJUST_ONE2POINTS_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_AdjItem(&pPara->m_oResult,  pXmlSierialize);
}

void stt_init_paras(TMT_ADJUST_ANGLE pParas)
{
    pParas.init();
}

void stt_xml_serialize(PTMT_ADJUST_ANGLE_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    stt_xml_serialize_data_type(pXmlSierialize, "ģ������","ModuleType","","ModuleType", pPara->m_nModuleType);
    pXmlSierialize->xml_serialize("ģ��λ��","ModuleIndex","s","ModuleIndex",pPara->m_nModule);
    pXmlSierialize->xml_serialize("����","TempretureID","","TempretureID",pPara->m_nTempretureID);
    pXmlSierialize->xml_serialize("ͨ�����","Channel","","Channel",pPara->m_nChannel);
	pXmlSierialize->xml_serialize("�����ֵ", "OutMag"," ","number",pPara->m_fOutMag);

	pXmlSierialize->xml_serialize("��λ����ֵ", "MeasValue"," ","number",pPara->m_fMeasAng);
    pXmlSierialize->xml_serialize("������", "Deviation"," ","number",pPara->m_fDeviation);
#else
  stt_xml_serialize_data_type(pXmlSierialize, /* "ģ������" */ g_sLangTxt_Gradient_ModuleType.GetString(), "ModuleType", "", "ModuleType", pPara->m_nModuleType);
  pXmlSierialize->xml_serialize(/* "ģ��λ��" */ g_sLangTxt_Native_ModPos.GetString(), "ModuleIndex", "s", "ModuleIndex", pPara->m_nModule);
  pXmlSierialize->xml_serialize(/* "����" */ g_sLangTxt_Native_TempZone.GetString(), "TempretureID", "", "TempretureID", pPara->m_nTempretureID);
  pXmlSierialize->xml_serialize(/* "ͨ�����" */ g_sLangTxt_ChannelIndex.GetString(), "Channel", "", "Channel", pPara->m_nChannel);
  pXmlSierialize->xml_serialize(/* "�����ֵ" */ g_sLangTxt_Native_OutputAmp.GetString(), "OutMag", " ", "number", pPara->m_fOutMag);

  pXmlSierialize->xml_serialize(/* "��λ����ֵ" */ g_sLangTxt_Native_PhaseMeasVal.GetString(), "MeasValue", " ", "number", pPara->m_fMeasAng);
  pXmlSierialize->xml_serialize(/* "������" */ g_sLangTxt_Native_MeterError.GetString(), "Deviation", " ", "number", pPara->m_fDeviation);
#endif
}

void stt_xml_serialize(PTMT_ADJUST_ANGLE_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_AdjItem(&pPara->m_oResult,  pXmlSierialize);
}

void stt_init_paras(TMT_ADJUST_FREQ pParas)
{
    pParas.init();
}

void stt_xml_serialize(PTMT_ADJUST_FREQ_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    stt_xml_serialize_data_type(pXmlSierialize, "ģ������","ModuleType","","ModuleType", pPara->m_nModuleType);
    pXmlSierialize->xml_serialize("ģ��λ��","ModuleIndex","s","ModuleIndex",pPara->m_nModule);

	pXmlSierialize->xml_serialize("�ο�Ƶ��", "OutValue"," ","number",pPara->m_fRefFreq);
	pXmlSierialize->xml_serialize("����Ƶ��", "MeasValue"," ","number",pPara->m_fMeasFreq);
    pXmlSierialize->xml_serialize("������", "Deviation"," ","number",pPara->m_fDeviation);
#else
  stt_xml_serialize_data_type(pXmlSierialize, /* "ģ������" */ g_sLangTxt_Gradient_ModuleType.GetString(), "ModuleType", "", "ModuleType", pPara->m_nModuleType);
  pXmlSierialize->xml_serialize(/* "ģ��λ��" */ g_sLangTxt_Native_ModPos.GetString(), "ModuleIndex", "s", "ModuleIndex", pPara->m_nModule);

  pXmlSierialize->xml_serialize(/* "�ο�Ƶ��" */ g_sLangTxt_Native_RefFreq.GetString(), "OutValue", " ", "number", pPara->m_fRefFreq);
  pXmlSierialize->xml_serialize(/* "����Ƶ��" */ g_sLangTxt_Native_MeasFreq.GetString(), "MeasValue", " ", "number", pPara->m_fMeasFreq);
  pXmlSierialize->xml_serialize(/* "������" */ g_sLangTxt_Native_MeterError.GetString(), "Deviation", " ", "number", pPara->m_fDeviation);
#endif
}

void stt_xml_serialize(PTMT_ADJUST_FREQ_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_AdjItem(&pPara->m_oResult,  pXmlSierialize);
}

void stt_init_paras(TMT_ADJUST_DCZERO pParas)
{
    pParas.init();
}

void stt_xml_serialize(PTMT_ADJUST_DCZERO_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize)
{
#ifdef NOT_USE_XLANGUAGE
    stt_xml_serialize_data_type(pXmlSierialize, "ģ������","ModuleType","","ModuleType", pPara->m_nModuleType);
    pXmlSierialize->xml_serialize("ģ��λ��","ModuleIndex","s","ModuleIndex",pPara->m_nModule);
    pXmlSierialize->xml_serialize("����","TempretureID","","TempretureID",pPara->m_nTempretureID);
    pXmlSierialize->xml_serialize("ͨ�����","Channel","","Channel",pPara->m_nChannel);
    pXmlSierialize->xml_serialize("ͨ��Ӳ����λ","Tap","","Tap",pPara->m_nTap);

	pXmlSierialize->xml_serialize("��Ư����ֵ", "MeasValue"," ","number",pPara->m_fMeasDcZero);
    pXmlSierialize->xml_serialize("������", "Deviation"," ","number",pPara->m_fDeviation);
#else
  stt_xml_serialize_data_type(pXmlSierialize, /* "ģ������" */ g_sLangTxt_Gradient_ModuleType.GetString(), "ModuleType", "", "ModuleType", pPara->m_nModuleType);
  pXmlSierialize->xml_serialize(/* "ģ��λ��" */ g_sLangTxt_Native_ModPos.GetString(), "ModuleIndex", "s", "ModuleIndex", pPara->m_nModule);
  pXmlSierialize->xml_serialize(/* "����" */ g_sLangTxt_Native_TempZone.GetString(), "TempretureID", "", "TempretureID", pPara->m_nTempretureID);
  pXmlSierialize->xml_serialize(/* "ͨ�����" */ g_sLangTxt_ChannelIndex.GetString(), "Channel", "", "Channel", pPara->m_nChannel);
  pXmlSierialize->xml_serialize(/* "ͨ��Ӳ����λ" */ g_sLangTxt_Native_ChannelHardGear.GetString(), "Tap", "", "Tap", pPara->m_nTap);

  pXmlSierialize->xml_serialize(/* "��Ư����ֵ" */ g_sLangTxt_Native_ZeroDriftMeas.GetString(), "MeasValue", " ", "number", pPara->m_fMeasDcZero);
  pXmlSierialize->xml_serialize(/* "������" */ g_sLangTxt_Native_MeterError.GetString(), "Deviation", " ", "number", pPara->m_fDeviation);
#endif
}

void stt_xml_serialize(PTMT_ADJUST_DCZERO_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize)
{
    stt_xml_serialize_AdjItem(&pPara->m_oResult,  pXmlSierialize);
}

void stt_init_paras(PTMT_ADJUST_THREE pPara)
{

}

void stt_xml_serialize(PTMT_ADJUST_THREE_PARAS pPara, CSttXmlSerializeBase *pXmlSerialize)
{
    // pXmlSerialize->xml_serialize("ģ������", "ModuleType"," ","ModuleType",pPara->m_nModuleType);
    //2021-5-4  lijunqing  ��������  ��׼ID������֮���ת��
#ifdef NOT_USE_XLANGUAGE
    stt_xml_serialize_data_type(pXmlSerialize, "ģ������","ModuleType","","ModuleType", pPara->m_nModuleType);

    pXmlSerialize->xml_serialize("ģ����","ModuleIndex","s","ModuleIndex",pPara->m_nModule);
    pXmlSerialize->xml_serialize("����","TempretureID","","TempretureID",pPara->m_nTempretureID);

    pXmlSerialize->xml_serialize("ͨ��1���", "Channel1","s","number",pPara->m_nChannel);
    pXmlSerialize->xml_serialize("ͨ��1��ֵ", "Mag1","s","number",pPara->m_fMag);
    pXmlSerialize->xml_serialize("ͨ��1��λ", "Ang1"," ","number",pPara->m_fAng);
    pXmlSerialize->xml_serialize("ͨ��1Ƶ��", "Freq1"," ","number",pPara->m_fFreq);

    pXmlSerialize->xml_serialize("ͨ��2���", "Channel2","s","number",pPara->m_nChannel2);
    pXmlSerialize->xml_serialize("ͨ��2��ֵ", "Mag2","s","number",pPara->m_fMag2);
    pXmlSerialize->xml_serialize("ͨ��2��λ", "Ang2"," ","number",pPara->m_fAng2);
    pXmlSerialize->xml_serialize("ͨ��2Ƶ��", "Freq2"," ","number",pPara->m_fFreq2);

    pXmlSerialize->xml_serialize("ͨ��3���", "Channel3","s","number",pPara->m_nChannel3);
    pXmlSerialize->xml_serialize("ͨ��3��ֵ", "Mag3","s","number",pPara->m_fMag3);
    pXmlSerialize->xml_serialize("ͨ��3��λ", "Ang3"," ","number",pPara->m_fAng3);
    pXmlSerialize->xml_serialize("ͨ��3Ƶ��", "Freq3"," ","number",pPara->m_fFreq3);

    pXmlSerialize->xml_serialize("�Ƿ�����У׼", "LargeCurrent","","number",pPara->m_nLargeCurrent);
#else
  stt_xml_serialize_data_type(pXmlSerialize, /* "ģ������" */ g_sLangTxt_Gradient_ModuleType.GetString(), "ModuleType", "", "ModuleType", pPara->m_nModuleType);

  pXmlSerialize->xml_serialize(/* "ģ��λ��" */ g_sLangTxt_Native_ModPos.GetString(), "ModuleIndex", "s", "ModuleIndex", pPara->m_nModule);
  pXmlSerialize->xml_serialize(/* "����" */ g_sLangTxt_Native_TempZone.GetString(), "TempretureID", "", "TempretureID", pPara->m_nTempretureID);

  pXmlSerialize->xml_serialize(/* "ͨ��1���"*/ g_sLangTxt_Native_Channel1ID.GetString(), "Channel1", "s", "number", pPara->m_nChannel);
  pXmlSerialize->xml_serialize(/* "ͨ��1��ֵ" */ g_sLangTxt_Native_Channel1Amp.GetString(), "Mag1", "s", "number", pPara->m_fMag);
  pXmlSerialize->xml_serialize(/* "ͨ��1��λ" */ g_sLangTxt_Native_Channel1Phase.GetString(), "Ang1", " ", "number", pPara->m_fAng);
  pXmlSerialize->xml_serialize(/* "ͨ��1Ƶ��" */ g_sLangTxt_Native_Channel1Freq.GetString(), "Freq1", " ", "number", pPara->m_fFreq);

  pXmlSerialize->xml_serialize(/* "ͨ��2���" */ g_sLangTxt_Native_Channel2Num.GetString(), "Channel2", "s", "number", pPara->m_nChannel2);
  pXmlSerialize->xml_serialize(/* "ͨ��2��ֵ" */ g_sLangTxt_Native_Channel2Amp.GetString(), "Mag2", "s", "number", pPara->m_fMag2);
  pXmlSerialize->xml_serialize(/* "ͨ��2��λ" */ g_sLangTxt_Native_Channel2Phase.GetString(), "Ang2", " ", "number", pPara->m_fAng2);
  pXmlSerialize->xml_serialize(/* "ͨ��2Ƶ��" */ g_sLangTxt_Native_Channel2Freq.GetString(), "Freq2", " ", "number", pPara->m_fFreq2);

  pXmlSerialize->xml_serialize(/* "ͨ��3���" */ g_sLangTxt_Native_Channel3Num.GetString(), "Channel3", "s", "number", pPara->m_nChannel3);
  pXmlSerialize->xml_serialize(/* "ͨ��3��ֵ" */ g_sLangTxt_Native_Channel3Amp.GetString(), "Mag3", "s", "number", pPara->m_fMag3);
  pXmlSerialize->xml_serialize(/* "ͨ��3��λ" */ g_sLangTxt_Native_Channel3Phase.GetString(), "Ang3", " ", "number", pPara->m_fAng3);
  pXmlSerialize->xml_serialize(/* "ͨ��3Ƶ��" */ g_sLangTxt_Native_Channel3Freq.GetString(), "Freq3", " ", "number", pPara->m_fFreq3);

  pXmlSerialize->xml_serialize(/* "�Ƿ�����У׼" */ g_sLangTxt_Native_IsHighCurrentCalib.GetString(), "LargeCurrent", "", "number", pPara->m_nLargeCurrent);
#endif
}

void stt_xml_serialize(PTMT_ADJUST_THREE_RESULTS pPara, CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSerialize->xml_serialize("ͨ��1��ֵϵ��","Coef1","","float",pPara->m_oResult[0].m_fCoef);
    pXmlSerialize->xml_serialize("ͨ��1��Ư","Zero1","","float",pPara->m_oResult[0].m_fZero);
    pXmlSerialize->xml_serialize("ͨ��1��λ","Angle1","","float",pPara->m_oResult[0].m_fAngle);
    pXmlSerialize->xml_serialize("ͨ��2��ֵϵ��","Coef2","","float",pPara->m_oResult[1].m_fCoef);
    pXmlSerialize->xml_serialize("ͨ��2��Ư","Zero2","","float",pPara->m_oResult[1].m_fZero);
    pXmlSerialize->xml_serialize("ͨ��2��λ","Angle2","","float",pPara->m_oResult[1].m_fAngle);
    pXmlSerialize->xml_serialize("ͨ��3��ֵϵ��","Coef3","","float",pPara->m_oResult[2].m_fCoef);
    pXmlSerialize->xml_serialize("ͨ��3��Ư","Zero3","","float",pPara->m_oResult[2].m_fZero);
    pXmlSerialize->xml_serialize("ͨ��3��λ","Angle3","","float",pPara->m_oResult[2].m_fAngle);
#else
  pXmlSerialize->xml_serialize(/* "ͨ��1��ֵϵ��" */ g_sLangTxt_Native_Channel1AmpCoeff.GetString(), "Coef1", "", "float", pPara->m_oResult[0].m_fCoef);
  pXmlSerialize->xml_serialize(/* "ͨ��1��Ư" */ g_sLangTxt_Native_Channel1ZeroOffset.GetString(), "Zero1", "", "float", pPara->m_oResult[0].m_fZero);
  pXmlSerialize->xml_serialize(/* "ͨ��1��λ" */ g_sLangTxt_Native_Channel1Phase.GetString(), "Angle1", "", "float", pPara->m_oResult[0].m_fAngle);
  pXmlSerialize->xml_serialize(/* "ͨ��2��ֵϵ��" */ g_sLangTxt_Native_Channel2AmpCoeff.GetString(), "Coef2", "", "float", pPara->m_oResult[1].m_fCoef);
  pXmlSerialize->xml_serialize(/* "ͨ��2��Ư" */ g_sLangTxt_Native_Channel2ZeroOffset.GetString(), "Zero2", "", "float", pPara->m_oResult[1].m_fZero);
  pXmlSerialize->xml_serialize(/* "ͨ��2��λ" */ g_sLangTxt_Native_Channel2Phase.GetString(), "Angle2", "", "float", pPara->m_oResult[1].m_fAngle);
  pXmlSerialize->xml_serialize(/* "ͨ��3��ֵϵ��" */ g_sLangTxt_Native_Channel3AmpCoeff.GetString(), "Coef3", "", "float", pPara->m_oResult[2].m_fCoef);
  pXmlSerialize->xml_serialize(/* "ͨ��3��Ư" */ g_sLangTxt_Native_Channel3ZeroOffset.GetString(), "Zero3", "", "float", pPara->m_oResult[2].m_fZero);
  pXmlSerialize->xml_serialize(/* "ͨ��3��λ" */ g_sLangTxt_Native_Channel3Phase.GetString(), "Angle3", "", "float", pPara->m_oResult[2].m_fAngle);
#endif
}

void stt_init_paras(TMT_ADJUST_ONECOPY pParas)
{

}

void stt_xml_serialize(PTMT_ADJUST_ONECOPY_PARAS pPara, CSttXmlSerializeBase *pXmlSerialize)
{
    //pXmlSerialize->xml_serialize("ģ������", "ModuleType"," ","ModuleType",pPara->m_nModuleType);
    //2021-5-4  lijunqing  ��������  ��׼ID������֮���ת��
#ifdef NOT_USE_XLANGUAGE
    stt_xml_serialize_data_type(pXmlSerialize, "ģ������","ModuleType","","ModuleType", pPara->m_nModuleType);

    pXmlSerialize->xml_serialize("ģ����","ModuleIndex","s","ModuleIndex",pPara->m_nModule);
    pXmlSerialize->xml_serialize("����","TempretureID","","TempretureID",pPara->m_nTempretureID);
    pXmlSerialize->xml_serialize("ͨ�����", "Channel","s","number",pPara->m_nChannel);
    pXmlSerialize->xml_serialize("����ѡ��", "FreqSel"," ","FreqSel",pPara->m_nFreqSel);
    pXmlSerialize->xml_serialize("��λ", "GearID"," ","Gear",pPara->m_nGearID);

    pXmlSerialize->xml_serialize("ģ����2", "ModuleIndex2","s","ModuleIndex",pPara->m_nModule2);
    pXmlSerialize->xml_serialize("����2", "TempretureID2"," ","TempretureID",pPara->m_nTempretureID2);
    pXmlSerialize->xml_serialize("ͨ�����2", "Channel2"," ","number",pPara->m_nChannel2);
    pXmlSerialize->xml_serialize("��λ2", "GearID2"," ","Gear",pPara->m_nGearID2);
#else
  stt_xml_serialize_data_type(pXmlSerialize, /* "ģ������" */ g_sLangTxt_Gradient_ModuleType.GetString(), "ModuleType", "", "ModuleType", pPara->m_nModuleType);

  pXmlSerialize->xml_serialize(/* "ģ��λ��" */ g_sLangTxt_Native_ModPos.GetString(), "ModuleIndex", "s", "ModuleIndex", pPara->m_nModule);
  pXmlSerialize->xml_serialize(/* "����" */ g_sLangTxt_Native_TempZone.GetString(), "TempretureID", "", "TempretureID", pPara->m_nTempretureID);
  pXmlSerialize->xml_serialize(/* "ͨ�����" */ g_sLangTxt_ChannelIndex.GetString(), "Channel", "s", "number", pPara->m_nChannel);
  pXmlSerialize->xml_serialize(/* "����ѡ��" */ g_sLangTxt_Native_WaveformSelection.GetString(), "FreqSel", " ", "FreqSel", pPara->m_nFreqSel);
  pXmlSerialize->xml_serialize(/* "��λ" */ g_sLangTxt_Native_Gear.GetString(), "GearID", " ", "Gear", pPara->m_nGearID);

  pXmlSerialize->xml_serialize(/* "ģ����2" */ g_sLangTxt_Native_ModuleNo2.GetString(), "ModuleIndex2", "s", "ModuleIndex", pPara->m_nModule2);
  pXmlSerialize->xml_serialize(/* "����2" */ g_sLangTxt_Native_TempZone2.GetString(), "TempretureID2", " ", "TempretureID", pPara->m_nTempretureID2);
  pXmlSerialize->xml_serialize(/* "ͨ�����2" */ g_sLangTxt_Native_ChannelNo2.GetString(), "Channel2", " ", "number", pPara->m_nChannel2);
  pXmlSerialize->xml_serialize(/* "��λ2" */ g_sLangTxt_Native_Gear2.GetString(), "GearID2", " ", "Gear", pPara->m_nGearID2);
#endif
}

void stt_xml_serialize(PTMT_ADJUST_ONECOPY_RESULTS pPara, CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize_AdjItem(&pPara->m_oResult,  pXmlSerialize);
}

void stt_init_paras(PTMT_ADJ_MODULE_OUTPUT pPara)
{
    pPara->init();
}


void stt_xml_serialize(PTMT_ADJ_CHANNEL_VECTOR pPara, const char *pszID, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pXmlVector =pXmlSerialize->xml_serialize(pszID, pszID,  "Vector", stt_ParaGroupKey());

    if (pXmlVector == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pXmlSerialize->xml_serialize("��ֵ", "Mag","s","number", pPara->m_fMag);
    pXmlSerialize->xml_serialize("��λ", "Ang"," ","number", pPara->m_fAngle);
#else
  pXmlSerialize->xml_serialize(/* "��ֵ" */ g_sLangTxt_Native_Amplitude.GetString(), "Mag", "s", "number", pPara->m_fMag);
  pXmlSerialize->xml_serialize(/* "��λ" */ g_sLangTxt_Native_Phase.GetString(), "Ang", " ", "number", pPara->m_fAngle);
#endif
}

void stt_xml_serialize(PTMT_ADJ_CHAANEL pPara, long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef NOT_USE_XLANGUAGE
    CSttXmlSerializeBase *pXmlCh =pXmlSerialize->xml_serialize("ͨ��", "Ch", nIndex, "Channel", stt_ParaGroupKey());
#else
  CSttXmlSerializeBase *pXmlCh = pXmlSerialize->xml_serialize(/* "ͨ��" */ g_sLangTxt_Native_Channel.GetString(), "Ch", nIndex, "Channel", stt_ParaGroupKey());
#endif

    if (pXmlCh == NULL)
    {
        return;
    }
#ifdef NOT_USE_XLANGUAGE
    pXmlCh->xml_serialize("��ֵ", "Mag","s","number", pPara->m_oVector.m_fMag);
    pXmlCh->xml_serialize("��λ", "Ang"," ","number", pPara->m_oVector.m_fAngle);
#else
  pXmlCh->xml_serialize(/* "��ֵ" */ g_sLangTxt_Native_Amplitude.GetString(), "Mag", "s", "number", pPara->m_oVector.m_fMag);
  pXmlCh->xml_serialize(/* "��λ" */ g_sLangTxt_Native_Phase.GetString(), "Ang", " ", "number", pPara->m_oVector.m_fAngle);
#endif
    //stt_xml_serialize(&pPara->m_harm[0], "DC", pXmlCh);
    //stt_xml_serialize(&pPara->m_harm[1], "Base", pXmlCh);
    //CString strID;

    //for (long nIndex=2; nIndex<ADJUST_MAX_HARM_COUNT; nIndex++)
    // {
    //    strID.Format("Harm%d", nIndex);
    //     stt_xml_serialize(&pPara->m_harm[nIndex], strID.GetString(), pXmlCh);
    //}
}

void stt_xml_serialize(PTMT_ADJ_MODULE_OUTPUT pPara, CSttXmlSerializeBase *pXmlSerialize)
{
    //pXmlSerialize->xml_serialize("ģ������", "ModuleType","","ModuleType",pPara->m_nModuleType);
    //2021-5-4  lijunqing  ��������  ��׼ID������֮���ת��
#ifdef NOT_USE_XLANGUAGE
    stt_xml_serialize_data_type(pXmlSerialize, "ģ������","ModuleType","","ModuleType", pPara->m_nModuleType);

    pXmlSerialize->xml_serialize("ģ��λ��","ModuleIndex","","ModuleIndex", pPara->m_nModuleIndex);
    pXmlSerialize->xml_serialize("Ƶ��", "FreqIndex","","long",pPara->m_nFreqIndex);
	pXmlSerialize->xml_serialize("���ͨ��", "Channel","","long",pPara->m_nChannel);//���ڶ�ͨ������������豸,��PIC200D
    pXmlSerialize->xml_serialize("Ӳ����λ", "Tap","","number",pPara->m_nTap);
#else
  stt_xml_serialize_data_type(pXmlSerialize, /* "ģ������" */ g_sLangTxt_Gradient_ModuleType.GetString(), "ModuleType", "", "ModuleType", pPara->m_nModuleType);

  pXmlSerialize->xml_serialize(/* "ģ��λ��" */ g_sLangTxt_Native_ModPos.GetString(), "ModuleIndex", "", "ModuleIndex", pPara->m_nModuleIndex);
  pXmlSerialize->xml_serialize(/* "Ƶ��" */ g_sLangTxt_Native_Freq.GetString(), "FreqIndex", "", "long", pPara->m_nFreqIndex);
  pXmlSerialize->xml_serialize(/* "���ͨ��" */ g_sLangTxt_Native_OutputChannel.GetString(), "Channel", "", "long",
                               pPara->m_nChannel);  // ���ڶ�ͨ������������豸,��PIC200D
  pXmlSerialize->xml_serialize(/* "Ӳ����λ" */ g_sLangTxt_Native_HardwareGear.GetString(), "Tap", "", "number", pPara->m_nTap);
#endif
    for (long nIndex=0; nIndex < STT_MODULE_CHANNEL_MAX; nIndex++ )//����48·С�ź�
    {
        stt_xml_serialize(&pPara->m_oChannels[nIndex],  nIndex, pXmlSerialize);
    }
}

void stt_init_paras(PTMT_ADJ_SWITCH_OUTPUT pParas)
{
    pParas->init();
}

void stt_xml_serialize(PTMT_ADJ_SWITCH_OUTPUT pPara, CSttXmlSerializeBase *pXmlSerialize)
{
    //pXmlSerialize->xml_serialize("ģ������", "ModuleType","","ModuleType",pPara->m_nModuleType);
    //2021-5-4  lijunqing  ��������  ��׼ID������֮���ת��
#ifdef NOT_USE_XLANGUAGE
    stt_xml_serialize_data_type(pXmlSerialize, "ģ������","ModuleType","","ModuleType", pPara->m_nModuleType);

    pXmlSerialize->xml_serialize("ģ����","ModuleIndex","","ModuleIndex", pPara->m_nModuleIndex);
    pXmlSerialize->xml_serialize("�л�ģʽ", "SwitchMode","","long",pPara->m_nSwitchMode);
#else
  stt_xml_serialize_data_type(pXmlSerialize, /* "ģ������" */ g_sLangTxt_Gradient_ModuleType.GetString(), "ModuleType", "", "ModuleType", pPara->m_nModuleType);

  pXmlSerialize->xml_serialize(/* "ģ����" */ g_sLangTxt_Native_ModuleNumber.GetString(), "ModuleIndex", "", "ModuleIndex", pPara->m_nModuleIndex);
  pXmlSerialize->xml_serialize(/* "�л�ģʽ" */ g_sLangTxt_Native_SwitchMode.GetString(), "SwitchMode", "", "long", pPara->m_nSwitchMode);
#endif
}

void stt_init_paras(PTMT_ADJ_BINARY_OUTPUT pParas)
{
    pParas->init();
}

void stt_xml_serialize(PTMT_ADJ_BINARY_OUTPUT pPara, CSttXmlSerializeBase *pXmlSerialize)
{
    CString strName, strID;

    for(int i = 0; i < 16; i++)
    {
		strName.Format("����%d������ƽ(����Ч�����Ч)", (i + 1));
		strID.Format("BoutDef%d", (i + 1));
        pXmlSerialize->xml_serialize(strName.GetString(), strID.GetString(), "", "bool", pPara->m_nBoutTurnOnValue[i]);

		strID.Format("Bout%d", (i + 1));
		pXmlSerialize->xml_serialize("", strID.GetString(), "", "bool", pPara->m_nBoutValue[i]);
    }
}

void stt_init_paras(PTMT_ADJ_REGISTER_OUTPUT pParas)
{
	pParas->init();
}

void stt_xml_serialize(PTMT_ADJ_REGISTER_OUTPUT pPara, CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSerialize->xml_serialize("�Ĵ�����ַ(16����)","RegAddr","","", pPara->m_nRegAddr);
	pXmlSerialize->xml_serialize("�Ĵ���ֵ(16����)","RegValue","","", pPara->m_nRegValue);
#else
  pXmlSerialize->xml_serialize(/* "�Ĵ�����ַ(16����)" */ g_sLangTxt_Native_RegAddrHex.GetString(), "RegAddr", "", "", pPara->m_nRegAddr);
  pXmlSerialize->xml_serialize(/* "�Ĵ���ֵ(16����)" */ g_sLangTxt_Native_RegValHex.GetString(), "RegValue", "", "", pPara->m_nRegValue);
#endif
}

void stt_init_paras(PTMT_ADJ_MODULEFLASH pParas)
{
    pParas->init();
}

void stt_xml_serialize(PTMT_ADJ_MODULEFLASH_PARAS pPara, CSttXmlSerializeBase *pXmlSerialize)
{
    pXmlSerialize->xml_serialize("ģ��λ��", "ModuleIndex", "", "ModuleIndex", pPara->m_nModuleIndex);
    pXmlSerialize->xml_serialize("ģ��������ڱ��", "ModuleAddr", "", "ModuleAddr", pPara->m_nModuleAddr);
}

void stt_xml_serialize(PTMT_ADJ_MODULEFLASH_RESULTS pPara, CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef NOT_USE_XLANGUAGE
    pXmlSerialize->xml_serialize("���", "Result","","number",pPara->m_nResult);
#else
  pXmlSerialize->xml_serialize(/* "���" */ g_sLangTxt_Native_Results.GetString(), "Result", "", "number", pPara->m_nResult);
#endif
}

#include"../../../SttCmd/SttTestCmd.h"
#include"../../../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_ModuleOutPut()
{
    TMT_ADJ_MODULE_OUTPUT oModuleOutPut;
    oModuleOutPut.init();
    CSttXmlSerializeTool oSttXmlSerializeTool;
    CSttTestCmd oSttTestCmd;
    CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
    pMacro->GetParas();
    //pMacro->GetResults();
    oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
    CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
    CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
    stt_xml_serialize(&oModuleOutPut, pMacroParas);
    CString strXMLPath;
    strXMLPath = _P_GetConfigPath();
    strXMLPath += ("ModuleOutPut.xml");
    //    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

    oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

void stt_xml_serialize_write_RegisterTest()
{
	TMT_ADJ_REGISTER_OUTPUT oRegisterOutPut;
	oRegisterOutPut.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	//pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oRegisterOutPut, pMacroParas);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("RegisterOutPut.xml");
	//    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

/*
void stt_init_paras(tmt_RecordParas *pPara)
{
    pPara->init(IECSIZE_MAX);
}

void stt_xml_serialize(tmt_RecordPara &oPara, long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
    CSttXmlSerializeBase *pSubSerialize =pXmlSerialize->xml_serialize("����", "Subscribe", nIndex, "Subscribe", stt_ParaGroupKey());

        if (pSubSerialize == NULL)
        {
                return;
        }

        pSubSerialize->xml_serialize(("Ŀ��MAC"), ("DestMac"),(" "),("string"),oPara.dest_mac);
        pSubSerialize->xml_serialize(("Appid"), ("APPID"),(" "),("string"),oPara.appid);
        pSubSerialize->xml_serialize(("���չ��"), ("Port"),(" "),("string"),oPara.port);
        pSubSerialize->xml_serialize(("��������"), ("Type"),(" "),("string"),oPara.ntype);
}

void stt_xml_serialize(tmt_RecordParas *pPara, CSttXmlSerializeBase *pXmlSerialize)
{	
    pXmlSerialize->xml_serialize("��������","SubscribeCount","","int",pPara->m_nSubNumber);
    pXmlSerialize->xml_serialize("����ģʽ","Mode","","int",pPara->m_mode);
        long nIndex = 0;

    for (nIndex=0; nIndex<pPara->m_nSubNumber; nIndex++)
        {
        stt_xml_serialize(pPara->m_paras[nIndex], nIndex, pXmlSerialize);
        }
}

#include"../../SttCmd/SttTestCmd.h"
#include"tmt_record.h"
#include"../../../Module/API/GlobalConfigApi.h"

void stt_xml_serialize_write_Record()
{
        tmt_RecordTest oRecordTest;
        oRecordTest.init(IECSIZE_MAX);
        CSttXmlSerializeTool oSttXmlSerializeTool;
        CSttTestCmd oSttTestCmd;
        CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
        pMacro->GetParas();
        //pMacro->GetResults();
        oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
        CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
        CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
        stt_xml_serialize(&oRecordTest.m_oRecordPara, pMacroParas);
        CString strXMLPath;
        strXMLPath = _P_GetConfigPath();
        strXMLPath += ("RecordDemo.xml");
        //    pMacro->SaveXmlFile(strXMLPath,CSttCmdDefineXmlRWKeys::g_pXmlKeys);

        oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
