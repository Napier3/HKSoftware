#ifndef SEQUENCEGRADIENTESTIMATEDLG_H
#define SEQUENCEGRADIENTESTIMATEDLG_H

#include "../../SttTest/Common/Sequence/tmt_sequence_gradient_test.h"
#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>

class SequenceGradientEstimateGrid : public QTableWidget
{
	Q_OBJECT
public:
	SequenceGradientEstimateGrid(int rows, int columns, QWidget* parent);
	~SequenceGradientEstimateGrid();

	virtual void InitGrid();//��ʼ����ͷ
	virtual void EnableRow(long nIndex, BOOL bEnabled = TRUE);//����ĳ���е�ʹ��״̬
	virtual void InitData(tmt_GradientParasEx* pParas);//���ݽṹ���е���ֵ���Ա����и��е�ֵ���г�ʼ��
	void ComboxModelStyle(QComboBox *pCombox);//���������ʼ��
	void CbbErrorType(int nIndex, CString strText);//�������������ı༭״̬

private:
	QComboBox* NewErrorType();//�����µ��������������Լ������������)
	QComboBox* AbsErrorType();//�����������������
	tmt_GradientParasEx* m_pParas;

protected slots:
	void slot_OnCellChanged(int row,int col);
	void slot_cmbErrorChanged(const QString& strText);

};

class SequenceGradientEstimateDlg : public QDialog
{
	Q_OBJECT
private:
	tmt_GradientParasEx* m_pParas;
	SequenceGradientEstimateGrid* m_pGrid;

public:
	SequenceGradientEstimateDlg(tmt_GradientParasEx* pParas, QWidget* parent = NULL);
	virtual ~SequenceGradientEstimateDlg();

public:
	void InitUI();

protected slots:
	void slot_btnOK_Clicked();
	void slot_btnCancel_Clicked();

};

#endif