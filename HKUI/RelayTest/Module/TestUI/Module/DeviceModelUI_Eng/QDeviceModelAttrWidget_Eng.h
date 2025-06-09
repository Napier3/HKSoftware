#ifndef QDeviceModelAttrWidget_Eng_H
#define QDeviceModelAttrWidget_Eng_H

#include "../../../../../Module/OSInterface/QT/XMessageBox.h"
#include "../../../../../61850/Module/XLanguageResourcePp_Mms.h"
#include "../../../../../RelayTest/Module/XLangResource_Native.h"
#include "../../../../../AutoTest/Module/XrioRead/XDeviceModel/XDeviceModel.h"

namespace Ui {
class QDeviceModelAttrWidget_Eng;
}

class QDeviceModelAttrWidget_Eng : public QWidget
{
    Q_OBJECT

public:
    explicit QDeviceModelAttrWidget_Eng(QWidget *parent = 0);
    virtual ~QDeviceModelAttrWidget_Eng();
	BOOL CreateQDeviceModelAttrWidget_Eng(CDvmDataset *pDeviceAttrs);
    CDvmDataset *m_pAttrWidgetDeviceAttrs;

    CString m_strValueDeviceModel;
    CString m_strValueManufacturer;
    CString m_strValueDeviceType;
    CString m_strValueSerialnr;
    CString m_strValueAdditionalINF02;

    CString m_strValueDeviceAddress;
    CString m_strValueSubstation;
    CString m_strValueSubstatioAddress;
    CString m_strValueBay;
    CString m_strValueBayAddress;
    CString m_strValueProtectedObjectName;

    CString m_strValuePhases;
    CString m_strValueFNom;
    CString m_strValueVNom;
    CString m_strValueVPrimLL;
    CString m_strValueINom;
    CString m_strValueIprim;

    CString m_strValueVLNVN;
    CString m_strValueININOM;

    CString m_strValueVMAX_LL;
    CString m_strValueIMAX;

    CString m_strValueDEBOUNCETIME;
    CString m_strValueDEGLITCHTIME;
    CString m_strValueOVERLOADSUPTIME;
private:
    void InitDeviceModelAttrWidget();
    void InitObjectValue(CDvmDataset *pDeviceAttrs);
    void InitConnnect();

    BOOL UpdateObjectValue(CString& strObject,const CString& strParentID ,const CString& strObjectID,CDvmDataset *pDataset);//xrio更新
    BOOL UpdateObjectDataOrValue(CString& strObject,const CString& strXrioParentID ,const CString& strXrioObjectID,const CString& strRioParentID,CDvmDataset *pDataset);//判断是xrio还是rio更新
    CDvmValue* FindValueObject(const CString& strParentID ,const CString& strObjectID);
    // 成员变量，用于存储上一次的合法输入（包括Hz后缀）
    BOOL ProcessInput(QLineEdit* pLineEdit, const QString& unit, QString &lastValidInput);

    QString ValueVPrimLLToValueVPrimLL2(QString &text);
    QString ValueVPrimLL2ToValueVPrimLL(QString &text);
    QString ValueVPrimLL3ToValueVPrimLL(QString &text);


    QString ValueVNomToValueVNom2(QString &text);
    QString ValueVNom2ToValueVNom(QString &text);
    QString ValueVNom3ToValueVNom(QString &text);

    QString ValueINom2ToValueINom(QString &text);

    QString ValuePhases2ToValueVPrimLL2_ValueVNom2(QString &text);
    QString ValuePhases3ToValueVPrimLL2_ValueVNom2(QString &text);

    QString m_strValueFNomlastValidInput;
    QString m_strValueVPrimLLlastValidInput;
    QString m_strValueVPrimLLlastValidInput2;
    QString m_strValueVPrimLLlastValidInput3;

    QString m_strValueVNomlastValidInput;
    QString m_strValueVNomlastValidInput2;
    QString m_strValueVNomlastValidInput3;

    QString m_strValueIPRIMlastValidInput;
    QString m_strValueIPRIMlastValidInput2;

    QString m_strValueINomlastValidInput;
    QString m_strValueINomlastValidInput2;

    QString m_strValueVMAXLLValidInput;
    QString m_strValueIMAXValidInput;

    QString m_strValueOVERLOADSUPTIMEValidInput;
    QString m_strValueDeBounceTimeValidInput;
    QString m_strValueDeGlitchTimeValidInput;

    QString m_strValueBackTimeValidInput;

    Ui::QDeviceModelAttrWidget_Eng *ui;
private slots:
    //ui界面自动添加槽函数
    void on_m_radCustomize_clicked();
    void on_m_radHigh_clicked();
    void on_m_radLow_clicked();
    void on_m_radDisconnect_clicked();
    void on_m_btnOK_clicked();
    void on_m_btnCancel_clicked();
    void on_m_editDeviceMode_editingFinished();
    void on_m_editManufacturer_editingFinished();
    void on_m_editDeviceType_editingFinished();
    void on_m_editDeviceAddress_editingFinished();
    void on_m_editSerialnr_editingFinished();
    void on_m_editProtectedObjectName_editingFinished();
    void on_m_editAdditionalINF02_editingFinished();
    void on_m_editSubstation_editingFinished();
    void on_m_editSubstatioAddress_editingFinished();
    void on_m_editBay_editingFinished();
    void on_m_editBayAddress_editingFinished();
    void on_m_editFNom_editingFinished();
    void on_m_editVPrimLL_editingFinished();
    void on_m_editVPrimLL2_editingFinished();
    void on_m_editVPrimLL3_editingFinished();
    void on_m_editVNom_editingFinished();
    void on_m_editVNom2_editingFinished();
    void on_m_editVNom3_editingFinished();
    void on_m_editIPRIM_editingFinished();
    void on_m_editIPRIM2_editingFinished();
    void on_m_editINom_editingFinished();
    void on_m_editINom2_editingFinished();
    void on_m_editVMaxLL_editingFinished();
    void on_m_editIMax_editingFinished();
    void on_m_editOverloadSupTime_editingFinished();
    void on_m_editDeBounceTime_editingFinished();
    void on_m_editDeGlitchTime_editingFinished();
    void on_m_radPhases2_clicked();
    void on_m_radPhases3_clicked();
    void on_m_editBackTime_editingFinished();
    //手动添加槽函数
    void slot_m_editDeviceMode_editingFinished(const QString& CurrentText);
    void slot_m_editManufacturer_editingFinished(const QString& CurrentText);
    void slot_m_editDeviceType_editingFinished(const QString& CurrentText);
    void slot_m_editDeviceAddress_editingFinished(const QString& CurrentText);
    void slot_m_editSerialnr_editingFinished(const QString& CurrentText);
    void slot_m_editProtectedObjectName_editingFinished(const QString& CurrentText);
    void slot_m_editAdditionalINF02_editingFinished(const QString& CurrentText);
    void slot_m_editSubstation_editingFinished(const QString& CurrentText);
    void slot_m_editSubstatioAddress_editingFinished(const QString& CurrentText);
    void slot_m_editFNom_editingFinished(const QString& CurrentText);
    void slot_m_editBay_editingFinished(const QString& CurrentText);
    void slot_m_editBayAddress_editingFinished(const QString& CurrentText);
    void slot_m_editVPrimLL_editingFinished(const QString& CurrentText);
    void slot_m_editVPrimLL2_editingFinished(const QString& CurrentText);
    void slot_m_editVPrimLL3_editingFinished(const QString& CurrentText);
    void slot_m_editVNom_editingFinished(const QString& CurrentText);
    void slot_m_editVNom2_editingFinished(const QString& CurrentText);
    void slot_m_editVNom3_editingFinished(const QString& CurrentText);
    void slot_m_editIPRIM_editingFinished(const QString& CurrentText);
    void slot_m_editIPRIM2_editingFinished(const QString& CurrentText);
    void slot_m_editINom_editingFinished(const QString& CurrentText);
    void slot_m_editINom2_editingFinished(const QString& CurrentText);
    void slot_m_editVMaxLL_editingFinished(const QString& CurrentText);
    void slot_m_editIMax_editingFinished(const QString& CurrentText);
    void slot_m_editOverloadSupTime_editingFinished(const QString& CurrentText);
    void slot_m_editDeBounceTime_editingFinished(const QString& CurrentText);
    void slot_m_editDeGlitchTime_editingFinished(const QString& CurrentText);
    void slot_m_radPhases2_clicked();
    void slot_m_radPhases3_clicked();
signals:
    void sig_CancelClicked();  // 声明信号
    void sig_UpdataDeviceAttrs(CDvmDataset *pDataset);
    void sig_m_editDeviceMode_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editManufacturer_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editDeviceType_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editDeviceAddress_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editSerialnr_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editProtectedObjectName_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editAdditionalINF02_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editSubstation_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editSubstatioAddress_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editBay_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editBayAddress_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editFNom_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editVPrimLL_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editVPrimLL2_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editVPrimLL3_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editVNom_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editVNom2_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editVNom3_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editIPRIM_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editIPRIM2_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editINom_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editINom2_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editVMaxLL_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editIMax_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editOverloadSupTime_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editDeBounceTime_editingFinished_Widget(const QString& CurrentText);
    void sig_m_editDeGlitchTime_editingFinished_Widget(const QString& CurrentText);
    void sig_m_radPhases2_clicked_Widget();
    void sig_m_radPhases3_clicked_Widget();
};

class QDeviceModelAttrDlg_Eng : public QDialog
{
    Q_OBJECT

public:
    explicit QDeviceModelAttrDlg_Eng(CXDeviceModel *pXDeviceModel,QWidget *parent = 0);
    virtual ~QDeviceModelAttrDlg_Eng();
private:
    QDeviceModelAttrWidget_Eng *pDeviceModelAttrWidget;
private slots:
    void slot_UpdataDeviceAttrs(CDvmDataset* pDataset);

signals:
    void sig_UpdataDeviceAttrs(CDvmDataset *pDataset);
};

#endif // QDeviceModelAttrWidget_Eng_H
