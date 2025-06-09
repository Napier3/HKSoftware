
#pragma once

#include "SetFileXmlParseGlobal.h"


//#include "SetsFileXml_HI.h"
#include "SetsFileXml_UI.h"
#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"
class CSetsFileXml_Update : public CExBaseList
{
public:
	CSetsFileXml_Update();
	virtual ~CSetsFileXml_Update();


	long  m_nItemNum;
	pugi::xml_node *m_pNode;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETSFILEXML_UPDATE;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetsFileXml_UpdateKey();     }
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

//私有成员变量
private:

//私有成员变量访问方法
public:
	void SetItemNum(long nNum);
	void ClearAllXmlNode();

//属性变量访问方法
public:
	void GetMd5_FromFile(const CString &strClass, CString &strMd5);
	CSetsFileXml_UI* FindUIByClass(const CString &strClass);
	CSetsFileXml_UI* FindUIByClass_Grp(const CString &strClass, long nGrp);
	CSetsFileXml_UI* AddNewUI(const CString &strLd, const CString &strClass, long nGrp, const CString &strMd5);
};

