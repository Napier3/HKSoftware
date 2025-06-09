#pragma once
//#include "../../../Module/BaseClass/ExBaseList.h"
#include "ByteBlocks.h"
#include "ProtocolXmlRWKeys.h"

/************************************************************************/
/* 数据集定义：定义一些列的数据，="字节块集" + "数据定义" + "字节块集"  */
/************************************************************************/

class CBbDataSet:	public CByteBlocks
{
public:
	CBbDataSet(void);
	virtual ~CBbDataSet(void);

public:
	CString m_strDataCountMin;
	CString m_strDataCountMax;

	//实际解析的时候使用，暂时注释掉
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
	//字节块的解析		具体的解析在派生类中执行解析
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)		{		return PpParseError();		};

	//字节块的制造
	virtual DWORD Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)	{		return PpParseError();		};

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
};
