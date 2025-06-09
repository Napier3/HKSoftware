#include "StdAfx.h"
#include "JsonPathData.h"
#include "../API/StringConvert/String_Utf8_To_Gbk.h"
#include "../API/StringConvert/String_Gbk_To_Utf8.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int CJsonData::g_iJson_Find_ItemData = 0;

CJsonData::CJsonData()
{
	m_node = NULL;
}
CJsonData::~CJsonData()
{
}

void CJsonData::ReadNode(CJSON *jNode,map<CJSON*, CString> *_mapBkmk)
{
	m_node = jNode;
	if(m_node == NULL)
		return ;
	m_strName = m_node->string;

	int nDestLen = 0;
	unsigned char *pszGbk = NULL;

	CJSON* item;
	item = m_node->child;
	while (item != NULL)
	{
		CJsonData* pObj = new CJsonData();
		pObj->SetParent(this);	
		AddTail(pObj);

		if(item->valuestring != NULL)			//20230824 luozibing���UTF-8��ʽ��������������
		{			
			if(IsChinese(item->valuestring))
				if(is_str_utf8(item->valuestring))
				{
					//20230928 huangliang ʹ�ü��ݺ����������
					nDestLen = strlen(item->valuestring);
					utf8_to_gbk_r((unsigned char*)item->valuestring, strlen(item->valuestring), &pszGbk, &nDestLen);
					free(jNode->valuestring);
					strcpy(item->valuestring, (const char *)pszGbk);
					//item->valuestring = UTF8toANSI(item->valuestring);
				}
		}

		pObj->ReadNode(item,_mapBkmk);

		AddBkmk(item,_mapBkmk);

		item = item->next;
	}
}

void CJsonData::AddBkmk(CJSON *jNode,map<CJSON*, CString> *_mapBkmk)
{
	if(jNode)
	{
		CString strKey(jNode->valuestring);

		if(xml_CheckBkmk(strKey) != BMK_PATH)
			return ;

		_mapBkmk->insert(pair<CJSON*, CString>(jNode, strKey));
	}
}

DWORD CJsonData::GetSelectBkmk(const CString &sSelectBkmk, int iIndex)
{
	DWORD hItem = 0;

	//�������в���
	if(m_node->valuestring!= NULL)
	{
		if(sSelectBkmk == m_node->valuestring)
		{
			if(CJsonData::g_iJson_Find_ItemData == iIndex)
			{
				return this->m_dwItemData;
			}
			else
			{
				CJsonData::g_iJson_Find_ItemData++;
			}
		}
	}

	//���ӽڵ��в���
	CJsonData* pObj = NULL;
	POS pos = GetHeadPosition();
	while (pos != NULL)
	{
		pObj = (CJsonData*)GetNext(pos);
		if(pObj == NULL)
			return 0;
		
		hItem = pObj->GetSelectBkmk(sSelectBkmk, iIndex);
		if(hItem != 0)
		{
			return hItem;
		}
	}

	return 0;
}
bool CJsonData::IsChinese(char *strutf8)
{
	int nLen = strlen(strutf8);
	unsigned char ch1;
	for (int i = 0; i != nLen; ++i)
	{
		ch1 = strutf8[i];
		if (ch1 >= 0xA0)
		{
			return true;
		}
		else
		{
			continue;
		}
	}
	return false;
}
bool CJsonData::is_str_utf8(const char* str)
{
	unsigned int nBytes = 0;//UFT8����1-6���ֽڱ���,ASCII��һ���ֽ�
	unsigned char chr = *str;
	bool bAllAscii = true;
	for (unsigned int i = 0; str[i] != '\0'; ++i)
	{
		chr = *(str + i);
		//�ж��Ƿ�ASCII����,�������,˵���п�����UTF8,ASCII��7λ����,���λ���Ϊ0,0xxxxxxx
		if (nBytes == 0 && (chr & 0x80) != 0)
		{
			bAllAscii = false;
		}
		if (nBytes == 0)
		{
			//�������ASCII��,Ӧ���Ƕ��ֽڷ�,�����ֽ���
			if (chr >= 0x80)
			{
				if (chr >= 0xFC && chr <= 0xFD)
				{
					nBytes = 6;
				}
				else if (chr >= 0xF8)
				{
					nBytes = 5;
				}
				else if (chr >= 0xF0)
				{
					nBytes = 4;
				}
				else if (chr >= 0xE0)
				{
					nBytes = 3;
				}
				else if (chr >= 0xC0)
				{
					nBytes = 2;
				}
				else
				{
					return false;
				}
				nBytes--;
			}
		}
		else
		{
			//���ֽڷ��ķ����ֽ�,ӦΪ 10xxxxxx
			if ((chr & 0xC0) != 0x80)
			{
				return false;
			}
			//����Ϊ��Ϊֹ
			nBytes--;
		}
	}
	//Υ��UTF8�������
	if (nBytes != 0)
	{
		return false;
	}
	if (bAllAscii)
	{ //���ȫ������ASCII, Ҳ��UTF8
		return true;
	}
	return true;
}

/***************************************************/
CJsonPathData::CJsonPathData(void)
{
}

CJsonPathData::~CJsonPathData(void)
{
}

BOOL CJsonPathData::OpenXmlFile(const CString &strFile)
{
	if (!IsFileExist(strFile))
	{
		//2022-11-25  lijunqing
#ifdef _DEBUG
		CString strMsg = _T("File error :") + strFile;
		CLogPrint::LogString(XLOGLEVEL_ERROR, strMsg);
#endif
		return FALSE;
	}

	DeleteAll();
	m_MapBkmks.clear();

	char* data;
	data = ReadFile(strFile);
	if (data == NULL)
	{
		return FALSE;
	}

	//��ȡ���ڵ�
	m_root = CJSON_Parse(data);

	free(data);
	if(m_root == NULL)
		return FALSE;

	CJsonData* pObj = new CJsonData();
	AddTail(pObj);

	pObj->ReadNode(m_root,&m_MapBkmks);	

	return TRUE;
}

char* CJsonPathData::ReadFile(const CString &strFile)
{
	CFile file;
	file.Open((LPCTSTR)strFile, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeRead);//���ļ�
	ULONGLONG nlen = file.GetLength();//��ȡ�ļ��ܳ���

	char* data;
	data = (char*)malloc(nlen + 1);

	file.SeekToBegin();//����λ��������ʼ�ֽ�
	file.Read(data,nlen);//�����
	file.Close();//�ر��ļ�

	return data;
}

BOOL CJsonPathData::SaveXmlFile(const CString &strFile)
{
	if (strFile.GetLength() < 3)
	{
		return FALSE;
	}

	try
	{
		ClearFileReadOnlyAttr(strFile);

		CString strPath = GetPathFromFilePathName(strFile);
		CreateAllDirectories(strPath);

		CFile file;
		file.Open((LPCTSTR)strFile, CFile::modeCreate | CFile::modeWrite);//���ļ�

		//20231009 huangliang ��Ҫ���ļ��ı���ΪUTF-8
		char* data = CJSON_Print_UTF8(m_root, 0);

		file.SeekToBegin();//����λ��������ʼ�ֽ�
		file.Write(data,strlen(data));//����д
		file.Close();//�ر��ļ�

		free(data);
	}
	catch (...)
	{
		return FALSE;
	}
	
	return TRUE;
}

void CJsonPathData::SetBkmk(CJSON *jNode, const CString &sBkmk)
{
	CString strKmk = sBkmk;

	free(jNode->valuestring);
	CString_to_char(strKmk, &jNode->valuestring);
}

BOOL CJsonPathData::AddBkmk(CJSON *jNode, const CString &sBkmk)
{
	if(xml_CheckBkmk(sBkmk) != BMK_PATH)
		return FALSE;

	SetBkmk(jNode, sBkmk);

	m_MapBkmks.insert(pair<CJSON*, CString>(jNode, sBkmk));
	return TRUE;
}

BOOL CJsonPathData::Replacekmk(CJSON *jNode, const CString &sNewBkmk)
{
	if(xml_CheckBkmk(sNewBkmk) != BMK_PATH)
		return FALSE;

	map<CJSON*, CString>::iterator it;  
    it = m_MapBkmks.find(jNode);  
	if(it != m_MapBkmks.end())
	{
		SetBkmk(jNode, sNewBkmk);

		m_MapBkmks.erase(it); 
		m_MapBkmks.insert(pair<CJSON*, CString>(jNode, sNewBkmk));
		return TRUE;
	}

	return FALSE;
}
BOOL CJsonPathData::Deletekmk(CJSON *jNode)
{
	CString sNewBkmk = _T("");
	map<CJSON*, CString>::iterator it;  
    it = m_MapBkmks.find(jNode);  
	if(it !=m_MapBkmks.end())
	{
		SetBkmk(jNode, sNewBkmk);

		m_MapBkmks.erase(it); 
		return TRUE;
	}

	return FALSE;
}

DWORD CJsonPathData::GetSelectBkmk(const CString &sSelectBkmk, int iIndex)
{
	CJsonData* pObj = (CJsonData*)GetHead();
	if(pObj == NULL)
		return 0;

	CJsonData::g_iJson_Find_ItemData = 0;
	return pObj->GetSelectBkmk(sSelectBkmk, iIndex);
}

//һ�����滻
BOOL CJsonPathData::DataReplacekmk(const CString &sSelectBkmk, const CString &sData)
{
	map<CJSON*, CString>::iterator it;  
	for(it=m_MapBkmks.begin(); it!=m_MapBkmks.end(); it++)
	{
		if(it->second == sSelectBkmk)
		{
			CJSON *jNode = it->first;
			SetBkmk(jNode, sData);
			m_MapBkmks.erase(it); 
		}
	}
	return FALSE;
}