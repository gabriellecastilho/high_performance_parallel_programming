#include <stdio.h>
#include <math.h>

#define G 100.0/10.0 //6.6743e-11 // Gravitational constant

int main() {
    int n = 10.0;  // Number of particles
    double pos[n][2];  // Position of particles (x, y)
    double mass[n];  // Mass of particles
    double vel[n][2];  // Force on particles (x, y)
    double bri[n];
    double acc[n][2];  // Force on particles (x, y)
    double delta_t = 0.00001;
    int nsteps = 200;
    FILE *file;
    double e = 0.001;

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
    for (int k = 0; k < nsteps; k++) {
        for (int i = 0; i < n; i++) {
            acc[i][0] = 0.0;
            acc[i][1] = 0.0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    double r = sqrt(pow(pos[i][0] - pos[j][0], 2) + pow(pos[i][1] - pos[j][1], 2));
                    acc[i][0] += - G * (mass[j] * (pos[i][0] - pos[j][0])) / pow(r + e,3);
                    acc[i][1] += -G * (mass[j] * (pos[i][1] - pos[j][1])) / pow(r + e,3);
                }
            }
            vel[i][0] += acc[i][0] * delta_t;
            vel[i][1] += acc[i][1] * delta_t;
        }
        for (int i = 0; i < n; i++) {
            pos[i][0] += vel[i][0] * delta_t;
            pos[i][1] += vel[i][1] * delta_t;
        }
    }
    // Print force on each particle
    for (int i = 0; i < 2; i++) {
        //printf("Force on particle %d: (%.2f, %.2f)\n", i, force[i][0], force[i][1]);
        printf("Position of particle %d: (%.2f, %.2f)\n", i, pos[i][0], pos[i][1]);
        printf("Velocity of particle %d: (%.2f, %.2f)\n", i, vel[i][0], vel[i][1]);
    }

    file = fopen("result.gal", "w");
    for (int j = 0; j < n; j++) {
        fwrite(&pos[j][0], sizeof(double), 1, file);
        fwrite(&pos[j][1], sizeof(double), 1, file);
        fwrite(&mass[j], sizeof(double), 1, file);
        fwrite(&vel[j][0], sizeof(double), 1, file);
        fwrite(&vel[j][1], sizeof(double), 1, file);
        fwrite(&bri[j], sizeof(double), 1, file);
    }
    fclose(file);

    double item;
    file = fopen("ellipse_N_00010_after200steps.gal", "r");
    for (int j = 0; j < 12; j++) {
        fread(&item, sizeof(double), 1, file);
        printf("%f ", item);
    }
    fclose(file);
    return 0;
}
