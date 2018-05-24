// On charge la librairie VirtualWire afin de pouvoir réaliser une communication
// sans fil via notre récepteur 433MHz.
#include <VirtualWire.h>

// On défini les occurences dont on aura besoin.
#define DIR_RIGHT 3
#define PUL_A_RIGHT 4
#define PUL_B_RIGHT 5
#define DIR_LEFT 8
#define PUL_A_LEFT 9
#define PUL_B_LEFT 10
#define SPEED 200

// On défini les variables dont on aura besoin pour la réception sans fil.
uint8_t buf[VW_MAX_MESSAGE_LEN];
uint8_t buflen = VW_MAX_MESSAGE_LEN;


boolean automode = false;
uint8_t i;

// Initialisation de notre programme,, ne s'exécute qu'une seule fois au démarrage.
void setup()
{
  // Afin de faire les tests, à supprimer dans la version finale.
  Serial.begin(9600);

  // On déclare les sorties.
  pinMode(DIR_RIGHT, OUTPUT);
  pinMode(PUL_A_RIGHT, OUTPUT);
  pinMode(PUL_B_RIGHT, OUTPUT);
  pinMode(DIR_LEFT, OUTPUT);
  pinMode(PUL_A_LEFT, OUTPUT);
  pinMode(PUL_B_LEFT, OUTPUT);

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
  // Si on est en mode manuel.
  if (!automode)
  {
    // Si un message est reçu.
    if (vw_get_message(buf, &buflen))
    {
      // Si on reçoit l'ordre de faire avancer le robot.
      if (char(buf[0]) == 'F' && buflen == 1)
      {
        // Afin de faire les tests, à supprimer dans la version finale.
        Serial.println("Avancer");

        // On défini le sens des moteurs afin de faire avancer le robot.
        forward();

        // On fait à peu près un tour de roue.
        for (i = 0; i < 200; i++)
          moteur(SPEED);
      }

      // Si on reçoit l'ordre de faire reculer le robot.
      else if (char(buf[0]) == 'B' && buflen == 1)
      {
        // Afin de faire les tests, à supprimer dans la version finale.
        Serial.println("Reculer");

        // On défini le sens des moteurs afin de faire avancer le robot.
        backward();

        // On fait à peu près un tour de roue.
        for (i = 0; i < 200; i++)
          moteur(SPEED);
      }

      // Si on reçoit l'ordre de faire tourner le robot à droite.
      else if (char(buf[0]) == 'R' && buflen == 1)
      {
        // Afin de faire les tests, à supprimer dans la version finale.
        Serial.println("Tourner à droite");

        // On défini le sens des moteurs afin de faire avancer le robot.
        turnRight();

        // On fait à peu près un tour de roue.
        for (i = 0; i < 200; i++)
          moteur(SPEED);
      }

      // Si on reçoit l'ordre de faire tourner le robot à gauche.
      else if (char(buf[0]) == 'L' && buflen == 1)
      {
        // Afin de faire les tests, à supprimer dans la version finale.
        Serial.println("Tourner à gauche");

        // On défini le sens des moteurs afin de faire avancer le robot.
        turnLeft();

        // On fait à peu près un tour de roue.
        for (i = 0; i < 200; i++)
          moteur(SPEED);
      }

      // Si on reçoit l'ordre de passer en mode automatique..
      else if (char(buf[0]) == 'A' && buflen == 1)
      {
        // Afin de faire les tests, à supprimer dans la version finale.
        Serial.println("Passage en mode automatique");

        // On active le mode automatique.
        automode = true;
      }
    }
  }

  // Si on est en mode automatique.
  else
  {
    // Si un message est reçu.
    if (vw_get_message(buf, &buflen))
    {
      // Si on reçoit l'ordre de passer en mode automatique.
      if (char(buf[0]) == 'A' && buflen == 1)
      {
        // On active le mode manuel.
        automode = false;
      }
    }

    //
    else ()
    {
      // Si la communication série est disponible.
      if (Serial.available())
      {
        // On récupère le message envoyé par la carte Raspberry Pi.
        message = Serial.read();

        // Si on reçoit l'ordre de faire avancer le robot.
        if (char(message) == 'F')
        {
          // Afin de faire les tests, à supprimer dans la version finale.
          Serial.println("Avancer");

          // On défini le sens des moteurs afin de faire avancer le robot.
          forward();

          // On fait à peu près un tour de roue.
          for (i = 0; i < 200; i++)
            moteur(SPEED);
        }

        // Si on reçoit l'ordre de faire reculer le robot.
        else if (char(message) == 'B')
        {
          // Afin de faire les tests, à supprimer dans la version finale.
          Serial.println("Reculer");

          // On défini le sens des moteurs afin de faire avancer le robot.
          backward();

          // On fait à peu près un tour de roue.
          for (i = 0; i < 200; i++)
            moteur(SPEED);
        }

        // Si on reçoit l'ordre de faire tourner le robot à droite.
        else if (char(message) == 'R')
        {
          // Afin de faire les tests, à supprimer dans la version finale.
          Serial.println("Tourner à droite");

          // On défini le sens des moteurs afin de faire avancer le robot.
          turnRight();

          // On fait à peu près un tour de roue.
          for (i = 0; i < 200; i++)
            moteur(SPEED);
        }

        // Si on reçoit l'ordre de faire tourner le robot à gauche.
        else if (char(message) == 'L')
        {
          // Afin de faire les tests, à supprimer dans la version finale.
          Serial.println("Tourner à gauche");

          // On défini le sens des moteurs afin de faire avancer le robot.
          turnLeft();

          // On fait à peu près un tour de roue.
          for (i = 0; i < 200; i++)
            moteur(SPEED);
        }
      }
    }
  }
}

// Fonction permettant de faire tourner les moteurs.
void moteur(int vitesse)
{

  digitalWrite(PUL_A_RIGHT, HIGH);
  digitalWrite(PUL_A_LEFT, HIGH);
  digitalWrite(PUL_B_RIGHT, LOW);
  digitalWrite(PUL_B_LEFT, LOW);

  delayMicroseconds(vitesse);

  digitalWrite(PUL_A_RIGHT, HIGH);
  digitalWrite(PUL_A_LEFT, HIGH);
  digitalWrite(PUL_B_RIGHT, HIGH);
  digitalWrite(PUL_B_LEFT, HIGH);

  delayMicroseconds(vitesse);

  digitalWrite(PUL_A_RIGHT, LOW);
  digitalWrite(PUL_A_LEFT, LOW);
  digitalWrite(PUL_B_RIGHT, HIGH);
  digitalWrite(PUL_B_LEFT, HIGH);

  delayMicroseconds(vitesse);

  digitalWrite(PUL_A_RIGHT, LOW);
  digitalWrite(PUL_A_LEFT, LOW);
  digitalWrite(PUL_B_RIGHT, LOW);
  digitalWrite(PUL_B_LEFT, LOW);

  delayMicroseconds(vitesse);
}

// Fonction permettant de définir le sens des moteurs afin de faire avancer le robot.
void forward()
{
  digitalWrite(DIR_RIGHT, HIGH);
  digitalWrite(DIR_LEFT, LOW);
}

// Fonction permettant de définir le sens des moteurs afin de faire reculer le robot.
void backward()
{
  digitalWrite(DIR_RIGHT, LOW);
  digitalWrite(DIR_LEFT, HIGH);
}

// Fonction permettant de définir le sens des moteurs afin de faire tourner le robot vers la gauche.
void turnLeft()
{
  digitalWrite(DIR_RIGHT, HIGH);
  digitalWrite(DIR_LEFT, HIGH);
}

// Fonction permettant de définir le sens des moteurs afin de faire tourner le robot vers la droite.
void turnRight()
{
  digitalWrite(DIR_RIGHT, LOW);
  digitalWrite(DIR_LEFT, LOW);
}
