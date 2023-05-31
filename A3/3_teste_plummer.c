#include <stdio.h>
#include <math.h>

#define G 10/10 //6.6743e-11  // Gravitational constant

int main() {
    int n = 10;  // Number of particles
    double mass[n];  // Mass of particles
    double pos[n][2];  // Position of particles (x, y)
    double vel[n][2];  // Force on particles (x, y)
    double force[n][2];  // Force on particles (x, y)
    double bri[n];
    FILE *file;

    // Assign values to mass and pos arrays
    // ...
    file = fopen("ellipse_N_00010.gal", "r");
    for (int j = 0; j < n; j++) {
        fread(&pos[j][0], sizeof(double), 1, file);
        fread(&pos[j][1], sizeof(double), 1, file);
        fread(&mass[j], sizeof(double), 1, file);
        fread(&vel[j][0], sizeof(double), 1, file);
        fread(&vel[j][1], sizeof(double), 1, file);
        fread(&bri[j], sizeof(double), 1, file);
    }
    fclose(file);

    // Calculate force on each particle
    for (int i = 0; i < n; i++) {
        force[i][0] = 0;
        force[i][1] = 0;
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            double r = sqrt(pow(pos[i][0] - pos[j][0], 2) + pow(pos[i][1] - pos[j][1], 2));
            double f = G * mass[i] * mass[j] / pow(r, 2);
            force[i][0] += f * (pos[j][0] - pos[i][0]) / r;
            force[i][1] += f * (pos[j][1] - pos[i][1]) / r;
        }
    }

    // Print force on each particle
    for (int i = 0; i < n; i++) {
        //printf("Force on particle %d: (%.2f, %.2f)\n", i, force[i][0], force[i][1]);
        printf("Position of particle %d: (%.2f, %.2f)\n", i, pos[i][0], pos[i][1]);
    }

    return 0;
}
