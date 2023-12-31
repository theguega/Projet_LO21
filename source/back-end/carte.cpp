#include "carte.hpp"
using namespace std;




std::initializer_list < TypeCarte > TypesCarte = {
    TypeCarte::Niv1,
    TypeCarte::Niv2,
    TypeCarte::Niv3,
    TypeCarte::Noble
};




std::initializer_list < Capacite > Capacites = {
    Capacite::NewTurn,
    Capacite::TakePrivilege,
    Capacite::TakeJetonFromBonus,
    Capacite::TakeJetonToAdv,
    Capacite::AssociationBonus,
    Capacite::None
};




string TypeCartetoString(TypeCarte t) {
    switch (t) {
    case TypeCarte::Niv1:
        return "Niv1";
    case TypeCarte::Niv2:
        return "Niv2";
    case TypeCarte::Niv3:
        return "Niv3";
    case TypeCarte::Noble:
        return "Noble";
    default:
        throw SplendorException("Type inconnue");
    }
}

int TypeCartetoInt(TypeCarte t) {
    switch (t) {
    case TypeCarte::Niv1:
        return 1;
    case TypeCarte::Niv2:
        return 2;
    case TypeCarte::Niv3:
        return 3;
    case TypeCarte::Noble:
        return 4;
    default:
        throw SplendorException("Type inconnue");
    }
}

ostream & operator << (ostream & f, TypeCarte t) {
    f << TypeCartetoString(t);
    return f;
}

QDebug operator<<(QDebug f, TypeCarte t){
    f << TypeCartetoString(t);
    return f;
}




string CapacitetoString(Capacite c) {
    switch (c) {
    case Capacite::NewTurn:
        return "NewTurn";
    case Capacite::TakePrivilege:
        return "TakePrivilege";
    case Capacite::TakeJetonFromBonus:
        return "TakeJetonFromBonus";
    case Capacite::TakeJetonToAdv:
        return "TakeJetonToAdv";
    case Capacite::AssociationBonus:
        return "AssociationBonus";
    case Capacite::None:
        return "None";
    default:
        throw SplendorException("Capacite inconnue");
    }
}


string CapacitetoShort(Capacite c){
    switch (c) {
    case Capacite::NewTurn:
        return "NT";
    case Capacite::TakePrivilege:
        return "TP";
    case Capacite::TakeJetonFromBonus:
        return "TJ";
    case Capacite::TakeJetonToAdv:
        return "TA";
    case Capacite::AssociationBonus:
        return "AB";
    case Capacite::None:
        return "NN";
    default:
        throw SplendorException("Capacite inconnue");
    }
}
ostream & operator << (ostream & f, Capacite c) {
    f << CapacitetoString(c);
    return f;
}
QDebug operator<<(QDebug f, Capacite c){
    f << CapacitetoString(c);
    return f;
}




std::map < std::string, Capacite > stringToCapaciteMap = {
    {
        "NewTurn",
        Capacite::NewTurn
    },
    {
        "TakePrivilege",
        Capacite::TakePrivilege
    },
    {
        "TakeJetonFromBonus",
        Capacite::TakeJetonFromBonus
    },
    {
        "TakeJetonToAdv",
        Capacite::TakeJetonToAdv
    },
    {
        "AssociationBonus",
        Capacite::AssociationBonus
    },
    {
        "None",
        Capacite::None
    }
};




Capacite StringToCapacite(const std::string & capaciteStr) {
    auto tmp = stringToCapaciteMap.find(capaciteStr);
    if (tmp != stringToCapaciteMap.end()) {
        return tmp -> second;
    } else {
        return Capacite::None;
    }
}

ostream & operator << (ostream & f, const Prix & p) {
    f << toEmojiCouleur(Couleur::BLANC) << " : " << p.getBlanc() << "    " << toEmojiCouleur(Couleur::BLEU) << " : " << p.getBleu() << "\n";
    f << toEmojiCouleur(Couleur::VERT) << " : " << p.getVert() << "    " << toEmojiCouleur(Couleur::NOIR) << " : " << p.getNoir() << "\n";
    f << toEmojiCouleur(Couleur::ROUGE) << " : " << p.getRouge() << "    " << toEmojiCouleur(Couleur::PERLE) << " : " << p.getPerle() << "\n";
    return f;
}

QDebug operator<<(QDebug f, const Prix &p) {
    f << Couleur::BLANC << " : " << p.getBlanc() << "    " << Couleur::BLEU << " : " << p.getBleu() << "\n";
    f << Couleur::VERT << " : " << p.getVert() << "    " << Couleur::NOIR << " : " << p.getNoir() << "\n";
    f << Couleur::ROUGE << " : " << p.getRouge() << "    " << Couleur::PERLE << " : " << p.getPerle() << "\n";
    return f;
}

ostream & operator << (ostream & f, const Bonus & b) {
    f << b.getNbBonus() << " " << b.getCouleur();
    return f;
}

QDebug operator<<(QDebug f, const Bonus &b){
    f << b.getNbBonus() << " " << b.getCouleur();
    return f;
}




Carte::Carte(TypeCarte t, Prix & p, Capacite c1, Capacite c2, Bonus & b, unsigned int nbC, unsigned int nbP, unsigned int id): type(t), prix(p), capacite1(c1), capacite2(c2), bonus(b), nbCouronnes(nbC), nbPtsPrivilege(nbP), id(id) {
    if (t == TypeCarte::Noble)
        throw SplendorException("Veuillez utiliser le constructeur approprie");
}


Carte::Carte(TypeCarte t, Capacite c, unsigned int nbP, unsigned int id): type(t), prix(0, 0, 0, 0, 0, 0), capacite1(c), capacite2(Capacite::None), bonus(), nbCouronnes(0), nbPtsPrivilege(nbP), id(id) {
    if (t != TypeCarte::Noble)
        throw SplendorException("Veuillez utiliser le constructeur approprie");
}




ostream & operator << (ostream & f, const Carte & c) {
    f << "------------------------------\n";
    f << c.getType() << "   " << "Bonus : " << c.getBonus() << "\n";
    f << "------------------------------\n";
    f << "Capacite : " << c.getCapacite1() << ", " << c.getCapacite2() << "\n";
    f << "------------------------------\n";
    f << "Prix :\n" << c.getPrix();
    f << "------------------------------\n";
    f << "Prestiges : " << c.getNbPtsPrivilege() << "   " << "Couronnes : " << c.getNbCouronnes() << "\n";
    f << "------------------------------\n";
    return f;
}




QDebug operator<<(QDebug f, const Carte & c) {
    f << "------------------------------\n";
    f << c.getType() << "   " << "Bonus : " << c.getBonus() << "\n";
    f << "------------------------------\n";
    f << "Capacite : " << c.getCapacite1() << ", " << c.getCapacite2() << "\n";
    f << "------------------------------\n";
    f << "Prix :\n" << c.getPrix();
    f << "------------------------------\n";
    f << "Prestiges : " << c.getNbPtsPrivilege() << "   " << "Couronnes : " << c.getNbCouronnes() << "\n";
    f << "------------------------------\n";
    return f;
}




std::string Carte::getInfos() const {
    std::ostringstream oss;

    if (getCapacite1() == Capacite::None && getCapacite2() == Capacite::None) {
        oss << "Aucune capacite ";
        return oss.str();
    }

    if (getCapacite1() != Capacite::None) {
        switch (getCapacite1()) {
        case Capacite::NewTurn:
            oss << "Rejouer";
            break;
        case Capacite::TakePrivilege:
            oss << "Prendre 1 Privilège";
                break;
        case Capacite::TakeJetonFromBonus:
            oss << "Prendre 1 jeton de la couleur de la carte";
            break;
        case Capacite::TakeJetonToAdv:
            oss << "Prendre un jeton de l'adversaire";
            break;
        case Capacite::AssociationBonus:
            oss << "Copier la couleur d'une de vos cartes";
            break;
        default:
            throw SplendorException("Capacite inconnue");
        }
    }
    if (getCapacite2() != Capacite::None) {
        oss << " Et ";
        switch (getCapacite2()) {
        case Capacite::NewTurn:
            oss << "Rejouer ";
            break;
        case Capacite::TakePrivilege:
            oss << "Prendre 1 Privilège";
                break;
        case Capacite::TakeJetonFromBonus:
            oss << "Prendre 1 jeton de la couleur de la carte";
            break;
        case Capacite::TakeJetonToAdv:
            oss << "Prendre un jeton de l'adversaire";
            break;
        case Capacite::AssociationBonus:
            oss << "Copier la couleur d'une de vos cartes";
            break;
        default:
            throw SplendorException("Capacite inconnue");
        }
    }
    return oss.str();
}




JeuCarte::JeuCarte() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "conn2");
    db.setDatabaseName("data/data_carte.sqlite");
    if (!db.open()) {
        std::cerr << "Impossible d'ouvrir la base de donnees 1: " << db.lastError().text().toStdString() << std::endl;
        return;
    }
    // cartes joaillerie
    QSqlQuery query(db);
    if (!query.exec("SELECT * FROM carte")) {
        std::cerr << "Erreur de preparation de la requete : " << query.lastError().text().toStdString() << std::endl;
        db.close();
        return;
    }
    while (query.next()) {
        unsigned int id = query.value(0).toUInt();
        string type = query.value(1).toString().toStdString();
        unsigned int p_blanc = query.value(2).toUInt();
        unsigned int p_bleu = query.value(3).toUInt();
        unsigned int p_vert = query.value(4).toUInt();
        unsigned int p_rouge = query.value(5).toUInt();
        unsigned int p_noir = query.value(6).toUInt();
        unsigned int p_perle = query.value(7).toUInt();
        string capacite1 = query.value(8).toString().toStdString();
        string capacite2 = query.value(9).toString().toStdString();
        string couleur_bonus = query.value(10).toString().toStdString();
        unsigned int bonus = query.value(11).toUInt();
        unsigned int nb_couronnes = query.value(12).toUInt();
        unsigned int nb_pts_privileges = query.value(13).toUInt();

        Prix p(p_blanc, p_bleu, p_vert, p_rouge, p_noir, p_perle);
        Bonus b(StringToCouleur(couleur_bonus), bonus);

        if (type == "Niv1") {
            cartes_nv1.push_back(new Carte(TypeCarte::Niv1, p, StringToCapacite(capacite1), StringToCapacite(capacite2), b, nb_couronnes, nb_pts_privileges, id));
        } else if (type == "Niv2") {
            cartes_nv2.push_back(new Carte(TypeCarte::Niv2, p, StringToCapacite(capacite1), StringToCapacite(capacite2), b, nb_couronnes, nb_pts_privileges, id));
        } else if (type == "Niv3") {
            cartes_nv3.push_back(new Carte(TypeCarte::Niv3, p, StringToCapacite(capacite1), StringToCapacite(capacite2), b, nb_couronnes, nb_pts_privileges, id));
        } else {
            throw SplendorException("Erreur de construction, le type de carte ne convient pas ici");
        }
    }
    // cartes nobles
    QSqlQuery query2(db);
    if (!query2.exec("SELECT * FROM carte_noble")) {
        std::cerr << "Erreur de preparation de la requete : " << query2.lastError().text().toStdString() << std::endl;
        db.close();
        return;
    }

    while (query2.next()) {
        unsigned int id = query2.value(0).toUInt();
        std::string capacite = query2.value(1).toString().toStdString();
        unsigned int nb_pts_privileges = query2.value(2).toUInt();
        cartes_nobles.push_back(new Carte(TypeCarte::Noble, StringToCapacite(capacite), nb_pts_privileges, id));
    }

    db.close();
}




JeuCarte::~JeuCarte() {
    for (size_t i = 0; i < getNbCartes_nv1(); ++i) {
        delete cartes_nv1[i];
    }
    for (size_t i = 0; i < getNbCartes_nv2(); ++i) {
        delete cartes_nv2[i];
    }
    for (size_t i = 0; i < getNbCartes_nv3(); ++i) {
        delete cartes_nv3[i];
    }
    for (size_t i = 0; i < getNbCartes_nobles(); ++i) {
        delete cartes_nobles[i];
    }
}




const Carte & JeuCarte::getCarteNiv1(size_t i) const {
    if (i >= getNbCartes_nv1())
        throw SplendorException("Indice invalide pour le niveau 1");
    return * cartes_nv1[i];
}




const Carte & JeuCarte::getCarteNiv2(size_t i) const {
    if (i >= getNbCartes_nv2())
        throw SplendorException("Indice invalide pour le niveau 2");
    return * cartes_nv2[i];
}




const Carte & JeuCarte::getCarteNiv3(size_t i) const {
    if (i >= getNbCartes_nv2())
        throw SplendorException("Indice invalide pour le niveau 3");
    return * cartes_nv3[i];
}




const Carte & JeuCarte::getCarteNoble(size_t i) const {
    if (i >= getNbCartes_nobles())
        throw SplendorException("Indice invalide pour les cartes Nobles");
    return * cartes_nobles[i];
}




Pioche::Pioche(const JeuCarte & j, TypeCarte t): type_carte(t) {
    if (t == TypeCarte::Niv1) {
        for (size_t i = 0; i < j.getNbCartes_nv1(); i++)
            cartes.push_back( & j.getCarteNiv1(i));
    } else if (t == TypeCarte::Niv2) {
        for (size_t i = 0; i < j.getNbCartes_nv2(); i++)
            cartes.push_back( & j.getCarteNiv2(i));
    } else if (t == TypeCarte::Niv3) {
        for (size_t i = 0; i < j.getNbCartes_nv3(); i++)
            cartes.push_back( & j.getCarteNiv3(i));
    } else if (t == TypeCarte::Noble) {
        for (size_t i = 0; i < j.getNbCartes_nobles(); i++)
            cartes.push_back( & j.getCarteNoble(i));
    } else {
        throw SplendorException("Type de cartes inconnu");
    }
}




Pioche::~Pioche() {
    for (size_t i = 0; i < getNbCartes(); i++)
        cartes[i] = nullptr;
}




const Carte & Pioche::piocher() {
    if (estVide())
        throw SplendorException("Plus de cartes dans cette pioche");

    //generation d'un indice aleatoire
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution < > distrib(0, static_cast < int > (cartes.size()) - 1);
    size_t i = distrib(gen);

    const Carte * c = cartes[i];
    cartes.erase(cartes.begin() + i);

    return *c;
}




const Carte & Pioche::piocher(unsigned int id) {
    if (estVide())
        throw SplendorException("Plus de cartes dans cette pioche");

    auto it = std::find_if(cartes.begin(), cartes.end(), [id](const Carte * carte) {
        return carte -> getId() == id;
    });

    if (it != cartes.end()) {
        const Carte * carteTrouvee = * it;
        cartes.erase(it);
        return * carteTrouvee;
    } else
        throw SplendorException("Aucune carte avec l'ID specifie n'a ete trouvee dans cette pioche");
}
