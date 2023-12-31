#ifndef ESPACEJEUX_H
#define ESPACEJEUX_H

/*
----------------------------------------------------------
  ______                               _
 |  ____|                             | |
 | |__   ___ _ __   __ _  ___ ___     | | ___ _   ___  __
 |  __| / __| '_ \ / _` |/ __/ _ \_   | |/ _ \ | | \ \/ /
 | |____\__ \ |_) | (_| | (_|  __/ |__| |  __/ |_| |>  <
 |______|___/ .__/ \__,_|\___\___|\____/ \___|\__,_/_/\_\
            | |
            |_|
----------------------------------------------------------
*/

#include <iostream>
#include <string>
#include <array>
#include <vector>

#include "jetons.hpp"
#include "carte.hpp"




class Pyramide {
    friend class Partie;
    private:    
        std::array<std::vector<const Carte*>,4> array_cartes;
        Pioche &pNv1;
        Pioche &pNv2;
        Pioche &pNv3;
        Pioche &pNoble;
    public:
        Pyramide( Pioche *piocheNv1, Pioche *piocheNv2,Pioche *piocheNv3,Pioche *piocheNoble); // constructeur
        ~Pyramide(); 

        bool estVide() const;
        void remplirPyramide(); // parcour de toute la pyramide pour remplir les cases vides   
        void remplircasePyramide(unsigned int i, unsigned int j); // remplir une case de la pyramide
        
        const Carte& reserverCarte(int i, int j); // retourne la carte de la pyramide et la supprime
        const Carte& acheterCarte(unsigned int i,unsigned int j); // retourne la carte de la pyramide et la supprime + rempli la case avec une nouvelle carte de la pioche
        const Carte& ReserverCartePioche(unsigned int niveau); //retourne une carte de la pioche
        
        void definitCarte(int i, int j, const Carte& c) { array_cartes[i][j] = &c; };
        
        const Carte* getCarte(size_t i, size_t j) { return array_cartes[i][j]; };
        size_t getNbCartesNiv(unsigned int niveau) const {return array_cartes[niveau].size(); };
        Pioche& getPioche1() const { return pNv1; }
        Pioche& getPioche2() const { return pNv2; }
        Pioche& getPioche3() const { return pNv3; }
        Pioche& getPiocheNoble() const { return pNoble; }

        void afficherPyramide() const;
        void afficherNobles() const;
        
        Pyramide(const Pyramide&) = delete;
        Pyramide& operator=(const Pyramide&) = delete;
     };




class EspaceJeux {
    friend class Partie;
    private:
        // --------- init des jetons ---------
        const LotDeJetons *lotJetons;
        const LotPrivileges *lotPrivileges;
        Sac *sac;
        Plateau *plateau; 
        
        // --------- init des cartes ---------
        JeuCarte *jeuxCartes;
        Pioche *piocheNv1;
        Pioche *piocheNv2 ;
        Pioche *piocheNv3 ;
        Pioche *piocheNoble ;
        Pyramide *pyramide ;

    public:
        EspaceJeux() : lotJetons(&LotDeJetons::getLotDeJetons()), lotPrivileges(&LotPrivileges::getLotPrivileges()), sac(&Sac::getSac(*lotJetons)), plateau(&Plateau::getPlateau(*lotPrivileges)),  jeuxCartes(new JeuCarte()), piocheNv1(new Pioche(*jeuxCartes, TypeCarte::Niv1)), piocheNv2(new Pioche(*jeuxCartes, TypeCarte::Niv2)), piocheNv3(new Pioche(*jeuxCartes, TypeCarte::Niv3)), piocheNoble(new Pioche(*jeuxCartes, TypeCarte::Noble)), pyramide(new Pyramide(piocheNv1, piocheNv2, piocheNv3, piocheNoble)) {}

        ~EspaceJeux() { delete jeuxCartes; delete piocheNv1; delete piocheNv2; delete piocheNv3; delete piocheNoble; delete pyramide; };

        Plateau& getPlateau() const { return *plateau; }
        Pyramide& getPyramide() const {return *pyramide; }
        Sac& getSac() const { return *sac; }
        
        EspaceJeux(const EspaceJeux&) = delete;
        EspaceJeux& operator=(const EspaceJeux&) = delete;
};
 
 #endif  //ESPACEJEUX_H
