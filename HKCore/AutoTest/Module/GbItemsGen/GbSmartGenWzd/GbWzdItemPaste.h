#pragma once

#include "../../../../Module/DataMngr/DataGroup.h"
#include "GbSmartGenWzdGlobal.h"

class CGbWzdItemPaste : public CDataGroup
{
public:
	CGbWzdItemPaste(void);
	virtual ~CGbWzdItemPaste(void);

	CString m_strSrcParentItemsID;
	CString m_strSrcItemsName;
	CString m_strSrcItemsID;
	CString m_strItemType;  //目前仅支持：macrotest, commcmd, items
	CString m_strDestParentItemsID;
	CString m_strDestItemsName;
	CString m_strDestItemsID;

public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBWZDITEMPASTE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbWzdItemPasteKey();     }
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
	void GetDestItemPath(CString &strDestItemPath);
};
