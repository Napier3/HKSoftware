#pragma once

#include "GbWzdXItemBase.h"

//��Ե�����ӵ�ͨѶ����˹��ֶ���ӣ�
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
//��ԡ�����װ�ø���̬���е�ͨѶ����Ȳ��ǵ�����ӵģ��ֲ���ͨ������ӵ�
//��ӡ�װ�ø���̬���е�ͨѶ����ʱ�����ᴴ��CGbWzdCommCmdUpdate���󡣵��ڱ༭�޸�ʱ���ᴴ��CGbWzdCommCmdUpdate����
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
//��Ӳ���ǰ����ͨѶ���
class CGbWzdCommCmdAddGrp : public CDataGroup
{
public:
	CGbWzdCommCmdAddGrp(void);
	virtual ~CGbWzdCommCmdAddGrp(void);

	CString m_strParentItemsID;
	long m_nAftUseReset;  //���Ժ�ָ��Ƿ�ʹ�á�װ�ø���̬��
	long m_nAddCommCmd;   //�Ƿ����ͨѶ������Ŀ

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