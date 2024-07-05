// Vasile-Daniel DAN 
// 23 April 2024 

#include <stdio.h>
#include <math.h>

int main(){

    FILE  *fp = NULL; 

    fp = fopen("circle1data.txt", "w");

    if(fp == NULL){
        printf("Error opening the file");
        return 1; 
    }

    double x,y,r,delta; 

    r = 2; delta = 5e-3; // 0.005 = 5*10^(-3)

    for (y = -r; y<=r; y+=delta){
        if(r*r-y*y >= 0){
            x = sqrt(r*r-y*y); 
            fprintf(fp, "%lf\t %lf\n", x,y);
        }
    }

    for (y = r; y>=-r; y-=delta){
        if(r*r-y*y >= 0){
            x = -sqrt(r*r-y*y); 
            fprintf(fp, "%lf\t %lf\n", x,y);
        }
    }

    fclose(fp);

    // =======   PLOT  =================== // 
    FILE  *gnuplotPipe = NULL; 

    gnuplotPipe = popen("gnuplot -persist", "w");

    if(gnuplotPipe == NULL){
        printf("Error opening Gnuplot");
        return 1; 
    }

    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'circle1plot.png'\n");

    fprintf(gnuplotPipe, "set xlabel 'x'\n");
    fprintf(gnuplotPipe, "set ylabel 'y'\n");
    fprintf(gnuplotPipe, "set title 'Circle 1 Plot'\n");

    fprintf(gnuplotPipe, "plot 'circle1data.txt' using 1:2 with lines\n ");

    fflush(gnuplotPipe);

    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);

    return 0; 
}