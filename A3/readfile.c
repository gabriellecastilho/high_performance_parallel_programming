#include <stdio.h>

int main() {
    double item;
    FILE	*file;

    //file = fopen("result.gal", "r");
    //file = fopen("ellipse_N_00010.gal", "r");
    file = fopen("ellipse_N_00010_after200steps.gal", "r");
    for (int j = 0; j < 12; j++) {
        fread(&item, sizeof(double), 1, file);
        printf("%f ", item);
    }
    fclose(file);
    return 0;
}