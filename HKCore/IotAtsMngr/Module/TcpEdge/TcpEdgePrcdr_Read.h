/**
 *@file
 *\brief 测试过程对象(读指令)
 */

#ifndef TCPEDGEPRCDRREAD_H
#define TCPEDGEPRCDRREAD_H

#include "TcpEdgePrcdrBase.h"

class CTcpEdgePrcdr_Read : public CTcpEdgePrcdrBase
{
public:
	CTcpEdgePrcdr_Read();
	virtual ~CTcpEdgePrcdr_Read();

public:
	/**
	 *@brief 停止执行测试流程
	 *@return 返回非0停止成功
	 */ 
	virtual BOOL RunStepNull();

	//处理应答报文逻辑
	/**
	 *@brief 详细处理接收报文数据
	 *@param[in] pPkgDetail 报文对象
	 *@return 返回非0处理成功
	 */ 
	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail);
	/**
	 *@brief 更新错误信息
	 *@param[in] pPkgDetail 报文对象
	 *@param[in] strID 数据集ID
	 */ 	
	void UpdateFailErrorInfo(CPxPkgBase *pPkgDetail, CString strID);
	/**
	 *@brief 更新错误信息
	 *@param[in] strNecessityLack 必要参数缺失信息
	 *@param[in] strNecessityErr 必要参数错误信息
	 *@param[in] strRangeOut 超出范围信息
	 *@param[in] strReturnFalse 返回值错误信息
	 *@return 返回超出范围信息
	 */ 	
	void UpdateErrInfo(QString strNecessityLack, QString strNecessityErr, QString strRangeOut, QString strReturnFalse);
};

#endif