#include "StdAfx.h"
#include "PdfConfigData.h"

CPdfConfigData::CPdfConfigData(void)
{
}

CPdfConfigData::~CPdfConfigData(void)
{
	m_oPdfConfigDTS.DeleteAll();
}

void CPdfConfigData::LoadPdfConfig(const CString &strFile)
{
	m_strFileName = strFile;
	m_oPdfConfigDTS.OpenXmlFile(m_strFileName, CDataMngrXmlRWKeys::g_pXmlKeys);

	GetPdfDataType(TALBE_TYPE_PARAMETER);
	GetPdfDataType(TALBE_TYPE_SETTING);
	GetPdfDataType(TALBE_TYPE_ENA);
	GetPdfDataType(TALBE_TYPE_MATRIX);

	GetPdfDataType(HEAD_NAME_COL);
	GetPdfDataType(HEAD_DW_COL);
	GetPdfDataType(HEAD_VALUE_COL);

	GetPdfDataType(DEL_TILTE_ROW);
	GetPdfDataType(DEL_ROW_DATA);
}
void CPdfConfigData::SavePdfConfig()
{
	m_oPdfConfigDTS.SaveXmlFile(m_strFileName, CDataMngrXmlRWKeys::g_pXmlKeys);
}

CDataType *CPdfConfigData::GetPdfDataType(CString strKey)
{
	CDataType *pDataType = (CDataType*)m_oPdfConfigDTS.FindByID(strKey);
	if(pDataType == NULL)
	{
		pDataType = new CDataType();
		pDataType->m_strName = strKey;
		pDataType->m_strID = strKey;
		m_oPdfConfigDTS.AddNewChild(pDataType);
	}
	return pDataType;
}

//�жϱ���������
BOOL CPdfConfigData::IsDatasetTitle(const CString &strText, CString &strTileName)
{
	if(IsCheckTitle(TALBE_TYPE_PARAMETER, strText))
	{
		strTileName = TALBE_TYPE_PARAMETER;
		return TRUE;
	}
	if(IsCheckTitle(TALBE_TYPE_SETTING, strText))
	{
		strTileName = TALBE_TYPE_SETTING;
		return TRUE;
	}
	if(IsCheckTitle(TALBE_TYPE_ENA, strText))
	{
		strTileName = TALBE_TYPE_ENA;
		return TRUE;
	}
	if(IsCheckTitle(TALBE_TYPE_MATRIX, strText))
	{
		strTileName = TALBE_TYPE_MATRIX;
		return TRUE;
	}

	return FALSE;
}

//������ð�������
BOOL CPdfConfigData::IsCheckTitle(const CString &strKey, const CString &strText)
{
	CDataType *pDataType = (CDataType*)m_oPdfConfigDTS.FindByID(strKey);

	CDataTypeValue* pDataV = NULL;
	POS pos = pDataType->GetHeadPosition();
	while (pos != NULL)
	{
		pDataV = (CDataTypeValue *)pDataType->GetNext(pos);
		if(strText.Find(pDataV->m_strName) != -1)
		{
			return TRUE;
		}
	}
	return FALSE;
}

//���Ʋ�����ȫ��ͬ����
BOOL CPdfConfigData::IsCheckHead(const CString &strKey, const CString &strText)
{
	CDataType *pDataType = (CDataType*)m_oPdfConfigDTS.FindByID(strKey);

	CDataTypeValue* pDataV = NULL;
	POS pos = pDataType->GetHeadPosition();
	while (pos != NULL)
	{
		pDataV = (CDataTypeValue *)pDataType->GetNext(pos);
		if(pDataV->m_strName == strText)
		{
			return TRUE;
		}
	}
	return FALSE;
}


//��ȡɾ����Ϣ
CDataType *CPdfConfigData::GetDelRowTilte()
{
	return (CDataType*)m_oPdfConfigDTS.FindByID(DEL_TILTE_ROW);
}
CDataType *CPdfConfigData::GetDelRowData()
{
	return (CDataType*)m_oPdfConfigDTS.FindByID(DEL_ROW_DATA);
}

