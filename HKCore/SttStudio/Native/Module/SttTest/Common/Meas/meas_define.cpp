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
		strName=_T("直流分量");
		break;
	case 1:
		strName=_T("基波");
		break;
	default:
		strName.Format("%d次谐波",nIndex);
	}

	CString strID;
	strID.Format("Harm%d",nIndex);
	CSttXmlSerializeBase *pXmlVector = pXmlSerialize->xml_serialize(strName.GetString(), strID.GetString(), "Harm", stt_ParaGroupKey());

	pXmlVector->xml_serialize("幅值","Mag","","float", pVector->fAmp);
	pXmlVector->xml_serialize("相位","Angle","","float", pVector->fAngle);
	pXmlVector->xml_serialize("频率","Freq","","float", pVector->fFreq);
}

void stt_xml_serialize(MEAS_CHANNEL *pChannel, long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
	CString strName;
	strName.Format("通道%d",nIndex+1);
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
	strName.Format("模块%d",nIndex+1);
	CString strID;
	strID.Format("Module%d",nIndex);
	CSttXmlSerializeBase *pXmlModule = pXmlSerialize->xml_serialize(strName.GetString(), strID.GetString(), "Module", stt_ParaGroupKey());
	pXmlModule->xml_serialize("模块位置","ModulePos","","long", pModule->nModulePos);
	stt_xml_serialize_data_type(pXmlModule, "模块类型","ModuleType","","ModuleType", pModule->nModuleType);

	for(long i=0;i<pModule->nChanCount;i++)
	{
		stt_xml_serialize(&pModule->oChannels[i],i,pXmlModule);
	}
}

void stt_xml_serialize(MEAS_DEVICE *pMeasDevice, CSttXmlSerializeBase *pXmlSerialize)
{
	pXmlSerialize->xml_serialize("模块数量","ModuleCount","","long", pMeasDevice->nModuleCnt);

	long nIndex = 0;
	for (nIndex=0; nIndex<pMeasDevice->nModuleCnt; nIndex++)
	{
		stt_xml_serialize(&pMeasDevice->oModules[nIndex], nIndex,pXmlSerialize);
	}
}

void stt_xml_serialize_register_meas(CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pDevice = pXmlSerialize->xml_serialize("模拟量插件采集数据", "ModuleMeas", "ModuleMeas", stt_ParaGroupKey());

	stt_xml_serialize(g_MeasDevice, pDevice);
}
