//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharInterfaceVariable.h  CCharInterfaceVariable

#pragma once

#include "CharacteristicGlobal.h"



class CCharInterfaceVariable : public CExBaseObject
{
public:
	CCharInterfaceVariable();
	virtual ~CCharInterfaceVariable();


	CString  m_strValue;
//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARINTERFACEVARIABLE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharInterfaceVariableKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	virtual long InsertToListCtrl(CListCtrl *pListCtrl,long lItemIndex);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

