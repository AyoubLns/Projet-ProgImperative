#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include "image.h"
#include "sobel.h"

/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
Ayoub
100% degré de confiance
 **/
ImageGris renormalise(ImageGris img) {
    
    ImageGris img_ret (img.size());
    int max = 0;

    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; j < img[0].size(); j++) {
            if (img[i][j] > max) max = img[i][j];
        }
    }

    for (int i = 0; i < img.size(); i++) {
        img_ret[i] = vector<double> (img[0].size());
        for (int j = 0; j < img[0].size(); j++) {
            img_ret[i][j] = img[i][j] * 255 / max;
        }
    }

    return img_ret;
}

/** Filtre de seuillage
 * @param img
 * @param seuil un entier dans l'intervalle [0,255]
 * @return image en noir et blanc obtenue en remplacant la teinte de
 *  chaque pixel par
 *  - du blanc si teinte < seuil
 *  - du noir  si teinte > seuil
Ayoub
100% degré de confiance
 **/
ImageGris seuillage(ImageGris img, int seuil) { 
    for(int i=0; i<img.size(); i++){
        for(int j=0; j<img[0].size(); j++){
            if(img[i][j]>=seuil){
                img[i][j]=0.;
            }else{
                img[i][j]=255.;
            }
        }
   }return img;
}

/*ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction doubleSeuillage non implantée ligne 27");
}

ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction doubleSeuillage non implantée ligne 32");
}
*/

