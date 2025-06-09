#pragma once

#include "SetsFileToolInterface.h"
#include "SetFilesXmlParse/SetFilesXml_DSC.h"

class CStesFileXmlTool :public CSetsFileToolInterface
{
public:
	CStesFileXmlTool(void);
	~CStesFileXmlTool(void);
	CSetFilesXml_DSC m_oSetsFileXml_Dsc;

	static CFileToolInterface* Create()
	{
		return new CStesFileXmlTool();
	}

	virtual BOOL ExportFile(const CString &strFile, LPDISPATCH lpDispatch=NULL);
	virtual BOOL ImportFile(const CString &strFile, LPDISPATCH lpDispatch=NULL);
	virtual void InitDatasetIDByName(CDvmDataset *pDataset)	{	}

	CDvmDataset* GetSetsByID(const CString &strID);

	void GetMd5_FromFile(const CString strClass, CString &strMd5);  //��ֵ���ļ���ֱ�ӻ�ȡ��MD5
	void GetMd5_FromCal(const CString strClass, CString &strMd5);   //���ݶ�ֵ������õ���MD5
};

