#pragma once

#include "SetsFileToolInterface.h"
#include "..\..\..\..\Module\Office\WordBaseClass.h"

class CStesFileWordTool :public CFileToolInterface
{
public:
	CStesFileWordTool(void);
	~CStesFileWordTool(void);

	static CFileToolInterface* Create()
	{
		return new CStesFileWordTool();
	}

	virtual BOOL ExportFile(const CString &strFile, LPDISPATCH lpDispatch=NULL);
	virtual BOOL ImportFile(const CString &strFile, LPDISPATCH lpDispatch=NULL);

private:
	CWordAppBase *m_pWordAppBase;
	CWordDocBase *m_pWordDocBase;

	void CreateWordBaseApp(LPDISPATCH lpDispatch=NULL);
	void ReleaseWord();

private:
	//Export
	void ExportSets();
	void ExportTitle();
// 	void ExportGroup(CSysParaEditGroup *pGroup, BOOL bAddTitle=FALSE);
// 	void ExportGroupTitle(CSysParaEditGroup *pGroup, BOOL bAddTitle=FALSE);
	void ExportTableTitle(MSWord::Table  oTable);
// 	void ExportSet(CSet *pSet, MSWord::Row &oRow, long nRow);

private:
	//import
	//void 
};

