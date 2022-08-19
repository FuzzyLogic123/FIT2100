#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task4.h"

int isStructEqual(UnitCode unitcode1, UnitCode unitcode2);

int main(void)
{
    UnitCode unitcode1, unitcode2;

    unitcode1.FacID = "FIT";
    unitcode1.UnitID = 1047;

    unitcode2.FacID = "FIT";
    unitcode2.UnitID = 1047;

    isStructEqual(unitcode1, unitcode2);
    return 0;
}

int isStructEqual(UnitCode unitcode1, UnitCode unitcode2)
{
    if (strcmp(unitcode1.FacID, unitcode2.FacID) == 0 && unitcode1.UnitID == unitcode2.UnitID)
    {
        printf("The structs are the same");
    }
    else
    {
        printf("the structs are different");
    }
    return 0;
}