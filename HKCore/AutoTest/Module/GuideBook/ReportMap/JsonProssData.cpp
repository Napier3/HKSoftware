#include "StdAfx.h"
#include "JsonProssData.h"

CJsonData::CJsonData()
{
	m_node = NULL;
}
CJsonData::~CJsonData()
{
}

void CJsonData::ReadNode(CJSON *jNode, map<CString, CJSON*> *_mapBkmk)
{
	m_node = jNode;
	if(m_node == NULL)
		return ;
	m_strName = m_node->string;

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
					
					item->valuestring = UTF8toANSI(item->valuestring);;
				}
		}

		pObj->ReadNode(item, _mapBkmk);

		AddBkmk(item, _mapBkmk);

		item = item->next;
	}
}

void CJsonData::AddBkmk(CJSON *jNode, map<CString, CJSON*> *_mapBkmk)
{
	if(jNode)
	{
		CString strKey(jNode->valuestring);

		if(xml_CheckBkmk(strKey) == BMK_NULL)
			return ;
		_mapBkmk->insert(pair<CString, CJSON*>(strKey, jNode));
	}
}

DWORD CJsonData::GetSelectBkmk(const CString &sSelectBkmk)
{
	DWORD hItem = 0;

	//�������в���
	if(m_node->valuestring!= NULL)
	{
		if(sSelectBkmk == m_node->valuestring)
		{
			return this->m_dwItemData;
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
		
		hItem = pObj->GetSelectBkmk(sSelectBkmk);
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
char * CJsonData::UTF8toANSI(char * strutf8)
{
	USES_CONVERSION;
	//��ȡת��Ϊ���ֽں���Ҫ�Ļ�������С���������ֽڻ�����
	UINT nLen = MultiByteToWideChar(CP_UTF8, NULL, strutf8, -1, NULL, NULL);
	WCHAR *wszBuffer = new WCHAR[nLen + 1];
	nLen = MultiByteToWideChar(CP_UTF8, NULL, strutf8, -1, wszBuffer, nLen);
	wszBuffer[nLen] = 0;

	nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, NULL, NULL, NULL, NULL);
	CHAR *szBuffer = new CHAR[nLen + 1];
	nLen = WideCharToMultiByte(936, NULL, wszBuffer, -1, szBuffer, nLen, NULL, NULL);
	szBuffer[nLen] = 0;
	delete[]wszBuffer;
	return szBuffer;
}
/***************************************************/
CJsonProssData::CJsonProssData(void)
{
}

CJsonProssData::~CJsonProssData(void)
{
}

BOOL CJsonProssData::OpenXmlFile(const CString &strFile)
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

	pObj->ReadNode(m_root, &m_MapBkmks);	

	return TRUE;
}

char* CJsonProssData::ReadFile(const CString &strFile)
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

BOOL CJsonProssData::SaveXmlFile(const CString &strFile)
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
		file.Open((LPCTSTR)strFile, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);//���ļ�

		char* data = CJSON_Print(m_root);

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
void CJsonProssData::SetBkmk(CJSON *jNode, const CString &sBkmk)
{
	CString strKmk = sBkmk;
	free(jNode->valuestring);
	CString_to_char(strKmk, &jNode->valuestring);
}
BOOL CJsonProssData::AddBkmk(CJSON *jNode, const CString &sBkmk)
{
	if(xml_CheckBkmk(sBkmk) == BMK_NULL)
		return FALSE;

	SetBkmk(jNode, sBkmk);
	m_MapBkmks.insert(pair<CString, CJSON*>(sBkmk, jNode));//20230823 luozibing ��sBkmk������
	return TRUE;
}

BOOL CJsonProssData::Replacekmk(const CString &sSelectBkmk, const CString &sNewBkmk)
{
	if(xml_CheckBkmk(sNewBkmk) == BMK_NULL)
		return FALSE;

	map<CString, CJSON*>::iterator it;  
    it = m_MapBkmks.find(sSelectBkmk);  
	if(it != m_MapBkmks.end())
	{
		CJSON *jNode = it->second;
		if(jNode != NULL)
		{
			SetBkmk(jNode, sNewBkmk);
		}

		m_MapBkmks.erase(it); 
		m_MapBkmks.insert(pair<CString, CJSON*>(sNewBkmk, jNode));
		return TRUE;
	}

	return FALSE;
}
BOOL CJsonProssData::Deletekmk(const CString &sSelectBkmk)
{
	CString sNewBkmk = _T("");
	map<CString, CJSON*>::iterator it;  
    it = m_MapBkmks.find(sSelectBkmk);  
	if(it != m_MapBkmks.end())
	{
		CJSON *jNode = it->second;
		if(jNode != NULL)
		{
			SetBkmk(jNode, sNewBkmk);
		}

		m_MapBkmks.erase(it); 
		return TRUE;
	}

	return FALSE;
}

DWORD CJsonProssData::GetSelectBkmk(const CString &sSelectBkmk)
{
	CJsonData* pObj = (CJsonData*)GetHead();
	if(pObj == NULL)
		return 0;
	return pObj->GetSelectBkmk(sSelectBkmk);
}

//һ�����滻
BOOL CJsonProssData::DataReplacekmk(const CString &sSelectBkmk, const CString &sData)
{
	map<CString, CJSON*>::iterator it;  
    it = m_MapBkmks.find(sSelectBkmk);  
	if(it != m_MapBkmks.end())
	{
		CJSON *jNode = it->second;
		if(jNode != NULL)
		{
			SetBkmk(jNode, sData);
		}

		m_MapBkmks.erase(it); 
		return TRUE;
	}

	return FALSE;
}