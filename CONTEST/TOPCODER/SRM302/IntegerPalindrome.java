import java.util.*;
import java.util.regex.*;
import java.text.*;
import java.math.*;


public class IntegerPalindrome
{
	long getNumberOfPalindromeInKDigit(int k, int init)
	{
		if (k == 0) return 1;
		long ret = init;
		for (long i = 2; i <= k; ++i)
			ret = ret * 10;
		return ret;
	}
	
	public long findByIndex(int K)
	{
		K++;
		int L = 1;
		while (true)
		{
			long nums = getNumberOfPalindromeInKDigit((L + 1) / 2, 9);
			if (K > nums) 
				K -= nums;
			else 
				break;
			L++;
		}
		
		String ans = "";
		for (int i = (L + 1) / 2; i >= 1; --i)
		{
			long remain = getNumberOfPalindromeInKDigit(i - 1, 10);
			char c = '0';
			if (i == (L + 1) / 2) c = '1';
			
			while (K > remain) 
			{
				K -= remain;
				c++;
			}
			ans = ans + c;
		}
		
		if (L % 2 == 0) ans = ans + (new StringBuilder(ans).reverse().toString()); 
		else ans = ans + (new StringBuilder(ans).reverse().toString().substring(1));
		return Long.parseLong(ans);
	}
	
	// BEGIN KAWIGIEDIT TESTING
	// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
	private static boolean KawigiEdit_RunTest(int testNum, int p0, boolean hasAnswer, long p1) {
		System.out.print("Test " + testNum + ": [" + p0);
		System.out.println("]");
		IntegerPalindrome obj;
		long answer;
		obj = new IntegerPalindrome();
		long startTime = System.currentTimeMillis();
		answer = obj.findByIndex(p0);
		long endTime = System.currentTimeMillis();
		boolean res;
		res = true;
		System.out.println("Time: " + (endTime - startTime) / 1000.0 + " seconds");
		if (hasAnswer) {
			System.out.println("Desired answer:");
			System.out.println("\t" + p1);
		}
		System.out.println("Your answer:");
		System.out.println("\t" + answer);
		if (hasAnswer) {
			res = answer == p1;
		}
		if (!res) {
			System.out.println("DOESN'T MATCH!!!!");
		} else if ((endTime - startTime) / 1000.0 >= 2) {
			System.out.println("FAIL the timeout");
			res = false;
		} else if (hasAnswer) {
			System.out.println("Match :-)");
		} else {
			System.out.println("OK, but is it right?");
		}
		System.out.println("");
		return res;
	}
	public static void main(String[] args) {
		boolean all_right;
		all_right = true;
		
		int p0;
		long p1;
		
		// ----- test 0 -----
		p0 = 8;
		p1 = 9L;
		all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 1 -----
		p0 = 9;
		p1 = 11L;
		all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 2 -----
		p0 = 19;
		p1 = 111L;
		all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 3 -----
		p0 = 235;
		p1 = 13731L;
		all_right = KawigiEdit_RunTest(3, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 4 -----
		p0 = 23746;
		p1 = 137484731L;
		all_right = KawigiEdit_RunTest(4, p0, true, p1) && all_right;
		// ------------------
		
		if (all_right) {
			System.out.println("You're a stud (at least on the example cases)!");
		} else {
			System.out.println("Some of the test cases had errors.");
		}
	}
	// END KAWIGIEDIT TESTING
}
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
