/**
 *@file
 *\brief ����Э�鴮�л�����
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
	/** ���̰󶨵��豸 **/
	CTcpEdgeDevice* m_pDevice;
	/** ����ģ�� **/
	CDvmDevice *m_pDvmDevice;

	/** ���ձ����ܱ� **/
	CExBaseList m_listRecvPkg;
	/** ���ձ��Ķ�д�� **/
	QMutex m_oRecvPkgLocker;
	/** ���ͱ����ܱ� **/
	CExBaseList m_listSendPkg;
	/** ִ�й����ܱ� **/
	CExBaseList m_listPrcdr;
	/** ��ʱ�������� **/
	CExBaseList m_listTempPrcdr;
	/** ������ʱ����������� **/
	QMutex m_oPrcdrTmpCriticSection;

	/** ���ķ�����: ����->���� **/
	CTcpEdgeProtocolPkgParser m_oParser;
	/** ģ�ͷ�����: Model�ļ�->ӳ��� **/
	CTcpEdgeModelParser m_oModelParser;

	/** ���ڼ�¼����ͨ��δ�յ������ظ����ĵ��������� **/
	long m_nMngrHealthRespCount;
	/** ���ڼ�¼����ͨ��δ�յ������ظ����ĵ�����ʱ�� **/
	long m_nMngrHealthTime;
	/** ���ڼ�¼ҵ��δ�յ������ظ����ĵ��������� **/
	long m_nDataHealthRespCount;
	/** ���ڼ�¼ҵ��δ�յ������ظ����ĵ�����ʱ�� **/
	long m_nDataHealthTime;

	/** Э��涨�Ĺ���ͨ���˿ں� **/
	long m_nMngrPort;
	/** Э��涨��ҵ��ͨ���˿ں� **/
	long m_nDataPort;

	/** �豸ͨѶ���߳��Ƿ��˳� **/
	bool m_bExitEngineThread;
	/** �豸ͨѶ���߳� **/
	CTcpEdgeEngineThread* m_pThread;

public:
	CTcpEdgeProtocol();
	~CTcpEdgeProtocol();

	/**
	 *@brief ����Э�齫�豸������ƽ̨
	 *@param[in] pDevice �����豸����
	 */
	void AttachDevice(CTcpEdgeDevice* pDevice);
	/**
	 *@brief ����Э��ȷ��������ҵ��ͨ����Ӧ�Ķ˿ں�
	 *@param[in] nMngrPort ����˿�
	 *@param[in] nDataPort ҵ��˿�
	 */
	void AttachPort(long nMngrPort, long nDataPort);
	/**
	 *@brief ����Э��������ձ���
	 *@param[in] nPort ���Ķ˿�
	 *@param[in] bytes ��������
	 *@return ����ֵ�㶨Ϊ0
	 */
	long OnTestMsg(long nPort, QByteArray bytes);
	/**
	 *@brief ���ݲ���ID������������
	 *@param[in] strPrcdrID ����ID
	 *@return ���ز������̶���
	 */
	CTcpEdgePrcdrBase* CreateProcedure(QString& strPrcdrID);
	/**
	 *@brief ���ݲ���ID�����û��Զ���Ĳ�������
	 *@param[in] strPrcdrID ����ID
	 *@return �����û��Զ���Ĳ������̶���
	 */
	static CTcpEdgePrcdrBase* CreateUserProcedure(QString& strPrcdrID);
	/**
	 *@brief ��ʼ����������
	 *@param[in] strProcedureID ����ID
	 *@param[in] pListDatas ���Բ���
	 *@param[in] pDataset �������ݼ�
	 *@param[in] nPort ���Զ˿�(����/ҵ��)
	 *@return ��ʼ��ʧ�ܷ���ֵΪ0,����Ϊ1
	 */
	long RunProcedure(QString& strProcedureID, CExBaseList *pListDatas ,CDvmDataset *pDataset, long nPort = 0);
	/**
	 *@brief ��ʼ���û��Զ���Ĳ�������
	 *@param[in] strPkg ���Ա���
	 *@param[in] bIsMngrPort �Ƿ�Ϊ����ͨ������
	 */
	void RunUserProcedure(QString strPkg, bool bIsMngrPort);
	/**
	 *@brief ���ݱ��Ķ���������ݼ�
	 *@param[in] pData ���Ա��Ķ���
	 *@param[in] pBuf ���Ա���
	 */
	virtual void UpdateDataset(CTcpEdgePkg* pData, char *pBuf);
	/**
	 *@brief ���ݲ���ID�������ݼ�
	 *@param[in] pDataset �������ݼ�
	 *@param[in] strID ���Ա���ID
	 *@param[in] strPkgData ���Ա���
	 *@return ���ظ��µ����ݼ����ݶ���
	 */
	virtual CDvmValue* UpdateDataset(CDvmDataset* pDataset, const CString &strID, QString strPkgData);
	/**
	 *@brief ͨ�õĸ���ID�Զ��ظ���Ϣ
	 *@param[in] pPkgData ���Ա������ݶ���
	 *@param[in] strPrcdrID ���Ա���ID
	 *@param[in] strMid ���Ա�����Midֵ
	 *@param[in] nPort ���Զ˿�(����/ҵ��)
	 *@return ���ر�������
	 */
	CString OnReqSend(CTcpEdgePkgData* pPkgData, const CString& strPrcdrID, const CString& strMid, long nPort = 0);
	/**
	 *@brief ��ȡģ���ļ����Ĵ���
	 *@param[in] strFileName �ļ���
	 */
	void OnModelFileGet(CString strFileName);
	/**
	 *@brief ���²�����������
	 */
	void UpdatePrcdrList();
	/**
	 *@brief ��ȡ��ǰδ����ı���
	 *@param[in] oList δ�����ļ���
	 */
	void GetNotProcessedPkgs(CExBaseList &oList);
	/**
	 *@brief ɾ��ʧЧ����
	 */
	void DeleteUnvalidPkgs();
	/**
	 *@brief �������Ĵ����߳�
	 */
	void StartEngineThread();
	/**
	 *@brief �رձ��Ĵ����߳�
	 */
	void ExitEngineThread();
	/**
	 *@brief ����ͨ��������ʱ��Ӧ
	 */
	void OnMngrTimeOut();
	/**
	 *@brief ҵ��ͨ��������ʱ��Ӧ
	 */
	void OnDataTimeOut();

private:
	CDvmDataset* OnDataSpontReq(CTcpEdgePkg* pData, CString& strID, CString& strPkg);  //���������ϱ�
	CDvmDataset* OnModelChange(CTcpEdgePkg* pData, CString& strID, CString& strPkg);  //ģ�ͱ仯����
	CDvmDataset* OnDevAddReq(CTcpEdgePkg* pData, CString& strID, CString& strPkg);
	CDvmDataset* OnDevUpdate(CTcpEdgePkg* pData, CString& strID, CString& strPkg);    //�������豸״̬
	CDvmDataset* OnHealthReq(CTcpEdgePkg* pData, CString& strID, CString& strPkg);    //��Ե��������������������
	CDvmDataset* OnHealthResp(CTcpEdgePkg* pData, CString& strID, CString& strPkg); 

signals:
	/**
	 *@brief �豸������ʱ��Ϣ
	 */
	void sig_timeout();
	/**
	 *@brief �豸��Ϣ������Ϣ(IP,��Ϣ��,��Ϣ����)
	 */
	void sig_updatePkg(QString,QString,long);

public slots:
	/**
	 *@brief �˳�Э��������̵߳��źŲ�
	 */
	void slot_exitEngine();
	/**
	 *@brief �豸��Ϣ���µ��źŲ�
	 *@param[in] strIP �豸IP
	 *@param[in] strLog ��Ϣ��
	 *@param[in] nType ��Ϣ����
	 */
	void slot_updateViewPkg(QString strIP, QString strLog, long nType);
};

#endif