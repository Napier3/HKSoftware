#pragma once

#include "../../../Module/XFileMngrBase/XFileMngr.h"

//��Լģ���ļ�����
#define PP_DEV_FILE									(CLASSID_XFILE         + 0x00000011)
#define PP_DEV_FOLDER							    (CLASSID_XFOLDER    + 0x00000012)
#define PP_DEV_FILE_MNGR					        (CLASSID_XFILEMNGR + 0x00000013)

const CString g_strPpTemplateType = _T("��Լģ���ļ�");
const CString g_strTemplateFolder = _T("Template");
const CString g_strPpTemplateFileMngrXMLFile = _T("PpTemplateFileMngr.xml");
const CString g_strPpTemplateFileMngr = _T("PpTemplateFileMngr");

//CString GetPpTemplateFileMngr();

class CPpTemplateFile : public CXFile
{
public:
	CPpTemplateFile();
	virtual ~CPpTemplateFile();

private:
	BOOL m_bOpen;		//��ʶ�ļ��Ƿ񱻴�

public:
	void SetFileState(BOOL bOpen=TRUE)	{	m_bOpen = bOpen;	}
	BOOL GetFileState()	{	return m_bOpen;	}

	virtual UINT GetClassID()	{	return PP_DEV_FILE;	}
	//virtual BSTR GetXmlElementKey()		{	return CFileMngrXMLKeys::g_pFileMngrXMLKeys->m_strFileKey;	}
};