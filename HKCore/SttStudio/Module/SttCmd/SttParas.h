//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttParas.h  CSttParas

#pragma once

#include "SttCmdDefineGlobal.h"

#include "../../../Module/DataMngr/DataGroup.h"
#include "../../../Module/DataMngr/DvmDatasetGroup.h"
#include "../../../Module/DataMngr/DvmDevice.h"

#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
#include "GuideBook/SttReports.h"
#include "SttRptMapDatas.h"
#endif

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
#include "GuideBook/SttGuideBook.h"
#endif

class CSttParas : public CDataGroup
{
public:
	CSttParas();
	virtual ~CSttParas();

	//2021-8-6  lijunqing  
	CString m_strTextParasID;
	//CString m_strTextParas;    //2021-8-17  lijunqing  改为  m_pszTextParas
	char *m_pszTextParas;
	long m_nLenTextParas;

	void FreeTextParasBuf()
	{
		if (m_pszTextParas != NULL)
		{
			delete m_pszTextParas;
			m_pszTextParas = NULL;
		}

		m_nLenTextParas = 0;
	}

//重载函数
public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttParasKey();     }
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
    virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
    virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	bool m_bAttachParas;

//私有成员变量访问方法
public:
	void AttachParas(CDataGroup *pParas);

//属性变量访问方法
public:
// 	BOOL GetDataValueByID(const CString &strValueID, CString &strValue);
// 	BOOL GetDataValueByID(const CString &strValueID, long &nValue);

	CDvmData* AddNewData(const CString &strID, const CString &strValue, BOOL bUseFind=FALSE);
    CDvmData* AddNewData3(const CString &strID, const CString &strDataType, const CString &strValue);
    CDvmData* AddNewData(const CString &strID, long nValue, BOOL bUseFind=FALSE);
	CDvmData* AddNewData(const CString &strName,const CString &strID, long nValue);
	CDvmData* AddNewData(const CString &strName,const CString &strID, __int64 n64Value);

	CDvmData* SetDataAttr(const CString &strID, const CString &strValue);
	CDvmData* SetDataAttr(const CString &strID, long nValue);

    //2020-05
    BOOL GetDataValue(const CString &strID, CString &strValue);
    BOOL GetDataValue(const CString &strID, long &nValue);
    BOOL GetDataValue(const CString &strID, double &dValue);
	BOOL GetDataValue(const CString &strID, __int64 &n64Value);
    CDvmDataset* GetDvmDataset(BOOL bCreateNew=FALSE);
	CDvmDatasetGroup* GetDvmDatasetGroup(BOOL bCreateNew=FALSE);
	CDvmDevice* GetDvmDevice(BOOL bCreateNew=FALSE);		//2023-1-28  lijunqing 增加枚举装置模型的功能

#ifndef STT_CMD_PARAS_NOT_USE_TEST  //2022-10-24  lijunqing
    //lijunqing 2020-0916
    CSttReports* GetSttReports(BOOL bCreateNew=FALSE);
    CSttRptMapDatas* GetSttRptMapDatas(BOOL bCreateNew=FALSE);
#endif

	void AddDatas(CStringArray &astrTypes, long nValue=1);
	void AddContents(const CString &strID, const CString &strText);

#ifdef STT_CMD_PARAS_HAS_GUIDEBOOK
public:
    CSttGuideBook* NewGuideBook();
    void AttatchGuideBook(CSttGuideBook *pGuideBook);
    void AttatchItems(CSttItems *pItems);

	CSttGuideBook* GetGuideBook()	{	return m_pGuideBook;	};
	CSttItems* GetItems()				{	return m_pItems;			};

protected:
    CSttGuideBook *m_pGuideBook;
	CSttItems *m_pItems;   //shaolei  20210724  用于SetItemsReports和QueryItems指令
#endif

public:
	//2022-3-23  lijunqing 曾经考虑使用XFileMngr，但是底层服务使用起来太麻烦，就直接添加此函数
	void SearchFiles(const CString &strPath, long nGetSubDirs, long nGetFiles, const CString &strFileType);
protected:
	long Search(CDataGroup *pParent, const CString &strPath, long nGetSubDirs, long nGetFiles, const CString &strFileType);	

};

class CSttResults : public CSttParas
{
public:
	CSttResults();
	virtual ~CSttResults();

public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTRESULTS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttResultsKey();     }
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

};

class CSttSearchResults : public CSttParas  //zhouhj 20210925 增加搜索点结果
{
public:
	CSttSearchResults();
	virtual ~CSttSearchResults();

public:
	virtual UINT GetClassID() {    return STTCMDCLASSID_CSTTSEARCHRESULTS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttSearchResultsKey();     }
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

};

//2022-4-13  lijunqing 移动到CDataGroup
// BOOL stt_GetDataValueByID(CExBaseList *pList, const char* strValueID, CString &strValue);
// BOOL stt_GetDataValueByID(CExBaseList *pList, const char* strValueID, long &nValue);
// long stt_GetDataValueByID2(CExBaseList *pList, const char* strValueID, long nDefaultValue);
// BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, CString &strValue);
// BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, long &nValue);
// BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, double &dValue);
// BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, float &fValue);
// BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, short &nValue);//2021-9-1  lijunqing
// 
// long stt_SetDataValueByID(CExBaseList *pList, const CString &strValueID, const CString &strValue);
// long stt_GetDataValueByID2(CExBaseList *pList, const CString &strValueID, long nDefaultValue);
