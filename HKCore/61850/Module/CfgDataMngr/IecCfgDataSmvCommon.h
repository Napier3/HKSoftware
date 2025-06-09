//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataSmvCommon.h  CIecCfgDataSmvCommon

#pragma once

#include "IecCfgDataMngrGlobal.h"


class CIecCfgDataSmvCommon : public CExBaseObject
{
public:
	CIecCfgDataSmvCommon();
	virtual ~CIecCfgDataSmvCommon();


 	long  m_fUNom;
// 	long  m_fINom;
	long  m_fFNom;
//	long  m_fICenter;
	long  m_nSampleRate;
//zhouhj 2023.10.18 9-2与FT3对应的采样率需要分别配置,此处进行分开处理
	long  m_nSampleRate_FT3;
	long  m_nAsduNum;
	long  m_bNoQuality;
	long m_nBaudRate;//zhouhj 20211013
	long m_nDcVol;
	long m_nDcCur;
	long m_nDcNeuatralVol;//直流中性母线电压码值
	double m_dDcVolPrim;
	double m_dDcCurPrim;
	double m_dDcNeutralPrim;

	long m_nSCP;
	long m_nSCM;
	long m_nSV;
	float m_dInomProt;
	float m_dInomMeas;

//重载函数
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG_SMV_COMMON;   }

//私有成员变量
private:

};

