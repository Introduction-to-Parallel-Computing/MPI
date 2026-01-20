<p align="center">
  <img src="https://www.especial.gr/wp-content/uploads/2019/03/panepisthmio-dut-attikhs.png" alt="UNIWA" width="150"/>
</p>

<p align="center">
  <strong>UNIVERSITY OF WEST ATTICA</strong><br>
  SCHOOL OF ENGINEERING<br>
  DEPARTMENT OF COMPUTER ENGINEERING AND INFORMATICS
</p>

<hr/>

<p align="center">
  <strong>Introduction to Parallel Computing</strong>
</p>

<h1 align="center" style="letter-spacing: 1px;">
  Message Passing Interface (MPI)
</h1>

<p align="center">
  <strong>Vasileios Evangelos Athanasiou</strong><br>
  Student ID: 19390005
</p>

<p align="center">
  <a href="https://github.com/Ath21" target="_blank">GitHub</a> ·
  <a href="https://www.linkedin.com/in/vasilis-athanasiou-7036b53a4/" target="_blank">LinkedIn</a>
</p>

<hr/>

<p align="center">
  <strong>Supervision</strong>
</p>

<p align="center">
  Supervisor: Vasileios Mamalis, Professor
</p>
<p align="center">
  <a href="https://ice.uniwa.gr/en/emd_person/vassilios-mamalis/" target="_blank">UNIWA Profile</a>
</p>

<p align="center">
  Supervisor: Grammati Pantziou, Professor
</p>
<p align="center">
  <a href="https://ice.uniwa.gr/en/emd_person/grammati-pantziou/" target="_blank">UNIWA Profile</a> ·
  <a href="https://www.linkedin.com/in/grammati-pantziou-4731bb10a/" target="_blank">LinkedIn</a>
</p>

<p align="center">
  Co-supervisor: Michalis Iordanakis, Special Technical Laboratory Staff
</p>

<p align="center">
  <a href="https://scholar.google.com/citations?user=LiVuwVEAAAAJ&hl=en" target="_blank">UNIWA Profile</a>
</p>

<hr/>

<p align="center">
  Athens, December 2022
</p>

---

# Project Overview

This project implements a **parallel system** to check whether a sequence of integers is sorted in **ascending order**. It uses **point-to-point communication** between multiple processes without relying on collective MPI routines.  

The main objective is to distribute a sequence of size **N** equally among **p processors** and identify whether the sequence is sorted, as well as detect the **first element that violates the ascending order**.

---

## Table of Contents

| Section | Folder | Description |
|------:|--------|-------------|
| 1 | `assign/` | Assignment material for the MPI (Message Passing Interface) laboratory |
| 1.1 | `assign/PAR-LAB-EXER-I-2022-2023.pdf` | Laboratory exercise description in English |
| 1.2 | `assign/ΠΑΡ-ΕΡΓ-ΑΣΚ-Ι-2022-2023.pdf` | Περιγραφή εργαστηριακής άσκησης (Greek) |
| 2 | `docs/` | Documentation and theoretical background on MPI |
| 2.1 | `docs/Message-Passing-Interface.pdf` | MPI theory and concepts (EN) |
| 2.2 | `docs/Διασύνδεση-Περασμάτων-Μηνυμάτων.pdf` | Θεωρία Διασύνδεσης Περασμάτων Μηνυμάτων (EL) |
| 3 | `src/` | Source code for MPI programs |
| 3.1 | `src/mpi.c` | C implementation using the MPI programming model |
| 4 | `README.md` | Repository overview, build, and execution instructions |

---

## Features

- **Parallel Processing:**  
  Distributes the computational workload across multiple processors, allowing each process to check a sub-sequence concurrently.

- **Point-to-Point Communication:**  
  Uses `MPI_Send` and `MPI_Recv` to manually exchange data between processes, especially for boundary element verification.

- **Manager–Worker Model:**  
  - Process **P₀** acts as the manager:
    - Reads user input  
    - Distributes data  
    - Collects results and prints the final output  
  - Remaining processes act as workers.

- **Interactive Menu:**  
  Allows users to:
  - Run multiple sequence checks in succession  
  - Exit the program gracefully through a menu interface

---

## Technical Implementation

The program is written in **C** using the **MPI (Message Passing Interface)** environment.

### Core MPI Routines Used

- `MPI_Init`  
  Initializes the MPI execution environment.

- `MPI_Comm_rank` & `MPI_Comm_size`  
  Determine the **process ID** and the **total number of processes**.

- `MPI_Send` & `MPI_Recv`  
  Enable blocking point-to-point communication for:
  - Data distribution  
  - Boundary element comparison

- `MPI_Finalize`  
  Terminates the MPI environment cleanly.

---

## Boundary Element Logic

To ensure the entire sequence is globally sorted:

- Each process **Pᵢ** (except the last one) sends its **last element** to process **Pᵢ₊₁**.
- Process **Pᵢ₊₁** compares:
  - Its **first element**
  - With the **last element** of **Pᵢ**

This mechanism closes the gap created by simple parallel partitioning and ensures correct global ordering verification.

---

## Getting Started

### Repository Setup

```bash
git clone https://github.com/Internet-of-Things-aka-Uniwa/Traffic-Lights.git
cd Traffic-Lights
```

### Prerequisites

- MPI library installed (e.g., **OpenMPI** or **MPICH**)  
- C compiler (e.g., **GCC**)

---

## Compilation

Use `mpicc` to compile the source code:

```bash
mpicc -o Check_Sort_Seq Check_Sort_Seq.c
```

---

## Running the Program
Execute the program with mpirun, specifying the number of processors:
```bash
mpirun -np 4 ./Check_Sort_Seq
```
Note:

The sequence size N must be an integer multiple of the number of processors p.

---

## Usage Example
1. Input Size:

    Enter the total size of the sequence (e.g., 8).

2. Input Sequence:

    Enter the integers one by one.

3. Result:
    - Outputs yes if the sequence is sorted.
    - Outputs no and reports the first element that breaks the ascending order otherwise.

4. Menu Options:
    - [1] Run a new sequence check
    - [2] Exit the program

---

## Conclusion
This project demonstrates how MPI point-to-point communication can be used to solve a classic sequence validation problem in parallel. It highlights key concepts such as data distribution, process synchronization, and boundary condition handling, making it a solid example of practical parallel programming with MPI.

---

## Open the Documentation
1. Navigate to the `docs/` directory
2. Open the report corresponding to your preferred language:
    - English: `Message-Passing-Interface.pdf`
    - Greek: `Διασύνδεση-Περασμάτων-Μηνυμάτων.pdf`




