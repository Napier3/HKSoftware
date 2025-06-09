//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvElement.h  CDsvElement

#pragma once


#include "DsvBase.h"
#include "DsvElemAttr.h"

//任意元素模式
//任意元素
#define DSV_ANYELEMENT_MODE_ANY     _T("any")
//指定的元素
#define DSV_ANYELEMENT_MODE_DEFINE  _T("define")
//序列定义中的Element元素
#define DSV_ANYELEMENT_MODE_IN_SEQUENCE  _T("in-sequence")
//序列定义之外的元素
#define DSV_ANYELEMENT_MODE_OUT_SEQUENCE  _T("out-sequance")
//引用AnyElement元素
#define DSV_ANYELEMENT_MODE_REFERENCE  _T("reference")

#define DSV_ANYELEMENT_MODE_INDEX_NONE          -1
#define DSV_ANYELEMENT_MODE_INDEX_ANY           0
#define DSV_ANYELEMENT_MODE_INDEX_DEFINE        1
#define DSV_ANYELEMENT_MODE_INDEX_IN_SEQUENCE   2
#define DSV_ANYELEMENT_MODE_INDEX_OUT_SEQUENCE  3
#define DSV_ANYELEMENT_MODE_INDEX_REFERENCE     4

class CDsvElement : public CDsvBase
{
public:
	CDsvElement();
	virtual ~CDsvElement();

	CString  m_strMode;

//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDSVELEMENT;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDsvElementKey();     }
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
	virtual BOOL IsAnyDsvObjectEx();
	virtual BOOL IsValidateSucc();

	virtual BOOL ValidateData(CDvmData *pDvmData, CValues *pRptValues);
	virtual BOOL IsAnyDsvObject();
	virtual BOOL DsValidate(CDvmDataset *pDataset, POS &posDataset, CValues *pRptValues, CDsvBase *pPrevAnlyDsvObj=NULL);
	virtual BOOL DsvQuery(CDvmDataset *pDataset, CValues *pRptValues);

	CDsvElemAttr* AddAttr(const CString &strName, const CString &strID, const CString &strDataType, const CString &strOptr, const CString &strValue, const CString &strValue2);
	CDsvElemAttr* AddAttr();

	virtual CString GetValueAttr();
	virtual void GetNameAndValueText(CString &strText, BOOL bAddValue=TRUE);

};

class CDsvAnyElement : public CDsvElement
{
public:
	CDsvAnyElement();
	virtual ~CDsvAnyElement();

public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDSVANYELEMENT;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDsvAnyElementKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CBaseObject* Clone();
	virtual BOOL CopyOwn(CBaseObject* pDest);

	virtual BOOL IsAnyDsvObject();

public:
	void DsValidate(CExBaseList &listElments);
	BOOL IsMode_any();
	BOOL IsMode_define();
	BOOL IsMode_in_sequence();
	BOOL IsMode_out_sequance();
	BOOL IsMode_reference();
	
protected:
	void DsValidate_any(CExBaseList &listElments);
	void DsValidate_define(CExBaseList &listElments);
	void DsValidate_in_sequence(CExBaseList &listElments);
	void DsValidate_out_sequance(CExBaseList &listElments);
	void DsValidate_reference(CExBaseList &listElments);

};
