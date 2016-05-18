package segment;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import ngrams.model.ILanguageModel;

public class HerreraSegment extends AbstractSegment {
Map<List<String>,Double> map1 = new HashMap<List<String>, Double>();

int counter = 0;

	public HerreraSegment(ILanguageModel model) {
		super(model);
	}
	
	@Override
	public Sequence segment(String s)
	{
		List<Sequence> list = new ArrayList<>();
		
		
		segmentAux(list,s,0,new Sequence());
		
			return Collections.max(list);
	}
	private void segmentAux(List<Sequence> list, String s,int beginIndex, Sequence sequence )
	{

		if (beginIndex == s.length())
		{
			list.add(sequence);
			//System.out.println("list"+ list.get(list.size()-1));
			return;
		}
		
		String word1 = sequence.getPreviousWord();
		// check if prev and 2 are numbers ???
				
	
		//System.out.println(" ----word 1 " + word1);
		int i, len=s.length();
		double likelihood;
		Sequence copy;
		String word2;
		
		List<String> Nestedlist;
		
		for (i=beginIndex+1;i<=len;i++)
			{	
				
					Nestedlist =new ArrayList<String>();
					
					word2= s.substring(beginIndex, i);// chunks of the string
					//System.out.print ("   word2 is :    " + word2);
							//System.out.println(" ----word 2 " + word2);
							//System.out.println(" i= " + i);
							//System.out.println(" ");
					
					Nestedlist.add(word1);
					Nestedlist.add(word2);
					Nestedlist.add(beginIndex + " " + i);
					
				boolean checkmap = false;
				if(map1.containsKey(Nestedlist)) //dynamic programming part
				{
					likelihood = map1.get(Nestedlist);
					counter += 1;
					checkmap = true;
				}
				else if (word1 == null) //first word case
				{
					if(anynumber(word2))
					{
						likelihood = 5*l_model.getLikelihood(word1, word2); // beef up numbers
					}
					else if (containsnumber(word2))
					{
						likelihood = 3*l_model.getLikelihood(word1, word2); //beef up if contains a number
					}
					else
					{
						likelihood = l_model.getLikelihood(word1, word2);
					}
				}
				else if (word1.length() == 1)
				{
					if (issingledigit(word1) && issingledigit(word2) ) // combine two single numbers
					{
							likelihood = .00000000000000000000000001 ;
					}
					else if (issingledigit(word1))
					{
						if (word2.equals("th")|| word2.equals("st")||word2.equals("nd")||word2.equals("rd")||word2.equals("s"))	
						{
							likelihood =0.001*l_model.getLikelihood(word1, word2); // combine if word2 is one of the cases
						}
						else if(containsnumber(word2))
						{
							likelihood = .000001*l_model.getLikelihood(word1, word2);
						}
						else
							likelihood = 2*l_model.getLikelihood(word1, word2); // separate if not
					}
					else if (word1.equals("i") || word1.equals("a")) 
					{
						likelihood = .05*l_model.getLikelihood(word1, word2); // dont want i and a offalone everytime its seen
					}
					else 
						likelihood = .00000000000000000000000000000000000000000001; // punish really hard if word1 is a random single letter
				}
				else if (containsnumber(word2))
				{
					likelihood = .000000000000000000000000000000000000001; // if word2 contains a number punish to add it to word1
				}
				else if (word2.length() == 1)
					{ 
						if (ismultidigit(word1) && !issingledigit(word2))
						{
							if (word2.equals("s"))	// if word1 is a number and word two is s, punish to incentivise combining the two
							{
								likelihood =0.01*l_model.getLikelihood(word1, word2);
							}
							else
								likelihood = 4*l_model.getLikelihood(word1, word2); // else separate them by buffing the probability
						}
						else if (word2.equals("I")) // if I is capital, its probably stand alone, so buff it
							{
							likelihood = .5;
							
							}
						else if (word2.equals("i") || word2.equals("a")) 
						  {
							 likelihood = .05*l_model.getLikelihood(word1, word2); //dont want i and a offalone everytime its seen, punish
						  }
						  else
						  {
							  likelihood = .000000000000000000000000000000000000001; // combine every other single letter though
						  }
					}
				else if (word2.equals("ing"))
				{
					likelihood = .000000000000000000000001; // any case of ing in word2, punish to combine with word1
				}
				else if (word1.contains("ing")&& word1.length()>4 && word1.substring((word1.length()-3),word1.length()).equals("ing") && !word2.substring(0,1).equals("s"))
				{	//System.out.println("sub is:   " +word1.substring((word1.length()-4),(word1.length()-1)));
				likelihood = 100*l_model.getLikelihood(word1, word2);; // if word1 ends in ing and word2 doesnt start with s, buff to separate the two
				}
				
				else if (word2.length() >= 2)
				{
					if ( anynumber(word1) && !ismultidigit(word2) )  
					{
						if (word2.equals("th")|| word2.equals("st")||word2.equals("nd")||word2.equals("rd"))	
						{
							likelihood = .000000000000000000001; // punish to combine these endings to word1 if its a number
						}
						else
						{
						likelihood =5*l_model.getLikelihood(word1, word2); // else buff the probability to separate the two
						}
					}
					else if (word1.contains("nt")&& word1.length()>2 && word1.substring((word1.length()-2),word1.length()).equals("nt"))
						{	//System.out.println("sub is:   " +word1.substring((word1.length()-2),(word1.length())));
						likelihood =50000*l_model.getLikelihood(word1, word2); //strongly buff the ending nt to not combine anything afterwards
						}
					else if (word2.length() == 2)
						{
							if (word2.equals("es")|| word2.equals("ed")||word2.equals("ly")||word2.equals("er")||word2.equals("or")|| word2.equals("al")||word2.equals("ty")||word2.equals("ic")||word2.equals("en"))
							{
								likelihood =.0000001*l_model.getLikelihood(word1, word2); // combine suffixes
							}
							else if (word2.equals("nt")|| word2.equals("ts")|| word2.equals("el")|| word2.equals("ud"))
							{
							  likelihood =.0000001*l_model.getLikelihood(word1, word2); // help contractions combine
							}
							else if (word1.length() == 2) 
							{
							  likelihood =.000001*l_model.getLikelihood(word1, word2); // punish multiple words of size 2
							}
							else
								likelihood =l_model.getLikelihood(word1, word2); // use base probability
						}
					else
						likelihood =l_model.getLikelihood(word1, word2); // use base probability
				}
				else{
				likelihood =l_model.getLikelihood(word1, word2); // use base probability
				}
				
				if(!checkmap){  //populate hashmap with unseen calculations 
					map1.put(Nestedlist, likelihood);
				} 
					
				copy = new Sequence(sequence);
				copy.add(word2,likelihood);
				 
				segmentAux(list,s,i,copy);
			}
	}
	
	public static boolean issingledigit(String str)  
		{  
			try{
				
		  int num = Integer.parseInt(str);
		  if(num>=0 && num <=9) 
			  return true;
		       }
			
		catch (NumberFormatException e)
		{	return false;    }
	
		  return false;  
		}
	
	public static boolean ismultidigit(String str)  
	{  
		try{
			
	  int num = Integer.parseInt(str);
	  if(num> 9) 
		  return true;
	       }
		
	catch (NumberFormatException e)
	{	return false;    }

	  return false;  
	}
	
	public static boolean anynumber(String str)  
	{  
		try{
			
	  int num = Integer.parseInt(str);
	  if(num>=0) 
		  return true;
	       }
		
	catch (NumberFormatException e)
	{	return false;    }

	  return false;  
	}
	public static boolean containsnumber(String str)
	{
		boolean AtleastOnce = false;
		
		for (int j =0; j <str.length();j++)
		{
			if (anynumber(str.substring(j, j+1)))
				{AtleastOnce = true;
				return AtleastOnce;
				}
			
		}
		return AtleastOnce;
		
	}
}
