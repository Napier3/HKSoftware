//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbWzdAutoTemplate.h  CGbWzdAutoTemplate

#pragma once

#include "GbWzdAutoGlobal.h"
#include "..\..\..\Module\DataMngr\DvmCmp\DvmDatasetMap.h"
#include "..\..\..\Module\DataMngr\DvmCmp\DvmDeviceMap.h"

/*
<template name="K102" id="" gbxml-file="CSD_B_K102.gbxml" bin-offset="0" bout-offset="0" version="" date="" cnt-bin="18" cnt-bout="0">
	<dataset-map name="开入参数" id="bin-paras" map-name="开入参数" map-id="bin-paras" ldevice="CPU" ldevice-map="CPU">
		<data-map name="开入1" id="1.2.3" map-name="开入1" map-id="1.3.3"/>
		<data-map name="开入2" id="1.2.4" map-name="X7-开入2" map-id="1.3.4"/>
	</dataset-map>
	<dataset-map name="开出参数" id="bout-paras" map-name="开出参数" map-id="bout-paras" ldevice="CPU" ldevice-map="CPU">
		<data-map name="开出1" id="1.2.3" map-name="开出1" map-id="1.3.3"/>
		<data-map name="开出2" id="1.2.4" map-name="X7-开出2" map-id="1.3.4"/>
	</dataset-map>
	<dataset-map name="开入" id="dsRelayDin" map-name="开入" map-id="dsRelayDin" ldevice="CPU" ldevice-map="CPU">
		<data-map name="开入1" id="BIN1" map-name="X7-开入1" map-id="X7Bin1"/>
		<data-map name="开入2" id="BIN2" map-name="X7-开入2" map-id="X7Bin2"/>
	</dataset-map>
</template>
*/

#define WZD_AUTO_TEMPLATE_BINPARAS          _T("bin-paras")
#define WZD_AUTO_TEMPLATE_BOUTPARAS       _T("bout-paras")
#define WZD_AUTO_TEMPLATE_DVMDATASET       _T("dvm-dataset")

class CGbWzdAutoTemplate : public CExBaseList
{
public:
	CGbWzdAutoTemplate();
	virtual ~CGbWzdAutoTemplate();

	CString  m_strGbxmlFile;
	long  m_nBinOffset;
	long  m_nBoutOffset;
	CString  m_strVersion;
	CString  m_strDate;
	long  m_nCnt_Bin;
	long  m_nCnt_Bout;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CGBWZDAUTOTEMPLATE;   }
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::CGbWzdAutoTemplateKey();     }
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

protected:
	void InitDvmStand_Dataset(CExBaseList *pDataset);
	void InitDvmMaps_Dataset(CExBaseList *pDataset);
	CDvmDatasetMap* FindDvmDatasetMap(const CString &strDatasetID);

public:
	void InitDvm_Stand(CExBaseList *pDsList, UINT nDatasetClassID);
	void InitDvm_Maps(CExBaseList *pDsList, UINT nDatasetClassID);
	void GetAllMaps(CExBaseList &listVarMaps);
	
};

