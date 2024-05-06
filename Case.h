#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Inventory
{
 Idle_State,
 Add_Item,
 Move_Camp,
};


int input = 0;

enum Inventory huidigeStatus = Idle_State;

        switch( huidigeStatus )
        {
        case  Idle_State:
          printf("Wat wilt u doen?");
          printf("1. Een nieuw item toevoegen.");
          printf("2. Een item naar camp verplaatsen.");
          scanf("%d",&input);
          
           huidigeStatus = Idle_State + input;

           break;

        case Add_Item:
          huidigeStatus = Idle_State;

           break;

        case Move_Camp:
          
          
          
          huidigeStatus = Idle_State;
           break;

        default:
          printf( "Foutmelding\n" );
           break;

        }

  
  
  
