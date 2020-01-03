import javax.swing.*;
import javax.swing.GroupLayout.Alignment;
import javax.swing.table.DefaultTableModel;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.Calendar;
import java.util.Vector;

import RFID.*;

public class MainFrame extends JFrame implements Runnable{
	private static final long serialVersionUID = -2627421896510691129L;
	private long m_handle = 0;
	DefaultTableModel TableModel = new DefaultTableModel();
	private boolean b_threadFlg = false;

	Vector<String> vTitile = new Vector<String>();
	Vector<Object> vRowData = new Vector<Object>();

	private JButton openButton = null;
	private JButton closeButton = null;
	private JButton getInfoButton = null;
	private JButton getFlowButton = null;
	private JButton resetFlowButton = null;
	private JButton reverseDirButton = null;
	private JButton getSysTimeButton = null;
	private JButton setSysTimeButton = null;
	private JButton setOutPutButton = null;
	private JButton startButton = null;
	private JButton stopButton = null;

	private JTable reportTable = null;
	private JTextField IpTextField;

	public MainFrame(){
		setTitle("LS-Gate Demo for Java");
		
		//Load the library fist
		LoadLibrary();

		openButton = new JButton("open");
		openButton.addActionListener(new ActionListener() {

			public void actionPerformed(ActionEvent e) {
				// TODO Open Device
				String connStr = String.format("RDType=LSG405;CommType=NET;RemoteIP=%s;RemotePort=6012;LocalIP=", IpTextField.getText());
				stopButton.setEnabled(false);
				Long hrOut = new Long(0);
				int nret = rfidlib_reader.RDR_Open(connStr,hrOut);
				if(nret==0){
					ControlsEnable(true);	
					m_handle = hrOut;
					stopButton.setEnabled(false);
				}
				else{
					JOptionPane.showMessageDialog(null, "Open device failed!");
				}
			}
		});

		closeButton = new JButton("close");
		closeButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				// TODO Close Device
				int nret = rfidlib_reader.RDR_Close(m_handle);
				if (nret==0) {
					ControlsEnable(false);
					m_handle = 0;
				}
				else{
					JOptionPane.showMessageDialog(null, "Close device failed!");
				}
			}
		});


		getInfoButton = new JButton("get information");
		getInfoButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				char[] buffer = new char[256];
				Integer nSize = new Integer(0);
				int nret = rfidlib_reader.RDR_GetReaderInfor(m_handle,(byte)0,buffer,nSize);
				if (nret==0) {
					JOptionPane.showMessageDialog(null, String.valueOf(buffer, 0, nSize));
				}
				else {
					JOptionPane.showMessageDialog(null, String.format("failed!err=%d", nret));
				}
			}
		});

		JLabel ipLabel = new JLabel("IP:");

		IpTextField = new JTextField();
		IpTextField.setText("192.168.2.110");
		IpTextField.setColumns(10);

		JPanel CommandPanel = new JPanel();
		CommandPanel.setBorder(BorderFactory.createTitledBorder( "Command"));

		JPanel reportPanel = new JPanel();
		reportPanel.setBorder(BorderFactory.createTitledBorder( "Get report"));

		GroupLayout groupLayout = new GroupLayout(getContentPane());
		groupLayout.setHorizontalGroup(
				groupLayout.createParallelGroup(Alignment.TRAILING)
				.addGroup(groupLayout.createSequentialGroup()
						.addGroup(groupLayout.createParallelGroup(Alignment.LEADING)
								.addGroup(groupLayout.createSequentialGroup()
										.addGap(35)
										.addComponent(ipLabel)
										.addGap(18)
										.addComponent(IpTextField, GroupLayout.PREFERRED_SIZE, 104, GroupLayout.PREFERRED_SIZE)
										.addGap(18)
										.addComponent(openButton)
										.addGap(18)
										.addComponent(closeButton)
										.addGap(18)
										.addComponent(getInfoButton))
										.addGroup(groupLayout.createSequentialGroup()
												.addContainerGap()
												.addComponent(CommandPanel, GroupLayout.DEFAULT_SIZE, 529, Short.MAX_VALUE))
												.addGroup(groupLayout.createSequentialGroup()
														.addContainerGap()
														.addComponent(reportPanel, GroupLayout.PREFERRED_SIZE, 514, GroupLayout.PREFERRED_SIZE)))
														.addContainerGap())
				);
		groupLayout.setVerticalGroup(
				groupLayout.createParallelGroup(Alignment.LEADING)
				.addGroup(groupLayout.createSequentialGroup()
						.addGap(27)
						.addGroup(groupLayout.createParallelGroup(Alignment.BASELINE)
								.addComponent(ipLabel)
								.addComponent(IpTextField, GroupLayout.PREFERRED_SIZE, GroupLayout.DEFAULT_SIZE, GroupLayout.PREFERRED_SIZE)
								.addComponent(openButton)
								.addComponent(closeButton)
								.addComponent(getInfoButton))
								.addGap(18)
								.addComponent(CommandPanel, GroupLayout.PREFERRED_SIZE, 121, GroupLayout.PREFERRED_SIZE)
								.addGap(18)
								.addComponent(reportPanel, GroupLayout.DEFAULT_SIZE, 243, Short.MAX_VALUE)
								.addGap(18))
				);

		reportTable = new JTable();
		reportTable.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);

		startButton = new JButton("start");
		startButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				startThread();
			}
		});

		stopButton = new JButton("stop");
		stopButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				stopThread();
			}
		});

		GroupLayout gl_reportPanel = new GroupLayout(reportPanel);
		gl_reportPanel.setHorizontalGroup(
				gl_reportPanel.createParallelGroup(Alignment.LEADING)
				.addGroup(gl_reportPanel.createSequentialGroup()
						.addContainerGap()
						.addComponent(reportTable, GroupLayout.PREFERRED_SIZE, 385, GroupLayout.PREFERRED_SIZE)
						.addGap(18)
						.addGroup(gl_reportPanel.createParallelGroup(Alignment.LEADING)
								.addGroup(gl_reportPanel.createSequentialGroup()
										.addComponent(startButton, GroupLayout.DEFAULT_SIZE, 72, Short.MAX_VALUE)
										.addGap(13))
										.addGroup(gl_reportPanel.createSequentialGroup()
												.addComponent(stopButton, GroupLayout.DEFAULT_SIZE, 72, Short.MAX_VALUE)
												.addContainerGap())))
				);
		gl_reportPanel.setVerticalGroup(
				gl_reportPanel.createParallelGroup(Alignment.LEADING)
				.addGroup(gl_reportPanel.createSequentialGroup()
						.addContainerGap()
						.addGroup(gl_reportPanel.createParallelGroup(Alignment.LEADING)
								.addGroup(gl_reportPanel.createSequentialGroup()
										.addComponent(reportTable, GroupLayout.DEFAULT_SIZE, 199, Short.MAX_VALUE)
										.addContainerGap())
										.addGroup(Alignment.TRAILING, gl_reportPanel.createSequentialGroup()
												.addComponent(startButton)
												.addGap(18)
												.addComponent(stopButton)
												.addGap(93))))
				);
		reportPanel.setLayout(gl_reportPanel);

		getFlowButton = new JButton("get flow of people");
		getFlowButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {	
				Integer m_inFloPointer = new Integer(0);
				Integer m_outFlowPointer = new Integer(0);
				int nret = rfidlib_LSGate.LSG_CmdGetCurrentFlowOfPeople(m_handle, m_inFloPointer, m_outFlowPointer);
				if (nret==0) {
					JOptionPane.showMessageDialog(null, String.format("In:%d;Out:%d", m_inFloPointer,m_outFlowPointer));
				}
				else{
					JOptionPane.showMessageDialog(null, String.format("Failed,err=%d",nret));
				}

			}
		});

		resetFlowButton = new JButton("reset flow of people");
		resetFlowButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int nret=rfidlib_LSGate.LSG_CmdResetFlowOfPeople(m_handle,(byte)3);
				if (nret==0) {
					JOptionPane.showMessageDialog(null, "OK");
				}
				else{
					JOptionPane.showMessageDialog(null, String.format("failed,err = %d",nret));
				}
			}
		});

		reverseDirButton = new JButton("reverse direction");
		reverseDirButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int nret = rfidlib_LSGate.LSG_CmdReverseDirection(m_handle);
				if (nret==0) {
					JOptionPane.showMessageDialog(null, "OK");
				}
				else{
					JOptionPane.showMessageDialog(null, String.format("Failed,err=%d", nret));
				}
			}
		});

		getSysTimeButton = new JButton("Get System Time");
		getSysTimeButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				Integer year = new Integer(0);
				Byte month = new Byte((byte) 0);
				Byte day = new Byte((byte) 0);
				Byte hour = new Byte((byte) 0);
				Byte min = new Byte((byte) 0);
				Byte sec = new Byte((byte) 0);
				int nret = rfidlib_LSGate.LSG_CmdGetSystemTime(m_handle, year,month,day,hour,min,sec);
				if (nret==0) {
					JOptionPane.showMessageDialog(null, String.format("%d-%d-%d %d:%d:%d", year,month,day,hour,month,sec));
				}
				else{
					JOptionPane.showMessageDialog(null, String.format("Failed,err=%d", nret));
				}
			}
		});

		setSysTimeButton = new JButton("Set System Time");
		setSysTimeButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				int year = Calendar.YEAR;
				byte month = (byte) Calendar.MONTH;
				byte day = (byte) Calendar.DATE;
				byte hour = (byte) Calendar.HOUR;
				byte minute = (byte) Calendar.MINUTE;
				byte second = (byte) Calendar.SECOND;
				int nret = rfidlib_LSGate.LSG_CmdSetSystemTime(m_handle,year,month,day,hour,minute,second);
				if (nret==0) {
					JOptionPane.showMessageDialog(null, "OK");
				}
				else{
					JOptionPane.showMessageDialog(null, String.format("Failed,err=%d", nret));
				}
			}
		});
		setOutPutButton = new JButton("Set Out put");
		setOutPutButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				long dnOutputOper = rfidlib_reader.RDR_CreateSetOutputOperations();
				if (dnOutputOper!=0) {
					rfidlib_reader.RDR_AddOneOutputOperation(dnOutputOper,(byte)1,(byte)3,1,
							100,100);
					//调用声光报警
					int i = rfidlib_reader.RDR_SetOutput(m_handle, dnOutputOper);
					if(i==0){
						System.out.println("调用声光报警器执行报警：成功！返回："+i);
					}else{
						System.out.println("调用声光报警器执行报警：失败，返回："+i);
					}
					rfidlib_reader.DNODE_Destroy(dnOutputOper);
				}
			}
		});
		GroupLayout gl_CommandPanel = new GroupLayout(CommandPanel);
		gl_CommandPanel.setHorizontalGroup(
				gl_CommandPanel.createParallelGroup(Alignment.LEADING)
				.addGroup(gl_CommandPanel.createSequentialGroup()
						.addContainerGap()
						.addGroup(gl_CommandPanel.createParallelGroup(Alignment.LEADING, false)
								.addComponent(getSysTimeButton, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
								.addComponent(getFlowButton))
								.addGap(18)
								.addGroup(gl_CommandPanel.createParallelGroup(Alignment.LEADING, false)
										.addComponent(setSysTimeButton, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
										.addComponent(resetFlowButton))
										.addGap(30)
										.addGroup(gl_CommandPanel.createParallelGroup(Alignment.LEADING, false)
												.addComponent(setOutPutButton, GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
												.addComponent(reverseDirButton))
										.addContainerGap(26, Short.MAX_VALUE))
				);
		gl_CommandPanel.setVerticalGroup(
				gl_CommandPanel.createParallelGroup(Alignment.LEADING)
				.addGroup(gl_CommandPanel.createSequentialGroup()
						.addContainerGap()
						.addGroup(gl_CommandPanel.createParallelGroup(Alignment.BASELINE)
								.addComponent(getFlowButton)
								.addComponent(resetFlowButton)
								.addComponent(reverseDirButton))
								.addGap(18)
								.addGroup(gl_CommandPanel.createParallelGroup(Alignment.BASELINE)
										.addComponent(getSysTimeButton)
										.addComponent(setSysTimeButton)
										.addComponent(setOutPutButton)
										)
										.addContainerGap(22, Short.MAX_VALUE))
				);
		CommandPanel.setLayout(gl_CommandPanel);
		getContentPane().setLayout(groupLayout);

		//TableModel.setDataVector(arg0, arg1);

		vTitile.addElement("Serial Number");
		vTitile.addElement("Direction");
		vTitile.addElement("Time");

		TableModel.setDataVector(vRowData, vTitile);
		reportTable.setModel(TableModel);


		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setSize(555, 500);
		this.setResizable(false);
		this.setVisible(true);
		this.setLocation(200, 200);

		ControlsEnable(false);
	}

	
	private void LoadLibrary()
	{
		int osType = 0;
		int arType = 0;
		String libPath = System.getProperty("user.dir");
		String osName = System.getProperty("os.name");
		String architecture = System.getProperty("os.arch");
		osName = osName.toUpperCase();
		if (osName.equals("LINUX"))
		{
			osType = rfid_def.VER_LINUX;
		}
		else if (osName.indexOf("WIN") != -1)
		{
			osType = rfid_def.VER_WINDOWS;
		}

		architecture = architecture.toUpperCase();
		if (architecture.equals("AMD64")||architecture.equals("X64") || architecture.equals("UNIVERSAL"))
		{
			arType = rfid_def.AR_X64;
		}
		else
		{
			arType = rfid_def.AR_X86;
		}

		rfidlib_reader.LoadLib(libPath, osType, arType);
		rfidlib_LSGate.LoadLib(libPath, osType, arType);
	}
	
	private void ControlsEnable(boolean isOpen) {
		openButton.setEnabled(!isOpen);
		closeButton.setEnabled(isOpen);
		getInfoButton.setEnabled(isOpen);
		IpTextField.setEnabled(!isOpen);
		getFlowButton.setEnabled(isOpen);
		resetFlowButton.setEnabled(isOpen);
		reverseDirButton.setEnabled(isOpen);
		getSysTimeButton.setEnabled(isOpen);
		setSysTimeButton.setEnabled(isOpen);
		setOutPutButton.setEnabled(isOpen);
		startButton.setEnabled(isOpen);
		stopButton.setEnabled(isOpen);
	}

	public static void  main(String []args){
		new MainFrame();
	}

	private void startThread(){
		Thread m_thread = new Thread(this);
		vRowData.clear();
		TableModel.setDataVector(vRowData, vTitile);
		m_thread.start();
		startButton.setEnabled(false);
		stopButton.setEnabled(true);
	}

	private void stopThread() {
		b_threadFlg = false;
		stopButton.setEnabled(false);
		rfidlib_reader.RDR_SetCommuImmeTimeout(m_handle);
	}

	public synchronized void  run() {
		// TODO Auto-generated method stub
		b_threadFlg = true;
		int nret = 0;
		byte flag = 0;
		rfidlib_reader.RDR_ResetCommuImmeTimeout(m_handle);
		while(b_threadFlg){
			nret=rfidlib_LSGate.LSG_CmdGetReports(m_handle, flag, (byte)10);
			if (nret!=0) {
				flag = 0;
				System.out.println(String.format("err:%d", nret));
				continue;
			}
			flag = 1;
			int mCnt = rfidlib_reader.RDR_GetTagDataReportCount(m_handle);
			if(mCnt>0){	
				int hReport = rfidlib_reader.RDR_GetTagDataReport(m_handle,rfid_def.RFID_SEEK_FIRST);
				while (hReport!=0) {
					char[] slData = new char[64];
					String sTime;
					Integer nSize = new Integer(64);
					Byte dir = new Byte((byte) 0);
					byte []m_Time = new byte[6];		
					nret = rfidlib_LSGate.LSG_ParseSCEventData(hReport, slData, nSize,dir, m_Time);
					if (nret!=0) {
						flag = 0;
						break;
					}
					sTime = String.format("%d-%d-%d %d:%d:%d", m_Time[0],m_Time[1],m_Time[2],m_Time[3],
							m_Time[4],m_Time[5]);
					AddData(String.valueOf(slData), dir, sTime);
					hReport = rfidlib_reader.RDR_GetTagDataReport(m_handle,rfid_def.RFID_SEEK_NEXT);
				}
			}
		}
		startButton.setEnabled(true);
		stopButton.setEnabled(false);
		b_threadFlg = false;
		rfidlib_reader.RDR_ResetCommuImmeTimeout(m_handle);
	}

	//显示记录
	private void AddData(String slData,byte dir,String sTime) {
		//增加一条报警记录
		String sDir = "";
		if (dir == 1){
			sDir = "in";
		}
		else if (dir == 2){
			sDir = "out";
		}

		Vector<String> vectorRow = new Vector<String>();
		vectorRow.addElement(new String(slData));
		vectorRow.addElement(new String(sDir));
		vectorRow.addElement(new String(sTime));
		vRowData.addElement(vectorRow);		
		TableModel.setDataVector(vRowData, vTitile);
		reportTable.setModel(TableModel);
	}
}

