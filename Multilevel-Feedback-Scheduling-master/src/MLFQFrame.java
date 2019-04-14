import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Color;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JTextField;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.util.ArrayList;
import java.util.Random;
import java.awt.event.ActionEvent;
import javax.swing.SwingConstants;
import java.awt.GridLayout;
import javax.swing.JScrollPane;
import javax.swing.ScrollPaneConstants;

public class MLFQFrame extends JFrame implements ActionListener {
	private MLFQ mlfq;

	private JPanel mainPanel = new JPanel(null);
	private JPanel tablePanel = new JPanel();
	static JPanel ganttPanel = new JPanel(null);
	private JPanel algoPanel = new JPanel(null);
	private JPanel infoPanel = new JPanel(null);

	JButton startButton = new JButton("START");
	JButton stopButton = new JButton("STOP");
	JButton exitButton = new JButton("EXIT");

	JLabel q1Label1 = new JLabel("Q1", SwingConstants.CENTER);
	JLabel q2Label1 = new JLabel("Q2", SwingConstants.CENTER);
	JLabel q3Label1 = new JLabel("Q3", SwingConstants.CENTER);

	static JPanel qPanel[] = new JPanel[3];
	static JScrollPane pane[] = new JScrollPane[3];
	private JTextField quanTextField[] = new JTextField[3];

	private String[] rowLabelString = { "ID", "ARRIVAL", "BURST", "PRIORITY" };
	private String[] colLabelString = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15",
			"16", "17", "18", "19", "20" };

	int tableRow = 21;
	int tableColumn = 4;

	JTextField[][] panelHolder = new JTextField[tableRow][tableColumn];
	JLabel[][] label = new JLabel[tableRow][tableColumn];

	String[] algorithmString = { "", "(FCFS) First Come First Serve", "(SJF) Shortest Job First",
			"(SRTF) Shortest Remaining Time First", "(NPP) Non-preemptive Priority", "(PP) Preemptive Priority",
			"(RR) Round Robin" };

	JComboBox algorithmDropbox[] = new JComboBox[3];

	private String[][] processes = new String[1][4];
	private String[][] queues = new String[1][3];
	public int[][] queueTypes;
	public PCB[] pcb;
	private boolean queueBool[] = new boolean[1];

	public ArrayList<Color> pcb_colors = new ArrayList<Color>();
	static int numOfProcesses = 0, numOfQueues = 0;

	static JLabel[] processLabel;
	public static JLabel[][] processesLabel;

	public MLFQFrame() {
		add(mainPanel);
		mainPanel.setBackground(new Color(220, 220, 220));
		createTable();
		createGantt();
		createAlgo();
		createInfo();
	}

	public void createTable() {
		tablePanel.setBounds(20, 20, 370, 720);
		mainPanel.add(tablePanel);
		tablePanel.setLayout(new GridLayout(tableRow, tableColumn, 3, 3));
		int rowCtr = 0;
		int columnCtr = 0;

		for (int m = 0; m < tableRow; m++) {
			for (int n = 0; n < tableColumn; n++) {
				if (m == 0) {
					label[m][n] = new JLabel(rowLabelString[rowCtr], SwingConstants.CENTER);
					label[m][n].setOpaque(true);
					label[m][n].setBackground(new Color(180, 180, 180));
					tablePanel.add(label[m][n]);
					rowCtr++;
				} else if (n == 0) {
					label[m][n] = new JLabel(colLabelString[columnCtr], SwingConstants.CENTER);
					label[m][n].setOpaque(true);
					label[m][n].setBackground(new Color(180, 180, 180));
					tablePanel.add(label[m][n]);
					columnCtr++;
				} else {
					panelHolder[m][n] = new JTextField();
					tablePanel.add(panelHolder[m][n]);
				}
			}
		}
	}

	public void createGantt() {
		ganttPanel.setBounds(400, 20, 940, 390);
		ganttPanel.setBackground(new Color(200, 200, 200));
		mainPanel.add(ganttPanel);

		for (int i = 0; i < algorithmDropbox.length; i++) {
			int ctr = i;
			algorithmDropbox[i] = new JComboBox(algorithmString);
			quanTextField[i] = new JTextField();
			quanTextField[i].setText("Quantum");

			quanTextField[i].addFocusListener(new FocusListener() {
				private boolean showingPlaceholder = true;
				int i = ctr;

				public void focusGained(FocusEvent e) {
					if (showingPlaceholder) {
						showingPlaceholder = false;
						quanTextField[i].setText("");
					}
				}

				public void focusLost(FocusEvent arg0) {
					if (quanTextField[i].getText().isEmpty()) {
						quanTextField[i].setText("Quantum");
						showingPlaceholder = true;
					}
				}
			});

			qPanel[i] = new JPanel();
		}

		JLabel q1Label = new JLabel("Q1", SwingConstants.CENTER);
		JLabel q2Label = new JLabel("Q2", SwingConstants.CENTER);
		JLabel q3Label = new JLabel("Q3", SwingConstants.CENTER);

		ganttPanel.add(q1Label);
		q1Label.setOpaque(true);
		q1Label.setBackground(new Color(90, 90, 90));
		q1Label.setBounds(0, 0, 30, 128);

		ganttPanel.add(q2Label);
		q2Label.setOpaque(true);
		q2Label.setBackground(new Color(90, 90, 90));
		q2Label.setBounds(0, 130, 30, 128);

		ganttPanel.add(q3Label);
		q3Label.setOpaque(true);
		q3Label.setBackground(new Color(90, 90, 90));
		q3Label.setBounds(0, 260, 30, 128);

		qPanel[0].setBackground(Color.DARK_GRAY);
		qPanel[0].setBounds(30, 0, 2000, 128);
		qPanel[0].setOpaque(true);
		ganttPanel.add(qPanel[0]);

		qPanel[1].setBackground(Color.DARK_GRAY);
		qPanel[1].setBounds(30, 130, 2000, 128);
		qPanel[1].setOpaque(true);
		ganttPanel.add(qPanel[1]);

		qPanel[2].setBackground(Color.DARK_GRAY);
		qPanel[2].setBounds(30, 260, 2000, 128);
		qPanel[2].setOpaque(true);
		ganttPanel.add(qPanel[2]);

		pane[0] = new JScrollPane(qPanel[0]);
		pane[0].setOpaque(true);
		ganttPanel.add(pane[0]);

		pane[1] = new JScrollPane(qPanel[1]);
		pane[1].setOpaque(true);
		ganttPanel.add(pane[1]);

		pane[2] = new JScrollPane(qPanel[2]);
		pane[2].setOpaque(true);
		ganttPanel.add(pane[2]);
	}

	public void createAlgo() {
		algoPanel.setBounds(400, 423, 405, 310);
		algoPanel.setBackground(new Color(200, 200, 200));
		mainPanel.add(algoPanel);

		q1Label1.setBounds(0, 0, 405, 25);
		q1Label1.setOpaque(true);
		q1Label1.setBackground(new Color(90, 90, 90));
		algoPanel.add(q1Label1);

		algoPanel.add(algorithmDropbox[0]);
		algorithmDropbox[0].setBounds(10, 30, 200, 25);

		algoPanel.add(quanTextField[0]);
		quanTextField[0].setBounds(300, 30, 100, 25);

		q2Label1.setBounds(0, 80, 405, 25);
		q2Label1.setOpaque(true);
		q2Label1.setBackground(new Color(90, 90, 90));
		algoPanel.add(q2Label1);

		algoPanel.add(algorithmDropbox[1]);
		algorithmDropbox[1].setBounds(10, 110, 200, 25);

		algoPanel.add(quanTextField[1]);
		quanTextField[1].setBounds(300, 110, 100, 25);

		q3Label1.setBounds(0, 160, 405, 25);
		q3Label1.setOpaque(true);
		q3Label1.setBackground(new Color(90, 90, 90));
		algoPanel.add(q3Label1);

		algoPanel.add(algorithmDropbox[2]);
		algorithmDropbox[2].setBounds(10, 190, 200, 25);

		algoPanel.add(quanTextField[2]);
		quanTextField[2].setBounds(300, 190, 100, 25);

		algoPanel.add(startButton);
		startButton.setBounds(10, 250, 120, 50);

		algoPanel.add(stopButton);
		stopButton.setBounds(140, 250, 120, 50);

		algoPanel.add(exitButton);
		exitButton.setBounds(270, 250, 120, 50);

		startButton.addActionListener(this);
		exitButton.addActionListener(this);
		stopButton.addActionListener(this);
	}

	public void createInfo() {
		infoPanel.setBounds(815, 423, 523, 310);
		infoPanel.setBackground(Color.DARK_GRAY);
		mainPanel.add(infoPanel);
	}

	public Color addColor() {
		Random randomizer = new Random();
		int R = randomizer.nextInt(256);
		int G = randomizer.nextInt(256);
		int B = randomizer.nextInt(256);

		return (new Color(R, G, B));
	}

	public void addProcesses(String[] processControl, Color color) {
		if (numOfProcesses == 0) {
			for (int x = 0; x < processControl.length; x++) {
				processes[numOfProcesses][x] = processControl[x];
			}
		} else {
			String[][] temp = processes;
			processes = new String[numOfProcesses + 1][4];
			for (int x = 0; x < temp.length; x++) {
				for (int y = 0; y < 4; y++) {
					processes[x][y] = temp[x][y];
				}
			}
			processes[numOfProcesses] = processControl;
		}
		numOfProcesses++;
		pcb_colors.add(color);
	}

	public void loadProcesses() {
		pcb = new PCB[numOfProcesses];

		for (int x = 0; x < numOfProcesses; x++) {
			pcb[x] = new PCB(processes[x][0], Integer.parseInt(processes[x][1]), Integer.parseInt(processes[x][2]),
					Integer.parseInt(processes[x][2]), Integer.parseInt(processes[x][3]), pcb_colors.get(x));
		}
		mlfq.loadProcesses(pcb);
	}

	public void addQueues(String[] qcb, boolean isPreemptive) {
		if (numOfQueues == 0) {
			queueBool[numOfQueues] = isPreemptive;
			for (int x = 0; x < qcb.length; x++) {
				queues[numOfQueues][x] = qcb[x];
			}
		} else {
			boolean[] booltmp = queueBool;
			queueBool = new boolean[numOfQueues + 1];
			for (int a = 0; a < booltmp.length; a++) {
				queueBool[a] = booltmp[a];
			}
			queueBool[numOfQueues] = isPreemptive;

			String[][] temp = queues;
			queues = new String[numOfQueues + 1][3];
			for (int x = 0; x < temp.length; x++) {
				for (int y = 0; y < 3; y++) {
					queues[x][y] = temp[x][y];
				}
			}
			queues[numOfQueues] = qcb;
		}
		numOfQueues++;
	}

	public static void addComponent(JPanel panel, JComponent component, int x1, int y1, int x2, int y2) {
		component.setBounds(x1, y1, x2, y2);
		panel.add(component);
		panel.repaint();
		panel.revalidate();
	}

	public void schedulingAlgo(String choice, int[] pID, int[] a, int[] b, int[] p, int queue, int quantum) {
		if (choice.startsWith("(FCFS)")) {
			new FCFS(pID, a, b, queue);
		} else if (choice.startsWith("(SJF)")) {
			new SJF(pID, a, b, queue);
		} else if (choice.startsWith("(SRTF)")) {
			new SRTF(pID, a, b, queue);
		} else if (choice.startsWith("(NPP)")) {
			new NP(pID, a, b, p, queue);
		} else if (choice.startsWith("(PP)")) {
			new PEP(pID, b, a, p);
		} else if (choice.startsWith("(RR)")) {
			new RR(pID, a, b, quantum, queue);
		}
	}


	public String schedulingAlgorithm(String choice) {
		if (choice.startsWith("(FCFS)")) {
			return "FCFS";
		} else if (choice.startsWith("(SJF)")) {
//			new SJF(pID, a, b, queue);
			return "SRTF";
		} else if (choice.startsWith("(SRTF)")) {
			return "SRTF";
		} else if (choice.startsWith("(NPP)")) {
//			new NP(pID, a, b, p, queue);
			return "PRIO";
		} else if (choice.startsWith("(PP)")) {
//			new PEP(pID, b, a, p);
			return "PRIO";
		} else if (choice.startsWith("(RR)")) {
//			new RR(pID, a, b, quantum, queue);
			return "RR";
		}
		return choice;
	}

	public boolean isPreemptive(String choice){
		if (choice.startsWith("(FCFS)") || choice.startsWith("(SJF)") || choice.startsWith("(NPP)")) {
			return false;
		}
		else if (choice.startsWith("(SRTF)") || choice.startsWith("(PP)") || choice.startsWith("(RR)")) {
			return true;
		}
		return false;
	}

	public void resetAll(){
		for (int i = 1; i < tableRow; i++) {
			for (int j = 1; j < tableColumn; j++) {
				panelHolder[i][j].setText("");
			}
		}
	}

	@Override
	public void actionPerformed(ActionEvent event) {
		if (event.getSource() == startButton) {
			int rowCtr = 1;

			while (rowCtr <= 20) {
				String value = panelHolder[rowCtr][1].getText();
				if (!value.equals("")) {
					rowCtr++;
				} else {
					break;
				}
			}

			// String pcb[] = new String[4];
			int[] pID = new int[rowCtr - 1];
			int[] arrival = new int[rowCtr - 1];
			int[] burst = new int[rowCtr - 1];
			int[] priority = new int[rowCtr - 1];

			for (int i = 1; i < rowCtr; i++) {
				for (int j = 1; j < tableColumn; j++) {
					String value = panelHolder[i][j].getText();
					if (!value.equals("")) {
						if (j == 1) {
							arrival[i - 1] = Integer.parseInt(value);
						} else if (j == 2) {
							burst[i - 1] = Integer.parseInt(value);
						} else if (j == 3) {
							priority[i - 1] = Integer.parseInt(value);
						}
						pID[i - 1] = i;
						// processes[i - 1][0] = Integer.toString(i);
						// processes[i - 1][j] = value;
						// pcb[0] = Integer.toString(i);
						// pcb[j] = value;
					} else {
						break;
					}
				}
				// addProcesses(pcb, addColor());
			}

//			 int ctr = 0;
//			 for (int x = 0; x < algorithmDropbox.length; x++) {
//			 String choice =
//			 String.valueOf(algorithmDropbox[x].getSelectedItem());
//			 String quantum = quanTextField[x].getText();
//			 String schedAlgo = schedulingAlgorithm(choice);
//			 String qcb[] = { Integer.toString(++ctr), quantum, schedAlgo };
//			 boolean flag = isPreemptive(choice);
//
//			 if (!choice.equals(""))
//				 addQueues(qcb, flag);
//			 }

			int quantum = 0;
			for (int i = 0; i < algorithmDropbox.length; i++) {
				String choice = String.valueOf(algorithmDropbox[i].getSelectedItem());
				if(!quanTextField[i].getText().equals("Quantum"))
					quantum = Integer.parseInt(quanTextField[i].getText());
				schedulingAlgo(choice, pID, arrival, burst, priority, i, quantum);
			}

			System.out.println(numOfQueues);
			System.out.println(numOfProcesses);
		}

		if (event.getSource() == exitButton) {
			System.exit(0);
		}

		if(event.getSource() == stopButton){
			resetAll();
		}
	}
}
