#ifndef ADC_H
#define ADC_H

class ADC
{
public:
    ADC ();
    ~ADC ();
    float value () const;

private:
    class ADCPrivate;
    ADCPrivate *p;
};

#endif // ADC_H
