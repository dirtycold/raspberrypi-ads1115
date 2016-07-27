#include <QCoreApplication>

#include <adc.h>

int main(/*int argc, char *argv[]*/)
{
    // QCoreApplication a(argc, argv);

    ADC adc;
    for (int i = 0; i < 5; ++i)
    {
        adc.value ();
    }

    return 0;
}
