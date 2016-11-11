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

#if !defined(__ARBRE_MAP_H__)
#define __ARBRE_MAP_H__

#include "arbreavl.h"

template <class K, class V>
class ArbreMap {

    class Entree {
    public:

        Entree(const K& c) : cle(c), valeur() {
        }
        K cle;
        V valeur;

        bool operator<(const Entree &e) const {
            return cle < e.cle;
        }

        void operator=(const Entree& e) {
            cle = e.cle;
            valeur = e.valeur;
        }
    };

private:
    ArbreAVL<Entree> entrees;

public:
    bool contient(const K&) const;
    void enlever(const K&);
    void vider();

    const V& operator[] (const K&) const;
    V& operator[] (const K&);
    ArbreMap<K, V>& operator=(const ArbreMap<K, V>& entreesRecu);


    class IterateurConst {
    public:

        IterateurConst(const ArbreMap& a) : iter(a.entrees.debut()) {
        }

        IterateurConst(typename ArbreAVL<Entree>::Iterateur i) : iter(i) {
        }

        operator bool() const {
            return iter;
        }

        bool operator!() const {
            return !iter;
        }

        IterateurConst& operator++() {
            ++iter;
            return *this;
        }

        const K& cle() const {
            return (*iter).cle;
        }

        const V& valeur() const {
            return (*iter).valeur;
        }

    private:
        typename ArbreAVL<Entree>::Iterateur iter;
        friend class ArbreMap;
    };

    class Iterateur {
    public:

        Iterateur(const ArbreMap& a) : iter(a.entrees.debut()) {
        };

        Iterateur(typename ArbreAVL<Entree>::Iterateur i) : iter(i) {
        };

        operator bool() const {
            return iter;
        }

        bool operator!() const {
            return !iter;
        }

        Iterateur& operator++() {
            ++iter;
            return *this;
        };

        K& cle() {
            return (*iter).cle;
        };

        V& valeur() {
            return (*iter).valeur;
        };

    private:
        typename ArbreAVL<Entree>::Iterateur iter;
        friend class ArbreMap;
    };


    Iterateur debut() {
        return Iterateur(*this);
    }

    Iterateur fin() {
        return Iterateur(entrees.fin());
    }

    Iterateur rechercher(const K& cle) {
        return Iterateur(entrees.rechercher(cle));
    }

    Iterateur rechercherEgalOuSuivant(const K& cle) {
        return Iterateur(entrees.rechercherEgalOuSuivant(cle));
    }

    Iterateur rechercherEgalOuPrecedent(const K& cle) {
        return Iterateur(entrees.rechercherEgalOuPrecedent(cle));
    }


    IterateurConst debut() const {
        return IterateurConst(*this);
    }

    const IterateurConst fin() const {
        return IterateurConst(entrees.fin());
    }

    const IterateurConst rechercher(const K& cle) const {
        return IterateurConst(entrees.rechercher(cle));
    }

    const IterateurConst rechercherEgalOuSuivant(const K& cle) const {
        return IterateurConst(entrees.rechercherEgalOuSuivant(cle));
    }

    const IterateurConst rechercherEgalOuPrecedent(const K& cle) const {
        return IterateurConst(entrees.rechercherEgalOuPrecedent(cle));
    }

};

////////////////////////////////////////////
template <class K, class V>
void ArbreMap<K, V>::vider() {
    entrees.vider();
}

//////////////////////
template <class K, class V>
void ArbreMap<K, V>::enlever(const K& c) {
    entrees.enlever(Entree(c));
}

//////////////////////
template <class K, class V>
bool ArbreMap<K, V>::contient(const K& cleRecu) const {
    return entrees.contient(cleRecu);
}

//////////////////////
template <class K, class V>
const V& ArbreMap<K, V>::operator[] (const K& cleRecu) const {
    return (*(entrees.rechercher(cleRecu))).valeur;
}

//////////////////////
template <class K, class V>
V& ArbreMap<K, V>::operator[] (const K& cleRecu) {
    const Entree entreeTemp(cleRecu);
    typename ArbreAVL<Entree>::Iterateur iter = entrees.rechercher(entreeTemp);
    if (!iter) {
        entrees.inserer(entreeTemp);
        iter = entrees.rechercher(entreeTemp);
    }
    return (*iter).valeur;
}

//////////////////////
template <class K, class V>
ArbreMap<K, V>& ArbreMap<K, V>::operator=(const ArbreMap<K, V>& entreesRecu) {
    entrees = entreesRecu.entrees;
    return *this;
}

#endif