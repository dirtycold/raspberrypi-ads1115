#include <QCoreApplication>
#include <QThread>
#include <QDebug>

#include <adc.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ADS1115 adc;


    for (int i = 0; i < 4; ++i)
    {
        int count = 5;
        while (count --)
        {
            float value = adc.value (i);
            qDebug () << "channel:" << i << "value:" << value;
        }
        a.thread ()->msleep (500);
    }

    return 0;
}
