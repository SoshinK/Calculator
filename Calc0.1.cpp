#include <cstdio>
#include <cctype>
#include <cstring>

#define NDEBUG

#include <cassert>

typedef long double number;

enum CONSTANTS 
  {
  EXSIZE = 1024,
  };

#define PRINTFORMAT "%1023s"



char* Example = new char[EXSIZE];

size_t ExIndex = 0;


number GetE();

number GetN()
  {
  number val = 0;
  if(!isdigit(Example[ExIndex]))
    {
    printf("Calc:ERROR:not number\n");
    assert(0);
    }
  number exp = 0;
  while(isdigit(Example[ExIndex]) || Example[ExIndex] == '.')
    {
    if(Example[ExIndex] == '.' && exp == 0)exp = 1;
    else if(Example[ExIndex] == '.' && exp != 0)
      {
      printf("Calc:ERROR:extra point\n");
      assert(0);
      }
    else if(exp == 0)
      {
      val = val * 10 + Example[ExIndex] - '0';
      }
    else if(exp > 0)
      {
      exp /= 10;
      val += exp * (Example[ExIndex] - '0');
      }
    ExIndex++;
    }
  return val;
  }

number GetP()
  {
  number val = 0;
  char brace = Example[ExIndex];
  if(brace == '(')
    {
    ExIndex++;
    val = GetE();
    if(Example[ExIndex] != ')')
      {
      printf("Calc:ERROR:lost brace\n");
      assert(0);
      }
    ExIndex++;
    }
  else val = GetN();
  return val;
  }



number GetT()
  {
  number val = GetP();
  while(Example[ExIndex] == '*' || Example[ExIndex] == '/')
    {
    char oper = Example[ExIndex];
    ExIndex++;
    number val2 = GetP();
    if(oper == '*')val *= val2;
    if(oper == '/')val /= val2;
    }
  return val;
  }


number GetE()
  {
  number val = GetT();
  while(Example[ExIndex] == '+' || Example[ExIndex] == '-')
    {
    char oper = Example[ExIndex];
    ExIndex++;
    number val2 = GetT();
    if(oper == '+')val += val2;
    if(oper == '-')val -= val2;
    }
  return val;
  }

number GetG()
  {
  number answer = GetE();
  if(Example[ExIndex] != '\0')
    {
    printf("Calc:unknown symbol. Cant interpret\n");
    assert(0);
    }
  return answer;
  }  




int main(int argc, char* argv[])
  {
  if(argc > 2)printf("Calc:to much arguments for Calculator. Enter ./calc info to watch info\n");
  if(argc == 1)
    {
    //strcpy(Example, argv[1]);
    //printf("%s\n", Example);
    printf("\nCalculator v0.1. Enter ./calc info to watch the reference.\n");
    printf("Please, enter the expression:");
    scanf(PRINTFORMAT, Example);
    number answer = GetG();
    printf("%Lf\n", answer);
    }
  if(argc == 2 && !strcmp(argv[1], "info"))
    {
    printf(" \
=========================================================\n \
                     Calculator v0.1                     \n \
                                                         \n \
Minimal terminal calculator version 0.1                  \n \
                                                         \n \
Supportable operations:+,-,*,/. Braces (, ) are          \n \
supportable. Accuracy: 10^(-6)                           \n \
                                                         \n \
To calculate enter your expression                       \n \
(expression MUST be without any                          \n \
spaces):                                                 \n \
                                                         \n \ 
./calc                                                   \n \
Calculator v0.1 Enter ./calc info to watch the reference.\n \
Please, enter the expression:(200+222)*1231.3123/1456    \n \
356.877603                                               \n \
                                                         \n \
Soshin Konstantin, 2017 MIPT           \n");
    }
  else if(argc == 2)
    {
    printf("Calc:ERROR:unkonown key '%s'. Enter ./calc info for reference\n", argv[1]);
    }
  return 0;
  } 











