import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.Color;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JComboBox;
import javax.swing.JComponent;
import javax.swing.JTextField;
import java.awt.event.ActionListener;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.event.ActionEvent;
import javax.swing.SwingConstants;
import java.awt.GridLayout;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.ArrayList;

public class MLFQFrame extends JFrame implements ActionListener {
	private JTextField avgWait = new JTextField("");
	private JTextField avgTurnaround = new JTextField("");
	private JTextField avgResponse = new JTextField("");

	private JPanel mainPanel = new JPanel(null);
	private JPanel tablePanel = new JPanel();
	private JPanel algoPanel = new JPanel(null);
	static JPanel infoPanel = new JPanel(null);
	static JPanel ganttPanel = new JPanel(null);

	private JButton startButton = new JButton("START");
	private JButton stopButton = new JButton("RESET");
	private JButton exitButton = new JButton("EXIT");

	private JLabel q1Label1 = new JLabel("Q1", SwingConstants.CENTER);
	private JLabel q2Label1 = new JLabel("Q2", SwingConstants.CENTER);
	private JLabel q3Label1 = new JLabel("Q3", SwingConstants.CENTER);

	static JPanel qPanel = new JPanel();
	private JTextField quanTextField[] = new JTextField[3];

	private String[] rowLabelString = { "ID", "ARRIVAL", "BURST", "PRIORITY" };
	private String[] colLabelString = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20" };

	private int tableRow = 21;
	private int tableColumn = 4;
	static int[][] processID;
	static int[][] arrivalTime;
	static int[][] burstTime;
	static int[][] priority;
	private int queues[];
	private int quantum[];

	private JPanel processNumPanel = new JPanel();
	private JLabel processNumLabel = new JLabel("Number of Processes: ");
	private JTextField processNumField = new JTextField("");
	private JButton enterButton = new JButton("ENTER");
	private JButton clearButton = new JButton("CLEAR");

	private JLabel queueNumLabel = new JLabel("Number of Queues: ");
	private JTextField queueNumField = new JTextField("");
	private JButton queueEnterButton = new JButton("ENTER");
	private JButton queueClearButton = new JButton("CLEAR");

	private JTextField[][] panelHolder = new JTextField[tableRow][tableColumn];
	private JLabel[][] label = new JLabel[tableRow][tableColumn];

	private String[] algorithmString = {"(FCFS) First Come First Serve", "(SJF) Shortest Job First", "(SRTF) Shortest Remaining Time First", "(NPP) Non-preemptive Priority", "(PP) Preemptive Priority","(RR) Round Robin" };
	private String[] policy = {"Higher Before Lower", "Fixed Time Slots"};
	private JComboBox algorithmDropbox[] = new JComboBox[3];
	private JComboBox policyDropbox = new JComboBox(policy);

	private boolean isProcessLoaded = false;
	private boolean isQueueLoaded = false;
	static int numOfProcesses = 0, numOfQueues = 0;
	static boolean stop = false;

	static JPanel[][] processLabel;
	static JPanel[] timeLabel;
	static JPanel processPanel = new JPanel();
	static JPanel timePanel = new JPanel();

	static float avgwt = 0, avgta = 0, avgrt = 0;
	static boolean isTrue = true;
	static ArrayList<Integer> process_ID = new ArrayList<Integer>();
	static ArrayList<Integer> arrival_time = new ArrayList<Integer>();

	public MLFQFrame() {
		add(mainPanel);
		mainPanel.setBackground(new Color(220, 220, 220));
		createTable();
		createGantt();
		createAlgo();
		createInfo();
	}

	public void createTable() {
		processNumPanel.setBounds(20, 10, 370, 30);
		mainPanel.add(processNumPanel);

		clearButton.setEnabled(false);
		processNumPanel.setLayout(new BoxLayout(processNumPanel, BoxLayout.LINE_AXIS));
		processNumPanel.add(processNumLabel);
		processNumPanel.add(processNumField);
		processNumPanel.add(enterButton);
		processNumPanel.add(clearButton);

		processNumField.addKeyListener(new KeyAdapter() {
			public void keyTyped(KeyEvent e){
				char c = e.getKeyChar();
				if(((c < '0')||(c > '9')) && (c != KeyEvent.VK_BACK_SPACE)){
					e.consume();
				}
			}
		});
		enterButton.addActionListener(this);
		clearButton.addActionListener(this);

		tablePanel.setBounds(20, 40, 370, 720);
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
					panelHolder[m][n].setEnabled(false);
					panelHolder[m][n].addKeyListener(new KeyAdapter() {
						public void keyTyped(KeyEvent e){
							char c = e.getKeyChar();
							if(((c < '0')||(c > '9')) && (c != KeyEvent.VK_BACK_SPACE)){
								e.consume();
							}
						}
					});
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

			quanTextField[i].addKeyListener(new KeyAdapter() {
				public void keyTyped(KeyEvent e){
					char c = e.getKeyChar();
					if(((c < '0')||(c > '9')) && (c != KeyEvent.VK_BACK_SPACE)){
						e.consume();
					}
				}
			});

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

		}

		qPanel.setLayout(new GridLayout(2,1));
		JLabel q1Label = new JLabel("GANTT CHART", SwingConstants.CENTER);

		ganttPanel.add(q1Label);
		q1Label.setOpaque(true);
		q1Label.setBackground(new Color(90, 90, 90));
		q1Label.setBounds(0, 20, 1000, 38);
		qPanel.setBackground(Color.GRAY);
		timePanel.setBackground(Color.GRAY);
		processPanel.setBackground(Color.GRAY);

		JScrollPane pane1 = new JScrollPane(qPanel);
		pane1.setBounds(0, 60, 950,128);
		ganttPanel.add(pane1);

		queueEnterButton.addActionListener(this);
		queueClearButton.addActionListener(this);
	}

	public void createAlgo() {
		algoPanel.setBounds(400, 423, 405, 310);
		algoPanel.setBackground(new Color(200, 200, 200));
		mainPanel.add(algoPanel);

		queueClearButton.setEnabled(false);
		queueNumLabel.setBounds(15,0,130,30);
		queueNumField.setBounds(125,0,85,30);
		queueEnterButton.setBounds(215,0,90,30);
		queueClearButton.setBounds(305,0,90,30);

		queueNumField.addKeyListener(new KeyAdapter() {
			public void keyTyped(KeyEvent e){
				char c = e.getKeyChar();
				if(((c < '0')||(c > '9')) && (c != KeyEvent.VK_BACK_SPACE)){
					e.consume();
				}
			}
		});

		algoPanel.add(policyDropbox);
		policyDropbox.setBounds(10, 30, 390, 25);
		policyDropbox.setEnabled(false);

		algoPanel.add(queueNumLabel);
		algoPanel.add(queueNumField);
		algoPanel.add(queueEnterButton);
		algoPanel.add(queueClearButton);

		q1Label1.setBounds(0, 60, 405, 25);
		q1Label1.setOpaque(true);
		q1Label1.setBackground(new Color(90, 90, 90));
		algoPanel.add(q1Label1);

		algoPanel.add(algorithmDropbox[0]);
		algorithmDropbox[0].setBounds(10, 90, 200, 25);
		algorithmDropbox[0].setEnabled(false);

		algoPanel.add(quanTextField[0]);
		quanTextField[0].setBounds(300, 90, 100, 25);
		quanTextField[0].setEnabled(false);

		q2Label1.setBounds(0, 130, 405, 25);
		q2Label1.setOpaque(true);
		q2Label1.setBackground(new Color(90, 90, 90));
		algoPanel.add(q2Label1);

		algoPanel.add(algorithmDropbox[1]);
		algorithmDropbox[1].setBounds(10, 160, 200, 25);
		algorithmDropbox[1].setEnabled(false);

		algoPanel.add(quanTextField[1]);
		quanTextField[1].setBounds(300, 160, 100, 25);
		quanTextField[1].setEnabled(false);

		q3Label1.setBounds(0, 195, 405, 25);
		q3Label1.setOpaque(true);
		q3Label1.setBackground(new Color(90, 90, 90));
		algoPanel.add(q3Label1);

		algoPanel.add(algorithmDropbox[2]);
		algorithmDropbox[2].setBounds(10, 225, 200, 25);
		algorithmDropbox[2].setEnabled(false);

		algoPanel.add(quanTextField[2]);
		quanTextField[2].setBounds(300, 225, 100, 25);
		quanTextField[2].setEnabled(false);

		algoPanel.add(startButton);
		startButton.setBounds(10, 260, 120, 40);
		startButton.setEnabled(false);

		algoPanel.add(stopButton);
		stopButton.setBounds(140, 260, 120, 40);

		algoPanel.add(exitButton);
		exitButton.setBounds(270, 260, 120, 40);

		algorithmDropbox[0].addActionListener(this);
		algorithmDropbox[1].addActionListener(this);
		algorithmDropbox[2].addActionListener(this);
		policyDropbox.addActionListener(this);
		startButton.addActionListener(this);
		exitButton.addActionListener(this);
		stopButton.addActionListener(this);
	}

	public static void addComponent(JPanel panel, JComponent component, int x1, int y1, int x2, int y2){
		panel.add(component);
		component.setBounds(x1, y1, x2, y2);
		panel.repaint();
		panel.revalidate();
	}

	public void createInfo() {
		JLabel info = new JLabel("INFO PANEL");
		JLabel wait = new JLabel("Average Waiting Time");
		JLabel turnaround = new JLabel("Average Turnaround Time");
		JLabel response = new JLabel("");

		infoPanel.setBounds(815, 423, 523, 310);
		wait.setBounds(30, 20, 523, 20);
		response.setBounds(30, 90, 523, 20);
		turnaround.setBounds(30, 160, 523, 20);

		avgWait.setBounds(30, 50, 300, 30);
		//avgResponse.setBounds(30, 120, 300, 30);
		avgTurnaround.setBounds(30, 190, 300, 30);

		avgWait.setEditable(false);
		avgTurnaround.setEditable(false);
		avgResponse.setEditable(false);

		infoPanel.add(avgWait);
		infoPanel.add(avgTurnaround);
		infoPanel.add(avgResponse);

		infoPanel.add(wait);
		infoPanel.add(turnaround);
		infoPanel.add(response);

		mainPanel.add(infoPanel);
	}

	public void enterQueue(int num){
		processLabel = new JPanel[1][];
		timeLabel = new JPanel[numOfProcesses];

		for (int m = 0; m < num; m++) {
			algorithmDropbox[m].setEnabled(true);
			quanTextField[m].setEnabled(false);
		}

		queueEnterButton.setEnabled(false);
		queueClearButton.setEnabled(true);
		policyDropbox.setEnabled(true);

		isQueueLoaded = true;
		if(isProcessLoaded && isQueueLoaded){
			startButton.setEnabled(true);
		}
	}

	public void resetQueue(){
		for(int m = 0; m < 3; m++){
			int ctr = m;
			algorithmDropbox[m].setSelectedIndex(0);
			policyDropbox.setSelectedIndex(0);
			quanTextField[m].setText("Quantum");
			quanTextField[m].addFocusListener(new FocusListener() {
				int i = ctr;
				private boolean showingPlaceholder = true;
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
			algorithmDropbox[m].setEnabled(false);
			quanTextField[m].setEnabled(false);
		}
		queueNumField.setText("");
		isQueueLoaded = false;
		startButton.setEnabled(false);
		queueEnterButton.setEnabled(true);
		queueClearButton.setEnabled(false);
		policyDropbox.setEnabled(false);
		queueNumField.setEnabled(true);
	}

	public void enterProcess(int num){
		for (int m = 1; m <= num; m++) {
			for (int n = 1; n < tableColumn; n++) {
				panelHolder[m][n].setEnabled(true);
			}
		}
		enterButton.setEnabled(false);
		clearButton.setEnabled(true);

		isProcessLoaded = true;
		if(isProcessLoaded && isQueueLoaded){
			startButton.setEnabled(true);
		}
	}

	public void resetTable(){
		for (int i = 1; i < tableRow; i++) {
			for (int j = 1; j < tableColumn; j++) {
				panelHolder[i][j].setText("");
				panelHolder[i][j].setEnabled(false);
			}
		}
		processNumField.setText("");
		isProcessLoaded = false;
		startButton.setEnabled(false);
		enterButton.setEnabled(true);
		clearButton.setEnabled(false);
		processNumField.setEnabled(true);
	}

	public void getInfo(){
		processID = new int[numOfQueues][numOfProcesses];
		arrivalTime = new int[numOfQueues][numOfProcesses];
		burstTime = new int[numOfQueues][numOfProcesses];
		priority = new int[numOfQueues][numOfProcesses];
		queues = new int[numOfQueues];
		quantum = new int[numOfQueues];

		try{
			for(int m = 1; m <= numOfProcesses; m++){
				for(int n = 1; n < tableColumn; n++){
					processID[0][m-1] = m;

					if(!panelHolder[m][n].getText().isEmpty()){
						int number = Integer.parseInt(panelHolder[m][n].getText());
						if(n == 1){
							arrivalTime[0][m-1] = number;
						}else if (n == 2){
							if(number != 0 && number <= 50){
								burstTime[0][m-1] = number;
							}else if(number > 50){
								JOptionPane.showMessageDialog(this, "Burst time should not be greater than 50", "Invalid Input", JOptionPane.ERROR_MESSAGE);
								return;
							}else{
								JOptionPane.showMessageDialog(this, "Burst time should not be equal to 0", "Invalid Input", JOptionPane.ERROR_MESSAGE);
								return;
							}
						}else{
							priority[0][m-1] = number;
						}

					}
					else{
						JOptionPane.showMessageDialog(this, "Data should not be blank", "Invalid Input", JOptionPane.ERROR_MESSAGE);
						return;
					}
				}
			}
		}catch(Exception e){}

			for(int i = 0; i < numOfQueues; i++){
				queues[i] = algorithmDropbox[i].getSelectedIndex();
				if(policyDropbox.getSelectedIndex() == 0){
					if(algorithmDropbox[i].getSelectedIndex() == 5){
						try{
							quantum[i] = Integer.parseInt(quanTextField[i].getText());
						}catch(NumberFormatException e){
							JOptionPane.showMessageDialog(this, "Please input the quantum!", "Invalid Input", JOptionPane.ERROR_MESSAGE);
							return;
						}
					}
				}
				if(policyDropbox.getSelectedIndex() == 1){
					try{
						quantum[i] = Integer.parseInt(quanTextField[i].getText());
					}catch(NumberFormatException e){
						JOptionPane.showMessageDialog(this, "Please input the quantum!", "Invalid Input", JOptionPane.ERROR_MESSAGE);
						return;
					}
				}
			}

			clearButton.setEnabled(false);
			queueClearButton.setEnabled(false);
			startButton.setEnabled(false);

			schedulingAlgo();

		}

		public void schedulingAlgo(){
			int i = 0;
			while(isTrue){
					try{
						if(policyDropbox.getSelectedIndex() == 0){
							if(queues[i] == 0){
								new FCFS(processID[i], arrivalTime[i], burstTime[i], priority[i], i);
							}
							else if(queues[i] == 1){
								new SJF(processID[i], arrivalTime[i], burstTime[i], priority[i], i);
							}
							else if(queues[i] == 2){
								new SRTF(processID[i], arrivalTime[i], burstTime[i], priority[i], i);
							}
							else if(queues[i] == 3){
								new NP(processID[i], arrivalTime[i], burstTime[i], priority[i], i);
							}
							else if(queues[i] == 4){
								new PP(processID[i], arrivalTime[i], burstTime[i], priority[i], i);
							}
							else if(queues[i] == 5){
								try{
									new RR(processID[i], arrivalTime[i], burstTime[i], priority[i], quantum[i], i);
								}catch(NumberFormatException e){
									JOptionPane.showMessageDialog(this, "Please input the quantum!", "Invalid Input", JOptionPane.ERROR_MESSAGE);
									clearButton.setEnabled(true);
									queueClearButton.setEnabled(true);
									startButton.setEnabled(true);
								}
							}
						}else if(policyDropbox.getSelectedIndex() == 1){
							if(queues[i] == 0){
								new FCFS(processID[i], arrivalTime[i], burstTime[i], priority[i], i, quantum[i]);
							}
							else if(queues[i] == 1){
								new SJF(processID[i], arrivalTime[i], burstTime[i], priority[i], i, quantum[i]);
							}
							else if(queues[i] == 2){
								new SRTF(processID[i], arrivalTime[i], burstTime[i], priority[i], i, quantum[i]);
							}
							else if(queues[i] == 3){
								new NP(processID[i], arrivalTime[i], burstTime[i], priority[i], i, quantum[i]);
							}
							else if(queues[i] == 4){
								new PP(processID[i], arrivalTime[i], burstTime[i], priority[i], i, quantum[i]);
							}
							else if(queues[i] == 5){
								try{
									new RR(processID[i], arrivalTime[i], burstTime[i], priority[i], quantum[i], i);
								}catch(NumberFormatException e){
									JOptionPane.showMessageDialog(this, "Please input the quantum!", "Invalid Input", JOptionPane.ERROR_MESSAGE);
									clearButton.setEnabled(true);
									queueClearButton.setEnabled(true);
									startButton.setEnabled(true);
								}
							}
						}
					}catch(Exception e){}
						if(i == (numOfQueues - 1)){
							i = -1;
						}
						i++;
				}

				processLabel[0] = new JPanel[process_ID.size()];
				GanttThread ppt = new GanttThread(process_ID, arrival_time, 0);

				avgWait.setText(""+avgwt/numOfProcesses);
				avgTurnaround.setText(""+avgta/numOfProcesses);
				//avgResponse.setText(""+avgrt/numOfProcesses);
			}

			@Override
			public void actionPerformed(ActionEvent event) {
				if (event.getSource() == startButton) {
					getInfo();
				}

				if (event.getSource() == exitButton) {
					System.exit(0);
				}

				if(event.getSource() == stopButton){
					isTrue = true;
					avgrt = 0;
					avgta = 0;
					avgwt = 0;
					process_ID.clear();
					arrival_time.clear();
					resetTable();
					resetQueue();
					try{
						for(int i = 0; i < numOfQueues; i++){
							qPanel.removeAll();
							avgWait.setText("");
							avgTurnaround.setText("");
							avgResponse.setText("");
							timePanel.removeAll();
							processPanel.removeAll();
							mainPanel.repaint();
							mainPanel.revalidate();
						}
					}catch(Exception e){}
					}

					if(event.getSource() == enterButton){
						try{
							numOfProcesses = Integer.parseInt(processNumField.getText());
							if(numOfProcesses > 20 || numOfProcesses == 0){
								if(numOfProcesses == 0)
								JOptionPane.showMessageDialog(this, "Processes should not be equal to 0", "Invalid Input", JOptionPane.ERROR_MESSAGE);
								else
								JOptionPane.showMessageDialog(this, "Processes should not be more than 20", "Invalid Input", JOptionPane.ERROR_MESSAGE);
							}else{
								processNumField.setEnabled(false);
								enterProcess(numOfProcesses);
							}
						}catch(NumberFormatException e){
							numOfProcesses = 0;
						}
					}

					if(event.getSource() == clearButton){
						resetTable();
					}

					if(event.getSource() == queueEnterButton){
						try{
							numOfQueues = Integer.parseInt(queueNumField.getText());
							if(numOfQueues > 3 || numOfQueues == 0){
								if(numOfQueues == 0)
								JOptionPane.showMessageDialog(this, "Queues should not be equal to 0", "Invalid Input", JOptionPane.ERROR_MESSAGE);
								else
								JOptionPane.showMessageDialog(this, "Queues should not be more than 3", "Invalid Input", JOptionPane.ERROR_MESSAGE);
							}else{
								queueNumField.setEnabled(false);
								enterQueue(numOfQueues);
							}
						}catch(NumberFormatException e){
							numOfQueues = 0;
						}
					}

					if(event.getSource() == queueClearButton){
						resetQueue();
					}

					if(event.getSource() == policyDropbox){
						try{
							for(int i = 0; i < numOfQueues; i++){
								if(policyDropbox.getSelectedIndex() == 1){
									quanTextField[i].setEnabled(true);
								}
								else if(policyDropbox.getSelectedIndex() == 0){
									quanTextField[i].setEnabled(false);
								}
							}
						}catch(Exception e){}
						}

						for(int i = 0; i < numOfQueues; i++){
							try{
								if((event.getSource() == algorithmDropbox[i]) && (policyDropbox.getSelectedIndex() == 0) ){
									if(algorithmDropbox[i].getSelectedIndex() == 5){
										quanTextField[i].setEnabled(true);
									}else{
										quanTextField[i].setEnabled(false);
									}
								}
							}catch(Exception e){}
							}
						}
					}
