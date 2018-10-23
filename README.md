# BooleanMinimization

## Digital Logic Design Project A2 – Exact Boolean Minimization
## Due: 23:55, Nov. 15, 2018
>> Sum of products (SOP) is a standard form for 2-level Boolean function
representation. The corresponding literals are ANDed in product terms and then ORed
together as the output. The SOP representation can be realized in either AND-OR
gates or NAND-NAND gates. Since the circuit cost is strongly correlated with the
numbers of product terms and literals. Dr. Maurice Karnaugh proposed a pictorial
form of a truth table, as known as the Karnaugh map, and combined adjacent squares
recursively for prime implicant (PI) generations. However, the Karnaugh map is
difficult to scale when the number of Boolean variables is greater than 6. Dr. Quine
and Dr. McCluskey developed a computer-based tabular form to identify all PIs
efficiently. This is the well-known Quine–McCluskey algorithm. Since the minimum
SOP representation is the subset of PIs, Dr. Petrick propose a technique to determine
all minimum SOP solutions from the PI candidates. In this project, you are going to
process a single-output Boolean function (with don't cares) in PLA format and obtain
its minimum SOP representation in PLA format using Qunie-McCluskey algorithm
followed by Petrick Algorithm. Report the number of product terms and literals.

## How to use it in Liunx?
* Download the file in your computer(OS:Linux).
* Type "g++ main.cpp -std=c++11" in your CMD.
  * Remember you need to use cd change your directory where main.cpp is.
  * If it succeed, you will see a.out added in the folder.
* And type "./a.out input.pla output.pla" to execute the program.
* If it works, you will see the result on CMD, and there are files named output.pla in the folder.
  * "input" and "output" can change to any name you want.

## Contact
* If there is any bug or question, you can use email contact me:
  * zero871015@gmail.com

Thank you.</br>
-Zero871015 10/23/2018
