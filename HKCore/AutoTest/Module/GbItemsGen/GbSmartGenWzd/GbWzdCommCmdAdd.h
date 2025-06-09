#pragma once

#include "GbWzdXItemBase.h"

//针对单个添加的通讯命令（人工手动添加）
class CGbWzdCommCmdAdd : public CGbWzdXItemBase
{
public:
	CGbWzdCommCmdAdd(void);
	virtual ~CGbWzdCommCmdAdd(void);

	CString m_strCommCmdID;

public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBWZDCOMMCMDADD;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbWzdCommCmdAddKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:

	void AddDataToWzdCmdCfg(CDvmData *pData ,CDvmDataset *pDataset);
	void AddDataToWzdCmdCfg(CValue *pValue ,CDvmDataset *pDataset);
	void DeleteAllDatasToWzdCmdCfg();
	void DeleteDataFromWzdCmdCfg(const CString &strDataID);
	void UpdateDataToWzdCmdCfg(CDvmData *pDvmData);
	void UpdateZoneIndexToWzdCmdCfg(int nZoneIndex);
	void UpdateDelayBftToWzdCmdCfg(const CString &strDelay);
	void UpdateDelayAftToWzdCmdCfg(const CString &strDelay);

	void ClearEmptyCmdParas(CDvmDataset *pDataset);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//针对“设置装置复归态”中的通讯命令，既不是单独添加的，又不是通过向导添加的
//添加“装置复归态”中的通讯命令时，不会创建CGbWzdCommCmdUpdate对象。但在编辑修改时，会创建CGbWzdCommCmdUpdate对象
class CGbWzdCommCmdUpdate : public CDataGroup
{
public:
	CGbWzdCommCmdUpdate(void);
	virtual ~CGbWzdCommCmdUpdate(void);

	CString m_strParentItemsID;
	CString m_strItemsName;
	CString m_strItemsID;

	CDvmContents *m_pCommCmd;
	CDvmContents* GetCommCmd();
	void GetCommCmd_String(CString &strCommCmd);
public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBWZDCOMMCMDUPDATE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbWzdCommCmdUpdateKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual void InitAfterRead();
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	void GetItemPath(CString &strItemPath);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//添加测试前、后通讯组合
class CGbWzdCommCmdAddGrp : public CDataGroup
{
public:
	CGbWzdCommCmdAddGrp(void);
	virtual ~CGbWzdCommCmdAddGrp(void);

	CString m_strParentItemsID;
	long m_nAftUseReset;  //测试后恢复是否使用“装置复归态”
	long m_nAddCommCmd;   //是否添加通讯命令项目

public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBWZDCOMMCMDADDGRP;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbWzdCommCmdAddGrpKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual void InitAfterRead();
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
};