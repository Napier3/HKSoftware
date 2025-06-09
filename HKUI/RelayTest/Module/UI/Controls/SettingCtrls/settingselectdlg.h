#ifndef SETTINGSELECTDLG_H
#define SETTINGSELECTDLG_H

#include <QDialog>
#include "../../../../../Module/DataMngr/DvmData.h"
#include "../../../XLangResource_Native.h"
#include "SttGlobalModel.h"

namespace Ui {
class SettingSelectDlg;
}

class SettingSelectDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SettingSelectDlg(QWidget *parent = 0);
    virtual ~SettingSelectDlg();

	void InitShow(const QString &strFullPath, const QString &strName, const QString &strValue);

	//20240820 huangliang ת�Ƶ�CSttGlobalModel��
	////20240806 huangliang ������ֵ����·��,�������ʽ����
	//static bool AnalysisPath(const QString &strSrcPath, QString *strName, QString *strValue);

public:
	QString m_strSelectFullPath;		//��ֵ·��
	QString m_strSelectName;			//��ֵ����
	QString m_strSelectValue;			//ֵ

signals:
	void sig_ShowSetting(QString sFormat, QString sName);
    void sig_Setting();
    void sig_Clear();
    void sig_ClearAll();
	void sig_Cannel(bool bHide);	//20240731 huangliang ������ر��

//20240704 huangliang
public slots:
	void slot_SelectModeData(CExBaseObject *pItem);		//��Ӧ��ֵѡ����
	void slot_SelectModeData(QString sValue);

private slots:
    void on_pushButton_Setting_clicked();	

    void on_pushButton_cannel_clicked();

    void on_pushButton_AllCannel_clicked();

protected:
#ifdef _PSX_QT_LINUX_
    virtual void focusOutEvent(QFocusEvent *) ;
#else
    void focusOutEvent(QFocusEvent *) override;
#endif

	bool CheckFocusInChild(QWidget *pParent);

	virtual void keyPressEvent(QKeyEvent *);
	virtual void mousePressEvent(QMouseEvent *);

	//20240820 huangliang ת�Ƶ�CSttGlobalModel�У����ʽ�༭����Ҫʹ��
	////��ģ�������в��Ҷ�Ӧ����
	//static BOOL FindNameFromDeviceModel(const CString &strPath, QString *strName, QString *strValue);
	////static void SetItemText(const CString &sValue, const CString &sFormat);	//��ӵĺ���
	//static BOOL GetNameByPath(const CString &strPath);
	//static long MatchID(CExBaseObject *pCurrItem, const CString &strPath);
	//static CExBaseObject* FindRptDataByPath(CExBaseList *pCurrItem, const CString &strPath);

private:
    Ui::SettingSelectDlg *ui;
};

extern CExBaseList* g_pDvmDevice_AttachSetting;			//ģ��

#endif // SETTINGSELECTDLG_H
