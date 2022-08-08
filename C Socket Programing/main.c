//
//  main.c
//  C code
//
//  Created by Zain 👻 on 06/10/2021.
//

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <fcntl.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////D E C L A R A T I O N S     O F      F U N C T I O N S /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char** parsingCommand(char *, char *);
void pipe_Function(char **);
void basic_Command(char *);
int maxSize = 10;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////                K I L L      F U N C T I O N                            /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void forKill(int input)
{
      if(input == 2 || input == 20)
      {
      }
      else
      {
              kill(0,SIGCONT);
      }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////             P A R S I N G      F U N C T I O N S                /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char **parsingCommand(char *arraySTR, char *Input)
{
    char **pointer_ARG = (char **)malloc(sizeof(char *) * maxSize);
    int i = 1;
    int index = 0;
      
    char *dummyVar = strtok(arraySTR, Input);
    while(dummyVar)
      {
          if(index >= i * maxSize)
          {
              pointer_ARG = realloc(pointer_ARG, sizeof(char *) * ( maxSize * (++i)));
              //ALLOCATING THE SIZE OF ARRAY IN POINTER
          }
              //printf("%s",p);
                pointer_ARG[index] = dummyVar;
                index++;//COUNTER TO INDEX
                dummyVar = strtok(NULL, Input);// tokenizing a string
      }
      pointer_ARG[index] = NULL;
      return pointer_ARG;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////    R  E D I R E C T I O N    P A R S I N G   F U N C T I O N /  ////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char **redirectionFunction(char *arrayStr, char *Input)
{
    char ** ptr_LES = (char **)malloc(sizeof(char *) * maxSize);
    char **ptr_ARG = NULL;
    int i = 1, INDEX = 0;
    int counter = 0;
    char *PTR = strtok(arrayStr, Input);// tokenizing a string
    
    //while loop
      while(PTR)
      {
        
          if(INDEX >= i * maxSize)
         {
            ptr_ARG = realloc(ptr_ARG, sizeof(char *) * ( maxSize * (++i)));//allocating the size of array
         }
          
          if(counter != 0)
          {
                        
              ptr_ARG = parsingCommand(PTR, " ");
              ptr_LES[INDEX] = ptr_ARG[0];
              INDEX++;
         }
          
          counter += 1;
          PTR = strtok(NULL, Input);// tokenizing a string
      }
    
      ptr_LES[INDEX] = NULL;
      return ptr_LES;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////PA R S I N G   A R G U M E N T     F U N C T I O N  /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char **parserArg(char *arrayStr, char *Input)
{
        int counter = 2;//bcz we start with to to check
        char **ptrARG = (char **)malloc(sizeof(char *) * maxSize);
        int i = 1;
        int index = 0;
        char *PTR = strtok(arrayStr, Input);// tokenizing a string
   
    //while loop
      while(PTR)
      {
          //if else conditions
              if(index >= i * maxSize)
              {
                      
                  ptrARG = realloc(ptrARG, sizeof(char *) * ( maxSize * (++i)));
                  //allocating the size of Array
              }
               //string comparison
              if((strcmp(PTR, "<") == 0 )|| (strcmp(PTR, ">") == 0 ))
              {
                  counter = 0;
              }
              else if(counter != 1)
              {
                  ptrARG[index] = PTR;
                  index++;
              }
              counter++;
              PTR = strtok(NULL, Input);// tokenizing a string
      }
      ptrARG[index] = NULL;
      return ptrARG;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////                    P  I  P  E       F U N C T I O N                  /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void pipe_Function(char **Input)
{
    int iterator, pfd[2], processID, dummy=0;
    int forFile,length=0, i=0;
    
    char **delimeter=NULL;

    char *opdirect, **opLes=NULL, *ipdirect;
    char **ipNot=NULL, *checker = NULL;
 //for loop
    
    for(iterator = 0; Input[iterator]; iterator++)
    {
        char copyArray[strlen(Input[iterator])];//getting the length of string
        strcpy(copyArray, Input[iterator]);//copy string for array to other variable
        opdirect = strchr(Input[iterator], '>');//first occurrence of a character in a string.
        ipdirect = strchr(Input[iterator], '<');//first occurrence of a character in a string.
        if(Input[iterator][strlen(Input[iterator]) - 1] == '&')
        {
            checker = strchr(Input[iterator], '&');
            Input[iterator][strlen(Input[iterator]) - 1] = '\0';
        }
           
        if(opdirect)
        {
            opLes = redirectionFunction(Input[iterator], ">");
            for(i = 0; opLes[i]; i++)
            {
                forFile = open(opLes[i],  O_CREAT | O_WRONLY  , S_IRUSR | S_IWUSR );  //opening the file
                close(forFile);//closing file
            }
        }
        strcpy(Input[iterator], copyArray);//copying file
        
        if(ipdirect)
        {
            ipNot = redirectionFunction(Input[iterator], "<");
            for(length = 0; ipNot[length]; length++){
 
                        }
                }
     
     strcpy(Input[iterator], copyArray);
     delimeter = parserArg(Input[iterator], " ");
     pipe(pfd);
        //using fork command
        processID = fork();
       
        if(processID == 0)
       {
             if(iterator != 0)
             dup2(dummy, STDIN_FILENO);
 
             if(Input[iterator+1] != NULL)
             dup2(pfd[1], STDOUT_FILENO);
               
             if(opdirect)
               {
                   close(STDOUT_FILENO);
                   forFile = open(opLes[i - 1],  O_CREAT | O_WRONLY  , S_IRUSR | S_IWUSR );
               }
               if(ipdirect)
               {
                   close(STDIN_FILENO);
                   forFile = open(ipNot[length - 1], O_RDONLY);
               }
               close(pfd[0]);
           
           
             //execvp() system call
         if(execvp(delimeter[0], delimeter ) == -1)
         perror("");

       }
       else
       {
           close(pfd[1]);
           if(!checker)
           {
           wait(0);
           }
               dummy = pfd[0];
       }
}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////                B A S I C      F U N C T I O N                      /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void basic_Command(char* Input)
{
    int processID, fd, i=0, k = 0;
    char **ptrArg, *opRedirect, **opLes=NULL, *ipRedirect, **ipNot = NULL, *dummy = NULL;
    opRedirect = strchr(Input, '>');
    ipRedirect = strchr(Input, '<');
    if(Input[strlen(Input) - 1] == '&')//getting length of string
    {
        dummy = strchr(Input, '&');
        Input[strlen(Input) - 1] = '\0';
    }
    char copyArray[strlen(Input)];
    strcpy(copyArray, Input);
      if(opRedirect)
      {
              opLes = redirectionFunction(Input, ">");
              for(i = 0; opLes[i]; i++)
              {
                  fd = open(opLes[i],  O_CREAT | O_WRONLY  , S_IRUSR | S_IWUSR );
                  close(fd);
              }
      }
    //string copy
      strcpy(Input, copyArray);

      if(ipRedirect)
      {
        ipNot = redirectionFunction(Input, "<");
        for(k = 0; ipNot[k]; k++)
        {
                       
        }
      }
    
    
    //string copy
      strcpy(Input, copyArray);
    ptrArg = parserArg(Input, " ");
        
    
    //using fork command
      processID = fork();
        if(processID == 0)
        {
            if(opRedirect)
            {
                close(STDOUT_FILENO);
                //file opening
            fd = open(opLes[i - 1],  O_CREAT | O_WRONLY  , S_IRUSR | S_IWUSR );
              }
              if(ipRedirect)
              {
                  close(STDIN_FILENO);
                  fd = open(ipNot[k - 1], O_RDONLY);
              }
              if(execvp(ptrArg[0], ptrArg ) == -1)
              perror("");
            }
            else
                {
                    if(!dummy)
                    {
                        wait(0);
                    }
                }
}
//main function
int main()
{
      int index, length;
      char choice,*cmd, **ptrARG, **inputs;
        
        struct sigaction obj;
        obj.sa_handler = forKill;
       
        signal(SIGINT, forKill);
        signal(SIGTSTP, forKill);
        while(1)
        {
            printf("Input : ");
            cmd = (char *)malloc(sizeof(char) * 128);
            index = 0;
            length = 100;
            choice = getchar();
            if(choice == EOF)
            {
                return 0;
            }
            else
            {
                //while loop
                while( choice != '\n')
                {
                    if(index >= length)
                    {
                        length *= 2;
                        cmd = (char *)realloc(cmd, sizeof(char) * length);//allocating the space Array
                    }
                    cmd[index++] = choice;
                    choice = getchar();
                    if(choice == EOF)
                    continue;
                }
                
                ptrARG = parsingCommand(cmd, ";");

                for(index = 0; ptrARG[index]; index++)
                {
                    char *p = strchr(ptrARG[index], '|');
                    if(p)
                    {
                        inputs = parsingCommand(ptrARG[index], "|");
                        pipe_Function(inputs);
                    }
                    else
                    {
                        basic_Command(ptrARG[index]);
                    }
                }
              }
            }
      return 0;
}
