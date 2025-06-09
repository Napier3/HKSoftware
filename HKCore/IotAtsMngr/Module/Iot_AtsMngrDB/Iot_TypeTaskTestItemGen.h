//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TypeTaskTestItemGen.h  CIot_TypeTaskTestItemGen

#pragma once

#include "Iot_AtsMngrGlobal.h"



class CIot_TypeTaskTestItemGen : public CExBaseObject
{
public:
	CIot_TypeTaskTestItemGen();
	virtual ~CIot_TypeTaskTestItemGen();


	long  m_nIndex_Gen;
	long  m_nIndex_Bench;
	long  m_nIndex_Items;
	//20230609：讨论确定增加该字段
	long  m_nSelect; //表需要增加“select”字段，对应界面上的勾选状态
	CString  m_strPara1_Name;
	CString  m_strPara1_Id;
	float  m_fPara1_Value;
	CString  m_strPara2_Name;
	CString  m_strPara2_Id;
	float  m_fPara2_Value;
	CString  m_strPara3_Name;
	CString  m_strPara3_Id;
	float  m_fPara3_Value;
	CString  m_strPara4_Name;
	CString  m_strPara4_Id;
	float  m_fPara4_Value;
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_TYPETASKTESTITEMGEN;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestItemGenKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Gen;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestItemGenKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_GenKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Gen);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Gen = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CIot_TypeTaskTestItemGens : public CExBaseList
{
public:
	CIot_TypeTaskTestItemGens();
	virtual ~CIot_TypeTaskTestItemGens();


	//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_TYPETASKTESTITEMGENS;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestItemGensKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestItemGenKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestItemGenKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

	//私有成员变量
private:

	//私有成员变量访问方法
public:

	//属性变量访问方法
public:
	BOOL QueryItemGens(CXDbBaseLib *pXDbLib, long nItemsIndex, long nBenchIndex);
};