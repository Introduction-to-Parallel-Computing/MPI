<p align="center">
  <img src="https://www.especial.gr/wp-content/uploads/2019/03/panepisthmio-dut-attikhs.png" alt="UNIWA" width="150"/>
</p>

<p align="center">
  <strong>UNIVERSITY OF WEST ATTICA</strong><br>
  SCHOOL OF ENGINEERING<br>
  DEPARTMENT OF COMPUTER ENGINEERING AND INFORMATICS
</p>

<p align="center">
  <a href="https://www.uniwa.gr" target="_blank">University of West Attica</a> ·
  <a href="https://ice.uniwa.gr" target="_blank">Department of Computer Engineering and Informatics</a>
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
  Co-supervisor: Michalis Iordanakis, Academic Scholar
</p>

<p align="center">
  <a href="https://ice.uniwa.gr/academic_sc_ho/" target="_blank">UNIWA Profile</a> ·
  <a href="https://scholar.google.com/citations?user=LiVuwVEAAAAJ&hl=en" target="_blank">Scholar</a>
</p>

</hr>

---

<p align="center">
  Athens, December 2022
</p>

---

<p align="center">
  <img src="https://i.ytimg.com/vi/KpyhUOC-ugE/maxresdefault.jpg" width="250"/>
</p>

---

# INSTALL

## Message Passing Interface (MPI)

This guide explains how to set up, build, and run the project on your local machine.

---

## 1. Repository Setup

```bash
git clone https://github.com/Introduction-to-Parallel-Computing/MPI.git
cd MPI/src
```

---

## 2. Prerequisites

- MPI library installed (e.g., **OpenMPI** or **MPICH**)
- C compiler (e.g., **GCC**)

---

## 3. Compilation

Use `mpicc` to compile the source code:

```bash
mpicc -o Check_Sort_Seq Check_Sort_Seq.c
```

---

## 4. Running the Program

Execute the program with mpirun, specifying the number of processors:

```bash
mpirun -np 4 ./Check_Sort_Seq
```

Note:

The sequence size N must be an integer multiple of the number of processors p.

---

## 5. Usage Example

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

## 6. Open the Documentation

1. Navigate to the `docs/` directory
2. Open the report corresponding to your preferred language:
   - English: `Message-Passing-Interface.pdf`
   - Greek: `Διασύνδεση-Περασμάτων-Μηνυμάτων.pdf`
