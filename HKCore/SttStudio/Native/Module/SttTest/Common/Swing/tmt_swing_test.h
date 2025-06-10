#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"


typedef struct tmt_swing_paras 
{
	//故障参数
	float	m_fPowerAngleBegin;	//功角始值
	float	m_fPowerAngleEnd;	//功角终值
	float	m_fCycle;			//振荡周期
	int		m_nSwingCount;		//震荡次数
	float	m_fRate;			//em/en
	int		m_nTripPoint;		//跳闸接入点
	int		m_nTripSpeedUp;		//加速信号接点
	int		m_nTripSpeedDown;	//减速信号接点
//	float	m_fFreq;			//频率
	BOOL	m_bReciprocating;	//是否往复振荡
	int		m_nAccelerate;		//减速或加速 0-减速 1-加速
	BOOL	m_bDzdt;			//阻抗是否变化
	float	m_fDzdt;			//dz/dt

	BOOL	m_bTransFault;		//是否转换性故障
	int		m_nFaultType;		//故障类型
	float	m_fImpedance;		//短路阻抗
	float	m_fSCurrent;		//短路电流
	float	m_fFaultTime;		//故障发生时间
	int		m_nK0CalMode;		//零序补偿系数计算方式
	float	m_fK0Amp;			//|零序补偿比例系数Ko|或Re(Ko) m_fRMRL
	float	m_fK0Angle;			//零序相位补偿系数Phi(Ko)或Im(Ko) m_fXMXL

	//通用参数
	float	m_fPreFaultTime;	//振荡前时间
	int		m_nCTPoint;			//CT正极性 0 指向母线，1指向线路
	float	m_fImpSys;			//系统侧阻抗
	float	m_fImpSysPh;		//PHI(zs)
	float	m_fImpTf;			//变压器阻抗
	float	m_fImpTfPh;			//PHI
	float	m_fImpTs;			//发电机暂态阻抗
	float	m_fActTimeSet;		//动作时间定值

	//开关量
// 	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
// 	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	//0-非故障态开出 1-故障态开出
    tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];//0-非故障态开出 1-故障态开出

    //GoosePub
    tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];
public:
	virtual void init()
	{
		m_fPowerAngleBegin = 0;
		m_fPowerAngleEnd = 200;
		m_fCycle = 3;
		m_nSwingCount = 5;
		m_fRate = 1.25f;
		m_nTripPoint = 0;
		m_nTripSpeedUp = 2;
		m_nTripSpeedDown = 3;
		m_bReciprocating=0;
		m_nAccelerate=1;
		m_bDzdt=0;
		m_fDzdt = 4.4452f;
//		m_fFreq = 50;

		m_bTransFault=0;
		m_nFaultType = 0;
		m_fImpedance = 1.0f;
		m_fSCurrent = 5.0f;
		m_fFaultTime = 0.5f;
		m_nK0CalMode = 0;
		m_fK0Amp = 0;
		m_fK0Angle =0;

		m_fPreFaultTime = 0;
		m_nCTPoint = 1;
		m_fImpSys = 25;
		m_fImpSysPh = 90;
		m_fImpTf = 15;
		m_fImpTfPh = 78;
		m_fImpTs = 1;
		m_fActTimeSet = 1;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
//			m_binIn[i].init();
			m_binOut[i].init();
		}

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
//			m_binInEx[i].init();
			m_binOutEx[i].init();
		}

        for(int nIndex=0;nIndex<MAX_MODULES_GOOSEPUB_COUNT;nIndex++)
            m_oGoosePub[nIndex].init();
	} 

}tmt_SwingParas;

typedef struct tmt_swing_results
{
	float m_fTripTime;
	float m_fSpeedUp;
	float m_fSpeedDown;
	long m_nAct;

public:
	virtual void init()
	{
		m_fTripTime = 0.0f;
		m_fSpeedUp = 0.0f;
		m_fSpeedDown = 0.0f;
		m_nAct = 0;
	} 

}tmt_SwingResults;


typedef struct tmt_swing_test : public TMT_PARAS_HEAD
{
public:
	tmt_SwingParas      m_oSwingParas ;
	tmt_SwingResults   m_oSwingResults;


	void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuSwing);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oSwingParas.init();
		m_oSwingResults.init();
	}

	tmt_swing_test()	{init();}
	virtual void clear_result(){	m_oSwingResults.init();	}
	virtual ~tmt_swing_test(){}
}tmt_SwingTest;

void stt_init_paras(tmt_SwingParas *pParas);
void stt_init_results(tmt_SwingResults *pResults);

void stt_xml_serialize(tmt_SwingParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_SwingResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_SwingTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
