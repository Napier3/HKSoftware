//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttContents.h  CSttContents

#pragma once

#include "../SttCmdDefineGlobal.h"
#include "../../../../Module/DataMngr/DataGroup.h"

class CSttContents : public CDataGroup
{
public:
	CSttContents();
	virtual ~CSttContents();

    CString  m_strText;

//���غ���
public:
	virtual UINT GetClassID() {    return STTGBXMLCLASSID_CSTTCONTENTS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttContentsKey();     }
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

