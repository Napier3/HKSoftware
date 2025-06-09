//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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


	CString  m_strLd;   //��ֵ����LD��ʵ����
	CString  m_strClass;   //��ֵ�������ݼ�����ȥ�����ֺ�׺
	long  m_nInfoGrpNum;  //��ֵ������
	long  m_nGrp;  //������ֵ����ֵ��������ֵ�����Բ�������������ֵ�Ͷ�����ֵ�ɶ�ֵ������ϢInfoGrp�е�setGrpNum���Ծ�����setGrpNumΪ1ʱ��ʾ���鶨ֵΪ������ֵ����
	CString m_strMd5_Cal;   //����õ���MD5

	pugi::xml_node *m_pNode;
//���غ���
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void SetModifyedFlag(BOOL bFlag);
	void UpdateSettings(CSetsFileXml_Settings *pSrcSettings);
	void AppendByModify(CSetsFileXml_Settings *pModifySettings);

//���Ա������ʷ���
public:
	CSetsFileXml_InfoGrp* FindInforGrpByDesc(const CString &strDesc);
	void ParseToDvm(CDvmLogicDevice *pLDevice);
	//����ֵ���ݣ�ƴ�ӳ�һ�����ַ������أ����ڼ���Md5ֵ
	void GetValStringTotal(CString &strValTotal, BOOL bReCalMd5=FALSE);
	void GetValStringTotal_V110(CString &strValTotal, BOOL bReCalMd5);
	void GetValStringTotal_V110_Single(CString &strValTotal); //������ֵ����ȡ��ֵ���ݵĴ��ı�
	void GetValStringToTal_V110_Multi(CString &strValTotal, long nGrp); //������ֵ����ȡָ����ֵ���Ķ�ֵ���ݵĴ��ı�
	char* GetValStringToTal_V110_Multi(long nGrp); //������ֵ����ȡָ����ֵ���Ķ�ֵ���ݵĴ��ı�

	void GetMd5_ForCal(CString &strMd5, const CString &strValTotal, BOOL bReCalMd5);
	long GetSetGrpNum();//��ȡ��ֵ��������
	BOOL IsModifyed_Grp(long nGrp); //ָ����ֵ������ֵ�����Ƿ񱻱༭

	long CmpDataset(CDvmDataset *pDataset, long nGrp, char**ppszRet);
	long CmpDatasets(CDvmDevice *pDvmDevice, CString &strErrorInfo);
	long CmpSetsFile(CSetFilesXml_DSC *pDscUp, CString &strErrorInfo);
	long CmpSetsFile(CSetsFileXml_Settings *pSettings, long nGrp, CString &strErrorInfo);
	CDvmData* FindData(CDvmDataset *pDataset, const CString &strName, const CString &strDataType
		, const CString &strLD, const CString &strRef);
	CString GetDataTypeMap(const CString &strDataType);  //��ֵ�ļ��к�ģ���ļ��е��������͵Ķ��岻һ�£���ת����
	CString GetDataType(CDvmData *pData);
	BOOL IsEqualValue(const CString &strSIVal, const CString &strSIUnit, const CString &strStep
		, CDvmData *pData, CString &strNewValue, const CString &strSIDataType);
	CString GetValDealStep(const CString &strStep, const CString &strValue);
};

