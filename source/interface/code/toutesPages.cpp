#include <QApplication>
#include <QDebug>
#include <QObject>
#include <QApplication>
#include <QScreen>
#include <QSize>
#include "toutesPages.h"
#include "pageMenuPrincipal.h"
#include "pageJeu.h"
#include "pageBibliotheque.h"
#include "pageCreation.h"

toutesPages::toutesPages(QWidget* parent, QApplication* app) {
    setWindowIcon(QIcon("gif/splendor.jpg"));
    setWindowTitle("SplendorDuel");

    pageMenuPrincipal* menuPrincipal = new pageMenuPrincipal; //Ajoute la page menuPrincipal
    pageCreation* crea = new pageCreation; //Ajoute la page creation (qui sert a creer la page de Jeu)
    pageBibliotheque* bibli = new pageBibliotheque;


    addWidget(menuPrincipal); //Le addWidget dans ce cas permet de mettre menuPrincipal comme l'index 0
    addWidget(crea); //Crea devient l'index 1
    addWidget(bibli);

    QObject::connect(menuPrincipal->getBoutonQuitter(), &QPushButton::clicked, app, &QCoreApplication::quit); //On connecte le bouton quitter du menu avec le fait de quitter l'application

    connect(menuPrincipal->getBoutonDemarrer(), &QPushButton::clicked, this, [this]() {
        setCurrentIndex(1); //En appuyer sur demarrer, on va sur la page de creation de Jeu
    });
    connect(crea->getRetourMenu(), &QPushButton::clicked, this, [this](){
        setCurrentIndex(0); //Permet de retourner au menu principal
    });
    connect(menuPrincipal->getBoutonBibli(), &QPushButton::clicked, [this] (){
        setCurrentIndex(2);
    });
    connect(bibli->getRetourMenu(), &QPushButton::clicked, this, [this](){
        setCurrentIndex(0); //Permet de retourner au menu principal depuis scrollSauvegardes
    });
    connect(crea, &pageCreation::fermerToutesPages, this, &toutesPages::fermerFenetre); //Connecte le signal fermerToutesPages (emit lors de la validation dans creation page) vec la methode fermer fenêtre afin de tout fermer au moment de la mise en route du jeu

    pop = new popUpValider(nullptr, "restituer la dernière sauvegarde", "", "brain");
    connect(menuPrincipal->getBoutonSauvegarde(), &QPushButton::clicked, this, [this]() {
        pop->show();
    });
    connect(pop -> getBoutonOui(), &QPushButton::clicked, this, &toutesPages::boutonOuiPresse);
    connect(pop -> getBoutonOui(), &QPushButton::clicked, pop, &popUpValider::close);
    connect(pop -> getBoutonNon(), &QPushButton::clicked, pop, &popUpValider::close);
}

void toutesPages::boutonOuiPresse() { //Connecte le bouton oui du PopUpValider
    this -> hide();
    jeu = new pageJeu("Old");
    jeu -> show();
    emit fermerToutesPages();
}
