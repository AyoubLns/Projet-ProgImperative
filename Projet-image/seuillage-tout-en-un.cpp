#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double>> ImageGris;


/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl


/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};


/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 Ayoub
100% degré de confiance
 **/

ImageGris intensiteH(ImageGris image) {
    int height = image.size();
    int width = image[0].size();
    ImageGris img_renv (height);

    // parcours de l'image
    for (int i = 0; i < height; i++) {
        img_renv[i] = vector<double> (width);
        for (int j = 0; j < width; j++) {
            if ((i == 0 or j == 0) or (i == height - 1 or j == width - 1)){
                 img_renv[i][j] = 0;
            } else {
                img_renv[i][j] = image[i-1][j-1] + 2 * image[i][j-1] + image[i+1][j-1] - image[i-1][j+1] - 2 * image[i][j+1] - image[i+1][j+1];
            }
        }
    }
    return img_renv;
}



/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
 Ayoub
100% degré de confiance
 **/
ImageGris intensiteV(ImageGris image) {
    int height = image.size();
    int width = image[0].size();
    ImageGris img_renv (height);

    // parcours de l'image
    for (int i = 0; i < height; i++) {
        img_renv[i] = vector<double> (width);
        for (int j = 0; j < width; j++) {
            if ((i == 0 or j == 0) or (i == height - 1 or j == width - 1)){
                 img_renv[i][j] = 0;
            } else {
                img_renv[i][j] = image[i-1][j-1] + 2 * image[i-1][j] + image[i-1][j+1] - image[i+1][j-1] - 2 * image[i+1][j] - image[i+1][j+1];
            }
        }
    }
    return img_renv;
}



/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 Ayoub
100% degré de confiance
 **/
ImageGris intensite(ImageGris image) {
    int height = image.size();
    int width = image[0].size();
    ImageGris img_renv (height);
    
    ImageGris Horizontal = intensiteH(image);
    ImageGris Vertical = intensiteV(image);

    // parcours de l'image
    for (int i = 0; i < height; i++) {
        img_renv[i] = vector<double> (width);
        for (int j = 0; j < width; j++) {
            if ((i == 0 or j == 0) or (i == height - 1 or j == width - 1)){
                 img_renv[i][j] = 0;
            } else {
                img_renv[i][j] = sqrt(Horizontal[i][j] * Horizontal[i][j] + Vertical[i][j] * Vertical[i][j]);
            }
        }
    }
    return img_renv;
}



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



/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
Ayoub
90% degré de confiance
 **/
ImageGris renormalise(ImageGris img) {
    
    ImageGris img_ret (img.size());
    int max = img[0][0];
    int min = img[0][0];
    for (int i = 0; i < img.size(); i++) {
        for (int j = 0; j < img[0].size(); j++) {
            if (img[i][j] > max){
                max = img[i][j];
            }
            if (img[i][j] < min){
                min = img[i][j];
            }
        }
    }

    for (int i = 0; i < img.size(); i++) {
        img_ret[i] = vector<double> (img[0].size());
        for (int j = 0; j < img[0].size(); j++) {
            if (img[i][j] < 0){
                img_ret[i][j] = 0;
            }else{
                img_ret[i][j] = (img[i][j] * 255) / (max-min);
            }
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
    
    ImageGris img_ret(img.size());
        
    for(int i=0; i<img.size(); i++){
        img_ret[i] = vector<double> (img[0].size());
        for(int j=0; j<img[0].size(); j++){
            if(img[i][j]>=seuil){
                img_ret[i][j]=0.;
            }else{
                img_ret[i][j]=255.;
            }
        }
   }
   return img_ret;
}


/** Filtre de double seuillage
 * @param imgIntensite image d'intensite
 * @param imgContour image codant un ensemble de pixels selectionnes
 * @param seuil un entier de l'intervalle [0,255]
 * @return une copie d'imgIntensite modifiee de sorte que:
 *  -si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *  -sinon pixel blanc
 **/
/**
ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction doubleSeuillage non implantée ligne 124");
}
**/

/** Filtre de double seuillage iteratif
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @param nbAmeliorations un entier non negatif: le nombre d'itérations
 * @return le double seuillage de img
 **/
/**
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    // Remplacer la ligne suivante par le code adéquat
    throw runtime_error("Fonction doubleSeuillage non implantée ligne 137");
}
**/


void seuillageTest() {
    CHECK( ImageGrisEgal(seuillage( imgGrisTest, 80),
              ImageGris( {
                  {255, 0, 255, 0},
                  {255, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(seuillage( intensite(imgGrisTest), 80),
              ImageGris( {
                  {255, 255, 255, 255},
                  {255, 0, 0, 255},
                  {255, 255, 0, 255},
                  {255, 255, 255, 255}
              }),
              0.001) );
    /**CHECK( ImageGrisEgal(doubleSeuillage(intensite(imgGrisTest), 400, 80, 4 ),
                          ImageGris( {
                              {255, 255, 255, 255},
                              {255, 0, 0, 255},
                              {255, 255, 0, 255},
                              {255, 255, 255, 255}
                          }),
                          0.001) );
    */

    cout << "Vérifier que les images obtenues dans 'seuillage/' sont semblables à celles fournies dans 'seuillage/correction/'" << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/Billes.256.pgm")), 80), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Lena.512.pgm"  )), 80), "seuillage/Lena.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.ppm et House.256.ppm" << endl;
}

/**
    void doubleSeuillageTest(){
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;

    ecrirePGM(doubleSeuillage(lirePGM("images/Lena.512.pgm"),
                              seuillage(intensite(lirePGM("images/Lena.512.pgm" )),80),70),
              "seuillage_double/Lena-unpas.512.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Billes.256.pgm")), 500, 80, 100), "seuillage_double/Billes.256.pgm");
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Lena.512.pgm"  )), 500, 80, 100), "seuillage_double/Lena.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.ppm et House.256.ppm" << endl;
}
**/


int main(){

    seuillageTest();
    //doubleSeuillageTest();

    return 0;
}

