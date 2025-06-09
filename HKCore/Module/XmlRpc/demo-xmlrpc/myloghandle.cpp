#include "stdafx.h"

#include "myloghandle.h"

MyLogHandle::MyLogHandle()
{

}

void MyLogHandle::log(int level, const char* msg)
{
	TRACE("%s\r\n", msg);
//    qDebug()<<msg;
}
