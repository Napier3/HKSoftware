#pragma once
#include "../../../Module/System/VariantDataAddress.h"
#include "SttMacroXmlKeys.h"

#define KEYTYPE_RESULTKEY		0X1
#define KEYTYPE_PARAMETERKEY	0X2

#define PARACLASSID_PARA            (CLASSID_BASECLASS + 0x00000101)
#define PARACLASSID_PARAS           (CLASSID_LISTCLASS + 0x00000102)
#define PARACLASSID_PARAGROUP       (CLASSID_LISTCLASS + 0x00000103)

//参数注册时是否注册描述信息，比如名称、单位等
extern BOOL g_bParaRegisterDescInfor;// = FALSE;
extern BOOL g_bValidateParaWhenRegist;// = FALSE;
extern BOOL g_bValueFromStringWhenRegister;

class CSttParaObject : public CExBaseObject
{
public:
	CSttParaObject(void);
	virtual ~CSttParaObject(void);
	
		virtual UINT GetClassID() {        return PARACLASSID_PARA;                               }

	CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,int *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,long *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,float *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,double *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,unsigned char *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,short *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	CSttParaObject(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,const char *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,int *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,long *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,float *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,double *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,unsigned char *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,short *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	CSttParaObject(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,const char *value);//,long nKeyType=KEYTYPE_PARAMETERKEY);

	BOOL CompareID(const char *pszID)			{	return (m_strID == CString(pszID));					}
	BOOL CompareID(const CString &strID)		{	return (m_strID == strID);								}
	BOOL CompareValAddr(LPVOID pValAddr)	{	return m_varValue.CompareValAddr(pValAddr);	}
	void SetCreateGroup(const CString &strCreateGroup)						{	m_strCreateGroup = strCreateGroup;	}

public:
	CString m_strUnit;				//关键字的单位
	CString m_strDataTypeID;		//关键字的数据类型
	CString m_strDefaultValue;		//关键字的缺省值
//	long	m_nKeyType;
//	CString m_strGroup;
	CVariantDataAddress m_varValue;	//关键字的实际值
	CString m_strCreateGroup;

private:
	void SetPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	void SetPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue);//,long nKeyType=KEYTYPE_PARAMETERKEY);
	
	
public:
	void ValidateParaWhenRegist();
	CString GetParaPath_ID();
	CString GetParaPath_Name();

public:
	//读写XML
	virtual BSTR GetXmlElementKey() {	return CMacroXmlKeys::g_pMacroXmlKeys->m_strParaKey;	}
    virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
    virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	void SetParaValue(const CString &strValue, BOOL bUpdateDefault=TRUE);
	float GetValue();
	CString GetValueString()		{		return m_varValue.ToString();		}
	CString GetVariable()	{	return m_strID;}
	CString GetName()	{	return m_strName;}
// 	void SetGroup(const CString &strGrouop)	{	m_strGroup = strGrouop;	}
// 	void SetGroup(const char* strGrouop)	{	if (strGrouop != NULL)	m_strGroup = strGrouop;	}
	BOOL IsParaChanged();
	void InitByDefault();
};
