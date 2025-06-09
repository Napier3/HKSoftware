#pragma once
#include "../../../module/baseclass/exbaselist.h"
#include "ProtocolXmlRWKeys.h"
#include "PpPackageRef.h"
#include "PpJumps.h"
#include "PpTimers.h"
#include "PpNodes.h"
#include "PpPackageDetail.h"

class CPpJumps;
class CPpNodes;
class CPpTimers;


class CPpNode :	public CExBaseList
{
public:
	CPpNode(long nType);
	virtual ~CPpNode(void);

private:
	CPpNode(void){};
	long m_nTypeID;
	CExBaseObject *m_pPackageSend;

//属性
public:
	CPpNodes* m_pResponseNodes;  //响应节点,m_strXmlKey="response"
	CPpJumps* m_pJumps;
	CPpNodes* m_pProcessNodes;    //处理节点,m_strXmlKey="process"
	CPpTimers* m_pTimers;
	CPpScript* m_pInitScript;
	CPpScript* m_pEndScript;
	CPpPackageRef *m_pPackageRef;
	CPpPackageRefs *m_pPackageRefs;

	CString m_strChannelID; //节点使用的通讯通道

public:
	virtual UINT GetClassID(){ return PPCLASSID_PPNODE; };
	virtual BSTR GetXmlElementKey()  {      return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strPpNodeKey;     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

public:
	virtual void InitAfterRead();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

public:
	CPpTimers* GetTimers();
	CPpJumps* GetJumps();
	CPpNodes* GetReponseNodes();
	CPpNodes* GetProcessNodes();
	CPpScript* GetInitScript();
	CPpScript* GetEndScript();
	CPpPackageRef* GetPackageRef();
	CPpPackageRefs* GetPackageRefs();

	void SetPackageSend(CExBaseObject *pPkgSend);
	CExBaseObject* GetPackageSend()		{	return m_pPackageSend;		};

	void GetPackageVariables(CExBaseList &oVariables);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	long GetTypeID()	{	return m_nTypeID;		}

public:
	void SetNodePackageID(const CString &strPakageID);
	CString GetNodePackageID();
	void InitPackageRef();

	BOOL IsPackageResponse(CPpPackageDetail *pPkgDetail);
	BOOL IsPackageResponses(CPpPackageDetail *pPkgDetail);
	void BeginTimer();
	void ResetTimer();
	void KillTimer();
	CPpNode* RunJumps(CPpPackageDetail *pPkgDetail);
	BOOL IsEndNode();
	CPpNode* RunTimers(DWORD dwTickCount);

	void RunInitScript(CExBaseObject *pPkg);
	void RunEndScript(CExBaseObject *pPkg);
	void RunNodeScript(CPpScript *pScript, CExBaseObject *pPkg);
};

extern CPpNode *g_pPpEndNode;

CPpNode* PpGetJumpToNode(const CString &strJumpTo, CPpNode *pJumpTo, CExBaseObject *pJumpDef);