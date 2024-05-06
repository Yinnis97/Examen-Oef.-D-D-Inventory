#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item 
{
    char name[50];

    struct price
    {
     int Quantity;
     char unit[3];
    }price;

    float weight;
    
}item[20];

// Geeft / zoekt de waarde van een spec (Weigh,Price,Name).
char* extractValue(char *jsonString, char *key) 
{
  if(strcmp(key,"\"name\"") == 0 || strcmp(key,"\"unit\"") == 0)
  {
    char *start = strstr(jsonString, key);
    if (start == NULL) 
    {
        printf("Key not found: %s\n", key);
        return NULL;
    }
    start = strstr(start, ":");
    if (start == NULL) 
    {
        printf("Invalid JSON format.\n");
        return NULL;
    }
    start = strchr(start, '"');
    if (start == NULL) 
    {
        printf("Invalid JSON format.\n");
        return NULL;
    }
    start++; // moet het volgende character hebben na de " 
    char *end = strchr(start, '"');
    if (end == NULL) 
    {
        printf("Invalid JSON format.\n");
        return NULL;
    }
    int len = end - start;
    char *value = (char *)malloc(len + 1);
    if (value == NULL) 
    {
        printf("Memory allocation error.\n");
        return NULL;
    }
    strncpy(value, start, len);
    value[len] = '\0';
    return value;
  }
  else //is nodig sinds we alleen bij de naam en unit "" hebben.
  {
    char *start = strstr(jsonString, key);
    if (start == NULL) 
    {
        printf("Key not found: %s\n", key);
        return NULL;
    }
    start = strstr(start, ":");
    if (start == NULL) 
    {
        printf("Invalid JSON format.\n");
        return NULL;
    }
    start++;
    char *end = strchr(start, ',');
    if (end == NULL) 
    {
        printf("Invalid JSON format.\n");
        return NULL;
    }
    int len = end - start;
    char *value = (char *)malloc(len + 1);
    if (value == NULL) 
    {
        printf("Memory allocation error.\n");
        return NULL;
    }
    strncpy(value, start, len);
    value[len] = '\0';
    return value;
  }
}

// JSON PARSING
void parseJSON(char *jsonString, struct Item *item) 
{
    //NAME
    char *name = extractValue(jsonString, "\"name\"");
    if (name == NULL) 
    {
        printf("Error: Name not found.\n");
        return;
    }
    strcpy(item->name, name);
    free(name);

    //PRICE
    char *priceStr = extractValue(jsonString, "\"quantity\"");
    if (priceStr == NULL) 
    {
        printf("Error: Price not found.\n");
        return;
    }
    float price = atof(priceStr);
    item->price.Quantity = price ;
    free(priceStr);

    //UNIT
    char *unit = extractValue(jsonString, "\"unit\"");
    if (unit == NULL) 
    {
        printf("Error: Unit not found.\n");
        return;
    }
    if (strcmp(unit, "gp") == 0) 
    {
        strcpy(item->price.unit, "gp");
    } 
    else if (strcmp(unit, "pp") == 0)
    {
        strcpy(item->price.unit, "pp");
    }
    else if (strcmp(unit, "ep") == 0)
    {
        strcpy(item->price.unit, "ep");
    }
    else if (strcmp(unit, "sp") == 0)
    {
        strcpy(item->price.unit, "sp");
    }
    else if (strcmp(unit, "cp") == 0)
    {
        strcpy(item->price.unit, "cp");
    }
    free(unit);

    //WEIGHT
    char *weightStr = extractValue(jsonString, "\"weight\"");
    if (weightStr == NULL) 
    {
        printf("Error: Weight not found.\n");
        return;
    }
    item->weight = atof(weightStr);
    free(weightStr);
}
