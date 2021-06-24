//test prufer coloring
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "coloring.h"
#include "prufercode.h"

int main(){
    printf("Prufercode: ");
    pruffercode();
    printf("\nPrufercode: ");
    fathercode();
    printf("\nTo mau do thi: \n");
    coloring_graph("prufer.txt");
    
    return 0;
}