//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetsFileXml_Settings.h  CSetsFileXml_Settings

#pragma once

#include "SetFileXmlParseGlobal.h"


#include "SetsFileXml_InfoGrp.h"
#include "..\..\..\..\..\Module\DataMngr\DvmLogicDevice.h"
#include "..\..\..\..\..\Module\DataMngr\DvmDevice.h"
#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"
class CSetFilesXml_DSC;

class CSetsFileXml_Settings : public CExBaseList
{
public:
	CSetsFileXml_Settings();
	virtual ~CSetsFileXml_Settings();


	CString  m_strLd;   //定值归属LD的实例名
	CString  m_strClass;   //定值所处数据集名称去掉数字后缀
	long  m_nInfoGrpNum;  //定值分组数
	long  m_nGrp;  //多区定值区号值，单区定值该属性不声明（单区定值和多区定值由定值分组信息InfoGrp中的setGrpNum属性决定，setGrpNum为1时表示该组定值为单区定值）。
	CString m_strMd5_Cal;   //计算得到的MD5

	pugi::xml_node *m_pNode;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETSFILEXML_SETTINGS;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetsFileXml_SettingsKey();     }
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

	virtual BSTR GetXml(CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);
	char* GetXml_XmlNode();

//私有成员变量
private:

//私有成员变量访问方法
public:
	void SetModifyedFlag(BOOL bFlag);
	void UpdateSettings(CSetsFileXml_Settings *pSrcSettings);
	void AppendByModify(CSetsFileXml_Settings *pModifySettings);

//属性变量访问方法
public:
	CSetsFileXml_InfoGrp* FindInforGrpByDesc(const CString &strDesc);
	void ParseToDvm(CDvmLogicDevice *pLDevice);
	//将定值数据，拼接成一个大字符串返回，用于计算Md5值
	void GetValStringTotal(CString &strValTotal, BOOL bReCalMd5=FALSE);
	void GetValStringTotal_V110(CString &strValTotal, BOOL bReCalMd5);
	void GetValStringTotal_V110_Single(CString &strValTotal); //单区定值，获取定值数据的大文本
	void GetValStringToTal_V110_Multi(CString &strValTotal, long nGrp); //多区定值，获取指定定值区的定值数据的大文本
	char* GetValStringToTal_V110_Multi(long nGrp); //多区定值，获取指定定值区的定值数据的大文本

	void GetMd5_ForCal(CString &strMd5, const CString &strValTotal, BOOL bReCalMd5);
	long GetSetGrpNum();//获取定值区的数量
	BOOL IsModifyed_Grp(long nGrp); //指定定值区，定值数据是否被编辑

	long CmpDataset(CDvmDataset *pDataset, long nGrp, char**ppszRet);
	long CmpDatasets(CDvmDevice *pDvmDevice, CString &strErrorInfo);
	long CmpSetsFile(CSetFilesXml_DSC *pDscUp, CString &strErrorInfo);
	long CmpSetsFile(CSetsFileXml_Settings *pSettings, long nGrp, CString &strErrorInfo);
	CDvmData* FindData(CDvmDataset *pDataset, const CString &strName, const CString &strDataType
		, const CString &strLD, const CString &strRef);
	CString GetDataTypeMap(const CString &strDataType);  //定值文件中和模型文件中的数据类型的定义不一致，需转换下
	CString GetDataType(CDvmData *pData);
	BOOL IsEqualValue(const CString &strSIVal, const CString &strSIUnit, const CString &strStep
		, CDvmData *pData, CString &strNewValue, const CString &strSIDataType);
	CString GetValDealStep(const CString &strStep, const CString &strValue);
};

