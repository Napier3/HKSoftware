#include "SttIecGooseGrid_PkgAnalyze.h"

CSttIecGooseGrid_PkgAnalyze::CSttIecGooseGrid_PkgAnalyze(QWidget* pparent):CSttIecSmvGrid_PkgAnalyze(pparent)
{
	m_pIecRcdFuncWidget = this;
}

CSttIecGooseGrid_PkgAnalyze::~CSttIecGooseGrid_PkgAnalyze()
{

}

void CSttIecGooseGrid_PkgAnalyze::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;

	//2022-5-28  lijunqing
	CDvmDataset *pDatasetCstcErr = NULL;
	CDvmData *pDataCtrl = NULL;

	FindDvmDataForCtrl(pCapDevice, CAP_DATASET_MAP_ID_GOCSTC, &pDatasetCstcErr, &pDataCtrl);

	if (pDataCtrl != NULL)
	{
		ShowDatas(pDataCtrl);
	}
}

void CSttIecGooseGrid_PkgAnalyze::Release()
{
	delete this;
}
