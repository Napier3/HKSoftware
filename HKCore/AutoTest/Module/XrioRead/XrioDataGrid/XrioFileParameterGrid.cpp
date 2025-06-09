// XrioFileParameterGrid.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XrioFileParameterGrid.h"
#include "..\..\XrioRead\XrioCustomParameter.h"
#include "..\..\XrioRead\XrioObjectCfg.h"
#include "..\..\XrioRead\XrioListCfg.h"
#include "..\XrioReadTool\XrioReadTool.h"

#define XRIO_PARAMETER_TABLE_COLS       12

#define XRIO_PARAMETER_COL_INDEX        0
#define XRIO_PARAMETER_COL_STATE        1
#define XRIO_PARAMETER_COL_NAME         2
#define XRIO_PARAMETER_COL_ID           3
#define XRIO_PARAMETER_COL_DESCRIPTION  4
#define XRIO_PARAMETER_COL_DATATYPE     5
#define XRIO_PARAMETER_COL_REFVALUE     6
#define XRIO_PARAMETER_COL_VALUE        7
#define XRIO_PARAMETER_COL_UNIT         8
#define XRIO_PARAMETER_COL_MIN          9
#define XRIO_PARAMETER_COL_MAX          10

// CXrioFileParameterGrid

CXrioFileParameterGrid::CXrioFileParameterGrid()
{
	m_nAdjustBeginCol = 1;
}

CXrioFileParameterGrid::~CXrioFileParameterGrid()
{
}

// CXrioFileParameterGrid ��Ա����
void CXrioFileParameterGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(XRIO_PARAMETER_TABLE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}

void CXrioFileParameterGrid::InitGridTitle()
{
	CString astrGridTitle[XRIO_PARAMETER_TABLE_COLS] = {_T("���"),_T("״̬"),_T("����"),_T("ID"),_T("����"),_T("��������"),_T("�ο�ֵ"),
		_T("ֵ"),_T("��λ"),_T("��Сֵ"),_T("���ֵ"),_T("��ʽ")};
	int iGridWidth[XRIO_PARAMETER_TABLE_COLS]={50, 50, 150, 50, 300, 80, 80, 80, 50, 80, 80, 150};
	SetColumnCount(XRIO_PARAMETER_TABLE_COLS);
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, XRIO_PARAMETER_TABLE_COLS);
}

void CXrioFileParameterGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	//CXrioCustomParameter *pCustomParameter = ((CXrioTplMapObj *)pData)->m_pXrioParas;
	CXrioCustomParameter *pCustomParameter = ((CXrioCustomParameter *)pData);

	if (pCustomParameter == NULL)
	{
		Show_Index(pCustomParameter, nRow, XRIO_PARAMETER_COL_INDEX);//���
		nRow++;
		return;
	}
//	_T("���"),_T("״̬"),_T("����"),_T("Id"),_T("����"),_T("��������"),_T("�ο�ֵ"),_T("ֵ"),_T("��λ"),_T("��Сֵ"),_T("���ֵ"),_T("��ʽ")

	Show_Index(pCustomParameter, nRow, XRIO_PARAMETER_COL_INDEX);//���
	long lEnabled;
	if (pCustomParameter->m_strEnabled == _T("true"))
	{
		lEnabled = 1;
	}
	else
	{
		lEnabled = 0;
	}
	Show_Check(pCustomParameter, nRow, XRIO_PARAMETER_COL_STATE, &lEnabled);//״̬
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_NAME, pCustomParameter->m_strName);   //����
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_ID, pCustomParameter->m_strID);	//Id
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_DESCRIPTION, pCustomParameter->m_strDescription);	//����
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_DATATYPE, pCustomParameter->m_strDataType);	//��������

	Show_String(pCustomParameter, nRow, XRIO_PARAMETER_COL_VALUE, &pCustomParameter->m_strValue);					//ֵ
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_UNIT, pCustomParameter->m_strUnit);  //��λ
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_MIN, pCustomParameter->m_strMinValue);		//��Сֵ
	Show_StaticString(pCustomParameter, nRow, XRIO_PARAMETER_COL_MAX, pCustomParameter->m_strMaxValue);		//���ֵ

//	POS pos = pCustomParameter->GetHeadPosition();
//	UINT nClassID = XRIOCLASSID_BASECLASS;
//	CExBaseObject* pDataObject = NULL;
//
//	while(pos)
//	{
//		pDataObject = pCustomParameter->GetNext(pos);
//		nClassID = pDataObject->GetClassID();
//        switch(nClassID)
//		{
//		case XRIOCLASSID_UNIT:
//			Show_StaticString(pCustomParameter, nRow, 8, ((CXrioUnit*)pDataObject)->m_strUnit);				//��λ
//			break;
//		case XRIOCLASSID_ENABLEDREFLIST:
//			break;
//		case XRIOCLASSID_VALUEREFLIST:
//			break;
//		case XRIOCLASSID_ENUMLIST:
////			Show_ComboBox((CXrioEnumList*)pDataObject, nRow, 6, _T(""));
//			break;
//		default:
//			break;
//		}
//	}

	nRow++;
}
