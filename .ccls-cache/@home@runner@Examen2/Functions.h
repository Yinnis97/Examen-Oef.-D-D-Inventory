#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void Usage()
{
  printf("Usage:   Inventory.exe equipment-files [number-of-items] [-w max-weight] [-m money] [-c camp-file]\n"); 
  printf("\n");
  printf("Options:\n");
  printf("number-of-items      Optional per file to define the number in the inventory\n");
  printf("-w max-weight        Maximum weight before becoming encumbered\n");
  printf("-m money             List of coins and types (cp, sp, ep, gp, pp)\n");
  printf("-c camp-file         Optional camp file for all discovered items during play that stay in camp\n");
}


void isplayerencumbered(float w,float mw)
{
  printf("Total Weight Player : %0.2f lbs\n",w);
  printf("Max Weight Player   : %0.2f lbs\n",mw);
  
  if(w > mw)
  {
    printf("Player is Encumbered!\n");
  }
  else
  {
    printf("Player is not Encumbered!\n");
  }
}




























