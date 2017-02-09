package edu.depaul.se433;

import static org.junit.Assert.*;
import java.lang.IllegalArgumentException;
import org.junit.Test;

public class StringUtilTest {

	//Default expected words that are pluralized normally
	@Test
	public void testPluralizeCat() {
		
		String actualVal = StringUtil.pluralize("cat");
		String expectedVal = "cats";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeBox() {
		
		String actualVal = StringUtil.pluralize("box");
		String expectedVal = "boxes";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeDog() {
		
		String actualVal = StringUtil.pluralize("dog");
		String expectedVal = "dogs";
		
		assertEquals(expectedVal, actualVal);
	}
	
	//Words that end in y tests
	@Test
	public void testPluralizePenny() {
		
		String actualVal = StringUtil.pluralize("penny");
		String expectedVal = "pennies";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeParty() {
		
		String actualVal = StringUtil.pluralize("party");
		String expectedVal = "parties";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeValley() {
		
		String actualVal = StringUtil.pluralize("valley");
		String expectedVal = "valleys";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeAttorney() {
		
		String actualVal = StringUtil.pluralize("attorney");
		String expectedVal = "attorneys";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeDelay() {
		
		String actualVal = StringUtil.pluralize("delay");
		String expectedVal = "delays";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeSoliloquy() {
		
		String actualVal = StringUtil.pluralize("soliloquy");
		String expectedVal = "soliloquies";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeOutbuy() {
		
		String actualVal = StringUtil.pluralize("outbuy");
		String expectedVal = "outbuys";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeTinkerToy() {
		
		String actualVal = StringUtil.pluralize("tinkertoy");
		String expectedVal = "tinkertoys";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeBoy() {
		
		String actualVal = StringUtil.pluralize("boy");
		String expectedVal = "boys";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizePichiy() {
		
		String actualVal = StringUtil.pluralize("pichiy");
		String expectedVal = "pichiys";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeCouiy() {
		
		String actualVal = StringUtil.pluralize("couiy");
		String expectedVal = "couiys";
		
		assertEquals(expectedVal, actualVal);
	}
	
	
	//Advanced branch coverage tests for ay, ey, iy, oy, uy
	@Test
	public void testAY() {
		
		String actualVal = StringUtil.pluralize("ay");
		String expectedVal = "ays";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testEY() {
		
		String actualVal = StringUtil.pluralize("ey");
		String expectedVal = "eys";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testIY() {
		
		String actualVal = StringUtil.pluralize("iy");
		String expectedVal = "ies";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testOY() {
		
		String actualVal = StringUtil.pluralize("oy");
		String expectedVal = "oys";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testUY() {
		
		String actualVal = StringUtil.pluralize("uy");
		String expectedVal = "uys";
		
		assertEquals(expectedVal, actualVal);
	}
	
	//Irregular words test
	@Test
	public void testPluralizeMan() {
		
		String actualVal = StringUtil.pluralize("man");
		String expectedVal = "men";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeDatum() {
		
		String actualVal = StringUtil.pluralize("datum");
		String expectedVal = "data";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizePhenomenon() {
		
		String actualVal = StringUtil.pluralize("phenomenon");
		String expectedVal = "phenomena";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizePerson() {
		
		String actualVal = StringUtil.pluralize("person");
		String expectedVal = "people";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeCrisis() {
		
		String actualVal = StringUtil.pluralize("crisis");
		String expectedVal = "crises";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeMouse() {
		
		String actualVal = StringUtil.pluralize("mouse");
		String expectedVal = "mice";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeFish() {
		
		String actualVal = StringUtil.pluralize("fish");
		String expectedVal = "fish";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeMoose() {
		
		String actualVal = StringUtil.pluralize("moose");
		String expectedVal = "moose";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeNucleus() {
		
		String actualVal = StringUtil.pluralize("nucleus");
		String expectedVal = "nuclei";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeLoaf() {
		
		String actualVal = StringUtil.pluralize("loaf");
		String expectedVal = "loaves";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeSheep() {
		
		String actualVal = StringUtil.pluralize("sheep");
		String expectedVal = "sheep";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeGoose() {
		
		String actualVal = StringUtil.pluralize("goose");
		String expectedVal = "geese";
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test
	public void testPluralizeI() {
		
		String actualVal = StringUtil.pluralize("I");
		String expectedVal = "We";
		
		assertEquals(expectedVal, actualVal);
	}
	
	//These tests are for input error checking
	@Test(expected=IllegalArgumentException.class)
	public void testPluralizeNullString() {
		
		String actualVal = StringUtil.pluralize(null);
		String expectedVal = null;
		
		assertEquals(expectedVal, actualVal);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testPluralizeEmptyString() {
		
		String testVal = StringUtil.pluralize("");
		String actualVal = "s";
		
		assertEquals(testVal, actualVal);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testPluralizeInvalidInput() {
		
		String testVal = StringUtil.pluralize("abcdefg");
		String actualVal = "abcdefg";
		
		assertEquals(testVal, actualVal);
	}
	
	@Test(expected=IllegalArgumentException.class)
	public void testPluralizeInvalidInput2() {
		
		String testVal = StringUtil.pluralize(",./<>?;\':");
		String actualVal = ",./<>?;\':";
		
		assertEquals(testVal, actualVal);
	}

}
