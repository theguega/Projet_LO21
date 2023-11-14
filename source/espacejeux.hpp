#ifndef ESPACEJEUX_H
#define ESPACEJEUX_H
#include <iostream>
#include <string>
#include <array>
#include <vector>

#include "jetons.hpp"
#include "carte.h"


class Pyramide {

    private:    
        std::vector<const Carte*> array_cartes[4];
        Pioche &pNv1;
        Pioche &pNv2;
        Pioche &pNv3;
        Pioche &pNoble;
    public:
        Pyramide( Pioche *piocheNv1, Pioche *piocheNv2,Pioche *piocheNv3,Pioche *piocheNoble); // constructeur
        ~Pyramide(); 

        bool estVide() const;

        void remplirPyramide(); // parcour de toute la pyramide pour remplir les cases vides   
        void remplircasePyramide(int i, int j); // remplir une case de la pyramide
        void definitCarte(int i, int j, const Carte& c) { array_cartes[i][j] = &c; };
        
        const Carte* getCarte(int i, int j) { return array_cartes[i][j]; }; // retourne la carte de la pyramide sans la supprimer
        
        const Carte& reserverCarte(int i, int j); // retourne la carte de la pyramide et la supprime
        const Carte& acheterCarte(int i, int j); // retourne la carte de la pyramide et la supprime + rempli la case avec une nouvelle carte de la pioche
        const Carte& ReserverCartePioche(int niveau); //retourne une carte de la pioche
        
        int getNbCartesNiv(int niveau) const; // retourne le nombre de cartes d'un niveau dans la pyramide
        void afficherPyramide() const; // affiche la pyramide
        
        friend class Partie;


        /*
        Pyramide(const Pyramide&) = delete;
        Pyramide& operator=(const Pyramide&) = delete; */ 
     };


class EspaceJeux {
    private:
        // idealement espace jeux initialise tout les elements de jeux jsp si c'est pertinant d'init en reference
        
        // --------- init des jetons ---------
        const LotDeJetons *lotJetons;
        const LotPrivileges *lotPrivileges;
        Sac *sac;
        Plateau *plateau; 
        
        // --------- init des cartes ---------
        
        JeuCarte *jeuxCartes = new JeuCarte();
        Pioche *piocheNv1 = new Pioche(*jeuxCartes, TypeCarte::Niv1);
        Pioche *piocheNv2 = new Pioche(*jeuxCartes, TypeCarte::Niv2);
        Pioche *piocheNv3 = new Pioche(*jeuxCartes, TypeCarte::Niv3);
        Pioche *piocheNoble = new Pioche(*jeuxCartes, TypeCarte::Noble);
        Pyramide *pyramide = new Pyramide(piocheNv1, piocheNv2, piocheNv3, piocheNoble);
    public:
        EspaceJeux() : lotJetons(&LotDeJetons::getLotDeJetons()), lotPrivileges(&LotPrivileges::getLotPrivileges()), sac(&Sac::getSac(*lotJetons)), plateau(&Plateau::getPlateau(*sac, *lotPrivileges)) {};
        ~EspaceJeux() { delete jeuxCartes; delete piocheNv1; delete piocheNv2; delete piocheNv3; delete piocheNoble; delete pyramide; } ;

        Plateau& getPlateau() const { return *plateau; }
        Pyramide& getPyramide() const {return *pyramide; }
        

        EspaceJeux(const EspaceJeux&) = delete;
        EspaceJeux& operator=(const EspaceJeux&) = delete;

        friend class Partie;
 

};
 
 #endif  //ESPACEJEUX_H
