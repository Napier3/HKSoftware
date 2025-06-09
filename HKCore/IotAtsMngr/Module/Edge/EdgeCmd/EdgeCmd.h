//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeCmd.h  CEdgeCmd

#pragma once

#include "EdgeCmdMngrGlobal.h"
#include "EdgeGlobalDef.h"
#include "EdgeParam.h"

#include "..\MqttEdgePkgBase.h"

class CEdgeCmd : public CMqttEdgePkgBase
{
public:
	CEdgeCmd();
	virtual ~CEdgeCmd();


	long  m_nCode;
	CString  m_strMsg;
	CString  m_strApp;
	CString  m_strSign;
	long  m_nMid;//long long
	CString  m_strType;
	CString  m_strTimestamp;
	CString  m_strDeviceId;
	long  m_nExpire;
//重载函数
public:
	virtual UINT GetClassID() {    return EDGECMDCLASSID_CEDGECMD;   }
	virtual BSTR GetXmlElementKey()  {      return CEdgeCmdMngrXmlRWKeys::CEdgeCmdKey();     }
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

private:
	CEdgeParam *m_pEdgeParam;
	CString m_strProcedureID;
	CString m_strErrorInfo;

public:
	CEdgeParam* GetEdgeParam()	{	return m_pEdgeParam;	}
	void SetEdgeParam(CEdgeParam* pEdgeParam);
	CString GetProcedureID()	{	return m_strProcedureID;	}
	void SetProcedureID(const CString& strProcedureID){ m_strProcedureID = strProcedureID; }
	CString GetCmdErrorInfo() { return m_strErrorInfo; }

public:
	void PraseCmdBuf(char *pBuf,long nLen, char *pszDestBuffer,const CString &strFormat=EDGE_DATA_FORMAT_JSON);
};

