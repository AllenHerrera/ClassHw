import java.util.Scanner;

public class Project3 {
	public static int F(int i, int j, int k) {
     int s, t;
System.out.println( " " );
System.out.println( "new iteration of f" );
System.out.println( "value of i= " + i );
System.out.println( "value of j= " + j );
System.out.println( "value of k= " + k );

     if ( i <= 0 || j <= 0 ){
System.out.println( "returning 0" );
        return 0;}
     else if ( i + j < k ){
        
System.out.println( "returning i + k    " + (i+k));
	return (i+k);}
     else {
        s = 0;
        for (t = 1; t < k; t++) {
System.out.println( "value of t= " + t );
           s = s + F(i-t, j-t, k-1);

        }
System.out.println( " returning value of s= " + s );
        return s;
     }
  }

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);

		//get initial value to work with
		System.out.println("**** Welcome to the Project 3 Recursive Function Helper Program ****");
		System.out.print("Enter a value for i: ");
		int i = in.nextInt();
	
		System.out.print("Enter a value for j: ");
		int j = in.nextInt();

		System.out.print("Enter a value for k: ");
		int k = in.nextInt();

		//perform some basic input validation
		while(i != 0 || j != 0 || k != 0) {
			//initial recursive call
			int x = F(i, j, k);

			System.out.println("F(" + i + "," + j + "," + k + ") => " + x);

			//allow the user to enter other numbers
			System.out.print("\nEnter 0s for all variables to quit. ");
			System.out.println("Or enter other values.");
			
			System.out.print("Enter a value for i: ");
			i = in.nextInt();
			System.out.print("Enter a value for j: ");
			j = in.nextInt();
			System.out.print("Enter a value for k: ");
			k = in.nextInt();

		}
		System.out.println("Goodbye");

	}
}
