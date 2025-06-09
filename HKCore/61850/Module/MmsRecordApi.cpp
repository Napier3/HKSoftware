// MmsApi.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MmsApi.h"
#include "EnumType.h"
#include "MmsRecordApi.h"
#include "../../Module/System/TickCount32.h"


bool mms_get_record_file_long(char **ppSrc, long nLen, WORD &nValue)
{
	char *pSrc = *ppSrc;
	char *pEnd = pSrc + nLen;
	char pValueBuff[8]; 
	long nIndex = 0;
	char *pDest = pValueBuff;

	while (pSrc <= pEnd)
	{
		if (*pSrc != '_')
		{
			*pDest = *pSrc;
			pDest++;
			pSrc++;
			nIndex++;

			if (nIndex >= nLen)
			{
				break;
			}
		}
		else
		{
            return false;
		}
	}

	*pDest = 0;
	nValue = atol(pValueBuff);
	*ppSrc = pSrc;
	
    return true;
}

bool mms_get_record_file_name_offser(char **ppSrc, long nOffset, char *pSrcEnd)
{
	char *p = *ppSrc;
	long nCount = 0;

	while (p<pSrcEnd)
	{
		if (*p == '_')
		{
			nCount++;

			if (nCount == nOffset)
			{
				*ppSrc = p + 1;
				break;
			}
		}

		p++;
	}

	return (nCount == nOffset);
}


bool mms_get_record_file_name_time(char *pszFileName, __time64_t &tm64)
{
	char pszBuffer[MAX_PATH];
	strcpy(pszBuffer, pszFileName);
	char *p = pszBuffer;

	if (!mms_get_record_file_name_offser(&p, 3, p+strlen(pszBuffer)))
	{
        return false;
	}
	
	SYSTEMTIME tmSys;
	ZeroMemory(&tmSys, sizeof(SYSTEMTIME));

	mms_get_record_file_long(&p, 4, tmSys.wYear);
	mms_get_record_file_long(&p, 2, tmSys.wMonth);
	mms_get_record_file_long(&p, 2, tmSys.wDay);
	p++;   //jump '_'
	mms_get_record_file_long(&p, 2, tmSys.wHour);
	mms_get_record_file_long(&p, 2, tmSys.wMinute);
	mms_get_record_file_long(&p, 2, tmSys.wSecond);
	p++;   //jump '_'
	mms_get_record_file_long(&p, 3, tmSys.wMilliseconds);

	CTime tm(tmSys);
	tm64 = tm.GetTime();

    return true;
}




class CMmsRecordFileNameSort
{
private:
	typedef struct _struct_RecordFileSort
	{
		char pFileData[MAX_PATH];
		__time64_t tm64Value;
	}RECORDFILESORT, *PRECORDFILESORT;

	long m_nFileCount;
	RECORDFILESORT m_pRecordFileSort[MAX_MVL_DIR_ENT_COUNT];

public:
	CMmsRecordFileNameSort()		
	{
		m_nFileCount = 0;
	};

	virtual ~CMmsRecordFileNameSort()
	{
		
	};


protected:
    bool InitStruct(PRECORDFILESORT pSort, char *pszFile)
	{
		if (! mms_get_record_file_name_time(pszFile, pSort->tm64Value) )
		{
			pSort->tm64Value = 0;
            return false;
		}

        return true;
	}

    bool Sort(PRECORDFILESORT pSort, long nCount)
	{
		long i=0, j=0;
		RECORDFILESORT data;

		for (i=0; i<nCount-1; i++)
		{
			for (j=i+1; j<nCount; j++)
			{
				if (pSort[i].tm64Value > pSort[j].tm64Value)
				{
					data = pSort[j];
					pSort[j] = pSort[i];
					pSort[i] = data;
				}
			}
		}

		return (m_nFileCount > 0);
	}

	void AddFile(char *pszFile)
	{
		char *pTemp = pszFile;
		BOOL bFind = FALSE;
		char *pszFind = NULL;

		while (*pTemp != 0)
		{
			if (*pTemp == '.')
			{
				bFind = TRUE;
				*pTemp = 0;
				break;
			}

			pTemp++;
		}

		for (long i=0; i<m_nFileCount; i++)
		{
			if (strcmp(pszFile, m_pRecordFileSort[i].pFileData) == 0)
			{
				pszFind = m_pRecordFileSort[i].pFileData;
				break;
			}
		}

		if (pszFind == NULL)
		{
			strcpy(m_pRecordFileSort[m_nFileCount].pFileData, pszFile);
			InitStruct(&m_pRecordFileSort[m_nFileCount], pszFile);
			m_nFileCount++;
		}

		if (bFind)
		{
			*pTemp = '.';
		}
	}

public:
	void Sort(ACSI_NODE *pDevice)
	{
		XMMS_FILE_SYS_OBJ *pFileDir = &pDevice->FileDir;
		XMMS_FILE_SYS_OBJ *pSubDir = NULL;
		ASSERT(pFileDir->subFiles.numOfData != 0);

		for (long i=0; i<pFileDir->subFiles.numOfData/*pFileDir->nCount*/; i++)
		{
			pSubDir = (XMMS_FILE_SYS_OBJ*)(pFileDir->subFiles.Datas[i]);
			AddFile(mms_string(&pSubDir->filedir.filename)/*pFileDir->dir[i].filename*/);
		}

		Sort(m_pRecordFileSort, m_nFileCount);
	}
	
	void Sort(long nDvIdex)
	{
		ACSI_NODE *pDevice = &pACSINode[nDvIdex];
		Sort(pDevice);
	}

    bool GetLastFile(CString &strFile)
	{
		if (m_nFileCount > 0)
		{
			strFile = m_pRecordFileSort[m_nFileCount-1].pFileData;
            return true;
		}
		else
		{
			strFile.Empty();
            return false;
		}
	}
};


bool mms_get_last_record_file(ACSI_NODE *pDevice, CString &strFileName)
{
	CMmsRecordFileNameSort oSort;
	oSort.Sort(pDevice);
	return oSort.GetLastFile(strFileName);
}

bool mms_get_last_record_file(long nDvIndex, CString &strFileName)
{
	CMmsRecordFileNameSort oSort;
	oSort.Sort(nDvIndex);
	return oSort.GetLastFile(strFileName);
}

