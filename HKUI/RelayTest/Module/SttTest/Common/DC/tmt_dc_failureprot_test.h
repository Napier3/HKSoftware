#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"

#define TMT_DCFAILUREPROT_TESTNAME_LEN	64

typedef struct tmt_dc_failure_prot_paras 
{
public:
	//故障参数
	float	m_fActValue_Setting[2];			    //变化量动作定值
	float	m_fActTime_Setting[2];					//动作时间
	float	m_fPreFaultTime;					//故障前时间
	float	m_fMarginTime;					//故障时间裕度
	int	    m_nBinLogic;		    //开入逻辑选择
	long	m_nOutputSwitchMode; 				   //开出翻转启动方式
	float	m_fBoutHoldTime;					//开出保持时间
	float	m_fBoutTimeTrig;					//开出反转时刻
	float	m_fPreFaultVol;	               //故障前电压
	float	m_fPreFaultCur;	               //故障前电流						
	float   m_fIstart;         //电流变化始值
	float 	m_fIend;           //电流变化终值
	float 	m_fDidtStart;      //电流滑差起始值
	float 	m_fDidtEnd;        //电流滑差终止值
	float 	m_fDidtStep;       //电流滑差变化步长
	float 	m_fHoldTime;        //保持时间
	float 	m_fDidt;            //电流滑差
	float 	m_fFI;             //Ⅰ段电流
	float 	m_fMul;              //倍数
	int   	m_nIChanSelect;    //电流通道选择
	float 	m_fFIstart;         //Ⅰ段电流变化始值
	float 	m_fFIend;           //Ⅰ段电流变化终值
	float 	m_fFIstep;          //Ⅰ段电流变化步长
	float   m_fFActionTime;       //整定动作时间

	//开关量
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
//	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];
	long m_nStateBOut[MAX_BINARYIN_COUNT];//用二进制标识各个开出状态
	
public:
virtual void init()
	{
		m_fActValue_Setting[0]	= 0;		
		m_fActValue_Setting[1] = 0;		
		m_fActTime_Setting[0] = 0;			
		m_fActTime_Setting[1] = 0;		
		m_fPreFaultTime = 0;		
		m_fMarginTime = 0;			
		m_nBinLogic = 0;					
		m_fBoutHoldTime = 0;	
		m_nOutputSwitchMode = 0;
		m_fBoutHoldTime = 0;	
		m_fBoutTimeTrig = 0;	
		m_fPreFaultVol = 0;	
        m_fPreFaultCur = 0;
		m_fIstart = 0;        
		m_fIend = 0;         
		m_fDidtStart = 0;    
		m_fDidtEnd = 0;       
		m_fDidtStep = 0;      
		m_fHoldTime = 0;      
		m_fDidt = 0;          
		m_fFI = 0;    
		m_fMul = 0;      
		m_nIChanSelect = 0;
		m_fFIstart = 0;       
		m_fFIend = 0;         
		m_fFIstep = 0;        

		for (int nIndex = 0;nIndex<MAX_BINARYOUT_COUNT;nIndex++)
		{	
			m_binIn[nIndex].init();
		//	m_binOut[nIndex].init();
		}
		for(int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
           m_nStateBOut[i] = 0;
		}
	}

}tmt_DCFailureProtParas;

typedef struct tmt_dc_failure_prot_paras_ex :public tmt_DCFailureProtParas
{
public:
	char	m_pszFIstart[PARAS_RSLT_EXPR_LEN];		//Ⅰ段电流变化始值
	char	m_pszFIend[PARAS_RSLT_EXPR_LEN];		//Ⅰ段电流变化终值
	char	m_pszFIstep[PARAS_RSLT_EXPR_LEN];		    //Ⅰ段电流变化步长
	char	m_pszFActionTime[PARAS_RSLT_EXPR_LEN];		//整定动作时间
	char	m_pszFI[PARAS_RSLT_EXPR_LEN];	        //Ⅰ段电流
	char	m_pszMul[PARAS_RSLT_EXPR_LEN];		    //倍数
	char	m_pszHoldTime[PARAS_RSLT_EXPR_LEN];	    //保持时间
	char	m_pszIstart[PARAS_RSLT_EXPR_LEN];		//电流变化始值
	char	m_pszIend[PARAS_RSLT_EXPR_LEN];		    //电流变化终值
	char	m_pszDidtStart[PARAS_RSLT_EXPR_LEN];	//电流滑差起始值
	char	m_pszDidtEnd[PARAS_RSLT_EXPR_LEN];		//电流滑差终止值
	char	m_pszDidtStep[PARAS_RSLT_EXPR_LEN];		//电流滑差变化步长
	char	m_pszDidt[PARAS_RSLT_EXPR_LEN];	    //电流滑差

	virtual void init()
	{
		tmt_DCFailureProtParas::init();
		memset(m_pszFIstart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszFIend,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszFIstep,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszFActionTime,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszFI,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszMul,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszHoldTime,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIstart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIend,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDidtStart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDidtEnd,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDidtStep,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDidt,0,PARAS_RSLT_EXPR_LEN);
	} 

}tmt_DCFailureProtParasEx;
typedef struct tmt_dc_failure_prot_results
{
public:
	float	m_fResSACValue;			    //Ⅱ段电流变化率
	float	m_fResSATime;					//Ⅱ段动作时间
	float	m_fResFATime;					//Ⅰ段动作时间
	float	m_fResFACurValue;					//Ⅰ段电流动作值

public:
	virtual void init()
	{
       m_fResSACValue = 0; 
	   m_fResSATime = 0;
	   m_fResFATime = 0;
	   m_fResFACurValue = 0;
	} 

}tmt_DCFailureProtResults;




typedef struct tmt_dc_failure_didt_act_value_test : public TMT_PARAS_HEAD  //Ⅱ段变化量动作定值
{
public:
	tmt_DCFailureProtParasEx m_oFailureProtTestParas;
	tmt_DCFailureProtResults m_oFailureProtTestResults;
	
public:
	virtual void init()
	{
		init_head(); //20210918 zhouhj
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		m_oFailureProtTestParas.init();
		m_oFailureProtTestResults.init();
		strcpy(m_pszMacroID, STT_MACRO_ID_FailureProtDidtActValue);
	} 
	tmt_dc_failure_didt_act_value_test(){     init();}
	~tmt_dc_failure_didt_act_value_test(){}

}tmt_DCFailureDidtActValueTest;

typedef struct tmt_dc_failure_didt_act_time_test :public tmt_DCFailureDidtActValueTest  //Ⅱ段动作时间
{

public:
	virtual void init()
	{
      tmt_DCFailureDidtActValueTest::init();
	  strcpy(m_pszMacroID, STT_MACRO_ID_FailureProtDidtActTime);
	 
	} 
	tmt_dc_failure_didt_act_time_test(){     init();}
	~tmt_dc_failure_didt_act_time_test(){}

}tmt_DCFailureDidtActTimeTest;


typedef struct tmt_dc_failure_act_time_test :public tmt_DCFailureDidtActValueTest    //Ⅰ段动作时间
{

public:	
	virtual void init()
	{
      tmt_DCFailureDidtActValueTest::init();
	  strcpy(m_pszMacroID, STT_MACRO_ID_FailureProtActTime);	 
	} 

	tmt_dc_failure_act_time_test(){     init();}
	~tmt_dc_failure_act_time_test(){}

}tmt_DCFailureActTimeTest;

typedef struct tmt_dc_failure_act_value_test :public tmt_DCFailureDidtActValueTest   //Ⅰ段动作电流定值
{

public:		
	virtual void init()
	{
	  tmt_DCFailureDidtActValueTest::init();
	  strcpy(m_pszMacroID, STT_MACRO_ID_FailureProtActValue);
	} 

	tmt_dc_failure_act_value_test(){     init();}
	~tmt_dc_failure_act_value_test(){}
}tmt_DCFailureActValueTest;


void stt_init_paras(tmt_DCFailureProtParas *pParas);
void stt_init_results(tmt_DCFailureProtResults *pResults);

void stt_xml_serialize_Common(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_FailureProtDidtActValue(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_FailureProtDidtActTime(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_FailureProtActValue(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_FailureProtActTime(tmt_DCFailureProtParas *pParas, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_FailureProtDidtActValue_ex(tmt_DCFailureProtParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_FailureProtDidtActTime_ex(tmt_DCFailureProtParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_FailureProtActValue_ex(tmt_DCFailureProtParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_FailureProtActTime_ex(tmt_DCFailureProtParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_FailureProtDidtActValue(tmt_DCFailureProtResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_FailureProtDidtActTime(tmt_DCFailureProtResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_FailureProtActValue(tmt_DCFailureProtResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_FailureProtActTime(tmt_DCFailureProtResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_DCFailureDidtActValueTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize_ex(tmt_DCFailureDidtActValueTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly=FALSE);
