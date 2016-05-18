package tagger;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.List;

import perceptron.AbstractPerceptron;
import perceptron.SubgradientPerceptron;
import token.NERToken;
import feature.AbstractFeatureExtractor;


public class HerreraNERecognizer extends AbstractNERecognizer
{
	
	@Override
	public void train(AbstractFeatureExtractor<NERToken> extractor, AbstractPerceptron perceptron, InputStream in) throws Exception
	{
		BufferedReader reader = new BufferedReader(new InputStreamReader(in));
		List<NERToken> tokens;
		NERToken token;
		int i, y;
		int[] x;
		
		while (!(tokens = getNERTokens(reader)).isEmpty())
		{
			for (i=0; i<tokens.size(); i++)
			{
				token = tokens.get(i);
				x = extractor.getFeatureIndices(tokens, i);
				y = extractor.getLabelIndex(token.getLabel());
				perceptron.train(x, y);
			}
		}
	}
	
	static public void main(String[] args) throws Exception
	{
		final String TRN_FILE = "C:/Users/Allen Herrera/workspace/CS325/trn.ner.txt";
		final String DEV_FILE = "C:/Users/Allen Herrera/workspace/CS325/dev.ner.txt";
		final double ALPHA = 0.00001;
		final int MAX_ITER = 100;
		
		HerreraNERecognizer ner = new HerreraNERecognizer();
		
		AbstractFeatureExtractor<NERToken> ex = ner.collect(new FileInputStream(TRN_FILE));
		AbstractPerceptron perceptron = new SubgradientPerceptron(ALPHA, ex.getFeatureSize(), ex.getLabelSize());
		double score;

		for (int i=0; i<MAX_ITER; i++)
		{
			ner.train(ex, perceptron, new FileInputStream(TRN_FILE));
			score = ner.evaluate(ex, perceptron, new FileInputStream(DEV_FILE));
			System.out.printf("%3d: %5.2f\n", i, score);
		}
	}
}