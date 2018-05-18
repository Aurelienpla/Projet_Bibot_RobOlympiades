import xlrd
 
from xlwt import Workbook, Formula
 
path = r"/home/ubuntu/Desktop/testcommRaspiArduino/mapping.xls"
 
# On créer un "classeur"
classeur = Workbook()
# On ajoute une feuille au classeur
feuille = classeur.add_sheet("OCB")
 
# Ecrire "1" dans la cellule à la ligne 0 et la colonne 0
feuille.write(0, 0, 1)
# Ecrire "2" dans la cellule à la ligne 0 et la colonne 1
feuille.write(0, 1, 2)
# Ecrire une formule dans la cellule à la ligne 0 et la colonne 2
# qui va additioner les deux autres cellules
feuille.write(0, 2, Formula('A1+B1'))
 
# Ecriture du classeur sur le disque
classeur.save(path)
 
#print u"Fichier créé: {}".format(path)
