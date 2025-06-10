#pragma once

#include "tmt_impedance_test.h"
#include "../tmt_test_paras_head.h"

#define TMT_RECLOSE_ACC_TESTNAME_LEN	64

typedef struct tmt_reclose_acc_paras :public tmt_ImpedanceParas
{
	float	m_fTSetting[2];		//装置故障动作时间定值
	float	m_fTAfterTrig[2];	//故障后延时
	float  m_fUnom;//额定电压
    bool m_bSelected;//mym add 2021-6-21;
	
	//2022.5.26 caoxc 增加项目名称
	char m_pszTestName[TMT_RECLOSE_ACC_TESTNAME_LEN];

    float m_fVzFreq;//抽取电压频率

    //Pnv
    int m_nState1BOut;//故障前开出(0011格式，表示四个开出，倒序
    int m_nState2BOut;//故障态开出
    int m_nState3BOut;//重合闸开出
    int m_nState4BOut;//后加速开出

public:
	virtual void init()
	{
		tmt_ImpedanceParas::init();
		m_fTSetting[0] = 5.0f;
		m_fTSetting[1] = 3.0f;
		m_fTAfterTrig[0] = 0.0f;
		m_fTAfterTrig[1] = 0.0f;
		m_fUnom = 57.74;
		m_bSelected = false;
        m_nState1BOut = 11;
        m_nState2BOut = 11;
        m_nState3BOut = 11;
        m_nState4BOut = 11;
        m_fVzFreq = 50;

		//2022.5.26 caoxc
		memset(m_pszTestName, 0, TMT_RECLOSE_ACC_TESTNAME_LEN);
	} 

}tmt_RecloseAccParas;

typedef struct tmt_reclose_acc_paras_ex :public tmt_RecloseAccParas
{
public:
	char m_pszImpedance[2][PARAS_RSLT_EXPR_LEN];		//短路阻抗幅值(第一次故障阻抗、第二次故障阻抗)	m_fZ m_fZdev
	char m_pszImpAngle[2][PARAS_RSLT_EXPR_LEN];		//阻抗角(第一次故障阻抗、第二次故障阻抗) m_fPhi
	char m_pszUxInput_Mag[PARAS_RSLT_EXPR_LEN];	//同期电压(检同期方式有效)
	char m_pszUxInput_Ang[PARAS_RSLT_EXPR_LEN];
	char m_pszTestItemName[PARAS_RSLT_EXPR_LEN];//存储名称 便于修改 马扬名 2021-9-15
	float m_fImpdanceSetting;//zhouhj 20211021 阻抗定值
	float m_fImpAngleSetting;//zhouhj 20211021 阻抗角定值
	float m_fSynAngleSetting;//zhouhj 20211021 检同期角度定值


	virtual void init()
	{
		tmt_RecloseAccParas::init();
		memset(m_pszImpedance[0],0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszImpedance[1],0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszImpAngle[0],0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszImpAngle[1],0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszUxInput_Mag,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszUxInput_Ang,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszTestItemName,0,PARAS_RSLT_EXPR_LEN);
		m_fImpdanceSetting = 5.0f;
		m_fImpAngleSetting = 78.0f;
		m_fSynAngleSetting = 10.0f;

	} 
}tmt_RecloseAccParasEx;

typedef struct tmt_reclose_acc_results :public tmt_ImpedanceResults
{

public:
	virtual void init()
	{
		tmt_ImpedanceResults::init();
		
	} 

}tmt_RecloseAccResults;

#define ITEM_CNT_RECLOSE  5
typedef struct tmt_reclose_acc_test : public TMT_PARAS_HEAD
{
public:
	tmt_RecloseAccParasEx      m_oRecloseAccParas ;
	tmt_RecloseAccResults   m_oRecloseAccResults;

	char m_szName[MAX_NAME_LEN];
	
	float m_fR;
	float m_fX;

	void init()
	{		
		init_head(); //2021-9-13  lijunqing

		strcpy(m_pszMacroID, STT_MACRO_ID_RecloseAcc);
		strcpy(m_szName, "Z = 1.900Ω, A-E, 瞬时");
		memset(m_szName,  0,  32);
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		m_nSelected = 1;
		m_fR = 0.0f;
		m_fX = 0.0f;
		m_oRecloseAccParas.init();
		m_oRecloseAccResults.init();	
	}

	tmt_reclose_acc_test()	{init();}
	virtual void clear_result(){	m_oRecloseAccResults.init();	}
	virtual ~tmt_reclose_acc_test(){}
}tmt_RecloseAccTest;

typedef struct tmt_tu_reclose_acc_test : public TMT_PARAS_HEAD//配网测试专用重合闸后加速
{
public:
	tmt_RecloseAccParasEx      m_oRecloseAccParas ;
	tmt_RecloseAccResults   m_oRecloseAccResults;

	char m_szName[MAX_NAME_LEN];

	float m_fR;
	float m_fX;

	void init()
	{		
		init_head(); 

		strcpy(m_pszMacroID, STT_MACRO_ID_TURecloseAcc);
		strcpy(m_szName, "Z = 1.900Ω, A-E, 瞬时");
		memset(m_szName,  0,  32);
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		m_nSelected = 1;
		m_fR = 0.0f;
		m_fX = 0.0f;
		m_oRecloseAccParas.init();
		m_oRecloseAccResults.init();	
	}

	tmt_tu_reclose_acc_test()	{init();}
	virtual void clear_result(){	m_oRecloseAccResults.init();	}
	virtual ~tmt_tu_reclose_acc_test(){}
}tmt_TURecloseAccTest;

typedef struct tmt_reclose_acc_pnv_test : public tmt_reclose_acc_test
{
public:

    void init()
    {
        strcpy(m_pszMacroID, STT_MACRO_ID_StateRecloseAcc);
    }

    tmt_reclose_acc_pnv_test()	{init();}
    virtual void clear_result(){	m_oRecloseAccResults.init();	}
    virtual ~tmt_reclose_acc_pnv_test(){}
}tmt_RecloseAccPnvTest;

void stt_init_paras(tmt_RecloseAccParas *pParas);
void stt_init_paras_ex(tmt_RecloseAccParasEx *pParas);
void stt_init_results(tmt_RecloseAccResults *pResults);

void stt_xml_serialize(tmt_RecloseAccParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_pnv(tmt_RecloseAccParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_RecloseAccParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_RecloseAccResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_RecloseAccTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_RecloseAccPnvTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
