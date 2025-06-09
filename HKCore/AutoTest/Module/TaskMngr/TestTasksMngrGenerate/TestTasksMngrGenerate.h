//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestTasksMngrGenerate.h  CTestTasksMngrGenerate

#pragma once

#include "TestTasksMngrGenerateGlobal.h"


#include "TtmgReportsMngr.h"
#include "TtmgFactorys.h"
#include "TtmgStations.h"
#include "TtmgBatchs.h"

#include "..\..\..\..\Module\Office\ExcelReadWrite.h"
#include "..\TestGlobalDefine.h"

#include "..\TestProject.h"


class CTestTasksMngrGenerate : public CExBaseList
{
private:
	CTestTasksMngrGenerate();
	virtual ~CTestTasksMngrGenerate();

	static CTestTasksMngrGenerate *g_pTestTasksMngrGenerate;
	static long g_nTestTasksMngrGenerateRef;

public:
	static CString GetGbxml1();
	static CString GetGbxml2();
	static CString GetGbxml3();
	static CTestProject* GetTestProject();
	static CDvmDataset* GetReportSNGen();
	static CDvmDataset* GetTaskReportSNGen();
	static CExcelReadWrite* GetExcelReadWrite();
	static CTestTasksMngrGenerate* GetTestTasksMngrGenerate();
	static CTestTasksMngrGenerate* Create();
	static void Release();

//重载函数
public:
	virtual UINT GetClassID() {    return TTMGCLASSID_CTESTTASKSMNGRGENERATE;   }
	virtual BSTR GetXmlElementKey()  {      return CTestTasksMngrGenerateXmlRWKeys::CTestTasksMngrGenerateKey();     }
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

//私有成员变量
private:
	CExcelReadWrite m_oExcelWrite;

public:
	CTtmgBatchs *m_pBatchs;
	CTtmgFactorys *m_pFactorys;
	CTtmgReportsMngr *m_pReportsMngr;
	CTtmgStations *m_pStations;

	CString  m_strGbxml1;
	CString  m_strGbxml2;
	CString  m_strGbxml3;

	CTestGlobalDefine m_oTestDefine;
	CDvmDataset *m_pReportSNGen;
	CDvmDataset *m_pTaskReportSNGen;
	CTestProject m_oTestProject;

//私有成员变量访问方法
public:
	void Generate();
};

