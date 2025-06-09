//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndComboBox.h  CUIWndComboBox

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowBase.h"

#include "..\DataMngr\ShortDatas.h"

class CUIWndComboBox :public CComboBox, public CUIWindowBase
{
public:
	CUIWndComboBox();
	virtual ~CUIWndComboBox();


	long  m_nCurrIndex;
	long  m_nSort;
	CString  m_strSource;
	int m_nIndex;
//重载函数
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

//私有成员变量
private:
	CShortDatas *m_pDatas;

public:
	virtual BOOL UICreate(CWnd *pParent);
	virtual BOOL Destroy();


};

