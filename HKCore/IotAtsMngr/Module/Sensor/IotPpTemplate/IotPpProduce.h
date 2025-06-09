//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IotPpProduce.h  CIotPpProduce

#pragma once

#include "IOTPPGlobal.h"

#include "IotPpParse.h"

#include "IotPpInterface.h"
#include "IotPpPkgHead.h"
#include "IotPpDataList.h"

class CIotPpProduce : public CIotPpParse
{
public:
	CIotPpProduce();
	virtual ~CIotPpProduce();


//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOTPPPRODUCE;   }
	virtual BSTR GetXmlElementKey()  {      return CIOTPPXmlRWKeys::CIotPpProduceKey();     }
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
protected:
	CIotPpInterface *m_pIotPpInterface;

//˽�г�Ա�������ʷ���
public:
	CIotPpInterface* GetIotPpInterface()	{	return m_pIotPpInterface;	}

//���Ա������ʷ���
public:
};

