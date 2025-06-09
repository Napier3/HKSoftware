#pragma once

/*
	模块功能详细说明：系统管理模块，即系统配置
	相关文件：SystemConfig.xsd、SystemConfig.xml
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
	//基本方法
	virtual BOOL Init();
	virtual long InitAfterSerialize();
	virtual UINT GetClassID();
	//串行化
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	
	//编辑
	virtual long IsEqual(CExBaseObject* pObj);
	virtual long Copy(CExBaseObject* pDesObj);
	virtual CExBaseObject* Clone();
	
};