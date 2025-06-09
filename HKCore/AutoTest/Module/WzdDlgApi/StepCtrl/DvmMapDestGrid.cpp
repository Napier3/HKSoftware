#include "stdafx.h"
#include "DvmMapDestGrid.h"

CDvmMapDestGrid::CDvmMapDestGrid()
{

}

CDvmMapDestGrid::~CDvmMapDestGrid()
{

}

void CDvmMapDestGrid::ShowDatasets()
{
	long nCount = m_listDvmDsMapStand.GetCount();
	ASSERT( nCount > 0);

	if (nCount == 0)
	{
		return;
	}

	CDvmCmpDsPropGridProperty* pPropDataset = NULL;
	CDvmDatasetMap *pDatasetMap = NULL;
	POS pos = m_listDvmDsMapStand.GetHeadPosition();
	CDvmDataset *pDataset = NULL;
	CString strDsPath;

	if (nCount == 1)
	{
		pDatasetMap = (CDvmDatasetMap *)m_listDvmDsMapStand.GetNext(pos);
		pDataset = (CDvmDataset*)pDatasetMap->m_pMap;
		ShowDataset(pDataset, NULL);
	}
	else
	{
		while (pos != NULL)
		{
			pDatasetMap = (CDvmDatasetMap *)m_listDvmDsMapStand.GetNext(pos);
			pDataset = (CDvmDataset*)pDatasetMap->m_pMap;

			if (pDataset == NULL || pDataset->m_strID != m_pDatasetMap->m_strMapID)
			{
				continue;
			}

			strDsPath = pDataset->m_strID;

			if ( pDatasetMap->m_strLdviceMap != pDatasetMap->m_strLdvice)
			{
				strDsPath.Format(_T("%s$%s"), pDatasetMap->m_strLdviceMap, pDataset->m_strID);
			}

			pPropDataset = new CDvmCmpDsMapPropGridProperty(strDsPath);
			ShowDataset(pDataset, pPropDataset);
			AddProperty(pPropDataset, FALSE, FALSE);
		}
	}

	AdjustLayout();
	Invalidate(FALSE);
}
