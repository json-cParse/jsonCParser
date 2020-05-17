#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

int stringToInt(char* s)
{
    ///125 -> 521 strlen
    int n,p=1;
    n=strlen(s);
    int number=0;
    for(int i=n-1; i>=0; i--)
    {
        number=number+(s[i]-'0')*p;
        p*=10;
    }
    return number;
}

double stringToDouble(char* s)
{
    int n,p=1;
    double number=0, decimal=0;
    n=strlen(s)-1;
    while(s[n]!='.')
    {
        decimal=decimal+(s[n]-'0')*p;
        p*=10;
        n--;
    }
    decimal/=p;
    p=1;
    for(int i=n-1; i>=0; i--)
    {
        number=number+(s[i]-'0')*p;
        p*=10;
    }
    number+=decimal;
    return number;
}

///b=0 este int
///b=1 este double

char* createNumber(char s,bool* b,FILE* fin)
{
    char c;
    char* num, *sep=" ,\t\n]";
    num=(char*)malloc(1000*sizeof(char));
    assert(num != NULL);
    num[0]=s;
    //printf("%s\n",num);
    int i=1;
    while(strchr(sep,(c = fgetc(fin))) == NULL)
    {
        num[i]=c;
        //printf("%s\n",num);
        i++;
        if(c == '.')
            (*b)=1;
    }
    num[i]='\0';
    return num;
}

char* createBoolAndNull(char s, FILE* fin)
{
    char c;
    char* var, *sep=" \t,\n]";
    var=(char*)malloc(1000*sizeof(char));
    assert(var != NULL);
    var[0]=s;
    //printf("%s\n",var);
    int i=1;
    while(strchr(sep,(c = fgetc(fin))) == NULL)
    {
        var[i]=c;
        //printf("%s\n",var);
        i++;
    }
    var[i]='\0';
    return var;
}
