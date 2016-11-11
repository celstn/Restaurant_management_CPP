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
#if !defined(_DATE__H_)
#define _DATE__H_

#include <iostream>

class Date {
public:
    Date();
    Date(int jourRecu, int heureRecu, int minRecu);

    bool operator<(const Date& date) const;
    bool operator==(const Date& date) const;

    bool operator <=(const Date& date) const;
    Date operator =(const Date& date);

private:
    int jours, heures, minutes;

    friend std::ostream& operator <<(std::ostream&, const Date& date);
    friend std::istream& operator >>(std::istream&, Date& date);
};
#endif
