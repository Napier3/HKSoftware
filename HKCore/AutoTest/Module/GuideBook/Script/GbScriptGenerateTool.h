#pragma once

#include "../GuideBook.h"

class CGbScriptGenerateInterface
{
public:
	virtual void GetVariableDefine_GetPara(CString &strDefine, const CString &strID, const CString &strPath) = 0;
	virtual void GetVariableDefine_GetReportValue(CString &strDefine, const CString &strID, const CString &strPath) = 0;
	virtual void GetVariableDefine_GetSetValue(CString &strDefine, const CString &strID, const CString &strPath) = 0;
	virtual void GetVariableDefine_GetTestPara(CString &strDefine, const CString &strID) = 0;
	virtual void GetVariableDefine_VarAndVal(CString &strDefine, const CString &strID, const CString &strValue) = 0;
	virtual void GetVariableDefine_VariableDef(CString &strDefine, const CString &strVariable) = 0;
	virtual void GetVariableDefine_vString(CString &strDefine) = 0;
	virtual void GetVariableDefine_vGetTestPara(CString &strDefine, const CString &strvID, const CString &strID) = 0;
	virtual void GetVariableDefine_vGetDsDataValue(CString &strDefine, const CString &strvID, const CString &strID) = 0;
	virtual void GetVariableDefine_vGetReportValue(CString &strDefine, const CString &strvID, const CString &strID) = 0;
	virtual void GetVariableDefine_vGetPara(CString &strDefine, const CString &strvID, const CString &strID) = 0;
	virtual void GetVariableDefine_VarAndVal_Value(CString &strDefine, const CString &strID, const CString &strValue) = 0;
	virtual void GetVariableDefine_nRsltJdg(CString &strDefine) = 0;
};

class CGbScriptGenerateTool
{
private:
	CGbScriptGenerateTool();
	virtual ~CGbScriptGenerateTool();

	static CGbScriptGenerateTool* g_pGbScriptGenerateTool;
	static long g_nGbScriptGenerateToolRef;

	CGbScriptGenerateInterface *m_pLua;
	CGbScriptGenerateInterface *m_pXvm;
	
	CGbScriptGenerateInterface* GetGbScriptGenerateInterface(CExBaseObject *pGbObj);

public:
	static CGbScriptGenerateTool* Create();
	static void Release();
	
	static void GetVariableDefine_GetPara(CString &strDefine, CExBaseObject *pGbObj, const CString &strID, const CString &strPath);
	static void GetVariableDefine_GetReportValue(CString &strDefine, CExBaseObject *pGbObj, const CString &strID, const CString &strPath);
	static void GetVariableDefine_GetSetValue(CString &strDefine, CExBaseObject *pGbObj, const CString &strID, const CString &strPath);
	static void GetVariableDefine_GetTestPara(CString &strDefine, CExBaseObject *pGbObj, const CString &strID);
	static void GetVariableDefine_VarAndVal(CString &strDefine, CExBaseObject *pGbObj, const CString &strID, const CString &strValue);
	static void GetVariableDefine_VariableDef(CString &strDefine, CExBaseObject *pGbObj, const CString &strVariable);
	static void GetVariableDefine_vString(CString &strDefine, CExBaseObject *pGbObj);
	static void GetVariableDefine_vGetTestPara(CString &strDefine, CExBaseObject *pGbObj, const CString &strvID, const CString &strID);
	static void GetVariableDefine_vGetDsDataValue(CString &strDefine, CExBaseObject *pGbObj, const CString &strvID, const CString &strID);
	static void GetVariableDefine_vGetReportValue(CString &strDefine, CExBaseObject *pGbObj, const CString &strvID, const CString &strID);
	static void GetVariableDefine_vGetPara(CString &strDefine, CExBaseObject *pGbObj, const CString &strvID, const CString &strID);
	static void GetVariableDefine_VarAndVal_Value(CString &strDefine, CExBaseObject *pGbObj, const CString &strID, const CString &strValue);
	static void GetVariableDefine_nRsltJdg(CString &strDefine, CExBaseObject *pGbObj);
};

