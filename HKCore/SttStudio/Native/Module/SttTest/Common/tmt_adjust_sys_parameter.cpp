#include "stdafx.h"
#include "tmt_adjust_sys_parameter.h"
#include "../../Module/DataMngr/DataGroup.h"
#include "../../Module/API/GlobalConfigApi.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

long g_dwSttAdjSysParaCurrVersion = STT_ADJUST_SYS_PARA_VERSION_1_0;
#ifdef _PSX_IDE_QT_
bool g_bWriteHdInfor=TRUE;
#else
BOOL g_bWriteHdInfor=TRUE;
#endif

#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/Module/FpgaUart/FpgaUart.h"
#endif
#endif
PSTT_DEVICESYSTEMPARAMETER g_theDeviceSystemParameter = NULL;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
bool stt_open_adjust_file(const char *pszFileName)
{
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += pszFileName;
	return stt_open_adjust_file_path(strXMLPath);
}

bool stt_open_adjust_file_path(const CString &strFilePath)
{
	stt_create_adjust(1, 2, 32, 1, 1);

	if (g_theDeviceSystemParameter == NULL)
	{
		return  false;
	}

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CSttXmlSerializeBase *pSttXmlSerialize = oSttXmlSerializeTool.CreateXmlSerializeRead(CDataMngrXmlRWKeys::CDataGroupKey(), strFilePath);

	if(pSttXmlSerialize==NULL)
	{//û��У׼ϵ���ļ�����ʾ����Ϊ�ջ�������ʱӦ�ø��ݻ�õ�Ӳ����Դ����һ��ȱʡ��У׼ϵ���ļ�������Ϊ��ʼ�������ݡ�
		//��ʱ��ģ���У׼ϵ���汾��Ϊ-1����ʾΪȱʡ��ϵ���ļ������û�а汾��������ݶ������ʾΪ�ϰ汾��ϵ���ļ�����ʱ�汾��Ϊ0
		return false;
	}

	stt_xml_serialize(g_theDeviceSystemParameter, pSttXmlSerialize);
	g_theDeviceSystemParameter->init_after_read();
	g_theDeviceSystemParameter->init_hd_ch_id();  //��ʼ��Ӳ��ͨ��
	return true;
}

void stt_xml_serialize_write_adjust()
{
	PSTT_DEVICESYSTEMPARAMETER pDvSysParameter = NULL;
	pDvSysParameter = stt_create_adjust(1, 2, 32, 1, 1);

	if (pDvSysParameter == NULL)
	{
		return;
	}

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CDataGroup oDataGroup;
	oDataGroup.m_strID = "Device";
	oDataGroup.m_strName = "Device";
	oDataGroup.m_strDataType = "Device";
	CSttXmlSerializeBase *pSttXmlSerialize = oSttXmlSerializeTool.CreateXmlSerializeWrite(&oDataGroup);

	stt_xml_serialize(pDvSysParameter, pSttXmlSerialize);
	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += ("DeviceSystemParas.xml");

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
}

void stt_create_adjust_ex()
{
	PSTT_DEVICESYSTEMPARAMETER pDvSysParameter = NULL;
	pDvSysParameter = stt_create_adjust(1, 2, 32, 1, 1);
}

void stt_xml_serialize_register_adjust(const CString &strXMLPath)
{
	PSTT_DEVICESYSTEMPARAMETER pDvSysParameter = NULL;
	pDvSysParameter = stt_create_adjust(1, 2, 32, 1, 1);

	if (pDvSysParameter == NULL)
	{
		return;
	}

	CSttXmlSerializeTool oSttXmlSerializeTool;
	CDataGroup oDataGroup;
	oDataGroup.m_strID = "Device";
	oDataGroup.m_strName = "Device";
	oDataGroup.m_strDataType = "Device";
	CSttXmlSerializeBase *pSttXmlSerialize = oSttXmlSerializeTool.CreateXmlSerializeRegister(&oDataGroup);

	stt_xml_serialize(pDvSysParameter, pSttXmlSerialize);

	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);
#ifdef _PSX_QT_LINUX_
	system("sync");
#endif
}

void stt_xml_serialize_register_adjust(CSttXmlSerializeTool &oSttXmlSerializeTool)
{
	stt_create_adjust();

	CDataGroup oDataGroup;
	oDataGroup.m_strID = "Device";
	oDataGroup.m_strName = "Device";
	oDataGroup.m_strDataType = "Device";
	CSttXmlSerializeBase *pSttXmlSerialize = oSttXmlSerializeTool.CreateXmlSerializeRegister(&oDataGroup);

	stt_xml_serialize(g_theDeviceSystemParameter, pSttXmlSerialize);
}

void stt_xml_serialize_register_adjust(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_create_adjust();

	//2021-5-5  lijunqing ����Device���ڵ�
	CSttXmlSerializeBase *pDevice = pXmlSerialize->xml_serialize("Device", "Device", "Device", CDataMngrXmlRWKeys::CDataGroupKey());

	stt_xml_serialize(g_theDeviceSystemParameter, pDevice);
}


void stt_xml_serialize_register_adjust()
{
	PSTT_DEVICESYSTEMPARAMETER pDvSysParameter = NULL;
	pDvSysParameter = stt_create_adjust(1, 2, 32, 1, 1);

	if (pDvSysParameter == NULL)
	{
		return;
	}

	stt_save_adjust_file("DeviceSystemParas.xml");
	CSttXmlSerializeTool oSttXmlSerializeTool;
	stt_xml_serialize_register_adjust(oSttXmlSerializeTool);

#ifdef _PSX_QT_LINUX_
	system("sync");
#endif
}

bool stt_save_adjust_file(const char *pszFileName)
{
	if (g_theDeviceSystemParameter == NULL)
	{
		return  false;
	}

	CSttXmlSerializeTool oSttXmlSerializeTool;
	stt_xml_serialize_register_adjust(oSttXmlSerializeTool);

	CString strXMLPath;
	strXMLPath = _P_GetConfigPath();
	strXMLPath += pszFileName;
	oSttXmlSerializeTool.Stt_WriteFile(strXMLPath);

	return true;
}



void stt_init_paras(STT_DEVICESYSTEMPARAMETER *pParas)
{
	memset(&pParas, 0, sizeof(STT_DEVICESYSTEMPARAMETER));
	pParas->init();
}

void stt_xml_serialize_AdjItem(PSTT_ADJUST_ITEM pPara,  CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef NOT_USE_XLANGUAGE
	pXmlSerialize->xml_serialize("��ֵϵ��","Coef","","float",pPara->m_fCoef);
	pXmlSerialize->xml_serialize("��Ư","Zero","","float",pPara->m_fZero);
	pXmlSerialize->xml_serialize("��λ","Angle","","float",pPara->m_fAngle);
#else
	pXmlSerialize->xml_serialize(/*"��ֵϵ��"*/g_sLangTxt_Native_AmpFactor.GetString(),"Coef","","float",pPara->m_fCoef);
	pXmlSerialize->xml_serialize(/*"��Ư"*/g_sLangTxt_Gradient_ZeroDrift.GetString(),"Zero","","float",pPara->m_fZero);
	pXmlSerialize->xml_serialize(/*"��λ"*/g_sLangTxt_Native_Phase.GetString(),"Angle","","float",pPara->m_fAngle);
#endif
}

void stt_xml_serialize(PSTT_ADJUST_ITEM pPara,  CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlAdjItem =pXmlSerialize->xml_serialize("AdjustItem", "AdjustItem", "AdjustItem", stt_ParaGroupKey());

	if (pXmlAdjItem == NULL)
	{
		return;
	}

	stt_xml_serialize_AdjItem(pPara, pXmlAdjItem);
}

void stt_xml_serialize(PSTT_CHANNEL_GEAR_ADJUST pPara,  long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
	#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pXmlGear = pXmlSerialize->xml_serialize(stt_ParaGroupKey(),nIndex, "��λ", "Gear", "GearAdjust");

#else
	CSttXmlSerializeBase *pXmlGear = pXmlSerialize->xml_serialize(stt_ParaGroupKey(),nIndex, /*"��λ"*/g_sLangTxt_Native_Gear.GetString(), "Gear", "GearAdjust");
#endif
	if (pXmlGear == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlGear->xml_serialize("��λ","GearValue","","float",pPara->m_fGearValue);
#else
	pXmlGear->xml_serialize(/*"��λ"*/g_sLangTxt_Native_Gear.GetString(),"GearValue","","float",pPara->m_fGearValue);
#endif
	stt_xml_serialize(&pPara->m_oAdjItem, pXmlGear);
}

void stt_xml_serialize(PSTT_CHANNEL_WAVE_ADJUST pPara,  const char *pszName, const char *pszID, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlChWaveAdj =pXmlSerialize->xml_serialize(pszName, pszID, "ChWaveAdj", stt_ParaGroupKey());

	if (pXmlChWaveAdj == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlChWaveAdj->xml_serialize("��λ��","GearCount","","int", pPara->m_nGearCount);
#else
	pXmlChWaveAdj->xml_serialize(/*"��λ��"*/g_sLangTxt_Native_NumGears.GetString(),"GearCount","","int", pPara->m_nGearCount);
#endif

	long nIndex = 0;

	for (nIndex=0; nIndex<pPara->m_nGearCount; nIndex++)
	{
		stt_xml_serialize(&pPara->m_oChGearAdj[nIndex], nIndex, pXmlChWaveAdj);
	}
}

void stt_xml_serialize(PSTT_CHANNEL_ADJUSTS pPara,  const char *pszName, const char *pszID, long nHarmCount, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlChAdj =pXmlSerialize->xml_serialize(pszName, pszID, "ChannelAdj", stt_ParaGroupKey());

	if (pXmlChAdj == NULL)
	{
		return;
	}

	pPara->nHarmCount=nHarmCount+1;

	long nIndex = 0;
	if(pPara->m_pChWaveAdj==NULL)
	{
		pPara->m_pChWaveAdj = (PSTT_CHANNEL_WAVE_ADJUST)malloc((nHarmCount+1)*sizeof(STT_CHANNEL_WAVE_ADJUST));
		for (nIndex=0; nIndex < pPara->nHarmCount; nIndex++)
		{
			pPara->m_pChWaveAdj[nIndex].init();
		}
	}
#ifdef NOT_USE_XLANGUAGE
    pXmlChAdj->xml_serialize("Ӳ��1��ֱ����Ư","DcZero","","float", pPara->m_fDcZero[0]);
    pXmlChAdj->xml_serialize("Ӳ��2��ֱ����Ư","DcZero2","","float", pPara->m_fDcZero[1]);
    pXmlChAdj->xml_serialize("Ӳ��3��ֱ����Ư","DcZero3","","float", pPara->m_fDcZero[2]);
	pXmlChAdj->xml_serialize("�����������ϵ��","LargeCurrentRatio","","float", pPara->m_fLargeCurrentRatio);
#else
	pXmlChAdj->xml_serialize(/*"Ӳ��1��ֱ����Ư"*/g_sLangTxt_Native_HW1DCZeroDrift.GetString(),"DcZero","","float", pPara->m_fDcZero[0]);
	pXmlChAdj->xml_serialize(/*"Ӳ��2��ֱ����Ư"*/g_sLangTxt_Native_HW2DCZeroDrift.GetString(),"DcZero2","","float", pPara->m_fDcZero[1]);
	pXmlChAdj->xml_serialize(/*"Ӳ��3��ֱ����Ư"*/g_sLangTxt_Native_HW3DCZeroDrift.GetString(),"DcZero3","","float", pPara->m_fDcZero[2]);
	pXmlChAdj->xml_serialize(/*"�����������ϵ��"*/g_sLangTxt_Native_LCNLCoeff.GetString(),"LargeCurrentRatio","","float", pPara->m_fLargeCurrentRatio);
#endif

	if(pPara->nHarmCount >= 2)
	{
		stt_xml_serialize(&pPara->m_pChWaveAdj[0], "DC", "DC", pXmlChAdj);
		stt_xml_serialize(&pPara->m_pChWaveAdj[1], "Base", "Base", pXmlChAdj);
	}

	CString strName, strID;
	for (nIndex=2; nIndex < pPara->nHarmCount; nIndex++)
	{
#ifdef NOT_USE_XLANGUAGE
		strName.Format("%d��г��", nIndex);
#else
		strName.Format(/*"%d��г��"*/g_sLangTxt_Native_NthHarmonic.GetString(), nIndex);
#endif
		strID.Format("H%d", nIndex);
		stt_xml_serialize(&pPara->m_pChWaveAdj[nIndex], strName.GetString(), strID.GetString(), pXmlChAdj);
	}
}

void stt_xml_serialize(PSTT_TRANGE_ADJUST pPara, long nIndex, long nHarmCount, long nChannelNum, CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pXmlTemperatureAdj = pXmlSerialize->xml_serialize( stt_ParaGroupKey(), nIndex ,"����", "T","T_Range");
#else
	CSttXmlSerializeBase *pXmlTemperatureAdj = pXmlSerialize->xml_serialize( stt_ParaGroupKey(), nIndex ,/*"����"*/g_sLangTxt_Native_TempZone.GetString(), "T","T_Range");
#endif
	if (pXmlTemperatureAdj == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlTemperatureAdj->xml_serialize("�¶�","Temperature","","float", pPara->m_fTemperature);
#else
	pXmlTemperatureAdj->xml_serialize(/*"�¶�"*/g_sLangTxt_Native_Temp.GetString(),"Temperature","","float", pPara->m_fTemperature);
#endif
	stt_xml_serialize(&pPara->m_oChIdcAdj, "Idc", "Idc",  pXmlTemperatureAdj);
	stt_xml_serialize(&pPara->m_oChUdcAdj, "Udc", "Udc",  pXmlTemperatureAdj);

	if(stt_xml_serialize_is_read(pXmlTemperatureAdj))
	{
		if(pPara->m_pChsAdjust != NULL)
		{
			for(long nChannel=0;nChannel < pPara->nChannelNum;nChannel++)
			{
				if(pPara->m_pChsAdjust[nChannel].m_pChWaveAdj != NULL)
					free(pPara->m_pChsAdjust[nChannel].m_pChWaveAdj);
			}
			free(pPara->m_pChsAdjust);
			pPara->m_pChsAdjust = NULL;
		}
	}

	if(pPara->m_pChsAdjust==NULL)
	{
		pPara->m_pChsAdjust=(PSTT_CHANNEL_ADJUSTS)malloc(nChannelNum*sizeof(STT_CHANNEL_ADJUSTS));
	}
	pPara->nChannelNum = nChannelNum;

	nIndex = 0;
	CString strName, strID;

	for (nIndex=0; nIndex < nChannelNum; nIndex++)
	{
		if(stt_xml_serialize_is_read(pXmlTemperatureAdj))
			pPara->m_pChsAdjust[nIndex].init();
#ifdef NOT_USE_XLANGUAGE
		strName.Format("ͨ��%d", nIndex+1);
#else
		strName.Format(/*"ͨ��%d"*/g_sLangTxt_Native_ChnN.GetString(), nIndex+1);
#endif
		strID.Format("Ch%d", nIndex);
		stt_xml_serialize(&pPara->m_pChsAdjust[nIndex], strName.GetString(), strID.GetString(), nHarmCount, pXmlTemperatureAdj);
	}
}

void stt_xml_serialize(PSTT_HD_GEAR pPara, long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlHdGear = pXmlSerialize->xml_serialize( stt_ParaGroupKey(), nIndex,"HdGear", "HdGear", "HdGear");

	if (pXmlHdGear == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlHdGear->xml_serialize("��λID","GearID","","long", pPara->m_nGearID);
	pXmlHdGear->xml_serialize("��λֵ","GearValue","","float", pPara->m_fGearValue);
#else
	pXmlHdGear->xml_serialize(/*"��λID"*/g_sLangTxt_Native_GearID.GetString(),"GearID","","long", pPara->m_nGearID);
	pXmlHdGear->xml_serialize(/*"��λֵ"*/g_sLangTxt_Native_GearVal.GetString(),"GearValue","","float", pPara->m_fGearValue);
#endif
}


void stt_xml_serialize(PSTT_HD_GEARS pPara,  const char *pszName, const char *pszID, CSttXmlSerializeBase *pXmlSerialize)
{
	CSttXmlSerializeBase *pXmlHdGears = pXmlSerialize->xml_serialize(pszName, pszID,  "HdGears", stt_ParaGroupKey());

	if (pXmlHdGears == NULL)
	{
		return;
	}

	long nIndex = 0;
#ifdef NOT_USE_XLANGUAGE
	pXmlHdGears->xml_serialize("Ӳ����λ��","HdGearCount","","long", pPara->m_nHdGearCount);
#else
	pXmlHdGears->xml_serialize(/*"Ӳ����λ��"*/g_sLangTxt_Native_HwGearCount.GetString(),"HdGearCount","","long", pPara->m_nHdGearCount);
#endif

	for (nIndex=0; nIndex<pPara->m_nHdGearCount; nIndex++)
	{
		stt_xml_serialize(&pPara->m_oHdGear[nIndex], nIndex, pXmlHdGears);
	}
}


void stt_xml_serialize(PSTT_MODULE_ADJUST  pPara,  CSttXmlSerializeBase *pXmlSerialize, long nChannelNum, long HarmCount)
{
	if (g_theAdjParaXmlSerialConfig.m_nModuleAdjusts == 0)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pXmlModuleAdj = pXmlSerialize->xml_serialize("У׼ϵ��", "AdjustParas", "AdjustParas", stt_ParaGroupKey());
#else
	CSttXmlSerializeBase *pXmlModuleAdj = pXmlSerialize->xml_serialize(/*"У׼ϵ��"*/g_sLangTxt_Native_CalibCoeff.GetString(), "AdjustParas", "AdjustParas", stt_ParaGroupKey());
#endif
	if (pXmlModuleAdj == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlModuleAdj->xml_serialize("������","TemperatureCount","","long", pPara->m_nTemperatureCount);
#else
	pXmlModuleAdj->xml_serialize(/*"������"*/g_sLangTxt_Native_TempZoneCount.GetString(),"TemperatureCount","","long", pPara->m_nTemperatureCount);
#endif
	long nIndex = 0;

	for (nIndex=0; nIndex < pPara->m_nTemperatureCount; nIndex++)
	{
		stt_xml_serialize(&pPara->m_oTempAdjust[nIndex], nIndex, HarmCount, nChannelNum, pXmlModuleAdj);
	}

}

void stt_xml_serialize(PSTT_MODULE_CH_DEF  pPara,  long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pXmlHdCh = pXmlSerialize->xml_serialize( stt_ParaGroupKey(),nIndex, "Ӳ��ͨ��", "HdCh", "HdCh");
#else
		CSttXmlSerializeBase *pXmlHdCh = pXmlSerialize->xml_serialize( stt_ParaGroupKey(),nIndex, /*"Ӳ��ͨ��"*/g_sLangTxt_Native_HwChannel.GetString(), "HdCh", "HdCh");
#endif
	if (pXmlHdCh  == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlHdCh->xml_serialize("ͨ��ID","ID","","string", pPara->m_pszChId);
	pXmlHdCh->xml_serialize("ͨ������","Index","","long", pPara->m_nChIndex);
	pXmlHdCh->xml_serialize("�����������Դ","ChRsIndex","","long", pPara->m_nChRsIndex);
	pXmlHdCh->xml_serialize("�������ֵ","ChACMaxValue","","float", pPara->m_fChACMaxValue);
	pXmlHdCh->xml_serialize("ֱ�����ֵ","ChDCMaxValue","","float", pPara->m_fChDCMaxValue);
#else
	pXmlHdCh->xml_serialize(/*"ͨ��ID"*/g_sLangTxt_Native_ChnID.GetString(),"ID","","string", pPara->m_pszChId);
	pXmlHdCh->xml_serialize(/*"ͨ������"*/g_sLangTxt_Native_ChnIndex.GetString(),"Index","","long", pPara->m_nChIndex);
	pXmlHdCh->xml_serialize(/*"�����������Դ"*/g_sLangTxt_Native_AssocSWRes.GetString(),"ChRsIndex","","long", pPara->m_nChRsIndex);
	pXmlHdCh->xml_serialize(/*"�������ֵ"*/g_sLangTxt_Native_ACMaxValue.GetString(),"ChACMaxValue","","float", pPara->m_fChACMaxValue);
	pXmlHdCh->xml_serialize(/*"ֱ�����ֵ"*/g_sLangTxt_Native_DCMaxValue.GetString(),"ChDCMaxValue","","float", pPara->m_fChDCMaxValue);
#endif
	if(stt_xml_serialize_is_read(pXmlSerialize))
	{
		pPara->m_nChMeasPos = nIndex;//20220211 zhoulei Ĭ��ֵ,�����ϰ汾
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlHdCh->xml_serialize("ͨ���ɼ�ӳ��λ��","ChMeasPos","","long", pPara->m_nChMeasPos);//20220211zhoulei
#else
		pXmlHdCh->xml_serialize(/*"ͨ���ɼ�ӳ��λ��"*/g_sLangTxt_Native_ChAcqMapLoc.GetString(),"ChMeasPos","","long", pPara->m_nChMeasPos);//20220211zhoulei
#endif
	//pXmlHdCh->xml_serialize("����ģʽ","WorkMode","","WorkMode", pPara->m_nWorkMode);
	//pXmlHdCh->xml_serialize("��������","EeType","","EeType", pPara->m_nEeType);
	//2021-5-4  lijunqing  ��������  ��׼ID������֮���ת��
#ifdef NOT_USE_XLANGUAGE
	stt_xml_serialize_data_type(pXmlHdCh, "����ģʽ","WorkMode","","WorkMode", pPara->m_nWorkMode);
#else
	stt_xml_serialize_data_type(pXmlHdCh, /*"����ģʽ"*/g_sLangTxt_Native_OpMode.GetString(),"WorkMode","","WorkMode", pPara->m_nWorkMode);
#endif
	if(stt_xml_serialize_is_read(pXmlSerialize))
	{
		pPara->m_nEeType = 0;//20220209 zhoulei ���ļ�ʱ���������״̬
	}
#ifdef NOT_USE_XLANGUAGE
	stt_xml_serialize_data_type(pXmlHdCh, "��������","EeType","","EeType", pPara->m_nEeType);
#else
	stt_xml_serialize_data_type(pXmlHdCh, /*"��������"*/g_sLangTxt_Native_ElecType.GetString(),"EeType","","EeType", pPara->m_nEeType);
#endif
}

void stt_xml_serialize(PSTT_MODULE_CH_DEFS  pPara,  CSttXmlSerializeBase *pXmlSerialize, long nChannelNum)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pXmlChMaps = pXmlSerialize->xml_serialize("Ӳ��ͨ������", "ChDefine", "ChDefine", stt_ParaGroupKey());
#else
	CSttXmlSerializeBase *pXmlChMaps = pXmlSerialize->xml_serialize(/*"Ӳ��ͨ������"*/g_sLangTxt_Native_HwChDef.GetString(), "ChDefine", "ChDefine", stt_ParaGroupKey());
#endif
	if (pXmlChMaps  == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlChMaps->xml_serialize("ͨ����","ChannelNum","","long", nChannelNum);
#else
	pXmlChMaps->xml_serialize(/*"ͨ����"*/g_sLangTxt_IEC_ChannelNumber.GetString(),"ChannelNum","","long", nChannelNum);
#endif
	long nIndex = 0;

	for (nIndex=0; nIndex < nChannelNum; nIndex++)
	{
		stt_xml_serialize(&pPara->m_oChDef[nIndex], nIndex, pXmlChMaps);
	}
}

//void stt_xml_serialize(PSTT_MODULE_CH_GROUP  pPara,  long nIndex, CSttXmlSerializeBase *pXmlSerialize)
//{
//	CSttXmlSerializeBase *pXmlChGroup = pXmlSerialize->xml_serialize("ͨ������", "ChGroup", nIndex, "ChGroup", stt_ParaGroupKey());

//	if (pXmlChGroup  == NULL)
//	{
//		return;
//	}

//	pXmlChGroup->xml_serialize("ͨ��1","Ch1","","string", pPara->m_pszCh1ID);
//	pXmlChGroup->xml_serialize("ͨ��2","Ch2","","string", pPara->m_pszCh2ID);
//	pXmlChGroup->xml_serialize("ͨ��3","Ch3","","string", pPara->m_pszCh3ID);
//}

//void stt_xml_serialize(PSTT_MODULE_CH_GROUPS  pPara,  CSttXmlSerializeBase *pXmlSerialize)
//{
//	CSttXmlSerializeBase *pXmlChGroups = pXmlSerialize->xml_serialize("ͨ�����鶨��", "ChGroups", "ChGroups", stt_ParaGroupKey());

//	if (pXmlChGroups  == NULL)
//	{
//		return;
//	}

//	pXmlChGroups->xml_serialize("������","ChGroupCount","","long", pPara->m_nChGroupCount);

//	long nIndex = 0;

//	for (nIndex=0; nIndex < pPara->m_nChGroupCount; nIndex++)
//	{
//		stt_xml_serialize(&pPara->m_oChGroups[nIndex], nIndex, pXmlChGroups);
//	}
//}

void stt_xml_serialize(PSTT_CH_DRV_POS  pPara,  CSttXmlSerializeBase *pXmlSerialize, long nChannelNum)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pXmlChGroups = pXmlSerialize->xml_serialize("ͨ������λ��", "ChDrvPos", "ChDrvPos", stt_ParaGroupKey());
#else
	CSttXmlSerializeBase *pXmlChGroups = pXmlSerialize->xml_serialize(/*"ͨ������λ��"*/g_sLangTxt_Native_ChDrivePos.GetString(), "ChDrvPos", "ChDrvPos", stt_ParaGroupKey());
#endif
	if (pXmlChGroups  == NULL)
	{
		return;
	}

	//20220216 zhoulei ����12·ֱ��С�ź�
	CString strName,strID;
	for(int nIndex=0;nIndex<nChannelNum;nIndex++)
	{
#ifdef NOT_USE_XLANGUAGE
		strName.Format(_T("ͨ��%dλ��"),nIndex+1);
#else
		strName.Format(/*_T("ͨ��%dλ��")*/g_sLangTxt_Native_ChPos.GetString(),nIndex+1);
#endif
		strID.Format(_T("Ch%dPos"),nIndex+1);
		pXmlChGroups->xml_serialize(strName.GetString(),strID.GetString(),"","long", pPara->m_nChDrvPos[nIndex]);
	}
//	pXmlChGroups->xml_serialize("ͨ��1λ��","Ch1Pos","","long", pPara->m_nChDrvPos[0]);
//	pXmlChGroups->xml_serialize("ͨ��2λ��","Ch2Pos","","long", pPara->m_nChDrvPos[1]);
//	pXmlChGroups->xml_serialize("ͨ��3λ��","Ch3Pos","","long", pPara->m_nChDrvPos[2]);
//	pXmlChGroups->xml_serialize("ͨ��4λ��","Ch4Pos","","long", pPara->m_nChDrvPos[3]);
//	pXmlChGroups->xml_serialize("ͨ��5λ��","Ch5Pos","","long", pPara->m_nChDrvPos[4]);
//	pXmlChGroups->xml_serialize("ͨ��6λ��","Ch6Pos","","long", pPara->m_nChDrvPos[5]);
}

void stt_xml_serialize(PSTT_MODULE_CH_MAP_DEF  pPara,  CSttXmlSerializeBase *pXmlSerialize, long nChannelNum)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pXmlChMapDef = pXmlSerialize->xml_serialize("ͨ��ӳ�䶨��", "ChMapDef", "ChMapDef", stt_ParaGroupKey());
#else
	CSttXmlSerializeBase *pXmlChMapDef = pXmlSerialize->xml_serialize(/*"ͨ��ӳ�䶨��"*/g_sLangTxt_Native_ChMapDef.GetString(), "ChMapDef", "ChMapDef", stt_ParaGroupKey());
#endif
	if (pXmlChMapDef  == NULL)
	{
		return;
	}

	//	stt_xml_serialize(&pPara->m_oChMaps, pXmlChMapDef);
	stt_xml_serialize(&pPara->m_oChDefs, pXmlChMapDef, nChannelNum);
	stt_xml_serialize(&pPara->m_oChDrvPos, pXmlChMapDef, nChannelNum);
}

void stt_xml_serialize(PST_MODULE_ATTR  pPara,  CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pXmlModuleAttrs = pXmlSerialize->xml_serialize("ģ������", "ModuleAttrs", "ModuleAttrs", stt_ParaGroupKey());
#else
	CSttXmlSerializeBase *pXmlModuleAttrs = pXmlSerialize->xml_serialize(/*"ģ������"*/g_sLangTxt_Native_ModProps.GetString(), "ModuleAttrs", "ModuleAttrs", stt_ParaGroupKey());
#endif
	if (pXmlModuleAttrs == NULL)
	{
		return;
	}

	if (g_theAdjParaXmlSerialConfig.m_nModuleAttr != 0)
	{
		//2021-5-4  lijunqing  ��������  ��׼ID������֮���ת��
#ifdef NOT_USE_XLANGUAGE
		stt_xml_serialize_data_type(pXmlModuleAttrs, "ģ������","ModuleType","","ModuleType", pPara->m_nModuleType);
		pXmlModuleAttrs->xml_serialize("�ͺ�","Model","","string", pPara->m_strModelName);
		pXmlModuleAttrs->xml_serialize("��������","Factory","","Factory", pPara->m_strFactory);
		pXmlModuleAttrs->xml_serialize("��������","DateFac","","DateProduce", pPara->m_strDateProduce);
		pXmlModuleAttrs->xml_serialize("���к�","SN","","string", pPara->m_strModuleSN);
		pXmlModuleAttrs->xml_serialize("ģ��λ��","ModulePos","","long", pPara->m_nModuleIndex);
#else
		stt_xml_serialize_data_type(pXmlModuleAttrs, /*"ģ������"*/g_sLangTxt_Gradient_ModuleType.GetString(),"ModuleType","","ModuleType", pPara->m_nModuleType);
		pXmlModuleAttrs->xml_serialize(/*"�ͺ�"*/g_sLangTxt_Report_AppModel.GetString(),"Model","","string", pPara->m_strModelName);
		pXmlModuleAttrs->xml_serialize(/*"��������"*/g_sLangTxt_Report_DeviceFactory.GetString(),"Factory","","Factory", pPara->m_strFactory);
		pXmlModuleAttrs->xml_serialize(/*"��������"*/g_sLangTxt_Gradient_ManufactDate.GetString(),"DateFac","","DateProduce", pPara->m_strDateProduce);
		pXmlModuleAttrs->xml_serialize(/*"���к�"*/g_sLangTxt_Report_AppSN.GetString(),"SN","","string", pPara->m_strModuleSN);
		pXmlModuleAttrs->xml_serialize(/*"ģ��λ��"*/g_sLangTxt_Native_ModPos.GetString(),"ModulePos","","long", pPara->m_nModuleIndex);
#endif
		if(pPara->m_nModuleType==STT_MODULE_TYPE_DIGITAL_0G8M
				||pPara->m_nModuleType==STT_MODULE_TYPE_DIGITAL_2G6M
				||pPara->m_nModuleType==STT_MODULE_TYPE_DIGITAL_4G4M
				||pPara->m_nModuleType==STT_MODULE_TYPE_FT3
                ||pPara->m_nModuleType==STT_MODULE_TYPE_SWITCH
				||pPara->m_nModuleType==STT_MODULE_TYPE_Stable2M)
		{
			pPara->m_nChannelNum = 0;
			pPara->m_nHarmCount = 0;

            if(stt_xml_serialize_is_read(pXmlModuleAttrs))
            {
                //��ģʽ���Ȱ�ģ�����ͳ�ʼ��
                if(pPara->m_nModuleType==STT_MODULE_TYPE_DIGITAL_0G8M
                        ||pPara->m_nModuleType==STT_MODULE_TYPE_DIGITAL_2G6M
                        ||pPara->m_nModuleType==STT_MODULE_TYPE_DIGITAL_4G4M)
                {
                    pPara->m_nFiberPortNum_LC = 8;
                    pPara->m_nFiberPortNum_STSend = 6;
                }
                else if(pPara->m_nModuleType==STT_MODULE_TYPE_FT3)
                {
                    pPara->m_nFiberPortNum_STSend = 12;
                    pPara->m_nFiberPortNum_STRecv = 4;
                }
            }

#ifdef NOT_USE_XLANGUAGE
            pXmlModuleAttrs->xml_serialize("LC�����","FiberPortNum_LC","","long", pPara->m_nFiberPortNum_LC);
            pXmlModuleAttrs->xml_serialize("ST���͹����","FiberPortNum_STSend","","long", pPara->m_nFiberPortNum_STSend);
            pXmlModuleAttrs->xml_serialize("ST���չ����","FiberPortNum_STRecv","","long", pPara->m_nFiberPortNum_STRecv);
#else
	    pXmlModuleAttrs->xml_serialize(/*"LC�����"*/g_sLangTxt_Native_LCOptPortCount.GetString(),"FiberPortNum_LC","","long", pPara->m_nFiberPortNum_LC);
		pXmlModuleAttrs->xml_serialize(/*"ST���͹����"*/g_sLangTxt_Native_STTxOptPortCount.GetString(),"FiberPortNum_STSend","","long", pPara->m_nFiberPortNum_STSend);
		pXmlModuleAttrs->xml_serialize(/*"ST���չ����"*/g_sLangTxt_Native_STRxOptPortCount.GetString(),"FiberPortNum_STRecv","","long", pPara->m_nFiberPortNum_STRecv);
#endif
		}
		else
		{
			if(pPara->m_nModuleType == STT_MODULE_TYPE_ADMU)
			{
				//��ģʽ���Ȱ�ģ�����ͳ�ʼ��
				if(stt_xml_serialize_is_read(pXmlModuleAttrs))
				{
					pPara->m_nFiberPortNum_LC = 0;
					pPara->m_nFiberPortNum_STSend = 1;
					pPara->m_nFiberPortNum_STRecv = 1;
				}
				pXmlModuleAttrs->xml_serialize("LC�����","FiberPortNum_LC","","long", pPara->m_nFiberPortNum_LC);
				pXmlModuleAttrs->xml_serialize("ST���͹����","FiberPortNum_STSend","","long", pPara->m_nFiberPortNum_STSend);
				pXmlModuleAttrs->xml_serialize("ST���չ����","FiberPortNum_STRecv","","long", pPara->m_nFiberPortNum_STRecv);
			}

#ifdef NOT_USE_XLANGUAGE
			pXmlModuleAttrs->xml_serialize("ͨ����","ChannelNum","","long", pPara->m_nChannelNum);
			BOOL bRet = pXmlModuleAttrs->xml_serialize("г����","HarmCount","","long", pPara->m_nHarmCount);
#else
			pXmlModuleAttrs->xml_serialize(/*"ͨ����"*/g_sLangTxt_IEC_ChannelNumber.GetString(),"ChannelNum","","long", pPara->m_nChannelNum);
			BOOL bRet = pXmlModuleAttrs->xml_serialize(/*"г����"*/g_sLangTxt_Native_HarmOrder.GetString(),"HarmCount","","long", pPara->m_nHarmCount);
#endif
			if(stt_xml_serialize_is_read(pXmlModuleAttrs)&&(!bRet))
				pPara->m_nHarmCount = ADJUST_MAX_HARM_COUNT;
		}
#ifdef NOT_USE_XLANGUAGE
//		pXmlModuleAttrs->xml_serialize("ֱ����ѹͨ�����ֵ","UdcMax","","float", pPara->m_fDCVoltMax);
//		pXmlModuleAttrs->xml_serialize("ֱ������ͨ�����ֵ","IdcMax","","float", pPara->m_fDCCurrMax);
		pXmlModuleAttrs->xml_serialize("����У׼�Ľ������ֵ","ChMax","","float", pPara->m_fChMax);
		pXmlModuleAttrs->xml_serialize("����У׼��ֱ�����ֵ","ChDcMax","","float", pPara->m_fChDcMax);
		if(stt_xml_serialize_is_read(pXmlModuleAttrs))
		{
			pPara->m_fDefChMax = pPara->m_fChMax;
			pPara->m_fDefChDcMax = pPara->m_fChDcMax;
		}
		pXmlModuleAttrs->xml_serialize("��������ƽ������ֵ","DefChMax","","float", pPara->m_fDefChMax);
		pXmlModuleAttrs->xml_serialize("���������ֱ�����ֵ","DefChDcMax","","float", pPara->m_fDefChDcMax);
		pXmlModuleAttrs->xml_serialize("Ƶ�ʲ���ϵ��","FreCoef","","float", pPara->m_fFreCoef);
		pXmlModuleAttrs->xml_serialize("����Ӳ����λ��ʱ","fDigitalDelay","","float", pPara->m_fDigitalDelay);
		stt_xml_serialize_data_type(pXmlModuleAttrs, "��ѹ����Ӳ������","ModulePower","","ModulePower", pPara->m_nModulePower);
		stt_xml_serialize_data_type(pXmlModuleAttrs, "����ͨ���ϲ�ģʽ","ChMergeMode","","ChMergeMode", pPara->m_nChMergeMode);
#else
//		pXmlModuleAttrs->xml_serialize(/*"ֱ����ѹͨ�����ֵ"*/g_sLangTxt_Native_DCVoltChMax.GetString(),"UdcMax","","float", pPara->m_fDCVoltMax);
//		pXmlModuleAttrs->xml_serialize(/*"ֱ������ͨ�����ֵ"*/g_sLangTxt_Native_DCCurrChMax.GetString(),"IdcMax","","float", pPara->m_fDCCurrMax);
		pXmlModuleAttrs->xml_serialize(/*"ͨ�����������ֵ"*/g_sLangTxt_Native_ChACOutMax.GetString(),"ChMax","","float", pPara->m_fChMax);
		pXmlModuleAttrs->xml_serialize(/*"ͨ����ֱ�����ֵ"*/g_sLangTxt_Native_ChDCOutMax.GetString(),"ChDcMax","","float", pPara->m_fChDcMax);
		pXmlModuleAttrs->xml_serialize(/*"Ƶ�ʲ���ϵ��"*/g_sLangTxt_Native_FreqCompCoeff.GetString(),"FreCoef","","float", pPara->m_fFreCoef);
		pXmlModuleAttrs->xml_serialize(/*"����Ӳ����λ��ʱ"*/g_sLangTxt_Native_DigiHWPhaseDelay.GetString(),"fDigitalDelay","","float", pPara->m_fDigitalDelay);
		//		pXmlModuleAttrs->xml_serialize("��ѹ����Ӳ������","ModulePower","","ModulePower", pPara->m_nModulePower);
		stt_xml_serialize_data_type(pXmlModuleAttrs, /*"��ѹ����Ӳ������"*/g_sLangTxt_Native_VoltCurrHWChar.GetString(),"ModulePower","","ModulePower", pPara->m_nModulePower);
		//		pXmlModuleAttrs->xml_serialize("����ͨ���ϲ�ģʽ","ChMergeMode","","ChMergeMode", pPara->m_nChMergeMode);
		stt_xml_serialize_data_type(pXmlModuleAttrs, /*"����ͨ���ϲ�ģʽ"*/g_sLangTxt_Native_CurrChMergeMode.GetString(),"ChMergeMode","","ChMergeMode", pPara->m_nChMergeMode);    
#endif

#ifdef _PSX_QT_LINUX_

		if(pPara->m_nModuleType == STT_MODULE_TYPE_SWITCH)
		{
#ifdef NOT_USE_XLANGUAGE
		pXmlModuleAttrs->xml_serialize("K1~K8��Ϊ����","SwitchIn_0","","long", pPara->m_nSwitchIn[0]);
		pXmlModuleAttrs->xml_serialize("K9~K16��Ϊ����","SwitchIn_1","","long", pPara->m_nSwitchIn[1]);
		pXmlModuleAttrs->xml_serialize("K17~K24��Ϊ����","SwitchIn_2","","long", pPara->m_nSwitchIn[2]);
		pXmlModuleAttrs->xml_serialize("K25~K32��Ϊ����","SwitchIn_3","","long", pPara->m_nSwitchIn[3]);
		pXmlModuleAttrs->xml_serialize("K33~K40��Ϊ����","SwitchIn_4","","long", pPara->m_nSwitchIn[4]);
		pXmlModuleAttrs->xml_serialize("K41~K48��Ϊ����","SwitchIn_5","","long", pPara->m_nSwitchIn[5]);
		pXmlModuleAttrs->xml_serialize("K49~K56��Ϊ����","SwitchIn_6","","long", pPara->m_nSwitchIn[6]);
		pXmlModuleAttrs->xml_serialize("K57~K64��Ϊ����","SwitchIn_7","","long", pPara->m_nSwitchIn[7]);
#else
			pXmlModuleAttrs->xml_serialize("K1~K8��Ϊ����","SwitchIn_0","","long", pPara->m_nSwitchIn[0]);
			pXmlModuleAttrs->xml_serialize("K9~K16��Ϊ����","SwitchIn_1","","long", pPara->m_nSwitchIn[1]);
			pXmlModuleAttrs->xml_serialize("K17~K24��Ϊ����","SwitchIn_2","","long", pPara->m_nSwitchIn[2]);
			pXmlModuleAttrs->xml_serialize("K25~K32��Ϊ����","SwitchIn_3","","long", pPara->m_nSwitchIn[3]);
			pXmlModuleAttrs->xml_serialize("K33~K40��Ϊ����","SwitchIn_4","","long", pPara->m_nSwitchIn[4]);
			pXmlModuleAttrs->xml_serialize("K41~K48��Ϊ����","SwitchIn_5","","long", pPara->m_nSwitchIn[5]);
			pXmlModuleAttrs->xml_serialize("K49~K56��Ϊ����","SwitchIn_6","","long", pPara->m_nSwitchIn[6]);
			pXmlModuleAttrs->xml_serialize("K57~K64��Ϊ����","SwitchIn_7","","long", pPara->m_nSwitchIn[7]);

// 		pXmlModuleAttrs->xml_serialize(/*"��һ�鿪������Ϊ����"*/g_sLangTxt_Native_1stSetDigInCfg.GetString(),"SwitchIn_0","","long", pPara->m_nSwitchIn[0]);
// 		pXmlModuleAttrs->xml_serialize(/*"�ڶ��鿪������Ϊ����"*/g_sLangTxt_Native_2stSetDigInCfg.GetString(),"SwitchIn_1","","long", pPara->m_nSwitchIn[1]);
// 		pXmlModuleAttrs->xml_serialize(/*"�����鿪������Ϊ����"*/g_sLangTxt_Native_3stSetDigInCfg.GetString(),"SwitchIn_2","","long", pPara->m_nSwitchIn[2]);
// 		pXmlModuleAttrs->xml_serialize(/*"�����鿪������Ϊ����"*/g_sLangTxt_Native_4stSetDigInCfg.GetString(),"SwitchIn_3","","long", pPara->m_nSwitchIn[3]);
#endif
		}

#endif

		if(pPara->m_nModuleType == STT_MODULE_TYPE_WEEK_EX || pPara->m_nModuleType == STT_MODULE_TYPE_ADMU)
		{
			pXmlModuleAttrs->xml_serialize("ͨ���������Ϳɱ�(1:�ɱ�,0:���ɱ�)", "ChTypeChg", "", "long", pPara->m_nChTypeChg);
		}

		if(!g_bWriteHdInfor)
		{
			if(stt_xml_serialize_is_write(pXmlModuleAttrs)||stt_xml_serialize_is_register(pXmlModuleAttrs))
                        {
#ifdef NOT_USE_XLANGUAGE
				pXmlModuleAttrs->xml_serialize("����ֱ����ѹͨ�����ֵ","UdcMax","","float", pPara->m_fUdcMax);
				pXmlModuleAttrs->xml_serialize("����ֱ����ѹͨ����Сֵ","UdcMin","","float", pPara->m_fUdcMin);
				pXmlModuleAttrs->xml_serialize("ģ��FPGA�汾","FpgaVer","","FPGAVersion", pPara->m_strFPGAVer);
#else
				pXmlModuleAttrs->xml_serialize(/*"ģ��FPGA�汾"*/g_sLangTxt_Native_ModFPGAVer.GetString(),"FpgaVer","","FPGAVersion", pPara->m_strFPGAVer);
#endif
			}
		}

		if(stt_xml_serialize_is_read(pXmlModuleAttrs))
		{
			pPara->m_dwVersion = STT_ADJUST_MODULE_PARA_VERSION;
		}
		else
		{
#ifdef NOT_USE_XLANGUAGE
		pXmlModuleAttrs->xml_serialize("ģ�����԰汾","Version","","long", pPara->m_dwVersion);
#else
		pXmlModuleAttrs->xml_serialize(/*"ģ�����԰汾"*/g_sLangTxt_Native_ModAttrVer.GetString(),"Version","","long", pPara->m_dwVersion);
#endif
		}

		if (g_theAdjParaXmlSerialConfig.m_nModuleChDef != 0)
		{
			stt_xml_serialize(&pPara->m_oChDefMap, pXmlModuleAttrs, pPara->m_nChannelNum);
		}

//	if (g_theAdjParaXmlSerialConfig.m_nModuleHdGear == 0)
//	{
//		return;
//	}

//	if (pPara->has_idc())
//	{
//#ifdef NOT_USE_XLANGUAGE
//		stt_xml_serialize(&pPara->m_oHdGears_Idc, "����ֱ������ͨ��Ӳ����λ", "HdIdcGears", ///pXmlModuleAttrs);
//#else
//		stt_xml_serialize(&pPara->m_oHdGears_Idc, /*"����ֱ������ͨ��Ӳ����λ"*/g_sLangTxt_Native_IndepDCCurrChHWRange.GetString(), "HdIdcGears", pXmlModuleAttrs);
//#endif
//	}

//	if (pPara->has_udc())
//	{
//#ifdef NOT_USE_XLANGUAGE
//		stt_xml_serialize(&pPara->m_oHdGears_Udc, "����ֱ����ѹͨ��Ӳ����λ", "HdUdcGears", pXmlModuleAttrs);
//#else
//		stt_xml_serialize(&pPara->m_oHdGears_Udc, /*"����ֱ����ѹͨ��Ӳ����λ"*/g_sLangTxt_Native_IndepDCVoltChHWRange.GetString(), "HdUdcGears", pXmlModuleAttrs);
//#endif
//	}
//#ifdef NOT_USE_XLANGUAGE
//	stt_xml_serialize(&pPara->m_oHdGears, "ģ��ͨ����λ", "HdGears", pXmlModuleAttrs);
//#else
//	stt_xml_serialize(&pPara->m_oHdGears, /*"ģ��ͨ����λ"*/g_sLangTxt_Native_ModChRange.GetString(), "HdGears", pXmlModuleAttrs);
//#endif
	}
}

void stt_xml_serialize(PSTT_MODULE pPara, long nIndex, CSttXmlSerializeBase *pXmlSerialize)
{
	if (! g_theAdjParaXmlSerialConfig.has_module())
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pXmlModule = pXmlSerialize->xml_serialize(stt_ParaGroupKey(), nIndex, "ģ��", "Module", "Module");
#else
	CSttXmlSerializeBase *pXmlModule = pXmlSerialize->xml_serialize(stt_ParaGroupKey(), nIndex, /*"ģ��"*/g_sLangTxt_Module.GetString(), "Module", "Module");
#endif
	if (pXmlModule == NULL)
	{
		return;
	}

	if(!g_bWriteHdInfor)//��д��ϵ���ļ�,ͨ��adjust�����ȡӲ��ʵ����Ϣ
	{
		if(stt_xml_serialize_is_write(pXmlSerialize)||stt_xml_serialize_is_register(pXmlSerialize))
		{
			PSTT_CHANNEL_WAVE_ADJUST pChUdcAdj =
				&pPara->m_oModuleAdjust.m_oTempAdjust[0].m_oChUdcAdj;
			int nGearCnt = pChUdcAdj->m_nGearCount;
			if(nGearCnt > 0)
			{
				float fGearValue = pChUdcAdj->m_oChGearAdj[nGearCnt - 1].m_fGearValue;
				if(fGearValue > 0.000001)
				{
					pPara->m_oModuleAttr.m_fUdcMax = fGearValue;
					pPara->m_oModuleAttr.m_fUdcMin = 0;

					for(int j = 0; j < nGearCnt; j++)
					{
						if(pChUdcAdj->m_oChGearAdj[j].m_oAdjItem.m_fCoef < 0.01)
						{
							pPara->m_oModuleAttr.m_fUdcMin = pChUdcAdj->m_oChGearAdj[j].m_fGearValue;
							break;
						}
					}
				}
			}
		}
	}

	stt_xml_serialize(&pPara->m_oModuleAttr, pXmlModule);
	stt_xml_serialize(&pPara->m_oModuleAdjust, pXmlModule,pPara->m_oModuleAttr.m_nChannelNum,pPara->m_oModuleAttr.m_nHarmCount);

	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		pPara->init_ch_drv_pos();
		pPara->init_after_read();
	}

}

void stt_xml_serialize(PSTT_BOUT_ATTRS pPara, long nBoutCount, CSttXmlSerializeBase *pXmlSerialize)
{
	if (g_theAdjParaXmlSerialConfig.m_nBOutAttr == 0)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pBoutDefXmlAttrs = pXmlSerialize->xml_serialize("��������ֵͨ����", "BoutTrunOnValueDef", "BoutTrunOnValueDef", stt_ParaGroupKey());
#else
	CSttXmlSerializeBase *pBoutDefXmlAttrs = pXmlSerialize->xml_serialize(/*"��������ֵͨ����"*/g_sLangTxt_Native_TripRelayPickupDef.GetString(), "BoutTrunOnValueDef", "BoutTrunOnValueDef", stt_ParaGroupKey());
#endif
	if (pBoutDefXmlAttrs == NULL)
	{
		return;
	}

	CString strName, strID;
	for(int i = 0; i < nBoutCount && i < 16; i++)
	{
		strName.Format("����%d��ֵͨ", (i + 1));
		strID.Format("Bout%d", (i + 1));
		pBoutDefXmlAttrs->xml_serialize(strName.GetString(), strID.GetString(), "", "bool", pPara->m_nBout[i]);
	}

//    pBoutDefXmlAttrs->xml_serialize("����1��ֵͨ", "Bout1", "", "bool", pPara->m_nBout[0]);
//    pBoutDefXmlAttrs->xml_serialize("����2��ֵͨ", "Bout2", "", "bool", pPara->m_nBout[1]);
//    pBoutDefXmlAttrs->xml_serialize("����3��ֵͨ", "Bout3", "", "bool", pPara->m_nBout[2]);
//    pBoutDefXmlAttrs->xml_serialize("����4��ֵͨ", "Bout4", "", "bool", pPara->m_nBout[3]);
//    pBoutDefXmlAttrs->xml_serialize("����5��ֵͨ", "Bout5", "", "bool", pPara->m_nBout[4]);
//    pBoutDefXmlAttrs->xml_serialize("����6��ֵͨ", "Bout6", "", "bool", pPara->m_nBout[5]);
//    pBoutDefXmlAttrs->xml_serialize("����7��ֵͨ", "Bout7", "", "bool", pPara->m_nBout[6]);
//    pBoutDefXmlAttrs->xml_serialize("����8��ֵͨ", "Bout8", "", "bool", pPara->m_nBout[7]);
}

void stt_xml_serialize(PSTT_BIN_ADJUST pPara, long nBinCount, CSttXmlSerializeBase *pXmlSerialize)
{
	CString strName, strID;
	if (g_theAdjParaXmlSerialConfig.m_nBinAttr == 0)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pBinAdjXmlAttrs = pXmlSerialize->xml_serialize("�������ɼ�У׼ϵ��", "BinAdjustParas", "BinAdjustParas", stt_ParaGroupKey());
#else
	CSttXmlSerializeBase *pBinAdjXmlAttrs = pXmlSerialize->xml_serialize("", "BinAdjustParas", "BinAdjustParas", stt_ParaGroupKey());
#endif
	if (pBinAdjXmlAttrs == NULL)
	{
		return;
	}

	char strTemp[11] = "ABCDEFGHIJ";
	for(int i = 0; i < nBinCount && i < 10; i++)
	{
		strName.Format("����%c", strTemp[i]);
		strID.Format("Bin%c", strTemp[i]);
		CSttXmlSerializeBase *pBinAdj = pBinAdjXmlAttrs->xml_serialize(strName.GetString(), strID.GetString(), "BinAdj", stt_ParaGroupKey());

		pBinAdj->xml_serialize("��λ��","GearCount","","int", pPara[i].m_nGearCount);
		long nIndex = 0;

		for (nIndex=0; nIndex < pPara[i].m_nGearCount && nIndex < ADJUST_MAX_GEAR_COUNT; nIndex++)
		{
			stt_xml_serialize(&pPara[i].m_oBinGearAdj[nIndex], nIndex, pBinAdj);
		}
	}
}

void stt_xml_serialize(PSTT_DEVICE_ATTRS pPara, CSttXmlSerializeBase *pXmlSerialize)
{
	if (g_theAdjParaXmlSerialConfig.m_nDeviceAttr == 0)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	CSttXmlSerializeBase *pXmlAttrs = pXmlSerialize->xml_serialize("װ������", "DeviceAttrs", "DeviceAttrs", stt_ParaGroupKey());
#else
	CSttXmlSerializeBase *pXmlAttrs = pXmlSerialize->xml_serialize(/*"װ������"*/g_sLangTxt_State_ApplianceProperties.GetString(), "DeviceAttrs", "DeviceAttrs", stt_ParaGroupKey());
#endif
	if (pXmlAttrs == NULL)
	{
		return;
	}
#ifdef NOT_USE_XLANGUAGE
	pXmlAttrs->xml_serialize("�ͺ�","Model","","string", pPara->m_strDeviceName);
	pXmlAttrs->xml_serialize("���к�","SN","","string", pPara->m_strSN);
	pXmlAttrs->xml_serialize("�Ƶ��","Fnom","","float", pPara->m_fBaseFre);
    pXmlAttrs->xml_serialize("���忪������(��)","BinCount","","long", pPara->m_nBinCount);
	pXmlAttrs->xml_serialize("���忪���ѹ�ɼ�(0-��֧��,1-֧��)","BinVoltMeas","","long", pPara->m_nBinVoltMeas);
    pXmlAttrs->xml_serialize("���忪������(��)","BoutCount","","long", pPara->m_nBoutCount);
	pXmlAttrs->xml_serialize("���忪���ط�(0-��֧��,1-֧��)","BoutReplay","","long", pPara->m_nBoutReplay);
    pXmlAttrs->xml_serialize("����ʱ��,ģ����������λ����(��)","PhaseForMUTest","","float", pPara->m_fPhaseForMUTest);
	pXmlAttrs->xml_serialize("���ÿ���Ȩ���ж�(0-������,1-����)","CheckAuthority","","long", pPara->m_nCheckAuthority);
	pXmlAttrs->xml_serialize("���������Ĭ��ģʽ(0-��������,1-��������)","WindSpeed","","long", pPara->m_nWindSpeed);
	pXmlAttrs->xml_serialize("��������","Factory","","Factory", pPara->m_strFactory);
	pXmlAttrs->xml_serialize("��������","DateFac","","DateProduce", pPara->m_strDateProduce);
#else
	pXmlAttrs->xml_serialize(/*"�ͺ�"*/g_sLangTxt_Report_AppModel.GetString(),"Model","","string", pPara->m_strDeviceName);
	pXmlAttrs->xml_serialize(/*"���к�"*/g_sLangTxt_Report_AppSN.GetString(),"SN","","string", pPara->m_strSN);
	pXmlAttrs->xml_serialize(/*"�Ƶ��"*/g_sLangTxt_Report_Fnom.GetString(),"Fnom","","float", pPara->m_fBaseFre);
	pXmlAttrs->xml_serialize(/*"���忪������(��)"*/g_sLangTxt_Native_MainBrdDInQty.GetString(),"BinCount","","long", pPara->m_nBinCount);
	pXmlAttrs->xml_serialize(/*"���忪������(��)"*/g_sLangTxt_Native_MainBrdDOutQty.GetString(),"BoutCount","","long", pPara->m_nBoutCount);
	pXmlAttrs->xml_serialize(/*"����ʱ��,ģ����������λ����(��)"*/g_sLangTxt_Native_WSecMomentAnaPhAbsComp.GetString(),"PhaseForMUTest","","float", pPara->m_fPhaseForMUTest);
	pXmlAttrs->xml_serialize(/*"���ÿ���Ȩ���ж�(0-�����ã�1-����)"*/g_sLangTxt_Native_CtrlAuthCheck.GetString(),"CheckAuthority","","long", pPara->m_nCheckAuthority);
	pXmlAttrs->xml_serialize(/*"��������"*/g_sLangTxt_Report_DeviceFactory.GetString(),"Factory","","Factory", pPara->m_strFactory);
	pXmlAttrs->xml_serialize(/*"��������"*/g_sLangTxt_Gradient_ManufactDate.GetString(),"DateFac","","DateProduce", pPara->m_strDateProduce);
#endif
	if(!g_bWriteHdInfor)//��д��ϵ���ļ�,ͨ��adjust�����ȡӲ��ʵ����Ϣ
	{
		if(stt_xml_serialize_is_write(pXmlAttrs)||stt_xml_serialize_is_register(pXmlAttrs))
		{
#ifdef NOT_USE_XLANGUAGE
			pXmlAttrs->xml_serialize("TestMngr�汾","MngrVer","","MngrVersion", pPara->m_strMngrVer);
			pXmlAttrs->xml_serialize("TestServer����","AppName","","AppName", pPara->m_strAppName);
			pXmlAttrs->xml_serialize("TestServer�汾","AppVer","","AppVersion", pPara->m_strAppVer);
			pXmlAttrs->xml_serialize("����汾","FpgaVer","","FPGAVersion", pPara->m_strFPGAVer);
			pXmlAttrs->xml_serialize("�����汾","DriverVer","","DriverVersion", pPara->m_strDriverVer);
			pXmlAttrs->xml_serialize("��������","DriverName","","DriverName", pPara->m_strDriverName);
            pXmlAttrs->xml_serialize("����ST��ģʽ������","STModeSet","","STModeSet", pPara->m_nSTModeSet);
			pXmlAttrs->xml_serialize("״̬��������(��)","StateCount","","long", pPara->m_nStateCount);

			long nUartCnt = 0;
#ifndef _STT_NOT_IN_TEST_SERVER_
#ifdef _PSX_QT_LINUX_			
			if(g_pFpgaUart != NULL)
			{
				nUartCnt = g_pFpgaUart->m_oUartSettings.nUartCnt;
			}
#endif
#endif
			pXmlAttrs->xml_serialize("��������(��)","UartCount","","long", nUartCnt);

#else
			pXmlAttrs->xml_serialize(/*"TestServer����"*/g_sLangTxt_Native_TestSrvName.GetString(),"AppName","","AppName", pPara->m_strAppName);
			pXmlAttrs->xml_serialize(/*"TestServer�汾"*/g_sLangTxt_Native_TestSrvVersion.GetString(),"AppVer","","AppVersion", pPara->m_strAppVer);
			pXmlAttrs->xml_serialize(/*"����汾"*/g_sLangTxt_Native_MainBrdVersion.GetString(),"FpgaVer","","FPGAVersion", pPara->m_strFPGAVer);
			pXmlAttrs->xml_serialize(/*"�����汾"*/g_sLangTxt_Native_DrvVersion.GetString(),"DriverVer","","DriverVersion", pPara->m_strDriverVer);
			pXmlAttrs->xml_serialize(/*"��������"*/g_sLangTxt_Native_DrvName.GetString(),"DriverName","","DriverName", pPara->m_strDriverName);
			pXmlAttrs->xml_serialize(/*"����ST��ģʽ������"*/g_sLangTxt_Native_MainBrdSTPortModeCfg.GetString(),"STModeSet","","STModeSet", pPara->m_nSTModeSet);
#endif
		}
	}

	//	pXmlAttrs->xml_serialize("�ж���Idc","HasIdc","","bool", pPara->m_bHasIdc);
	//	pXmlAttrs->xml_serialize("Idc���ֵ","IdcMax","","float", pPara->m_fIdcMax);
	//	pXmlAttrs->xml_serialize("�ж���Udc","HasUdc","","bool", pPara->m_bHasUdc);
	//	pXmlAttrs->xml_serialize("Udc���ֵ","UdcMax","","float", pPara->m_fUdcMax);
}

void stt_xml_serialize(PSTT_DEVICESYSTEMPARAMETER pPara, CSttXmlSerializeBase *pXmlSerialize)
{
	pXmlSerialize->xml_serialize("ModuleCount","ModuleCount","","long", pPara->m_nModuleCount);

	if (stt_xml_serialize_is_write(pXmlSerialize) || stt_xml_serialize_is_register(pXmlSerialize))
	{
#ifdef NOT_USE_XLANGUAGE
		pXmlSerialize->xml_serialize("ϵͳ�汾��","SysVersion","","long", g_dwSttAdjSysParaCurrVersion);
#else
		pXmlSerialize->xml_serialize(/*"ϵͳ�汾��"*/g_sLangTxt_Native_SysVerNumber.GetString(),"SysVersion","","long", g_dwSttAdjSysParaCurrVersion);
#endif
	}

	stt_xml_serialize(&pPara->m_oDeviceAttrs, pXmlSerialize);
	stt_xml_serialize(&pPara->m_oBoutTurnOnValue, pPara->m_oDeviceAttrs.m_nBoutCount, pXmlSerialize);
	if(pPara->m_oDeviceAttrs.m_nBinVoltMeas)
	{
		stt_xml_serialize(pPara->m_oBinAdj, pPara->m_oDeviceAttrs.m_nBinCount, pXmlSerialize);
	}

	long nIndex = 0;

	for(nIndex = 0; nIndex < pPara->m_nModuleCount; nIndex++)
	{
		if(!g_bWriteHdInfor)
		{
			if(stt_xml_serialize_is_write(pXmlSerialize) || stt_xml_serialize_is_register(pXmlSerialize))
			{
				if(pPara->m_oModules[nIndex].m_oModuleAttr.m_nUsed == 0)
	{
					continue;//2023-11-15 zhoulei����PNS330���ⲿģ��
				}
			}
		}

		stt_xml_serialize(&pPara->m_oModules[nIndex], nIndex, pXmlSerialize);
	}
}

void stt_create_adjust()
{
	stt_create_adjust(1, 2, 32, 1, 1);
}

//����У׼�����ļ�
bool stt_create_adjust(PSTT_CHANNEL_WAVE_ADJUST pChWaveAdj, long nGearCount)
{
	pChWaveAdj->m_nGearCount = nGearCount;

	return true;
}

bool stt_create_adjust(PSTT_CHANNEL_ADJUSTS pChAdjs, long nHarmCount, long nGearCount)
{
	pChAdjs->nHarmCount = nHarmCount;

	if(pChAdjs->m_pChWaveAdj == NULL)
	{
		pChAdjs->m_pChWaveAdj = (PSTT_CHANNEL_WAVE_ADJUST)malloc(nHarmCount*sizeof(STT_CHANNEL_WAVE_ADJUST));

		for (long nIndex=0; nIndex < nHarmCount; nIndex++)
		{
			pChAdjs->m_pChWaveAdj[nIndex].init();
			stt_create_adjust(&pChAdjs->m_pChWaveAdj[nIndex], nGearCount);
		}
	}

	return true;
}

bool stt_create_adjust(PSTT_TRANGE_ADJUST pAdjTempeature, long nHarmCount, long nGearCount, long nChannelNum)
{
	stt_create_adjust(&pAdjTempeature->m_oChIdcAdj, nGearCount);
	stt_create_adjust(&pAdjTempeature->m_oChUdcAdj, nGearCount);

	if(pAdjTempeature->m_pChsAdjust==NULL)
	{
		pAdjTempeature->m_pChsAdjust = (PSTT_CHANNEL_ADJUSTS)malloc(nChannelNum*sizeof(STT_CHANNEL_ADJUSTS));
	}
	pAdjTempeature->nChannelNum = nChannelNum;

	for (long nIndex=0; nIndex < nChannelNum; nIndex++)
	{
		pAdjTempeature->m_pChsAdjust[nIndex].init();
		stt_create_adjust(&pAdjTempeature->m_pChsAdjust[nIndex], nHarmCount, nGearCount);
	}

	return true;
}

bool stt_create_adjust(PSTT_MODULE_ADJUST pAdjModule, long nTemperatureCount, long nHarmCount, long nGearCount, long nHdGearCount, long nChannelNum)
{
	pAdjModule->m_nTemperatureCount = nTemperatureCount;

	for (long nIndex=0; nIndex<ADJUST_MAX_TEMPRERATURE_COUNT; nIndex++)
	{
		stt_create_adjust(&pAdjModule->m_oTempAdjust[nIndex], nHarmCount, nGearCount, nChannelNum);
	}

	return true;
}

bool stt_create_adjust(PST_MODULE_ATTR pModuleAttr, long nHdGearCount)
{
//    pModuleAttr->m_oHdGears.m_nHdGearCount = nHdGearCount;
//    pModuleAttr->m_oHdGears_Idc.m_nHdGearCount = nHdGearCount;
//    pModuleAttr->m_oHdGears_Udc.m_nHdGearCount = nHdGearCount;
	pModuleAttr->m_nChannelNum = ADJUST_MAX_CHANNEL_COUNT;

	//	pModuleAttr->m_oChDefMap.m_oChMaps.m_nChMapsCount = 6;

	return true;
}

bool stt_init_adjust(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, long nTemperatureCount, long nModuleCount, long nHarmCount, long nGearCount, long nHdGearCount)
{
	pDvSysParas->m_nModuleCount = nModuleCount;

	long nIndex = 0;

	for (nIndex=0; nIndex<nModuleCount; nIndex++)
	{
		pDvSysParas->m_oModules[nIndex].m_oModuleAttr.m_nHarmCount = nHarmCount;

		stt_create_adjust(&pDvSysParas->m_oModules[nIndex].m_oModuleAttr, nHdGearCount);
		stt_create_adjust(&pDvSysParas->m_oModules[nIndex].m_oModuleAdjust, nTemperatureCount, nHarmCount, nGearCount, nHdGearCount,
						  pDvSysParas->m_oModules[nIndex].m_oModuleAttr.m_nChannelNum);

	}

	pDvSysParas->init_after_read();

	return true;
}

PSTT_DEVICESYSTEMPARAMETER stt_create_adjust(long nTemperatureCount, long nModuleCount, long nHarmCount, long nGearCount, long nHdGearCount)
{
	if (g_theDeviceSystemParameter == NULL)
	{
		g_theDeviceSystemParameter = (PSTT_DEVICESYSTEMPARAMETER)malloc(sizeof(STT_DEVICESYSTEMPARAMETER));
		g_theDeviceSystemParameter->init();
		stt_init_adjust(g_theDeviceSystemParameter, nTemperatureCount, nModuleCount, nHarmCount, nGearCount, nHdGearCount);
		g_theAdjParaXmlSerialConfig.init();
	}

	return g_theDeviceSystemParameter;
}

void stt_free_adjust()
{
	if (g_theDeviceSystemParameter != NULL)
	{
		long nTemperatureCount;
		for(long nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount;nIndex++)
		{
			STT_MODULE oModule = g_theDeviceSystemParameter->m_oModules[nIndex];

			nTemperatureCount = oModule.m_oModuleAdjust.m_nTemperatureCount;
			for(long nTemperature=0;nTemperature < nTemperatureCount;nTemperature++)
			{
				PSTT_CHANNEL_ADJUSTS pChsAdjust = oModule.m_oModuleAdjust.m_oTempAdjust[nTemperature].m_pChsAdjust;
				if(pChsAdjust!=NULL)
				{
					for(long nChannel=0;nChannel < oModule.m_oModuleAttr.m_nChannelNum;nChannel++)
					{
						if(pChsAdjust[nChannel].m_pChWaveAdj!=NULL)
							free(pChsAdjust[nChannel].m_pChWaveAdj);
					}
					free(pChsAdjust);
				}
			}
		}

		free(g_theDeviceSystemParameter);
	}
}

//////////////////////////////////////////////////////////////////////////
//
PSTT_MODULE stt_adj_find_module_byModulePos(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, long nModulePos, long nModuleType)
{
	for(long nIndex = 0; nIndex < pDvSysParas->m_nModuleCount; nIndex++)
	{
		if(nModuleType == pDvSysParas->m_oModules[nIndex].m_oModuleAttr.m_nModuleType)
		{
//20231023 STT_MODULE_TYPE_WEEK_MAIN �ϲ��� STT_MODULE_TYPE_WEEK_EX
//            if(nModuleType == STT_MODULE_TYPE_WEEK_MAIN)
//            {
//                return &pDvSysParas->m_oModules[nIndex];
//            }
//            else
			if(nModulePos == pDvSysParas->m_oModules[nIndex].m_oModuleAttr.m_nModuleIndex)
			{
				return &pDvSysParas->m_oModules[nIndex];
			}
		}
	}

	return NULL;
}

PSTT_CHANNEL_WAVE_ADJUST stt_adj_find_ch_wave(PSTT_TRANGE_ADJUST  pTemperatureAdj, long nChannel, long nFreqSel)
{
	PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = NULL;

	if (ADJUST_CHANNEL_INDEX_IDC == nChannel)
	{
		pChWaveAdj = &pTemperatureAdj->m_oChIdcAdj;
	}
	else if (ADJUST_CHANNEL_INDEX_UDC == nChannel)
	{
		pChWaveAdj = &pTemperatureAdj->m_oChUdcAdj;
	}
    else if (nChannel < 0 || nChannel >= STT_MODULE_CHANNEL_MAX)//20220414 zhoulei 48·С�ź�
	{//ֱ��ͨ��
		//pChWaveAdj = &pTemperatureAdj->m_oChUdcAdj;
		return NULL;
	}
	else
	{//������г������
		if (nFreqSel < 0 || nFreqSel >= pTemperatureAdj->m_pChsAdjust[nChannel].nHarmCount)
		{
			return NULL;
		}
		else
		{//����ͨ���Ͳ��δ������õ�����У׼ϵ��
			pChWaveAdj = &pTemperatureAdj->m_pChsAdjust[nChannel].m_pChWaveAdj[nFreqSel];
		}
	}

	return pChWaveAdj;
}

PSTT_TRANGE_ADJUST stt_adj_find_t_range(PSTT_MODULE pModule, float fTempreture)
{
	PSTT_TRANGE_ADJUST  pTemperatureAdj = NULL;
	PSTT_MODULE_ADJUST pModuleAdjust = &pModule->m_oModuleAdjust;

	//ֻ��һ������
	if (pModuleAdjust->m_nTemperatureCount <= 1)
	{
		return &pModuleAdjust->m_oTempAdjust[0];
	}

	//С�ڵ�һ������
	if (fTempreture <= pModuleAdjust->m_oTempAdjust[0].m_fTemperature)
	{
		return &pModuleAdjust->m_oTempAdjust[0];
	}

	//�������һ������
	if (fTempreture >= pModuleAdjust->m_oTempAdjust[pModuleAdjust->m_nTemperatureCount-1].m_fTemperature)
	{
		return &pModuleAdjust->m_oTempAdjust[pModuleAdjust->m_nTemperatureCount-1];
	}

	for (long nIndex=1; nIndex<pModuleAdjust->m_nTemperatureCount-1; nIndex++)
	{
		if (fTempreture <= pModuleAdjust->m_oTempAdjust[nIndex].m_fTemperature)
		{
			return &pModuleAdjust->m_oTempAdjust[nIndex];
		}
	}

	return &pModuleAdjust->m_oTempAdjust[0];
}

PSTT_CHANNEL_ADJUSTS stt_adj_find_channel(PSTT_MODULE pModule, long nChannel, float fTemperature)
{
	PSTT_TRANGE_ADJUST  pTemperatureAdj = NULL;
	pTemperatureAdj = stt_adj_find_t_range(pModule, fTemperature);

	if (pTemperatureAdj == NULL)
	{
		return NULL;
	}

	if (nChannel < 0 || nChannel >= pModule->m_oModuleAttr.m_nChannelNum)
	{
		return &pTemperatureAdj->m_pChsAdjust[0];
	}

	return &pTemperatureAdj->m_pChsAdjust[nChannel];
}

PSTT_CHANNEL_WAVE_ADJUST stt_adj_find_ch_wave(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PSTT_MODULE pModule, float fTemperature, long nChannel, long nFreqSel)
{
	//	if (nModule < 0 || nModule >= ADJUST_MAX_MODULE_COUNT)
	//	{
	//		return NULL;
	//	}

	PSTT_TRANGE_ADJUST  pTemperatureAdj = NULL;
	PSTT_CHANNEL_ADJUSTS  pChannelAdjs = NULL;
	PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = NULL;

	pTemperatureAdj = stt_adj_find_t_range(pModule, fTemperature);
	pChWaveAdj = stt_adj_find_ch_wave(pTemperatureAdj, nChannel, nFreqSel);

	return pChWaveAdj;
}

PSTT_ADJUST_ITEM stt_adj_find_adjust_item(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PSTT_MODULE pModule, float fTemperature, long nChannel, long nFreqSel, float fAmp)
{
	PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = stt_adj_find_ch_wave(pDvSysParas, pModule, fTemperature, nChannel, nFreqSel);

	if (pChWaveAdj == NULL)
	{
		return NULL;
	}

	PSTT_CHANNEL_GEAR_ADJUST pChGearAdj = pChWaveAdj->m_oChGearAdj;

	//	if (fAmp <= pChGearAdj->m_fGearValue)
	//	{
	//		return &pChGearAdj->m_oAdjItem;
	//	}

	if (fAmp > (pChGearAdj[pChWaveAdj->m_nGearCount-1].m_fGearValue + 0.001))
	{
		return &pChGearAdj[pChWaveAdj->m_nGearCount-1].m_oAdjItem;
	}

	//��λ
	for (long nIndex=0; nIndex<pChWaveAdj->m_nGearCount; nIndex++)
	{
		if (fAmp > (pChGearAdj[nIndex].m_fGearValue + 0.001))
		{

		}
		else
		{
			return &pChGearAdj[nIndex].m_oAdjItem;
		}
	}

	return NULL;
}

PSTT_ADJUST_ITEM stt_adj_get_ac(float fAmp,PSTT_MODULE pModule,int nChannel,float fTemperature,int nHarm)
{
	return stt_adj_find_adjust_item(g_theDeviceSystemParameter, pModule, fTemperature, nChannel, nHarm, fAmp);
}

//float stt_adj_get_ac_max(float fAmp, PSTT_MODULE pModule)
//{
//    STT_HD_GEARS oHdGears = pModule->m_oModuleAttr.m_oHdGears;
//    float fMax = 0;

//    for(int nIndex = 0; nIndex < oHdGears.m_nHdGearCount; nIndex++)
//    {
//        if(fAmp > (oHdGears.m_oHdGear[nIndex].m_fGearValue + 0.001))
//        {
//        }
//        else
//        {
//            fMax = oHdGears.m_oHdGear[nIndex].m_fGearValue;
//            break;
//        }
//    }

//    return fMax;
//}

//int stt_adj_get_ac_HGearID(float fAmp, PSTT_MODULE pModule)
//{
//    STT_HD_GEARS oHdGears = pModule->m_oModuleAttr.m_oHdGears;
//    int nHGearID = -1;

//    for(int nIndex = 0; nIndex < oHdGears.m_nHdGearCount; nIndex++)
//    {
//        if(fAmp > (oHdGears.m_oHdGear[nIndex].m_fGearValue + 0.001))
//        {
//        }
//        else
//        {
//            nHGearID = nIndex;
//            break;
//        }
//    }

//    return nHGearID;
//}

float stt_adj_get_ac_max_GearVal(float nChannel,PSTT_MODULE pModule,int nHarm)
{
	PSTT_CHANNEL_WAVE_ADJUST  pChWaveAdj = stt_adj_find_ch_wave(g_theDeviceSystemParameter, pModule, 0, nChannel, nHarm);

	if (pChWaveAdj == NULL)
	{
		return 0;
	}

	PSTT_CHANNEL_GEAR_ADJUST pChGearAdj = pChWaveAdj->m_oChGearAdj;

	return pChGearAdj[pChWaveAdj->m_nGearCount-1].m_fGearValue;
}

PSTT_ADJUST_ITEM stt_adj_find_meas_u_item(float fGearVal,int nModulePos,int nChannel,float fTemperature,int nHarm)
{
	if (nChannel < 0)
	{
		return NULL;
	}

	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_U_MEAS;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_U_MEAS[nIndex];
		if(pModule->m_oModuleAttr.m_nModuleIndex==nModulePos)
		{
			if(nHarm < 0||nHarm > pModule->m_oModuleAttr.m_nHarmCount)
				return NULL;

			if (nChannel >= pModule->m_oModuleAttr.m_nChannelNum)
			{
				return NULL;
			}

			PSTT_CHANNEL_ADJUSTS pChannelAdj = NULL;
			PSTT_TRANGE_ADJUST  pTemperatureAdj = NULL;
			pTemperatureAdj = stt_adj_find_t_range(pModule, fTemperature);

			if (pTemperatureAdj == NULL)
			{
				return NULL;
			}

			pChannelAdj = &pTemperatureAdj->m_pChsAdjust[nChannel];
			if(pChannelAdj->m_pChWaveAdj != NULL)
			{
				int nGearCount = pChannelAdj->m_pChWaveAdj[nHarm].m_nGearCount;

				for(int nGearIndex=0;nGearIndex<nGearCount;nGearIndex++)
				{
					if(fGearVal > (pChannelAdj->m_pChWaveAdj[nHarm].m_oChGearAdj[nGearIndex].m_fGearValue + 0.00001))
					{

					}
					else
					{
						return &(pChannelAdj->m_pChWaveAdj[nHarm].m_oChGearAdj[nGearIndex].m_oAdjItem);
					}
				}
			}

			break;
		}
	}

	return NULL;
}

PSTT_ADJUST_ITEM stt_adj_find_meas_i_item(float fGearVal,int nModulePos,int nChannel,float fTemperature,int nHarm)
{
	if (nChannel < 0)
	{
		return NULL;
	}

	for(int nIndex=0;nIndex<g_theDeviceSystemParameter->m_nModuleCount_I_MEAS;nIndex++)
	{
		PSTT_MODULE pModule=g_theDeviceSystemParameter->m_oModules_I_MEAS[nIndex];
		if(pModule->m_oModuleAttr.m_nModuleIndex==nModulePos)
		{
			if(nHarm < 0||nHarm > pModule->m_oModuleAttr.m_nHarmCount)
				return NULL;

			if (nChannel >= pModule->m_oModuleAttr.m_nChannelNum)
			{
				return NULL;
			}

			PSTT_CHANNEL_ADJUSTS pChannelAdj = NULL;
			PSTT_TRANGE_ADJUST  pTemperatureAdj = NULL;
			pTemperatureAdj = stt_adj_find_t_range(pModule, fTemperature);

			if (pTemperatureAdj == NULL)
			{
				return NULL;
			}

			pChannelAdj = &pTemperatureAdj->m_pChsAdjust[nChannel];
			if(pChannelAdj->m_pChWaveAdj != NULL)
			{
				int nGearCount = pChannelAdj->m_pChWaveAdj[nHarm].m_nGearCount;

				for(int nGearIndex=0;nGearIndex<nGearCount;nGearIndex++)
				{
					if(fGearVal > (pChannelAdj->m_pChWaveAdj[nHarm].m_oChGearAdj[nGearIndex].m_fGearValue + 0.00001))
					{

					}
					else
					{
						return &(pChannelAdj->m_pChWaveAdj[nHarm].m_oChGearAdj[nGearIndex].m_oAdjItem);
					}
				}
			}

			break;
		}
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//
//���л��������ͣ��ַ��� ==>>  �ı�  2021-5-4  lijunqing
#include "tmt_adjust_sys_para_trans.h"

void stt_xml_serialize_data_type(CSttXmlSerializeBase *pXmlSerialize, const char *pszName, const char *pszID, const char *pszUnit, const char *pszDataType, long &nValue)
{
	char pszValue[32] = {0};

	if (stt_xml_serialize_is_read(pXmlSerialize))
	{
		pXmlSerialize->xml_serialize(pszName, pszID, pszUnit, pszDataType, pszValue);
		stt_tmt_adj_para_trans_to_long(pszValue, pszDataType, nValue);
	}
	else
	{
		stt_tmt_adj_para_trans_to_string(nValue, pszDataType, pszValue);
		pXmlSerialize->xml_serialize(pszName, pszID, pszUnit, pszDataType, pszValue);
	}
}
