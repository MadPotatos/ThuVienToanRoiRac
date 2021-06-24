//test prufer coloring
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include "coloring.h"
#include "prufercode.h"

int main(){
    printf("Prufercode: ");
    pruffercode();
    printf("Fathercode: ");
    fathercode();
    printf("\nTo mau do thi: \n");
    coloring_graph("color.txt");
    return 0;
}