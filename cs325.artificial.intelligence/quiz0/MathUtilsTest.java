package utils;

import org.junit.Test;
import static org.junit.Assert.*;


public class MathUtilsTest {
	@Test
	public void divideTest()
	{
	    assertEquals(MathUtils.divide(1, 2), 0.5, 0);
	}
}