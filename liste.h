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
#if !defined(__LISTE_H__)
#define __LISTE_H__

#include <iostream>

template<class T>
class Liste {
public:
    class Iterateur;

    Liste();

    ~Liste();

    void insererDebut(const T &ingredient);

    void effacerTousMaillons();

    int tailleListe();

    Iterateur debutListe() const;

    T &operator[](const Iterateur &);

    const T &operator[](const Iterateur &) const;

private:
    class Maillon {
    public:
        Maillon(const T &contenuRecu, Maillon *suivantRecu = NULL) {
            contenu = contenuRecu;
            suivant = suivantRecu;
        }

        T contenu;
        Maillon *suivant;
    };

public:
    class Iterateur {
    public:
        Iterateur();

        Iterateur(const Iterateur &);

        Iterateur(const Liste &);

        operator bool() const;

        bool operator!() const;

        Iterateur operator++(int);

        T &operator*() const;

        Iterateur &operator=(const Iterateur &);

    private:
        Maillon *courant;
        const Liste &listeIngredients;

        friend class Liste;
    };

    void lierStation(const Iterateur &iterRecu);

private:
    Maillon *dernier;
    int longueur;

};

////////////////////////////////////////////
template<class T>
Liste<T>::Liste() {
    dernier = NULL;
    longueur = 0;
}

////////////////////////
template<class T>
Liste<T>::~Liste() {
    effacerTousMaillons();
}

////////////////////////
template<class T>
int Liste<T>::tailleListe() {
    return longueur;
}

////////////////////////
template<class T>
void Liste<T>::effacerTousMaillons() {
    if (dernier != NULL) {
        Maillon *temp = dernier->suivant;

        while (temp != dernier) {
            dernier->suivant = temp->suivant;
            delete temp;
            temp = dernier->suivant;
        }
        dernier = NULL;
    }
    longueur = 0;
}

////////////////////////
template<class T>
void Liste<T>::insererDebut(const T &ingredient) {
    if (dernier == NULL) {
        dernier = new Maillon(ingredient);
        dernier->suivant = dernier;
    } else {
        dernier->suivant = new Maillon(ingredient, dernier->suivant);
    }
    longueur++;
}

////////////////////////
template<class T>
void Liste<T>::lierStation(const Iterateur &iterRecu) {
    if (dernier == NULL) {
        dernier = new Maillon(iterRecu);
        dernier->suivant = dernier;
    } else {
        dernier->suivant = new Maillon(iterRecu, dernier->suivant);
    }
    longueur++;
}

////////////////////////
template<class T>
typename Liste<T>::Iterateur Liste<T>::debutListe() const {
    return Iterateur(*this);
}

////////////////////////
template<class T>
T &Liste<T>::operator[](const Iterateur &iterRecu) {
    return iterRecu.courant->contenu;
}

////////////////////////
template<class T>
const T &Liste<T>::operator[](const Iterateur &iterRecu) const {
    return iterRecu.courant->contenu;
}


////////////////////////////////////////////
// class Iterateur /////////////////////////


template<class T>
Liste<T>::Iterateur::Iterateur(const Iterateur &i)
        : listeIngredients(i.listeIngredients) {
    courant = i.courant;
}

////////////////////////
template<class T>
Liste<T>::Iterateur::Iterateur(const Liste<T> &l)
        : listeIngredients(l) {
    courant = l.dernier;
}

////////////////////////
template<class T>
bool Liste<T>::Iterateur::operator!() const {
    return courant == NULL;
}

////////////////////////
template<class T>
Liste<T>::Iterateur::operator bool() const {
    return courant != NULL;
}

////////////////////////
template<class T>
T &Liste<T>::Iterateur::operator*() const {
    return courant->contenu;
}

////////////////////////
template<class T>
typename Liste<T>::Iterateur Liste<T>::Iterateur::operator++(int) {
    Iterateur temp(*this);
    courant = courant->suivant;
    if (courant == listeIngredients.dernier) courant = NULL;
    return temp;
}

////////////////////////
template<class T>
typename Liste<T>::Iterateur &Liste<T>::Iterateur::operator=(const Iterateur &autre) {
    courant = autre.courant;
    return *this;
}

#endif

