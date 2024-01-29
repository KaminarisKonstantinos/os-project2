# Simple Scheduling Environment in C - OS University Project #2

This project implements a basic scheduling environment in C, capable of performing both First-Come-First-Serve (FCFS) and Round Robin (RR) scheduling for a given set of processes.

## Features

- **FCFS Scheduling:** The system follows the First-Come-First-Serve scheduling algorithm to manage the order of execution for the submitted processes.

- **RR Scheduling:** Round Robin scheduling is employed, allowing each process to run for a predefined time slice before moving to the next one in a cyclic manner.

- **IO Capability:** Each process can request an IO operation, blocking itself until the IO operation is completed.

## How to Use

To run the project on your machine, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/kaminariskonstantinos/os-project2.git
   ```
   
2. Build and compile the code:
   ```bash
   cd os-project2/project2_scheduler/work
   make
   cd ../myscheduler
   make
   ```

3. Run the bash script:
   ```bash
   ./run.sh
   ```

Happy coding!

## Documentation in Greek

For detailed information in Greek, refer to the following documents:

- **Original Assignment:** Find the original project assignment in Greek within Part 2 of the [`Project2-OS-2023-2024.pdf`](Project2-OS-2023-2024.pdf) file.

- **Project Report:** Access my detailed report, written in Greek, in Part 2 of the [`OS_Report2.pdf`](OS_Report2.pdf) file.
