#include <stdexcept>
/** @file
 * Affichage d'une image PBM
 **/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param source le nom d'un fichier PBM
 Nihed et Ayoub
 100% degré de confiance
 **/
void affichePBM(string source){
    ifstream PBM;
    PBM.open(source);

    string bit;
    PBM >> bit;
    int length;
    PBM >> length;
    int width;
    PBM >> width;

    for(int i = 0; i < width; i++){
        for(int j = 0; j < length; j++){
            PBM >> bit;
            if (bit == "0"){
                cout << " ";
            }else{
                cout << "@";
            }
        }
        cout << endl;
    }
    PBM.close();
}

/** Echange le noir et le blanc dans une image PBM
 * @param source le nom du fichier PBM à lire
 * @param cible le nom du nouveau fichier PMB créé
 Nihed et Ayoub
 100% degré de confiance
 **/
void inversePBM(string source, string cible) {
    ifstream PBM;       //saisir du fichier
    PBM.open(source);

    ofstream PBMinv;    //génerer le fichier
    PBMinv.open(cible);

    string bit;
    PBM >> bit;
    PBMinv << bit << endl;
    int length;
    PBM >> length;
    PBMinv << length << " ";
    int width;
    PBM >> width;
    PBMinv << width << endl;

    for(int i = 0; i < width; i++){
        for(int j = 0; j < length; j++){
            PBM >> bit;
            if (bit == "0"){
                PBMinv << 1 << " ";
            }else{
                PBMinv << 0 << " ";
            }
        }
        PBMinv << endl;
    }
    PBM.close();
    PBMinv.close();
}


int main(){
    cout << "Affichage du smiley " << endl;
    affichePBM("./images/smiley.pbm");
    cout << "Fabrication du smiley inversé (vérifiez que le nouveau fichier a été créé dans le dosier pbm/smiley-inverse.pbm" << endl;
    inversePBM("images/smiley.pbm","pbm/smiley-inverse.pbm");
    cout << "Affichage du smiley inversé" << endl;
    affichePBM("./pbm/smiley-inverse.pbm");
    return 0;
}
