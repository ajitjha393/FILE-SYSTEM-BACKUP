import javax.swing.*;
import java.awt.*;
import java.awt.Color;
import java.awt.Font;
import java.util.ArrayList;

public class GanttThread extends Thread {

  Color[] col = {new Color(230, 25, 75),new Color(245, 130, 48),new Color(255, 225, 25),new Color(60, 180, 75),
    new Color(0, 130, 200),new Color(0, 130, 200),new Color(145, 30, 180),new Color(70, 240, 240),
    new Color(240, 50, 230),new Color(210, 245, 60),new Color(250, 190, 190),new Color(0, 128, 128),
    new Color(230, 190, 255),new Color(170, 110, 40),new Color(255, 250, 200),new Color(128, 0, 0),
    new Color(170, 255, 195),new Color(128, 128, 0),new Color(0, 0, 128),new Color(128, 128, 128),new Color(255, 215, 180)};

    ArrayList<Integer> arr;
    ArrayList<Integer> t;

    int distance = 15;
    int index = 0;
    int queue;

    public GanttThread(ArrayList<Integer> arr, ArrayList<Integer> t, int queue){
      this.arr = arr;
      this.t = t;
      // timeLabel = new JLabel[t.size()];
      this.queue = queue;
      this.start();
    }

    public void run(){
      for(int x =  0; x < arr.size(); x++){
        try{
          // while(index != t.size()){
          //   timeLabel[index] = new JLabel("" + t.get(index), SwingConstants.CENTER);
          //   MLFQFrame.addComponent(MLFQFrame.timePanel, timeLabel[index], distance*t.get(index),65, 16, 65);
          //   index++;
          // }

          MLFQFrame.processLabel[queue][x] = new JPanel(null);
          MLFQFrame.processLabel[queue][x].setPreferredSize(new Dimension(20, 50));
          JLabel p = new JLabel("P" + arr.get(x), SwingConstants.CENTER);
          p.setBounds(0, 0, 15, 45);
          MLFQFrame.processLabel[queue][x].add(p);
          MLFQFrame.processLabel[queue][x].setFont(new Font("Calibri", Font.PLAIN, 10));
          MLFQFrame.processLabel[queue][x].setBackground(col[arr.get(x)-1]);
          MLFQFrame.processLabel[queue][x].setOpaque(true);
          MLFQFrame.addComponent(MLFQFrame.processPanel, MLFQFrame.processLabel[queue][x], distance, 20, 16, 65);
          Thread.sleep(100);
          distance += 18;
        }catch(Exception e){}
          MLFQFrame.qPanel.add(MLFQFrame.processPanel);//(MLFQFrame.qPanel, MLFQFrame.processPanel, 0, 0, 1000, 70);
        }
        MLFQFrame.qPanel.add(MLFQFrame.timePanel);//(MLFQFrame.qPanel, MLFQFrame.timePanel, 0, 80, 1000, 50);
      }
    }
