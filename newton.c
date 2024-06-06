#include "newton.h"
#include "mat.h"
#include <stdio.h>
#include <stdlib.h>

static double derivada(double (*function)(double), double x) {
  double h = INTERVALO * (abst(x) + 1.0);
  return (function(x + h) - function(x - h)) / (2 * h);
}

void newton_destruir(Newton n) {
  if (n != NULL) {
    free(n);
  }
}

Newton newton_criar(double (*function)(double), double tolerancia,
                    int max_passos) {
  Newton n = (Newton)malloc(sizeof(newton));
  n->function = function;
  n->tolerancia = tolerancia;
  n->max_passos = max_passos;
  return n;
}

Status newton_procurar_zero(Newton n, double *xs, Zero zeros, int nr_raizes) {
  for (int i = 0; i < nr_raizes; i++) {
    double x = xs[i];
    for (int passo = 0; passo < n->max_passos; passo++) {
      double fx = n->function(x);
      double dfx = derivada(n->function, x);

      if (dfx == 0.0) {
        zeros[i].status = ERRO;
        break;
      }

      double x1 = x - fx / dfx;
      if (abst(x1 - x) < n->tolerancia) {
        zeros[i].status = SUCESSO;
        zeros[i].zero = x1;
        break;
      }
      x = x1;
    }
    if (zeros[i].status != SUCESSO) {
      zeros[i].status = ERRO;
    }
  }
  return SUCESSO;
}
