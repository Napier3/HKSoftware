//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DinWzdFromSclGinCh.h  CDinWzdFromSclGinCh

#pragma once

#include "GuideBookWizardDefine.h"



class CDinWzdFromSclGinCh : public CExBaseObject
{
public:
	CDinWzdFromSclGinCh();
	virtual ~CDinWzdFromSclGinCh();


	CString  m_strAppID;
	CString  m_strGsChIndex;
	CString  m_strDataType;
//���غ���
public:
	virtual UINT GetClassID() {    return GBWZDCLASSID_CDINWZDFROMSCLGINCH;   }
	virtual BSTR GetXmlElementKey()  {      return CGbWzdToolXmlRWKeys::CDinWzdFromSclGinChKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

