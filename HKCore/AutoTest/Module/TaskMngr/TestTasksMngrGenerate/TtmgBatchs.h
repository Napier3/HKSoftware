//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TtmgBatchs.h  CTtmgBatchs

#pragma once

#include "TestTasksMngrGenerateGlobal.h"


#include "TtmgBatch.h"

class CTtmgBatchs : public CExBaseList
{
public:
	CTtmgBatchs();
	virtual ~CTtmgBatchs();

	long m_nCurrBatchGenIndex;
	CTtmgBatch *m_pCurrBatch;

	long m_nCurrBatchRptGenIndex;
	CTtmgBatchReport *m_pCurrBatchReport;

	long m_nTotalReports;
//���غ���
public:
	virtual UINT GetClassID() {    return TTMGCLASSID_CTTMGBATCHS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestTasksMngrGenerateXmlRWKeys::CTtmgBatchsKey();     }
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
	void Generate(CThreadProgressInterface *pGenThread);
	CTtmgBatch* GetFirstBatch();
	CTtmgBatch* GetNextBatch();
	CTtmgBatch* GetCurrBatch()	{	return m_pCurrBatch;	}
	long GetCurrBatchIndex()	{	return m_nCurrBatchGenIndex;	}

	CTtmgBatchReport* GetFirstBatchReport();
	CTtmgBatchReport* GetNextBatchReport();
	CTtmgBatchReport* GetCurrBatchReport()	{	return m_pCurrBatchReport;	}
	long GetCurrBatchRptIndex()	{	return m_nCurrBatchRptGenIndex;	}

};

