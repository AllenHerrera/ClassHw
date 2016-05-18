package sort;

import static org.junit.Assert.assertTrue;

import java.util.Arrays;
import java.util.Random;

import org.junit.Ignore;
import org.junit.Test;

import utils.AbstractEngineComparer;
import utils.DSUtils;


/**
 * @author Jinho D. Choi ({@code jinho.choi@emory.edu})
 */
public class IntroSortTest
{
	@Test
	public void testAccuracy()
	{
		final int ITERATIONS = 1000;
		final int SIZE = 100;
		
		System.out.println("accuracy from IntroSortTest");
		
		testAccuracy(ITERATIONS, SIZE, new HeapSort<>());
		testAccuracy(ITERATIONS, SIZE, new IntroSort<>());
		testAccuracy(ITERATIONS, SIZE, new QuickSort<>());
		testAccuracy(ITERATIONS, SIZE, new ShellQuickSort<>());
	}
	
	void testAccuracy(final int ITERATIONS, final int SIZE, AbstractSort<Integer> engine)
	{
	
		final Random rand = new Random(0);
		Integer[] original, sorted;
		
		for (int i=0; i<ITERATIONS; i++)
		{
			original = DSUtils.getRandomIntegerArray(rand, SIZE, SIZE);
			sorted = Arrays.copyOf(original, SIZE);
			
			engine.sort(original);
			Arrays.sort(sorted);
		
			assertTrue(DSUtils.equals(original, sorted));
		}
	}
	
	@Test
    //@Ignore
	
	@SuppressWarnings("unchecked")
	public void compareSpeeds()
	{System.out.println("comparing speeds");
		final int ITERATIONS = 1000;
		final int INIT_SIZE  = 100;
		final int MAX_SIZE   = 1000;
		final int INCREMENT  = 100;
		final int OPS        = 1;
		final Random RAND    = new Random(0);
		
		System.out.println("Test@RandomArray");
		SortSpeed comp = new SortSpeed();
		comp.printTotal(ITERATIONS, INIT_SIZE, MAX_SIZE, INCREMENT, OPS, RAND, new HeapSort<>(), new QuickSort<>(), new IntroSort<>(), new ShellQuickSort<>()) ;
		
		System.out.println("Test@AscendingArray");
		SortSpeedAscend comp1 = new SortSpeedAscend();
		comp1.printTotal(ITERATIONS, INIT_SIZE, MAX_SIZE, INCREMENT, OPS, RAND, new HeapSort<>(), new QuickSort<>(), new IntroSort<>(), new ShellQuickSort<>()) ;
		
		System.out.println("Test@DescendingArray");
		SortSpeedAscend comp2 = new SortSpeedAscend();
		comp2.printTotal(ITERATIONS, INIT_SIZE, MAX_SIZE, INCREMENT, OPS, RAND, new HeapSort<>(), new QuickSort<>(), new IntroSort<>(), new ShellQuickSort<>()) ;
		
		
	}
	
	class SortSpeed extends AbstractEngineComparer<AbstractSort<Integer>>
	{  
		@Override
		@SuppressWarnings("unchecked")
		public void add(final Random RAND, final int SIZE, long[][] times, AbstractSort<Integer>... engines)
		{
			final Integer[] KEYS = getRandomIntegerArray(RAND, SIZE, SIZE);
			
			final int LEN = engines.length;
			AbstractSort<Integer> engine;
			Integer[] temp;
			long st, et;
			int i;
			
			for (i=0; i<LEN; i++)
			{
				temp = Arrays.copyOf(KEYS, SIZE);
				engine = engines[i];
				st = System.currentTimeMillis();
				engine.sort(temp);
				et = System.currentTimeMillis();
				times[i][0] += (et - st);
			}
			
		}
		
		public Integer[] getRandomIntegerArray(Random rand, int size, int range)
		{ 
			//System.out.println("Test@RandomArray");
			Integer[] array = new Integer[size];
			
			for (int i=0; i<size; i++)
				array[i] = rand.nextInt(range);
			
			return array;
		}
	}
		class SortSpeedAscend extends AbstractEngineComparer<AbstractSort<Integer>>
		{  
			@Override
			@SuppressWarnings("unchecked")
			public void add(final Random RAND, final int SIZE, long[][] times, AbstractSort<Integer>... engines)
			{
				final Integer[] KEYS = getAscendingArray(RAND, SIZE, SIZE);
				
				final int LEN = engines.length;
				AbstractSort<Integer> engine;
				Integer[] temp;
				long st, et;
				int i;
				
				for (i=0; i<LEN; i++)
				{
					temp = Arrays.copyOf(KEYS, SIZE);
					engine = engines[i];
					st = System.currentTimeMillis();
					engine.sort(temp);
					et = System.currentTimeMillis();
					times[i][0] += (et - st);
				}
				
			}
		public Integer[] getAscendingArray(Random rand, int size, int range)
		{
			//System.out.println("Test@AscendingArray");
			Integer[] array = new Integer[size];
			
			for (int i=0; i<size; i++)
				array[i] = i;
			
			return array;
		}
	}
		class SortSpeedDescend extends AbstractEngineComparer<AbstractSort<Integer>>
		{  
			@Override
			@SuppressWarnings("unchecked")
			public void add(final Random RAND, final int SIZE, long[][] times, AbstractSort<Integer>... engines)
			{
				final Integer[] KEYS = getDescendingArray(RAND, SIZE, SIZE);
				
				final int LEN = engines.length;
				AbstractSort<Integer> engine;
				Integer[] temp;
				long st, et;
				int i;
				
				for (i=0; i<LEN; i++)
				{
					temp = Arrays.copyOf(KEYS, SIZE);
					engine = engines[i];
					st = System.currentTimeMillis();
					engine.sort(temp);
					et = System.currentTimeMillis();
					times[i][0] += (et - st);
				}
				
			}
		public Integer[] getDescendingArray(Random rand, int size, int range)
		{
			//System.out.println("Test@DescendingArray");
			Integer[] array = new Integer[size];
			
			for (int i=0; i<size; i++)
				array[i] = (size-i);
			
			return array;
		}
	}
	
}
