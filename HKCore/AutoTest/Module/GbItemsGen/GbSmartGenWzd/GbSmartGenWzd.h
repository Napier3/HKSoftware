#pragma once
#include "GbMacroGenWzd.h"
#include "GbWzdMacroTestAdd.h"
#include "GbWzdCommCmdAdd.h"
#include "GbWzdItemsNameLib.h"
#include "../Module/SttCmd/GuideBook/SttItems.h"
#include "GbWzdItemsAdd.h"
#include "GbWzdItemEdit.h"
#include "GbWzdItemMove.h"
#include "../Module/SmartTestInterface/PpSttCommConfig.h"
#include "GbWzdItemCopy.h"
#include "GbWzdItemRsltExprEdit.h"
#include "GbWzdItemSetState.h"
#include "GbWzdSafetyAdd.h"
#include "GbWzdItemPaste.h"

#define COMMCMD_RWOPTR_READ   _T("read")
#define COMMCMD_RWOPTR_REGISTER   _T("register")
#define COMMCMD_RWOPTR_WRITE   _T("write")

#define COMMCMD_RWOPTR_READ_INT  0
#define COMMCMD_RWOPTR_REGISTER_INT  1
#define COMMCMD_RWOPTR_WRITE_INT  2

class CGbSmartGenWzd : public CDataGroup
{
public:
	CGbSmartGenWzd(void);
	virtual ~CGbSmartGenWzd(void);

	//2022-10-4  lijunqing 向导页面，需要记忆上次的选择，这样提高效率
	//因此添加此对象用于记录和保存默认的对象
	CGbMacroGenWzd *m_pGbMacroGenWzdInit; 

	void UpdateGbMacroGenWzdInit();  //根据当前向导步，更新默认向导

public:
	//2023-1-28  lijunqing 
	//用于处理缺省的属性，程序启动，获取上次程序退出是的默认属性
	//主要用于通信设置部分
	BOOL m_bOwnAttrOnly;
	virtual long XmlRead(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys); 
	virtual long XmlWrite(CXmlRWDocBase &oXMLDoc,CXmlRWElementBase &oParent, BSTR pszElementKey, CXmlRWKeys *pXmlRWKeys);

	virtual UINT GetClassID() {    return DVMCLASSID_GBSMARTGENWZD;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbSmartGenWzdKey();     }
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

//属性定义
public:
	CString m_strDeviceType;  //设备类型  2022-9-28  lijunqing
	CString m_strDvmFile;
	CString m_strEngineProgID;
	CString m_strPpFile;
	CString m_strDevIP;
	long m_nDevPort;
	CString m_strLocalIP;

    //2023-2-8  lijunqing
    long  m_nIsTimeSetsUnit_ms;
	long  m_nIsAddDevReset;//是否添加装置复归态  shaolei 2023-7-24

	//2022-11-25，设计之初：保存向导对应的模板的项目结构，暂时没有存
	CDataGroup *m_pGbItemsRootTree;   //测试项目分类数据树

	BOOL m_bModifyFlag;  

public:
	CDvmDataset *m_pProtocolEngineCfg;
	CDataGroup *m_pDevice;
	CDataGroup *m_pTestApp;

	long GetEngineProgIDIndex();
	BOOL ValidateCreateParas();
	void InitProtocolEngine();
	void InitCreateParas_Device();
	void CmdDelay_Init();
	void UpdateDvmDataset(const CString &strDsPath, CDvmValues *pRptValues);
	void UpdateDvmDataset(CDvmDataset *pRptDataset);

public:
	CDataGroup *m_pTestClass;  //测试分类
	CDataGroup *m_pCommCmdCfg; //通讯命令配置，配置新建通讯命令项目时，能创建的通讯项目
	CDvmDevice *m_pDvmDevice; //设备数据模型，创建测试时，打开选中的模型文件
	CDataGroup *m_pCmdDelay;

	CGbMacroGenWzd *m_pCurrGbMacroGenWzd;  //当前的向导
	CGbWzdItemCopy *m_pCurrItemCopy;  //当前被复制的项目

public:
	//2023-1-28  lijunqing  将通信部分的内容，全部移植到向导对象
	CPpSttCommConfig m_oCommConfig;
	CPpSttCommConfig* SaveDevInfoToCfg();
	void SaveDevInfoToCfg_MMS(CPpSttCommConfig *pCommCfg); 
	void SaveDevInfoToCfg_CMS(CPpSttCommConfig *pCommCfg); 
	void SaveDevInfoToCfg_PpEngine(CPpSttCommConfig *pCommCfg); //zhouhj 2023.12.6

public:
	void CreateNew();
	void InitGbSmartGenWzd();
	CString InitDvmDevice(const CString &strFile);  //返回模型文件的全路径
	CDvmDataset* FindDatasetByPath(const CString &strPath);
	CString ImportDvmFile(const CString &strFile);    //重新导入模型，并返回模型文件的全路径
	void AfterImportDvmFile();  //导入模型后，清理跟commcmd相关的记录

	CGbMacroGenWzd* NewGbMacroGenWzd();
	void CancelMacroGenWzd();

	void OpenSmartGenWzdFile();
	void OpenSmartGenWzdFileForAttr();
	void OpenSmartGenWzdFile(const CString &strFile);
	void SaveSmartGenWzdFile(const CString &strFile);
	void SaveSmartGenWzdFile();
	CString GetDefaultSmartGenWzdFile();

	//测试项目分类数据树  编辑
	void NewItems(const CString &strParentPath, CExBaseObject *pItems);
	void EditItems(const CString &strParentPath, const CString &strItemsID, const CString &strItemsName
		, CExBaseObject *pItems, long nRepeatTimes, long nRptTitle, long nTitleLevel);
	void DeleteItems(const CString &strParentPath, CExBaseObject *pItems);

	//向导记录的编辑
	void DeleteItems_SttItems(const CString &strParentPath, CSttItems *pSttItems);
	void DeleteItems_SttItems(CSttItems *pSttItems);
	void DeleteItems_SttCommCmd(const CString &strParentPath, CSttCommCmd *pSttCommCmd);
	void DeleteItems_SttCommCmd_Wzd(CSttCommCmd *pSttCommCmd, CDataGroup *pGrp);
	void DeleteItems_SttMacroTest(const CString &strParentPath, CSttMacroTest *pSttMacroTest);
	void MoveItem(const CString &strParentPath, CExBaseObject *pItem, const CString &strMoveType);
	void ItemPaste(const CString &strDestParentPath, CExBaseObject *pDestItem);
	void AfterItemPaste(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste);

	void AfterItemPaste_MacroGenWzd(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbMacroGenWzd* pMacroGenWzd, CExBaseList *pList);
	void AfterItemPaste_CommCmdAdd(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdCommCmdAdd *pCommCmdAdd, CExBaseList *pList);
	void AfterItemPaste_MacroTestAdd(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdMacroTestAdd *pMacroTestAdd, CExBaseList *pList);
	void AfterItemPaste_ItemsAdd(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdItemsAdd *pItemsAdd, CExBaseList *pList);
	void AfterItemPaste_ItemEdit(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdItemEdit *pItemEdit, CExBaseList *pList);
	void AfterItemPaste_ItemMove(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdItemMove *pItemMove, CExBaseList *pList);
	void AfterItemPaste_ItemSetState(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdItemSetState *pItemSetState, CExBaseList *pList);
	void AfterItemPaste_SafetyAdd(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdSafetyAdd *pSafetyAdd, CExBaseList *pList);
	void AfterItemPaste_CommCmdUpdate(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdCommCmdUpdate *pCommCmdUpdate, CExBaseList *pList);
	void AfterItemPaste_CommCmdAddGrp(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdCommCmdAddGrp *pCommCmdAddGrp, CExBaseList *pList);
	void AfterItemPaste_ItemsDelete(CGbWzdItemCopy *pCopy, CGbWzdItemPaste *pPaste, CGbWzdItemsDelete *pItemsDelete, CExBaseList *pList);

	CGbMacroGenWzd* FindMacroGen(const CString &strItemsID, const CString &strItemsName, const CString &strParentItemPath);
	CGbWzdXItemBase* FindXItemBase(const CString &strItemsID, const CString &strParentItemPath);
	CGbWzdItemMove* FindItemMove(const CString &strItemsID, const CString &strParentItemPath);
	CGbWzdItemRsltExprEdit* FindItemRsltExprEdit(const CString &strItemsID, const CString &strParentItemPath);
	CGbWzdItemSetState* FindItemSetState(const CString &strItemsID, const CString &strParentItemPath);
	CGbWzdSafetyAdd* FindSafetyAdd(const CString &strItemsID, const CString &strParentItemPath);
	CGbWzdCommCmdUpdate* FindCommCmdUpdate(const CString &strItemsID, const CString &strParentItemPath);
	CGbWzdCommCmdAddGrp* FindCommCmdAddGrp(const CString &strParentItemPath);
	CGbWzdItemsDelete* FindItemsDelete(const CString &strItemsID, const CString &strParentItemPath);

	CGbWzdMacroTestAdd* MacroTestAdd(const CString &strParentItemPath, const CString &strItemID, const CString &strItemName, const CString &strMacroID);
	CGbWzdCommCmdAdd* CommCmdAdd(const CString &strParentItemPath, const CString &strItemID, const CString &strItemName, const CString &strCommCmdID);
	CGbWzdItemsAdd* ItemsAdd(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName
		, long nRepeatTimes, long nRptTitle, long nTitleLevel);
	CGbWzdItemRsltExprEdit* ItemsRsltExprEdit(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName);
	CGbWzdItemSetState* ItemsSetState(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName
		, long nSelect, long nEnable, long nShow);
	CGbWzdSafetyAdd* SafetyAdd_Add(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName
		, const CString &strMsgs, CDataGroup *pListDatas = NULL);
	CGbWzdSafetyAdd* SafetyAdd_Edit(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName
		, const CString &strMsgs, CDataGroup *pListDatas = NULL);
	void SafetyAdd_Delete(const CString &strParentItemPath, const CString &strItemsID);
	CGbWzdCommCmdUpdate* CommCmdUpdate(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName, const CString &strContents);
	CGbWzdCommCmdAddGrp* CommCmdAddGrp(const CString &strParentItemPath, long nAftUseReset, long nAddCommCmd);
	CGbWzdItemsDelete* ItemsDelete(const CString &strParentItemPath, const CString &strItemsID, const CString &strItemsName);

	CDvmData* GetCmdCfgData(const CString &strCmdID, const CString &strCfgID);  //2022-9-19  lijunqing
	CString GetItemCopyType();  //返回当前被复制的项目的项目类型
	void SetItemCopy(const CString &strParentItemPath, CExBaseObject *pCurrSelItem, const CString &strItemPath);

protected:
	CString m_strSmartGenWzdFile;

protected:
	void InitTestClass();
	void stt_OpenCommCmdCfg();
	CDataGroup* GetParentItems(const CString &strParentPath);
	void InitWzd();
	CString GetEngineProgID();
	CDataGroup* IsCommCmdAddByWzd(const CString &strPath, CSttCommCmd *pSttCommCmd, BOOL &bWzd);
};
