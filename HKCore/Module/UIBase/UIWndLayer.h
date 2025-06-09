//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIWndLayer.h  CUIWndLayer

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowList.h"

#include "UIWndBitmap.h"
#include "UIWndButton.h"
#include "UIWndComboBox.h"
#include "UIWndDateTimeCtrl.h"
#include "UIWndEdit.h"
#include "UIWndStaticText.h"
#include "UIWndTime.h"
#include "UIWndFileMngr.h"
#include "UIWndRegister.h"
#include "UIWndCheckBox.h"
#include "UIWndListControl.h"
#include "UIWndListBox.h"

#define LAYERTYPE_WINDOW     0
#define LAYERTYPE_GROUP      1

class CUIWndLayer : public CUIWindowList
{
public:
	CUIWndLayer();
	virtual ~CUIWndLayer();


	long  m_nShowChildren;
	long  m_nBringToTop;
	long  m_nBorder;

//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDLAYER;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndLayerKey();     }
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


private:
	DWORD  m_dwLayerType;

//˽�г�Ա�������ʷ���
public:
	CUIWindowBase* FindWindowByID(LPCTSTR pszWindowID);
	CUIWindowBase* FindWindowByID(CString &strstrWindowID);

	virtual BOOL UICreate(CWnd *pParent);
	virtual BOOL Show(long nShow);

	BOOL IsWindowType();
	BOOL IsGroupType();
};

