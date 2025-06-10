#ifndef DRV_MANU_GRADIENT_DEF_H
#define DRV_MANU_GRADIENT_DEF_H

#ifdef _PSX_IDE_QT_
#include<QVector>
#endif
#include "tmt_gradient_test.h"
#include "tmt_manu_test.h"
#include "../../SttDevice/RelayTest/drv_define.h"

typedef struct
{
    unsigned int	nmodule;                 //ģ����
    unsigned int	nposCnt;                 //λ�����������Ϊ6
    unsigned int	npos[GRADIENT_PARAM_MAX];  //λ��ֵ
	long 			ndat[GRADIENT_PARAM_MAX];  //ÿ��λ�õ�����
}drv_gradientdigunit;

typedef struct
{
    unsigned int	nmodule;  //ģ����
    unsigned int	nposCnt;  //λ�����������Ϊ6
	unsigned int	npos[CHANNEL_MAX*3]; //λ��ֵ
	long 			ndat[CHANNEL_MAX*3]; //ÿ��λ�õ�����
}drv_gradientalgunit;

typedef struct
{
    long ndat[GRADIENT_ALG_PARA_CNT];
}drv_gradientalg;

typedef struct
{
    unsigned int ndat[GRADIENT_SMV_PARA_CNT];
}drv_gradientdig;

//�������������������Ա������λ�ñ�����structDegPara deg[3000];��ͬ������ᵼ���������ȷ
typedef struct
{
    drv_gradientalg    alg[MODULE_MAX];
	drv_gradientdig    dig[DIGITAL_MODULE_MAX];
}drv_gradientnormal;

typedef struct
{
    drv_gradientalgunit	 algDgress[MODULE_MAX];          //ģ��ݱ����ݣ����4��ģ��
    drv_gradientdigunit	  digDgress[DIGITAL_MODULE_MAX];  //SMV�ݱ����ݣ����4��ģ��
}drv_gradientpara;

typedef struct
{
    unsigned int nalgCount;             //ģ��ģ������
    unsigned int ndigCount;             //����ģ������
    unsigned int ngradientCount;         //�ݱ�����    �ݱ���� + 1 ����
    unsigned int nisReturn;             // 0�� ����ֵ   1�� ����ϵ��������
    unsigned int ndiRef;                //�������ο���0����ת	1��������	2���½���
    unsigned int ndiLogic;              //��������Ч�߼���0��������		1�������
    unsigned int ndiValid;              //��������Чλ��bit9~0��Ӧ����9~0
	unsigned int ngsAndValid;           //goose����Чλ��δʹ��
    unsigned int ngsOrValid;            //goose����Чλ��δʹ��    
    unsigned int ntimeDiv;              //�ݱ�ʱ��ֶȣ�����ֵ������ʱ��
    unsigned int ntimeBfChg;            //�ݱ�ǰʱ�䣬��λ���룬�仯ǰʱ��
	drv_gradientnormal bfChange;          //�ݱ�ǰ���ݲ���������
    unsigned int ntimeBfFault;          //����ǰʱ�䣬��λ����
	 drv_gradientnormal bfFault;           //����ǰ����������
    unsigned int nDIBfFault;            //����ǰ�����ź�
    unsigned int nDIFault;              // ���Ͽ���
    unsigned int nDIFaultFlipSec;       // ���Ͽ��뷭ת��ֵ
    unsigned int nDIFaultFlipnSec;      // ���Ͽ��뷭תʱ������
    drv_gradientpara       gradient[GRADIENT_MAX_COUNT];     //�ݱ���������3000���ݱ�
}drv_gradient_test;



typedef struct
{
    unsigned int nmodule; //ģ����
    unsigned int nharmCnt; //г����Ŀ
    unsigned int ndat[DIGITAL_CHANNEL_MAX * 3 * HARMONIC_MAX]; // 2325 total 9300 bytes
}drv_sinharmitem;

typedef struct
{
    unsigned int nmoduleCount; // ��������ģ��
    drv_sinharmitem harm[4];
}drv_sinharm;

typedef struct
{
    unsigned int nmodule;
    unsigned int nwaveCount;//������
	long ndat[CHANNEL_MAX+CHANNEL_MAX*3*HARMONIC_MAX]; // �˴�Ӧ����564
}drv_harm;

typedef struct
{
    unsigned int nmdCount;//��ʾһ���м���ģ��ģ�� ��󲻳���4����û����0
    unsigned int nuiDO;//����
    drv_harm      harm[4];
}drv_harmpara;

typedef struct
{
    drv_sinharm     dig; //����ģ��
    drv_harmpara  alg; //ģ��
}drv_manu_test;

typedef struct
{
    unsigned int 	nisStop;			//���յ������Ƿ�ֹͣ
    unsigned int	nmdelay;			//���յ�������ֹͣ��ʱʱ�䣬��λ����
    unsigned int 	nisSend0;		//ֹͣʱSMV�Ƿ���0���Ƿ񱣳ַ���
    unsigned int 	nbiRef;			//����ο�0����ת	1��true		2��false
    unsigned int 	nbiAndValid;		//��������Чλ
    unsigned int 	nbiOrValid;		//�������Чλ
    unsigned int 	ngsAndValid;		//δʹ�ã�ʹ��biAndValid
    unsigned int 	ngsOrValid;		//δʹ�ã�ʹ��biOrValid
}drv_manu_bi;

////manu  &&    degress
//typedef struct
//{
//    unsigned int nstep;      //����
//    unsigned int ntype;		//0:start  1:stop  2:change  3:di change  4:start to return
//    unsigned int ntm_h;      //��
//    unsigned int ntm_l;      //tm_l/2^32
//    unsigned int ndi;        //Ӳ����
//    unsigned int ngsdi;      //gs����
//    unsigned int nsource;    //����仯״̬
//}drv_gradient_result;

typedef struct
{
    drv_manu_test       m_oManuStruct;
    drv_manu_bi           m_oManuBinStruct;
    drv_gradient_test  m_oGradientStruct;
}drv_manu_gradient_test;


void tmt_to_drv_manual_digital(drv_manu_test *pDrv, tmt_channel *pUData, tmt_channel *pIData, bool bDC=false,int harm=1);
void tmt_to_drv_manual_analog(drv_manu_test *pDrv, tmt_channel *pUData, tmt_channel *pIData, tmt_BinaryOut *binOut, bool bDC=false,int harm=1);
void tmt_to_drv_Gradient_alg(drv_gradient_test *pDrvGradient, tmt_GradientProcess *pGradientProcess, int nGradientType,int nHarmIndex=1);
void tmt_to_drv_Gradient_dig(drv_gradient_test *pDrvGradient, tmt_GradientProcess *pGradientProcess, int nGradientType, int bDC=false,int nHarmIndex=1);
#endif

