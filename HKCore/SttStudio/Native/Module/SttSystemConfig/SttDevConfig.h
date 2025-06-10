//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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
	long  m_nMultiExpList;//多测试项时,在开始测试时,是否自动展开项目列表
	long  m_nUseSclView;
	long  m_nLogPrint;//20231213 suyang 对是否输出打印信息进行管理 0不打印
	long m_nFt3_Prim_Code_Value;
	long m_nLockMaps;//20240507 wangtao 锁定映射，当值为0时，连接网络后自动生成缺省通道映射
	long m_nSel_Sys_Pata;
	long m_nHasFT3;/// suyang 20240711 增加用于系统参数报文类型是否显示柔直FT3 0显示 1不显示
//重载函数
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

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

