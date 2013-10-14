import java.util.*;
import java.util.regex.*;
import java.text.*;
import java.math.*;


public class JoinedString
{
	boolean isLess(String s1, String s2)
	{
		if (s1.length() < s2.length()) return true;
		if (s1.length() > s2.length()) return false;
		return s1.compareTo(s2) < 0;
	}
	
	public int getCommon(String tail, String head)
	{
		if (tail == null) return 0;
		if (head == null) return 0;
		
		for (int l = Math.min(tail.length(), head.length()); l >= 1; --l)
			if (tail.substring(tail.length() - l).equals(head.substring(0, l))) return l;
		return 0;
	}
	
	int[][] calCommon;
	
	String getAns(int state, int last, String[] words, String[][] ret)
	{
		if (ret[state][last] != null) return ret[state][last];
		
		if (state == 0) return (ret[state][last] = "");
		if (state > 0)
		{
			for (int i = 0; i < words.length; ++i) 
				if ((state & (1 << i)) != 0)
				{
					int common = calCommon[last][i];
					String ns = words[i].substring(common) + getAns(state - (1 << i), i, words, ret);
					if (ret[state][last] == null) ret[state][last] = ns;
					if (isLess(ns, ret[state][last])) ret[state][last] = ns;
				}
		}
		return ret[state][last];
	}
	
	public String joinWords(String[] words)
	{
		Set<String> availWords = new HashSet<String>();
		for (int i = 0; i < words.length; ++i)
		{
			boolean ok = true;
			for (int j = 0; j < words.length; ++j)
				if (j != i && words[i].length() < words[j].length())
					if (words[j].contains(words[i])) 
						ok = false;
			if (ok) availWords.add(words[i]);
		}
		
		words = availWords.toArray(new String[0]);
		int N = words.length;
		
		String[][] ret = new String[1 << N][N + 1];
		calCommon = new int[N + 1][N + 1];
		for (int i = 0; i <= N; ++i)
			for (int j = 0; j <= N; ++j)
				calCommon[i][j] = getCommon(i == N ? null : words[i], j == N ? null : words[j]);
		
		return getAns((1 << N) - 1, N, words, ret);
	}
	
	// BEGIN KAWIGIEDIT TESTING
	// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
	private static boolean KawigiEdit_RunTest(int testNum, String[] p0, boolean hasAnswer, String p1) {
		System.out.print("Test " + testNum + ": [" + "{");
		for (int i = 0; p0.length > i; ++i) {
			if (i > 0) {
				System.out.print(",");
			}
			System.out.print("\"" + p0[i] + "\"");
		}
		System.out.print("}");
		System.out.println("]");
		JoinedString obj;
		String answer;
		obj = new JoinedString();
		long startTime = System.currentTimeMillis();
		answer = obj.joinWords(p0);
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
		
		String[] p0;
		String p1;
		
		// ----- test 0 -----
		p0 = new String[]{"BAB","ABA"};
		p1 = "ABAB";
		all_right = KawigiEdit_RunTest(0, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 1 -----
		p0 = new String[]{"ABABA","AKAKA","AKABAS","ABAKA"};
		p1 = "ABABAKAKABAS";
		all_right = KawigiEdit_RunTest(1, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 2 -----
		p0 = new String[]{"AAA","BBB","CCC","ABC","BCA","CAB"};
		p1 = "AAABBBCABCCC";
		all_right = KawigiEdit_RunTest(2, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 3 -----
		p0 = new String[]{"OFG","SDOFGJTILM","KBWNF","YAAPO","AWX","VSEAWX","DOFGJTIL","YAA"};
		p1 = "KBWNFSDOFGJTILMVSEAWXYAAPO";
		all_right = KawigiEdit_RunTest(3, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 4 -----
		p0 = new String[]{"NVCSKFLNVS","HUFSPMRI","FLNV","KMQD","RPJK","NVSQORP","UFSPMR","AIHUFSPMRI"};
		p1 = "AIHUFSPMRINVCSKFLNVSQORPJKMQD";
		all_right = KawigiEdit_RunTest(4, p0, true, p1) && all_right;
		// ------------------
		
		// ----- test 5 -----
		p0 = new String[]{"STRING","RING"};
		p1 = "STRING";
		all_right = KawigiEdit_RunTest(5, p0, true, p1) && all_right;
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