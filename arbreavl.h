/*
 * INF3105 - Structures de données et algorithmes
 * UQAM / Département d'informatique
 * Été 2014
 *
 * Reference : Professeur Eric Beaudry / ericbeaudry.ca
 *
 * Projet realise par :
 * Maxime Roy (celstn)
 * Floriant Beaumont
 *
 */
#if !defined(__ARBREAVL_H__)
#define __ARBREAVL_H__

#include <assert.h>
#include <stdio.h>
#include "pile.h"
#include <stdlib.h> 

template<class T>
class ArbreAVL {
public:
    ArbreAVL();

    ArbreAVL(const ArbreAVL &);

    ~ArbreAVL();

    class Iterateur;

    void inserer(const T &);

    void enlever(const T &);

    bool vide() const;

    void vider();

    bool contient(const T &) const;

    int hauteur() const;

    Iterateur debut() const;

    Iterateur fin() const;

    Iterateur rechercher(const T &) const;

    Iterateur rechercherEgalOuSuivant(const T &) const;

    Iterateur rechercherEgalOuPrecedent(const T &) const;

    const T &operator[](const Iterateur &) const;

    T &operator[](const Iterateur &);

    ArbreAVL &operator=(const ArbreAVL &);

private:
    class Noeud;

    Noeud *racine;

    const T &max(Noeud *) const;

    bool inserer(const T &, Noeud *&);

    bool contient(const T &, Noeud *const &) const;

    bool enlever(const T &e, Noeud *&n);

    bool enleverGauche(const T &, Noeud *&);

    bool enleverDroite(const T &, Noeud *&);

    void rotationGaucheDroite(Noeud *&);

    void rotationDroiteGauche(Noeud *&);

    void vider(Noeud *&);

    void copier(const Noeud *, Noeud *&) const;


public:
    class Iterateur {
    public:
        Iterateur(const ArbreAVL &a);

        Iterateur(const Iterateur &a);

        Iterateur(const ArbreAVL &a, Noeud *c);

        operator bool() const;

        bool operator!() const;

        Iterateur &operator=(const Iterateur &);

        bool operator==(const Iterateur &) const;

        bool operator!=(const Iterateur &) const;

        T &operator*();

        const T &operator*() const;

        Iterateur &operator++();

        Iterateur operator++(int);

    private:
        const ArbreAVL &arbreAssocie;
        Noeud *courant;
        Pile<Noeud *> chemin;

        friend class ArbreAVL;
    };

private:

    class Noeud {
    public:
        Noeud(const T &);

        Noeud *gauche;
        Noeud *droite;
        int equilibre;
        T contenu;
    };
};


////////////////////////////////////////////
template<class T>
ArbreAVL<T>::Noeud::Noeud(const T &c) :
        gauche(NULL), droite(NULL), equilibre(0), contenu(c) {
}

//////////////////////
template<class T>
ArbreAVL<T>::ArbreAVL() : racine(NULL) {
}

//////////////////////
template<class T>
ArbreAVL<T>::ArbreAVL(const ArbreAVL<T> &autre) : racine(NULL) {
    copier(autre.racine, racine);
}

//////////////////////
template<class T>
ArbreAVL<T>::~ArbreAVL() {
    vider(racine);
}

//////////////////////
template<class T>
void ArbreAVL<T>::inserer(const T &elementRecu) {
    inserer(elementRecu, racine);
}

//////////////////////
template<class T>
bool ArbreAVL<T>::inserer(const T &elementRecu, Noeud *&noeudRecu) {
    if (noeudRecu == NULL) {
        noeudRecu = new Noeud(elementRecu);
        return true;
    }

    if (elementRecu < noeudRecu->contenu) { //Inserer a gauche
        if (inserer(elementRecu, noeudRecu->gauche)) {
            noeudRecu->equilibre++;
            if (noeudRecu->equilibre == 0) return false;
            if (noeudRecu->equilibre == 1)return true;
            assert(noeudRecu->equilibre == 2);
            if (noeudRecu->gauche->equilibre == -1)
                rotationDroiteGauche(noeudRecu->gauche);
            rotationGaucheDroite(noeudRecu);
        }
        return false;

    } else if (noeudRecu->contenu < elementRecu) { //Inserer a droite
        if (inserer(elementRecu, noeudRecu->droite)) {
            noeudRecu->equilibre--;
            if (noeudRecu->equilibre == 0) return false;
            if (noeudRecu->equilibre == -1)return true;
            assert(noeudRecu->equilibre == -2);
            if (noeudRecu->droite->equilibre == 1) {
                rotationGaucheDroite(noeudRecu->droite);
            }
            rotationDroiteGauche(noeudRecu);
        }
        return false;
    }

    noeudRecu->contenu = elementRecu;
    return false;
}

//////////////////////
template<class T>
void ArbreAVL<T>::enlever(const T &elementRecu) {
    enlever(elementRecu, racine);
}

//////////////////////
template<class T>
bool ArbreAVL<T>::enlever(const T &elementRecu, Noeud *&noeudRecu) {
    if (noeudRecu == NULL) return false;
    if (elementRecu < noeudRecu->contenu) return enleverGauche(elementRecu, noeudRecu);
    if (noeudRecu->contenu < elementRecu) return enleverDroite(elementRecu, noeudRecu);

    Noeud *temp = noeudRecu;
    if (noeudRecu->gauche == NULL) {
        noeudRecu = noeudRecu->droite;
        delete temp;
        return true;
    }
    if (noeudRecu->droite == NULL) {
        noeudRecu = noeudRecu->gauche;
        delete temp;
        return true;
    }

    noeudRecu->contenu = max(noeudRecu->gauche);
    return enleverGauche(noeudRecu->contenu, noeudRecu);
}

//////////////////////
template<class T>
bool ArbreAVL<T>::enleverGauche(const T &elementRecu, Noeud *&noeudRecu) {
    bool retour = false;
    if (enlever(elementRecu, noeudRecu->gauche)) {
        noeudRecu->equilibre--;
        if (noeudRecu->equilibre == -1) return false;
        if (noeudRecu->equilibre == 0) return true;
        assert(noeudRecu->equilibre == -2);
        retour = noeudRecu->droite->equilibre != 0;
        if (noeudRecu->droite->equilibre == 1) rotationGaucheDroite(noeudRecu->droite);
        rotationDroiteGauche(noeudRecu);
    }
    return retour;
}

//////////////////////
template<class T>
bool ArbreAVL<T>::enleverDroite(const T &elementRecu, Noeud *&noeudRecu) {
    bool retour = false;
    if (enlever(elementRecu, noeudRecu->droite)) {
        noeudRecu->equilibre++;
        if (noeudRecu->equilibre == +1) return false;
        if (noeudRecu->equilibre == 0) return true;
        assert(noeudRecu->equilibre == 2);
        retour = noeudRecu->gauche->equilibre != 0;
        if (noeudRecu->gauche->equilibre == -1) rotationDroiteGauche(noeudRecu->gauche);
        rotationGaucheDroite(noeudRecu);
    }
    return retour;
}

//////////////////////
template<class T>
void ArbreAVL<T>::rotationGaucheDroite(Noeud *&racinesousarbre) {
    Noeud *temp = racinesousarbre->gauche;
    int ea = temp->equilibre;
    int eb = racinesousarbre->equilibre;
    int neb = -(ea > 0 ? ea : 0) - 1 + eb;
    int nea = ea + (neb < 0 ? neb : 0) - 1;

    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;
    racinesousarbre->gauche = temp->droite;
    temp->droite = racinesousarbre;
    racinesousarbre = temp;
}

//////////////////////
template<class T>
void ArbreAVL<T>::rotationDroiteGauche(Noeud *&racinesousarbre) {
    Noeud *temp = racinesousarbre->droite;
    int ea = temp->equilibre;
    int eb = racinesousarbre->equilibre;
    int neb = -(ea < 0 ? ea : 0) + 1 + eb;
    int nea = (neb > 0 ? neb : 0) + 1 + ea;

    temp->equilibre = nea;
    racinesousarbre->equilibre = neb;
    racinesousarbre->droite = temp->gauche;
    temp->gauche = racinesousarbre;
    racinesousarbre = temp;
}

//////////////////////
template<class T>
bool ArbreAVL<T>::vide() const {
    return racine == NULL;
}

//////////////////////
template<class T>
void ArbreAVL<T>::vider() {
    vider(racine);
}

//////////////////////
template<class T>
void ArbreAVL<T>::vider(Noeud *&noeudRecu) {
    if (noeudRecu == NULL) return;
    vider(noeudRecu->gauche);
    vider(noeudRecu->droite);
    delete noeudRecu;
    noeudRecu = NULL;
}

//////////////////////
template<class T>
void ArbreAVL<T>::copier(const Noeud *sourceRecu, Noeud *&noeudRecu) const {

    if (sourceRecu == NULL) {
        noeudRecu = NULL;
        return;
    }

    noeudRecu = new Noeud(sourceRecu->contenu);
    noeudRecu->equilibre = sourceRecu->equilibre;

    if (sourceRecu->gauche != NULL) {
        copier(sourceRecu->gauche, noeudRecu->gauche);
    } else {
        noeudRecu->gauche = NULL;
    }

    if (sourceRecu->droite != NULL) {
        copier(sourceRecu->droite, noeudRecu->droite);
    } else {
        noeudRecu->droite = NULL;
    }

}

//////////////////////
template<class T>
bool ArbreAVL<T>::contient(const T &element) const {
    Iterateur iterTemp = rechercher(element);
    return iterTemp;
}

//////////////////////
template<class T>
int ArbreAVL<T>::hauteur() const {

    Noeud *noeud = racine;
    int hauteur = 0;

    while (noeud != NULL) {
        ++hauteur;
        if (noeud->equilibre == -1) {
            noeud = noeud->droite;
        } else {
            noeud = noeud->gauche;
        }
        return hauteur;
    }
}

//////////////////////
template<class T>
const T &ArbreAVL<T>::max(Noeud *noeudRecu) const {
    if (noeudRecu->droite == NULL) return noeudRecu->contenu;
    return max(noeudRecu->droite);
}

//////////////////////
template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::debut() const {

    Iterateur iter(*this);
    iter.courant = racine;

    if (iter.courant != NULL) {
        while (iter.courant->gauche != NULL) {
            iter.chemin.empiler(iter.courant);
            iter.courant = iter.courant->gauche;
        }
    }

    return iter;
}

//////////////////////
template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::fin() const {
    return Iterateur(*this);
}

//////////////////////
template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercher(const T &e) const {
    Iterateur iter(*this);
    Noeud *n = racine;

    while (n) {
        if (e < n->contenu) {
            iter.chemin.empiler(n);
            n = n->gauche;
        } else if (n->contenu < e)
            n = n->droite;
        else {
            iter.courant = n;
            return iter;
        }
    }

    iter.chemin.vider();
    return iter;
}

//////////////////////
template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuSuivant(const T &elementRecu) const {
    Iterateur iterTemp(*this);
    Noeud *noeudTemp = racine;

    while (noeudTemp) {
        if (elementRecu < noeudTemp->contenu) {
            iterTemp.chemin.empiler(noeudTemp);
            noeudTemp = noeudTemp->gauche;
        } else if (noeudTemp->contenu < elementRecu) {
            iterTemp.chemin.empiler(noeudTemp);
            noeudTemp = noeudTemp->droite;
        } else {
            iterTemp.courant = noeudTemp;
            return iterTemp;
        }
    }

    while (!iterTemp.chemin.vide()) {
        iterTemp.courant = iterTemp.chemin.depiler();
        if (elementRecu < iterTemp.courant->contenu) {
            return iterTemp;
        }
    }

    iterTemp.courant = NULL;
    return Iterateur(*this);
}

//////////////////////
template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::rechercherEgalOuPrecedent(const T &elementRecu) const {
    Iterateur iterTemp(*this);
    Noeud *noeudTemp = racine;
    iterTemp.courant = NULL;

    while (noeudTemp) {
        if (elementRecu < noeudTemp->contenu) {
            iterTemp.chemin.empiler(noeudTemp);
            noeudTemp = noeudTemp->gauche;
        } else if (elementRecu > noeudTemp->contenu) {
            iterTemp.chemin.empiler(noeudTemp);
            iterTemp.courant = noeudTemp;
            noeudTemp = noeudTemp->droite;
        } else {
            iterTemp.courant = noeudTemp;
            return iterTemp;
        }
    }

    if (iterTemp.courant != NULL)
        return iterTemp;
    return Iterateur(*this);
}

//////////////////////
template<class T>
const T &ArbreAVL<T>::operator[](const Iterateur &iterateurRecu) const {
    assert(&iterateurRecu.arbreAssocie == this);
    assert(iterateurRecu.courant);
    return iterateurRecu.courant->contenu;
}

//////////////////////
template<class T>
T &ArbreAVL<T>::operator[](const Iterateur &iterateurRecu) {
    assert(&iterateurRecu.arbreAssocie == this);
    assert(iterateurRecu.courant);
    return iterateurRecu.courant->contenu;
}

//////////////////////
template<class T>
ArbreAVL<T> &ArbreAVL<T>::operator=(const ArbreAVL &autreRecu) {
    if (this == &autreRecu) return *this;
    copier(autreRecu.racine, racine);
    return *this;
}

//////////////////////
template<class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL &a)
        : arbreAssocie(a), courant(NULL) {
}

//////////////////////
template<class T>
ArbreAVL<T>::Iterateur::Iterateur(const ArbreAVL<T>::Iterateur &autreRecu)
        : arbreAssocie(autreRecu.arbreAssocie) {
    courant = autreRecu.courant;
    chemin = autreRecu.chemin;
}

//////////////////////
template<class T>
typename ArbreAVL<T>::Iterateur &ArbreAVL<T>::Iterateur::operator++() {
    assert(courant);
    Noeud *suivant = courant->droite;

    while (suivant) {
        chemin.empiler(suivant);
        suivant = suivant->gauche;
    }

    if (!chemin.vide()) {
        courant = chemin.depiler();
    } else {
        courant = NULL;
    }

    return *this;
}

//////////////////////
template<class T>
typename ArbreAVL<T>::Iterateur ArbreAVL<T>::Iterateur::operator++(int) {
    Iterateur iterRetour(*this);
    operator++();
    return iterRetour;
}

//////////////////////
template<class T>
ArbreAVL<T>::Iterateur::operator bool() const {
    return courant != NULL;
}

//////////////////////
template<class T>
bool ArbreAVL<T>::Iterateur::operator!() const {
    return courant == NULL;
}

//////////////////////
template<class T>
bool ArbreAVL<T>::Iterateur::operator==(const Iterateur &o) const {
    assert(&arbreAssocie == &o.arbreAssocie);
    return courant == o.courant;
}

//////////////////////
template<class T>
bool ArbreAVL<T>::Iterateur::operator!=(const Iterateur &o) const {
    assert(&arbreAssocie == &o.arbreAssocie);
    return courant != o.courant;
}

//////////////////////
template<class T>
T &ArbreAVL<T>::Iterateur::operator*() {
    assert(courant != NULL);
    return courant->contenu;
}

//////////////////////
template<class T>
const T &ArbreAVL<T>::Iterateur::operator*() const {
    assert(courant != NULL);
    return courant->contenu;
}

//////////////////////
template<class T>
typename ArbreAVL<T>::Iterateur &ArbreAVL<T>::Iterateur::operator=(const Iterateur &autreRecu) {
    assert(&arbreAssocie == &autreRecu.arbreAssocie);
    courant = autreRecu.courant;
    chemin = autreRecu.chemin;
    return *this;
}

#endif


