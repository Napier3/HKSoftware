//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIBaseAxises.h  CUIBaseAxises

#pragma once

#include "UIBaseGlobal.h"


#include "UIBaseAxis.h"

class CUIBaseAxises : public CExBaseList
{
public:
	CUIBaseAxises();
	virtual ~CUIBaseAxises();


	COLORREF  m_crBkColor;
	COLORREF  m_crGridColor;
	COLORREF  m_crCenterColor;
	COLORREF  m_crAxisColor;
	COLORREF  m_crFrameColor;
	long  m_nLockHorVerScale;
//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIBASEAXISES;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIBaseAxisesKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

