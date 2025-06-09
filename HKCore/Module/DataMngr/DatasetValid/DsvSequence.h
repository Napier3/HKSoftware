//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvSequence.h  CDsvSequence

#pragma once

#include "DsvElement.h"

class CDsvChoice;

class CDsvSequence : public CDsvBase
{
public:
	CDsvSequence();
	virtual ~CDsvSequence();


//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDSVSEQUENCE;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDsvSequenceKey();     }
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
	CDsvAnyElement* AddAnyElement(const CString &strText, long nOption, long nUnbound);
	CDsvElement* AddElement(const CString &strText, long nOption, long nUnbound);
	CDsvChoice*  AddChoice(long nOption, long nUnbound);
	CDsvSequence* AddSequence(long nOption, long nUnbound);

	virtual BOOL DsValidate(CDvmDataset *pDataset,CValues *pRptValues, BOOL bValidateHead=TRUE);
	virtual BOOL DsValidate(CDvmDataset *pDataset, POS &posDataset, CValues *pRptValues, CDsvBase *pPrevAnlyDsvObj=NULL);
	virtual BOOL DsvQuery(CDvmDataset *pDataset, CValues *pRptValues);

	virtual void GetNameAndValueText(CString &strText, BOOL bAddValue=TRUE);

	long FindDsvElementIndex(CExBaseObject *pElement);

};

