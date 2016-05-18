package utils;

import org.junit.Test;
import static org.junit.Assert.*;

public class MathUtilsTest {
	
	@Test
	public void getMiddleIndexTest()
	{
	    assertEquals(MathUtils.getMiddleIndex(0, 10), 5);
	}
}
