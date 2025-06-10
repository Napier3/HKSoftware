#ifndef SttIecRecordMainWidget_H
#define SttIecRecordMainWidget_H

#include <QDialog>
#include <QFont>
#include "../../Module/SmartCap/61850Cap/CapDevice/CapDeviceBase.h"
#include "SttIecRcdFuncInterface.h"

//2022-12-02  lijunqing  
#include "../../Assist/SttAssistGlobalApi.h"

namespace Ui {
class QSttIecRecordMainWidget;
}


class QSttIecRecordMainWidget : public QDialog, 
	public CSttWndAssistInterface  //2022-12-02 lijunqing ����������صĽӿ�
{
    Q_OBJECT
public:
    explicit QSttIecRecordMainWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttIecRecordMainWidget();

//CSttWndAssistInterface
public:
	//���Ҵ��ڣ������� �ҵ����ش���,      ���򷵻�NULL
	//�������������ش˺�������Ϊ���ֱ�ӷ��ش���ָ�룬Ȼ��ǿ��ת��ΪCSttWndAssistInterface�������
	virtual CSttWndAssistInterface* ast_FindWnd(const CString &strWndID);

	//����ִ�нӿ�
	virtual bool ast_ExecCmd(const CString &strCmdID,const CString &strParas);
	virtual bool ast_ExecCmd_Data(const CString &strCmdID, const CString &strDataID);
	virtual bool ast_ExecCmd_DataFile(const CString &strCmdID, const CString &strDataFile);

public:
	void SetIecCapWriteFile(bool b);
	void SetIecCapDebugHead(bool b);

	void InitIecRecordCbWidget(const CString &strFuncID,long nPkgDetectType);

	void ShowIecDetectWindow();
	void ShowIecCbWindow();
	void UpdateCapDevice(CCapDeviceBase *pCapDevice);
	void StartDetect();//��ʼ̽�� 
	void UpdateIecfg();//iecfg�ļ��޸ĺ�,����̽�������е�����
	void CloseIecCapDetect();//20220629 zhouhj �رղ��Թ��ܽ���ʱ,����ײ㻹����̽��ģʽ,�ر�̽��ͨ��
	void ClearAll_StartDetect();//���ȫ��,���¿�ʼ̽��
	void UpdateIecDetectType(long nPkgDetectType);

public slots:

signals:
	void sig_ShowIecDetectWindow();
	void sig_ShowIecCbWindow();

private slots:
	void on_ShowIecDetectWindow();
	void on_ShowIecCbWindow();

private:
    Ui::QSttIecRecordMainWidget *ui;

public://20231017 wxy �ⲿ��Ҫ��m_pSttIecRecordDetectWidget������Ϊ����
	QDialog *m_pSttIecRecordDetectWidget;//����̽�����,��ʾ̽�⵽��ȫ�����ƿ�
	QDialog *m_pSttIecRecordCbWidget;//���뱨�ļ��ӽ����,��ʾ�������ƿ鱨�ĵ�ȫ����Ϣ

};

extern QSttIecRecordMainWidget *g_theSttIecRecordMainWidget;

#endif // SttIecRecordMainWidget_H
