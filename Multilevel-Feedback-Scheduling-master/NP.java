import java.util.ArrayList;
import java.util.*;
import java.awt.*;
import javax.swing.*;
import javax.swing.JLabel;

public class NP {
	private int[] processID;
	private int[] arrivalTime;
	private int[] burstTime;
	private int[] burstTemp;
  private int[] priority;
	private int queue, lastArrival;
	private int nextQueue;
	private int quantum = -1;
	private int numOfProcesses;
	private ArrayList<Integer> process_ID = new ArrayList<Integer>();
	private ArrayList<Integer> arrival_time = new ArrayList<Integer>();
	float avgwt = 0, avgta = 0, avgrt = 0;

	public NP(int[] processID, int[] arrivalTime, int[] burstTime, int[] priority, int queue) {
		this.processID = processID;
		this.arrivalTime = arrivalTime;
		this.burstTime = burstTime;
    this.priority = priority;
		this.queue = queue;
		burstTemp = burstTime;
		numOfProcesses = processID.length;

		getAllInfo();
		MLFQFrame.processLabel[queue] = new JPanel[process_ID.size()];
		GanttThread ppt = new GanttThread(process_ID, arrival_time, queue);
	}

	public NP(int[] processID, int[] arrivalTime, int[] burstTime, int[] priority, int queue, int quantum) {
		this.processID = processID;
		this.arrivalTime = arrivalTime;
		this.burstTime = burstTime;
    this.priority = priority;
		this.queue = queue;
		this.quantum = quantum;
		burstTemp = burstTime;
		nextQueue = queue;
		if(queue != MLFQFrame.numOfQueues - 1){
			nextQueue++;
		}else{
			nextQueue = 0;
		}
		numOfProcesses = processID.length;

		getAllInfo();
		MLFQFrame.processLabel[queue] = new JPanel[process_ID.size()];
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
				if ((arrivalTime[i] <= st) && (flag[i] == 0) && (priority[i] <= min)) {
					min = priority[i];
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
				avgta += turnaroundTime[c];
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
          sortArray(priority, j);
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
		MLFQFrame.avgwt += avgwt;
    MLFQFrame.avgta += avgta;
    MLFQFrame.avgrt += avgrt;

		createGantt(completionTime, serviceTime, processID);
	}

	public void createGantt(int[] completionTime, int[] serviceTime, int[] processID) {
		int ctr = 0, quantumCtr = 0;

		for (int i = getMinMax(arrivalTime, 0); i <= getMinMax(completionTime, 1); i++) {
			if (serviceTime[ctr] == i) {
				if(queue == 0)
					MLFQFrame.arrival_time.add(i);
			}
			if (serviceTime[ctr] < i) {
				MLFQFrame.process_ID.add(processID[ctr]);
				burstTemp[ctr]--;
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
				if(burstTemp[i] != 0){
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

			for(int j = 0; j < processID.length; j++){
				if(burstTemp[j] != 0){
					MLFQFrame.processID[nextQueue][temporary] = processID[j];
					MLFQFrame.arrivalTime[nextQueue][temporary] = lastArrival;
					MLFQFrame.burstTime[nextQueue][temporary] = burstTime[j];
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
