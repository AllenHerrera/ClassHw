package tagger;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;

import org.junit.Test;

import classifier.NaiveBayes;

/**
 * @author Jinho D. Choi ({@code jinho.choi@emory.edu})
 */
public class HW2Test
{
	@Test
	public void test()
	{
		
		//AbstractTagger tagger = new HMMTagger(0.0001);
		
		AbstractTagger tagger = new GreedyTagger(new NaiveBayes(0.0000001));
	
		
		try
		{
			System.out.println("Training");
			train(tagger, new FileInputStream("C:/Users/Allen Herrera/workspace/CS325/trn.pos.txt"));
			System.out.println("Decoding");
			evaluate(tagger, new FileInputStream("C:/Users/Allen Herrera/workspace/CS325/dev.pos.txt"));
		}
		catch (Exception e) {e.printStackTrace();}
	}
	
	void train(AbstractTagger tagger, InputStream in) throws Exception
	{
		BufferedReader reader = new BufferedReader(new InputStreamReader(in));
		List<String> words = new ArrayList<>(), tags = new ArrayList<>();;
		Pattern p = Pattern.compile("\t");
		String line;
		String[] t;
		
		while ((line = reader.readLine()) != null)
		{
			t = p.split(line);
			
			if (t.length < 2)
			{
				tagger.addSentence(words, tags);
				words.clear();
				tags.clear();
			}
			else
			{
				words.add(t[0]);
				tags .add(t[1]);
			}
		}
		
		tagger.train();
	}
	
	void evaluate(AbstractTagger tagger, InputStream in) throws Exception
	{
		BufferedReader reader = new BufferedReader(new InputStreamReader(in));
		List<String> words = new ArrayList<>(), tags = new ArrayList<>();;
		Pattern p = Pattern.compile("\t");
		int total = 0, correct = 0;
		String line;
		String[] t;
		
		while ((line = reader.readLine()) != null)
		{
			t = p.split(line);
			
			if (t.length < 2)
			{
				total += words.size();
				correct += correct(tags, tagger.decode(words).get(0));
				words.clear();
				tags.clear();
			}
			else
			{
				words.add(t[0]);
				tags .add(t[1]);
			}
		}
		
		System.out.printf("%5.2f (%d/%d)\n", 100d*correct/total, correct, total);
	}
	
	int correct(List<String> tags, TagList list)
	{
		int i, size = tags.size(), c = 0;
		
		for (i=0; i<size; i++)
		{
			if (tags.get(i).equals(list.getTag(i)))
				c++;
		}
		
		return c;
	}
}
