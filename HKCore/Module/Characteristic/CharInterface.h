//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharInterface.h  CCharInterface

#pragma once

#include "CharacteristicGlobal.h"


#include "CharInterfaceVariable.h"

class CCharInterface : public CExBaseList
{
public:
	CCharInterface();
	virtual ~CCharInterface();


//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARINTERFACE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharInterfaceKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);

	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long InsertToListCtrl(CListCtrl *pListCtrl);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

