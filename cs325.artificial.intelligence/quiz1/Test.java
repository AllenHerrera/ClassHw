package ngrams;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

import ngrams.smoothing.NoSmoothing;
import utils.IOUtils;

public class Test {
	public static void main(String[] args) throws FileNotFoundException
	
	{

Unigram unigram = new Unigram(new NoSmoothing());
Bigram bigram = new Bigram(new NoSmoothing());

IOUtils.readUnigrams(unigram, new FileInputStream("1grams.txt"));
IOUtils.readBigrams (bigram , new FileInputStream("2grams.txt"));

String[] w = {"he","came","to","my","school","to","study"};
double p = 1;

p= p*unigram.getLikelihood(w[0]); // running total probability
System.out.println("  " + w[0]);
System.out.println(p);
for (int i=1; w.length > i;i++) //iterate through bigram probabilities
	{
	p=p*bigram.getLikelihood(w[i-1],w[i]); //update p with each bigram probability
	//print tests to see if the numbers make sense
	System.out.println(" bigram prob of:  " + w[i-1] + "  " + w[i]);
	//System.out.println(" count of " + w[i-1] + "  " + bigram.getUnigramMap() + "  count of  "  + "  " + w[i]);
	System.out.println(bigram.getLikelihood(w[i-1],w[i]));
	System.out.println(" new total prob is " + p);
	System.out.println();
	}
   

System.out.println(p);
	}
}