import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.UIManager.LookAndFeelInfo;

public class Main{
  public static void main(String[] args){
	  
    try {
      for (LookAndFeelInfo info : UIManager.getInstalledLookAndFeels()) {
        if ("Nimbus".equals(info.getName())) {
          UIManager.setLookAndFeel(info.getClassName());
          break;
        }
      }
    } catch (Exception e) {}

    MLFQFrame mlfqFrame = new MLFQFrame();
    mlfqFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    mlfqFrame.setExtendedState(JFrame.MAXIMIZED_BOTH);
    mlfqFrame.setUndecorated(true);
    mlfqFrame.setVisible(true);
    mlfqFrame.setLocationRelativeTo(null);
  }
}
