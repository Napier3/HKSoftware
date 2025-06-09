#pragma once

#include "GuideBookDefine.h"
#include "../../../Module/TestMacro/TestMacros.h"
class CScriptText;

//用户自定义数据,在测试时,用户可能多次修改同一个参数数据
//CMacroTestParaDataUser用于保存每次的修改
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

	//缓冲区串行化
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual BSTR GetXmlElementKey();

	virtual BOOL IsEqual(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDesObj);
	virtual CBaseObject* Clone();
};

//测试参数数据,即参数计算的表达式，在自动测试时，作为CMacroTestParaDatasUser的子对象时
//表示用户修改过的参数数据对象，此时其子对象为CMacroTestParaDataUser
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

	//缓冲区串行化
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