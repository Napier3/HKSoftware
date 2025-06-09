/**
 *@file
 *\brief ���Թ��̶���(��Ȩ��֤)
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
	 *@brief ��ϸ������ձ�������
	 *@param[in] pPkgDetail ���Ķ���
	 *@return ���ط�0����ɹ�
	 */ 	
	virtual BOOL ProcessPackageDetail(CPxPkgBase *pPkgDetail);
	
private:
	virtual BOOL RunProcedure_Auth(CPxPkgBase *pPkgDetail);
	BOOL ProcessAuth(CPxPkgBase *pPkgDetail);
};

#endif