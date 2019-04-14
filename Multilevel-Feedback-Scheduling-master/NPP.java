import java.util.*;
import javax.swing.JLabel;

public class NPP {

  public NPP(int[] process, int[] arrivalTime, int[] burstTime, int[] priority, int queue){
		int size = process.length;
    int temp, temp1, min, k = 1, burst = 0, sum = 0, ta = 0;
    float wavg, tavg, tsum = 0, wsum = 0;
    int[] wt = new int[size];
    int[] rt = new int[size];
    int[] tt = new int[size];

    for(int i = 0; i < size; i++){
      for(int j = 0; j < size; j++){
        if(arrivalTime[i] < arrivalTime[j]){/*sorting acc to arrival time*/
          temp = process[j];
          process[j] = process[i];
          process[i] = temp;
          temp = arrivalTime[j];
          arrivalTime[j]= arrivalTime[i];
          arrivalTime[i] = temp;
          temp1 = burstTime[j];
          burstTime[j] = burstTime[i];
          burstTime[i] = temp1;
        }
      }
    }

    for(int j = 0; j < size; j++){
      burst = burst + burstTime[j];
      min=burstTime[k];
      for(int i = k; i < size; i++){ /*main logic*/
        min = priority[k];
        if (burst>=arrivalTime[i]){
          if(priority[i]<min){
            temp = process[k];
            process[k] = process[i];
            process[i] = temp;
            temp = arrivalTime[k];
            arrivalTime[k] = arrivalTime[i];
            arrivalTime[i] = temp;
            temp1 = burstTime[k];
            burstTime[k] = burstTime[i];
            burstTime[i] = temp1;
            temp = priority[k];
            priority[k] = priority[i];
            priority[i] = temp;
          }
        }
      }
      k++;
    }

    for(int i = 0; i < size; i++){
      sum = sum + burstTime[i];
      wt[i] = sum - arrivalTime[i];
    }

    for(int i = 0; i < size; i++){
      wsum = wsum+wt[i];
    }

    wavg = wsum/size;
    for(int i = 0; i < size; i++){
      ta = ta + burstTime[i];
      tt[i] = ta - arrivalTime[i];
    }

    for(int i = 0; i < size; i++){
      tsum = tsum + tt[i];
    }

    tavg=tsum/size;
    for(int i = 0; i < size; i++){
      rt[i] = wt[i];
    }

    System.out.printf("************************");
    System.out.printf("\n RESULT:-\t\t\t VARIOUS TIMES");
    System.out.printf("\nprocess\t burst\t arrival\tpriority " );
    for(int i=0;i<size;i++){
      System.out.printf("\n  p%d",process[i]);
      System.out.printf("\t   %d",burstTime[i]);
      System.out.printf("\t   %d",arrivalTime[i]);
      System.out.printf("\t\t   %d",priority[i]);
    }

    System.out.printf("\nwaiting time\tturnaround time\tresponce time");
    for(int i=0;i<size;i++){
      System.out.printf("\n  %d",wt[i]);
      System.out.printf("\t\t  %d",tt[i]);
      System.out.printf("\t\t%d",rt[i]);
    }

    System.out.printf("\nAVERAGE WAITING TIME:-  %f ms",wavg);
    System.out.printf("\nAVERAGE TURN AROUND TIME:-  %f ms" ,tavg);
    System.out.printf("\nAVERAGE RESPONSE TIME:-  %f ms\n",wavg);
  }
}
