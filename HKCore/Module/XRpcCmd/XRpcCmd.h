//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XRpcCmd.h  CXRpcCmd

#pragma once

class CXRpcCmdPara : public CExBaseObject
{
	
};

class CXRpcCmd : public CExBaseList
{
public:
	CXRpcCmd();
	virtual ~CXRpcCmd();


	CString  m_strDataType;

#ifdef _DVM_VALUE_USE_CHAR_
	wchar_t m_strValue[_DVM_VALUE_LENGTH_];
#else
	CString  m_strValue;
#endif

#ifdef DVM_USE_MAP
	CExBaseObject *m_pDvmMapObj;
#endif

//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDVMVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CXRpcCmdKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	
	//缓冲区串行化
	virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:

#ifdef DVM_USE_MAP
	BOOL IsAllMap();
#endif
	CXRpcCmd* FindValueByID(const CString &strValueID);

};


//////////////////////////////////////////////////////////////////////////
//CDvmBrcb
class CDvmBrcbValue : public CXRpcCmd
{
public:
	CDvmBrcbValue();
	virtual ~CDvmBrcbValue();

	//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDVMBRCBVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmDataKey();     }
	virtual CBaseObject* Clone();
};