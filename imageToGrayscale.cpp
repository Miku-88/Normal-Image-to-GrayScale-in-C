#include <stdio.h>
#include <stdlib.h>
#include "lodepng.h"

int main() {
    unsigned char *image;
    unsigned width, height, red, green, blue, alpha, gray;
    unsigned error;

    error = lodepng_decode32_file(&image, &width, &height, "four.png");

    if (error) {
        printf("Error %d: %s\n", error, lodepng_error_text(error));
        return 1;
    }

    for (unsigned i = 0; i < height; i++) {
        for (unsigned j = 0; j < width; j++) {
            red = image[4 * width * i + 4 * j + 0];
            green = image[4 * width * i + 4 * j + 1];
            blue = image[4 * width * i + 4 * j + 2];
            alpha = image[4 * width * i + 4 * j + 3];
            gray = (red + green + blue) / 3;

            image[4 * width * i + 4 * j + 0] = gray;
            image[4 * width * i + 4 * j + 1] = gray;
            image[4 * width * i + 4 * j + 2] = gray;
        }
    }

    error = lodepng_encode32_file("four_output.png", image, width, height);

    if (error) {
        printf("Error %d: %s\n", error, lodepng_error_text(error));
        free(image);
        return 1;
    }
    free(image);
    return 0;
}
