package tagger;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;


import classifier.AbstractClassifier;
import classifier.Prediction;
import classifier.StringFeature;

/**
 * @author Jinho D. Choi ({@code jinho.choi@emory.edu})
 */
public class TopKTagger extends ExhaustiveTagger
{
	final int k;
	
	public TopKTagger(AbstractClassifier classifier, int k)
	{
		super(classifier);
		this.k = k;
	}

	@Override
	protected List<Prediction> getPredictions(List<StringFeature> features)
	{
		return getKBestList(classifier.predict(features), k);
	}
	
	static public <T extends Comparable<T>>List<T> getKBestList(List<T> list, int k)
	{
		List<T> best = new ArrayList<>();
			/*.out.println("  ");System.out.println("unsorted  ");
			for (int i=0; i< list.size();i++)
			{		
					System.out.print("["+list.get(i)+"]");
			} */
		
		Collections.sort(list);
		
			/*System.out.println("  ");System.out.println("sorted  ");
			for (int i=0; i< list.size();i++)
			{		
					System.out.print("["+list.get(i)+"]");
			}*/
		
		for (int i=0; i<k;i++)
		{
				best.add(list.get(list.size()-1-i)); //print final 3 elements of the list (i.e the top 3 probabilities)
		}
			/*System.out.println("  ");System.out.println("best  ");
			for (int i=0; i< best.size();i++)
			{		
					System.out.print("["+best.get(i)+"]");
			}System.out.println("  ");System.out.println("END BEST  "); */
		return best;
	}
	
	
}