//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DvmContents.h  CDvmContents

#pragma once

#include "GbSmartGenWzdGlobal.h"

class CDvmContents : public CDataGroup
{
public:
	CDvmContents();
	virtual ~CDvmContents();

    CString  m_strText;

//���غ���
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CCONTENTS;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CDvmContentsKey();     }
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

    virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
    virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);


//˽�г�Ա����
private:


//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

