#include "SttIecGooseGrid_PkgError.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../XLangResource_Native.h"
#include <QHeaderView>

CSttIecGooseGrid_PkgError::CSttIecGooseGrid_PkgError(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
}

CSttIecGooseGrid_PkgError::~CSttIecGooseGrid_PkgError()
{

}


void CSttIecGooseGrid_PkgError::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;

	if (pCapDevice == NULL)
	{
		return;
	}

	//2022-5-28  lijunqing
	CDvmDataset *pDsError = NULL;
	CDvmData *pDataCtrl = NULL;

	FindDvmDataForCtrl(pCapDevice, CAP_DATASET_MAP_ID_GSERR, &pDsError, &pDataCtrl);

	if (pDataCtrl != NULL)
	{
		ShowDatas(pDataCtrl);
	}
}

void CSttIecGooseGrid_PkgError::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	pXCapPkgBufferMngr->LogBufferPos();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	UpdateDatas();
}

void CSttIecGooseGrid_PkgError::Release()
{
	delete this;
}

void CSttIecGooseGrid_PkgError::Config()
{
	if (m_pCapDevice == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("当前m_pCapDevice == NULL 清除失败.")*/g_sLangTxt_Currentfailed.GetString()); //lcq
		return;
	}

	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)m_pCapDevice;
	pCapDevice->ClearAnalysisResultErrors();
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("清空报文统计结果成功.")*/g_sLangTxt_Succeeded.GetString()); //lcq
}

void CSttIecGooseGrid_PkgError::InitGridTitle()
{
	CString astrGridTitle[2]= {"项目", "数目"};
// 	xlang_GetLangStrByFile(astrGridTitle[0], _T("Smv_Item"));
// 	xlang_GetLangStrByFile(astrGridTitle[1], _T("Smv_Number"));
	m_nGridWidth[0] = 100;
	m_nGridWidth[1] = 100;

	QExBaseListGridBase::InitGridTitle(astrGridTitle, m_nGridWidth, 2);
	horizontalHeader()->setResizeMode(QHeaderView::Stretch);//平均分布各列

}
void CSttIecGooseGrid_PkgError::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmValue *pValue = (CDvmValue*)pData;

	if (bInsertRow)
	{
		insertRow(NULL);
	}

	Show_StaticString(pValue, nRow, 0, &pValue->m_strName);
	if (pValue->m_strValue.IsEmpty())
	{
		pValue->m_strValue = "0";
	}
	Show_StaticString(pValue, nRow, 1, &pValue->m_strValue);

	nRow++;
}
void CSttIecGooseGrid_PkgError::UpdateData(CExBaseObject *pData, int nRow)
{
	CDvmValue *pValue = (CDvmValue*)pData;

	Show_StaticString(pValue, nRow, 1, &pValue->m_strValue);
}
