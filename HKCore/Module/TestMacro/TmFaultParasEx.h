//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TmFaultParasEx.h  CTmFaultParasEx

#pragma once

#include "TestMacroGlobal.h"

#include "../DataMngr/DataGroup.h"


class CTmFaultParasEx : public CDataGroup
{
public:
	CTmFaultParasEx();
	virtual ~CTmFaultParasEx();


//���غ���
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTMFAULTPARASEX;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTmFaultParasExKey();     }
// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
// 	virtual void InitAfterRead();
// 	virtual BOOL IsEqualOwn(CBaseObject* pObj);
//	virtual BOOL CopyOwn(CBaseObject* pDest);
 	virtual CBaseObject* Clone();
// 	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
// 	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);


//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

