package segment;

import java.io.FileInputStream;
import java.util.List;

import ngrams.Bigram;
import ngrams.Unigram;
import ngrams.model.Backoff;
import ngrams.model.Interpolation;
import ngrams.model.ILanguageModel;
import ngrams.smoothing.LaplaceSmoothing;
import ngrams.smoothing.DiscountSmoothing;
import ngrams.smoothing.NoSmoothing;

import org.junit.Test;

import utils.IOUtils;

public class HerreraSegmentTest {
	
	@Test
	public void test() throws Exception
	{
		System.out.println("running@HerreraTest");
		Unigram unigram = new Unigram(new DiscountSmoothing(.9));
		//Unigram unigram = new Unigram(new LaplaceSmoothing(1));
		
		Bigram bigram = new Bigram(new NoSmoothing());
		//Bigram bigram = new Bigram(new DiscountSmoothing(0.9));
		//Bigram bigram = new Bigram(new LaplaceSmoothing(1));
		
		IOUtils.readUnigrams(unigram, new FileInputStream("1grams.txt"));
		IOUtils.readBigrams (bigram , new FileInputStream("2grams.txt"));
		
		//double unigramWeight = .01;
		double unigramWeight = .005;
		double bigramWeight = .995;
		
		//ILanguageModel model = new Backoff(unigram, bigram, unigramWeight);
		ILanguageModel model = new Interpolation(unigram, bigram, unigramWeight, bigramWeight);
		
		AbstractSegment segment = new HerreraSegment(model);
		
	
		//test(segment, "therealdeal");
		test(segment, "2thingsthatdontmix");
		test(segment, "10turnons");
		test(segment, "90s");
		//test(segment, "haveiwon");
		//test(segment, "throwbackthursday");
		test(segment, "100thingsaboutme");
		test(segment, "alliwant");
		test(segment, "annoyingbios");
		test(segment, "aprilfoolsjokes");
		test(segment, "areallygoodejob");
		test(segment, "jinhoishere");
		test(segment, "riskitforthebiscuit");
		test(segment, "windowdressing");
		test(segment, "howimetyourmother");
		test(segment, "onlyonmondays");
		test(segment, "4amnights");
		//test(segment, "arelationshipisoverwhen");
		//test(segment, "artistseveryonelikesbutidont");
		//test(segment, "donttrythisathome");
		//test(segment, "Iwin");
	}
	
	void test(AbstractSegment segment, String s)
	{
		Sequence sequence = segment.segment(s);
		//List<String> List =sequence.getSequence();
		//for (int i = 0; i < List.size(); i++) 
			//{
			   // String element = List.get(i);
				//if (element.length()==1 && element.compareTo("I")!=0)
					//{System.out.println(element);
						//element = element + List.get(i+1);
						//List.remove(i);
					//}
			//}
		//sequence.l_words= List;
		
		System.out.println(sequence.getSequence()+" "+sequence.getMaximumLikelihood());		
	}
}
