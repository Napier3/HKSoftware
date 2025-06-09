//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharacterArea.h  CCharacterArea

#pragma once

#include "CharacteristicGlobal.h"


#include "CharElementLens.h"
#include "CharElementArc.h"
#include "CharElementArcd.h"
#include "CharElementArcp.h"
#include "CharElementLine.h"
#include "CharElementLined.h"
#include "CharElementLinep.h"
#include "CharElementMho.h"

class CCharacterArea : public CExBaseList
{
public:
	CCharacterArea();
	virtual ~CCharacterArea();


//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARACTERAREA;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharacterAreaKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual long InitListCtrlColumns(CListCtrl *pListCtrl);
	virtual long InsertToListCtrl(CListCtrl *pListCtrl);
	
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

