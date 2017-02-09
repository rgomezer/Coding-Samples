package test;
/*
 * Rodolfo Gomez
 * 4/19/16
 * SE 433
 * Assignment 3: Using JUnit and Eclipse
 */

import static org.junit.Assert.*;

import org.junit.Test;

import converter.LengthConverter;

public class LengthConverterTest {

	private static double delta = 0.0001;
	
	@Test
	public void testKMToMile() 
	{	
		double actual = LengthConverter.KMToMile(5.0);
		double testVal = 3.10686;
		
		assertEquals(testVal, actual, delta);
	}

	@Test
	public void testMileToKM() 
	{
		double actual = LengthConverter.MileToKM(5.0);
		double testVal = 8.04672;
		
		assertEquals(testVal, actual, delta);
	}
	
	@Test
	public void testKMToMile1() 
	{	
		double actual = LengthConverter.KMToMile(10.0);
		double testVal = 6.21371;
		
		assertEquals(testVal, actual, delta);
	}

	@Test
	public void testMileToKM1() 
	{
		double actual = LengthConverter.MileToKM(10.0);
		double testVal = 16.0934;
		
		assertEquals(testVal, actual, delta);
	}
	
	@Test
	public void testKMToMile2() 
	{	
		double actual = LengthConverter.KMToMile(15.0);
		double testVal = 9.32057;
		
		assertEquals(testVal, actual, delta);
	}

	@Test
	public void testMileToKM2() 
	{
		double actual = LengthConverter.MileToKM(15.0);
		double testVal = 24.1401;
		
		assertEquals(testVal, actual, delta);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testNegativeValueKMToMile() 
	{
		double actual = LengthConverter.KMToMile(-5.0);
		double testVal = -3.10686;
		
		assertEquals(testVal, actual, delta);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testNegativeValueMileToKM() 
	{
		double actual = LengthConverter.MileToKM(-5.0);
		double testVal = -8.04672;
		
		assertEquals(testVal, actual, delta);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testPositiveInfinityKMToMile() 
	{
		double actual = LengthConverter.KMToMile(Double.POSITIVE_INFINITY);
		double testVal = Double.POSITIVE_INFINITY;
		
		assertEquals(testVal, actual, delta);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testPositiveNegativeInfinityKMToMile() 
	{
		double actual = LengthConverter.KMToMile(Double.NEGATIVE_INFINITY);
		double testVal = Double.NEGATIVE_INFINITY;
		
		assertEquals(testVal, actual, delta);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testPositiveInfinityMileToKM() 
	{
		double actual = LengthConverter.MileToKM(Double.POSITIVE_INFINITY);
		double testVal = Double.POSITIVE_INFINITY;
		
		assertEquals(testVal, actual, delta);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testNegativeInfinityMileToKM() 
	{
		double actual = LengthConverter.MileToKM(Double.NEGATIVE_INFINITY);
		double testVal = Double.NEGATIVE_INFINITY;
		
		assertEquals(testVal, actual, delta);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testNotANumberKMToMile() 
	{
		double actual = LengthConverter.KMToMile(Math.sqrt(-5.0));
		double testVal = Math.sqrt(-5.0);
		
		assertEquals(testVal, actual, delta);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testNotANumberMileToKM() 
	{
		double actual = LengthConverter.MileToKM(Math.sqrt(-5.0));
		double testVal = Math.sqrt(-5.0);
		
		assertEquals(testVal, actual, delta);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testMaxDoubleKMToMile() 
	{
		double actual = LengthConverter.KMToMile(Double.MAX_VALUE);
		double testVal = Double.MAX_VALUE;
		
		assertEquals(testVal, actual, delta);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testMaxDoubleMileToKM() 
	{
		double actual = LengthConverter.MileToKM(Double.MAX_VALUE);
		double testVal = Double.MAX_VALUE;
		
		assertEquals(testVal, actual, delta);
	}
	
}
