#ifndef NEWTON_H
#define NEWTON_H

#define INTERVALO 1e-7

typedef enum { ERRO, SUCESSO } Status;

typedef struct newton *Newton;
typedef struct zero *Zero;

typedef struct zero {
  Status status;
  double zero;
} zero;

typedef struct newton {
  double (*function)(double);
  double tolerancia;
  int max_passos;
} newton;


void newton_destruir(Newton n);
Newton newton_criar(double (*function)(double), double tolerancia, int max_passos);
Status newton_procurar_zero(Newton n, double *x, Zero zeros, int nr_raizes);

#endif