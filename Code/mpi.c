/*
Laboratory OS 2 / Exercise 2 / Question 3 / 2021-22
Name: Athanasiou Vasileios Evangelos
Student ID: 19390005
Compilation command: gcc -o client client.c 
*/

#include <stdio.h>
#include "mpi.h"
#include <stdlib.h>
#include <string.h>

void Check_MPI_Routines (int return_value, char *mpi_routine);                                           // Declaration of the prototype of the "Check_MPI_Routines ()" function, which is implemented in lines 192-199
void Check_Memory (int *seq);                                                                            // Declaration of the prototype of the "Check_Memory ()" function, which is implemented in lines 201-208
void Check_Sort_Breaker (int *seq, int n, int *ptr_sort_breaker, int *ptr_sort_breaker_exist);           // Declaration of the prototype of the "Check_Sort_Breaker ()" function, which is implemented in lines 210-228

int main (int argc, char *argv[])
{
/*********************************************************************************************** Variable Declarations ***********************************************************************************************/
    int rank, p;                                                                                         // The process identifier, The number of processes
    int N, elements_per_processor;                                                                       // The size of the sequence, The number of elements that each process will have for checking
    int *Seq, *Seq_per_processor;                                                                        // The sequence, The portion of the sequence that each process will have for checking
    int dest, src;                                                                                       // Helper variable for the even distribution of elements among the processes P1,...,P(p-1) from the process P0, Helper variable of the process P0 for receiving the sorting status of the elements from the other processes
    int sort_breaker, first_sort_breaker;                                                                // The element that breaks the sorting, The first element that breaks the sorting
    int sort_breaker_exist, first_sort_breaker_stored;                                                   // Indicator for the existence of an element that breaks the sorting, Indicator for storing the first element that breaks the sorting
    int last_element_send, last_element_recv;                                                            // The last element of a process to send to the immediately next one, The last element of a process to receive from the immediately next one
    int choice, k;                                                                                       // The choice for the menu, Helper variable for the correct even distribution of elements among the processes 
    int i, j;                                                                                            // Helper variables for loop execution
    int tag_N = 1;                                                                                       // The label for sending-receiving between processes for the size of the sequence
    int tag_Seq = 2;                                                                                     // The label for sending-receiving between processes for the elements of the sequence
    int tag_Check_Sort_Seq = 3;                                                                          // The label for sending-receiving between processes for the sorting check of the elements of each process
    int tag_Sort_Breaker = 4;                                                                            // The label for sending-receiving between processes for any element that breaks the sorting
    int tag_Last_Element = 5;                                                                            // The label for sending-receiving between processes for the last element they have
    int tag_Choice = 6;                                                                                  // The label for sending-receiving between processes for the choice in the menu
    char is_sort[5];                                                                                     // The storage unit for the sorting status of the elements of each process 
    MPI_Status status;                                                                                   // The status of a reception from one process where the sender is another process
 /******************************************************************************************* Start of the MPI environment **************************************************************************************/   
    Check_MPI_Routines (MPI_Init (&argc, &argv), "MPI_Init ()");                                         // Start using MPI routines and check with "Check_MPI_Routines ()" for any malfunction
    Check_MPI_Routines (MPI_Comm_rank(MPI_COMM_WORLD, &rank), "MPI_Comm_rank ()");                       // Assign the identifier of each process to rank and check with "Check_MPI_Routines ()" for any malfunction
    Check_MPI_Routines (MPI_Comm_size(MPI_COMM_WORLD, &p), "MPI_Comm_size ()");                          // Assign the number of processes to p and check with "Check_MPI_Routines ()" for any malfunction
 /******************************************************************************************* Infinite Loop **************************************************************************************************/
    while (1)                                                                                           
    {
/*-------------------------------------------------------------------------------------------------- P0 --------------------------------------------------------------------------------------------------------*/
        if (rank == 0)                                                                                   /* Code that will be executed only by process P0 */
        {
            do                                                                                           /* Loop to ensure that the size of the sequence will be an integer multiple of the number of processes */
            {
                system ("clear");                                                                        // Clear the screen 
                printf ("Number of processors are %d\n", p);                                             // Print the number of processes 
                printf ("Size of integers' sequence must be integer multiple of number of processors (N mod processors == 0).\n"); // Print the loop condition in natural language
                printf ("Input the size of integers' sequence : ");                                      // Print for inputting the size of the sequence
                scanf ("%d", &N);                                                                        // Input the size of the sequence 
            }
            while (N % p != 0);                                                                          /* The condition */
            
            Seq = (int *) malloc (N * sizeof (int));                                                     // Dynamic memory allocation for storing the sequence
            Check_Memory (Seq);                                                                          // Check with "Check_Memory ()" for any malfunction
            printf ("Input the integers' sequence\n");                                                   // Print for inputting numbers into the sequence
            for (i = 0; i < N; i++)                                                                      /* Loop for accessing the sequence */
            {
                printf ("Seq[%d] : ", i);                                                                // Print the positions of the sequence
                scanf ("%d", &Seq[i]);                                                                   // Input elements into the sequence
            }
            for (dest = 1; dest < p; dest++)                                                             /* Helper loop for sending the size of the sequence to the other processes P1...P(p-1) */
               Check_MPI_Routines (MPI_Send (&N, 1, MPI_INT, dest, tag_N, MPI_COMM_WORLD), "MPI_Send ()"); // Send the size of the sequence to the other processes P1...P(p-1) and check with "Check_MPI_Routines ()" for any malfunction
/*................................. Waiting until the receiver (dest) calls the corresponding MPI_Recv (line 78) with label tag_N (receivers: P1,...,P(p-1)) ..................................................*/            
            elements_per_processor = N / p;                                                              // The number of elements that each process will have for checking
            k = elements_per_processor;                                                                  // Store the number of elements that each process will have in a helper variable for proper even distribution of elements among the processes 
            
            Seq_per_processor = (int *) malloc (elements_per_processor * sizeof (int));                  // Dynamic memory allocation for storing the portion of the sequence that process P0 will have
            Check_Memory (Seq_per_processor);                                                            // Check with "Check_Memory ()" for any malfunction
            for (dest = 1; dest < p; dest++)                                                             /* Helper loop for the proper even distribution of the elements that each of the other processes P1,...,P(p-1) will have */
            {
                Check_MPI_Routines (MPI_Send (&Seq[k], elements_per_processor, MPI_INT, dest, tag_Seq, MPI_COMM_WORLD), "MPI_Send ()"); // Send the corresponding portion of the sequence that each of the other processes P1,...,P(p-1) will have and check with "Check_MPI_Routines ()" for any malfunction
/*................................. Waiting until the receiver (dest) calls the corresponding MPI_Recv (line 83) with label tag_Seq (receivers: P1,...,P(p-1)) ................................................*/
                k += elements_per_processor;                                                             // Increase the helper variable for the proper even distribution of elements among the processes by the number of elements of each process 
            }
            for (j = 0; j < elements_per_processor; j++)                                                 /* Loop for the allocation of the elements of the sequence that belong to process P0 */
                Seq_per_processor[j] = Seq[j];                                                           // Store each element that belongs to process P0
        }
/*-------------------------------------------------------------------------------------------------- P1,...,P(p-1) ---------------------------------------------------------------------------------------------*/
        else                                                                                             /* Code that will be executed only by processes P1,...,P(p-1) */
        {
            Check_MPI_Routines (MPI_Recv (&N, 1, MPI_INT, 0, tag_N, MPI_COMM_WORLD, &status), "MPI_Recv ()"); // Receive the size of the sequence from process P0 and check with "Check_MPI_Routines ()" for any malfunction
/*................................. Waiting until the sender calls the corresponding MPI_Send (line 59) with label tag_N (sender: P0) .............................................................................*/
            elements_per_processor = N / p;                                                              // The number of elements that each process, except P0, will have
            Seq_per_processor = (int *) malloc (elements_per_processor * sizeof (int));                  // Dynamic memory allocation for storing the portion of the sequence that each process will have, except P0
            Check_Memory (Seq_per_processor);                                                            // Check with "Check_Memory ()" for any malfunction
            Check_MPI_Routines (MPI_Recv (&Seq_per_processor[0], elements_per_processor, MPI_INT, 0, tag_Seq, MPI_COMM_WORLD, &status), "MPI_Recv ()"); // Receive the corresponding portion of the sequence from process P0, which each of the other processes P1...P(p-1) will have, and check with "Check_MPI_Routines ()" for any malfunction
/*................................. Waiting until the sender calls the corresponding MPI_Send (line 68) with label tag_Seq (sender: P0) ...........................................................................*/
        }
/*-------------------------------------------------------------------------------------------------- P0,...,P(p-1) ---------------------------------------------------------------------------------------------*/   
        sort_breaker_exist = 0;                                                                          // Initialize the indicator for the existence of any element that breaks the sorting
        Check_Sort_Breaker (Seq_per_processor, elements_per_processor, &sort_breaker, &sort_breaker_exist); // Call the "Check_Sort_Breaker ()" function for the existence of any element that breaks the sorting of the elements held by the calling process
/*-------------------------------------------------------------------------------------------------- P0,...,P(p-2) ---------------------------------------------------------------------------------------------*/
        if (rank != p - 1)                                                                               /* Code that will be executed only by processes P0,...,P(p-2) */
        {
            last_element_send = Seq_per_processor[elements_per_processor - 1];                           // Store the last element from the portion that each process holds
            Check_MPI_Routines (MPI_Send (&last_element_send, 1, MPI_INT, (rank + 1) % p, tag_Last_Element, MPI_COMM_WORLD), "MPI_Send ()"); // Send the last element from the portion that each process holds to the immediately next process and check with "Check_MPI_Routines ()" for any malfunction
/*................................. Waiting until the receiver ((rank + 1) % p) calls the corresponding MPI_Recv (line 99) with label tag_Last_Element (receivers: P1,...,P(p-1)) ..............................*/
        }
/*-------------------------------------------------------------------------------------------------- P1,...,P(p-1) ---------------------------------------------------------------------------------------------*/
        if (rank != 0)                                                                                   /* Code that will be executed only by processes P1,...,P(p-1) */
        {
            Check_MPI_Routines (MPI_Recv (&last_element_recv, 1, MPI_INT, rank - 1, tag_Last_Element, MPI_COMM_WORLD, &status), "MPI_Recv ()"); // The process calling it receives the last element from the immediately previous process and checks with "Check_MPI_Routines ()" for any malfunction
/*................................. Waiting until the sender (rank - 1) calls the corresponding MPI_Send (line 93) with label tag_Last_Element (senders: P0,...,P(p-2)) ............................................*/            
            if (last_element_recv > Seq_per_processor[0])                                                /* The last element of the immediately previous process is greater than the first element of the process */
            {
                sort_breaker = last_element_recv;                                                        // Store the last element of the immediately previous process as the element that breaks the sorting
                sort_breaker_exist = 1;                                                                  // Indicate that there is an element that breaks the sorting
            }
            if (!sort_breaker_exist)                                                                     /* The last element of the immediately previous process does not break the sorting of the elements of the process calling it */
            {
                strcpy (is_sort, "yes");                                                                 // Confirm to the process, except P0, that there are no elements breaking the sorting of its elements
                Check_MPI_Routines (MPI_Send (&is_sort, 5, MPI_CHAR, 0, tag_Check_Sort_Seq, MPI_COMM_WORLD), "MPI_Send ()"); // Send the confirmation string of the absence of an element breaking the sorting to process P0 and check with "Check_MPI_Routines ()" for any malfunction
/*................................. Waiting until the receiver calls the corresponding MPI_Recv (line 115) with label tag_Check_Sort_Seq (receiver: P0) .......................................................*/
            }
            else                                                                                         /* The last element of the immediately previous process breaks the sorting of the elements of the process calling it  */
            {
                strcpy (is_sort, "no");                                                                  // Confirm to the process, except P0, that there are elements breaking the sorting of its elements
                Check_MPI_Routines (MPI_Send (&is_sort, 5, MPI_CHAR, 0, tag_Check_Sort_Seq, MPI_COMM_WORLD), "MPI_Send ()");   // Send the confirmation string of the existence of an element breaking the sorting to process P0 and check with "Check_MPI_Routines ()" for any malfunction
/*................................. Waiting until the receiver calls the corresponding MPI_Recv (line 134) with label tag_Check_Sort_Seq (receiver: P0) .......................................................*/
                Check_MPI_Routines (MPI_Send (&sort_breaker, 1, MPI_INT, 0, tag_Sort_Breaker, MPI_COMM_WORLD), "MPI_Send ()"); // Send the element that breaks the sorting of its elements to process P0 and check with "Check_MPI_Routines ()" for any malfunction
/*................................. Waiting until the receiver calls the corresponding MPI_Recv (line 138) with label tag_Sort_Breaker (receiver: P0) .........................................................*/
            }
            free (Seq_per_processor);                                                                    // Free the memory used for storing the portion of the sequence that each process received from P0
        }
/*-------------------------------------------------------------------------------------------------- P0 --------------------------------------------------------------------------------------------------------*/
        else                                                                                             /* Code that will be executed only by process P0 */
        {
            if (sort_breaker_exist)                                                                      /* Process P0 has an element that breaks the sorting */
            {
                first_sort_breaker = sort_breaker;                                                       // Store the element of P0 that breaks the sorting, which is also the first of its sequence 
                first_sort_breaker_stored = 1;                                                           // Initialize the indicator to avoid storing any elements that break the sorting from processes P1...P(p-1)
            }
            else                                                                                         /* Process P0 does not have an element that breaks the sorting */
                first_sort_breaker_stored = 0;                                                           // Initialize the indicator for storing the first element that breaks the sorting from processes P1...P(p-1)                                                  
            for (src = 1; src < p; src++)                                                                /* Helper loop for receiving the sorting status of the elements from the other processes P1...P(p-1) */ 
            {        
                Check_MPI_Routines (MPI_Recv (&is_sort, 5, MPI_CHAR, src, tag_Check_Sort_Seq, MPI_COMM_WORLD, &status), "MPI_Recv ()"); // Receive the sorting status of the elements from the other processes P1...P(p-1) and check with "Check_MPI_Routines ()" for any malfunction
/*................................. Waiting until the sender (src) calls the corresponding MPI_Send (line 115) with label tag_Check_Sort_Seq (senders: P1,...,P(p-1)) .............................................*/                 
                if (!strcmp (is_sort, "no"))                                                             /* The sorting is broken in the elements of a process other than P0 */
                {
                    Check_MPI_Routines (MPI_Recv (&sort_breaker, 1, MPI_INT, src, tag_Sort_Breaker, MPI_COMM_WORLD, &status), "MPI_Recv ()"); // Receive the element that breaks the sorting from the process that sent "no" to P0 and check with "Check_MPI_Routines ()" for any malfunction
/*................................. Waiting until the sender (src) calls the corresponding MPI_Send (line 117) with label tag_Sort_Breaker (senders: P1 or ... or P(p-1)) ............................................*/ 
                    if (first_sort_breaker_stored == 0)                                                  /* The first process other than P0 that sends the element that breaks the sorting */
                        first_sort_breaker = sort_breaker;                                               // The first element that breaks the sorting, without considering the status of process P0 yet
                    first_sort_breaker_stored++;                                                         // Increase the indicator to temporarily store the first element that breaks the sorting
                }
            }
            if (!first_sort_breaker_stored && !sort_breaker_exist)                                       /* There are no elements that break the sorting of the entire sequence */
            {
               printf ("\n\n------------------- P%d -----------------------------\n\n", rank);           // Print the identifier of the process executing this command (P0)
               printf ("Is sequence sorted? yes\n");                                                     // The conclusion of process P0 that the sequence is sorted
            }
            else                                                                                         /* There are elements that break the sorting of the entire sequence */
            {
                printf ("\n\n------------------- P%d -----------------------------\n\n", rank);          // Print the identifier of the process executing this command (P0)
                printf ("Is sequence sorted? no\n");                                                     // The conclusion of process 0 (P0) that the sequence is not sorted
                printf ("Which is the 1st sort breaker? %d\n", first_sort_breaker);                      // Print the first element that breaks the sorting of the sequence 
            }
            free (Seq);                                                                                  // Free the memory used for the entire sequence
            free (Seq_per_processor);                                                                    // Free the memory used for storing the portion of the sequence that process P0 received
/**************************************************************************************************** Menu ******************************************************************************************************/
            do                                                                                               /* Loop to ensure a valid choice from the menu */
            {
                printf ("\n");
                printf ("[1] Continue...\n");
                printf ("[2] Exit...\n");
                printf ("Input a choice : ");
                scanf ("%d", &choice);                                                                       // Input the choice from the above menu
                if (choice != 1 && choice != 2)                                                              /* Invalid choice */
                    printf ("Invalid choice!\n");                                                            // Print confirmation message
            }
            while (choice != 1 && choice != 2);                                                              /* The condition */
            for (dest = 1; dest < p; dest++)                                                             /* Helper loop for sending the user's choice from the menu to the other processes P1...P(p-1) */
                Check_MPI_Routines (MPI_Send (&choice, 1, MPI_INT, dest, tag_Choice, MPI_COMM_WORLD), "MPI_Send ()"); // Send the user's choice from the menu to the other processes P1...P(p-1) and check with "Check_MPI_Routines ()" for any malfunction
/*................................. Waiting until the receiver (dest) calls the corresponding MPI_Recv (line 179) with label tag_Choice (receivers: P1,...,P(p-1)) ............................................*/            
            if (choice == 2)                                                                             /* The user's choice was to Exit the program */
                break;                                                                                   // Exit process P0 from the infinite loop 
        }
/*-------------------------------------------------------------------------------------------------- P1,...,P(p-1) ---------------------------------------------------------------------------------------------*/    
        if (rank != 0)                                                                                   /* Code that will be executed only by processes P1...P(p-1) */
        {
            Check_MPI_Routines (MPI_Recv (&choice, 1, MPI_INT, 0, tag_Choice, MPI_COMM_WORLD, &status), "MPI_Recv ()"); // Receive the user's choice from the menu from process P0 and check with "Check_MPI_Routines ()" for any malfunction
/*................................. Waiting until the sender calls the corresponding MPI_Send (line 171) with label tag_Choice (sender: P0) .......................................................................*/ 
            if (choice == 2)                                                                             /* The user's choice was to Exit the program */
                break;                                                                                   // Exit processes P1...P(p-1) from the infinite loop
        }
    }
 /******************************************************************************************************************************************************************************************************************/
    Check_MPI_Routines (MPI_Finalize (), "MPI_Finalize ()");                                             // End the use of MPI routines and check with "Check_MPI_Routines ()" for any malfunction 
        
    return 0;
}

/****************************************************************************************** Code Check_MPI_Routines ******************************************************************************************/ 
void Check_MPI_Routines (int return_value, char *mpi_routine)                                            /* The function checks the return values of MPI routines for any errors */
{
    if (return_value != MPI_SUCCESS)                                                                     /* The return value of the MPI routine indicates an error */
    {
        printf ("Error in executing MPI routine \"%s\"\n", mpi_routine);                                 // Print error message when executing an MPI routine
        MPI_Abort (MPI_COMM_WORLD, return_value);                                                        // Abort the use of MPI routines
    }
}
/****************************************************************************************** Code Check_Memory *************************************************************************************************/ 
void Check_Memory (int *seq)                                                                             /* The function checks dynamic memory allocation for arrays for any errors */
{
    if (!seq)                                                                                            /* Memory allocation failed */
    {
        printf ("Error in allocating heap memory\n");                                                    // Print error message on dynamic allocation failure 
        exit (1);                                                                                        // Terminate the program with return value 1
    }
}
/****************************************************************************************** Code Check_Sort_Breaker ******************************************************************************************/ 
void Check_Sort_Breaker (int *seq, int n, int *ptr_sort_breaker, int *ptr_sort_breaker_exist)            /* The function checks the sorting of the elements of the calling process */
{
    int i;                                                                                               // Helper variable for loop

    for (i = 0; i < n; i++)                                                                              /* Loop for accessing the elements of the calling process */
    {
        if (i != n - 1)                                                                                  /* The iteration has not accessed the last element of the process  */
        {
            if (seq[i] > seq[i + 1])                                                                     /* The sorting is broken */
            {
                if (*ptr_sort_breaker_exist == 0)                                                        /* Indication that this is the first element of the process that breaks the sorting */
                {
                    *ptr_sort_breaker = seq[i];                                                          // The first element of the process that breaks the sorting
                    *ptr_sort_breaker_exist = 1;                                                         // Indication that an element of the process that breaks the sorting has been found
                }
            }
        }
    }   
}
