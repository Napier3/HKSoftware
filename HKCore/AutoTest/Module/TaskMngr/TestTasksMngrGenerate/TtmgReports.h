//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TtmgReports.h  CTtmgReports

#pragma once

#include "TestTasksMngrGenerateGlobal.h"


#include "TtmgReport.h"
#include "..\..\..\..\Module\XfileMngrBase\XFileMngr.h"

class CTtmgReports : public CExBaseList
{
public:
	CTtmgReports();
	virtual ~CTtmgReports();


	CString  m_strPath;
	CXFileMngr *m_pXFileMngr;

//���غ���
public:
	virtual UINT GetClassID() {    return TTMGCLASSID_CTTMGREPORTS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestTasksMngrGenerateXmlRWKeys::CTtmgReportsKey();     }
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
	void InitAllReports();
	CTtmgReport* GetReport();

	CTtmgReport* FindReportByID(const CString &strID);

private:
	void InitAllReports(CXFolder *pXFolder);
};

