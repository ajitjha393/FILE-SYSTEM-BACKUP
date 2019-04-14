import java.util.ArrayList;

import javax.swing.JLabel;

public class RR {

	public RR(int[] process, int[] arrivalTime, int[] burstTime, int quantum, int queue) {
		int temp = 0;
		int size = process.length;
		int responseTime[] = new int[size];
		int waitingTime[] = new int[size];
		int turnaroundTime[] = new int[size];

		for (int i = 0; i < size; i++) {
			for (int k = i + 1; k < size; k++) {
				if (arrivalTime[i] > arrivalTime[k]) {
					temp = process[i];
					process[i] = process[k];
					process[k] = temp;
					temp = arrivalTime[i];
					arrivalTime[i] = arrivalTime[k];
					arrivalTime[k] = temp;
					temp = burstTime[i];
					burstTime[i] = burstTime[k];
					burstTime[k] = temp;
				}
			}
		}

		ArrayList<Integer> arr = new ArrayList<Integer>();
		ArrayList<Integer> arr2 = new ArrayList<Integer>();
		ArrayList<Integer> p = new ArrayList<Integer>();
		ArrayList<Integer> t = new ArrayList<Integer>();

		int time = arrivalTime[0];
		int counter = 0;
		int q = 0;
		int te[] = new int[size];

		t.add(time);
		while (!arr.isEmpty()) {

			p.add(arr2.get(0));

			if (arr.get(0) >= q) {
				arr.set(0, arr.get(0) - q);
				time += q;
			} else {
				time += arr.get(0);
				arr.set(0, 0);
			}

			if (arr.get(0) != 0) {
				arr.add(arr.get(0));
				arr.remove(0);
				arr2.add(arr2.get(0));
				arr2.remove(0);
			} else {
				arr.remove(0);
				arr2.remove(0);
			}

			t.add(time);
			counter++;
		}

		for (int i = 0; i < counter; i++) {
			System.out.print("\t| P" + p.get(i));
		}

		System.out.print(" |\n");

		for (int i = 0; i < counter + 1; i++) {
			System.out.print("\t" + t.get(i));
		}

		MLFQFrame.processLabel = new JLabel[size];
		GanttThread ppt = new GanttThread(p, t, queue);
	}
}
