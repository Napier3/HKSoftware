#pragma once

#include "GbWzdCmd.h"


class CGbWzdCmdSave : public CGbWzdCmd
{
public:
	CGbWzdCmdSave();
	virtual ~CGbWzdCmdSave();

	virtual UINT GetClassID()			{		return GBWZDCLASSID_SAVE;	} 
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey();

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

public:
	

public:
	virtual BOOL Execute(DWORD dwExecMode);
	virtual BOOL IsCmdFinish();
	virtual void GetCmdInfor(CString &strText);
};