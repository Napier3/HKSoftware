/**
 *@file
 *\brief 测试过程对象(鉴权认证)
 */

#ifndef TCPEDGEPRCDRAUTH_H
#define TCPEDGEPRCDRAUTH_H

#include "TcpEdgePrcdrBase.h"

class CTcpEdgePrcdr_Auth : public CTcpEdgePrcdrBase
{
public:
	long nAuthCount;
	CTcpEdgePrcdr_Auth();
	virtual ~CTcpEdgePrcdr_Auth();

public:
	/**
	 *@brief 停止执行测试流程
	 *@return 返回非0停止成功
	 */ 	
	virtual BOOL RunStepNull();
	/**
	 *@brief 执行测试流程1
	 *@return 返回非0执行成功
	 */ 
	virtual BOOL RunStep1();
	/**
	 *@brief 详细处理接收报文数据
	 *@param[in] pPkgDetail 报文对象
	 *@return 返回非0处理成功
	 */ 	
	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail);
	
private:
	virtual BOOL RunProcedure_Auth(CPxPkgBase *pPkgDetail);
	BOOL ProcessAuth(CPxPkgBase *pPkgDetail);
};

#endif