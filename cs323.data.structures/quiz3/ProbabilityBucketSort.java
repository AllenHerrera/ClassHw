package sort;


public class ProbabilityBucketSort extends AbstractBucketSort<Double>
{
	private final int MAX;
	
	
	public ProbabilityBucketSort(int maxDigits)
	{
		super(10, true);
		MAX = maxDigits;
	}
	
	@Override
	
	public void sort(Double[] array, int beginIndex, int endIndex)
	{
		for (int i=0; i<MAX; i++)
		{
			super.sort(array, beginIndex, endIndex);
		}
	}
	
	@Override
	protected int getBucketIndex(Double key)
	{
		return (int) (key/.1);
	}
}
