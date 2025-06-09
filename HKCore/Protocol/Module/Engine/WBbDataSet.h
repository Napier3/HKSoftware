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
	//�ֽڿ�Ľ���		����Ľ�������������ִ�н���
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)		{		return PpParseError();		};

	//�ֽڿ������
	virtual DWORD Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
};
