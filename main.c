#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"
#include "Structs.h"
#include "JsonReader.h"


int main(int argc, char *argv[]) 
{
   int i = 1;
  
 if(argc < 2)
 {
   Usage();
   return 1;
 }

float MaxWeight = 0;
float TotalWeight = 0;
char campFile[20] = "";
int TotalItems = 1;

for(int i = 1 ; i < argc ; i++)
  {
    //Checken voor weight.
    if(strcmp(argv[i], "-w") == 0)
    {
      MaxWeight = atof(argv[i + 1]);
      i++;
      printf("%s\n",argv[i]);
    }
      
    //--------------------------------------------------------------------------------------------
    //Checken voor Money.
      
    else if(strcmp(argv[i], "-m") == 0)
    {  
      //for loop voor het doorgaan en checken van het type coins
      for(int j = i ; j < argc ; j++)
        {

          char *endptr;
          long num = strtol(argv[j+1], &endptr, 10);
          
          if(*endptr == 'p' && *endptr != '\0')
          {
            char *temp = argv[j+1];
            coins.pp = atoi(temp);
            temp = NULL;
            free(temp);
            i++;
          }

          else if(*endptr == 'g' && *endptr != '\0')
          {
            char *temp = argv[j+1];
            coins.gp = atoi(temp);
            temp = NULL;
            free(temp);
            i++;
          }

          else if(*endptr == 'e' && *endptr != '\0')
          {
            char *temp = argv[j+1];
            coins.ep = atoi(temp);
            temp = NULL;
            free(temp);
            i++;
          }

          else if(*endptr == 's' && *endptr != '\0')
          {
            char *temp = argv[j+1];
            coins.sp = atoi(temp);
            temp = NULL;
            free(temp);
            i++;
          }
            
          else if(*endptr == 'c' && *endptr != '\0')
          {
            char *temp = argv[j+1];
            coins.cp = atoi(temp);
            temp = NULL;
            free(temp);
            i++;
          }
          else
          {
            break;
          }
          
        }
      
      printf("%dpp\n",coins.pp);
      printf("%dgp\n",coins.gp);
      printf("%dep\n",coins.ep);
      printf("%dsp\n",coins.sp);
      printf("%dcp\n",coins.cp);

    }
    //--------------------------------------------------------------------------------------------
    //Checken voor Camp.
      
    else if(strcmp(argv[i], "-c") == 0)
    {
      strcpy(campFile, argv[i + 1]);
      i++;
       printf("%s\n",argv[i]);
    }
      
    //--------------------------------------------------------------------------------------------
   
    else 
    {
     
        while(i < argc)
        {
          //Checken voor het aantal van een specifiek item.
           int Amount = atoi(argv[i]);
           if( atoi(argv[i]) != 0 )
           {
             Amount = atoi(argv[i]);
             i++;
           }
           else
           {
             Amount = 1;
           }
          //Check de files die geopend moeten worden.
         char buffer[1024];
         char *parsing = NULL;
         FILE *file = fopen(argv[i], "r");
         if (file) 
         {
           while (!feof(file)) 
           {
             if (fgets(buffer, sizeof(buffer), file) == NULL) 
             {
               break;
             }
             parsing = buffer;

             parseJSON(parsing, &item[TotalItems]);
             i++;

           }
           fclose(file);
           printf("\nItem %d :\n\n",TotalItems);

         }
     
          if(Amount > 1)
          {
            item[TotalItems].weight = item[TotalItems].weight * Amount;
          }
         printf("Name   : %s\n", item[TotalItems].name);
         printf("Price  : %d%s\n", item[TotalItems].price.Quantity ,item[TotalItems].price.unit);
         printf("Weight : %.2f lbs\n", item[TotalItems].weight);
         printf("Amount : %d\n",Amount);
         Amount = 0;
         TotalItems++;
         player.numItems = &TotalItems + Amount;
          
         item[TotalItems].next = &item[TotalItems+1] + Amount;
        }
         printf("\n"); 
     
    }
    
  }
  
  //--------------------------------------------------------------------------------------------
  //Berekenen van het totale gewicht van de speler en kijken of hij encumbered is
  
  for(int w = 1 ; w < *player.numItems ; w++ )
    {
      TotalWeight = TotalWeight + item[w].weight;
    }
  isplayerencumbered(TotalWeight, MaxWeight);

  
 //--------------------------------------------------------------------------------------------


  
  return 0;
}


