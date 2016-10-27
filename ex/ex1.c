#include<stdio.h>
#include<stdlib.h>

#define DEBUG 1

typedef struct {
    
    char* first;
    char* last;
    int age;
    int sex;    // 0 = male, 1 = female, 2 = both :)

} p_person;


int main( int argc, char** argv ) {

    // in C all variables should be declared at the beginning of the function (including main)

    int i;
    
    p_person person; // create a struct variable: p_person is data type, person is variable person

    char first[10];
    first[0] = 'b';
    first[1] = 'r';
    first[2] = 'e';
    first[3] = 'n';
    first[4] = 't';
    first[5] = '\0';    // may use 0 instead of '\0' this indicates where the string is terminated

    // Quick question ... how would be create an array that holds 10 p_person elements ??

    printf("-----------------------------------------------\n");

    printf("Number of elements in first = %lu\n", sizeof(first)); 

    for ( i=0; i<sizeof(first); i++ ) printf("first[%d]=%c\n", i, first[i] ); 

    person.first = first;
    person.last = "munsell";
    person.age = 44;
    person.sex = 0;

    printf("-----------------------------------------------\n");

    if ( person.sex == 0 )

        printf("first %s, last %s, first initial %c, age %d, male\n", person.first, person.last, person.first[0], person.age );

    else

        printf("first %s, last %s, first initial %c, age %d, female\n", person.first, person.last, person.first[0], person.age);

    person.first[3] = 't';

    printf("first %s\n", person.first);

    // -----------------------------------
    // Concept of a pointer
    // -----------------------------------
    // pointer "points" to a memory location (not the actual value)
    // you may de-reference the pointer (*p) to manipulate the value the pointer is pointing at (I know sounds weird)

    printf("-----------------------------------------------\n");

    int* p = malloc(sizeof(int));
    int* pp;

    printf("(p) Memory Location [%p] has value = %d\n", p, (*p));

    (*p)=42;

    printf("(p) Memory Location [%p] has value = %d\n", p, (*p));

    (*p)++;

    printf("(p) Memory Location [%p] has value = %d\n", p, (*p));

    pp = p;

    (*pp)++;

    printf("(pp) Memory Location [%p] has value = %d\n", pp, (*pp));
    printf("(p) Memory Location [%p] has value = %d\n", p, (*p));

    // What do you think this is doing p++ ???

    // -----------------------------------
    // Open a file and loop through each line
    // -----------------------------------

    printf("-----------------------------------------------\n");

    FILE* fhnd;

    fhnd = fopen( "test.txt", "r" );

    char line[50];

    if ( fhnd != NULL ) {

        while ( fgets( line, sizeof(line), fhnd ) != NULL ) {

            if ( DEBUG ) printf( "%s", line );

        }

    }

    fclose( fhnd );

    return 0;

} // end main function
