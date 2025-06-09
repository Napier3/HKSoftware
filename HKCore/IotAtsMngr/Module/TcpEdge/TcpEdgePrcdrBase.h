/**
 *@file
 *\brief �������̶������
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
	/** ��������IP **/
	CString m_strIP;
	/** ��������SOCKET�˿� **/
	long m_nPort;
	/** ���ձ����е�idֵ **/
	CString m_strMid;
	/** �������� **/
	CString m_strASDU;
	/** �������ݼ�����: JSONģʽ�����ݼ������Ǵ�ģ���ļ��ж�ȡ,
	���Ǵ��ⲿ�����ű��ĵ����ݼ�m_pRefDataset���Ǵ��ļ��ж�ȡ�� **/
	CDvmDataset* m_pDvmDataset; 
	/** ������SetIdֵ **/
	CString m_strParaSetID;
	/** ������JobIdֵ **/
	CString m_strJobId;
	/** ����id��ÿ֡���ĵ�Ψһ����ʶ�����÷�Χ 0-4294967295 **/
	unsigned long m_ulMid;
	/** ����Э��������� **/
	CTcpEdgeProtocol* m_pTcpProtocolRef;

	CTcpEdgePrcdrBase();
	virtual ~CTcpEdgePrcdrBase();

public:
	/**
	 *@brief ��ʼִ�в�������
	 *@return ���ط�0�����ɹ�
	 */ 
	virtual BOOL Run();
	/**
	 *@brief ִֹͣ�в�������
	 *@return ���ط�0ֹͣ�ɹ�
	 */ 
	virtual BOOL RunStepNull();
	/**
	 *@brief ִ�в�������1
	 *@return ���ط�0ִ�гɹ�
	 */ 
	virtual BOOL RunStep1();
	/**
	 *@brief �������ݼ���ȡ�û��Զ��屨��
	 *@param[in] pDataset �������ݼ�
	 *@return �����û��Զ��屨��
	 */ 
	virtual QString GetUserString(CDvmDataset* pDataset);
	/**
	 *@brief ������ձ�������
	 *@return ���ط�0����ɹ�
	 */ 
	BOOL ProcessRecvPkgs();
	/**
	 *@brief ��ϸ������ձ�������
	 *@param[in] pPkgDetail ���Ķ���
	 *@return ���ط�0����ɹ�
	 */ 
	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail);
	/**
	 *@brief ��ɴ�����ձ�������
	 *@param[in] pPkgDetail ���Ķ���
	 *@return ���ط�0��������
	 */ 
	virtual BOOL ProcessPackageFinished(CPxPkgBase *pPkgDetail);

	//����������̵��·�����
	/**
	 *@brief �����û��Զ��屨��
	 *@param[in] strPkg ����
	 *@return ���ط�0�ɹ�
	 */ 
	BOOL SendUser(QString strPkg);
	/**
	 *@brief ���ͱ���
	 *@param[in] strPkg ����
	 *@param[in] strPrcdrID ��������ID
	 *@return ���ط�0�ɹ�
	 */ 
	BOOL Send(QString strPkg, QString strPrcdrID);
	/**
	 *@brief ���ͱ���
	 *@param[in] pPkg ���Ķ���
	 *@param[in] strFunName ����������
	 *@param[in] strCot ����Cot
	 *@param[in] nPort ���ķ��Ͷ˿�
	 *@return ���ط�0�ɹ�
	 */ 
	BOOL Send(CTcpEdgePkg* pPkg, CString strFunName, CString strCot, long nPort = 0);
	/**
	 *@brief ��������Э�����
	 *@param[in] pProtocol ����Э�����
	 */ 
	void SetTcpProtocol(CTcpEdgeProtocol *pProtocol){m_pTcpProtocolRef = pProtocol;}
	/**
	 *@brief �Ӳ�������ID��ȡ�˿ں�
	 *@param[in] strPrcdrID ��������ID
	 */ 
	long GetPortFromPrcdrID(QString strPrcdrID);

private:
	BYTE* Produce(BYTE* pStrASDU, long& nPkgLen, long nContinueID);
	void UpdateDataset(const QString& strID, QString strPkgData);

protected:
	/**
	 *@brief ��ȡ����������̵��豸����
	 *@return �����豸����
	 */ 
	CTcpEdgeDevice* GetDevice();
	/**
	 *@brief ���ͱ���
	 *@param[in] map ���ļ���
	 *@param[in] strPrcdrID ��������ID
	 *@param[in] nPort ���Զ˿ں�
	 *@return ���ط�0�ɹ�
	 */ 
	BOOL Send(QByteMap map, QString strPrcdrID, long nPort = 0);
	/**
	 *@brief ���ͱ���
	 *@param[in] pPkg ���Ķ���
	 *@param[in] strPrcdrID ��������ID
	 *@param[in] nPort ���Զ˿ں�
	 *@return ���ط�0�ɹ�
	 */ 
	BOOL Send(CTcpEdgePkg* pPkg, QString strPrcdrID, long nPort = 0);
	/**
	 *@brief ���ɱ���
	 *@param[in] strPkgData ��������
	 *@param[in] map �������ݷֶ�
	 *@return ���ص�ǰ���͵ı���Byte
	 */ 
	QByteMap Produce(QString strPkgData, QByteMap& map);
	/**
	 *@brief ���ɱ���
	 *@param[in] pPkg ���Ķ���
	 *@param[in] map �������ݷֶ�
	 *@return ���ص�ǰ���͵ı���Byte
	 */ 
	QByteMap Produce(CTcpEdgePkg* pPkg, QByteMap& map);
	/**
	 *@brief ���ɱ���ͷ
	 *@param[in] strFunName ����������
	 *@return ���ر���ͷ����
	 */ 
	CTcpEdgePkgHead* ProduceHead(const CString& strFunName);
	/**
	 *@brief ���ɱ���ͷ
	 *@param[in] strFunName ����������
	 *@param[in] strCot ������Cot
	 *@return ���ر���ͷ����
	 */ 
	CTcpEdgePkgHead* ProduceHead(const CString& strFunName, const CString& strCot);
	/**
	 *@brief ���ɱ�������
	 *@param[in] strPrcdrID ��������ID
	 *@return ���ر������ݶ���
	 */ 
	CTcpEdgePkgData* ProduceData(const CString& strPrcdrID);
	/**
	 *@brief ���ɱ���
	 *@param[in] pPkg ���Ķ���
	 *@return ���ر���
	 */ 
	CString ProduceASDU(CTcpEdgePkg* pPkg);
	/**
	 *@brief ɾ���Ǳ������
	 *@param[in] pJson Json����
	 *@param[in] pNode ���ݼ��ڵ�
	 */ 
	void DeleteNotMust(CJSON* pJson, CExBaseList* pNode);
	/**
	 *@brief �����ݼ�����ת����JSON����
	 *@param[in] pJson Json����
	 *@param[in] pData ���ݼ�
	 */ 
	void DatasetToJson(CJSON* pJson, CExBaseList* pData);
	/**
	 *@brief �������ݼ�
	 *@param[in] strID ��������ID
	 *@param[in] map ���ļ���
	 */ 
	void UpdateDataset(const CString& strID, QByteMap map);
	/**
	 *@brief ���²��Թ�����ʱ��¼
	 *@param[in] pPkg ���Ķ���
	 */ 
	void UpdateRecord(CTcpEdgePkg* pPkg);

signals:
	/**
	 *@brief �豸��Ϣ������Ϣ(IP,��Ϣ��,��Ϣ����)
	 */ 
	void sig_updateViewPkg(QString,QString,long);
};

#endif