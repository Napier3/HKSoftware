//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIWndComboBox.h  CUIWndComboBox

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowBase.h"

#include "UIBaseItems.h"

class CUIWndListBox :public CListBox, public CUIWindowBase
{
public:
	CUIWndListBox();
	virtual ~CUIWndListBox();


//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDCOMBOBOX;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndComboBoxKey();     }
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
	CUIBaseItems *m_pItems;

public:
	virtual BOOL UICreate(CWnd *pParent);
	virtual BOOL Destroy();
	void InsertDatas();


};

