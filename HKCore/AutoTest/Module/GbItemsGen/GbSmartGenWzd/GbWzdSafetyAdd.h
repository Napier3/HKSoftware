#pragma once

#include "../../../../Module/DataMngr/DataGroup.h"
#include "GbSmartGenWzdGlobal.h"

//对于安全措施的数据列表，作为CGbWzdSafetyAdd的子对象（CDvmData）
class CGbWzdSafetyAdd : public CDataGroup
{
public:
	CGbWzdSafetyAdd(void);
	virtual ~CGbWzdSafetyAdd(void);

	CString m_strParentItemsID;
	CString m_strItemsName;
	CString m_strItemsID;
	CString m_strMsg;

public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBWZDSAFETYADD;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbWzdSafetyAddKey();     }
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
