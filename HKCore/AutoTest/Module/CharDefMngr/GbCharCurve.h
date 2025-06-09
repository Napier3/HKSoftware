//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharCurve.h  CGbCharCurve

#pragma once

#include "GbCharDefMngrGlobal.h"


#include "GbCharArc.h"
#include "GbCharLine.h"
#include "GbCharLiner.h"
#include "GbCharLines.h"
#include "GbCharPArc.h"
#include "GbCharPLine.h"
#include "GbCharPLiner.h"
#include "GbCharPLines.h"

class CGbCharCurve : public CExBaseList
{
public:
	CGbCharCurve();
	virtual ~CGbCharCurve();


//重载函数
public:
	virtual UINT GetClassID() {    return CHRCLASSID_CGBCHARCURVE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbCharDefMngrXmlRWKeys::CGbCharCurveKey();     }
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

