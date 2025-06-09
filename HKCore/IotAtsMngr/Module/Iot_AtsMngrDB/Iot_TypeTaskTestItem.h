//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TypeTaskTestItem.h  CIot_TypeTaskTestItem

#pragma once

#include "Iot_AtsMngrGlobal.h"

#define Task_Test_Item_Type_Item_Items         _T("items")
#define Task_Test_Item_Type_Item_Commcmd       _T("commcmd")
#define Task_Test_Item_Type_Item_MacroTest     _T("macrotest")
#define Task_Test_Item_Type_Item_SysParaEdit   _T("sysparaedit")
#define Task_Test_Item_Type_Item_Safety        _T("safety")

//任务记录-子项目表
class CIot_TypeTaskTestItem : public CExBaseObject
{
public:
	CIot_TypeTaskTestItem();
	virtual ~CIot_TypeTaskTestItem();


	long  m_nIndex_Item;
	long  m_nIndex_Task;
	CString  m_strSn_Items;
	long  m_nState;
	CString  m_strTm_Test;
	CString  m_strTempreture;
	CString  m_strHumidity;
	CString  m_strRpt_File;
	CString  m_strRpt_File_S;
	CString  m_strType_Item;
	long  m_nIndex_Test;
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_TYPETASKTESTITEM;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestItemKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Item;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestItemKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_ItemKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Item);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Item = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

