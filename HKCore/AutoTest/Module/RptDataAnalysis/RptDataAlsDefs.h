//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptDataAlsDefs.h  CRptDataAlsDefs

#pragma once

#include "RptAnalysisGlobal.h"


#include "RptDataAlsDef.h"

class CRptDataAlsDefs : public CExBaseList
{
public:
	CRptDataAlsDefs();
	virtual ~CRptDataAlsDefs();


//���غ���
public:
	virtual UINT GetClassID() {    return RPTALSCLASSID_CRPTDATAALSDEFS;   }
	virtual BSTR GetXmlElementKey()  {      return CRptAnalysisXmlRWKeys::CRptDataAlsDefsKey();     }
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

//˽�г�Ա�������ʷ���
public:
};

