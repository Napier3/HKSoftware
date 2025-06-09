// AtsVerUpdateZip.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AtsVerUpdateZip.h"
#include "contrib\minizip\zip.h"
#include "contrib\minizip\unzip.h"
#include "..\..\..\Module\API\FileApi.h"

// CAtsVerUpdateZip

IMPLEMENT_DYNAMIC(CAtsVerUpdateZip, CWnd)

CAtsVerUpdateZip::CAtsVerUpdateZip()
{

}

CAtsVerUpdateZip::~CAtsVerUpdateZip()
{
}

int CAtsVerUpdateZip::Zip(CStringArray& strFileArray,const CString& strZipFile)
{
	if(strFileArray.GetCount()==0 || strZipFile.IsEmpty())
		return FALSE;
	//����ѹ����
	zipFile zf = NULL;
	USES_CONVERSION; 
	zf = zipOpen((LPCSTR)T2A(strZipFile),0);
	//ѹ���ļ�
	zip_fileinfo FileInfo; 
	ZeroMemory(&FileInfo, sizeof(FileInfo));
	for(int i=0;i<strFileArray.GetCount();i++)
	{
		CString strFilePath = strFileArray.GetAt(i);
		zipOpenNewFileInZip(zf, (LPCSTR)T2A(strFilePath), &FileInfo, NULL, 0, NULL, 0, NULL,Z_DEFLATED, Z_DEFAULT_COMPRESSION);
		CFile zpFile;
		if(!zpFile.Open(strFilePath,CFile::modeReadWrite))
		{
			continue;
		}
		ULONGLONG size = zpFile.GetLength();
		void* pData = malloc(size);
		zpFile.Read(pData,(UINT)size);
		zipWriteInFileInZip(zf,pData,size);
		zipCloseFileInZip(zf);
		free(pData);
	}
	//�ر���
	zipClose(zf,0);
	return TRUE;
}

int CAtsVerUpdateZip::Unzip(const CString& strZipFile,const CString& strDestPath)//strZipFile:zipѹ���ļ�����·��
{
	int rv = UNZ_ERRNO;
	unzFile uzf=NULL;
	unz_global_info global_info;
	unz_file_info file_info;
	USES_CONVERSION;
	uzf = unzOpen((LPCSTR)T2A(strZipFile));
	if(uzf==NULL)
		return rv;
	rv = unzGetGlobalInfo(uzf, &global_info);
	if (rv != UNZ_OK)
		return rv;
	rv = unzGoToFirstFile(uzf);
	if (rv != UNZ_OK)
		return rv;
	for(int i=0;i<global_info.number_entry;++i)
	{
		char szFileName[MAX_PATH]={0};
		char chExtraField[255]={0};
		char szComment[255]={0};
		rv = unzGetCurrentFileInfo(uzf, &file_info, szFileName, MAX_PATH, chExtraField, sizeof(chExtraField), szComment, sizeof(szComment));  
		if(rv != UNZ_OK)
			break;
		_strupr_s( szFileName, sizeof(szFileName) );    
		for(int j=0; szFileName[j]; j++) 
		{ 
			if(szFileName[j]=='/') 
				szFileName[j]='//';
		} 
		rv = unzOpenCurrentFile(uzf);			  //������
		//		rv = unzOpenCurrentFilePassword(uzf,NULL);//������
		if(rv != UNZ_OK)
			break;
		//��ȡ����
		void *pData = malloc(file_info.uncompressed_size);
		if(!pData)
		{
			unzCloseCurrentFile(uzf);
			break;
		}
		UINT size = file_info.uncompressed_size;
		int sizeRead = unzReadCurrentFile(uzf,pData,size);
		if(sizeRead!= size)
		{
			unzCloseCurrentFile(uzf);
			free(pData);
			break;
		}
		//������ѹ����ļ�
		CString strFileName = A2T(szFileName);
		CString strUnzipFilePath,strTempFilePath;
		if(!strDestPath.IsEmpty())
		{
			int nPos = strFileName.Find(_T("UPDATETEMP"));
			if(nPos>=0)
			{
				CString strTemp = strFileName.Mid(nPos+11);
				nPos = strTemp.Find(_T("\\"));
				strTempFilePath = strTemp.Mid(nPos+1);
			}
			else
			{
				strTempFilePath = GetPathFileNameFromFilePathName(strFileName);
			}
			strUnzipFilePath = strDestPath;
			strUnzipFilePath += strTempFilePath;
		}
		else
		{
			strUnzipFilePath = strFileName;
		}
		CreateAllDirectories(GetPathFromFilePathName(strUnzipFilePath));
		CFile file;
		if(file.Open(strUnzipFilePath.AllocSysString(),CFile::modeCreate|CFile::modeReadWrite))
		{
			file.Write(pData,size);
			file.Close();
		}
		free(pData);
		//�رյ�ǰ�ļ�
		rv = unzCloseCurrentFile(uzf);
		if(rv != UNZ_OK)
			break;
		rv = unzGoToNextFile(uzf);
		if(rv != UNZ_OK)
			break;
	}
	//�ر���
	unzClose(uzf);
	return UNZ_OK;
}



