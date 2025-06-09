#include "StdAfx.h"
#include "CpusDvmDeviceTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCpusDvmDeviceTool::CCpusDvmDeviceTool(void)
{
	
}

CCpusDvmDeviceTool::~CCpusDvmDeviceTool(void)
{
	
}

void CCpusDvmDeviceTool::Cpus_to_DvmDevice(CCpus *pSrc, CDvmDevice *pDest)
{
	pDest->m_strID = pSrc->m_strID;
	pDest->m_strName = pSrc->m_strName;

	POS pos = pSrc->GetHeadPosition();
	CCpu *p = NULL;
	CDvmLogicDevice *pNew = NULL;

	while (pos != NULL)
	{
		p = (CCpu *)pSrc->GetNext(pos);
		pNew = new CDvmLogicDevice();
		pDest->AddNewChild(pNew);
		Cpu_to_DvmLdevice(p, pNew);
	}
}

void CCpusDvmDeviceTool::DvmDevice_to_Cpus(CDvmDevice *pSrc, CCpus *pDest)
{
	pDest->m_strID = pSrc->m_strID;
	pDest->m_strName = pSrc->m_strName;

	POS pos = pSrc->GetHeadPosition();
	CCpu *pNew = NULL;
	CDvmLogicDevice *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmLogicDevice *)pSrc->GetNext(pos);
		pNew = new CCpu();
		pDest->AddNewChild(pNew);
		DvmLdevice_to_Cpu(p, pNew);
	}
}

void CCpusDvmDeviceTool::Cpu_to_DvmLdevice(CCpu *pSrc, CDvmLogicDevice *pDest)
{
	pDest->m_strID = pSrc->m_strID;
	pDest->m_strName = pSrc->m_strName;

	POS pos = pSrc->GetHeadPosition();
	CDataSet *p = NULL;
	CDvmDataset *pNew = NULL;

	while (pos != NULL)
	{
		p = (CDataSet *)pSrc->GetNext(pos);
		pNew = new CDvmDataset();
		pDest->AddNewChild(pNew);
		DataSet_to_DvmDataset(p, pNew);
	}
}

void CCpusDvmDeviceTool::DataSet_to_DvmDataset(CDataSet *pSrc, CDvmDataset *pDest)
{
	pDest->m_strID = pSrc->m_strID;
	pDest->m_strName = pSrc->m_strName;

	POS pos = pSrc->GetHeadPosition();
	CDataObj *p = NULL;
	CDvmData *pNew = NULL;

	while (pos != NULL)
	{
		p = (CDataObj *)pSrc->GetNext(pos);
		pNew = new CDvmData();
		pDest->AddNewChild(pNew);
		DataObj_to_DvmData(p, pNew);
	}
}

void CCpusDvmDeviceTool::DataObj_to_DvmData(CDataObj *pSrc, CDvmData *pDest)
{
	pDest->m_strID = pSrc->m_strID;
	pDest->m_strName = pSrc->m_strName;

	POS pos = pSrc->GetHeadPosition();
	CDataObjValue *p = NULL;
	CDvmValue *pNew = NULL;

	while (pos != NULL)
	{
		p = (CDataObjValue *)pSrc->GetNext(pos);
		pNew = new CDvmValue();
		pDest->AddNewChild(pNew);
		DataObjValue_to_DvmValue(p, pNew);
	}
}

void CCpusDvmDeviceTool::DataObjValue_to_DvmValue(CDataObjValue *pSrc, CDvmValue *pDest)
{
	pDest->m_strID = pSrc->m_strID;
	pDest->m_strName = pSrc->m_strName;

	POS pos = pSrc->GetHeadPosition();
	CDataObjValue *p = NULL;
	CDvmValue *pNew = NULL;

	while (pos != NULL)
	{
		p = (CDataObjValue *)pSrc->GetNext(pos);
		pNew = new CDvmValue();
		pDest->AddNewChild(pNew);
		DataObjValue_to_DvmValue(p, pNew);
	}
}

void CCpusDvmDeviceTool::DvmLdevice_to_Cpu(CDvmLogicDevice *pSrc, CCpu *pDest)
{
	pDest->m_strID = pSrc->m_strID;
	pDest->m_strName = pSrc->m_strName;

	POS pos = pSrc->GetHeadPosition();
	CDataSet *pNew = NULL;
	CDvmDataset *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmDataset *)pSrc->GetNext(pos);
		pNew = new CDataSet();
		pDest->AddNewChild(pNew);
		DvmDataset_to_DataSet(p, pNew);
	}
}

void CCpusDvmDeviceTool::DvmDataset_to_DataSet(CDvmDataset *pSrc, CDataSet *pDest)
{
	pDest->m_strID = pSrc->m_strID;
	pDest->m_strName = pSrc->m_strName;

	POS pos = pSrc->GetHeadPosition();
	CDataObj *pNew = NULL;
	CDvmData *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmData *)pSrc->GetNext(pos);
		pNew = new CDataObj();
		pDest->AddNewChild(pNew);
		DvmData_to_DataObj(p, pNew);
	}
}

void CCpusDvmDeviceTool::DvmData_to_DataObj(CDvmData *pSrc, CDataObj *pDest)
{
	pDest->m_strID = pSrc->m_strID;
	pDest->m_strName = pSrc->m_strName;

	POS pos = pSrc->GetHeadPosition();
	CDataObjValue *pNew = NULL;
	CDvmValue *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmValue *)pSrc->GetNext(pos);
		pNew = new CDataObjValue();
		pDest->AddNewChild(pNew);
		DvmValue_to_DataObjValue(p, pNew);
	}
}

void CCpusDvmDeviceTool::DvmValue_to_DataObjValue(CDvmValue *pSrc, CDataObjValue *pDest)
{
	pDest->m_strID = pSrc->m_strID;
	pDest->m_strName = pSrc->m_strName;

	POS pos = pSrc->GetHeadPosition();
	CDataObjValue *pNew = NULL;
	CDvmValue *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmValue *)pSrc->GetNext(pos);
		pNew = new CDataObjValue();
		pDest->AddNewChild(pNew);
		DvmValue_to_DataObjValue(p, pNew);
	}
}


