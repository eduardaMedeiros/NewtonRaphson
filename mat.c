#include "mat.h"

static double pot(double base, int exp) {
  if (exp == 0)
    return 1.0;
  return base * pot(base, exp - 1);
}

static double ang(double x) {
  double dois_pi = 2.0 * PI;

  int k = (int)(x / dois_pi);
  x -= k * dois_pi;

  if (x > PI) {
    x -= dois_pi;
  } else if (x < -PI) {
    x += dois_pi;
  }

  return x;
}

double abst(double x) { 
  return (x >= 0) ? x : -x; 
}

double sin(double x) {
  x = ang(x);
  double term = x;
  double result = term;
  for (int n = 1; abst(term) > TOLERANCIA; n++) {
    term *= -x * x / ((2 * n) * (2 * n + 1));
    result += term;
  }
  return result;
}

double cos(double x) {
  x = ang(x);
  double term = 1;
  double result = term;
  for (int n = 1; abst(term) > TOLERANCIA; n++) {
    term *= -x * x / ((2 * n - 1) * (2 * n));
    result += term;
  }
  return result;
}

static double exp_recursiva(double x, double term, int n) {
  if (abst(term) < TOLERANCIA) {
    return 0.0;
  }
  return term + exp_recursiva(x, term * x / n, n + 1);
}

double exp(double x) { 
  return 1.0 + exp_recursiva(x, x, 1); 
}

double ln(double x) {
  if (x <= 0) {
    return -INFINITO;
  }
  double y = (x - 1) / (x + 1);
  double term = y;
  double result = term;
  for (int n = 1; abst(term) > TOLERANCIA; n++) {
    term *= pot(y, 2) * (2 * n - 1) / (2 * n + 1);
    result += term;
  }
  return 2 * result;
}

double sqrt(double x) {
  if (x < 0) {
    return -INFINITO;
  }
  double guess = x / 2.0;
  double next_guess;
  do {
    next_guess = 0.5 * (guess + x / guess);
    if (abst(next_guess - guess) < TOLERANCIA)
      break;
    guess = next_guess;
  } while (1);
  return next_guess;
}