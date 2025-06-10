#pragma once

#include "../../Module/xml/XmlRWInterface.h"
#include "../../Module/DataMngr/DataGroup.h"
#include "SttMacroXmlKeys.h"

inline BSTR stt_NameKey()			{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strNameKey;}
inline BSTR stt_IDKey()				{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strIDKey;}
inline BSTR stt_UnitKey()			{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strParaUnitKey;}
inline BSTR stt_DataTypeKey()	{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strParaDataTypeKey;}
inline BSTR stt_ValueKey()			{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strParaValueKey;}
inline BSTR stt_DefValueKey()		{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strParaDefValueKey;}
inline BSTR stt_ParaKey()			{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strParaKey;}
inline BSTR stt_ParaGroupKey()	{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strParaGroupKey ;	}
inline BSTR stt_FormatKey()          {  return CMacroXmlKeys::g_pMacroXmlKeys->m_strParasFormatKey;}

inline BSTR stt_TestMacrosKey()		{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strTestMacrosKey ;	}
inline BSTR stt_TestMacroKey()		{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strTestMacroKey ;	}
inline BSTR stt_FaultParasKey()		{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strFaultParasKey ;	}
inline BSTR stt_FaultParasExKey()	{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strFaultParasExKey ;	}
inline BSTR stt_SysParasKey()			{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strSysParasKey ;	}
inline BSTR stt_ResultsKey()			{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strResultsKey ;	}
inline BSTR stt_ResultExKey()			{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strResultExKey ;	}
inline BSTR stt_ParasKey()			{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strParasKey ;	}
inline BSTR stt_SearchResultsKey()			{	return CMacroXmlKeys::g_pMacroXmlKeys->m_strSearchResultsKey ;	}//zhouhj 20210925 增加用于搜索类返回结果

#define STT_XML_SERIALIZE_MODE_ERROR              0
#define STT_XML_SERIALIZE_MODE_READ               1
#define STT_XML_SERIALIZE_MODE_WRITE              2
#define STT_XML_SERIALIZE_MODE_RIGISTER           3
#define STT_XML_SERIALIZE_MODE_UpdateSysParas     4 //更新系统参数的模式 zhouhj 2024.5.20

#define STT_XML_SERIALIZE_SYS_PARA_ID_VNom       "VNom"
#define STT_XML_SERIALIZE_SYS_PARA_ID_INom       "INom"
#define STT_XML_SERIALIZE_SYS_PARA_ID_FNom       "FNom"
#define STT_XML_SERIALIZE_SYS_PARA_ID_OldVNom    "OldVNom"//模板中原有系统参数ID
#define STT_XML_SERIALIZE_SYS_PARA_ID_OldINom    "OldINom"
#define STT_XML_SERIALIZE_SYS_PARA_ID_OldFNom    "OldFNom"



class CSttXmlSerializeBase : public CExBaseList
{
public:
	CSttXmlSerializeBase(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement)
	{
		m_pXmlElement = pElement;
		m_pXmlDoc = pXmlDoc;
		m_pDataGroup = NULL;
	}

	CSttXmlSerializeBase(CDataGroup *pDataGroup)
	{
		m_pDataGroup = pDataGroup;
		m_pXmlElement = NULL;
		m_pXmlDoc = NULL;
	}
	
	virtual ~CSttXmlSerializeBase()
	{
	}
	
protected:
	CSttXmlSerializeBase()	{			}
	CXmlRWElementBase *m_pXmlElement;
	CXmlRWDocBase *m_pXmlDoc;
	CDataGroup *m_pDataGroup;

public:
	CXmlRWElementBase* CreateElement(BSTR bstrElementKey)
	{
		if (bstrElementKey == NULL)
		{
			return m_pXmlDoc->CreateElement(stt_ParaKey(), m_pXmlElement);
		}
		else
		{
			return m_pXmlDoc->CreateElement(bstrElementKey, m_pXmlElement);
		}
	}

public:
	virtual CSttXmlSerializeBase* create_new(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement, BOOL bAddChild) = 0;
	virtual unsigned long get_serialize_mode()		{	return STT_XML_SERIALIZE_MODE_ERROR;	}
	virtual BOOL IsSttGroupXmlSerialize(){return FALSE;}
	CXmlRWElementBase* GetElement()			{	return m_pXmlElement;	}
    CXmlRWDocBase * GetRWDoc(){return m_pXmlDoc;}
	CDataGroup* GetDataGroup() {return m_pDataGroup;}

public:
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,CString &strAttrVal, BSTR bstrElementKey = NULL) ;
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,wchar_t *strAttrVal, BSTR bstrElementKey = NULL) ;
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,long &nAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,int &nAttrVal, BSTR bstrElementKey = NULL);
    virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,unsigned int &unAttrVal, BSTR bstrElementKey = NULL) ;

#ifdef _PSX_QT_LINUX_
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,BOOL &bAttrVal, BSTR bstrElementKey = NULL);
#endif

	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,double &dAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,short &unAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,float &fAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,char *strAttrVal, BSTR bstrElementKey = NULL) ;

	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey = NULL);
	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey = NULL);

	//2021-6-1  lijunqing : use bstrElementKey and nIndex 
	virtual CSttXmlSerializeBase* xml_serialize(BSTR bstrElementKey, long nIndex, const char *pszName,const char *pszID, const char *pszDataTypeID) ;

	//增加用于电压电流幅值、频率比对系统参数串行化
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);
};

//2020-4-6  lijq
inline BOOL stt_xml_serialize_is_read(CSttXmlSerializeBase *pSttXmlSerialize)
{
	return (STT_XML_SERIALIZE_MODE_READ == pSttXmlSerialize->get_serialize_mode());
}

inline BOOL stt_xml_serialize_is_write(CSttXmlSerializeBase *pSttXmlSerialize)
{
	return (STT_XML_SERIALIZE_MODE_WRITE == pSttXmlSerialize->get_serialize_mode());
}

inline BOOL stt_xml_serialize_is_register(CSttXmlSerializeBase *pSttXmlSerialize)
{
	return (STT_XML_SERIALIZE_MODE_RIGISTER == pSttXmlSerialize->get_serialize_mode());
}

class CSttXmlSerializeRead : public CSttXmlSerializeBase
{
public:
	CSttXmlSerializeRead(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement);
	virtual ~CSttXmlSerializeRead();

protected:
	CSttXmlSerializeRead()	{		}

	CXmlRWElementBase* FindElement(const char *pszID, BSTR bstrElementKey);
	CXmlRWElementBase* FindElement(BSTR bstrElementKey, long nIndex);  //2021-6-1  lijunqing
	CXmlRWElementBase* FindElement(BSTR bstrElementKey, BSTR bstrAttrID, const char *pszAttrValue,   long nIndex);  //2021-6-5  lijunqing

public:
	virtual CSttXmlSerializeBase* create_new(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement, BOOL bAddChild)
	{
		CSttXmlSerializeRead *pNew = new CSttXmlSerializeRead(pXmlDoc, pElement);

		if (bAddChild)
		{
			AddNewChild(pNew);
		}

		return pNew;
	}
	virtual unsigned long get_serialize_mode()		{	return STT_XML_SERIALIZE_MODE_READ;	}

public:
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,CString &strAttrVal, BSTR bstrElementKey = NULL) ;
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,wchar_t *strAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,long &nAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,int &nAttrVal, BSTR bstrElementKey = NULL);
    virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,unsigned int &unAttrVal, BSTR bstrElementKey = NULL);
#ifdef _PSX_QT_LINUX_
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,BOOL &bAttrVal, BSTR bstrElementKey = NULL);
#endif
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,double &dAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,short &unAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,float &fAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,char *strAttrVal, BSTR bstrElementKey = NULL);

	//增加用于电压电流幅值、频率比对系统参数串行化
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);

	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey = NULL);
	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey = NULL);
	
	//2021-6-1  lijunqing : use bstrElementKey and nIndex 
	virtual CSttXmlSerializeBase* xml_serialize(BSTR bstrElementKey, long nIndex, const char *pszName,const char *pszID, const char *pszDataTypeID);
};

class CSttXmlSerializeWrite : public CSttXmlSerializeBase
{
public:
	CSttXmlSerializeWrite(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement);
	virtual ~CSttXmlSerializeWrite();

protected:
	CSttXmlSerializeWrite()	{		}

public:
	virtual CSttXmlSerializeBase* create_new(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement, BOOL bAddChild)
	{
		CSttXmlSerializeWrite *pNew = new CSttXmlSerializeWrite(pXmlDoc, pElement);

		if (bAddChild)
		{
			AddNewChild(pNew);
		}

		return pNew;
	}
	virtual unsigned long get_serialize_mode()		{	return STT_XML_SERIALIZE_MODE_WRITE;	}

public:
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,CString &strAttrVal, BSTR bstrElementKey = NULL) ;
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,wchar_t *strAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,long &nAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,int &nAttrVal, BSTR bstrElementKey = NULL);
    virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,unsigned int &unAttrVal, BSTR bstrElementKey = NULL);
#ifdef _PSX_QT_LINUX_
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,BOOL &bAttrVal, BSTR bstrElementKey = NULL);
#endif
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,double &dAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,short &unAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,float &fAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,char *strAttrVal, BSTR bstrElementKey = NULL);

	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey = NULL);
	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey = NULL);

	//2021-6-1  lijunqing : use bstrElementKey and nIndex 
	virtual CSttXmlSerializeBase* xml_serialize(BSTR bstrElementKey, long nIndex, const char *pszName,const char *pszID, const char *pszDataTypeID);
	//增加用于电压电流幅值、频率比对系统参数串行化
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);
};

class CSttXmlSerializeRegister : public CSttXmlSerializeWrite
{
public:
	CSttXmlSerializeRegister(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement);
	virtual ~CSttXmlSerializeRegister();

protected:
	CSttXmlSerializeRegister()	{		}

public:
	virtual CSttXmlSerializeBase* create_new(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement, BOOL bAddChild)
	{
		CSttXmlSerializeRegister *pNew = new CSttXmlSerializeRegister(pXmlDoc, pElement);
		
		if (bAddChild)
		{
			AddNewChild(pNew);
		}

		return pNew;
	}
	virtual unsigned long get_serialize_mode()		{	return STT_XML_SERIALIZE_MODE_RIGISTER;	}

public:
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,CString &strAttrVal, BSTR bstrElementKey = NULL) ;
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,wchar_t *strAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,long &nAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,int &nAttrVal, BSTR bstrElementKey = NULL);
    virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,unsigned int &unAttrVal, BSTR bstrElementKey = NULL);
#ifdef _PSX_QT_LINUX_
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,BOOL &bAttrVal, BSTR bstrElementKey = NULL);
#endif
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,double &dAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,short &unAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,float &fAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,char *strAttrVal, BSTR bstrElementKey = NULL);

	//增加用于电压电流幅值、频率比对系统参数串行化
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);

	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey = NULL);
	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey = NULL);
	virtual CSttXmlSerializeBase* xml_serialize(BSTR bstrElementKey, long nIndex, const char *pszName,const char *pszID, const char *pszDataTypeID);

};


//////////////////////////////////////////////////////////////////////////

class CSttDataGroupSerializeRead : public CSttXmlSerializeBase
{
public:
	CSttDataGroupSerializeRead(CDataGroup *pDataGroup);
	virtual ~CSttDataGroupSerializeRead();

protected:
	CSttDataGroupSerializeRead()	{		}

public:
	virtual CSttXmlSerializeBase* create_new(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement, BOOL bAddChild)
	{
		CSttXmlSerializeRead *pNew = new CSttXmlSerializeRead(pXmlDoc, pElement);

		if (bAddChild)
		{
			AddNewChild(pNew);
		}

		return pNew;
	}
	virtual unsigned long get_serialize_mode()		{	return STT_XML_SERIALIZE_MODE_READ;	}
	virtual BOOL IsSttGroupXmlSerialize(){return TRUE;}//20220803 zhouhj

	//添加单个系统参数
	BOOL AddSysPara(const CString &strSysParaID,const CString &strOldSysParaID,double dCurrValue);

public:
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,CString &strAttrVal, BSTR bstrElementKey = NULL) ;
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,wchar_t *strAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,long &nAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,int &nAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,unsigned int &unAttrVal, BSTR bstrElementKey = NULL);
#ifdef _PSX_QT_LINUX_
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,BOOL &bAttrVal, BSTR bstrElementKey = NULL);
#endif
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,double &dAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,short &unAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,float &fAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,char *strAttrVal, BSTR bstrElementKey = NULL);

	//增加用于电压电流幅值、频率比对系统参数串行化
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);

	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey = NULL);
	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey = NULL);

	//2021-6-1  lijunqing : use bstrElementKey and nIndex 
	virtual CSttXmlSerializeBase* xml_serialize(BSTR bstrElementKey, long nIndex, const char *pszName,const char *pszID, const char *pszDataTypeID);

	CDataGroup m_oSysParasList;//存放当前被读取的xml内的系统参数和当前实际的系统参数
};


//////////////////////////////////////////////////////////////////////////

class CSttDataGroupSerializeRegister : public CSttXmlSerializeBase
{
public:
	CSttDataGroupSerializeRegister(CDataGroup *pDataGroup);
	virtual ~CSttDataGroupSerializeRegister();

protected:
	CSttDataGroupSerializeRegister()	{		}

public:
	virtual CSttXmlSerializeBase* create_new(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement, BOOL bAddChild)
	{
		CSttXmlSerializeRead *pNew = new CSttXmlSerializeRead(pXmlDoc, pElement);

		if (bAddChild)
		{
			AddNewChild(pNew);
		}

		return pNew;
	}


	virtual unsigned long get_serialize_mode()		{	return STT_XML_SERIALIZE_MODE_RIGISTER;	} //yyj 20210906
	virtual BOOL IsSttGroupXmlSerialize(){return TRUE;}//20220803 zhouhj

public:
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,CString &strAttrVal, BSTR bstrElementKey = NULL) ;
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,wchar_t *strAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,long &nAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,int &nAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,unsigned int &unAttrVal, BSTR bstrElementKey = NULL);
#ifdef _PSX_QT_LINUX_
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,BOOL &bAttrVal, BSTR bstrElementKey = NULL);
#endif
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,double &dAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,short &unAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,float &fAttrVal, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,char *strAttrVal, BSTR bstrElementKey = NULL);

	//增加用于电压电流幅值、频率比对系统参数串行化
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);

	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey = NULL);
	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey = NULL);

	//2021-6-1  lijunqing : use bstrElementKey and nIndex 
	virtual CSttXmlSerializeBase* xml_serialize(BSTR bstrElementKey, long nIndex, const char *pszName,const char *pszID, const char *pszDataTypeID);
};

//////////////////////////////////////////////////////////////////////////

class CSttSerializeUpdateSysParas : public CSttXmlSerializeBase
{
public:
	CSttSerializeUpdateSysParas();
	virtual ~CSttSerializeUpdateSysParas();

	virtual CSttXmlSerializeBase* create_new(CXmlRWDocBase *pXmlDoc, CXmlRWElementBase *pElement, BOOL bAddChild)
	{
		CSttSerializeUpdateSysParas *pNew = NULL;//new CSttSerializeUpdateSysParas(pXmlDoc, pElement);

		if (bAddChild)
		{
			AddNewChild(pNew);
		}

		return pNew;
	}

	virtual unsigned long get_serialize_mode()		{	return STT_XML_SERIALIZE_MODE_UpdateSysParas;	}
	virtual BOOL IsSttGroupXmlSerialize(){return FALSE;}

	//添加单个系统参数
	BOOL AddSysPara(const CString &strSysParaID,const CString &strOldSysParaID
		,double dCurrValue,double dOldValue);

	//增加用于电压电流幅值、频率比对系统参数串行化
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		double &dAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);
	virtual BOOL xml_serialize_sys_pata(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,
		float &fAttrVal,const char *pszSysParaID, BSTR bstrElementKey = NULL);
	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, long nIndex, const char *pszDataTypeID, BSTR bstrElementKey = NULL);
	virtual CSttXmlSerializeBase* xml_serialize(const char *pszName,const char *pszID, const char *pszDataTypeID, BSTR bstrElementKey = NULL);

	CDataGroup m_oSysParasList;//存放当前被读取的xml内的系统参数和当前实际的系统参数
};