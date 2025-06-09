#include "stdafx.h"
#include "meas_define.h"
#include "../tmt_adjust_sys_parameter.h"


MEAS_DEVICE *g_MeasDevice = NULL;

void stt_xml_serialize(MEAS_CHANNEL_VECTOR *pVector, long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
	CString strName;
	switch(nIndex)
	{
	case 0:
		strName=_T("ֱ������");
		break;
	case 1:
		strName=_T("����");
		break;
	default:
		strName.Format("%d��г��",nIndex);
	}

	CString strID;
	strID.Format("Harm%d",nIndex);
	CSttXmlSerializeBase *pXmlVector = pXmlSerialize->xml_serialize(strName.GetString(), strID.GetString(), "Harm", stt_ParaGroupKey());

	pXmlVector->xml_serialize("��ֵ","Mag","","float", pVector->fAmp);
	pXmlVector->xml_serialize("��λ","Angle","","float", pVector->fAngle);
	pXmlVector->xml_serialize("Ƶ��","Freq","","float", pVector->fFreq);
}

void stt_xml_serialize(MEAS_CHANNEL *pChannel, long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
	CString strName;
	strName.Format("ͨ��%d",nIndex+1);
	CString strID;
	strID.Format("Channel%d",nIndex);
	CSttXmlSerializeBase *pXmlChannel = pXmlSerialize->xml_serialize(strName.GetString(), strID.GetString(), "Channel", stt_ParaGroupKey());

	for(long i=0;i<pChannel->nHarmCount;i++)
	{
		stt_xml_serialize(&pChannel->oVector[i],i,pXmlChannel);
	}
}

void stt_xml_serialize(MEAS_MODULE *pModule, long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
	CString strName;
	strName.Format("ģ��%d",nIndex+1);
	CString strID;
	strID.Format("Module%d",nIndex);
	CSttXmlSerializeBase *pXmlModule = pXmlSerialize->xml_serialize(strName.GetString(), strID.GetString(), "Module", stt_ParaGroupKey());
	pXmlModule->xml_serialize("ģ��λ��","ModulePos","","long", pModule->nModulePos);
	stt_xml_serialize_data_type(pXmlModule, "ģ������","ModuleType","","ModuleType", pModule->nModuleType);

	for(long i=0;i<pModule->nChanCount;i++)
	{
		stt_xml_serialize(&pModule->oChannels[i],i,pXmlModule);
	}
}

void stt_xml_serialize(MEAS_DEVICE *pMeasDevice, CSttXmlSerializeBase *pXmlSerialize)
{
	pXmlSerialize->xml_serialize("ģ������","ModuleCount","","long", pMeasDevice->nModuleCnt);

	long nIndex = 0;
	for (nIndex=0; nIndex<pMeasDevice->nModuleCnt; nIndex++)
	{
		stt_xml_serialize(&pMeasDevice->oModules[nIndex], nIndex,pXmlSerialize);
	}
}

void stt_xml_serialize_register_meas(CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pDevice = pXmlSerialize->xml_serialize("ģ��������ɼ�����", "ModuleMeas", "ModuleMeas", stt_ParaGroupKey());

	stt_xml_serialize(g_MeasDevice, pDevice);
}
