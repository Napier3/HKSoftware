#include "SttIecSmvGrid_PkgError.h"
#include "../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../Module/XLanguage/QT/XLanguageAPI_QT.h"
#include "../../XLangResource_Native.h"
#include "../../../Module/API/GlobalConfigApi.h"

#include <QHeaderView>

CSttIecSmvGrid_PkgError::CSttIecSmvGrid_PkgError(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	g_nRecordTestCalState = 1;//20220618 zhouhj 在进入报文统计界面时,不再进行计算操作,默认在计算中 
}

CSttIecSmvGrid_PkgError::~CSttIecSmvGrid_PkgError()
{
	g_nRecordTestCalState = 0;//20220618 zhouhj 在退出报文统计界面时,默认计算完毕
}

void CSttIecSmvGrid_PkgError::InitGridTitle()
{
	CString astrGridTitle[2];
	xlang_GetLangStrByFile(astrGridTitle[0], _T("Smv_Item"));
	xlang_GetLangStrByFile(astrGridTitle[1], _T("Smv_Number"));
	//= {"项目", "数目"};
//	int iGridWidth[2]={500, 300};
	m_nGridWidth[0] = 100;
	m_nGridWidth[1] = 100;

	QExBaseListGridBase::InitGridTitle(astrGridTitle, m_nGridWidth, 2);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分布各列

}

void CSttIecSmvGrid_PkgError::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
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

void CSttIecSmvGrid_PkgError::UpdateData(CExBaseObject *pData, int nRow)
{
	CDvmValue *pValue = (CDvmValue*)pData;

	Show_StaticString(pValue, nRow, 1, &pValue->m_strValue);
}

QSttIecSmvPkgErrorWidget::QSttIecSmvPkgErrorWidget(QWidget *parent)
	:QWidget(parent)
{
	m_pIecRcdFuncWidget = this;
	m_pGridPkgError = new CSttIecSmvGrid_PkgError(this);
	m_pWndPkgError = new QSttIecSmvDiscretCharWidget(this);
	/*setStyleSheet("background-color:white;");*/
	InitUI();
}

void QSttIecSmvPkgErrorWidget::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;

	if (pCapDevice == NULL)
	{
		return;
	}

	//2022-5-28  lijunqing
	CDvmDataset *pDsError = NULL;
	CDvmData *pDataCtrl = NULL;

	FindDvmDataForCtrl(pCapDevice, CAP_DATASET_MAP_ID_SVERR, &pDsError, &pDataCtrl);

	if (pDataCtrl != NULL)
	{
		m_pGridPkgError->ShowDatas(pDataCtrl);
	}

}

void QSttIecSmvPkgErrorWidget::Release()
{
	delete this;
}

void QSttIecSmvPkgErrorWidget::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	pXCapPkgBufferMngr->LogBufferPos();
 	pXSttCap_61850->UpdateDvmDeviceDatas();
 
	m_pGridPkgError->UpdateDatas();
	m_pWndPkgError->GetMaxTimeDiscrete(pCapDevice);
	m_pWndPkgError->PrepareData();

	if (m_pCapDevice != NULL)
	{
		CCapDeviceBase *pCapDevice = (CCapDeviceBase*)m_pCapDevice;
		pCapDevice->UpdateErrorTypeNum();
	}
}

void QSttIecSmvPkgErrorWidget::Config()
{
	if (m_pCapDevice == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,/*_T("当前m_pCapDevice == NULL 清除失败.")*/g_sLangTxt_Currentfailed.GetString()); //lcq
		return;
	}

	CCapDeviceBase *pCapDevice = (CCapDeviceBase*)m_pCapDevice;
	pCapDevice->ClearAnalysisResultErrors();
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,/*_T("清空报文统计结果成功.")*/g_sLangTxt_Succeeded.GetString());  //lcq
}

void QSttIecSmvPkgErrorWidget::InitUI()
{
	m_pLayout = new QHBoxLayout(this);

	m_pGridPkgError->setGeometry(0, 0, 200, 100);
	m_pWndPkgError->setGeometry(0, 0, 200, 100);
	m_pLayout->addWidget(m_pGridPkgError);
	m_pLayout->addWidget(m_pWndPkgError);
	m_pLayout->setStretch(0, 1);
	m_pLayout->setStretch(1, 1);

	setLayout(m_pLayout);
}
