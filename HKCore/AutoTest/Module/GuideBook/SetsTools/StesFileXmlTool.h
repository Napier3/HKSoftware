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

	void GetMd5_FromFile(const CString strClass, CString &strMd5);  //定值单文件中直接获取的MD5
	void GetMd5_FromCal(const CString strClass, CString &strMd5);   //根据定值单计算得到的MD5
};

