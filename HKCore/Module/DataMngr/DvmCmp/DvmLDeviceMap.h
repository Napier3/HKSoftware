//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DvmDatasetMap.h  CDvmLDeviceMap

#pragma once

#include "../DvmDevice.h"


#include "DvmDatasetMap.h"
//m_strName:��׼�ļ�
//m_strMapName:Ŀ���ļ�

class CDvmLDeviceMap : public CDvmMapObject
{
public:
	CDvmLDeviceMap();
	virtual ~CDvmLDeviceMap();

	BOOL m_bDvmLDeviceMapExist;
//���غ���
public:
	virtual UINT GetClassID() {    return DMPCLASSID_CDVMLDVICEMAP;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDvmLDeviceMapKey();     }
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
	BOOL OpenDvmMapFile(const CString &strFile);
	BOOL IsDvmMapFileExist();
	CDvmDatasetMap* FindDsMap(const CString &strLdId, const CString &strDsID);
	CDvmDatasetMap* FindByDsMap(const CString &strLdId, const CString &strDsID);
	CDvmDatasetMap* FindDsMap(const CString &strDsPath);
	CDvmDatasetMap* FindByDsMap(const CString &strDsPath);
	CDvmDatasetMap* FindDsMap(const CString &strLdId, const CString &strDsID, const CString &strLdMapId, const CString &strDsMapID);
	CDvmDataMap* FindDataMap(const CString &strDataPath);
	CDvmDataMap* FindDataMapObj(const CString &strLdID, const CString &strDataPath);
	CDvmDataMap* FindDataMapObj(const CString &strDataPath);
	BOOL FindDataMap(const CString &strDataPath, CString &strDataMapID);

	void TransFromMap(const CString &strLdId, const CString &strDsID, CDvmData *pDvmData);
	void TransToMap(CDvmDataset *pDataset, const CString &strSrcDsID);

	CDvmDatasetMap* AddDvmMap(CDvmDataset *pStand, CDvmDataset *pDest);

	virtual BOOL CanFindDvmMapChild(UINT nClassID);

	CDvmDatasetMap* AddDvmMap(CDvmDatasetMap *pDatasetMap, CDvmDataset *pDest, BOOL bNewStandDataset = FALSE);

};

