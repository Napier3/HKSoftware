//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIBaseFileTypePostfix.h  CUIBaseFileTypePostfix

#pragma once

#include "UIBaseGlobal.h"

#include "..\XfileMngrBase\XFileTypes.h"


class CUIBaseFileTypePostfix : public CExBaseObject
{
public:
	CUIBaseFileTypePostfix();
	virtual ~CUIBaseFileTypePostfix();


//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIBASEFILETYPEPOSTFIX;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIBaseFileTypePostfixKey();     }
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

