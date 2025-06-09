//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvBase.h  CDsvBase

#pragma once

#include "../DataMngrGlobal.h"
#include "../DvmDataset.h"
#include "../Values.h"

class CDsvBase : public CExBaseList
{
public:
	CDsvBase();
	virtual ~CDsvBase();


	long  m_nMinOcc;
	long  m_nMaxOcc;

	CExBaseList m_listDsvMatch;
	BOOL m_bDsvSucc;
	
//重载函数
public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);

//私有成员变量
private:

//私有成员变量访问方法
public:
	virtual CDsvBase* GetFirstDsvElement();
	virtual BOOL IsAnyDsvObject()	{	return FALSE;	}
	virtual BOOL DsValidate(CDvmDataset *pDataset, POS &posDataset,CValues *pRptValues, CDsvBase *pPrevAnlyDsvObj=NULL)	{	ASSERT (FALSE);	return FALSE;	}
	virtual BOOL DsvQuery(CDvmDataset *pDataset, CValues *pRptValues)	{	ASSERT (FALSE);	return FALSE;	}

	virtual BOOL IsValidateSucc();
	virtual long GetAllMatchObjects(CExBaseList &listMatchObject, CExBaseList &listAnyDsvMatchObject);

	virtual CString GetText();
	virtual CString GetValueAttr()	{	return _T("");	}
	virtual void GetNameAndValueText(CString &strText, BOOL bAddValue=TRUE){};
	virtual BOOL IsElement();
};

