//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DsvScript.h  CDsvScript

#pragma once

#include "DsvSequence.h"
#include "../DvmDevice.h"
#include "DsvEliminate.h"
#include "DsvAppearForErr.h"

#define DSVSCRIPT_TYPE_ID_SEQUENCE         _T("sequence")
#define DSVSCRIPT_TYPE_ID_ELEMENT_QUERY    _T("query")

//只分析关联数据集的数据，其他数据不处理
#define DSVSCRIPT_INDS_MODEID_ONLY_DSV_DSDATAS         _T("only-dsv-ds-datas")
//数据集报文只能包含当前数据集的报文
#define DSVSCRIPT_INDS_MODEID_DATAS_ALL_IN_DS          _T("datas-all-in-ds")
#define DSVSCRIPT_INDS_MODEINDEX_ONLY_DSV_DSDATAS         0
#define DSVSCRIPT_INDS_MODEINDEX_DATAS_ALL_IN_DS          1

class CDsvScript : public CDsvSequence
{
public:
	CDsvScript();
	virtual ~CDsvScript();

	//模式：序列验证、检索模式
	CString m_strDsvType;

	//关联数据集，数据集模式：只分析关联数据集的数据；只能包含关联数据集的方式
	CString m_strInDataset;
	CString m_strInDatasetMode;
	long    m_nInDstasetMode;

public:
	CExBaseList *m_pDsvSrc;
	CDvmDataset m_dsDsvAll;
	CExBaseList m_listDsvFinal;
	CExBaseList m_listMore;
	CExBaseList m_listMiss;
	CExBaseList m_listAppearForErr;

	CExBaseList m_listAnyDsvMatch;
//重载函数
public:
	virtual UINT GetClassID() {    return DVMCLASSID_CDSVSCRIPT;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDsvScriptKey();     }
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

	//ReadXml
	virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	
	virtual long SerializeChildren(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL CopyChildren(CBaseObject* pDest)	;

	void InitInDstasetMode();
public:
	CDsvEliminate* GetDsvEliminate();
	CDsvEliminate* GetDsvEliminateRef()	{	return m_pDsvEliminate;	}
	CDsvAppearForErr* GetDsvAppearForErr();

	virtual void EmptyRefDatasets();
	virtual void InitRefDataset(CDvmDevice *pDevice);
	virtual void SetRefDataset(CExBaseList *pDataset);

	virtual BOOL DsValidate(CDvmDataset *pDataset, CValues *pRptValues, BOOL bValidateHead=TRUE);
// 	long FindDsvElementIndex(CExBaseObject *pElement);

private:
	CDsvEliminate *m_pDsvEliminate;  //需要排除的报文
	CDsvAppearForErr *m_pDsvAppearForErr;  //出现即不合格报文
	CExBaseList m_listRefDataset;    //关联的数据集

	void QueryInRefDataset(CDvmDataset *pDsForValidate, CDvmDataset *pDestDataset);
	void QueryInRefDataset(CDvmDataset *pDsForValidate, CDvmDataset *pDestDataset, CExBaseList *pInDataset);

	BOOL InitDsValidateState(CDvmDataset *pDsDataset, CExBaseList *pListMatch, CExBaseList *pListAnyMatch);
	void InitDsValidateState(CDvmDataset *pDsDataset);
	void InitErrrorDsvObjcts(CExBaseList *pListDest);
	
	void InitAnlyElementListMatch(CDvmDataset *pDataset);
	void InitAnlyElementListMatch(CExBaseList *pListDsv, CDvmDataset *pDataset);
	void InitAnlyElementListMatch(CDsvBase *pAnly, CDvmDataset *pDataset, CDvmData *pPrev, CDvmData *pNext);
	void QueryAllElement(CExBaseList *pListDsv, CExBaseList *pListElement);
	void GetAnyElementPrevNextDvmData(CExBaseList *pListDsv, CDsvBase *pAnly, CDvmData **ppPrev, CDvmData **ppNext);

	BOOL DsValidate_Sequence(CDvmDataset *pDataset, CValues *pRptValues, BOOL bValidateHead=TRUE);
	BOOL DsValidate_Query(CDvmDataset *pDataset, CValues *pRptValues, BOOL bValidateHead=TRUE);
	void DsvRemoveEliminageFromMore();
	BOOL ValidateAppearForErr(CDvmDataset *pDataset, CValues *pRptValues);

public:
	void GetDsv_All(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime);
	void GetDsv_All_ByValue(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime, const CString &strValue);
	
	void GetDsv_All_Match(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime);
	void GetDsv_All_More(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime);
	void GetDsv_All_Miss(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime);
	void GetDsv_AppearForErr(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime);
	void GetDsv_Std(CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime);

	void GetDsv_AddData(CDvmData *pDvmData, CString &strText, BOOL bIsDsvTextWithValue, BOOL bIsDsvTextWithUtcTime);
};

