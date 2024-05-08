#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Functions.h"
#include "Structs.h"
#include "JsonReader.h"

void ShowItem(struct Item item, int i);

int main(int argc, char *argv[]) 
{
   int i = 1;
  
 if(argc < 2)
 {
   Usage();
   return 1;
 }

float MaxWeight = 0;    //max gewicht voordat men encumbered is.
float TotalWeight = 0;  //Totale gewicht van alle items.
char campFile[20] = "";
int TotalItems = 1;     //Aantal items dat men heeft.
int Amount = 0;         //Aantal stuks van een specifiek item.
char buffer[1024];
  
for(int i = 1 ; i < argc ; i++)
  {
    //Checken voor weight.
    if(strcmp(argv[i], "-w") == 0)
    {
      MaxWeight = atof(argv[i + 1]);
      i++;
      printf("Weight : %s lbs\n",argv[i]);
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
      
      printf("Platinum Coins : %dpp\n",coins.pp);
      printf("Gold Coins     : %dgp\n",coins.gp);
      printf("Electrum Coins : %dep\n",coins.ep);
      printf("Silver Coins   : %dsp\n",coins.sp);
      printf("Copper Coins   : %dcp\n",coins.cp);

    }
    //--------------------------------------------------------------------------------------------
    //Checken voor Camp File Name.
      
    else if(strcmp(argv[i], "-c") == 0)
    {
      strcpy(campFile, argv[i + 1]);
      i++;
       printf("Camp File Name : %s\n",argv[i]);
    }
      
    //--------------------------------------------------------------------------------------------
   
    else 
    {
     
        while(i < argc)
        {
          //Checken voor het aantal van een specifiek item.
           Amount = atoi(argv[i]);
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

          //bij meerdere items ook de totale weight en prijs veranderen.
          if(Amount > 1)
          {
            item[TotalItems].weight = item[TotalItems].weight * Amount;
            item[TotalItems].price.Quantity = item[TotalItems].price.Quantity * Amount;
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
while(1)
{
      
  printf("-------------------------------------------------------\n");
  printf( "Wat wilt u doen?\n" );
  printf( "Een nieuw item toevoegen : Type \"AddItem\".\n" );
  printf( "Een item naar camp verplaatsen : Type \"MoveCamp\".\n" );
  printf( "Door de lijst met objecten stappen : Type \"Scroll\"\n");
  printf( "Ik ben klaar : Type \"Klaar\".\n" );
  printf("-------------------------------------------------------\n");
     
  char input[20] = {0};
  fgets(input, sizeof(input), stdin);
  input[strcspn(input, "\n")] = 0;
     
  if(strcmp(input,"AddItem") == 0)
  {
   
    printf("Gelieve een .json file in te geven.\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
    
        
         char *parsing = NULL;
         FILE *file = fopen(input, "r");
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
           }
      
           fclose(file);
          
         TotalItems++;
         player.numItems = &TotalItems;
         item[TotalItems].next = &item[TotalItems+1];

           for(int k = 1 ; k < TotalItems ; k++)
           {
             ShowItem(item[k] , k);
           }

        }
        else
         {
          continue;
         }
    
    TotalWeight = TotalWeight + item[TotalItems-1].weight;
    isplayerencumbered(TotalWeight, MaxWeight); 
    printf("\n"); 

      }

  //Verplaatsen van item naar camp
  else if(strcmp(input,"MoveCamp") == 0)
  {
    printf("Geef de .json file die je naar camp wilt sturen.\n");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0;
     char str;
     char *tempname; 
     FILE *file = fopen(input, "r");
     if (file) 
     {
       while (!feof(file)) 
       {
         if (fgets(buffer, sizeof(buffer), file) == NULL) 
         {
           break;
         }
         
         int len = fread(buffer, 1, sizeof(buffer), file); 
         
         tempname = extractValue(buffer, "\"name\"");
   
       }

       fclose(file);
     }
    
    file = fopen(campFile, "a");
     if (file) 
     {
       fputs(buffer, file); 
       fclose(file);
       printf("-------------------------------------------------------\n");
       printf("%s verplaatst naar %s\n",input,campFile);
       printf("-------------------------------------------------------\n");
     }
    
    for(int i = 1 ; i < TotalItems ; i++)
      { 
        
        printf("-----%s-----\n",tempname);
        
        if(strcmp(tempname,item[i].name) == 0)
        { 
          printf("%s",item[i].name);
          printf("i = %d\n",i);
       
           
          TotalWeight = TotalWeight - item[i].weight;
          isplayerencumbered(TotalWeight, MaxWeight); 
          
         while(i < TotalItems)
            { 
              strcpy(item[i].name , item[i+1].name);
              item[i].price.Quantity = item[i+1].price.Quantity;
              strcpy(item[i].price.unit , item[i+1].price.unit);
              item[i].weight = item[i+1].weight;
              i++;
            }
          TotalItems = TotalItems - 1;
          player.numItems = &TotalItems;
        }
      }
     for(int k = 1 ; k < TotalItems; k++)
     {
       ShowItem(item[k] ,  k);
     }
  }
    
  else if (strcmp(input,"Scroll") == 0)
  {
    /*
   for(int i = 1 ; 1 < TotalItems ; i++)
     {
      struct Item *Item = (struct Item *)malloc(sizeof(struct Item));
      item[i].next = &item[i+1];
     }
   */
    int i = 1;
     printf("-------------------------------------------------------\n");
     ShowItem(item[i] ,  i);
     printf("-------------------------------------------------------\n");
    while(strcmp(item[i].name, "\0"))
     {  
        printf("Laat Volgende Item zien \"Volgend\"\n");
        printf("Laat Vorig Item zien \"Vorig\"\n");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
    
       if(strcmp(input,"Volgend") == 0)
       {
         i++;
         ShowItem(item[i] ,  i);
       }
       else if (strcmp(input,"Vorig") == 0)
       {
         if(i == 1)
         {
           ShowItem(item[i] ,  i);
         }
         else
         {
           i--;
           ShowItem(item[i] ,  i);
         }
       }
         
       else
        {
          continue;;
        }

     }
    
  }
    
  else if (strcmp(input,"Klaar") == 0)
  {
    break;
  }
     
  else
  {
    printf("Gelieve een correcte input in te geven.\n");
  }
 }


  
  return 0;
}



void ShowItem(struct Item item , int i)
{
  printf("-------------------------------------------------------\n");
  printf("Item %d \n",i); 
  printf("Item Name   : %s \n",item.name);
  printf("Item Price  : %d %s \n",item.price.Quantity,item.price.unit);   
  printf("Item Weight : %.2f \n",item.weight);
  printf("-------------------------------------------------------\n");

}
