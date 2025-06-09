#include "stdafx.h"
#include "JsonRptFill.h"
#include "../../../../../Module/API/FileApi.h"
#include "../../../../../Module/API/StringConvert/String_Gbk_To_Utf8.h"

CJsonRptFill::CJsonRptFill(void)
{
}

CJsonRptFill::~CJsonRptFill(void)
{
	FreeJsonDoc();
}


void CJsonRptFill::FreeJsonDoc()
{
	if (m_pJsonDoc == NULL)
	{
		return;
	}

	//���json�ڵ��������Ӷ����string=NULL��������������
	CJSON_ClearArrayKey(m_pJsonDoc);

	CJSON_Delete(m_pJsonDoc);
	m_pJsonDoc = NULL;
}


void CJsonRptFill::Cal(CJSON *pJson)
{	
	if (pJson->type == CJSON_String)
	{
		Cal_String(pJson);
	}

	CalChild(pJson);
}

void CJsonRptFill::Cal_String(CJSON *pJson)
{	
	char *pString = pJson->valuestring;

	if (*pString < 0)
	{//��������
		return;
	}

	if (strstr(pString, "$") == NULL)
	{
		return;
	}

	CValue *pValue = FindRptDataByPath(pJson->valuestring);

	if (pValue != NULL)
	{
		//20231010 huangliang �滻���ݸ�ΪUTF-8����
		char *pszBufIn;
		CString_to_char(pValue->m_strValue, &pszBufIn);

		unsigned char *pszUtf8 = NULL;
		int nDestLen = 0;
		gbk_to_utf8_r((unsigned char*)pszBufIn, strlen(pszBufIn), &pszUtf8, &nDestLen, 0);
		pszUtf8[nDestLen] = '\0';
		delete pszBufIn;

		free(pJson->valuestring);
		pJson->valuestring = new char[nDestLen + 1];
		strcpy(pJson->valuestring, (const char *)pszUtf8);	
		delete pszUtf8;	//20231107 huangliang δ��ӣ����ܷ����ڴ�й©
	}
	else
	{
		//20231007 huangliang δ�ҵ�����Ϊ������Ҫ�滻������
		//pJson->valuestring[0] = 0;
	}
}

void CJsonRptFill::CalChild(CJSON *pJson)
{	
	CJSON * pChild = pJson->child;

	while(pChild != NULL)
	{
		if(pChild->type == CJSON_Object)
		{
			Cal(pChild);
		}
		else if(pChild->type == CJSON_Array)
		{
			CalChildArr(pChild);
		}
		else if (pChild->type == CJSON_String)
		{
			Cal_String(pChild);
		}

		pChild = pChild->next;
	}
}

void CJsonRptFill::CalChildArr(CJSON *pJson)
{	
	CJSON *pChild = pJson->child;

	while(pChild)
	{
		Cal(pChild);
		pChild= pChild->next;
	}
}

long CJsonRptFill::OpenRptTemplateFile(const CString &strReportFile)
{
	if (!IsFileExist(strReportFile))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("[%s] error!"), strReportFile.GetString());
		return FALSE;
	}

	m_pJsonDoc = CJSON_Open_File(strReportFile.GetString());

	return (m_pJsonDoc != NULL);
}

long CJsonRptFill::SaveRptFile(const CString &strRptFile)
{
	return CJSON_Write_File(m_pJsonDoc, strRptFile.GetString());
}


long CJsonRptFill::FillRpt(CGuideBook* pGuideBook)
{
	m_pGuideBook = pGuideBook;
	Cal(m_pJsonDoc);

	return 0;
}
