//QObjectGlobalApi.h
#ifndef _QObjectGlobalApi_H__
#define _QObjectGlobalApi_H__


QObject* qobj_findChild(QObject* parent, const char* typeName, const QMetaObject* meta, const QString& name);
QObject* qobj_findChild(QObject* parent, const char* typeName, const QString& name);


#endif//_QObjectGlobalApi_H__
