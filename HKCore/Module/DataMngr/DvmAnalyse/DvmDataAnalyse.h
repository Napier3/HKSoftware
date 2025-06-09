//DvmDataAnalyse.h  CDvmDataAnalyse

#pragma once

#include "..\DataMngr\DvmData.h"
#include "..\..\KeyDb\XMatchObject.h"
#include "..\..\KeyDb\XKeyDB.h"

class CDvmAnalyseQueryInterface
{
public:
	virtual long QueryByKeys(CXKeyMatchRefList *pKeysList, CExBaseList &listAnalyseObj) = 0;
};

class CDvmDataAnalyse : public CExBaseObject
{
public:
	CDvmDataAnalyse();
	virtual ~CDvmDataAnalyse();

	CDvmData *m_pDvmDataRef;
	CXKeyMatchRefList m_listMatchXKeys;	//���ö���ƥ��Ĺؼ���;    //���ݶ�����������Ĺؼ���
	
	CExBaseList m_listAnlyseDestObject; 

	void DvmAnalyse(CDvmData *pDvmData, CXKeyDB *pXKeyDB, CDvmAnalyseQueryInterface *pQuery); 
	CString GetKeys();
	CString GetTemps();

	void DvmQueryFilter(CExBaseList &listTemplate);
protected:

};