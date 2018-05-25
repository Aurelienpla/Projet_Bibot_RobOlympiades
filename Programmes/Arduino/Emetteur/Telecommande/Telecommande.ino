// On charge la librairie VirtualWire afin de pouvoir réaliser une communication
// sans fil via notre émetteur 433MHz.
#include <VirtualWire.h>

// On défini les occurences dont on aura besoin.
#define PIN_LED 13
#define PIN_DATA 6
#define PIN_AUTOMODE 12
#define PIN_FORWARD 8
#define PIN_RIGHT 4
#define PIN_BACKWARD 2
#define PIN_LEFT 7
#define DELAY 250
#define SPEED 1000

// On défini les caractères à envoyer en fonction des actions à entreprendre.
const char *automode = "A"; // Mode automatique
const char *forward = "F"; // Avancer
const char *right = "R"; // Tourner à droite
const char *backward = "B"; // Reculer
const char *left = "L"; // Tourner à gauche

// Initialisation de notre programme,, ne s'exécute qu'une seule fois au démarrage.
void setup()
{

  Serial.begin(9600);
  
  // On défini les entrées qui seront utilisées pour notre bouton poussoir.
  pinMode(PIN_AUTOMODE, INPUT_PULLUP); // Bouton "mode automatique"
  pinMode(PIN_FORWARD, INPUT_PULLUP); // Bouton "avancer"
  pinMode(PIN_BACKWARD, INPUT_PULLUP); // Bouton "reculer"
  pinMode(PIN_RIGHT, INPUT_PULLUP); // Bouton "tourner à droite"
  pinMode(PIN_LEFT, INPUT_PULLUP); // Bouton "tourner à gauche"

  // Bits par seconde (nous pouvons le modifier mais cela modifiera la portée).
  // On choisi 1000bps puisque c'est le meilleur ratio afin d'obtenir une portée
  // conséquente et une bonne qualité de transmission.
  vw_setup(SPEED);

  // On défini l'entrée sur laquelle on reliera la broche DATA de l'émetteur.
  vw_set_tx_pin(PIN_DATA);
}

// Boucle de notre programme, s'exécute en boucle.
void loop()
{

  // Si un appui est détecté sur le bouton "mode automatique".
  if (digitalRead(PIN_AUTOMODE) == LOW)
  {
    Serial.println(automode);
    digitalWrite(PIN_LED, HIGH);
    vw_send((uint8_t *)automode, strlen(automode));
    vw_wait_tx();
    digitalWrite(PIN_LED, LOW);
    delay(DELAY);
  }

  // Si un appui est détecté sur le bouton "avancer".
  else if (digitalRead(PIN_FORWARD) == LOW)
  {
    Serial.println(forward);
    digitalWrite(PIN_LED, HIGH);
    vw_send((uint8_t *)forward, strlen(forward));
    vw_wait_tx();
    digitalWrite(PIN_LED, LOW);
    delay(DELAY);
  }

  // Si un appui est détecté sur le bouton "reculer".
  else if (digitalRead(PIN_BACKWARD) == LOW)
  {
    Serial.println(backward);
    digitalWrite(PIN_LED, HIGH);
    vw_send((uint8_t *)backward, strlen(backward));
    vw_wait_tx();
    digitalWrite(PIN_LED, LOW);
    delay(DELAY);
  }

  // Si un appui est détecté sur le bouton "tourner à droite".
  else if (digitalRead(PIN_RIGHT) == LOW)
  {
    Serial.println(right);
    digitalWrite(PIN_LED, HIGH);
    vw_send((uint8_t *)right, strlen(right));
    vw_wait_tx();
    digitalWrite(PIN_LED, LOW);
    delay(DELAY);
  }

  // Si un appui est détecté sur le bouton "tourner à gauche".
  else if (digitalRead(PIN_LEFT) == LOW)
  {
    Serial.println(left);
    digitalWrite(PIN_LED, HIGH);
    vw_send((uint8_t *)left, strlen(left));
    vw_wait_tx();
    digitalWrite(PIN_LED, LOW);
    delay(DELAY);
  }

}
