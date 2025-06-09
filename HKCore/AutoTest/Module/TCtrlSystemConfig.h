#pragma once

/*
	ģ�鹦����ϸ˵����ϵͳ����ģ�飬��ϵͳ����
	����ļ���SystemConfig.xsd��SystemConfig.xml
*/

#include "../../Module/BaseClass/ExBaseObject.h"

class CTCtrlSystemConfig : public CExBaseObject
{
public:
	CTCtrlSystemConfig();
	virtual ~CTCtrlSystemConfig();

public:
	CString m_strDBName;
	CString m_strTaskMngrFile;
	CString m_strWorkSpaceFile;
	
public:
	//��������
	virtual BOOL Init();
	virtual long InitAfterSerialize();
	virtual UINT GetClassID();
	//���л�
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	
	//�༭
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();
	
};