#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
using namespace std;

/** Structure de données pour représenter une image binaire **/
typedef vector<vector<int>> ImageNB;


/** Construire une image binaire depuis un fichier PBM
 * @param source le nom d'un fichier PBM
 * @return une image binaire (0/1)
 Nihed et Ayoub
 100% degré de confiance
 **/
ImageNB lirePBM(string source) {
    ifstream PBM;
    PBM.open(source);
    if (not PBM){
        throw runtime_error("Fichier non trouve: "+source);
    }
    
    string bit;
    PBM >> bit;
    int length;
    PBM >> length;
    int width;
    PBM >> width;
    
    int pixel;
    ImageNB img(length);
    
    for(int i = 0; i < length ;i++){
        img[i] = vector<int>(width);
        for(int j = 0; j < width ; j++){
            PBM >> pixel;
            img[i][j] = pixel; 
        }
    }
    PBM.close();
    
    return img;
}


/** Ecrit une image binaire dans un fichier PBM
 * @param img une image binaire (0/1)
 * @param cible le nom d'un fichier PBM
 Nihed et Ayoub
 100% degré de confiance
 **/

void ecrirePBM(ImageNB img, string cible) {
    ofstream PBM;
    PBM.open(cible);

    string bit = "P1";
    PBM << bit << endl;
    int length = img.size();
    PBM << length << " ";
    int width = img[0].size();
    PBM << width << endl;

    for(int i = 0; i < length; i++){
        for (int j = 0; j < width; j++){
            PBM << img[i][j] << " ";   
        }
        PBM << endl;
    }

    PBM.close();
}



/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param img une image binaire (0/1)
 Nihed et Ayoub
 100% degré de confiance
 **/
void affichePBM(ImageNB img) {
    for(int i = 0; i<img.size(); i++){
        for (int j = 0; j<img[i].size(); j++){
            if (img[i][j] == 0){ 
                cout << " ";
            }else{
                cout << "@";

            }
        }
        cout << endl;
    }
}


/** Echange le noir et le blanc dans une image PBM
 * @param img une image binaire (0/1)
 * @return l'image où le blanc et le noir ont été inversés
 Nihed et Ayoub
 100% degré de confiance
 **/
ImageNB inversePBM(ImageNB img) {
    ImageNB img_inv (img.size());
    
    for(int i = 0; i<img_inv.size(); i++){
        img_inv[i] = vector<int>(img[i].size());
        for (int j = 0; j<img_inv[i].size(); j++){
            if (img[i][j] == 0){ 
                img_inv[i][j] = 1;
            }else{
                img_inv[i][j] = 0;
            }
        }
    }
    return img_inv;
}

void testLirePBM(){
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(lirePBM("images/smiley.pbm"),  "pbm/smiley.pbm");
    ecrirePBM(lirePBM("images/cercle.pbm"),  "pbm/cercle.pbm");
    ecrirePBM(lirePBM("images/code.pbm"), "pbm/code.pbm");
    ecrirePBM(lirePBM("images/damier.pbm"), "pbm/damier.pbm");
}

int main(){
    testLirePBM();
    cout << "Tests des fonctions lirePPM et ecrirePPM" << endl;
    ImageNB img = lirePBM("images/smiley.pbm");
    cout << "Affichage du smiley " << endl;
    affichePBM(img);
    ImageNB reverse = inversePBM(img);
    cout << "Affichage du smiley inversé" << endl;
    affichePBM(reverse);
    return 0;
}


