#include <periodic_led.h>

/****************************************************
 * PeriodicLed
 ****************************************************/

PeriodicLed::PeriodicLed(AnalogOutput *output, float amplitude, unsigned long period)
    : output(output),
      state(LedState::UNINITIALIZED),
      amplitude(amplitude),
      period(period),
      start_time(0) {}

const float PeriodicLed::get_amplitude()
{
    return amplitude;
}

const unsigned long PeriodicLed::get_period()
{
    return period;
}

const unsigned long PeriodicLed::get_start_time()
{
    return start_time;
}

const float PeriodicLed::get_output(unsigned long time)
{
    return 0;
}

const LedState PeriodicLed::get_state()
{
    return state;
}

void PeriodicLed::init()
{
    if (!output->initialize())
    {
        return;
    }

    state = LedState::READY;
}

void PeriodicLed::turn_on()
{
    if (state == LedState::UNINITIALIZED)
    {
        return;
    }

    state = LedState::RUNNING;
    start_time = millis();
}

void PeriodicLed::turn_off()
{
    if (state == LedState::UNINITIALIZED)
    {
        return;
    }

    state = LedState::READY;
}

const void PeriodicLed::display()
{
    unsigned long elapsedTime = millis() - get_start_time();
    unsigned long periodTime = elapsedTime % get_period();
    float brightness = get_output(periodTime);

    // Sets the LED output to `brightness` if RUNNING, or to 0 if READY. No-ops otherwise.
    switch (state)
    {
    case LedState::READY:
        output->set_value(0);
        break;
    case LedState::RUNNING:
        output->set_value(brightness);
        break;
    case LedState::UNINITIALIZED:
    default:
        break;
    }
}

/****************************************************
 * ConstantLed
 ****************************************************/

ConstantLed::ConstantLed(AnalogOutput *output, float amplitude, unsigned long period) : PeriodicLed(output, amplitude, period) {}

// y(t) = A
const float ConstantLed::get_output(unsigned long time)
{
    return get_amplitude();
}

/****************************************************
 * RectangularLed
 ****************************************************/

RectangularLed::RectangularLed(AnalogOutput *output, float amplitude, unsigned long period, unsigned long dutyCycle)
    : PeriodicLed(output, amplitude, period),
      _dutyCycle(dutyCycle) {}

const unsigned long RectangularLed::getDutyCycle()
{
    return _dutyCycle;
}

// y(t) = {A if t < D, 0 otherwise}
const float RectangularLed::get_output(unsigned long time)
{
    float output = time < getDutyCycle() ? get_amplitude() : 0;
    return output;
}

/****************************************************
 * SinusoidalLed
 ****************************************************/

SinusoidalLed::SinusoidalLed(AnalogOutput *output, float amplitude, unsigned long period) : PeriodicLed(output, amplitude, period) {}

// y(t) = 1/2 A (sin(2 pi t / T) + 1)
const float SinusoidalLed::get_output(unsigned long time)
{
    float output = get_amplitude() * (sin(2 * time * PI / get_period()) + 1) / 2;
    return output;
}

/****************************************************
 * TriangularLed
 ****************************************************/

TriangularLed::TriangularLed(AnalogOutput *output, float amplitude, unsigned long period) : PeriodicLed(output, amplitude, period) {}

// y(t) = A |t - 1/2 * T| / T
const float TriangularLed::get_output(unsigned long time)
{
    return get_amplitude() * abs(time - get_period() / 2.0) / get_period();
}

/****************************************************
 * SawToothLed
 ****************************************************/

SawToothLed::SawToothLed(AnalogOutput *output, float amplitude, unsigned long period) : PeriodicLed(output, amplitude, period) {}

// y(t) = A t / T
const float SawToothLed::get_output(unsigned long time)
{
    float output = get_amplitude() * time / get_period();
    return output;
}
