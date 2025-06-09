#pragma once
#include "PpPackage.h"


class CPpParsePackage :	public CPpPackage
{
public:
	CPpParsePackage(void);
	virtual ~CPpParsePackage(void);

	CExBaseObject *m_pPackageDetailRef;
	PPACKAGEBUFFERPOS m_pBufferPos;
	long m_nRequiredLen;  //匹配时，用于检查接收报文缓冲区是否有足够的报文数据

public:
	virtual UINT GetClassID() {        return PPCLASSID_PPPARSEPACKGE;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strRPackageKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	//字节块的解析		具体的解析在派生类中执行解析
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);

	//字节块的匹配		主要用于解析
	virtual DWORD Match(PACKAGEBUFFERPOS &oPkgBufPos);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	void CloneAppendInterfaceVariable(CExBaseList &oDestList);
	
};
