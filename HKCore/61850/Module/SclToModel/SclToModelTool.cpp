#include "stdafx.h"
#include "SclToModelTool.h"
#include "..\..\..\Module\System\TickCount32.h"
#include "..\..\..\Module\API\FileApi.h"



CSclToModelTool::CSclToModelTool()
{
	m_pSclReadDlg = NULL;
	m_bCan_Free_SCL_INFO = FALSE;
	m_pOwnerWnd = NULL;
//	m_pSclStation = NULL;
}

CSclToModelTool::~CSclToModelTool()
{
	Free_SCL_INFO();

	if (m_pSclReadDlg != NULL)
	{
		delete m_pSclReadDlg;
		m_pSclReadDlg = NULL;
	}
}

void CSclToModelTool::Free_SCL_INFO()
{
	if (m_bCan_Free_SCL_INFO)
	{
		g_bUseSmemEnable = FALSE;
		scl_info_destroy(&m_SclInfo);
		g_bUseSmemEnable = TRUE;
		m_bCan_Free_SCL_INFO = FALSE;
	}
}

BOOL CSclToModelTool::ReadSclFile(const CString &strFile, CWnd *pOwnerWnd)
{	
	if (strFile == m_strFile)
		return TRUE;

	m_strFile=strFile;
	m_pOwnerWnd = pOwnerWnd;

	m_pSclReadDlg = new CSclReadDlg();
	
	m_pSclReadDlg->SetWindowTitle(_T("读取SCD文件"));
	m_pSclReadDlg->SetUseModeless();
	m_pSclReadDlg->DoModal();
	CWinThread *pThread = AfxBeginThread(ReadSCLThread, this);

	pThread->m_bAutoDelete = TRUE;

	return TRUE;
}

UINT CSclToModelTool::ReadSCLThread( LPVOID pParam )
{
	::CoInitialize(NULL);
	CSclToModelTool *pSclToModelTool = (CSclToModelTool *)pParam;

 	pSclToModelTool->m_pSclReadDlg->SetMaxRange(3);

	pSclToModelTool->m_pSclReadDlg->ShowMsg(_T("释放上个SCL文件处理的过程中的临时内存空间，请稍候......"));
	pSclToModelTool->Free_SCL_INFO();
	pSclToModelTool->m_oSclIEDs.DeleteAll();

 	pSclToModelTool->m_pSclReadDlg->ShowMsg(_T("读取SCD文件......"));
	g_bUseSmemEnable = FALSE;
 	ST_RET ret = scl_parse(pSclToModelTool->m_strFile.GetBuffer(), &pSclToModelTool->m_SclInfo);
	g_bUseSmemEnable = TRUE;
 	pSclToModelTool->m_bCan_Free_SCL_INFO = TRUE;
 	CString strMsg;
 
 	if (ret == SD_SUCCESS)
 	{
		pSclToModelTool->m_pSclReadDlg->StepIt();
		pSclToModelTool->m_pSclReadDlg->ShowMsg(_T("处理IED数据......"));

		SCL_IED		*scl_ied = NULL;
		CSclIED *pSclIED = NULL;

		for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)pSclToModelTool->m_SclInfo.iedHead);
			scl_ied != NULL;
			scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)pSclToModelTool->m_SclInfo.iedHead, (DBL_LNK *)scl_ied))
		{
			pSclIED = new CSclIED;
			pSclToModelTool->m_oSclIEDs.AddTail(pSclIED);

#ifdef SCL_USE_MMS_STRING_
			pSclIED->m_strID = mms_string(&scl_ied->name);
			pSclIED->m_strName = scl_ied->desc;
			pSclIED->m_strFactoryName = mms_string(&scl_ied->manufacturer);
			pSclIED->m_strDevType = mms_string(&scl_ied->type);
			pSclIED->m_pScl_ied = scl_ied;
#else
			pSclIED->m_strID = scl_ied->name;
			pSclIED->m_strName = scl_ied->desc;
			pSclIED->m_strFactoryName = scl_ied->manufacturer;
			pSclIED->m_strDevType = scl_ied->type;
			pSclIED->m_pScl_ied = scl_ied;
#endif
		}

		pSclToModelTool->ReadAllIedAddr();

		if (pSclToModelTool->m_pOwnerWnd != NULL)
		{
			pSclToModelTool->m_pOwnerWnd->PostMessage(WM_SCLTOMODEL_READ_FINISH, (LPARAM)pParam, (WPARAM)SCLTOMODEL_READ_SHOW);
		}
	}
 	else
 	{
		AfxMessageBox(_T("无法解析SCL文件."));
 	}
 
 	pSclToModelTool->m_pSclReadDlg->ShowWindow(SW_HIDE);
	::CoUninitialize();

	return 0;
}

void CSclToModelTool::GetAndSaveDeviceModel(CString &strSclFilePath,CString &strDeviceModelPath,CString &strIEDName)
{
	m_strFile = strSclFilePath;

	ST_RET ret = scl_parse(m_strFile.GetBuffer(), &m_SclInfo);
	m_bCan_Free_SCL_INFO = TRUE;

	if (ret == SD_SUCCESS)
	{
		SCL_IED		*scl_ied = NULL;

		for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)m_SclInfo.iedHead);
			scl_ied != NULL;
			scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)m_SclInfo.iedHead, (DBL_LNK *)scl_ied))
		{
#ifdef SCL_USE_MMS_STRING_
			if (stricmp(mms_string(&scl_ied->name),strIEDName) == 0)
#else
			if (stricmp(scl_ied->name,strIEDName) == 0)
#endif
			{
				break;
			}
		}

		if (scl_ied != NULL)
		{
			model_XmlWrite(strDeviceModelPath ,scl_ied,GetSclInfo(),0);
		}
	}
	else
	{
		AfxMessageBox(_T("无法解析SCL文件."));
	}

	Free_SCL_INFO();
}

BOOL CSclToModelTool::GetIED_ModelFile(CSclIED *pSclIED,CString &strIEDModelPath)
{
	strIEDModelPath = _P_GetLibraryPath();
	strIEDModelPath += ParseFileName(m_strFile);
#ifdef SCL_USE_MMS_STRING_
	if (pSclIED->m_pScl_ied->desc!=NULL)
	{
		strIEDModelPath.Append(pSclIED->m_pScl_ied->desc);
	}

	if (!mms_str_is_null(&pSclIED->m_pScl_ied->name))
	{
		strIEDModelPath.Append(mms_string(&pSclIED->m_pScl_ied->name));
	}
	strIEDModelPath.Append(_T(".xml"));
#else
	strIEDModelPath.AppendFormat(_T("\\%s%s.xml"),pSclIED->m_pScl_ied->desc,pSclIED->m_pScl_ied->name);
#endif
	return model_XmlWrite(strIEDModelPath ,pSclIED->m_pScl_ied,&m_SclInfo);
}

void CSclToModelTool::ReadAllIedAddr()
{
	CSclIED *pIed = NULL;
	SCL_SUBNET *scl_subnet = NULL;
	SCL_CAP *scl_cap = NULL;
	SCL_ADDRESS *scl_address = NULL;

	for (scl_subnet = (SCL_SUBNET*)list_find_last((DBL_LNK *)m_SclInfo.subnetHead);
		scl_subnet != NULL;
		scl_subnet = (SCL_SUBNET *)list_find_prev((DBL_LNK *)m_SclInfo.subnetHead, (DBL_LNK *)scl_subnet))
	{

		for (scl_cap= (SCL_CAP*)list_find_last((DBL_LNK *)scl_subnet->capHead);
			scl_cap != NULL;
			scl_cap = (SCL_CAP *)list_find_prev((DBL_LNK *)scl_subnet->capHead, (DBL_LNK *)scl_cap))
		{
#ifdef SCL_USE_MMS_STRING_
			pIed = (CSclIED*)m_oSclIEDs.FindByID(mms_string(&scl_cap->iedName));		
#else
			pIed = (CSclIED*)m_oSclIEDs.FindByID(scl_cap->iedName);		
#endif

			if (pIed==NULL)//没有对应的IED
			{
				continue;
			}

			for (scl_address= (SCL_ADDRESS*)list_find_last((DBL_LNK *)scl_cap->addressHead);
				scl_address!= NULL;
				scl_address = (SCL_ADDRESS*)list_find_prev((DBL_LNK *)scl_cap->addressHead, (DBL_LNK *)scl_address))
			{
#ifdef SCL_USE_MMS_STRING_
				if(!mms_str_is_null(&scl_address->address_ip))
				{
					pIed->m_strIP=mms_string(&scl_address->address_ip);
				}

				if(!mms_str_is_null(&scl_address->address_ip_subnet))
				{
					pIed->m_strSubNet=mms_string(&scl_address->address_ip_subnet);
				}

				if(!mms_str_is_null(&scl_address->address_ip_gateway))
				{
					pIed->m_strGateWay = mms_string(&scl_address->address_ip_gateway);
				}
#else
				if(scl_address->address_ip!=NULL)
				{
					pIed->m_strIP=scl_address->address_ip;
				}

				if(scl_address->address_ip_subnet!=NULL)
				{
					pIed->m_strSubNet=scl_address->address_ip_subnet;
				}

				if(scl_address->address_ip_gateway!=NULL)
				{
					pIed->m_strGateWay = scl_address->address_ip_gateway;
				}
#endif
			}

		}
	}	
}