// On charge la librairie VirtualWire afin de pouvoir réaliser une communication
// sans fil via notre émetteur 433MHz.
#include <VirtualWire.h>

// On défini les caractères à envoyer en fonction des actions à entreprendre.
const char *forward = "F"; // Avancer
const char *right = "R"; // Tourner à droite
const char *backward = "B"; // Reculer
const char *left = "L"; // Tourner à gauche

// Initialisation de notre programme,, ne s'exécute qu'une seule fois au démarrage.
void setup()
{

  // On défini les entrées qui seront utilisées pour notre bouton poussoir.
  pinMode(12, INPUT_PULLUP); // Bouton "avancer"
  pinMode(2, INPUT_PULLUP); // Bouton "reculer"
  pinMode(4, INPUT_PULLUP); // Bouton "tourner à droite"
  pinMode(7, INPUT_PULLUP); // Bouton "tourner à gauche"

  // Bits par seconde (nous pouvons le modifier mais cela modifiera la portée).
  // On choisi 1000bps puisque c'est le meilleur ratio afin d'obtenir une portée
  // conséquente et une bonne qualité de transmission.
  vw_setup(1000);

  // On défini l'entrée sur laquelle on reliera la broche DATA de l'émetteur.
  vw_set_tx_pin(6);
  
}

// Boucle de notre programme, s'exécute en boucle.
void loop()
{

  // Si un appui est détecté sur le bouton "avancer".
  if (digitalRead(12) == LOW)
  {
    digitalWrite(13, HIGH);
    vw_send((uint8_t *)forward, strlen(forward));
    vw_wait_tx();
    digitalWrite(13, LOW);
    delay(50);
  }

  // Si un appui est détecté sur le bouton "reculer".
  else if (digitalRead(2) == LOW)
  {
    digitalWrite(13, HIGH);
    vw_send((uint8_t *)backward, strlen(backward));
    vw_wait_tx();
    digitalWrite(13, LOW);
    delay(50);
  }

  // Si un appui est détecté sur le bouton "tourner à droite".
  else if (digitalRead(4) == LOW)
  {
    digitalWrite(13, HIGH);
    vw_send((uint8_t *)right, strlen(right));
    vw_wait_tx();
    digitalWrite(13, LOW);
    delay(50);
  }

  // Si un appui est détecté sur le bouton "tourner à gauche".
  else if (digitalRead(7) == LOW)
  {
    digitalWrite(13, HIGH);
    vw_send((uint8_t *)left, strlen(left));
    vw_wait_tx();
    digitalWrite(13, LOW);
    delay(50);
  }

}
