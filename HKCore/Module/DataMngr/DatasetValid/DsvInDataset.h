//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvInDataset.h  CDsvInDataset

#pragma once

#include "DsvSequence.h"

class CDsvInDataset : public CDsvSequence
{
public:
	CDsvInDataset();
	virtual ~CDsvInDataset();


//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDSVINDATASET;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDsvInDatasetKey();     }
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
// 	CDsvElement* AddElement(const CString &strText, long nOption, long nUnbound);
// 
// 	virtual BOOL DsValidate(CDvmDataset *pDataset, BOOL bValidateHead=TRUE);
// 	virtual BOOL DsValidate(CDvmDataset *pDataset, POS &posDataset, CDsvBase *pPrevAnlyDsvObj=NULL);
};

