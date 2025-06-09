#pragma once
#include "BbDataSets.h"
#include "ProtocolXmlRWKeys.h"

class CWBbDataSets:	public CBbDataSets
{
public:
	CWBbDataSets(void);
	virtual ~CWBbDataSets(void);

public:
	virtual UINT GetClassID()				{        return PPCLASSID_WBBDATASETS;										}
	virtual BSTR GetXmlElementKey()	{      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataSetsKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	//字节块的解析		具体的解析在派生类中执行解析
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)		{		return PpParseError();		};

	//字节块的制造
	virtual DWORD Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);
public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
};
