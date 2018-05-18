int PULd1=7; 
int PULd2=6;
int DIRd=5;

int PULg1=10; 
int PULg2=9;
int DIRg=8;

int HumiditeAna=0;

void setup() {
  Serial.begin(9600);
  
  pinMode (PULd1, OUTPUT);
  pinMode (PULd2, OUTPUT);
  pinMode (DIRd, OUTPUT);

  pinMode (PULg1, OUTPUT);
  pinMode (PULg2, OUTPUT);
  pinMode (DIRg, OUTPUT);

  pinMode(HumiditeAna, INPUT);

}

void moteur(int vitesse)
{    
    digitalWrite(PULd1,HIGH);
    digitalWrite(PULd2,LOW);

    delayMicroseconds(vitesse);
    
    digitalWrite(PULd1,HIGH);
    digitalWrite(PULd2,HIGH);

    delayMicroseconds(vitesse);
    
    digitalWrite(PULd1,LOW);
    digitalWrite(PULd2,HIGH);
  
    delayMicroseconds(vitesse);
    
    digitalWrite(PULd1,LOW);
    digitalWrite(PULd2,LOW);

    delayMicroseconds(vitesse); 
}

void moteur2(int vitesse)
{    
    digitalWrite(PULg1,HIGH);
    digitalWrite(PULg2,LOW);
    
    delayMicroseconds(vitesse);
    
    digitalWrite(PULg1,HIGH);
    digitalWrite(PULg2,HIGH);
   
    delayMicroseconds(vitesse);
        
    digitalWrite(PULg1,LOW);
    digitalWrite(PULg2,HIGH);
    
    delayMicroseconds(vitesse);

    digitalWrite(PULg1,LOW);
    digitalWrite(PULg2,LOW);
    
    delayMicroseconds(vitesse); 
}

void avancer()
{
  digitalWrite(DIRd,HIGH);
  digitalWrite(DIRg,LOW);

}

void reculer()
{
   digitalWrite(DIRd,LOW);
   digitalWrite(DIRg,HIGH);
}

void gauche()
{
   digitalWrite(DIRd,HIGH);
   digitalWrite(DIRg,HIGH);
}

void droite()
{   
   digitalWrite(DIRd,LOW);
   digitalWrite(DIRg,LOW);
        
}


void diagdroite()
{   
   digitalWrite(DIRd,LOW);
   digitalWrite(DIRg,LOW);
        
}

void stopp()
{
  digitalWrite(PULd1,LOW);
  digitalWrite(PULd2,LOW);
}


int message, test, Hsol;
long cpt=0, valeur=0, Hsoltot=0;

void loop() 
{
////////////////////////////////////////////////////////////////
/*            communication serie raspbery                    */  
////////////////////////////////////////////////////////////////
if (Serial.available())  
  {
    message = Serial.read()-'0';  // on soustrait le caractère 0, qui vaut 48 en ASCII
    
    if(message>0)
    {
      test = message;
      //Serial.println(message);
      //Serial.println(test); 
      stopp();
      delay(50);
    }
      
  }

////////////////////////////////////////////////////////////////
/*            Hydrométrie                                     */  
////////////////////////////////////////////////////////////////  
if (cpt==10)
{
   //Serial.println("passage hydro");
   cpt=0;
   for(int a=0;a<10;a++)
   {
     //Serial.println(a);
     Hsol = analogRead(HumiditeAna); 
     // Serial.println(Hsol);
     Hsoltot+=Hsol;
     delay(1000);
   }
   valeur=Hsoltot/10;
   //Serial.print("calcule hydro ");
   Serial.println(valeur);
   Hsoltot=0;
  }

////////////////////////////////////////////////////////////////
/*            mouvement robot                                 */  
////////////////////////////////////////////////////////////////
else
{
switch (test) 
  {
  case 1:  
    avancer();
    for(int i=0;i<200;i++){
    moteur(200);moteur2(200);
    }
    // Serial.println("avance");
    cpt++;
    Serial.println(cpt);
  break;

  case 2:
    reculer();
    for(int i=0;i<200;i++){
    moteur(200);moteur2(200);
    }
     //Serial.println("recule");
     cpt++;
     Serial.println(cpt);
  break; 
   
  case 3:
    gauche();
    for(int i=0;i<200;i++){
    moteur(200);moteur2(200);
    }
     //Serial.println("gauche");
     cpt++;
     Serial.println(cpt);
  break;

  case 4:
    droite();
    for(int i=0;i<200;i++){
    moteur(200);moteur2(200);
    }
     //Serial.println("droite");
     cpt++;
     Serial.println(cpt);
  break;

    }
  }
}

