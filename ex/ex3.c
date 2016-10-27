#include<stdio.h>
#include<stdlib.h>

#define DEBUG 1

typedef struct {
    
    char* first;
    char* last;
    int age;
    int sex;    // 0 = male, 1 = female, 2 = both :)

} p_struct;


void initialize( p_struct* p_person_array, int length );
void printPerson( p_struct* p_person );


int main( int argc, char** argv ) {

    // in C all variables should be declared at the beginning of the function (including main)
    
    int length;
    int i;



    p_struct person_array[10]; // create a struct variable: p_person is data type, person is variable person

     printf("%lu,%lu\n", sizeof(person_array), sizeof(p_struct) );

    length = sizeof(person_array)/sizeof(p_struct);

    printf("%d\n", length );

    initialize( person_array, length );

    for ( i=0; i<length; i++ ) {

        printPerson( &person_array[i] );

    }

    
    
    return 0;

} // end main function


void initialize( p_struct* p_person_array, int length ) {

    int i;

    for ( i=0; i<length; i++ ) {

        p_person_array[i].first=0;
        p_person_array[i].last=0;
        p_person_array[i].age=0;
        p_person_array[i].sex=0;

    }
    
}

void printPerson( p_struct* p_person ) {


    printf("-----------------------------------------------\n");

    
    printf("first %s, last %s, age %d, ", p_person->first, p_person->last, p_person->age );
    
    if ( p_person->sex == 0 )

        printf("male\n");

    else

        printf("female\n");



}