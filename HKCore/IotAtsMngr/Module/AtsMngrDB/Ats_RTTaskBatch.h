//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_RTTaskBatch.h  CAts_RTTaskBatch

#pragma once

#include "ATSMNGRGlobal.h"
#include "Ats_RTDevice.h"
#include "../../../Module/DataMngr/DvmDevice.h"
#include "../SensorPpCfg/SensorPpDeviceType.h"

#define ATS_TASKBATCH_STATE_NOTSTART	0
#define ATS_TASKBATCH_STATE_NOTFINISH	1
#define ATS_TASKBATCH_STATE_FINISH		2

class CAts_RTTaskBatch : public CExBaseList
{
public:
	CAts_RTTaskBatch();
	virtual ~CAts_RTTaskBatch();


	long  m_nIndex_TaskBatch;
	long  m_nIndex_Task;
	CString  m_strDvmFile;
	CString  m_strGbxmlFile;
	CString  m_strReportPkgFile;
	CString  m_strEngineRawPkgFile;
	CString  m_strVmRawPkgFile;
	SYSTEMTIME  m_tmStartTime;
	SYSTEMTIME  m_tmEndTime;
	long  m_nState;//0:未开始，1：未结束，2：结束

	static CAts_RTTaskBatch *CreateRTTaskBatch(const CString &strName,const CString &strID,const CString &strGbxml,const CString &strPacketPath);

//重载函数
public:
	virtual UINT GetClassID() {    return ATSCLASSID_CATS_RTTASKBATCH;   }
	virtual BSTR GetXmlElementKey()  {      return CATSMNGRXmlRWKeys::CAts_RTTaskBatchKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_TaskBatch;     }
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CATSMNGRXmlRWKeys::CAts_RTTaskBatchKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CATSMNGRXmlRWKeys::CAts_RTDeviceKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CATSMNGRXmlRWKeys::Index_TaskBatchKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_TaskBatch);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_TaskBatch = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);
	virtual CExBaseObject* DB_CreateNewChild();

public:
	CDvmDevice *m_pDvmDeviceRef;	//数据设备模型
	CSensorPpDeviceType *m_pSensorPpCfg;//传感器规约配置对象，为空表示不是传感器对象

	CDvmDevice *GetDvmDevice();
	CDvmDataset *FindDataModel(const CString &strID);
	
public:
	CFile m_oRptFile;
	BOOL WriteReportData(char *pBuf,long nLen,long &nWritePos);

	void SetState_NotStart(){m_nState = ATS_TASKBATCH_STATE_NOTSTART;}
	void SetState_NotFinish(){m_nState = ATS_TASKBATCH_STATE_NOTFINISH;}
	void SetState_Finish(){m_nState = ATS_TASKBATCH_STATE_FINISH;}
	BOOL IsState_NotStart(){return (m_nState == ATS_TASKBATCH_STATE_NOTSTART);}
	BOOL IsState_Finish(){return (m_nState == ATS_TASKBATCH_STATE_FINISH);}
};

