//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmMapObject.h  CDvmMapObject

#pragma once

#include "../DvmDevice.h"
#include "../../StringCmp/StringCmp.h"


//m_strName、m_strID为标准对象的名称、ID
//m_strMapName、m_strMapID为MAP对象的名称、ID

class CDvmMapObject : public CExBaseList
{
public:
	CDvmMapObject();
	virtual ~CDvmMapObject();


	CString  m_strMapName;
	CString  m_strMapID;
	
	CExBaseObject *m_pStand;
	CExBaseObject *m_pMap;
	
	CStringCmp *m_pStringCmp_Name;
	CStringCmp *m_pStringCmp_ID;
	long       m_nCmpResult;   //对象的不同之处
	DWORD      m_dwItemDataStand;
	DWORD      m_dwItemDataMap;
	long       m_nCmpRate;
	long       m_nCmpErrCount;   //没有匹配或者不完全匹配的数量

//重载函数
public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);

	virtual CDvmMapObject* CreateNewDvmMap(CExBaseObject *pStand, CExBaseObject *pMap);
//私有成员变量
private:

//私有成员变量访问方法
public:
	void StringCmp();
	CStringCmpBlocks* GetNameCmp_Stand();
	CStringCmpBlocks* GetNameCmp_Dest();
	CStringCmpBlocks* GetIDCmp_Stand();
	CStringCmpBlocks* GetIDCmp_Dest();
	void FreeStringCmp();

	virtual void SetMap0(CExBaseObject *pMap);
	virtual void SetStand0(CExBaseObject *pStand);
	virtual void SetMap(CExBaseObject *pStand, CExBaseObject *pMap);
	BOOL IsInChild_Stand(CExBaseObject *pStand);
	BOOL IsInChild_Map(CExBaseObject *pMap);

	CDvmMapObject* FindDvmMap_Stand(CExBaseObject *pStand);
	CDvmMapObject* FindDvmMap_Dest(CExBaseObject *pDest);
	
public:
	virtual void AddNullDvmMap_Stand();
	virtual void SortDvmMap_Stand();

	virtual long FindDvmMapObj_ByStand(UINT nClassID, CExBaseObject *pStand, CExBaseList &listDvmMap, BOOL bFindIdSame = FALSE);
	virtual CDvmMapObject* FindDvmMapObj_ByStand(UINT nClassID, CExBaseObject *pStand);   //shaolei 20210507  根据源数据，查找映射对象
	virtual long FindDvmMapObj_ByMap(UINT nClassID, CExBaseObject *pMap, CExBaseList &listDvmMap);
	virtual CDvmMapObject* FindDvmMapObj_ByMap(UINT nClassID, CExBaseObject *pMap);
	virtual BOOL CanFindDvmMapChild(UINT nClassID);
	
	virtual CDvmMapObject* FindDvmMapObj(CExBaseObject *pStand, CExBaseObject *pMap);
	virtual CDvmMapObject* FindDvmMapObj_ByStandID(const CString &strStandID, CExBaseObject *pMap);

	virtual void DeleteMap();
	virtual BOOL IsMapEmpty();

	CDvmMapObject* FindMapObj(const CString &strID, const CString &strMapID);


	//获取MAP对象
	virtual void GetAllMaps(CExBaseList &listVarMaps);
	BOOL IsMapFull();   //是否完全匹配
	void CountErrMapCount();   //统计不匹配和不完全匹配的数量
	CString GetMapIDByValueID(const CString &strID);
	CDvmMapObject* GetMapByID(const CString &strID);
	CDvmMapObject* GetMapByIDEx(const CString &strID);

};

CDvmMapObject* dvmmap_NewMpObject(CExBaseObject *pStand, CExBaseObject *pMap, long nCmpRate);
CDvmMapObject* dvmmap_GetMpObject(CExBaseObject *pDvmObject);
extern BOOL g_bDvmCmdDataNameFull;