//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TtmgBatch.h  CTtmgBatch

#pragma once

#include "TestTasksMngrGenerateGlobal.h"


#include "TtmgBatchReport.h"

class CTtmgFactory;
class CTtmgStation;

typedef CArray<long, long> CArray_Long; 

class CTtmgBatch : public CExBaseList
{
public:
	CTtmgBatch();
	virtual ~CTtmgBatch();


	CString  m_strStation;
	CString  m_strFactory;
	long  m_nNum;
	long  m_nWordBeginNO;
	CString  m_strProduceNO;
	long  m_nErrors;
	CString  m_strProduceDate;
	long  m_nFlowNO;
	CString  m_strFolder;
	long  m_nCurrGenIndex;
	long  m_nHasWriteExcel;
	long  m_nHandTestNum;
	CString  m_strTestBeginTime;
//���غ���
public:
	virtual UINT GetClassID() {    return TTMGCLASSID_CTTMGBATCH;   }
	virtual BSTR GetXmlElementKey()  {      return CTestTasksMngrGenerateXmlRWKeys::CTtmgBatchKey();     }
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
	CString  m_strTimeForID;
	void GenerateSuccAndErrorRpts();
	CTtmgBatchReport* GetReportRand();

	CString  m_strCurrTestTime;
//˽�г�Ա�������ʷ���
public:
	void Generate(CThreadProgressInterface *pGenThread);

	void GenerateReport(CThreadProgressInterface *pGenThread, CTtmgBatchReport *pReport
		, CTtmgFactory *pFactory, CTtmgStation *pStation, long nRptIndex
		, CArray_Long &nArrayLong);
	
private:
	void GenerateReport_QRCode(CThreadProgressInterface *pGenThread, CTtmgBatchReport *pReport
		, CTtmgFactory *pFactory, CTtmgStation *pStation, long nRptIndex
		, CArray_Long &nArrayLong);

	void GenerateReport_Excel(CThreadProgressInterface *pGenThread
		, CTtmgFactory *pFactory, CTtmgStation *pStation);
};

