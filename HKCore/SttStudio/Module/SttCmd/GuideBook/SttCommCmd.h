//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

	//多次通讯，处理通讯结果
	CString m_strCalMode;   //计算模式：求取平均值、取最大值、取最小值
	LONG m_nRepeatTimes; //通讯的次数
	long m_nReportFillUseNoRepeat;  //重复测试时，报告填写覆盖第一次
	long m_nUseCurrSetData;   //使用当前设置的数据
	long m_nUseDeviceEx;   //使用扩展设备进行通讯
	CString m_strBeginMode;

	long m_nUseConnect;    //20150107   一些不需要链接的通讯命令
	long m_nZoneIndex;     //通讯命令使用的定值区号，只针对定值
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

	//2022-10-3  lijunqing 针对智能测试终端软件平台，基于HTML报告模板，通信命令是否需要将关联的数据集填写到
	//报告中，采用标记进行表示，以提高程序运行的效率，否则通过接口函数查询或者每次都将数据传入报告模板进行填写
	//程序运行效率很低
	long m_nFillRptDataset;

//重载函数
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

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	CSttCommCmdData* GetCommCmdData(BOOL bCreate);
	void UpdateEx(CSttCommCmd *pDest);
	virtual long GetItemTestCount();
};

