*I worked on this assignment alone, using only this semester's course materials.
* Allen Herrera:::: Aherre4@emory.edu:::: 1854183
* ====================================================================
* Do not touch the following 3 xdef lists:
* ====================================================================
	xref ReadInt, WriteInt
        xdef Start, Stop, End,b2,br5,br6
       
* ********************************************************************
* Add more xdef directives below if you need more external labels
* - You can only add a label as a break point (stop location) in EGTAPI
* - if the label has been xdef!
* - You will probably need to use break points for debugging 
* - in this project.
* ********************************************************************

Start:
* ********************************************************************
* Put your main program after this line and the Stop label below
* Your main program must read in i, j, and k and
* print the value of F(i,j,k)
* ********************************************************************
	jsr ReadInt
	move.l D0, -(a7) 	*put i into stack
	

	jsr ReadInt
	move.l D0, -(a7) 	*put j into stack
	

	jsr ReadInt
	move.l D0, -(a7) 	*put k into stack
	
	
	bsr F
br5:
	move.l (a6),D0 		*write sum from stack into D0
	jsr WriteInt
br6:	
	adda.l #12, a7 		*clear stack


* ====================================================================
* Don't touch the stop label - you need it to stop the program
* ====================================================================
Stop:   nop
        nop



F:
* ********************************************************************
* Put your recursive function F here 
* ********************************************************************
	move.l a7, a6		*adjust my frame pointer
	

	move.l 12(a6),D0   	*move i into d0
b2:	
	cmp.l #0, D0		*if i<=0 
	ble return0
	

	move.l 8(a6),D1		*move j into D1
	cmp.l #0,D1		* || j<=0
	ble return0		* both cmp above branch to returning Zero
		

	move.l 4(a6),D2		*move k into D2 	
	add.l D0,D1		* i+j 
	cmp.l D2,D1		* i+j < k
	blt returnik		*branch to return i+k
	
	
	move.l #0, -(a7) 	*initialize s in stack as zero
	move.l #1, -(a7) 	*initialize t in stack as 1 (my counter)
	
	
forloop:
	
	move.l 4(a6), D2 	*move k to D2
	cmp.l -8(a6), D2 	* k < t
	ble returns

*atm -8(a6)= t, 4(a6)= s, 4(a6)= k, 8(a6)= j , 12(a6)= i
	
	move.l 12(a6), D0 	*move i into D0		
	sub.l -8(a6), D0	*i-t
	move.l D0, -(a7)	* new i in stack

	move.l 8(a6), D0 	*move j into D0
	sub.l -8(a6), D0	*j -t
	move.l D0, -(a7)	*new j in stack

	move.l 4(a6), D0 	* move k into D0
	sub.l #1,D0		* k-1
	move.l D0, -(a7)	*new k  in stack

	
	


	bsr F			*recursion yah!!!!
	
	move.l -4(a6), D3	*the returned value to be added to s

	move.l 24(a6),D4  	*move old s from stack to D4
	add.l D3, D4		* S= S + F(result)
	move.l D4, 24(a6)	*save updated s in stack

	move.l 20(a6), D3  	* t++
	add.l #1, D3
	move.l D3, 20(a6)	*update t in stack
	
	adda.l #28, a6		*clean pointer to move backwards
	adda.l #12, a7		*clean stack to move backwards
	

	bra forloop		*loops yah!!!


	

return0:
	
	move.l #0, D3		*return 0 via stack
	move.l D3, -(a7)
	move.l a7, a6		*adjust pointer
	move.l D3, -(a7)	*needed to keep stack format/order
	adda.l #8, a7		*adjust stack for rts
	rts 
returnik:
	
	add.l  D0, D2		*i + k
	move.l D2, -(a7)	* move to stack

	move.l a7, a6		*adjust pointer
	move.l D2, -(a7)	*needed to keep stack format/order
	adda.l #8, a7		*adjust Stack for rts
	rts   		

returns:

	move.l -4(a6), D4 	*return s ia stack
	adda.l #4, a7		*adjust stack
	move.l a7, a6		*adjust pointer
	move.l D4,-(a7) 	*needed to keep stack format/order

	adda.l #8, a7		*adjust stack


	rts 


* ====================================================================
* Don't add anything below this line...
* ====================================================================
End:
        end
