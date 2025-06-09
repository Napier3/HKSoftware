#pragma once
#include "BbDataSet.h"
#include "ProtocolXmlRWKeys.h"
#include "WBbData.h"

class CWBbDataSet:	public CBbDataSet
{
public:
	CWBbDataSet(void);
	virtual ~CWBbDataSet(void);

public:
	long m_nDataSetID;
	CString m_strDataSetID;
	
	long m_nDataSetCount;
	CString m_strDataSetCount;
	
	long m_nGItemIndex;
	CString m_strGItemIndex;

	long m_nPackDataCount;
	CString m_strPackDataCount;

	CWBbData* m_pWBbData;
	//long m_nDataCountMax;
	
public:
	virtual UINT GetClassID() {        return PPCLASSID_WBBDATASET;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataSetKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();


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
