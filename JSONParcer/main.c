#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "data.h"
#include "conversion.h"
#include "array.h"
#include "readJSON.h"
#include "tempFunctions.h"


int main()
{
    readJson("test.json");
    return 0;
}
