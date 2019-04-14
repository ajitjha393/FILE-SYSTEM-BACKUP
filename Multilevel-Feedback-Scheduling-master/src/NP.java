import java.util.*;

public class NP {

	public NP(int[] process, int[] arrivalTime, int[] burstTime, int[] priority, int queue) {
		int size = process.length;
		int temp;
		float avgwt = 0, avgtt = 0, avgrt = 0;

		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				if (arrivalTime[i] > arrivalTime[j]) {
					temp = arrivalTime[i];
					arrivalTime[i] = arrivalTime[j];
					arrivalTime[j] = temp;
					temp = priority[i];
					priority[i] = priority[j];
					priority[j] = temp;
					temp = burstTime[i];
					burstTime[i] = burstTime[j];
					burstTime[j] = temp;
					temp = process[i];
					process[i] = process[j];
					process[j] = temp;
				}
			}
		}

		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				if (arrivalTime[i] == arrivalTime[j]) {
					if (priority[i] > priority[j]) {
						temp = arrivalTime[i];
						arrivalTime[i] = arrivalTime[j];
						arrivalTime[j] = temp;
						temp = priority[i];
						priority[i] = priority[j];
						priority[j] = temp;
						temp = burstTime[i];
						burstTime[i] = burstTime[j];
						burstTime[j] = temp;
						temp = process[i];
						process[i] = process[j];
						process[j] = temp;
					}
				}
			}
		}

		for (int i = 1; i < size; i++) {
			for (int j = i + 1; j < size; j++) {

				if (priority[i] > priority[j]) {
					temp = arrivalTime[i];
					arrivalTime[i] = arrivalTime[j];
					arrivalTime[j] = temp;
					temp = priority[i];
					priority[i] = priority[j];
					priority[j] = temp;
					temp = burstTime[i];
					burstTime[i] = burstTime[j];
					burstTime[j] = temp;
					temp = process[i];
					process[i] = process[j];
					process[j] = temp;
				}
			}
		}

		ArrayList<Integer> p = new ArrayList<Integer>();
		ArrayList<Integer> a = new ArrayList<Integer>();
		ArrayList<Integer> b = new ArrayList<Integer>();
		ArrayList<Integer> t = new ArrayList<Integer>();
		ArrayList<Integer> arrival = new ArrayList<Integer>();
		ArrayList<Integer> burst = new ArrayList<Integer>();
		int counter = 0;
		int[] pros = new int[size];

		for (int i = 0; i < size; i++) {
			p.add(process[i]);
			a.add(arrivalTime[i]);
			b.add(burstTime[i]);
			arrival.add(arrivalTime[i]);
			burst.add(burstTime[i]);
		}

		int totalTime = Collections.min(a);
		t.add(totalTime);
		while (!p.isEmpty()) {

			if (totalTime >= a.get(0)) {
				pros[counter] = p.get(0);
				totalTime += b.get(0);
				p.remove(0);
				a.remove(0);
				b.remove(0);
				counter++;
				t.add(totalTime);
			}
		}

		System.out.println();
		System.out.println("\nNP GANTT CHART");

		int[] serviceTime = new int[size];
		int[] completionTime = new int[size];
		int[] turnaroundTime = new int[size];
		int[] waitingTime = new int[size];
		int[] responseTime = new int[size];
		int[] arrivals = new int[size];
		int[] bursts = new int[size];

		for (int i = 0; i < size; i++) {
			System.out.print("\t|  P" + pros[i]);
			arrivals[i] = arrival.get(pros[i] - 1);
			bursts[i] = burst.get(pros[i] - 1);
			serviceTime[i] = t.get(i);
		}

		System.out.print("  |\n");

		for (int i = 0; i < size + 1; i++) {
			System.out.print("\t" + t.get(i));
			if (i != 0) {
				completionTime[i - 1] = t.get(i);
				responseTime[i - 1] = serviceTime[i - 1] - arrivals[i - 1];
				turnaroundTime[i - 1] = completionTime[i - 1] - arrivals[i - 1];
				waitingTime[i - 1] = turnaroundTime[i - 1] - bursts[i - 1];
				avgwt += waitingTime[i - 1];
				avgtt += turnaroundTime[i - 1];
				avgrt += responseTime[i - 1];
			}
		}

		System.out.println("Average waiting time: " + avgwt / size);
		System.out.println("Average turnaround time: " + avgtt / size);
		System.out.println("Average response time: " + avgrt / size);

	}
}
