//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TtmgBatch.cpp  CTtmgBatch


#include "stdafx.h"
#include "TtmgBatch.h"
#include "TestTasksMngrGenerate.h"

CTtmgBatch::CTtmgBatch()
{
	//初始化属性
	m_nNum = 0;
	m_nWordBeginNO = 0;
	m_nErrors = 0;
	m_nFlowNO = 0;
	m_nCurrGenIndex = 0;
	m_nHasWriteExcel = 0;
	m_nHandTestNum = 0;

	//初始化成员变量
}

CTtmgBatch::~CTtmgBatch()
{
}

long CTtmgBatch::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strStationKey, oNode, m_strStation);
	xml_GetAttibuteValue(pXmlKeys->m_strFactoryKey, oNode, m_strFactory);
	xml_GetAttibuteValue(pXmlKeys->m_strNumKey, oNode, m_nNum);
	xml_GetAttibuteValue(pXmlKeys->m_strWordBeginNOKey, oNode, m_nWordBeginNO);
	xml_GetAttibuteValue(pXmlKeys->m_strProduceNOKey, oNode, m_strProduceNO);
	xml_GetAttibuteValue(pXmlKeys->m_strErrorsKey, oNode, m_nErrors);
	xml_GetAttibuteValue(pXmlKeys->m_strProduceDateKey, oNode, m_strProduceDate);
	xml_GetAttibuteValue(pXmlKeys->m_strFlowNOKey, oNode, m_nFlowNO);
	xml_GetAttibuteValue(pXmlKeys->m_strFolderKey, oNode, m_strFolder);
	xml_GetAttibuteValue(pXmlKeys->m_strCurrGenIndexKey, oNode, m_nCurrGenIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strHasWriteExcelKey, oNode, m_nHasWriteExcel);
	xml_GetAttibuteValue(pXmlKeys->m_strHandTestNumKey, oNode, m_nHandTestNum);
	xml_GetAttibuteValue(pXmlKeys->m_strTestBeginTimeKey, oNode, m_strTestBeginTime);
	return 0;
}

long CTtmgBatch::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strStationKey, oElement, m_strStation);
	xml_SetAttributeValue(pXmlKeys->m_strFactoryKey, oElement, m_strFactory);
	xml_SetAttributeValue(pXmlKeys->m_strNumKey, oElement, m_nNum);
	xml_SetAttributeValue(pXmlKeys->m_strWordBeginNOKey, oElement, m_nWordBeginNO);
	xml_SetAttributeValue(pXmlKeys->m_strProduceNOKey, oElement, m_strProduceNO);
	xml_SetAttributeValue(pXmlKeys->m_strErrorsKey, oElement, m_nErrors);
	xml_SetAttributeValue(pXmlKeys->m_strProduceDateKey, oElement, m_strProduceDate);
	xml_SetAttributeValue(pXmlKeys->m_strFlowNOKey, oElement, m_nFlowNO);
	xml_SetAttributeValue(pXmlKeys->m_strFolderKey, oElement, m_strFolder);
	xml_SetAttributeValue(pXmlKeys->m_strCurrGenIndexKey, oElement, m_nCurrGenIndex);
	xml_SetAttributeValue(pXmlKeys->m_strHasWriteExcelKey, oElement, m_nHasWriteExcel);
	xml_SetAttributeValue(pXmlKeys->m_strHandTestNumKey, oElement, m_nHandTestNum);
	xml_SetAttributeValue(pXmlKeys->m_strTestBeginTimeKey, oElement, m_strTestBeginTime);
	return 0;
}

long CTtmgBatch::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strStation);
		BinarySerializeCalLen(oBinaryBuffer, m_strFactory);
		BinarySerializeCalLen(oBinaryBuffer, m_nNum);
		BinarySerializeCalLen(oBinaryBuffer, m_nWordBeginNO);
		BinarySerializeCalLen(oBinaryBuffer, m_strProduceNO);
		BinarySerializeCalLen(oBinaryBuffer, m_nErrors);
		BinarySerializeCalLen(oBinaryBuffer, m_strProduceDate);
		BinarySerializeCalLen(oBinaryBuffer, m_nFlowNO);
		BinarySerializeCalLen(oBinaryBuffer, m_strFolder);
		BinarySerializeCalLen(oBinaryBuffer, m_nCurrGenIndex);
		BinarySerializeCalLen(oBinaryBuffer, m_nHasWriteExcel);
		BinarySerializeCalLen(oBinaryBuffer, m_nHandTestNum);
		BinarySerializeCalLen(oBinaryBuffer, m_strTestBeginTime);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strStation);
		BinarySerializeRead(oBinaryBuffer, m_strFactory);
		BinarySerializeRead(oBinaryBuffer, m_nNum);
		BinarySerializeRead(oBinaryBuffer, m_nWordBeginNO);
		BinarySerializeRead(oBinaryBuffer, m_strProduceNO);
		BinarySerializeRead(oBinaryBuffer, m_nErrors);
		BinarySerializeRead(oBinaryBuffer, m_strProduceDate);
		BinarySerializeRead(oBinaryBuffer, m_nFlowNO);
		BinarySerializeRead(oBinaryBuffer, m_strFolder);
		BinarySerializeRead(oBinaryBuffer, m_nCurrGenIndex);
		BinarySerializeRead(oBinaryBuffer, m_nHasWriteExcel);
		BinarySerializeRead(oBinaryBuffer, m_nHandTestNum);
		BinarySerializeRead(oBinaryBuffer, m_strTestBeginTime);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strStation);
		BinarySerializeWrite(oBinaryBuffer, m_strFactory);
		BinarySerializeWrite(oBinaryBuffer, m_nNum);
		BinarySerializeWrite(oBinaryBuffer, m_nWordBeginNO);
		BinarySerializeWrite(oBinaryBuffer, m_strProduceNO);
		BinarySerializeWrite(oBinaryBuffer, m_nErrors);
		BinarySerializeWrite(oBinaryBuffer, m_strProduceDate);
		BinarySerializeWrite(oBinaryBuffer, m_nFlowNO);
		BinarySerializeWrite(oBinaryBuffer, m_strFolder);
		BinarySerializeWrite(oBinaryBuffer, m_nCurrGenIndex);
		BinarySerializeWrite(oBinaryBuffer, m_nHasWriteExcel);
	}
	return 0;
}

void CTtmgBatch::InitAfterRead()
{
	if (m_nNum == m_nCount)
	{
		return;
	}

	long nIndex = 0;

	for (nIndex=0; nIndex<m_nNum; nIndex++)
	{
		CTtmgBatchReport *pReport = new CTtmgBatchReport();
		AddNewChild(pReport);
	}
}

BOOL CTtmgBatch::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTtmgBatch *p = (CTtmgBatch*)pObj;

	if(m_strStation != p->m_strStation)
	{
		return FALSE;
	}

	if(m_strFactory != p->m_strFactory)
	{
		return FALSE;
	}

	if(m_nNum != p->m_nNum)
	{
		return FALSE;
	}

	if(m_nWordBeginNO != p->m_nWordBeginNO)
	{
		return FALSE;
	}

	if(m_strProduceNO != p->m_strProduceNO)
	{
		return FALSE;
	}

	if(m_nErrors != p->m_nErrors)
	{
		return FALSE;
	}

	if(m_strProduceDate != p->m_strProduceDate)
	{
		return FALSE;
	}

	if(m_nFlowNO != p->m_nFlowNO)
	{
		return FALSE;
	}

	if(m_strFolder != p->m_strFolder)
	{
		return FALSE;
	}

	if(m_nCurrGenIndex != p->m_nCurrGenIndex)
	{
		return FALSE;
	}

	if(m_nHasWriteExcel != p->m_nHasWriteExcel)
	{
		return FALSE;
	}

	if(m_nHandTestNum != p->m_nHandTestNum)
	{
		return FALSE;
	}

	if(m_strTestBeginTime != p->m_strTestBeginTime)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTtmgBatch::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CTtmgBatch *p = (CTtmgBatch*)pDest;

	p->m_strStation = m_strStation;
	p->m_strFactory = m_strFactory;
	p->m_nNum = m_nNum;
	p->m_nWordBeginNO = m_nWordBeginNO;
	p->m_strProduceNO = m_strProduceNO;
	p->m_nErrors = m_nErrors;
	p->m_strProduceDate = m_strProduceDate;
	p->m_nFlowNO = m_nFlowNO;
	p->m_strFolder = m_strFolder;
	p->m_nCurrGenIndex = m_nCurrGenIndex;
	p->m_nHasWriteExcel = m_nHasWriteExcel;
	p->m_nHandTestNum = m_nHandTestNum;
	p->m_strTestBeginTime = m_strTestBeginTime;
	return TRUE;
}

CBaseObject* CTtmgBatch::Clone()
{
	CTtmgBatch *p = new CTtmgBatch();
	Copy(p);
	return p;
}

BOOL CTtmgBatch::CanPaste(UINT nClassID)
{
	if (nClassID == TTMGCLASSID_CTTMGBATCHREPORT)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTtmgBatch::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestTasksMngrGenerateXmlRWKeys *pXmlKeys = (CTestTasksMngrGenerateXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTtmgBatchReportKey)
	{
		pNew = new CTtmgBatchReport();
	}

	return pNew;
}

CExBaseObject* CTtmgBatch::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TTMGCLASSID_CTTMGBATCHREPORT)
	{
		pNew = new CTtmgBatchReport();
	}

	return pNew;
}


long TTMG_GetRandValueLong(CArray_Long &nArray, long nBeginVal, long nMaxValue)
{
	long nRet = 0;
	nRet = rand() % nMaxValue;
	long nCount = nArray.GetCount();
	long nIndex = nRet % nCount;

	nRet = nArray.GetAt(nIndex);
	nArray.RemoveAt(nIndex);

	return nRet;
}

void CTtmgBatch::Generate(CThreadProgressInterface *pGenThread)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("++++++++++++报告生成初始化"));
	CTtmgBatchReport *pReport = NULL;
	POS pos = NULL;

	//第一步：获取Factory、Station
	CTtmgFactory *pFactory = TTMG_FindFactory(m_strFactory);
	CTtmgStation *pStation = TTMG_FindStation(m_strStation);

	//第二步：根据报告总数，创建Report对象
	long nIndex = 0;

// 	for (nIndex=0; nIndex<m_nNum; nIndex++)
// 	{
// 		CTtmgBatchReport *pReport = new CTtmgBatchReport();
// 		AddNewChild(pReport);
// 	}

	//第三步：指定报告文件，合格、不合格，拷贝报告文件
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T(">>指定报告文件，合格、不合格"));
	GenerateSuccAndErrorRpts();

	//第四步：遍历每个报告，生成二维码
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T(">>遍历每个报告，生成二维码"));

	pos = GetHeadPosition();
	COleDateTime oTime;
	oTime.ParseDateTime(m_strProduceDate);
	SYSTEMTIME tmSys;
	oTime.GetAsSystemTime(tmSys);
	m_strTimeForID.Format(_T("%d%02d%02d"), tmSys.wYear, tmSys.wMonth, tmSys.wDay);
	
	CArray_Long nArrayLong;
	long nMax = 1500;
	nArrayLong.SetSize(1500);
	
	for (nIndex=0; nIndex<nMax; nIndex++)
	{
		nArrayLong.SetAt(nIndex, m_nFlowNO + nIndex);
	}

	nIndex = 0;
	m_strCurrTestTime = m_strTestBeginTime;

	oTime.ParseDateTime(m_strTestBeginTime);
	oTime.GetAsSystemTime(tmSys);
	CTime tmTest(tmSys);
	CTimeSpan tmSpan(1, 0, 0, 0);
	long nTmCount = 0;

	while (pos != NULL)
	{
		pReport = (CTtmgBatchReport *)GetNext(pos);
		GenerateReport(pGenThread, pReport, pFactory, pStation, nIndex, nArrayLong);
		nIndex++;
		nTmCount++;

		if (nTmCount == 200)
		{
			nTmCount = 0;
			tmTest += tmSpan;
			tmTest.GetAsSystemTime(tmSys);
			m_strCurrTestTime.Format(_T("%d年%d月%d日"), tmSys.wYear, tmSys.wMonth, tmSys.wDay);
		}
	}

	//第五步：导出Excel文件
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T(">>导出Excel文件"));
	GenerateReport_Excel(pGenThread, pFactory, pStation);
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("++++++++++++报告生成初始化完成"));
}

CTtmgBatchReport* CTtmgBatch::GetReportRand()
{
	long nIndex = 0;
	nIndex = rand() % m_nCount;
	CTtmgBatchReport *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (TRUE)
	{
		p = (CTtmgBatchReport *)GetNext(pos);

		if (p->m_strSrcRpt.GetLength() == 0)
		{
			if (nIndex == 0)
			{
				pFind = p;
				break;
			}

			nIndex--;
		}

		if (pos == NULL)
		{
			pos = GetHeadPosition();
		}
	}

	return pFind;
}

void CTtmgBatch::GenerateSuccAndErrorRpts()
{
	long nIndex = 0;
	CTestTasksMngrGenerate *pGenerate = CTestTasksMngrGenerate::GetTestTasksMngrGenerate();
	CTtmgReports *pRptsError = pGenerate->m_pReportsMngr->m_pReportsError;
	CTtmgReports *pRptsSucc = pGenerate->m_pReportsMngr->m_pReportsSucc;
	CTtmgReports *pRptsDestructive = pGenerate->m_pReportsMngr->m_pReportsDestructive;
	CTtmgReports *pRptsNonDestructive = pGenerate->m_pReportsMngr->m_pReportsNonDestructive;
	CTtmgReport  *pReportSumAllSuc = pGenerate->m_pReportsMngr->m_pReportSumAllSuc;
	CTtmgReport  *pReportSumError = pGenerate->m_pReportsMngr->m_pReportSumError;
	CTtmgReport  *pReportSumSucc = pGenerate->m_pReportsMngr->m_pReportSumSucc;

	CTtmgBatchReport *pReport = NULL;
	CTtmgReport *pSrcRpt = NULL;
	CTtmgReport *pSrcRpt1 = NULL;
	CTtmgReport *pSrcRpt2 = NULL;

	//处理不合格报告
	for (nIndex=0; nIndex<m_nErrors; nIndex++)
	{
		pReport = GetReportRand();
		pSrcRpt = pRptsError->GetReport();
		pReport->InitReport(pSrcRpt, NULL, NULL, pReportSumError);
	}

	//处理破坏性和非破坏性报告
	for (nIndex=0; nIndex<m_nHandTestNum; nIndex++)
	{
		pReport = GetReportRand();
		pSrcRpt = pRptsSucc->GetReport();
		pSrcRpt1 = pRptsDestructive->GetReport();
		pSrcRpt2 = pRptsNonDestructive->GetReport();
		pReport->InitReport(pSrcRpt, pSrcRpt1, pSrcRpt2, pReportSumAllSuc);
	}

	//合格报告
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pReport = (CTtmgBatchReport *)GetNext(pos);

		if (pReport->m_strSrcRpt.GetLength() == 0)
		{
			pSrcRpt = pRptsSucc->GetReport();
			pReport->InitReport(pSrcRpt, NULL, NULL, pReportSumSucc);
		}
	}
}

void CTtmgBatch::GenerateReport(CThreadProgressInterface *pGenThread, CTtmgBatchReport *pReport
					, CTtmgFactory *pFactory, CTtmgStation *pStation, long nRptIndex
					, CArray_Long &nArrayLong)
{
	GenerateReport_QRCode(pGenThread, pReport, pFactory, pStation, nRptIndex, nArrayLong);
}

void CTtmgBatch::GenerateReport_QRCode(CThreadProgressInterface *pGenThread, CTtmgBatchReport *pReport
								, CTtmgFactory *pFactory, CTtmgStation *pStation, long nRptIndex
								, CArray_Long &nArrayLong)
{
	CString strText;

	//类型+厂商
	//pReport->m_strDeviceAttr.AppendFormat(_T("类型：JYL，厂商：%s，"), pFactory->m_strName);
	pReport->AddDeviceAttr(_T("类型"), _T("JYL"));
	pReport->AddDeviceAttr(_T("厂商"), pFactory->m_strName);

	//型号
	//pReport->m_strDeviceAttr.AppendFormat(_T("型号：%s，"), pFactory->m_strID);
	pReport->AddDeviceAttr(_T("型号"), pFactory->m_strID);

	//ID
// 	pReport->m_strDeviceAttr.AppendFormat(_T("ID：JYL%s%s%s%s%04d，")
// 		, pFactory->m_strCode, pFactory->m_strOwnDef
// 		, m_strProduceNO, m_strTimeForID, m_nFlowNO+nRptIndex);
	long nRand = TTMG_GetRandValueLong(nArrayLong, m_nFlowNO, m_nNum);
	strText.Format(_T("JYL%s%s%s%s%04d")
		, pFactory->m_strCode, pFactory->m_strOwnDef
		, m_strProduceNO, m_strTimeForID, nRand);//m_nFlowNO+nRptIndex);
	pReport->AddDeviceAttr(_T("ID"), strText);

	//硬件版本
	//pReport->m_strDeviceAttr.AppendFormat(_T("硬件版本：%s，"), pFactory->m_strHdVer);
	pReport->AddDeviceAttr(_T("硬件版本"), pFactory->m_strHdVer);

	//生产日期
	//pReport->m_strDeviceAttr.AppendFormat(_T("生产日期：%s"), m_strProduceDate);
	pReport->AddDeviceAttr(_T("生产日期"), m_strProduceDate);

	//编号
	//pReport->m_strDeviceAttr.AppendFormat(_T("编号：%s"), m_strProduceDate);
	pReport->m_strWordBeginNO.Format(_T("YD20173963-%d"), nRptIndex+m_nWordBeginNO);
	pReport->AddDeviceAttr(_T("编号"), pReport->m_strWordBeginNO);

	pReport->AddDeviceAttr(_T("TestBeginTime"), m_strCurrTestTime);
	pReport->AddDeviceAttr(_T("TestEndTime"), m_strCurrTestTime);
	pReport->AddDeviceAttr(_T("硬件版本号"), pFactory->m_strHdVer);

	//pReport->InitDeviceAttr();
	pReport->InitDestRpt();
}

void CTtmgBatch::GenerateReport_Excel(CThreadProgressInterface *pGenThread
						  , CTtmgFactory *pFactory, CTtmgStation *pStation)
{
	CString strFile, strPath;
	CExBaseList *pList = (CExBaseList*)GetParent();
	long nIndex = pList->FindIndex(this) + 1;
	
	m_strName.Format(_T("%d-%s-%sx%d套-%s")
		, nIndex, pStation->m_strName
		, pFactory->m_strName, m_nNum, m_strProduceDate);

	strPath = TTMG_GetRptGenRootPath() + m_strName;
	m_strFolder.Format(_T("%s\\"), strPath);
	CreateAllDirectories(strPath);
	strFile.Format(_T("%s\\%s.xlsx"), strPath, m_strName);

	CString strMsg;
	strMsg.Format(_T("导出Excel文件：%s.xlsx"), m_strName);
	pGenThread->ShowMsg(strMsg);

	POS pos = GetHeadPosition();
	CTtmgBatchReport *pReport = NULL;
	CExcelReadWrite *pExcelWrite = CTestTasksMngrGenerate::GetExcelReadWrite();
	pExcelWrite->InitExcel();
	BOOL bTrue = TRUE;

	pExcelWrite->ShowInExcel(FALSE);
	pExcelWrite->OpenExcelFile(_T(""));

	try
	{
		pExcelWrite->LoadSheet(1, TRUE);
	}
	catch (...)
	{	
	}

	long nRowIndex = 1;
	CString strText;

	pExcelWrite->SetColWidth(1, 160);
	pExcelWrite->SetColWidth(2, 12);
	pExcelWrite->SetColWidth(3, 30);
	pExcelWrite->SetColWidth(3, 50);

	while (pos != NULL)
	{
		pReport = (CTtmgBatchReport *)GetNext(pos);

		try
		{
			pReport->GetDeviceAttr(strText);
			pExcelWrite->SetCellString(nRowIndex, 1, strText);
			pExcelWrite->SetCellString(nRowIndex, 2, _T("测试完成"));
			pExcelWrite->SetCellString(nRowIndex, 3, pReport->m_strErrorType);

			if (pReport->m_pTtmgReportRefDestructive != NULL)
			{
				pExcelWrite->SetCellString(nRowIndex, 4, _T("破坏和非破坏测试合格"));
			}
		}
		catch (...)
		{	
		}
		nRowIndex++;
	}


	try
	{
		pExcelWrite->SaveasXSLFile(strFile);
		pExcelWrite->CloseExcelFile(FALSE);
	}
	catch (...)
	{	
	}
}

