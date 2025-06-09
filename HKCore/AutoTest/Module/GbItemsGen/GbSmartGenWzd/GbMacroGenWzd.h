#pragma once

#include "../../../Module/DataMngr/DvmDevice.h"
#include "SttCmdWzd_CmdDataset.h"
#include "GbWzdXItemBase.h"

class CGbMacroGenWzd : public CGbWzdXItemBase
{
public:
	CGbMacroGenWzd(void);
	virtual ~CGbMacroGenWzd(void);

public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBMACROGENWZD;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbMacroGenWzdKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	//2022-10-4  lijunqing 向导页面，需要记忆上次的选择，这样提高效率
	//因此添加此对象用于记录和保存默认的对象
	CString GetInitXmlFile();
	void OpenInitXmlFile();
	void SaveInitXmlFile();
	void InitGbMacroGenWzd(CGbMacroGenWzd *pSrc);

public:
	CSttCmdWzd_Step* GetFirstStep();
	void OnAtsGenerateItems_CmdWzd(CExBaseList *pCmdGrp);
	CSttCmdWzd_Step* GetRelatedStep(CSttCmdWzd_Step *pStep);   //根据通讯前步骤，查找对应的通讯后步骤

	void InitCmdWzdRef(CDataGroup *pRoot);
	void InitCmdWzdRefEx(CDataGroup *pA_Bft);
	BOOL IsLastSetp();  //是否是最后一步
	BOOL IsFirstSetp(CSttCmdWzd_Step *pStep);  //是否是第一步
	BOOL IsFirstSetp();  //是否是第一步
	BOOL HasStepNeedShow();  //是否需要用户操作的步骤：例如：改定值、改压板、写误差

	CSttCmdWzd_Step* GetNextStep();
	CSttCmdWzd_Step* GetPreStep();
	CSttCmdWzd_Step*CurrStep()	{	return m_pCurrSetpWzd;	}
	
	//新增形参bAdd_AFT。用于标记是否添加测试后恢复。当创建测试时，勾选了“添加装置复归态”，则不用添加测试后恢复，而是添加“复归态”
	void NextClick_Init(CDataGroup &oCommCmd, BOOL bAdd_AFT); 
	void NextClick_Finish(CDataGroup &oCommCmd);
	void InitGenerateItemsParas(CSttCmdWzd_Step *pCmdDatasets, CDataGroup *pA_Bft);

public:
	CDataGroup *m_pCmdGenParas;  //OnAtsGenerateItems_CmdWzd返回的参数，root对象
	CDataGroup *m_pCmdCfg;	   //通讯前、通讯后配置
	CDataGroup *m_pMacroUIParas;   //生成的项目树形相关，TestClass、ItemsName等  STT_CMD_PARA_MacroUIParas
	CDataGroup *m_pMacroUIAttrs;    //STT_CMD_PARA_TestMacroUI
	CDvmContents *m_pCharacteristic;

	CString m_strTestClass;
	CString m_strTestMacroUI;
	long m_nRepeatTimes;
	//shaolei 2023-6-21  是否作为标题、标题等级
	long m_nRptTitle;
	long m_nTitleLevel;

	//根据cmd-wzd指令的应答，重新整理的向导步骤，方便查找下一步
	CDataGroup m_oListCmdWzdStep;

	//通讯命令向导的当前步骤，指定一个read、write、rigster命令。初始值应当为ROOT节点
	CSttCmdWzd_Step *m_pCurrSetpWzd;  

public:
	void InitCommCmdCfg();

	CDataGroup* GetCmdGenParas();
	CDataGroup* GetCmdCfg();
	CDataGroup* GetMacroUIParas();
	CDataGroup* GetMacroUIAttrs();
	CDvmContents* GetCharacteristic();

	//CDvmData* GetCmdCfgData(const CString &strCmdID);
	void AddDataToWzdCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, CDvmData *pData);
	void AddDataToWzdCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, CValue *pValue);
	void DeleteDataFromWzdCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, const CString &strDataID);
	void UpdateDataToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, CDvmData *pDvmData);
	void DeleteAllDatasToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);
	void UpdateZoneIndexToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, int nZoneIndex);
	void UpdateDelayBftToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, const CString &strDelay);
	void UpdateDelayAftToWzdCmdCfg(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath, const CString &strDelay);
	CDataGroup* FindGroup_Item(CDataGroup *pItemsGroup, const CString &strCommCmdID, const CString &strDatasetPath);
	CDataGroup* FindGroup_Dataset(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);
	CDvmData* FindData(const CString strDataID, const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);
	CDvmData* FindData_ZoneIndex(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);
	CDvmData* FindData_DelayBftCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);
	CDvmData* FindData_DelayAftCmd(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);

	void ClearEmptyCmdParas(const CString &strItemsID, const CString &strCommCmdID, const CString &strDatasetPath);
	void ClearAllCmdGenParas();  //清空通讯命令配置参数
};

CGbMacroGenWzd* gb_wzd_curr_macro_gen();
