//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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


//���غ���
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

