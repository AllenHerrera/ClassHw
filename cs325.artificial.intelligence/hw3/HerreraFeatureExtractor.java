package feature;

import java.util.ArrayList;
import java.util.List;

import token.NERToken;

public class HerreraFeatureExtractor extends AbstractFeatureExtractor<NERToken>
{
	@Override
	public List<StringFeature> getStringFeatures(List<NERToken> tokens, int index)
	{
		List<StringFeature> features = new ArrayList<>();

				
		//forward a word
		if (index+1 < tokens.size()-1)
			features.add(new StringFeature("f1", tokens.get(index+1).getWord()));
		
		//forward the 2nd word	
		if(index+2 < tokens.size()-1)
			features.add(new StringFeature("f2", tokens.get(index+2).getWord()));
		
		
		// current word form
		features.add(new StringFeature("f3", tokens.get(index).getWord()));
		
		
		// previous word form
		if (index-1 >= 0)
			features.add(new StringFeature("f4", tokens.get(index-1).getWord()));
		
		// 2nd previous word form
		if (index-2 >= 0)
			features.add(new StringFeature("f5", tokens.get(index-2).getWord()));
		
		
		// previous label
		if (index-1 >= 0)
			features.add(new StringFeature("f6", tokens.get(index-1).getLabel()));
		
		// 2nd previous label
		if (index-2 >= 0)
			features.add(new StringFeature("f7", tokens.get(index-2).getLabel()));
		
		 /*3rd previous label
		if (index-3 >= 0)
			features.add(new StringFeature("f8", tokens.get(index-3).getLabel()));
		*/
		
		int Tlength =tokens.get(index).getWord().length();
		
		//forward word Prefix
		if (index+1 < tokens.size()-1)
		{int Tlength2 =tokens.get(index+1).getWord().length();
		
		for(int i =1; i<=3; i++)
		{	if (i <= Tlength2)
		{
			features.add(new StringFeature("f11", tokens.get(index+1).getWord().substring(0, i)));
		}}}
		
		//forward word suffix
		if (index+1 < tokens.size()-1)
		{int Tlength2 =tokens.get(index+1).getWord().length();
		
		for(int j =1; j<=5; j++)
		{	
			if (j <= Tlength2)
				features.add(new StringFeature("f12", tokens.get(index+1).getWord().substring(Tlength2 -j, Tlength2)));			
		}
		}
				
				
		//use prefix
		for(int i =1; i<=3; i++)
		{	if (i <= Tlength)
			features.add(new StringFeature("f8", tokens.get(index).getWord().substring(0, i)));
		}
		
		//use suffix
		for(int j =1; j<=5; j++)
		{	
			if (j <= Tlength)
				features.add(new StringFeature("f9", tokens.get(index).getWord().substring(Tlength -j, Tlength)));			
		}
		
		
		// previous words suffix
		if (index-1 >= 0)
		{
			int Tlengthim1 = tokens.get(index-1).getWord().length();
			for(int w =1; w<=3; w++)
			 {	
				if (w <= Tlengthim1)
					features.add(new StringFeature("f10", tokens.get(index-1).getWord().substring(Tlengthim1 -w, Tlengthim1)));
				
			 }
		}
		
	/*	
		if (Tlength ==1)
		features.add(new StringFeature("f11", tokens.get(index).getWord()));
		
		if (Tlength ==2)
			features.add(new StringFeature("f12", tokens.get(index).getWord()));

		if (Tlength >=6)
			features.add(new StringFeature("f13", tokens.get(index).getWord()));

		*/
				
		return features;
	}
}