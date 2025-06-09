#include "XDeviceModel.h"

CXDeviceModel::CXDeviceModel()
{
	m_pDvmDevice_Global = NULL;
	m_pDvmDevice_Show = NULL;
    m_pRioDatasets = NULL;
    m_pDeviceAttrs = NULL;
    m_pCBConfig_Dataset = NULL;
}

CXDeviceModel::~CXDeviceModel()
{
	if (m_pDvmDevice_Show != NULL)
	{
		delete m_pDvmDevice_Show;
		m_pDvmDevice_Show = NULL;
	}
}

BOOL CXDeviceModel::GetCharacteristics(CCharacteristics *pCharacteristics, CDvmDataset *pSelectDataset)
{
    CExBaseObject* pFind = NULL;
    pFind = m_oCharacterLib_Show.FindByID(pSelectDataset->m_strID);
    if(pFind == NULL)
    {
        return FALSE;
    }
    CCharacterFolder *pFindCharacterFolder = (CCharacterFolder*)pFind;
    pCharacteristics->AppendClone(pFindCharacterFolder);
    return TRUE;
}

CCharacterFolder* CXDeviceModel::SetCharacteristics(CCharacteristics *pCharacteristics, CDvmDataset *pSelectDataset)
{
    CExBaseObject* pFind = NULL;
    pFind = m_oCharacterLib_Show.FindByID(pSelectDataset->m_strID);
    if(pFind == NULL)
    {
        return NULL;
    }
    CCharacterFolder *pFindCharacterFolder = (CCharacterFolder*)pFind;
    pFindCharacterFolder->DeleteAll();
    pFindCharacterFolder->Append(pCharacteristics);
    pCharacteristics->RemoveAll();
    return (CCharacterFolder*)pFindCharacterFolder->Clone();
}

void CXDeviceModel::InitDvmDevice(CDvmDevice* pDvmDevice_Global)
{
	m_pDvmDevice_Global = pDvmDevice_Global;

	if (m_pDvmDevice_Show != NULL)
	{
		delete m_pDvmDevice_Show;
		m_pDvmDevice_Show = NULL;
	}

	m_pDvmDevice_Show = (CDvmDevice*)m_pDvmDevice_Global->Clone();
	UpdateDvmRef();
}

CDvmDataset *CXDeviceModel::GetDeviceAttrs()
{
    return m_pDeviceAttrs;
}

CDvmDataset *CXDeviceModel::GetCBConfig()
{
    return m_pCBConfig_Dataset;
}

CDvmData* CXDeviceModel::GetDeviceAttrsDataByID(const CString &strID)
{
	if (m_pDeviceAttrs == NULL)
	{
		return NULL;
	}

	return (CDvmData*)m_pDeviceAttrs->FindByID(strID);
}

CDvmData* CXDeviceModel::GetCBConfigDataByID(const CString &strID)
{
	if (m_pCBConfig_Dataset == NULL)
	{
		return NULL;
	}

	return (CDvmData*)m_pCBConfig_Dataset->FindByID(strID);
}

void CXDeviceModel::UpdateDvmRef()
{
	if (m_pDvmDevice_Show == NULL)
	{
		m_pRioDatasets = NULL;
		m_pDeviceAttrs = NULL;
		m_pCBConfig_Dataset = NULL;
		return;
	}

	m_pRioDatasets = (CDvmLogicDevice *)m_pDvmDevice_Show->FindByID(XRIO_DEVICE_MODEL_ID_RIO);

	if (m_pRioDatasets == NULL)
	{
		m_pDeviceAttrs = NULL;
		m_pCBConfig_Dataset = NULL;
		return;
	}

	m_pDeviceAttrs = (CDvmDataset*)m_pRioDatasets->FindByID(XRIO_DEVICE_MODEL_ID_DEVICE);
	m_pCBConfig_Dataset = (CDvmDataset*)m_pRioDatasets->FindByID(XRIO_DEVICE_MODEL_ID_CBCONFIGURATION);
}

