//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecSmvChDataType.h  CIecSmvChDataType

#pragma once

#include "IecGlobalDataMngrGlobal.h"



class CIecSmvChDataType : public CDataType
{
public:
	CIecSmvChDataType();
	virtual ~CIecSmvChDataType();


//���غ���
public:
	virtual UINT GetClassID() {    return STGCLASSID_CIecSmvCHDATATYPE;   }
	virtual BSTR GetXmlElementKey()  {      return CIecGlobalDataMngrXmlRWKeys::CIecSmvChDataTypeKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

