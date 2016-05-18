package sort;

public class IntroSort<T extends Comparable<T>> extends AbstractSort<T> {
	
	@Override
	public void sort(T[] array, int beginIndex, int endIndex) 
	{
		int MaxDepth = getMaxDepthForIntroSort(beginIndex, endIndex);
		
		introsort(array,MaxDepth,beginIndex, endIndex);		
	}	
	
	private void introsort(T[] array, int MaxDepth, int beginIndex, int endIndex)
	{
		//System.out.println(" it works!!!");
		//int n =array.length;
		if ( beginIndex +1 < endIndex)
		{
			//System.out.println(" running n>1 BOI: " + MaxDepth);
			if (MaxDepth == 0)
			{
				//System.out.println(" running HEAP BOI: " + MaxDepth);
					
			 HeapSort(array,beginIndex,endIndex);
			}
			else
			{   
				//System.out.println(" running quick: " + MaxDepth);			
				
				int pivotIndex = partition(array, beginIndex, endIndex);
				
				introsort(array, MaxDepth-1, beginIndex, pivotIndex);
			
				introsort(array, MaxDepth-1, pivotIndex+1, endIndex);
			}
	}
}
	public void HeapSort(T[] array, int beginIndex, int endIndex)
	{
		//Heapigy all elements
		for (int k=getParentIndex(beginIndex, endIndex); k>=beginIndex; k--)
			sink(array, k, beginIndex, endIndex);
		
		//Swap the endIndex element with the root element and sink it
		while (endIndex > beginIndex+1)
		{
			swap(array, beginIndex, --endIndex);
			sink(array, beginIndex, beginIndex, endIndex);
		}
	}
	
	private void sink(T[] array, int k, int beginIndex, int endIndex)
	{
		for (int i=getLeftChildIndex(beginIndex, k); i<endIndex; k=i,i=getLeftChildIndex(beginIndex, k))
		{
			if (i+1 < endIndex && compareTo(array, i, i+1) < 0) i++;
			if (compareTo(array, k, i) >= 0) break;
			swap(array, k, i);
		}
	}
	private int getParentIndex(int beginIndex, int k)
	{
		return beginIndex + (k-beginIndex)/2 - 1;
	}
	
	private int getLeftChildIndex(int beginIndex, int k)
	{
		return beginIndex + 2*(k-beginIndex) + 1;
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
}
