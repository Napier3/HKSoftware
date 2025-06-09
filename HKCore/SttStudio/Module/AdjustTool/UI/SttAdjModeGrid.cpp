//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��


#include "stdafx.h"
#include "SttAdjModeGrid.h"
#ifndef NOT_USE_XLANGUAGE
#include "../../../Local/SttAdjMain/XLanguageResource_SttAdjMain.h"
#endif

CSttAdjModeGrid::CSttAdjModeGrid()
{
	//��ʼ������
	//m_strChildDataTypeID = CommDBData_ID_Record;		//STT_ADJ_DATA_TYPE_SttModel;

	//m_strChildDataTypeID = CommDBData_ID_Record;  //STT_ADJ_DATA_TYPE_SttModel;

	m_strChildDataTypeID = CommDBData_ID_Record;
}

CSttAdjModeGrid::~CSttAdjModeGrid()
{

}


void CSttAdjModeGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(5);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CSttAdjModeGrid::InitGridTitle()
{
#ifndef NOT_USE_XLANGUAGE
	CString astrTitle[5] = {/*_T("���")*/g_sLangTxt_Index,  /*_T("����")*/g_sLangTxt_SttAdjMain_Name,  /*_T("����")*/g_sLangTxt_Type, /* _T("�ͺ�")*/g_sLangTxt_SttAdjMain_AppModel,   /*_T("ģ����")*/g_sLangTxt_SttAdjMain_ModuleCount};//ģ��ID
#else
	CString astrTitle[5] = {_T("���"),  _T("����"),  _T("����"),  _T("�ͺ�"),   _T("ģ����")};//ģ��ID
#endif
	CString astrAttrs[5] = {_T(""),  _T("name"),  _T("id"),  _T("value"),  _T("value")};
	int nWidth[5]  =  {40,  120,  100,  100,  100};


	CExBaseListGrid::InitGridTitle(astrTitle, nWidth, 5);
	InitGridColAttrs(astrAttrs, 5);
}

// 2020-11-23 mym add
// д���Լ��ģ��⺯���ǻ����е��õĺ�������ShowDatas�����У�ÿһ�����ݵ���һ�Σ�Ȼ��nRow�Ӽӣ�������һ�У�
void CSttAdjModeGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{		
	if (pData->GetClassID() != DVMCLASSID_CDVMDATA)//DTMCLASSID_CDATAGROUP
	{
		return;
	}

	CDvmData * pDvmData_Value= NULL;
	CString   strModel, strType;

	POS posValue = NULL;

	CDvmData *pDvmData  = (CDvmData*)pData;
	Show_Index(pDvmData, nRow, 0);
	Show_StaticString(pDvmData, nRow, 1, &pData->m_strName);

	posValue = pDvmData->GetHeadPosition();
	while(posValue != NULL)
	{
		pDvmData_Value  = (CDvmData *)pDvmData->GetNext(posValue);
		if (pDvmData_Value->m_strID=="Model")//��ʱ��ȡID=="Model" ��ʱ��VALUEֵ��
		{
			strModel  = pDvmData_Value->m_strValue;
		}
		else if (pDvmData_Value->m_strID=="Type")//��ʱ��ȡID=="Model" ��ʱ��VALUEֵ��
		{
#ifndef NOT_USE_XLANGUAGE
			if (pDvmData_Value->m_strValue=="0")
				strType  = /*"װ��"*/g_sLangTxt_SttAdjMain_Device;
			if (pDvmData_Value->m_strValue=="1")
				strType  = /*"ģ��"*/g_sLangTxt_Module;
#else
			if (pDvmData_Value->m_strValue=="0")
				strType  = "װ��";
			if (pDvmData_Value->m_strValue=="1")
				strType  = "ģ��";
#endif
		}
		
	}
	Show_StaticString(pDvmData, nRow, 2, strType);//pData->m_strID);

	Show_StaticString(pDvmData, nRow, 3, &strModel);

	//for (long nCol=2; nCol<m_nCols; nCol++)
	//{
	// 	ShowAttrCol(pChDrvPos, nRow, nCol);
	//}

	nRow++;
}
