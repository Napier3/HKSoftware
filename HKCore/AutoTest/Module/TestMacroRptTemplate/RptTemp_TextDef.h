//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_TextDef.h  CRptTemp_TextDef

#pragma once

#include "TestMacroRptTemplateGlobal.h"
#include "RptTemp_Enable.h"
#include "../../../Module/DataMngr/DataGroup.h"



class CRptTemp_TextDef : public CExBaseList
{
public:
	CRptTemp_TextDef();
	virtual ~CRptTemp_TextDef();


	CString  m_strFont;   //字体
	float     m_fSize;     //字号
	long     m_nBold;     //是否加粗
	CString  m_strText;
	CString  m_strData1_Id;
	CString  m_strData2_Id;
	CString  m_strData3_Id;
	CString  m_strData4_Id;
	CString  m_strData5_Id;
	CString  m_strData6_Id;
	CString  m_strHAlignType; //文本水平对齐方式 AlignLeft和空值:左对齐 AlignRight：右对齐 AlignCenter：水平居中 //ftt 2024.12.10

//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_TEXTDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_TextDefKey();     }
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
	CRptTemp_Enable *m_pEnable;

//私有成员变量访问方法
public:
	CRptTemp_Enable* GetEnable()	{	return m_pEnable;	}

//属性变量访问方法
public:
	BOOL IsEnable(CExBaseList *pParas);
	CDataGroup* GetItemsTec();
};

