package edu.depaul.se433;

/*
 *  !!!! This program may contain defects.  
 */

public class Orders {

  public enum ShippingMethod { Standard, NextDay };

  public static float calculateTotal(float rawTotal, ShippingMethod shippingMethod, String destinationState) {
	if (rawTotal <= 0) throw new IllegalArgumentException("Total must be positive.");
	float total = rawTotal; 
	if (shippingMethod == ShippingMethod.Standard && total < 50) {
	  total += 10;
	} else if (shippingMethod == ShippingMethod.NextDay) {
	  total += 25; 
	}
	if (destinationState.equals("California") ||
		destinationState.equals("Illinios") ||
		destinationState.equals("New York") ||
		destinationState.equals("CA") ||
		destinationState.equals("IL") ||
		destinationState.equals("NY")) {
	  total += total * 0.06;
	}
	return total; 
  } 
  
}
