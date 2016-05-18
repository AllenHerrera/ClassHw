*I worked on this assignment alone, using only this semester's course materials.
*Allen Herrera ::: Aherre4@emory.edu :::: 1854183
* BubbleSort skeleton file
* 

        xdef Start, Stop, End, break
	xref WriteInt, WriteLn
        xdef A, B, k
        xdef BubbleSort
	
*****************************************************************************
* Main program: call BubbleSort twice to sort 2 different arrays
*	 	and print the sorted arrays out
*
*       ******   DO NOT change the main program.  ***********
*
* Write your BubbleSort routine starting at the "BubbleSort:" label below
*****************************************************************************
Start:
	move.l #A, D0
	move.l #5, D1
	bsr    BubbleSort		* Sort array A

**** Print array A
	move.l #0, i
Print1: 
	move.l #5, D0
	cmp.l  i, D0
	beq    Start2

	move.l #A, A0
	move.l i, D0
	muls  #4, D0
	move.l  0(A0, D0.w), D0
	jsr    WriteInt

	addi.l  #1, i
	bra    Print1

Start2:
        move.l #str, A0
        move.l #5, D0
	jsr    WriteLn

        move.l #B, D0
        move.l #10, D1
        bsr    BubbleSort		* Sort array B

**** Print array B
        move.l #0, i
Print2:
        move.l #10, D0
        cmp.l  i, D0
        beq    Stop

        move.l #B, A0
        move.l i, D0
        muls  #4, D0
        move.l  0(A0, D0.w), D0
        jsr    WriteInt

        addi.l  #1, i
        bra    Print2


*************************************************************************
* Write your code for the BubleSort() function here
*
*  The BubbleSort subroutine MUST receive the inputs as follows:
*
*          D0 = addres of int array to be sorted
*          D1 = N
*
*  No value needs to be returned....
*************************************************************************


BubbleSort:

	move.l #0, D2   *initialize counter
	sub.l k,D1	*leave the tail elements k untouched as its sorted already

Loop:
break:	
	movea.l D0, A0
	adda.l #4, A0   *access next element
	move.l (D0), D3	* use addresses to get values
	move.l (A0), D4
	

	
	cmp D2,D1	*compare counter
	ble end 	

	add.l #1, D2	* Counter ++
	cmp D3,D4	*compare elements
	bgt continue	*switch elements if D4>D3
	move.l D3, (A0)
	move.l D4, (D0) *referencing the old array - switching


continue:
	
	add.l #4, D0	*move down an element
	
	bra Loop


****************************************************************************
* Write your assembler instructions below (do not pass the rts instruction)
****************************************************************************



end:	
	
	add.l k, D1  *get back to total elements
	
	muls #4, D2
	sub.l D2, D0 *reset D0
	
	move.l k, D5 *k counter
	add.l #1,D5  *K++
	move.l D5, k

	
	cmp D5 ,D1   * Test to know when done
	bgt BubbleSort
	
	move.l #1, k *reset k for the next array

	rts	*** I have added a rts to make sure your function returns....

* ********************************************************************
* Add more variables here if you need them
* ********************************************************************

k: dc.l 1



* ********************************************************************
* Don't touch the stop label - you need it to stop the program
* ********************************************************************
Stop:   nop
        nop

* ********************************************************************
* Don't touch these variables (used by main program)
* ********************************************************************
A:      dc.l 8, -1, -8, 4, 11
B:      dc.l 78, -1, 8, 45, 11, -89, 56, 9, 12, -19
i:      ds.l 1
str:    dc.b '--------'

End:

        end
