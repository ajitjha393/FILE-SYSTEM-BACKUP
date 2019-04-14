import java.util.ArrayList;
import java.util.Scanner;
import java.util.Collections;
import javax.swing.JLabel;
import java.awt.Color;
import javax.swing.SwingConstants;
import javax.swing.JFrame;

public class PP {
	static ArrayList<Integer> p2 = new ArrayList();

	public PP(int[] process, int[] arrivalTime, int[] burstTime, int[] priority, int queue) {
		int temp = 0;
		int size = process.length;
		float avgwt = 0, avgtt = 0, avgrt = 0;

		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				if (arrivalTime[i] > arrivalTime[j]) {
					temp = process[i];
					process[i] = process[j];
					process[j] = temp;
					temp = arrivalTime[i];
					arrivalTime[i] = arrivalTime[j];
					arrivalTime[j] = temp;
					temp = burstTime[i];
					burstTime[i] = burstTime[j];
					burstTime[j] = temp;
					temp = priority[i];
					priority[i] = priority[j];
					priority[j] = temp;
				}
			}
		}

		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				if (priority[i] > priority[j]) {
					temp = process[i];
					process[i] = process[j];
					process[j] = temp;
					temp = arrivalTime[i];
					arrivalTime[i] = arrivalTime[j];
					arrivalTime[j] = temp;
					temp = burstTime[i];
					burstTime[i] = burstTime[j];
					burstTime[j] = temp;
					temp = priority[i];
					priority[i] = priority[j];
					priority[j] = temp;
				}
			}
		}

		ArrayList<Integer> p = new ArrayList<Integer>();
		ArrayList<Integer> a = new ArrayList<Integer>();
		ArrayList<Integer> b = new ArrayList<Integer>();
		ArrayList<Integer> pr = new ArrayList<Integer>();
		ArrayList<Integer> arrival = new ArrayList<Integer>();
		ArrayList<Integer> burst = new ArrayList<Integer>();

		for (int i = 0; i < size; i++) {
			// System.out.println("P" + process[i] + "\t\t" + arrivalTime[i] +
			// "\t\t" + burstTime[i] + "\t\t" + priority[i]);
			p.add(process[i]);
			a.add(arrivalTime[i]);
			b.add(burstTime[i]);
			pr.add(priority[i]);
		}

		int counter = 0;
		System.out.println("\nPP GANTT CHART");
		ArrayList<Integer> t = new ArrayList<Integer>();
		t.add(Collections.min(a));
		int current = t.get(0);

		for (int i = 0; i < size; i++) {
			if (a.get(i) == 0) {
				while (counter != a.get(0)) {
					b.set(i, b.get(i) - 1);
					counter++;
					p2.add(p.get(i));

				}
				current += counter;
				t.add(current);

			}
		}

		int time = Collections.min(a);
		while (!p.isEmpty()) {
			time = 0;
			while (b.get(0) != 0) {
				b.set(0, b.get(0) - 1);
				time += 1;
				System.out.print("P" + p.get(0));
				p2.add(p.get(0));

			}
			current += time;
			t.add(current);

			if (b.get(0) == 0) {
				b.remove(0);
				p.remove(0);
			}
		}

		System.out.print("   |\n");
		//
		// MLFQFrame.processLabel = new JLabel[p2.size()];
		// for(int i = 0; i < t.size(); i++){
		// System.out.print("\t" + t.get(i));
		// }

		// GanttThread ppt = new GanttThread(p2, t, queue);
	}
}
