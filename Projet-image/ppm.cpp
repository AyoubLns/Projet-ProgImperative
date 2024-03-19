#include <stdexcept>
/** @file
 * Lecture et écriture d'images au format PPM
 **/
#include <iostream>
#include <fstream>
#include "image.h"
#include "ppm.h"

/** Lit une image au format PPM, retourne un tableau de Couleur
* @param source vers une image .ppm
* @return une image
Ayoub
100% degré de confiance
**/
Image lirePPM(string source) {
    ifstream PPM;
    PPM.open(source);
    if (not PPM)
    throw runtime_error("Fichier non trouve: "+source);

    string bit ;
    PPM >> bit;
    int length;
    PPM >> length;
    int width;
    PPM >> width;
    int color_max;
    PPM >> color_max;

    Image img_red (length);
    for(int i = 0; i < length; i++){
        img_red[i] = vector<Couleur>(width);
        for(int j = 0; j < width; j++){
            Couleur pixel;
            PPM >> pixel.r;
            PPM >> pixel.g;
            PPM >> pixel.b;
            img_red[i][j] = pixel;
        }
    }
    PPM.close();

    return img_red;
}

/** ´Ecrit une image dans un fichier PPM
* @param img une image
* @param cible le nom d’un fichier PPM
Ayoub
100% degré de confiance
**/
void ecrirePPM(Image img, string cible) {
    ofstream PPM;
    PPM.open(cible);

    string bit = "P3";
    PPM << bit << endl;
    int length = img.size();
    PPM << length << " ";
    int width = img[0].size();
    PPM << width << endl;

    PPM << 255 << endl;

    for(int i = 0; i<img.size(); i++){
        for (int j = 0; j<img[i].size(); j++){
            PPM << img[i][j].r << " " << img[i][j].g << " " << img[i][j].b << " ";
        }
        PPM << endl;
    }

    PPM.close();
}
