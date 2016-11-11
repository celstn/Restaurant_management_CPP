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
#include "inventaire.h"

ListeIngredients::ListeIngredients(const ListeIngredients &listeIngredientRecu) {
    listeIngredients = listeIngredientRecu.listeIngredients;
    quantiteIngredient = listeIngredientRecu.quantiteIngredient;
}

//////////////////////
ListeIngredients::~ListeIngredients() {
    listeIngredients->vider();
    listeIngredients = NULL;
    quantiteIngredient = 0;
}

//////////////////////
void ListeIngredients::viderLaListe() {
    listeIngredients->vider();
    quantiteIngredient = 0;
}

//////////////////////
const int &ListeIngredients::operator[](const std::string &nomRecu) const {
    return (*listeIngredients)[nomRecu];
}

//////////////////////
int &ListeIngredients::operator[](const std::string &nomRecu) {
    return (*listeIngredients)[nomRecu];
}

//////////////////////
ListeIngredients &ListeIngredients::operator+=(const ListeIngredients &listeIngredientsRecu) {

    ArbreMap<std::string, int>::Iterateur iter01 = listeIngredientsRecu.listeIngredients->debut();
    while (iter01) {
        (*listeIngredients)[iter01.cle()] += iter01.valeur();
        ++iter01;
    }

    ArbreMap<std::string, int>::Iterateur iter02 = listeIngredients->debut();
    while (iter02) {
        quantiteIngredient += (*listeIngredients)[iter02.cle()];
        ++iter02;
    }

    return *this;
}

//////////////////////
ListeIngredients &ListeIngredients::operator=(const ListeIngredients &listeIngredientsRecu) {
    delete listeIngredients;
    listeIngredients = listeIngredientsRecu.listeIngredients;
    quantiteIngredient = listeIngredientsRecu.quantiteIngredient;
    return *this;
}

//////////////////////
std::istream &operator>>(std::istream &is, ListeIngredients &listeIngredientRecu) {
    std::string chaine;
    int quantite;
    is >> chaine;

    while (is && chaine != "---") {
        is >> quantite;
        if (quantite > 0) {
            ArbreMap<string, int> *temp = listeIngredientRecu.listeIngredients;
            (*temp)[chaine] = quantite;
            listeIngredientRecu.quantiteIngredient++;
        }
        is >> chaine;
    }

    return is;
}


////////////////////////////////////////////
ListeInventaires::ListeInventaires(const ListeInventaires &listeInventaireRecu) {
    ArbreMap<Date, int>::IterateurConst iter = listeInventaireRecu.listeInventaires.debut();

    while (iter) {
        listeInventaires[iter.cle()] = iter.valeur();
        ++iter;
    }
    quantiteTotal = 0;
}

//////////////////////
const int &ListeInventaires::operator[](const Date &dateRecu) const {
    return listeInventaires[dateRecu];
}

//////////////////////
int &ListeInventaires::operator[](const Date &dateRecu) {
    return listeInventaires[dateRecu];
}

//////////////////////
ListeInventaires &ListeInventaires::operator+=(const ListeInventaires &listeInventaireRecu) {
    ArbreMap<Date, int>::IterateurConst iter = listeInventaireRecu.listeInventaires.debut();

    while (iter) {
        listeInventaires[iter.cle()] += iter.valeur();
        ++iter;
    }

    quantiteTotal = 0;
    ArbreMap<Date, int>::Iterateur iter02 = listeInventaires.debut();
    while (iter02) {
        quantiteTotal += iter02.valeur();
        ++iter02;
    }
    return *this;
}

//////////////////////
ListeInventaires &ListeInventaires::operator=(const ListeInventaires &listeInventairesRecu) {
    listeInventaires = listeInventairesRecu.listeInventaires;
    return *this;
}

//////////////////////
std::istream &operator>>(std::istream &is, ListeInventaires &listeInventaireRecu) {
    std::string chaine;
    is >> chaine;
    while (is && chaine != "---") {
        int quantite;
        Date expiration;
        is >> quantite >> expiration;
        listeInventaireRecu.listeInventaires[expiration] = quantite;
        listeInventaireRecu.quantiteTotal++;
        is >> chaine;
    }
    return is;
}


////////////////////////////////////////////
int Restaurant::ouvrir(std::istream &entreeFichier) {

    ArbreMap<std::string, ListeIngredients> recette_ArbreMap;
    ArbreMap<std::string, ListeInventaires> inventaire_ArbreMap;
    ListeIngredients ingredientsRequisReservation_ListeIngred;

    ListeIngredients *listeIngredientsTemp = new ListeIngredients();
    int numeroCommande = 0;
    Date date_HorlogeInterne;

    while (entreeFichier) {
        std::string commande;
        entreeFichier >> commande;
        if (!entreeFichier) break;

        if (commande == "recette") {
            std::string nomRecette;
            entreeFichier >> nomRecette;;
            entreeFichier >> *listeIngredientsTemp;;

            ArbreMap<std::string, ListeIngredients>::Iterateur iter = recette_ArbreMap.rechercher(nomRecette);
            recette_ArbreMap[nomRecette].listeIngredients = listeIngredientsTemp->listeIngredients;

            listeIngredientsTemp = new ListeIngredients();

        } else if (commande == "reception") {
            Date date_reception;
            entreeFichier >> date_reception;

            if (date_reception <=
                date_HorlogeInterne) {
                std::cout
                        << "Attention : ce programme supporte uniquement un ordre chronologique (voir hypothèse 3 à la section 3.5)!"
                        << std::endl;

                //Passer a la prochaine reception 
                std::string nomIngredientInventaire = "";
                int quantiteInventaire = 0;
                Date dateExpiration;
                entreeFichier >> nomIngredientInventaire;

                while (entreeFichier && nomIngredientInventaire != "---") {
                    entreeFichier >> quantiteInventaire;
                    entreeFichier >> dateExpiration;
                    entreeFichier >> nomIngredientInventaire;
                }
            } else {
                date_HorlogeInterne = date_reception;

                std::string nomIngredientInventaire = "";
                int quantiteInventaire = 0;
                Date dateExpiration;
                ListeInventaires listeInventairesTemp;

                entreeFichier >> nomIngredientInventaire;

                while (entreeFichier && nomIngredientInventaire != "---") {
                    entreeFichier >> quantiteInventaire;
                    entreeFichier >> dateExpiration;

                    ListeInventaires listeInventaireTemp;
                    listeInventaireTemp[dateExpiration] = quantiteInventaire;

                    inventaire_ArbreMap[nomIngredientInventaire] += listeInventaireTemp;
                    entreeFichier >> nomIngredientInventaire;
                }
            }
        } else if (commande == "reservation") {
            Date date_preparation;
            entreeFichier >> date_preparation;
            if (date_preparation <=
                date_HorlogeInterne) {
                std::cout
                        << "Attention : ce programme supporte uniquement un ordre chronologique (voir hypothèse 3 à la section 3.5)!"
                        << std::endl;

                //Passer la prochiane reservation
                std::string nomRepasReservation;
                entreeFichier >> nomRepasReservation;

                while (entreeFichier && nomRepasReservation != "---") {
                    int quantiteRepas = 0;
                    entreeFichier >> quantiteRepas;
                    entreeFichier >> nomRepasReservation;
                }

            } else {
                date_HorlogeInterne = date_preparation;

                std::string nomRepasReservation;
                entreeFichier >> nomRepasReservation;

                while (entreeFichier && nomRepasReservation != "---") {
                    int quantiteRepas = 0;
                    entreeFichier >> quantiteRepas;
                    ArbreMap<string, int>::Iterateur iter_listeIngredientsRecette = recette_ArbreMap[nomRepasReservation].listeIngredients->debut();

                    while (iter_listeIngredientsRecette) {
                        ingredientsRequisReservation_ListeIngred[iter_listeIngredientsRecette.cle()] +=
                                quantiteRepas * iter_listeIngredientsRecette.valeur();
                        ingredientsRequisReservation_ListeIngred.quantiteIngredient +=
                                quantiteRepas * iter_listeIngredientsRecette.valeur();

                        ++iter_listeIngredientsRecette;
                    }
                    entreeFichier >> nomRepasReservation;
                }

                // Verifier dans la liste inventaire s'il y a tous les ingredients  non-perimes nescessaires a la reservation.
                bool est_validerLaReservation;

                if (ingredientsRequisReservation_ListeIngred.quantiteIngredient) {

                    enleverIngredientsPerimes(ingredientsRequisReservation_ListeIngred,
                                              inventaire_ArbreMap, date_HorlogeInterne);

                    est_validerLaReservation = validerLaReservation(ingredientsRequisReservation_ListeIngred,
                                                                    inventaire_ArbreMap, date_HorlogeInterne);

                } else {//Reservation de plats avec quantite = 0
                    est_validerLaReservation = true;
                }

                if (est_validerLaReservation) {

                    if (ingredientsRequisReservation_ListeIngred.quantiteIngredient) {
                        accepterReservation(ingredientsRequisReservation_ListeIngred,
                                            inventaire_ArbreMap, date_HorlogeInterne);
                    }

                    ingredientsRequisReservation_ListeIngred.viderLaListe();
                    std::cout << numeroCommande << " : OK" << std::endl;
                    numeroCommande++;
                } else {
                    ingredientsRequisReservation_ListeIngred.viderLaListe();

                    std::cout << numeroCommande << " : Echec" << std::endl;
                    numeroCommande++;;
                }
            }

        } else {
            std::cout << "Commande '" << commande << "' inconnue!" << std::endl;
            return 2;
        }
    }
    if (listeIngredientsTemp) {
        delete listeIngredientsTemp;
    }
    return 0;
}

//////////////////////
bool Restaurant::validerLaReservation(ListeIngredients &ingredientsReservationRecu,
                                      ArbreMap<std::string, ListeInventaires> &inventaireRecu,
                                      const Date &date_HorlogeRecu) const {
    bool reservationAccepter = false;
    ArbreMap<std::string, int>::Iterateur iter_Reservation = ingredientsReservationRecu.listeIngredients->debut();
    while (iter_Reservation) {

        // Si ingredient reservation egal pas 0.
        if (iter_Reservation.valeur()) {

            ArbreMap<std::string, ListeInventaires>::Iterateur iter_inventaire = inventaireRecu.rechercher(
                    iter_Reservation.cle());
            if (iter_inventaire) {

                if (iter_inventaire.valeur().quantiteTotal <
                    iter_Reservation.valeur()) { // Total dans inventaire trop petit
                    return false;
                }
                //Verifie si les quantites ils sont ok  et non-perimees.
                int calcul = 0;
                ArbreMap<Date, int>::Iterateur iter_qteDateInventaire = iter_inventaire.valeur().listeInventaires.debut();

                while (iter_qteDateInventaire) {
                    calcul += iter_qteDateInventaire.valeur();

                    if (calcul >= iter_Reservation.valeur()) {
                        reservationAccepter = true;
                        break;
                    } else {
                        reservationAccepter = false;
                    }
                    ++iter_qteDateInventaire;
                }

            } else {
                reservationAccepter = false;
                break;
            }
        }
        ++iter_Reservation;
    }

    return reservationAccepter;
}

//////////////////////
void Restaurant::accepterReservation(ListeIngredients &ingredientsReservationRecu,
                                     ArbreMap<std::string, ListeInventaires> &inventaireRecu,
                                     const Date &date_HorlogeRecu) {

    ArbreMap<std::string, int>::Iterateur iter_Reservation = ingredientsReservationRecu.listeIngredients->debut();
    while (iter_Reservation) {

        // Si ingredient reservation egal pas 0.
        if (iter_Reservation.valeur()) {

            ArbreMap<std::string, ListeInventaires>::Iterateur iter_inventaire = inventaireRecu.rechercher(
                    iter_Reservation.cle());
            if (iter_inventaire) {

                ArbreMap<Date, int>::Iterateur iter_qteDateInventaire = iter_inventaire.valeur().listeInventaires.debut();
                while (iter_qteDateInventaire) {

                    if (iter_Reservation.valeur() <= iter_qteDateInventaire.valeur()) {
                        iter_qteDateInventaire.valeur() -= iter_Reservation.valeur();
                        iter_inventaire.valeur().quantiteTotal -= iter_Reservation.valeur(); // toal
                        break;
                    }
                    if (iter_Reservation.valeur() > iter_qteDateInventaire.valeur()) {
                        iter_Reservation.valeur() -= iter_qteDateInventaire.valeur();
                        iter_inventaire.valeur().quantiteTotal -= iter_qteDateInventaire.valeur();
                        iter_qteDateInventaire.valeur() = 0;
                    }
                    ++iter_qteDateInventaire;
                }
            }
        }
        ++iter_Reservation;
    }
}

//////////////////////
void Restaurant::enleverIngredientsPerimes(ListeIngredients &ingredientsReservationRecu,
                                           ArbreMap<std::string, ListeInventaires> &inventaireRecu,
                                           const Date &date_HorlogeRecu) {

    ArbreMap<std::string, int>::Iterateur iter_ingredientReservation = ingredientsReservationRecu.listeIngredients->debut();
    while (iter_ingredientReservation) {

        // Si ingredient reservation egal pas 0.
        if (iter_ingredientReservation.valeur()) {

            ArbreMap<std::string, ListeInventaires>::Iterateur iter_inventaire = inventaireRecu.rechercher(
                    iter_ingredientReservation.cle());
            if (iter_inventaire) {

                ArbreMap<Date, int>::Iterateur iter_qteDateInventaire = iter_inventaire.valeur().listeInventaires.debut();
                while (iter_qteDateInventaire) {

                    if (iter_qteDateInventaire.cle() <= date_HorlogeRecu ||
                        iter_qteDateInventaire.valeur() == 0) { //Enlever les perimes
                        iter_inventaire.valeur().quantiteTotal -= iter_qteDateInventaire.valeur();
                        iter_inventaire.valeur().listeInventaires.enlever(iter_qteDateInventaire.cle());
                    }

                    if (date_HorlogeRecu < iter_qteDateInventaire.cle()) {
                        break;
                    }
                    ++iter_qteDateInventaire;
                }
            }
        }
        ++iter_ingredientReservation;
    }
}
