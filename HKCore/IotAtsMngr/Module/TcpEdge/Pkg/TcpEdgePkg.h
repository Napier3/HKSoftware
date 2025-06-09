//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgePkg.h  CTcpEdgePkg

#pragma once

#include "TcpEdgePkgGlobal.h"

#include "TcpEdgePkgBase.h"
#include "TcpEdgePkgHead.h"
#include "TcpEdgePkgData.h"


class CTcpEdgePkg : public CTcpEdgePkgBase
{
public:
	CTcpEdgePkg();
	virtual ~CTcpEdgePkg();

	long m_nPort;
	CTcpEdgePkgHead* m_pPkgHead;
	CTcpEdgePkgData* m_pPkgData;

public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CTCPEDGEPKG;   }
	virtual BSTR GetXmlElementKey()  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CTcpEdgePkgXmlRWKeys::CTcpEdgePkgKey();     }

public:
	//报文对象转换
	CString Produce();
	CJSON* Parser(char* pBuf);	
	CTcpEdgePkgData* CreatePkgDataByID(const CString& strPrcdrID, char* pDataJson);
	CString GetPrcdrIDByPkgData(CTcpEdgePkgData* pPkgData);
};

