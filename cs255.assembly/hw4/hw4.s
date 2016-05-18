*I worked on this assignment alone, using only this semester's course materials.
* Allen Herrera, 1854183, aherre4@emory.edu
	xdef Start, Stop, End
	xdef Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10
	xdef A, B, C
	xdef i, j, k
	xdef head
	xdef ans_b, ans_w, ans_l

Start:
*******************************************************************
* Put your assembler instructions here
* Write the answer to each question after the corresponding label.
* DO NOT REMOVE ANY LABEL IN THIS ASSIGNMENT (all labels are now NECESSARY)
* *** Failure to do so will result in point deductions ***
*******************************************************************

Q1: MOVEA.l #A, A0	*Store a address
	Move.l #4, D0 
	ADDA.l D0, A0    *add4 to address
	MOVE.b (A0), D0  *only need a byte from data from address
	ext.w D0		*extend for safety
	ext.l D0
	Move.l D0, ans_l       *put data value  into ans_l
	
*         ans_l = A[4];





Q2: MOVEA.l #B, A1           *Store b address
	Move.l #14, D1         
	ADDA.l D1, A1         *add 14 to address to account for shift
	MOVE.w (A1), D1      *move 2 bytes of data from address in A1 into D1
	
	ext.l D1		*extend for safety
	Move.l D1, ans_l	*move data into ans_l

*         ans_l = B[7];






Q3: MOVEA.l #C, A2 		*Store C address
	Move.l k, D2
	MULS #4, D2
	ADDA.l D2, A2	*add 4*k to address to accountto access correct object
	MOVE.l (A2), D2  *move 4 bytes of data from address in A2 into D2
	
	Move.l D2, ans_l *move data into ans_l

*         ans_l = C[k];





Q4: movea.l #A, A0	*Store a address
	Move.w j, D0
	Move.l k, D1	*extend data reg. to add safely
	ext.l D0	
	add.l D1, D0	*add j+k

	
	ADDA.l D0, A0 *add J+k to shift the address needed

	Move.b (A0), D0 *move 1 byte of data from address in A0 into D0
	ext.w D0
		
	Move.w D0, ans_w  *move data into ans_w

*         ans_w = A[j + k];      




Q5: movea.l #C, A0 	*store address of C
	Move.b i, D0	
	Move.l k, D1	*store more values
	ext.w D0
	ext.l D0	*extend values to add safely

	add.l D1, D0	*add

	
	ADDA.l D0, A0	*add that value to shift the adress

	Move.w 20(A0), D0 
	ext.l D0
		
	Move.w D0, ans_w *move data into ans_w

*         ans_w = C[i + k];      




Q6:movea.l #A, A0 *store address A
	Move.b i, D0
	Move.w j, D1	*store more values
	ext.w D0
	ext.l D0
	ext.l D1

	add.l D1, D0	*add extended values
	
	ADDA.l D0, A0 *shift by that much in address

	Move.b (A0), D0  *move 1 byte of data from address in A0 into D0
	ext.w D0
	ext.l D0	
		
	Move.l D0, ans_l *move data into ans_l
*         ans_l = A[j] + B[i];  




Q7: movea.l #A, A0 	*store address of A
	Move.w #30, D0
	Move.w j, D1
	ext.w D0
	ext.l D0
	ext.l D1	

	ADDA.l D1, A0	*add
	Move.b (A0), D2	 *take value of that shifted address
	suba.l D1, A0	*subtract to get original address

	ext.w D2	
	ext.l D2

	sub.l D0, D2 * subtract to get ? to use in A[?]
	
	ADDA.l D2, A0 *shift by ?

	Move.b (A0), D0  *move 1 byte of data from address in A0 into D0
	ext.w D0
	ext.l D0	
		
	Move.l D0, ans_l *move data into ans_l

*         ans_l = A[A[j] - 30];      

	
Q8: MOVEA.l #B, A0	*Store address B
	Move.l #28, D0
	ADDA.l D0, A0	*add 28 to it (4*7)
	MOVE.w (A0), D0  *move 2 bytes of data from address in A0 into D0
	ext.w D0
	ext.l D0
	Move.w D0, ans_w *move data into ans_w


*         ans_w = B[14]





Q9: move.l head, D0		*get the address of head
	Move.l (D0), ans_l	*get the value from the address of head into ans_l
	

*	  ans_l = head.value1;



Q10: move.l head, D0	*get the address of head
	add.l #6, D0		*shift 6 (4+2)
	move.l (D0), D0		*get list 2
	add.l #6, D0		*shift 6
	move.l (D0), D0		*get list 3
	add.l #4, D0		
	move.w (D0), ans_w	*get 2nd element
*	  ans_w = head.next.next.value2; *12



*************************************************
* Don't write any code below this line
*************************************************

Stop:	nop
	nop

*************************************************
* Don't touch these variables
* You do NOT need to define more variables !!!
*************************************************

ans_b: ds.b 2
ans_w: ds.w 1
ans_l: ds.l 1

i:     dc.b  2
************************************************************************
* We need to add a 1 byte dummy variable to make the next variable j
* locate on an EVEN address.
* Due to some architectural constraints, short and int variables MUST
* start on an even address (or you will get an "odd address" error)
************************************************************************
dummy: ds.b 1

j:   dc.w  3
k:   dc.l  4

A:  dc.b   4, 11, -22, 33, -44, 55, -66, 77, -88, 99

B:  dc.w   24, 111, -222, 333, -444, 555, -666, 777, -888, 999

C:  dc.l   987, 1111, -2222, 3333, -4444, 5555, -6666, 7777, -8888, 9999


head:   dc.l  list1

list3:  dc.l 1234
        dc.w 12
	dc.l list4
list2:  dc.l 5678
        dc.w 34
	dc.l list3
list4:  dc.l 9012
        dc.w 56
	dc.l list5
list1:  dc.l 3456
        dc.w 78
	dc.l list2
list5:  dc.l 7890
        dc.w 90
	dc.l 0


End:
	end

