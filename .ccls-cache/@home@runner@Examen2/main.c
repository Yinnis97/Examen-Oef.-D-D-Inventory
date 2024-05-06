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


for(int i = 1 ; i < argc ; i++)
  {
    //Checken voor weight.
    if(strcmp(argv[i], "-w") == 0)
    {
      MaxWeight = atof(argv[i + 1]);
      i++;
      printf("%s\n",argv[i]);
    }

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
          }

          else if(*endptr == 'g' && *endptr != '\0')
          {
            char *temp = argv[j+1];
            coins.gp = atoi(temp);
            temp = NULL;
            free(temp);
          }

          else if(*endptr == 'e' && *endptr != '\0')
          {
            char *temp = argv[j+1];
            coins.ep = atoi(temp);
            temp = NULL;
            free(temp);
          }

          else if(*endptr == 's' && *endptr != '\0')
          {
            char *temp = argv[j+1];
            coins.sp = atoi(temp);
            temp = NULL;
            free(temp);
          }
            
          else if(*endptr == 'c' && *endptr != '\0')
          {
            char *temp = argv[j+1];
            coins.cp = atoi(temp);
            temp = NULL;
            free(temp);
          }
          else
          {
            break;
          }
          
        }
      i+=3;
      printf("%dpp\n",coins.pp);
      printf("%dgp\n",coins.gp);
      printf("%dep\n",coins.ep);
      printf("%dsp\n",coins.sp);
      printf("%dcp\n",coins.cp);

    }

    //Checken voor Camp.
    else if(strcmp(argv[i], "-c") == 0)
    {
      strcpy(campFile, argv[i + 1]);
      i++;
       printf("%s\n",argv[i]);
    }

    //Check de files die geopend moeten worden.
    else 
    {
     int k = 1;
     
     while(i < argc)
     {
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
          
          parseJSON(parsing, &item[k]);
          i++;

        }
        fclose(file);
        printf("\nItem %d :\n\n",k);
        
      }
  
      printf("Name: %s\n", item[k].name);
      printf("Price: %d%s\n", item[k].price.Quantity ,item[k].price.unit);
      printf("Weight: %.2f lbs\n", item[k].weight);
      k++;
      player.numItems = &k;
     }
      printf("\n");
    }
    
  }

  //------ Berekenen van het totale gewicht van de speler en kijken of hij encumbered is -----
  
  for(int w = 1 ; w < *player.numItems ; w++ )
    {
      TotalWeight = TotalWeight + item[w].weight;
    }
  isplayerencumbered(TotalWeight, MaxWeight);

 //--------------------------------------------------------------------------------------------
  return 0;
}


