//PttAtsTransTool.h  CPttAtsTransTool

#pragma once

#include "MacroMap\MacroMaps.h"
#include "Parser\PNTplParse.h"

#include "..\..\..\Module\MemBuffer\EquationBuffer.h"
#include "..\..\..\Module\XfileMngrBase\XFolder.h"
#include "..\..\..\Module\XfileMngrBase\XFileMngr.h"

#include "..\GuideBook\GuideBook.h"
#include "..\GuideBook\MacroTest.h"
#include "..\GuideBook\Safety.h"

#include "PttGlobalDefine.h"
#include "..\GuideBook\Script\GbScriptGenerateTool.h"

#define  RsltExprVar_type_SysPara        1
#define  RsltExprVar_type_Setting         2
#define  RsltExprVar_type_MacroPara    3
#define  RsltExprVar_type_MacroRslt     4

//20200831 shaolei
//修改LUA脚本与XVM脚本功能兼容，暂时不考虑PowerTest模板转换功能，PowerTest模板转换的脚本暂定为LUA
class CPttAtsTransTool 
{
public:
	CPttAtsTransTool();
	virtual ~CPttAtsTransTool();

public:
	CString TransPttFile (const CString& strFile);

protected:
	CMacroMaps m_oMacroMaps; 
	CPNTplParse m_oFileParse;

	CString m_strPttFile;
	CGuideBook *m_pGuideBook;
	CDevice *m_pDevice;
	CItems *m_pItems_ProtectionRelay;
	BOOL m_bUseGlobalSetting;
	BOOL m_bHasTransTestObject;

	//以下的几个变量，用于参数转换
	CPNTplElement *m_pElementBinary;
	CDataSet m_oBinaryDataset;
	CMacroMap *m_pCurMacroMap;

	CPNTplElement *m_pElementCommonPara;
	CPNTplElement *m_pElementSetting;
	CPNTplElement *m_pElementTestItem;
	
	CExBaseList *m_pSystemParas;
	CExBaseList *m_pDsSettings;

	CMacroTestPara *m_pCurMacroTestPara;

public:
	void TransRoot(CPNTplRoot* _pRoot);
	void TransElement(CPNTplElement *pElement);

	void InitTestObject();
	void TransElement_TestObject(CPNTplElement *pElement);
	void TransElement_GlobalSetting(CPNTplElement *pElement);
	void TransElement_ProtectionRelay(CPNTplElement *pElement);
	void TransElement_CommonParameter(CPNTplElement *pElement);
	void TransElement_Setting(CPNTplElement *pElement);
	void TransElement_CFG(CPNTplElement *pElement);
	void TransElement_Binary(CPNTplElement *pElement);
	void TransElement_TextInput(CPNTplElement *pElement);
	void TransElement_Character(CPNTplElement *pElement);
	void TransElement_CalculatorExp(CPNTplElement *pElement);
	void TransElement_Report(CPNTplElement *pElement);
	void TransElement_TestPoint(CPNTplElement *pElement);
	void TransElement_TestItem(CPNTplElement *pElement);
	void CheckInputValues(CPNTplElement *pElement);
	BOOL CheckInput_Valid(CPNTplEquation *pInput);
	void InitBefore_TransTestItem(CPNTplElement *pElement,const CString &strMacroID,CMacroTestPara *pMacroTestPara);
	void TransElement_MacroTest_Paras(CPNTplElement *pElement, CMacroMap *pMacroMap);
	void TransElement_MacroTest_ParasEx(CPNTplElement *pElement, CMacroMap *pMacroMap);
	void TransElement_MacroTest_Paras_Expr(CString &strAtsParaValue, CMacroMap *pMacroMap);
	void TransElement_MacroTest_RsltScript(CPNTplElement *pElement, CMacroTest *pMacroTest, CMacroMap *pMacroMap);
	void TransElement_MacroTest_RsltScript_Var(CExBaseList &listVars, CPNTplEquation *pEquation, CString &strExpr, CMacroMap *pMacroMap);
	void TransElement_MacroTest_RsltScript_VarDef(CExBaseList &listVars, CString &strScript);
	void TransElement_MacroTest_RsltScript_VarSet(CExBaseList &listVars, CString &strScript);
	void TransElement_TestItem_Safety(const CString &strHint, const CString &strItemName);
	void Trans_MacroMap_Exprs(CPNTplElement *pElement, CMacroMap *pMacroMap);
	void Trans_MacroMap_Expr(CPNTplElement *pElement, CParaMapExpr *pParaMapExpr);
	void Trans_MacroMap_Expr_Cal(CPNTplElement *pElement, CParaMapCal *pParaMapCal);

//	void UpdateMacroTestParaData(CMacroTestPara *pMacroTestPara,const CString &strAtsParaID, const CString &strAtsParaValue, BOOL bShowLog);
	void Replcae_ElementEquationValue(CPNTplElement *pElement,const CString &strName,const CString &strValue);
	CMacroMap *FindMacroMapObj(CMacroMaps *pMacroMaps,const CString &strMacroID,CPNTplElement *pElement);

	void Trans_ComboBox_SysParas_Settings(CPNTplElement *pElement);
	void Trans_ComboBox_Dataset(CPNTplElement *pElement ,CDataSet *pDataset);

	double Trans_MacroMap_CalExpr(const CString &strExpr);
	double Trans_MacroMap_GetEquationVal(CPNTplEquation *pEquation);
	double Trans_MacroMap_GetValueByVarID(const CString &strVarID);
	CPNTplEquation* Trans_MacroMap_FindValueByVarID(const CString &strVarID);
	BOOL GetKeyValue(CExBaseList *pList, const CString &strKey, CString &strValue);
	BOOL GetKeyValue(CExBaseList *pList, const CString &strKey, float &fValue);
	BOOL GetKeyValue(CExBaseList *pList, const CString &strKey, long &nValue);
	void TransElement_Dataset(CExBaseList *pDataset, CPNTplElement *pElement);
	void TransGroup(CExBaseList *pDataset, CPNTplGroup *pGroup);

	void TransSpecialCharacters(CString &strName);
	CExBaseList* GetDvmDataset_Setting();
	BOOL IsSettingSysPara(const CString &strVar);
	BOOL IsVarMacroPara(const CString &strVar);
	BOOL AddSetting_TestItem(CDataSet *pSetting,const CString &strSettingName,const CString &strSettingID,CPNTplElement *pElement,const CString &strEquationID);

protected:
	class CRsltExprVar : public CExBaseObject
	{
	public:
		CRsltExprVar()	{	m_pGuideBook = NULL;	};
		virtual ~CRsltExprVar()	{}

		UINT m_nVarType;
		CGuideBook *m_pGuideBook;

		void AppendVarDefScript(CString &strScript)
		{
			CString strDef;
			switch (m_nVarType)
			{
			case RsltExprVar_type_SysPara:
				//strScript.AppendFormat(_T("local v%s = GetTestPara(\"%s\");\r\n"), m_strID, m_strID);
				CGbScriptGenerateTool::GetVariableDefine_vGetTestPara(strDef, m_pGuideBook, m_strID, m_strID);
				strScript += strDef;
				break;

			case RsltExprVar_type_Setting:
				//strScript.AppendFormat(_T("local v%s = GetDsDataValue(\"Prot$dsSetting$%s\");\r\n"), m_strID, m_strID);
				CGbScriptGenerateTool::GetVariableDefine_vGetDsDataValue(strDef, m_pGuideBook, m_strID, m_strID);
				strScript += strDef;
				break;

			case RsltExprVar_type_MacroPara:
			case RsltExprVar_type_MacroRslt:
				//strScript.AppendFormat(_T("local v%s = GetReportValue(\"\", \"%s\");\r\n"), m_strID, m_strID);
				CGbScriptGenerateTool::GetVariableDefine_vGetReportValue(strDef, m_pGuideBook, m_strID, m_strID);
				strScript += strDef;
				break;
			}
		}

		void AppendVarSetScript(CString &strScript)
		{
			if (m_nVarType == RsltExprVar_type_MacroRslt)
			{
				strScript.AppendFormat(_T("vString=tostring(v%s);\r\nSetReportValStr(\"\", \"%s\", vString);\r\n"), m_strID, m_strID);
			}
		}

		void AppendVarAndExpr(CString &strExpr, BOOL bFirst)
		{
			if (m_nVarType != RsltExprVar_type_MacroRslt)
			{
				return;
			}

			if (bFirst)
			{
				strExpr.AppendFormat(_T("v%s"), m_strID);
			}
			else
			{
				strExpr.AppendFormat(_T(" and v%s"), m_strID);
			}
		}
	};

	void NewRsltExprVar(CExBaseList *pList, const CString &strVar, UINT nVarType);
	void NewRsltExprVar(CExBaseList *pList, const CString &strVar);

	BOOL GetEquationMapValue(CPNTplEquation *pEquation,CString &strValue);
};