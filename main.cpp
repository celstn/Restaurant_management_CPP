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
#include <fstream>
#include "inventaire.h"

using namespace std;

int main(int argc, const char **argv) {
    Restaurant resto;
    if (argc > 1) {
        std::ifstream entree_fichier(argv[1]);
        if (entree_fichier.fail()) {
            std::cerr << "Erreur d'ouverture du fichier '" << argv[1] << "'" << std::endl;
            return 1;
        }
        return resto.ouvrir(entree_fichier);
    } else
        return resto.ouvrir(std::cin);
}
