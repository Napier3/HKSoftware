//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DvmDatasetGroup.h  CDvmDatasetGroup

#pragma once

#include "DvmDataset.h"

class CDvmDatasetGroup : public CDvmDataset
{
public:
	CDvmDatasetGroup();
	virtual ~CDvmDatasetGroup();

//���غ���
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

//˽�г�Ա����
private:
	void CopyChildrenWithDwData(CExBaseList* pSrc, CExBaseList* pDest);

//˽�г�Ա�������ʷ���
public:
	//shaolei 2021-12-04
	void FilterDataExEqualValueStr(CExBaseList &oDestList, const CString &strTagID, const CString &strValue);
	void FilterDataExHasValueStr(CExBaseList &oDestList, const CString &strTagID, const CString &strValue);
	void FilterDataExHasNoValueStr(CExBaseList &oDestList, const CString &strTagID, const CString &strValue);
	void FilterCombineDataEx(CString &strValues, const CString &strTagID, CString &strSeparator);
	
};
