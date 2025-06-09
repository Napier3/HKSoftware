//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��


#include "stdafx.h"
#include "DvmDatasetGrid.h"

#define DVMDATASET_COL_INDEX      0
#define DVMDATASET_COL_NAME       1
#define DVMDATASET_COL_ID            2
#define DVMDATASET_COL_DATATYPE      3
#define DVMDATASET_COL_UNIT            4
#define DVMDATASET_COL_VALUE      5

#define DVMDATASET_COLS           6

//int nMaxCols[MAX_TABLE_TYPE] = {6, 5�� 6�� 6�� 7�� 6�� 9�� 9 };//ÿ�ֱ�����Ͷ�Ӧ��������

CDvmDatasetGrid::CDvmDatasetGrid()
{
	//��ʼ������

	//��ʼ����Ա����
	m_oDataType.AddNewValue(_T("long"), _T("long"), _T("0"));
	m_oDataType.AddNewValue(_T("string"), _T("string"), _T("1"));
	m_oDataType.AddNewValue(_T("float"), _T("float"), _T("2"));
	m_oDataType.AddNewValue(_T("time"), _T("time"), _T("3"));

	m_nAdjustBeginCol = 1;

	m_nTableType = UNKNOWN_TABLE;

	m_nTableColNum = 0;
}

CDvmDatasetGrid::~CDvmDatasetGrid()
{

}


void CDvmDatasetGrid::InitGrid()
{
	//m_nAdjustBeginCol = 1;
	ASSERT(m_nTableColNum>0);
	ASSERT(m_nTableType != UNKNOWN_TABLE);
	

	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(m_nTableColNum);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}


void CDvmDatasetGrid::InitGridTitle()
{
	switch(m_nTableType)
	{
	case CLIENT_TABLE://�ͻ���
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("���"),_T("�ͻ�����"),_T("�ͻ����"),_T("������ģ����"),_T("��Ȩģ����"), _T("��Ȩ���������")};
			int iGridWidth[MAX_TABLE_TYPE]={100,150,100, 100, 100,100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	case SOFTDOG_TABLE:                       //�������
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("���"),_T("��������"),_T("������Ա����"),_T("��Ȩ��Ȩ����Ϣ"),_T("������Ա����")};
			int iGridWidth[MAX_TABLE_TYPE]={100,150,100, 100, 100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	case CLIENT_NEW_TEMPLATE_TABLE:           //�ͻ�ģ���
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("���"),_T("ģ������"),_T("������Ա"),_T("�ϴ�����"),_T("�����Ա"), _T("�������")};
			int iGridWidth[MAX_TABLE_TYPE]={100,150,100, 100, 100,100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	case OLD_DEVELOP_TASK_TABLE:              //��ʷ���������
	case CLIENT_OLD_TEMPLATE_TABLE:           //�ͻ���ʷģ���
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("���"),_T("�汾"),_T("������Ա"),_T("�ϴ�����"),_T("�����Ա"), _T("�������")};
			int iGridWidth[MAX_TABLE_TYPE]={100,150,100, 100, 100,100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	case DEVELOP_TASK_TABLE:                  //���������
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("���"),_T("ģ������"), _T("״̬"),_T("������Ա"),_T("�ϴ�����"),_T("�����Ա"), _T("�������")};
			int iGridWidth[MAX_TABLE_TYPE]={100,150,100, 100, 100, 100, 100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	case DEVELOPER_TEMPLATE_STATISTICS_TABLE: //������Աģ�忪��ͳ�Ʊ�
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("���"),_T("������Ա"), _T("35KV������"),_T("110KV"),_T("220kV��·"),_T("220KV��ѹ��"), _T("220KVĸ��"), _T("220KV����"), _T("����")};
			int iGridWidth[MAX_TABLE_TYPE]={100,100,100, 100, 100,100, 100, 100, 100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	case DEVELOPER_CLIENT_STATISTICS_TABLE:   //�ͻ���λģ�忪��ͳ�Ʊ�
		{
			CString astrGridTitle[MAX_TABLE_TYPE] = {_T("���"),_T("�ͻ���λ"), _T("35KV������"),_T("110KV"),_T("220kV��·"),_T("220KV��ѹ��"), _T("220KVĸ��"), _T("220KV����"), _T("����")};
			int iGridWidth[MAX_TABLE_TYPE]={100,100,100, 100, 100,100, 100, 100, 100};
			CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, m_nTableColNum);
		}
		break;
	default:
		break;
	}
}

void CDvmDatasetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	if (pData->GetClassID() != DVMCLASSID_CDVMDATA)
	{
		return;
	}

	CDvmData *pDvmData = (CDvmData*)pData;

	Show_Index(pDvmData, nRow, DVMDATASET_COL_INDEX);
	Show_String(pDvmData, nRow, DVMDATASET_COL_NAME, &pDvmData->m_strName);
	Show_String(pDvmData, nRow, DVMDATASET_COL_ID, &pDvmData->m_strID);
	Show_ComboBox(pDvmData, &m_oDataType, nRow, DVMDATASET_COL_DATATYPE, &pDvmData->m_strDataType);
	Show_String(pDvmData, nRow, DVMDATASET_COL_UNIT, &pDvmData->m_strUnit);
	Show_String(pDvmData, nRow, DVMDATASET_COL_VALUE, &pDvmData->m_strValue);

	//Show_Check(pShortData, nRow, DVMDATASET_COL_ID, (long*)&pShortData->m_strID);
// 
// #ifdef _UNICODE
// 	if (wcsicmp(pShortData->m_strDataTypeID, _T("bool")) == 0)
// #else
// 	if (stricmp(pShortData->m_strDataTypeID, _T("bool") == 0)
// #endif
// 	{
// 		Show_Check(pShortData, nRow, DVMDATASET_COL_VALUE, (long*)&pShortData->m_dwItemData);
// 	}
// 	else
// 	{
// 		Show_DataType_Val(pShortData, nRow, DVMDATASET_COL_VALUE, pShortData->m_strDataTypeID, (long*)&pShortData->m_dwItemData);
// 	}

	nRow++;
}

CDataType* CDvmDatasetGrid::FindDataType(const CString &strDataType)
{
	return &m_oDataType;
}


void  CDvmDatasetGrid::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	
}


void CDvmDatasetGrid::OnDataSelChanged(int nRow, int nCol)
{
	//CShortData *pData = (CShortData*)GetCurrSelData(1);
	CShortData *pData = (CShortData*)GetDataRow(nRow, 1);

	if (pData == NULL)
	{
		return;
	}

}

void CDvmDatasetGrid::SetTableType(GridType nTableType)
{
	m_nTableType = nTableType;
	switch(m_nTableType)
	{
	case CLIENT_TABLE://�ͻ���
	case CLIENT_NEW_TEMPLATE_TABLE:           //�ͻ�ģ���
	case OLD_DEVELOP_TASK_TABLE:              //��ʷ���������
	case CLIENT_OLD_TEMPLATE_TABLE:           //�ͻ���ʷģ���
		{
			m_nTableColNum = 6;
		}
		break;
	case SOFTDOG_TABLE:                       //�������
		{
			m_nTableColNum = 5;
		}
		break;
	case DEVELOP_TASK_TABLE:                  //���������
		{
			m_nTableColNum = 7;
		}
		break;
	case DEVELOPER_TEMPLATE_STATISTICS_TABLE: //������Աģ�忪��ͳ�Ʊ�
	case DEVELOPER_CLIENT_STATISTICS_TABLE:   //�ͻ���λģ�忪��ͳ�Ʊ�
		{
			m_nTableColNum = 9;
		}
		break;
	default:
		break;
	}
}

