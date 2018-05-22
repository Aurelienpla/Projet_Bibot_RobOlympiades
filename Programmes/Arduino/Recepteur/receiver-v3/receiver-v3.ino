// On charge la librairie VirtualWire afin de pouvoir réaliser une communication
// sans fil via notre récepteur 433MHz.
#include <VirtualWire.h>

// On défini les occurences dont on aura besoin.
#define PUL_A_RIGHT 7
#define PUL_B_RIGHT 6
#define DIR_RIGHT 6
#define PUL_A_LEFT 10
#define PUL_B_LEFT 9
#define DIR_LEFT 8

// On défini les variables dont on aura besoin pour la réception sans fil.
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;
uint8_t i;

// Initialisation de notre programme,, ne s'exécute qu'une seule fois au démarrage.
void setup()
{
  // Afin de faire les tests, à supprimer dans la version finale.
  Serial.begin(9600);

  // On déclare les sorties.
  pinMode(PUL_A_RIGHT, OUTPUT);
  pinMode(PUL_B_RIGHT, OUTPUT);
  pinMode(DIR_RIGHT, OUTPUT);
  pinMode(PUL_A_LEFT, OUTPUT);
  pinMode(PUL_B_LEFT, OUTPUT);
  pinMode(DIR_LEFT, OUTPUT);

  // Bits par seconde (nous pouvons le modifier mais cela modifiera la portée).
  // On choisi 1000bps puisque c'est le meilleur ratio afin d'obtenir une portée
  // conséquente et une bonne qualité de transmission.
  vw_setup(1000);

  // On défini l'entrée sur laquelle on reliera la broche DATA du récepteur.
  vw_set_rx_pin(2);

  // On démarre la réception sans fil.
  vw_rx_start();
}

// Boucle de notre programme, s'exécute en boucle.
void loop()
{

  // Si un message est reçu.
  if (vw_get_message(buf, &buflen))
  {
    // Si on reçoit l'ordre de faire avancer le robot.
    if (char(buf[0]) == 'F' && buflen == 1)
    {
      // Afin de faire les tests, à supprimer dans la version finale.
      Serial.println("Avancer");
      
      // Ajouter ici les actions à effectuer sur les moteurs.
    }

    // Si on reçoit l'ordre de faire avancer le robot.
    else if (char(buf[0]) == 'B' && buflen == 1)
    {
      // Afin de faire les tests, à supprimer dans la version finale.
      Serial.println("Reculer");
      
      // Ajouter ici les actions à effectuer sur les moteurs.
    }

    // Si on reçoit l'ordre de faire tourner à droite le robot.
    else if (char(buf[0]) == 'R' && buflen == 1)
    {
      // Afin de faire les tests, à supprimer dans la version finale.
      Serial.println("Tourner à droite");
      
      // Ajouter ici les actions à effectuer sur les moteurs.
    }

    // Si on reçoit l'ordre de faire tourner à gauche le robot.
    else if (char(buf[0]) == 'L' && buflen == 1)
    {
      // Afin de faire les tests, à supprimer dans la version finale.
      Serial.println("Tourner à gauche");
      
      // Ajouter ici les actions à effectuer sur les moteurs.
    }
    
  }
}

// Fonction permettant de définir les sens des moteurs afin de faire avancer le robot.
void forward()
{
  digitalWrite(DIR_RIGHT, HIGH);
  digitalWrite(DIR_LEFT, LOW);
}

// Fonction permettant de définir les sens des moteurs afin de faire reculer le robot.
void backward()
{
   digitalWrite(DIR_RIGHT, LOW);
   digitalWrite(DIR_LEFT, HIGH);
}

// Fonction permettant de définir les sens des moteurs afin de faire tourner à gauche le robot.
void turnLeft()
{
   digitalWrite(DIR_RIGHT, HIGH);
   digitalWrite(DIR_LEFT, HIGH);
}

// Fonction permettant de définir les sens des moteurs afin de faire tourner à droite le robot.
void turnRight()
{   
   digitalWrite(DIR_RIGHT, LOW);
   digitalWrite(DIR_LEFT, LOW);
        
}
