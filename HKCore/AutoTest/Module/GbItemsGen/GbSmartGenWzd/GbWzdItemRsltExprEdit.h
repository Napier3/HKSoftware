#pragma once

#include "../../../../Module/DataMngr/DataGroup.h"
#include "GbSmartGenWzdGlobal.h"
#include "DvmContents.h"

class CGbWzdItemRsltExprEdit : public CDataGroup
{
public:
	CGbWzdItemRsltExprEdit(void);
	virtual ~CGbWzdItemRsltExprEdit(void);

	CString m_strParentItemsID;
	CString m_strItemsName;
	CString m_strItemsID;

public:
	virtual UINT GetClassID() {    return DVMCLASSID_GBWZDITEMRSLTEXPREDIT;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CGbWzdItemRsltExprEditKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

public:
	CDvmContents *m_pRsltExpr;

public:
	void SetRsltExpr(const CString &strRsltExpr);

};
