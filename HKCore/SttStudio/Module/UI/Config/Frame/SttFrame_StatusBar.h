//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_StatusBar.h  CSttFrame_StatusBar

#pragma once

#include "SttTestCtrlFrameCfgMngrGlobal.h"


#include "SttFrame_Panal.h"

class CSttFrame_StatusBar : public CExBaseList
{
public:
	CSttFrame_StatusBar();
	virtual ~CSttFrame_StatusBar();

	//图标的位置，包括：上(top)、下(bottom)、左(left)、右(right)
	CString  m_strIconPos;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTFRAME_STATUSBAR;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrlFrameCfgMngrXmlRWKeys::CSttFrame_StatusBarKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CSttFrame_Panal *m_pPanal;

//私有成员变量访问方法
public:
	CSttFrame_Panal* GetPanal()	{	return m_pPanal;	}
	void SetPanal(CSttFrame_Panal* pPanal)	{	m_pPanal = pPanal;	}

//属性变量访问方法
public:
};

