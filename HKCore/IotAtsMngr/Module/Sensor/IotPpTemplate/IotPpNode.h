//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
	SYSTEMTIME m_tmRunBegin;	//RunNode��ʼʱ�䣬���ڼ�ⱨ���Ƿ��ʱ
//���غ���
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

//˽�г�Ա����
private:
	CIotPpAcks *m_pIotPpAcks;
	CIotPpTimers *m_pIotPpTimers;

//˽�г�Ա�������ʷ���
public:
	CIotPpAcks* GetIotPpAcks()	{	return m_pIotPpAcks;	}
	CIotPpTimers* GetIotPpTimers()	{	return m_pIotPpTimers;	}

//���Ա������ʷ���
public:
	void SetRunBegin(){GetLocalTime(&m_tmRunBegin);}
	void BeginTimer(DWORD dwCurrTick);
	void KillTimer();
	BOOL IsTimerOut(DWORD dwCurrTick,CIotPpNode **ppCurNode);

	void UpdateTimers(CDvmDataset *pAttrDataset,CExBaseList *pInterface);
		CIotPpAck *FindPpAck(const CString &strPkgID);
};

