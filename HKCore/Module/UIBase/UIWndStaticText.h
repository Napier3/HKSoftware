//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIWndStaticText.h  CUIWndStaticText

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowBase.h"


class CUIWndStaticText : public CStatic, public CUIWindowBase
{
public:
	CUIWndStaticText();
	virtual ~CUIWndStaticText();


//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDSTATICTEXT;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndStaticTextKey();     }
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

public:
	virtual BOOL UICreate(CWnd *pParent);
	virtual BOOL Destroy();
	void SetWndText(CString strWndText);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

protected:
	//{{AFX_MSG(CUIWndStaticText)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

};

