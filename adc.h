#ifndef ADC_H
#define ADC_H

class ADC
{
public:
    ADC ();
    float value (int channel) const;

private:
    class ADCPrivate;
    ADCPrivate *p;
};

#endif // ADC_H
