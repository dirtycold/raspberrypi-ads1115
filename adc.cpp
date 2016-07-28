#include "adc.h"

#include <ads1115.h>
#include <wiringPi.h>

#include <QDebug>

// Just works, I don't know why ;-)
static const int base = 100;

ADS1115::ADS1115()
{
    ads1115Setup (base, 0x48);
}

float ADS1115::value(int channel) const
{
    float voltage (NAN);

    do
    {
        if (channel < 0 || channel > 3)
        {
            qCritical () << "channel invalid.";
            break;
        }

        float value = (int16_t) analogRead (base + channel);
        voltage = (float) value * 4.096 / 32768.0;

        qDebug () << "value:" << value << "voltage:" << voltage;
    }
    while (false);

    return voltage;
}
