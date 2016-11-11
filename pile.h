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
#include <cstdlib>
#include <iostream>
#include "assert.h"

#if !defined(__PILE_H__)
#define __PILE_H__

template<class T>
class Pile {
public:
    Pile();

    Pile(const Pile &);

    ~Pile();

    void empiler(const T &);

    void depiler(T &out);

    T depiler();

    bool vide() const {
        return sommet == NULL;
    }

    void vider();

    const Pile<T> &operator=(const Pile<T> &);

private:

    class Cellule {
    public:
        Cellule(const T &e, Cellule *c);

        T contenu;
        Cellule *suivante;
    };

    Cellule *sommet;
};

////////////////////////////////////////////
template<class T>
Pile<T>::Pile() {
    sommet = NULL;
}

//////////////////////
template<class T>
Pile<T>::~Pile() {
    vider();
}
//////////////////////

template<class T>
Pile<T>::Pile(const Pile<T> &autre) {
    sommet = NULL;
    *this = autre;
}

//////////////////////
template<class T>
void Pile<T>::vider() {
    while (!vide())
        depiler();
}

//////////////////////
template<class T>
Pile<T>::Cellule::Cellule(const T &e, Cellule *c)
        : suivante(c) {
    contenu = e;
}

//////////////////////
template<class T>
void Pile<T>::empiler(const T &e) {
    sommet = new Cellule(e, sommet);
    assert(sommet);
}

//////////////////////
template<class T>
T Pile<T>::depiler() {
    assert(sommet);
    Cellule c(*sommet);
    delete sommet;
    sommet = c.suivante;
    return c.contenu;
}

//////////////////////
template<class T>
void Pile<T>::depiler(T &elementRetour) {
    assert(sommet != NULL);
    elementRetour = sommet->contenu;
    Cellule *temp = sommet;
    sommet = sommet->suivante;
    delete temp;
}

//////////////////////
template<class T>
const Pile<T> &Pile<T>::operator=(const Pile<T> &autreRecu) {
    if (&autreRecu == this) return *this;
    Cellule **laPile = &sommet;
    Cellule *autrePile = autreRecu.sommet;

    while (autrePile) {
        if ((*laPile) == NULL) {
            *laPile = new Cellule(autrePile->contenu, NULL);
        } else {
            (*laPile)->contenu = autrePile->contenu;
            laPile = &((*laPile)->suivante);
            autrePile = autrePile->suivante;
        }
    }
    autrePile = *laPile;
    *laPile = NULL;
    while (autrePile != NULL) {
        Cellule *temp = autrePile->suivante;
        delete autrePile;
        autrePile = temp;
    }
    return *this;
}

#endif


