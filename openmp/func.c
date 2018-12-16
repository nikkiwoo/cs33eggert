#include "func.h"
#include "util.h"

void func0(double *weights, double *arrayX, double *arrayY, int xr, int yr, int n)
{
    int i;
    for(i = 0; i < n; i++){
      weights[i] = 1/((double)(n));
        arrayX[i] = xr;
        arrayY[i] = yr;
    }
}

void func1(int *seed, int *array, double *arrayX, double *arrayY,
			double *probability, double *objxy, int *index,
			int Ones, int iter, int X, int Y, int Z, int n)
{
    int i, j;
    int index_X, index_Y;
    int max_size = X*Y*Z;
    int One = Ones;
    int localn = n;
    int localY = Y;
    int localZ = Z;
#pragma omp parallel for firstprivate(localn)
    for(i = 0; i<localn; i++){
      arrayX[i] += 1 + 5*rand2(seed,i);
      arrayY[i] += -2 + 2*rand2(seed,i);
      probability[i] = 0;
#pragma omp parallel for private(index_X) private(index_Y) firstprivate(max_size) firstprivate(One) firstprivate(localZ)
      for(j=0; j < One; j++){
            index_X = round(arrayX[i]) + objxy[j*2 + 1];
            index_Y = round(arrayY[i]) + objxy[j*2];
            index[i*One + j] = fabs(index_X*Y*localZ + index_Y*localZ + iter);
            if(index[i*One + j] >= max_size)
	      {
                index[i*One + j] = 0;
	      }
	    probability[i] += (pow((array[index[i*One + j]] - 100),2) -
                               pow((array[index[i*One + j]]-228),2))/50.;
        }
      probability[i] = probability[i]/((double)(One));
    }
}

void func2(double *weights, double *probability, int n)
{
	int i;
	double sumWeights=0;
	#pragma omp parallel for reduction(+:sumWeights)
	for(i = 0; i < n; i++) {
	  weights[i] = weights[i] * exp(probability[i]);
	  sumWeights += weights[i];
	}
	
   	
	#pragma omp parallel for firstprivate(sumWeights)
	for(i = 0; i < n; i++)
	weights[i] = weights[i]/sumWeights;
}

void func3(double *arrayX, double *arrayY, double *weights, double *x_e, double *y_e, int n)
{
	double estimate_x=0.0;
	double estimate_y=0.0;
		
    int i;
    /*        for(i = 0; i < n; i+=4){
      estimate_x += arrayX[i] * weights[i];
      estimate_y += arrayY[i] * weights[i];
      estimate_x += arrayX[i+1] * weights[i+1];
      estimate_y += arrayY[i+1] * weights[i+1];
      estimate_x += arrayX[i+2] * weights[i+2];
      estimate_y += arrayY[i+2] * weights[i+2];
      estimate_x += arrayX[i+3] * weights[i+3];
      estimate_y += arrayY[i+3] * weights[i+3];
    }
    for(; i < n; i++) {
      estimate_x += arrayX[i] * weights[i];
      estimate_y += arrayY[i] * weights[i];
      }*/

#pragma omp parallel for reduction(+:estimate_x) reduction(+:estimate_y)
    for(i = 0; i < n; i++){
   		estimate_x += arrayX[i] * weights[i];
   		estimate_y += arrayY[i] * weights[i];
		}
    
	*x_e = estimate_x;
	*y_e = estimate_y;

}

void func4(double *u, double u1, int n)
{
	int i; /*
	for(i = 0; i < n; i+=4){
	  u[i] = u1 + i/((double)(n));
	  u[i+1] = u1 + i/((double)(n));
	  u[i+2] = u1 + i/((double)(n));
	  u[i+3] = u1 + i/((double)(n));
	}
	for (; i< n; i++) {
	  u[i] = u1 + i/((double)(n));
	}*/

#pragma omp parallel for
	for(i = 0; i < n; i++){
   		u[i] = u1 + i/((double)(n));
   	}
}

void func5(double *x_j, double *y_j, double *arrayX, double *arrayY, double *weights, double *cfd, double *u, int n)
{
	int i, j;
	int localn = n;
	#pragma omp parallel for firstprivate(localn)
	for(j = 0; j < localn; j++){
   		//i = findIndex(cfd, n, u[j]);
   		i = findIndexBin(cfd, 0, n, u[j]);
   		if(i == -1)
   			i = localn-1;
   		x_j[j] = arrayX[i];
   		y_j[j] = arrayY[i];

   	}
#pragma omp parallel for firstprivate(localn)
	for(i = 0; i < localn; i++){
		arrayX[i] = x_j[i];
		arrayY[i] = y_j[i];
		weights[i] = 1/((double)(n));
	}
}
