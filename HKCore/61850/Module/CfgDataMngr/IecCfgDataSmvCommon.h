//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
//zhouhj 2023.10.18 9-2��FT3��Ӧ�Ĳ�������Ҫ�ֱ�����,�˴����зֿ�����
	long  m_nSampleRate_FT3;
	long  m_nAsduNum;
	long  m_bNoQuality;
	long m_nBaudRate;//zhouhj 20211013
	long m_nDcVol;
	long m_nDcCur;
	long m_nDcNeuatralVol;//ֱ������ĸ�ߵ�ѹ��ֵ
	double m_dDcVolPrim;
	double m_dDcCurPrim;
	double m_dDcNeutralPrim;

	long m_nSCP;
	long m_nSCM;
	long m_nSV;
	float m_dInomProt;
	float m_dInomMeas;

//���غ���
public:
	virtual UINT GetClassID() {    return CFGCLASSID_CIECCFG_SMV_COMMON;   }

//˽�г�Ա����
private:

};

