//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharInterfaceVariable.h  CCharInterfaceVariable

#pragma once

#include "CharacteristicGlobal.h"



class CCharInterfaceVariable : public CExBaseObject
{
public:
	CCharInterfaceVariable();
	virtual ~CCharInterfaceVariable();

	CString  m_strValue;
	//定值相关的计算脚本
	CString  m_strScript;
	//CExBaseObject *m_pDataObjRef;
//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARINTERFACEVARIABLE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharInterfaceVariableKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual long InsertToListCtrl(CListCtrl *pListCtrl,long lItemIndex);
	virtual long UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex);
//私有成员变量
private:

//私有成员变量访问方法
public:
	BOOL GetVariableValue(CString &strValue);
	void InitVariableValue();
};

BOOL CharVar_CalScriptValue(CCharInterfaceVariable *pCharVar);
CExBaseObject* CharVar_GetScriptValObj(CCharInterfaceVariable *pCharVar);
CString* CharVar_CalScriptValue(CExBaseObject *pData);
void CharVar_CalScriptValue(CExBaseObject *pData, CString &strValue);
