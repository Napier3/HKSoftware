#pragma once
#include "ProtocolXmlRWKeys.h"
#include "BbVariable.h"

class CBbVariables :	public CExBaseList
{
public:
	CBbVariables(CString strXmlKey);
	virtual ~CBbVariables(void);

public:

	CString m_strXmlKey;//XML文件的关键字，在读写xml文件的过程中，数据接口和变量都使用CbbVariables对象，所以需要此属性来保存xml的element关键字
public:
		/*virtual void Init()
		virtual long InitAfterSerialize()*/

	    virtual UINT GetClassID(){ return PPCLASSID_BBVARIABLES; };
		virtual BSTR GetXmlElementKey()  {  return m_strXmlKey.AllocSysString();   };
		/*virtual long IsEqual(CExBaseObject* pObj)*/
		
		virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
		virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

		virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
		virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	CBbVariable* AddVariable(const CString &strID, const CString &strDataType);

public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
	void GetVariablesString(CString &strVariables);
	void Append(CExBaseList &oDestList);
	void CloneAppend(CExBaseList &oDestList);

	long FindVariableByID(const CString &strID, CExBaseList &oDestList);
	long FindVariableByName(const CString &strName, CExBaseList &oDestList);
};
