//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RemoteDevs.h  CRemoteDevs

#pragma once

#include "61850ClientCfgMngrGlobal.h"


#include "RemoteDev.h"

class CRemoteDevs : public CExBaseList
{
public:
	CRemoteDevs();
	virtual ~CRemoteDevs();


	long  m_nIntgPd;
	long  m_nOptFlds_BR;
	long  m_nOptFlds_RP;
	long  m_nTrgOps_UI;
	long  m_nUseEntryidUpdate;
	long m_nWriteCtrlType;//���������ֱ��ģʽ
	long m_nCtrlTest;//����test
	long m_nCtrlCheck;//λ0:synchrocheck   λ1:Interlock-check
	long m_nHasTimeAct;//
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CREMOTEDEVS;   }
	virtual BSTR GetXmlElementKey()  {      return C61850ClientCfgMngrXmlRWKeys::CRemoteDevsKey();     }
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

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
#ifdef USE_61850CLient_STRCUT
	ACSI_NODE* FindAcsiNodeByID(const CString &strDeviceID);
	ACSI_NODE* FindAcsiNode_UnConnect();
#endif
};

