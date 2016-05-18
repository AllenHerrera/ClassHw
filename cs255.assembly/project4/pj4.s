*I worked on this assignment alone, using only this semester's course materials
* Allen Herrera ::: aherre4@emory.edu ::: 1854183 
*====================================================================
* Do not touch the following xdef lists:
* ====================================================================
	xref ReadInt, PrintList, malloc
        xdef Start, Stop, End, x, y, z, a, yy
        xdef head, elem
* ********************************************************************
* Add more xdef directives below if you need more external labels
* - You can only add a label as a break point (stop location) in EGTAPI
* - if the label has been xdef !!!
* - And I am pretty sure you need to use break point for debugging 
* - in this project...
* ********************************************************************

Start:
* ********************************************************************
* Put your main program after this line and the Stop label below
* See project page for a description of the main function
* ********************************************************************
	move.l #0, head
	move.l #0, -(a7) 	*my i counter for the loop
Forloop:
	move.l (a7), D3		*if/when i==5, end loop
	cmp.l #5, D3
	bge End

	jsr ReadInt		*Read in new elem

	move.l D0, -(a7)	*save this value in stack
	move.l #8, d0           * 8 byte for a List object
        jsr    malloc
    
	move.l a0, elem  	*address of elem in elem
        move.l (a7), (a0) 	* (a0) contains elem value
	adda.l #4, a7		*reset stack

	move.l head, a0		
        move.l elem, a1		*4(a1) is elem.next,(a1)is its value
x:
	bsr InsertList		*recursion yah!
	move.l d0, head  
y:	
	move.l head, a0       
	jsr PrintList		*print my linkedlist
z:	
	move.l (a7), D3		* i++
	add.l #1, D3
	move.l D3, (a7)
yy:
	bra Forloop



* ====================================================================
* Don't touch the stop label - you need it to stop the program
* ====================================================================
Stop:   nop
        nop

head:   ds.l 1
elem:   ds.l 1


InsertList:
* ********************************************************************
* Put your InsertList function here 
* ********************************************************************
	move.l a0, D1		*if head== null
	cmp.l #0, D1
	beq returnelem
	
	move.l (d1), D0		*head.value
	cmp.l (a1), D0		*or head.value <= newelem
	ble returnelem
a:
*head.next = (InsertList(head.next, newelem);
	move.l a0, -(a7)	
	movea.l 4(a0), a0
	bsr InsertList
	
*(a7) contains head address from before recursive funtion	
	move.l (a7), a0 	
	adda.l #4, a7		*adjust stack
	
	move.l d0, 4(a0)      	*head.next = newelem
	
        move.l a0, d0       	*return head
	


	rts


returnelem:
	move.l a0, 4(a1)      	*new.next = head
        move.l a1, d0       	*return(new [in d0] )
        rts


* ====================================================================
* Don't add anything below this line...
* ====================================================================
End:
        end
