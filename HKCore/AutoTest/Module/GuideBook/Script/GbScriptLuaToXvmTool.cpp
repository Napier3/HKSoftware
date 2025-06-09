#include "stdafx.h"
#include "GbScriptLuaToXvmTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CGbsLuaToXvmTool::CGbsLuaToXvmTool()
{

}

CGbsLuaToXvmTool::~CGbsLuaToXvmTool()
{

}

BOOL CGbsLuaToXvmTool::NeedLuaToXVM(CExBaseList *pTemplate)
{
	CGuideBook *pPpTemplate = (CGuideBook*)pTemplate;

	if (pPpTemplate->IsScriptType_XVM())
	{
		return FALSE;
	}

	pPpTemplate->SetScriptType_XVM();

	return TRUE;
}

void CGbsLuaToXvmTool::ShowReplaceItemPath(CExBaseObject *pItem)
{
	if (!g_bShowReplaceItemPath)
	{
		return;
	}

	CString strPath;
	strPath = pItem->GetNamePathEx(GBCLASSID_DEVICE, FALSE);

	if (strPath.GetLength() > 0)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, strPath);
	}
}

//2020-7-9 lijunqing  ������滻
void CGbsLuaToXvmTool::ReplaceEx()
{
	//2020-07-09  lijunqing
	//XVM �ڴ���ű��ַ�����ʱ�򣬶��ڡ�\\��ת�����ˡ�\�������³���������Ҫ����ת��
	Replace(_T("\\\\"), _T("/"));
}

