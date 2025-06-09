#pragma once

#include "ProtocolXmlRWKeys.h"
#include "PpDataBind.h"

class CPpDataBinds:	public CExBaseList
{
public:
	CPpDataBinds(void);
	virtual ~CPpDataBinds(void);

public:
	CString m_strDataBindTypeID	;
	CExBaseObject *m_pBindData;   //绑定的数据

public:
	virtual UINT GetClassID() {        return PPCLASSID_PPDATABINDS;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataBindsKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead()	{	ValidateBinds();	}

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
	CPpDataBind* GetInforIndexBind();
	long GetDataBindCount();
	POS GetFirstDataBindPos();
	CPpDataBind* GetNextDataBind(POS &pos);
	CPpDataBind* GetAtDataBind(POS &pos);
	void LogString(const CString &strTitle);

	virtual void InitBindsDataType();
//	void SetItemIndexBind(const CString &strVariableID);
	void ValidateBinds();

private:
	BOOL m_bHasInitBindsDataType;
// 	CPpDataBind *m_pOldBind;
// 	CPpDataBind *m_pNewBind;
};
