// On charge la librairie VirtualWire afin de pouvoir réaliser une communication
// sans fil via notre émetteur 433MHz.
#include <VirtualWire.h>

const char *forward = "F";
const char *right = "R";
const char *backward = "B";
const char *left = "L";

// Initialisation de notre programme,, ne s'exécute qu'une seule fois au démarrage.
void setup()
{

  // On défini les entrées qui seront utilisées pour notre bouton poussoir.
  pinMode(2, INPUT_PULLUP);

  // Bits par seconde (nous pouvons le modifier mais cela modifiera la portée).
  // On choisi 1000bps puisque c'est le meilleur ratio afin d'obtenir une portée
  // conséquente et une bonne qualité de transmission.
  vw_setup(1000);

  // On défini l'entrée sur laquelle on reliera la broche DATA de l'émetteur.
  vw_set_tx_pin(3);
  
}

// Boucle de notre programme, s'exécute en boucle.
void loop()
{

  // Si un appui est détecté sur le bouton "".
  if (digitalRead(2) == LOW)
  {
    digitalWrite(9, HIGH);
    vw_send((uint8_t *)forward, strlen(forward));
    vw_wait_tx();
    digitalWrite(9, LOW);
    delay(500);
    //delay(2000);
    //while(digitalRead(2) == HIGH);
  }

}
