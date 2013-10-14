import java.util.HashMap;
import java.util.Scanner;

public class Test1971 {

	static class Option {
		public String name;
		public int factor;
	}

	static class PerformanceCal {
		private int [] factorCnt = new int[101];
		private HashMap<String, Option> options = new HashMap<String, Option>();
		private long speed;
		private long resolution;

		PerformanceCal() {
			for (int i = 1; i <= 100; ++i) {
				factorCnt[i] = 0;
			}
		}

		public void addOption(Option op) {
			options.put(op.name, op);
			factorCnt[op.factor]++;
		}

		public void execCmd(String cmd, String optionName) {
			int factor = options.get(optionName).factor;
			if (cmd.equals("On")) {
				factorCnt[factor]++;
			} else {
				factorCnt[factor]--;
			}
		}

		public void setSpeed(long s) { 
			speed = s;
		}

		public void setResolution(long width, long height) {
			resolution = width * height;
		}

		public long getCurCPUCycle() {
			long result = resolution;
			for (int i = 2; i <= 100; ++i) {
				for (int j = 0; j < factorCnt[i]; ++j) {
					result = result * ((long) i);
					if (result >= speed) return result;
				}
			}
			return result;
		}

		public String getPerformance() {
			long cpu = getCurCPUCycle();
			if (cpu * 60 <= speed) {
				return "Perfect";
			} else if (cpu * 10 > speed) { 
				return "Slideshow";
			} else {
				return "So-so";
			}
		}
	}
	
	public static void main(String [] args) {
		
		PerformanceCal pc = new PerformanceCal();
		Scanner scan = new Scanner(System.in);
		int N = scan.nextInt();

		for (int i = 0; i < N; ++i) {
			Option op = new Option();
			op.name = scan.next();
			op.factor = scan.nextInt();
			pc.addOption(op);
		}

		pc.setResolution(scan.nextLong(), scan.nextLong());
		pc.setSpeed(scan.nextLong());

		System.out.println(pc.getPerformance());
		int M = scan.nextInt();
		for (int i = 0; i < M; ++i) {
			String cmd = scan.next();
			if (cmd.equals("On") || cmd.equals("Off")) {
				pc.execCmd(cmd, scan.next());
			} else {
				pc.setResolution(scan.nextLong(), scan.nextLong());
			}
			System.out.println(pc.getPerformance());
		}
	}
}