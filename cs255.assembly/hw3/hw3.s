******************************************************************
*Allen Herrera, id number 1854183, aherre4@emory.edu.
*I worked on this assignment alone, using only this semester's course materials
******************************************************************
a	xdef Start, Stop, End
	xdef Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10
	xdef v1, v2, v3, v4, v5, v6, v7, v8, v9, v10

Start:
*******************************************************************
* Put your assembler instructions here
* Write the answer to each question after the corresponding label.
* *** Failure to do so will result in point deductions! ***
*******************************************************************

Q1: MOVE.B #14, v1
   	
Q2: MOVE.B B, v2

Q3: MOVE.B (20000), v3

Q4: MOVE.B v4, (20001)

Q5: MOVE.W #-3000, v5

Q6: MOVE.W S, v6

Q7: MOVE.W (20002), v7

Q8: MOVE.L #-400400, v8

Q9: MOVE.L L, v9

Q10: MOVE.L (20004), v10


Stop:	nop
	nop

*************************************************
* Put your variable definitions here...
*************************************************

v1: DS.B 1	

v2: DC.B -12

v3: DC.B $A1

v4: DC.B -28

v5: DS.W 1

v6: DC.W -7

v7: DC.W -%1000000

v8: DS.L 1

v9: DC.L -15

v10: DC.L @151



*************************************************
* Don't edit any line below this text!
*************************************************
End:
         ORG 10000
B:  dc.b    13
    dc.b     0
S:  dc.w    -4
L:  dc.l    -8

         ORG 20000-$1600
    dc.b    -123
    dc.b       0
    dc.w    -314
    dc.l    -4321
	end

