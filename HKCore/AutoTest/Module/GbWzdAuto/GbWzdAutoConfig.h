//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbWzdAutoConfig.h  CGbWzdAutoConfig

#pragma once

#include "GbWzdAutoGlobal.h"


#include "GbWzdAutoTemplate.h"

class CGbWzdAutoConfig : public CExBaseList
{
public:
	CGbWzdAutoConfig();
	virtual ~CGbWzdAutoConfig();


	CString  m_strDvmFile;
	CString  m_strGbxmlFile;
	CString  m_strRel_Path;  //相对路径
	CString  m_strAuto;   //是否全自动拼接模板 1=全自动；0=单步走；
	long m_nDICount;      //开入数量
	long m_nDOCount;      //开出数量
	long m_nEnaCount;     //压板数量
	CString m_strBmk_DITest;  //开入测试书签名
	CString m_strBmk_DOTest;  //开出测试书签名

	CExBaseList *m_pScriptLocalLib;

//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CGBWZDAUTOCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::CGbWzdAutoConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:
	CGbWzdAutoTemplate* AddGbWzdAutoTemplate(const CString &strName, const CString &strID, const CString &strGbxmlFile, long nBinOffset, long nBoutOffset);
	CString GetDvmFile();
	CString GetGbxmlFile();
	long FindTemplateByNameHas(const CString &strName);
};

