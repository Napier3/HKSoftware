#pragma once
#include "SttParaObjects.h"
class CSttTestBaseInterface;


class CSttParaObjectsGroup : public CSttParaObjects  
{
public:
	CSttParaObjectsGroup(void);
	virtual ~CSttParaObjectsGroup(void);
	virtual UINT GetClassID() {        return PARACLASSID_PARAGROUP;                               }

	CString m_strDataType; 
	//CString m_strCounterVar; //�������������������������Ϊ�գ����ܶ�̬����

public:
	CSttParaObjectsGroup* RegisterGroup(const CString &strName, const CString &strID, const CString &strDataType, LPVOID pItemData);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey();
    virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
    virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual void GetParameter(CString &strParameter, BOOL bOnlyGetChange=FALSE);
	virtual void GetReportEx(CString &strReport);
	virtual void GetReportEx(CStringSerializeBuffer &oBinaryBuffer);
	virtual void Parser(CEquationBuffer *pEquation);
	virtual void InitDefault();

//	virtual void ReadParas(CXmlRWNodeBase &oNode, BSTR bstrParasKey);
    virtual void ReadParas(CXmlRWNodeListBase &oParas);
	void DeleteAllGroup(const CString &strDataType);
	long GetGroupCount(const CString &strDataType);
	CSttParaObjectsGroup* GetGroup(const CString &strDataType, long nIndex);
	BOOL DeleteGroup(const CString &strDataType, long nIndex);
	void GetParaIDPath(CString &strPath, CSttParaObject *pPara);
	CString GetParaIDPath(CSttParaObject *pPara);
	CSttTestBaseInterface* GetSttTestBaseInterface();
};
