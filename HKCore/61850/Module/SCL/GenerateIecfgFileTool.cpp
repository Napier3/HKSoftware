#include "StdAfx.h"
#include "GenerateIecfgFileTool.h"

CGenerateIecfgFileTool::CGenerateIecfgFileTool(void)
{
}

CGenerateIecfgFileTool::~CGenerateIecfgFileTool(void)
{
}

BOOL CGenerateIecfgFileTool::Generate(CIecCfgDevice *pIecfgDevice,const CString &strIedName)
{
	if (strIedName.Find(_T("PL22")) == 0)//110kV��·����
	{
		return GenerateLineProtIecfg_220kV(pIecfgDevice);
	}
	else if (strIedName.Find(_T("PL11")) == 0)//220kV��·����
	{
		return GenerateLineProtIecfg_110kV(pIecfgDevice);
	}

	return FALSE;
}

BOOL CGenerateIecfgFileTool::GenerateLineProtIecfg_220kV(CIecCfgDevice *pIecfgDevice)
{
	CIecCfgDatasMngr *pIecCfgDatasMngr = (CIecCfgDatasMngr*)pIecfgDevice->FindByClassID(CFGCLASSID_CIECCFGDATASMNGR);
	ASSERT(pIecCfgDatasMngr);
	CIecCfgDatasSMV *pSmvMngr = pIecCfgDatasMngr->GetSmvMngr();
	GenerateSMV_LineProt(pSmvMngr);
	CIecCfgGoutDatas* pGoutMngr = pIecCfgDatasMngr->GetGoutMngr();
	GenerateGout_Common(pGoutMngr);
	CIecCfgGinDatas *pIecCfgGinDatas = pIecCfgDatasMngr->GetGinMngr();

	CExBaseList oList;
	pIecCfgGinDatas->GetIecCfgDatas(oList);

	CExBaseObject *pCurObj = NULL;
	POS pos = oList.GetHeadPosition();
	CIecCfgGinData *pIecCfgGinData = NULL;
	BOOL bHasMapBin[4] = {FALSE,FALSE,FALSE,FALSE};
	CString strDesc[4];
	strDesc[0] = _T("��A��·��");
	strDesc[1] = _T("��B��·��");
	strDesc[2] = _T("��C��·��");
	strDesc[3] = _T("�غ�բ����");

	while (pos != NULL)
	{
		pCurObj = oList.GetNext(pos);
		pIecCfgGinData = (CIecCfgGinData *)pCurObj;
		pIecCfgGinData->m_nFiberIndex = 1;

		for (int nChMapIndex = 0;nChMapIndex<4;nChMapIndex++)
		{
			if ((!bHasMapBin[nChMapIndex])&&pIecCfgGinData->SetChMap(strDesc[0],nChMapIndex + 1))//�����δӳ�������ӳ��
			{
				bHasMapBin[nChMapIndex] = TRUE;
			}
		}
	}

	BOOL bRet = TRUE;

	for (int nChMapIndex = 0;nChMapIndex<4;nChMapIndex++)
	{
		if (!bHasMapBin[nChMapIndex])//�����δӳ�������ӳ��
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("110kV��·����,GOOSE����%ldͨ��ӳ��(%s)ʧ��"),nChMapIndex+1,strDesc[0].GetString());
			bRet = FALSE;
		}
	}

	oList.RemoveAll();
	return bRet;
}

BOOL CGenerateIecfgFileTool::GenerateLineProtIecfg_110kV(CIecCfgDevice *pIecfgDevice)
{
	CIecCfgDatasMngr *pIecCfgDatasMngr = (CIecCfgDatasMngr*)pIecfgDevice->FindByClassID(CFGCLASSID_CIECCFGDATASMNGR);
	ASSERT(pIecCfgDatasMngr);
	CIecCfgDatasSMV *pSmvMngr = pIecCfgDatasMngr->GetSmvMngr();
	GenerateSMV_LineProt(pSmvMngr);
	CIecCfgGoutDatas* pGoutMngr = pIecCfgDatasMngr->GetGoutMngr();
	GenerateGout_Common(pGoutMngr);
	CIecCfgGinDatas *pIecCfgGinDatas = pIecCfgDatasMngr->GetGinMngr();
	CExBaseList oList;
	pIecCfgGinDatas->GetIecCfgDatas(oList);

	CExBaseObject *pCurObj = NULL;
	POS pos = oList.GetHeadPosition();
	CIecCfgGinData *pIecCfgGinData = NULL;
	BOOL bHasMapBin1 = FALSE;
	BOOL bHasMapBin4 = FALSE;

	while (pos != NULL)
	{
		pCurObj = oList.GetNext(pos);
		pIecCfgGinData = (CIecCfgGinData *)pCurObj;
		pIecCfgGinData->m_nFiberIndex = 1;

		if ((!bHasMapBin1)&&pIecCfgGinData->SetChMap(_T("��·����"),1))//�����δӳ�������ӳ��
		{
			bHasMapBin1 = TRUE;
		}

		if ((!bHasMapBin4)&&pIecCfgGinData->SetChMap(_T("�غ�բ����"),4))//�����δӳ�������ӳ��
		{
			bHasMapBin4 = TRUE;
		}
	}

	BOOL bRet = TRUE;

	if (!bHasMapBin1)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("110kV��·����,GOOSE����1ͨ��ӳ��(��·����)ʧ��"));
		bRet = FALSE;
	}

	if (!bHasMapBin4)
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("110kV��·����,GOOSE����4ͨ��ӳ��(�غ�բ����)ʧ��"));
		bRet = FALSE;
	}

	oList.RemoveAll();
	return bRet;
}

BOOL CGenerateIecfgFileTool::GenerateSMV_LineProt(CIecCfgDatasSMV *pSmvMngr)
{
	CExBaseList oList;
	pSmvMngr->GetIecCfgDatas(oList);

	CExBaseObject *pCurObj = NULL;
	POS pos = oList.GetHeadPosition();
	CIecCfgSmvDataBase *pIecSmvDataBase = NULL;

	while (pos != NULL)
	{
		pCurObj = oList.GetNext(pos);
		pIecSmvDataBase = (CIecCfgSmvDataBase *)pCurObj;
		pIecSmvDataBase->m_nFiberIndex = 0;
		pIecSmvDataBase->SetAbc(TRUE,TRUE,TRUE);
	}

	oList.RemoveAll();
	return TRUE;
}


BOOL CGenerateIecfgFileTool::GenerateGout_Common(CIecCfgGoutDatas* pGoutMngr)
{
	CExBaseList oList;
	pGoutMngr->GetIecCfgDatas(oList);

	CExBaseObject *pCurObj = NULL;
	POS pos = oList.GetHeadPosition();
	CIecCfgGooseDataBase *pIecGooseDataBase = NULL;

	while (pos != NULL)
	{
		pCurObj = oList.GetNext(pos);
		pIecGooseDataBase = (CIecCfgGooseDataBase *)pCurObj;
		pIecGooseDataBase->m_nFiberIndex = 1;
	}

	oList.RemoveAll();
	return TRUE;
}
