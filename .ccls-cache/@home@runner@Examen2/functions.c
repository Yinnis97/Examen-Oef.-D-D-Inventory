#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *nextField( char **buffer )
{
  char *token = strsep( buffer, "," );
  if( token[0] == '"' && token[strlen( token ) - 1] != '"' )
  {
    token[strlen( token )] = ',';
    token[0] = '\0';
    token++;
    (void)strsep( buffer, "\"" );
    (void)strsep( buffer, "," );
  }
  return token;
}























