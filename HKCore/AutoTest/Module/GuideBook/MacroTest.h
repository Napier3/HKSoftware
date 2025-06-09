#pragma once

#include "GbItemBase.h"
#include "GuideBookDefine.h"
#include "Msg.h"
#include "MacroTestPara.h"
#include "CommCmd.h"
#include "TestMacroUiParas.h"

class CMacroTest : public CGbItemBase
{
public:
	CMacroTest();
	virtual ~CMacroTest();
	virtual CGbItemBase* CloneForTempFile();


	static CMacroTest* _New(CBaseObject *pParent=NULL)
	{
		CMacroTest *pNew = new CMacroTest();
		pNew->InitAfterRead();
		pNew->SetParent(pParent);
		pNew->InitMacroID();
		return pNew;
	}

	void InitMacroID();

public:
	CString m_strType;
	long m_nRepeatTimes;  //重复次数
	long m_nReportFillUseNoRepeat;  //重复测试时，报告填写覆盖第一次
	long m_nTestTimes;

	//报告处理方式:
	//0=每次独立的报告，own
	//1=最后一次作为报告
	//2=平均值作为报告，average
	//3=最大值，max
	//4=最小值，min
	CString m_strReportMode;   

	LONG GetCalMode()
	{
		return Gb_GetReportCalMode(m_strReportMode);
	}

protected:
	CExBaseList m_oListMsgs;
	CMacroTestPara* m_pPara;
	//shaolei 2022-01-05
	CTestMacroUiParas* m_pUiParas;

public:
	//shaolei 2022-01-05
	CTestMacroUiParas* GetTestMacroUiParas()	{	return m_pUiParas;	}
	CTestMacroUiParas* CreateTestMacroUiParas();
	void SetTestMacroID(const CString &strTestMacroID);
	CString GetTestMacroID();
	CExBaseList* GetMsgs()						{		return &m_oListMsgs;			}
	CMacroTestPara* GetMacroTestPara();
	CMacroTestParaDatas* GetFaultParaDatas();
	CMacroTestParaDatas* GetFultParaDatasUser();
	virtual BOOL GetItemParaValue(const CString &strValueID, double &dValue);
	virtual long SetItemParaValue(const CString & strValueID, const CString & strValue, BOOL bAddNew=FALSE);

	virtual void AdjustReprtDatas();
	void UpdateMacroTestParaData(const CShortData  *pData, BOOL bShowLog, BOOL bUseDefaultValue)		{		m_pPara->UpdateMacroTestParaData(pData, bShowLog,bUseDefaultValue);	}
	void ValidateMacroTestParaData(const CShortData  *pData)		{		m_pPara->ValidateMacroTestParaData(pData);	}
	void UpdateMacroTestParaData(const CShortData  *pData, const CString &strMacroID, BOOL bShowLog)		{		m_pPara->UpdateMacroTestParaData(pData, strMacroID, bShowLog);	}
	void UpdateMacroTestParaData(const CString &strID, const CString &strValue, BOOL bShowLog)		{		m_pPara->UpdateMacroTestParaData(strID, strValue, bShowLog);	}
	void ResetMacroTestParaData()		{		m_pPara->ResetMacroTestParaData();	}
	CExBaseObject* FindMacroTestParaData(const CShortData  *pData)		{		return m_pPara->FindMacroTestParaData(pData);	}
	void UpdateMacroTestParaDataUser(const CShortData  *pData)		{		m_pPara->UpdateMacroTestParaDataUser(pData);	}

//重写父类方法
public:
	virtual UINT GetClassID()		{		return GBCLASSID_MACROTEST;			}

	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	
	virtual BSTR GetXmlElementKey(){		return CGbXMLKeys::g_pGbXMLKeys->m_strMacroTestKey;	};

	virtual void InitAfterRead();

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);

	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

#ifdef GUIDEBOOK_DEV_MODE
	virtual void GenerateDevReports();
#endif

	virtual void ClearReport(BOOL bBack=TRUE);

	virtual void ReplaceSrciptText(CScriptText *pScript, UINT nScriptClassID, CGbItemBase *pSrcGbItem, BOOL bShowLog);
	void FreeTestParas()	{	m_pPara->FreeTestParas();	}

public:
	virtual long CalTestTimeLong();
	virtual long GetState();
	virtual void ClearItemInDbState();
	virtual void SetTkID(long nTkID);
	virtual void SetSelect(long nSelect);

	//shaolei 20220607
	virtual void SetItemState(long nShow, long nEnable, long nSelect, BOOL bSetShow, BOOL bSetEnable, BOOL bSetSelect);

	//处理SV接收压板一致性测试，智能生成对应的测试项目
	//形参：SV接收压板数据集
	void GenSvMatchItems(CExBaseList *pDataSet);
	void GenSvMatchItems_GetSubCommCmd(CCommCmd **ppEnaOn, CCommCmd **ppReadAin, CCommCmd **ppEnaOff);
	virtual long GetItemTestCount();
	void GetTestTimes(long &nCurrTestTimes, long &nRepeatTimes);
};

void Gb_ResetMacroParas(CTestMacro* pMacro);
void Gb_ResetDatas(CShortDatas *pDatas);
CString Gb_GetMacroScriptUiDll(CMacroTest *pMacroTest);
