//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SetFilesXml_DSC.h  CSetFilesXml_DSC

#pragma once

#include "SetFileXmlParseGlobal.h"


#include "SetsFileXml_Header.h"
#include "SetsFileXml_HashInfo.h"
#include "SetsFileXml_DevInfo.h"
#include "SetsFileXml_FileInfo.h"
#include "SetsFileXml_Settings.h"
#include "SetsFileXml_Remark.h"
#include "..\..\..\..\..\Module\DataMngr\DvmLogicDevice.h"
#include "SetsFileXml_Update.h"
#include "..\..\..\..\..\Module\xml\PugiXML\pugixml.hpp"
#include "..\..\..\..\..\Module\xml\XmlRW_Pugi.h"
#include <map>
#include <list>

class CSetFilesXml_DSC : public CExBaseList
{
public:
	CSetFilesXml_DSC();
	virtual ~CSetFilesXml_DSC();


	CString  m_strConfigVersion;

	long m_nSetsZone;   //从文件中解析到的当前定值区号
	CDvmLogicDevice *m_pLDevice;

	CString m_strMd5_Cal_Parameter;   //计算获得的MD5  系统参数 
	CString m_strMd5_Cal_Setting;   //计算获得的MD5    保护定值
	CString m_strMd5_Cal_Ena;   //计算获得的MD5        软压板
	CString m_strMd5_Cal_MatrixSet;   //计算获得的MD5  出口定值

	CString m_strMd5_Cal_VtcParameter;   //免配置参数  有的定值文件没有

	CExBaseList m_oListHashInfoBk; //用于备份HashInfo下的HI。

	pugi::xml_node *m_pNodeHashInfoBk; 


	CString m_strFile; //2024-11-29 lijunqing
	CString m_strFileTemp;

	CXmlRWDocBase *m_pRWDoc;
	pugi::xml_node *m_pNode;


	//2024-12-18 yuanting
	CString m_strSettingFilePath;
	CString m_strSettingFileName;

	//2024-12-26 yuanting
	//CStringList m_strSIList;
	map<CString,list<CString>>  m_mapAttributeName;

//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSETFILESXML_DSC;   }
	virtual BSTR GetXmlElementKey()  {      return CSetFileXmlParseXmlRWKeys::CSetFilesXml_DSCKey();     }
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

	virtual BOOL OpenXmlFile(const CString &strFile, BSTR bstrElementKey, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);
	virtual BOOL OpenXmlFile(const CString &strFile, CXmlRWKeys *pXmlRWKeys,const long &nXmlRWType = _PUGI_XML_TYPE_);

//私有成员变量
private:
	CSetsFileXml_Header *m_pHeader;
	CSetsFileXml_HashInfo *m_pHashInfo;
	CSetsFileXml_DevInfo *m_pDevInfo;
	CSetsFileXml_FileInfo *m_pFileInfo;

	//2024-11-15 yuanting
	CSetsFileXml_Update *m_pUpdateInfo;
	CSetsFileXml_Remark *m_pRemark;

//私有成员变量访问方法
public:
	CSetsFileXml_Header* GetHeader()	{	return m_pHeader;	}
	void SetHeader(CSetsFileXml_Header* pHeader)	{	m_pHeader = pHeader;	}
	CSetsFileXml_HashInfo* GetHashInfo()	{	return m_pHashInfo;	}
	void SetHashInfo(CSetsFileXml_HashInfo* pHashInfo)	{	m_pHashInfo = pHashInfo;	}
	CSetsFileXml_DevInfo* GetDevInfo()	{	return m_pDevInfo;	}
	void SetDevInfo(CSetsFileXml_DevInfo* pDevInfo)	{	m_pDevInfo = pDevInfo;	}
	CSetsFileXml_FileInfo* GetFileInfo()	{	return m_pFileInfo;	}
	void SetFileInfo(CSetsFileXml_FileInfo* pFileInfo)	{	m_pFileInfo = pFileInfo;	}

	CSetsFileXml_Update* GetUpdateInfo()	{	return m_pUpdateInfo;	}
	void SetUpdateInfo(CSetsFileXml_Update* pUpdateInfo)	{	m_pUpdateInfo = pUpdateInfo;	}
	CSetsFileXml_Remark* GetRemark()	{	return m_pRemark;	}
	void SetRemark(CSetsFileXml_Remark* pRemark)	{	m_pRemark = pRemark;	}


//属性变量访问方法
public:
	void ParseToDvm();
	CSetsFileXml_Settings* FindSettingsByClass(const CString &strClass);
	CSetsFileXml_Settings* FindSettings(const CString &strClass, const CString &strLD);
	void GetSettingsValTotl(CString &strValTotal);
	void GetSettingsValTotal_ByVersion(const CString &strClass, CString &strValTotal, BOOL bReCalMd5);
	void GetSettingsValTotl(const CString &strClass, CString &strValTotal);
	void GetSettingsValTotl_V110(const CString &strClass, CString &strValTotal, BOOL bReCalMd5);
	//返回定值单文件中的哈希值
	void GetMd5_FromFile(const CString &strClass, CString &strMd5);
	void GetMd5_FromCal(const CString &strClass, CString &strMd5);

	void ClearUpdateInfo(BOOL bDeleteUpdate=FALSE);  //下装定值后，需要将更新设置信息清零，确保下次下装时，更新设置信息仅为最新一次的更新
	void ClearHashInfo(BOOL bBk);  //清零或备份HashInfo
	void AppendHashInfoFromBk();   //从备份中还原HashInfo
	void CalSettingsMd5ByModify(); //下装前，根据编辑，计算定值的md5，并存到Update信息段
	void CalSettingsMd5ByModify_Multi(CSetsFileXml_Settings *pSettings);  //多区定值，根据编辑，计算md5，并存到Update信息段

	void SetModifyedFlag(BOOL bFlag);
	void UpdateSettings(CSetFilesXml_DSC *pSrcDevice);
	void AppendByModify(CSetFilesXml_DSC *pDeviceModify);//从pDeviceModify中，获取被修改的对象
	void UpdateHeader();//更新头部信息：文件修改时间、文件总MD5码
	//2024-12-12 yuanting 增加控制 是否跟新Header中的Md5 同时返回计算的MD5值
	//void CalTotalSettingsMd5();//计算总的MD5值
	CString CalTotalSettingsMd5(bool bIsUpdateHeader = true);//计算总的MD5值
	CString CalTotalSettingsMd5_XmlNode(bool bIsUpdateHeader = true); //通过xml_node计算MD5

public:
	long CmpDataset(const CString &strPath, const CString &strFile, const CString &strDsFile, long nGrp, char**ppszRet);
	long CmpDataset(CDvmDataset *pDataset, long nGrp, char**ppszRet);
	long CmpDatasets(const CString &strPath, const CString &strFile, const CString &strDvmFile,char**ppszRet,const CString &strDeviceModel,bool bIsDeviceModel = 0);
	//long CmpDatasets(CDvmDevice *pDvmDevice, char**ppszRet);
	//错误信息追加 最后返回
	long CmpDatasets(CDvmDevice *pDvmDevice, CString& strErrorInfo);
	//2024-12-16 yuanting
	long CmpDatasets(CDvmDevice *pDvmDevice,CString& strErrorInfo, const CString &strDeviceModel,bool bIsDeviceModel = 0);
	long CmpSetsFile(const CString &strPath, const CString &strFileUp, const CString &strFileDown, char**ppszRet);
	//long CmpSetsFile(CSetFilesXml_DSC *pSrcUp, char**ppszRet);
	//错误信息追加 最后返回
	long CmpSetsFile(CSetFilesXml_DSC *pSrcUp,  CString& strErrorInfo);
	//2024-12-16 yuanting
	long CmpSetsFile2(CSetFilesXml_DSC *pSrcUp, CString& strErrorInfo);
	long EditSettings(char* strPara, char**ppszRet);
	long SaveSettingsFile(CString &strPath, CString &strFile,char **ppszRet);
	long OpenSettingsFile(CString &strPath, CString &strFile, char **ppszRet);
	long OpenSettingsFile(CString &strFilePath);

	//2024-12-19 yuanrting
	long SaveSettingsFile(CString &strPathName);
	void AddNewUpdate();

	//2024-12-12 yuanting  验证定值文件格式
	long FileFormatCheck(CString& strErrorInfo);
	long CheckDSC(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckHeader(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckHashInfo(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckHI(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckUpdate(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckUI(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckDevInfo(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckDI(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckFileInfo(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckFI(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckSetting(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckInfoGrp(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckSI(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckVal(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckRemark(pugi::xml_node *pNode,CString& strErrorInfo);
	long CheckRI(pugi::xml_node *pNode,CString& strErrorInfo);


	//验证节点名称，是否为当前规定的名称
	long CheckNode(pugi::xml_node oNode,CString strNodeText,CString strParentName,CString& strErrorInfo);
	//验证节属性，是否为当前规定的名称
	long CheckAttribute(pugi::xml_attribute xmlAtt,CString strAttText,CString& strNodeName,CString &strDesc,CString& strErrorInfo);

	//初始化属性名称
	void InitAttributeName();
	//验证是否有错误的属性名称
	long FindAttributeName(pugi::xml_node *pNode,CString& strErrorInfo,CString &strDesc);
	//验证属性名称是否缺少
	long AttributeIsLack(pugi::xml_node *pNode,CString& strErrorInfo,CString &strDesc,CString strOtherAttName = "");
	//验证是子节点是否是非法的
	long FindChildNodeName(pugi::xml_node *pNode,CString& strErrorInfo);
	//验证是子节点 是否缺少
	long ChildNodeIsLack(pugi::xml_node *pNode,CString& strErrorInfo);


};

