#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/

#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"
#include "pgm.h"

/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 Nihed et Ayoub
 100% degré de confiance
 **/
ImageGris lirePGM(string source) {
    ifstream PGM;
    PGM.open(source);
    if (not PGM)
    throw runtime_error("Fichier non trouve: "+source);

    string bit;
    PGM >> bit;
    int length;
    PGM >> length;
    int width;
    PGM >> width;
    int max;
    PGM >> max;

    double pixel;
    ImageGris img(length);

    for(int i = 0; i < length ;i++){
        img[i] = vector<double> (width);
        for(int j = 0; j < width ; j++){
            PGM >> pixel;
            img[i][j] = pixel;
        }
    }
    PGM.close();

    return img;

}


/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 Nihed et Ayoub
 100% degré de confiance
 **/
void ecrirePGM(ImageGris img, string cible) {
    ofstream PGM;
    PGM.open(cible);

    string bit = "P2";
    PGM << bit << endl;
    int length = img.size();
    PGM << length << " ";
    int width = img[0].size();
    PGM << width << endl;

    PGM << 255 << endl;

    for(int i = 0; i<img.size(); i++){
        for (int j = 0; j<img[i].size(); j++){
               PGM << img[i][j] << endl;
        }
    }

    PGM.close();
}

/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) {
    if (a.size() != b.size())  {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i=0; i<a[0].size(); i++)
        if (a[0].size() != b[i].size()) {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<a[0].size(); j++)
            if (abs(a[i][j] - b[i][j]) > precision) {
                cout << "Valeur differentes en position " << i << "," << j
             << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
}

/** Construit une image cliché d'une image en niveau de gris
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 Nihed et Ayoub
 100% degré de confiance
 **/
ImageGris inversePGM(ImageGris img) {
    ImageGris img_inv (img.size());

    for (int i = 0; i<img_inv.size(); i++){
        img_inv[i] = vector<double> (img[i].size());
        for (int j = 0; j< img_inv[i].size(); j++){
            img_inv[i][j] = 255 - img[i][j];
        }
    }
    return img_inv;
}
