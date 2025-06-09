#pragma once
#include "DataByteBlock.h"
#include "ProtocolXmlRWKeys.h"
#include "RByteBlock.h"
#include "PpDatabind.h"

class CWDataByteBlock:	public CDataByteBlock
{
public:
	CWDataByteBlock(void);
	virtual ~CWDataByteBlock(void);

// public:
// 	CString m_strValue;
	CPpScript* CreateScript();

public:
	virtual UINT GetClassID() {        return PPCLASSID_WDATABYTEBLOCK;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataBlockKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

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
