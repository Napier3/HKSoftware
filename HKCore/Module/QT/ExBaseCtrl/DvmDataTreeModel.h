#ifndef _QDvmDataTreeModel_H
#define _QDvmDataTreeModel_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>

#include "../../DataMngr/DvmDataset.h"

class QDvmDataTreeModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	QDvmDataTreeModel(CDvmData *pDvmData, QObject *parent = 0);
	virtual ~QDvmDataTreeModel();

	void InitTreeMode();
	void setupModelData(CDvmData *pDvmData);

	QVariant data(const QModelIndex &index, int role) const;
	QVariant data(const QModelIndex &index);
	Qt::ItemFlags flags(const QModelIndex &index) const;
	QVariant headerData(int section, Qt::Orientation orientation,
		int role = Qt::DisplayRole) const;
	QModelIndex index(int row, int column,
		const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

protected:
	QString GetAttrID(const QModelIndex &index);
	QVariant GetAttrValue(const QModelIndex &index) const ;
	QVariant GetAttrValue(const QModelIndex &index, const QString &strAttrID) const ;
	CDvmValue* FindByAttrID(const QModelIndex &index, const QString &strAttrID) const ;

	CDvmData *rootItem;
	QList<QString> m_listHeadTitle;
	QList<QString> m_listColAttrID;
};


#endif //_QDvmDataTreeModel_H
