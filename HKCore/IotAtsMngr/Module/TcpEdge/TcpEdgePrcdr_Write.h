/**
 *@file
 *\brief 测试过程对象(写指令)
 */

#ifndef TCPEDGEPRCDRWRITE_H
#define TCPEDGEPRCDRWRITE_H

#include "TcpEdgePrcdrBase.h"

class CTcpEdgePrcdr_Write : public CTcpEdgePrcdrBase
{

public:
	CTcpEdgePrcdr_Write();
	virtual ~CTcpEdgePrcdr_Write();

private:
	BOOL ProcessCtrlCmd(CPxPkgBase *pPkgDetail);
	BOOL ProduceData_CtrlCmd(CString strCtrlType,CString strDeviceID,CString strCtrlVal,CString strDataRefer);
	BOOL ProcessParaSet(CPxPkgBase *pPkgDetail);

public:
	/**
	 *@brief 停止执行测试流程
	 *@return 返回非0停止成功
	 */ 
	virtual BOOL RunStepNull();
	/**
	 *@brief 执行测试应答
	 *@param[in] pPkgDetail 报文对象
	 *@return 返回非0执行成功
	 */ 
	virtual BOOL ProcessPackageAck(CPxPkgBase *pPkgDetail);
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
	void FailErrorInfo(CPxPkgBase *pPkgDetail, CString strID);
	/**
	 *@brief 获取错误信息
	 *@param[in] strStatus 错误状态
	 *@param[in] strErrorCode 错误代码
	 *@param[in] strNote 错误提示
	 *@param[in] StrPkgID 报文测试ID
	 *@return 返回错误信息
	 */ 
	QString FailErrorInfo(CString strStatus, CString strErrorCode, CString strNote, CString StrPkgID);
	/**
	 *@brief 获取失败信息
	 *@param[in] strStatus 错误状态
	 *@param[in] strErrorCode 错误代码
	 *@param[in] strNote 错误提示
	 *@param[in] StrPkgID 报文测试ID
	 *@return 返回失败信息
	 */ 
	QString ReurnFalseInfo(CString strStatus, CString strErrorCode, CString strNote, CString StrPkgID);
	/**
	 *@brief 获取超出范围信息
	 *@param[in] strStatus 错误状态
	 *@param[in] strErrorCode 错误代码
	 *@param[in] strNote 错误提示
	 *@param[in] StrPkgID 报文测试ID
	 *@return 返回超出范围信息
	 */ 	
	QString RangeOutInfo(CString strStatus, CString strErrorCode, CString strNote, CString StrPkgID);
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