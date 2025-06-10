#ifndef DRV_ABNORMAL_DEFINE
#define DRV_ABNORMAL_DEFINE

#include"drv_state_test.h"
#include "tmt_abnsimulation_test.h"

//SMV����������Ϣ
typedef struct{
    unsigned int nmodule;				//ģ����
    unsigned int nreserved[3];			//ռλ����
    unsigned int nsampleCount;			//���������Ͳ������
    unsigned int nsmvsamplebegin[4];				//������������ֵ
}drv_smvconfig;

typedef struct
{
    int ngoosemodule;
    int ngroup ;//goose group
    int ngooselen;
    char szgoosebuf[1520];//goose out buffer
    int nTimePos;
}drv_gooseabnormal;

//abnormal
typedef struct{
    unsigned int	npoint;     //�쳣���0��79
    unsigned short nlost;        //��֡  1Ϊ��֡��0Ϊ����
    unsigned short	njitter; 	//���� 0 ������ 1Ϊ0.1us��250usд��2500
    int nerrcmpt;                //����   -1999 �� 2000 0Ϊ�Ǵ���
    unsigned int nflypoint;      //�ɵ�ʹ��
    int		 nflyPointVValue;	//�ɵ��ѹֵ
    int		 nflyPointIValue;	//�ɵ����ֵ
}drv_svabnunit;

typedef struct
{
    unsigned int   nmodule ;//����ģ���ţ�Ĭ��
    unsigned int  nptCnt;     //�쳣����
    drv_svabnunit	smv_abnormal[80];	//ÿ�ܲ�������쳣����
    int  ngroup;//SMV��� 8bit��Ч��0��Ч 1ʹ�� �� 0011 ���ǵ�һ�ڶ���ʹ�ܣ�������Ч��
    unsigned int   nabnormalcircle ;//�쳣�ܲ���
    unsigned int   nnormalcircle;// �����ܲ���
    unsigned int   nroopcount ;//ѭ������
}drv_smvabnormal;

typedef struct{
    unsigned int ncount;				//���ݳ���
    unsigned int ngroup;				//���ݹ�ں�
    unsigned char szdat[1536];			//��������
}drv_datconfig;

typedef struct{
    unsigned int nmodule;			//ģ����
    unsigned int ncount;				//�����ܺ�
    drv_datconfig dat[8];
}drv_abnormalconfigs;

typedef struct
{
        unsigned long nStateNum;                                    //״̬������ţ�0��ʼ
        // 0 manual 1 time 2 gps 3 bin or 4 bin and
        unsigned long nTirpType;                                 //������������Ӧλ����д��Ҫ��ת����״̬
        unsigned long nReversal;                                    //���뷭ת�ο�����:
            //0�����뷭ת����wa
            //1�����������ش���
            //2�������½��ش���
        unsigned long  nOrValid;               //����򴥷���Чλ
        unsigned long nAndValid;                                    //�����봥����Чλѡ��bit9~bit0��Ӧͨ��9~ͨ��0
        unsigned long nGpsSec;                                      //GPS������ֵ
        unsigned long nGpsnSec;                                     //GPS��������ֵ
        unsigned long nTimemSec;                                    //ʱ�䴥������ֵ
        unsigned long nDelay;                                       //���봥����ʱʱ�䣬���������������ʱ�೤ʱ�䴥��
        drv_analogbosetting oBo;
        drv_acanalogpara acAnalog;                          //ģ�����
        drv_digitalpara  acDigital;			//���ֲ���
        int nabnormaltype;           //0������ 1��SMV�쳣  2��GOOSE �쳣 ������ �޶���
        drv_gsechangeditems GooseChangedItem;// abnormaltype=0 valid
        drv_abnormalconfigs oabnormalcomfig;
        drv_smvabnormal osmvabnormal;//abnormaltype=1 valid
        drv_gooseabnormal ogooseabnormal;//abnormaltype=2 valid
        int nsendconfig;
        drv_smvconfig oconfig;
}drv_abnstate;

typedef struct
{
        unsigned long nModuleCount;				//ģ������
        unsigned long nStateModuleCount;        //����ģ��
        unsigned long nStateCount;				//״̬����
        unsigned long nloop;
        unsigned long nReverRefence;                                //0 �ο���һ��״̬ 1�ο���һ��״̬
        unsigned long noriginal;                //GOOSE init Value;
        drv_analogbosetting oBo;//ʲô���ã�����
        drv_abnstate stabnState[STATECOUNT];				//״̬
}drv_abnstate_test;

void tmt_to_drv(tmt_AbnSimulationTest *pTmt, drv_abnstate_test *pDrv);

#endif
