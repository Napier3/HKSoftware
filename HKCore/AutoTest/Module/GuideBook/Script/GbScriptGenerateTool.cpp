#include "stdafx.h"
#include "GbScriptGenerateTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CGbScriptGenerate_LUA
class CGbScriptGenerate_LUA : public CGbScriptGenerateInterface
{
public:
	CGbScriptGenerate_LUA()
	{

	}

	virtual ~CGbScriptGenerate_LUA()
	{

	}

	virtual void GetVariableDefine_GetPara(CString &strDefine, const CString &strID, const CString &strPath) 
	{
		strDefine.Format(_T("local %s = GetPara(\"%s\",\"%s\");"),strID,strPath,strID);
	}
	virtual void GetVariableDefine_GetReportValue(CString &strDefine, const CString &strID, const CString &strPath) 
	{
		strDefine.Format(_T("local %s = GetReportValue(\"%s\",\"%s\");"),strID,strPath,strID);
	}
	virtual void GetVariableDefine_GetSetValue(CString &strDefine, const CString &strID, const CString &strPath) 
	{
		strDefine.Format(_T("local %s = GetSetValue(\"%s\",\"%s\");"),strID,strPath,strID);
	}
	virtual void GetVariableDefine_GetTestPara(CString &strDefine, const CString &strID)
	{
		strDefine.Format(_T("local %s = GetTestPara(\"%s\");"),strID,strID);
	}
	virtual void GetVariableDefine_VarAndVal(CString &strDefine, const CString &strID, const CString &strValue)
	{
		strDefine.Format(_T("local %s = %s;"),strID, strValue);
	}
	virtual void GetVariableDefine_VariableDef(CString &strDefine, const CString &strVariable)
	{
		strDefine.Format(_T("local %s = "),strVariable);
	}
	virtual void GetVariableDefine_vString(CString &strDefine)
	{
		strDefine.Format(_T("local vString;\r\n"));
	}
	virtual void GetVariableDefine_vGetTestPara(CString &strDefine, const CString &strvID, const CString &strID)
	{
		strDefine.Format(_T("local v%s = GetTestPara(\"%s\");\r\n"),strvID,strID);
	}
	virtual void GetVariableDefine_vGetDsDataValue(CString &strDefine, const CString &strvID, const CString &strID)
	{
		strDefine.Format(_T("local v%s = GetDsDataValue(\"Prot$dsSetting$%s\");\r\n"),strvID,strID);
	}
	virtual void GetVariableDefine_vGetReportValue(CString &strDefine, const CString &strvID, const CString &strID)
	{
		strDefine.Format(_T("local v%s = GetReportValue(\"\", \"%s\");\r\n"),strvID,strID);
	}
	virtual void GetVariableDefine_vGetPara(CString &strDefine, const CString &strvID, const CString &strID)
	{
		strDefine.Format(_T("local v%s = GetPara(\"..\\\\\", \"%s\");\r\n"),strvID,strID);
	}
	virtual void GetVariableDefine_VarAndVal_Value(CString &strDefine, const CString &strID, const CString &strValue)
	{
		strDefine.Format(_T("local %s_Value = %s;\r\n"),strID,strValue);
	}
	virtual void GetVariableDefine_nRsltJdg(CString &strDefine)
	{
		strDefine.Format(_T("local nRsltJdg = 0;\r\n\r\n"));
	}
};

//////////////////////////////////////////////////////////////////////////
//CGbScriptGenerate_XVM
class CGbScriptGenerate_XVM : public CGbScriptGenerateInterface
{
public:
	CGbScriptGenerate_XVM()
	{

	}

	virtual ~CGbScriptGenerate_XVM()
	{

	}

	virtual void GetVariableDefine_GetPara(CString &strDefine, const CString &strID, const CString &strPath) 
	{
		strDefine.Format(_T("var %s;\r\n %s = GetPara(\"%s\",\"%s\");"),strID, strID, strPath,strID);
	}
	virtual void GetVariableDefine_GetReportValue(CString &strDefine, const CString &strID, const CString &strPath) 
	{
		strDefine.Format(_T("var %s;\r\n %s = GetReportValue(\"%s\",\"%s\");"),strID, strID, strPath,strID);
	}
	virtual void GetVariableDefine_GetSetValue(CString &strDefine, const CString &strID, const CString &strPath) 
	{
		strDefine.Format(_T("var %s;\r\n %s = GetSetValue(\"%s\");"),strID, strID, strPath);
	}
	virtual void GetVariableDefine_GetTestPara(CString &strDefine, const CString &strID)
	{
		strDefine.Format(_T("var %s;\r\n %s = GetTestPara(\"%s\");"),strID, strID, strID);
	}
	virtual void GetVariableDefine_VarAndVal(CString &strDefine, const CString &strID, const CString &strValue)
	{
		strDefine.Format(_T("var %s;\r\n %s = %s;"),strID, strID, strValue);
	}
	virtual void GetVariableDefine_VariableDef(CString &strDefine, const CString &strVariable)
	{
		strDefine.Format(_T("var %s;\r\n %s = "), strVariable, strVariable);
	}
	virtual void GetVariableDefine_vString(CString &strDefine)
	{
		strDefine.Format(_T("var vString;\r\n"));
	}
	virtual void GetVariableDefine_vGetTestPara(CString &strDefine, const CString &strvID, const CString &strID)
	{
		strDefine.Format(_T("var v%s;\r\n v%s = GetTestPara(\"%s\");\r\n"),strvID, strvID, strID);
	}
	virtual void GetVariableDefine_vGetDsDataValue(CString &strDefine, const CString &strvID, const CString &strID)
	{
		strDefine.Format(_T("var v%s;\r\n v%s = GetDsDataValue(\"Prot$dsSetting$%s\");\r\n"),strvID,strvID, strID);
	}
	virtual void GetVariableDefine_vGetReportValue(CString &strDefine, const CString &strvID, const CString &strID)
	{
		strDefine.Format(_T("var v%s;\r\n v%s = GetReportValue(\"\", \"%s\");\r\n"),strvID, strvID, strID);
	}
	virtual void GetVariableDefine_vGetPara(CString &strDefine, const CString &strvID, const CString &strID)
	{
		strDefine.Format(_T("var v%s;\r\n v%s = GetPara(\"..\\\\\", \"%s\");\r\n"),strvID, strvID, strID);
	}
	virtual void GetVariableDefine_VarAndVal_Value(CString &strDefine, const CString &strID, const CString &strValue)
	{
		strDefine.Format(_T("var %s_Value;\r\n %s_Value = %s;\r\n"),strID, strID, strValue);
	}
	virtual void GetVariableDefine_nRsltJdg(CString &strDefine)
	{
		strDefine.Format(_T("var nRsltJdg;\r\n nRsltJdg = 0;\r\n\r\n"));
	}
};


//////////////////////////////////////////////////////////////////////////
//CGbScriptGenerateTool
CGbScriptGenerateTool* CGbScriptGenerateTool::g_pGbScriptGenerateTool = NULL;
long CGbScriptGenerateTool::g_nGbScriptGenerateToolRef = 0;
	

CGbScriptGenerateTool::CGbScriptGenerateTool()
{
	m_pLua = new CGbScriptGenerate_LUA();
	m_pXvm = new CGbScriptGenerate_XVM();

}

CGbScriptGenerateTool::~CGbScriptGenerateTool()
{
	delete m_pLua;
	delete m_pXvm;
}

CGbScriptGenerateTool* CGbScriptGenerateTool::Create()
{
	g_nGbScriptGenerateToolRef++;

	if (g_nGbScriptGenerateToolRef == 1)
	{
		g_pGbScriptGenerateTool = new CGbScriptGenerateTool();
	}

	return g_pGbScriptGenerateTool;
}

void CGbScriptGenerateTool::Release()
{
	g_nGbScriptGenerateToolRef--;

	if (g_nGbScriptGenerateToolRef == 0)
	{
		delete g_pGbScriptGenerateTool;
		g_pGbScriptGenerateTool = NULL;
	}
}

CGbScriptGenerateInterface* CGbScriptGenerateTool::GetGbScriptGenerateInterface(CExBaseObject *pGbObj)
{
	if (Gb_IsScriptType_LUA(pGbObj))
	{
		return m_pLua;
	}
	else
	{
		return m_pXvm;
	}
}

void CGbScriptGenerateTool::GetVariableDefine_GetPara(CString &strDefine, CExBaseObject *pGbObj, const CString &strID, const CString &strPath)
{
	CGbScriptGenerateInterface *p = g_pGbScriptGenerateTool->GetGbScriptGenerateInterface(pGbObj);
	ASSERT (p != NULL);
	p->GetVariableDefine_GetPara(strDefine, strID, strPath);
}

void CGbScriptGenerateTool::GetVariableDefine_GetReportValue(CString &strDefine, CExBaseObject *pGbObj, const CString &strID, const CString &strPath)
{
	CGbScriptGenerateInterface *p = g_pGbScriptGenerateTool->GetGbScriptGenerateInterface(pGbObj);
	ASSERT (p != NULL);
	p->GetVariableDefine_GetReportValue(strDefine, strID, strPath);
}

void CGbScriptGenerateTool::GetVariableDefine_GetSetValue(CString &strDefine, CExBaseObject *pGbObj, const CString &strID, const CString &strPath)
{
	CGbScriptGenerateInterface *p = g_pGbScriptGenerateTool->GetGbScriptGenerateInterface(pGbObj);
	ASSERT (p != NULL);
	p->GetVariableDefine_GetSetValue(strDefine, strID, strPath);
}

void CGbScriptGenerateTool::GetVariableDefine_GetTestPara(CString &strDefine, CExBaseObject *pGbObj, const CString &strID)
{
	CGbScriptGenerateInterface *p = g_pGbScriptGenerateTool->GetGbScriptGenerateInterface(pGbObj);
	ASSERT (p != NULL);
	p->GetVariableDefine_GetTestPara(strDefine, strID);
}

void CGbScriptGenerateTool::GetVariableDefine_VarAndVal(CString &strDefine, CExBaseObject *pGbObj, const CString &strID, const CString &strValue)
{
	CGbScriptGenerateInterface *p = g_pGbScriptGenerateTool->GetGbScriptGenerateInterface(pGbObj);
	ASSERT (p != NULL);
	p->GetVariableDefine_VarAndVal(strDefine, strID, strValue);
}

void CGbScriptGenerateTool::GetVariableDefine_VariableDef(CString &strDefine, CExBaseObject *pGbObj, const CString &strVariable)
{
	CGbScriptGenerateInterface *p = g_pGbScriptGenerateTool->GetGbScriptGenerateInterface(pGbObj);
	ASSERT (p != NULL);
	p->GetVariableDefine_VariableDef(strDefine, strVariable);
}

void CGbScriptGenerateTool::GetVariableDefine_vString(CString &strDefine, CExBaseObject *pGbObj)
{
	CGbScriptGenerateInterface *p = g_pGbScriptGenerateTool->GetGbScriptGenerateInterface(pGbObj);
	ASSERT (p != NULL);
	p->GetVariableDefine_vString(strDefine);
}

void CGbScriptGenerateTool::GetVariableDefine_vGetTestPara(CString &strDefine, CExBaseObject *pGbObj, const CString &strvID, const CString &strID)
{
	CGbScriptGenerateInterface *p = g_pGbScriptGenerateTool->GetGbScriptGenerateInterface(pGbObj);
	ASSERT (p != NULL);
	p->GetVariableDefine_vGetTestPara(strDefine, strvID, strID);
}

void CGbScriptGenerateTool::GetVariableDefine_vGetDsDataValue(CString &strDefine, CExBaseObject *pGbObj, const CString &strvID, const CString &strID)
{
	CGbScriptGenerateInterface *p = g_pGbScriptGenerateTool->GetGbScriptGenerateInterface(pGbObj);
	ASSERT (p != NULL);
	p->GetVariableDefine_vGetDsDataValue(strDefine, strvID, strID);
}

void CGbScriptGenerateTool::GetVariableDefine_vGetReportValue(CString &strDefine, CExBaseObject *pGbObj, const CString &strvID, const CString &strID)
{
	CGbScriptGenerateInterface *p = g_pGbScriptGenerateTool->GetGbScriptGenerateInterface(pGbObj);
	ASSERT (p != NULL);
	p->GetVariableDefine_vGetReportValue(strDefine, strvID, strID);
}

void CGbScriptGenerateTool::GetVariableDefine_vGetPara(CString &strDefine, CExBaseObject *pGbObj, const CString &strvID, const CString &strID)
{
	CGbScriptGenerateInterface *p = g_pGbScriptGenerateTool->GetGbScriptGenerateInterface(pGbObj);
	ASSERT (p != NULL);
	p->GetVariableDefine_vGetPara(strDefine, strvID, strID);
}

void CGbScriptGenerateTool::GetVariableDefine_VarAndVal_Value(CString &strDefine, CExBaseObject *pGbObj, const CString &strID, const CString &strValue)
{
	CGbScriptGenerateInterface *p = g_pGbScriptGenerateTool->GetGbScriptGenerateInterface(pGbObj);
	ASSERT (p != NULL);
	p->GetVariableDefine_VarAndVal_Value(strDefine, strID, strValue);
}

void CGbScriptGenerateTool::GetVariableDefine_nRsltJdg(CString &strDefine, CExBaseObject *pGbObj)
{
	CGbScriptGenerateInterface *p = g_pGbScriptGenerateTool->GetGbScriptGenerateInterface(pGbObj);
	ASSERT (p != NULL);
	p->GetVariableDefine_nRsltJdg(strDefine);
}