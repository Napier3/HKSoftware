//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptDataAlsDefsMngr.h  CRptDataAlsDefsMngr

#pragma once

#include "RptAnalysisGlobal.h"


#include "RptDataAlsDefs.h"

class CRptDataAlsDefsMngr : public CExBaseList
{
public:
	CRptDataAlsDefsMngr();
	virtual ~CRptDataAlsDefsMngr();
	void FreeRptDataAlsDefsMngr();

//���غ���
public:
	virtual UINT GetClassID() {    return RPTALSCLASSID_CRPTDATAALSDEFSMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CRptAnalysisXmlRWKeys::CRptDataAlsDefsMngrKey();     }
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
	CExBaseList m_listAllItem;
	long GetAllDataAlsDef(CExBaseList &listDataDef);

//˽�г�Ա�������ʷ���
public:
	CExBaseList* GetAllDataAlsDef()		{	return &m_listAllItem;	}
};

