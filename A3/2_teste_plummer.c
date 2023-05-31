#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x, y;
    double mass;
    double vx, vy;
    double b;
} particle;

void read_file(FILE *file, particle *p){
	fread(&p->x, sizeof(double), 1, file);
	fread(&p->y, sizeof(double), 1, file);
	fread(&p->mass, sizeof(double), 1, file);
	fread(&p->vx, sizeof(double), 1, file);
	fread(&p->vy, sizeof(double), 1, file);
	fread(&p->b, sizeof(double), 1, file);
}

void write_file(FILE *file, particle *p){
	fwrite(&p->x, sizeof(double), 1, file);
	fwrite(&p->y, sizeof(double), 1, file);
	fwrite(&p->mass, sizeof(double), 1, file);
	fwrite(&p->vx, sizeof(double), 1, file);
	fwrite(&p->vy, sizeof(double), 1, file);
	fwrite(&p->b, sizeof(double), 1, file);
}

int main(int argc, char const *argv[]) {
    argc = 5;

    int N = atoi(argv[1]);
    FILE	*file;
    int nsteps = atoi(argv[3]);
    double dt = (double)atof(argv[4]);

    int i, j, k;
    double ax, ay, dx, dy, dist, dist_e;
    double e = 0.001;
    double G = 100.0 / N;
    particle particles[N];
    
    file = fopen(argv[2], "r");
    for (j = 0; j < N; j++) {
        read_file(file, &particles[j]);
    }
    fclose(file);

    for (i = 0; i < nsteps; i++) {
        for (j = 0; j < N; j++) {
            ax = 0.0;
            ay = 0.0;
            for (k = 0; k < N; k++) {
                if (j != k) {
                    dx = particles[j].x - particles[k].x;
                    dy = particles[j].y - particles[k].y;
                    dist = sqrt(pow(dx,2) + pow(dy,2));
                    dist_e = (pow(dist + e,3));
                    ax += (particles[k].mass * dx) / dist_e;
                    ay += (particles[k].mass * dy) / dist_e;
                }
            }
            ax = - G * ax;
            ay = - G * ay;
            particles[j].vx += ax * dt;
            particles[j].vy += ay * dt;
        }
        for (j = 0; j < N; j++) {
            particles[j].x += particles[j].vx * dt;
            particles[j].y += particles[j].vy * dt;
        }
    }
    for (i = 0; i < 2; i++) {
        printf("Position of particle %d: (%.2f, %.2f)\n", i, particles[i].x, particles[i].y);
        printf("Velocity of particle %d: (%.2f, %.2f)\n", i, particles[i].vx, particles[i].vy);
    }
    file = fopen("result.gal", "w");
    for (j = 0; j < N; j++) {
        write_file(file, &particles[j]);
    }
    fclose(file);
    double item;
    file = fopen("ellipse_N_00010_after200steps.gal", "r");
    for (j = 0; j < 12; j++) {
        fread(&item, sizeof(double), 1, file);
        printf("%f ", item);
    }
    fclose(file);
    return 0;
}
