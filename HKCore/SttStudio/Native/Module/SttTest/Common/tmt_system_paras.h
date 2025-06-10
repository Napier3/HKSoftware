#pragma once

#include"../../SttTestBase/SttXmlSerialize.h"

typedef struct tmt_system_paras		// PSU 状态内递变参数
{
	int		m_nOutputMode;	//0-模拟 1-数字   2-数字+模拟
	float	m_fVNom;			//额定值
	float	m_fINom;
	float	m_fFNom;
	float 	m_fStabTime;		//防抖时间
	float	m_fVPrimary[4];		//PT变比
	float	m_fVSecondary[4];
	float	m_fIPrimary[4];		//CT变比
	float	m_fISecondary[4];

	int	m_nIecFormat;		//报文输出格式  0-IEC61850-9-2，1-IEC61850-9-1，2-IEC60044-8(国网)，3-采集器输出(新宁光电)
	//4-弱信号输出，5-采集器输出(许继)，6-采集器输出(国网)，7-IEC60044-8(南瑞)，8-串补采集器输出(中电普瑞)
	int	m_nWSgnMode;		//弱信号输出设置 0-弱信号不输出，1-Va',...Ic'定义为弱信号 原m_nLLOutput
	int	m_n588InPort;		//IEC61588接收口 0-7
	int	m_n588Syn;			//IEC61588同步机制 0-延时请求-响应 1-对等延时
	int	m_nParaMode;		//参数设置选择 0-一次值 1-二次值 与m_bPrimaryPara相反 已用到的地方已经全部掉过来了
	int	m_nPkgOutMode;		//报文输出选择 0-一次值 1-二次值 与m_bPrimaryValue相反 已用到的地方已经全部掉过来了
	int	m_nBCodeMode;		//B码逻辑 0-正逻辑 1-负逻辑
	int	m_nLoopMode;			//光纤连接方式 0-双回 1-单回

	void init()
	{
		m_nOutputMode = 2;
		m_fVNom=57.735;
		m_fINom=1;
		m_fFNom=50.0f;
		m_fStabTime=0;

		for(int nIndex = 0;nIndex<4;nIndex++)
		{
			m_fVPrimary[nIndex] = 110.0f;
			m_fVSecondary[nIndex] = 100.0f;
			m_fIPrimary[nIndex] = 1000.0f;
			m_fISecondary[nIndex] = 1.0f;
			m_nIecFormat = 0;
			m_nWSgnMode = 0;
			m_n588InPort = 0;
			m_n588Syn = 0;
			m_nParaMode = 0;
			m_nPkgOutMode = 1;
			m_nBCodeMode = 0;
			m_nLoopMode = 0;
		}
	}

	tmt_system_paras(){}
	virtual ~tmt_system_paras(){}

	float PkgModePTRate(int nGroup)
	{
		float fPTRate = 1;

		if(m_nParaMode&&(!m_nPkgOutMode))//参数设置为一次值，报文输出为二次值
		{
			fPTRate = m_fVSecondary[nGroup]/(1000*m_fVPrimary[nGroup]);
		}
		else if((!m_nParaMode)&&m_nPkgOutMode)//参数设置为二次值，报文输出为一次值
		{
			fPTRate = 1000*m_fVPrimary[nGroup]/m_fVSecondary[nGroup];
		}

		return fPTRate;
	}

	float PkgModeCTRate(int nGroup)
	{
		float fCTRate = 1;

		if(m_nParaMode&&(!m_nPkgOutMode))//参数设置为一次值，报文输出为二次值
		{
			fCTRate = m_fISecondary[nGroup]/m_fIPrimary[nGroup];
		}
		else if((!m_nParaMode)&&m_nPkgOutMode)//参数设置为二次值，报文输出为一次值
		{
			fCTRate = m_fIPrimary[nGroup]/m_fISecondary[nGroup];
		}

		return fCTRate;
	}
}tmt_SystemParas;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas
///
///
void stt_xml_serialize_write_SystemParas();
void stt_init_paras(tmt_SystemParas *pParas);
void stt_xml_serialize(tmt_SystemParas *pParas, CSttXmlSerializeBase *pXmlSierialize);


