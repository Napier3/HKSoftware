#pragma once

#include "GuideBookDefine.h"
#include "ScriptText.h"
#include "MacroTestParaDatas.h"

class CMacroTestPara : public CExBaseList
{
public:
	CMacroTestPara();
	virtual ~CMacroTestPara();
	virtual void ClearItemInDbState();
	
	CValues *m_pValuesForCal;

protected:
	CString m_strMacroID;
	CString m_strTestMode;

	CScriptText *m_pScript;
	//故障参数
	CMacroTestParaDatas* m_pFaultParaDatas;
	//用户自定义参数
	CMacroTestParaDatasUser* m_pFaultParaDatasUser;

	void CreateScript();
	void CreateFaultParaDatas();
	void CreateFaultParaDatasUser();

public:
	virtual UINT GetClassID()		{		return GBCLASSID_MACROPARA;			}

	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

	virtual void InitAfterRead();

	//缓冲区串行化
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual BSTR GetXmlElementKey();

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	//接口函数
	void SetTestMode(const CString &strMode){m_strTestMode = strMode;}
	CString GetTestMode()				{		return m_strTestMode;		}

	void InitMacroID();
	void SetMacroID(const CString &strID);
	CString GetMacroID()				{		return m_strMacroID;		}

	CMacroTestParaDatas* GetFaultParaDatas()		{	return m_pFaultParaDatas;	}
	CMacroTestParaDatas* GetFaultParaDatasUser()		{	return m_pFaultParaDatasUser;	}
	CString GetParaDatas();
	CString GetParaDatas_UIParas();
	void FreeTestParas();
	CString GetParaDatasString();
	CValues* GetParaValues() {   return m_pValuesForCal;    }
	CScriptText* GetScriptText(){ return m_pScript;}
	
	void InitTestParaDatas(BOOL bInitByMacro=TRUE);
	void UpdateMacroTestParaData(const CShortData  *pData, BOOL bShowLog, BOOL bUseDefaultValue)		{		m_pFaultParaDatas->UpdateMacroTestParaData(pData, bShowLog, bUseDefaultValue);	}
	void UpdateMacroTestParaData(const CString &strID, const CString &strValue, BOOL bShowLog)		{		m_pFaultParaDatas->UpdateMacroTestParaData(strID, strValue, bShowLog, TRUE);	}
	void ResetMacroTestParaData()		{		m_pFaultParaDatas->ResetMacroTestParaData();	}
	void ValidateMacroTestParaData(const CShortData  *pData);
	void UpdateMacroTestParaData(const CShortData  *pData, const CString &strMacroID, BOOL bShowLog)
	{
		if (m_strMacroID == strMacroID)
		{
			m_pFaultParaDatas->UpdateMacroTestParaData(pData, bShowLog, TRUE);
		}
	}
	void UpdateMacroTestParaDataUser(const CShortData  *pData)		
	{		
		ASSERT (m_pFaultParaDatasUser != NULL);
		m_pFaultParaDatasUser->UpdateMacroTestParaDataUser(pData);	
	}

	CExBaseObject* FindMacroTestParaData(const CShortData  *pData)		{		return m_pFaultParaDatas->FindMacroTestParaData(pData);	}

	BOOL IsOwnMacroTestData(const CString &strID);

private:
	void CalFaultParaDatas();
	void CalFaultParaDatasUser();
	void CalFaultParaDatas(CMacroTestParaDatas *pParaDaras);
	BOOL CalFaultParaData(const CString &strExpress, CValue* pData, BOOL bLogError=FALSE);
	CShortData* GetMacroTestData(const CString &strID);
	BOOL IsValueTimeNeedTransFrom_ms_s(const CString &strID);
};

CTestMacros* Gb_GetMacrosPtr(CExBaseObject *pItem);
CTestMacro* Gb_GetMacroPtr(CExBaseObject *pItem);
CTestMacro* Gb_GetMacroPtr(CExBaseObject *pItem, const CString &strMacroID);
