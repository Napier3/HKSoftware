//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XSclFileObj.h  CXSclFileObj

#pragma once

#include "SclFileMngrGlobal.h"



class CXSclFileObj : public CExBaseObject
{
public:
	CXSclFileObj();
	virtual ~CXSclFileObj();


	CString  m_strCurrSelIED;
	long  m_nSize;
	CString  m_strSsclPath;
	CString  m_strSclPath;
	long  m_nUse;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CXSCLFILEOBJ;   }
	virtual BSTR GetXmlElementKey()  {      return CSclFileMngrXmlRWKeys::CXSclFileObjKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

