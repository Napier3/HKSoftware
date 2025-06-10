//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGuideBook.h  CSttGuideBook

#pragma once

#include "../SttCmdDefineGlobal.h"

#include "SttItemBase.h"

#include "SttJobGuide.h"
#include "SttDevice.h"

class CSttGuideBook : public CSttItemBase
{
public:
	CSttGuideBook();
	virtual ~CSttGuideBook();


	CString  m_strTestMacroFileID;
	CString  m_strTestTypeFile;
	CString  m_strDevID;
	CString  m_strDevBy;
	CString  m_strVersion;
	CString  m_strCommCmdConfigFile;
	CString  m_strPpTemplateFile;
	CString  m_strScriptMngrFile;
	CString  m_strPpEngineProgID;
	CString  m_strDvmFile;
	CString  m_strStandNameFile;
	CString  m_strDeviceModelFile;
	long  m_nTestControlMode;
	CString  m_strExpandConfigFile;
	CString  m_strIecfgFile;
	long  m_nReadOnly;
	long  m_nIsSaveRptToDB;
	CString  m_strAuthoritySN;
	CString  m_strAuthorityCop;
	CString  m_strScriptType;

	//2022-3-19  lijunqing  globaldatas
	CDvmDataset *m_pGlobalDatas;	//测试的全局数据
	CDataGroup *m_pItemsTec;  //2023-10-23 shaolei   南瑞windows软件，要求填写到报告中的“技术要求”、“报告数据保留小数位数”可编辑
	CDataGroup *m_pAinDataMapCfg;  //2023-11-14 遥测参数映射。在导出word报告时，需要反向映射。故增加指针记录到模板中

//重载函数
public:
	virtual UINT GetClassID() {    return STTGBXMLCLASSID_CSTTGUIDEBOOK;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttGuideBookKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

public:
	CString m_strPath;
	CString m_strFile;        //保存的dscxml的全路径
	CString m_strFile_Gbrpt;  //保存的测试记录的全路径

//属性变量访问方法
public:
	void SetGuideBookName(const CString &strName);  //2022-9-13  lijunqing
	CString GetGuideBookName();

	//2022-1-11  lijunqing
	CSttDevice* GetDevice(BOOL bCreate=FALSE);

	//2022-3-19  lijunqing  globaldatas
	CDvmDataset* GetGlobalDatas(BOOL bCreateNew=FALSE);
	void InitGlobalDatas(CDvmDataset *pGlobalDatas);
	void ClearGuideBook();
	void InitDevice();
	virtual long GetGbItemCount();
	void GetProcess(long &nIndexCurrent, long &nCountTotal);
	virtual void GetFirstTwoItemsByItemsType(CString &strFirst, CString &strSecond);
	virtual void GetAllItemsByItemsType(CExBaseList &oList);

	//2022-3-30  lijunqing
	void SaveFile();
	void SaveFile(const CString &strPath, const CString &strFileName);
	CSttItemBase* InsertItems(const CString &strParentPath, CSttItems *pItems, BOOL &bUpdateParent);
	BOOL InsertItemsEx(const CString &strParentPath, CExBaseList *pItemsList, BOOL &bUpdateParent);
	//根据类型，查找第一个CSttItems项目
	CSttItems* FindFirstItems(const CString &strType, BOOL bCheckType = TRUE);

	//2023-2-8  lijunqing
	CDvmData* FindDataByID(const CString &strID);
	BOOL GetDataValueByID(const CString &strID, float &fValue);
	void AddTimeSettingCoef(long nTSettingUnitMs);
	void UpdateSysPara(CExBaseList *pSrcList, BOOL bCreateNew);

	CDataGroup* GetItemsTec();
	void SetItemsTec(CDataGroup *pItemsTec);
	CDataGroup* GetAinDataMapCfg();
	void SetAinDataMapCfg(CDataGroup *pAinDataMapCfg);
	BOOL IsAinDataMapValid();  //遥测参数映射是否有效
	CDataGroup* GetAinRatios();
	void SetAinRatios(CDataGroup *pAinRatios);  //保存到全局数据
};

CSttItemBase* stt_gb_find_itembase(CSttGuideBook *pSttGuideBook, const CString &strItemPath);
CSttItemBase* stt_gb_find_itembase_ex(CSttGuideBook *pSttGuideBook, const CString &strItemPath);
void stt_gb_get_itempath_id(CSttItemBase *pSttItemBase, CString &strItemPath, UINT nRootClassID = STTGBXMLCLASSID_CSTTDEVICE);
void stt_gb_get_itempath_name(CSttItemBase *pSttItemBase, CString &strItemPath, UINT nRootClassID = STTGBXMLCLASSID_CSTTDEVICE);
void stt_gb_delete_childitem_commcmd(CSttItemBase *pSttItemBase, BOOL bRecursion = TRUE);  //删除pSttItemBase下及其子节点的所有通讯命令项目

//获取当前测试项及子测试项标题 zhouhj  2023.7.27
void stt_gb_get_all_child_title_itembase(CSttItemBase *pSttItemBase,CDataGroup *pDataGroup,const CString &strRootItemsID);
#ifndef _PSX_IDE_QT_
void getItems(CSttItems* pItem, CList<CSttItems*>& list);
#endif
