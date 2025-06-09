//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DvmDevice.h  CDvmDevice

#pragma once

#include "DataMngrGlobal.h"
#include "DvmLogicDevice.h"
#include "DvmCmp/DvmCmpKeyDataTypes.h"

#define  DEVICE_type          _T("type")
#define  DEVICE_manufacturer  _T("manufacturer")
#define  DEVICE_desc          _T("desc")

//2023-4-21  lijunqing ����Data���ݶ����formart���Ե�ʹ��ģʽ
//0=����ģʽ��Ĭ�ϣ�1=��ʽģʽ�����ڸ�����ֵ���м��㣬����   V*120/32767
#define DVM_FORMART_USE_MODE_VAL    0
#define DVM_FORMART_USE_MODE_EXPR    1
#define DVM_FORMART_USE_MODE_ID_VAL    _T("value")
#define DVM_FORMART_USE_MODE_ID_EXPR  _T("expression")

#define DVM_FORMART_USE_MODE_KEY _T("format-mode")

class CDvmDevice : public CExBaseList
{
//��ģ�ͣ�ģ�Ͳ�һ��ʱ���ҡ�ƥ����
protected:
	static CDvmCmpKeyDataTypes *g_pDvmCmpKeyDataTypes;
	static long g_nDvmCmpKeyDataTypesRef;

	static void CreateDvmCmpKeyDataTypes();
	static void ReleaseDvmCmpKeyDataTypes();

public:
	CDvmDevice();
	virtual ~CDvmDevice();

	CDvmDataset *m_pDeviceAttr;
	BOOL m_bModifiedFlag;

	//2023-4-21  lijunqing ����Data���ݶ����formart���Ե�ʹ��ģʽ
	//0=����ģʽ��Ĭ�ϣ�1=��ʽģʽ�����ڸ�����ֵ���м��㣬����   V*120/32767
	long m_nFormatUseMode;  
//���غ���
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDVMDEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmDeviceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long Serialize(CBinarySerialBuffer &oBinaryBuffer);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

	BOOL IsFormatUseMode_Val()	{	return m_nFormatUseMode == DVM_FORMART_USE_MODE_VAL;		}
	BOOL IsFormatUseMode_Expr()	{	return m_nFormatUseMode == DVM_FORMART_USE_MODE_EXPR;		}

	void InitFormatUseMode();
	void InitFormatUseMode(const CString &strValue);
//˽�г�Ա����
private:
	void FreeAttrs();

//˽�г�Ա�������ʷ���
public:
	CDvmData* GetAttr(const CString &strAttrID);
	BOOL GetDeviceAttribute(const CString &strAttrTag, CString &strAttrValue);
	BOOL SetDeviceAttribute(const CString &strAttrTag, const CString &strAttrValue);

	CDvmLogicDevice* AddNewLogicDevice(CDvmLogicDevice *pSrc = NULL);
	CDvmLogicDevice* FindByIndex(long nIndex);
	CDvmLogicDevice* FindByIDHas(const CString &strIdHas);
	CDvmDataset* GetDeviceAttrs();
	long GetIndex()	{	return CString_To_long(m_strID);	}

//2020-6-18  lijunqing  ����ͨ�õĹ���
public:
	CDvmDataset* FindDataset(const CString &strDatasetID);
	CDvmDataset* FindDatasetByPath(const CString &strDatasetIDPath);  //2022-11-21 lijunqing
	long GetDatasetList(const CString &strKey, CExBaseList &oListDataset);  //��ȡ���ݼ��б�
	long GetDatasetList(CStringArray &strKeyArray, CExBaseList &oListDataset);  //��ȡ���ݼ��б�

	CDvmDataset* GetDataset(const CString &strLdID, const CString &strDsID, BOOL bCreateNew = TRUE);

	//2023-4-18  lijunqing
	long GetDatasetCount();
public:
	CDvmData* SelectDataObj(const CString &strPath);
	long SelectDataObj(const CString &strPath, CExBaseList &listDatas);
	CDvmData* FindDataObjByID_Has(const CString &strID);
	long FindDataObjByID_Has(const CString &strID, CExBaseList &listDatas);
	long SelectDatas_FilterByPath(const CString &strDatasetPath, const CString &strIDPath, CExBaseList &oListDest, const CString &strSeperator=_T("$"));
	long SelectDataObj(const CString &strDatasetPath, const CString &strPath, CExBaseList &listDatas);

	CDvmData* FindDataObjByID(const CString &strID);
	CDvmData* FindDataObjByID(const CString &strCpuID, const CString &strDsID, const CString &strDataID);
	long FindDataObjByID(const CString &strID, CExBaseList &listDatas);
	CDvmDataset* SelectDatasetByKey(const CString &strIDPath);

#ifndef _PSX_IDE_QT_
	//add by masj 2022-06-08
	void FindDatasetEX(const CString &strDatasetID,  CList<CDvmDataset*>& _list);
#endif
};

void dvm_SetModifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);

#ifndef _PSX_IDE_QT_
BOOL ats_GetDeviceModeleFiles(CString &strDeviceFile, CWnd *pParent, const CString &strCaption=_T(""));
#endif

long dvm_GetLdIndex(const CString &strLdevice);
CDvmLogicDevice* dvm_FindByLdIndex(CDvmDevice *pDevice, long nLdIndex);
