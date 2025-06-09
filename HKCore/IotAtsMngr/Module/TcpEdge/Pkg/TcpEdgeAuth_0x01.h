//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TcpEdgeAuth_0x01.h  CTcpEdgeAuth_0x01

#pragma once
#include "TcpEdgePkgBase.h"


class CTcpEdgeAuth_0x01: public CTcpEdgePkgBase
{
public:
	CTcpEdgeAuth_0x01();
	virtual ~CTcpEdgeAuth_0x01();


//重载函数
public:

protected:
	CString m_strTcpEdgeName;
	CString m_strRandNum;
	CString m_strSignature;


//私有成员变量
private:

//私有成员变量访问方法
public:
	CString ParseAuthASDUPkg(BYTE *pByte);

	CString GetTcpEdgeName()  {  return m_strTcpEdgeName;  }
	CString GetRandNum()      {  return m_strRandNum;      }
	CString GetSignature()    {  return m_strSignature;    }
//属性变量访问方法
public:
};

