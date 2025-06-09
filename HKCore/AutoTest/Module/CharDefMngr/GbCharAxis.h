//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharAxis.h  CGbCharAxis

#pragma once

#include "GbCharDefMngrGlobal.h"


#include "GbCharLineDraw.h"
#include "GbCharPointDraw.h"

class CGbCharAxis : public CExBaseList
{
public:
	CGbCharAxis();
	virtual ~CGbCharAxis();


	CString  m_strAxis;
	CString  m_strXName;
	CString  m_strYName;
	CString  m_strXMin;
	CString  m_strYMin;
	CString  m_strXMax;
	CString  m_strYMax;
//重载函数
public:
	virtual UINT GetClassID() {    return CHRCLASSID_CGBCHARAXIS;   }
	virtual BSTR GetXmlElementKey()  {      return CGbCharDefMngrXmlRWKeys::CGbCharAxisKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

