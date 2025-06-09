//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TypeTask.h  CIot_TypeTask

#pragma once

#include "Iot_AtsMngrGlobal.h"


//型式检验任务表
class CIot_TypeTask : public CExBaseObject
{
public:
	CIot_TypeTask();
	virtual ~CIot_TypeTask();


	long  m_nIndex_Task;
	CString  m_strId_User;
	long  m_nState_Create;
	CString  m_strSn_Sample;
	CString  m_strName_Sample;
	CString  m_strModel_Sample;
	long  m_nCnt_Sample;
	CString  m_strName_Client;
	CString  m_strName_Manufactor;
	CString  m_strAddress_Client;
	CString  m_strAddress_Manufactor;
	CString  m_strName_Template;
	CString  m_strPic_File;
	CString  m_strPic_File_S;
	CString  m_strTask_File;
	CString  m_strTask_File_S;
	CString  m_strDvm_File;
	CString  m_strDvm_File_S;
	CString  m_strDoc_File;
	CString  m_strDoc_File_S;
	CString  m_strId_Maininspection;
	CString  m_strId_Checker;
	CString  m_strId_Proofreader;
	CString  m_strInspection_Type;
	long  m_nTask_State;      //任务状态: 0-待测试；1-测试异常；2-测试中断；3-测试中；4-测试完成-不合格；5-测试完成-合格
	long  m_nTask_Rpt_State;  //任务报告状态: 0-未导出报告；1-已导出报告
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_TYPETASK;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Task;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_TaskKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Task);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Task = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL QueryTypeTaskByIndex(CXDbBaseLib *pXDbLib, long nIndex_TypeTask);
	BOOL UpdateSampleCnt(CXDbBaseLib *pXDbLib, long nIndex_TypeTask, long nSampleCnt);
};

