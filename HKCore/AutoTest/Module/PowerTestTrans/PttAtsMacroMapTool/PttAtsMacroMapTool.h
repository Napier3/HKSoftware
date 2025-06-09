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

	CMacroMaps* m_pMacroMaps;  //ӳ���ļ�������ָ�룬��������ļ��õ��Ĺ��ܼ�������
// 	CMacroMaps m_oExistMacroMaps;  //�����PowerTestAtsMacroMap.xml�ļ�����,��ӳ���ļ���������
// 							 //�Ա����ά��ӳ���ļ���ʱ��ͨ��CMacroMaps* m_pMacroMaps��
// 							//��ģ���ļ���������PTģ�弰��������m_oMacroMaps���бȶԣ���������m_oMacroMaps�е���ģ�弰�²���д��ӳ���ļ��У�

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