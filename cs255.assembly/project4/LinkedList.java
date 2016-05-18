// Write the recursion in Java first
import java.io.*;

class ListElement {
   int value;
   ListElement next;
}

class LinkedList {
   public static ListElement InsertList(ListElement head, ListElement newelem) {  
      // Develop your InsertList function in Java first!
	if (head == null || head.value <= newelem.value) {
		newelem.next = head;
		return newelem;	
	} else {
		head.next = InsertList(head.next, newelem);
		return head;
	}
	
   }

   public static void Print(ListElement head) {
      while (head != null)
       { System.out.print(head.value + " ");
         head = head.next;
       }
      System.out.println();
   }

   public static void main(String[] args) throws IOException {
       ListElement head = null;
       ListElement elem;
 
       elem = new ListElement();
       elem.value = 50;
       head = InsertList( head, elem );
       Print(head);

       elem = new ListElement();
       elem.value = 1;
       head = InsertList( head, elem );
       Print(head);

       elem = new ListElement();
       elem.value = 90;
       head = InsertList( head, elem );
       Print(head);

	elem = new ListElement();
       elem.value = 55;
       head = InsertList( head, elem );
       Print(head);

	elem = new ListElement();
       elem.value = 100;
       head = InsertList( head, elem );
       Print(head);

   }
}

