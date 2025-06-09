#pragma once
#include "SttParaObject.h"

#include "../../../Module/MemBuffer/EquationBuffer.h"
#include "../../../Module/BaseClass/StringSerializeBuffer.h"

class CSttParaObjects : public CExBaseList  
{
public:
	CSttParaObjects(void);
	virtual ~CSttParaObjects(void);
		virtual UINT GetClassID() {        return PARACLASSID_PARAS;                               }

protected:
	BSTR m_strXmlElementName;//Xml元素名称

public:
	CSttParaObject* RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue,const char *value);//, const CString &strGroup=_T(""));
	CSttParaObject* RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue, int *value);//, const CString &strGroup=_T(""));
	CSttParaObject* RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue, long *value);//, const CString &strGroup=_T(""));
	CSttParaObject* RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue, float *value);//, const CString &strGroup=_T(""));
	CSttParaObject* RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue, double *value);//, const CString &strGroup=_T(""));
	CSttParaObject* RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue, unsigned char *value);//, const CString &strGroup=_T(""));
	CSttParaObject* RegisterPara(const CString &strName,const CString &strID,const CString &strUnit,const CString &strDataTypeID,const CString &strDefaultValue, short *value);//, const CString &strGroup=_T(""));
	CSttParaObject* RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue,const char *value);//, const char* strGroup=NULL);
	CSttParaObject* RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, int *value);//, const char* strGroup=NULL);
	CSttParaObject* RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, long *value);//, const char* strGroup=NULL);
	CSttParaObject* RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, float *value);//, const char* strGroup=NULL);
	CSttParaObject* RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, double *value);//, const char* strGroup=NULL);
	CSttParaObject* RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, unsigned char *value);//, const char* strGroup=NULL);
	CSttParaObject* RegisterPara(const char *pszName,const char *pszID,const char *pszUnit,const char *pszDataTypeID,const char *pszDefaultValue, short *value);//, const char* strGroup=NULL);

	void UnRegisterPara(const char *pszID);
	void UnRegisterPara(const CString &strID);
	void UnRegisterPara(LPVOID pValAddr);

	void EditParaName(const char *pszID, const char *pszName);
	void EditParaName(const CString &strID, const CString &strName);
	void EditParaName(LPVOID pValAddr, const char *pszName);

	////WriteXML
    void SetXmlElementName(BSTR strXmlName)	{	m_strXmlElementName = strXmlName;	}
	virtual BSTR GetXmlElementKey() {	return m_strXmlElementName;	}
    //virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	virtual CSttParaObject* FindByVariable(const CString strID);
	virtual float GetValueByVariable(CString strID);
	virtual void GetParameter(CString &strParameter, BOOL bOnlyGetChange=FALSE);
	virtual void GetReportEx(CString &strReport);
	virtual void GetReportEx(CStringSerializeBuffer &oBinaryBuffer);
	virtual void Parser(CEquationBuffer *pEquation);
	virtual void InitDefault();

    virtual void ReadParas(CXmlRWNodeBase &oNode, BSTR bstrParasKey);
    virtual void ReadParas(CXmlRWNodeListBase &oParas);

protected:
	virtual void FindPara(const char *pszID, CSttParaObject **ppFind, POS *pPos);
	virtual void FindPara(const CString &strID, CSttParaObject **ppFind, POS *pPos);
	virtual void FindPara(LPVOID pValAddr, CSttParaObject **ppFind, POS *pPos);

};
