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

	//���������л�
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

	//���ͨѶ������ͨѶ���
	CString m_strCalMode;   //����ģʽ����ȡƽ��ֵ��ȡ���ֵ��ȡ��Сֵ
	LONG m_nRepeatTimes; //ͨѶ�Ĵ���
	long m_nReportFillUseNoRepeat;  //�ظ�����ʱ��������д���ǵ�һ��
	long m_nUseCurrSetData;   //ʹ�õ�ǰ���õ�����
	long m_nUseDeviceEx;   //ʹ����չ�豸����ͨѶ
	CString m_strBeginMode;

	//����ʱʹ�õ����ݣ�ͨѶ����Ĳ�������Ϊ���㹫ʽ��������ܺ������
	CValues m_oValuesForTest;

	long m_nUseConnect;    //20150107   һЩ����Ҫ���ӵ�ͨѶ����
	long m_nZoneIndex;     //ͨѶ����ʹ�õĶ�ֵ���ţ�ֻ��Զ�ֵ

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