//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttFrame_GbTree.h  CSttFrame_GbTree

#pragma once

#include "SttTestCtrlFrameCfgMngrGlobal.h"


#include "SttFrame_Size.h"
#include "SttFrame_Font.h"

class CSttFrame_GbTree : public CExBaseList
{
public:
	CSttFrame_GbTree();
	virtual ~CSttFrame_GbTree();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTFRAME_GBTREE;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestCtrlFrameCfgMngrXmlRWKeys::CSttFrame_GbTreeKey();     }
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
	CSttFrame_Font *m_pFont;
	CSttFrame_Size *m_pSize;

//私有成员变量访问方法
public:
	CSttFrame_Font* GetFont()	{	return m_pFont;	}
	void SetFont(CSttFrame_Font* pFont)	{	m_pFont = pFont;	}
	CSttFrame_Size* GetSize()	{	return m_pSize;	}
	void SetSize(CSttFrame_Size* pSize)	{	m_pSize = pSize;	}

//属性变量访问方法
public:
};

