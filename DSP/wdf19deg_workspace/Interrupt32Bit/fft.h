#ifndef FFT_H_
#define FFT_H_
#include <math.h>

/* Define complex multiplication and its conjugate */
#define  rmul(x,y)      (x.re * y.re - x.im * y.im)
#define  imul(x,y)      (x.im * y.re + x.re * y.im)
#define rcmul(x,y)      (x.re * y.re + x.im * y.im)
#define icmul(x,y)      (x.im * y.re - x.re * y.im)

/* Declare the structure to hold complex numbers */
typedef struct{
	double re;
	double im;
}complex;
int fft(int lx, complex *cx, float signi, float sc);

#endif /* FFT_H_ */
