//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataSmvCommon.cpp  CIecCfgDataSmvCommon
#include "stdafx.h"
#include "IecCfgDataSmvCommon.h"

CIecCfgDataSmvCommon::CIecCfgDataSmvCommon()
{
		//初始化属性
 	m_fUNom = 110;
// 	m_fINom = 1200;
	m_fFNom = 50;
// 	m_fICenter = 120;
	m_nSampleRate = 4000;
	m_nSampleRate_FT3 = 500;
	m_nBaudRate= 0;
	m_nAsduNum = 1;
	m_bNoQuality = FALSE;

	m_nDcVol= 100;
	m_nDcCur= 1000;
	m_nDcNeuatralVol = 100;
	m_dDcVolPrim= 1000;
	m_dDcCurPrim= 100;
	m_dDcNeutralPrim = 1000;

	m_nSCP = 1;
	m_nSCM = 1;
	m_nSV = 1;
	m_dInomProt = 1000;
	m_dInomMeas = 1000;
}

CIecCfgDataSmvCommon::~CIecCfgDataSmvCommon()
{
}
