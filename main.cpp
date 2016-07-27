#include <QCoreApplication>
#include <QDebug>

#include <adc.h>

int main(/*int argc, char *argv[]*/)
{
    // QCoreApplication a(argc, argv);

    ADC adc;
    for (int i = 0; i < 4; ++i)
    {
        float value = adc.value (i);
        qDebug () << "channel:" << i << "value:" << value;
    }

    return 0;
}
