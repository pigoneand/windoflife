import java.util.*;
import java.util.regex.*;
import java.text.*;
import java.math.*;


public class Segments
{
	public String intersection(int[] s1, int[] s2)
	{
		int x1 = Math.max(Math.min(s1[0], s1[2]), Math.min(s2[0], s2[2]));
		int x2 = Math.min(Math.max(s1[0], s1[2]), Math.max(s2[0], s2[2]));
		int y1 = Math.max(Math.min(s1[1], s1[3]), Math.min(s2[1], s2[3]));
		int y2 = Math.min(Math.max(s1[1], s1[3]), Math.max(s2[1], s2[3]));
		if (x1 > x2 || y1 > y2) return "NO";
		if (x1 == x2 && y1 == y2) return "POINT";
		return "SEGMENT";
	}
	
	// BEGIN KAWIGIEDIT TESTING
	// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
	private static boolean KawigiEdit_RunTest(int testNum, int[] p0, int[] p1, boolean hasAnswer, String p2) {
		System.out.print("Test " + testNum + ": [" + "{");
		for (int i = 0; p0.length > i; ++i) {
			if (i > 0) {
				System.out.print(",");
			}
			System.out.print(p0[i]);
		}
		System.out.print("}" + "," + "{");
		for (int i = 0; p1.length > i; ++i) {
			if (i > 0) {
				System.out.print(",");
			}
			System.out.print(p1[i]);
		}
		System.out.print("}");
		System.out.println("]");
		Segments obj;
		String answer;
		obj = new Segments();
		long startTime = System.currentTimeMillis();
		answer = obj.intersection(p0, p1);
		long endTime = System.currentTimeMillis();
		boolean res;
		res = true;
		System.out.println("Time: " + (endTime - startTime) / 1000.0 + " seconds");
		if (hasAnswer) {
			System.out.println("Desired answer:");
			System.out.println("\t" + "\"" + p2 + "\"");
		}
		System.out.println("Your answer:");
		System.out.println("\t" + "\"" + answer + "\"");
		if (hasAnswer) {
			res = answer.equals(p2);
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
		
		int[] p0;
		int[] p1;
		String p2;
		
		// ----- test 0 -----
		p0 = new int[]{0,0,0,1};
		p1 = new int[]{1,0,1,1};
		p2 = "NO";
		all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
		// ------------------
		
		// ----- test 1 -----
		p0 = new int[]{0,0,0,1};
		p1 = new int[]{0,1,0,2};
		p2 = "POINT";
		all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
		// ------------------
		
		// ----- test 2 -----
		p0 = new int[]{0,-1,0,1};
		p1 = new int[]{-1,0,1,0};
		p2 = "POINT";
		all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
		// ------------------
		
		// ----- test 3 -----
		p0 = new int[]{0,0,2,0};
		p1 = new int[]{1,0,10,0};
		p2 = "SEGMENT";
		all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
		// ------------------
		
		// ----- test 4 -----
		p0 = new int[]{5,5,5,5};
		p1 = new int[]{6,6,6,6};
		p2 = "NO";
		all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
		// ------------------
		
		// ----- test 5 -----
		p0 = new int[]{10,0,-10,0};
		p1 = new int[]{5,0,-5,0};
		p2 = "SEGMENT";
		all_right = KawigiEdit_RunTest(5, p0, p1, true, p2) && all_right;
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
