//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SysParaMap.h  CSysParaMap

#pragma once

#include "PowerTestSetMapsGlobal.h"



class CSysParaMap : public CExBaseObject
{
public:
	CSysParaMap();
	virtual ~CSysParaMap();


	CString  m_strMap;
//���غ���
public:
	virtual UINT GetClassID() {    return SETMAPMNGRCLASSID_CPARAMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CPowerTestSetMapsXmlRWKeys::CParaMapKey();     }
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

