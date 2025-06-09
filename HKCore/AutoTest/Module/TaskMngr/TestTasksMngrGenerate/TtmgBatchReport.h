//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//TtmgBatchReport.h  CTtmgBatchReport

#pragma once

#include "TestTasksMngrGenerateGlobal.h"
#include "TtmgReport.h"
#include "..\..\..\..\Module\DataMngr\DvmDataset.h"

#define TTMG_RPTGENSTATE_INDEX_Test                  0
#define TTMG_RPTGENSTATE_INDEX_Destructive        1
#define TTMG_RPTGENSTATE_INDEX_NonDestructive  2
#define TTMG_RPTGENSTATE_INDEX_Sum                 3

class CTtmgBatchReport : public CExBaseObject
{
public:
	CTtmgBatchReport();
	virtual ~CTtmgBatchReport();


	CString  m_strDeviceAttr;
	CString  m_strSrcRpt;
	CString  m_strDestRpt;
	CString  m_strErrorType;
	long  m_nHasGenerated;

	CDvmDataset m_oDvmDeviceAttr;
	long m_nRptIndex;
	
	//unsigned char m_chRptGenState[4];
	long               m_nRptGenStateIndex;
//���غ���
public:
	virtual UINT GetClassID() {    return TTMGCLASSID_CTTMGBATCHREPORT;   }
	virtual BSTR GetXmlElementKey()  {      return CTestTasksMngrGenerateXmlRWKeys::CTtmgBatchReportKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void Generate(CThreadProgressInterface *pGenThread);
	void FinishGenerate(CThreadProgressInterface *pGenThread);
	void InitReport(CTtmgReport *pRpt, CTtmgReport *pRptDestructive, CTtmgReport *pRptNonDestructive, CTtmgReport *pReportSum);

	void AddDeviceAttr(const CString &strName, const CString &strValue);
	void InitDeviceAttr();
	void GetDeviceAttr(CString &strDeviceAttr);
	void GetDeviceAttrXML(CString &strXML);
	void InitDestRpt();

public:
	CTtmgReport *m_pTtmgReportRef;
	CTtmgReport *m_pTtmgReportRefDestructive;
	CTtmgReport *m_pTtmgReportRefNonDestructive;
	CTtmgReport *m_pTtmgReportRefSum;

	CString m_strFolderName;
	CString m_strWordBeginNO;
	CString m_strDestPath;

protected:
	void Generate_CreateDir(CThreadProgressInterface *pGenThread);
	void Generate_Test(CThreadProgressInterface *pGenThread);
	void Generate_Destructive(CThreadProgressInterface *pGenThread);
	void Generate_NonDestructive(CThreadProgressInterface *pGenThread);
	void Generate_Sum(CThreadProgressInterface *pGenThread);
	void Generate_XXX(CThreadProgressInterface *pGenThread, CTtmgReport *pTtmgReport, const CString &strGbxml);

};

