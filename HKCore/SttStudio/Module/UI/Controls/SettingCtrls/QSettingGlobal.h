#ifndef QSETTINGGLOBAL_H
#define QSETTINGGLOBAL_H
/*
 * Create By HuangLiang 20240802
 * 用于定值关联
*/

#include <QObject>
#include "QSettingLineEdit.h"
#include "QSettingItem.h"
#include "settingselectdlg.h"

#define STT_SETTING_SETTINGGLOBAL_ClassID	"QSettingGlobal"

class QSettingGlobal : public QObject
{
	Q_OBJECT
public:
	explicit QSettingGlobal();
	virtual ~QSettingGlobal();

	//设置顶级父地址
	void SetParent(QWidget *pParent){ m_pParent = pParent; }

	//选择定值后通知控件
	void SettingSelect(CExBaseObject *pItem);
	void SettingSelect(const CString &sValue);

signals:
	void sig_SettingSelect(CExBaseObject *pItem);		//响应定值选择结果信号
	void sig_SettingSelect(QString sValue);				

public slots:
	void slot_ShowSetting(QString sFormat, QString sName);
    void slot_ClearAllMap();

protected:
	QWidget *m_pParent;

	//关联定值界面信号
	bool ConnectForSettingDlg();

	//全部取消响应
	virtual void ClearAllMaps();
	void ChildInitMaps(QObject *child, int iOperation);
	void ChildInitTable(QTableWidget *table, int iOperation);

};

extern QSettingGlobal *g_pQSettingGlobal_Object;

#endif // QSETTINGGLOBAL_H
