#pragma once

#include "../SttCmdDefineGlobal.h"
#include "../../../../Module/DataMngr/DvmValues.h"
#include "../../../../Module/DataMngr/DvmDataset.h"
#include "../../../../Module/DataMngr/DataGroup.h"

class CSttReport : public CExBaseList
{
public:
	CSttReport();
	virtual ~CSttReport();

	CString m_strBeginTime;
	CString m_strEndTime;
	//����
public:
	CDvmValues *m_pValues;//20230103 zhouhj ��CValues��ΪCDvmValues
	CDvmDataset *m_pRptDvmDataset; 

	//��д���෽��
public:
	virtual UINT GetClassID()		{    return STTCMDCLASSID_REPORT;   }
	virtual BSTR GetXmlElementKey(){return CSttCmdDefineXmlRWKeys::g_pXmlKeys->m_strCSttReportKey;}

	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

public:
    void InitValues(CValues *pSrc);
    void InitRptDvmDataset(CDvmDataset *pSrc);
	void InitReport(CDataGroup *pDataGroup);
	CDvmValue* FindValueByID(const CString &strID);

	//�����У����Ӽ����̶��Ľ��ֵ�����ڰ�����жϵļ���ֵ
	BOOL AddRptValues_ErrorCal(); 
};
