//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndDateTimeCtrl.h  CUIWndDateTimeCtrl

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowBase.h"


class CUIWndDateTimeCtrl : public CUIWindowBase
{
public:
	CUIWndDateTimeCtrl();
	virtual ~CUIWndDateTimeCtrl();


	CString  m_strFormart;
	long  m_nUseCurTime;
	long  m_nYear;
	long  m_nDay;
	long  m_nHour;
	long  m_nMinute;
	long  m_nSecond;
//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDDATETIMECTRL;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndDateTimeCtrlKey();     }
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

//私有成员变量访问方法
public:
};

