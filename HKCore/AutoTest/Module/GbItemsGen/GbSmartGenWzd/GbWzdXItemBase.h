#pragma once

#include "../../../Module/DataMngr/DvmDevice.h"
#include "GbSmartGenWzdGlobal.h"
#include "DvmContents.h"
#include "../../../../SttStudio/Module/SttGlobalDef.h"
#include "../../../../Module/API/GlobalConfigApi.h"

class CGbWzdXItemBase : public CDataGroup
{
public:
	CGbWzdXItemBase(void);
	virtual ~CGbWzdXItemBase(void);

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	CString m_strParentItemsID;
	CString m_strItemsName;
	CString m_strItemsID;

	CDvmContents *m_pParas;
public:
	void SetParas(const CString &strParas);
	//void SetRsltExpr(const CString &strRsltExpr);

	void GetItemPath(CString &strItemPath);
};
