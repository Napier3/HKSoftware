//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IotPpNode.h  CIotPpNode

#pragma once

#include "IOTPPGlobal.h"


#include "IotPpAcks.h"
#include "IotPpTimers.h"

class CIotPpNode : public CExBaseList
{
public:
	CIotPpNode();
	virtual ~CIotPpNode();


	CString  m_strPkg_Id;
	SYSTEMTIME m_tmRunBegin;	//RunNode开始时间，用于检测报文是否过时
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOTPPNODE;   }
	virtual BSTR GetXmlElementKey()  {      return CIOTPPXmlRWKeys::CIotPpNodeKey();     }
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

//私有成员变量
private:
	CIotPpAcks *m_pIotPpAcks;
	CIotPpTimers *m_pIotPpTimers;

//私有成员变量访问方法
public:
	CIotPpAcks* GetIotPpAcks()	{	return m_pIotPpAcks;	}
	CIotPpTimers* GetIotPpTimers()	{	return m_pIotPpTimers;	}

//属性变量访问方法
public:
	void SetRunBegin(){GetLocalTime(&m_tmRunBegin);}
	void BeginTimer(DWORD dwCurrTick);
	void KillTimer();
	BOOL IsTimerOut(DWORD dwCurrTick,CIotPpNode **ppCurNode);

	void UpdateTimers(CDvmDataset *pAttrDataset,CExBaseList *pInterface);
		CIotPpAck *FindPpAck(const CString &strPkgID);
};

