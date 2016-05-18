package sort;

import static org.junit.Assert.assertTrue;

import java.util.Arrays;
import java.util.Random;


import org.junit.Test;


import utils.DSUtils;

public class ProbabilityBucketSortTest {
	
	@Test
	public void test()
	{
		final int ITERATIONS = 10;
		final int SIZE = 100;
		
		testAccuracy(ITERATIONS, SIZE, new ProbabilityBucketSort((SIZE)));
		
	 
	}
	
 
	void testAccuracy(final int ITERATIONS, final int size, AbstractSort<Double> engine)
	{
		
		final Random rand = new Random(0);
		Double[] original, sorted;
		
		for (int i=0; i<ITERATIONS; i++)
		{
			original = getRandomDoubleArray(rand, size);
			
							//for (int o =0;o<100;o++)
							//System.out.print("["+original[o]+"] ");
			
			sorted = Arrays.copyOf(original, size);
							//	System.out.println(" ");
							//for (int o =0;o<100;o++)
							//System.out.print("["+sorted[o]+"] ");
							//System.out.println(" ");System.out.println(" ");
			engine.sort(original);
			Arrays.sort(sorted);
							//for (int o =0;o<100;o++)
							//	System.out.print("["+original[o]+"] ");
							//System.out.println(" ");
							
							//for (int o =0;o<100;o++)
							//	System.out.print("["+sorted[o]+"] ");
			assertTrue(DSUtils.equals(original, sorted));
		}
	}
	
	static public Double[] getRandomDoubleArray(Random rand, int size)
	{
		Double[] array = new Double[size];
		
		for (int i=0; i<size; i++)
			array[i] = rand.nextDouble();
		
		return array;
	}
	
}
