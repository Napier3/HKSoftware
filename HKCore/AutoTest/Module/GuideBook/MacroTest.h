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
	long m_nRepeatTimes;  //�ظ�����
	long m_nReportFillUseNoRepeat;  //�ظ�����ʱ��������д���ǵ�һ��
	long m_nTestTimes;

	//���洦��ʽ:
	//0=ÿ�ζ����ı��棬own
	//1=���һ����Ϊ����
	//2=ƽ��ֵ��Ϊ���棬average
	//3=���ֵ��max
	//4=��Сֵ��min
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

//��д���෽��
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

	//����SV����ѹ��һ���Բ��ԣ��������ɶ�Ӧ�Ĳ�����Ŀ
	//�βΣ�SV����ѹ�����ݼ�
	void GenSvMatchItems(CExBaseList *pDataSet);
	void GenSvMatchItems_GetSubCommCmd(CCommCmd **ppEnaOn, CCommCmd **ppReadAin, CCommCmd **ppEnaOff);
	virtual long GetItemTestCount();
	void GetTestTimes(long &nCurrTestTimes, long &nRepeatTimes);
};

void Gb_ResetMacroParas(CTestMacro* pMacro);
void Gb_ResetDatas(CShortDatas *pDatas);
CString Gb_GetMacroScriptUiDll(CMacroTest *pMacroTest);
