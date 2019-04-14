import java.util.ArrayList;
import java.util.*;
import javax.swing.JLabel;

public class SJF {
	private int[] processID;
	private int[] arrivalTime;
	private int[] burstTime;
	private int numOfProcesses;
	private ArrayList<Integer> process_ID = new ArrayList<Integer>();
	private ArrayList<Integer> arrival_time = new ArrayList<Integer>();
	float avgwt = 0, avgtt = 0, avgrt = 0;

	public SJF(int[] processID, int[] arrivalTime, int[] burstTime, int queue) {
		this.processID = processID;
		this.arrivalTime = arrivalTime;
		this.burstTime = burstTime;
		numOfProcesses = processID.length;

		getAllInfo();
		MLFQFrame.processLabel = new JLabel[process_ID.size()];
		GanttThread ppt = new GanttThread(process_ID, arrival_time, queue);
	}

	public void getAllInfo() {
		int[] waitingTime = new int[numOfProcesses];
		int[] turnaroundTime = new int[numOfProcesses];
		int[] completionTime = new int[numOfProcesses];
		int[] serviceTime = new int[numOfProcesses];
		int[] responseTime = new int[numOfProcesses];
		int[] flag = new int[numOfProcesses];

		for (int i = 0; i < numOfProcesses; i++) {
			flag[i] = 0;
		}

		int st = 0, tot = 0;

		while (true) {
			int c = numOfProcesses, min = 50;
			if (tot == numOfProcesses)
				break;

			for (int i = 0; i < numOfProcesses; i++) {
				if ((arrivalTime[i] <= st) && (flag[i] == 0) && (burstTime[i] <= min)) {
					min = burstTime[i];
					c = i;
				}
			}

			if (c == numOfProcesses)
				st++;
			else {
				completionTime[c] = st + burstTime[c];
				st += burstTime[c];
				turnaroundTime[c] = completionTime[c] - arrivalTime[c];
				waitingTime[c] = turnaroundTime[c] - burstTime[c];
				avgwt += waitingTime[c]; // total waiting time
				avgtt += turnaroundTime[c];
				flag[c] = 1;
				tot++;
			}
		}

		for (int i = 0; i < numOfProcesses; i++) {
			serviceTime[i] = waitingTime[i] + arrivalTime[i];
			responseTime[i] = serviceTime[i] - arrivalTime[i];
			avgrt += responseTime[i];
		}

		for (int i = 0; i < numOfProcesses; i++) {
			for (int j = 0; j < numOfProcesses - (i + 1); j++) {
				if (serviceTime[j] > serviceTime[j + 1]) {
					sortArray(serviceTime, j);
					sortArray(arrivalTime, j);
					sortArray(burstTime, j);
					sortArray(waitingTime, j);
					sortArray(completionTime, j);
					sortArray(turnaroundTime, j);
					sortArray(processID, j);
				}
			}
		}

		printInfo(completionTime, serviceTime);
	}

	public void printInfo(int[] completionTime, int[] serviceTime) {
		System.out.println("SJF\n");
		System.out.println("\npid  arrival burst");
		for (int i = 0; i < numOfProcesses; i++) {
			System.out.println(processID[i] + "\t" + arrivalTime[i] + "\t" + burstTime[i]);
		}
		System.out.println("\naverage waiting time: " + (avgwt / numOfProcesses));
		System.out.println("average turnaround time:" + (avgtt / numOfProcesses));
		System.out.println("average response time:" + (avgrt / numOfProcesses));
		createGantt(completionTime, serviceTime, processID);
	}

	public void createGantt(int[] completionTime, int[] serviceTime, int[] processID) {
		int ctr = 0;
		System.out.println("\nGANTT CHART\n");

		for (int i = getMinMax(arrivalTime, 0); i <= getMinMax(completionTime, 1); i++) {
			if (serviceTime[ctr] == i) {
				arrival_time.add(i);
			}
			if (serviceTime[ctr] < i) {
				process_ID.add(processID[ctr]);
			}
			if (i == completionTime[ctr]) {
				arrival_time.add(i);
				ctr++;
			}
		}
	}

	public void sortArray(int[] array, int j) {
		int temp;
		temp = array[j];
		array[j] = array[j + 1];
		array[j + 1] = temp;
	}

	public int getMinMax(int[] num, int identifier) {
		Arrays.sort(num);

		if (identifier == 0) {
			return num[0];
		} else {
			return num[num.length - 1];
		}
	}
}
