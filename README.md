![Alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a5/Flag_of_the_United_Kingdom_%281-2%29.svg/255px-Flag_of_the_United_Kingdom_%281-2%29.svg.png)

# MPI Program for Checking Sorted Sequence

For the requested Assignment, click the link:
[Assignment](Assignment/)

For the Source Code, click the link:
[Code](Code/)

For the detailed Documentation, click the link:
[Documentation](Documentation/)

## Assignment Overview

This project involves creating an MPI (Message Passing Interface) program in C that checks whether a sequence of integers is sorted in ascending order. The program is designed to run in a parallel environment with multiple processors (p), allowing the workload to be distributed evenly among them.

### Objectives

- Read a sequence of integers from the user.
- Check in parallel if the sequence is sorted in ascending order.
- Print the result, including the first element that breaks the sorting (if applicable).
- Handle any number of processors (p) and allow for dynamic adjustment of input size (N).
- Provide a user-friendly menu to continue checking sequences or exit the program.

## Course Information

- **Course**: [Introduction to Parallel Computing](https://ice.uniwa.gr/education/undergraduate/courses/introduction-to-parallel-computing/)
- **Semester**: 5
- **Program of Study**: [UNIWA](https://www.uniwa.gr/)
- **Department**: [Informatics and Computer Engineering](https://ice.uniwa.gr/)
- **Lab Instructor**: [Iordanakis Michael](https://ice.uniwa.gr/academic_sc_ho/)
- **Academic Season**: 2022-2023

## Student Information

- **Name**: Athanasiou Vasileios Evangelos
- **Student ID**: 19390005
- **Status**: Undergraduate

## Program Structure

### 1. Main MPI Program

- **File**: `mpi.c`
- **Functionality**: 
  - Reads the size of the integer sequence (N) and the sequence itself from the user.
  - Distributes the workload of checking whether the sequence is sorted among `p` processors.
  - Collects the results and prints whether the sequence is sorted, along with the first unsorted element if applicable.

### 2. Menu and Iteration

- The program provides a menu with options to:
  1. Continue checking another sequence.
  2. Exit the program.
- The menu is displayed repeatedly until the user chooses to exit.

## Requirements

- **Operating System**: Linux-based OS or any Unix-like system that supports MPI.
- **Compiler**: GCC (GNU Compiler Collection).
- **Libraries**: MPI library (`mpi.h`).

## Installation and Usage

### 1. Clone the Repository
Download the repository to your local machine:
```
https://github.com/Introduction-to-Parallel-Computing/MPI
```
### 2. Compile the Source Code
Compile the MPI program using the GCC compiler:
```
mpicc -o mpi mpi.c
```
### 3. Run the Program
Run the MPI program using the `mpirun` or `mpiexec` command, specifying the number of processes:
```
mpirun -np <number_of_processors> ./mpi
```

![Alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5c/Flag_of_Greece.svg/255px-Flag_of_Greece.svg.png)

# MPI Πρόγραμμα για Έλεγχο Ταξινομημένης Ακολουθίας

Για την ζητούμενη Άσκηση, κάντε κλικ στον σύνδεσμο:
[Άσκηση](Assignment/)

Για τον Κώδικα, κάντε κλικ στον σύνδεσμο:
[Κώδικας](Code/)

Για την λεπτομερή Τεκμηρίωση, κάντε κλικ στον σύνδεσμο:
[Τεκμηρίωση](Documentation/)

## Επισκόπηση Άσκησης

Αυτό το έργο περιλαμβάνει τη δημιουργία ενός προγράμματος MPI (Message Passing Interface) σε C που ελέγχει αν μια ακολουθία ακεραίων είναι ταξινομημένη σε αύξουσα σειρά. Το πρόγραμμα είναι σχεδιασμένο να εκτελείται σε ένα παράλληλο περιβάλλον με πολλαπλούς επεξεργαστές (p), επιτρέποντας την ομοιόμορφη κατανομή του φόρτου εργασίας μεταξύ τους.

### Στόχοι

- Ανάγνωση μιας ακολουθίας ακεραίων από τον χρήστη.
- Έλεγχος παράλληλα αν η ακολουθία είναι ταξινομημένη σε αύξουσα σειρά.
- Εκτύπωση του αποτελέσματος, συμπεριλαμβανομένου του πρώτου στοιχείου που χαλάει την ταξινόμηση (αν υπάρχει).
- Διαχείριση οποιουδήποτε αριθμού επεξεργαστών (p) και δυνατότητα δυναμικής προσαρμογής του μεγέθους εισόδου (N).
- Παροχή ενός φιλικού προς το χρήστη μενού για να συνεχίσει να ελέγχει ακολουθίες ή να τερματίσει το πρόγραμμα.

## Πληροφορίες Μαθήματος

- **Μάθημα**: [Εισαγωγή στον Παράλληλο Υπολογισμό](https://ice.uniwa.gr/education/undergraduate/courses/introduction-to-parallel-computing/)
- **Εξάμηνο**: 5
- **Πρόγραμμα Σπουδών**: [UNIWA](https://www.uniwa.gr/)
- **Τμήμα**: [Μηχανικών Πληροφορικής και Υπολογιστών](https://ice.uniwa.gr/)
- **Διδάσκων**: [Ιορδανάκης Μιχαήλ](https://ice.uniwa.gr/academic_sc_ho/)
- **Ακαδημαϊκή Χρονιά**: 2022-2023

## Πληροφορίες Φοιτητή

- **Όνομα**: Αθανασίου Βασίλειος Ευάγγελος
- **ΑΜ**: 19390005
- **Κατάσταση**: Προπτυχιακός

## Δομή Προγράμματος

### 1. Κύριο Πρόγραμμα MPI

- **Αρχείο**: `mpi.c`
- **Λειτουργικότητα**: 
  - Διαβάζει το μέγεθος της ακολουθίας ακεραίων (N) και την ίδια την ακολουθία από τον χρήστη.
  - Κατανέμει το φόρτο εργασίας για τον έλεγχο αν η ακολουθία είναι ταξινομημένη μεταξύ `p` επεξεργαστών.
  - Συγκεντρώνει τα αποτελέσματα και εκτυπώνει αν η ακολουθία είναι ταξινομημένη, μαζί με το πρώτο στοιχείο που δεν είναι ταξινομημένο αν χρειαστεί.

### 2. Μενού και Επανάληψη

- Το πρόγραμμα παρέχει ένα μενού με επιλογές για:
  1. Συνεχίστε να ελέγχετε άλλη ακολουθία.
  2. Έξοδο από το πρόγραμμα.
- Το μενού εμφανίζεται επανειλημμένα έως ότου ο χρήστης επιλέξει να εξέλθει.

## Απαιτήσεις

- **Λειτουργικό Σύστημα**: Λειτουργικό σύστημα βασισμένο σε Linux ή οποιοδήποτε Unix-like σύστημα που υποστηρίζει MPI.
- **Μεταγλωττιστής**: GCC (GNU Compiler Collection).
- **Βιβλιοθήκες**: Βιβλιοθήκη MPI (`mpi.h`).

## Εγκατάσταση και Χρήση

### 1. Κλωνοποιήστε το Αποθετήριο
Κατεβάστε το αποθετήριο στον τοπικό σας υπολογιστή:
```
git clone https://github.com/Introduction-to-Parallel-Computing/MPI
```
### 2. Μεταγλώττιση του Κώδικα
Μεταγλωττίστε το πρόγραμμα MPI χρησιμοποιώντας τον μεταγλωττιστή GCC:
```
mpicc -o mpi mpi.c
```
### 3. Εκτέλεση του Προγράμματος
Εκτελέστε το πρόγραμμα MPI χρησιμοποιώντας την εντολή `mpirun` ή `mpiexec`, καθορίζοντας τον αριθμό διαδικασιών:
```
mpirun -np <number_of_processors> ./mpi
```
