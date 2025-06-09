/**
 *@file
 *\brief 测试流程对象基类
 */
#ifndef TCPEDGEPRCDRBASE_H
#define TCPEDGEPRCDRBASE_H

#include "TcpEdgeGlobalDef.h"
#include "Pkg/TcpEdgePkg.h"
#include "../ProtocolBase/PxPrcdrBase.h"
#include <QMap>

typedef QMap<BYTE*, long> QByteMap;

class CTcpEdgeDevice;
class CTcpEdgeProtocol;
class CTcpEdgePrcdrBase : public QObject, public CPxPrcdrBase
{
	Q_OBJECT
public:
	/** 过程所属IP **/
	CString m_strIP;
	/** 过程所属SOCKET端口 **/
	long m_nPort;
	/** 接收报文中的id值 **/
	CString m_strMid;
	/** 报文数据 **/
	CString m_strASDU;
	/** 报文数据集对象: JSON模式的数据集并不是从模型文件中读取,
	而是从外部传入存放报文的数据集m_pRefDataset才是从文件中读取的 **/
	CDvmDataset* m_pDvmDataset; 
	/** 报文内SetId值 **/
	CString m_strParaSetID;
	/** 报文内JobId值 **/
	CString m_strJobId;
	/** 报文id，每帧报文的唯一个标识，采用范围 0-4294967295 **/
	unsigned long m_ulMid;
	/** 报文协议对象引用 **/
	CTcpEdgeProtocol* m_pTcpProtocolRef;

	CTcpEdgePrcdrBase();
	virtual ~CTcpEdgePrcdrBase();

public:
	/**
	 *@brief 开始执行测试流程
	 *@return 返回非0启动成功
	 */ 
	virtual BOOL Run();
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
	 *@brief 根据数据集获取用户自定义报文
	 *@param[in] pDataset 报文数据集
	 *@return 返回用户自定义报文
	 */ 
	virtual QString GetUserString(CDvmDataset* pDataset);
	/**
	 *@brief 处理接收报文数据
	 *@return 返回非0处理成功
	 */ 
	BOOL ProcessRecvPkgs();
	/**
	 *@brief 详细处理接收报文数据
	 *@param[in] pPkgDetail 报文对象
	 *@return 返回非0处理成功
	 */ 
	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail);
	/**
	 *@brief 完成处理接收报文数据
	 *@param[in] pPkgDetail 报文对象
	 *@return 返回非0结束处理
	 */ 
	virtual BOOL ProcessPackageFinished(CPxPkgBase *pPkgDetail);

	//处理特殊过程的下发报文
	/**
	 *@brief 发送用户自定义报文
	 *@param[in] strPkg 报文
	 *@return 返回非0成功
	 */ 
	BOOL SendUser(QString strPkg);
	/**
	 *@brief 发送报文
	 *@param[in] strPkg 报文
	 *@param[in] strPrcdrID 测试流程ID
	 *@return 返回非0成功
	 */ 
	BOOL Send(QString strPkg, QString strPrcdrID);
	/**
	 *@brief 发送报文
	 *@param[in] pPkg 报文对象
	 *@param[in] strFunName 测试流程名
	 *@param[in] strCot 报文Cot
	 *@param[in] nPort 报文发送端口
	 *@return 返回非0成功
	 */ 
	BOOL Send(CTcpEdgePkg* pPkg, CString strFunName, CString strCot, long nPort = 0);
	/**
	 *@brief 关联报文协议对象
	 *@param[in] pProtocol 报文协议对象
	 */ 
	void SetTcpProtocol(CTcpEdgeProtocol *pProtocol){m_pTcpProtocolRef = pProtocol;}
	/**
	 *@brief 从测试流程ID获取端口号
	 *@param[in] strPrcdrID 测试流程ID
	 */ 
	long GetPortFromPrcdrID(QString strPrcdrID);

private:
	BYTE* Produce(BYTE* pStrASDU, long& nPkgLen, long nContinueID);
	void UpdateDataset(const QString& strID, QString strPkgData);

protected:
	/**
	 *@brief 获取发起测试流程的设备对象
	 *@return 返回设备对象
	 */ 
	CTcpEdgeDevice* GetDevice();
	/**
	 *@brief 发送报文
	 *@param[in] map 报文集合
	 *@param[in] strPrcdrID 测试流程ID
	 *@param[in] nPort 测试端口号
	 *@return 返回非0成功
	 */ 
	BOOL Send(QByteMap map, QString strPrcdrID, long nPort = 0);
	/**
	 *@brief 发送报文
	 *@param[in] pPkg 报文对象
	 *@param[in] strPrcdrID 测试流程ID
	 *@param[in] nPort 测试端口号
	 *@return 返回非0成功
	 */ 
	BOOL Send(CTcpEdgePkg* pPkg, QString strPrcdrID, long nPort = 0);
	/**
	 *@brief 生成报文
	 *@param[in] strPkgData 报文内容
	 *@param[in] map 报文内容分段
	 *@return 返回当前发送的报文Byte
	 */ 
	QByteMap Produce(QString strPkgData, QByteMap& map);
	/**
	 *@brief 生成报文
	 *@param[in] pPkg 报文对象
	 *@param[in] map 报文内容分段
	 *@return 返回当前发送的报文Byte
	 */ 
	QByteMap Produce(CTcpEdgePkg* pPkg, QByteMap& map);
	/**
	 *@brief 生成报文头
	 *@param[in] strFunName 测试流程名
	 *@return 返回报文头对象
	 */ 
	CTcpEdgePkgHead* ProduceHead(const CString& strFunName);
	/**
	 *@brief 生成报文头
	 *@param[in] strFunName 测试流程名
	 *@param[in] strCot 报文内Cot
	 *@return 返回报文头对象
	 */ 
	CTcpEdgePkgHead* ProduceHead(const CString& strFunName, const CString& strCot);
	/**
	 *@brief 生成报文内容
	 *@param[in] strPrcdrID 测试流程ID
	 *@return 返回报文内容对象
	 */ 
	CTcpEdgePkgData* ProduceData(const CString& strPrcdrID);
	/**
	 *@brief 生成报文
	 *@param[in] pPkg 报文对象
	 *@return 返回报文
	 */ 
	CString ProduceASDU(CTcpEdgePkg* pPkg);
	/**
	 *@brief 删除非必须空项
	 *@param[in] pJson Json对象
	 *@param[in] pNode 数据集节点
	 */ 
	void DeleteNotMust(CJSON* pJson, CExBaseList* pNode);
	/**
	 *@brief 将数据集数据转换成JSON对象
	 *@param[in] pJson Json对象
	 *@param[in] pData 数据集
	 */ 
	void DatasetToJson(CJSON* pJson, CExBaseList* pData);
	/**
	 *@brief 更新数据集
	 *@param[in] strID 测试流程ID
	 *@param[in] map 报文集合
	 */ 
	void UpdateDataset(const CString& strID, QByteMap map);
	/**
	 *@brief 更新测试过程临时记录
	 *@param[in] pPkg 报文对象
	 */ 
	void UpdateRecord(CTcpEdgePkg* pPkg);

signals:
	/**
	 *@brief 设备消息更新消息(IP,消息体,消息类型)
	 */ 
	void sig_updateViewPkg(QString,QString,long);
};

#endif