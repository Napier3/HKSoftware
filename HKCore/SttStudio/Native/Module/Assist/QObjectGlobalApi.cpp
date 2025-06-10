#include "stdafx.h"
#include "QObjectGlobalApi.h"



void test_view_superClass(QObject *obj)
{
    //qDebug() << obj->objectName() + ": all superClass";
    const QMetaObject *mo = &obj->staticMetaObject;

    if (obj->inherits("QDialog"))
    {
        // qDebug() << "inherits(QDialog)";
    }

    //QStack<QString> parentClasses;
    while (mo != 0)
    {
     // qDebug() << mo->className();
      mo = mo->superClass();
    }
}

void test_view_parent(QObject *objCurr)
{
    QObject *pParent = objCurr->parent();
    QString strName2 = objCurr->objectName();
   // qDebug() << strName2;

    test_view_superClass(objCurr);

    while (pParent != 0)
    {
        test_view_superClass(pParent);

        //qDebug() << parentClasses;
        pParent = pParent->parent();
    }


}

QObject* qobj_findChild(QObject* parent, const char* typeName, const QMetaObject* meta, const QString& name)
{
  const QObjectList &children = parent->children();
  int i;

  for (i = 0; i < children.size(); ++i)
  {
    QObject* obj = children.at(i);

    if (!obj)
      return NULL;

    // Skip if the name doesn't match.
    if (!name.isNull() && obj->objectName() != name)
      continue;

    if ((typeName && obj->inherits(typeName)) ||
      (meta && meta->cast(obj)))
      return obj;
  }

  for (i = 0; i < children.size(); ++i) 
  {
    QObject* obj = qobj_findChild(children.at(i), typeName, meta, name);

    if (obj != NULL)
      return obj;
  }

  return NULL;
}

QObject* qobj_findChild(QObject* parent, const char* typeName, const QString& name)
{
	const QObjectList &children = parent->children();
	int i;
	QString strObjNme;

	for (i = 0; i < children.size(); ++i)
	{
		QObject* obj = children.at(i);

		if (!obj)
			return NULL;

		// Skip if the name doesn't match.
		strObjNme = obj->objectName();

		if (!name.isNull() &&  strObjNme != name)
			continue;

		if ( typeName && obj->inherits(typeName) )
			return obj;
	}

	for (i = 0; i < children.size(); ++i) 
	{
		QObject* obj = qobj_findChild(children.at(i), typeName, name);

		if (obj != NULL)
			return obj;
	}

	return NULL;
}
