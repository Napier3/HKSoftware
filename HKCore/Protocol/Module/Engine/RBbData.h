#pragma once
#include "BbData.h"
#include "ProtocolXmlRWKeys.h"
#include "RDataByteBlock.h"
//#include "DeviceModel/PpTag.h"

class CRBbData:	public CBbData
{
public:
	CRBbData(void);
	virtual ~CRBbData(void);

	CPpScript	*m_pInitScript;
	CPpScript* GetInitScript();
	DWORD RunInitScript();

public:
	virtual UINT GetClassID() {        return PPCLASSID_RBBDATA;                               }
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strDataKey;     }

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual void InitAfterRead();

public:
	//字节块的解析		具体的解析在派生类中执行解析
	virtual DWORD Parse(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail);

	//字节块的制造
	virtual DWORD Produce(PACKAGEBUFFERPOS &oPkgBufPos, CExBaseList *pDetail)	{		return PpParseError();		};
public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
//	CPpTag* GetDeviceTag(CString &strDataAttrID, POS &rPosition, CExBaseList *pList);

};
