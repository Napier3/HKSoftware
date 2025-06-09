#ifndef _TCPEDGEAUTOTESTMNGR_H_
#define _TCPEDGEAUTOTESTMNGR_H_

class CTcpEdgeAutoTestMngr : public QObject
{
	Q_OBJECT

private:
	CTcpEdgeSocket* m_pAutoTestSocket;

public:
	CTcpEdgeAutoTestMngr();
	virtual ~CTcpEdgeAutoTestMngr();

public:

};

#endif