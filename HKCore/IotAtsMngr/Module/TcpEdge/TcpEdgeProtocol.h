/**
 *@file
 *\brief 报文协议串行化对象
 */

#ifndef _TCPEDGEPROTOCOL_H_
#define _TCPEDGEPROTOCOL_H_

#include "TcpEdgePrcdrBase.h"
#include "TcpEdgeProtocolPkgParser.h"
#include "TcpEdgeModelParser.h"
#include "TcpEdgeEngineThread.h"
#include "Pkg/TcpEdgePkg.h"
#include "../../../Module/DataMngr/DvmDevice.h"

#include <QMutex>

class CTcpEdgeDevice;
class CTcpEdgeProtocol : public QObject, public CExBaseList
{
	Q_OBJECT
public:
	/** 过程绑定的设备 **/
	CTcpEdgeDevice* m_pDevice;
	/** 数据模型 **/
	CDvmDevice *m_pDvmDevice;

	/** 接收报文总表 **/
	CExBaseList m_listRecvPkg;
	/** 接收报文读写锁 **/
	QMutex m_oRecvPkgLocker;
	/** 发送报文总表 **/
	CExBaseList m_listSendPkg;
	/** 执行过程总表 **/
	CExBaseList m_listPrcdr;
	/** 临时过程链表 **/
	CExBaseList m_listTempPrcdr;
	/** 访问临时过程链表的锁 **/
	QMutex m_oPrcdrTmpCriticSection;

	/** 报文分析器: 报文->对象 **/
	CTcpEdgeProtocolPkgParser m_oParser;
	/** 模型分析器: Model文件->映射表 **/
	CTcpEdgeModelParser m_oModelParser;

	/** 用于记录管理通道未收到心跳回复报文的连续次数 **/
	long m_nMngrHealthRespCount;
	/** 用于记录管理通道未收到心跳回复报文的连续时间 **/
	long m_nMngrHealthTime;
	/** 用于记录业务未收到心跳回复报文的连续次数 **/
	long m_nDataHealthRespCount;
	/** 用于记录业务未收到心跳回复报文的连续时间 **/
	long m_nDataHealthTime;

	/** 协议规定的管理通道端口号 **/
	long m_nMngrPort;
	/** 协议规定的业务通道端口号 **/
	long m_nDataPort;

	/** 设备通讯子线程是否退出 **/
	bool m_bExitEngineThread;
	/** 设备通讯子线程 **/
	CTcpEdgeEngineThread* m_pThread;

public:
	CTcpEdgeProtocol();
	~CTcpEdgeProtocol();

	/**
	 *@brief 根据协议将设备关联至平台
	 *@param[in] pDevice 关联设备对象
	 */
	void AttachDevice(CTcpEdgeDevice* pDevice);
	/**
	 *@brief 根据协议确定管理与业务通道对应的端口号
	 *@param[in] nMngrPort 管理端口
	 *@param[in] nDataPort 业务端口
	 */
	void AttachPort(long nMngrPort, long nDataPort);
	/**
	 *@brief 根据协议解析接收报文
	 *@param[in] nPort 报文端口
	 *@param[in] bytes 报文数据
	 *@return 返回值恒定为0
	 */
	long OnTestMsg(long nPort, QByteArray bytes);
	/**
	 *@brief 根据测试ID创建测试流程
	 *@param[in] strPrcdrID 测试ID
	 *@return 返回测试流程对象
	 */
	CTcpEdgePrcdrBase* CreateProcedure(QString& strPrcdrID);
	/**
	 *@brief 根据测试ID创建用户自定义的测试流程
	 *@param[in] strPrcdrID 测试ID
	 *@return 返回用户自定义的测试流程对象
	 */
	static CTcpEdgePrcdrBase* CreateUserProcedure(QString& strPrcdrID);
	/**
	 *@brief 初始化测试流程
	 *@param[in] strProcedureID 测试ID
	 *@param[in] pListDatas 测试参数
	 *@param[in] pDataset 测试数据集
	 *@param[in] nPort 测试端口(管理/业务)
	 *@return 初始化失败返回值为0,否则为1
	 */
	long RunProcedure(QString& strProcedureID, CExBaseList *pListDatas ,CDvmDataset *pDataset, long nPort = 0);
	/**
	 *@brief 初始化用户自定义的测试流程
	 *@param[in] strPkg 测试报文
	 *@param[in] bIsMngrPort 是否为管理通道报文
	 */
	void RunUserProcedure(QString strPkg, bool bIsMngrPort);
	/**
	 *@brief 根据报文对象更新数据集
	 *@param[in] pData 测试报文对象
	 *@param[in] pBuf 测试报文
	 */
	virtual void UpdateDataset(CTcpEdgePkg* pData, char *pBuf);
	/**
	 *@brief 根据测试ID更新数据集
	 *@param[in] pDataset 测试数据集
	 *@param[in] strID 测试报文ID
	 *@param[in] strPkgData 测试报文
	 *@return 返回更新的数据集数据对象
	 */
	virtual CDvmValue* UpdateDataset(CDvmDataset* pDataset, const CString &strID, QString strPkgData);
	/**
	 *@brief 通用的根据ID自动回复消息
	 *@param[in] pPkgData 测试报文数据对象
	 *@param[in] strPrcdrID 测试报文ID
	 *@param[in] strMid 测试报文中Mid值
	 *@param[in] nPort 测试端口(管理/业务)
	 *@return 返回报文数据
	 */
	CString OnReqSend(CTcpEdgePkgData* pPkgData, const CString& strPrcdrID, const CString& strMid, long nPort = 0);
	/**
	 *@brief 获取模型文件报文处理
	 *@param[in] strFileName 文件名
	 */
	void OnModelFileGet(CString strFileName);
	/**
	 *@brief 更新测试流程链表
	 */
	void UpdatePrcdrList();
	/**
	 *@brief 获取当前未处理的报文
	 *@param[in] oList 未处理报文集合
	 */
	void GetNotProcessedPkgs(CExBaseList &oList);
	/**
	 *@brief 删除失效报文
	 */
	void DeleteUnvalidPkgs();
	/**
	 *@brief 启动报文处理线程
	 */
	void StartEngineThread();
	/**
	 *@brief 关闭报文处理线程
	 */
	void ExitEngineThread();
	/**
	 *@brief 管理通道心跳超时响应
	 */
	void OnMngrTimeOut();
	/**
	 *@brief 业务通道心跳超时响应
	 */
	void OnDataTimeOut();

private:
	CDvmDataset* OnDataSpontReq(CTcpEdgePkg* pData, CString& strID, CString& strPkg);  //数据主动上报
	CDvmDataset* OnModelChange(CTcpEdgePkg* pData, CString& strID, CString& strPkg);  //模型变化报告
	CDvmDataset* OnDevAddReq(CTcpEdgePkg* pData, CString& strID, CString& strPkg);
	CDvmDataset* OnDevUpdate(CTcpEdgePkg* pData, CString& strID, CString& strPkg);    //更新子设备状态
	CDvmDataset* OnHealthReq(CTcpEdgePkg* pData, CString& strID, CString& strPkg);    //边缘网关主动发起心跳请求
	CDvmDataset* OnHealthResp(CTcpEdgePkg* pData, CString& strID, CString& strPkg); 

signals:
	/**
	 *@brief 设备心跳超时消息
	 */
	void sig_timeout();
	/**
	 *@brief 设备消息更新消息(IP,消息体,消息类型)
	 */
	void sig_updatePkg(QString,QString,long);

public slots:
	/**
	 *@brief 退出协议关联子线程的信号槽
	 */
	void slot_exitEngine();
	/**
	 *@brief 设备消息更新的信号槽
	 *@param[in] strIP 设备IP
	 *@param[in] strLog 消息体
	 *@param[in] nType 消息类型
	 */
	void slot_updateViewPkg(QString strIP, QString strLog, long nType);
};

#endif