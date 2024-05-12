STRCHR : The C library function char *strchr(const char *str, int c) searches for the first occurrence of the character c (an unsigned char) in the string pointed to by the argument str.

STRSTR : This function takes two strings s1 and s2 as arguments and finds the first occurrence of the string s2 in the string s1. The process of matching does not include the terminating null-characters(‘\0’), but function stops there. 

strcspn() : calculates the length of the number of characters before the 1st occurrence of character present in both the string.

STRTOL : Interprets an integer value in a byte string pointed to by str.
Discards any whitespace characters (as identified by calling isspace) until the first non-whitespace character is found, then takes as many characters as possible to form a valid base-n (where n=base) integer number representation and converts them to an integer value. The valid integer value consists of the following parts: