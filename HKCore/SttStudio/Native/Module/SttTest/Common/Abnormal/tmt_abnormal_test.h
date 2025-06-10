#pragma once
#include"../../../SttTestBase/SttXmlSerialize.h"

#define SMV_ABNORMAL_TYPE_NULL                                0  //û���쳣
#define SMV_ABNORMAL_TYPE_FrameDrop                           1  //��֡
#define SMV_ABNORMAL_TYPE_FrampShaking                        2  //����
#define SMV_ABNORMAL_TYPE_FlyPoint                            3  //�ɵ�
#define SMV_ABNORMAL_TYPE_OutOfOrder                          4  //����
#define SMV_ABNORMAL_TYPE_DelayDeviation                      5  //��ʱƫ��
#define SMV_ABNORMAL_TYPE_DelayChange                         6  //��ʱ�仯
#define SMV_ABNORMAL_TYPE_SeqNumDevt                          7  //���ƫ��
#define SMV_ABNORMAL_TYPE_QualitySet                          8  //Ʒ���쳣



typedef struct tmt_smv_abnormal_msg		//9-2���ò���
{
	char     m_strMacAddrDst[MAX_PATH];	//Ŀ�ĵ�ַ/
	char     m_strMacAddrSrc[MAX_PATH];	//Դ��ַ/
	int	     m_nAppID;				//APPIDת��Ϊ���ƣ�����GetDataFromHex/
	int	     m_nVLanID;          //
	int	     m_nVLanPriority;         //
//	int      m_nPort;		//�����ѡ��m_nPNFSendMode0 Ĭ��Ϊ	m_nSendMode/
	int      m_nVersion;		//SMV�汾��/
//	int		 m_nSmpDelay;			//������ʱm_nDelayTime0/
	int		 m_nSyn;					//ͬ����ʽ0-δͬ��1-����ͬ��2-ȫվͬ����SmpSynch Ŀǰֻ��Ĭ��ֵΪ	m_nSynMode/
	char	 m_strSVID[MAX_PATH];	//m_strSVID0/
	char	 m_strDataset[MAX_PATH];	//���ݼ�m_strDatSet0/
	int      m_nNetType;
	int      m_nUseOrigPkgSet;//ʹ��ԭʼ�������� Ϊ0ʱ������ԭʼ����

	void init()
	{
		memset(m_strMacAddrDst,0, MAX_PATH);
		memset(m_strMacAddrSrc,0, MAX_PATH);
		memset(m_strSVID,0, MAX_PATH);
		memset(m_strDataset,0, MAX_PATH);
		m_nAppID = 0;
		m_nVLanID = 0;
		m_nVLanPriority = 0;
//		m_nPort = 0;
		m_nVersion = 0;
//		m_nSmpDelay = 0;
		m_nSyn = 1;
		m_nNetType = 0x88ba;
		m_nUseOrigPkgSet = 0;
	}

	tmt_smv_abnormal_msg()
	{

	}
	virtual ~tmt_smv_abnormal_msg()
	{
	}
}tmt_SmvAbnormalMsg;

// typedef struct tmt_smv_quality_set
// {
// 	int m_nValid;       //bit0-1: 00-��, 01-��Ч, 10-������11-����
// 	int m_nOverflow;    //�����  ���
// 	int m_nOutRange;    //����  ��ֵ��
// 	int m_nBadBmVal;    //��������׼ֵ
// 	int m_nJitter;      //�޶���   ����
// 	int m_nFault;       //�޹���  ����
// 	int m_nOldDataOT;   //�޳�ʱ  ���ݳ�ʱ
// 	int m_nInconformity;//һ�� ��һ��
// 	int m_nImprecise;   //��ȷ   ����ȷ
// 	int m_nSrc;         //����   ��ȡ��
// 	int m_nTest;        //����   ����
// 	int m_nOprLock;     //����Ա����
// 
// 	void init()
// 	{
// 		m_nValid = 0;
// 		m_nOverflow = 0;
// 		m_nOutRange = 0;
// 		m_nBadBmVal = 0;
// 		m_nJitter = 0;
// 		m_nFault = 0;
// 		m_nOldDataOT = 0;
// 		m_nInconformity = 0;
// 		m_nImprecise = 0;
// 		m_nSrc = 0;
// 		m_nTest = 0;
// 		m_nOprLock = 0;
// 	}
// 	tmt_smv_quality_set()	{}
// 	virtual ~tmt_smv_quality_set(){}
// }tmt_SmvQualitySet;

typedef struct tmt_state_abnormal_smv		// SMV�쳣����
{
	UINT	m_nGroupIndex;			// �����쳣�ı�����ţ��ӿ�ʼ��ѡ��������ÿ�����hqyIEC61850_9_2_Setting.Control_Block block������(��0��ʼ���)
	UINT	m_nSendMode;		// ���ͷ�ʽ��0-ÿ�ܲ�����1-ÿ�뷢��
	UINT	m_nCircleNum_TypeCircle;		// �����ܲ�����nSendMode = type_circle��Ч
	UINT	m_nCircleNum_TypeSecond;// ÿ�뷢���ܲ���type= type_second��Ч
	UINT	m_nSendTime_TypeSecond;		// ����ʱ��nSendMode= type_second��Ч

	UINT	m_nAbnormalType;			// �쳣���ͣ�-�Ƿ��쳣1-��֡2-����3-�ɵ�4-����5-��ʱƫ��6-��ʱ�仯7-���ƫ��8-Ʒ���쳣
	int	    m_nAbnormalPoint[80];		// 80���쳣ֵ
//	int		m_nLoseStep;			// ʧ���޴˹��ܣ���ʱδ�õ�
	int		m_nQualityBit[12];	// Ʒ��
	UINT	m_nInvalidChanel[80];	// ͨ��ʹ�ܣ���Чͨ��ѡ������
//	UINT	m_nTestmode;			// ����
	UINT	m_nDelayDeviation;		// ��ʱƫ��
	UINT	m_nDelayChangeValue;		// ��ʱ�仯
//	float	m_fDelayTime;			// ��ʱʱ��
	float	m_fFlyPointVolt;		// �ɵ��ѹֵ
	float	m_fFlyPointCurrent;	// �ɵ����ֵ
//	UINT	m_uJitterDirection;	// ��������,Ĭ�������������ϣ��˲�������ѡ
	UINT	m_uFrampShakingValue;			// ����ֵ��λns,��������������ֵͳһ�޸�
	int		m_nOutOfOrderValue;			// ����-80,û�д�����Ϊ
	UINT	m_nSeqNumDevtValue;			// ���ƫ��

	int     m_nVolChEnable[6];//�ɵ��ѹʹ��
	int     m_nCurChEnable[6];//�ɵ����ʹ��
//	tmt_SmvQualitySet   m_oQualitySet;
	tmt_SmvAbnormalMsg  m_oSmvMsg;

	void init()
	{
		m_nGroupIndex = 0;			// �����쳣�ı�����ţ���0��ʼ��ѡ��������ÿ�����hqyIEC61850_9_2_Setting.Control_Block block������
		m_nSendMode = 0;			// ���ͷ�ʽ��-ÿ�ܲ�����1-ÿ�뷢��
		m_nCircleNum_TypeCircle = 1;		// �����ܲ�����nSendMode = type_circle��Ч
		m_nCircleNum_TypeSecond = 1;// ÿ�뷢���ܲ���type= type_second��Ч
		m_nSendTime_TypeSecond = 1;		// ����ʱ��nSendMode= type_second��Ч

		m_nAbnormalType = SMV_ABNORMAL_TYPE_NULL;			// �쳣���ͣ�-�Ƿ��쳣1-��֡2-����3-�ɵ�4-����5-��ʱƫ��6-��ʱ�仯7-���ƫ��

		for (int nIndex=0;nIndex<80;nIndex++)
		{
			m_nAbnormalPoint[nIndex] = 0;
			m_nInvalidChanel[nIndex] = 0;// 80���쳣ֵ��Ʒ��ͨ����ʼ
		}

		for (int nIndex = 0;nIndex<6;nIndex++)
		{
			m_nVolChEnable[nIndex] = 0;
			m_nCurChEnable[nIndex] = 0;
		}

		for (int nIndex = 0;nIndex<12;nIndex++)
		{
			m_nQualityBit[nIndex] = 0;
		}

// 		m_nLoseStep = 0;			// ʧ��????
// 		m_nTestmode = FALSE;			// ����
		m_nDelayDeviation = 0;		// ��ʱƫ��(us)
		m_nDelayChangeValue = 0;		// ��ʱ�仯(us)
//		m_fDelayTime;			// ��ʱʱ��????
		m_fFlyPointVolt = 0;		// �ɵ��ѹֵ
		m_fFlyPointCurrent = 0;	// �ɵ����ֵ
		m_uFrampShakingValue = 10000;		// ����ֵ��λns,��������������ֵͳһ�޸�
		m_nOutOfOrderValue = 0;			// ����-1999 - 20000,û�д�����Ϊ????
		m_nSeqNumDevtValue = 5;			// ���ƫ��
//		m_oQualitySet.init();
		m_oSmvMsg.init();
	}

	tmt_state_abnormal_smv()	{	init();	}
	virtual ~tmt_state_abnormal_smv(){}
}tmt_StateAbnormalSMV;

typedef struct tmt_state_abnormal_goose		// GOOSE�쳣����
{
	int		m_nGroupIndex;	//��Ŵ�0��ʼ
	BOOL    m_bSrcMac_Sel;
	char	m_strSrcMac[MAX_PATH];
	BOOL    m_bDestMac_Sel;
	char	m_strDestMac[MAX_PATH];
	BOOL    m_bGocbRef_Sel;
	char	m_strGocbRef[MAX_PATH];
	BOOL    m_bGoID_Sel;
	char	m_strGoID[MAX_PATH];
	BOOL    m_bDataSet_Sel;
	char	m_strDataSet[MAX_PATH];
	BOOL	m_bStNumSet_Sel;
	int		m_nStNum;	
	BOOL	m_bSqNumSet_Sel;
	int		m_nSqNum;	
	BOOL	m_bTtlSet_Sel;
	int		m_nTimeAllowToLive;    // ��������ʱ�䵥λ����
	BOOL    m_bAppID_Sel;
	int  	m_nAppID;
	BOOL    m_bNdsCom_Sel;
	BOOL	m_nNdsCom;	//ί�е�ʹ�ܺ�ΪTRUE��Ĭ��nNdsComΪFalse
	BOOL	m_bTestFlag_Sel;
	BOOL	m_nTestFlag;	//���Ա�ǵ�ʹ�ܺ�ΪTRUE��Ĭ��nTestFlagΪFalse
	BOOL	m_bVlanSet_Sel;
	int		m_nVlanID;
	BOOL	m_bNetTypeSet_Sel;
	int		m_nNetType;//�����ʶ
	BOOL	m_bConfRecvSet_Sel;
	int		m_nConfRecv;	// ���ð汾
	int		m_nVLanPriority;
	int		m_nTimequality;//ʱ��Ʒ��
	int		m_nPort;   // ���Ͷ˿ںţ���һ���˿ں�Ϊ��-1��ʾ������
	int		m_nReserved1;
	int		m_nReserved2;

	void init()
	{
		m_nGroupIndex = 0;	//��Ŵӿ�ʼ
		m_bSrcMac_Sel = TRUE;
		m_bDestMac_Sel = TRUE;
		m_bGocbRef_Sel = TRUE;
		m_bGoID_Sel = TRUE;
		m_bDataSet_Sel = TRUE;
		m_bAppID_Sel = TRUE;
		m_bNdsCom_Sel = TRUE;
		m_bTestFlag_Sel = TRUE;
		memset(m_strSrcMac,0, MAX_PATH);
		memset(m_strDestMac,0, MAX_PATH);
		memset(m_strGocbRef,0, MAX_PATH);
		memset(m_strGoID,0, MAX_PATH);
		memset(m_strDataSet,0, MAX_PATH);
		strcpy(m_strSrcMac,"08-08-08-08-08-08");
		strcpy(m_strDestMac,"01-0C-CD-01-00-02");
		strcpy(m_strGocbRef,"HBDY221MUGO/LLN0$GO$gocb0");
		strcpy(m_strGoID,"HBDY221MUGO/LLN0.gocb0");
		strcpy(m_strDataSet,"HBDY221MUGO/LLN0$dsGOOSE0");
		m_nAppID = 0x4001;
		m_bStNumSet_Sel = TRUE;
		m_nStNum = 1;	
		m_bSqNumSet_Sel = TRUE;
		m_nSqNum = 1;	
		m_bTtlSet_Sel = TRUE;
		m_nTimeAllowToLive = 10000;    // ��������ʱ�䵥λ����
		m_nNdsCom = FALSE;	//ί�е�ʹ�ܺ�ΪTRUE��Ĭ��nNdsComΪFalse
		m_nTestFlag = FALSE;	//���Ա�ǵ�ʹ�ܺ�ΪTRUE��Ĭ��nTestFlagΪFalse
		m_bVlanSet_Sel = TRUE;
		m_nVlanID = 0;
		m_bNetTypeSet_Sel = TRUE;
		m_nNetType = 0x88b8;//�����ʶ
		m_bConfRecvSet_Sel = TRUE;
		m_nConfRecv = 1;	// ���ð汾
		m_nVLanPriority = 4;
		m_nTimequality = 0;//ʱ��Ʒ��
		m_nPort = 1;   // ���Ͷ˿ںţ���һ���˿ں�Ϊ��-1��ʾ������
		m_nReserved1 = 0;
		m_nReserved2 = 0;
	}

	tmt_state_abnormal_goose()	{	init();	}
	virtual ~tmt_state_abnormal_goose(){}
}tmt_StateAbnormalGOOSE;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_AbnormalSMV(tmt_StateAbnormalSMV *pAbnormalSMV, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AbnormalGOOSE(tmt_StateAbnormalGOOSE *pAbnormalGOOSE, CSttXmlSerializeBase *pXmlSierialize);



