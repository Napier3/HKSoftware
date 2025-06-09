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
void initPositiveIntegerLne(QLineEdit *lne);  //限制正整数
void initPositiveIntegerCombobox(QComboBox *cmb);
void initMaxLineEdit(QLineEdit *lne);       //限制浮点数输入范围为[-999.999.999,999.999.999] 小数点三位默认
void initMaxLineEdit_four(QLineEdit *lne);  //限制浮点数输入范围为[-999.999.9999,999.999.9999] 小数点四位
void initMaxEdit(QLineEdit *lne);   

void initMaxPositiveEdit(QLineEdit *lne);   //限制大于0,三位小数
void initMaxPositiveEdit_Three(QLineEdit *lne);//限制大于0,三位小数
void initMaxPositiveEdit_four(QLineEdit*lne);
void initMaxPositiveCombox(QComboBox *cmb);
void initMaxPositiveCombox_four(QComboBox *cmb);
void initMaxPositiveComboxNoLimit(QComboBox *cmb);

void init360LineEdit(QLineEdit *lne);       //限制-180 +180之间
void initMaxV(QLineEdit* lne);       //电压最大450V 电流最大10A 频率最大5000Hz
void initMaxV(QComboBox *ccmb);
void initMaxI(QLineEdit* lne);
void initMaxI(QComboBox *cmb);
void initMaxHz(QLineEdit *lne);
void initMaxHYL(QLineEdit *lne);
double R180(double val );
double roudVal(double val, double maxV, double minV, double cycle );
double GetAmp( const std::complex<double>& c1 );
double GetAngle( const std::complex<double>& c1 );  // 角度
//void Delay_MSec(unsigned int msec);//zhouhj 2-24.5.6 delete 
QString comparaSwitchStatus(int ch[],int ch2[],int num);
QString compareSwitchStatusBynSource(int v);
float setLimit(float min,float max,float val);
float setAngleLimit(float val);
float setAngleLimitEx(float val);//(-360~360) sf 20210805
void initMaxEdit_one(QLineEdit *lne);//0~999.9 一位小数

//递变
para_type getParaTypeByInt(int iVar);
//序分量
Sequence_type getParaTypeByIndex(int iVar);
changed_type getChangeTypeByIndex( int index );
//线电压
LineVolt_type getParaTypeByVIndex(int iVar);

void LimitAngle360(float &fAngle);
void LimitAngle180(float &fAngle);

//功率、线电压、序分量计算
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

// 其它
// void GetAnalogUIStringList(QStringList &oList,MOUDLEType moduleType);
// void GetAnalogUIStringList(int nGroupIndex,int nGroupChNum,QStringList &oList,const QString &strUI);


//模态对话框键盘
//数字软键盘
//nType: 0-电压 1-电流 2-相位 3-频率 4-数字键盘
void GetWidgetBoard_DigitData(long nType,QString& strText,QWidget *parent = NULL);
//英文键盘
void GetEngWidgetBoard_DigitData(QString& strText,QWidget *parent);
void GetChsWidgetBoard_DigitData(QString& strText, QWidget *parent, QRect rc);

//非模态对话框键盘
//数字软键盘
//nType: 0-电压 1-电流 2-相位 3-频率 4-数字键盘
void CreateKeyBoardWidget();
void ReleaseKeyboardWidget();
void ExitHideKeyboardWidget();//隐藏非模态对话框
void GetWidgetBoard_DigitData(long nType,QString& strText,CCommonCtrlInterface *pCommonCtrl,QWidget *parent ,int bTableWidget = 0);
void Global_SoftKeyBoardAttachObj(QWidget *pParentWidget,long nKeyBoardType = STT_DefaultKeyboardType_Number);

CString Global_GetSaveAsRootPath();//获取另存为文件的根目录路径,对应Linux系统下,判断当前USB接口是否挂载U盘,如挂载则存储到对应的文件夹下,否则存储在环境的Library目录下
BOOL Global_GetUsbRootFolderPath(CString &strUsbRootFolderPath);//获取USB接口根目录路径

#endif
