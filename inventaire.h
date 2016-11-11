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
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "date.h"
#include "arbremap.h"

#if !defined(_INVENTAIRE__H_)
#define _INVENTAIRE__H_

using namespace std;


class ListeIngredients {
public:
    ListeIngredients() {
        quantiteIngredient = 0;
        listeIngredients = new ArbreMap<string, int>;
    };

    ListeIngredients(const ListeIngredients &);

    ~ListeIngredients();

    const int &operator[](const std::string &nomRecu) const;

    int &operator[](const std::string &nomRecu);

    ListeIngredients &operator+=(const ListeIngredients &liste);

    ListeIngredients &operator=(const ListeIngredients &);

private:
    ArbreMap<string, int> *listeIngredients;
    int quantiteIngredient;

    void afficherListeIngredients();

    void viderLaListe();

    friend std::istream &operator>>(std::istream &, ListeIngredients &);

    friend class Restaurant;
};

////////////////////////////////////////////
class ListeInventaires {
public:

    ListeInventaires() {
        quantiteTotal = 0;
    };

    ListeInventaires(const ListeInventaires &);

    ~ListeInventaires() {
        quantiteTotal = 0;
        listeInventaires.vider();
    }

    const int &operator[](const Date &) const;

    int &operator[](const Date &);

    ListeInventaires &operator+=(const ListeInventaires &);

    ListeInventaires &operator=(const ListeInventaires &);

private:
    ArbreMap<Date, int> listeInventaires;
    int quantiteTotal;

    friend std::istream &operator>>(std::istream &, ListeInventaires &);

    friend class Restaurant;
};

////////////////////////////////////////////
class Restaurant {
public:
    Restaurant() {
    };

    int ouvrir(std::istream &entreeFichier);

private:
    bool validerLaReservation(ListeIngredients &ingredientsReservationRecu,
                              ArbreMap<std::string, ListeInventaires> &inventaireRecu,
                              const Date &date_HorlogeRecu) const;

    void accepterReservation(ListeIngredients &ingredientsReservationRecu,
                             ArbreMap<std::string, ListeInventaires> &inventaireRecu, const Date &date_HorlogeRecu);

    void enleverIngredientsPerimes(ListeIngredients &ingredientsReservationRecu,
                                   ArbreMap<std::string, ListeInventaires> &inventaireRecu,
                                   const Date &date_HorlogeRecu);
};

#endif

