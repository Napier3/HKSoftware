#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    long k = 0;
    for (k=0; k<100; k++)
    {
        qDebug() << k;
        //QThread::msleep(1000);
    }
    
    return a.exec();
}

