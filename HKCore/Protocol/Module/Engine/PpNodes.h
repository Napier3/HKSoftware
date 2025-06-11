#pragma once
#include "ExBaseList.h"
#include "ProtocolXmlRWKeys.h"
#include "PpNode.h"

class CPpNodes :	public CExBaseList
{
public:
	CPpNodes(long nTypeID);
	virtual ~CPpNodes(void);

private:
	CPpNodes(){}

	long m_nTypeID;//0Îªresponse£¬1Îªprocess
//ÊôÐÔ
public:

//
public:
	virtual UINT GetClassID(){ return PPCLASSID_PPNODES; };
	virtual BSTR GetXmlElementKey();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
	long GetTypeID()	{	return m_nTypeID;		}
	BOOL IsPpResponseNodes()	{	return (m_nTypeID == PPNODE_TYPE_RESPONSE); }
	BOOL IsPpProcessNodes()	{	return (m_nTypeID == PPNODE_TYPE_PROCESS); }
};
