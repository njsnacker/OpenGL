#include <iostream>
#include <ctime>
#define N 512
#define SIZE (N + 2) * (N + 2)
#define IX(i, j) ((i) + (N + 2) * (j))

static float u[SIZE], v[SIZE], u_prev[SIZE], v_prev[SIZE];
static float dens[SIZE], dens_prev[SIZE];
static float s[SIZE];

static float dt;

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}

void addSource(float *x, float *s, float dt)
{
    for (int i = 0; i < SIZE; i++)
    {
        x[i] += dt * s[i];
    }
}

void diffuse(int b, float *x, float *x0, float diff, float dt)
{
    int i, j, k;
    float a = dt * diff * N * N;
    for (k = 0; k < 20; k++)
    {
        for (i = 1; i <= N; i++)
        {
            for (j = 1; j <= N; j++)
            {
                x[IX(i, j)] = (x0[IX(i, j)] + a * (x[IX(i - 1, j)] + x[IX(i + 1, j)] + x[IX(i, j - 1)] + x[IX(i, j + 1)])) / (1 + 4 * a);
            }
        }
        //set_bnd ( N, b, x );
    }
}

void advect(int b, float *d, float *d0, float *u, float *v, float dt)
{
    int i, j, i0, j0, i1, j1;
    float x, y, s0, t0, s1, t1, dt0;
    dt0 = dt * N;
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N; j++)
        {
            x = i - dt0 * u[IX(i, j)];
            y = j - dt0 * v[IX(i, j)];
            if (x < 0.5)
                x = 0.5;
            if (x > N + 0.5)
                x = N + 0.5;
            i0 = (int)x;
            i1 = i0 + 1;
            if (y < 0.5)
                y = 0.5;
            if (y > N + 0.5)
                y = N + 0.5;
            j0 = (int)y;
            j1 = j0 + 1;
            s1 = x - i0;
            s0 = 1 - s1;
            t1 = y - j0;
            t0 = 1 - t1;
            d[IX(i, j)] = s0 * (t0 * d0[IX(i0, j0)] + t1 * d0[IX(i0, j1)]) + s1 * (t0 * d0[IX(i1, j0)] + t1 * d0[IX(i1, j1)]);
        }
    }
    //set_bnd ( N, b, d );
}