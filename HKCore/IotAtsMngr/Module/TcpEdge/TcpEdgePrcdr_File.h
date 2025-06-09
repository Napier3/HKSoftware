/**
 *@file
 *\brief 测试过程对象(文件传输指令)
 */

#ifndef TCPEDGEPRCDRFILE_H
#define TCPEDGEPRCDRFILE_H

#include "TcpEdgePrcdrBase.h"

class CTcpEdgePrcdr_File : public CTcpEdgePrcdrBase
{
public:
	CTcpEdgePrcdr_File();
	virtual ~CTcpEdgePrcdr_File();

private:
	BOOL m_bRecAppSetCfgFileResp;   //用于判断是否收到了AppSetCfgFileResp报文
	CString m_strFilePath; //文件路径,包含文件名
	CString m_strFileName; //文件名
	BOOL m_bFileFind;//判断文件是否读取成功

	CString m_strParaSetID;
	CString m_strJobId;
	CString m_strBase64;
	CString m_strCmdId;	//用于记录创建的发送报文ID
	CString m_strContinue; //用于记录创建的发送报文是否有后续
	long m_nFileSegNo;	//用于记录创建的发送报文的序号
	CString m_strRecvCrc32;//用于记录接受到的FileGetResp中的CRC32

	long m_nFileGetType;//召唤文件的类型 0-普通,1-模型,2-拓扑,3-报文

	long m_nMaxFileSize;
	long m_nCurFileSize;

private:
	//推送、获取文件功能
	long GetFileSize(const CString& strFilePath);
	BOOL Base64ToFile(const CString& strFilePath, long& nFileLength);
	CString FileToBase64(const CString& strFilePath);

	BOOL ProcessFileGet(CPxPkgBase *pPkgDetail);
	BOOL ProcessFileGetResp(CPxPkgBase *pPkgDetail);
	BOOL ProduceData_FileGetResp(CPxPkgBase *pPkgDetail);
	BOOL ProduceData_FileGet();
	BOOL ProduceData_FileTransResp(const CString& strCmdId, const CString& strFileSegNo,
		CString strStatus, CString strErrorCode, CString strNote);
	BOOL ProduceData_FileTransReq();

	//BOOL ProcessFileSend(CPxPkgBase *pPkgDetail);
	//BOOL ProduceData_FileSend(SOCKET hSocket);

	CString GetValueFromDataset(const CString& strDataID);
	CString CRC32(CString strFilePath, long nFileLength);

	//过程中Dataset处理
	void CreateDataset(CTcpEdgePkgHead* pHead);

private:
	BOOL ProcessDeviceGetLogReq(CPxPkgBase *pPkgDetail);
	BOOL ProcessContGetLogReq(CPxPkgBase *pPkgDetail);
	BOOL ProcessAppGetLogReq(CPxPkgBase *pPkgDetail);
	
	BOOL ProcessAppGetCfgFileReq(CPxPkgBase *pPkgDetail);
	//BOOL ProcessAppSetCfgFileReq(CPxPkgBase *pPkgDetail);

	BOOL ProcessDeviceUpdateStatusReq(CPxPkgBase *pPkgDetail);

	BOOL ProcessAppInstallStateReq(CPxPkgBase *pPkgDetail);

public:
	/**
	 *@brief 停止执行测试流程
	 *@return 返回非0停止成功
	 */ 
	virtual BOOL RunStepNull();
	/**
	 *@brief 详细处理接收报文数据
	 *@param[in] pPkgDetail 报文对象
	 *@return 返回非0处理成功
	 */ 
	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail);
	/**
	 *@brief 设置文件传输类型
	 *@param[in] strID 传输类型(FileModelGet/FileTopoGet/FileMessageGet)
	 */ 
	void SetFileGetType(const QString& strID);
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