===========================================================================================
HISTORIQUE DU LOGICIEL IMAGE
-avant 2012 : logiciel IMAGE_EII : logiciel maison INSA-INFO/EII (Ivan Leplumey?)
destin� � l'enseignement : en C sous Visual sudio 2005
am�lior� au cours du temps par stagiaires et enseignants (V�ronique Coat, Olivier Deforges,...)

-ann�e 2012-2013 : projet 4INFO encad� par Marie Babel
�tudiants : Benoit Averty, Samuel Babin, Matthieu Berg�re, Thomas Letan, Sacha Percot-T�tu, Florian Teyssier
objectif : interface graphique (QT) + librairie Imagein (C++) : bien con�u et g�n�rique
r�sultat : librairie DETIQ-T

-�t� 2013 : stage �t� Sacha Percot
objectif : refactoring IMAGE_EII sur la base du projet
r�alisation : logiciel EIIMAGE int�grant Imagein et ajout de tous les menus de IMAGE_EII
en utilisant le code C existant pour les algos + principe des plugin

-rentr�e 2013 : EIIMAGE utilis� en TP en EII
pb : perte sources correspondant � l'exe utilis� en TP

-hivers 2014-2015 : am�lioration par Antoine Lorence, Ing� de recherche CDD
synchronisation souce/exe
correction de plusieurs bug
compilation sous CMake
d�pot sous GitHub
changement de nom en ImageINSA (pour utilisation en dehors de l'INSA, � l'�tranger)

-Et� 2016 : stage de Antoine Pazat:
des bugs corrig�s
am�liorations
pb: ne compile pas sous windows / pas de doc ormi rapprot tr�s succint

-automne 2016 : patch par Alexandre Sanchez
(en raison modif de la version du compilateur de code-blocks)

-printemps 2017 : compilation sous windows + cr�ation environnement de dvt/compilatin
sur machine virtuelle par Alexandre Sanchez 

-�t� 2017 : stage 3INFO de Quentin Bigot :
correction am�lioration des fonctionnalit�s + mode d'emploi compilation sur
machine virtuelle

-3 octobre 2017 : compilation de la verison TP-2017-2018 par Luce sur la machine virtuelle
32 bits et utilisation en TP COTR automne 2017

-d�cembre 2017 : utilisation ancienne version des squelettes plugin car la nouvelle version ne fonctionne plus

TODO : 
-plugin : identifier version � jour et voir lien avec le r�pertoire plugin dans les r�pertoire source de ImageINSA (Luce)
-machine virtuelle : nettoyage des r�pertoires sur la machine virtuelle (Alex)

-installation environnement d�veloppement sur machine virtuelle 64 bits, avec login TestingAdmin, 
en suivant le mode d'emploi de Antoine Laurence (GitHub)
-mise-�-jour documentation de l'installation de la machine virtuelle
-compilation avec login Tesing, sur machine virtuelle en 64 bits 
-mise � jour du mode d'emploi de Quentin Bigot
-github : merge de la branche qbigo sur le master
-cr�er les zip (sources, exe, trames-plugin) avec la version du master
-faire un m�canisme/processus (script?) de cr�ation de ces zip avec tag de la date de cr�ation
-r�flexion sur l'archivage long terme pour maintenance (mise-�-jour r�guli�re du logiciel)
�lements de r�flexion : 
*documents concern�s : sources,trames plugin etudiants/enseignants, documents non �volutifs (rapports), 
modes d'emploi (contenant parfois des login et mdp), tableau des updates,zip r�cup�rables pour les TP.
*lieux d'archivage potentiels : GitHub, r�pertoires locaux sur le serveur EII, GitLab, ftp,...
(Julien dans la boucle pour tous les points ci-dessus)
==============================================================================================
D�cembre 2017 : pb de compilation des squelettes de plugin
Version code-Blocks en salle TP : 16.01
Version GCC (c'est ca qui compte) : ??

Squelettes plugin:
version moodle COTR : compile (vieux cpb 12/2014, vieux algo 2011-2012)
version moodle AI : compile pas (nouveau cpb 11/2016, nouveau algo 2015-2016)

version : trames-plugins-tp-2017-12-12.zip
utilisation vieux cpb (12/2014) et nouveau algo (2015-2016)

=> mise sur moodle-COTR et moodle AI et public/TPCOTR
=> nouvelle version de ImageINSA (sources + exe) mise sur moodle AI
=> pas mis les nouveaux zip sur Serveur EII:\Logiciels\Windows (pas les droits)
===============
Stage de Quentin Bigot
-Bilan des bugs pr�sents dans la version TP et dans la version apazat 
-Cr�ation d'un environnement de d�veloppement et compilation de ImageINSA sur machine virtuelle
-Ecriture d'un guide de compilation + script pour compilation facile par les enseignants
-Int�gration des modifications de apazat et nouvelles corrections

================
Avril 2017
Test de Alexandre Sanchez :
-la version "apazat" s'execute sous linux et windows 
-les trames de plugin code-blocks ne compilent pas avec la nouvelle version "apazat" 
-la version "alorence" (donc celle utilis�e en TP en 2016-2017) 
-fonctionne parfaitement sur Windows7 64bits.Y compris la compilation des plugins. 
==================
fin 2016
Alexandre Sanchez a r�cup�r� et compil� sous linux la version de Antoine Pazat
==================
Octobre 2016
Alexandre Sanchez a modifi� quelque chose (?) pour pouvoir compiler les plug-in 
avec la nouvelle version de code-block 
==================
Debut 2016
ajout modif souhait�es (issues forum enseignant sur moodle) dans fichier update
===================
Octobre 2015
module COMP
-modification du plugin DPCM squelette et solution => fichiers dpcm-squelette2 et dpcm-solution2
integres dans le zip sur public/2015-2016/COMP
-quelques bugs not�s dans le logiciel ImageINSA

=========================================
D�but 2015:
information apr�s mis � joru du logiciel par Antoine Lorence : 
-restoration des sources correspondantes a l'exe
-mise sur GitHub

Tout est sur Github � l'adresse https://github.com/eiimage/eiimage/releases
Antoine a archiv� des zip et les a associ�s � une release (= un tag git). 
Il y a :
- Une version compil�e pour windows : ImageINSA-Win32-2014-12-18.zip
- Un dossier avec les projets Code::Blocks � fournir aux �tudiants pour le d�veloppement de plugins : trames-plugins-tp.zip
- Un dossier avec toutes les sources ImageInsa + Detiq-T : sources_ImageINSA_AND_Detiq-T.zip"

Une copie de ces dossier est sur le serveur enseignement Public:
Y:\Logiciels des salles de TP\Analyse d'images (r�pertoire non accessible aux �tudiants)


====================================================
CONTENU DU REPERTOIRE

1-UTILES:

images: toutes les images utilis�es en TP

plugin-fournis-etudiants : squelettes plugins
plugin-version-enseignant : solutions plugin + tests en cours

Log Eiimages 2012-11-29 : sources (sans les corrections faites par Sacha et Marie le 11/10/2012) + exe + rapport sacha + rapport projet 4INFO 
Eiimage-exe-salle-101 : exe utilis� en salle TP 101 : exe de la version avec les corrections faites par Marie et Sacha le 11/10/2012
(les sources n'ont pas �t� retrouv�es) **

2-ARCHIVES:
Eiimage.zip : archive datant du 29/11/2012 (sources sans les corrections)
LogImages 2012-11-29-old-incomplet : executable
eiimage10.12.2012 : executable (qui date en fait du 10 octobre et non du 10 d�cembre! erreur de nommage)
LogImages 2012-11-29 : archive faite par Sacha (m�me contenu que Log Eiimages 2012-11-29 sans le rapport detiq-t)
=================================================
PLUGIN

Les plugin fournis aux �tudiants contiennent des dll deja compil�es qui peuvent �tre 
charg�es et ex�cut�es dans le logiciel (mais fournissent des r�sultats faux, bien s�r).

(pb : aucun exemple de plugin ne compile ni sur vieux PC, ni sur le nouveau
=> � voir si compile en salle de TP)

Entropy :
squelette : fait 
correction : fait

DPCM
squelette : fait
correction : en cours 
voir code dans DPCMtestLuce, � placer dans le r�pertoire plugins

WU
squelette enti�rement vide : fait (dans plugin DPCM)

Estim mvt:
rien fait

Exemples de plugins:
Eiimage\eiimage\plugins\Segmentation
Eiimage\eiimage\plugins\Entropy

=> Entropy et Segmentation et SegmentationTest marchent


Consignes pour les �tudiants
*r�cup�rer (via moodle,fileZ,public)
le squelettePlugin-Entropy-etudiants.zip
Eiimage.zip

*Placer le r�pertoire Entropy contenant le projet Code::Blocks � modifier dans \Eiimage\eiimage\plugins

*Compl�ter le code.

*Compiler pour g�n�rer un fichier Entropy.dll dans Entropy\bin\Release

*Lancer application "eiimage.exe", charger le plug-in en s�lectionnant le fichier Entropy.dll g�n�r� 

=============================================================
doc en ligne

http://www.cplusplus.com/reference
===============================================

===== echanges de mail
** voir le MAIL de SACHA du 22/07/2013



