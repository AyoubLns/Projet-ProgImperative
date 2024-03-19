/** @file
 * Structures de données pour représenter des images
 **/

#ifndef _IMAGE_H
#define _IMAGE_H
#include <vector>
using namespace std;

// Ecrire votre code ici
typedef vector<vector<int>> ImageNB;
typedef vector<vector<double>> ImageGris;

struct Couleur {
    /** Intensite de rouge **/
    double r;
    /** Intensite de vert **/
    double g;
    /** Intensite de bleu **/
    double b;
};

typedef vector<vector<Couleur>> Image;
#endif
