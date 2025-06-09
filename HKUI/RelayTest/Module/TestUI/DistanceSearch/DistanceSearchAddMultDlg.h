#ifndef DISTANCESEARCHADDMULTDLG_H
#define DISTANCESEARCHADDMULTDLG_H

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QComboBox>
#include "../../../../Module/DataMngr/DataGroup.h"

namespace Ui {
class QDistanceSearchAddMultDlg;
}

class QDistanceSearchAddMultDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QDistanceSearchAddMultDlg(QWidget *parent = 0);
    virtual ~QDistanceSearchAddMultDlg();
    void InitUI();
	void SetDatas(CDataGroup *pParas);
	void GetDatas(CDataGroup *pParas);

private:
    void SetValueToPage(CDvmData *pData);
    void GetPageToValue(CDvmData *pData);
    void CheckAllPresence(CDataGroup *pParas);
    void AddDistanceSearchMultItem();

private:
    Ui::QDistanceSearchAddMultDlg *ui;

    QCheckBox *m_cbAN;  //AN
    QCheckBox *m_cbBN;  //BN
    QCheckBox *m_cbCN;  //CN
    QCheckBox *m_cbAB;  //AB
    QCheckBox *m_cbBC;  //BC
    QCheckBox *m_cbCA;  //CA
    QCheckBox *m_cbABC;  //ABC

    QLineEdit *m_editLNActionTime;
    QLineEdit *m_editLLActionTime;
    QLineEdit *m_editLLLActionTime;

    int m_nInputWidgetWidth;     //20240802 wanmj lineEdit和comboBox固定宽度

    int nFaultTypeArr[7];	//AN-ABC七种故障类型
    double dTSetting[3];	//LN、LL、LLL三种故障类型对应动作时间
    double dFaultCur;	//短路电流
    double dFaultVolt;	//短路电压
    int nZoneType;  //区段
    double dOrigImp;    //中心点阻抗
    double dOrigAng;    //中心点阻抗角
    double dSearchAngBeg;   //搜索角始值
    double dSearchAngEnd;   //搜索角终值
    double dAngStep;    //角度改变步长
    double dSearchLen;  //搜索半径
    double dRelErr; //相对误差
    double dAbsErr; //绝对误差
    int nErrType;   //误差类型

    double dBegX;   //搜索线起点横坐标
    double dBegY;   //搜索线起点纵坐标
    QVector<double> dEndX;   //搜索线终点横坐标数组
    QVector<double> dEndY;   //搜索线终点纵坐标数组

signals:
    void sig_AddDistanceSearchItem(int nFaultType, double dSettingTime, int nZoneType, double dBegZ, double dBegAng, double dEndZ, double dEndAng,
                                   double dFaultCur, double dFaultVolt, double dRelErr, double dAbsErr, int nErrType);

private slots:
    void on_m_btnOk_clicked();
    void on_m_btnCancel_clicked();
    void on_m_editLNActionTime_editingFinished();
    void on_m_editLLActionTime_editingFinished();
    void on_m_editLLLActionTime_editingFinished();
    void on_m_cbbZoneType_currentIndexChanged(int index);
    void on_m_editOrigImp_editingFinished();
    void on_m_editOrigAng_editingFinished();
    void on_m_editFaultCur_editingFinished();
    void on_m_editFaultVol_editingFinished();
    void on_m_editSearchAngBeg_editingFinished();
    void on_m_editSearchAngEnd_editingFinished();
    void on_m_editAngStep_editingFinished();
    void on_m_editSearchLen_editingFinished();
    void on_m_editRelErr_editingFinished();
    void on_m_editAbsErr_editingFinished();
};

#endif // DISTANCESEARCHADDMULTDLG_H
