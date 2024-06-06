#include "mat.h"
#include "newton.h"
#include <stdio.h>
#include <stdlib.h>

double f(double);

int main() {
  double tolerancia = 1e-5;
  int max_passos = 10;

  Newton n = newton_criar(&f, tolerancia, max_passos);
  if (n == NULL) {
    fprintf(stderr, "Falha na alocação de memória para Newton\n");
    return EXIT_FAILURE;
  }

  double x[] = {5.0, 8.0};
  int nr_raizes = 2;
  Zero zeros = (Zero)malloc(nr_raizes * sizeof(struct zero));

  if (zeros == NULL) {
    fprintf(stderr, "Falha na alocação de memória para zeros\n");
    newton_destruir(n);
    return EXIT_FAILURE;
  }

  Status status = newton_procurar_zero(n, x, zeros, nr_raizes);

  if (status == SUCESSO) {
    for (int i = 0; i < nr_raizes; i++) {
      if (zeros[i].status == SUCESSO) {
        printf("Vizinhança de x=%g => Raiz encontrada: %g\n", x[i],
               zeros[i].zero);
      } else {
        printf("Não foi encontrada uma raiz na vizinhança de x=%g\n", x[i]);
      }
    }
  }

  newton_destruir(n);

  if (zeros != NULL) {
    free(zeros);
  }

  return EXIT_SUCCESS;
}

double f(double x) { return 0 }