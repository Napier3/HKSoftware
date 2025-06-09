#pragma once
#include "..\..\..\..\module\baseclass\exbaselist.h"

#include "EpCmmNetConfig.h"
#include "EpCmmSerialConfig.h"

class CEpDeviceCmmConfig :	public CExBaseList
{
public:
	CEpDeviceCmmConfig(void);
	~CEpDeviceCmmConfig(void);

public:
	//基本方法
	virtual void Init();
	virtual long InitAfterSerialize();
	virtual UINT GetClassID(){return EPCLASSID_DEVICE_CMM_CONFIG;};

	//串行化
	virtual BSTR GetXmlElementKey()  {      return CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strCmmConfigKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	//编辑
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//创建子对象
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

public:
	//打开文件
	BOOL OpenPpTemplateXmlFile(const CString &strFile);

	/************************************************************************/
	/* 2011-01-13 添加 用于点表编辑
	*/
	/************************************************************************/
	virtual long InsertChildrenTreeCtrl(CTreeCtrl *pTreeCtrl, HTREEITEM htiParent);

	CExBaseObject* GetChildByClassID(UINT nClassID);
};
