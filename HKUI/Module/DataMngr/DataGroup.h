//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DataGroup.h  CDataGroup

#pragma once

#include "DataMngrGlobal.h"

//2021-1-17  lijunqing  基本没有使用场合，注释掉
//#include "LongDatas.h"
#include "ShortDatas.h"
#include "DvmData.h"

class CDataGroup : public CExBaseList
{
public:
	CDataGroup();
	virtual ~CDataGroup();


	CString m_strDataType; 
	CString m_strValue;

//重载函数
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CDATAGROUP;   }
	virtual BSTR GetXmlElementKey()  {      return CDataMngrXmlRWKeys::CDataGroupKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual BOOL UpdateChildren(CBaseObject* pDest)	;   //shaolei 2022-1-6

//私有成员变量
private:

protected:
	virtual void ResetParas(CDataGroup *pGroup);
	virtual void SelectAllGroups(CExBaseList &listDataGroup, CShortData *pData);

//私有成员变量访问方法
public:
	virtual void SelectAllDatas(CExBaseList &listDatas, BOOL bAddGroup=TRUE, BOOL bValidID=FALSE);
	virtual void SelectAllGroups(CExBaseList &listDataGroup, const CString &strDataType);
	virtual void OnSetParaValue(CShortData *pPara, CExBaseList &listNew, CExBaseList &listDelete);
	virtual void ResetParas();
	virtual BOOL SetPara(const CString &strIDPath, const CString &strValue, CExBaseList &listNew, CExBaseList &listDelete);
	virtual CShortData* FindDataByIDPath(const CString &strIDPath);
	virtual BOOL UpdateOwn(CBaseObject* pDest);//zhouhj 20221027 增加用于更新当前值

	virtual void SetGroupCount(const CString &strDataType, long nGroupCount, CExBaseList &listNew, CExBaseList &listDelete);
	void ResetDatas(CExBaseList &listDatas);
	void ResetDatas();   //2021-8-15  lijunqing

	void GetDataIDPath(CString &strPath, CExBaseObject *pPara);
	CString GetDataIDPath(CExBaseObject *pPara);
	void StringSerialize(CStringSerializeBuffer &oBinaryBuffer);
	virtual void Parser(CEquationBuffer *pEquation);

	CDvmData* AddNewData(const CString &strName, const CString &strID, const CString &strDataType, const CString &strValue
		, const CString &strUnit=_T(""), const CString &strMin=_T(""), const CString &strMax=_T(""), const CString &strStep=_T(""));
	CDvmData* AddNewData(const CString &strID, const CString &strValue);
	//2021-9-5 lijunqing 简单新建Data函数
	CDvmData* AddNewData(const CString &strID,float fValue);
	CDvmData* AddNewData(const CString &strID,long nValue);
	CDvmData* AddNewData(const CString &strID,double fValue);

	//2020-10-03
	CDataGroup* FindByDataType(const CString &strDataType);
	CDataGroup* FindByDataType(const CString &strDataType, long nFindIndex);
	long FindByDataType(const CString &strDataType, CExBaseList &oList);
	CDataGroup* AddNewGroup(const CString &strName, const CString &strID, const CString &strDataType, BOOL bInitNameAndId=TRUE);
	
	//2020-11-23 mym add为了删除data，但只知道datatype的情况下，获取第几个的顺序；
    long FindByDataType_Data(const CString &strDataType, CExBaseList &oList);


	//2020-10-13 lijunqing
	CDvmData* FindDataByValue(const CString &strValue);

	void ShortData_to_DvmData();
	long GetChildCount(UINT nClassID);
	long GetChildCount(const CString &strDataType);
	CExBaseObject* GetChildByIndex(long nIndex, UINT nClassID);  //2024-3-13 lijunqing

	//2020-10-27  lijunqing
	//2022-1-18  shaolei 增加类型判断
	BOOL GetDataValue(const CString &strID, CString &strValue, UINT nClassID = DVMCLASSID_CDVMDATA);
	BOOL GetDataValue(const CString &strID, long &nValue, UINT nClassID = DVMCLASSID_CDVMDATA);
	BOOL GetDataValue(const CString &strID, double &dValue, UINT nClassID = DVMCLASSID_CDVMDATA);//zhouhj 20210828 快速获取浮点值
	BOOL GetDataType(const CString &strID, CString &strDataType, UINT nClassID = DVMCLASSID_CDVMDATA);//dingxy 20240515 快速获取DataType

	//2021-8-2  lijunqing
	void SetDataValue(const CString &strID, const CString &strValue, BOOL bAddNewNotExist = FALSE, UINT nClassID = DVMCLASSID_CDVMDATA);
	void SetDataValue(const CString &strID, long nValue, BOOL bAddNewNotExist = FALSE, UINT nClassID = DVMCLASSID_CDVMDATA);
	void SetDataValue(const CString &strID, double dValue, BOOL bAddNewNotExist = FALSE, UINT nClassID = DVMCLASSID_CDVMDATA);//zhouhj 20220424 快速获取浮点值

	//2021-10-3  lijunqing
	void InitDataValues(CDataGroup *pSrc, BOOL bCloneWhenNotFind);
	void InitDataValues(CDataGroup *pSrc, BOOL bCloneWhenNotFind, BOOL bUseFormatFirst);  //更新参数时，判定format属性不为空，则优先使用format
	void AddDataValuesNotExist(CDataGroup *pSrc);//将pSrc多余的部分，添加到this shaolei 2023-10-24

	void InitNameByID(const CString &strName,const CString &strID);//zhouhj 20220424 通过ID查找,对其name属性进行赋值

	//2022-8-11 lijunqing 根据查询的条件对象，判断当前数据对象是否包含数据，默认使用CDvmData
	BOOL Match(CDataGroup *pQuery); 
////多语言相关
public:
	virtual CString GetXLangID(CExBaseObject *pChildObj);
	virtual void GetXLangID(CExBaseObject *pChildObj, CString &strLangID);

	//生成子对象为DvmData
	BOOL SetDvmDataXml(const CString &strXml);

	//shaolei  2023-4-3 查找ID包含的数据。默认不递归
	long SelectDatas_IDHas(const CString &strIDHas, CExBaseList &oListDatas, BOOL bRecursive=FALSE); 

//2023-12-11 lijunqing
public:
	void AppendValues( CValues *pValues);

	//2024-3-10  lijunqing  基于自动测试Safety扩展数据分类，增加AddNew2兼容CShortDatas
	CValues* GetValues();
	void GetValues(CValues *pValues);
	CShortData* AddNew2(const CString &strName,const CString &strID, const CString &strUnit, const CString &strDataTypeID, const CString &strValue, LONG nReserved,const CString &bstrFormat,const CString &bstrRemark, BOOL bAddSame=TRUE);
	CString GetAttrValue(const CString &strValueID);

};

//2021-5-5  lijunqing 
CDataGroup* dvm_FindDataGroupByValue(CExBaseList &listGroup, const CString &strValue);

//2022-4-13  lijunqing 从SttParas移动到此处，更加方便使用
BOOL stt_GetDataValueByID(CExBaseList *pList, const char* strValueID, CString &strValue);
BOOL stt_GetDataValueByID(CExBaseList *pList, const char* strValueID, long &nValue);
long stt_GetDataValueByID2(CExBaseList *pList, const char* strValueID, long nDefaultValue);
BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, CString &strValue);
BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, long &nValue);
BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, double &dValue);
BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, float &fValue);
BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, short &nValue);//2021-9-1  lijunqing

long stt_SetDataValueByID(CExBaseList *pList, const CString &strValueID, const CString &strValue);
long stt_GetDataValueByID2(CExBaseList *pList, const CString &strValueID, long nDefaultValue);

//2022-9-12  lijunqing
void dvm_SetDvmX_Value(CExBaseObject *pData, long nValue);
void dvm_SetDvmX_Value(CExBaseObject *pData, const CString &strValue);
void dvm_GetDvmX_Value(CExBaseObject *pData, long &nValue);
void dvm_GetDvmX_Value(CExBaseObject *pData, CString &strValue);
long dvm_GetDvmX_Value_long(CExBaseObject *pData);
CString dvm_GetDvmX_Value_string(CExBaseObject *pData);

