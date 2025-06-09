#pragma once
#include "onllydatadef.h"
#include "UIMarkup.h"


#define READATTRIB(Markup,name,OutValue,inValue) \
	OutValue = Markup.GetAttrib(name); \
	if(OutValue == _T("")) \
	{ \
	OutValue = inValue; \
	} \

#define GETCHILDDATA_I(name,value,dvalue) \
	GetChildData(name,strTemp,dvalue); \
	value = _ttoi(strTemp); \

#define GETCHILDDATA_L(name,value,dvalue) \
	GetChildData(name,strTemp,dvalue); \
	value = _ttol(strTemp); \

#define GETCHILDDATA_F(name,value,dvalue) \
	GetChildData(name,strTemp,dvalue); \
	value = _wtof(strTemp); \


#define GETCHILDELEMDATA(name,value,dvalue) \
	value = m_MarkUp.GetChildElemValue(name,dvalue); \


class COnllyF66FileRead
{
public:
	COnllyF66FileRead(void);
	virtual ~COnllyF66FileRead(void);

	vector<MU_SETTING> m_downmu;
	MU_GENERALSETTTING m_mugersetting;  // MU通用配置
	GSEUI m_gseui;

public:
	BOOL ReadF66File(const CString &strPath);

private:
	BOOL ReadMUMSGTestSetXML(MSGTESTSETPtr& MuPtr);
	void ReadMUChnCfgXML(vector<MU_CHNSET>& mu_chnset);
	void ReadGOOSEChnCfgXML(vector<GSECHNCFG>& gsechncfg);
	void ReadMUMSGCfgDataXml(MuCfgData *ChDataPtr);
	void ReadMU92OpData(OTHER92OP& other92op);
	void ReadMUGerSet(MU_GENERALSETTTING& mu_gset);
	void ReadMUCfgXML(vector<MU_SETTING>& mu_setting,const CString& NodeName);
	void ReadGOOSECfgXML(vector<GSECFG>& GseCfg,const CString& NodeName);
private:
	CUIMarkup m_MarkUp;
	DWORD m_nVersion;

private:
	void InitMSGTestSet(const MSGTESTSETPtr& msgtestsetptr)
	{
		msgtestsetptr->nIndex = 0;
		msgtestsetptr->bCheck = FALSE;
		msgtestsetptr->nNum = 100;
		msgtestsetptr->nTestType = 0;
		msgtestsetptr->TestBeginPt = 0;
		memset(&msgtestsetptr->TestTypeSet,0,sizeof(int)*TestType*MaxItem);

		msgtestsetptr->TestTypeSet[1][0] = 10;

		for (int i = 2; i < TestType; i++)
		{
			msgtestsetptr->TestTypeSet[i][0] = 20;
			msgtestsetptr->TestTypeSet[i][1] = 5;
		}

		msgtestsetptr->TestTypeSet[5][2] = 2;
		msgtestsetptr->TestTypeSet[6][2] = 0;
		msgtestsetptr->TestTypeSet[10][2] = 64;
		msgtestsetptr->logicCheck = 1;
		msgtestsetptr->nStartType = 0;

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 80; j++)
			{
				msgtestsetptr->ExpPtSet[i][j] = 0;
			}
		}
	}

	void GetChildData(LPCTSTR name,CString& Outvalue,LPCTSTR inValue = _T(""))
	{
		if (m_MarkUp.FindChildElem(name))
		{
			Outvalue = m_MarkUp.GetChildData();
			if (Outvalue.IsEmpty())
			{
				Outvalue = inValue;
				return;
			}
		}

// 		CString strText;
// 		strText = name;
// 		CString strMsg;
// 		strMsg.Format(_T("查找不到节点[%s]"), strText);
// 		TRACE(strMsg);
	}

	void GetAttrib(LPCTSTR name,CString& Outvalue,LPCTSTR inValue = _T(""))
	{
		Outvalue = m_MarkUp.GetAttrib(name);

		if(Outvalue.IsEmpty())
		{
			Outvalue = inValue;
		}
	}
};
	


//SMV-异常数据基本结构体定义
#define MAX_CTRL_NUM	30
#define MAX_CHNSET_NUM	100
#define MAX_SMV_TESTTYPE_NUM	10


struct struct_ChTest
{
	char pszChName[4];   //Ua~Uw, Ia~Iw
	int ChValue;
};


struct struct_MsgTest_Auto
{		
	int  nTestType;			//测试类型
	BOOL bLimit;			//是否限制次数
	int  nLmNum;			//限制次数

	int  nCtrlSize;			//选择的控制块数	
	int  nCtrlAry[MAX_CTRL_NUM];//控制块数组

	int nSetSize;			//飞点个数
	int nSetAry[MAX_CTRL_NUM][MAX_CHNSET_NUM];//飞点数组

	int  nIndex;			//单位索引
	int  TestTypeSet[MAX_SMV_TESTTYPE_NUM][3];	//测试类型参数设置

	int  nStartStyle;		//起始方式，0:帧计数启动；1:Goose In触发

	int	 nBeginPt;			//测试起始帧
	int  nlogicCheck;		//bit31=1代表逻辑与，bit31=0代表逻辑或。其他位代表开入ABCDRabcdr
};


struct struct_MsgTest_UI
{		
	int  nTestType;			// 测试类型
	int bLimit;			// 是否限制次数
	int  nLmNum;			// 限制次数

	int  TestTypeSet[3];	// 测试类型参数设置

	int  nIndex;            // 单位索引
	int  nStartStyle;		// 起始方式，0:帧计数启动；1:Goose In触发
	int	 nBeginPt;			// 测试起始帧
	int  nlogicMode;        // 0=逻辑与   1=逻辑或   差动、状态序列都是这种方式
	int dwBin;            // 

	int nChTestCount;
	struct struct_ChTest pChTestPara[MAX_VOLT_NUMBER + MAX_CURR_NUMBER];
};

// 
// class CDownLoadCfg : public COnllyDownCfg
// {
// public:
// 	static CDownLoadCfg *g_pDownLoadCfg;
// 	static long g_nDownLoadCfgRef;
// 	static BOOL g_bWinWorkThreadExit;
// 
// 	static CDownLoadCfg* Create();
// 	static void Release();
// 
// private:
// 	CDownLoadCfg(void);
// 	virtual ~CDownLoadCfg(void);
// 
// public:
// 	CMSGManager m_MM1; // 一号板
// 	CMSGManager m_MM2; // 二号板
// 
// 	int m_Conn;        // 当前连接的是第几块板
// 	vector<MU_SETTING> m_downmu;
// 	MU_GENERALSETTTING m_mugersetting;  // MU通用配置
// 	GSEUI m_gseui;
// 	BOOL m_bDown;  // 下载是否成功 
// 	BOOL m_bDownEx;  // 是否遥信虚端子下载
// 	BOOL m_bSmvExp;  // 是否异常测试
// 
// 	BOOL m_bIsDownLoadCfgFinish;
// public:
// 
// 	static DWORD WINAPI WinWorkThread(LPVOID lpParameter);
// 
// 	// 读取配置界面配置文件，只读当前协议
// 	void ReadXMLFile(LPCTSTR strPath);
// 	// 使用前初始化
// 	void Init();
// 	// 下载
// 	BOOL DownLoadCfgFile();
// 	
// 	// 释放CMSGManager
// 	void UnInitialize();
// 	
// private:
// 	BOOL SendParToMainBoard();
// 	void NextAction();
// 	BOOL ShowCheckResult(int nReturnCode,vector<int>& LanVec_re,int nType);
// 	BOOL CompareDevInfo();
// 
// public:
// 	// SMV异常处理异常
// 	BOOL GetErrorString(UINT nIndex,CString& parstring);
// 	void SetErrorString(UINT nIdnex,MSGTESTSETPtr msgtestptr);
// 	void DownLoadErrorString(UINT nIndex, CString& parstring);
// 	void DownLoad(UINT nIndex);
// 
// private:
// 	void ParseString(MSGTESTSETPtr msgtestptr, CString& parstring);
// 	void FindData(CString& string,CString& parstring,int& Pos);
// 
// public:
// 	BOOL SetGSEChnValue(int nCtrlIndex,int nChnIndex,UINT iValue,BOOL bSend = FALSE);
// 	BOOL ReSetGSEChnValue(int nCtrlIndex,int nChnIndex,BOOL bSend = FALSE);
// 
// 
// 	// 2013-07-15增加
// 	// 使用方法
// 	// 1、判断下位机型号支不支持异常模拟
// 	// 2、SendMsgData_Convert
// 	// 以上过程都需在下载完成后进行
// 	//发送 SMV 异常数据报文(单个结构体)
// 	HRESULT SendMsgData_Convert(struct_MsgTest_UI *pMsgTest,UINT16 uTotalStateNum=1, UINT16 uCurStateIndex=0);
// 	HRESULT SendMsgData(struct_MsgTest_Auto *pMsgTest,UINT16 uTotalStateNum=1, UINT16 uCurStateIndex=0);
// 	HRESULT SendMsgData_91_92(struct_MsgTest_Auto *pMsgTest,UINT16 uTotalStateNum=1,UINT16 uCurStateIndex=0);
// 	HRESULT SendMsgData_FT3(struct_MsgTest_Auto *pMsgTest,UINT16 uTotalStateNum=1,UINT16 uCurStateIndex=0);
// 
// public:
// 	//由调用者指定, 数据发送依赖的数据管理对象
// // 	void SetSmvExpMgrObj(CSmvExpMgrObj *pMsgObj);
// // 	CSmvExpMgrObj *m_pSmvExpMgrObj;
// 	//判断是否支持 SMV 异常模拟
// 	BOOL IsSupportSmvExp(); 
// 	//判断是否有第 2 块 821 板
// 	BOOL HasIO821_2(); 
// 	void InitMsgTest_CtrlAry(struct_MsgTest_Auto *pMsgTest);
// 	void ConvertData(struct_MsgTest_Auto* pMsgTest);
// 	void my_Init_MsgTest(struct_MsgTest_Auto *pMsgTest);
// private:
// 	//根据不同的版本补充完整的结构体，以兼容旧版本的 IO821
// 	void ONLLYDEV_BIEX61850_Standardize(ONLLYDEV_BIEX61850 *pTemp);
// 
//  };

// 
// 
// class CPKTestDownLoadCfg : public CDownLoadCfg
// {
// public:
// 	CPKTestDownLoadCfg(void);
// 	virtual ~CPKTestDownLoadCfg(void);
// 
// private:
// 	BOOL InitMUChnFillSet(MUDOWNCFGSHAREPTR pmudowncfg,
// 		MU_SETTING& musetting,int nSampleType,int nFT3Format);
// 	BOOL InitDownGSECFG(GSEUI& gseui);
// 
// public:
// 	BOOL WriteMUCfgFile(vector<MU_SETTING>* pmusetting,MU_GENERALSETTTING& mugsetting);
// 	BOOL WriteGSEcfgFile(GSEUI& gseui);
// };
