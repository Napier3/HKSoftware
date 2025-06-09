//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetsFileXml_HashInfo.h  CSetsFileXml_HashInfo

#pragma once

#include "SetFileXmlParseGlobal.h"


#include "SetsFileXml_HI.h"
#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"
class CSetsFileXml_HashInfo : public CExBaseList
{
public:
	CSetsFileXml_HashInfo();
	virtual ~CSetsFileXml_HashInfo();


	long  m_nItemNum;

	pugi::xml_node *m_pNode;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETSFILEXML_HASHINFO;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetsFileXml_HashInfoKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	
	void SetItemNum(long nNum);
	void ClearAllXmlNode();

//私有成员变量
private:
	
//私有成员变量访问方法
public:

//属性变量访问方法
public:
	void GetMd5_FromFile(const CString &strClass, CString &strMd5);
	CSetsFileXml_HI* FindHIByClass(const CString &strClass);
};

