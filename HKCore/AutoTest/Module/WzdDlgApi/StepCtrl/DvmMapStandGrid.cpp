#include "stdafx.h"
#include "DvmMapStandGrid.h"

CDvmMapStandGrid::CDvmMapStandGrid()
{

}

CDvmMapStandGrid::~CDvmMapStandGrid()
{

}

void CDvmMapStandGrid::ShowDatasets()
{
	long nCount = m_listDvmDsMapStand.GetCount();
	ASSERT( nCount > 0);

	if (nCount == 0)
	{
		return;
	}

	long nIndex = 1;
	//CDvmDatasetMap *pDatasetMap = (CDvmDatasetMap*)m_listDvmDsMapStand.GetHead();
	//shaolei 20220228 ��Ϊֻ��ʾ��ǰѡ�е����ݼ�ӳ���µ�����ӳ������
	CDvmDatasetMap *pDatasetMap = m_pDatasetMap;
	CDvmDataset *pDataset = (CDvmDataset*)pDatasetMap->m_pStand;
	POS pos = pDataset->GetHeadPosition();
	CDvmData *pDvmData = NULL;
	CDvmCmpDsPropGridProperty* pPropData = NULL;

// 	CDvmDataset* pMapDvmDataset = (CDvmDataset*)m_pDatasetMap->m_pMap;
// 	if(pMapDvmDataset)
// 	{
		while (pos != NULL)
		{
 			pDvmData = (CDvmData*)pDataset->GetNext(pos);
// 			CDvmData* pMapDvmData = (CDvmData*)pMapDvmDataset->FindByID(pDvmData->m_strID);
// 			if(!pMapDvmData 
// 				&& m_pDatasetMap->m_strID.Find("Parameter") == -1
// 				&& m_pDatasetMap->m_strID.Find("Ena") == -1
// 				&& m_pDatasetMap->m_strID.Find("Setting") == -1)
// 			{
// 				continue;
// 			}

			if (CDvmMapTool::g_bOnlyShowNoMap == 1)
			{
				if (pDvmData->IsAllMap())
				{
					continue;
				}
			}

			pPropData = NewDvmDataProp(pDvmData, nIndex);
			nIndex++;
			AddProperty(pPropData,FALSE, FALSE);
		}
//	}

	AdjustLayout();
	Invalidate(FALSE);
}