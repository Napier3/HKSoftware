#ifndef _SttNativeTestMngrBaseApp_h__
#define _SttNativeTestMngrBaseApp_h__

#include "../../../Module/OSInterface/OSInterface.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/xml/XmlRWInterface.h"
#include "../../../Module/DataMngr/DataMngrGlobal.h"
#include "../../../Module/TestMacro/TestMacroGlobal.h"
#include "../../../Module/Log/LogPrint.h"
#include "../../../Module/Socket/XPing.h"
#include "../../../Module/FilterText/FilterTextGlobal.h"
#include "../../Module/Engine/SttPowerTestEngineBase.h"

#include "../../../61850/Module/CfgDataMngr/IecCfgDataMngrGlobal.h"
#include "../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"
#include "../../Module/SttTestResourceMngr/SttTestResourceMngr.h"

#include "../../Module/SttTest/Common/tmt_soe_test.h"

#define FILE_SOETESTPARA		"SoeTest.soexml"
#define FILE_SYSTEMPARA			"SystemParas.sysxml"
#define MACROID_SOETEST			"SttSoeTest"

//20230-01-03 wuxinyi 切换测试模块
#define STT_UPDATE_TESTMACRO_SM_ID			_T("TestMacroSM")				//TestMacroSM共享内存ID
#define STT_UPDATE_TESTMACRO_TPLID			_T("UpdateTestMacroTplID")	//各个测试模块的tpl_id
#define STT_UPDATE_TEST_XML_POSTFIX			_T("tplxml")				//新增测试模块模板文件后缀
#define ARGV_CMD_PARA_ID_TmpPath			_T("TmpPath")					//模板文件路径

//2021-5-30  lijunqing 
#include "../../Module/SttTest/Common/tmt_test_mngr.h"

//2021-9-6  lijunqing 
#include "../../../AutoTest/Module/Characteristic/CharacteristicLib.h"
#include "../../../AutoTest/Module/Characteristic/Characteristics.h"
#include "../../../Module/XDrawBase/XDrawPointEx.h"
#include "../../../Module/XDrawBase/XDrawLineEx.h"


enum ACTION_TYPE{
	ACTION_OPENTESTPARA = 0,
	ACTION_SAVETESTPARA,
	ACTION_SAVEASTESTPARA,
	ACTION_START,
	ACTION_MANUTRIGER,
	ACTION_STOP,
	ACTION_SYSTEMPARA,
	ACTION_OFFLINE,
	ACTION_COMMONPARA,
	ACTION_SETTING,
	ACTION_SETSWITCH,
	ACTION_IEC,
	ACTION_AUXOUTPUT,
	ACTION_SOETEST,
	ACTION_NETSET,
	ACTION_SETREPORT,
	ACTION_SYSREPORT,
	ACTION_WORDREPORT,
	ACTION_OPENREPORT,
	ACTION_SAVEREPORT,
	ACTION_VIEWSWITCH,
	ACTION_VIEWSTATINF,
	ACTION_VIEWTEST,
	ACTION_VIEWREPORT,
	ACTION_UPDATELOCAL,
	ACTION_UPDATETESTAPP,
	ACTION_CHRSMAPS,
	ACTION_AUXDC,
	ACTION_MODULESGEAERSWITCH,
	ACTION_VERSIONINFOR,
	ACTION_IECCap
};	

enum MONITOR_TYPE{
	MONITOR_PLOT = 0,
	MONITOR_VECTOR,
	MONITOR_POWER,
	MONITOR_SEQUENCE,
	MONITOR_LINEVOLT,
	MONITOR_INFO,
	MONITOR_WAVE
};

enum PARAS_TYPE{
	PARAS_TEST = 0,
	PARAS_GOOSE,
	PARAS_EXINPUTSET,
	PARAS_EXOUTPUTSET
};
extern bool g_bTestAppConnect;

//改为全局变量，方便通过配置修改颜色
extern unsigned long  _CHARACTER_TEST_POINT_COLOR_Initial ;//               RGB(255, 0, 0)                //初始状态颜色  红色
extern unsigned long  _CHARACTER_TEST_POINT_COLOR_Selected  ;//              RGB(0, 255, 255)              //选中状态颜色 紫色
extern unsigned long  _CHARACTER_TEST_POINT_COLOR_EndOfTest  ;//             RGB(255, 0, 255)              //试验结束颜色 青色
extern unsigned long  _CHARACTER_TEST_POINT_COLOR_TestLine  ;//              RGB(0, 255, 0)              //当前测试点直线颜色

class CSttXTestMngrBaseApp : public CSttPowerTestEngineBase
{
public:
	CSttXTestMngrBaseApp();
	virtual ~CSttXTestMngrBaseApp();

public:
	void initLocalSysPara();

	virtual CSttTestResourceBase* CreateTestResource(){return NULL;}//创建测试资源
	virtual void InitTestResource();//初始化测试资源

	void SetModifyPara()	{	m_bTmtParaChanged = TRUE;	}	//20210913 sf add
	BOOL GetModifyPara()	{	return m_bTmtParaChanged;	}
	//IEC
	BOOL m_bIECParasChanged;

	CIecCfgGoutDatas* m_pIecCfgGoutDatas;
	virtual void GenerateTestCmdFromIEC(CSttParas &oSttParas);

	CSttTestResourceBase *m_pSttTestResource;

	virtual void GenerateTestCmdFromDefaultOutput(CSttTestCmd &oSttTestCmd);

	CString getSystemParasFilePath();

	tmt_SoeParas m_oSoeParas;	

	CString getSoeParasFilePath();
	BOOL SaveSoeParasFile(const CString& strSoeFile="");
	long OpenSoeParasFile(const CString& strSoeFile="");
	void initDefaultSoeParaFile();
	virtual void GenerateTestCmdFromSoeParas(CSttTestCmd &oSttTestCmd);

	//TestApp
	PTMT_PARAS_HEAD  m_pTmt_Paras_Head;//mym 2021-7-23

	void GetSystemParaDataGroup();

	BOOL  m_bInitConneced;	//初始连接标志
	bool  m_bGooseFlag;	//Goose置灰标记
	bool  m_bFt3Flag;//FT3置灰标记

public:
	BOOL m_bTmtParaChanged;  //2021-9-13  lijunqing  参数编辑保存部分
	bool m_bViewTestStarted;//zhouhj 20211122 该成员变量放入此基类中,在脱机模式下,共用此参数

	//2021-5-30  lijunqing
	//测试控制部分：公共部分
	TMT_PARAS_MNGR m_oTmtTestMngr;

	CXDrawList  m_oCharDrawList; //特性曲线相关的测试点、测试线绘图对象
//	CAutoCriticSection m_oCriticSectionCharDrawList;
	CCharElementInverse *m_pCharElementBase;	//反时限绘图相关 sf 20211012

	long m_nCurrTestIndex;  ////当前测试点编号
	virtual void SerializeTestParas(CSttXmlSerializeBase *pMacroParas, PTMT_PARAS_HEAD pParas,
		long nVolRsNum,long nCurRsNum,long nBinExNum,long nBoutExNum,BOOL bHasGoosePub)	{	}
	virtual BOOL HasNextNeedTest();  ////是否还有下一个测试点需要测试
	virtual long GetNextItemNeedTest();
	virtual BOOL TestCurrTestPoint();
	virtual void FinishTestPoint( int nIndex);
	virtual void GenerateTestCmdFromParas(CSttTestCmd &oSttTestCmd,bool bSel=true);
	virtual void UpdateTestCmdFromParas(CSttTestCmd &oSttTestCmd,bool bSel=true);
	virtual void InitTestCmdFromParas(CSttTestCmd &oSttTestCmd, const CString &strCmdID, bool bSel=true);
	virtual void ClearTestMngr();
	virtual void ClearResult(PTMT_PARAS_HEAD pHead);
	virtual void OnSearchPointReport(const CString &strMacroID, CDataGroup *pSearchResults){}//zhouhj  增加用于搜索类获取当前点值
	virtual long OnUpdateSyncTime(CDataGroup *pRtSyncTime);

	virtual long Event_OnProcessComtradeRequstData(long nIndex){return 0;}
	virtual long Event_OnProcessComtradeSendDataStartAck(long nIndex){return 0;}
	
	//2022.5.20 caoxc 增加函数，在打开模板文件时清除测试结果
	virtual void ClearTestResult(PTMT_PARAS_HEAD pParas){};

	void ChangeCurrTestPoint(int nIndex);	//20210917 sf 更新当前测试点颜色和选中状态
	void DeleteAllDrawPoints();

	virtual PTMT_PARAS_HEAD CreateTestParas(const char * pszMacroID) {return NULL;}//zhouhj 20211118 修改基类虚函数,确保BaseFrameClient工程编译通过
	virtual PTMT_PARAS_HEAD CreateTestParas(PTMT_PARAS_HEAD pCurr);

	//2021-9-7  lijunqing
	virtual CExBaseObject* CreateCharDraw(PTMT_PARAS_HEAD pTmtPara) {return NULL;}//zhouhj 20211118 修改基类虚函数,确保BaseFrameClient工程编译通过

	void Test_Add(PTMT_PARAS_HEAD pParas);
	PTMT_PARAS_HEAD Test_GetAt(long nIndex);
	void Test_InsertAt(PTMT_PARAS_HEAD pParas, long nIndex);
	void Test_SetAt(PTMT_PARAS_HEAD pParas, long nIndex);
	void Test_DeleteAt(long nIndex);
	PTMT_PARAS_HEAD m_pCurrOpTest;

	virtual CString GetDefaultParaFile();
	BOOL OpenTestTestMngrFile(const CString& strParasFile);
	BOOL SaveTestMngrFile(const CString& strParasFile);

	BOOL IsValidTestParasFile(const CString& strParasFile,BOOL bOpen=TRUE);
	int GetTestItemTableRow(PTMT_PARAS_HEAD pCurr);

	bool GetSetValue(char *pszSetID, float &fValue)
	{
		CDvmData *pFind = (CDvmData*)g_pTmt_SetsRef->FindByID(pszSetID);

		if (pFind != NULL)
		{
			fValue = pFind->m_strValue.toFloat();
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}

	bool GetSetValue(char *pszSetID, long &fValue)//20230804 suyang
	{
		CDvmData *pFind = (CDvmData*)g_pTmt_SetsRef->FindByID(pszSetID);

		if (pFind != NULL)
		{
			fValue = pFind->m_strValue.toLong();
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	CString GetSetName(CString strID)	//20210913 sf
	{
		CDvmData *pFind = (CDvmData*)g_pTmt_SetsRef->FindByID(strID);
		
		CString strName;
		if (pFind != NULL)
		{
			strName = pFind->m_strName;
			return strName;
		}
		else
		{
			return _T("");
		}
	}

	//如果是新建测试点，需要根据m_strExprValueID中定义的数据，初始化测试点的各表达式
	//pszExprGroupPath="Common",  "Gnd1"
	//<group name="通用" id="Common" data-type="" value="">
	//例如:<group name="接地距离一段" id="Gnd1" data-type="" value="">
	virtual void InitTestParaExpr(PTMT_PARAS_HEAD pItemPara, char *pszExprGroupPath, bool bInit = false);
	//virtual void InitTestParaExpr_Ex(PTMT_PARAS_HEAD pItemPara, char *pszExprGroupPath);

	//根据具体测试功能对每个数据的表达式进行调整，例如：故障类型为”相接地“
	//则只有TtripA的表达式为 TtripA > 0 其他TtripB的表达式为 TtripB <= 0
	virtual void AdjustTestParaExpr(PTMT_PARAS_HEAD pItemPara){};

	//2021-7-26  lijunqing  获取测试点的结果变量，用于表达式计算
	virtual void InitTestItemResultRef(PTMT_PARAS_HEAD pItemPara) {}//zhouhj 20211118 修改基类虚函数,确保BaseFrameClient工程编译通过

public:
	void SerializeGoosePubs(CSttXmlSerializeBase *pXmlGoosePubsParent,CIecCfgGoutDatas *pGoutDatas);//完成GOOSE发布数据对象的串行化
	void SerializeGooseGinPubs(CSttXmlSerializeBase *pXmlGoosePubsParent,CIecCfgGinDatas *pGinDatas);//完成GOOSE订阅数据对象的串行化
	void SerializeFT3Pubs(CSttXmlSerializeBase *pXmlFT3PubsParent,CIecCfgDatasSMV *pIecCfgDatasSMV);//完成FT3发布数据对象的串行化

	BOOL IsTestAppExist(const CString &strIP);

	virtual void OnReport_ReadDevice(const CString &strMacroID, CDataGroup *pParas);//读取Device的Report解析函数

	virtual void OnTestInitialize(CEventResult *pEventInfo,CDataGroup *pParas);
	virtual void EndBinStateOnStarting();

	CString m_strParaFileTitle;		//过流试验模板文件
	CString m_strParaFilePostfix;	//project(*.octxml)
	CString m_strDefaultParaFile;	//默认参数文件路径

	CString m_strFilePath;   //全局路径

	QList<CIecCfgGoutDatas*> m_listGoosePub;		//状态序列的Goose数据发布列表
	virtual void InitGoosePubDataGroups();
	CIecCfgGoutDatas *GetGoutDatas(long nIndex)
	{
		if (nIndex<0)
		{
			return NULL;
		}

		if (nIndex>=m_listGoosePub.size())
		{
			return NULL;
		}

		return m_listGoosePub.at(nIndex);
	}
	QList<CIecCfgGinDatas*> m_listGooseGinPub;		//Goose数据订阅列表
	virtual void InitGooseGinPubDataGroups();
	CIecCfgGinDatas *GetGinDatas(long nIndex)
	{
		if (nIndex<0)
		{
			return NULL;
		}

		if (nIndex>=m_listGooseGinPub.size())
		{
			return NULL;
		}

		return m_listGooseGinPub.at(nIndex);
	}

	//chenling 状态序列的FT3数据发布列表20230511
	QList<CIecCfgDatasSMV*> m_listFT3Pub;		
	virtual void InitFT3PubDataGroups();
	CIecCfgDatasSMV *GetFT3Datas(long nIndex)
	{
		if (nIndex<0)
		{
			return NULL;
		}

		if (nIndex>=m_listFT3Pub.size())
		{
			return NULL;
		}

		return m_listFT3Pub.at(nIndex);
	}

	void GetSMVDataAppIDs(QList<int> &listAppIDs);

//2021-9-6  lijunqing
//特性曲线
public:
	CCharacteristics *m_pCharacteristics;
	
	BOOL OpenCharacteristicsFile(const CString &strFile);

//2023-12-27  wuxinyi
//切换测试模块 
public:
	CString ReadXmlTplID(const CString & strSrcXmlFile);//从xml文件中读取tpl_id
	virtual CString GetTplID();//获取tpl_id,一般为当前exe名称,smv异常模拟重写该函数
	virtual BOOL IsCurrModuleTplID(const CString &strTplID);//是否为当前测试模块,smv异常模拟重写该函数
	virtual void UpdateTestModule(const CString& strParasFile, const CString &strTplID){}//更新测试模块
};

extern CSttXTestMngrBaseApp* g_theSttXTestMngrBaseApp;
extern CSttTestAppCfg g_oSttTestAppCfg;



#endif //_SttNativeTestMngrBaseApp_h__
