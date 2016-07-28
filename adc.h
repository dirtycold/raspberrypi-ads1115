#ifndef ADC_H
#define ADC_H

class ADS1115
{
public:
    ADS1115 ();
    float value (int channel) const;
};

#endif // ADC_H
