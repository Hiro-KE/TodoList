#pragma once

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct FTodo{

    char time[6];
    char note[50];
} FTodo;

// Creating this due to being unable to create a "==" operator for some reasons 
uint8_t equalTodo(const FTodo lhs, const FTodo rhs){
    if ((lhs.note == rhs.note) && (lhs.time == lhs.time)) return 1;
    return 0;
}

int isValidTime(const char* str){

    char hour[3];
    hour[0] = str[0];
    hour[1] = str[1];
    hour[2] = '\0';
    
    char separator[2];
    separator[0] = str[2];
    separator[1] = '\0';

    char minutes[3];
    minutes[0] = str[3];
    minutes[1] = str[4];
    minutes[2] = '\0';
    if ((atoi(hour) < 0) || (atoi(hour) > 23)) return 0;
    if ((atoi(minutes) < 0) || (atoi(minutes) > 59)) return 0;
    if (separator[0] != ':') return 0;

    return 1;
}

int isValidNote(const char* str){

    uint8_t i;
    
    for(i = 0 ; i < strlen(str) ; i++)
        if (isalpha(str[i]) == 0)
            return 0;
    
    return 1;
}

void convertStringToTodo(const char* str, FTodo* resultTodo){
    
    char hour[3];
    hour[0] = str[0];
    hour[1] = str[1];
    hour[2] = '\0';
    
    char separator[2];
    separator[0] = str[2];
    separator[1] = '\0';

    char minutes[3];
    minutes[0] = str[3];
    minutes[1] = str[4];
    minutes[2] = '\0';

    char time[6] = "";
    strcat(time, hour);
    strcat(time, separator);
    strcat(time, minutes);
    strcpy(resultTodo->time, time); 

    uint16_t i;
    uint16_t noteCounter = 0;
    char noteString[50] = "";
    
    for( i = 8 ; i < strlen(str) ; i++ ){
        char strToAppend[2];
        strToAppend[0] = str[i];
        strToAppend[1] = '\0';
        strcat(noteString, strToAppend);
    }
    strcpy(resultTodo->note, noteString); 
}

// Converts the Todo struct to a string
void todoToString(const FTodo* inTodo, char* resultString){
    strcat(resultString, inTodo->time);
    strcat(resultString, " - ");
    strcat(resultString, inTodo->note);
}

uint8_t fillListFromFile(FILE* inTodoFile, FTodo* outTodoList){
    uint8_t resultSize = 0;

    if (inTodoFile == NULL){
        printf("Error file");
        return -1;
    }
    else {
        char str[1024] = "";
        uint16_t i = 0;
        uint16_t index = 0;
        uint16_t lastLineIndex = 0;
        
        int c = 0;

        while ( (c = fgetc (inTodoFile)) != EOF ){
            str[index] = c;
            index++;
            if (c == '\n' || c == EOF){
                uint16_t length = index - lastLineIndex + 1;
                char stringToConvert[60] = "";
                for(i = lastLineIndex ; i < index-1 ; i++){
                    char strToAppend[2];
                    strToAppend[0] = str[i];
                    strToAppend[1] = '\0';
                    strcat(stringToConvert, strToAppend);
                    
                }
                lastLineIndex = index ;
                
                FTodo todoTemp;

                convertStringToTodo(stringToConvert, &todoTemp);
                outTodoList[resultSize] = todoTemp;
                resultSize++;

            }
            
        }
            

    }
    return resultSize;

}
