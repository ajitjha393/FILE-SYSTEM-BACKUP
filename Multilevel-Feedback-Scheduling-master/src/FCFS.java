import java.util.ArrayList;
import java.util.*;
import javax.swing.JLabel;

public class FCFS {
	private int[] processID;
	private int[] arrivalTime;
	private int[] burstTime;
	private int numOfProcesses;
	float avgwt = 0, avgta = 0, avgrt = 0;

	private ArrayList<Integer> process_ID = new ArrayList<Integer>();
	private ArrayList<Integer> arrival_time = new ArrayList<Integer>();

	public FCFS(int[] processID, int[] arrivalTime, int[] burstTime, int queue) {
		this.processID = processID;
		this.arrivalTime = arrivalTime;
		this.burstTime = burstTime;
		numOfProcesses = processID.length;

		getInfo();
		MLFQFrame.processLabel = new JLabel[process_ID.size()];
		GanttThread ppt = new GanttThread(process_ID, arrival_time, queue);
	}

	public void printInfo(int[] completionTime, int[] serviceTime) {
		System.out.println("FCFS\n");
		System.out.println("\npid  arrival  burst");
		for (int i = 0; i < numOfProcesses; i++) {
			System.out.println(processID[i] + "\t " + arrivalTime[i] + "\t" + burstTime[i]);
		}

		System.out.println("\naverage waiting time: " + (avgwt / numOfProcesses));
		System.out.println("average turnaround time:" + (avgta / numOfProcesses));
		System.out.println("average response time:" + (avgrt / numOfProcesses));

		createGantt(completionTime, serviceTime, processID);
	}

	public void getInfo() {
		int[] waitingTime = new int[numOfProcesses];
		int[] turnaroundTime = new int[numOfProcesses];
		int[] completionTime = new int[numOfProcesses];
		int[] serviceTime = new int[numOfProcesses];
		int[] responseTime = new int[numOfProcesses];

		for (int i = 0; i < numOfProcesses; i++) {
			for (int j = 0; j < numOfProcesses - (i + 1); j++) {
				if (arrivalTime[j] > arrivalTime[j + 1]) {
					sortArray(arrivalTime, j);
					sortArray(burstTime, j);
					sortArray(processID, j);
				}
			}
		}

		for (int i = 0; i < numOfProcesses; i++) {
			if (i == 0) {
				completionTime[i] = arrivalTime[i] + burstTime[i];
			} else {
				if (arrivalTime[i] > completionTime[i - 1]) {
					completionTime[i] = arrivalTime[i] + burstTime[i];
				} else
					completionTime[i] = completionTime[i - 1] + burstTime[i];
			}
			turnaroundTime[i] = completionTime[i] - arrivalTime[i];
			waitingTime[i] = turnaroundTime[i] - burstTime[i];
			serviceTime[i] = waitingTime[i] + arrivalTime[i];
			responseTime[i] = serviceTime[i] - arrivalTime[i];
			avgwt += waitingTime[i]; // total waiting time
			avgta += turnaroundTime[i];
			avgrt += responseTime[i];
		}
		printInfo(completionTime, serviceTime);
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
