package test;
import static org.junit.Assert.*;

import java.util.Arrays;
import java.util.Collection;
import org.junit.Assume;
import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;
import org.junit.runner.RunWith;
import org.junit.runners.Parameterized;
import org.junit.runners.Parameterized.Parameters;

import converter.LengthConverter;

@RunWith(Parameterized.class)

public class LengthConverterParameterizedTest 
{
	enum ConversionType
	{
		MILE_TO_KILOMETER,
		KILOMETER_TO_MILE,
		ERROR_MILE_TO_KILOMETER,
		ERROR_KILOMETER_TO_MILE
	}
	
	@Rule
	public ExpectedException expectedException = ExpectedException.none();
	
	public LengthConverterParameterizedTest(final ConversionType type, final double expected, final double value) 
	{
		this.type = type;
		this.expected = expected;
		this.value = value;
	}
	
	@Parameters
	public static Collection<Object[]> data() 
	{
		return Arrays.asList(new Object[][] 
				{ 
					{ConversionType.KILOMETER_TO_MILE, 3.10686, 5.0 }, // expected, value
					{ConversionType.KILOMETER_TO_MILE, 6.21371, 10.0 }, 
					{ConversionType.KILOMETER_TO_MILE, 9.32057, 15.0 }, 
					{ConversionType.KILOMETER_TO_MILE, 12.4274, 20.0 }, 
					{ConversionType.KILOMETER_TO_MILE, 15.5343, 25.0},
					
					{ConversionType.MILE_TO_KILOMETER, 8.04672, 5.0},
					{ConversionType.MILE_TO_KILOMETER, 16.0934, 10.0},
					{ConversionType.MILE_TO_KILOMETER, 24.1402, 15.0},
					{ConversionType.MILE_TO_KILOMETER, 32.1868, 20.0},

					{ConversionType.ERROR_KILOMETER_TO_MILE, -40.2335, -25.0},
					{ConversionType.ERROR_KILOMETER_TO_MILE, Double.POSITIVE_INFINITY, Double.POSITIVE_INFINITY},
					{ConversionType.ERROR_KILOMETER_TO_MILE, Double.NEGATIVE_INFINITY, Double.NEGATIVE_INFINITY},
					{ConversionType.ERROR_KILOMETER_TO_MILE, Double.MAX_VALUE, Double.MAX_VALUE},
					{ConversionType.ERROR_KILOMETER_TO_MILE, -1.0, Math.sqrt(-5.0)},
					
					{ConversionType.ERROR_MILE_TO_KILOMETER, -40.2335, -25.0},
					{ConversionType.ERROR_MILE_TO_KILOMETER, Double.POSITIVE_INFINITY, Double.POSITIVE_INFINITY},
					{ConversionType.ERROR_MILE_TO_KILOMETER, Double.NEGATIVE_INFINITY, Double.NEGATIVE_INFINITY},
					{ConversionType.ERROR_MILE_TO_KILOMETER, Double.MAX_VALUE, Double.MAX_VALUE},
					{ConversionType.ERROR_MILE_TO_KILOMETER, -1.0, Math.sqrt(-5.0)}
				});
	}
	
	@Test
	public void testKMToMile() 
	{
		Assume.assumeTrue(this.type == ConversionType.KILOMETER_TO_MILE);
		
		assertEquals(expected, LengthConverter.KMToMile(value), delta);
	}

	@Test
	public void testMileToKM() 
	{
		Assume.assumeTrue(this.type == ConversionType.MILE_TO_KILOMETER);
		
		assertEquals(expected, LengthConverter.MileToKM(value), delta);
	}
	
	@Test
	public void testExceptionsKMToMile()
	{
		Assume.assumeTrue(this.type == ConversionType.ERROR_KILOMETER_TO_MILE);
		expectedException.expect(IllegalArgumentException.class);
		
		assertEquals(expected, LengthConverter.KMToMile(value), delta);
	}
	
	@Test
	public void testExceptionsMileToKM()
	{
		Assume.assumeTrue(this.type == ConversionType.ERROR_MILE_TO_KILOMETER);
		expectedException.expect(IllegalArgumentException.class);
		
		assertEquals(expected, LengthConverter.MileToKM(value), delta);
	}
	
	//Data
	private double expected; // expected output 
    private double value;     // input value 
    private ConversionType type;
	private static double delta = 0.0001;
}
