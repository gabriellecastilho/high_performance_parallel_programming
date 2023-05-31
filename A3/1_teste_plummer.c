#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    double  x, y;
    double  m;
    double  vx, vy;
    double  b;
} particle;

void read_part(FILE *file, particle *p)
{
	fread(&p->x, sizeof(double), 1, file);
	fread(&p->y, sizeof(double), 1, file);
	fread(&p->m, sizeof(double), 1, file);
	fread(&p->vx, sizeof(double), 1, file);
	fread(&p->vy, sizeof(double), 1, file);
	fread(&p->b, sizeof(double), 1, file);
}

void write_part(FILE *file, particle *p)
{
	fwrite(&p->x, sizeof(double), 1, file);
	fwrite(&p->y, sizeof(double), 1, file);
	fwrite(&p->m, sizeof(double), 1, file);
	fwrite(&p->vx, sizeof(double), 1, file);
	fwrite(&p->vy, sizeof(double), 1, file);
	fwrite(&p->b, sizeof(double), 1, file);
}

void get_acc(particle *p1, particle *p2, double *ax, double *ay, double N)
{
    const double  G = 100.0 / N;
    const double  e = 0.001;
    double  r = sqrt(pow((p1->x - p2->x), 2) + pow((p1->y - p2->y), 2));
    *ax += - G *(p2->m * (p1->x - p2->x)) / pow(r + e, 3);
    *ay += - G * (p2->m * (p1->y - p2->y)) / pow(r + e, 3);
}

void update_vel(particle *p, double ax, double ay, double delta_t)
{
    p->vx += ax * delta_t;
    p->vy += ay * delta_t;
}

void update_pos(particle *p, double delta_t)
{
    p->x += p->vx * delta_t;
    p->y += p->vy * delta_t;
}

int main(int argc, char const *argv[])
{
    if (argc != 6)
        printf("Error: give 5 input args (N filename nsteps delta_t graphics)\n");
    else
    {
        const int      N = atoi(argv[1]);
        const int      nsteps = atoi(argv[3]);
        const double   delta_t = (double)atof(argv[4]);

        int      i, j, k;
        double   ax, ay;
        particle part[N];
        FILE	 *file;

        file = fopen(argv[2], "r");
        for (j = 0; j < N; j++)
            read_part(file, &part[j]);
        fclose(file);

        for (i = 0; i < nsteps; i++) {
            for (j = 0; j < N; j++) {
                ax = 0.0;
                ay = 0.0;
                for (k = 0; k < N; k++)
                    if (j != k)
                        get_acc(&part[j], &part[k], &ax, &ay, N);
                update_vel(&part[j], ax, ay, delta_t);
            }
            for (j = 0; j < N; j++)
                update_pos(&part[j], delta_t);
        }

        file = fopen("result.gal", "w");
        for (j = 0; j < N; j++)
            write_part(file, &part[j]);
        fclose(file);
    }
    return (0);
}
