#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"
#include "gbxmlkeys.h"
#include "DataObj.h"


#define CMD_PARA_ID_BEFORE            0
#define CMD_PARA_ID_AFTER             1
#define CMD_PARA_ID_RETRYMAX          2
#define CMD_PARA_ID_RETRY_BEFORE      3
#define CMD_PARA_ID_RETRY_TIMES       4
#define CMD_PARA_ID_RETRY_GAP         5
#define CMD_PARA_ID_CMMTIMES          6
#define CMD_PARA_ID_CMM_CALMODE       7


class CCmd : public CValues
{
public:
	CCmd();
	virtual ~CCmd();

public:
	virtual UINT GetClassID()		{		return GBCLASSID_CMD;			}

	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

	//缓冲区串行化
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual BSTR GetXmlElementKey()		{	return CGbXMLKeys::g_pGbXMLKeys->m_strCmdKey;	}

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
	virtual BOOL UpdateOwn(CBaseObject* pDest);

	long GetDelayBeforeCmd();
	long GetDelayAfterCmd();
	long GetDelayBeforeRetry();
	long GetTimeLong();
	long GetTimeGap();

	long GetValueBySysPara(const CString& strFind);
	LONG GetCalMode();
	CValues* GetValues()	{	return this;	}

	void UpdateCmdData(CCmd *pCmd, UINT nDataID, BOOL bShowLog);

public:
	CString m_strDatasetPath;  //dataset-path
	//LONG m_nDelayBeforeCmd;
	//LONG m_nDelayAfterCmd;
	CString m_strDelayBeforeCmd; //Modify 2010-12-27
	CString m_strDelayAfterCmd;
	//LONG m_nDelayBeforeRetry;
	CString m_strDelayBeforeRetry;
	LONG m_nMaxRetrytimes;
	//LONG m_nTimeLong;
	//LONG m_nTimeGap;
	CString m_strTimeLong;
	CString m_strTimeGap;

	//多次通讯，处理通讯结果
	CString m_strCalMode;   //计算模式：求取平均值、取最大值、取最小值
	LONG m_nRepeatTimes; //通讯的次数
	long m_nReportFillUseNoRepeat;  //重复测试时，报告填写覆盖第一次
	long m_nUseCurrSetData;   //使用当前设置的数据
	long m_nUseDeviceEx;   //使用扩展设备进行通讯
	CString m_strBeginMode;

	//测试时使用的数据，通讯命令的参数可以为计算公式，这个功能后续添加
	CValues m_oValuesForTest;

	long m_nUseConnect;    //20150107   一些不需要链接的通讯命令
	long m_nZoneIndex;     //通讯命令使用的定值区号，只针对定值

public:
	BOOL HasRepeatTestFinish(long nTimes)
	{
		return (nTimes >= m_nRepeatTimes - 1);
	}

	BOOL GetCmdScript(CString &strScript);
	BOOL IsCmdDataset(UINT nDatasetID);
	BOOL IsCmdNeedWriteToLocal();
	CValue* FindValue(CDataObj *pDataObj);
	BOOL IsEmptyDataset();

	BOOL IsBeginModeSynchro();
	BOOL IsBeginModeAsynchronous();
	void SetBeginModeSynchro();
	void SetBeginModeAsynchronous();

	long CalTestTimeLong();

	void ClearCommCmdParas();
	void AddCommCmdParaValue(const CString &strValID, const CString &strValue);

private:
	static const CString g_strBeginModeSynchro;
	static const CString g_strBeginModeAsynchronous;
};