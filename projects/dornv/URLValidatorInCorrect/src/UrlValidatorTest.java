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

   
   
   public void testManualTest()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://www.amazon.com")); //true
	   System.out.println(urlVal.isValid("http://www..amazon.com")); //false
	   System.out.println(urlVal.isValid("http:///www.amazon.com")); //false
	   System.out.println(urlVal.isValid("http:255.255.255.255")); //false
	   System.out.println(urlVal.isValid("http://255.255.255.255")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.com:80")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.com:80/test1/file")); //true
	   System.out.println(urlVal.isValid("http://www.amazon.com?action=view")); //false, but should return true
	   System.out.println(urlVal.isValid("http://www.amazon.com?action=edit&mode=up")); //false, but should return true
	   System.out.println(urlVal.isValid("http://www.amazon.com:80?action=view")); //false, but should return true
	   System.out.println(urlVal.isValid("http://www.amazon.com/../")); //false
	   System.out.println(urlVal.isValid("http://www.google.com/../")); //false
	   System.out.println(urlVal.isValid("http://www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("https://www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("h3t://www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("3ht://www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("http:/www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("http/www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("www.google.com:65a")); //false
	   System.out.println(urlVal.isValid("www.google.com")); //false, but should return true
	   System.out.println(urlVal.isValid("www.amazon.com")); //false, but should return true
	   
   }
   
   //Maybe partition based on URLs that are just one off being correct and their correct count part?
   //EX: http:/www.amazon.com and http://www.amazon.com
   //We could do this with each of the 5 URL parts
   //This could test some sort of boundary values
   //We could also test URLs with one of the 5 URL parts being incorrect
   //EX: http://www..amazon.com and http://www.amazon.com:65a
   public void testYourFirstPartition()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(urlVal.isValid("http://www.amazon.com")); //true
   }
   
   public void testYourSecondPartition(){
	   
   }
   
   //Two options:
   //1. Go through every combination of URL parts that we add to  the results pair arrays
   //2. Randomly choose 10000 combinations of URL parts from our arrays
   public void testIsValid(Object[] testObjects)
   {
	   for(int i = 0;i<10000;i++)
	   {
		   
	   }
   }
   
   public void testAnyOtherUnitTest()
   {
	   
   }
   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   //Need to add more values here
   ResultPair[] testUrlScheme = {new ResultPair("http://", true)};
   ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true)};
   ResultPair[] testUrlPort = {new ResultPair(":80", true)};
   ResultPair[] testPath = {new ResultPair("/test1", true)};
   ResultPair[] testUrlQuery = {new ResultPair("?action=view", true)};
   
   //what we will pass to testIsValid
   Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
   int[] testPartsIndex = {0, 0, 0, 0, 0};

}
