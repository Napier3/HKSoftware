#pragma once
#include "ByteBlocks.h"
#include "ProtocolXmlRWKeys.h"

class CBbDataSets:	public CByteBlocks
{
public:
	CBbDataSets(void);
	virtual ~CBbDataSets(void);

public:
	CString m_strSetCountMax;
	CString m_strSetCountMin;

	//ʵ�ʽ�����ʱ��ʹ�ã���ʱע�͵�
	//long m_nSetCountMax;
	//long m_nSetCountMin;

public:
	virtual UINT GetClassID() {        return PPCLASSID_BBDATASETS;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataSetsKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	//�ֽڿ�Ľ���		����Ľ�������������ִ�н���
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)		{		return PpParseError();		};

	//�ֽڿ������
	virtual DWORD Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)	{		return PpParseError();		};

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
};
