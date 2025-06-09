#include "StdAfx.h"
#include "RptJsonData.h"

CRptJsonData::CRptJsonData(void)
{
	m_root = NULL;
	m_node = NULL;
}

CRptJsonData::~CRptJsonData(void)
{
	DeleteAll();
	if(m_root != NULL)
		CJSON_Delete(m_root);
}

BOOL CRptJsonData::OpenXmlFile(const CString &strFile, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
	char* data;
	data = ReadFile(strFile);
	if (data == NULL)
	{
		return false;
	}

	DeleteAll();

	//��ȡ���ڵ�
	m_root = CJSON_Parse(data);
	free(data);

	if(m_root == NULL)
		return false;

	ReadItem(m_root, NULL);
	return true;
}

char* CRptJsonData::ReadFile(const CString &strFile)
{
	CFile file;
	file.Open((LPCTSTR)strFile, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeRead);//���ļ�
	int nlen = file.GetLength();//��ȡ�ļ��ܳ���

	char* data;
	data = (char*)malloc(nlen + 1);

	file.SeekToBegin();//����λ��������ʼ�ֽ�
	file.Read(data,nlen);//�����
	file.Close();//�ر��ļ�

	return data;
}

void CRptJsonData::ReadItem(CJSON* Fitem, CRptJsonData* pParent)
{
	CJSON* item;
	item = Fitem->child;

	if(pParent == NULL)
		pParent = this;

	while (item != NULL)
	{
		CRptJsonData* pObj = new CRptJsonData();
		pObj->m_node = item;		
		pParent->AddTail(pObj);

		CJSON* childItem = item->child;
		if (childItem != NULL)
		{
			ReadItem(item, pObj);			
		}

		item = item->next;
	}
}

BOOL CRptJsonData::SaveXmlFile(const CString &strFile, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType)
{
	CFile file;
	file.Open((LPCTSTR)strFile, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);//���ļ�

	char* data = CJSON_Print(m_root);

	file.SeekToBegin();//����λ��������ʼ�ֽ�
	file.Write(data,strlen(data));//����д
	file.Close();//�ر��ļ�

	free(data);
	return true;
}