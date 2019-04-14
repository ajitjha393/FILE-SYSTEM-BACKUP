import java.util.ArrayList;
import java.util.*;
import java.awt.*;
import javax.swing.*;
import javax.swing.JLabel;

public class FCFS {
	private int[] processID;
	private int[] arrivalTime;
	private int[] burstTime;
	private int[] priority;
	private int queue, lastArrival;
	private int quantum = -1;
	private int numOfProcesses;
	private int nextQueue;
	float avgwt = 0, avgta = 0, avgrt = 0;

	private ArrayList<Integer> process_ID = new ArrayList<Integer>();
	private ArrayList<Integer> arrival_time = new ArrayList<Integer>();

	public FCFS(int[] processID, int[] arrivalTime, int[] burstTime, int[] priority, int queue) {
		this.processID = processID;
		this.arrivalTime = arrivalTime;
		this.burstTime = burstTime;
		this.priority = priority;
		numOfProcesses = processID.length;

		getInfo();
		MLFQFrame.processLabel[queue] = new JPanel[process_ID.size()];
	}

	public FCFS(int[] processID, int[] arrivalTime, int[] burstTime, int[] priority, int queue, int quantum) {
		this.processID = processID;
		this.arrivalTime = arrivalTime;
		this.burstTime = burstTime;
		this.priority = priority;
		this.quantum = quantum;
		this.queue = queue;
		nextQueue = queue;
		numOfProcesses = processID.length;
		if(queue != (MLFQFrame.numOfQueues-1)){
			nextQueue++;
		}else{
			nextQueue = 0;
		}

		getInfo();
	}

	public void printInfo(int[] completionTime, int[] serviceTime) {
		// System.out.println("FCFS\n");
		// System.out.println("\npid  arrival  burst");
		// for (int i = 0; i < numOfProcesses; i++) {
		// 	System.out.println(processID[i] + "\t " + arrivalTime[i] + "\t" + burstTime[i]);
		// }
    MLFQFrame.avgwt += avgwt;
    MLFQFrame.avgta += avgta;
    MLFQFrame.avgrt += avgrt;

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
					sortArray(priority, j);
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
			avgwt += waitingTime[i];
			avgta += turnaroundTime[i];
			avgrt += responseTime[i];
		}
		printInfo(completionTime, serviceTime);
	}

	public void createGantt(int[] completionTime, int[] serviceTime, int[] processID) {
		int ctr = 0, quantumCtr = 1;
		for (int i = getMinMax(arrivalTime, 0); i <= getMinMax(completionTime, 1); i++) {
			if (serviceTime[ctr] == i) {
				if(queue == 0)
					MLFQFrame.arrival_time.add(i);
			}
			if (serviceTime[ctr] < i) {
				MLFQFrame.process_ID.add(processID[ctr]);
				burstTime[ctr]--;
			}
			if (i == completionTime[ctr]) {
				MLFQFrame.arrival_time.add(i);
				ctr++;
			}
			if(quantum > 0){
				if(quantumCtr == quantum){
          MLFQFrame.arrival_time.add(i);
					lastArrival = i;
					break;
				}
				quantumCtr++;
			}
		}

		try{
			int counter = 0, temporary = 0;
			for(int i = 0; i < processID.length; i++){
				if(burstTime[i] != 0){
					counter++;
				}
			}

			if(counter == 0){
				MLFQFrame.isTrue = false;
				return;
			}

			MLFQFrame.processID[nextQueue] = new int[counter];
			MLFQFrame.burstTime[nextQueue] = new int[counter];
			MLFQFrame.arrivalTime[nextQueue] = new int[counter];
			MLFQFrame.priority[nextQueue] = new int[counter];

			for(int j = 0; j < processID.length; j++){
				if(burstTime[j] != 0){
					MLFQFrame.processID[nextQueue][temporary] = processID[j];
					MLFQFrame.arrivalTime[nextQueue][temporary] = lastArrival;
					MLFQFrame.burstTime[nextQueue][temporary] = burstTime[j];
					MLFQFrame.priority[nextQueue][temporary] = priority[j];
					temporary++;
				}
			}
		}catch(ArrayIndexOutOfBoundsException e){ return;}

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
