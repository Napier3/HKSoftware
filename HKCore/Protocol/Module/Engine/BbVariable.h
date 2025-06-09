#pragma once

class CBbVarValue;

#include "../../../module/baseclass/ExBaseObject.h"
#include "ProtocolXmlRWKeys.h"
#include "BbVarValue.h"

class CPpPackage;

class CBbVariable :	public CExBaseObject
{
public:
	CBbVariable(void);
	virtual ~CBbVariable(void);

public:
	CString  m_strType;	//数据类型
	CString m_strVarKind;	//变量种类 系统变量，帧变量等		
	CString m_strValue;
	CBbVarValue m_oValue;

	CPpPackage* GetPackage(UINT nClassID);

public:
		/*virtual void Init()
		virtual long InitAfterSerialize()*/

	    virtual UINT GetClassID(){ return PPCLASSID_BBVARIABLE; };
		virtual BSTR GetXmlElementKey()  {  return CProtocolXmlRWKeys::g_pXmlRWKeys->m_strVariableKey;   };
		/*virtual long IsEqual(CExBaseObject* pObj)
		virtual long Copy(CExBaseObject* pDesObj)
		virtual CExBaseObject* Clone()
		virtual long BinarySerializeOwn(SysTool::IBinarySerialBufferPtr &oBinaryBuff)*/
		virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
		virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	
public:
	void SetValue(CHAR val)			{    m_oValue = val;		}
	void SetValue(BYTE val)			{    m_oValue = val;		}
	void SetValue(SHORT val)		{    m_oValue = val;		}
	void SetValue(USHORT val)	{    m_oValue = val;		}
	void SetValue(INT val)			{    m_oValue = val;		}
	void SetValue(UINT val)			{    m_oValue = val;		}
	void SetValue(LONG val)		{    m_oValue = val;		}
	void SetValue(ULONG val)		{    m_oValue = val;		}
	void SetValue(FLOAT val)		{    m_oValue = val;		}
	void SetValue(DOUBLE val)		{    m_oValue = val;		}
	void SetValue(BSTR val)			{    m_oValue = val;		}

	void SetValue(CHAR *val)		{    m_oValue = val;		}
	void SetValue(BYTE *val)		{    m_oValue = val;		}
	void SetValue(SHORT *val)		{    m_oValue = val;		}
	void SetValue(USHORT *val)	{    m_oValue = val;		}
	void SetValue(INT *val)			{    m_oValue = val;		}
	void SetValue(UINT *val)		{    m_oValue = val;		}
	void SetValue(LONG *val)		{    m_oValue = val;		}
	void SetValue(ULONG *val)		{    m_oValue = val;		}
	void SetValue(FLOAT *val)		{    m_oValue = val;		}
	void SetValue(DOUBLE *val)	{    m_oValue = val;		}
	void SetValue(BSTR *val)		{    m_oValue = val;		}
public:
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
};
