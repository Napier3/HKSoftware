//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

	long m_nSetsZone;   //���ļ��н������ĵ�ǰ��ֵ����
	CDvmLogicDevice *m_pLDevice;

	CString m_strMd5_Cal_Parameter;   //�����õ�MD5  ϵͳ���� 
	CString m_strMd5_Cal_Setting;   //�����õ�MD5    ������ֵ
	CString m_strMd5_Cal_Ena;   //�����õ�MD5        ��ѹ��
	CString m_strMd5_Cal_MatrixSet;   //�����õ�MD5  ���ڶ�ֵ

	CString m_strMd5_Cal_VtcParameter;   //�����ò���  �еĶ�ֵ�ļ�û��

	CExBaseList m_oListHashInfoBk; //���ڱ���HashInfo�µ�HI��

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

//���غ���
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

//˽�г�Ա����
private:
	CSetsFileXml_Header *m_pHeader;
	CSetsFileXml_HashInfo *m_pHashInfo;
	CSetsFileXml_DevInfo *m_pDevInfo;
	CSetsFileXml_FileInfo *m_pFileInfo;

	//2024-11-15 yuanting
	CSetsFileXml_Update *m_pUpdateInfo;
	CSetsFileXml_Remark *m_pRemark;

//˽�г�Ա�������ʷ���
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


//���Ա������ʷ���
public:
	void ParseToDvm();
	CSetsFileXml_Settings* FindSettingsByClass(const CString &strClass);
	CSetsFileXml_Settings* FindSettings(const CString &strClass, const CString &strLD);
	void GetSettingsValTotl(CString &strValTotal);
	void GetSettingsValTotal_ByVersion(const CString &strClass, CString &strValTotal, BOOL bReCalMd5);
	void GetSettingsValTotl(const CString &strClass, CString &strValTotal);
	void GetSettingsValTotl_V110(const CString &strClass, CString &strValTotal, BOOL bReCalMd5);
	//���ض�ֵ���ļ��еĹ�ϣֵ
	void GetMd5_FromFile(const CString &strClass, CString &strMd5);
	void GetMd5_FromCal(const CString &strClass, CString &strMd5);

	void ClearUpdateInfo(BOOL bDeleteUpdate=FALSE);  //��װ��ֵ����Ҫ������������Ϣ���㣬ȷ���´���װʱ������������Ϣ��Ϊ����һ�εĸ���
	void ClearHashInfo(BOOL bBk);  //����򱸷�HashInfo
	void AppendHashInfoFromBk();   //�ӱ����л�ԭHashInfo
	void CalSettingsMd5ByModify(); //��װǰ�����ݱ༭�����㶨ֵ��md5�����浽Update��Ϣ��
	void CalSettingsMd5ByModify_Multi(CSetsFileXml_Settings *pSettings);  //������ֵ�����ݱ༭������md5�����浽Update��Ϣ��

	void SetModifyedFlag(BOOL bFlag);
	void UpdateSettings(CSetFilesXml_DSC *pSrcDevice);
	void AppendByModify(CSetFilesXml_DSC *pDeviceModify);//��pDeviceModify�У���ȡ���޸ĵĶ���
	void UpdateHeader();//����ͷ����Ϣ���ļ��޸�ʱ�䡢�ļ���MD5��
	//2024-12-12 yuanting ���ӿ��� �Ƿ����Header�е�Md5 ͬʱ���ؼ����MD5ֵ
	//void CalTotalSettingsMd5();//�����ܵ�MD5ֵ
	CString CalTotalSettingsMd5(bool bIsUpdateHeader = true);//�����ܵ�MD5ֵ
	CString CalTotalSettingsMd5_XmlNode(bool bIsUpdateHeader = true); //ͨ��xml_node����MD5

public:
	long CmpDataset(const CString &strPath, const CString &strFile, const CString &strDsFile, long nGrp, char**ppszRet);
	long CmpDataset(CDvmDataset *pDataset, long nGrp, char**ppszRet);
	long CmpDatasets(const CString &strPath, const CString &strFile, const CString &strDvmFile,char**ppszRet,const CString &strDeviceModel,bool bIsDeviceModel = 0);
	//long CmpDatasets(CDvmDevice *pDvmDevice, char**ppszRet);
	//������Ϣ׷�� ��󷵻�
	long CmpDatasets(CDvmDevice *pDvmDevice, CString& strErrorInfo);
	//2024-12-16 yuanting
	long CmpDatasets(CDvmDevice *pDvmDevice,CString& strErrorInfo, const CString &strDeviceModel,bool bIsDeviceModel = 0);
	long CmpSetsFile(const CString &strPath, const CString &strFileUp, const CString &strFileDown, char**ppszRet);
	//long CmpSetsFile(CSetFilesXml_DSC *pSrcUp, char**ppszRet);
	//������Ϣ׷�� ��󷵻�
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

	//2024-12-12 yuanting  ��֤��ֵ�ļ���ʽ
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


	//��֤�ڵ����ƣ��Ƿ�Ϊ��ǰ�涨������
	long CheckNode(pugi::xml_node oNode,CString strNodeText,CString strParentName,CString& strErrorInfo);
	//��֤�����ԣ��Ƿ�Ϊ��ǰ�涨������
	long CheckAttribute(pugi::xml_attribute xmlAtt,CString strAttText,CString& strNodeName,CString &strDesc,CString& strErrorInfo);

	//��ʼ����������
	void InitAttributeName();
	//��֤�Ƿ��д������������
	long FindAttributeName(pugi::xml_node *pNode,CString& strErrorInfo,CString &strDesc);
	//��֤���������Ƿ�ȱ��
	long AttributeIsLack(pugi::xml_node *pNode,CString& strErrorInfo,CString &strDesc,CString strOtherAttName = "");
	//��֤���ӽڵ��Ƿ��ǷǷ���
	long FindChildNodeName(pugi::xml_node *pNode,CString& strErrorInfo);
	//��֤���ӽڵ� �Ƿ�ȱ��
	long ChildNodeIsLack(pugi::xml_node *pNode,CString& strErrorInfo);


};

