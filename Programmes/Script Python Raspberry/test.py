#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Le Raspbery Pi envoie des messages à l'Arduino

import serial  # bibliothèque permettant la communication série
import time    # pour le délai d'attente entre les messages
import xlrd

from xlwt import Workbook, Formula
 
path = r"/home/ubuntu/Desktop/testcommRaspiArduino/mapping.xls"

classeur = Workbook()
feuille = classeur.add_sheet("OCB")

ser = serial.Serial('/dev/ttyACM0', 9600)
compteur = 1
time.sleep(4)   
h=0
compt=0

def fonctionxls(hydro, compt2):
        feuille.write(compt2, 0, hydro)
        print(compt)
        print(hydro)
        classeur.save(path)
        

while h<100:     # boucle répétée jusqu'à l'interruption du programme
        
        if compteur ==1:
                ser.write('1'.encode('utf-8'))
        if compteur == 11:
                ser.write('2'.encode('utf-8'))
      
      
        donnee=ser.readline()
        print(donnee.decode('UTF-8'))
        if donnee.decode('UTF-8') == '10\r\n':
                donnee2=ser.readline()  #on affiche la réponse
                donnee3=donnee2.decode('UTF-8')
                print(donnee3)
                fonctionxls(donnee3,compt)
                compt=compt+1
                
                
                
        #print("increment compteur")
        compteur=compteur+1
        #print(compteur)
        if compteur == 22:
                compteur = 1
        h=h+1
        
classeur.save(path)
#print u"Fichier créé: {}".format(path)
