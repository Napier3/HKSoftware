#pragma once

#include "SetsFileToolInterface.h"

#include "../../../../Module/Acrobat/PdfTextParseSets.h"
#include "../../../../Module/Acrobat/PdfXmlParseSets.h"
#include "../Cpus.h"

class CStesFilePdfTool :public CSetsFileToolInterface
{
public:
	CStesFilePdfTool(void);
	virtual ~CStesFilePdfTool(void);

	static CFileToolInterface* Create()
	{
		return new CStesFilePdfTool();
	}

	//20230728 huangliang �����޶�����
	bool m_bCorrect;
	CPdfXmlParseSets m_oSetsParse;   //shaolei ��Ϊ��Ա  2024-3-12

	virtual BOOL ExportFile(const CString &strFile, LPDISPATCH lpDispatch=NULL);
	virtual BOOL ImportFile(const CString &strFile, LPDISPATCH lpDispatch=NULL);
	virtual void SetManualConfirmInterface(CSetsFileManualConfirmInterface *pInterface);

public:
	
private:
	
};

