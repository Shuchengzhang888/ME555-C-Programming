#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  size_t len = strlen(inputName);
  char * result;
  //strndup: return fixed length(len) string from first parameters(inputname) 
  result = strndup(inputName, len);
  result = realloc(result, (len + 8) * sizeof(*result));
  //copy ".counts\0" to inputName in the "result+len" place
  strcpy(result + len, ".counts\0");
  return result;
}
