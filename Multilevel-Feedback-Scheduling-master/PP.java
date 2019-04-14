import java.util.ArrayList;
import javax.swing.JLabel;
import javax.swing.*;
import java.awt.*;
import java.util.*;

public class PP {
	private int[] arrivalTime;
	private int[] processID;
	private int[] burstTime;
	private int[] priority;
	private int queue, quantum = -1;
	private int nextQueue, lastArrival;
	private int numOfProcesses;
	private ArrayList<Integer> process_ID = new ArrayList<Integer>();
	private ArrayList<Integer> arrival_time = new ArrayList<Integer>();
	float avgwt = 0, avgta = 0, avgrt = 0;

	public PP(int[] processID, int[] arrivalTime, int[] burstTime, int[] priority, int queue) {
		this.processID = processID;
		this.arrivalTime = arrivalTime;
		this.burstTime = burstTime;
		this.priority = priority;
		this.queue = queue;
		numOfProcesses = processID.length;
		printInfo();
	}

	public PP(int[] processID, int[] arrivalTime, int[] burstTime, int[] priority, int queue, int quantum) {
		this.processID = processID;
		this.arrivalTime = arrivalTime;
		this.burstTime = burstTime;
		this.priority = priority;
		this.queue = queue;
		this.quantum = quantum;
		nextQueue = queue;
		if(queue != MLFQFrame.numOfQueues - 1){
			nextQueue++;
		}else{
			nextQueue = 0;
		}
		numOfProcesses = processID.length;
		printInfo();
	}

	public void printInfo(){
		int[] completionTime = new int[numOfProcesses];
		int[] waitingTime = new int[numOfProcesses];
		int[] turnaroundTime = new int[numOfProcesses];
		int[] responseTime = new int[numOfProcesses];
		int[] serviceTime = new int[numOfProcesses];
		int[] fullBurst = burstTime.clone();
		int[] flag = new int[numOfProcesses];

		for (int i = 0; i < numOfProcesses; i++) {
			flag[i] = 0;
		}
		int st = 0, tot = 0;
		ArrayList<Integer> list = new ArrayList<Integer>();

		int temp = 0, quantumCtr = 1;

		while (true) {
			int min = 50, c = numOfProcesses;
			if (tot == numOfProcesses) {
				MLFQFrame.arrival_time.add(st);
				break;
			}

			for (int i = 0; i < numOfProcesses; i++) {
				if ((arrivalTime[i] <= st) && (flag[i] == 0) && (priority[i] <= min)) {
					min = priority[i];
					c = i;
				}
			}

			if (c == numOfProcesses) {
				st++;
			}else{
				MLFQFrame.process_ID.add(processID[c]);
				burstTime[c]--;

				if(quantum > 0){
					if(quantumCtr == quantum){
						MLFQFrame.arrival_time.add(st);
						lastArrival = st;
						break;
					}
					quantumCtr++;
				}
				if (!list.contains(processID[c])) {
					if (list.isEmpty()) {
						list.add(processID[c]);
					} else {
						temp = list.get(0);
						list.remove(0);
						list.add(processID[c]);
					}
					MLFQFrame.arrival_time.add(st);
				}
				st++;

				if (burstTime[c] == 0) {
					completionTime[c] = st;
					turnaroundTime[c] = completionTime[c] - arrivalTime[c];
					waitingTime[c] = turnaroundTime[c] - fullBurst[c];
					serviceTime[c] = waitingTime[c] + arrivalTime[c];
					responseTime[c] = serviceTime[c] - arrivalTime[c];
					avgwt += waitingTime[c];
					avgta += turnaroundTime[c];
					avgrt += responseTime[c];
					flag[c] = 1;
					tot++;
				}
			}
		}

		MLFQFrame.avgwt += avgwt;
    MLFQFrame.avgta += avgta;
    MLFQFrame.avgrt += avgrt;

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

			for(int j = 0; j < processID.length; j++){
				if(burstTime[j] != 0){
					MLFQFrame.processID[nextQueue][temporary] = processID[j];
					MLFQFrame.arrivalTime[nextQueue][temporary] = lastArrival;
					MLFQFrame.burstTime[nextQueue][temporary] = burstTime[j];
					temporary++;
				}
			}
		}catch(ArrayIndexOutOfBoundsException e){ return;}

		MLFQFrame.processLabel[queue] = new JPanel[process_ID.size()];
		GanttThread ppt = new GanttThread(process_ID, arrival_time, queue);
	}
}
