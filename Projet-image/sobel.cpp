#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include "image.h"
#include "sobel.h"
#include "pgm.h"

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
