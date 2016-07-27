#include "adc.h"

/*
 * Based on code from:
 *
 * ADS1115 4-Channel ADC Uses I2C with Raspberry Pi
 * http://www.bristolwatch.com/rpi/ads1115.html
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <linux/i2c-dev.h>

#include <QDebug>

class ADC::ADCPrivate
{
    friend class ADC;

    int file;
    int value;
    uint8_t writeBuffer [3];
    uint8_t readBuffer [2];
    float floatValue;

    const int address = 0x48;
    const float voltsPerStep = 4.096 / 32768.0;
};

ADC::ADC()
    : p (new ADCPrivate)
{
    do
    {
        if ((p->file = open ("/dev/i2c-1", O_RDWR)) < 0)
        {
            qDebug () << "opening device failed.";
            break;
        }

        if (ioctl (p->file, I2C_SLAVE, p->address) < 0)
        {
            qDebug () << "address invalid.";
            break;
        }

        p->writeBuffer [0] = 1;
        p->writeBuffer [1] = 0b11000010;
        p->writeBuffer [2] = 0b10000101;

        if (write (p->file, p->writeBuffer, 3) != 3)
        {
            qDebug () << "writing register 1 failed.";
            break;
        }

        sleep (1);
    }

    while (false);
}

ADC::~ADC()
{
   p->writeBuffer [0] = 1;
   p->writeBuffer [1] = 0b11000011;
   p->writeBuffer [2] = 0b10000101;

   if (write (p->file, p->writeBuffer, 3) != 3)
   {
       qDebug () << "writing register 1 failed.";
       // break;
   }
   else
   {
       close (p->file);
   }

   delete p;
}

float ADC::value() const
{
    float value (0);
    do
    {
        if (read (p->file, p->readBuffer, 2) != 2)
        {
            qDebug () << "reading conversion failed.";
            break;
        }

        p->value = p->readBuffer [0] << 8 | p->readBuffer [1];

        if (p->value < 0)
        {
            p->value = 0;
        }

        p->floatValue = p->value * p->voltsPerStep;

        qDebug () << "conversion:" << p->value << "value:" << p->floatValue;

        value = p->floatValue;
        sleep (1);
    }
    while (false);

    return value;
}
