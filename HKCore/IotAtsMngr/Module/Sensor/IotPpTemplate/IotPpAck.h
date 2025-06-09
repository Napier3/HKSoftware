//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IotPpAck.h  CIotPpAck

#pragma once

#include "IOTPPGlobal.h"


#include "IotPpJumps.h"
class CDvmDataset;

class CIotPpAck : public CExBaseList
{
public:
	CIotPpAck();
	virtual ~CIotPpAck();


	CString  m_strPkg_Id;
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOTPPACK;   }
	virtual BSTR GetXmlElementKey()  {      return CIOTPPXmlRWKeys::CIotPpAckKey();     }
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
	CIotPpJumps *m_pIotPpJumps;

//˽�г�Ա�������ʷ���
public:
	CIotPpJumps* GetIotPpJumps()	{	return m_pIotPpJumps;	}

//���Ա������ʷ���
public:
	void UpdateTimers(CDvmDataset *pAttrDataset,CExBaseList *pInterface);
};

