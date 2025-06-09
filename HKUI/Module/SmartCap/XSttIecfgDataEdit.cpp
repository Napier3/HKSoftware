#include "StdAfx.h"
#include "XSttIecfgDataEdit.h"


/*SetChGoutAttrEx(strAppID, nIndex, vAppCh, vDevCh, ............);*/
/*SetChGinAttrEx(strAppID, strChID, strAttrID, strValue);*/

CXSttIecfgDataEdit::CXSttIecfgDataEdit()
{
}

CXSttIecfgDataEdit::~CXSttIecfgDataEdit(void)
{

}

void CXSttIecfgDataEdit::SetGoutMapAttr(CString strDatasetID, CString  strAttrID,  CString strMapValue, CString strDevMapValue)
{

}

void CXSttIecfgDataEdit::SetGinMapAttr(CString strDatasetID, CString  strAttrID,  CString strMapValue, CString strDevMapValue)
{

}

void CXSttIecfgDataEdit::SetDatasetP_GinP_GoutP(CDvmDataset *pDataset, CDvmData *pGin ,CDvmData *pGout)
{
	m_pDataset = pDataset;
	m_pGin = pGin ;
	m_pGout = pGout;
}

// CDvmDataset *pDataset = (CDvmDataset *)m_oDeviceModel.FindDataset(CAP_DATASET_MAP_ID_IEDTest);
// CDvmData *pGin = (CDvmData *)pDataset->FindByID(_T("Gin"));
// CDvmData *pGout = (CDvmData *)pDataset->FindByID(_T("Gout"));