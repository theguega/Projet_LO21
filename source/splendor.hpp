w#ifndef SPLENDOR_H
#define SPLENDOR_H

// Déclaration de la classe Carte
class Carte {
    //Samuel B
private:
    // Définition de la structure Jetons pour le coût et le bonus
    struct Jetons {
        //CouleurJeton couleur;
        int quantite;
    };

    Jetons cout;
    Jetons bonus;
    int nbCouronnes;
    int nbPtsPrivilege;

public:
    // Constructeur de Carte
    Carte(Jetons cout, Jetons bonus, int nbCouronnes, int nbPtsPrivilege)
        : cout(cout), bonus(bonus), nbCouronnes(nbCouronnes), nbPtsPrivilege(nbPtsPrivilege) {}
};



// Déclaration de la classe Pyramide
class Pyramide {
    //Apres
public:
    void reserverCarte();
    void acheterCarte();
};

// Déclaration de la classe Joueur
/*class Joueur {
    //Samuel M
private:
    std::string nom;
    int score;
    Jetons jetons;
    Carte cartes;
    Privilege privilege;

public:
    int getNbCouronnes();
    int getNbPrestige();
    int getPtsBonus();
};
 */

// Déclaration de la classe EspaceJeux
class EspaceJeux {
public:
    //Sac sac;
    Pyramide pyramide;
    //Plateau plateau;
};

// Déclaration de la classe Partie
class Partie {
    //Robert
private:
    //Joueur joueur1;
    //Joueur joueur2;
    EspaceJeux espaceJeux;
    int tour;

public:
    bool finPartie();
};

// Déclaration de la classe Jeu
class Jeu {
    //plus tard
public:
    Partie lancer();
    bool conditionsVictoire();
};

class I_A {
    //plus tard
};

class Physique {
    //plus tard
};

class JeuDeCarte {
    //Samuel B
};

#endif // SPLENDOR_H