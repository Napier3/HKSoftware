//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Text.h  CRptTemp_Text

#pragma once

#include "TestMacroRptTemplateGlobal.h"



class CRptTemp_Text : public CExBaseObject
{
public:
	CRptTemp_Text();
	virtual ~CRptTemp_Text();


	CString  m_strText;
	CString  m_strFont;   //字体
	float     m_fSize;     //字号
	long     m_nBold;     //是否加粗

	CString  m_strData1_Id;
	CString  m_strData2_Id;
	CString  m_strData3_Id;
	CString  m_strData4_Id;
	CString  m_strData5_Id;
	CString  m_strData6_Id;
	CString  m_strTextFormat;//用于保留配置的规则，方便实时更新
	void *m_pGbItemBase;  //绑定的测试项目（CGbItemBase或者CSttItemBase）
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_TEXT;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_TextKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

