package edu.depaul.se433;

import static org.junit.Assert.*;
import org.junit.Test;
import edu.depaul.se433.Orders.ShippingMethod;

public class OrdersTest {

	//These tests deal with the sales tax calculated in with the Total Shipping Cost
		//The states should be IL, CA, NY
		@Test
		public void testCalculateTotalSalesTaxILStandard() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.Standard, "IL");
			float actual = 42.40f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalSalesTaxILNextDay() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.NextDay, "IL");
			float actual = 58.29f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalSalesTaxIllinoisStandard() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.Standard, "Illinios");
			float actual = 42.40f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalSalesTaxIllinoisNextDay() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.NextDay, "Illinios");
			float actual = 58.29f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalSalesTaxNYStandard() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.Standard, "NY");
			float actual = 42.40f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalSalesTaxNYNextDay() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.NextDay, "NY");
			float actual = 58.29f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalSalesTaxNewYorkStandard() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.Standard, "New York");
			float actual = 42.40f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalSalesTaxNewYorkNextDay() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.NextDay, "New York");
			float actual = 58.29f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalSalesTaxCAStandard() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.Standard, "CA");
			float actual = 42.40f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalSalesTaxCACNextDay() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.NextDay, "CA");
			float actual = 58.29f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalSalesTaxCaliforniaStandard() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.Standard, "California");
			float actual = 42.40f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalSalesTaxCaliforniaCNextDay() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.NextDay, "California");
			float actual = 58.29f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		//These test(s) should be valid for any state that have no sales tax
		@Test
		public void testCalculateTotalAnyStateStandard() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.Standard, "WA");
			float actual = 40.00f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalAnyStateNextDay() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.NextDay, "WA");
			float actual = 55.00f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalAnyStateNextDay2() {
			
			float testVal1 = Orders.calculateTotal(60.0f, ShippingMethod.NextDay, "WA");
			float actual = 85.00f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		//The next set of test cases deal with error checking
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalIsZero() {
			
			float testVal1 = Orders.calculateTotal(0.0f, ShippingMethod.Standard, "WA");
			float actual = 40.00f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalNegativeValue() {
			
			float testVal1 = Orders.calculateTotal(-30.0f, ShippingMethod.NextDay, "WA");
			float actual = 55.00f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalEmptyString() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.NextDay, "");
			float actual = 55.00f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalEmptyString2() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.NextDay, " ");
			float actual = 55.00f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalNullString() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.NextDay, null);
			float actual = 55.00f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalUSTerritory() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.NextDay, "Guam");
			float actual = 55.00f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalInvalidState() {
			
			float testVal1 = Orders.calculateTotal(30.0f, ShippingMethod.NextDay, "thishouldnotwork");
			float actual = 55.00f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalPositiveInfinity() {
			
			float testVal1 = Orders.calculateTotal(Float.POSITIVE_INFINITY, ShippingMethod.NextDay, "WA");
			float actual = Float.POSITIVE_INFINITY;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalNegativeInfinity() {
			
			float testVal1 = Orders.calculateTotal(Float.NEGATIVE_INFINITY, ShippingMethod.NextDay, "WA");
			float actual = Float.NEGATIVE_INFINITY;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalNaN() {
			
			float testVal1 = Orders.calculateTotal(30.0f/0.0f, ShippingMethod.NextDay, "WA");
			float actual = Float.POSITIVE_INFINITY;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalMaxValue() {
			
			float testVal1 = Orders.calculateTotal(Float.MAX_VALUE, ShippingMethod.NextDay, "WA");
			float actual = Float.MAX_VALUE;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalMinValue() {
			
			float testVal1 = Orders.calculateTotal(Float.MIN_VALUE, ShippingMethod.Standard, "WA");
			float actual = Float.MIN_VALUE+10.0f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalCheckForOverflow() {
			
			float testVal1 = Orders.calculateTotal(Float.MAX_VALUE+10.0f, ShippingMethod.Standard, "WA");
			float actual = Float.MAX_VALUE+10.0f+10.0f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test(expected=IllegalArgumentException.class)
		public void testCalculateTotalCheckForUnderflow() {
			
			float testVal1 = Orders.calculateTotal(Float.MIN_VALUE-10.0f, ShippingMethod.Standard, "WA");
			float actual = Float.MIN_NORMAL+10.0f+10.0f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		//Edge conditions
		@Test
		public void testCalculateTotalEdgeCaseIL() {
			
			float testVal1 = Orders.calculateTotal(50.01f, ShippingMethod.Standard, "IL");
			float actual = 53.01f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalEdgeCaseIllinois() {
			
			float testVal1 = Orders.calculateTotal(50.01f, ShippingMethod.NextDay, "Illinios");
			float actual = 79.51f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalEdgeCaseIllinois2() {
			
			float testVal1 = Orders.calculateTotal(50.01f, ShippingMethod.Standard, "Illinios");
			float actual = 53.01f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalEdgeCaseIllinois3() {
			
			float testVal1 = Orders.calculateTotal(49.99f, ShippingMethod.NextDay, "Illinios");
			float actual = 79.48f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalEdgeCaseIllinois4() {
			
			float testVal1 = Orders.calculateTotal(49.99f, ShippingMethod.Standard, "Illinios");
			float actual = 63.58f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalEdgeCaseCA() {
			
			float testVal1 = Orders.calculateTotal(50.01f, ShippingMethod.Standard, "CA");
			float actual = 53.01f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalEdgeCaseCalifornia() {
			
			float testVal1 = Orders.calculateTotal(50.01f, ShippingMethod.Standard, "California");
			float actual = 53.01f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		
		@Test
		public void testCalculateTotalEdgeCaseNY() {
			
			float testVal1 = Orders.calculateTotal(50.01f, ShippingMethod.Standard, "NY");
			float actual = 53.01f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalEdgeCaseNewYork() {
			
			float testVal1 = Orders.calculateTotal(50.01f, ShippingMethod.Standard, "New York");
			float actual = 53.01f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalEdgeCaseAnyState() {
			
			float testVal1 = Orders.calculateTotal(50.01f, ShippingMethod.Standard, "WA");
			float actual = 50.01f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		@Test
		public void testCalculateTotalEdgeCaseAnyState2() {
			
			float testVal1 = Orders.calculateTotal(49.99f, ShippingMethod.Standard, "WA");
			float actual = 59.99f;
			
			assertEquals(actual, testVal1, delta);
		}
		
		//Data
		private static double delta = 0.01;

}
