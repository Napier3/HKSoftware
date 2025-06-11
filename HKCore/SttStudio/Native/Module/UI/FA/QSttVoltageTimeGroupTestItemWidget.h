#ifndef QSTTVOLTAGETIMEGROUPTESTITEMWIDGET_H
#define QSTTVOLTAGETIMEGROUPTESTITEMWIDGET_H

#include <QWidget>
#include "../Controls/SttCheckBox.h"
#include <QTableWidget>
#include <QPushButton>
#include "../../../Module/DataMngr/DataGroup.h"
#include "../../SttTest/Common/tmt_result_def.h"

class QSttVoltageTimeGroupTestItemWidget : public QWidget
{
	Q_OBJECT

public:
	QSttVoltageTimeGroupTestItemWidget(QWidget *parent = NULL);
	virtual ~QSttVoltageTimeGroupTestItemWidget();

private:
	CDataGroup *m_pVolTimeTypeSecDataGroup;
	QList<QSttCheckBox*> m_pSelcetCheckItemList; // �洢��ѡ����б�
	QTableWidget* m_pVolTimeTypeTestItemTableWidget;//������Ŀ���
	QPushButton *m_pCheckSelBtn;//ȫѡ/���
	QSttCheckBox *m_pRemoteMonitorCheckBox;//ң�ű�λ����
	CString m_strItemID;//��ǰ���ԵĽڵ�·��
	long m_nBinIn[MAX_BINARYIN_COUNT];//�洢��һ�ο�����

public:
	void InitUI();
	void InitTable();
	void InitConnections();
	void InitData(CDataGroup *pParas);
	void StartInit();
	void StopInit();
	void UpdateData(CDataGroup *pParas);
	void UpdateStateTable();//����״̬�������ñ��
	void UpdateResultState( CString strID,const CString &strState );//���²�����Ŀ����״̬һ��
	void ClearResultState();
	void UpdateEventMsg(CEventResult *pCurrEventResult);
	CString FindBinInChange(long *pnNewArr, int size);//�ж��Ƿ��λ

private slots:
	void slot_CheckSelBtnClicked();
	void slot_RemoteMonitorClicked(bool checked);
	void slot_TableWidgetClicked(int row,int col);
	void slot_CheckBoxClicked(bool checked);

};

#endif