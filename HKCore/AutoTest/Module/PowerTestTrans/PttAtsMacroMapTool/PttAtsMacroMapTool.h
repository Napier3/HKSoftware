//PttAtsMacroMapTool.h  CPttAtsMacroMapTool

#pragma once
#include "..\MacroMap\MacroMaps.h"
#include "..\Parser\PNTplParse.h"
#include "..\..\..\..\Module\MemBuffer\EquationBuffer.h"
#include "..\..\Module\XfileMngrBase\XFolder.h"
#include "..\..\Module\XfileMngrBase\XFileMngr.h"

#define WM_INSERT_NEW_MAP  (WM_USER + 1819)

class CPttAtsMacroMapTool 
{
public:
	CPttAtsMacroMapTool();
	virtual ~CPttAtsMacroMapTool();

	void AttachMapsMsgRcvWnd(CWnd *pWnd)	{	m_pMapsMsgRcvWnd = pWnd;	}
	void AnalyseFile (const CString& strFile);
	//void AnalyseFolder (CXFileMngr *pFileMngr);
	void AnalyseFolder(const CString &strFolder);
	//static UINT AnalyseThread(LPVOID pPara);
	void AddAllTestItemMacroToMaps(CPNTplRoot* pRoot);
	BOOL AddMacroAndParatoMap(CPNTplElement* pElement);
	void AddBinaryParatoMap(CPNTplElement* pBinary);
	void AddParatoMap(CMacroMap* pMacroMap, CPNTplElement* pElement);
	CString GetPtParas();

	CMacroMaps* m_pMacroMaps;  //映射文件类对象的指针，保存解析文件得到的功能及参数；
// 	CMacroMaps m_oExistMacroMaps;  //保存读PowerTestAtsMacroMap.xml文件对象,把映射文件读进来，
// 							 //以便后期维护映射文件的时候，通过CMacroMaps* m_pMacroMaps中
// 							//从模板文件读上来的PT模板及参数，与m_oMacroMaps进行比对，将不存在m_oMacroMaps中的新模板及新参数写进映射文件中；

	CTestMacros m_oAtsTestMacros;

	CPNTplParse m_oFileParse;
	CExBaseList m_listBinaryPara;

public:
	void InitTool();
	void SaveMapFile();

	BOOL IsModified()	{	return m_pMacroMaps->IsModified();	}
	void SetModifiedFlag(BOOL bModify=TRUE)	{	m_pMacroMaps->SetModifiedFlag(bModify);	}

protected:
	CWnd *m_pMapsMsgRcvWnd;
};