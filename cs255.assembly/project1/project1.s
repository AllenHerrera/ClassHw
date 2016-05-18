*I worked on this assignment alone, using only this semester's course materials.
*Allen Herrera (1854183) aherre4@emory.edu
* ********************************************************************
* Do not touch the following 2 xdef lists:
* ********************************************************************
        xdef Start, Stop, End
        xdef a, b, len_a, len_b, min, max, common

* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
* You can add more xdef here to export labels to EGTAPI
* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	xdef break1,break2, i, j, common

* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*      Put your assembler program here - between the start and stop label
*      DO NOT define any variables here - see the variable section below
* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Start:
	movea.l #a, A0          *load base address
	movea.l #b, A1
	move.l 0(A0, D0.l), min *initialize min
	
WhileA:
	move.l i, D0    

	muls #4, D0	        *since long words, need to shift properly
	move.l 0(A0, D0.l), D7  *a[i] into D7
	cmp D7, D3	        *if D7 > D3; D3 = D7
	blt Greater_thanA   

greater_checkA:

	cmp D7, D2	        *if D7 < D3; D3 = D7
	bgt Less_thanA    

less_checkA:
	move.l j, D4		*counter for b array
While2commonCheck:   
	

	muls #4, D4             *(long words)x4 need to shift properly

	move.l 0(A1, D4.l), D6  * b[j] stored in D6

	cmp D7, D6		*compare a[i] and b[j]
	BEQ Counter_plusplus	
	

comm_continue:
	
	Divs #4, D4


	add.l #1, D4 		 *j++
	

	cmp.l #len_b, D4         *if len_b = j, then exit nested loop
	bge WhileAcontinued
	
	bra While2commonCheck	 *loop back if not exited

WhileAcontinued:
	
	Divs #4, D0   

	add.l #1, D0 		 * i++
	move.l D0, i

	cmp.l #len_a, D0         *if len_a = i
	bge WhileB	         *a array done, exit loop, check b array


break1:
	bra WhileA

Greater_thanA:
	move.l D7, D3  		 *new greatestest from A
	move.l D3, max
	bra greater_checkA

Less_thanA:
	move.l D7, D2  		 *new lowestfrom A
	move.l D2, min
	bra less_checkA
Counter_plusplus:	
	move.l common, D1	* new common value between A & B
	add.l #1, D1
	move.l D1, common 
	
	bra comm_continue



WhileB:
	
	move.l j, D1
	
	muls #4, D1  	       *since long words, need to shift properly

	move.l 0(A1, D1.l), D7

	cmp D7, D3	       *if D7 > D3; D3 = D7
	blt Greater_thanB

greater_checkB:

	cmp D7, D2	       *if D7 < D3; D3 = D7
	bgt Less_thanB
less_checkB:

	Divs #4, D1

	add.l #1, D1           * j++
	move.l D1, j

	cmp.l #len_b, D1       *if len_b = j, then exit Bloop
	bge EndWhile	       *done
break2:
	bra WhileB

Greater_thanB:
	move.l D7, D3 	       *new greatest from B
	move.l D3, max
	bra greater_checkB

Less_thanB:
	move.l D7, D2          *new lowest from B
	move.l D2, min
	bra less_checkB

EndWhile:
				


* ********************************************************************
* Don't touch the stop label - you need it to stop the program
* ********************************************************************
Stop:   nop


End:    nop

* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*    Variable Section -   Put your variables here
*
*    DO NOT define a, b, min, max, common, etc
*    They are already defined below
* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

i: dc.l 0
j: dc.l 0

* ********************************************************************
* XXXX Don't touch anything below this line !!!
* ********************************************************************
a:      dc.l  1, 2, 3, 4, 5
b:      dc.l  6, 7, 8, 9, 10, 11 
len_a: 	equ 5
len_b:	equ 6
min:	ds.l 1
max:	ds.l 1
common:	ds.l 1

* ********************************************************************
* Add more variables below if you need them
* ********************************************************************




        end
