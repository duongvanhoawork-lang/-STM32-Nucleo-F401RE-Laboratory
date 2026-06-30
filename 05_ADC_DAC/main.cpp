#include "mbed.h"

// Potentiometer connected to pin A0
// A0 on the NUCLEO-F401RE corresponds to PA0 (ADC_IN0)
AnalogIn pot(A0);

// LED connected to pin D6
// D6 on the NUCLEO-F401RE corresponds to PA6 and supports PWM output
PwmOut led(D6);

int main()
{
    // Configure the PWM period to 100 microseconds
    // PWM frequency = 1 / 100us = 10 kHz
    // This frequency is high enough to prevent visible LED flickering
    led.period_us(100);

    while (true)
    {
        // Read the analog value from the potentiometer
        // pot.read() returns a floating-point value between 0.0 and 1.0
        // 0.0 corresponds to 0V
        // 1.0 corresponds to 3.3V
        float value = pot.read();

        // Convert the normalized value into the actual input voltage
        // Assuming the ADC reference voltage is 3.3V
        float voltage = value * 3.3f;

        // Convert the normalized value into a 12-bit ADC reading
        // A 12-bit ADC produces values from 0 to 4095
        int adc_value = (int)(value * 4095.0f);

        // Update the PWM duty cycle
        // led.write() accepts values from 0.0 to 1.0
        // A larger value results in a higher duty cycle
        // A higher duty cycle makes the LED appear brighter
        led.write(value);

        // Wait 10 ms before the next reading
        // This helps reduce noise and provides stable updates
        ThisThread::sleep_for(10ms);
    }
}
