//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AinExpand.h  CAinExpand

#pragma once

#include "GuideBookDefine.h"



class CAinExpand : public CExBaseObject
{
public:
	CAinExpand();
	virtual ~CAinExpand();


	long  m_nAbs;
	long  m_nReal;
	long  m_nRslt;
//���غ���
public:
	virtual UINT GetClassID() {    return GBCLASSID_CAINEXPAND;   }
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::CAinExpandKey();     }
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

