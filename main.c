// Copyright here

// Includes here
#include "Todo.h"
// Defines here
#define TODO_LIST_SIZE 256
#define FILE_NAME "todolist.txt"
#define FILE_SIZE 1024

// Main program function 
int main(int argc, char *argv[]){

    if (argc < 3) {
        printf("Wrong input!\n");
        return -1;
    }

    FTodo TodoList[TODO_LIST_SIZE];
    uint16_t listIndex;
    FILE * todoFile;
    uint16_t i;
    char stringToWrite[FILE_SIZE] = "";

    todoFile = fopen(FILE_NAME, "r");
    uint8_t TodoListSize;
    TodoListSize = fillListFromFile(todoFile, TodoList);
    fclose(todoFile);

    for( i = 1 ; i < argc-1 ; i += 2 ){

        FTodo todo; 
        strcpy(todo.time, argv[i]);
        strcpy(todo.note, argv[i+1]);

        int isValidNoteValue = isValidNote(todo.note);
        int isValidTimeValue = isValidTime(todo.time);

        if ( !isValidNoteValue || !isValidTimeValue )
            printf("Wrong input!\n");
        else {
            // Check if the todo already exists
            uint8_t j;
            uint8_t exists = false;
            for(j = 0 ; j < TodoListSize ; j++){
                if (equalTodo(todo, TodoList[j]) == true) exists = true;
            }
            
            if (exists == false){
                TodoList[TodoListSize] = todo;
                TodoListSize++;
            }
        }
    }

    todoFile = fopen(FILE_NAME, "w");
    fprintf(todoFile, stringToWrite);
    fclose(todoFile);

    return 0;

}