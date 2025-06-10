#pragma once

#include "../KeyDb/XKeyDB.h"
#include "../DataMngr/DvmDevice.h"
#include "../DataMngr/DataGroup.h"
#include "../KeyDb/XMatchList.h"


CDvmData* iec_match_get_dvmdata(CExBaseObject *pObj);

//电压、电流：A相、B相、C相进行分组：子对象为CDvmData
class CXIecDs_Group_U_or_I_ALL : public CDataGroup
{
public:
	CXIecDs_Group_U_or_I_ALL();
	virtual ~CXIecDs_Group_U_or_I_ALL();
	
	//WriteXml
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

};

//电压或者电流，三相分组
class CXIecDs_Group_ABC : public CDataGroup
{
public:
	CXIecDs_Group_ABC();
	virtual ~CXIecDs_Group_ABC();

	CExBaseObject *m_pA;
	CExBaseObject *m_pB;
	CExBaseObject *m_pC;

	CString m_strType;
	long m_nRelationIndex; //矢量图部分，关联的UI配对组编号

	CXKeyMatchRefList m_listMatchXKeys;

	//WriteXml
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	
	
	void InitXKeyMatchRefList(CXKeyMatchRefList &listMatchXKeys, CXKeyMatchRef *pKeyDel);
};

//电压和电流组合的通道分组例如：Ua+Ia；Ub+Ib；Uc+Ic
class CXIecDs_Group_UI : public CDataGroup
{
public:
	CXIecDs_Group_UI();
	virtual ~CXIecDs_Group_UI();
	
	CExBaseObject *m_pU;
	CExBaseObject *m_pI;

	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

};

//电压+电流三相 组合
class CXIecDs_Group_UI_ABC : public CDataGroup
{
public:
	CXIecDs_Group_UI_ABC();
	virtual ~CXIecDs_Group_UI_ABC();

	CXIecDs_Group_UI *m_pUI_A;
	CXIecDs_Group_UI *m_pUI_B;
	CXIecDs_Group_UI *m_pUI_C;

	void InitUI(CXIecDs_Group_ABC *pU, CXIecDs_Group_ABC *pI);
};

class CXIecDatasetSmartMatch : public CDataGroup
{
public:
	CXIecDatasetSmartMatch();
	virtual ~CXIecDatasetSmartMatch();

	void AttachKeyDB(CXKeyDB *pKeyDB)	{	m_pKeyDB = pKeyDB;	}

protected:
	CXKeyDB *m_pKeyDB;
	CDvmDataset *m_pIecDataset;

	CXMatchList m_oXMatchList;//关键字分析

	//按照ABC三相对电压电流进行分组
	CDataGroup *m_pGroupUa;
	CDataGroup *m_pGroupUb;
	CDataGroup *m_pGroupUc;
	CDataGroup *m_pGroupIa;
	CDataGroup *m_pGroupIb;
	CDataGroup *m_pGroupIc;
	
	//三相组  CXIecDs_Group_ABC，用于矢量图、序分量等电压、电流三相组合属性分析
	CDataGroup *m_pGroup_ABC_U_List;
	CDataGroup *m_pGroup_ABC_I_List;

	//三相组  CXIecDs_Group_UI_ABC，用于矢量图、序分量等电压、电流三相组合属性分析
	CDataGroup *m_pGroup_UI_ABC_List;

public:
	CExBaseList m_listUIGroup_ABC;  //CXIecDs_UIGroup_ABC
	CExBaseList m_listUIGroup_UI;    //CXIecDs_UIGroup_UI

public:
	void IecDatasetSmartMatch(CDvmDataset *pDataset);
	CDataGroup* Group_ABC_U_List()	{	return m_pGroup_ABC_U_List;	}
	CDataGroup* Group_ABC_I_List()	{	return m_pGroup_ABC_I_List;	}
	CDataGroup* Group_UI_ABC_List()	{	return m_pGroup_UI_ABC_List;	}

protected:
	void Group_U_I_A_B_C();
	void RemoveKey(const CString &strKey, CExBaseList &listDest);
	void SelectByKey(const CString &strKey, CExBaseList &listDest);
	void RemoveByKey(const CString &strKey, CExBaseList &listDest);
	void SelectByKey(const CString &strKey1, const CString &strKey2, CExBaseList &listDest);
	
	void GroupForABC(CDataGroup *pGroup_ABC, const CString &strType, CDataGroup *pGroupA, CDataGroup *pGroupB, CDataGroup *pGroupC);
	CXMatchObject* GroupForABC_Find(CXMatchObject *pA, CDataGroup *pGroupX, CXKeyMatchRef *pTypeA, CXKeyMatchRef *pTypeX);
	BOOL GroupForABC_Find_Match(CXMatchObject *pA, CXMatchObject *pX, CXKeyMatchRef *pTypeA, CXKeyMatchRef *pTypeX);

	void Group_U_I_ABC(CDataGroup *pGroup_ABC_U, CDataGroup *pGroup_ABC_I);
	void Group_I_U_ABC(CDataGroup *pGroup_ABC_I, CDataGroup *pGroup_ABC_U);
	CXIecDs_Group_ABC* Group_XX_ABC_Find(CXKeyMatchRefList &oXMatchList, CDataGroup *pGroup_ABC_X);
};

