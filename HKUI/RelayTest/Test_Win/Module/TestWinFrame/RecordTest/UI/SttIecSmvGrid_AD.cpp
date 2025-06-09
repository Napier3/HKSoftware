#include "SttIecSmvGrid_AD.h"
#include "../../../../Module/SmartCap/XSmartCapMngr.h"
#include "../../../../Module/XLanguage/QT/XLanguageAPI_QT.h"

CSttIecSmvGrid_AD::CSttIecSmvGrid_AD(QWidget* pparent):CSttIecChsGridBase(pparent)
{
	m_pIecRcdFuncWidget = this;
}

CSttIecSmvGrid_AD::~CSttIecSmvGrid_AD()
{

}

void CSttIecSmvGrid_AD::IecRcdFunc(CCapDeviceBase *pCapDevice)
{
	m_pCapDevice = pCapDevice;
	CDvmDataset *pDvmDataset = GetDvmDataset();  //dsSV1、dsSV2……
	ShowDatas(pDvmDataset);
}

void CSttIecSmvGrid_AD::Release()
{
	delete this;
}

void CSttIecSmvGrid_AD::InitGridTitle()
{
	CString astrGridTitle[5];
	astrGridTitle[0]= "AD1";
	astrGridTitle[1]="AD2";
	astrGridTitle[2]="AD1-AD2";
	astrGridTitle[3]="|AD1-AD2|";
	xlang_GetLangStrByFile(astrGridTitle[4], _T("Gradient_Phase"));
	//= {"AD1", "AD2", "AD1-AD2", "|AD1-AD2|", "相位差"};
	int iGridWidth[5]={250, 250, 150, 150, 150};
	QExBaseListGridBase::InitGridTitle(astrGridTitle, iGridWidth, 5);
}

//extern long g_nSmvFirstChIsTdelay;
// 
// void CSttIecSmvGrid_AD::ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars)
// {
// 	DisConnectAll_SigSlot();
// 	m_pCurrData = NULL;
// 
// 	if (pDatas == NULL)
// 	{
// 		SetRowCount(0);
// 		return;
// 	}
// 
// 	m_pDatas = pDatas;
// 	CDvmData *pData = NULL;	
// 	POS pos = pDatas->GetHeadPosition();
// 	int nRowIndex = 0;//zhouhj Qt中不包括标题行
// 	long nCalRows = GetDatasCount();//zhouhj Qt中不包括标题行
// 	SetRowCount(nCalRows, bResetScrollBars);
// 
// 	if (g_nSmvFirstChIsTdelay)
// 	{
// 		if (pos != NULL)
// 		{
// 			pData = (CDvmData *)m_pDatas->GetNext(pos);
// 			pData->m_dwReserved = 1;
// 		}
// 	}
// 
// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData *)pDatas->GetNext(pos);
// 
// 		if (pData->m_dwReserved == 1)
// 		{
// 			continue;
// 		}
// 
// 		CDvmData *pAD = FindAD(pData, pDatas);
// 
// 		if (pAD == NULL)
// 		{
// 			continue;
// 		}
// 
// 		float fValue1, fValue2, fValue3 = 0.0;   //AD1-AD2, |AD1-AD2|，相位差
// 		CalAD1_AD2(fValue1, fValue2, fValue3, pData, pAD);
// 
// 		Show_StaticString(pData, nRowIndex, 0, &pData->m_strName);
// 		Show_StaticString(pAD, nRowIndex, 1, &pAD->m_strName);
// 		Show_Float(pData, nRowIndex, 2, 3, &fValue1);   //精度：三位小数
// 		Show_Float(pData, nRowIndex, 3, 3, &fValue2);
// 		Show_Float(pData, nRowIndex, 4, 3, &fValue3);
// 		
// 		nRowIndex++;
// 	}
// 
// 	pos = pDatas->GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData *)pDatas->GetNext(pos);
// 		pData->m_dwReserved = 0;
// 	}
// 
// 	SetRowCount(nRowIndex, bResetScrollBars);
// 	AfterShowDatas(1, bResetScrollBars);
// }

void CSttIecSmvGrid_AD::IecRcdFuncUpdate(CCapDeviceBase *pCapDevice)
{
	CXSttCap_61850 *pXSttCap_61850 = g_theXSmartCapMngr->GetSttCap_61850();
	CXCapPkgBufferMngrInterface *pXCapPkgBufferMngr = pXSttCap_61850->GetSttXCapBufferMngr();
	//pXCapPkgBufferMngr->LogBufferPos();
	pXSttCap_61850->UpdateDvmDeviceDatas();

	UpdateDatas();
}

// void CSttIecSmvGrid_AD::UpdateDatas()
// {
// 	if (m_pDatas == NULL)
// 	{
// 		return;
// 	}
// 
// 	CDvmData *pData = NULL;	
// 	POS pos = m_pDatas->GetHeadPosition();
// 	int nRowIndex = 0;
// 
// 	if (g_nSmvFirstChIsTdelay)
// 	{
// 		if (pos != NULL)
// 		{
// 			pData = (CDvmData *)m_pDatas->GetNext(pos);
// 			pData->m_dwReserved = 1;
// 		}
// 	}
// 
// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData *)m_pDatas->GetNext(pos);
// 
// 		if (pData->m_dwReserved == 1)
// 		{
// 			continue;
// 		}
// 
// 		CDvmData *pAD = FindAD(pData, m_pDatas);
// 
// 		if (pAD == NULL)
// 		{
// 			continue;
// 		}
// 
// 		float fValue1, fValue2, fValue3 = 0.0;   //AD1-AD2, |AD1-AD2|，相位差
// 		CalAD1_AD2(fValue1, fValue2, fValue3, pData, pAD);
// 
// 		Show_Float(pData, nRowIndex, 2, 3, &fValue1);  //精度：三位小数
// 		Show_Float(pData, nRowIndex, 3, 3, &fValue2);
// 		Show_Float(pData, nRowIndex, 4, 3, &fValue3);
// 
// 		nRowIndex++;
// 	}
// 
// 	pos = m_pDatas->GetHeadPosition();
// 
// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData *)m_pDatas->GetNext(pos);
// 		pData->m_dwReserved = 0;
// 	}
// }

//根据pChData，查找对应的双AD的通道
// CDvmData* CSttIecSmvGrid_AD::FindAD(CDvmData *pChData, CExBaseList *pDvmDataset)
// {
// 	CDvmData *pFind = NULL;
// 	POS pos = pDvmDataset->GetHeadPosition();
// 	CDvmData *pData = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pData = (CDvmData *)pDvmDataset->GetNext(pos);
// 
// 		if (pData == pChData)
// 		{
// 			continue;
// 		}
// 
// 		if (pData->m_dwReserved == 1)
// 		{
// 			continue;
// 		}
// 
// 		long nLen1 = pChData->m_strName.GetLength();
// 		long nLen2 = pData->m_strName.GetLength();
// 
// 		if (nLen1 != nLen2)
// 		{
// 			continue;
// 		}
// 
// 		//默认只有最后一个字符不一样，例如：第一组保护电流A相-保护电流A相1 + 第一组保护电流A相-保护电流A相2
// 		CString strName1, strName2;
// 		strName1 = pChData->m_strName.Left(nLen1 -1);
// 		strName2 = pData->m_strName.Left(nLen2 - 1);
// 
// 		if (strName1 == strName2)
// 		{
// 			pFind = pData;
// 			pChData->m_dwReserved = 1;
// 			pData->m_dwReserved = 1;
// 			break;
// 		}
// 	}
// 
// 	return pFind;
// }

//fValue1 = AD1-AD2；fValue2 = |AD1 - AD2|；fValue3 = 相位差
// void CSttIecSmvGrid_AD::CalAD1_AD2(float &fValue1, float &fValue2, float &fValue3, CDvmData *pAD1, CDvmData *pAD2)
// {
// 	float fMag1, fMag2, fAng1, fAng2 = 0.0;
// 	CString strMagID, strAngID;
// 	strMagID = _T("$mag");
// 	strAngID = _T("$ang");
// 
// 	CString strMag1 = pAD1->m_strID + strMagID;
// 	CDvmValue *pMag1 = (CDvmValue*)pAD1->FindByID(strMag1);	
// 	CString strMag2 = pAD2->m_strID + strMagID;
// 	CDvmValue *pMag2 = (CDvmValue*)pAD2->FindByID(strMag2);
// 
// 	if (pMag1 != NULL && pMag2 != NULL)
// 	{
// 		fMag1 = CString_To_double(pMag1->m_strValue);
// 		fMag2 = CString_To_double(pMag2->m_strValue);
// 	}
// 
// 	CString strAng1 = pAD1->m_strID + strAngID;
// 	CDvmValue *pAng1 = (CDvmValue*)pAD1->FindByID(strAng1);	
// 	CString strAng2 = pAD2->m_strID + strAngID;
// 	CDvmValue *pAng2 = (CDvmValue*)pAD2->FindByID(strAng2);	
// 
// 	if (pAng1 != NULL && pAng2 != NULL)
// 	{
// 		fAng1 = CString_To_double(pAng1->m_strValue);
// 		fAng2 = CString_To_double(pAng2->m_strValue);
// 	}
// 
// 	fValue1 = fMag1 - fMag2;
//     fValue2 = fabsf(fValue1);
// 	fValue3 = fAng1 - fAng2;
// }

/*
<dataset name="0X4001_dsSV1$AD" id="dsSV1$AD" data-type="" write-mode="0" index="0">
	<data name="A相保护电流-保护电流A相1" id="AD1" data-type="" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step="">
		<value name="Ch1" id="AD1$Ch1" data-type="" value="A相保护电流-保护电流A相1">
			<value name="幅值" id="SV1_I1_Ia1$mag" data-type="FLOAT" value="0.00"/>
			<value name="相位" id="SV1_I1_Ia1$ang" data-type="FLOAT" value="0.00"/>
			<value name="频率" id="SV1_I1_Ia1$freq" data-type="FLOAT" value="50.00"/>
		</value>
		<value name="Ch2" id="AD1$Ch2" data-type="" value="A相保护电流-保护电流A相2">
			<value name="幅值" id="SV1_I2_Ia1$mag" data-type="FLOAT" value="0.00"/>
			<value name="相位" id="SV1_I2_Ia1$ang" data-type="FLOAT" value="0.00"/>
			<value name="频率" id="SV1_I2_Ia1$freq" data-type="FLOAT" value="50.00"/>
		</value>
		<value name="幅值差AD1-AD2" id="AD1$dmag" data-type="FLOAT" value=""/>
		<value name="幅值差|AD1-AD2|" id="AD1$dmag_abs" data-type="FLOAT" value=""/>
		<value name="相位差AD1-AD2" id="AD1$dang" data-type="FLOAT" value=""/>
		<value name="相位差|AD1-AD2|" id="AD1$dang_abs" data-type="FLOAT" value=""/>
	</data>
	<data name="B相保护电流-保护电流B相1" id="AD2" data-type="" value="" unit="" min="" max="" format="" index="0" time="0" change="0" step="">
		……
	</data>
	……
</dataset>
*/
//一个data是一行
void CSttIecSmvGrid_AD::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDvmData *pChData = (CDvmData*)pData;

	if (bInsertRow)
	{
		insertRow(NULL);
	}
	
	ShowDataEx(pChData, nRow);

	nRow++;
}

void CSttIecSmvGrid_AD::UpdateData(CExBaseObject *pData, int nRow)
{
	CDvmData *pChData = (CDvmData*)pData;

	ShowDataEx(pChData, nRow);
}

void CSttIecSmvGrid_AD::ShowDataEx(CDvmData *pChData, int nRow)
{
	CString strID = pChData->m_strID + _T("$Ch1");   //AD1
	CDvmValue *pCh1 = (CDvmValue*)pChData->FindByID(strID);
	Show_StaticString(pCh1, nRow, 0, &pCh1->m_strValue);

	strID = pChData->m_strID + _T("$Ch2");           //AD2
	CDvmValue *pCh2 = (CDvmValue*)pChData->FindByID(strID);
	Show_StaticString(pCh2, nRow, 1, &pCh2->m_strValue);

	ShowAttrValue(pChData, nRow, 2, _T("$dmag"));   //AD1-AD2
	ShowAttrValue(pChData, nRow, 3, _T("$dmag_abs"));  //|AD1 - AD2|
	ShowAttrValue(pChData, nRow, 4, _T("$dang")); //相位差
}

//dsSV1$AD、dsSV2$AD
CDvmDataset* CSttIecSmvGrid_AD::GetDvmDataset()
{
	CCapDeviceBase *pCapDevice = (CCapDeviceBase *)m_pCapDevice;
	ASSERT(iecfg_IsTypeAnalog(pCapDevice->m_nType));

	CDvmDataset *pDatasetRef = pCapDevice->GetDvmDataset();  //此处获取的是dsSV1、dsSV2……

	if (pDatasetRef == NULL)
	{
		return NULL;
	}

	CDvmLogicDevice *pLDevice = (CDvmLogicDevice *)pDatasetRef->GetParent();
	return ((CDvmDataset *)pLDevice->FindByID(pDatasetRef->m_strID + _T("$AD")));
}