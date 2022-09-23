## Process-Scheduling ##

Implementations of the non-pre-emptive 'First come, first served' and pre-emptive 'Shortest remaining time next' with a time quantum of three seconds process scheduling algorithms. 

The implemetations read a file of structured input, execute the complied algorithm and write the results to a text file. The results include for each process its wait and turnaround time, and its success in meeting of its deadline value.

This project was initially developed without the usage of version control.

## Context ##

If no source path has been provided, algorithm will read the contents of *processes.txt* from the directory that the program resides in.

If a source path has been provided, it must be the **only** argument to the file and provided as an **absolute path**. 

Each line of the input value must contain of **space seperated** values for a single process, which include its name, arrival and service time, and its deadline value.

The values that denote these metrics are of **seconds**.

## Assumption ##

For pre-emptive algorithms, if a process is executing within a time quantum that has yet to be completed regardless of the arrival of processes of shorter burst times, the process will be alotted the entire quantum. It is only after the quantum finishes where it is determined if the process with the shortest remaining time is be changed - not during the quantum. 

## Usage ##

* Clone this repository
* Compile the program of the algorithm you desire to employ
* Execute the compiled program with one or no option 

## Option ##

* *sourcefile* - allows the user to specify a path of the file that contains process(es) information to be read and must be directly specified after the invocation of
the program 

## Execution ##

* The successful execution of the program requires the following **exact ordering** in its invocation - `./(executable program name) [sourcefile]?`