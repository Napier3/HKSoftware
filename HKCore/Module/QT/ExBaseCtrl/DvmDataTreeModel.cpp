#include <QtGui>

#include "DvmDataTreeModel.h"

QDvmDataTreeModel::QDvmDataTreeModel(CDvmData *pDvmData, QObject *parent)
: QAbstractItemModel(parent)
{
	rootItem = pDvmData;
	InitTreeMode();
}

QDvmDataTreeModel::~QDvmDataTreeModel()
{
	//delete rootItem;
}

void QDvmDataTreeModel::InitTreeMode()
{
	m_listHeadTitle << "项目" << "实际值"<<  "原始值";
	m_listColAttrID << "name" << "$actual"<<  "$stand";
}

void QDvmDataTreeModel::setupModelData(CDvmData *pDvmData)
{
	rootItem = pDvmData;
}

int QDvmDataTreeModel::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
	{
		CExBaseList *p = (CExBaseList*)parent.internalPointer();

		if (p == NULL)
		{
			return 1;
		}

		return 3;
	}	
	else
	{
		return 3;//m_listHeadTitle.size();
	}	
}

QString QDvmDataTreeModel::GetAttrID(const QModelIndex &index)
{
	return m_listColAttrID.at(index.column());
}

QVariant QDvmDataTreeModel::GetAttrValue(const QModelIndex &index) const
{
	CString strAttrID = m_listColAttrID.at(index.column());
	return GetAttrValue(index, strAttrID);
}

QVariant QDvmDataTreeModel::GetAttrValue(const QModelIndex &index, const QString &strAttrID) const
{
	QVariant valRet;

	if (index.column() == 0)
	{
		CDvmValue *p = (CDvmValue*)index.internalPointer();
		valRet = p->m_strName;
	}
	else
	{
		CDvmValue *pFind = FindByAttrID(index, strAttrID);

		if (pFind != NULL)
		{
			valRet = pFind->m_strValue;
		}
	}

	return valRet;
}

CDvmValue* QDvmDataTreeModel::FindByAttrID(const QModelIndex &index, const QString &strAttrID) const
{
	CExBaseObject *p = (CExBaseObject*)index.internalPointer();

	if (p == NULL)
	{
		return NULL;
	}

	long nClassID = p->GetClassID();
	CDvmValue *pFind = NULL;

	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		CDvmData *pData = (CDvmData*)p;
		pFind = pData->FindByID_MmsAttr(strAttrID);
	}
	else if (nClassID == DVMCLASSID_CDVMVALUE)
	{
		CDvmValue *pValue = (CDvmValue*)p;
		pFind = pValue->FindByID_MmsAttr(strAttrID);
	}

	return pFind;
}

QVariant QDvmDataTreeModel::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	CExBaseList *item = static_cast<CExBaseList*>(index.internalPointer());

	if (role == Qt::DisplayRole)
	{
		return GetAttrValue(index);
	}
	else if(role == Qt::TextColorRole)
	{//通道多了或少了，标红
// 		if()
// 		{
// 			return QVariant(QColor("#FF0000"));
// 		}
		//if(index.column() == 3)
		{//数据与scd文件不一致标红
			QVariant v = GetAttrValue(index, "$rslt");

			if(v.toInt() == 0)
			{
				return QVariant(QColor("#FF0000"));
			}
		}
	}

	return QVariant();
}

QVariant QDvmDataTreeModel::data( const QModelIndex &index )
{
	if (!index.isValid())
		return QVariant();

	CDvmValue *pValue = (CDvmValue *)index.internalPointer();

	if (index.column() == 0)
	{
		return pValue->m_strName;
	}
	else
	{
		return GetAttrValue(index);
	}
}

Qt::ItemFlags QDvmDataTreeModel::flags(const QModelIndex &index) const
{
	if (!index.isValid())
		return 0;

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QVariant QDvmDataTreeModel::headerData(int section, Qt::Orientation orientation,
							   int role) const
{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		return m_listHeadTitle.at(section);
	}
	else if(role == Qt::TextColorRole)
	{
		return QVariant(QColor("#00FF00"));
	}

	return QVariant();
}

QModelIndex QDvmDataTreeModel::index(int row, int column, const QModelIndex &parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	CExBaseList *parentItem = NULL;

	if (!parent.isValid())
		parentItem = rootItem;
	else
		parentItem = static_cast<CExBaseList*>(parent.internalPointer());

	CExBaseList *childItem = (CExBaseList*)parentItem->GetAtIndex(row);

	if (childItem != NULL)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

QModelIndex QDvmDataTreeModel::parent(const QModelIndex &index) const
{
	if (!index.isValid())
		return QModelIndex();

	CExBaseList *childItem = static_cast<CExBaseList*>(index.internalPointer());
	CExBaseList *parentItem = (CExBaseList*)childItem->GetParent();

	if (parentItem == rootItem)
		return QModelIndex();

	return createIndex(parentItem->m_dwItemData, 0, parentItem);
}

int QDvmDataTreeModel::rowCount(const QModelIndex &parent) const
{
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
	{
		return rootItem->GetCount();
	}
	else
	{
		CDvmValue *pValue = static_cast<CDvmValue*>(parent.internalPointer());

		if (pValue->m_strDataType == "STRUCT")
		{//一个数据
			return 1;
		}
		else
		{
			return pValue->GetCount();
		}
	}
}
