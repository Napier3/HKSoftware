//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TmResultEx.h  CTmResultEx

#pragma once

#include "TestMacroGlobal.h"

#include "../DataMngr/DataGroup.h"


class CTmResultParasEx : public CDataGroup
{
public:
	CTmResultParasEx();
	virtual ~CTmResultParasEx();


//���غ���
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTMRESULTPARASEX;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTmResultParasExKey();     }
// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
// 	virtual void InitAfterRead();
// 	virtual BOOL IsEqualOwn(CBaseObject* pObj);
// 	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
// 	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
// 	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

