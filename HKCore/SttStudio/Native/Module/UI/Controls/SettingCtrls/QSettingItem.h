#pragma once

#include <QObject>
#include <QTableWidget>
#include "SettingInterface.h"
#include "../../Module/QExBaseListGridBase/QGridDefine.h"

class QSettingItem : public QObject, public QGV_ITEM, public CSettingInterface
{
	Q_OBJECT
public:
	//explicit QSettingItem(const QString &text);
	explicit QSettingItem(QTableWidget *parent);
	virtual ~QSettingItem(void);

	void ShowSettingDlg();	//20240806 huangliang �����¼������˺����

protected:
	QTableWidget *m_pTableWidget;

public slots:
	void slot_itemPressed(QTableWidgetItem *item);

	void slot_Setting();
	void slot_Clear();
	void slot_Cannel(bool bHide);	//20240731 huangliang ������ر��

public:
	virtual void UpdateText(const QString &strText);	//ʵ��ԭ�ؼ�����ֵ����
	virtual void RefushData();	//ˢ����ʾ��ǰ�������ƻ�ֵ

	virtual BOOL IsSetting();	//��������"SettingIdPath"Ϊ����ǹ���

	virtual CString GetText();	//20240722 huangliang ��ȡ����ֵ

protected:
	virtual void SetProperty(const CString &sFormat);
	virtual void connectSetting();
	virtual void Disconnect();
};
