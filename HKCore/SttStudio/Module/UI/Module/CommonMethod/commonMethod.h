#ifndef COMMONMETHOND_H
#define COMMONMETHOND_H
#include <QtGui>
#include <QString>
#include <QToolButton>
#include <vector>
#include <cmath>
#include <complex>

#include "../SttUIDefine.h"
#include "../../Module/SttTestSysGlobalPara.h"
#include "../../Module/SttTest/Common/tmt_system_config.h"
#include "../../Module/SttTest/Common/tmt_common_def.h"
#include "../../Controls/SttLineEdit.h"
#include "../QExBaseListGridBase/QGridDefine.h"

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#include<QtWidgets>
#endif
#include "../../../../../Module/OSInterface/QT/CString_QT.h"

#define STT_DefaultKeyboardType_Number                 0
#define STT_DefaultKeyboardType_English                1
#define STT_DefaultKeyboardType_Symbol                 2
#define STT_DefaultKeyboardType_Chinese                3

#define SINCOUNT 200000
extern float sinData[SINCOUNT*2+4];
void generagelsinData();

bool ping_ip(QString ip);

float getMaxFormThreeValue(float f1,float f2,float f3);
float getMinFormThreeValue(float f1,float f2,float f3);

ErrorType getErrorTypeEnumByIndex(int index);
PTPhase getPTPhaseByIndex(int index); 
QString getErrorTypeStringByEnum(ErrorType type);
QString getErrorTypeResultStringByEnum( ErrorType type );
bool isPosiDigitstr(QString str);
void initToolbutton(QToolButton *btn,QString strName,QString pic_name);
bool ping_ip(QString ip);
void initPositiveIntegerLne(QLineEdit *lne);  //����������
void initPositiveIntegerCombobox(QComboBox *cmb);
void initMaxLineEdit(QLineEdit *lne);       //���Ƹ��������뷶ΧΪ[-999.999.999,999.999.999] С������λĬ��
void initMaxLineEdit_four(QLineEdit *lne);  //���Ƹ��������뷶ΧΪ[-999.999.9999,999.999.9999] С������λ
void initMaxEdit(QLineEdit *lne);   

void initMaxPositiveEdit(QLineEdit *lne);   //���ƴ���0,��λС��
void initMaxPositiveEdit_Three(QLineEdit *lne);//���ƴ���0,��λС��
void initMaxPositiveEdit_four(QLineEdit*lne);
void initMaxPositiveCombox(QComboBox *cmb);
void initMaxPositiveCombox_four(QComboBox *cmb);
void initMaxPositiveComboxNoLimit(QComboBox *cmb);

void init360LineEdit(QLineEdit *lne);       //����-180 +180֮��
void initMaxV(QLineEdit* lne);       //��ѹ���450V �������10A Ƶ�����5000Hz
void initMaxV(QComboBox *ccmb);
void initMaxI(QLineEdit* lne);
void initMaxI(QComboBox *cmb);
void initMaxHz(QLineEdit *lne);
void initMaxHYL(QLineEdit *lne);
double R180(double val );
double roudVal(double val, double maxV, double minV, double cycle );
double GetAmp( const std::complex<double>& c1 );
double GetAngle( const std::complex<double>& c1 );  // �Ƕ�
//void Delay_MSec(unsigned int msec);//zhouhj 2-24.5.6 delete 
QString comparaSwitchStatus(int ch[],int ch2[],int num);
QString compareSwitchStatusBynSource(int v);
float setLimit(float min,float max,float val);
float setAngleLimit(float val);
float setAngleLimitEx(float val);//(-360~360) sf 20210805
void initMaxEdit_one(QLineEdit *lne);//0~999.9 һλС��

//�ݱ�
para_type getParaTypeByInt(int iVar);
//�����
Sequence_type getParaTypeByIndex(int iVar);
changed_type getChangeTypeByIndex( int index );
//�ߵ�ѹ
LineVolt_type getParaTypeByVIndex(int iVar);

void LimitAngle360(float &fAngle);
void LimitAngle180(float &fAngle);

//���ʡ��ߵ�ѹ�����������
PowerValue GetPowerValue(bool isDC, tmt_Channel*pUa, tmt_Channel*pUb, tmt_Channel*pUc, tmt_Channel*pIa, tmt_Channel*pIb, tmt_Channel*pIc);

SeqValue GetZeroSeqValue( tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC );
SeqValue GetPositiveSeqValue( tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC );
SeqValue GetNegativeSeqValue( tmt_Channel*pA, tmt_Channel*pB, tmt_Channel*pC );

double roudVal( double val, double maxV, double minV, double cycle );
double R180( double val );

double GetASubBAmp( tmt_Channel*pA, tmt_Channel*pB );
double GetASubBAngle( tmt_Channel*pA, tmt_Channel*pB);

unsigned int GetIntByBits(long arrSwitch[],int nCount);
QString compareSwitchStatusByInput(int nInput);

void CalcPhrasePArr(int nABCSel,float fSelAngle,float *pCalcPhraseArr);
void CalcPhraseNArr(int nABCSel,float fSelAngle,float *pCalcPhraseArr);

// ����
// void GetAnalogUIStringList(QStringList &oList,MOUDLEType moduleType);
// void GetAnalogUIStringList(int nGroupIndex,int nGroupChNum,QStringList &oList,const QString &strUI);


//ģ̬�Ի������
//���������
//nType: 0-��ѹ 1-���� 2-��λ 3-Ƶ�� 4-���ּ���
void GetWidgetBoard_DigitData(long nType,QString& strText,QWidget *parent = NULL);
//Ӣ�ļ���
void GetEngWidgetBoard_DigitData(QString& strText,QWidget *parent);
void GetChsWidgetBoard_DigitData(QString& strText, QWidget *parent, QRect rc);

//��ģ̬�Ի������
//���������
//nType: 0-��ѹ 1-���� 2-��λ 3-Ƶ�� 4-���ּ���
void CreateKeyBoardWidget();
void ReleaseKeyboardWidget();
void ExitHideKeyboardWidget();//���ط�ģ̬�Ի���
void GetWidgetBoard_DigitData(long nType,QString& strText,CCommonCtrlInterface *pCommonCtrl,QWidget *parent ,int bTableWidget = 0);
void Global_SoftKeyBoardAttachObj(QWidget *pParentWidget,long nKeyBoardType = STT_DefaultKeyboardType_Number);

CString Global_GetSaveAsRootPath();//��ȡ���Ϊ�ļ��ĸ�Ŀ¼·��,��ӦLinuxϵͳ��,�жϵ�ǰUSB�ӿ��Ƿ����U��,�������洢����Ӧ���ļ�����,����洢�ڻ�����LibraryĿ¼��
BOOL Global_GetUsbRootFolderPath(CString &strUsbRootFolderPath);//��ȡUSB�ӿڸ�Ŀ¼·��

#endif
