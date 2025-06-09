#pragma once

#include "../../../../Module/DataMngr/DataGroup.h"
#include "GbSmartGenWzdGlobal.h"

class CGbWzdItemMove : public CDataGroup
{
public:
	CGbWzdItemMove(void);
	virtual ~CGbWzdItemMove(void);

	CString m_strParentItemsID;
	CString m_strItemsName;
	CString m_strItemsID;
	CString m_strMoveType;  //move-up; move-down
	long m_nMoveTimes;  //移动的次数。上移和下移可以抵消

public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBWZDITEMMOVE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbWzdItemMoveKey();     }
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
