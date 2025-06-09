// IEDGSSVInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "SclFileRead.h"
#include "..\..\..\Module\System\TickCount32.h"
#include "..\..\..\Module\DataMngr\DvmDevice.h"
#include "..\SclToModel\ModelWriteXml.h"


CSclFileRead::CSclFileRead()
{
	m_bSclIedSaveDvm = TRUE;
	m_bIsInReadState = FALSE;
	m_pThreadProgress = FALSE;
#ifndef _PSX_IDE_QT_
	m_pScdFileRWDlg=NULL;
#endif
	m_pRefIED = NULL;
	m_bCan_Free_SCL_INFO = FALSE;
	m_pReadThread = NULL;
	m_pOwnerWnd = NULL;
}

CSclFileRead::~CSclFileRead()
{
	Free_SCL_INFO();

#ifndef _PSX_IDE_QT_
	if (m_pScdFileRWDlg != NULL)
	{
		delete m_pScdFileRWDlg;
		m_pScdFileRWDlg = NULL;
	}
#endif

	if (m_pReadThread != NULL)
	{
#ifdef _PSX_IDE_QT_
		m_pReadThread->PostThreadMessage(WM_QUIT, 0, 0);
		m_pReadThread->wait();
#endif
		m_pReadThread = NULL;
	}
}

void CSclFileRead::Free_SCL_INFO()
{
	if (m_bCan_Free_SCL_INFO)
	{
		scl_info_destroy(&m_SclInfo);
		m_bCan_Free_SCL_INFO = FALSE;
	}
}

DWORD CSclFileRead::Filter(const CString &strTxtFilter, DWORD dwMode)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		p->FilterOwn(strTxtFilter, dwMode);
	}

	return 0;
}

void CSclFileRead::ReadGSSVChannels(CSclCtrls *pCtrls)
{
	if (pCtrls->IsRead())
	{
		return;
	}

	BOOL bGsIn = scl_IsGsIns(pCtrls);
	BOOL bGsOut = scl_IsGsOuts(pCtrls);
	BOOL bSmvIn = scl_IsSmvIns(pCtrls);
	BOOL bSmvOut = scl_IsSmvOuts(pCtrls);

	//获取通道
	POS pos = pCtrls->GetHeadPosition();
	CSclCtrlBase *pCtrl = NULL;

	while (pos != NULL)
	{
		pCtrl = (CSclCtrlBase *)pCtrls->GetNext(pos);

		if (bGsIn)
		{
			FindGSSVInChannelInfo(&m_SclInfo, pCtrl);
		}

		if (bGsOut)
		{
			FindGSSVOutChannelInfo(&m_SclInfo, pCtrl);
		}

		if (bSmvIn)
		{
			FindGSSVInChannelInfo(&m_SclInfo, pCtrl);
		}

		if (bSmvOut)
		{
			FindGSSVOutChannelInfo(&m_SclInfo, pCtrl);
		}

		pCtrl->m_nChnCount = pCtrl->GetCount();
	}

	pCtrls->SetRead();
}

// BOOL CSclFileRead::ReadGSSVControl(CExBaseList *pList)
// {
// 	UINT nClassID = pList->GetClassID();
// 
// 	if (   (nClassID == SCLIECCLASSID_CTRLS_GS_IN)
// 		|| (nClassID == SCLIECCLASSID_CTRLS_GS_OUT)
// 		|| (nClassID == SCLIECCLASSID_CTRLS_SMV_IN)
// 		|| (nClassID == SCLIECCLASSID_CTRLS_SMV_OUT) )
// 	{
// 		ReadGSSVControl((CSclCtrls*)pList);
// 		return TRUE;
// 	}
// 	else
// 	{
// 		return FALSE;
// 	}
// }

// void CSclFileRead::ReadGSSVControl(CSclIed *pIed, BOOL bGsIn, BOOL bGsOut, BOOL bSmvIn, BOOL bSmvOut)
// {
// 	ReadGSSVControl(&m_SclInfo, pIed, bGsIn, bGsOut, bSmvIn, bSmvOut);
// }


void CSclFileRead::ReadIedInfoAndCtrls(SCL_INFO* scl_info)
{
	SCL_IED		*scl_ied = NULL;
	SCL_AP		*scl_ap = NULL;
	SCL_LD		*scl_ld = NULL;
	SCL_LN		*scl_ln = NULL;
	CDvmDevice *pDvmDevice = NULL;
	CSclIed *pNewIed = NULL;
	CDvmLogicDevice *pDvmLdevice = NULL;

	for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)scl_info->iedHead);
		scl_ied != NULL;
		scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)scl_info->iedHead, (DBL_LNK *)scl_ied))
	{
		pNewIed = new CSclIed();
		m_pSclStation->AddNewChild(pNewIed);
		SetRefIED(pNewIed,scl_ied);

		if (m_bSclIedSaveDvm)
		{
			pDvmDevice = pNewIed->GetDvmDevice();
		}

		CString strType ,strManufacturer , strDesc ;

#ifdef SCL_USE_MMS_STRING_
		strType = mms_string(&scl_ied->type);
		strManufacturer = mms_string(&scl_ied->manufacturer);
#else
		strType = scl_ied->type;
		strManufacturer = scl_ied->manufacturer;
#endif
		strDesc = scl_ied->desc ;

		if (m_bSclIedSaveDvm)
		{
			pDvmDevice->SetDeviceAttribute(DEVICE_type, strType);
			pDvmDevice->SetDeviceAttribute(DEVICE_manufacturer, strManufacturer);
			pDvmDevice->SetDeviceAttribute(DEVICE_desc, strDesc);
		}

		for (scl_ap = (SCL_AP *)list_find_last((DBL_LNK *)scl_ied->apHead);
			scl_ap != NULL;
			scl_ap = (SCL_AP *)list_find_prev((DBL_LNK *)scl_ied->apHead, (DBL_LNK *)scl_ap))
		{
			for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)scl_ap->ldHead);
				scl_ld != NULL;
				scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ap->ldHead, (DBL_LNK *)scl_ld))
			{
#ifdef SCL_USE_MMS_STRING_
				if(mms_str_length(&scl_ld->inst)!=0)
				{
					pNewIed->SetLDType(mms_string(&scl_ld->inst));		
				}

				if (m_bSclIedSaveDvm)
				{
					pDvmLdevice=new CDvmLogicDevice();			//cgl	对应逻辑节点
					pDvmDevice->AddNewChild(pDvmLdevice);				
					pDvmLdevice->m_strName=scl_ld->desc;
					pDvmLdevice->m_strID.Format(_T("%s%s"), pNewIed->m_strID, mms_string(&scl_ld->inst));	
				}
#else
				if(scl_ld->inst!=NULL)
				{
					pNewIed->SetLDType(scl_ld->inst);		
				}

				if (m_bSclIedSaveDvm)
				{
					pDvmLdevice=new CDvmLogicDevice();			//cgl	对应逻辑节点
					pDvmDevice->AddNewChild(pDvmLdevice);				
					pDvmLdevice->m_strName=scl_ld->desc;
					pDvmLdevice->m_strID.Format(_T("%s%s"), pNewIed->m_strID, scl_ld->inst);	
				}
#endif

				if (m_bSclIedSaveDvm)
				{
					pDvmLdevice->m_strName.AppendFormat(_T("(%s)"), pDvmLdevice->m_strID);
				}

				for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
					scl_ln != NULL;
					scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
				{
					ST_CHAR lnName	[MAX_TYPE_LEN + 1] = {0};
					//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
					//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
					//strncat (lnName, scl_ln->inst, MAX_IDENT_LEN + 1 - strlen(lnName));
					scl_get_ln_name(scl_ln, lnName);

					if (0 == stricmp(lnName, "LLN0"))
					{
						ReadLdDataset(scl_ln, scl_ap, pDvmLdevice);//zhouhj 2023.12.4 在此函数中通过pDvmLdevice是否为空，确认是否创建Dvm对象

						//2016-5-17
						if (m_bSclIedSaveDvm)
						{
							ReadLdRptCtrl(scl_ln, scl_ap, pDvmLdevice);//zhow20170610
							ReadLdLogCtrl(scl_ln, scl_ap, pDvmLdevice);//zhow20170610
						}

						ReadIedCtrls(scl_ln, scl_ap, pNewIed);//对于有Input描述及含相关索引的、GSEControl、SampledValueControl，new相关控制块；
	
						break;
					}
				}
			}
		}

		pNewIed->SetIedType();
	
	}

	ReadAllIedAddr();//把IP地址等信息写入new的Ied中
}

void CSclFileRead::ReadStationInfo()
{
#ifdef SCL_USE_MMS_STRING_
	m_pSclStation->m_strName = mms_string(&m_SclInfo.Header.id);
#else
	m_pSclStation->m_strName = m_SclInfo.Header.id;
#endif

	if (m_SclInfo.substationHead != NULL)
	{
		if (m_SclInfo.substationHead->desc != NULL)
		{
			if (m_SclInfo.substationHead->desc[0] != 0)
			{
				m_pSclStation->m_strName = m_SclInfo.substationHead->desc;
			}
		}

		if (m_pSclStation->m_strName.GetLength() == 0)
		{
			if (m_SclInfo.substationHead->name != NULL)
			{
				if (m_SclInfo.substationHead->name[0] != 0)
				{
					m_pSclStation->m_strName = m_SclInfo.substationHead->name;
				}
			}
		}
	}

	if (m_pSclStation->m_strName.GetLength() < 2)
	{
		m_pSclStation->m_strName = GetPathFileNameFromFilePathName(m_strFile);
		long nPos = m_pSclStation->m_strName.Find('.');

		if (nPos > 0)
		{
			m_pSclStation->m_strName = m_pSclStation->m_strName.Left(nPos);;
		}
	}

	m_pSclStation->m_strID = m_pSclStation->m_strName;

	SCL_BAY *scl_bay=NULL;
	SCL_VOLLEVEL *scl_vollevel=NULL;
	SCL_SUBSTATION *scl_substation=NULL;

	for (scl_substation = (SCL_SUBSTATION*)list_find_last((DBL_LNK *)m_SclInfo.substationHead);
		scl_substation != NULL;
		scl_substation = (SCL_SUBSTATION *)list_find_prev((DBL_LNK *)m_SclInfo.substationHead, (DBL_LNK *)scl_substation))
	{
		CSclBay *pSclBay=new CSclBay();
		m_pSclStation->AddNewChild(pSclBay);
		pSclBay->m_strName=scl_substation->name;
		pSclBay->m_strID=scl_substation->desc;	

		for (scl_vollevel = (SCL_VOLLEVEL*)list_find_last((DBL_LNK *)scl_substation->vollevelHead);
			scl_vollevel != NULL;
			scl_vollevel = (SCL_VOLLEVEL *)list_find_prev((DBL_LNK *)scl_substation->vollevelHead, (DBL_LNK *)scl_vollevel))
		{
			CSclBayVLevel *pSclBayVLevel=new CSclBayVLevel();
			pSclBay->AddNewChild(pSclBayVLevel);
			pSclBayVLevel->m_strName=scl_vollevel->name;
			pSclBayVLevel->m_strID=scl_vollevel->desc;		

			for (scl_bay = (SCL_BAY*)list_find_last((DBL_LNK *)scl_vollevel->bayHead);
				scl_bay != NULL;
				scl_bay = (SCL_BAY *)list_find_prev((DBL_LNK *)scl_vollevel->bayHead, (DBL_LNK *)scl_bay))
			{
				CSclIedRef *pSclIedRef=new CSclIedRef();
				pSclBayVLevel->AddNewChild(pSclIedRef);
				pSclIedRef->m_strName=scl_bay->name;
				pSclIedRef->m_strID=scl_bay->desc;		
			}
		}
	}
}

void CSclFileRead::ReadAllIedAddr()
{
	CSclIed *pIed = NULL;
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
			pIed = m_pSclStation->GetRefIed(mms_string(&scl_cap->iedName));	
#else
			pIed = m_pSclStation->GetRefIed(scl_cap->iedName);	
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
				if(mms_str_length(&scl_address->address_ip)>0)
				{
					pIed->m_strIP= mms_string(&scl_address->address_ip);
				}
				if(mms_str_length(&scl_address->address_ip_subnet)>0)
				{
					pIed->m_strIP_SUBNET=mms_string(&scl_address->address_ip_subnet);

				}
				if(mms_str_length(&scl_address->address_ip_gateway)>0)
				{
					pIed->m_strIP_GATEWAY=mms_string(&scl_address->address_ip_gateway);
				}
#else
				if(scl_address->address_ip!=NULL)
				{
					pIed->m_strIP=scl_address->address_ip;
				}
				if(scl_address->address_ip_subnet!=NULL)
				{
					pIed->m_strIP_SUBNET=scl_address->address_ip_subnet;

				}
				if(scl_address->address_ip_gateway!=NULL)
				{
					pIed->m_strIP_GATEWAY=scl_address->address_ip_gateway;
				}
#endif
			}

		}
	}	
}

void CSclFileRead::ReadIedCtrls(SCL_LN *scl_ln0, SCL_AP *scl_ap, CSclIed *pIed)
{
	SCL_INPUTS *scl_inputs = NULL;
	SCL_EXTREF *scl_extref = NULL;

	for (scl_inputs = (SCL_INPUTS *)list_find_last((DBL_LNK *)scl_ln0->inputsHead);
		scl_inputs != NULL;
		scl_inputs = (SCL_INPUTS *)list_find_prev((DBL_LNK *)scl_ln0->inputsHead, (DBL_LNK *)scl_inputs))
	{
		long index_extref = 1;
		for (scl_extref = (SCL_EXTREF *)list_find_last((DBL_LNK *)scl_inputs->extrefHead);
			scl_extref != NULL;
			scl_extref = (SCL_EXTREF *)list_find_prev((DBL_LNK *)scl_inputs->extrefHead, (DBL_LNK *)scl_extref))
		{
			scl_extref->index = index_extref;
			index_extref++;

			//get extref desc
			GetExtRefDesc(scl_ap, scl_extref);

#ifdef SCL_USE_MMS_STRING_
			//GOOSE Subscribe
			if ((mms_str_length(&scl_extref->inAddr) > 0)
				&& (mms_str_length(&scl_extref->domName) > 0))
			{
				pIed->GetGsIns();
			} 

			//SV Subscribe
			if ((mms_str_length(&scl_extref->inAddr) > 0)
				&& (mms_str_length(&scl_extref->domName) > 0))
			{
				pIed->GetSmvIns();
			}
#else
			//GOOSE Subscribe
			if ((strlen(scl_extref->inAddr) > 0)
				&& (strlen(scl_extref->domName) > 0))
			{
				pIed->GetGsIns();
			} 

			//SV Subscribe
			if ((strlen(scl_extref->inAddr) > 0)
				&& (strlen(scl_extref->domName) > 0))
			{
				pIed->GetSmvIns();
			}
#endif
		}
	}

	//GOOSE Outputs
	if ( (NULL != (SCL_GCB *)list_find_last((DBL_LNK *)scl_ln0->gcbHead)))							
	{
		pIed->GetGsOuts();
	}

	//SMV Outputs
	if ( (NULL != (SCL_SVCB *)list_find_last((DBL_LNK *)scl_ln0->svcbHead)))
	{
		pIed->GetSmvOuts();
	}
}

void CSclFileRead::ReadLdDataset(SCL_LN *scl_ln0, SCL_AP *scl_ap, CDvmLogicDevice *pDvmLdevice)
{
	SCL_DATASET *scl_dataset = NULL;
	SCL_FCDA *scl_fcda = NULL;

	for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)scl_ln0->datasetHead);
		scl_dataset != NULL;
		scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)scl_ln0->datasetHead, (DBL_LNK *)scl_dataset))
	{
#ifdef SCL_USE_MMS_STRING_
		if (IsDatasetInGSSV(scl_ln0, mms_string(&scl_dataset->name)))
#else
		if (IsDatasetInGSSV(scl_ln0, scl_dataset->name))
#endif
		{

			for (scl_fcda = (SCL_FCDA *)list_find_last((DBL_LNK *)scl_dataset->fcdaHead);
				scl_fcda != NULL;
				scl_fcda = (SCL_FCDA *)list_find_prev((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
			{
				//get fcda type, value and desc
				GetFCDAInfo(&m_SclInfo, scl_ap, scl_fcda);//zhow20170608:将FCDA中的LN、DO、DA等详细信息补全
			}

		}

		if (pDvmLdevice != NULL)
		{							
			CDvmDataset *pDataset=new CDvmDataset();
			pDvmLdevice->AddNewChild(pDataset);
#ifdef SCL_USE_MMS_STRING_
			pDataset->m_strID.Format(_T("LLN0$%s"), mms_string(&scl_dataset->name));
#else
			pDataset->m_strID.Format(_T("LLN0$%s"), scl_dataset->name);
#endif
			pDataset->m_strName.Format(_T("%s(%s)"), scl_dataset->desc, pDataset->m_strID);

			for (scl_fcda = (SCL_FCDA *)list_find_last((DBL_LNK *)scl_dataset->fcdaHead);
				scl_fcda != NULL;
				scl_fcda = (SCL_FCDA *)list_find_prev((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
			{

				CDvmData *pData=new CDvmData();									
				pDataset->AddNewChild(pData);
				LogFCDAInfo(&m_SclInfo, scl_ap, scl_fcda,pData);	//zhow20170608:将设备模型的信息写入new的CDvmData中；	
			}
		}
	}
}

//whether the dataset is in GOOSE or SV
bool CSclFileRead::IsDatasetInGSSV(SCL_LN *sclln, char *dataset)
{
	SCL_GCB		*scl_gcb = NULL;
	SCL_SVCB	*scl_svcb = NULL;

	for (scl_gcb = (SCL_GCB *)list_find_last((DBL_LNK *)sclln->gcbHead);
		scl_gcb != NULL;
		scl_gcb = (SCL_GCB *)list_find_prev((DBL_LNK *)sclln->gcbHead, (DBL_LNK *)scl_gcb))
	{
		if(scl_gcb->isGoose == SD_FALSE)
		{
			continue;
		}

#ifdef SCL_USE_MMS_STRING_
		if (0 == strcmp(dataset, mms_string(&scl_gcb->datSet)))
#else
		if (0 == strcmp(dataset, scl_gcb->datSet))
#endif
		{
			return true;
		}
	}

	for (scl_svcb = (SCL_SVCB *)list_find_last((DBL_LNK *)sclln->svcbHead);
		scl_svcb != NULL;
		scl_svcb = (SCL_SVCB *)list_find_prev((DBL_LNK *)sclln->svcbHead, (DBL_LNK *)scl_svcb))
	{
#ifdef SCL_USE_MMS_STRING_
		if (0 == strcmp(dataset, mms_string(&scl_svcb->datSet)))
#else
		if (0 == strcmp(dataset, scl_svcb->datSet))
#endif
		{
			return true;
		}
	}

	return false;
}

//get extref desc
ST_RET CSclFileRead::GetExtRefDesc(SCL_AP *sclap, SCL_EXTREF *sclextref)
{
	SCL_LD	*scl_ld = NULL;
	SCL_LN	*scl_ln = NULL;
	SCL_DAI	*scl_dai = NULL;

	ST_CHAR extrefldName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR extreflnName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	extrefdoName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	extrefdaName	[MAX_IDENT_LEN + 1] = {0};//zhow:20170803
	ST_CHAR	extrefdescName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR extrefdoiName	[MAX_IDENT_LEN + 1] = {0};

	//find extref ld/ln/do name from sclextref
	FindextrefName(sclextref, extrefldName, extreflnName, extrefdoName,extrefdaName);

	strncpy (extrefdescName, extrefdoName, MAX_IDENT_LEN + 1);
	strcat (extrefdescName, "$dU");
	strncpy (extrefdoiName, extrefdoName, MAX_IDENT_LEN + 1);
	strcat (extrefdoiName, "$desc");

	for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)sclap->ldHead);
		scl_ld != NULL;
		scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)sclap->ldHead, (DBL_LNK *)scl_ld))
	{
#ifdef SCL_USE_MMS_STRING_
		if (0 == strcmp(extrefldName, mms_string(&scl_ld->inst)))
#else
		if (0 == strcmp(extrefldName, scl_ld->inst))
#endif
		{
			for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
				scl_ln != NULL;
				scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
			{
				ST_CHAR lnName[MAX_TYPE_LEN + 1] = {0};
				//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
				//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
				//strncat (lnName, scl_ln->inst,  MAX_IDENT_LEN + 1 - strlen(lnName));
				scl_get_ln_name(scl_ln, lnName);

				if (0 == strcmp(extreflnName, lnName))
				{
					for (scl_dai = (SCL_DAI *)list_find_last((DBL_LNK *)scl_ln->daiHead);
						scl_dai != NULL;
						scl_dai = (SCL_DAI *)list_find_prev((DBL_LNK *)scl_ln->daiHead, (DBL_LNK *)scl_dai))
					{
#ifdef SCL_USE_MMS_STRING_
						if (strcmp(mms_string(&scl_dai->flattened), extrefdescName) == 0)
						{//sclextref dU desc 
							if (scl_dai->Val)
							{
								mms_str_init2(&sclextref->desc,2*(strlen(scl_dai->Val)+2));
								strcpy(mms_string(&sclextref->desc),scl_dai->Val);
								UTF8ToMultiByte(mms_string(&sclextref->desc));
							}
						}
						else if (strcmp(mms_string(&scl_dai->flattened), extrefdoiName) == 0)
						{//sclextref do desc
							if (scl_dai->Val)
							{
								mms_str_init2(&sclextref->dodesc,2*(strlen(scl_dai->Val)+2));
								strcpy(mms_string(&sclextref->dodesc),scl_dai->Val);
							}
						}
#else
						if (strcmp(scl_dai->flattened, extrefdescName) == 0)
						{//sclextref dU desc 
							if (scl_dai->Val)
							{
								strncpy (sclextref->desc, scl_dai->Val, MAX_IDENT_LEN + 1);
								UTF8ToMultiByte(sclextref->desc);
							}
						}
						else if (strcmp(scl_dai->flattened, extrefdoiName) == 0)
						{//sclextref do desc
							if (scl_dai->Val)
							{
								strncpy (sclextref->dodesc, scl_dai->Val, MAX_IDENT_LEN + 1);
							}
						}
#endif
					}

					if (scl_ln->desc)
					{//sclextref ln desc
#ifdef SCL_USE_MMS_STRING_
						mms_str_init2(&sclextref->lndesc,(strlen(scl_ln->desc) + 2));
						strcpy(mms_string(&sclextref->lndesc),scl_ln->desc);
#else
						strncpy (sclextref->lndesc, scl_ln->desc, MAX_IDENT_LEN + 1);
#endif
					}

#ifdef SCL_USE_MMS_STRING_
					ReadGSSVChannelDOType(mms_string(&scl_ln->lnType),extrefdoName ,sclextref);
#else
					ReadGSSVChannelDOType(scl_ln->lnType,extrefdoName ,sclextref);
#endif
					ReadGSSVChanelDaType(sclextref ,extrefdaName);

					break;
				}
			}
			break;
		}
	}

	return SD_SUCCESS;
}

void CSclFileRead::ReadGSSVChannelDOType(char *lnType,char *extrefdoName , SCL_EXTREF *sclextref)
{
	SCL_LNTYPE *scl_lntype = NULL;
	SCL_DO *scl_do = NULL;

	for (scl_lntype = (SCL_LNTYPE *)list_find_last((DBL_LNK *)m_SclInfo.lnTypeHead);
		scl_lntype != NULL;
		scl_lntype = (SCL_LNTYPE *)list_find_prev((DBL_LNK *)m_SclInfo.lnTypeHead, (DBL_LNK *)scl_lntype))
	{
#ifdef SCL_USE_MMS_STRING_
		if (0 == strcmp(mms_string(&scl_lntype->id), lnType))
#else
		if (0 == strcmp(scl_lntype->id, lnType))
#endif
		{

			for (scl_do = (SCL_DO *)list_find_last((DBL_LNK *)scl_lntype->doHead);
				scl_do != NULL;
				scl_do = (SCL_DO *)list_find_prev((DBL_LNK *)scl_lntype->doHead, (DBL_LNK *)scl_do))
			{
#ifdef SCL_USE_MMS_STRING_
				if (0 == strcmp(mms_string(&scl_do->name),extrefdoName))
				{
					mms_str_copy(&sclextref->type, &scl_do->type);
//					strncpy (mms_string(&sclextref->type), scl_do->type,  MAX_IDENT_LEN + 1);
					break;
				}
#else
				if (0 == strcmp(scl_do->name,extrefdoName))
				{
					strncpy (sclextref->type, scl_do->type,  MAX_IDENT_LEN + 1);
					break;
				}
#endif
			}
			break;
		}
	}
}

void CSclFileRead::ReadGSSVChanelDaType( SCL_EXTREF *sclextref ,char *extrefdaName)
{
	SCL_LNTYPE *scl_lntype = NULL;
	SCL_DOTYPE *doType = NULL;
	SCL_DO *scl_do = NULL;
	SCL_DA *scl_da = NULL;
	ST_CHAR fcdadodaName	[MAX_IDENT_LEN + 1] = {0};

	strncpy (fcdadodaName, extrefdaName, MAX_IDENT_LEN + 1);
	ST_CHAR daFstName[MAX_IDENT_LEN + 1] = {0};
	FindDelStr(fcdadodaName, daFstName);

	for (doType = (SCL_DOTYPE *)list_find_last((DBL_LNK *)m_SclInfo.doTypeHead);
		doType != NULL;
		doType = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)m_SclInfo.doTypeHead, (DBL_LNK *)doType))
	{
#ifdef SCL_USE_MMS_STRING_
		if (0 == mms_str_cmp(&doType->id, &sclextref->type))
		{
			if (extrefdaName[0] =='\0')
			{
				mms_str_copy(&sclextref->cdc, &doType->cdc);
				break;
			}

			mms_str_copy(&sclextref->cdc, &doType->cdc);

			for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)doType->daHead);
				scl_da != NULL;
				scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)doType->daHead, (DBL_LNK *)scl_da))
			{
				if (0 == strcmp(mms_string(&scl_da->name), daFstName ))
				{
					if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
					{
						ST_CHAR	tdotype[MAX_IDENT_LEN + 1] = {0};
						strncpy (tdotype, mms_string(&scl_da->type), MAX_IDENT_LEN + 1);

						ReadGSSVChanelDaType(sclextref,extrefdaName);
					}
					else//da type
					{
						if (0 == strcmp(mms_string(&scl_da->bType), "Struct"))
						{
							ReadGSSVChanelBDA(fcdadodaName ,scl_da ,sclextref);
						}
						else
						{
							mms_str_copy(&sclextref->type, &scl_da->bType);
						}
					}	
					break;
				}
			}
			break;
		}
#else
		if (0 == strcmp(doType->id, sclextref->type))
		{
			if (extrefdaName[0] =='\0')
			{
				strncpy(sclextref->cdc, doType->cdc, MAX_IDENT_LEN + 1);
				break;
			}

			strncpy(sclextref->cdc, doType->cdc, MAX_IDENT_LEN + 1);

			for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)doType->daHead);
				scl_da != NULL;
				scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)doType->daHead, (DBL_LNK *)scl_da))
			{
				if (0 == strcmp(scl_da->name, daFstName ))
				{
					if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
					{
						ST_CHAR	tdotype[MAX_IDENT_LEN + 1] = {0};
						strncpy (tdotype, scl_da->type, MAX_IDENT_LEN + 1);

						ReadGSSVChanelDaType(sclextref,extrefdaName);
					}
					else//da type
					{
						if (0 == strcmp(scl_da->bType, "Struct"))
						{
							ReadGSSVChanelBDA(fcdadodaName ,scl_da ,sclextref);
						}
						else
						{
							strncpy(sclextref->type, scl_da->bType, MAX_IDENT_LEN + 1);
						}
					}	
					break;
				}
			}
			break;
		}
#endif
	}
}

void CSclFileRead::ReadGSSVChanelBDA(char *extrefdoName ,SCL_DA *scl_da , SCL_EXTREF *sclextref)
{
	SCL_DATYPE *scl_datype = NULL;
	SCL_BDA *scl_bda = NULL;
	if (strlen(extrefdoName)>0)
	{
		for (scl_datype = (SCL_DATYPE *)list_find_last((DBL_LNK *)m_SclInfo.daTypeHead);
			scl_datype != NULL;
			scl_datype = (SCL_DATYPE *)list_find_prev((DBL_LNK *)m_SclInfo.daTypeHead, (DBL_LNK *)scl_datype))
		{
#ifdef SCL_USE_MMS_STRING_
			if (0 == strcmp(mms_string(&scl_datype->id), mms_string(&scl_da->type )))
			{
				for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)scl_datype->bdaHead);
					scl_bda != NULL;
					scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)scl_datype->bdaHead, (DBL_LNK *)scl_bda))
				{
					if (0 == strcmp(mms_string(&scl_bda->name), extrefdoName))
					{
						mms_str_copy(&sclextref->type, &scl_bda->bType);
						break;
					}
				}
				break;
			}
#else
			if (0 == strcmp(scl_datype->id, scl_da->type ))
			{
				for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)scl_datype->bdaHead);
					scl_bda != NULL;
					scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)scl_datype->bdaHead, (DBL_LNK *)scl_bda))
				{
					if (0 == strcmp(scl_bda->name, extrefdoName))
					{
						strncpy (sclextref->type, scl_bda->bType, MAX_IDENT_LEN + 1);
						break;
					}
				}
				break;
			}
#endif
		}
	} 
	else
	{
#ifdef SCL_USE_MMS_STRING_
		mms_str_copy(&sclextref->type, &scl_da->type);
#else
		strncpy (sclextref->type, scl_da->type, MAX_IDENT_LEN + 1);
#endif
	}
}

//get fcda type, /*value*/ and desc
ST_RET CSclFileRead::GetFCDAInfo(SCL_INFO* sclinfo, SCL_AP *sclap, SCL_FCDA *sclfcda)
{
	SCL_LD	*scl_ld = NULL;
	SCL_LN	*scl_ln = NULL;
	SCL_DAI	*scl_dai = NULL;

#ifdef SCL_USE_MMS_STRING_
	CString fcdaldName = _T("");
	CString fcdalnName = _T("");
	CString	fcdadaiName = _T("");
	CString	fcdadescName = _T("");
	CString fcdadoiName = _T("");

	fcdaldName = mms_string(&sclfcda->ldInst);
	fcdalnName.Format(_T("%s%s%s"),mms_string(&sclfcda->prefix),mms_string(&sclfcda->lnClass),mms_string(&sclfcda->lnInst));

	if (mms_str_length(&sclfcda->doName)>0)
	{
		fcdadaiName = mms_string(&sclfcda->doName);
		fcdadescName = mms_string(&sclfcda->doName);
		fcdadoiName = mms_string(&sclfcda->doName);
	}

	if (mms_str_length(&sclfcda->daName)>0)
	{
		fcdadaiName.AppendFormat(_T("$%s"),mms_string(&sclfcda->daName));
	}

	CString strOld, strNew;
	strOld = _T(".");
	strNew = _T("$");
	fcdadaiName.Replace(strOld, strNew);
	fcdadescName.Replace(strOld, strNew);
// 	fcdadaiName.Replace('.','$');
// 	fcdadescName.Replace('.','$');
	fcdadescName += _T("$dU");
	//fcdadoiName.Replace('.','$');
	ConfigDoiName(fcdadoiName);
#else
	ST_CHAR fcdaldName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR fcdalnName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	fcdadaiName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	fcdadescName[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR fcdadoiName	[MAX_IDENT_LEN + 1] = {0};

	strncpy (fcdaldName, sclfcda->ldInst, MAX_IDENT_LEN + 1);
	strncpy (fcdalnName, sclfcda->prefix, MAX_IDENT_LEN + 1);
	strncat (fcdalnName, sclfcda->lnClass, MAX_IDENT_LEN + 1 - strlen(fcdalnName));
	strncat (fcdalnName, sclfcda->lnInst,  MAX_IDENT_LEN + 1 - strlen(fcdalnName));

	if (strlen (sclfcda->doName))
	{
		strncpy (fcdadaiName, sclfcda->doName, MAX_IDENT_LEN + 1);
		strncpy (fcdadescName, sclfcda->doName, MAX_IDENT_LEN + 1);
		strncpy (fcdadoiName, sclfcda->doName, MAX_IDENT_LEN + 1);
	}
	if (strlen (sclfcda->daName))
	{
		strcat (fcdadaiName, "$");
		strncat (fcdadaiName, sclfcda->daName, MAX_IDENT_LEN + 1 - strlen(fcdadaiName));
	}
	
	ReplaceDotToDollar(fcdadaiName);
	ConfigDescName(fcdadescName);
	ConfigDoiName(fcdadoiName);
#endif


	for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)sclap->ldHead);
		scl_ld != NULL;
		scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)sclap->ldHead, (DBL_LNK *)scl_ld))
	{
#ifdef SCL_USE_MMS_STRING_
		if (fcdaldName == mms_string(&scl_ld->inst))
		{
			for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
				scl_ln != NULL;
				scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
			{
				CString lnName = _T("");
				//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
				//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
				//strncat (lnName, scl_ln->inst,  MAX_IDENT_LEN + 1 - strlen(lnName));
				scl_get_ln_name(scl_ln, lnName);

				//!!! -- lijunqing  2014-10-27
				//sclfcda->prefix == scl_ln->prefix and sclfcda->lnClass == scl_ln->lnClass and sclfcda->inst == scl_ln->inst
				if (fcdalnName == lnName)
				{
					CString lnType;
					lnType = mms_string(&scl_ln->lnType);

					//fcda type
					GetFCDAType(sclinfo, sclfcda, lnType);

					for (scl_dai = (SCL_DAI *)list_find_last((DBL_LNK *)scl_ln->daiHead);
						scl_dai != NULL;
						scl_dai = (SCL_DAI *)list_find_prev((DBL_LNK *)scl_ln->daiHead, (DBL_LNK *)scl_dai))
					{
						//if (0 == strcmp(mms_string(&scl_dai->flattened), fcdadescName))
						if (fcdadescName == mms_string(&scl_dai->flattened))
						{//fcda desc dU
							if (scl_dai->Val)
							{
								mms_str_init2(&sclfcda->desc ,(2*strlen(scl_dai->Val)+2));
								
								strcpy (mms_string(&sclfcda->desc),scl_dai->Val);
								UTF8ToMultiByte(mms_string(&sclfcda->desc));
							}
						}
						else if (fcdadoiName == mms_string(&scl_dai->flattened))//(0 == strcmp(mms_string(&scl_dai->flattened), fcdadoiName))
						{//fcda do desc
							if (scl_dai->Val)
							{
								mms_str_init2(&sclfcda->dodesc ,(2*strlen(scl_dai->Val)+2));
								strcpy(mms_string(&sclfcda->dodesc), scl_dai->Val);
							}
						}
					}

					if (scl_ln->desc)
					{//sclextref ln desc
						mms_str_init2(&sclfcda->lndesc ,(2*strlen(scl_ln->desc)+2));
						strcpy (mms_string(&sclfcda->lndesc), scl_ln->desc);
					}

					break;
				}
			}
			break;
		}
#else
		if (0 == strcmp(fcdaldName, scl_ld->inst))
		{
			for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
				scl_ln != NULL;
				scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
			{
				ST_CHAR lnName[MAX_TYPE_LEN + 1] = {0};
				//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
				//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
				//strncat (lnName, scl_ln->inst,  MAX_IDENT_LEN + 1 - strlen(lnName));
				scl_get_ln_name(scl_ln, lnName);

				//!!! -- lijunqing  2014-10-27
				//sclfcda->prefix == scl_ln->prefix and sclfcda->lnClass == scl_ln->lnClass and sclfcda->inst == scl_ln->inst
				if (0 == strcmp(fcdalnName, lnName))
				{
					ST_CHAR lnType [MAX_IDENT_LEN + 1] = {0};
					strncpy(lnType, scl_ln->lnType, MAX_IDENT_LEN + 1);

					//fcda type
					GetFCDAType(sclinfo, sclfcda, lnType);

					for (scl_dai = (SCL_DAI *)list_find_last((DBL_LNK *)scl_ln->daiHead);
						scl_dai != NULL;
						scl_dai = (SCL_DAI *)list_find_prev((DBL_LNK *)scl_ln->daiHead, (DBL_LNK *)scl_dai))
					{
						if (0 == strcmp(scl_dai->flattened, fcdadescName))
						{//fcda desc dU
							if (scl_dai->Val)
							{
								strncpy (sclfcda->desc, scl_dai->Val, MAX_IDENT_LEN + 1);
								UTF8ToMultiByte(sclfcda->desc);
							}
						}
						else if (0 == strcmp(scl_dai->flattened, fcdadoiName))
						{//fcda do desc
							if (scl_dai->Val)
							{
								strncpy(sclfcda->dodesc, scl_dai->Val, MAX_IDENT_LEN + 1);
							}
						}
					}

					if (scl_ln->desc)
					{//sclextref ln desc
						strncpy (sclfcda->lndesc, scl_ln->desc, MAX_IDENT_LEN + 1);
					}

					break;
				}
			}
			break;
		}
#endif
	}

	return SD_SUCCESS;
}

void CSclFileRead::Valid_dU_DescString(CString &strName,char *pFCDA_LdName,long nMaxLenth)
{
	if (strlen(pFCDA_LdName) >= nMaxLenth)
	{
		return;
	}

	UTF8ToMultiByte(pFCDA_LdName);
	strName = pFCDA_LdName;
}


ST_RET CSclFileRead::LogFCDAInfo(SCL_INFO* sclinfo, SCL_AP *sclap, SCL_FCDA *sclfcda, CDvmData *pDvmData)
{
	SCL_LD	*scl_ld = NULL;
	SCL_LN	*scl_ln = NULL;
	SCL_DAI	*scl_dai = NULL;

	ST_CHAR fcdaldName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR fcdalnName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	fcdadaiName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	fcdadescName[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR fcdadoiName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR fcdadoName	[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR fcdadodaName	[MAX_IDENT_LEN + 1] = {0};

#ifdef SCL_USE_MMS_STRING_
	strncpy (fcdaldName, mms_string(&sclfcda->ldInst), MAX_IDENT_LEN + 1);
	strncpy (fcdalnName, mms_string(&sclfcda->prefix), MAX_IDENT_LEN + 1);
	strncat (fcdalnName, mms_string(&sclfcda->lnClass), MAX_IDENT_LEN + 1 - strlen(fcdalnName));
	strncat (fcdalnName, mms_string(&sclfcda->lnInst),  MAX_IDENT_LEN + 1 - strlen(fcdalnName));

	if (mms_str_length(&sclfcda->doName)>0)
	{
		strncpy (fcdadaiName, mms_string(&sclfcda->doName), MAX_IDENT_LEN + 1);
		strncpy (fcdadescName, mms_string(&sclfcda->doName), MAX_IDENT_LEN + 1);
		strncpy (fcdadoiName, mms_string(&sclfcda->doName), MAX_IDENT_LEN + 1);
	}
	if (mms_str_length(&sclfcda->daName)>0)
	{
		strcat (fcdadaiName, "$");
		strcat (fcdadaiName, mms_string(&sclfcda->daName));
	}

	ReplaceDotToDollar(fcdadaiName);
	ConfigDescName(fcdadescName);
	ConfigDoiName(fcdadoiName);
	int nLen = strlen(fcdadaiName);

	pDvmData->m_strID= mms_string(&sclfcda->prefix);
	pDvmData->m_strID += mms_string(&sclfcda->lnClass);
	pDvmData->m_strID += mms_string(&sclfcda->lnInst);

	if (mms_str_length(&sclfcda->fc)>0)
	{
		pDvmData->m_strID += "$";
		pDvmData->m_strID += mms_string(&sclfcda->fc);
	}

	if (mms_str_length(&sclfcda->doName)>0)
	{
		pDvmData->m_strID += "$";
		pDvmData->m_strID += mms_string(&sclfcda->doName);
	}

	if (mms_str_length(&sclfcda->daName)>0)
	{
		pDvmData->m_strID += "$";
		pDvmData->m_strID += mms_string(&sclfcda->daName);
	}

	static long nTMp111 = 0;

	if (pDvmData->m_strID == _T("BinInSGGIO7$ST$Ind17"))
	{
		nTMp111++;
	}
#else
	strncpy (fcdaldName, sclfcda->ldInst, MAX_IDENT_LEN + 1);
	strncpy (fcdalnName, sclfcda->prefix, MAX_IDENT_LEN + 1);
	strncat (fcdalnName, sclfcda->lnClass, MAX_IDENT_LEN + 1 - strlen(fcdalnName));
	strncat (fcdalnName, sclfcda->lnInst,  MAX_IDENT_LEN + 1 - strlen(fcdalnName));

	if (strlen (sclfcda->doName))
	{
		strncpy (fcdadaiName, sclfcda->doName, MAX_IDENT_LEN + 1);
		strncpy (fcdadescName, sclfcda->doName, MAX_IDENT_LEN + 1);
		strncpy (fcdadoiName, sclfcda->doName, MAX_IDENT_LEN + 1);
	}
	if (strlen (sclfcda->daName))
	{
		strcat (fcdadaiName, "$");
		strncat (fcdadaiName, sclfcda->daName, MAX_IDENT_LEN + 1 - strlen(fcdadaiName));
	}
	ReplaceDotToDollar(fcdadaiName);
	ConfigDescName(fcdadescName);
	ConfigDoiName(fcdadoiName);
	int nLen = strlen(fcdadaiName);

	pDvmData->m_strID= sclfcda->prefix;
	pDvmData->m_strID += sclfcda->lnClass;
	pDvmData->m_strID += sclfcda->lnInst;

	if (*sclfcda->fc != 0)
	{
		pDvmData->m_strID += "$";
		pDvmData->m_strID += sclfcda->fc;
	}

	if (*sclfcda->doName != 0)
	{
		pDvmData->m_strID += "$";
		pDvmData->m_strID += sclfcda->doName;
	}

	if (*sclfcda->daName != 0)
	{
		pDvmData->m_strID += "$";
		pDvmData->m_strID += sclfcda->daName;
	}
#endif

	for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)sclap->ldHead);
		scl_ld != NULL;
		scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)sclap->ldHead, (DBL_LNK *)scl_ld))
	{
#ifdef SCL_USE_MMS_STRING_
		if (0 == mms_str_cmp(&sclfcda->ldInst,&scl_ld->inst))
#else
		if (0 == strcmp(sclfcda->ldInst, scl_ld->inst))
#endif
		{
			for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
				scl_ln != NULL;
				scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
			{
#ifdef SCL_USE_MMS_STRING_
				//!!! -- lijunqing  2014-10-27
				if ( (mms_str_cmp(&sclfcda->prefix , &scl_ln->prefix) == 0)
					&& (mms_str_cmp(&sclfcda->lnClass, &scl_ln->lnClass) == 0)
					&& (mms_str_cmp(&sclfcda->lnInst, &scl_ln->inst) == 0) )
					//if (0 == strcmp(fcdalnName, lnName))
				{
					CString lnType;
					lnType = mms_string(&scl_ln->lnType);
					//GetFCDAType(sclinfo, sclfcda, lnType,pDvmData);
					pDvmData->m_strDataType=_T("STRUCT");

					if (pDvmData->m_strID == _T("BinInSGGIO7$ST$Ind17"))
					{
						nTMp111++;
					}

					long nTmp222 = 0;

					for (scl_dai = (SCL_DAI *)list_find_last((DBL_LNK *)scl_ln->daiHead);scl_dai != NULL;	scl_dai = (SCL_DAI *)list_find_prev((DBL_LNK *)scl_ln->daiHead, (DBL_LNK *)scl_dai))
					{
						if (nTmp222 == 85)
						{
							nTmp222++;
						}

						nTmp222++;
						strncpy (fcdadodaName,mms_string(&scl_dai->flattened), MAX_IDENT_LEN + 1);
#else
				if ( (strcmp(sclfcda->prefix , scl_ln->prefix) == 0)
					&& (strcmp(sclfcda->lnClass, scl_ln->lnClass) == 0)
					&& (strcmp(sclfcda->lnInst, scl_ln->inst) == 0) )
					//if (0 == strcmp(fcdalnName, lnName))
				{
					ST_CHAR lnType [MAX_IDENT_LEN + 1] = {0};
					strncpy(lnType, scl_ln->lnType, MAX_IDENT_LEN + 1);
					//GetFCDAType(sclinfo, sclfcda, lnType,pDvmData);
					pDvmData->m_strDataType=_T("STRUCT");

					for (scl_dai = (SCL_DAI *)list_find_last((DBL_LNK *)scl_ln->daiHead);scl_dai != NULL;	scl_dai = (SCL_DAI *)list_find_prev((DBL_LNK *)scl_ln->daiHead, (DBL_LNK *)scl_dai))
					{
						strncpy (fcdadodaName,scl_dai->flattened, MAX_IDENT_LEN + 1);
#endif
						FindDelStr(fcdadodaName, fcdadoName);
						if (strcmp(fcdadoName,fcdadaiName)!=0)
						{
							FindContinueDelStr(fcdadodaName, fcdadoName);
							if(strcmp(fcdadoName,fcdadaiName)!=0)
							{
								continue;
							}
						}					

						*fcdaldName = 0;
#ifdef SCL_USE_MMS_STRING_
						if (strstr(mms_string(&scl_dai->flattened), "$dU") != NULL)
						{
							if (scl_dai->Val != NULL)
							{
								strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
								Valid_dU_DescString(pDvmData->m_strName,fcdaldName,MAX_IDENT_LEN);
							}
						}
						else if (strstr(mms_string(&scl_dai->flattened), "$min") != NULL)
						{
							if (scl_dai->Val != NULL)
							{
								strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
								UTF8ToMultiByte(fcdaldName);
								pDvmData->m_strMin = fcdaldName;
							}
						}
						else if (strstr(mms_string(&scl_dai->flattened), "$max") != NULL)
						{
							if (scl_dai->Val != NULL)
							{
								strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
								UTF8ToMultiByte(fcdaldName);
								pDvmData->m_strMax = fcdaldName;
							}
						}
						else if (strstr(mms_string(&scl_dai->flattened), "$units$SIUnit") != NULL)
						{
							if (scl_dai->Val != NULL)
							{
								strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
								UTF8ToMultiByte(fcdaldName);
								pDvmData->m_strUnit= fcdaldName;
							}
						}
						else if (IsCreateValue(scl_dai))
						{
							if (scl_dai->Val!=NULL)
							{
								strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
							}

							UTF8ToMultiByte(fcdaldName);
							//pDvmData->m_strUnit= fcdaldName;
							CDvmValue *pNew = new CDvmValue();
							pNew->m_strValue = fcdaldName;
							pNew->m_strID = mms_string(&scl_dai->flattened);
							pNew->m_strName= mms_string(&scl_dai->flattened);
							pDvmData->AddNewChild(pNew);

							//寻找data数据格式
							CString finaldatype;
							finaldatype = mms_string(&scl_dai->flattened);							            
							GetValueType(sclinfo, sclfcda, lnType,finaldatype);//finaldatype传进去的是scl_dai->flattened，因为要做判断，传出来的是确定的数据类型
							pNew->m_strDataType=finaldatype;	

							if (pNew->m_strDataType.Find('$') != -1)
							{
								long nTest = 0;
								nTest++;
								nTest++;
							}
						}
#else
						if (strstr(scl_dai->flattened, "$dU") != NULL)
						{
							if (scl_dai->Val != NULL)
							{
								strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
								UTF8ToMultiByte(fcdaldName);
								pDvmData->m_strName = fcdaldName;
							}
						}
						else if (strstr(scl_dai->flattened, "$min") != NULL)
						{
							if (scl_dai->Val != NULL)
							{
								strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
								UTF8ToMultiByte(fcdaldName);
								pDvmData->m_strMin = fcdaldName;
							}
						}
						else if (strstr(scl_dai->flattened, "$max") != NULL)
						{
							if (scl_dai->Val != NULL)
							{
								strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
								UTF8ToMultiByte(fcdaldName);
								pDvmData->m_strMax = fcdaldName;
							}
						}
						else if (strstr(scl_dai->flattened, "$units$SIUnit") != NULL)
						{
							if (scl_dai->Val != NULL)
							{
								strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
								UTF8ToMultiByte(fcdaldName);
								pDvmData->m_strUnit= fcdaldName;
							}
						}
						else if (IsCreateValue(scl_dai))
						{
							if (scl_dai->Val!=NULL)
							{
								strncpy (fcdaldName, scl_dai->Val, MAX_IDENT_LEN + 1);
							}

							UTF8ToMultiByte(fcdaldName);
							//pDvmData->m_strUnit= fcdaldName;
							CDvmValue *pNew = new CDvmValue();
							pNew->m_strValue = fcdaldName;
							pNew->m_strID = scl_dai->flattened;
							pNew->m_strName= scl_dai->flattened;
							pDvmData->AddNewChild(pNew);

							//寻找data数据格式
							char finaldatype[MAX_IDENT_LEN + 1] = {0};
							strncpy (finaldatype, scl_dai->flattened, MAX_IDENT_LEN + 1);							            
							GetValueType(sclinfo, sclfcda, lnType,finaldatype);//finaldatype传进去的是scl_dai->flattened，因为要做判断，传出来的是确定的数据类型
							pNew->m_strDataType=finaldatype;							
						}
#endif
					}

					break;
				}
			}
			break;
		}
	}

	return SD_SUCCESS;
}

//get fcda type

#ifdef SCL_USE_MMS_STRING_
void CSclFileRead::GetFCDAType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &lntype)
#else
void CSclFileRead::GetFCDAType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, ST_CHAR *lntype)
#endif
{
#ifdef SCL_USE_MMS_STRING_
	CString	dotype = _T("");
	CString	datype = _T("");

	CString	fcdadodaName = _T("");

	//fcda doname is empty
	if (mms_str_length(&sclfcda->doName)>0)
	{
		fcdadodaName = mms_string(&sclfcda->doName);
	}

	//fcda daname is empty
	if (mms_str_length(&sclfcda->daName)>0)
	{
		fcdadodaName.AppendFormat(_T("$%s"),mms_string(&sclfcda->daName));
	}

	//find dotype from scl_lntype
	FindDoType(sclinfo, sclfcda, lntype, dotype, fcdadodaName);

	//find datype from scl_dotype
	if (mms_str_length(&sclfcda->doName)>0)
	{
		FindDaType(sclinfo, sclfcda, dotype, datype, fcdadodaName);
	} 
	else
	{
		//find fcda do struct
		return;
	}

	//find final type from scl_datype
	if (mms_str_length(&sclfcda->daName)>0)
	{
		FindFinalType(sclinfo, sclfcda, datype, fcdadodaName);
	} 
	else
	{
		//find fcda da struct
		return;
	}
#else
	ST_CHAR	dotype		[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	datype		[MAX_IDENT_LEN + 1] = {0};

	ST_CHAR	fcdadodaName[MAX_IDENT_LEN + 1] = {0};

	if (strlen (sclfcda->doName))
	{
		strncpy (fcdadodaName, sclfcda->doName, strlen(sclfcda->doName) + 1);
	}

	//fcda daname is empty
	if (strlen (sclfcda->daName))
	{
		strcat (fcdadodaName, "$");
		strncat (fcdadodaName, sclfcda->daName, strlen(sclfcda->daName) + 1);
	}

	//find dotype from scl_lntype
	FindDoType(sclinfo, sclfcda, lntype, dotype, fcdadodaName);

	//find datype from scl_dotype
	if (strlen (sclfcda->doName))
	{
		FindDaType(sclinfo, sclfcda, dotype, datype, fcdadodaName);
	} 
	else
	{
		//find fcda do struct
		return;
	}

	//find final type from scl_datype
	if (strlen (sclfcda->daName))
	{
		FindFinalType(sclinfo, sclfcda, datype, fcdadodaName);
	} 
	else
	{
		//find fcda da struct
		return;
	}
#endif

	return ;
}
#ifdef SCL_USE_MMS_STRING_
void CSclFileRead::GetFCDAType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &lntype,CDvmData *pDvmData)
#else
void CSclFileRead::GetFCDAType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, ST_CHAR *lntype,CDvmData *pDvmData)
#endif
{
	//fcda doname is empty
#ifdef SCL_USE_MMS_STRING_
	CString	dotype	= _T("");
	CString	datype = _T("");

	CString	fcdadodaName = _T("");

	if (mms_str_length(&sclfcda->doName)>0)
	{
		fcdadodaName = mms_string(&sclfcda->doName);
	}

	//fcda daname is empty
	if (mms_str_length(&sclfcda->daName)>0)
	{
		fcdadodaName.AppendFormat(_T("$%s"),mms_string(&sclfcda->daName));
	}

	//find dotype from scl_lntype
	FindDoType(sclinfo, sclfcda, lntype, dotype, fcdadodaName);

	//find datype from scl_dotype
	if (mms_str_length(&sclfcda->doName)>0)
	{
		FindDaType(sclinfo, sclfcda, dotype, datype, fcdadodaName,pDvmData);
	} 
	else
	{
		//find fcda do struct
		return;
	}

	//find final type from scl_datype
	if (mms_str_length(&sclfcda->daName)>0)
	{
		FindFinalType(sclinfo, sclfcda, datype, fcdadodaName);
	} 
	else
	{
		//find fcda da struct
		return;
	}
#else
	ST_CHAR	dotype		[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	datype		[MAX_IDENT_LEN + 1] = {0};

	ST_CHAR	fcdadodaName[MAX_IDENT_LEN + 1] = {0};

	if (strlen (sclfcda->doName))
	{
		strncpy (fcdadodaName, sclfcda->doName, strlen(sclfcda->doName) + 1);
	}

	//fcda daname is empty
	if (strlen (sclfcda->daName))
	{
		strcat (fcdadodaName, "$");
		strncat (fcdadodaName, sclfcda->daName, strlen(sclfcda->daName) + 1);
	}

	//find dotype from scl_lntype
	FindDoType(sclinfo, sclfcda, lntype, dotype, fcdadodaName);

	//find datype from scl_dotype
	if (strlen (sclfcda->doName))
	{
		FindDaType(sclinfo, sclfcda, dotype, datype, fcdadodaName,pDvmData);
	} 
	else
	{
		//find fcda do struct
		return;
	}

	//find final type from scl_datype
	if (strlen (sclfcda->daName))
	{
		FindFinalType(sclinfo, sclfcda, datype, fcdadodaName);
	} 
	else
	{
		//find fcda da struct
		return;
	}
#endif

	return ;
}

//find dotype from scl_lntype
#ifdef SCL_USE_MMS_STRING_
void CSclFileRead::FindDoType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &lntype, CString &dotype, CString &fcdadodaName)
#else
void CSclFileRead::FindDoType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *lntype, char *dotype, char *fcdadodaName)
#endif
{
	SCL_LNTYPE	*scl_lntype = NULL;
	SCL_DO		*scl_do = NULL;

	for (scl_lntype = (SCL_LNTYPE *)list_find_last((DBL_LNK *)sclinfo->lnTypeHead);
		scl_lntype != NULL;
		scl_lntype = (SCL_LNTYPE *)list_find_prev((DBL_LNK *)sclinfo->lnTypeHead, (DBL_LNK *)scl_lntype))
	{
#ifdef SCL_USE_MMS_STRING_
		if (lntype == mms_string(&scl_lntype->id))
		{
			CString doName = _T("");
			FindDelStr(fcdadodaName, doName);

			for (scl_do = (SCL_DO *)list_find_last((DBL_LNK *)scl_lntype->doHead);
				scl_do != NULL;
				scl_do = (SCL_DO *)list_find_prev((DBL_LNK *)scl_lntype->doHead, (DBL_LNK *)scl_do))
			{
				if (doName == mms_string(&scl_do->name)) //(0 == strcmp(mms_string(&scl_do->name), doName))
				{
					dotype = mms_string(&scl_do->type);
					break;
				}	
			}
			break;
		}
#else
		if (0 == strcmp(scl_lntype->id, lntype))
		{
			ST_CHAR doName[MAX_IDENT_LEN + 1] = {0};
			FindDelStr(fcdadodaName, doName);

			for (scl_do = (SCL_DO *)list_find_last((DBL_LNK *)scl_lntype->doHead);
				scl_do != NULL;
				scl_do = (SCL_DO *)list_find_prev((DBL_LNK *)scl_lntype->doHead, (DBL_LNK *)scl_do))
			{
				if (0 == strcmp(scl_do->name, doName))
				{
					strncpy (dotype, scl_do->type,  MAX_IDENT_LEN + 1);
					break;
				}	
			}
			break;
		}
#endif
	}
}

//find datype from scl_dotype
#ifdef SCL_USE_MMS_STRING_
void CSclFileRead::FindDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &dotype, CString &datype, CString &fcdadodaName)
#else
void CSclFileRead::FindDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype, char *datype, char *fcdadodaName)
#endif
{
	SCL_DOTYPE	*scl_dotype = NULL;
	SCL_DA		*scl_da = NULL;

	//not find dotype
	if (dotype.GetLength() <= 0)//(strlen(dotype) <= 0)
	{
#ifdef SCL_USE_MMS_STRING_
		if (mms_str_length(&sclfcda->type) <= 0)
		{
			mms_str_set(&sclfcda->type, "Struct");
		}
#else
		if (strlen(sclfcda->type) <= 0)
		{
			strcpy (sclfcda->type, "Struct");
		}
#endif
	}
	else
	{
		if (fcdadodaName.GetLength() <= 0)  //(strlen(fcdadodaName) <= 0)
		{
			FindDaStruct(sclinfo, sclfcda, dotype);
		} 
		else
		{
			for (scl_dotype = (SCL_DOTYPE *)list_find_last((DBL_LNK *)sclinfo->doTypeHead);
				scl_dotype != NULL;
				scl_dotype = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)sclinfo->doTypeHead, (DBL_LNK *)scl_dotype))
			{
#ifdef SCL_USE_MMS_STRING_
				if (dotype == mms_string(&scl_dotype->id)) //(0 == strcmp(mms_string(&scl_dotype->id), dotype))
				{
					CString daFstName = _T("");
					FindDelStr(fcdadodaName, daFstName);

					mms_str_copy(&sclfcda->DOType ,&scl_dotype->id);//zhow:2017.08.01
					mms_str_copy(&sclfcda->cdc ,&scl_dotype->cdc);//zhow:2017.08.01

					for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
						scl_da != NULL;
						scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
					{
						if (daFstName == mms_string(&scl_da->name)) //(0 == strcmp(mms_string(&scl_da->name), daFstName))
						{
							if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
							{
								CString	tdotype;
								tdotype = mms_string(&scl_da->type);

								FindDaType(sclinfo, sclfcda, tdotype, datype, fcdadodaName);
							}
							else//da type
							{
								if (0 == strcmp(mms_string(&scl_da->bType), "Struct"))
								{
									datype = mms_string(&scl_da->type);
								}
								else
								{
									mms_str_copy(&sclfcda->type, &scl_da->bType);
								}
							}	
							break;
						}
					}
					break;
				}
#else
				if (0 == strcmp(scl_dotype->id, dotype))
				{
					ST_CHAR daFstName[MAX_IDENT_LEN + 1] = {0};
					FindDelStr(fcdadodaName, daFstName);

					strncpy(sclfcda->DOType ,scl_dotype->id,MAX_IDENT_LEN+1 );//zhow:2017.08.01
					strncpy(sclfcda->cdc ,scl_dotype->cdc,MAX_CDC_LEN+1 );//zhow:2017.08.01

					for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
						scl_da != NULL;
						scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
					{
						if (0 == strcmp(scl_da->name, daFstName))
						{
							if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
							{
								ST_CHAR	tdotype[MAX_IDENT_LEN + 1] = {0};
								strncpy (tdotype, scl_da->type, MAX_IDENT_LEN + 1);

								FindDaType(sclinfo, sclfcda, tdotype, datype, fcdadodaName);
							}
							else//da type
							{
								if (0 == strcmp(scl_da->bType, "Struct"))
								{
									strncpy (datype, scl_da->type, MAX_IDENT_LEN + 1);
								}
								else
								{
									strncpy(sclfcda->type, scl_da->bType, MAX_IDENT_LEN + 1);
								}
							}	
							break;
						}
					}
					break;
				}
#endif
			}
		}
	}
}

#ifdef SCL_USE_MMS_STRING_
void CSclFileRead::FindDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &dotype, CString &datype, CString &fcdadodaName,CDvmData *pDvmData)
#else
void CSclFileRead::FindDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype, char *datype, char *fcdadodaName,CDvmData *pDvmData)
#endif
{
	SCL_DOTYPE	*scl_dotype = NULL;
	SCL_DA		*scl_da = NULL;

#ifdef SCL_USE_MMS_STRING_
	//not find dotype
	if (dotype.GetLength( ) >= 0) //(strlen(dotype) <= 0)
	{
		if (mms_str_length(&sclfcda->type) <= 0)
		{
			mms_str_set(&sclfcda->type, "Struct");
		}
	}
	else                
	{
		if (fcdadodaName.GetLength() <= 0) //(strlen(fcdadodaName) <= 0)
		{
			FindDaStruct(sclinfo, sclfcda, dotype,pDvmData);
		} 
		else
		{
			for (scl_dotype = (SCL_DOTYPE *)list_find_last((DBL_LNK *)sclinfo->doTypeHead);
				scl_dotype != NULL;
				scl_dotype = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)sclinfo->doTypeHead, (DBL_LNK *)scl_dotype))
			{
				if (dotype == mms_string(&scl_dotype->id) ) // (0 == strcmp(mms_string(&scl_dotype->id), dotype))
				{
					CString daFstName = _T("");
					FindDelStr(fcdadodaName, daFstName);

					for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
						scl_da != NULL;
						scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
					{
						if (daFstName == mms_string(&scl_da->name))
						{
							if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
							{
								CString	tdotype;
								tdotype = mms_string(&scl_da->type);

								FindDaType(sclinfo, sclfcda, tdotype, datype, fcdadodaName,pDvmData);
							} 
							else//da type
							{
								if (0 == strcmp(mms_string(&scl_da->bType), "Struct"))
								{
									datype = mms_string(&scl_da->type);
								}
								else
								{
									mms_str_copy(&sclfcda->type, &scl_da->bType);
									CDvmValue *pNew = new CDvmValue();
									pNew->m_strID=mms_string(&scl_da->name);
									pNew->m_strDataType=mms_string(&scl_da->bType);
									pDvmData->AddNewChild(pNew);
								}
							}	
							break;
						}
					}
					break;
				}
			}
		}
	}
#else
	if (strlen(dotype) <= 0)
	{
		if (strlen(sclfcda->type) <= 0)
		{
			strcpy (sclfcda->type, "Struct");
		}
	}
	else                
	{
		if (strlen(fcdadodaName) <= 0)
		{
			FindDaStruct(sclinfo, sclfcda, dotype,pDvmData);
		} 
		else
		{
			for (scl_dotype = (SCL_DOTYPE *)list_find_last((DBL_LNK *)sclinfo->doTypeHead);
				scl_dotype != NULL;
				scl_dotype = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)sclinfo->doTypeHead, (DBL_LNK *)scl_dotype))
			{
				if (0 == strcmp(scl_dotype->id, dotype))
				{
					ST_CHAR daFstName[MAX_IDENT_LEN + 1] = {0};
					FindDelStr(fcdadodaName, daFstName);

					for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
						scl_da != NULL;
						scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
					{
						if (0 == strcmp(scl_da->name, daFstName))
						{
							if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
							{
								ST_CHAR	tdotype[MAX_IDENT_LEN + 1] = {0};
								strncpy (tdotype, scl_da->type, MAX_IDENT_LEN + 1);

								FindDaType(sclinfo, sclfcda, tdotype, datype, fcdadodaName,pDvmData);
							} 
							else//da type
							{
								if (0 == strcmp(scl_da->bType, "Struct"))
								{
									strncpy (datype, scl_da->type, MAX_IDENT_LEN + 1);
								}
								else
								{
									strncpy(sclfcda->type, scl_da->bType, MAX_IDENT_LEN + 1);
									CDvmValue *pNew = new CDvmValue();
									pNew->m_strID=scl_da->name;
									pNew->m_strDataType=scl_da->bType;
									pDvmData->AddNewChild(pNew);
								}
							}	
							break;
						}
					}
					break;
				}
			}
		}
	}
#endif
}

#ifdef SCL_USE_MMS_STRING_
void CSclFileRead::FindDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &dotype)
#else
void CSclFileRead::FindDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype)
#endif
{
	SCL_DOTYPE	*scl_dotype = NULL;
	SCL_DA		*scl_da = NULL;

	//strncat(sclfcda->type, _T("<"), 2);

	for (scl_dotype = (SCL_DOTYPE *)list_find_last((DBL_LNK *)sclinfo->doTypeHead);
		scl_dotype != NULL;
		scl_dotype = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)sclinfo->doTypeHead, (DBL_LNK *)scl_dotype))
	{
#ifdef SCL_USE_MMS_STRING_
		if (dotype == mms_string(&scl_dotype->id) ) // (0 == strcmp(mms_string(&scl_dotype->id), dotype))
		{
			mms_str_copy(&sclfcda->DOType ,&scl_dotype->id);//zhow:2017.08.01
			mms_str_copy(&sclfcda->cdc ,&scl_dotype->cdc);//zhow:2017.08.01

// 			sclfcda->DOType = scl_dotype->id;//zhow:2017.08.01
// 			sclfcda->cdc = scl_dotype->cdc;//zhow:2017.08.01
			for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
				scl_da != NULL;
				scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
			{
				if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
				{
					CString	tdotype;
					tdotype = mms_string(&scl_da->type);

					FindDaStruct(sclinfo, sclfcda, tdotype);
				}
				else//da type
				{
					if (0 == strcmp(mms_string(&scl_da->bType), "Struct"))
					{
						CString datype;
						datype = mms_string(&scl_da->type);

						FindFinalStruct(sclinfo, sclfcda, datype);
					}
					else
					{
						mms_str_cat(&sclfcda->type, mms_string(&scl_da->bType));
						mms_str_cat(&sclfcda->type, ",");
					}
				}	
			}
			break;
		}
#else
		if (0 == strcmp(scl_dotype->id, dotype))
		{
			strncpy(sclfcda->DOType ,scl_dotype->id,MAX_IDENT_LEN+1 );//zhow:2017.08.01
			strncpy(sclfcda->cdc ,scl_dotype->cdc,MAX_CDC_LEN+1 );//zhow:2017.08.01

// 			sclfcda->DOType = scl_dotype->id;//zhow:2017.08.01
// 			sclfcda->cdc = scl_dotype->cdc;//zhow:2017.08.01
			for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
				scl_da != NULL;
				scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
			{
				if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
				{
					ST_CHAR	tdotype[MAX_IDENT_LEN + 1] = {0};
					strncpy (tdotype, scl_da->type, MAX_IDENT_LEN + 1);

					FindDaStruct(sclinfo, sclfcda, tdotype);
				}
				else//da type
				{
					if (0 == strcmp(scl_da->bType, "Struct"))
					{
						ST_CHAR datype[MAX_IDENT_LEN + 1] = {0};
						strncpy (datype, scl_da->type, MAX_IDENT_LEN + 1);

						FindFinalStruct(sclinfo, sclfcda, datype);
					}
					else
					{
						strncat(sclfcda->type, scl_da->bType, strlen(scl_da->bType));
						strncat(sclfcda->type, ",", 2);
					}
				}	
			}
			break;
		}
#endif
	}

	//sclfcda->type[strlen(sclfcda->type) - 1] = _T('>');
}

#ifdef SCL_USE_MMS_STRING_
void CSclFileRead::FindDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &dotype,CDvmData *pDvmData)
#else
void CSclFileRead::FindDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype,CDvmData *pDvmData)
#endif
{
	SCL_DOTYPE	*scl_dotype = NULL;
	SCL_DA		*scl_da = NULL;

	//strncat(sclfcda->type, _T("<"), 2);

	for (scl_dotype = (SCL_DOTYPE *)list_find_last((DBL_LNK *)sclinfo->doTypeHead);
		scl_dotype != NULL;
		scl_dotype = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)sclinfo->doTypeHead, (DBL_LNK *)scl_dotype))
	{
#ifdef SCL_USE_MMS_STRING_
		if (dotype == mms_string(&scl_dotype->id))//(0 == strcmp(mms_string(&scl_dotype->id), dotype))
		{
			for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
				scl_da != NULL;
				scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
			{
				if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
				{
					CString	tdotype;
					tdotype = mms_string(&scl_da->type);

					FindDaStruct(sclinfo, sclfcda, tdotype,pDvmData);
				}
				else//da type
				{
					if (0 == strcmp(mms_string(&scl_da->bType), "Struct"))
					{
						CString datype;
						datype = mms_string(&scl_da->type);

						FindFinalStruct(sclinfo, sclfcda, datype);
					}
					else
					{
						mms_str_cat(&sclfcda->type, mms_string(&scl_da->bType));
						mms_str_cat(&sclfcda->type, ",");
						CDvmValue *pNew = new CDvmValue();
						pNew->m_strID=mms_string(&scl_da->name);
						pNew->m_strDataType= mms_string(&scl_da->bType);
						pDvmData->AddNewChild(pNew);
					}
				}	
			}
			break;
		}
#else
		if (0 == strcmp(scl_dotype->id, dotype))
		{
			for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
				scl_da != NULL;
				scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
			{
				if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
				{
					ST_CHAR	tdotype[MAX_IDENT_LEN + 1] = {0};
					strncpy (tdotype, scl_da->type, MAX_IDENT_LEN + 1);

					FindDaStruct(sclinfo, sclfcda, tdotype,pDvmData);
				}
				else//da type
				{
					if (0 == strcmp(scl_da->bType, "Struct"))
					{
						ST_CHAR datype[MAX_IDENT_LEN + 1] = {0};
						strncpy (datype, scl_da->type, MAX_IDENT_LEN + 1);

						FindFinalStruct(sclinfo, sclfcda, datype);
					}
					else
					{
						strncat(sclfcda->type, scl_da->bType, strlen(scl_da->bType));
						strncat(sclfcda->type, ",", 2);
						CDvmValue *pNew = new CDvmValue();
						pNew->m_strID=scl_da->name;
						pNew->m_strDataType=scl_da->bType;
						pDvmData->AddNewChild(pNew);
					}
				}	
			}
			break;
		}
#endif
	}

	//sclfcda->type[strlen(sclfcda->type) - 1] = _T('>');
}

//find final type from scl_datype
#ifdef SCL_USE_MMS_STRING_
void CSclFileRead::FindFinalType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &datype, CString &fcdadodaName)
#else
void CSclFileRead::FindFinalType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *datype, char *fcdadodaName)
#endif
{
	SCL_DATYPE	*scl_datype = NULL; 
	SCL_BDA		*scl_bda = NULL;

#ifdef SCL_USE_MMS_STRING_
	CString		tdatype = _T("");

	if (datype.IsEmpty())
	{
		if (mms_str_length(&sclfcda->type) <= 0)
		{
			mms_str_set(&sclfcda->type, "Struct");
		}
	}
#else
	ST_CHAR		tdatype[MAX_IDENT_LEN + 1] = {0};

	if (strlen(datype) <= 0)
	{
		if (strlen(sclfcda->type) <= 0)
		{
			strcpy (sclfcda->type, "Struct");
		}
	}
#endif
	else
	{
#ifdef SCL_USE_MMS_STRING_
		if (fcdadodaName.IsEmpty())
#else
		if (strlen(fcdadodaName) <= 0)
#endif
		{
			FindFinalStruct(sclinfo, sclfcda, datype);
		}
		else
		{
			for (scl_datype = (SCL_DATYPE *)list_find_last((DBL_LNK *)sclinfo->daTypeHead);
				scl_datype != NULL;
				scl_datype = (SCL_DATYPE *)list_find_prev((DBL_LNK *)sclinfo->daTypeHead, (DBL_LNK *)scl_datype))
			{
#ifdef SCL_USE_MMS_STRING_
				if (datype == mms_string(&scl_datype->id))//(0 == strcmp(mms_string(&scl_datype->id), datype))
				{
					CString daFstName = _T("");
					FindDelStr(fcdadodaName, daFstName);

					for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)scl_datype->bdaHead);
						scl_bda != NULL;
						scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)scl_datype->bdaHead, (DBL_LNK *)scl_bda))
					{
						if (daFstName == mms_string(&scl_bda->name))
						{
							if (0 == strcmp(mms_string(&scl_bda->bType), "Struct"))
							{
								tdatype = mms_string(&scl_bda->type);
							}
							else
							{
								mms_str_copy(&sclfcda->type, &scl_bda->bType);
							}
							break;
						}
					}
					break;
				}
#else
				if (0 == strcmp(scl_datype->id, datype))
				{
					ST_CHAR daFstName[MAX_IDENT_LEN + 1] = {0};
					FindDelStr(fcdadodaName, daFstName);

					for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)scl_datype->bdaHead);
						scl_bda != NULL;
						scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)scl_datype->bdaHead, (DBL_LNK *)scl_bda))
					{
						if (0 == strcmp(scl_bda->name, daFstName))
						{
							if (0 == strcmp(scl_bda->bType, "Struct"))
							{
								strncpy (tdatype, scl_bda->type, MAX_IDENT_LEN + 1);
							}
							else
							{
								strncpy(sclfcda->type, scl_bda->bType, MAX_IDENT_LEN + 1);
							}
							break;
						}
					}
					break;
				}
#endif
			}

			FindFinalType(sclinfo, sclfcda, tdatype, fcdadodaName);
		}	
	}
}

#ifdef SCL_USE_MMS_STRING_
void CSclFileRead::FindFinalStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &datype)
#else
void CSclFileRead::FindFinalStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *datype)
#endif
{
	SCL_DATYPE	*scl_datype = NULL; 
	SCL_BDA		*scl_bda = NULL;

#ifdef SCL_USE_MMS_STRING_
	CString		tdatype= _T("");
	mms_str_cat(&sclfcda->type, "<");

	for (scl_datype = (SCL_DATYPE *)list_find_last((DBL_LNK *)sclinfo->daTypeHead);
		scl_datype != NULL;
		scl_datype = (SCL_DATYPE *)list_find_prev((DBL_LNK *)sclinfo->daTypeHead, (DBL_LNK *)scl_datype))
	{
		if (datype == mms_string(&scl_datype->id))
		{
			for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)scl_datype->bdaHead);
				scl_bda != NULL;
				scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)scl_datype->bdaHead, (DBL_LNK *)scl_bda))
			{
				if (0 == strcmp(mms_string(&scl_bda->bType), "Struct"))
				{
					tdatype = mms_string(&scl_bda->type);

					FindFinalStruct(sclinfo, sclfcda, tdatype);
				}
				else
				{
					mms_str_cat(&sclfcda->type, mms_string(&scl_bda->bType));
					mms_str_cat(&sclfcda->type, ",");
				}
			}

			break;
		}
	}
	
	char *pzfType = mms_string(&sclfcda->type);
	pzfType[mms_str_length(&sclfcda->type) - 1] = _T('>');
#else
	ST_CHAR		tdatype[MAX_IDENT_LEN + 1] = {0};

	strncat(sclfcda->type, "<", 2);

	for (scl_datype = (SCL_DATYPE *)list_find_last((DBL_LNK *)sclinfo->daTypeHead);
		scl_datype != NULL;
		scl_datype = (SCL_DATYPE *)list_find_prev((DBL_LNK *)sclinfo->daTypeHead, (DBL_LNK *)scl_datype))
	{
		if (0 == strcmp(scl_datype->id, datype))
		{
			for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)scl_datype->bdaHead);
				scl_bda != NULL;
				scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)scl_datype->bdaHead, (DBL_LNK *)scl_bda))
			{
				if (0 == strcmp(scl_bda->bType, "Struct"))
				{
					strncpy (tdatype, scl_bda->type, MAX_IDENT_LEN + 1);

					FindFinalStruct(sclinfo, sclfcda, tdatype);
				}
				else
				{
					strncat(sclfcda->type, scl_bda->bType, strlen(scl_bda->bType));
					strncat(sclfcda->type, ",", 2);
				}
			}

			break;
		}
	}

	sclfcda->type[strlen(sclfcda->type) - 1] = _T('>');
#endif
}

// find extref ld/ln/do name from sclextref;
// sclextref->inAddr: ldname/lnname.doname, doname: ***.***.***,(dot number is 0,1,......);
void CSclFileRead::FindextrefName(SCL_EXTREF *sclextref, char *ldName, 
								  char *lnName, char *doName ,char *daName)
{
	char *pch = NULL; 
	bool bIndex = false;

#ifdef SCL_USE_MMS_STRING_
	strncpy (ldName, mms_string(&sclextref->inAddr), MAX_IDENT_LEN + 1);
#else
	strncpy (ldName, sclextref->inAddr, MAX_IDENT_LEN + 1);
#endif

	for (pch = ldName; *pch; pch++)
	{
		if(*pch == _T(':'))
		{
			pch++;
			bIndex = true ;
		}

		if (bIndex)
		{
			*ldName = *pch;
			if (*pch == _T('/'))
			{
				*ldName = _T('\0');
			}
			ldName++;
		}
		if (*pch == _T('/'))
		{
			*pch++ = _T('\0');
			strcpy (lnName, pch);
			break;
		}
	}

	for (pch = lnName; *pch; pch++)
	{
		if (*pch == _T('.'))
		{
			*pch++ = _T('\0');
			strcpy (doName, pch);
			break;
		}
	}

	for (pch = doName; *pch; pch++)
	{
		if (*pch == _T('.'))
		{
			*pch++ = _T('\0');
			strcpy (daName, pch);
			break;
		}
	}
}

//replace dot to dollar in string srcStr
void CSclFileRead::ReplaceDotToDollar(char *srcStr)
{
	for (; *srcStr; srcStr++)
	{
		if (*srcStr == _T('.'))
		{
			*srcStr = _T('$');
		}
	}
}

//if srcStr have dot, remove dot and the string behind dot, 
//and link dU at the end of srcStr
void CSclFileRead::ConfigDescName(char *srcStr)
{
	char *pch = srcStr;

	for (; *pch; pch++)
	{
		if (*pch == _T('.'))
		{
			*pch = _T('$');
		}
	}
	strcat (srcStr, "$dU");
}

//if srcStr have dot, replace the dot to \0, 
//and link desc at the end of srcStr
void CSclFileRead::ConfigDoiName(char *srcStr)
{
	char *pch = srcStr;

	for (; *pch; pch++)
	{
		if (*pch == _T('.'))
		{
			*pch = 0;
		}
	}
	strcat (srcStr, "$desc");
}

void CSclFileRead::ConfigDoiName(CString &srcStr)
{
	long nIndex = srcStr.Find('.');

	if (nIndex >= 0)
	{
		srcStr = srcStr.Left(nIndex);
	}

	srcStr += "$desc";
}

// find string before the first $/. form srcStr, remove the string and the first $/. from srcStr
// if find, return true, findStr = find string, srcStr = the string after $/.;
// else return false, findStr = srcStr, srcStr = {};
bool CSclFileRead::FindDelStr(char *srcStr, char *findStr)
{
	char *pch = srcStr;

	for (; *pch; pch++)
	{
		if ((*pch == _T('$')) || (*pch == _T('.')))
		{
			*pch++ = _T('\0');

			strcpy(findStr, srcStr);
			strcpy(srcStr, pch);

			return true;
		}
	}

	strcpy(findStr, srcStr);
	strcpy(srcStr, "\0");
	return false;
}

bool CSclFileRead::FindDelStr(CString &srcStr, CString &findStr)
{
	long nIndex = srcStr.Find('$');

	if (nIndex == -1)
	{
		nIndex = srcStr.Find('.');
	}

	if (nIndex != -1)
	{
		findStr = srcStr.Left(nIndex);
		srcStr = srcStr.Mid(nIndex+1);
		return true;
	} 

	findStr = srcStr;
	srcStr = _T("");	
	return false;
}

bool CSclFileRead::FindContinueDelStr(char *srcStr, char *findStr)
{
	char *pch = srcStr;

	for (; *pch; pch++)
	{
		if ((*pch == _T('$')) || (*pch == _T('.')))
		{
			*pch++ = _T('\0');

			strcat(findStr,"$");
			strcat(findStr,srcStr);
			strcpy(srcStr, pch);

			return true;
		}
	}

	strcpy(findStr, srcStr);
	strcpy(srcStr, "\0");
	return false;
}

#include "../../../Module/API/StringConvert/String_Utf8_To_Gbk.h"
bool CSclFileRead::UTF8ToMultiByte(char *srcStr)
{
	ST_INT iTextLen = 0;
	unsigned char wszGBK[512] = {0};
	int nLen = 0;
	//memset(wszGBK, 0, 256);
	iTextLen = utf8_to_gbk((unsigned char*)srcStr, strlen(srcStr), (unsigned char*)wszGBK, &nLen);
	memcpy(srcStr,wszGBK , nLen);
	srcStr[nLen] = 0;
// 	iTextLen = MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, NULL,0); 
// 	memset(wszGBK, 0, iTextLen * 2 + 2); 
// 	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, (LPWSTR)wszGBK, iTextLen); 
// 
// 	iTextLen = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL); 
// 	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, srcStr, iTextLen, NULL, NULL); 

	return true;
}

bool CSclFileRead::UTF8ToMultiByte(CString &srcStr)
{
// 	ST_INT iTextLen = 0;
// 	unsigned short wszGBK[256] = {0};
// 
// 	memset(wszGBK, 0, 256);
// 
// 	iTextLen = MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, NULL,0); 
// 	memset(wszGBK, 0, iTextLen * 2 + 2); 
// 	MultiByteToWideChar(CP_UTF8, 0, (LPCTSTR)srcStr, -1, (LPWSTR)wszGBK, iTextLen); 
// 
// 	iTextLen = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, NULL, 0, NULL, NULL); 
// 	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGBK, -1, (LPSTR)(LPCSTR)srcStr, iTextLen, NULL, NULL); 

	return true;
}


void CSclFileRead::ReadGSSVControl(SCL_INFO *sclinfo, CSclIed *pIed/*CString iedStr*/, BOOL bGsIn, BOOL bGsOut, BOOL bSmvIn, BOOL bSmvOut)
{
	SCL_IED	*scl_ied = NULL;
	SCL_AP *scl_ap = NULL;
	SCL_LD *scl_ld = NULL;
	SCL_LN *scl_ln = NULL;

	scl_ied = GetRefIED(pIed);
	ASSERT (scl_ied != NULL);

	// 	for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)sclinfo->iedHead);
	// 		scl_ied != NULL;
	// 		scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)sclinfo->iedHead, (DBL_LNK *)scl_ied))
	{
		//		if (0 == strcmp(pIed->m_strID.GetString(), scl_ied->name))
		{
			for (scl_ap = (SCL_AP *)list_find_last((DBL_LNK *)scl_ied->apHead);
				scl_ap != NULL;
				scl_ap = (SCL_AP *)list_find_prev((DBL_LNK *)scl_ied->apHead, (DBL_LNK *)scl_ap))
			{
#ifdef SCL_USE_MMS_STRING_
				CString apName(mms_string(&scl_ap->name));
#else
				CString apName(scl_ap->name);
#endif

				if ((scl_ap->desc) && (strlen(scl_ap->desc) > 0))
				{
					apName = apName + "--" + scl_ap->desc;
				}

				for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)scl_ap->ldHead);
					scl_ld != NULL;
					scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ap->ldHead, (DBL_LNK *)scl_ld))
				{
					for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
						scl_ln != NULL;
						scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
					{
						ST_CHAR lnName	[MAX_TYPE_LEN + 1] = {0};
						//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
						//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
						//strncat (lnName, scl_ln->inst, MAX_IDENT_LEN + 1 - strlen(lnName));
						scl_get_ln_name(scl_ln, lnName);

						//if (0 == strcmp(_strupr(_strdup(lnName)), _T("LLN0")))
						if (0 == stricmp(lnName, _T("LLN0")))
						{
#ifdef SCL_USE_MMS_STRING_
							if (bGsOut)//ClickType_GOOSE_Outputs == m_iClickType)
							{
								FindGSOutControl(sclinfo, scl_ln, mms_string(&scl_ied->name), 
									apName.GetString(), mms_string(&scl_ld->inst),scl_ld->desc, lnName, pIed->GetGsOuts());//new单个的控制块，并将相关参数MAC、AppID等等写入;
							} 
							/*else*/ 
							if (bSmvOut)//ClickType_SMV_Outputs == m_iClickType)
							{
								FindSVOutControl(sclinfo, scl_ln, mms_string(&scl_ied->name), 
									apName.GetString(), mms_string(&scl_ld->inst),scl_ld->desc, lnName, pIed->GetSmvOuts());//new单个的控制块，并将相关参数MAC、AppID等等写入;
							} 
#else
							if (bGsOut)//ClickType_GOOSE_Outputs == m_iClickType)
							{
								FindGSOutControl(sclinfo, scl_ln, scl_ied->name, 
									apName.GetString(), scl_ld->inst,scl_ld->desc, lnName, pIed->GetGsOuts());//new单个的控制块，并将相关参数MAC、AppID等等写入;
							} 
							/*else*/ 
							if (bSmvOut)//ClickType_SMV_Outputs == m_iClickType)
							{
								FindSVOutControl(sclinfo, scl_ln, scl_ied->name, 
									apName.GetString(), scl_ld->inst,scl_ld->desc, lnName, pIed->GetSmvOuts());//new单个的控制块，并将相关参数MAC、AppID等等写入;
							} 
#endif
							/*else */
							if (bGsIn)//ClickType_GOOSE_Inputs == m_iClickType || ClickType_SMV_Inputs == m_iClickType)
							{
								SCL_NODE_PATH scl_path;
								_scl_init_node_path(scl_path, scl_ied, scl_ap, scl_ld, scl_ln);
								FindGSSVInputs(sclinfo, scl_ln, pIed->GetGsIns(), scl_path);
							} 											

							if (bSmvIn)//ClickType_GOOSE_Inputs == m_iClickType || ClickType_SMV_Inputs == m_iClickType)
							{
								SCL_NODE_PATH scl_path;
								_scl_init_node_path(scl_path, scl_ied, scl_ap, scl_ld, scl_ln);
								FindGSSVInputs(sclinfo, scl_ln, pIed->GetSmvIns(), scl_path);
							} 											

							break;
						}
					}
				}
			}
			//break;
		}
	}

	//在此处将所有控制块都添加完毕，并将控制块的所有通道信息添加进去；
	ReadGSSVChannels(pIed->GetGsOuts());
	ReadGSSVChannels(pIed->GetSmvIns());
	ReadGSSVChannels(pIed->GetGsIns());
	ReadGSSVChannels(pIed->GetSmvOuts());

}

void CSclFileRead::FindGSSVInputs(SCL_INFO *sclinfo, SCL_LN *sclln, CSclCtrls *pCtrls, SCL_NODE_PATH &scl_path)
{
	SCL_INPUTS		*scl_inputs = NULL;
	SCL_EXTREF		*scl_extref = NULL;

	std::list<CString>	list_ied;
	std::list<CString>	list_extref;

	for (scl_inputs = (SCL_INPUTS *)list_find_last((DBL_LNK *)sclln->inputsHead);
		scl_inputs != NULL;
		scl_inputs = (SCL_INPUTS *)list_find_prev((DBL_LNK *)sclln->inputsHead, (DBL_LNK *)scl_inputs))
	{
		for (scl_extref = (SCL_EXTREF *)list_find_last((DBL_LNK *)scl_inputs->extrefHead);
			scl_extref != NULL;
			scl_extref = (SCL_EXTREF *)list_find_prev((DBL_LNK *)scl_inputs->extrefHead, (DBL_LNK *)scl_extref))
		{
#ifdef SCL_USE_MMS_STRING_
			if (mms_str_length(&scl_extref->domName) <= 0)
			{
				continue;
			}

			CString extrefname(_T(""));
			extrefname.Format(_T("%s%s/%s%s%s"), mms_string(&scl_extref->domName), 
				mms_string(&scl_extref->ldInst),	mms_string(&scl_extref->prefix), 
				mms_string(&scl_extref->lnClass), mms_string(&scl_extref->lnInst));


			if (mms_str_length(&scl_extref->doName)>0)
			{
				extrefname = extrefname + _T(".") + CString(mms_string(&scl_extref->doName));
			}
			if (mms_str_length(&scl_extref->daName)>0)
			{
				extrefname = extrefname + _T(".") + CString(mms_string(&scl_extref->daName));
			}
			list_extref.push_back(extrefname);

			if (list_ied.empty())
			{
				list_ied.push_back(CString(mms_string(&scl_extref->domName)));
			}
			else
			{
				std::list<CString>::iterator iter = list_ied.begin();
				std::list<CString>::iterator iend = list_ied.end();
				for(; iter != iend; iter++)
				{
					if (*iter == mms_string(&scl_extref->domName))
					{
						break;
					}
				}

				if (iter == iend)
				{
					list_ied.push_back(CString(mms_string(&scl_extref->domName)));
				}
			}
#else
			if (strlen(scl_extref->domName) <= 0)
			{
				continue;
			}

			CString extrefname(_T(""));
			extrefname.Format(_T("%s%s/%s%s%s"), scl_extref->domName, 
				scl_extref->ldInst,	scl_extref->prefix, 
				scl_extref->lnClass, scl_extref->lnInst);


			if (strlen(scl_extref->doName))
			{
				extrefname = extrefname + _T(".") + CString(scl_extref->doName);
			}
			if (strlen(scl_extref->daName))
			{
				extrefname = extrefname + _T(".") + CString(scl_extref->daName);
			}
			list_extref.push_back(extrefname);

			if (list_ied.empty())
			{
				list_ied.push_back(CString(scl_extref->domName));
			}
			else
			{
				std::list<CString>::iterator iter = list_ied.begin();
				std::list<CString>::iterator iend = list_ied.end();
				for(; iter != iend; iter++)
				{
					if (*iter == scl_extref->domName)
					{
						break;
					}
				}

				if (iter == iend)
				{
					list_ied.push_back(CString(scl_extref->domName));
				}
			}
#endif
		}
	}

	if (!list_ied.empty())
	{
		FindGSSVInControl(sclinfo, &list_ied, &list_extref, pCtrls, scl_path);
	}
}

void CSclFileRead::FindGSSVInControl(SCL_INFO *sclinfo, std::list<CString> *listied, 
									 std::list<CString> *listextref, CSclCtrls *pCtrls, SCL_NODE_PATH &scl_path)
{
	SCL_IED		*scl_ied = NULL;
	SCL_AP		*scl_ap = NULL;
	SCL_LD		*scl_ld = NULL;
	SCL_LN		*scl_ln = NULL;

	for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)sclinfo->iedHead);
		scl_ied != NULL;
		scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)sclinfo->iedHead, (DBL_LNK *)scl_ied))
	{
		std::list<CString>::iterator iter = listied->begin();
		std::list<CString>::iterator iend = listied->end();
		for(; iter != iend; iter++)
		{
#ifdef SCL_USE_MMS_STRING_
			if (*iter == mms_string(&scl_ied->name))
#else
			if (*iter == scl_ied->name)
#endif
			{
				break;
			}
		}
		if (iter == iend)
		{
// 			if (scl_IsGsIns(pCtrls))
// 			{//GOOSE in
// 				FindGSINControl(sclinfo, scl_ln, scl_ied->name, scl_ied->desc, apName.GetString(), 
// 					scl_ld->inst, lnName, listied, listextref, (CSclCtrlsGsIn*)pCtrls, scl_path);
// 			} 
// 			else  if (scl_IsSmvIns(pCtrls))
// 			{//sv in (ClickType_SMV_Inputs == m_iClickType)
// 				FindSVINControl(sclinfo, scl_ln, scl_ied->name, scl_ied->desc, apName.GetString(), 
// 					scl_ld->inst, lnName, listied, listextref, (CSclCtrlsSmvIn*)pCtrls, scl_path);
// 			}

			continue;
		}

		for (scl_ap = (SCL_AP *)list_find_last((DBL_LNK *)scl_ied->apHead);
			scl_ap != NULL;
			scl_ap = (SCL_AP *)list_find_prev((DBL_LNK *)scl_ied->apHead, (DBL_LNK *)scl_ap))
		{

#ifdef SCL_USE_MMS_STRING_
			CString apName(mms_string(&scl_ap->name));
#else
			CString apName(scl_ap->name);
#endif

			if ((scl_ap->desc) && (strlen(scl_ap->desc) > 0))
			{
				apName = apName + _T("--") + scl_ap->desc;
			}

			for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)scl_ap->ldHead);
				scl_ld != NULL;
				scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ap->ldHead, (DBL_LNK *)scl_ld))
			{
				for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
					scl_ln != NULL;
					scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
				{
					ST_CHAR lnName[MAX_TYPE_LEN + 1] = {0};
					//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
					//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
					//strncat (lnName, scl_ln->inst, MAX_IDENT_LEN + 1 - strlen(lnName));
					scl_get_ln_name(scl_ln, lnName);

					//if (0 != strcmp(_strupr(_strdup(lnName)), _T("LLN0")))
					if (0 != stricmp(lnName, _T("LLN0")))
					{
						continue;
					}

					//if (ClickType_GOOSE_Inputs == m_iClickType)
					if (scl_IsGsIns(pCtrls))
					{//GOOSE in
#ifdef SCL_USE_MMS_STRING_
						FindGSINControl(sclinfo, scl_ln, mms_string(&scl_ied->name), scl_ied->desc, apName.GetString(), 
							mms_string(&scl_ld->inst),scl_ld->desc, lnName, listied, listextref, (CSclCtrlsGsIn*)pCtrls, scl_path);
					} 
					else  if (scl_IsSmvIns(pCtrls))
					{//sv in (ClickType_SMV_Inputs == m_iClickType)
						FindSVINControl(sclinfo, scl_ln, mms_string(&scl_ied->name), scl_ied->desc, apName.GetString(), 
							mms_string(&scl_ld->inst),scl_ld->desc, lnName, listied, listextref, (CSclCtrlsSmvIn*)pCtrls, scl_path);
#else
						FindGSINControl(sclinfo, scl_ln, scl_ied->name, scl_ied->desc, apName.GetString(), 
							scl_ld->inst,scl_ld->desc, lnName, listied, listextref, (CSclCtrlsGsIn*)pCtrls, scl_path);
					} 
					else  if (scl_IsSmvIns(pCtrls))
					{//sv in (ClickType_SMV_Inputs == m_iClickType)
						FindSVINControl(sclinfo, scl_ln, scl_ied->name, scl_ied->desc, apName.GetString(), 
							scl_ld->inst,scl_ld->desc, lnName, listied, listextref, (CSclCtrlsSmvIn*)pCtrls, scl_path);
#endif
					}
					break;
				}
			}
		}
	}
}

void CSclFileRead::FindGSINControl(SCL_INFO *sclinfo, SCL_LN *sclln, const char *iedName, 
								   const char *iedDesc, const char *apName, const char *ldName, const char *ldDesc, const char *lnName, 
								   std::list<CString> *listied, std::list<CString> *listextref, CSclCtrlsGsIn *pGsIns
								   , SCL_NODE_PATH &scl_path)
{
	SCL_GCB		*scl_gcb = NULL;
	SCL_DATASET	*scl_dataset = NULL;

	for (scl_gcb = (SCL_GCB *)list_find_last((DBL_LNK *)sclln->gcbHead);
		scl_gcb != NULL;
		scl_gcb = (SCL_GCB *)list_find_prev((DBL_LNK *)sclln->gcbHead, (DBL_LNK *)scl_gcb))
	{
		if(scl_gcb->isGoose == SD_FALSE)
		{
			continue;
		}

#ifdef SCL_USE_MMS_STRING_
		if (pGsIns->IsExist(iedName, ldName, lnName, mms_string(&scl_gcb->datSet)))
		{
			continue;
		}

		if (!IsOutGSSVHaveInGSSVChannel(sclln, mms_string(&scl_gcb->datSet), iedName, listextref))
		{
			continue;
		}
#else
		if (pGsIns->IsExist(iedName, ldName, lnName, scl_gcb->datSet))
		{
			continue;
		}

		if (!IsOutGSSVHaveInGSSVChannel(sclln, scl_gcb->datSet, iedName, listextref))
		{
			continue;
		}
#endif

		CSclCtrlGsIn *pNew = new CSclCtrlGsIn();
		pGsIns->AddNewChild(pNew);

		CString iedStr(iedName);
		if (iedDesc && (strlen(iedDesc) > 0))
		{
			iedStr = iedStr + _T("--") + CString(iedDesc);
		}

		pNew->m_strName  = iedStr;
		pNew->m_strIedID = iedName;
		pNew->m_strIedDesc = iedStr;
		pNew->apName = apName;

		pNew->m_strExLDdesc = ldDesc;
		pNew->m_strLDdesc = scl_path.scl_ld->desc;
		pNew->m_strExIedDesc = iedStr;

		for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)sclln->datasetHead);
			scl_dataset != NULL;
			scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)sclln->datasetHead, (DBL_LNK *)scl_dataset))
		{
#ifdef SCL_USE_MMS_STRING_
			if((0 == mms_str_cmp(&scl_gcb->datSet, &scl_dataset->name))
#else
			if((0 == strcmp(scl_gcb->datSet, scl_dataset->name))
#endif
				&& (scl_dataset->desc)
				&& (strlen(scl_dataset->desc) > 0))
			{
				pNew->m_strDataSetDesc = scl_dataset->desc;
				break;
			}
		}

#ifdef SCL_USE_MMS_STRING_
		pNew->gocbref = mms_string(&scl_gcb->name);//.Format(_T("%s%s/%s$GO$%s"), iedName, ldName, lnName, scl_gcb->name);
		pNew->m_strgocbRef.Format(_T("%s%s/%s$GO$%s"), iedName, ldName, lnName, mms_string(&scl_gcb->name));
		pNew->m_strID = mms_string(&scl_gcb->name);

		pNew->ldName = ldName;
		pNew->lnName = lnName;
		pNew->m_strDataSet = mms_string(&scl_gcb->datSet);
		pNew->m_strDataSetPath.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, mms_string(&scl_gcb->datSet));

		pNew->m_strGooseId = mms_string(&scl_gcb->appID);

		ST_CHAR lnName2	[MAX_TYPE_LEN + 1] = {0};
		scl_get_ln_name(scl_path.scl_ln, lnName2);
		pNew->ldName_own = mms_string(&scl_path.scl_ld->inst);
		pNew->lnName_own = lnName2;
		pNew->apName_own = mms_string(&scl_path.scl_ap->name);
		pNew->m_dwVersion = scl_gcb->confRev;

		FindGSConnectAP(sclinfo, iedName, apName, ldName, mms_string(&scl_gcb->name), pNew);
#else
		pNew->gocbref = scl_gcb->name;//.Format(_T("%s%s/%s$GO$%s"), iedName, ldName, lnName, scl_gcb->name);
		pNew->m_strgocbRef.Format(_T("%s%s/%s$GO$%s"), iedName, ldName, lnName, scl_gcb->name);
		pNew->m_strID = scl_gcb->name;

		pNew->ldName = ldName;
		pNew->lnName = lnName;
		pNew->m_strDataSet = scl_gcb->datSet;
		pNew->m_strDataSetPath.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, scl_gcb->datSet);

		pNew->m_strGooseId = scl_gcb->appID;

		ST_CHAR lnName2	[MAX_TYPE_LEN + 1] = {0};
		scl_get_ln_name(scl_path.scl_ln, lnName2);
		pNew->ldName_own = scl_path.scl_ld->inst;
		pNew->lnName_own = lnName2;
		pNew->apName_own = scl_path.scl_ap->name;
		pNew->m_dwVersion = scl_gcb->confRev;

		FindGSConnectAP(sclinfo, iedName, apName, ldName, scl_gcb->name, pNew);
#endif
	}
}

void CSclFileRead::FindSVINControl(SCL_INFO *sclinfo, SCL_LN *sclln, const char *iedName, 
								  const  char *iedDesc, const char *apName, const char *ldName, const char *ldDesc, const char *lnName, 
								   std::list<CString> *listied,  std::list<CString> *listextref, CSclCtrlsSmvIn *pSmvIns
								   , SCL_NODE_PATH &scl_path)
{
	SCL_SVCB	*scl_svcb = NULL;
	SCL_DATASET *scl_dataset = NULL;

	for (scl_svcb = (SCL_SVCB *)list_find_last((DBL_LNK *)sclln->svcbHead);
		scl_svcb != NULL;
		scl_svcb = (SCL_SVCB *)list_find_prev((DBL_LNK *)sclln->svcbHead, (DBL_LNK *)scl_svcb))
	{
		//去掉重复control
		// 		CString dataset(_T(""));
		// 		dataset.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, scl_svcb->datSet);
		// 		int count = m_LControl.GetItemCount();
		// 	
		// 		int i = 0;
		// 		for (; i < count; i++)
		// 		{
		// 			if (m_LControl.GetItemText(i, 7) == dataset)
		// 			{
		// 				break;
		// 			}
		// 		}
		// 		if (i < count)
		// 		{
		// 			continue;
		// 		}
#ifdef SCL_USE_MMS_STRING_
		if (pSmvIns->IsExist(iedName, ldName, lnName, mms_string(&scl_svcb->datSet)))
		{
			continue;
		}

		if (!IsOutGSSVHaveInGSSVChannel(sclln, mms_string(&scl_svcb->datSet), iedName, listextref))
		{
			continue;
		}
#else
		if (pSmvIns->IsExist(iedName, ldName, lnName, scl_svcb->datSet))
		{
			continue;
		}

		if (!IsOutGSSVHaveInGSSVChannel(sclln, scl_svcb->datSet, iedName, listextref))
		{
			continue;
		}
#endif

		CSclCtrlSmvIn *pNew = new CSclCtrlSmvIn();
		pSmvIns->AddNewChild(pNew);

		CString iedStr(iedName);
		if ((iedDesc) && (strlen(iedDesc) > 0))
		{
			iedStr = iedStr + _T("--") + CString(iedDesc);
		}

		pNew->m_strName  = iedStr;
		pNew->iedExtName = iedName;
		pNew->iedStr = iedStr;//m_LControl.SetItemText(count, 3, iedStr);
		pNew->apName = apName;//m_LControl.SetItemText(count, 4, apName);

		pNew->m_strExLDdesc = ldDesc;
		pNew->m_strLDdesc = scl_path.scl_ld->desc;
		pNew->m_strExIedDesc = iedStr;

		for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)sclln->datasetHead);
			scl_dataset != NULL;
			scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)sclln->datasetHead, (DBL_LNK *)scl_dataset))
		{
#ifdef SCL_USE_MMS_STRING_
			if((0 == mms_str_cmp(&scl_svcb->datSet, &scl_dataset->name))
#else
			if((0 == strcmp(scl_svcb->datSet, scl_dataset->name))
#endif
				&& (scl_dataset->desc)
				&& (strlen(scl_dataset->desc) > 0))
			{
				//m_LControl.SetItemText(count, 5, scl_dataset->desc);
				pNew->m_strDataSetDesc = scl_dataset->desc;
				break;
			}
		}

		// 		CString smprate(_T(""));
		// 		smprate.Format(_T("%d"), scl_svcb->smpRate);
		// 		m_LControl.SetItemText(count, 6, smprate);
		pNew->scl_svcb_smpRate = scl_svcb->smpRate;
#ifdef SCL_USE_MMS_STRING_
		pNew->m_strDataSet = mms_string(&scl_svcb->datSet);//dataset;
#else
		pNew->m_strDataSet = scl_svcb->datSet;//dataset;
#endif
		pNew->ldName = ldName;
		pNew->lnName = lnName;
		//m_LControl.SetItemText(count, 7, dataset);

#ifdef SCL_USE_MMS_STRING_
		pNew->m_strSVID = mms_string(&scl_svcb->smvID);
		pNew->m_strID = mms_string(&scl_svcb->smvID);
#else
		pNew->m_strSVID = scl_svcb->smvID;
		pNew->m_strID = scl_svcb->smvID;
#endif
		//m_LControl.SetItemText(count, 8, scl_svcb->smvID);

		// 		CString nofasdu(_T(""));
		// 		nofasdu.Format(_T("%d"), scl_svcb->nofASDU);
		// 		m_LControl.SetItemText(count, 9, nofasdu);
		pNew->scl_svcb_nofASDU = scl_svcb->nofASDU;

		pNew->scl_svcb_confRev = scl_svcb->confRev;

		ST_CHAR lnName2	[MAX_TYPE_LEN + 1] = {0};
		scl_get_ln_name(scl_path.scl_ln, lnName2);

#ifdef SCL_USE_MMS_STRING_
		pNew->ldName_own = mms_string(&scl_path.scl_ld->inst);
		pNew->lnName_own = lnName2;
		//pNew->scl_datset_own = ;
		pNew->apName_own = mms_string(&scl_path.scl_ap->name);

		FindSVConnectAP(sclinfo, iedName, apName, ldName, mms_string(&scl_svcb->name), pNew);
#else
		pNew->ldName_own = scl_path.scl_ld->inst;
		pNew->lnName_own = lnName2;
		//pNew->scl_datset_own = ;
		pNew->apName_own = scl_path.scl_ap->name;

		FindSVConnectAP(sclinfo, iedName, apName, ldName, scl_svcb->name, pNew);
#endif
	}
}

bool CSclFileRead::IsOutGSSVHaveInGSSVChannel(SCL_LN *sclln, const char *dataset, const char *iedName,
											  std::list<CString> *listextref)
{
	SCL_DATASET	*scl_dataset = NULL;
	SCL_FCDA	*scl_fcda = NULL;

	for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)sclln->datasetHead);
		scl_dataset != NULL;
		scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)sclln->datasetHead, (DBL_LNK *)scl_dataset))
	{
#ifdef SCL_USE_MMS_STRING_
		if(0 != strcmp(dataset, mms_string(&scl_dataset->name)))
		{
			continue;
		}

		for (scl_fcda = (SCL_FCDA *)list_find_last((DBL_LNK *)scl_dataset->fcdaHead);
			scl_fcda != NULL;
			scl_fcda = (SCL_FCDA *)list_find_prev((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
		{
			CString fcdaname(_T(""));
			fcdaname.Format(_T("%s%s/%s%s%s"), iedName, 
				mms_string(&scl_fcda->ldInst), mms_string(&scl_fcda->prefix), 
				mms_string(&scl_fcda->lnClass), mms_string(&scl_fcda->lnInst));
			if (mms_str_length(&scl_fcda->doName)>0)
			{
				fcdaname = fcdaname + _T(".") + CString(mms_string(&scl_fcda->doName));
			}
			if (mms_str_length(&scl_fcda->daName)>0)
			{
				fcdaname = fcdaname + _T(".") + CString(mms_string(&scl_fcda->daName));
			}
#else
		if(0 != strcmp(dataset, scl_dataset->name))
		{
			continue;
		}

		for (scl_fcda = (SCL_FCDA *)list_find_last((DBL_LNK *)scl_dataset->fcdaHead);
			scl_fcda != NULL;
			scl_fcda = (SCL_FCDA *)list_find_prev((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
		{
			CString fcdaname(_T(""));
			fcdaname.Format(_T("%s%s/%s%s%s"), iedName, 
				scl_fcda->ldInst, scl_fcda->prefix, 
				scl_fcda->lnClass, scl_fcda->lnInst);
			if (strlen(scl_fcda->doName))
			{
				fcdaname = fcdaname + _T(".") + CString(scl_fcda->doName);
			}
			if (strlen(scl_fcda->daName))
			{
				fcdaname = fcdaname + _T(".") + CString(scl_fcda->daName);
			}
#endif

			std::list<CString>::iterator iter = listextref->begin();
			std::list<CString>::iterator iend = listextref->end();
			for(; iter != iend; iter++)
			{
				if (*iter == fcdaname)
				{
					break;
				}
			}

			if (iter != iend)
			{
				return true;
			}
		}
	}

	return false;
}

void CSclFileRead::FindGSOutControl(SCL_INFO *sclinfo, SCL_LN *sclln, const char *iedName, 
									const char *apName, const  char *ldName, const char *ldDesc, const char *lnName, CSclCtrlsGsOut *pGsOuts)
{
	SCL_GCB		*scl_gcb = NULL;
	SCL_DATASET	*scl_dataset = NULL;

	for (scl_gcb = (SCL_GCB *)list_find_last((DBL_LNK *)sclln->gcbHead);
		scl_gcb != NULL;
		scl_gcb = (SCL_GCB *)list_find_prev((DBL_LNK *)sclln->gcbHead, (DBL_LNK *)scl_gcb))
	{
		if (SD_FALSE == scl_gcb->isGoose)
		{
			continue;
		}

		// 		int count = m_LControl.GetItemCount();
		// 		CString countStr(_T(""));
		// 		countStr.Format(_T("%d"), count);

		//m_LControl.InsertItem(count, countStr);
		CSclCtrlGsOut *pNew = new CSclCtrlGsOut();
		pGsOuts->AddNewChild(pNew);

		//m_LControl.SetItemText(count, 3, apName);
		pNew->apName = apName;
		pNew->m_strLDdesc = ldDesc;

		for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)sclln->datasetHead);
			scl_dataset != NULL;
			scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)sclln->datasetHead, (DBL_LNK *)scl_dataset))
		{
#ifdef SCL_USE_MMS_STRING_
			if ((0 == mms_str_cmp(&scl_dataset->name, &scl_gcb->datSet)) 
#else
			if ((0 == strcmp(scl_dataset->name, scl_gcb->datSet)) 
#endif
				&& (scl_dataset->desc)
				&& (strlen(scl_dataset->desc) > 0))
			{
				//m_LControl.SetItemText(count, 4, scl_dataset->desc);
				pNew->m_strDataSetDesc = scl_dataset->desc;

				break;
			}
		}

		// 		CString gocbref(_T(""));
		// 		gocbref.Format(_T("%s%s/%s$GO$%s"), iedName, ldName, lnName, scl_gcb->name);
		// 		m_LControl.SetItemText(count, 5, gocbref);
#ifdef SCL_USE_MMS_STRING_
		pNew->gocbref = mms_string(&scl_gcb->name);
		pNew->m_strgocbRef.Format(_T("%s%s/%s$GO$%s"), iedName, ldName, lnName, mms_string(&scl_gcb->name));
		pNew->m_strID = mms_string(&scl_gcb->name);

		// 		CString dataset(_T(""));
		// 		dataset.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, scl_gcb->datSet);
		// 		m_LControl.SetItemText(count, 6, dataset);
		pNew->ldName = ldName;
		pNew->lnName = lnName;
		pNew->m_strDataSet = mms_string(&scl_gcb->datSet);
		pNew->m_strDataSetPath.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, mms_string(&scl_gcb->datSet));

		//m_LControl.SetItemText(count, 7, scl_gcb->appID);//goID
		pNew->m_strGooseId = mms_string(&scl_gcb->appID);

		// 		CString confrev(_T(""));
		// 		confrev.Format(_T("%d"), scl_gcb->confRev);
		// 		m_LControl.SetItemText(count, 8, confrev);
		pNew->m_dwVersion = scl_gcb->confRev;

		FindGSConnectAP(sclinfo, iedName, apName, ldName, mms_string(&scl_gcb->name), pNew);//zhow：在Communication中找到对应设备将MAC地址、APPID、VlanID、优先级 允许生成时间等等信息填入;
#else
		pNew->gocbref = scl_gcb->name;
		pNew->m_strgocbRef.Format(_T("%s%s/%s$GO$%s"), iedName, ldName, lnName, scl_gcb->name);
		pNew->m_strID = scl_gcb->name;

		// 		CString dataset(_T(""));
		// 		dataset.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, scl_gcb->datSet);
		// 		m_LControl.SetItemText(count, 6, dataset);
		pNew->ldName = ldName;
		pNew->lnName = lnName;
		pNew->m_strDataSet = scl_gcb->datSet;
		pNew->m_strDataSetPath.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, scl_gcb->datSet);

		//m_LControl.SetItemText(count, 7, scl_gcb->appID);//goID
		pNew->m_strGooseId = scl_gcb->appID;

		// 		CString confrev(_T(""));
		// 		confrev.Format(_T("%d"), scl_gcb->confRev);
		// 		m_LControl.SetItemText(count, 8, confrev);
		pNew->m_dwVersion = scl_gcb->confRev;

		FindGSConnectAP(sclinfo, iedName, apName, ldName, scl_gcb->name, pNew);//zhow：在Communication中找到对应设备将MAC地址、APPID、VlanID、优先级 允许生成时间等等信息填入;
#endif
	}

}

void CSclFileRead::FindGSConnectAP(SCL_INFO *sclinfo, const char *iedName, const char *apName, 
								   const char *ldName, const char *gcbName, CSclCtrlGs *pGs)
{
	SCL_SUBNET	*scl_subnet = NULL;
	SCL_CAP		*scl_cap = NULL;
	SCL_GSE		*scl_gse = NULL;
	//SCL_BAY      *scl_bay=NULL;

	int ipos = 0;
	CString apStr(apName);
	if ((ipos = apStr.Find(_T("--"))) >= 0)
	{
		apStr = apStr.Left(ipos);
	}

	for (scl_subnet = (SCL_SUBNET *)list_find_last((DBL_LNK *)sclinfo->subnetHead);
		scl_subnet != NULL;
		scl_subnet = (SCL_SUBNET *)list_find_prev((DBL_LNK *)sclinfo->subnetHead, (DBL_LNK *)scl_subnet))
	{
		for (scl_cap = (SCL_CAP *)list_find_last((DBL_LNK *)scl_subnet->capHead);
			scl_cap != NULL;
			scl_cap = (SCL_CAP *)list_find_prev((DBL_LNK *)scl_subnet->capHead, (DBL_LNK *)scl_cap))
		{
#ifdef SCL_USE_MMS_STRING_
			if (0 != (strcmp(iedName, mms_string(&scl_cap->iedName))) 
				|| ( apStr !=  mms_string(&scl_cap->apName) ) )
				//|| (0 != strcmp(apStr, mms_string(&scl_cap->apName))))
			{
				continue;
			}

			for (scl_gse = (SCL_GSE *)list_find_last((DBL_LNK *)scl_cap->gseHead);
				scl_gse != NULL;
				scl_gse = (SCL_GSE *)list_find_prev((DBL_LNK *)scl_cap->gseHead, (DBL_LNK *)scl_gse))
			{
				if (0 != (strcmp(ldName, mms_string(&scl_gse->ldInst))) 
					|| (0 != strcmp(gcbName, mms_string(&scl_gse->cbName))))
#else
			if (0 != (strcmp(iedName, scl_cap->iedName)) 
				|| (0 != strcmp(apStr, scl_cap->apName)))
			{
				continue;
			}

			for (scl_gse = (SCL_GSE *)list_find_last((DBL_LNK *)scl_cap->gseHead);
				scl_gse != NULL;
				scl_gse = (SCL_GSE *)list_find_prev((DBL_LNK *)scl_cap->gseHead, (DBL_LNK *)scl_gse))
			{
				if (0 != (strcmp(ldName, scl_gse->ldInst)) 
					|| (0 != strcmp(gcbName, scl_gse->cbName)))
#endif
				{
					continue;
				}

				//m_LControl.SetItemText(nItem, 1, scl_gse->APPID);//appid
				pGs->m_dwAppID = scl_gse->APPID;


				// 				CString mac(_T(""));
				// 				unsigned char tmpmac[6] = {0};
				// 				memcpy(tmpmac, scl_gse->MAC, 6);
				// 				for(int i = 0; i < 6; i++)
				// 				{
				// 					CString tmp(_T(""));
				// 					if(tmpmac[i] < 16)
				// 						tmp.Format("0%x", tmpmac[i]);
				// 					else
				// 						tmp.Format("%x", tmpmac[i]);
				// 					mac += tmp;
				// 				}
				//m_LControl.SetItemText(nItem, 2, mac);
				scl_SetMac(pGs->m_strMac, (unsigned char*)scl_gse->MAC);

				//CString vlanpri(_T(""));
				//vlanpri.Format(_T("%d"), scl_gse->VLANPRI);
				pGs->m_dwVLandPriority = scl_gse->VLANPRI;

				//CString minTime(_T(""));
				//minTime.Format(_T("%d"), scl_gse->MinTime);
				pGs->scl_gse_MinTime = scl_gse->MinTime;

				//CString maxTime(_T(""));
				//maxTime.Format(_T("%d"), scl_gse->MaxTime);
				pGs->scl_gse_MaxTime = scl_gse->MaxTime;

				pGs->m_dwVLandID = scl_gse->VLANID;//	m_LControl.SetItemText(nItem, 9, scl_gse->VLANID);//vlanid

				// 				if (ClickType_GOOSE_Outputs == m_iClickType)
				// 				{//GOOSE Out
				// 					m_LControl.SetItemText(nItem, 9, scl_gse->VLANID);//vlanid
				// 					m_LControl.SetItemText(nItem, 10, vlanpri);
				// 					m_LControl.SetItemText(nItem, 11, minTime);
				// 					m_LControl.SetItemText(nItem, 12, maxTime);
				// 				} 
				// 				else
				// 				{//GOOSE In m_iClickType == 1
				// 					m_LControl.SetItemText(nItem, 10, scl_gse->VLANID);//vlanid
				// 					m_LControl.SetItemText(nItem, 11, vlanpri);
				// 					m_LControl.SetItemText(nItem, 12, minTime);
				// 					m_LControl.SetItemText(nItem, 13, maxTime);
				// 				}

				return;
			}
		}
	}
}

void CSclFileRead::FindSVOutControl(SCL_INFO *sclinfo, SCL_LN *sclln, const char *iedName, 
									const char *apName, const char *ldName, const char *ldDesc, const char *lnName, CSclCtrlsSmvOut *pSmvOuts)
{
	SCL_SVCB	*scl_svcb = NULL;
	SCL_DATASET *scl_dataset = NULL;

	for (scl_svcb = (SCL_SVCB *)list_find_last((DBL_LNK *)sclln->svcbHead);
		scl_svcb != NULL;
		scl_svcb = (SCL_SVCB *)list_find_prev((DBL_LNK *)sclln->svcbHead, (DBL_LNK *)scl_svcb))
	{
		// 		int count = m_LControl.GetItemCount();
		// 		CString countStr(_T(""));
		// 		countStr.Format(_T("%d"), count);

		CSclCtrlSmvOut *pNew = new CSclCtrlSmvOut();
		pSmvOuts->AddNewChild(pNew);

		//m_LControl.InsertItem(count, countStr);

		pNew->apName = apName;//m_LControl.SetItemText(count, 3, apName);
		pNew->m_strLDdesc = ldDesc;

		for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)sclln->datasetHead);
			scl_dataset != NULL;
			scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)sclln->datasetHead, (DBL_LNK *)scl_dataset))
		{
#ifdef SCL_USE_MMS_STRING_
			if ((0 == mms_str_cmp(&scl_dataset->name, &scl_svcb->datSet)) 
#else
			if ((0 == strcmp(scl_dataset->name, scl_svcb->datSet)) 
#endif
				&& (scl_dataset->desc)
				&& (strlen(scl_dataset->desc) > 0))
			{
				pNew->m_strDataSetDesc = scl_dataset->desc;//m_LControl.SetItemText(count, 4, scl_dataset->desc);

				break;
			}
		}

		pNew->scl_svcb_smpRate = scl_svcb->smpRate;
		// 		CString smprate(_T(""));
		// 		smprate.Format(_T("%d"), scl_svcb->smpRate);
		// 		m_LControl.SetItemText(count, 5, smprate);

		//CString dataset(_T(""));
		pNew->ldName = ldName;
		pNew->lnName = lnName;
#ifdef SCL_USE_MMS_STRING_
		pNew->m_strDataSet = mms_string(&scl_svcb->datSet);
		pNew->m_strDataSetPath.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, mms_string(&scl_svcb->datSet));
		//m_LControl.SetItemText(count, 6, dataset);

		pNew->m_strSVID =  mms_string(&scl_svcb->smvID);
		pNew->m_strID = mms_string(&scl_svcb->smvID);

		pNew->scl_svcb_nofASDU = scl_svcb->nofASDU;
		//CString nofasdu(_T(""));
		//nofasdu.Format(_T("%d"), scl_svcb->nofASDU);	
		//m_LControl.SetItemText(count, 8, nofasdu);
		pNew->scl_svcb_confRev = scl_svcb->confRev;

		FindSVConnectAP(sclinfo, iedName, apName, ldName, mms_string(&scl_svcb->name), pNew);
#else
		pNew->m_strDataSet = scl_svcb->datSet;
		pNew->m_strDataSetPath.Format(_T("%s%s/%s$%s"), iedName, ldName, lnName, scl_svcb->datSet);
		//m_LControl.SetItemText(count, 6, dataset);

		pNew->m_strSVID =  scl_svcb->smvID;
		pNew->m_strID = scl_svcb->smvID;

		pNew->scl_svcb_nofASDU = scl_svcb->nofASDU;
		//CString nofasdu(_T(""));
		//nofasdu.Format(_T("%d"), scl_svcb->nofASDU);	
		//m_LControl.SetItemText(count, 8, nofasdu);
		pNew->scl_svcb_confRev = scl_svcb->confRev;

		FindSVConnectAP(sclinfo, iedName, apName, ldName, scl_svcb->name, pNew);
#endif
	}

}

void CSclFileRead::FindSVConnectAP(SCL_INFO *sclinfo, const char *iedName, const char *apName, 
								   const char *ldName, const char *svcbName, CSclCtrlSmv *pSmv)
{
	SCL_SUBNET	*scl_subnet = NULL;
	SCL_CAP		*scl_cap = NULL;
	SCL_SMV		*scl_smv = NULL;

	int ipos = 0;
	CString apStr(apName);
	if ((ipos = apStr.Find(_T("--"))) >= 0)
	{
		apStr = apStr.Left(ipos);
	}

	for (scl_subnet = (SCL_SUBNET *)list_find_last((DBL_LNK *)sclinfo->subnetHead);
		scl_subnet != NULL;
		scl_subnet = (SCL_SUBNET *)list_find_prev((DBL_LNK *)sclinfo->subnetHead, (DBL_LNK *)scl_subnet))
	{
		for (scl_cap = (SCL_CAP *)list_find_last((DBL_LNK *)scl_subnet->capHead);
			scl_cap != NULL;
			scl_cap = (SCL_CAP *)list_find_prev((DBL_LNK *)scl_subnet->capHead, (DBL_LNK *)scl_cap))
		{
#ifdef SCL_USE_MMS_STRING_
			if (0 != (strcmp(iedName, mms_string(&scl_cap->iedName))) 
				|| (apStr != mms_string(&scl_cap->apName) ))
				//|| (0 != strcmp(apStr, mms_string(&scl_cap->apName))))
#else
			if (0 != (strcmp(iedName, scl_cap->iedName)) 
				|| (0 != strcmp(apStr, scl_cap->apName)))
#endif
			{
				continue;
			}

			for (scl_smv = (SCL_SMV *)list_find_last((DBL_LNK *)scl_cap->smvHead);
				scl_smv != NULL;
				scl_smv = (SCL_SMV *)list_find_prev((DBL_LNK *)scl_cap->smvHead, (DBL_LNK *)scl_smv))
			{
#ifdef SCL_USE_MMS_STRING_
				if (0 != (strcmp(ldName, mms_string(&scl_smv->ldInst))) 
					|| (0 != strcmp(svcbName, mms_string(&scl_smv->cbName))))
#else
				if (0 != (strcmp(ldName, scl_smv->ldInst)) 
					|| (0 != strcmp(svcbName, scl_smv->cbName)))
#endif
				{
					continue;
				}

				//if item have been checked or not
				// 				int count = m_LSelectControl.GetItemCount();
				// 				for (int i = 0; i < count; i++)
				// 				{
				// 					if (m_LSelectControl.GetItemText(i, 1) == CString(scl_smv->APPID))
				// 					{
				// 						m_LControl.SetCheck(nItem, TRUE);
				// 
				// 						break;
				// 					}
				// 				}

				// 				CString mac(_T(""));
				// 				unsigned char tmpmac[6] = {0};
				// 				memcpy(tmpmac, scl_smv->MAC, 6);
				// 				for(int i = 0; i < 6; i++)
				// 				{
				// 					CString tmp(_T(""));
				// 					if(tmpmac[i] < 16)
				// 						tmp.Format("0%x", tmpmac[i]);
				// 					else
				// 						tmp.Format("%x", tmpmac[i]);
				// 					mac += tmp;
				// 				}			

				scl_SetMac(pSmv->m_strMac, (unsigned char *)scl_smv->MAC);

				pSmv->scl_smv_VLANPRI = scl_smv->VLANPRI;
				//CString vlanpri(_T(""));
				//vlanpri.Format(_T("%d"), scl_smv->VLANPRI);

				// 				int i = 0;
				// 				for (; i < nItem; i++)
				// 				{
				// 					CString oldAppID = m_LControl.GetItemText(i, 1);
				// 					if (oldAppID == CString(scl_smv->APPID))
				// 					{
				// 						break;
				// 					}
				// 				}
				// 				if (i < nItem)
				// 				{
				// 					m_LControl.DeleteItem(nItem);	//已插入的不显示
				// 				} 
				// 				else
				{
					pSmv->m_dwAppID = scl_smv->APPID;//m_LControl.SetItemText(nItem, 1, scl_smv->APPID);
					//pSmv->mac = mac;//m_LControl.SetItemText(nItem, 2, mac);
					pSmv->scl_smv_VLANID = scl_smv->VLANID; //m_LControl.SetItemText(nItem, 9, scl_smv->VLANID);//vlanid
					//pSmv->vlanpri = vlanpri;//m_LControl.SetItemText(nItem, 10, vlanpri);
					// 				
					// 					if (ClickType_SMV_Outputs == m_iClickType)
					// 					{//sv out
					// 						m_LControl.SetItemText(nItem, 1, scl_smv->APPID);
					// 						m_LControl.SetItemText(nItem, 2, mac);
					// 						m_LControl.SetItemText(nItem, 9, scl_smv->VLANID);//vlanid
					// 						m_LControl.SetItemText(nItem, 10, vlanpri);
					// 					}
					// 					else
					// 					{//sv in m_iClickType == ClickType_SMV_Inputs
					// 						m_LControl.SetItemText(nItem, 1, scl_smv->APPID);
					// 						m_LControl.SetItemText(nItem, 2, mac);
					// 						m_LControl.SetItemText(nItem, 10, scl_smv->VLANID);//vlanid
					// 						m_LControl.SetItemText(nItem, 11, vlanpri);
					// 					}
				}

				return;
			}
		}
	}
}


void CSclFileRead::FindGSSVOutChannelInfo(SCL_INFO *sclinfo, CSclCtrlBase *pCtrlBase)
{
	SCL_IED		*scl_ied = NULL;
	SCL_AP		*scl_ap = NULL;
	SCL_LD		*scl_ld = NULL;
	SCL_LN		*scl_ln = NULL;
	CSclIed *pIed = scl_GetIed(pCtrlBase);
	scl_ied = GetRefIED(pIed);

// 	for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)sclinfo->iedHead);
// 		scl_ied != NULL;
// 		scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)sclinfo->iedHead, (DBL_LNK *)scl_ied))
	{
// 		if (pIed->m_strID != scl_ied->name)
// 		{
// 			continue;
// 		}

		for (scl_ap = (SCL_AP *)list_find_last((DBL_LNK *)scl_ied->apHead);
			scl_ap != NULL;
			scl_ap = (SCL_AP *)list_find_prev((DBL_LNK *)scl_ied->apHead, (DBL_LNK *)scl_ap))
		{

			int ipos = 0;
			CString apStr(pCtrlBase->apName);
			if ((ipos = apStr.Find(_T("--"))) >= 0)
			{
				apStr = apStr.Left(ipos);
#ifdef SCL_USE_MMS_STRING_
				if (apStr != mms_string(&scl_ap->name))// != strncmp(domName, dataSet.GetString(), strlen(domName)))
#else
				if (apStr != scl_ap->name)// != strncmp(domName, dataSet.GetString(), strlen(domName)))
#endif
				{
					continue;
				}
			}

			for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)scl_ap->ldHead);
				scl_ld != NULL;
				scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ap->ldHead, (DBL_LNK *)scl_ld))
			{
				ST_CHAR domName[MAX_TYPE_LEN + 1] = {0};

#ifdef SCL_USE_MMS_STRING_
				strncpy (domName, mms_string(&scl_ied->name), MAX_IDENT_LEN + 1);
				strncat (domName, mms_string(&scl_ld->inst), MAX_IDENT_LEN + 1 - strlen(domName));
#else
				strncpy (domName, scl_ied->name, MAX_IDENT_LEN + 1);
				strncat (domName, scl_ld->inst, MAX_IDENT_LEN + 1 - strlen(domName));
#endif
				strncat (domName, _T("//"), 1);

//				pCtrlBase->m_strLDdesc = scl_ld->desc;//zhow 增加LD的desc属性2017.07.31

				//??????????????
#ifdef SCL_USE_MMS_STRING_
				if (pCtrlBase->ldName != mms_string(&scl_ld->inst))// != strncmp(domName, dataSet.GetString(), strlen(domName)))
#else
				if (pCtrlBase->ldName != scl_ld->inst)// != strncmp(domName, dataSet.GetString(), strlen(domName)))
#endif
				{
					continue;
				}

				for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
					scl_ln != NULL;
					scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
				{
					ST_CHAR lnName[MAX_TYPE_LEN + 1] = {0};
					//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
					//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
					//strncat (lnName, scl_ln->inst, MAX_IDENT_LEN + 1 - strlen(lnName));
					scl_get_ln_name(scl_ln, lnName);

					//????????????
					if (pCtrlBase->lnName != lnName)
					{
						continue;
					}
#ifdef SCL_USE_MMS_STRING_
					FindOutChannel(scl_ln, mms_string(&scl_ied->name), pCtrlBase);//在此函数中new所有输出的通道，并将描述赋值；
#else
					FindOutChannel(scl_ln, scl_ied->name, pCtrlBase);//在此函数中new所有输出的通道，并将描述赋值；
#endif
					return;
				}
				
			}
		}
	}
}

void CSclFileRead::FindOutChannel(SCL_LN *sclln, char *iedName, CSclCtrlBase *pCtrlBase)
{
	SCL_DATASET *scl_dataset = NULL;
	SCL_FCDA	*scl_fcda = NULL;

	for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)sclln->datasetHead);
		scl_dataset != NULL;
		scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)sclln->datasetHead, (DBL_LNK *)scl_dataset))
	{
		//int dsnLen = strlen(scl_dataset->name);
		//int dsLen = dataSet.GetLength();
		//CString dsStr = dataSet.Mid(dsLen - dsnLen);
#ifdef SCL_USE_MMS_STRING_
		if (pCtrlBase->m_strDataSet != mms_string(&scl_dataset->name))//strncmp(scl_dataset->name, dsStr.GetString(), dsnLen))
#else
		if (pCtrlBase->m_strDataSet != scl_dataset->name)//strncmp(scl_dataset->name, dsStr.GetString(), dsnLen))
#endif
		{
			continue;
		}

		for (scl_fcda = (SCL_FCDA *)list_find_last((DBL_LNK *)scl_dataset->fcdaHead);
			scl_fcda != NULL;
			scl_fcda = (SCL_FCDA *)list_find_prev((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
		{
#ifdef SCL_USE_MMS_STRING_
			CString fcdaName(_T(""));
			fcdaName.Format(_T("%s%s/%s%s%s"), iedName, mms_string(&scl_fcda->ldInst), mms_string(&scl_fcda->prefix), 
				mms_string(&scl_fcda->lnClass), mms_string(&scl_fcda->lnInst));
			if (mms_str_length(&scl_fcda->doName)>0)
			{
				fcdaName = fcdaName + _T(".") + CString(mms_string(&scl_fcda->doName));
			}
			if (mms_str_length(&scl_fcda->daName)>0)
			{
				fcdaName = fcdaName + _T(".") + CString(mms_string(&scl_fcda->daName));
			}

			// 			int count = m_LChannel.GetItemCount();
			// 			CString countStr(_T(""));
			// 			countStr.Format(_T("%d"), count);
			// 			m_LChannel.InsertItem(count, countStr);
			CSclChBase *pCh = pCtrlBase->CreateNewCh();

			//if (ClickType_GOOSE_Outputs == m_iClickType)
			if (scl_IsGsOutCh(pCh))
			{//GOOSE out
				CSclChGsOut *pNew = (CSclChGsOut*)pCh;//new CSclChGsOut();
				pNew->fcda_lndesc = mms_string(&scl_fcda->lndesc);
				pNew->fcda_dodesc = mms_string(&scl_fcda->dodesc);
				pNew->fcda_desc =  mms_string(&scl_fcda->desc);
				pNew->fcda_type = mms_string(&scl_fcda->type);

				pNew->fcda_name = fcdaName;

// #ifdef DEBUG
				pNew->m_strID = fcdaName;
				pNew->m_strName = mms_string(&scl_fcda->lndesc);
// #endif
			} 
			else  if (scl_IsSmvOutCh(pCh))
			{//SV out (ClickType_SMV_Outputs == m_iClickType)
				CSclChSmvOut *pNew = (CSclChSmvOut*)pCh;//new CSclChSmvOut();
				pNew->fcda_lndesc = mms_string(&scl_fcda->lndesc);
				pNew->fcda_dodesc =  mms_string(&scl_fcda->dodesc);
				pNew->fcda_desc = mms_string(&scl_fcda->desc);
				pNew->fcda_name =  fcdaName;

				pNew->fcda_DOType = mms_string(&scl_fcda->DOType);
				pNew->fcda_cdc = mms_string(&scl_fcda->cdc);

//#ifdef DEBUG
				pNew->m_strID = fcdaName;
				pNew->m_strName = mms_string(&scl_fcda->lndesc);
//#endif
			}
#else
			CString fcdaName(_T(""));
			fcdaName.Format(_T("%s%s/%s%s%s"), iedName, scl_fcda->ldInst, scl_fcda->prefix, 
				scl_fcda->lnClass, scl_fcda->lnInst);
			if (strlen(scl_fcda->doName))
			{
				fcdaName = fcdaName + _T(".") + CString(scl_fcda->doName);
			}
			if (strlen(scl_fcda->daName))
			{
				fcdaName = fcdaName + _T(".") + CString(scl_fcda->daName);
			}

			// 			int count = m_LChannel.GetItemCount();
			// 			CString countStr(_T(""));
			// 			countStr.Format(_T("%d"), count);
			// 			m_LChannel.InsertItem(count, countStr);
			CSclChBase *pCh = pCtrlBase->CreateNewCh();

			//if (ClickType_GOOSE_Outputs == m_iClickType)
			if (scl_IsGsOutCh(pCh))
			{//GOOSE out
				CSclChGsOut *pNew = (CSclChGsOut*)pCh;//new CSclChGsOut();
				pNew->fcda_lndesc = scl_fcda->lndesc;
				pNew->fcda_dodesc = scl_fcda->dodesc;
				pNew->fcda_desc =  scl_fcda->desc;
				pNew->fcda_type = scl_fcda->type;
				pNew->fcda_name = fcdaName;

// #ifdef DEBUG
				pNew->m_strID = fcdaName;
				pNew->m_strName = scl_fcda->lndesc;
// #endif
			} 
			else  if (scl_IsSmvOutCh(pCh))
			{//SV out (ClickType_SMV_Outputs == m_iClickType)
				CSclChSmvOut *pNew = (CSclChSmvOut*)pCh;//new CSclChSmvOut();
				pNew->fcda_lndesc = scl_fcda->lndesc;
				pNew->fcda_dodesc =  scl_fcda->dodesc;
				pNew->fcda_desc = scl_fcda->desc;
				pNew->fcda_name =  fcdaName;

				pNew->fcda_DOType = scl_fcda->DOType;
				pNew->fcda_cdc = scl_fcda->cdc;

//#ifdef DEBUG
				pNew->m_strID = fcdaName;
				pNew->m_strName = scl_fcda->lndesc;
//#endif
			}
#endif
		}

		return;
	}
}

void CSclFileRead::FindGSSVInChannelInfo(SCL_INFO *sclinfo, /*CString dataset,*/ CSclCtrlBase *pCtrlBase)
{
	SCL_IED		*scl_ied = NULL;
	SCL_AP		*scl_ap = NULL;
	SCL_LD		*scl_ld = NULL;
	SCL_LN		*scl_ln = NULL;
	SCL_INPUTS	*scl_inputs = NULL;
	SCL_EXTREF	*scl_extref = NULL;

	CSclIed *pIed = scl_GetIed(pCtrlBase);
	std::list<EXTREFINFO>	list_extref;
	scl_ied = GetRefIED(pIed); 

// 	for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)sclinfo->iedHead);
// 		scl_ied != NULL;
// 		scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)sclinfo->iedHead, (DBL_LNK *)scl_ied))
	{
// 		if (pIed->m_strID != scl_ied->name)// != strcmp(iedStr.GetString(), scl_ied->name))
// 		{
// 			continue;
// 		}

		for (scl_ap = (SCL_AP *)list_find_last((DBL_LNK *)scl_ied->apHead);
			scl_ap != NULL;
			scl_ap = (SCL_AP *)list_find_prev((DBL_LNK *)scl_ied->apHead, (DBL_LNK *)scl_ap))
		{

			int ipos = 0;
			CString apStr(pCtrlBase->apname_own());

			if ((ipos = apStr.Find(_T("--"))) >= 0)
			{
				apStr = apStr.Left(ipos);
			}
#ifdef SCL_USE_MMS_STRING_
			if (mms_string(&scl_ap->name) != apStr)
#else
			if (scl_ap->name != apStr)
#endif
			{
				continue;
			}

			for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)scl_ap->ldHead);
				scl_ld != NULL;
				scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ap->ldHead, (DBL_LNK *)scl_ld))
			{
				for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
					scl_ln != NULL;
					scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
				{
					ST_CHAR lnName	[MAX_TYPE_LEN + 1] = {0};
					//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
					//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
					//strncat (lnName, scl_ln->inst, MAX_IDENT_LEN + 1 - strlen(lnName));
					scl_get_ln_name(scl_ln, lnName);

//					pCtrlBase->m_strLDdesc = scl_ld->desc;//zhow 增加LD的desc属性2017.07.31

					//if (0 == strcmp(_strupr(_strdup(lnName)), _T("LLN0")))
					if (0 == stricmp(lnName, _T("LLN0")))
					{
						for (scl_inputs = (SCL_INPUTS *)list_find_last((DBL_LNK *)scl_ln->inputsHead);
							scl_inputs != NULL;
							scl_inputs = (SCL_INPUTS *)list_find_prev((DBL_LNK *)scl_ln->inputsHead, (DBL_LNK *)scl_inputs))
						{
							for (scl_extref = (SCL_EXTREF *)list_find_last((DBL_LNK *)scl_inputs->extrefHead);
								scl_extref != NULL;
								scl_extref = (SCL_EXTREF *)list_find_prev((DBL_LNK *)scl_inputs->extrefHead, (DBL_LNK *)scl_extref))
							{
								char domName[MAX_TYPE_LEN + 1] = {0};

#ifdef SCL_USE_MMS_STRING_
								strncpy(domName, mms_string(&scl_extref->domName), MAX_IDENT_LEN + 1);
								strncat(domName, mms_string(&scl_extref->ldInst), MAX_IDENT_LEN + 1 - strlen(domName));

								//??????????if (0 == strncmp(domName, dataset.GetString(), strlen(scl_extref->domName)))
								//if (pCtrlBase->ldName == scl_extref->ldInst)
								if ( (pCtrlBase->GetInIedExtName() == mms_string(&scl_extref->domName) ) //(strcmp(pCtrlBase->GetInIedExtName() ,mms_string(&scl_extref->domName))  == 0)
									&&(pCtrlBase->ldName == mms_string(&scl_extref->ldInst)))
								{
									CString extrefname(_T(""));
									extrefname.Format(_T("%s%s/%s%s%s"), mms_string(&scl_extref->domName), 
										mms_string(&scl_extref->ldInst),	mms_string(&scl_extref->prefix), 
										mms_string(&scl_extref->lnClass), mms_string(&scl_extref->lnInst));

									if (mms_str_length(&scl_extref->doName)>0)
									{
										extrefname = extrefname + _T(".") + CString(mms_string(&scl_extref->doName));
									}
									if (mms_str_length(&scl_extref->daName)>0)
									{
										extrefname = extrefname + _T(".") + CString(mms_string(&scl_extref->daName));
									}

									EXTREFINFO tmpextref;
									tmpextref.inPath = CString(mms_string(&scl_extref->inAddr));
									tmpextref.inLNDesc = CString(mms_string(&scl_extref->lndesc));
									tmpextref.inDODesc = CString(mms_string(&scl_extref->dodesc));
									tmpextref.inDADesc = CString(mms_string(&scl_extref->desc));
									tmpextref.outPath = extrefname;
									tmpextref.index = scl_extref->index;

									tmpextref.inputRef_type = mms_string(&scl_extref->type);
									tmpextref.inputRef_cdc = mms_string(&scl_extref->cdc);
#else
								strncpy(domName, scl_extref->domName, MAX_IDENT_LEN + 1);
								strncat(domName, scl_extref->ldInst, MAX_IDENT_LEN + 1 - strlen(domName));

								//??????????if (0 == strncmp(domName, dataset.GetString(), strlen(scl_extref->domName)))
								//if (pCtrlBase->ldName == scl_extref->ldInst)
								if ((strcmp(pCtrlBase->GetInIedExtName() ,scl_extref->domName)  == 0)&&(pCtrlBase->ldName == scl_extref->ldInst))
								{
									CString extrefname(_T(""));
									extrefname.Format(_T("%s%s/%s%s%s"), scl_extref->domName, 
										scl_extref->ldInst,	scl_extref->prefix, 
										scl_extref->lnClass, scl_extref->lnInst);

									if (strlen(scl_extref->doName))
									{
										extrefname = extrefname + _T(".") + CString(scl_extref->doName);
									}
									if (strlen(scl_extref->daName))
									{
										extrefname = extrefname + _T(".") + CString(scl_extref->daName);
									}

									EXTREFINFO tmpextref;
									tmpextref.inPath = CString(scl_extref->inAddr);
									tmpextref.inLNDesc = CString(scl_extref->lndesc);
									tmpextref.inDODesc = CString(scl_extref->dodesc);
									tmpextref.inDADesc = CString(scl_extref->desc);
									tmpextref.outPath = extrefname;
									tmpextref.index = scl_extref->index;

									tmpextref.inputRef_type = scl_extref->type;
									tmpextref.inputRef_cdc = scl_extref->cdc;
#endif

									list_extref.push_back(tmpextref);
								}
							}
						}

						break;
					}
				}
			}
		}

		//break;
	}

	if (!list_extref.empty())
	{
		FindInChannel(sclinfo, pCtrlBase, &list_extref);
	}
}

void CSclFileRead::FindInChannel(SCL_INFO *sclinfo, CSclCtrlBase *pCtrlBase, 
								 std::list<EXTREFINFO> *listextref)
{
	SCL_IED		*scl_ied = NULL;
	SCL_AP		*scl_ap = NULL;
	SCL_LD		*scl_ld = NULL;
	SCL_LN		*scl_ln = NULL;
	SCL_DATASET *scl_dataset = NULL;
	SCL_FCDA	*scl_fcda = NULL;

	CString strInRefIedStr = pCtrlBase->GetInIedExtName();

	int ipos = 0;
	CString apStr(pCtrlBase->apName);

	if ((ipos = apStr.Find(_T("--"))) >= 0)
	{
		apStr = apStr.Left(ipos);
	}

	for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)sclinfo->iedHead);
		scl_ied != NULL;
		scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)sclinfo->iedHead, (DBL_LNK *)scl_ied))
	{
#ifdef SCL_USE_MMS_STRING_
		if (strInRefIedStr != mms_string(&scl_ied->name))//dataSet.Find(scl_ied->name) < 0)
#else
		if (strInRefIedStr != scl_ied->name)//dataSet.Find(scl_ied->name) < 0)
#endif
		{
			continue;
		}

		for (scl_ap = (SCL_AP *)list_find_last((DBL_LNK *)scl_ied->apHead);
			scl_ap != NULL;
			scl_ap = (SCL_AP *)list_find_prev((DBL_LNK *)scl_ied->apHead, (DBL_LNK *)scl_ap))
		{
#ifdef SCL_USE_MMS_STRING_
			if (mms_string(&scl_ap->name) != apStr)
#else
			if (scl_ap->name != apStr)
#endif
			{
				continue;
			}

			for (scl_ld = (SCL_LD *)list_find_last((DBL_LNK *)scl_ap->ldHead);
				scl_ld != NULL;
				scl_ld = (SCL_LD *)list_find_prev((DBL_LNK *)scl_ap->ldHead, (DBL_LNK *)scl_ld))
			{
				ST_CHAR domName[MAX_TYPE_LEN + 1] = {0};
#ifdef SCL_USE_MMS_STRING_
				strncpy (domName, mms_string(&scl_ied->name), MAX_IDENT_LEN + 1);
				strncat (domName, mms_string(&scl_ld->inst), MAX_IDENT_LEN + 1 - strlen(domName));
#else
				strncpy (domName, scl_ied->name, MAX_IDENT_LEN + 1);
				strncat (domName, scl_ld->inst, MAX_IDENT_LEN + 1 - strlen(domName));
#endif
				strncat (domName, _T("//"), 1);

				///?????????????????????????///???
				//if (pCtrlBase->ldName != scl_ld->inst)// != strncmp(domName, dataSet.GetString(), strlen(domName)))
#ifdef SCL_USE_MMS_STRING_
				if (pCtrlBase->ldName != mms_string(&scl_ld->inst))// != strncmp(domName, dataSet.GetString(), strlen(domName)))
#else
				if (pCtrlBase->ldName != scl_ld->inst)// != strncmp(domName, dataSet.GetString(), strlen(domName)))
#endif
				{
					continue;
				}

				for (scl_ln = (SCL_LN *)list_find_last((DBL_LNK *)scl_ld->lnHead);
					scl_ln != NULL;
					scl_ln = (SCL_LN *)list_find_prev((DBL_LNK *)scl_ld->lnHead, (DBL_LNK *)scl_ln))
				{
					ST_CHAR lnName	[MAX_TYPE_LEN + 1] = {0};
					//strncpy (lnName, scl_ln->prefix, MAX_IDENT_LEN + 1);
					//strncat (lnName, scl_ln->lnClass, MAX_IDENT_LEN + 1 - strlen(lnName));
					//strncat (lnName, scl_ln->inst, MAX_IDENT_LEN + 1 - strlen(lnName));
					scl_get_ln_name(scl_ln, lnName);

					if (pCtrlBase->lnName != lnName)//dataSet.Find(lnName) < 0)
					{
						continue;
					}

					for (scl_dataset = (SCL_DATASET *)list_find_last((DBL_LNK *)scl_ln->datasetHead);
						scl_dataset != NULL;
						scl_dataset = (SCL_DATASET *)list_find_prev((DBL_LNK *)scl_ln->datasetHead, (DBL_LNK *)scl_dataset))
					{
						//int dsnLen = strlen(scl_dataset->name);
						//int dsLen = dataSet.GetLength();
						//CString dsStr = dataSet.Mid(dsLen - dsnLen);
#ifdef SCL_USE_MMS_STRING_
						if (pCtrlBase->m_strDataSet != mms_string(&scl_dataset->name))// 0 != strncmp(scl_dataset->name, dsStr.GetString(), dsnLen))
#else
						if (pCtrlBase->m_strDataSet != scl_dataset->name)// 0 != strncmp(scl_dataset->name, dsStr.GetString(), dsnLen))
#endif
						{
							continue;
						}

						std::list<EXTREFINFO>::iterator iter = listextref->begin();
						std::list<EXTREFINFO>::iterator iend = listextref->end();
						for(; iter != iend; iter++)
						{
							int outcount = 0;

							for (scl_fcda = (SCL_FCDA *)list_find_last((DBL_LNK *)scl_dataset->fcdaHead);
								scl_fcda != NULL;
								scl_fcda = (SCL_FCDA *)list_find_prev((DBL_LNK *)scl_dataset->fcdaHead, (DBL_LNK *)scl_fcda))
							{
								CString fcdaName(_T(""));
#ifdef SCL_USE_MMS_STRING_
								fcdaName.Format(_T("%s%s/%s%s%s"), mms_string(&scl_ied->name), mms_string(&scl_fcda->ldInst), 
									mms_string(&scl_fcda->prefix), mms_string(&scl_fcda->lnClass), mms_string(&scl_fcda->lnInst));

								if (mms_str_length(&scl_fcda->doName)>0)
								{
									fcdaName = fcdaName + _T(".") + CString(mms_string(&scl_fcda->doName));
								}
								if (mms_str_length(&scl_fcda->daName)>0)
								{
									fcdaName = fcdaName + _T(".") + CString(mms_string(&scl_fcda->daName));
								}

								if ((*iter).outPath == fcdaName)
								{
									// 									int count = m_LChannel.GetItemCount();
									// 									m_LChannel.InsertItem(count, _T(""));
									// 
									CSclChBase *pCh = pCtrlBase->CreateNewCh();

									//if (ClickType_GOOSE_Inputs == m_iClickType)
									if (scl_IsGsInCh(pCh))
									{//GS in
										CSclChGsIn *pNew = (CSclChGsIn*)pCh;//new CSclChGsIn();
										pNew->fcda_map = mms_string(&scl_fcda->map);
										pNew->fcda_type = mms_string(&scl_fcda->type);

										pNew->inLNDesc =  (*iter).inLNDesc;
										pNew->fcda_lndesc =  mms_string(&scl_fcda->lndesc);
										pNew->inDODesc = (*iter).inDODesc;
										pNew->fcda_dodesc =  mms_string(&scl_fcda->dodesc);
										pNew->inDADesc =  (*iter).inDADesc;
										pNew->fcda_desc =  mms_string(&scl_fcda->desc);
										pNew->inIndex =  (*iter).index;//pCtrlBase->GetCount()-1;
										pNew->outIndex = outcount;
										pNew->inPath=  (*iter).inPath;
										pNew->fcda_name =  (*iter).outPath;	

										pNew->inputRef_type =  (*iter).inputRef_type;	//zhow:20170802

//#ifdef DEBUG
										pNew->m_strName = (*iter).inPath;
										pNew->m_strID = (*iter).outPath;
//#endif
									}
									else  if (scl_IsSmvInCh(pCh))
									{//SV in (ClickType_SMV_Inputs == m_iClickType)
										CSclChSmvIn *pNew = (CSclChSmvIn*)pCh;//new CSclChSmvIn();
										pNew->inLNDesc = (*iter).inLNDesc;
										pNew->fcda_lndesc =  mms_string(&scl_fcda->lndesc);
										pNew->inDODesc =  (*iter).inDODesc;
										pNew->fcda_dodesc =  mms_string(&scl_fcda->dodesc);
										pNew->inDADesc =  (*iter).inDADesc;
										pNew->fcda_desc =  mms_string(&scl_fcda->desc);
										pNew->inIndex =  (*iter).index;//pCtrlBase->GetCount()-1;
										pNew->outIndex =  outcount;
										pNew->inPath =  (*iter).inPath;
										pNew->fcda_name =  (*iter).outPath;

										pNew->fcda_DOType = mms_string(&scl_fcda->DOType);//zhow:20170802
										pNew->fcda_cdc = mms_string(&scl_fcda->cdc);//zhow:20170802
#else
								fcdaName.Format(_T("%s%s/%s%s%s"), scl_ied->name, scl_fcda->ldInst, 
									scl_fcda->prefix, scl_fcda->lnClass, scl_fcda->lnInst);

								if (strlen(scl_fcda->doName))
								{
									fcdaName = fcdaName + _T(".") + CString(scl_fcda->doName);
								}
								if (strlen(scl_fcda->daName))
								{
									fcdaName = fcdaName + _T(".") + CString(scl_fcda->daName);
								}

								if ((*iter).outPath == fcdaName)
								{
									// 									int count = m_LChannel.GetItemCount();
									// 									m_LChannel.InsertItem(count, _T(""));
									// 
									CSclChBase *pCh = pCtrlBase->CreateNewCh();

									//if (ClickType_GOOSE_Inputs == m_iClickType)
									if (scl_IsGsInCh(pCh))
									{//GS in
										CSclChGsIn *pNew = (CSclChGsIn*)pCh;//new CSclChGsIn();
										pNew->fcda_map = scl_fcda->map;
										pNew->fcda_type = scl_fcda->type;
										pNew->inLNDesc =  (*iter).inLNDesc;
										pNew->fcda_lndesc =  scl_fcda->lndesc;
										pNew->inDODesc = (*iter).inDODesc;
										pNew->fcda_dodesc =  scl_fcda->dodesc;
										pNew->inDADesc =  (*iter).inDADesc;
										pNew->fcda_desc =  scl_fcda->desc;
										pNew->inIndex =  (*iter).index;//pCtrlBase->GetCount()-1;
										pNew->outIndex = outcount;
										pNew->inPath=  (*iter).inPath;
										pNew->fcda_name =  (*iter).outPath;	

										pNew->inputRef_type =  (*iter).inputRef_type;	//zhow:20170802

//#ifdef DEBUG
										pNew->m_strName = (*iter).inPath;
										pNew->m_strID = (*iter).outPath;
//#endif
									}
									else  if (scl_IsSmvInCh(pCh))
									{//SV in (ClickType_SMV_Inputs == m_iClickType)
										CSclChSmvIn *pNew = (CSclChSmvIn*)pCh;//new CSclChSmvIn();
										pNew->inLNDesc = (*iter).inLNDesc;
										pNew->fcda_lndesc =  scl_fcda->lndesc;
										pNew->inDODesc =  (*iter).inDODesc;
										pNew->fcda_dodesc =  scl_fcda->dodesc;
										pNew->inDADesc =  (*iter).inDADesc;
										pNew->fcda_desc =  scl_fcda->desc;
										pNew->inIndex =  (*iter).index;//pCtrlBase->GetCount()-1;
										pNew->outIndex =  outcount;
										pNew->inPath =  (*iter).inPath;
										pNew->fcda_name =  (*iter).outPath;

										pNew->fcda_DOType = scl_fcda->DOType;//zhow:20170802
										pNew->fcda_cdc = scl_fcda->cdc;//zhow:20170802
#endif

										pNew->inputRef_DOType = (*iter).inputRef_type;//zhow:20170802
										pNew->inputRef_cdc = (*iter).inputRef_cdc;//zhow:20170802

//#ifdef DEBUG
										pNew->m_strName = (*iter).inPath;
										pNew->m_strID = (*iter).outPath;
//#endif
									}
								}

								outcount++;
							}

								if (pCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_GS_IN)
								{
									((CSclCtrlGsIn*)pCtrlBase)->m_nChnRefCount = outcount;
								}
								else if (pCtrlBase->GetClassID() == SCLIECCLASSID_CTRL_SMV_IN)
								{
									((CSclCtrlSmvIn*)pCtrlBase)->m_nChnRefCount = outcount;
								}

						}

						break;
					}
				}

				break;
			}
		}
	}
}

// void CSclFileRead::ReadIedDetail_Ctrls(CSclIed *pIed, CSclCtrls *pCtrls)
// {
// 	ReadGSSVControl(pCtrls);
// 
// 	if (pCtrls->GetCount() == 0)
// 	{
// 		if (m_pOwnerWnd != NULL)
// 		{
// 			m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pCtrls, (WPARAM)SCLFILE_READ_DELCTRLS);
// 		}
// 	}
// }

void CSclFileRead::ReadIedDetail(CSclIed *pIed)
{
#ifndef _USE_ONLY_DEVICE_MODEL_// 周宏军 20200229 在不需要解析SV/GOOSE的情况下使用此宏定义
	ReadGSSVControl(&m_SclInfo, pIed, pIed->HasGsIns(), pIed->HasGsOuts(), pIed->HasSmvIns(), pIed->HasSmvOuts());
#endif

// 	if (pIed->HasGsIns())
// 	{
// 		ReadIedDetail_Ctrls(pIed, pIed->GetGsIns());	
// 	}
// 
// 	if (pIed->HasGsOuts())
// 	{
// 		ReadIedDetail_Ctrls(pIed, pIed->GetGsOuts());
// 	}
// 
// 	if (pIed->HasSmvIns())
// 	{
// 		ReadIedDetail_Ctrls(pIed, pIed->GetSmvIns());
// 	}
// 
// 	if (pIed->HasSmvOuts())
// 	{
// 		ReadIedDetail_Ctrls(pIed, pIed->GetSmvOuts());
// 	}
}

#ifdef SCL_USE_MMS_STRING_
void CSclFileRead::GetValueType(SCL_INFO *sclinfo,SCL_FCDA * sclfcda, CString &lntype,CString &FinalDaType)
#else
void CSclFileRead::GetValueType(SCL_INFO *sclinfo,SCL_FCDA * sclfcda, ST_CHAR *lntype,char *FinalDaType)
#endif
{
	//fcda doname is empty
#ifdef SCL_USE_MMS_STRING_
	CString	dotype = _T("");
	CString	datype = _T("");

	CString	fcdadodaName = _T("");

	if (mms_str_length(&sclfcda->doName)>0)
	{
		fcdadodaName = mms_string(&sclfcda->doName);
	}

	//fcda daname is empty
	if (mms_str_length(&sclfcda->daName)>0)
	{
		fcdadodaName.AppendFormat(_T("$%s"),mms_string(&sclfcda->daName));
	}

	//find dotype from scl_lntype
	FindDoType(sclinfo, sclfcda, lntype, dotype, fcdadodaName);

	//find datype from scl_dotype
	if (mms_str_length(&sclfcda->doName)>0)
	{
		FindValueDaType(sclinfo, sclfcda, dotype, datype, fcdadodaName, FinalDaType);
	} 
	else
	{
		//find fcda do struct
		return;
	}

	//find final type from scl_datype
	if (mms_str_length(&sclfcda->daName)>0)
	{
		FindFinalType(sclinfo, sclfcda, datype, fcdadodaName);
	} 
	else
	{
		//find fcda da struct
		return;
	}
#else
	ST_CHAR	dotype		[MAX_IDENT_LEN + 1] = {0};
	ST_CHAR	datype		[MAX_IDENT_LEN + 1] = {0};

	ST_CHAR	fcdadodaName[MAX_IDENT_LEN + 1] = {0};

	if (strlen (sclfcda->doName))
	{
		strncpy (fcdadodaName, sclfcda->doName, strlen(sclfcda->doName) + 1);
	}

	//fcda daname is empty
	if (strlen (sclfcda->daName))
	{
		strcat (fcdadodaName, _T("$"));
		strncat (fcdadodaName, sclfcda->daName, strlen(sclfcda->daName) + 1);
	}

	//find dotype from scl_lntype
	FindDoType(sclinfo, sclfcda, lntype, dotype, fcdadodaName);

	//find datype from scl_dotype
	if (strlen (sclfcda->doName))
	{
		FindValueDaType(sclinfo, sclfcda, dotype, datype, fcdadodaName, FinalDaType);
	} 
	else
	{
		//find fcda do struct
		return;
	}

	//find final type from scl_datype
	if (strlen (sclfcda->daName))
	{
		FindFinalType(sclinfo, sclfcda, datype, fcdadodaName);
	} 
	else
	{
		//find fcda da struct
		return;
	}
#endif

	return ;

}

#ifdef SCL_USE_MMS_STRING_
void CSclFileRead::FindValueDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &dotype, CString &datype, CString &fcdadodaName,CString &FinalDaType)
#else
void CSclFileRead::FindValueDaType(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype, char *datype, char *fcdadodaName,char *FinalDaType)
#endif
{

	SCL_DOTYPE	*scl_dotype = NULL;
	SCL_DA		*scl_da = NULL;

	//not find dotype
	if (dotype.GetLength() <= 0) //(strlen(dotype) <= 0)
	{
#ifdef SCL_USE_MMS_STRING_
		if (mms_str_length(&sclfcda->type) <= 0)
		{
			mms_str_set(&sclfcda->type, _T("Struct"));
		}
#else
		if (strlen(sclfcda->type) <= 0)
		{
			strcpy (sclfcda->type, _T("Struct"));
		}
#endif
	}
	else                
	{

#ifdef SCL_USE_MMS_STRING_
		if (fcdadodaName.GetLength() <= 0) //(strlen(fcdadodaName) <= 0)
		{
			FindValueDaStruct(sclinfo, sclfcda, dotype,FinalDaType);
		} 
		else
		{
			for (scl_dotype = (SCL_DOTYPE *)list_find_last((DBL_LNK *)sclinfo->doTypeHead);
				scl_dotype != NULL;
				scl_dotype = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)sclinfo->doTypeHead, (DBL_LNK *)scl_dotype))
			{				
				if (dotype == mms_string(&scl_dotype->id)) //(0 == strcmp(mms_string(&scl_dotype->id), dotype))
				{
					CString daFstName = _T("");
					FindDelStr(fcdadodaName, daFstName);

					for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
						scl_da != NULL;
						scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
					{
						if (daFstName == mms_string(&scl_da->name)) //(0 == strcmp(mms_string(&scl_da->name), daFstName))
						{
							if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
							{
								CString	tdotype;
								tdotype = mms_string(&scl_da->type);

								FindValueDaType(sclinfo, sclfcda, tdotype, datype, fcdadodaName,FinalDaType);
							}
							else//da type
							{
								if (0 == strcmp(mms_string(&scl_da->bType), _T("Struct")))
								{
									datype = mms_string(&scl_da->type);
								}
								else
								{
									//strncpy(sclfcda->type, scl_da->bType, MAX_IDENT_LEN + 1);
									FinalDaType = mms_string(&scl_da->bType);
								}
							}	
							break;
						}
					}
					break;
				}
#else
		if (strlen(fcdadodaName) <= 0)
		{
			FindValueDaStruct(sclinfo, sclfcda, dotype,FinalDaType);
		} 
		else
		{
			for (scl_dotype = (SCL_DOTYPE *)list_find_last((DBL_LNK *)sclinfo->doTypeHead);
				scl_dotype != NULL;
				scl_dotype = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)sclinfo->doTypeHead, (DBL_LNK *)scl_dotype))
			{
				if (0 == strcmp(scl_dotype->id, dotype))
				{
					ST_CHAR daFstName[MAX_IDENT_LEN + 1] = {0};
					FindDelStr(fcdadodaName, daFstName);

					for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
						scl_da != NULL;
						scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
					{
						if (0 == strcmp(scl_da->name, daFstName))
						{
							if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
							{
								ST_CHAR	tdotype[MAX_IDENT_LEN + 1] = {0};
								strncpy (tdotype, scl_da->type, MAX_IDENT_LEN + 1);

								FindValueDaType(sclinfo, sclfcda, tdotype, datype, fcdadodaName,FinalDaType);
							}
							else//da type
							{
								if (0 == strcmp(scl_da->bType, _T("Struct")))
								{
									strncpy (datype, scl_da->type, MAX_IDENT_LEN + 1);
								}
								else
								{
									//strncpy(sclfcda->type, scl_da->bType, MAX_IDENT_LEN + 1);
									strncpy (FinalDaType, scl_da->bType, MAX_IDENT_LEN + 1);
								}
							}	
							break;
						}
					}
					break;
				}
#endif
			}
		}
	}

}

#ifdef SCL_USE_MMS_STRING_
void CSclFileRead::FindValueDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &dotype,CString &FinalDaType)
#else
void CSclFileRead::FindValueDaStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *dotype,char*FinalDaType)
#endif
{
	SCL_DOTYPE	*scl_dotype = NULL;
	SCL_DA		*scl_da = NULL;

	for (scl_dotype = (SCL_DOTYPE *)list_find_last((DBL_LNK *)sclinfo->doTypeHead);
		scl_dotype != NULL;
		scl_dotype = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)sclinfo->doTypeHead, (DBL_LNK *)scl_dotype))
	{
#ifdef SCL_USE_MMS_STRING_
		if (dotype == mms_string(&scl_dotype->id)) //(0 == strcmp(mms_string(&scl_dotype->id), dotype))
		{
			for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
				scl_da != NULL;
				scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
			{
				if (0==strcmp(mms_string(&scl_da->name),"cVal")||0==strcmp(mms_string(&scl_da->name),"setVal")||0==strcmp(mms_string(&scl_da->name),"setMag"))
				{
					if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
					{
						CString	tdotype;
						tdotype = mms_string(&scl_da->type);

						FindValueDaStruct(sclinfo, sclfcda, tdotype,FinalDaType);
					}
					else//da type
					{
						if (0 == strcmp(mms_string(&scl_da->bType), _T("Struct")))
						{
							CString datype;
							datype = mms_string(&scl_da->type);

							FindValueFinalStruct(sclinfo, sclfcda, datype,FinalDaType);
						}
						else
						{
							//	strncat(sclfcda->type, scl_da->bType, strlen(scl_da->bType));
							FinalDaType = mms_string(&scl_da->bType);
							//	strncat(sclfcda->type, _T(","), 2);
							break;
						}
					}	
				}
			}
			break;
		}
#else
		if (0 == strcmp(scl_dotype->id, dotype))
		{
			for (scl_da = (SCL_DA *)list_find_last((DBL_LNK *)scl_dotype->daHead);
				scl_da != NULL;
				scl_da = (SCL_DA *)list_find_prev((DBL_LNK *)scl_dotype->daHead, (DBL_LNK *)scl_da))
			{
				if (0==strcmp(scl_da->name,"cVal")||0==strcmp(scl_da->name,"setVal")||0==strcmp(scl_da->name,"setMag"))
				{
					if (scl_da->objtype == SCL_OBJTYPE_SDO)//sdo type
					{
						ST_CHAR	tdotype[MAX_IDENT_LEN + 1] = {0};
						strncpy (tdotype, scl_da->type, MAX_IDENT_LEN + 1);

						FindValueDaStruct(sclinfo, sclfcda, tdotype,FinalDaType);
					}
					else//da type
					{
						if (0 == strcmp(scl_da->bType, _T("Struct")))
						{
							ST_CHAR datype[MAX_IDENT_LEN + 1] = {0};
							strncpy (datype, scl_da->type, MAX_IDENT_LEN + 1);

							FindValueFinalStruct(sclinfo, sclfcda, datype,FinalDaType);
						}
						else
						{
							//	strncat(sclfcda->type, scl_da->bType, strlen(scl_da->bType));
							strncpy (FinalDaType, scl_da->bType, MAX_IDENT_LEN + 1);
							//	strncat(sclfcda->type, _T(","), 2);
							break;
						}
					}	
				}
			}
			break;
		}
#endif
	}
}

#ifdef SCL_USE_MMS_STRING_
void CSclFileRead::FindValueFinalStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, CString &datype,CString &FinalDaType)
#else
void CSclFileRead::FindValueFinalStruct(SCL_INFO *sclinfo, SCL_FCDA *sclfcda, char *datype,char*FinalDaType)
#endif
{

	SCL_DATYPE	*scl_datype = NULL; 
	SCL_BDA		*scl_bda = NULL;
#ifdef SCL_USE_MMS_STRING_
	CString		tdatype = _T("");
#else
	ST_CHAR		tdatype[MAX_IDENT_LEN + 1] = {0};
#endif

	//strncat(sclfcda->type, _T("<"), 2);

	for (scl_datype = (SCL_DATYPE *)list_find_last((DBL_LNK *)sclinfo->daTypeHead);
		scl_datype != NULL;
		scl_datype = (SCL_DATYPE *)list_find_prev((DBL_LNK *)sclinfo->daTypeHead, (DBL_LNK *)scl_datype))
	{
#ifdef SCL_USE_MMS_STRING_
		if (datype == mms_string(&scl_datype->id)) //(0 == strcmp(mms_string(&scl_datype->id), datype))
		{	
			for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)scl_datype->bdaHead);
				scl_bda != NULL;
				scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)scl_datype->bdaHead, (DBL_LNK *)scl_bda))
			{
				if (FinalDaType.Find(mms_string(&scl_bda->name)) != -1)	
				{
					if (0 == strcmp(mms_string(&scl_bda->bType), _T("Struct")))	
					{
						tdatype = mms_string(&scl_bda->type);

						FindValueFinalStruct(sclinfo, sclfcda, tdatype,FinalDaType);
					}
					else	
					{	
						//strncat(sclfcda->type, scl_bda->bType, strlen(scl_bda->bType));
						//strncat(sclfcda->type, _T(","), 2);
						FinalDaType = mms_string(&scl_bda->bType);
						break;
					}	
				}
			}


			break;
		}
#else
		if (0 == strcmp(scl_datype->id, datype))
		{	
			for (scl_bda = (SCL_BDA *)list_find_last((DBL_LNK *)scl_datype->bdaHead);
				scl_bda != NULL;
				scl_bda = (SCL_BDA *)list_find_prev((DBL_LNK *)scl_datype->bdaHead, (DBL_LNK *)scl_bda))
			{
				if (strstr(FinalDaType, scl_bda->name) != NULL)	
				{
					if (0 == strcmp(scl_bda->bType, _T("Struct")))	
					{
						strncpy (tdatype, scl_bda->type, MAX_IDENT_LEN + 1);

						FindValueFinalStruct(sclinfo, sclfcda, tdatype,FinalDaType);
					}
					else	
					{	
						//strncat(sclfcda->type, scl_bda->bType, strlen(scl_bda->bType));
						//strncat(sclfcda->type, _T(","), 2);
						strncpy (FinalDaType, scl_bda->bType, MAX_IDENT_LEN + 1);
						break;
					}	
				}
			}


			break;
		}
#endif
	}

	//	sclfcda->type[strlen(sclfcda->type) - 1] = _T('>');	
}


BOOL CSclFileRead::IsCreateValue(SCL_DAI *scldai)
{
#ifdef SCL_USE_MMS_STRING_
	if 	((strstr(mms_string(&scldai->flattened), "$cVal") != NULL)	|| (strstr(mms_string(&scldai->flattened), "$setVal") != NULL)
		|| (strstr(mms_string(&scldai->flattened), "$setMag") != NULL))
#else
	if 	((strstr(scldai->flattened, "$cVal") != NULL)	|| (strstr(scldai->flattened, "$setVal") != NULL)|| (strstr(scldai->flattened, "$setMag") != NULL))
#endif
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}

}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//cgl：只为检测SCD读写文件用


BOOL CSclFileRead::ReadSclFile(const CString &strFile, CWnd *pOwnerWnd, CSclStation *pSclStation)
{	
	m_pSclStation=pSclStation;
	m_pSclStation->SetScdFile(strFile);
	m_strFile=strFile;
	m_pOwnerWnd = pOwnerWnd;

#ifndef _PSX_IDE_QT_
	m_pScdFileRWDlg = new CScdFileRWDlg();
	m_pThreadProgress=(CThreadProgressInterface*)m_pScdFileRWDlg;
	m_pScdFileRWDlg->SetWindowTitle(_T("读取SCD文件"));
	m_pScdFileRWDlg->SetUseModeless();
	m_pScdFileRWDlg->DoModal();
	m_pReadThread = AfxBeginThread(ReadSCLThread, this);
	m_pReadThread->m_bAutoDelete = TRUE;
#else
	m_bIsInReadState = TRUE;
	m_pReadThread = new CWinThread(ReadSCLThread,this);
	m_pReadThread->m_bAutoDelete = FALSE;
	m_pReadThread->start();
#endif

	//if (m_pOwnerWnd != NULL)
	//{
	//	m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pSclStation, (WPARAM)SCLFILE_READ_FINISH);
	//}

	return TRUE;
}


UINT CSclFileRead::ReadSCLThread( LPVOID pParam )
{
	//yzj 2023.11.29 加载SCD十分缓慢所以替换回原先的进度条
	CSclFileRead *pSclFileRead = (CSclFileRead *)pParam;
	pSclFileRead->m_bIsInReadState = TRUE;

#ifndef _PSX_IDE_QT_
		::CoInitialize(NULL);
		pSclFileRead->m_pScdFileRWDlg->SetMaxRange(3);

	#ifdef SCL_USE_MMS_STRING_
		pSclFileRead->m_pScdFileRWDlg->ShowMsg(_T("释放SCL文件处理的过程中的临时内存空间，请稍候......"));
		pSclFileRead->Free_SCL_INFO();
	#else
	#endif
		g_bUseSmemEnable = FALSE;
		pSclFileRead->m_pScdFileRWDlg->ShowMsg(_T("读取SCD文件......"));
		ST_RET ret = scl_parse(pSclFileRead->m_strFile.GetBuffer(), &pSclFileRead->m_SclInfo);
		g_bUseSmemEnable = TRUE;
		pSclFileRead->m_bCan_Free_SCL_INFO = TRUE;
		CString strMsg;

		if (ret == SD_SUCCESS)
		{
			pSclFileRead->m_pScdFileRWDlg->StepIt();
			pSclFileRead->m_pScdFileRWDlg->ShowMsg(_T("处理IED数据......"));
			pSclFileRead->ReadStationInfo();
			pSclFileRead->ReadIedInfoAndCtrls(&pSclFileRead->m_SclInfo);

			//		pSclFileRead->ReadDataTypeTemplates(&pSclFileRead->m_SclInfo);//zhow:解析DataTypeTemplates 用到的

			pSclFileRead->m_pScdFileRWDlg->StepIt();	

			CSclStation *pSclStation=pSclFileRead->GetSclStation();


			long nCount = pSclStation->GetCount();
			POS pos =pSclStation->GetHeadPosition();		
			CExBaseObject *pTemp= NULL;

			if (nCount > 0)
			{
				pSclFileRead->m_pScdFileRWDlg->SetMaxRange(nCount);
				pSclFileRead->m_pScdFileRWDlg->ResetProcess();
				pSclFileRead->m_pScdFileRWDlg->StepIt();
				long nIndex=1;

				while (pos != NULL)
				{
					pTemp = pSclStation->GetNext(pos);

					if(pTemp->GetClassID() != SCLIECCLASSID_IED)
					{
						continue;
					}

					//strMsg.Format(_T("%d / %d 处理IED【%s】"), nIndex, nCount, pTemp->m_strName);
					strMsg.Format(_T("%d / %d"), nIndex, nCount);
					CString strText;
					strText = _T(" IED Parse:  ");
					strMsg += strText;
					strMsg += pTemp->m_strName;
					pSclFileRead->m_pScdFileRWDlg->ShowMsg(strMsg);
					pSclFileRead->ReadIedDetail((CSclIed*)pTemp);
					pSclFileRead->m_pScdFileRWDlg->StepIt();
					nIndex++;
				}
			}

			if (pSclFileRead->m_pOwnerWnd != NULL)
			{
				pSclFileRead->m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pParam, (WPARAM)SCLFILE_READ_SHOW);
			}
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("无法解析SCL文件【%s】！"), pSclFileRead->m_strFile);
		}

	#ifdef SCL_USE_MMS_STRING_
	#else
		pSclFileRead->m_pScdFileRWDlg->ShowMsg(_T("释放SCL文件处理的过程中的临时内存空间，请稍候......"));
		pSclFileRead->Free_SCL_INFO();
	#endif

		if (pSclFileRead->m_pOwnerWnd != NULL)
		{
			pSclFileRead->m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pParam, (WPARAM)SCLFILE_READ_FINISH);
		}

		pSclFileRead->m_pScdFileRWDlg->ShowWindow(SW_HIDE);
		::CoUninitialize();
#else
		pSclFileRead->m_pThreadProgress->SetMaxRange(3);
		pSclFileRead->m_pThreadProgress->InitThreadProgress(3, 1);

	#ifdef SCL_USE_MMS_STRING_
		pSclFileRead->m_pThreadProgress->ShowMsg(_T("释放SCL文件处理的过程中的临时内存空间，请稍候......"));
		pSclFileRead->Free_SCL_INFO();
	#else
	#endif
		g_bUseSmemEnable = TRUE;
		pSclFileRead->m_pThreadProgress->ShowMsg(_T("读取SCD文件......"));
		ST_RET ret = scl_parse((char*)pSclFileRead->m_strFile.GetString(), &pSclFileRead->m_SclInfo);
		g_bUseSmemEnable = FALSE;
		pSclFileRead->m_bCan_Free_SCL_INFO = TRUE;
		CString strMsg;

		if (ret == SD_SUCCESS)
		{
			pSclFileRead->m_pThreadProgress->StepIt();
			pSclFileRead->m_pThreadProgress->ShowMsg(_T("处理IED数据......"));
			pSclFileRead->ReadStationInfo();
			pSclFileRead->ReadIedInfoAndCtrls(&pSclFileRead->m_SclInfo);

			//		pSclFileRead->ReadDataTypeTemplates(&pSclFileRead->m_SclInfo);//zhow:解析DataTypeTemplates 用到的

			pSclFileRead->m_pThreadProgress->StepIt();	

			CSclStation *pSclStation=pSclFileRead->GetSclStation();


			long nCount = pSclStation->GetCount();
			POS pos =pSclStation->GetHeadPosition();		
			CExBaseObject *pTemp= NULL;

			if (nCount > 0)
			{
				pSclFileRead->m_pThreadProgress->SetMaxRange(nCount);
				pSclFileRead->m_pThreadProgress->ResetProcess();
				pSclFileRead->m_pThreadProgress->StepIt();
				long nIndex=1;

				while (pos != NULL)
				{
					pTemp = pSclStation->GetNext(pos);

					if(pTemp->GetClassID() != SCLIECCLASSID_IED)
					{
						continue;
					}

					//strMsg.Format(_T("%d / %d 处理IED【%s】"), nIndex, nCount, pTemp->m_strName);
					strMsg.Format(_T("%d / %d"), nIndex, nCount);
					CString strText;
					strText = _T(" IED Parse:  ");
					strMsg += strText;
					strMsg += pTemp->m_strName;
					pSclFileRead->m_pThreadProgress->ShowMsg(strMsg);
					pSclFileRead->ReadIedDetail((CSclIed*)pTemp);
					pSclFileRead->m_pThreadProgress->StepIt();
					nIndex++;
				}
			}

			if (pSclFileRead->m_pOwnerWnd != NULL)
			{
				pSclFileRead->m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pParam, (WPARAM)SCLFILE_READ_SHOW);//显示树形视图
			}
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("无法解析SCL文件【%s】！"), pSclFileRead->m_strFile);
		}

	#ifdef SCL_USE_MMS_STRING_
	#else
		pSclFileRead->m_pThreadProgress->ShowMsg(_T("释放SCL文件处理的过程中的临时内存空间，请稍候......"));
		pSclFileRead->Free_SCL_INFO();
	#endif

		if (pSclFileRead->m_pOwnerWnd != NULL)
		{
			pSclFileRead->m_pOwnerWnd->PostMessage(WM_SCLFILE_READ_FINISH, (LPARAM)pParam, (WPARAM)SCLFILE_READ_FINISH);
		}
#endif

	pSclFileRead->m_bIsInReadState = FALSE;
	return 0;
}

void CSclFileRead::MoveProgressWindow(CRect rc)
{
#ifndef _PSX_IDE_QT_
	m_pScdFileRWDlg->MoveWindow(&rc);
#endif
}

void CSclFileRead::SetProgessInterface(CThreadProgressInterface *pInterface)
{
	m_pThreadProgress = pInterface;
}

SCL_IED* CSclFileRead::GetRefIED(CSclIed *pIed)
{
	ASSERT (pIed->m_pRefItemData != NULL);
	SCL_IED *p_SCL_IED = (SCL_IED*)pIed->m_pRefItemData;
	return p_SCL_IED;
}

void CSclFileRead::SetRefIED(CSclIed *pIed, SCL_IED *p_SCL_IED)
{
	pIed->m_pRefItemData = p_SCL_IED;//整个SCD解析后的信息的指针
#ifdef SCL_USE_MMS_STRING_
	pIed->m_strID = mms_string(&p_SCL_IED->name);
	pIed->m_strModel = mms_string(&p_SCL_IED->type);
	pIed->m_strManufacturer = mms_string(&p_SCL_IED->manufacturer);
#else
	pIed->m_strID = p_SCL_IED->name;
	pIed->m_strModel = p_SCL_IED->type;
	pIed->m_strManufacturer = p_SCL_IED->manufacturer;
#endif

	if (p_SCL_IED->desc != NULL)
	{
		pIed->m_strName = p_SCL_IED->desc;
	}
	else
	{
		pIed->m_strName = pIed->m_strID;
	}

}
void CSclFileRead::ReadLdRptCtrl(SCL_LN *scl_ln0, SCL_AP *scl_ap, CDvmLogicDevice *pDvmLdevice)
{
	SCL_RCB *scl_ReportCtrl = NULL;
	CRptCtrls *pRptCtrls = pDvmLdevice->GetRptCtrls();
	CRptCtrl *pRptCtrl = NULL;

	for (scl_ReportCtrl = (SCL_RCB *)list_find_last((DBL_LNK *)scl_ln0->rcbHead);
		scl_ReportCtrl != NULL;
		scl_ReportCtrl = (SCL_RCB *)list_find_prev((DBL_LNK *)scl_ln0->rcbHead, (DBL_LNK *)scl_ReportCtrl))
	{
		pRptCtrl = new CRptCtrl();			//cgl	对应逻辑节点
		pRptCtrls->AddNewChild(pRptCtrl);	

#ifdef SCL_USE_MMS_STRING_
		pRptCtrl->m_strName = mms_string(&scl_ReportCtrl->name);
		pRptCtrl->m_strDatSet = mms_string(&scl_ReportCtrl->datSet);
		pRptCtrl->m_nIntgPd = scl_ReportCtrl->intgPd;
		pRptCtrl->m_strID = mms_string(&scl_ReportCtrl->rptID);
#else
		pRptCtrl->m_strName = scl_ReportCtrl->name;
		pRptCtrl->m_strDatSet = scl_ReportCtrl->datSet;
		pRptCtrl->m_nIntgPd = scl_ReportCtrl->intgPd;
		pRptCtrl->m_strID = scl_ReportCtrl->rptID;
#endif
		pRptCtrl->m_nConfRev = scl_ReportCtrl->confRev;
		pRptCtrl->m_nBuffered = scl_ReportCtrl->buffered;
		pRptCtrl->m_nBufTime = scl_ReportCtrl->bufTime;
		pRptCtrl->m_nTrgOps = (long)(scl_ReportCtrl->TrgOps[0]);
		pRptCtrl->m_nOptFields = (long)(scl_ReportCtrl->OptFlds[0]) + ((long)scl_ReportCtrl->OptFlds[1])*256;
		pRptCtrl->m_nRptEnabled = scl_ReportCtrl->maxClient;

	}

}

void CSclFileRead::ReadLdLogCtrl(SCL_LN *scl_ln0, SCL_AP *scl_ap, CDvmLogicDevice *pDvmLdevice)
{
	SCL_LCB *scl_LogCtrl = NULL;
	CLogCtrls *pLogCtrls = pDvmLdevice->GetLogCtrls();
	CLogCtrl *pLogCtrl = NULL;

	for (scl_LogCtrl = (SCL_LCB *)list_find_last((DBL_LNK *)scl_ln0->lcbHead);
		scl_LogCtrl != NULL;
		scl_LogCtrl = (SCL_LCB *)list_find_prev((DBL_LNK *)scl_ln0->lcbHead, (DBL_LNK *)scl_LogCtrl))
	{
		pLogCtrl = new CLogCtrl();			//cgl	对应逻辑节点
		pLogCtrls->AddNewChild(pLogCtrl);
#ifdef SCL_USE_MMS_STRING_
		pLogCtrl->m_strID = mms_string(&scl_LogCtrl->name);
		pLogCtrl->m_strName = scl_LogCtrl->desc;
		pLogCtrl->m_strDatSet = mms_string(&scl_LogCtrl->datSet);
		pLogCtrl->m_nIntgPd = scl_LogCtrl->intgPd;
 		
		pLogCtrl->m_strLogName = mms_string(&scl_LogCtrl->logName);
		pLogCtrl->m_nLogEna = scl_LogCtrl->logEna;
#else
		pLogCtrl->m_strID = scl_LogCtrl->name;
		pLogCtrl->m_strName = scl_LogCtrl->desc;
		pLogCtrl->m_strDatSet = scl_LogCtrl->datSet;
		pLogCtrl->m_nIntgPd = scl_LogCtrl->intgPd;

		pLogCtrl->m_strLogName = scl_LogCtrl->logName;
		pLogCtrl->m_nLogEna = scl_LogCtrl->logEna;
#endif
		pLogCtrl->m_nReasonCode = scl_LogCtrl->reasonCode;
 		pLogCtrl->m_nTrgOps = (long)(scl_LogCtrl->TrgOps[0]);

	}

}

BOOL CSclFileRead::GetAndSaveDeviceModel(const CString &strDeviceModelPath,const CString &strIEDName)
{
	if (!m_bCan_Free_SCL_INFO)
	{
		return FALSE;
	}

	SCL_IED	*scl_ied = NULL;

	for (scl_ied = (SCL_IED *)list_find_last((DBL_LNK *)m_SclInfo.iedHead);
		scl_ied != NULL;
		scl_ied = (SCL_IED *)list_find_prev((DBL_LNK *)m_SclInfo.iedHead, (DBL_LNK *)scl_ied))
	{
#ifdef SCL_USE_MMS_STRING_
		if (strIEDName.CompareNoCase(mms_string(&scl_ied->name)) == 0) //(stricmp(mms_string(&scl_ied->name),strIEDName) == 0)
#else
		if (stricmp(scl_ied->name,strIEDName) == 0)
#endif
		{
			break;
		}
	}

	if (scl_ied == NULL)
	{
		return FALSE;
	}

	//model_XmlWrite(strDeviceModelPath ,scl_ied,&m_SclInfo,0);
	return TRUE;
}

BOOL CSclFileRead::GetDvmFileFromSCL(const CString &strSclFile,const CString &strIedName,const CString &strSaveDvmFile)
{
	if (strSclFile != m_strFile)
	{
		m_bIsInReadState = TRUE;
		m_strFile = strSclFile;

#ifdef SCL_USE_MMS_STRING_
		Free_SCL_INFO();
#else
#endif
		ST_RET ret = scl_parse((char*)m_strFile.GetString(), &m_SclInfo);
		m_bCan_Free_SCL_INFO = TRUE;

		if(ret != SD_SUCCESS)
		{
			return FALSE;
		}
	}

	return GetAndSaveDeviceModel(strSaveDvmFile,strIedName);
}

#ifdef _USE_DATATYPETEMPLATES_READ_
void CSclFileRead::ReadDataTypeTemplates(SCL_INFO* scl_info)
{
	SCL_LNTYPE		*scl_LNType = NULL;
	SCL_DOTYPE		*scl_DOType = NULL;
	SCL_DATYPE		*scl_DAType = NULL;
	SCL_ENUMTYPE		*scl_EnumType = NULL;

	SCL_DO           *scl_DO = NULL;
	SCL_DA           *scl_DA = NULL;
	SCL_BDA          *scl_BDA = NULL;
	SCL_ENUMVAL      *scl_EnumVal = NULL;

	CDataTypeTmps *pDataTypeTmps = new CDataTypeTmps();

	CSclLNodeType *pLNodeType = NULL;
	CSclDOType *pDOType = NULL;
	CSclDAType *pDAType = NULL;
	CSclEnumType *pEnumType = NULL;
	CDODetail *pDODetail = NULL;
	CDADetail *pDADetail =NULL;
	CBDADetail *pBDADetail = NULL;
	CEnumVal *pEnumVal = NULL;

	m_pSclStation->AddNewChild(pDataTypeTmps);
	pDataTypeTmps->m_strName = scl_info->Header.id;
	pDataTypeTmps->m_strID = scl_info->Header.id;	

	for (scl_LNType = (SCL_LNTYPE *)list_find_last((DBL_LNK *)scl_info->lnTypeHead);
		scl_LNType != NULL;
		scl_LNType = (SCL_LNTYPE *)list_find_prev((DBL_LNK *)scl_info->lnTypeHead, (DBL_LNK *)scl_LNType))
	{
		pLNodeType = new CSclLNodeType();
		pDataTypeTmps->AddNewChild(pLNodeType);
		pLNodeType->m_strName = scl_LNType->lnClass;
		pLNodeType->m_strID = scl_LNType->id;

		for (scl_DO = (SCL_DO *)list_find_last((DBL_LNK *)scl_LNType->doHead);
			scl_DO != NULL;
			scl_DO = (SCL_DO *)list_find_prev((DBL_LNK *)scl_LNType->doHead, (DBL_LNK *)scl_DO))
		{
			pDODetail = new CDODetail();
			pLNodeType->AddNewChild(pDODetail);
			pDODetail->m_strName = scl_DO->name;
			pDODetail->m_strID = scl_DO->type;

		}

	}

	for (scl_DOType = (SCL_DOTYPE *)list_find_last((DBL_LNK *)scl_info->doTypeHead);
		scl_DOType != NULL;
		scl_DOType = (SCL_DOTYPE *)list_find_prev((DBL_LNK *)scl_info->doTypeHead, (DBL_LNK *)scl_DOType))
	{
		pDOType = new CSclDOType();
		pDataTypeTmps->AddNewChild(pDOType);
		pDOType->m_strName = scl_DOType->cdc;
		pDOType->m_strID = scl_DOType->id;

		for (scl_DA = (SCL_DA *)list_find_last((DBL_LNK *)scl_DOType->daHead);
			scl_DA != NULL;
			scl_DA = (SCL_DA *)list_find_prev((DBL_LNK *)scl_DOType->daHead, (DBL_LNK *)scl_DA))
		{
			pDADetail = new CDADetail();
			pDOType->AddNewChild(pDADetail);
			pDADetail->m_nObjType = scl_DA->objtype;
			pDADetail->m_strName = scl_DA->name;
			pDADetail->m_strAddr = scl_DA->sAddr;
			pDADetail->m_strBType = scl_DA->bType;
			pDADetail->m_strValKind = scl_DA->valKind;
			pDADetail->m_strID = scl_DA->type;
			pDADetail->m_nCount = scl_DA->count;
			pDADetail->m_strFC = scl_DA->fc;
			pDADetail->m_nTrgOp = 4*(scl_DA->dchg) + 2*(scl_DA->qchg) + scl_DA->dupd;
			pDADetail->m_strValue = scl_DA->Val;
			pDADetail->m_nSGroup = scl_DA->sGroup;

		}

	}


	for (scl_DAType = (SCL_DATYPE *)list_find_last((DBL_LNK *)scl_info->daTypeHead);
		scl_DAType != NULL;
		scl_DAType = (SCL_DATYPE *)list_find_prev((DBL_LNK *)scl_info->daTypeHead, (DBL_LNK *)scl_DAType))
	{
		pDAType = new CSclDAType();
		pDataTypeTmps->AddNewChild(pDAType);
		pDAType->m_strName = scl_DAType->id;
		pDAType->m_strID = scl_DAType->id;

		for (scl_BDA = (SCL_BDA *)list_find_last((DBL_LNK *)scl_DAType->bdaHead);
			scl_BDA != NULL;
			scl_BDA = (SCL_BDA *)list_find_prev((DBL_LNK *)scl_DAType->bdaHead, (DBL_LNK *)scl_BDA))
		{
			pBDADetail = new CBDADetail();
			pDAType->AddNewChild(pBDADetail);

			pBDADetail->m_strName = scl_BDA->name;
			pBDADetail->m_strAddr = scl_BDA->sAddr;
			pBDADetail->m_strBType = scl_BDA->bType;
			pBDADetail->m_strValKind = scl_BDA->valKind;
			pBDADetail->m_strID = scl_BDA->type;
			pBDADetail->m_nCount = scl_BDA->count;
			pBDADetail->m_strValue = scl_BDA->Val;
			pBDADetail->m_nSGroup = scl_BDA->sGroup;

		}

	}

	for (scl_EnumType = (SCL_ENUMTYPE *)list_find_last((DBL_LNK *)scl_info->enumTypeHead);
		scl_EnumType != NULL;
		scl_EnumType = (SCL_ENUMTYPE *)list_find_prev((DBL_LNK *)scl_info->enumTypeHead, (DBL_LNK *)scl_EnumType))
	{
		pEnumType = new CSclEnumType();
		pDataTypeTmps->AddNewChild(pEnumType);
		pEnumType->m_strName = scl_EnumType->id;
		pEnumType->m_strID = scl_EnumType->id;

		for (scl_EnumVal = (SCL_ENUMVAL *)list_find_last((DBL_LNK *)scl_EnumType->enumvalHead);
			scl_EnumVal != NULL;
			scl_EnumVal = (SCL_ENUMVAL *)list_find_prev((DBL_LNK *)scl_EnumType->enumvalHead, (DBL_LNK *)scl_EnumVal))
		{
			pEnumVal = new CEnumVal();
			pEnumType->AddNewChild(pEnumVal);

			pEnumVal->m_strID = scl_EnumVal->EnumVal;
			UTF8ToMultiByte(pEnumVal->m_strID);

			pEnumVal->m_strName = pEnumVal->m_strID;

			pEnumVal->m_nOrd = scl_EnumVal->ord;

		}

	}
}
#endif