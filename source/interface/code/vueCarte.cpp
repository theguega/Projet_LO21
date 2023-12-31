#include <QWidget>
#include <QMouseEvent>
#include <QHoverEvent>
#include <QLabel>
#include <QDebug>
#include <QEvent>
#include <QStackedWidget>
#include <QTimer>
#include "vueCarte.h"

carteVisuel::carteVisuel(QWidget *parent, int hauteur, int largeur, const Carte* carte) :
    QWidget(parent), h(hauteur), l(largeur), carte(carte){ //CarteVisuel sera la partie visuel de la carte
    setFixedSize(l, h); //Fixe la taille de la carte
}

void carteVisuel::paintEvent(QPaintEvent *event) { //Permet de faire les dessins vectoriels sur la carte
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    if(carte != nullptr){
        show();

        if(carte->getBonus().getCouleur() != Couleur::INDT){
            if(carte->getBonus().getCouleur() != Couleur::NOIR && carte->getBonus().getCouleur() != Couleur::BLANC){
                painter.setBrush(couleurEnQ(toStringCouleur(carte->getBonus().getCouleur()))); //On definie la couleur du pinceau en blanc
                painter.setPen(QPen(Qt::black, 1)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
                painter.drawPolygon(rect()); //On colorie le polygone
                QPolygonF rectangle; //Creer un polygone Qt
                rectangle << QPointF(1, 1) << QPointF(l - 1, 1) << QPointF(l - 1, (h-1)/4) << QPointF(0, (h-1)/4); //Ajoute les points du triangle
                painter.setBrush(couleurEnQ(toStringCouleur(carte->getBonus().getCouleur())+"Fonce")); //Prend la couleur definit
                painter.drawPolygon(rectangle); //Colorie le triangle
                painter.setBrush(couleurEnQ(toStringCouleur(carte->getBonus().getCouleur()))); //Prend la couleur definit
                QPolygonF petitRect;
                petitRect << QPointF(l/20, 1) << QPointF(l/5 + l/20, 1) << QPointF(l/5 + l/20, h/5) << QPointF(l/20, h/5);
                painter.drawPolygon(petitRect);
            }
            else if(carte->getBonus().getCouleur() == Couleur::NOIR){
                painter.setBrush(Qt::black); //On definie la couleur du pinceau en blanc
                painter.setPen(QPen(Qt::white, 1)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
                painter.drawPolygon(rect()); //On colorie le polygone
                QPolygonF rectangle; //Creer un polygone Qt
                rectangle << QPointF(1, 1) << QPointF(l - 1, 1) << QPointF(l - 1, (h-1)/4) << QPointF(0, (h-1)/4); //Ajoute les points du triangle
                painter.drawPolygon(rectangle); //Colorie le triangle
                painter.drawPolygon(rectangle); //Colorie le triangle
                QPolygonF petitRect;
                petitRect << QPointF(l/20, 1) << QPointF(l/5 + l/20, 1) << QPointF(l/5 + l/20, h/5) << QPointF(l/20, h/5);
                painter.drawPolygon(petitRect);
            }
            else if(carte->getBonus().getCouleur() == Couleur::BLANC){
                painter.setBrush(Qt::white); //On definie la couleur du pinceau en blanc
                painter.setPen(QPen(Qt::black, 1)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
                painter.drawPolygon(rect()); //On colorie le polygone
                QPolygonF rectangle; //Creer un polygone Qt
                rectangle << QPointF(1, 1) << QPointF(l - 1, 1) << QPointF(l - 1, (h-1)/4) << QPointF(0, (h-1)/4); //Ajoute les points du triangle
                painter.drawPolygon(rectangle); //Colorie le triangle
                painter.drawPolygon(rectangle); //Colorie le triangle
                QPolygonF petitRect;
                petitRect << QPointF(l/20, 1) << QPointF(l/5 + l/20, 1) << QPointF(l/5 + l/20, h/5) << QPointF(l/20, h/5);
                painter.drawPolygon(petitRect);
            }
        }
        else{
            painter.setBrush(Qt::gray); //On definie la couleur du pinceau en blanc
            painter.setPen(QPen(Qt::black, 1)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
            painter.drawPolygon(rect()); //On colorie le polygone
            QPolygonF rectangle; //Creer un polygone Qt
            rectangle << QPointF(1, 1) << QPointF(l - 1, 1) << QPointF(l - 1, (h-1)/4) << QPointF(0, (h-1)/4); //Ajoute les points du triangle
            painter.drawPolygon(rectangle); //Colorie le triangle
            QPolygonF petitRect;
            petitRect << QPointF(l/20, 1) << QPointF(l/5 + l/20, 1) << QPointF(l/5 + l/20, h/5) << QPointF(l/20, h/5);
            painter.drawPolygon(petitRect);
        }

        int radius = (h - 2)/15;
        int centerX = 2 * l/5;
        int centerY = (h-1)/8;

        for(int i = 0; i < carte->getBonus().getNbBonus(); i++){
            painter.drawEllipse(QPoint(centerX, centerY), radius, radius);
            centerX += 2 * h/15;
        }

        if(carte->getBonus().getCouleur() != Couleur::BLANC){
            painter.setPen(Qt::white); //Ajout le numero dans le triangle
            painter.setFont(QFont("Arial", 12));
            painter.drawText(l/10, h/6, QString::number(carte->getNbPtsPrivilege()));
        }
        else{
            painter.setPen(Qt::black); //Ajout le numero dans le triangle
            painter.setFont(QFont("Arial", 12));
            painter.drawText(l/10, h/6, QString::number(carte->getNbPtsPrivilege()));
        }

        radius = h/10 - 2;
        centerX = h/10 + 1;
        centerY = h / 5 * 4 + h/10 + 1;

        if(carte->getPrix().getBlanc() != 0){
            painter.setBrush(couleurEnQ("blanc"));
            painter.setPen(Qt::black);

            painter.drawEllipse(QPoint(centerX, centerY), radius, radius);

            QFont font("Arial", 12); // Définir la police et la taille de la police
            painter.setFont(font);

            QString texte = QString::number(carte->getPrix().getBlanc());
            QFontMetrics metrics(font);
            int textWidth = metrics.horizontalAdvance(texte);

            // Calculer la position en x pour centrer le texte
            int x = centerX - textWidth/2; // Position en x pour centrer le texte horizontalement
            int y = centerY + radius/2; // Position en y

            painter.drawText(x, y, texte);

            centerY -= (h/5 - 4);
        }

        if(carte->getPrix().getBleu() != 0){
            painter.setBrush(couleurEnQ("bleu"));
            painter.setPen(Qt::white);

            painter.drawEllipse(QPoint(centerX, centerY), radius, radius);

            QFont font("Arial", 12); // Définir la police et la taille de la police
            painter.setFont(font);

            QString texte = QString::number(carte->getPrix().getBleu());
            QFontMetrics metrics(font);
            int textWidth = metrics.horizontalAdvance(texte);

            // Calculer la position en x pour centrer le texte
            int x = centerX - textWidth/2; // Position en x pour centrer le texte horizontalement
            int y = centerY + radius/2; // Position en y

            painter.drawText(x, y, texte);

            centerY -= (h/5 - 4);
        }


        if(carte->getPrix().getVert() != 0){
            painter.setBrush(couleurEnQ("vert"));
            painter.setPen(Qt::white);

            painter.drawEllipse(QPoint(centerX, centerY), radius, radius);

            QFont font("Arial", 12); // Définir la police et la taille de la police
            painter.setFont(font);

            QString texte = QString::number(carte->getPrix().getVert());
            QFontMetrics metrics(font);
            int textWidth = metrics.horizontalAdvance(texte);

            // Calculer la position en x pour centrer le texte
            int x = centerX - textWidth/2; // Position en x pour centrer le texte horizontalement
            int y = centerY + radius/2; // Position en y

            painter.drawText(x, y, texte);

            centerY -= (h/5 - 4);
        }

        if(carte->getPrix().getNoir() != 0){
            painter.setBrush(Qt::black);
            painter.setPen(Qt::white);

            painter.drawEllipse(QPoint(centerX, centerY), radius, radius);

            QFont font("Arial", 12); // Définir la police et la taille de la police
            painter.setFont(font);

            QString texte = QString::number(carte->getPrix().getNoir());
            QFontMetrics metrics(font);
            int textWidth = metrics.horizontalAdvance(texte);

            // Calculer la position en x pour centrer le texte
            int x = centerX - textWidth/2; // Position en x pour centrer le texte horizontalement
            int y = centerY + radius/2; // Position en y

            painter.drawText(x, y, texte);
            painter.setPen(Qt::black);

            centerY -= (h/5 - 4);
        }

        if(carte->getPrix().getRouge() != 0){
            painter.setBrush(couleurEnQ("rouge"));
            painter.setPen(Qt::white);

            painter.drawEllipse(QPoint(centerX, centerY), radius, radius);

            QFont font("Arial", 12); // Définir la police et la taille de la police
            painter.setFont(font);

            QString texte = QString::number(carte->getPrix().getRouge());
            QFontMetrics metrics(font);
            int textWidth = metrics.horizontalAdvance(texte);

            // Calculer la position en x pour centrer le texte
            int x = centerX - textWidth/2; // Position en x pour centrer le texte horizontalement
            int y = centerY + radius/2; // Position en y

            painter.drawText(x, y, texte);

            centerY -= (h/5 - 4);
        }

        if(carte->getPrix().getPerle() != 0){
            painter.setBrush(couleurEnQ("perle"));
            painter.setPen(Qt::white);

            painter.drawEllipse(QPoint(centerX, centerY), radius, radius);

            QFont font("Arial", 12); // Définir la police et la taille de la police
            painter.setFont(font);

            QString texte = QString::number(carte->getPrix().getPerle());
            QFontMetrics metrics(font);
            int textWidth = metrics.horizontalAdvance(texte);

            // Calculer la position en x pour centrer le texte
            int x = centerX - textWidth/2; // Position en x pour centrer le texte horizontalement
            int y = centerY + radius/2; // Position en y

            painter.drawText(x, y, texte);

            centerY -= (h/5 - 4);
        }

        centerX = l - l/5 - 2;
        centerY = h/3.5 + 2;
        int base = l/5;
        int hauteur = h/5;
        int nbTriangle = 5, x, y, baseT, hauteurT;
        y = centerY;
        for(int i = 0; i < carte->getNbCouronnes(); i++){
            // Configurer la couleur et l'épaisseur du contour
            painter.setPen(QPen(Qt::black, 0.5));
            painter.setBrush(QColor("#FFD700")); // Couleur dorée

            x = centerX;
            y = centerY + hauteur*i/2;

            baseT = (base/nbTriangle);

            QPolygonF couronne;

            // Dessiner la couronne de 5 triangles isocèles
            for (int i = 0; i < nbTriangle; ++i) {

                QPolygonF triangle;


                if(i == nbTriangle/2){
                    hauteurT = hauteur/4;
                }
                else if(i%2 == 1){
                    hauteurT = hauteur/8;
                }
                else{
                    hauteurT = hauteur/6;
                }

                couronne << QPointF(x + baseT*i, y); // Coin inférieur gauche
                if(i == 0){
                    couronne << QPointF(x + baseT*i, y - hauteurT); // Sommet
                }
                else if(i == nbTriangle - 1){
                    couronne << QPointF(x + baseT*(i+1), y - hauteurT); // Sommet
                }
                else{
                    couronne << QPointF(x + baseT*i + baseT/2, y - hauteurT); // Sommet
                }
                couronne << QPointF(x + baseT*(i+1), y); // Coin inférieur droit
            }

            couronne << QPointF(x + baseT*(nbTriangle+1) - baseT, y + hauteur/5);
            couronne << QPointF(centerX, y + hauteur/5);

            painter.drawPolygon(couronne);
        }

        if(carte->getCapacite1() != Capacite::None){
            y += hauteur;
            painter.setBrush(QColor("#844383"));
            painter.setPen(Qt::black);
            painter.drawEllipse(QPoint(l - radius - 2, y), radius, radius);
        }
        if(carte->getCapacite2() != Capacite::None){
            y += hauteur;
            painter.setBrush(QColor("#844383"));
            painter.setPen(Qt::black);
            painter.drawEllipse(QPoint(l - radius - 2, y), radius, radius);
        }
    }
    else{
        hide();
    }
}

carteInfo::carteInfo(QWidget* parent, int hauteur, int largeur, std::string texte) : QWidget(parent){ //Carte info sera la partie avec les infos de la carte
    l = largeur; //Def la hauteur des cartes
    h = hauteur; //Def la largeur des cartes
    setFixedSize(l, h); //Fixe la taille

    labelInfo = new QLabel;
    labelInfo->setText(QString::fromStdString(texte)); //Def le texte du QLabel

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::black);
    labelInfo->setPalette(palette);

    labelInfo->setWordWrap(true); //pour que ça deborde pas de la carte
    labelInfo->setAlignment(Qt::AlignCenter);

    layout = new QVBoxLayout;
    layout->addWidget(labelInfo);
    setLayout(layout);

}

void carteInfo::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(Qt::white); //On definie la couleur du pinceau en blanc
    painter.drawPolygon(rect()); //On colorie le polygone

    painter.setPen(QPen(Qt::black, 2)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
    painter.drawRect(rect()); //On peind ce rectangle (permet de fair eun contour de la carte)
}

vueCarte::vueCarte(QWidget* parent, int hauteur, int largeur, const Carte* carte) :
    QStackedWidget(parent), h(hauteur), l(largeur), carte(carte){ //C'est un QStackedWidget afin de gerer plus facilement le changement entre les infos et le visu
    setFixedSize(l, h); //Fixe la taille
    if(carte != nullptr){
        std::string texteInfo = carte->getInfos();
        info = new carteInfo(nullptr, h, l, texteInfo); //Ajoute les infos de la carte
    }
    else{
        info = new carteInfo(nullptr, h, l, "");
    }

    visu = new carteVisuel(nullptr, h,l, carte); //Ajoute le visuel de la carte


    addWidget(visu); //visu devient l'index 0
    addWidget(info); //visu devient l'index 1

    setMouseTracking(true); //Autorise le tracking de la souris pour les enterEvent et leaveEvent
}

bool vueCarte::event(QEvent *event){
    if(affichageInfo){
        if (event->type() == QEvent::Enter) {
            qDebug() << "C'est un evenement d'entree (Enter Event).";
            setCurrentIndex(1);
            return true; // evenement traite
        }
        else if (event->type() == QEvent::Leave){
            qDebug() << "C'est un evenement de sorti (Leave Event).";
            setCurrentIndex(0);
            return true; // evenement traite
        }
    }

    // Appel a la methode parent pour gerer d'autres types d'evenements
    return QWidget::event(event);
}

void vuePaquet::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(QPen(Qt::black, 3)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
    painter.drawRect(rect()); //On peind ce rectangle (permet de fair eun contour de la carte)

    switch(niveau){
    case TypeCarte::Niv1:
        painter.setBrush(QColor("#80A266")); //On definie la couleur du pinceau
        painter.drawPolygon(rect()); //On colorie le polygone
        break;
    case TypeCarte::Niv2:
        painter.setBrush(QColor("#A39437")); //On definie la couleur du pinceau
        painter.drawPolygon(rect()); //On colorie le polygone
        break;
    case TypeCarte::Niv3:
        painter.setBrush(QColor("#1D60AF")); //On definie la couleur du pinceau
        painter.drawPolygon(rect()); //On colorie le polygone
        break;
    default:
        painter.setBrush(Qt::white); //On definie la couleur du pinceau
        painter.drawPolygon(rect()); //On colorie le polygone
        break;
    }



    // Définir les dimensions pour la couronne
    int margin = 10; // Marge entre les bords de la carte et la couronne
    int lSansMarge = l - 2 * margin;

    // Configurer la couleur et l'épaisseur du contour
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QColor("#FFD700")); // Couleur dorée

    QPolygonF couronne;

    // Dessiner la couronne de 5 triangles isocèles
    int nbTriangle = 5, x, y, base, hauteur;

    for (int i = 0; i < nbTriangle; ++i) {

        QPolygonF triangle;
        x = margin + lSansMarge/nbTriangle*i;
        y = h/2;
        base = lSansMarge/nbTriangle;

        if(i == nbTriangle/2){
            hauteur = h/5;
        }
        else if(i%2 == 1){
            hauteur = h/10;
        }
        else{
            hauteur = h/7.5;
        }

        couronne << QPointF(x, y); // Coin inférieur gauche
        if(i == 0){
            couronne << QPointF(x, y - hauteur); // Sommet
        }
        else if(i == nbTriangle - 1){
            couronne << QPointF(x + base, y - hauteur); // Sommet
        }
        else{
            couronne << QPointF(x + base / 2, y - hauteur); // Sommet
        }
        couronne << QPointF(x + base, y); // Coin inférieur droit
    }

    couronne << QPointF(x + base, y + h/7.5);
    couronne << QPointF(margin, y + h/7.5);

    painter.drawPolygon(couronne);

    QFont font("Arial", 12); // Définir la police et la taille de la police
    painter.setFont(font);

    QString texte = QString::number(getNbCartes());
    QFontMetrics metrics(font);
    int textWidth = metrics.horizontalAdvance(texte);

    // Calculer la position en x pour centrer le texte
    x = (l - textWidth) / 2; // Position en x pour centrer le texte horizontalement
    y = y + h/3; // Position en y

    painter.drawText(x, y, texte);
}

vueCarteJoueur::vueCarteJoueur(QWidget* parent, int hauteur, int largeur, const Carte *c) :
    QWidget(parent), h(hauteur), l(largeur), carte(c){
    setFixedSize(l, h);
}

void vueCarteJoueur::paintEvent(QPaintEvent* event){
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    if(carte != nullptr){

        if((estComplete && !estReservee) || (estReservee && estRetournee)){

            setFixedSize(l, h);

            if(carte->getBonus().getCouleur() != Couleur::INDT){
                if(carte->getBonus().getCouleur() != Couleur::NOIR && carte->getBonus().getCouleur() != Couleur::BLANC){
                    painter.setBrush(couleurEnQ(toStringCouleur(carte->getBonus().getCouleur()))); //On definie la couleur du pinceau en blanc
                    painter.setPen(QPen(Qt::black, 1)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
                    painter.drawPolygon(rect()); //On colorie le polygone
                    QPolygonF rectangle; //Creer un polygone Qt
                    rectangle << QPointF(1, 1) << QPointF(l - 1, 1) << QPointF(l - 1, (h-1)/4) << QPointF(0, (h-1)/4); //Ajoute les points du triangle
                    painter.setBrush(couleurEnQ(toStringCouleur(carte->getBonus().getCouleur())+"Fonce")); //Prend la couleur definit
                    painter.drawPolygon(rectangle); //Colorie le triangle
                    painter.setBrush(couleurEnQ(toStringCouleur(carte->getBonus().getCouleur()))); //Prend la couleur definit
                    QPolygonF petitRect;
                    petitRect << QPointF(l/20, 1) << QPointF(l/5 + l/20, 1) << QPointF(l/5 + l/20, h/5) << QPointF(l/20, h/5);
                    painter.drawPolygon(petitRect);
                }
                else if(carte->getBonus().getCouleur() == Couleur::NOIR){
                    painter.setBrush(Qt::black); //On definie la couleur du pinceau en blanc
                    painter.setPen(QPen(Qt::white, 1)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
                    painter.drawPolygon(rect()); //On colorie le polygone
                    QPolygonF rectangle; //Creer un polygone Qt
                    rectangle << QPointF(1, 1) << QPointF(l - 1, 1) << QPointF(l - 1, (h-1)/4) << QPointF(0, (h-1)/4); //Ajoute les points du triangle
                    painter.drawPolygon(rectangle); //Colorie le triangle
                    painter.drawPolygon(rectangle); //Colorie le triangle
                    QPolygonF petitRect;
                    petitRect << QPointF(l/20, 1) << QPointF(l/5 + l/20, 1) << QPointF(l/5 + l/20, h/5) << QPointF(l/20, h/5);
                    painter.drawPolygon(petitRect);
                }
                else if(carte->getBonus().getCouleur() == Couleur::BLANC){
                    painter.setBrush(Qt::white); //On definie la couleur du pinceau en blanc
                    painter.setPen(QPen(Qt::black, 1)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
                    painter.drawPolygon(rect()); //On colorie le polygone
                    QPolygonF rectangle; //Creer un polygone Qt
                    rectangle << QPointF(1, 1) << QPointF(l - 1, 1) << QPointF(l - 1, (h-1)/4) << QPointF(0, (h-1)/4); //Ajoute les points du triangle
                    painter.drawPolygon(rectangle); //Colorie le triangle
                    painter.drawPolygon(rectangle); //Colorie le triangle
                    QPolygonF petitRect;
                    petitRect << QPointF(l/20, 1) << QPointF(l/5 + l/20, 1) << QPointF(l/5 + l/20, h/5) << QPointF(l/20, h/5);
                    painter.drawPolygon(petitRect);
                }
            }
            else{
                painter.setBrush(Qt::gray); //On definie la couleur du pinceau en blanc
                painter.setPen(QPen(Qt::black, 1)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
                painter.drawPolygon(rect()); //On colorie le polygone
                QPolygonF rectangle; //Creer un polygone Qt
                rectangle << QPointF(1, 1) << QPointF(l - 1, 1) << QPointF(l - 1, (h-1)/4) << QPointF(0, (h-1)/4); //Ajoute les points du triangle
                painter.drawPolygon(rectangle); //Colorie le triangle
                QPolygonF petitRect;
                petitRect << QPointF(l/20, 1) << QPointF(l/5 + l/20, 1) << QPointF(l/5 + l/20, h/5) << QPointF(l/20, h/5);
                painter.drawPolygon(petitRect);
            }

            int radius = (h - 2)/15;
            int centerX = 2 * l/5;
            int centerY = (h-1)/8;

            for(unsigned int i = 0; i < carte->getBonus().getNbBonus(); i++){
                painter.drawEllipse(QPoint(centerX, centerY), radius, radius);
                centerX += 2 * h/15;
            }

            if(carte->getBonus().getCouleur() != Couleur::BLANC){
                painter.setPen(Qt::white); //Ajout le numero dans le triangle
                painter.setFont(QFont("Arial", 12));
                painter.drawText(l/10, h/6, QString::number(carte->getNbPtsPrivilege()));
            }
            else{
                painter.setPen(Qt::black); //Ajout le numero dans le triangle
                painter.setFont(QFont("Arial", 12));
                painter.drawText(l/10, h/6, QString::number(carte->getNbPtsPrivilege()));
            }

            radius = h/10 - 2;
            centerX = h/10 + 1;
            centerY = h / 5 * 4 + h/10 + 1;

            if(carte->getPrix().getBlanc() != 0){
                painter.setBrush(couleurEnQ("blanc"));
                painter.setPen(Qt::black);

                painter.drawEllipse(QPoint(centerX, centerY), radius, radius);

                QFont font("Arial", 12); // Définir la police et la taille de la police
                painter.setFont(font);

                QString texte = QString::number(carte->getPrix().getBlanc());
                QFontMetrics metrics(font);
                int textWidth = metrics.horizontalAdvance(texte);

                // Calculer la position en x pour centrer le texte
                int x = centerX - textWidth/2; // Position en x pour centrer le texte horizontalement
                int y = centerY + radius/2; // Position en y

                painter.drawText(x, y, texte);

                centerY -= (h/5 - 4);
            }

            if(carte->getPrix().getBleu() != 0){
                painter.setBrush(couleurEnQ("bleu"));
                painter.setPen(Qt::white);

                painter.drawEllipse(QPoint(centerX, centerY), radius, radius);

                QFont font("Arial", 12); // Définir la police et la taille de la police
                painter.setFont(font);

                QString texte = QString::number(carte->getPrix().getBleu());
                QFontMetrics metrics(font);
                int textWidth = metrics.horizontalAdvance(texte);

                // Calculer la position en x pour centrer le texte
                int x = centerX - textWidth/2; // Position en x pour centrer le texte horizontalement
                int y = centerY + radius/2; // Position en y

                painter.drawText(x, y, texte);

                centerY -= (h/5 - 4);
            }


            if(carte->getPrix().getVert() != 0){
                painter.setBrush(couleurEnQ("vert"));
                painter.setPen(Qt::white);

                painter.drawEllipse(QPoint(centerX, centerY), radius, radius);

                QFont font("Arial", 12); // Définir la police et la taille de la police
                painter.setFont(font);

                QString texte = QString::number(carte->getPrix().getVert());
                QFontMetrics metrics(font);
                int textWidth = metrics.horizontalAdvance(texte);

                // Calculer la position en x pour centrer le texte
                int x = centerX - textWidth/2; // Position en x pour centrer le texte horizontalement
                int y = centerY + radius/2; // Position en y

                painter.drawText(x, y, texte);

                centerY -= (h/5 - 4);
            }

            if(carte->getPrix().getNoir() != 0){
                painter.setBrush(Qt::black);
                painter.setPen(Qt::white);

                painter.drawEllipse(QPoint(centerX, centerY), radius, radius);

                QFont font("Arial", 12); // Définir la police et la taille de la police
                painter.setFont(font);

                QString texte = QString::number(carte->getPrix().getNoir());
                QFontMetrics metrics(font);
                int textWidth = metrics.horizontalAdvance(texte);

                // Calculer la position en x pour centrer le texte
                int x = centerX - textWidth/2; // Position en x pour centrer le texte horizontalement
                int y = centerY + radius/2; // Position en y

                painter.drawText(x, y, texte);
                painter.setPen(Qt::black);

                centerY -= (h/5 - 4);
            }

            if(carte->getPrix().getRouge() != 0){
                painter.setBrush(couleurEnQ("rouge"));
                painter.setPen(Qt::white);

                painter.drawEllipse(QPoint(centerX, centerY), radius, radius);

                QFont font("Arial", 12); // Définir la police et la taille de la police
                painter.setFont(font);

                QString texte = QString::number(carte->getPrix().getRouge());
                QFontMetrics metrics(font);
                int textWidth = metrics.horizontalAdvance(texte);

                // Calculer la position en x pour centrer le texte
                int x = centerX - textWidth/2; // Position en x pour centrer le texte horizontalement
                int y = centerY + radius/2; // Position en y

                painter.drawText(x, y, texte);

                centerY -= (h/5 - 4);
            }

            if(carte->getPrix().getPerle() != 0){
                painter.setBrush(couleurEnQ("perle"));
                painter.setPen(Qt::white);

                painter.drawEllipse(QPoint(centerX, centerY), radius, radius);

                QFont font("Arial", 12); // Définir la police et la taille de la police
                painter.setFont(font);

                QString texte = QString::number(carte->getPrix().getPerle());
                QFontMetrics metrics(font);
                int textWidth = metrics.horizontalAdvance(texte);

                // Calculer la position en x pour centrer le texte
                int x = centerX - textWidth/2; // Position en x pour centrer le texte horizontalement
                int y = centerY + radius/2; // Position en y

                painter.drawText(x, y, texte);

                centerY -= (h/5 - 4);
            }

            centerX = l - l/5 - 2;
            centerY = h/3.5 + 2;
            int base = l/5;
            int hauteur = h/5;
            int nbTriangle = 5, x, y, baseT, hauteurT;
            y = centerY;
            for(unsigned int i = 0; i < carte->getNbCouronnes(); i++){
                // Configurer la couleur et l'épaisseur du contour
                painter.setPen(QPen(Qt::black, 0.5));
                painter.setBrush(QColor("#FFD700")); // Couleur dorée

                x = centerX;
                y = centerY + hauteur*i/2;

                baseT = (base/nbTriangle);

                QPolygonF couronne;

                // Dessiner la couronne de 5 triangles isocèles
                for (int i = 0; i < nbTriangle; ++i) {

                    QPolygonF triangle;


                    if(i == nbTriangle/2){
                        hauteurT = hauteur/4;
                    }
                    else if(i%2 == 1){
                        hauteurT = hauteur/8;
                    }
                    else{
                        hauteurT = hauteur/6;
                    }

                    couronne << QPointF(x + baseT*i, y); // Coin inférieur gauche
                    if(i == 0){
                        couronne << QPointF(x + baseT*i, y - hauteurT); // Sommet
                    }
                    else if(i == nbTriangle - 1){
                        couronne << QPointF(x + baseT*(i+1), y - hauteurT); // Sommet
                    }
                    else{
                        couronne << QPointF(x + baseT*i + baseT/2, y - hauteurT); // Sommet
                    }
                    couronne << QPointF(x + baseT*(i+1), y); // Coin inférieur droit
                }

                couronne << QPointF(x + baseT*(nbTriangle+1) - baseT, y + hauteur/5);
                couronne << QPointF(centerX, y + hauteur/5);

                painter.drawPolygon(couronne);
            }

            if(carte->getCapacite1() != Capacite::None){
                y += hauteur;
                painter.setBrush(QColor("#844383"));
                painter.setPen(Qt::black);
                painter.drawEllipse(QPoint(l - radius - 2, y), radius, radius);
            }
            if(carte->getCapacite2() != Capacite::None){
                y += hauteur;
                painter.setBrush(QColor("#844383"));
                painter.setPen(Qt::black);
                painter.drawEllipse(QPoint(l - radius - 2, y), radius, radius);
            }
        }
        else if(estReservee){
            setFixedSize(l, h);

            switch(carte->getType()){
            case TypeCarte::Niv1:
                painter.setBrush(QColor("#80A266")); //On definie la couleur du pinceau
                painter.drawPolygon(rect()); //On colorie le polygone
                break;
            case TypeCarte::Niv2:
                painter.setBrush(QColor("#A39437")); //On definie la couleur du pinceau
                painter.drawPolygon(rect()); //On colorie le polygone
                break;
            case TypeCarte::Niv3:
                painter.setBrush(QColor("#1D60AF")); //On definie la couleur du pinceau
                painter.drawPolygon(rect()); //On colorie le polygone
                break;
            default:
                painter.setBrush(Qt::white); //On definie la couleur du pinceau
                painter.drawPolygon(rect()); //On colorie le polygone
                break;
            }

            // Définir les dimensions pour la couronne
            int margin = 10; // Marge entre les bords de la carte et la couronne
            int lSansMarge = l - 2 * margin;

            // Configurer la couleur et l'épaisseur du contour
            painter.setPen(QPen(Qt::black, 2));
            painter.setBrush(QColor("#FFD700")); // Couleur dorée

            QPolygonF couronne;

            // Dessiner la couronne de 5 triangles isocèles
            int nbTriangle = 5, x, y, base, hauteur;

            for (int i = 0; i < nbTriangle; ++i) {

                QPolygonF triangle;
                x = margin + lSansMarge/nbTriangle*i;
                y = h/2;
                base = lSansMarge/nbTriangle;

                if(i == nbTriangle/2){
                    hauteur = h/5;
                }
                else if(i%2 == 1){
                    hauteur = h/10;
                }
                else{
                    hauteur = h/7.5;
                }

                couronne << QPointF(x, y); // Coin inférieur gauche
                if(i == 0){
                    couronne << QPointF(x, y - hauteur); // Sommet
                }
                else if(i == nbTriangle - 1){
                    couronne << QPointF(x + base, y - hauteur); // Sommet
                }
                else{
                    couronne << QPointF(x + base / 2, y - hauteur); // Sommet
                }
                couronne << QPointF(x + base, y); // Coin inférieur droit
            }

            couronne << QPointF(x + base, y + h/7.5);
            couronne << QPointF(margin, y + h/7.5);

            painter.drawPolygon(couronne);
        }

        else{
            setFixedSize(l, h/4);

            if(carte->getBonus().getCouleur() != Couleur::INDT){
                if(carte->getBonus().getCouleur() != Couleur::NOIR && carte->getBonus().getCouleur() != Couleur::BLANC){
                    painter.setBrush(couleurEnQ(toStringCouleur(carte->getBonus().getCouleur()))); //On definie la couleur du pinceau en blanc
                    painter.setPen(QPen(Qt::black, 1)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
                    painter.drawPolygon(rect()); //On colorie le polygone
                    QPolygonF rectangle; //Creer un polygone Qt
                    rectangle << QPointF(1, 1) << QPointF(l - 1, 1) << QPointF(l - 1, (h-1)/4) << QPointF(0, (h-1)/4); //Ajoute les points du triangle
                    painter.setBrush(couleurEnQ(toStringCouleur(carte->getBonus().getCouleur())+"Fonce")); //Prend la couleur definit
                    painter.drawPolygon(rectangle); //Colorie le triangle
                    painter.setBrush(couleurEnQ(toStringCouleur(carte->getBonus().getCouleur()))); //Prend la couleur definit
                    QPolygonF petitRect;
                    petitRect << QPointF(l/20, 1) << QPointF(l/5 + l/20, 1) << QPointF(l/5 + l/20, h/5) << QPointF(l/20, h/5);
                    painter.drawPolygon(petitRect);
                }
                else if(carte->getBonus().getCouleur() == Couleur::NOIR){
                    painter.setBrush(Qt::black); //On definie la couleur du pinceau en blanc
                    painter.setPen(QPen(Qt::white, 1)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
                    painter.drawPolygon(rect()); //On colorie le polygone
                    QPolygonF rectangle; //Creer un polygone Qt
                    rectangle << QPointF(1, 1) << QPointF(l - 1, 1) << QPointF(l - 1, (h-1)/4) << QPointF(0, (h-1)/4); //Ajoute les points du triangle
                    painter.drawPolygon(rectangle); //Colorie le triangle
                    painter.drawPolygon(rectangle); //Colorie le triangle
                    QPolygonF petitRect;
                    petitRect << QPointF(l/20, 1) << QPointF(l/5 + l/20, 1) << QPointF(l/5 + l/20, h/5) << QPointF(l/20, h/5);
                    painter.drawPolygon(petitRect);
                }
                else if(carte->getBonus().getCouleur() == Couleur::BLANC){
                    painter.setBrush(Qt::white); //On definie la couleur du pinceau en blanc
                    painter.setPen(QPen(Qt::black, 1)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
                    painter.drawPolygon(rect()); //On colorie le polygone
                    QPolygonF rectangle; //Creer un polygone Qt
                    rectangle << QPointF(1, 1) << QPointF(l - 1, 1) << QPointF(l - 1, (h-1)/4) << QPointF(0, (h-1)/4); //Ajoute les points du triangle
                    painter.drawPolygon(rectangle); //Colorie le triangle
                    painter.drawPolygon(rectangle); //Colorie le triangle
                    QPolygonF petitRect;
                    petitRect << QPointF(l/20, 1) << QPointF(l/5 + l/20, 1) << QPointF(l/5 + l/20, h/5) << QPointF(l/20, h/5);
                    painter.drawPolygon(petitRect);
                }
            }
            else{
                painter.setBrush(Qt::gray); //On definie la couleur du pinceau en blanc
                painter.setPen(QPen(Qt::black, 1)); //On def le pinceau comme etant de couleur noir et de taille 2 (pour faire un rebord)
                painter.drawPolygon(rect()); //On colorie le polygone
                QPolygonF rectangle; //Creer un polygone Qt
                rectangle << QPointF(1, 1) << QPointF(l - 1, 1) << QPointF(l - 1, (h-1)/4) << QPointF(0, (h-1)/4); //Ajoute les points du triangle
                painter.drawPolygon(rectangle); //Colorie le triangle
                QPolygonF petitRect;
                petitRect << QPointF(l/20, 1) << QPointF(l/5 + l/20, 1) << QPointF(l/5 + l/20, h/5) << QPointF(l/20, h/5);
                painter.drawPolygon(petitRect);
            }

            int radius = (h - 2)/15;
            int centerX = 2 * l/5;
            int centerY = (h-1)/8;

            for(unsigned int i = 0; i < carte->getBonus().getNbBonus(); i++){
                painter.drawEllipse(QPoint(centerX, centerY), radius, radius);
                centerX += 2 * h/15;
            }

            if(carte->getBonus().getCouleur() != Couleur::BLANC){
                painter.setPen(Qt::white); //Ajout le numero dans le triangle
                painter.setFont(QFont("Arial", 12));
                painter.drawText(l/10, h/6, QString::number(carte->getNbPtsPrivilege()));
            }
            else{
                painter.setPen(Qt::black); //Ajout le numero dans le triangle
                painter.setFont(QFont("Arial", 12));
                painter.drawText(l/10, h/6, QString::number(carte->getNbPtsPrivilege()));
            }
        }
    }
    else{
        hide();
    }
}

void nobleVisuel::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(QColor("#FFC9A7"));
    painter.setPen(QPen(Qt::black, 2));

    painter.drawRect(rect());

    QPolygonF rectangle; //Creer un polygone Qt
    rectangle << QPointF(1, 1) << QPointF(l - 1, 1) << QPointF(l - 1, (h-1)/4) << QPointF(0, (h-1)/4); //Ajoute les points du triangle
    painter.setBrush(QColor("#DE474E")); //Prend la couleur definit
    painter.drawPolygon(rectangle); //Colorie le triangle
    painter.setBrush(QColor("#9E251E")); //Prend la couleur definit
    QPolygonF petitRect;
    petitRect << QPointF(l/20, 1) << QPointF(l/5 + l/20, 1) << QPointF(l/5 + l/20, h/5) << QPointF(l/20, h/5);
    painter.drawPolygon(petitRect);

    painter.setBrush(QColor("#65617A"));
    painter.drawEllipse(QPoint(l/2, 2*h/3 - 10), l/4, h/3);

    painter.setBrush(QColor("#E9C6C4"));
    painter.drawEllipse(QPoint(l/2, h / 3), h / 7, h / 7);

    int radius = (h - 2)/15;
    int centerX = 4 * l/5;
    int centerY = (h-1)/8;
    painter.setBrush(QColor("#844383"));

    if(carte->getCapacite1() != Capacite::None){
        painter.drawEllipse(QPoint(centerX, centerY), radius, radius);
    }

    painter.setPen(Qt::black); //Ajout le numero dans le triangle
    painter.setFont(QFont("Arial", 12));
    painter.drawText(l/10, h/6, QString::number(carte->getNbPtsPrivilege()));

    QPolygonF couronne;

    int hauteur = h/4;
    centerX = l/2 + 1;
    centerY = h/5.5;
    int temp = h/3 - (h-1)/4;
    int base = 2 * static_cast<int>(sqrt(radius*radius + temp * temp));
    //int base = h/5;
    int nbTriangle = 5, x, y, baseT, hauteurT;

    // Configurer la couleur et l'épaisseur du contour
    painter.setPen(QPen(Qt::black, 1));
    painter.setBrush(QColor("#FFD700")); // Couleur dorée

    x = centerX - base/2;
    y = centerY;

    baseT = (base/nbTriangle);

    // Dessiner la couronne de 5 triangles isocèles
    for (int i = 0; i < nbTriangle; ++i) {

        QPolygonF triangle;


        if(i == nbTriangle/2){
            hauteurT = hauteur/4;
        }
        else if(i%2 == 1){
            hauteurT = hauteur/8;
        }
        else{
            hauteurT = hauteur/6;
        }

        couronne << QPointF(x + baseT*i, y); // Coin inférieur gauche
        if(i == 0){
            couronne << QPointF(x + baseT*i, y - hauteurT); // Sommet
        }
        else if(i == nbTriangle - 1){
            couronne << QPointF(x + baseT*(i+1), y - hauteurT); // Sommet
        }
        else{
            couronne << QPointF(x + baseT*i + baseT/2, y - hauteurT); // Sommet
        }
        couronne << QPointF(x + baseT*(i+1), y); // Coin inférieur droit
    }

    couronne << QPointF(x + baseT*(nbTriangle+1) - baseT, y + hauteur/5);
    couronne << QPointF(x, y + hauteur/5);

    painter.drawPolygon(couronne);
}

bool vueCarteNoble::event(QEvent *event){
    if (event->type() == QEvent::Enter) {
        qDebug() << "C'est un evenement d'entree (Enter Event).";
        setCurrentIndex(1);
        return true; // evenement traite
    }
    else if (event->type() == QEvent::Leave){
        qDebug() << "C'est un evenement de sorti (Leave Event).";
        setCurrentIndex(0);
        return true; // evenement traite
    }

    // Appel a la methode parent pour gerer d'autres types d'evenements
    return QWidget::event(event);
}
