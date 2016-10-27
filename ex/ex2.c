#include<stdio.h>
#include<stdlib.h>

#define DEBUG 1

typedef struct {
    
    char* first;
    char* last;
    int age;
    int sex;    // 0 = male, 1 = female, 2 = both :)

} p_struct;


void printPerson( p_struct* p_person );


int main( int argc, char** argv ) {

    // in C all variables should be declared at the beginning of the function (including main)
    
    p_struct person; // create a struct variable: p_person is data type, person is variable person

    char* first = malloc( 10*sizeof(char) );

    first[0] = 'b';
    first[1] = 'r';
    first[2] = 'e';
    first[3] = 'n';
    first[4] = 't';
    first[5] = '\0'; 

    char last[10] = {'m','u','n','s','e','l','l','\0'};

    person.first = first;
    person.last = last;
    person.age = 44;
    person.sex = 0;

    printPerson( &person );

    free( person.first );
    
    return 0;

} // end main function


void printPerson( p_struct* p_person ) {


    printf("-----------------------------------------------\n");

    printf("first %s, last %s, first initial %c, age %d, ", p_person->first, p_person->last, p_person->first[0], p_person->age );

    if ( p_person->sex == 0 )

        printf("male\n");

    else

        printf("female\n");

    p_person->first[3] = 't';
    p_person->last[3] = 'z';

    printf("first %s, last %s\n", p_person->first, p_person->last);

}