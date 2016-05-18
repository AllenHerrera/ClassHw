/* HONOR CODE
My name is Allen Herrera, contactable at aherre4@emory.edu, id# 1854183
I worked on this homework with Kelly Kwan and referred to mainly stack overflows.
*/
public class OctoNumber {

public static int parseOcto(String s) 
	{
	int l = s.length();
int negativecounter = 0;
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

int finalvalue = 0;
	for (int y= 0; y<s.length();y++)
		{ if (savedvalue[y] != -1)
		finalvalue = finalvalue + (int) (Math.pow((int) 18, (int) s.length()-1-y )*savedvalue[y]);
		  else
			negativecounter = 1;
		}

	if (negativecounter == 1)
		return (finalvalue* -1);
	else 
		return finalvalue;
		}






public static String toString(int a) 
	{

int counter =0;

int remainder=0;
int negativecounter =0;

String savedstring= "";
if (a < 0)
	{negativecounter = 1;
	a=a*-1;}

if (a >= 1889568)
	counter = 5;
else if (a >= 104976)
	counter = 4;
else if (a >= 5832)
	counter = 3;
else if (a >= 324)
	counter = 2;
else if (a >= 18)
	counter = 1;
else
	counter = 0;


int[] savedvalues = new int [counter+1];

for (int i= counter; i >=0;i--)
	{

	savedvalues[(counter-i)] = (int) a/(int)Math.pow( (int) 18, (int) i);

	remainder = (int) a% (int)Math.pow( (int) 18, (int) i);

	a = remainder;

	}
for ( int y = 0; y<=counter;y++)
{
	if (savedvalues[y]==(0))
		savedstring += 0;
	else if (savedvalues[y]==(1))
		savedstring += "1";
	else if (savedvalues[y]==(2))
		savedstring += "2";
	else if (savedvalues[y]==(3))
		savedstring += "3";
	else if (savedvalues[y]==(4))
		savedstring += "4";
	else if (savedvalues[y]==(5))
		savedstring += "5";
	else if (savedvalues[y]==(6))
		savedstring += "6";
	else if (savedvalues[y]==(7))
		savedstring += "7";
	else if (savedvalues[y]==(8))
		savedstring += "8";
	else if (savedvalues[y]==(9))
		savedstring += "9";
	else if (savedvalues[y]==(10))
		savedstring += "%";
	else if (savedvalues[y]==(11))
		savedstring += "^";
	else if (savedvalues[y]==(12))
		savedstring += "#";
	else if (savedvalues[y]==(13))
		savedstring += "$";
	else if (savedvalues[y]==(14))
		savedstring += "&";
	else if (savedvalues[y]==(15))
		savedstring += "*";
	else if (savedvalues[y]==(16))
		savedstring += "/";
	else if (savedvalues[y]==(17))
		savedstring += "@";
	else if (savedvalues[y]==(-1))
		savedstring += -1;
	else
		System.out.println("error");
}
if (negativecounter == 1)
	return "-" + savedstring;
else 
	return savedstring;


  				     
	}
}

