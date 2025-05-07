#include <Arduino.h>
#include <MMFS.h>
#include "AvionicsState.h"
#include "AviEventListener.h"
#include "VoltageSensor.h"

using namespace mmfs;

MAX_M10S m;
DPS310 d;
BMI088andLIS3MDL b;
VoltageSensor vsfc(A0, 330, 220, "Flight Computer Voltage");

Sensor *s[] = {&m, &d, &b, &vsfc};
AvionicsState t(s, sizeof(s) / 4, nullptr);

MMFSConfig a = MMFSConfig()
                   .withBBAsync(true, 50)
                   .withBBPin(LED_BUILTIN)
                   .withBBPin(32)
                   //   .withBuzzerPin(33)
                   .withUsingSensorBiasCorrection(true)
                   .withUpdateRate(5)
                   .withState(&t);
MMFSSystem sys(&a);

AviEventLister listener;

void setup()
{
    sys.init();
}

void loop()
{
    sys.update();
}