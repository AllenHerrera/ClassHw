package segment;

import java.io.FileInputStream;

import ngrams.Bigram;
import ngrams.Unigram;
import ngrams.model.Backoff;
import ngrams.model.ILanguageModel;
import ngrams.smoothing.DiscountSmoothing;
import ngrams.smoothing.NoSmoothing;
import segment.AbstractSegment;
import segment.Segment;
import segment.Sequence;
import org.junit.Test;

import utils.IOUtils;



/**
 * @author Jinho D. Choi ({@code jinho.choi@emory.edu})
 */
public class SegmentTest
{
	@Test
	public void test() throws Exception
	{
		Unigram unigram = new Unigram(new DiscountSmoothing(0.9));
		Bigram bigram = new Bigram(new NoSmoothing());

		IOUtils.readUnigrams(unigram, new FileInputStream("1grams.txt"));
		IOUtils.readBigrams (bigram , new FileInputStream("2grams.txt"));
		
		double unigramWeight = .01;
		ILanguageModel model = new Backoff(unigram, bigram, unigramWeight);
		AbstractSegment segment = new Segment(model);
		
		test(segment, "therealdeal");
		test(segment, "isitoveryet");
		test(segment, "isplayingnow");
		test(segment, "thisiswhoweare");
		test(segment, "areallygoodjob");
	}
	
	void test(AbstractSegment segment, String s)
	{
		Sequence sequence = segment.segment(s);
		System.out.println(sequence.getSequence()+" "+sequence.getMaximumLikelihood());		
	}
}