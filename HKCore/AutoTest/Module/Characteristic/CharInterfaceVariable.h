//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharInterfaceVariable.h  CCharInterfaceVariable

#pragma once

#include "CharacteristicGlobal.h"



class CCharInterfaceVariable : public CExBaseObject
{
public:
	CCharInterfaceVariable();
	virtual ~CCharInterfaceVariable();

	CString  m_strValue;
	//��ֵ��صļ���ű�
	CString  m_strScript;
	//CExBaseObject *m_pDataObjRef;
//���غ���
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
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	BOOL GetVariableValue(CString &strValue);
	void InitVariableValue();
};

BOOL CharVar_CalScriptValue(CCharInterfaceVariable *pCharVar);
CExBaseObject* CharVar_GetScriptValObj(CCharInterfaceVariable *pCharVar);
CString* CharVar_CalScriptValue(CExBaseObject *pData);
void CharVar_CalScriptValue(CExBaseObject *pData, CString &strValue);
