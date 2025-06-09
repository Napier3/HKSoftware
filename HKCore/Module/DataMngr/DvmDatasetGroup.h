//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDatasetGroup.h  CDvmDatasetGroup

#pragma once

#include "DvmDataset.h"

class CDvmDatasetGroup : public CDvmDataset
{
public:
	CDvmDatasetGroup();
	virtual ~CDvmDatasetGroup();

//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDVMDATASETGROUP;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmDatasetGroupKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual BOOL CopyChildren(CBaseObject* pDest);
	CBaseObject* CloneEx(BOOL bCopyOwn,BOOL bCopyChildren);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);
	virtual void InitAfterRead();

	virtual BOOL UpdateDataValue(CDvmDataset *pSrcDataset, BOOL bIsNew = FALSE);

//私有成员变量
private:
	void CopyChildrenWithDwData(CExBaseList* pSrc, CExBaseList* pDest);

//私有成员变量访问方法
public:
	//shaolei 2021-12-04
	void FilterDataExEqualValueStr(CExBaseList &oDestList, const CString &strTagID, const CString &strValue);
	void FilterDataExHasValueStr(CExBaseList &oDestList, const CString &strTagID, const CString &strValue);
	void FilterDataExHasNoValueStr(CExBaseList &oDestList, const CString &strTagID, const CString &strValue);
	void FilterCombineDataEx(CString &strValues, const CString &strTagID, CString &strSeparator);
	
};
