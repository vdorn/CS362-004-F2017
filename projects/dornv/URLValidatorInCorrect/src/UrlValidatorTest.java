/*
 /*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import junit.framework.TestCase;
import java.util.Random;

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {

   private boolean printStatus = false;
   private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   //Manual testing
   //Manually created URLs based on some values our team thought were boundary values
   public void testManualTest()
   {
	   System.out.println("Starting Manual Testing:\n");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   System.out.println("http://www.amazon.com");
	   assertTestCase(urlVal.isValid("http://www.amazon.com"), true);
	   System.out.println("http://www..amazon.com");
	   assertTestCase(urlVal.isValid("http://www..amazon.com"), false);
	   System.out.println("http:///www.amazon.com");
	   assertTestCase(urlVal.isValid("http:///www.amazon.com"), false);
	   System.out.println("http:255.255.255.255");
	   assertTestCase(urlVal.isValid("http:255.255.255.255"), false);
	   System.out.println("http://255.255.255.255");
	   assertTestCase(urlVal.isValid("http://255.255.255.255"), true);
	   System.out.println("http://255.255.255.256");
	   assertTestCase(urlVal.isValid("http://255.255.255.256"), false);
	   System.out.println("http://255.255.256.255");
	   assertTestCase(urlVal.isValid("http://255.255.256.255"), false);
	   System.out.println("http://255.256.255.255");
	   assertTestCase(urlVal.isValid("http://255.256.255.255"), false);
	   System.out.println("http://256.255.255.255");
	   assertTestCase(urlVal.isValid("http://256.255.255.255"), false);
	   System.out.println("http://255.255.255");
	   assertTestCase(urlVal.isValid("http://255.255.255"), false);
	   System.out.println("http://255.255");
	   assertTestCase(urlVal.isValid("http://255.255"), false);
	   System.out.println("http://255");
	   assertTestCase(urlVal.isValid("http://255"), false);
	   System.out.println("http://www.amazon.com:80"); 
	   assertTestCase(urlVal.isValid("http://www.amazon.com:80"), true);
	   System.out.println("http://www.amazon.com:80/test1/file");
	   assertTestCase(urlVal.isValid("http://www.amazon.com:80/test1/file"), true);
	   System.out.println("http://www.amazon.com/?action=view"); 
	   assertTestCase(urlVal.isValid("http://www.amazon.com/?action=view"), true);
	   System.out.println("http://www.amazon.com/?action=edit&mode=up");
	   assertTestCase(urlVal.isValid("http://www.amazon.com/?action=edit&mode=up"), true);
	   System.out.println("http://www.amazon.com:80/?action=view");
	   assertTestCase(urlVal.isValid("http://www.amazon.com:80/?action=view"), true);
	   System.out.println("http://www.amazon.com/../");
	   assertTestCase(urlVal.isValid("http://www.amazon.com/../"), false);
	   System.out.println("http://www.google.com/../");
	   assertTestCase(urlVal.isValid("http://www.google.com/../"), false);
	   System.out.println("http://www.google.com:65a"); 
	   assertTestCase(urlVal.isValid("http://www.google.com:65a"), false);
	   System.out.println("https://www.google.com:65a");
	   assertTestCase(urlVal.isValid("https://www.google.com:65a"), false);
	   System.out.println("h3t://www.google.com:65a");
	   assertTestCase(urlVal.isValid("h3t://www.google.com:65a"), false);
	   System.out.println(urlVal.isValid("3ht://www.google.com:65a"));  
	   assertTestCase(urlVal.isValid("3ht://www.google.com:65a"), false);
	   System.out.println("http:/www.google.com:65a");
	   assertTestCase(urlVal.isValid("http:/www.google.com:65a"), false);
	   System.out.println("http/www.google.com:65a");
	   assertTestCase(urlVal.isValid("http/www.google.com:65a"), false);
	   System.out.println(urlVal.isValid("www.google.com:65a"));
	   assertTestCase(urlVal.isValid("www.google.com:65a"), false);
	   System.out.println(urlVal.isValid("www.google.com"));
	   assertTestCase(urlVal.isValid("www.google.com"), true);
	   System.out.println(urlVal.isValid("http://www.amazon.com:665535"));
	   assertTestCase(urlVal.isValid("http://www.amazon.com:665535"), true);
	   System.out.println(urlVal.isValid("http://www.amazon.com:665534"));
	   assertTestCase(urlVal.isValid("http://www.amazon.com:665534"), true);
	   System.out.println(urlVal.isValid("http://www.amazon.com:1"));
	   assertTestCase(urlVal.isValid("http://www.amazon.com:1"), true);
	   System.out.println(urlVal.isValid("http://www.amazon.com:9"));
	   assertTestCase(urlVal.isValid("http://www.amazon.com:9"), true);
	   System.out.println(urlVal.isValid("http://www.amazon.com:10"));
	   assertTestCase(urlVal.isValid("http://www.amazon.com:10"), true);
	   System.out.println(urlVal.isValid("http://www.amazon.com:99"));
	   assertTestCase(urlVal.isValid("http://www.amazon.com:99"), true);
	   System.out.println(urlVal.isValid("http://www.amazon.com:100"));
	   assertTestCase(urlVal.isValid("http://www.amazon.com:100"), true);
	   System.out.println(urlVal.isValid("http://www.amazon.com:999"));
	   assertTestCase(urlVal.isValid("http://www.amazon.com:999"), true);
	   System.out.println(urlVal.isValid("http://www.amazon.com:1000"));
	   assertTestCase(urlVal.isValid("http://www.amazon.com:1000"), true);
	   System.out.println(urlVal.isValid("http://www.amazon.com:9999"));
	   assertTestCase(urlVal.isValid("http://www.amazon.com:9999"), true);
	   System.out.println(urlVal.isValid("http://www.amazon.com:10000"));
	   assertTestCase(urlVal.isValid("http://www.amazon.com:10000"), true);
	   System.out.println("www.amazon.com");
	   assertTestCase(urlVal.isValid("www.amazon.com"), true);
	   System.out.println("\n");
   } 
   
   //Partition testing
   //The two partitions we chose to test were URLs that were valid and URLs that were invalid
   //Each partition contains values we deem to be boundary values and values we deem to be "normal" values
   //for the given URL part
   
   //valid partitions
   public void testYourFirstPartition()
   {
	   System.out.println("Starting First Partition:\n");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("http://www.amazon.com:80/test");
	   assertTestCase(urlVal.isValid("http://www.amazon.com:80/test"), true);
	   System.out.println("http://www.amazon.com:0/?action=edit&mode=up");
	   assertTestCase(urlVal.isValid("http://www.amazon.com:0/?action=edit&mode=up"), true);
	   System.out.println("http://www.amazon.com:0/?action=edit&mode=up");
	   assertTestCase(urlVal.isValid("http://www.amazon.com:0/?action=edit&mode=up"), true);
	   System.out.println("ftp://www.google.com:65535");
	   assertTestCase(urlVal.isValid("ftp://www.google.com:65535"), true);
	   System.out.println("https://www.google.com:65535");
	   assertTestCase(urlVal.isValid("https://www.google.com:65535"), true);
	   System.out.println("h3t://www.google.com:65535");
	   assertTestCase(urlVal.isValid("h3t://www.google.com:65535"), true);
	   System.out.println("http://www.facebook.com");
	   assertTestCase(urlVal.isValid("http://www.facebook.com"), true);
	   System.out.println("https://www.facebook.com");
	   assertTestCase(urlVal.isValid("https://www.facebook.com"), true);
	   System.out.println("https://www.facebook.com/?action=view");
	   assertTestCase(urlVal.isValid("https://www.facebook.com/?action=view"), true);
	   System.out.println("http://254.254.254.254");
	   assertTestCase(urlVal.isValid("http://254.254.254.254"), true);
	   System.out.println("\n");
   }
   
   //invalid partition
   public void testYourSecondPartition(){
	   System.out.println("Starting Second Partition:\n");
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println("http:/www.amazon.com");
	   assertTestCase(urlVal.isValid("http:/www.amazon.com"), false);
	   System.out.println("htp://www.amazon.com");
	   assertTestCase(urlVal.isValid("htp://www.amazon.com"), false);
	   System.out.println("http://wwww.amazon.com");
	   assertTestCase(urlVal.isValid("http://wwww.amazon.com"), false);
	   System.out.println("http://ww.facebook.com");
	   assertTestCase(urlVal.isValid("http://ww.facebook.com"), false);
	   System.out.println("http://www..google.com");
	   assertTestCase(urlVal.isValid("http://www..google.com"), false);
	   System.out.println("http://www.google.com:80a");
	   assertTestCase(urlVal.isValid("http://www.google.com:80a"), false);
	   System.out.println("http://www.google.com:80/testing123");
	   assertTestCase(urlVal.isValid("http://www.google.com:80/testing123"), false);
	   System.out.println("http://www.google.com:80/param?=&valid?param&=valid");
	   assertTestCase(urlVal.isValid("http://www.google.com:80/param?=&valid?param&=valid"), false);
	   System.out.println("http://www.google.com:80/?&=+?&");
	   assertTestCase(urlVal.isValid("http://www.google.com:80/?&=+?&"), false);
	   System.out.println("http://www.facebook.com/..");
	   assertTestCase(urlVal.isValid("http://www.facebook.com/.."), false);
	   System.out.println("http://www.facebook.com/..//test");
	   assertTestCase(urlVal.isValid("http://www.facebook.com/..//test"), false);
	   System.out.println(urlVal.isValid("http://www.facebook.com/../test")); //false
	   assertTestCase(urlVal.isValid("http://www.facebook.com/../test"), false);
	   System.out.println("http://www.amazon.com:-1");
	   assertTestCase(urlVal.isValid("http://www.amazon.com:-1"), false);
	   System.out.println("ftp://www.google.com:65536");
	   assertTestCase(urlVal.isValid("ftp://www.google.com:65536"), false);
	   System.out.println("http://256.256.256.256");
	   assertTestCase(urlVal.isValid("http://256.256.256.256"), true);
	   System.out.println("\n");
   }
   
   //Programmed Test
   //Randomly choose 10000 combinations of URL parts from our test object arrays
   //Values in the arrays were chosen based on boundary and non-boundary values
   public void testIsValid(Object[] testObjects)
   {
	   Random rand = new Random();
	   final int SCHEME_INDEX= 0;
	   final int AUTH_INDEX = 1;
	   final int PORT_INDEX = 2;
	   final int PATH_INDEX = 3;
	   final int QUERY_INDEX = 4;
	   
	  ResultPair[] schemes = (ResultPair[]) testObjects[SCHEME_INDEX];
	  ResultPair[] authorities = (ResultPair[]) testObjects[AUTH_INDEX];
	  ResultPair[] ports = (ResultPair[]) testObjects[PORT_INDEX];
	  ResultPair[] paths = (ResultPair[]) testObjects[PATH_INDEX];
	  ResultPair[] queries = (ResultPair[]) testObjects[QUERY_INDEX];

	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   
	   for(int i = 0; i < 10000; i++)
	   {
	 	  ResultPair scheme = schemes[rand.nextInt(schemes.length)];
	 	  ResultPair auth = authorities[rand.nextInt(authorities.length)];
	 	  ResultPair port = ports[rand.nextInt(ports.length)];
	 	  ResultPair path = paths[rand.nextInt(paths.length)];
	 	  ResultPair query = queries[rand.nextInt(queries.length)];

	 	  boolean valid = scheme.valid && auth.valid && port.valid && path.valid && query.valid;
	 	  String url = scheme.item + auth.item + port.item + path.item + query.item;
	 	  if(urlVal.isValid(url) != valid)
	 	  {
		 	  System.out.println("\"" + url + "\"");
		 	  System.out.println("Result:" + urlVal.isValid(url) + " Expected:" + valid);
		 	  System.out.println("ResultPairs input:");
		 	  System.out.println("   \"" + scheme.item + "\", " + scheme.valid);
		 	  System.out.println("   \"" + auth.item + "\", " + auth.valid);
		 	  System.out.println("   \"" + port.item + "\", " + port.valid);
		 	  System.out.println("   \"" + path.item + "\", " + path.valid);
		 	  System.out.println("   \"" + query.item + "\", " + query.valid);
		 	  System.out.println("\n");
	 		  
	 	  }
	 	  //assert(urlVal.isValid(url) ==  valid);
	   }   
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   //Need to add more values here
   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
		   new ResultPair("https://", true),
		   new ResultPair("ftp://", true),
		   new ResultPair("http:/", false),
		   new ResultPair("http//", false),
		   new ResultPair("", true)};
   ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
		   new ResultPair("www..google.com", false),
		   new ResultPair("www.amazon.com", true),
		   new ResultPair("www.facebook.com", true),
		   new ResultPair("ww.google.com", false),
		   new ResultPair("www.google.c", false),
		   new ResultPair("www.google..com", false),
		   new ResultPair("www/google.com", false),
		   new ResultPair("255.255.255.256", false),
		   new ResultPair("255.255.255.255", true)};
   ResultPair[] testUrlPort = {new ResultPair(":80", true),
		   new ResultPair(":80a", false),
		   new ResultPair("", true),
		   new ResultPair(":65535", true),
		   new ResultPair(":-1", false),
		   new ResultPair(":0", true)};
   ResultPair[] testPath = {new ResultPair("/test1", true),
		   new ResultPair("/..//test", false),
		   new ResultPair("/../", false),
		   new ResultPair("/apic.png", true),
		   new ResultPair("", true),
		   new ResultPair("/test/", true),
		   new ResultPair("/..", false)};
   ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
		   new ResultPair("?&=+?&", false),
		   new ResultPair("param?=&valid?param&=valid", false),
		   new ResultPair("testing123", false),
		   new ResultPair("?action=edit&mode=up", true),
		   new ResultPair("", true)};
   
   //what we will pass to testIsValid
   Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
   int[] testPartsIndex = {0, 0, 0, 0, 0};
   
   System.out.println("Starting testAnyOtherUnitTest... ");

   testIsValid(testUrlParts);
   }
   
   //assert function
   //used to print out URL validation errors detected in the URL Validator function
   public void assertTestCase(boolean actual, boolean expected) {
	   
	   String results ="Actual: " + actual + "; Expected: " + expected + ";";
	   
	   // Compare actual and expected values:
	   if(actual == expected) {
		   
		   System.out.println(results + " = TEST PASSED!\n");
	   }
	   else {
		   
		   System.out.println(results + " = TEST FAILED!\n");
	   }
   }
}