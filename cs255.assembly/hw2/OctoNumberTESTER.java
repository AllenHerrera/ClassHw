public class OctoNumber {

public static void main (String[] args){

String a = args[0];
System.out.println(parseOcto(a));
System.out.println("done");

}
public static int parseOcto(String s) 
	{
	int l = s.length();
		System.out.println(l);	
int setvalue = 0;
int[] savedvalue = new int [s.length()]; 
for (int i=0; i < s.length(); i++)  {   
char ReadChar = s.charAt(i);

if (ReadChar==('0'))
	setvalue= 0;
else if (ReadChar==('1'))
	setvalue= 1;
else if (ReadChar==('2'))
	setvalue= 2;
else if (ReadChar==('3'))
	setvalue= 3;
else if (ReadChar==('4'))
	setvalue= 4;
else if (ReadChar==('5'))
	setvalue= 5;
else if (ReadChar==('6'))
	setvalue= 6;
else if (ReadChar==('7'))
	setvalue= 7;
else if (ReadChar==('8'))
	setvalue= 8;
else if (ReadChar==('9'))
	setvalue= 9;
else if (ReadChar==('%'))
	setvalue= 10;
else if (ReadChar==('^'))
	setvalue= 11;
else if (ReadChar==('#'))
	setvalue= 12;
else if (ReadChar==('$'))
	setvalue= 13;
else if (ReadChar==('&'))
	setvalue= 14;
else if (ReadChar==('*'))
	setvalue= 15;
else if (ReadChar==('/'))
	setvalue= 16;
else if (ReadChar==('@'))
	setvalue= 17;
else if (ReadChar==('-'))
	setvalue= -1;
else
	System.out.println("error");
savedvalue[i] = setvalue;
}

int finalvalue = 0;System.out.println(finalvalue);
for (int y= 0; y<s.length();y++)
{ if (savedvalue[y] != -1)
	finalvalue = finalvalue + (int) (Math.pow((int) 18, (int) s.length()-1-y )*savedvalue[y]);
  
	
System.out.println("saved value " + y + " is "  + savedvalue[y]);
System.out.println(finalvalue);
}

return finalvalue;
	}

public static String toString(int a) 
	{

System.out.println("dont test");
return null;


  				     
	}
}

