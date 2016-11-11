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

#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>

Date::Date() {
    jours = heures = minutes = -1;
}

Date::Date(int jourRecu, int heureRecu, int minRecu) {
    jours = jourRecu;
    heures = heureRecu;
    minutes = minRecu;
}

//////////////////////
bool Date::operator<(const Date& d) const {

    if (d.jours < jours) return false;
    if (d.jours > jours) return true;

    if (d.heures < heures) return false;
    if (d.heures > heures) return true;

    if (d.minutes < minutes) return false;
    if (d.minutes > minutes) return true;

    return false;
}

//////////////////////
bool Date::operator <=(const Date& d) const {
    if (*this < d || (jours == d.jours && heures == d.heures && minutes == d.minutes)) return true;
    return false;
}

//////////////////////
std::ostream& operator <<(std::ostream& os, const Date& d) {
    //int jours, heures, minutes;
    char chaine[40];
    sprintf(chaine, "%dj_%02dh%02dm", d.jours, d.heures, d.minutes);
    os << chaine;
    return os;
}

//////////////////////
std::istream& operator >>(std::istream& is, Date& d) {
    char j, m, h, underscore;
    is >> d.jours >> j >> underscore >> d.heures >> h >> d.minutes >> m;
    assert(j == 'j');
    assert(underscore == '_');
    assert(h == 'h' && m == 'm');
    return is;
    
}

//////////////////////
Date Date::operator =(const Date& dateRecu) {
    jours = dateRecu.jours;
    heures = dateRecu.heures;
    minutes = dateRecu.minutes;
    return *this;
}
