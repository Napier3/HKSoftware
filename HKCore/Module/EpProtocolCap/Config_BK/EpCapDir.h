//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapDir.h  CEpCapDir

#pragma once

#include "EpCapConfigGlobal.h"



class CEpCapDir : public CExBaseObject
{
public:
	CEpCapDir();
	virtual ~CEpCapDir();


	long  m_nValue;
	long  m_nIndex1;
	long  m_nIndex2;
//���غ���
public:
	virtual UINT GetClassID() {    return ECCLASSID_CEPCAPDIR;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapConfigXmlRWKeys::CEpCapDirKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

