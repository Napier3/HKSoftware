
#pragma once

#include "../PoEngine/PoMmsDataSet.h"

class CPoCmsDataSet : public CPoMmsDataSet
{
public:
	static CPoCmsDataSet* _NewPoCmsDataSet(CMmsDatasetMapTool *pMmsDatasetMapTool);

	static CPoCmsDataSet* _NewPoCmsDataSet(ACSI_NODE *pACSI_NODE, LD_NODE *pLD_NODE, LD_DATASET_INFO *pDataset)
	{
		CPoCmsDataSet *pNew = new CPoCmsDataSet();
		pNew->m_pACSI_NODE = pACSI_NODE;
		pNew->m_pLD_NODE = pLD_NODE;
		pNew->m_pDataset = pDataset;
		pNew->m_pRpt = NULL;
		pNew->m_pFileDir = NULL;
		return pNew;
	}
	static CPoCmsDataSet* _NewPoCmsDataSet(ACSI_NODE *pACSI_NODE, tagRpt *pRpt)
	{
		CPoCmsDataSet *pNew = new CPoCmsDataSet();
		pNew->m_pACSI_NODE = pACSI_NODE;
		pNew->m_pLD_NODE = NULL;;
		pNew->m_pDataset = NULL;
		pNew->m_pRpt = pRpt;
		pNew->m_pFileDir = NULL;
		return pNew;
	}
	static CPoCmsDataSet* _NewPoCmsDataSet(ACSI_NODE *pACSI_NODE, CDvmDataset *pDvmDataset)
	{
		CPoCmsDataSet *pNew = new CPoCmsDataSet();
		pNew->m_pDvmDataset = pDvmDataset;
		pNew->m_pACSI_NODE = pACSI_NODE;
		pNew->m_pLD_NODE = NULL;;
		pNew->m_pDataset = NULL;
		pNew->m_pRpt = NULL;
		pNew->m_pFileDir = NULL;
		return pNew;
	}
	static CPoCmsDataSet* _NewPoFileDir(ACSI_NODE *pACSI_NODE, XMMS_FILE_SYS_OBJ *pFileDir)
	{
		CPoCmsDataSet *pNew = new CPoCmsDataSet();
		pNew->m_pACSI_NODE = pACSI_NODE;
		pNew->m_pLD_NODE = NULL;;
		pNew->m_pDataset = NULL;
		pNew->m_pRpt = NULL;
		pNew->m_pFileDir = pFileDir;
		return pNew;
	}
	
public:
	CPoCmsDataSet();
	virtual ~CPoCmsDataSet();

	virtual BOOL SetXmlData_Data(CDvmData *pData);
	virtual BOOL GetXmlDataEx_DvmData(CDvmData *pData);

};

BOOL po_Cms_GetXmlDataEx_DvmData(CDvmData *pData, ACSI_NODE *pDevice);


