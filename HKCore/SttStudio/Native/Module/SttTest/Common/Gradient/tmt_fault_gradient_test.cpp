#include "stdafx.h"
#include "tmt_fault_gradient_test.h"
#include"../../../SttCmd/SttTestCmd.h"
#ifdef NOT_USE_XLANGUAGE
#else
#include "../../../XLangResource_Native.h"                              

#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_xml_serialize
/// \param pParas
/// \param pXmlSierialize
////////////////////////////////////������д
void stt_xml_serialize(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	stt_xml_serialize_base(pParas, pXmlSierialize);
	stt_xml_serialize_FaultGradientSetting(pParas, pXmlSierialize);
	stt_xml_serialize_FaultGradientError(pParas, pXmlSierialize);
	stt_xml_serialize_binary_AndOr(pParas, pXmlSierialize);
	stt_xml_serialize_binary_in(pParas, pXmlSierialize);
	stt_xml_serialize_binary_out(pParas, pXmlSierialize);
}

//���� ����ֵ ���л�
void stt_xml_serialize_base(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("�仯ʼֵ", "BeginVal", "", "set", pParas->m_fStart);
	pXmlSierialize->xml_serialize("�仯��ֵ", "EndVal", "", "set", pParas->m_fStop );
	pXmlSierialize->xml_serialize("�仯����", "Step", "", "set", pParas->m_fStep);
	pXmlSierialize->xml_serialize("����ʱ��(��)","FaultTime","s","set",pParas->m_fFaultTime);
	pXmlSierialize->xml_serialize("���Է���ϵ��", "VaryMode", "", "number", pParas->m_nTestMode);
	
	pXmlSierialize->xml_serialize("����ģʽ", "FaultMode", "", "UIRampType", pParas->m_nFaultMode);
	pXmlSierialize->xml_serialize("�仯��", "ChangeValue", "", "UIRampChannel", pParas->m_nChangeValue);
	pXmlSierialize->xml_serialize("����ͨ������", "VarIndexType", "", "number", pParas->m_nVarIndexType);
	pXmlSierialize->xml_serialize("��·��ѹֵ", "ShorVmValue", "V", "set", pParas->m_fShortVm);
	pXmlSierialize->xml_serialize("��·��ѹ����","ShorVmType","","number",pParas->m_nShortVmType);
	pXmlSierialize->xml_serialize("��·����", "ShortVa", "A", "number", pParas->m_fShortVa);
	pXmlSierialize->xml_serialize("�迹��", "ImpedanceAngel", "��", "number", pParas->m_fAngle);

	pXmlSierialize->xml_serialize("�仯ǰʱ��(��)", "_PrepareTime", "s", "set", pParas->m_fPrepareTime);
	pXmlSierialize->xml_serialize("����ǰʱ��(��)", "_PreFaultTime", "s", "set", pParas->m_fPreFaultTime );
	pXmlSierialize->xml_serialize("����ǰ��ѹ", "_PrepareFaultVm", "V", "number", pParas->m_fPreFaultEDU);
	pXmlSierialize->xml_serialize("����ǰ����","_PrepareFaultVa","A","number",pParas->m_fPreFaultEDI);
	pXmlSierialize->xml_serialize("����ǰ���", "_PreFaultAngle", "��", "number", pParas->m_fEDUaIaAngle);
}

//������ �߼�����
void stt_xml_serialize_binary_AndOr(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("�����߼�","_AndOr","","InPutLogic_Psu",pParas->m_nBinLogic);
}

//������ 
void stt_xml_serialize_binary_in(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("����Aѡ��","_BinSelectA","","BOOL",pParas->m_binIn[0].nSelect);
	pXmlSierialize->xml_serialize("����Bѡ��","_BinSelectB","","BOOL",pParas->m_binIn[1].nSelect);
	pXmlSierialize->xml_serialize("����Cѡ��","_BinSelectC","","BOOL",pParas->m_binIn[2].nSelect);
	pXmlSierialize->xml_serialize("����Dѡ��","_BinSelectD","","BOOL",pParas->m_binIn[3].nSelect);
	pXmlSierialize->xml_serialize("����Eѡ��","_BinSelectE","","BOOL",pParas->m_binIn[4].nSelect);
	pXmlSierialize->xml_serialize("����Fѡ��","_BinSelectF","","BOOL",pParas->m_binIn[5].nSelect);
	pXmlSierialize->xml_serialize("����Gѡ��","_BinSelectG","","BOOL",pParas->m_binIn[6].nSelect);
	pXmlSierialize->xml_serialize("����Hѡ��","_BinSelectH","","BOOL",pParas->m_binIn[7].nSelect);
	pXmlSierialize->xml_serialize("����Iѡ��","_BinSelectI","","BOOL",pParas->m_binIn[8].nSelect);
	pXmlSierialize->xml_serialize("����Jѡ��","_BinSelectJ","","BOOL",pParas->m_binIn[9].nSelect);

}

//��̬���� ���Ͽ���
void stt_xml_serialize_binary_out(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("��̬����1״̬","_BoutNomal1","","DOutputState",pParas->m_binOut[0][0].nState);
	pXmlSierialize->xml_serialize("��̬����2״̬","_BoutNomal2","","DOutputState",pParas->m_binOut[0][1].nState);
	pXmlSierialize->xml_serialize("��̬����3״̬","_BoutNomal3","","DOutputState",pParas->m_binOut[0][2].nState);
	pXmlSierialize->xml_serialize("��̬����4״̬","_BoutNomal4","","DOutputState",pParas->m_binOut[0][3].nState);
	pXmlSierialize->xml_serialize("��̬����5״̬","_BoutNomal5","","DOutputState",pParas->m_binOut[0][4].nState);
	pXmlSierialize->xml_serialize("��̬����6״̬","_BoutNomal6","","DOutputState",pParas->m_binOut[0][5].nState);
	pXmlSierialize->xml_serialize("��̬����7״̬","_BoutNomal7","","DOutputState",pParas->m_binOut[0][6].nState);
	pXmlSierialize->xml_serialize("��̬����8״̬","_BoutNomal8","","DOutputState",pParas->m_binOut[0][7].nState);
	pXmlSierialize->xml_serialize("��̬����9״̬","_BoutNomal9","","DOutputState",pParas->m_binOut[0][8].nState);
	pXmlSierialize->xml_serialize("��̬����10״̬","_BoutNomal10","","DOutputState",pParas->m_binOut[0][9].nState);

	pXmlSierialize->xml_serialize("����̬����1״̬","_BoutError1","","DOutputState",pParas->m_binOut[1][0].nState);
	pXmlSierialize->xml_serialize("����̬����2״̬","_BoutError2","","DOutputState",pParas->m_binOut[1][1].nState);
	pXmlSierialize->xml_serialize("����̬����3״̬","_BoutError3","","DOutputState",pParas->m_binOut[1][2].nState);
	pXmlSierialize->xml_serialize("����̬����4״̬","_BoutError4","","DOutputState",pParas->m_binOut[1][3].nState);
	pXmlSierialize->xml_serialize("����̬����5״̬","_BoutError5","","DOutputState",pParas->m_binOut[1][4].nState);
	pXmlSierialize->xml_serialize("����̬����6״̬","_BoutError6","","DOutputState",pParas->m_binOut[1][5].nState);
	pXmlSierialize->xml_serialize("����̬����7״̬","_BoutError7","","DOutputState",pParas->m_binOut[1][6].nState);
	pXmlSierialize->xml_serialize("����̬����8״̬","_BoutError8","","DOutputState",pParas->m_binOut[1][7].nState);
	pXmlSierialize->xml_serialize("����̬����9״̬","_BoutError9","","DOutputState",pParas->m_binOut[1][8].nState);
	pXmlSierialize->xml_serialize("����̬����10״̬","_BoutError10","","DOutputState",pParas->m_binOut[1][9].nState);
}

//����ֵ 
void stt_xml_serialize_FaultGradientSetting(tmt_faultGradientParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("��ѹ��������ֵ", "USet", "V", "float", pParas->m_fUSet);
    pXmlSierialize->xml_serialize("������������ֵ", "ISet", "A", "float", pParas->m_fISet);
	pXmlSierialize->xml_serialize("�迹����������ֵ", "ImpAngleSet", "��", "float", pParas->m_fImpAngleSet);
	pXmlSierialize->xml_serialize("��·�迹��������ֵ", "ShortZImp", "��", "float", pParas->m_fShortZImp);
    pXmlSierialize->xml_serialize("Ƶ����������ֵ", "HzSet", "Hz", "float", pParas->m_fHzSet);
    pXmlSierialize->xml_serialize("�߽��1����ֵ", "AngleFSet", "��", "float", pParas->m_fAngleFSet);
    pXmlSierialize->xml_serialize("�߽��2����ֵ", "AngleSSet", "��", "float", pParas->m_fAngleSSet);
    pXmlSierialize->xml_serialize("�������������ֵ", "MaxAngleSet", "��", "float", pParas->m_fMaxAngleSet);
    pXmlSierialize->xml_serialize("����ϵ������ֵ", "RetCoefSet", "", "float", pParas->m_fRetCoefSet);
}

//���� ���ֵ 
void stt_xml_serialize_FaultGradientError(tmt_faultGradientParas *pParas,CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("��ѹ����ֵ�������","UActVal_AbsErr","","float",pParas->m_fUActVal_AbsErr);
	pXmlSierialize->xml_serialize("��ѹ����ֵ������","UActVal_RelErr","","float",pParas->m_fUActVal_RelErr);
	pXmlSierialize->xml_serialize("��ѹ����ֵ����ж��߼�","UActVal_ErrorLogic","","number",pParas->m_nUActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("��������ֵ�������","IActVal_AbsErr","","float",pParas->m_fIActVal_AbsErr);
	pXmlSierialize->xml_serialize("��������ֵ������","IActVal_RelErr","","float",pParas->m_fIActVal_RelErr);
	pXmlSierialize->xml_serialize("��������ֵ����ж��߼�","IActVal_ErrorLogic","","number",pParas->m_nIActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("�迹�Ƕ���ֵ�������", "ImpAngleActVal_AbsErr", "", "float", pParas->m_fImpAngleActVal_AbsErr);
	pXmlSierialize->xml_serialize("�迹�Ƕ���ֵ������", "ImpAngleActVal_RelErr", "", "float", pParas->m_fImpAngleActVal_RelErr);
	pXmlSierialize->xml_serialize("�迹�Ƕ���ֵ����ж��߼�", "ImpAngleActVal_ErrorLogic", "", "number", pParas->m_nImpAngleActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("��·�迹����ֵ�������", "ShortZImpActVal_AbsErr", "", "float", pParas->m_fShortZImpActVal_AbsErr);
	pXmlSierialize->xml_serialize("��·�迹����ֵ������", "ShortZImpActVal_RelErr", "", "float", pParas->m_fShortZImpActVal_RelErr);
	pXmlSierialize->xml_serialize("��·�迹����ֵ����ж��߼�", "ShortZImpActVal_ErrorLogic", "", "number", pParas->m_nShortZImpActVal_ErrorLogic);
	pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ�������","HzActVal_AbsErr","","float",pParas->m_fHzActVal_AbsErr);	
	pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ������","HzActVal_RelErr","","float",pParas->m_fHzActVal_RelErr);	
	pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ����ж��߼�","HzActVal_ErrorLogic","","number",pParas->m_nHzActVal_ErrorLogic);	
    pXmlSierialize->xml_serialize("�߽��1�������", "AngleF_AbsErr", "��", "float", pParas->m_fAngleF_AbsErr);
    pXmlSierialize->xml_serialize("�߽��1������", "AngleF_RelErr", "", "float", pParas->m_fAngleF_RelErr);
    pXmlSierialize->xml_serialize("�߽��1����ж��߼�", "AngleF_ErrorLogic", "", "number", pParas->m_nAngleF_ErrorLogic);
    pXmlSierialize->xml_serialize("�߽��2�������", "AngleS_AbsErr", "��", "float", pParas->m_fAngleS_AbsErr);
    pXmlSierialize->xml_serialize("�߽��2������", "AngleS_RelErr", "", "float", pParas->m_fAngleS_RelErr);
    pXmlSierialize->xml_serialize("�߽��2����ж��߼�", "AngleS_ErrorLogic", "", "number", pParas->m_nAngleS_ErrorLogic);
	pXmlSierialize->xml_serialize("��������Ǿ������","MaxAngle_AbsErr","��","float",pParas->m_fMaxAngle_AbsErr);	
	pXmlSierialize->xml_serialize("���������������","MaxAngle_RelErr","","float",pParas->m_fMaxAngle_RelErr);
	pXmlSierialize->xml_serialize("�������������ж��߼�","MaxAngle_ErrorLogic","","number",pParas->m_nMaxAngle_ErrorLogic);	
	pXmlSierialize->xml_serialize("����ϵ���������", "RetCoef_AbsErr", "", "float", pParas->m_fRetCoef_AbsErr);
	pXmlSierialize->xml_serialize("����ϵ��������", "RetCoef_RelErr", "", "float", pParas->m_fRetCoef_RelErr);
	pXmlSierialize->xml_serialize("����ϵ������ж��߼�", "RetCoef_ErrorLogic", "", "number", pParas->m_nRetCoef_ErrorLogic);

}

/////////////////////////////////////////////��� ��д
void stt_xml_serialize(tmt_faultGradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize)
{
	pXmlSierialize->xml_serialize("����ֵ","TripValue","A/V","number",pResults->m_fTripValue);
	pXmlSierialize->xml_serialize("����ʱ��","TripTime","s","number",pResults->m_fTripTime);
	pXmlSierialize->xml_serialize("����ֵ","ReturnValue","A/V","number",pResults->m_fReturnValue);
	pXmlSierialize->xml_serialize("����ϵ��","ReturnCoef","","number",pResults->m_fReturnCoef);
	pXmlSierialize->xml_serialize("��������","ActDsec","","number",pResults->m_nAct);

	pXmlSierialize->xml_serialize("��ѹ����ֵ���","TripUErrVal","","number",pResults->m_fTripUErrVal);
	pXmlSierialize->xml_serialize("��������ֵ���","TripIErrVal","","number",pResults->m_fTripIErrVal);
	pXmlSierialize->xml_serialize("Ƶ�ʶ���ֵ���","TripHzErrVal","","number",pResults->m_fTripHzErrVal);
	pXmlSierialize->xml_serialize("�迹�Ƕ���ֵ���", "ImpAngleErrVal", "", "number", pResults->m_fImpAngleErrVal);
	pXmlSierialize->xml_serialize("��·�迹����ֵ���", "ImpAngleErrVal", "", "number", pResults->m_fShortZImp);
//	pXmlSierialize->xml_serialize("��λ����ֵ���","TripAngleErrVal","","number",pResults->m_fTripAngleErrVal);
	pXmlSierialize->xml_serialize("����ϵ�����","RetCoefErrVal","","number",pResults->m_fRetCoefErrVal);
	pXmlSierialize->xml_serialize("������������","MaxAngleErrVal","","number",pResults->m_fMaxAngleErrVal);
//	pXmlSierialize->xml_serialize("�߽��1���","AngleFErrVal","","number",pResults->m_fAngleFErrVal);
//	pXmlSierialize->xml_serialize("�߽��2���","AngleSErrVal","","number",pResults->m_fAngleSErrVal);

	pXmlSierialize->xml_serialize("����1����ֵ","TripValueA","A/V","number",pResults->m_fTripValueChl[0]);
	pXmlSierialize->xml_serialize("����2����ֵ","TripValueB","A/V","number",pResults->m_fTripValueChl[1]);
	pXmlSierialize->xml_serialize("����3����ֵ","TripValueC","A/V","number",pResults->m_fTripValueChl[2]);
	pXmlSierialize->xml_serialize("����4����ֵ","TripValueD","A/V","number",pResults->m_fTripValueChl[3]);
	pXmlSierialize->xml_serialize("����5����ֵ","TripValueE","A/V","number",pResults->m_fTripValueChl[4]);
	pXmlSierialize->xml_serialize("����6����ֵ","TripValueF","A/V","number",pResults->m_fTripValueChl[5]);
	pXmlSierialize->xml_serialize("����7����ֵ","TripValueG","A/V","number",pResults->m_fTripValueChl[6]);
	pXmlSierialize->xml_serialize("����8����ֵ","TripValueH","A/V","number",pResults->m_fTripValueChl[7]);

	pXmlSierialize->xml_serialize("�߽��1","AngleF","","number",pResults->m_oMaxAngle.m_fAngleF);
	pXmlSierialize->xml_serialize("�߽��2","AngleS","","number",pResults->m_oMaxAngle.m_fAngleS);
	pXmlSierialize->xml_serialize("���������","MaxAngle","","number",pResults->m_oMaxAngle.m_fMaxAngle);

	if (g_nBinExCount>0)
	{
		CSttXmlSerializeBase *pXmlTripValueEx = pXmlSierialize->xml_serialize("TripValueEx", "TripValueEx", "TripValueEx", stt_ParaGroupKey());

		if (pXmlTripValueEx != NULL)
		{
			CString strName,strID,strTemp;

			CString str1 = _T("����");
			CString str1Ex = _T("������չ");
			CString str2 = _T("����ֵ");

			for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
			{
				strTemp.Format(_T("%d"),nIndex+1);
				strName = str1Ex + strTemp + str2;

				strID.Format("TripValueEx%d",(nIndex+1));
				pXmlTripValueEx->xml_serialize(strName.GetString(),strID.GetString(),"","A/V",pResults->m_fTripValueExChl[nIndex]);
			}
		}
	}
}

#include"../../../Module/API/GlobalConfigApi.h"
void stt_xml_serialize_write_FaultGradientTest()
{
	tmt_faultGradientTest oFGTest;
	oFGTest.init();
	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttTestCmd oSttTestCmd;
	CSttMacro *pMacro = oSttTestCmd.GetSttMacro();
	pMacro->GetParas();
	pMacro->GetResults();
	oSttXmlSerializeTool.CreateXmlSerializeWrite(&oSttTestCmd);
	CSttXmlSerializeBase *pMacroXml = oSttXmlSerializeTool.GetMacro();
	CSttXmlSerializeBase *pMacroParas = oSttXmlSerializeTool.GetMacroParas();
	stt_xml_serialize(&oFGTest.m_oFaultGradientParas, pMacroParas);

	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("FaultGradientTestDemo.xml");

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}


