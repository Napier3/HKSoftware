#pragma once

#include "GbItemBase.h"
#include "GuideBookDefine.h"
#include "Standard.h"
#include "Msg.h"
#include "DllCall.h"


class CSafety : public CGbItemBase
{
public:
	CSafety();
	virtual ~CSafety();
	virtual CGbItemBase* CloneForTempFile();

	static CSafety* _New(CBaseObject *pParent=NULL)
	{
		CSafety *pNew = new CSafety();
		pNew->InitAfterRead();
		return pNew;
	}

//属性
public:
	CString m_strType;
	long m_nDataMode;		//三种模式 Datas,Table,Script

	CExBaseList m_oListMsgs;
	CStandard* m_pStandard;
	CShortDatas*  m_pDatas;
	//SystemTool::ISysTablePtr m_oTable;
	CScriptText* m_pScriptText;
	CString m_strSoundFile;
	CDllCall *m_pDllCall;
// 	long    m_nDelayTime;    //延时的时间，主要针对脚本的模式，即执行完脚本后延时一定的时间
	
	CString m_strQRCodeData;
	long    m_nManyDeviceTestMode;

	static const CString g_strQRCodeDataID;
	static const CString g_strQRCodeFileID;
	static const CString g_strQRCodeFile;
	static const CString g_strEan13CodeFile;

	static void AddQRCodeDatas(CShortDatas *pDatas);

private:
	static CShortDatas *g_pQRCodeDatas;
	static long  g_nQRCodeDatas;
	
public:
	static void CreateQRCodeDatas();
	static void ReleaseQRCodeDatas();
	static CShortDatas* GetQRCodeDatas();

//公共接口
public:
	void SetType(CString strType)								{		m_strType = strType;		}
	CString GetType()														{		return m_strType;		}
	void SetDataMode(long nDataMode)				{		m_nDataMode = nDataMode;		}
	long GetDataMode()													{		return m_nDataMode;		}

	CStandard* GetStandard()										{		return m_pStandard;		}
	CExBaseList* GetMsgs()											{		return &m_oListMsgs;		}
	CShortDatas*  GetDatas()			{		return m_pDatas;		}
	CScriptText* GetScriptText()									{		return m_pScriptText;		}

	BOOL IsManyDeviceTestMode_OneTime()		{	return m_nManyDeviceTestMode == GbMdItemTestMode_OneTime;	}
	BOOL IsManyDeviceTestMode_ManyTime()	{	return m_nManyDeviceTestMode == GbMdItemTestMode_ManyTime;	}
	void SetManyDeviceTestMode_OneTime()	{	m_nManyDeviceTestMode = GbMdItemTestMode_OneTime;	}
	void SetManyDeviceTestMode_ManyTime()	{	m_nManyDeviceTestMode = GbMdItemTestMode_ManyTime;	}
	
	virtual BOOL GetItemParaValue(const CString &strValueID, double &dValue);
	virtual void InitAfterRead();
	long SetItemParaValue(const CString & strValueID, const CString & strValue, BOOL bAddNew=FALSE);
	CString GetWaveFilePath();
	CDllCall* GetDllCall()	{	return m_pDllCall;		}

	BOOL IsTypeDllCall(BOOL bValide=TRUE);//	{	return (m_nDataMode == SAFETY_DATAMODE_DLLCALL);	}
	
	CDllCall* CreateDllCall()	
	{
		if (m_pDllCall == NULL)
		{
			m_pDllCall = new CDllCall;
			AddNewChild(m_pDllCall);
		}

		return m_pDllCall;
	}

// 	void AddQRCodeData(const CString &strQRCode);
	BOOL IsQRCode();
	void AddQRCodeValues(CValues *pValues);
	CString GetQRCodeFile();
	CString GetQRCodePngFile();
	void WriteQRCodePngFile();

	void ParseBarCode(const char *pBuffer, char chSeparateChar, char chSeparateEndChar);
//重写父类方法
public:
	virtual UINT GetClassID()			{		return GBCLASSID_SAFETY;		}

	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{		return CGbXMLKeys::g_pGbXMLKeys->m_strSafetyKey;	}

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

#ifdef GUIDEBOOK_DEV_MODE
	virtual void GenerateDevReports();
	//void AddResultJudgeKey(CValues* pValues,long nResult);
#endif

	BOOL IsSafetyDataModeScript()
	{
		return (m_nDataMode == SAFETY_DATAMODE_SCRIPT);
	}
	BOOL IsSafetyDataModeQRCode()
	{
		return (m_nDataMode == SAFETY_DATAMODE_QRCODE);
	}
	BOOL IsSafetyDataModeList()
	{
		return (m_nDataMode == SAFETY_DATAMODE_LIST);
	}

	virtual void ReplaceSrciptText(CScriptText *pScript, UINT nScriptClassID, CGbItemBase *pSrcGbItem, BOOL bShowLog);
	void DeleteAllDatas_DLL();
	void AddDatas_DLL(CDvmData *pResults);

public:
	void InitDataMode();
	void InitDataModeType();

public:
	virtual long CalTestTimeLong();

	//2021-3-28  lijunqing  根据数据集创建安全措施的数据对象
	void CreateSafetyDatasByDvmDataset(CDataSet *pDataSet, CValues *pAttrs,const CString &strDataType, const CString &strDataFormat, const CString &strDefValue);

	//shaolei 20220607
	virtual void SetItemState(long nShow, long nEnable, long nSelect, BOOL bSetShow, BOOL bSetEnable, BOOL bSetSelect);

	//2023-4-17  lijunqing
	void AddMsg(const CString &strID, const CString &strMsg);

	virtual long GetItemTestCount();
	virtual void ClearReport(BOOL bBack=TRUE);
	void DeleteAllMsgs();  //shaolei 2023-7-19 删除所有提示信息
};