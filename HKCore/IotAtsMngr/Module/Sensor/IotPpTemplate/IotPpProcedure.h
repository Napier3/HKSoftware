//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IotPpProcedure.h  CIotPpProcedure

#pragma once

#include "IOTPPGlobal.h"


#include "IotPpInterface.h"
#include "IotPpNode.h"

class CIotPpProcedure : public CExBaseList
{
public:
	CIotPpProcedure();
	virtual ~CIotPpProcedure();


//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOTPPPROCEDURE;   }
	virtual BSTR GetXmlElementKey()  {      return CIOTPPXmlRWKeys::CIotPpProcedureKey();     }
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
	CIotPpInterface *m_pIotPpInterface;
	CIotPpNode *m_pIotPpNode;

//˽�г�Ա�������ʷ���
public:
	CIotPpInterface* GetIotPpInterface()	{	return m_pIotPpInterface;	}
	CIotPpNode* GetIotPpNode()	{	return m_pIotPpNode;	}

//���Ա������ʷ���
public:
	CIotPpNode* GetRootNode();
	void UpdateNodeTimers(CDvmDataset *pAttrDataset);
};

