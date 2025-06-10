#pragma once

#include "stdafx.h"
#include"../../SttTestBase/SttXmlSerialize.h"
#include "tmt_common_def.h"
#include"../../SttCmd/SttTestCmd.h"
#include"../../../Module/API/GlobalConfigApi.h"

#define MAX_HARM_COUNT        32
#define MAX_BINARYIN_COUNT	20
#define MAX_BINARYOUT_COUNT	20
#define MAX_VOLTAGE_COUNT	32
#define MAX_CURRENT_COUNT	32


typedef struct tmt_paras
{
public:
	float	    m_fVolAux;		// 辅助直流电压（仅模拟）
	BOOL        m_bKeepLoad;
	BOOL        m_bLargeCurrent;
	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
	//开关量
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];

public:
	void init()
	{
		m_fVolAux=0;
		m_bKeepLoad=FALSE;
		m_bLargeCurrent=FALSE;

		float fAngle[3] = {0, -120.0, 120.0};

		for(int i=0; i<MAX_VOLTAGE_COUNT; i++)
		{
			m_uiVOL[i].Harm[1].fAmp = 100;
			m_uiCUR[i].Harm[1].fAmp = 0;
			m_uiVOL[i].Harm[1].fAngle = m_uiCUR[i].Harm[1].fAngle = fAngle[i%3];
			m_uiVOL[i].Harm[1].fFreq=m_uiCUR[i].Harm[1].fFreq=50;
		}
	}

	tmt_paras()	{}
	virtual ~tmt_paras() {}
}tmt_Paras;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_init_paras(tmt_Paras *pParas);
void stt_xml_serialize(tmt_Paras *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_write_SetParameter();
