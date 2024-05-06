#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Speler
{
 struct Item;
 int *numItems;
 float *MaxWeight;
 struct Coins;
};


struct Coins
{
 int cp; //copper 1/100
 int sp; //silver 1/10
 int ep; //electrum 1/2
 int gp; //gold 1
 int pp; //platinum 10
}coins;




