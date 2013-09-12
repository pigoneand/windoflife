import java.util.*;
import java.util.regex.*;
import java.text.*;
import java.math.*;


public class SpiralNumbers
{
	public String getPosition(int N)
	{
		long target = N;
		int r = 0, c = 0;
		long n;
		for (n = 1; n * n < target; n += 2, r--, c++);
		long now = n * n;
		
		long c1 = (n - 1);
		long c2 = (n - 1);
		long c3 = (n - 1);
		while (now > target)
		{
			now--;
			if (c1 > 0) { c1--; c--; continue; }
			if (c2 > 0) { c2--; r++; continue; }
			if (c3 > 0) { c3--; c++; continue; }
			r--; 
		}
		return "(" + r + "," + c + ")";
	}
	
	// BEGIN KAWIGIEDIT TESTING
	// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
	private static boolean KawigiEdit_RunTest(int testNum, int p0, boolean hasAnswer, String p1) {
		System.out.print("Test " + testNum + ": [" + p0);
		System.out.println("]");
		SpiralNumbers obj;
		String answer;
		obj = new SpiralNumbers();
		long startTime = System.currentTimeMillis();
		answer = obj.getPosition(p0);
		long endTime = System.currentTimeMillis();
		boolean res;
		res = true;
		System.out.println("Time: " + (endTime - startTime) / 1000.0 + " seconds");
		if (hasAnswer) {
			System.out.println("Desired answer:");
			System.out.println("\t" + "\"" + p1 + "\"");
		}
		System.out.println("Your answer:");
		System.out.println("\t" + "\"" + answer + "\"");
		if (hasAnswer) {
			res = answer.equals(p1);
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
		String p1;
		
		// ----- test 0 -----
		p0 = 2;
		p1 = "(0,1)";
		all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 1 -----
		p0 = 3;
		p1 = "(1,1)";
		all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 2 -----
		p0 = 7;
		p1 = "(-1,-1)";
		all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 3 -----
		p0 = 17;
		p1 = "(2,-2)";
		all_right = KawigiEdit_RunTest(3, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 4 -----
		p0 = 24;
		p1 = "(-2,1)";
		all_right = KawigiEdit_RunTest(4, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 5 -----
		p0 = 830;
		p1 = "(-14,3)";
		all_right = KawigiEdit_RunTest(5, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 6 -----
		p0 = 765409;
		p1 = "(-437,221)";
		all_right = KawigiEdit_RunTest(6, p0, true, p1) && all_right;
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
