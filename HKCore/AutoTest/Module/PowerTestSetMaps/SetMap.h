//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SetMap.h  CSetMap

#pragma once

#include "PowerTestSetMapsGlobal.h"



class CSetMap : public CExBaseObject
{
public:
	CSetMap();
	virtual ~CSetMap();


	CString  m_strMap;
//���غ���
public:
	virtual UINT GetClassID() {    return SETMAPMNGRCLASSID_CSETMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CPowerTestSetMapsXmlRWKeys::CSetMapKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

