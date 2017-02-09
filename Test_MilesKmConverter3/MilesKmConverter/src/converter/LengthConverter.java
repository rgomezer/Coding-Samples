package converter;
/*
 * Rodolfo Gomez
 * 4/19/16
 * SE 433
 * Assignment 3: Using JUnit and Eclipse
 */

public class LengthConverter 
{
	public static double KMToMile(final double x)
	{
		if(x <= 0 || Double.isInfinite(x) || Double.isNaN(x) || x >= Double.MAX_VALUE)
		{
			throw new IllegalArgumentException();
		}
		
		return x * 0.621371192;
	}
	
	public static double MileToKM(final double x)
	{
		if(x <= 0 || Double.isInfinite(x) || Double.isNaN(x) || x >= Double.MAX_VALUE)
		{
			throw new IllegalArgumentException();
		}
		
		return x * 1.60934;
	}
	
	public static void main(String[] args)
	{
		System.out.println("Convert 5 miles to km");
		System.out.println(MileToKM(5.0) + " km");
		
		System.out.println("Convert 10 miles to km");
		System.out.println(MileToKM(10.0) + " km");
		
		System.out.println("Convert 15 miles to km");
		System.out.println(MileToKM(15.0) + " km");
		
		System.out.println("Convert 20 miles to km");
		System.out.println(MileToKM(20.0) + " km");
		
		System.out.println("Convert 25 miles to km");
		System.out.println(MileToKM(25.0) + " km");
		
		System.out.println("Convert 5 km to miles");
		System.out.println(KMToMile(5.0) + " mi");
		
		System.out.println("Convert 10 km to miles");
		System.out.println(KMToMile(10.0) + " mi");
		
		System.out.println("Convert 15 km to miles");
		System.out.println(KMToMile(15.0) + " mi");
		
		System.out.println("Convert 20 km to miles");
		System.out.println(KMToMile(20.0) + " mi");
		
		System.out.println("Convert 25 km to miles");
		System.out.println(KMToMile(25.0) + " mi");
	}
}
