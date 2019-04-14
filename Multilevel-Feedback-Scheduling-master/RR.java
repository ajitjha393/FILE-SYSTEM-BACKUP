import java.util.ArrayList;
import java.util.Scanner;
import javax.swing.JLabel;

public class RR {
  ArrayList<Integer> p = new ArrayList<Integer>();
  ArrayList<Integer> t = new ArrayList<Integer>();

  public RR(int[] process, int[] arrivalTime, int[] burstTime,  int[] priority, int quantum, int queue){
    int size = process.length;
    int lastArrival;
    int nextQueue = queue;

		if(queue != MLFQFrame.numOfQueues - 1){
			nextQueue++;
		}else{
			nextQueue = 0;
		}
    int[] wt = new int[size];
    int[] te = new int[size];
    int[] rt = new int[size];
    int[] turnaroundTime = new int[size];
    int[] responseTime = new int[size];
    int[] serviceTime = new int[size];
    int[] completionTime = new int[size];

    float awt = 0, att = 0, art = 0;

    int temp = 0;

    for (int i = 0; i < size; i++){
      for (int j = i + 1; j < size; j++){
        if(arrivalTime[i] > arrivalTime[j]){
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

    for(int i = 0; i < size; i++){
      rt[i] = burstTime[i];
      wt[i] = 0;
      te[i] = 0;
    }
    int j = 0, q = arrivalTime[0], counter = 0, loopCounter = 0;

    loop:
    while(j <= size){
      j++;
      for(int i = 0; i < size; i++){
        if(rt[i] == 0)
          continue;

        if(rt[i] > quantum){
          if(loopCounter == 0){
            serviceTime[i] = q;
          }
          counter = q;
          MLFQFrame.arrival_time.add(q);
          q = q + quantum;
          for(int k = counter; k < q; k++){
            MLFQFrame.process_ID.add(process[i]);
          }
          rt[i] = rt[i] - quantum;
          completionTime[i] = q;
          te[i] = te[i] + 1;
        }else{
          if(loopCounter == 0){
            serviceTime[i] = q;
          }
          counter = q;
          MLFQFrame.arrival_time.add(q);
          q = q + rt[i];
          for(int k = counter; k < q; k++){
            MLFQFrame.process_ID.add(process[i]);
          }
          rt[i] = rt[i] - rt[i];
          completionTime[i] = q;
        }

        if(i == size-1 && MLFQFrame.numOfQueues != 1){
          break loop;
        }
      }
      loopCounter++;
    }

    MLFQFrame.arrival_time.add(q);
    lastArrival = q;
    for(int i = 0; i < size; i++){
      turnaroundTime[i] = completionTime[i] - arrivalTime[i];
      wt[i] = Math.abs(turnaroundTime[i] - burstTime[i]);
      responseTime[i] = serviceTime[i] - arrivalTime[i];
      awt = awt + wt[i];
      att = att + turnaroundTime[i];
      art = art + responseTime[i];
    }
    MLFQFrame.avgwt += awt;
    MLFQFrame.avgta += att;
    MLFQFrame.avgrt += art;

    if(MLFQFrame.numOfQueues == 1){
      MLFQFrame.isTrue = false;
      return;
    }else{
      try{
  			int count = 0, temporary = 0;
  			for(int i = 0; i < process.length; i++){
  				if(rt[i] != 0){
  					count++;
  				}
  			}

  			if(count == 0){
  				MLFQFrame.isTrue = false;
  				return;
  			}

  			MLFQFrame.processID[nextQueue] = new int[count];
  			MLFQFrame.burstTime[nextQueue] = new int[count];
  			MLFQFrame.arrivalTime[nextQueue] = new int[count];
  			MLFQFrame.priority[nextQueue] = new int[count];

  			for(int k = 0; k < process.length; k++){
  				if(rt[k] != 0){
  					MLFQFrame.processID[nextQueue][temporary] = process[k];
  					MLFQFrame.arrivalTime[nextQueue][temporary] = lastArrival;
  					MLFQFrame.burstTime[nextQueue][temporary] = rt[k];
  					MLFQFrame.priority[nextQueue][temporary] = priority[k];
  					temporary++;
  				}
  			}
  		}catch(ArrayIndexOutOfBoundsException e){ return;}
    }
  }
}
