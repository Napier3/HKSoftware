#pragma once
//#include "../../../Module/BaseClass/ExBaseList.h"
#include "ByteBlocks.h"
#include "ProtocolXmlRWKeys.h"

/************************************************************************/
/* ���ݼ����壺����һЩ�е����ݣ�="�ֽڿ鼯" + "���ݶ���" + "�ֽڿ鼯"  */
/************************************************************************/

class CBbDataSet:	public CByteBlocks
{
public:
	CBbDataSet(void);
	virtual ~CBbDataSet(void);

public:
	CString m_strDataCountMin;
	CString m_strDataCountMax;

	//ʵ�ʽ�����ʱ��ʹ�ã���ʱע�͵�
	//long m_nDataCountMin;
	//long m_nDataCountMax;

public:
	virtual UINT GetClassID()				{        return PPCLASSID_BBDATASET;													}
	virtual BSTR GetXmlElementKey()	{      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataSetKey;		}

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
