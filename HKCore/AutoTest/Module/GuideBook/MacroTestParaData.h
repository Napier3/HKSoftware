#pragma once

#include "GuideBookDefine.h"
#include "../../../Module/TestMacro/TestMacros.h"
class CScriptText;

//�û��Զ�������,�ڲ���ʱ,�û����ܶ���޸�ͬһ����������
//CMacroTestParaDataUser���ڱ���ÿ�ε��޸�
class CMacroTestParaDataUser : public CExBaseObject
{
public:
	CMacroTestParaDataUser();
	virtual ~CMacroTestParaDataUser();

public:
	CString m_strExpression;

public:
	virtual UINT GetClassID()		{		return GBCLASSID_FAULTPARAS_PARA_USER;			}

	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

	//���������л�
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual BSTR GetXmlElementKey();

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
};

//���Բ�������,����������ı��ʽ�����Զ�����ʱ����ΪCMacroTestParaDatasUser���Ӷ���ʱ
//��ʾ�û��޸Ĺ��Ĳ������ݶ��󣬴�ʱ���Ӷ���ΪCMacroTestParaDataUser
class CMacroTestParaData : public CExBaseList
{
public:
	CMacroTestParaData();
	virtual ~CMacroTestParaData();

	CString m_strExpression;
	CString m_strExpressionBack;

public:
	virtual UINT GetClassID()		{		return GBCLASSID_FAULTPARAS_PARA;			}

	//ReadXML
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);

	//WriteXML
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElemen, CXmlRWKeys *pXmlRWKeys);

	//���������л�
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual BSTR GetXmlElementKey();

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID);

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();

	void SetToDataValue(CShortData  *pData);
	void SetExpression(const CString &strExpress)	{	m_strExpression = strExpress;	}
	CString GetExpression()		{	return m_strExpression;		}

	void AddMacroTestParaDataUser(const CString &strExpression);

private:
	CMacroTestParaDataUser* FindByExpression(const CString &strExpression);
	void InsertNewDataUser(const CString &strExpression);
};