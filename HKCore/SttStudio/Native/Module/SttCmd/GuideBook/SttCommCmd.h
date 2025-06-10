//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttCommCmd.h  CSttCommCmd

#pragma once

#include "../SttCmdDefineGlobal.h"

#include "SttItemBase.h"

//////////////////////////////////////////////////////////////////////////
//CSttCmdData
class CSttCommCmdData : public CValues
{
public:
	CSttCommCmdData();
	virtual ~CSttCommCmdData();

	CString m_strDatasetPath;  //dataset-path
	CString m_strDelayBeforeCmd; //Modify 2010-12-27
	CString m_strDelayAfterCmd;
	CString m_strDelayBeforeRetry;
	LONG m_nMaxRetrytimes;
	CString m_strTimeLong;
	CString m_strTimeGap;

	//���ͨѶ������ͨѶ���
	CString m_strCalMode;   //����ģʽ����ȡƽ��ֵ��ȡ���ֵ��ȡ��Сֵ
	LONG m_nRepeatTimes; //ͨѶ�Ĵ���
	long m_nReportFillUseNoRepeat;  //�ظ�����ʱ��������д���ǵ�һ��
	long m_nUseCurrSetData;   //ʹ�õ�ǰ���õ�����
	long m_nUseDeviceEx;   //ʹ����չ�豸����ͨѶ
	CString m_strBeginMode;

	long m_nUseConnect;    //20150107   һЩ����Ҫ���ӵ�ͨѶ����
	long m_nZoneIndex;     //ͨѶ����ʹ�õĶ�ֵ���ţ�ֻ��Զ�ֵ
public:
	virtual UINT GetClassID() {    return STTGBXMLCLASSID_CSTTCOMM_DATA;   }
	virtual BSTR GetXmlElementKey();
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

private:
	static const CString g_strStt_BeginModeSynchro;
	static const CString g_strStt_BeginModeAsynchronous;

};

//////////////////////////////////////////////////////////////////////////
//CSttCommCmd
class CSttCommCmd : public CSttItemBase
{
public:
	CSttCommCmd();
	virtual ~CSttCommCmd();

	CString  m_strCommCmdID;  //2022-9-14  lijunqing
	//CString  m_strType;
	CString  m_strRwOptr;
	long  m_nSortSoeByT;
	long  m_nDsvRunAfterResultScript;
	long  m_nCmdExecModeForMgrpt;

	//2022-10-3  lijunqing ������ܲ����ն����ƽ̨������HTML����ģ�壬ͨ�������Ƿ���Ҫ�����������ݼ���д��
	//�����У����ñ�ǽ��б�ʾ������߳������е�Ч�ʣ�����ͨ���ӿں�����ѯ����ÿ�ζ������ݴ��뱨��ģ�������д
	//��������Ч�ʺܵ�
	long m_nFillRptDataset;

//���غ���
public:
	virtual UINT GetClassID() {    return STTGBXMLCLASSID_CSTTCOMMCMD;   }
	virtual BSTR GetXmlElementKey();//  {      return CSttCmdDefineXmlRWKeys::CSttCommCmdKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	//2022-10-14  lijunqing
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	CSttCommCmdData* GetCommCmdData(BOOL bCreate);
	void UpdateEx(CSttCommCmd *pDest);
	virtual long GetItemTestCount();
};

