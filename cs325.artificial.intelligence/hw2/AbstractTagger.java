package tagger;

import java.util.ArrayList;
import java.util.List;

import classifier.AbstractClassifier;
import classifier.StringFeature;

/**
 * @author Jinho D. Choi ({@code jinho.choi@emory.edu})
 */
public abstract class AbstractTagger
{
	protected AbstractClassifier classifier;
	
	public AbstractTagger() {}
	
	/** @param classifier a multi-classifier. */
	public AbstractTagger(AbstractClassifier classifier)
	{
		this.classifier = classifier;
	}

	/**
	 * Adds training instances from a sentences.
	 * @param words the words in the sentence.
	 * @param tags the pos-tags in the sentence.
	 */
	public void addSentence(List<String> words, List<String> tags)
	{
		TagList list = new TagList(tags);
		List<StringFeature> features;
		int i, size = words.size();
		
		for (i=0; i<size; i++)
		{
			 features = getFeatures(words, list, i);
			 classifier.addInstance(tags.get(i), features);
		}
	}
	
	public void train()
	{
		classifier.train();
	}
	
	/**
	 * @return a list of string features from the current state.
	 * @param words the list of words.
	 * @param tags the list of previously found pos-tags.
	 * @param index the current index.
	 */
	protected List<StringFeature> getFeatures(List<String> words, TagList tags, int index)
	{
		List<StringFeature> features = new ArrayList<>();
		String t;
		String word = words.get(index);
		int wLength = word.length();
		
		// current word form
		features.add(new StringFeature("f0", words.get(index)));
		
		// previous tag
		t = (index-1 < 0) ? null : tags.getTag(index-1);
		features.add(new StringFeature("f1", t));
		
		// 2nd tag back
		t = (index-2 < 0) ? null : tags.getTag(index-2);
		features.add(new StringFeature("f2", t));
		
		//3rd tag back
		t = (index-3 < 0) ? null : tags.getTag(index-3);
		features.add(new StringFeature("f3", t));
		
		//4th tag back
/*		t = (index-4 < 0) ? null : tags.getTag(index-4);
		features.add(new StringFeature("f4", t));*/
		
		
		
		//forward a word
		t = (index+1 > words.size()-1) ? null : words.get(index+1);
		features.add(new StringFeature("f5", t));
		
		t = (index+2 > words.size()-1) ? null : words.get(index+2);
		features.add(new StringFeature("f6", t));
		
/*		t = (index+3 > words.size()-3) ? null : words.get(index+3);
		features.add(new StringFeature("f7", t));*/
	
		
		
		//get previous word
		t = (index-1 < 0) ? null : words.get(index-1);
		features.add(new StringFeature("f8", t));
		
		//get 2nd previous word
		t = (index-2 < 0) ? null : words.get(index-2);
		features.add(new StringFeature("f9", t));
		
	/*	if(index-3 > 0)
			features.add(new StringFeature("f10", words.get(index-3)));*/
		
		
		//use prefix
	
			for(int i =1; i<=3; i++)
			{	t = (i <= wLength) ?  word.substring(0, i) : null;
				features.add(new StringFeature("f11", t));
			}
		
		//use suffix
			for(int j =1; j<=5; j++)
			{	
				t = (wLength-j >= 0) ?  word.substring(wLength-j, wLength) : null;
				features.add(new StringFeature("f12", t));
				
			}
			// previous words suffix
			if (index-1 >= 0)
			{for(int w =1; w<=3; w++)
			 {	
				t = (words.get(index-1).length()-w >= 0) ?  words.get(index-1).substring(words.get(index-1).length()-w, words.get(index-1).length()) : null;
				features.add(new StringFeature("f15", t));
				
			 }
			}
		
			//length based approach
			t = (wLength ==1) ?  words.get(index) : null;
			features.add(new StringFeature("f11", t));
			
			t = (wLength ==2) ?  words.get(index) : null;
			features.add(new StringFeature("f12", t));
			
			t = (wLength >=7) ?  words.get(index) : null;
			features.add(new StringFeature("f13", t));
				
		return features;
	}

	
	/**
	 * @return the list of tags with the overall probability.
	 * @param words the list of words.
	 */
	public abstract List<TagList> decode(List<String> words);
}