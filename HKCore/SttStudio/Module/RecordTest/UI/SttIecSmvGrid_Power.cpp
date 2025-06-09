#include "SttIecSmvGrid_Power.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

CSttIecSmvGrid_Power::CSttIecSmvGrid_Power(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
	m_nCurrPowerIndex = 0;
	m_pCurrPower = NULL;
	m_pDvmDataset_Power = NULL;
}

CSttIecSmvGrid_Power::~CSttIecSmvGrid_Power()
{

}

void CSttIecSmvGrid_Power::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
	m_pDvmDataset_Power = GetDvmDataset();
	
	if (m_pDvmDataset_Power == NULL)
	{
		return;
	}

	if (m_pDvmDataset_Power->GetCount() == 0)
	{
		return ;
	}

	m_nCurrPowerIndex = 0;
	m_pCurrPower = (CDvmData *)m_pDvmDataset_Power->GetAtIndex(m_nCurrPowerIndex);
	ShowCurrPower();
}

void CSttIecSmvGrid_Power::Release()
{
	delete this;
}


BOOL CSttIecSmvGrid_Power::NeedNextAndPrev()
{
	return TRUE;
}

void CSttIecSmvGrid_Power::NextPage()
{
	m_nCurrPowerIndex++;

	if (m_nCurrPowerIndex >= m_pDvmDataset_Power->GetCount())
	{
		m_nCurrPowerIndex = 0;
	}

	m_pCurrPower = (CDvmData *)m_pDvmDataset_Power->GetAt(m_nCurrPowerIndex);
	ShowCurrPower();
}

void CSttIecSmvGrid_Power::PrevPage()
{
	m_nCurrPowerIndex--;

	if (m_nCurrPowerIndex < 0)
	{
		m_nCurrPowerIndex = m_pDvmDataset_Power->GetCount() - 1;
	}

	m_pCurrPower = (CDvmData *)m_pDvmDataset_Power->GetAt(m_nCurrPowerIndex);
	ShowCurrPower();
}

void CSttIecSmvGrid_Power::InitGridTitle()
{
	CString astrGridTitle[5];
	xlang_GetLangStrByFile(astrGridTitle[0], _T("Smv_Category"));
	xlang_GetLangStrByFile(astrGridTitle[1], _T("sAphase"));
	xlang_GetLangStrByFile(astrGridTitle[2], _T("sBphase"));
	xlang_GetLangStrByFile(astrGridTitle[3], _T("sCphase"));
	xlang_GetLangStrByFile(astrGridTitle[4], _T("Native_TotalPow"));
	//= {"类别", "A相", "B相","C相","总功率"};
	int iGridWidth[5]={120, 250, 250, 250, 100};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 5);

	CString strName[8];
	xlang_GetLangStrByFile(strName[0], _T("Native_Voltage"));
	xlang_GetLangStrByFile(strName[1], _T("Native_Current"));
	xlang_GetLangStrByFile(strName[2], _T("Native_EffectiveVol"));
	xlang_GetLangStrByFile(strName[3], _T("Native_EffectiveCurr"));
	xlang_GetLangStrByFile(strName[4], _T("Native_Power"));
	xlang_GetLangStrByFile(strName[5], _T("Native_ReactivePow"));
	xlang_GetLangStrByFile(strName[6], _T("Native_ApparentPow"));
	xlang_GetLangStrByFile(strName[7], _T("Native_PowFactor"));

	SetRowCount(8);
	Show_StaticString(NULL, 0, 0, strName[0]/*_T("电压")*/);
	Show_StaticString(NULL, 1, 0, strName[1]/*_T("电流")*/);
	Show_StaticString(NULL, 2, 0, strName[2]/*_T("电压有效值")*/);
	Show_StaticString(NULL, 3, 0, strName[3]/*_T("电流有效值")*/);
	Show_StaticString(NULL, 4, 0, strName[4]/*_T("功率(W)")*/);
	Show_StaticString(NULL, 5, 0, strName[5]/*_T("无功(Var")*/);
	Show_StaticString(NULL, 6, 0, strName[6]/*_T("视在功率(VA)")*/);
	Show_StaticString(NULL, 7, 0, strName[7]/*_T("功率因素")*/);

	Show_StaticString(NULL, 0, 4, g_strEmptyString);
	Show_StaticString(NULL, 1, 4, g_strEmptyString);
	Show_StaticString(NULL, 2, 4, g_strEmptyString);
	Show_StaticString(NULL, 3, 4, g_strEmptyString);
}

/*
<dataset name="0X4001_dsSV1$Power" id="dsSV1$Power" data-type="" write-mode="0" index="0">
	<data name="" id="P1" data-type="" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step="">
		<value name="A" id="P1$A" data-type="" value="">
			<value name="U" id="P1$A$U" data-type="" value="A相电压-电压A相1">
				<value name="幅值" id="SV1_U1_Ua1$mag" data-type="FLOAT" value="0.00"/>
				<value name="相位" id="SV1_U1_Ua1$ang" data-type="FLOAT" value="0.00"/>
				<value name="频率" id="SV1_U1_Ua1$freq" data-type="FLOAT" value="50.00"/>
			</value>
			<value name="I" id="P1$A$I" data-type="" value="A相电压-电压A相1">
				<value name="幅值" id="SV1_U1_Ua1$mag" data-type="FLOAT" value="0.00"/>
				<value name="相位" id="SV1_U1_Ua1$ang" data-type="FLOAT" value="0.00"/>
				<value name="频率" id="SV1_U1_Ua1$freq" data-type="FLOAT" value="50.00"/>
			</value>
			<value name="P" id="P1$A$P" data-type="float" value="0"/>
			<value name="Q" id="P1$A$Q" data-type="float" value="0"/>
			<value name="S" id="P1$A$S" data-type="float" value="0"/>
			<value name="coef" id="P1$A$coef" data-type="float" value="0"/>
		</value>
		<value name="B" id="P1$B" data-type="" value="">
			<value name="U" id="P1$B$U" data-type="" value="B相电压-电压B相1">
				<value name="幅值" id="SV1_U3_Ub1$mag" data-type="FLOAT" value="0.00"/>
				<value name="相位" id="SV1_U3_Ub1$ang" data-type="FLOAT" value="0.00"/>
				<value name="频率" id="SV1_U3_Ub1$freq" data-type="FLOAT" value="50.00"/>
			</value>
			<value name="I" id="P1$B$I" data-type="" value="B相电压-电压B相1">
				<value name="幅值" id="SV1_U3_Ub1$mag" data-type="FLOAT" value="0.00"/>
				<value name="相位" id="SV1_U3_Ub1$ang" data-type="FLOAT" value="0.00"/>
				<value name="频率" id="SV1_U3_Ub1$freq" data-type="FLOAT" value="50.00"/>
			</value>
			<value name="P" id="P1$B$P" data-type="float" value="0"/>
			<value name="Q" id="P1$B$Q" data-type="float" value="0"/>
			<value name="S" id="P1$B$S" data-type="float" value="0"/>
			<value name="coef" id="P1$B$coef" data-type="float" value="0"/>
		</value>
		<value name="C" id="P1$C" data-type="" value="">
			<value name="U" id="P1$C$U" data-type="" value="C相电压-电压C相1">
				<value name="幅值" id="SV1_U5_Uc1$mag" data-type="FLOAT" value="0.00"/>
				<value name="相位" id="SV1_U5_Uc1$ang" data-type="FLOAT" value="0.00"/>
				<value name="频率" id="SV1_U5_Uc1$freq" data-type="FLOAT" value="50.00"/>
			</value>
			<value name="I" id="P1$C$I" data-type="" value="C相电压-电压C相1">
				<value name="幅值" id="SV1_U5_Uc1$mag" data-type="FLOAT" value="0.00"/>
				<value name="相位" id="SV1_U5_Uc1$ang" data-type="FLOAT" value="0.00"/>
				<value name="频率" id="SV1_U5_Uc1$freq" data-type="FLOAT" value="50.00"/>
			</value>
			<value name="P" id="P1$C$P" data-type="float" value="0"/>
			<value name="Q" id="P1$C$Q" data-type="float" value="0"/>
			<value name="S" id="P1$C$S" data-type="float" value="0"/>
			<value name="coef" id="P1$C$coef" data-type="float" value="0"/>
		</value>
		<value name="P" id="P1$P" data-type="float" value="0"/>
		<value name="Q" id="P1$Q" data-type="float" value="0"/>
		<value name="S" id="P1$S" data-type="float" value="0"/>
		<value name="coef" id="P1$coef" data-type="float" value="0"/>
	</data>
	<data name="" id="P2" data-type="" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step="">
	……
	</data>
</dataset>
*/
void CSttIecSmvGrid_Power::ShowCurrPower()
{
	if (m_pCurrPower == NULL)
	{
		return;
	}

	CDvmValue *pA = (CDvmValue*)m_pCurrPower->FindByID_MmsAttr(_T("$A"));
	CDvmValue *pB = (CDvmValue*)m_pCurrPower->FindByID_MmsAttr(_T("$B")); 
	CDvmValue *pC = (CDvmValue*)m_pCurrPower->FindByID_MmsAttr(_T("$C")); 
	CDvmValue *pP = (CDvmValue*)m_pCurrPower->FindByID_MmsAttr(_T("$P"));
	CDvmValue *pVar = (CDvmValue*)m_pCurrPower->FindByID_MmsAttr(_T("$Q"));
	CDvmValue *pVA = (CDvmValue*)m_pCurrPower->FindByID_MmsAttr(_T("$S"));
	CDvmValue *pCoef = (CDvmValue*)m_pCurrPower->FindByID_MmsAttr(_T("$coef"));

	Show_StaticString(m_pCurrPower, 0, 1, pA->GetAttrByID_MmsAttr(_T("$U")));
	Show_StaticString(m_pCurrPower, 0, 2, pB->GetAttrByID_MmsAttr(_T("$U")));
	Show_StaticString(m_pCurrPower, 0, 3, pC->GetAttrByID_MmsAttr(_T("$U")));
	Show_StaticString(m_pCurrPower, 1, 1, pA->GetAttrByID_MmsAttr(_T("$I")));
	Show_StaticString(m_pCurrPower, 1, 2, pB->GetAttrByID_MmsAttr(_T("$I")));
	Show_StaticString(m_pCurrPower, 1, 3, pC->GetAttrByID_MmsAttr(_T("$I")));

	ShowCurrPower_Ch(pA, 2, 1);
	ShowCurrPower_Ch(pB, 2, 2);
	ShowCurrPower_Ch(pC, 2, 3);

	Show_StaticString(m_pCurrPower, 4, 1, pA->GetAttrByID_MmsAttr(_T("$P")));
	Show_StaticString(m_pCurrPower, 4, 2, pB->GetAttrByID_MmsAttr(_T("$P")));
	Show_StaticString(m_pCurrPower, 4, 3, pC->GetAttrByID_MmsAttr(_T("$P")));
	Show_StaticString(m_pCurrPower, 4, 4, pP->m_strValue);

	Show_StaticString(m_pCurrPower, 5, 1, pA->GetAttrByID_MmsAttr(_T("$Q")));
	Show_StaticString(m_pCurrPower, 5, 2, pB->GetAttrByID_MmsAttr(_T("$Q")));
	Show_StaticString(m_pCurrPower, 5, 3, pC->GetAttrByID_MmsAttr(_T("$Q")));
	Show_StaticString(m_pCurrPower, 5, 4, pVar->m_strValue);

	Show_StaticString(m_pCurrPower, 6, 1, pA->GetAttrByID_MmsAttr(_T("$S")));
	Show_StaticString(m_pCurrPower, 6, 2, pB->GetAttrByID_MmsAttr(_T("$S")));
	Show_StaticString(m_pCurrPower, 6, 3, pC->GetAttrByID_MmsAttr(_T("$S")));
	Show_StaticString(m_pCurrPower, 6, 4, pVA->m_strValue);

	Show_StaticString(m_pCurrPower, 7, 1, pA->GetAttrByID_MmsAttr(_T("$coef")));
	Show_StaticString(m_pCurrPower, 7, 2, pB->GetAttrByID_MmsAttr(_T("$coef")));
	Show_StaticString(m_pCurrPower, 7, 3, pC->GetAttrByID_MmsAttr(_T("$coef")));
	Show_StaticString(m_pCurrPower, 7, 4, pCoef->m_strValue);
}

void CSttIecSmvGrid_Power::ShowCurrPower_Ch(CDvmValue *pChABC, long nRow, long nCol)
{
	CDvmValue *pChU = (CDvmValue*)pChABC->FindByID_MmsAttr(_T("$U"));
	CDvmValue *pChI = (CDvmValue*)pChABC->FindByID_MmsAttr(_T("$I"));

	CString strText,strAmpValue;
	strAmpValue = pChU->GetAttrByID_MmsAttr(_T("$mag"));
	double dTmpValue = CString_To_double(strAmpValue);
	strAmpValue = stt_iec_rcd_get_double_string(dTmpValue,3);
	strText = strAmpValue + _T("V  ") +  pChU->GetAttrByID_MmsAttr(_T("$ang"));
	strText += _T("°");
	Show_StaticString(pChABC, nRow, nCol, strText);

	strAmpValue = pChI->GetAttrByID_MmsAttr(_T("$mag"));
	dTmpValue = CString_To_double(strAmpValue);
	strAmpValue = stt_iec_rcd_get_double_string(dTmpValue,3);
	strText = strAmpValue + _T("A  ") +  pChI->GetAttrByID_MmsAttr(_T("$ang")) + _T("°");
	Show_StaticString(pChABC, nRow + 1, nCol, strText);
}

void CSttIecSmvGrid_Power::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	ShowCurrPower();
}


CDvmDataset* CSttIecSmvGrid_Power::GetDvmDataset()
{
	CCapDeviceBase *pCapDevice = (CCapDeviceBase *)m_pCapDevice;
	ASSERT(iecfg_IsTypeAnalog(pCapDevice->m_nType));

	CDvmDataset *pDatasetRef = pCapDevice->GetDvmDataset();  //此处获取的是dsSV1、dsSV2……

	if (pDatasetRef == NULL)
	{
		return NULL;
	}

	CDvmLogicDevice *pLDevice = (CDvmLogicDevice *)pDatasetRef->GetParent();
	return ((CDvmDataset *)pLDevice->FindByID(pDatasetRef->m_strID + _T("$Power")));
}
