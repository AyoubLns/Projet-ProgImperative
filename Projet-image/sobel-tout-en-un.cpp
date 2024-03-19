#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;



/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cout << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl


/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};



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


void testSobel() {
    CHECK( ImageGrisEgal(intensiteH(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -373.47, 227.507, 0},
                  {0, -22.1312, 323.866, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensiteV(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -15.1398, 150.501, 0},
                  {0, -9.0336, 273.023, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensite(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, 373.777, 272.782, 0},
                  {0, 23.9039, 423.593, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );

    cout << "Vérifier que les images obtenues dans 'sobel/' sont semblables à celles fournies dans 'sobel/correction/'" << endl;
    ecrirePGM(intensite(lirePGM("images/Billes.256.pgm" )), "sobel/Billes.256.pgm");
    ecrirePGM(intensite(lirePGM("images/House.256.pgm"  )), "sobel/House.256.pgm");

}



int main(){

    testSobel();
    return 0 ;
}
