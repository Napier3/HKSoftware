//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmLogicDevice.h  CDvmLogicDevice

#pragma once

#include "DataMngrGlobal.h"


#include "DvmDatasetGroup.h"
#include "RptCtrls.h"
#include "LogCtrls.h"
#include "DvmLogs.h"

class CDvmLogicDevice : public CExBaseList
{
public:
	CDvmLogicDevice();
	virtual ~CDvmLogicDevice();

	long m_nIndex;

	//CDvmDataset *m_pDvmLogControl;

	CRptCtrls *m_pRptCtrls;
	CLogCtrls *m_pLogCtrls;
	CDvmLogs *m_pLogs;  //日志数据

//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDVMLOGICDEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmLogicDeviceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BOOL CanPaste(UINT nClassID);

	virtual void InitAfterRead();
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	
	virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);
	CRptCtrls* GetRptCtrls();
	CLogCtrls* GetLogCtrls();

#ifndef _PSX_IDE_QT_
	//add by masj 2022-06-08
    void FindByIDEX(const CString &strID, CList<CDvmDataset*>& _list);
#endif

//私有成员变量
private:

//私有成员变量访问方法
public:
	CDvmDataset* AddNewDataset(CDvmDataset *pSrc = NULL);
	CDvmDataset* AddNewDataset(const CString &strName, const CString &strID);//zhouhj 20210722增加用于快速添加数据集对象
	CDvmDatasetGroup* AddNewDatasetGroup(CDvmDatasetGroup *pSrc = NULL);
	CDvmDatasetGroup* AddNewDatasetGroup(const CString &strName, const CString &strID);//zhouhj 20210722增加用于快速添加数据集对象
	CDvmDataset* FindByIndex(long nIndex);

	void SetIndex(long nIndex)	{ m_nIndex = nIndex; }
	long GetIndex()				{ return m_nIndex; }
	BOOL HasValueID(const CString &strValueID);
	BOOL SetAttr(const CString &strAttrID, const CString &strValue);

	//xxy 20181127
	CDvmDataset *FindByNameAndClassID(const CString& strName,long nClassID);

	long GetDatasetList(const CString &strKey, CExBaseList &oListDataset);  //获取数据集列表

public:
	CDvmData* FindDataObjByName(const CString &strName);
	CDvmData* FindDataObjByID(const CString &strID);
	long FindDataObjByID(const CString &strID, CExBaseList &listDatas);
	CDvmData* FindDataObjByID_Has(const CString &strID);
	long FindDataObjByID_Has(const CString &strID, CExBaseList &listDatas);

};

CDvmDataset* dvm_FindDataset(CDvmLogicDevice *pLdevice, const CString &strID);
