#pragma once

#include "ProtocolXmlRWKeys.h"
#include "ByteBlock.h"

class CByteBlocks :	public CExBaseList
{
public:
	CByteBlocks(void);
	virtual ~CByteBlocks(void);

	BSTR m_strXmlKey;

public:
	virtual UINT GetClassID()				{        return PPCLASSID_BYTEBLOCKS;                               }
	virtual BSTR GetXmlElementKey()	{	return m_strXmlKey;	}
	//{      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strByteBlocksKey;     }

	// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	//字节块的解析		具体的解析在派生类中执行解析
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);

	//字节块的匹配		主要用于解析
	virtual DWORD Match(PACKAGEBUFFERPOS &oPkgBufPos);

	//字节块的制造
	virtual DWORD Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)	;
public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
	virtual void GetAllVariables(CExBaseList &oDestList);
	void GetBufferPos(long &nBegin, long &nEnd);
	void GetFirstAndLastByteBlock(CByteBlock **ppFirst, CByteBlock **ppLast);

};
