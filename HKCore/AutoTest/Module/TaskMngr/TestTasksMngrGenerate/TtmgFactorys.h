//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TtmgFactorys.h  CTtmgFactorys

#pragma once

#include "TestTasksMngrGenerateGlobal.h"


#include "TtmgFactory.h"

class CTtmgFactorys : public CExBaseList
{
public:
	CTtmgFactorys();
	virtual ~CTtmgFactorys();


//���غ���
public:
	virtual UINT GetClassID() {    return TTMGCLASSID_CTTMGFACTORYS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestTasksMngrGenerateXmlRWKeys::CTtmgFactorysKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

