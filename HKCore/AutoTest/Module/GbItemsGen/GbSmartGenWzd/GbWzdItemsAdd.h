#pragma once

#include "GbWzdXItemBase.h"

class CGbWzdItemsAdd : public CGbWzdXItemBase
{
public:
	CGbWzdItemsAdd(void);
	virtual ~CGbWzdItemsAdd(void);

	long m_nRepeatTimes;
	//shaolei 2023-6-21  是否作为标题、标题等级
	long m_nRptTitle;
	long m_nTitleLevel;

public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBWZDITEMSADD;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbWzdItemsAddKey();     }
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

};

//删除测试项目
class CGbWzdItemsDelete : public CDataGroup
{
public:
	CGbWzdItemsDelete(void);
	virtual ~CGbWzdItemsDelete(void);

	CString m_strParentItemsID;
	CString m_strItemsName;
	CString m_strItemsID;

public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBWZDITEMSDELETE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbWzdItemsDeleteKey();     }
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
	void GetItemPath(CString &strItemPath);
};