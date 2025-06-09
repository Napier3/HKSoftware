//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//GbWzdAutoConfig.h  CGbWzdAutoConfig

#pragma once

#include "GbWzdAutoGlobal.h"


#include "GbWzdAutoTemplate.h"

class CGbWzdAutoConfig : public CExBaseList
{
public:
	CGbWzdAutoConfig();
	virtual ~CGbWzdAutoConfig();


	CString  m_strDvmFile;
	CString  m_strGbxmlFile;
	CString  m_strRel_Path;  //���·��
	CString  m_strAuto;   //�Ƿ�ȫ�Զ�ƴ��ģ�� 1=ȫ�Զ���0=�����ߣ�
	long m_nDICount;      //��������
	long m_nDOCount;      //��������
	long m_nEnaCount;     //ѹ������
	CString m_strBmk_DITest;  //���������ǩ��
	CString m_strBmk_DOTest;  //����������ǩ��

	CExBaseList *m_pScriptLocalLib;

//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CGBWZDAUTOCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CGbXMLKeys::CGbWzdAutoConfigKey();     }
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

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CGbWzdAutoTemplate* AddGbWzdAutoTemplate(const CString &strName, const CString &strID, const CString &strGbxmlFile, long nBinOffset, long nBoutOffset);
	CString GetDvmFile();
	CString GetGbxmlFile();
	long FindTemplateByNameHas(const CString &strName);
};

