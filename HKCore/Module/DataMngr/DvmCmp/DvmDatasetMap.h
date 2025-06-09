//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DvmDatasetMap.h  CDvmDatasetMap

#pragma once

#include "../DvmDataset.h"


#include "DvmDataMap.h"

class CDvmDatasetMap : public CDvmMapObject
{
public:
	CDvmDatasetMap();
	virtual ~CDvmDatasetMap();

	CString  m_strLdviceMap;
	CString  m_strLdvice;
	BOOL m_bAddMapFindByStand;

//���غ���
public:
	virtual UINT GetClassID() {    return DMPCLASSID_CDVMDATASETMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmDatasetMapKey();     }
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

	virtual CDvmMapObject* CreateNewDvmMap(CExBaseObject *pStand, CExBaseObject *pMap);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CDvmDataMap* FindMapData(const CString &strDataID);
	BOOL FindMapData(const CString &strDataID, CString &strMapID, CString &strMapName);
	
	CDvmDataMap* FindDataByMapID(const CString &strMapID);
	BOOL FindDataByMapID(const CString &strMapID, CString &strDataID, CString &strDataName);

	void TransToMap(CDvmDataset *pDataset);
	void TransFromMap(CDvmDataset *pDataset);
	void ReplaceDvmValueID(CExBaseList *pList, const CString &strSrc, const CString &strDest);

	CDvmDataMap* AddDvmMap(CDvmData *pStand, CDvmData *pDest);
	CString GetDvmCmpID();
	virtual BOOL CanFindDvmMapChild(UINT nClassID);

	virtual void ClearEmptyMap();

protected:
	void TransFromMap(CDvmDataMap *pDataMap, CDvmData *pData);

public:
	void SetDataset_Map(CDvmDataset *pDataset_Map);

	//��ȡMAP����
	virtual void GetAllMaps(CExBaseList &listVarMaps);
	void ClearDatasetMap();

	CString GetDvmCmpPropGridPropertyName();
	void GetMapsCount(long &nFullMapCount, long &nTotalCount);
	BOOL IsAllMaped();
	BOOL HasValidMap();
};

