//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttDevConfig.h  CSttDevConfig

#pragma once

#include "SttSystemConfigGlobal.h"



class CSttDevConfig : public CExBaseObject
{
public:
	CSttDevConfig();
	virtual ~CSttDevConfig();


	CString  m_strCurSelModel;
	long  m_nSelOffLine;
	long  m_nSelSOE_Test;
	long  m_nSelSteadyOutput;
	long  m_nSetPassword;
	long  m_nOverloadDelay;
	long  m_nDoubleClickEdit;
	CString  m_strAuxIP;
	CString m_strLastFolderPath;
	long  m_nMultiExpList;//�������ʱ,�ڿ�ʼ����ʱ,�Ƿ��Զ�չ����Ŀ�б�
	long  m_nUseSclView;
	long  m_nLogPrint;//20231213 suyang ���Ƿ������ӡ��Ϣ���й��� 0����ӡ
	long m_nFt3_Prim_Code_Value;
	long m_nLockMaps;//20240507 wangtao ����ӳ�䣬��ֵΪ0ʱ������������Զ�����ȱʡͨ��ӳ��
	long m_nSel_Sys_Pata;
	long m_nHasFT3;/// suyang 20240711 ��������ϵͳ�������������Ƿ���ʾ��ֱFT3 0��ʾ 1����ʾ
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTDEVCONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CSttSystemConfigXmlRWKeys::CSttDevConfigKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

