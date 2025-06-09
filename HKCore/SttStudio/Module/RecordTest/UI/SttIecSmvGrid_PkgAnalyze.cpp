#include "SttIecSmvGrid_PkgAnalyze.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/API/MathApi.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

/*
��ϸ˵����
һ�������ļ��������Щ��Ŀ���������ļ��н������ã��ļ�λ��config\SttRcdSv_PkgAnalyze.xml

�����������ݼ�����Ϊ��CX61850CapBase::m_pDataset_SVCstcErr
	��ʼ������
	2.1 void CX61850CapBase::IecAnalysis_AddDataset_SV(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv)
	    ����SV���ƿ鴴����ص����ݼ�������ʸ��ͼ�����ʵ�
	2.2 void CX61850CapBase::IecAnalysis_AddDataset_SV_PkgAnalyze(CDvmLogicDevice *pLogicDevice, CDvmDataset *pDsSv)
	    a������SV���ݼ���ʼ�����ƿ�ķ�������
		b��XSttRcdInitSv_PkgAnalyze�����������ļ�����ʼ��SV���ƿ�ķ����������
		c��IecAnalysis_AddDataset_SV_PkgAnalyze_Iecfg���������ö�������stand���ݶ���

�������º�����ι�ϵ
	3.1 CSttIecSmvGrid_PkgAnalyze::IecRcdFuncUpdate
	3.2 pXSttCap_61850->UpdateDvmDeviceDatas()
	3.3 CX61850CapBase::UpdateDvmDeviceDatas_Analysis()
	3.4 CX61850CapBase::UpdateDvmDeviceDatas_Analysis_SVCstcErr()
	3.5 CX61850CapBase::UpdateDvmDeviceDatas_Analysis_SVCstcErr_Single(CCapDeviceBase *pCapDevice
	3.6 IecAnalysis_Update_SV_PkgAnalyze_val������ʵ��ֵ��ͬʱ������½���ж�rslt

�ġ�����ID��IECRCD_FUNC_Smv_PkgAnalyze
	g_oCapAnalysisConfig.Smv_PkgAnalyze();�������������
*/

CSttIecSmvGrid_PkgAnalyze::CSttIecSmvGrid_PkgAnalyze(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
}

CSttIecSmvGrid_PkgAnalyze::~CSttIecSmvGrid_PkgAnalyze()
{

}

void CSttIecSmvGrid_PkgAnalyze::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;

	//2022-5-28  lijunqing
	CDvmDataset *pDataset_SVCstcErr = NULL;
	CDvmData *pDataSv = NULL;

	FindDvmDataForCtrl(pCapDevice, CAP_DATASET_MAP_ID_SVCSTC, &pDataset_SVCstcErr, &pDataSv);

	if (pDataSv != NULL)
	{
		ShowDatas(pDataSv);
	}
	
/*
	CDvmDataset *pDvmDataset = pCapDevice->GetDvmDataset();
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CString strID = pDvmDataset->m_strID.Mid(2);

	CDvmLogicDevice *pLDevice = (CDvmLogicDevice *)pDvmDataset->GetParent();
	CDvmDataset *pDataset_SVCstcErr = (CDvmDataset *)pLDevice->FindByID(CAP_DATASET_MAP_ID_SVCSTC);

	if (pDataset_SVCstcErr != NULL)
	{
		CDvmData *pDataSv = (CDvmData*)pDataset_SVCstcErr->FindByID(strID);
		ShowDatas(pDataSv);
	}
*/
}

void CSttIecSmvGrid_PkgAnalyze::Release()
{
	delete this;
}

void CSttIecSmvGrid_PkgAnalyze::InitGridTitle()
{
	CString astrGridTitle[3];
	xlang_GetLangStrByFile(astrGridTitle[0], _T("sName"));
	xlang_GetLangStrByFile(astrGridTitle[1], _T("Smv_PkgValue"));
	astrGridTitle[2] = "SCL";
	//= {"����", "����ֵ","SCL"};
	int iGridWidth[3]={400, 300, 300};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 3);
}

void CSttIecSmvGrid_PkgAnalyze::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmValue *pValue = (CDvmValue*)pData;

	if (bInsertRow)
	{
		insertRow(NULL);
	}

	Show_StaticString(pValue, nRow, 0, &pValue->m_strName);
	ShowAttrValue(pValue, nRow, 1, _T("$actual"));
	ShowAttrValue(pValue, nRow, 2, _T("$stand"));

	nRow++;
}


void CSttIecSmvGrid_PkgAnalyze::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	UpdateDatas();
}

void CSttIecSmvGrid_PkgAnalyze::UpdateData(CExBaseObject *pData, int nRow)
{
	CDvmValue *pValue = (CDvmValue*)pData;

	ShowAttrValue(pValue, nRow, 1, _T("$actual"));
	ShowAttrValue(pValue, nRow, 2, _T("$stand"));
}

// void CSttIecSmvGrid_PkgAnalyze::Config()
// {
//
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("��ձ��ķ�������ɹ�."));
//}