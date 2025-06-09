#pragma once


#include "../../Module/DataMngr/DvmDevice.h"
#include "../../61850/Module/CfgDataMngr/IecCfgDevice.h"
#include "../../Module/SmartCap/XSttCap_61850.h"

class CXSttIecfgDataEdit 
{
public:
	CXSttIecfgDataEdit();
	virtual ~CXSttIecfgDataEdit(void);


public:
	void SetGoutMapAttr(CString strDatasetID, CString  strAttrID,  CString strMapValue, CString strDevMapValue);
	void SetGinMapAttr(CString strDatasetID, CString  strAttrID,  CString strMapValue, CString strDevMapValue);
	void SetDatasetP_GinP_GoutP(CDvmDataset *pDataset, CDvmData *pGin ,CDvmData *pGout);

public:
	CDvmDataset *m_pDataset;
	CDvmData *m_pGin ;
	CDvmData *m_pGout;

};
