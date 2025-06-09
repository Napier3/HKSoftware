#pragma once
#include "DataByteBlock.h"
#include "ProtocolXmlRWKeys.h"
#include "RByteBlock.h"
#include "Ppdatabind.h"

class CRDataByteBlock:	public CDataByteBlock
{
public:
	CRDataByteBlock(void);
	virtual ~CRDataByteBlock(void);

public:
	CString m_strValue;

public:
	virtual UINT GetClassID()				{        return PPCLASSID_RDATABYTEBLOCK;											}
	virtual BSTR GetXmlElementKey()	{      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataBlockKey;		}

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	//�ֽڿ�Ľ���		����Ľ�������������ִ�н���
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);

	//�ֽڿ������
	virtual DWORD Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)	{		return PpParseError();		};

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
};
