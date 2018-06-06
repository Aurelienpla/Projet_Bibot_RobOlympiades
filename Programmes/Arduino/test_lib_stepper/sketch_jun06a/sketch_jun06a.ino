#include <Stepper.h>

// pour un moteur de 200 pas par tour et brancher sur les broches 2, 3, 4, 5
Stepper moteur(200,4, 5, 9, 10);

void setup()
{
    moteur.setSpeed(30); // 30 tours par minute
    // (rappel : ici le moteur fait 200 pas par tour,
    // on fera donc 6000 pas par minute)
}

void loop()
{
    moteur.step(1000);
    delay(100);
    moteur.step(-1000);
    delay(2000);
}
