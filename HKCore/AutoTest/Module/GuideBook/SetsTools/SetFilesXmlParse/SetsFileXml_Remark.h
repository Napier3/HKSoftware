//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetsFileXml_Remark.h  CSetsFileXml_Remark

#pragma once

#include "SetFileXmlParseGlobal.h"


#include "SetsFileXml_RI.h"
#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"
class CSetsFileXml_Remark : public CExBaseList
{
public:
	CSetsFileXml_Remark();
	virtual ~CSetsFileXml_Remark();


	long  m_nItemNum;
	long  m_nUpdate;  //是否更新标记
	CString  m_strmd5;
//重载函数

	pugi::xml_node *m_pNode;
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETSFILEXML_REMARK;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetsFileXml_RemarkKey();     }
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

public:
	void GetValStringTotal_V110_Remark(CString &strValTotal);
	void GetMd5_ForCal(CString &strMd5, const CString &strValTotal, BOOL bReCalMd5,BOOL bIsUpdateMD5 = false);

//私有成员变量
private:
	CString m_strMd5_Cal;   //计算得到的MD5

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

