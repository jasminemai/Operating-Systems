#include<stdio.h>
#include<stdlib.h>

#define DEBUG 1

typedef struct {
    
    char* first;
    char* last;
    int age;
    int sex;    // 0 = male, 1 = female, 2 = both :)

} p_struct;

void passRef( int* p_a );
void passValue( int a );

void printPersonRef( p_struct* p_person );
void printPersonVal( p_struct person );


int main( int argc, char** argv ) {

    // in C all variables should be declared at the beginning of the function (including main)
    
    p_struct person; // create a struct variable: p_person is data type, person is variable person

    
    char first[10]; 
    
    first[0] = 'b';
    first[1] = 'r';
    first[2] = 'e';
    first[3] = 'n';
    first[4] = 't';
    first[5] = '\0'; 

    //    char* first = "brent";

    char last[10] = {'m','u','n','s','e','l','l','\0'};

    last[15] = 'b';

    person.first = first;
    person.last = last;
    person.age = 44;
    person.sex = 0;

    printPersonVal( person );
    printPersonRef( &person );
    printPersonVal( person );

    passValue( person.age );
    passRef( &person.age );
    passValue( person.age );

    return 0;

} // end main function

void passRef( int* p ) {

    (*p)+=2;

    printf("val = %d\n", (*p) );

}

void passValue( int val ) {

    val+=2;

    printf("val = %d\n", val );

}

void printPersonVal( p_struct person ) {


    printf("-----------------------------------------------\n");

    person.age = person.age++;
    person.first = "brett";

    printf("first %s, last %s, first initial %c, age %d, ", person.first, person.last, person.first[0], person.age );

    if ( person.sex == 0 )

        printf("male\n");

    else

        printf("female\n");

}

void printPersonRef( p_struct* p_person ) {


    printf("-----------------------------------------------\n");

    // p_person->first[3] = 't';
    p_person->age = 99;

    printf("first %s, last %s, first initial %c, age %d, ", p_person->first, p_person->last, p_person->first[0], p_person->age );

    if ( p_person->sex == 0 )

        printf("male\n");

    else

        printf("female\n");

}