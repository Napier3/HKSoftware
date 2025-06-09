#pragma once
#include "../../../module/baseclass/ExBaseObject.h"
#include "ProtocolXmlRWKeys.h"

class CPpDataBind:	public CExBaseObject
{
public:
	CPpDataBind(void);
	virtual ~CPpDataBind(void);

public:
	virtual UINT GetClassID() {        return PPCLASSID_PPDATABIND;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataBindKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	CString m_strDataAttrID;
	CString m_strDataType;

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual void InitDataType();

	BOOL IsBindValid()
	{
		return (m_strDataType.GetLength() > 0 &&m_strDataAttrID.GetLength() > 0);
	}
};
