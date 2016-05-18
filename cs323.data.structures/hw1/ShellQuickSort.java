package sort;

public class ShellQuickSort<T extends Comparable<T>> extends InsertionSort<T> {
	
	@Override
	public void sort(T[] array, int beginIndex, int endIndex) 
	{
		int MaxDepth = getMaxDepthForIntroSort(beginIndex, endIndex);
		
		shellquicksort(array,MaxDepth,beginIndex, endIndex);		
	}	
	
	private void shellquicksort(T[] array, int MaxDepth, int beginIndex, int endIndex)
	{
		//System.out.println(" it works!!!");
		//int n =array.length;
		if ( beginIndex +1 < endIndex)
		{
			//System.out.println(" running n>1 BOI: " + MaxDepth);
			if (MaxDepth == 0)
			{
				//System.out.println(" running HEAP BOI: " + MaxDepth);
					
			 ShellSort(array,beginIndex,endIndex);
			}
			else
			{   
				//System.out.println(" running quick: " + MaxDepth);			
				
				int pivotIndex = partition(array, beginIndex, endIndex);
				
				shellquicksort(array, MaxDepth-1, beginIndex, pivotIndex);
			
				shellquicksort(array, MaxDepth-1, pivotIndex+1, endIndex);
			}
	}
}
		
	protected int partition(T[] array, int beginIndex, int endIndex)
	{
		int fst = beginIndex, snd = endIndex;
		
		while (true)
		{
			while (++fst < endIndex   && compareTo(array, beginIndex, fst) >= 0);	// Find where endIndex > fst > pivot 
			while (--snd > beginIndex && compareTo(array, beginIndex, snd) <= 0);	// Find where beginIndex < snd < pivot
			if (fst >= snd) break;
			swap(array, fst, snd);
		}

		swap(array, beginIndex, snd);
		return snd;
	}
	
	protected int getMaxDepthForIntroSort(int beginIndex, int endIndex)
	{
		return 2 * (int)log2(endIndex - beginIndex);
	}
	
	private double log2(int i)
	{
		return Math.log(i) / Math.log(2);
	}
	public void ShellSort(T[] array, int beginIndex, int endIndex)
	{
		int h = getMaxH(endIndex - beginIndex);
		
		while (h >= 1)
		{
			//Insetion sort with the gap of h
			sort(array, beginIndex, endIndex, h);
			h = getNextH(h);
		}
	}
	
	public int getMaxH(int n)
	{
		final int upper = n / 3;	//Esitmate the upper bound of the sequence
		int h = 1, t;
		
		while (true)
		{
			t = 3*h + 1;			//Find the next number in the sequence
			if (t > upper) break;
			h = t;
		}
		
		return h;
	}
	
	public int getNextH(int h)
	{
		return h / 3;
	}
}
