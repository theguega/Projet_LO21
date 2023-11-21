#ifndef PROJET_LO21_JOUEUR_HPP
#define PROJET_LO21_JOUEUR_HPP

#include <unordered_map>

#include "jetons.hpp"
#include "carte.hpp"
#include "strategy.hpp"

// Rajouter classe exception
class JoueurException
{
public:
    JoueurException(const std::string& i) :info(i) {}
    std::string getInfo() const { return info; }
private:
    std::string info;
};



enum class type { IA, HUMAIN };

std::string toStringType(type t);

type toType(std::string s);

class Joueur {
private:
    // Rajouter un tab static avec les deux joueurs
    const string pseudo;
    const type typeDeJoueur;
    unsigned int ptsPrestige;
    unsigned int nbCouronnes;

    std::unordered_map<Couleur, std::vector<const Carte*>> cartes;
    std::unordered_map<Couleur, std::vector<const Carte*>> cartesReservees;
    std::unordered_map<Couleur, std::vector<const Jeton*>> jetons;
    std::vector<const Privilege*> privileges;
    Strategy* strategy;
public:
    // Constructeur done
    Joueur(string pseudo, type typeDeJoueur);

    // Destructeur
    ~Joueur();



    // Getters Done
    std::string getPseudo() const { return pseudo; };
    type getTypeDeJoueur() const { return typeDeJoueur; };
    unsigned int getptsPrestige() const { return ptsPrestige; };
    unsigned int getnbCouronnes() const { return nbCouronnes; };
    //Carte **getCartes();
    size_t getNbCartes() const { return cartes.size(); };
    size_t getNbCartes(Couleur c) const { return cartes.at(c).size(); }
    //Jetons **getJetons();
    size_t getNbCartesReservees() const { return cartesReservees.size(); }
    size_t getNbCartesReservees(Couleur c) const { return cartesReservees.at(c).size(); }
    size_t getNbJetons() const { return jetons.size(); }
    size_t getNbJetons(Couleur c) const { return jetons.at(c).size(); }
    //Privilege **getPrivileges();
    size_t getNbPrivileges() const { return privileges.size(); }
    //pb d'itération sur les cartes
    const Carte& getCarte(Couleur c, size_t i) const { return *cartes.at(c).at(i); }
    const Carte& getCarteReservee(Couleur c, size_t i) const { return *cartesReservees.at(c).at(i); }

    bool nbPtsPrestigeParCouleurSupDix() const;

    // Setters
    void updatePtsPrestige(int pts) { ptsPrestige += pts; };
    void updateNbCouronnes(int couronnes) { nbCouronnes += couronnes; };

    void addCarte(const Carte &carte);
    void addCarteReservee(const Carte &carte) ;
    void addJeton(const Jeton &jeton);
    void addPrivilege(const Privilege &privilege);

    // Supprimer un element du vecteur --> attention il faudra voir le lien avec les autres classes DONE
    // Si on supprime un privilège il doit revenir sur le plateau
    void supCarte(Carte &carte);
    void supCarteReservee(const Carte &carte);
    void supJeton(Jeton *jeton);
    const Privilege& supPrivilege(); // a voir si on retire pas juste le premier privilege

    // Affichage Done
    void afficherJoueur() const;
    void afficherCartes() const;
    void afficherJetons() const;
    void afficherPrivileges() const{
        std::cout << "Nombre de privilèges : " << &privileges << std::endl;
    }

    // (J'en ai besoin pour les score comment on l'implémente) (Signe Theo)
    //Je pense que c'est un attribut à définir à la fin de la partie
    //bool estGagant() const { return gagnant; };
    bool estGagnant() {return ptsPrestige >= 15;}; //exemple deso c degeu


};


#endif //PROJET_LO21_JOUEUR_HPP
