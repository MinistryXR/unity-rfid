import javax.swing.JFrame;
import javax.swing.GroupLayout;
import javax.swing.GroupLayout.Alignment;
import javax.swing.JLabel;

import RFID.*;

import javax.swing.JComboBox;
import javax.swing.LayoutStyle.ComponentPlacement;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.border.TitledBorder;
import javax.swing.table.DefaultTableModel;
import javax.swing.UIManager;

import java.awt.Color;

import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.JTable;
import javax.swing.JCheckBox;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.Vector;

public class MainFrm extends JFrame implements Runnable
{
	private static final long serialVersionUID = 1L;
	private long m_hr = 0;// 设备操作句柄
	private JTextField textIpAddr = new JTextField();;
	private JTable tableRecord = new JTable();
	private JComboBox<String> cmbActiveTime = new JComboBox<String>();
	private JComboBox<String> cmbFrequency = new JComboBox<String>();
	private JComboBox<String> cmbStopTime = new JComboBox<String>();
	private JButton btnOpen = new JButton("Open");
	private JButton btnClose = new JButton("Close");
	private JButton btnDevInfo = new JButton("Device Information");
	private JButton btnSetOutput = new JButton("Set Output");
	private JCheckBox checkBuzzer = new JCheckBox("Buzzer on board");
	private JCheckBox checkOutput_1 = new JCheckBox("Output#1");
	private JCheckBox checkOutput_2 = new JCheckBox("Output#2");
	private JCheckBox checkOutput_3 = new JCheckBox("Output#3");
	private JCheckBox checkOutput_4 = new JCheckBox("Output#4");
	private JButton btnStart = new JButton("start");
	private JButton btnStop = new JButton("Stop");
	private JButton btnClear = new JButton("Clear");
	private JComboBox<String> cmbCommunicateType = new JComboBox<String>();
	private JComboBox<String> cmbDevType = new JComboBox<String>();
	private JComboBox<String> cmbComName = new JComboBox<String>();
	private DefaultTableModel TableModel = new DefaultTableModel();
	private Vector<String> vTitile = new Vector<String>();
	private Vector<Object> vRowData = new Vector<Object>();
	private boolean b_isGetReportRun = false;

	private boolean bThreadRunFlg = false;

	public MainFrm()
	{
		setTitle("Meeting Gate Demo For Java");

		JPanel panelCommunicatePara = new JPanel();
		panelCommunicatePara.setBorder(new TitledBorder(null, "",
				TitledBorder.LEADING, TitledBorder.TOP, null, null));
		JPanel panelRecord = new JPanel();
		panelRecord.setBorder(new TitledBorder(null, "Get Record",
				TitledBorder.LEADING, TitledBorder.TOP, null, null));

		JPanel panelCommand = new JPanel();
		panelCommand.setBorder(new TitledBorder(null, "Command",
				TitledBorder.LEADING, TitledBorder.TOP, null, null));
		GroupLayout groupLayout = new GroupLayout(getContentPane());
		groupLayout
				.setHorizontalGroup(groupLayout
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								groupLayout
										.createSequentialGroup()
										.addContainerGap()
										.addGroup(
												groupLayout
														.createParallelGroup(
																Alignment.LEADING)
														.addGroup(
																Alignment.TRAILING,
																groupLayout
																		.createSequentialGroup()
																		.addComponent(
																				panelCommunicatePara,
																				GroupLayout.PREFERRED_SIZE,
																				448,
																				GroupLayout.PREFERRED_SIZE)
																		.addGap(27)
																		.addGroup(
																				groupLayout
																						.createParallelGroup(
																								Alignment.LEADING)
																						.addComponent(
																								btnDevInfo,
																								GroupLayout.DEFAULT_SIZE,
																								GroupLayout.DEFAULT_SIZE,
																								Short.MAX_VALUE)
																						.addComponent(
																								btnClose,
																								GroupLayout.DEFAULT_SIZE,
																								141,
																								Short.MAX_VALUE)
																						.addComponent(
																								btnOpen,
																								GroupLayout.DEFAULT_SIZE,
																								141,
																								Short.MAX_VALUE))
																		.addGap(80))
														.addGroup(
																Alignment.TRAILING,
																groupLayout
																		.createSequentialGroup()
																		.addGroup(
																				groupLayout
																						.createParallelGroup(
																								Alignment.TRAILING)
																						.addComponent(
																								panelCommand,
																								Alignment.LEADING,
																								GroupLayout.PREFERRED_SIZE,
																								652,
																								Short.MAX_VALUE)
																						.addComponent(
																								panelRecord,
																								GroupLayout.DEFAULT_SIZE,
																								GroupLayout.DEFAULT_SIZE,
																								Short.MAX_VALUE))
																		.addGap(44)))));
		groupLayout
				.setVerticalGroup(groupLayout
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								groupLayout
										.createSequentialGroup()
										.addContainerGap()
										.addGroup(
												groupLayout
														.createParallelGroup(
																Alignment.LEADING)
														.addGroup(
																groupLayout
																		.createSequentialGroup()
																		.addComponent(
																				btnOpen,
																				GroupLayout.PREFERRED_SIZE,
																				31,
																				GroupLayout.PREFERRED_SIZE)
																		.addGap(18)
																		.addComponent(
																				btnClose,
																				GroupLayout.PREFERRED_SIZE,
																				33,
																				GroupLayout.PREFERRED_SIZE)
																		.addGap(18)
																		.addComponent(
																				btnDevInfo,
																				GroupLayout.PREFERRED_SIZE,
																				34,
																				GroupLayout.PREFERRED_SIZE))
														.addComponent(
																panelCommunicatePara,
																GroupLayout.PREFERRED_SIZE,
																143,
																GroupLayout.PREFERRED_SIZE))
										.addGap(18)
										.addComponent(panelRecord,
												GroupLayout.PREFERRED_SIZE,
												193, GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												ComponentPlacement.UNRELATED)
										.addComponent(panelCommand,
												GroupLayout.PREFERRED_SIZE,
												275, GroupLayout.PREFERRED_SIZE)
										.addContainerGap(19, Short.MAX_VALUE)));
		btnOpen.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				OpenDev();
			}
		});
		btnClose.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				if (m_hr == 0)
				{
					return;
				}
				if (MainFrm.this.b_isGetReportRun)
				{
					JOptionPane.showMessageDialog(null,
							"Please stop getting reports first!");
					return;
				}
				rfidlib_reader.RDR_Close(m_hr);
				m_hr = 0;
				AllCtrEnable(false);

			}
		});
		btnDevInfo.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int iret = 0;
				char[] buffer = new char[128];
				Integer nSize = new Integer(0);
				iret = rfidlib_reader.RDR_GetReaderInfor(m_hr, (byte) 0,
						buffer, nSize);
				if (iret == 0)
				{
					JOptionPane.showMessageDialog(null,
							String.valueOf(buffer, 0, nSize));
				}
				else
				{
					String str = "Get device information failed!err = " + iret;
					JOptionPane.showMessageDialog(null, str);
				}
			}
		});

		JPanel panelWarningPorts = new JPanel();
		panelWarningPorts.setBorder(new TitledBorder(UIManager
				.getBorder("TitledBorder.border"), "Warning Ports",
				TitledBorder.LEADING, TitledBorder.TOP, null, new Color(0, 70,
						213)));

		JLabel lblNote = new JLabel(
				"Note:Pause duration will be Effective only when number >1");
		JLabel lblActiveTime = new JLabel("Active time(100ms):");
		JLabel lblFrequency = new JLabel("Frequency:");
		JLabel lblStopTime = new JLabel("Stop time(100ms):");

		GroupLayout gl_panelCommand = new GroupLayout(panelCommand);
		gl_panelCommand
				.setHorizontalGroup(gl_panelCommand
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								Alignment.TRAILING,
								gl_panelCommand
										.createSequentialGroup()
										.addGap(31)
										.addComponent(panelWarningPorts,
												GroupLayout.PREFERRED_SIZE,
												168, GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												ComponentPlacement.RELATED, 41,
												Short.MAX_VALUE)
										.addGroup(
												gl_panelCommand
														.createParallelGroup(
																Alignment.LEADING)
														.addComponent(lblNote)
														.addGroup(
																gl_panelCommand
																		.createSequentialGroup()
																		.addGroup(
																				gl_panelCommand
																						.createParallelGroup(
																								Alignment.TRAILING)
																						.addComponent(
																								lblStopTime)
																						.addComponent(
																								lblFrequency)
																						.addComponent(
																								lblActiveTime))
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addGroup(
																				gl_panelCommand
																						.createParallelGroup(
																								Alignment.LEADING,
																								false)
																						.addComponent(
																								cmbStopTime,
																								0,
																								GroupLayout.DEFAULT_SIZE,
																								Short.MAX_VALUE)
																						.addComponent(
																								cmbFrequency,
																								0,
																								GroupLayout.DEFAULT_SIZE,
																								Short.MAX_VALUE)
																						.addComponent(
																								cmbActiveTime,
																								0,
																								72,
																								Short.MAX_VALUE))
																		.addGap(55)
																		.addComponent(
																				btnSetOutput,
																				GroupLayout.PREFERRED_SIZE,
																				124,
																				GroupLayout.PREFERRED_SIZE)))
										.addGap(71)));
		gl_panelCommand
				.setVerticalGroup(gl_panelCommand
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panelCommand
										.createSequentialGroup()
										.addGroup(
												gl_panelCommand
														.createParallelGroup(
																Alignment.LEADING)
														.addGroup(
																gl_panelCommand
																		.createSequentialGroup()
																		.addGap(22)
																		.addComponent(
																				lblNote)
																		.addGap(18)
																		.addGroup(
																				gl_panelCommand
																						.createParallelGroup(
																								Alignment.BASELINE)
																						.addComponent(
																								lblActiveTime)
																						.addComponent(
																								cmbActiveTime,
																								GroupLayout.PREFERRED_SIZE,
																								GroupLayout.DEFAULT_SIZE,
																								GroupLayout.PREFERRED_SIZE))
																		.addGap(18)
																		.addGroup(
																				gl_panelCommand
																						.createParallelGroup(
																								Alignment.BASELINE)
																						.addComponent(
																								lblFrequency)
																						.addComponent(
																								cmbFrequency,
																								GroupLayout.PREFERRED_SIZE,
																								GroupLayout.DEFAULT_SIZE,
																								GroupLayout.PREFERRED_SIZE)
																						.addComponent(
																								btnSetOutput,
																								GroupLayout.PREFERRED_SIZE,
																								47,
																								GroupLayout.PREFERRED_SIZE))
																		.addGap(18)
																		.addGroup(
																				gl_panelCommand
																						.createParallelGroup(
																								Alignment.BASELINE)
																						.addComponent(
																								lblStopTime)
																						.addComponent(
																								cmbStopTime,
																								GroupLayout.PREFERRED_SIZE,
																								GroupLayout.DEFAULT_SIZE,
																								GroupLayout.PREFERRED_SIZE)))
														.addGroup(
																gl_panelCommand
																		.createSequentialGroup()
																		.addContainerGap()
																		.addComponent(
																				panelWarningPorts,
																				GroupLayout.PREFERRED_SIZE,
																				216,
																				GroupLayout.PREFERRED_SIZE)))
										.addContainerGap(24, Short.MAX_VALUE)));
		btnSetOutput.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				long dnOutputOper = rfidlib_reader
						.RDR_CreateSetOutputOperations();
				if (dnOutputOper == 0)
				{
					return;
				}
				int nret = 0;
				boolean b_sel = false;
				int outFrequency = cmbFrequency.getSelectedIndex() + 1;
				int outActiveDuration = (cmbActiveTime.getSelectedIndex() + 1) * 100;
				int outInactiveDuration = (cmbStopTime.getSelectedIndex() + 1) * 100;
				if (checkBuzzer.isSelected())
				{
					rfidlib_reader.RDR_AddOneOutputOperation(dnOutputOper,
							(byte) 1, (byte) 3, outFrequency,
							outActiveDuration, outInactiveDuration);
					b_sel = true;
				}
				if (checkOutput_1.isSelected())
				{
					rfidlib_reader.RDR_AddOneOutputOperation(dnOutputOper,
							(byte) 2, (byte) 3, outFrequency,
							outActiveDuration, outInactiveDuration);
					b_sel = true;
				}
				if (checkOutput_2.isSelected())
				{
					rfidlib_reader.RDR_AddOneOutputOperation(dnOutputOper,
							(byte) 3, (byte) 3, outFrequency,
							outActiveDuration, outInactiveDuration);
					b_sel = true;
				}
				if (checkOutput_3.isSelected())
				{
					rfidlib_reader.RDR_AddOneOutputOperation(dnOutputOper,
							(byte) 4, (byte) 3, outFrequency,
							outActiveDuration, outInactiveDuration);
					b_sel = true;
				}
				if (checkOutput_4.isSelected())
				{
					rfidlib_reader.RDR_AddOneOutputOperation(dnOutputOper,
							(byte) 5, (byte) 3, outFrequency,
							outActiveDuration, outInactiveDuration);
					b_sel = true;
				}

				if (b_sel)
				{
					nret = rfidlib_reader.RDR_SetOutput(m_hr, dnOutputOper);
				}
				rfidlib_reader.DNODE_Destroy(dnOutputOper);
				if (nret == 0)
				{
					JOptionPane.showMessageDialog(null, "Success");
				}
				else
				{
					String sRet = "Failed,error:" + nret;
					JOptionPane.showMessageDialog(null, sRet);
				}
			}
		});

		GroupLayout gl_panelWarningPorts = new GroupLayout(panelWarningPorts);
		gl_panelWarningPorts.setHorizontalGroup(gl_panelWarningPorts
				.createParallelGroup(Alignment.LEADING).addGroup(
						gl_panelWarningPorts
								.createSequentialGroup()
								.addGap(17)
								.addGroup(
										gl_panelWarningPorts
												.createParallelGroup(
														Alignment.LEADING)
												.addComponent(checkOutput_4)
												.addComponent(checkOutput_3)
												.addComponent(checkOutput_2)
												.addComponent(checkOutput_1)
												.addComponent(checkBuzzer))
								.addContainerGap(20, Short.MAX_VALUE)));
		gl_panelWarningPorts.setVerticalGroup(gl_panelWarningPorts
				.createParallelGroup(Alignment.LEADING).addGroup(
						gl_panelWarningPorts.createSequentialGroup()
								.addContainerGap().addComponent(checkBuzzer)
								.addPreferredGap(ComponentPlacement.UNRELATED)
								.addComponent(checkOutput_1)
								.addPreferredGap(ComponentPlacement.UNRELATED)
								.addComponent(checkOutput_2)
								.addPreferredGap(ComponentPlacement.UNRELATED)
								.addComponent(checkOutput_3)
								.addPreferredGap(ComponentPlacement.UNRELATED)
								.addComponent(checkOutput_4)
								.addContainerGap(14, Short.MAX_VALUE)));
		panelWarningPorts.setLayout(gl_panelWarningPorts);
		panelCommand.setLayout(gl_panelCommand);

		// tableRecord = new JTable();

		GroupLayout gl_panelRecord = new GroupLayout(panelRecord);
		gl_panelRecord.setHorizontalGroup(gl_panelRecord.createParallelGroup(
				Alignment.LEADING).addGroup(
				gl_panelRecord
						.createSequentialGroup()
						.addContainerGap()
						.addComponent(tableRecord, GroupLayout.PREFERRED_SIZE,
								431, GroupLayout.PREFERRED_SIZE)
						.addGap(45)
						.addGroup(
								gl_panelRecord
										.createParallelGroup(Alignment.LEADING,
												false)
										.addComponent(btnClear,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.DEFAULT_SIZE,
												Short.MAX_VALUE)
										.addComponent(btnStop,
												GroupLayout.DEFAULT_SIZE,
												GroupLayout.DEFAULT_SIZE,
												Short.MAX_VALUE)
										.addComponent(btnStart,
												GroupLayout.DEFAULT_SIZE, 98,
												Short.MAX_VALUE))
						.addContainerGap(52, Short.MAX_VALUE)));
		btnStart.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{

				MainFrm.this.btnStart.setEnabled(false);
				MainFrm.this.btnStop.setEnabled(true);
				MainFrm.this.btnClear.setEnabled(false);
				b_isGetReportRun = true;
				vRowData.clear();
				TableModel.setDataVector(vRowData, vTitile);

				Thread m_thread = new Thread(MainFrm.this);
				m_thread.start();
			}
		});
		btnStop.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				MainFrm.this.btnStop.setEnabled(false);
				bThreadRunFlg = false;
				// rfidlib_Gxxx.MGXXX_StopLoopCollectingBegin(m_hr);
			}
		});
		btnClear.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				vRowData.clear();
				TableModel.setDataVector(vRowData, vTitile);
			}
		});
		gl_panelRecord
				.setVerticalGroup(gl_panelRecord
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panelRecord
										.createSequentialGroup()
										.addGroup(
												gl_panelRecord
														.createParallelGroup(
																Alignment.LEADING)
														.addGroup(
																gl_panelRecord
																		.createSequentialGroup()
																		.addContainerGap()
																		.addComponent(
																				tableRecord,
																				GroupLayout.DEFAULT_SIZE,
																				148,
																				Short.MAX_VALUE))
														.addGroup(
																gl_panelRecord
																		.createSequentialGroup()
																		.addGap(26)
																		.addComponent(
																				btnStart,
																				GroupLayout.PREFERRED_SIZE,
																				32,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.UNRELATED)
																		.addComponent(
																				btnStop,
																				GroupLayout.PREFERRED_SIZE,
																				33,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.UNRELATED)
																		.addComponent(
																				btnClear,
																				GroupLayout.PREFERRED_SIZE,
																				31,
																				GroupLayout.PREFERRED_SIZE)))
										.addContainerGap()));
		panelRecord.setLayout(gl_panelRecord);
		JLabel lblCommunicateType = new JLabel("Communicate type:");
		JLabel lblDeviceType = new JLabel("Device type:");
		JPanel panelPortPara = new JPanel();
		panelPortPara.setBorder(new TitledBorder(UIManager
				.getBorder("TitledBorder.border"), "Serial port parameters",
				TitledBorder.LEADING, TitledBorder.TOP, null, Color.BLACK));
		JPanel panelNetPara = new JPanel();
		panelNetPara.setBorder(new TitledBorder(null, "Network parameters",
				TitledBorder.LEADING, TitledBorder.TOP, null, null));
		GroupLayout gl_panelCommunicatePara = new GroupLayout(
				panelCommunicatePara);
		gl_panelCommunicatePara
				.setHorizontalGroup(gl_panelCommunicatePara
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panelCommunicatePara
										.createSequentialGroup()
										.addGap(27)
										.addGroup(
												gl_panelCommunicatePara
														.createParallelGroup(
																Alignment.LEADING)
														.addGroup(
																gl_panelCommunicatePara
																		.createSequentialGroup()
																		.addComponent(
																				panelPortPara,
																				GroupLayout.PREFERRED_SIZE,
																				187,
																				GroupLayout.PREFERRED_SIZE)
																		.addGap(18)
																		.addComponent(
																				panelNetPara,
																				GroupLayout.DEFAULT_SIZE,
																				198,
																				Short.MAX_VALUE))
														.addGroup(
																gl_panelCommunicatePara
																		.createSequentialGroup()
																		.addComponent(
																				lblDeviceType)
																		.addGap(4)
																		.addComponent(
																				cmbDevType,
																				GroupLayout.PREFERRED_SIZE,
																				79,
																				GroupLayout.PREFERRED_SIZE)
																		.addGap(38)
																		.addComponent(
																				lblCommunicateType)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				cmbCommunicateType,
																				GroupLayout.PREFERRED_SIZE,
																				91,
																				GroupLayout.PREFERRED_SIZE)))
										.addContainerGap()));
		gl_panelCommunicatePara
				.setVerticalGroup(gl_panelCommunicatePara
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panelCommunicatePara
										.createSequentialGroup()
										.addContainerGap()
										.addGroup(
												gl_panelCommunicatePara
														.createParallelGroup(
																Alignment.LEADING)
														.addGroup(
																gl_panelCommunicatePara
																		.createSequentialGroup()
																		.addGap(3)
																		.addComponent(
																				lblDeviceType))
														.addComponent(
																cmbDevType,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE)
														.addGroup(
																gl_panelCommunicatePara
																		.createSequentialGroup()
																		.addGap(3)
																		.addGroup(
																				gl_panelCommunicatePara
																						.createParallelGroup(
																								Alignment.BASELINE)
																						.addComponent(
																								lblCommunicateType)
																						.addComponent(
																								cmbCommunicateType,
																								GroupLayout.PREFERRED_SIZE,
																								GroupLayout.DEFAULT_SIZE,
																								GroupLayout.PREFERRED_SIZE))))
										.addGap(18)
										.addGroup(
												gl_panelCommunicatePara
														.createParallelGroup(
																Alignment.BASELINE)
														.addComponent(
																panelPortPara,
																GroupLayout.PREFERRED_SIZE,
																73,
																GroupLayout.PREFERRED_SIZE)
														.addComponent(
																panelNetPara,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE))
										.addContainerGap(21, Short.MAX_VALUE)));

		JLabel lblIpAddr = new JLabel("IP:");

		// textIpAddr = new JTextField();
		textIpAddr.setText("192.168.1.224");
		textIpAddr.setColumns(10);
		GroupLayout gl_panelNetPara = new GroupLayout(panelNetPara);
		gl_panelNetPara.setHorizontalGroup(gl_panelNetPara.createParallelGroup(
				Alignment.LEADING).addGroup(
				gl_panelNetPara
						.createSequentialGroup()
						.addContainerGap()
						.addComponent(lblIpAddr)
						.addPreferredGap(ComponentPlacement.RELATED)
						.addComponent(textIpAddr, GroupLayout.DEFAULT_SIZE,
								140, Short.MAX_VALUE).addContainerGap()));
		gl_panelNetPara
				.setVerticalGroup(gl_panelNetPara
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panelNetPara
										.createSequentialGroup()
										.addContainerGap()
										.addGroup(
												gl_panelNetPara
														.createParallelGroup(
																Alignment.BASELINE)
														.addComponent(lblIpAddr)
														.addComponent(
																textIpAddr,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE))
										.addContainerGap(12, Short.MAX_VALUE)));
		panelNetPara.setLayout(gl_panelNetPara);

		JLabel lblComName = new JLabel("COM:");
		GroupLayout gl_panelPortPara = new GroupLayout(panelPortPara);
		gl_panelPortPara.setHorizontalGroup(gl_panelPortPara
				.createParallelGroup(Alignment.LEADING).addGroup(
						gl_panelPortPara
								.createSequentialGroup()
								.addContainerGap()
								.addComponent(lblComName)
								.addPreferredGap(ComponentPlacement.UNRELATED)
								.addComponent(cmbComName,
										GroupLayout.PREFERRED_SIZE, 97,
										GroupLayout.PREFERRED_SIZE)
								.addContainerGap(30, Short.MAX_VALUE)));
		gl_panelPortPara
				.setVerticalGroup(gl_panelPortPara
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panelPortPara
										.createSequentialGroup()
										.addContainerGap()
										.addGroup(
												gl_panelPortPara
														.createParallelGroup(
																Alignment.BASELINE)
														.addComponent(
																lblComName)
														.addComponent(
																cmbComName,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE))
										.addContainerGap(30, Short.MAX_VALUE)));
		panelPortPara.setLayout(gl_panelPortPara);
		panelCommunicatePara.setLayout(gl_panelCommunicatePara);
		getContentPane().setLayout(groupLayout);

		cmbCommunicateType.addItem("COM");
		cmbCommunicateType.addItem("Netword");
		cmbCommunicateType.setSelectedIndex(1);

		checkBuzzer.setSelected(true);
		checkOutput_1.setSelected(true);
		checkOutput_2.setSelected(true);
		checkOutput_3.setSelected(true);
		checkOutput_4.setSelected(true);

		for (int i = 1; i <= 255; i++)
		{
			cmbActiveTime.addItem(i + "");
			cmbFrequency.addItem(i + "");
			cmbStopTime.addItem(i + "");
		}
		cmbActiveTime.setSelectedIndex(0);
		cmbFrequency.setSelectedIndex(0);
		cmbStopTime.setSelectedIndex(0);

		vTitile.addElement("Serial Number");
		vTitile.addElement("Direction");
		vTitile.addElement("Instead state");

		TableModel.setDataVector(vRowData, vTitile);
		tableRecord.setModel(TableModel);

		LoadLibrary();
		ListAllCom();
		AllCtrEnable(false);

		this.setVisible(true);
		this.setSize(700, 700);
		this.setLocation(250, 100);
		this.setResizable(false);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
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
		int m_cnt = rfidlib_reader.RDR_GetLoadedReaderDriverCount();
		int nret = 0;
		for (int i = 0; i < m_cnt; i++)
		{
			char[] valueBuffer = new char[128];
			Integer nSize = new Integer(0);
			nret = rfidlib_reader.RDR_GetLoadedReaderDriverOpt(i,
					rfid_def.LOADED_RDRDVR_OPT_NAME, valueBuffer, nSize);
			if (nret == 0)
			{
				cmbDevType.addItem(String.valueOf(valueBuffer, 0, nSize));
			}
		}
		if (m_cnt > 0)
		{
			cmbDevType.setSelectedIndex(m_cnt - 1);
		}
	}
	
	

	private void ListAllCom()
	{
		int m_cnt = rfidlib_reader.COMPort_Enum();
		for (int i = 0; i < m_cnt; i++)
		{
			char[] buffer = new char[128];
			Integer nSize = new Integer(0);
			rfidlib_reader.COMPort_GetEnumItem(i, buffer, nSize);
			cmbComName.addItem(String.valueOf(buffer, 0, nSize));
		}
		if (m_cnt > 0)
		{
			cmbComName.setSelectedIndex(0);
		}
	}

	private void AllCtrEnable(boolean isOpen)
	{
		cmbDevType.setEnabled(!isOpen);
		cmbCommunicateType.setEnabled(!isOpen);
		cmbComName.setEnabled(!isOpen);
		textIpAddr.setEnabled(!isOpen);
		btnOpen.setEnabled(!isOpen);
		btnClose.setEnabled(isOpen);
		btnDevInfo.setEnabled(isOpen);
		btnStart.setEnabled(isOpen);
		btnStop.setEnabled(isOpen);
		btnClear.setEnabled(isOpen);
		checkBuzzer.setEnabled(isOpen);
		checkOutput_1.setEnabled(isOpen);
		checkOutput_2.setEnabled(isOpen);
		checkOutput_3.setEnabled(isOpen);
		checkOutput_4.setEnabled(isOpen);
		cmbActiveTime.setEnabled(isOpen);
		cmbFrequency.setEnabled(isOpen);
		cmbStopTime.setEnabled(isOpen);
		btnSetOutput.setEnabled(isOpen);
	}

	private void OpenDev()
	{
		String connstr = null;
		String sDevName = cmbDevType.getItemAt(cmbDevType.getSelectedIndex())
				.toString();
		int idx = cmbCommunicateType.getSelectedIndex();
		switch (idx)
		{
		case 0:
			String comNameString = cmbComName.getItemAt(
					cmbComName.getSelectedIndex()).toString();// ();
			connstr = rfid_def.CONNSTR_NAME_RDTYPE + "=" + sDevName + ";"
					+ rfid_def.CONNSTR_NAME_COMMTYPE + "="
					+ rfid_def.CONNSTR_NAME_COMMTYPE_COM + ";"
					+ rfid_def.CONNSTR_NAME_COMNAME + "=" + comNameString + ";"
					+ rfid_def.CONNSTR_NAME_COMBARUD + "=" + "38400" + ";"
					+ rfid_def.CONNSTR_NAME_COMFRAME + "=" + "8E1" + ";"
					+ rfid_def.CONNSTR_NAME_BUSADDR + "=" + "255";
			break;
		case 1:
			connstr = rfid_def.CONNSTR_NAME_RDTYPE + "=" + sDevName + ";"
					+ rfid_def.CONNSTR_NAME_COMMTYPE + "="
					+ rfid_def.CONNSTR_NAME_COMMTYPE_NET + ";"
					+ rfid_def.CONNSTR_NAME_REMOTEIP + "="
					+ textIpAddr.getText() + ";"
					+ rfid_def.CONNSTR_NAME_REMOTEPORT + "=" + 6012 + ";"
					+ rfid_def.CONNSTR_NAME_LOCALIP + "=" + "";
			break;
		default:
			break;
		}
		Long hrOut = new Long(0);
		int nret = rfidlib_reader.RDR_Open(connstr, hrOut);
		if (nret != 0)
		{
			String sRet = "Open device failed!err=" + nret;
			JOptionPane.showMessageDialog(null, sRet);
			return;
		}
		m_hr = hrOut;
		AllCtrEnable(true);
		this.btnStop.setEnabled(false);
	}

	public static void main(String[] args)
	{
		new MainFrm();
	}

	public void run()
	{
		// TODO Auto-generated method stub
		bThreadRunFlg = true;
		int flag = 0;
		while (bThreadRunFlg)
		{
			int iret = rfidlib_reader.RDR_BuffMode_FetchRecords(m_hr, flag);
			if (iret != 0)
			{
				flag = 0;
				continue;
			}
			flag = 1;

			long dnhReport = 0;
			dnhReport = rfidlib_reader.RDR_GetTagDataReport(m_hr,
					rfid_def.RFID_SEEK_FIRST);
			while (dnhReport != 0)
			{
				byte[] reportBuffer = new byte[128];
				Integer nSize = new Integer(reportBuffer.length);
				iret = rfidlib_reader.RDR_ParseTagDataReportRaw(dnhReport,
						reportBuffer, nSize);
				if (iret == 0)
				{
					if (nSize < 9)
					{
						dnhReport = rfidlib_reader.RDR_GetTagDataReport(m_hr,
								rfid_def.RFID_SEEK_NEXT);
						continue;
					}
					byte eventType;
					byte direction;
					byte[] time = new byte[6];
					byte dataLen = 0;

					eventType = reportBuffer[0];
					direction = reportBuffer[1];
					for (int i = 0; i < 6; i++)
					{
						time[i] = reportBuffer[2 + i];
					}
					dataLen = reportBuffer[8];

					nSize -= 9;
					if (nSize < dataLen)
					{
						dnhReport = rfidlib_reader.RDR_GetTagDataReport(m_hr,
								rfid_def.RFID_SEEK_NEXT);
						continue;
					}

					byte data[] = new byte[dataLen];
					System.arraycopy(reportBuffer, 9, data, 0, dataLen);
					String strData = gFunction.encodeHexStr(data);
					String insteadsta = "";
					byte insteedCheckingFlag = (byte) (direction >> 7 & 0x01);
					if (insteedCheckingFlag > 0)
					{
						insteadsta = "Yes";
					}
					direction = (byte) (direction & 0x7F);
					String strdir = "Wrong direction";
					switch (direction)
					{
					case 0:
						strdir = "NULL";
						break;
					case 1:
						strdir = "In";
						break;
					case 2:
						strdir = "Out";
						break;
					}
					
					AddNewReport(strData, strdir, insteadsta);
				}
				dnhReport = rfidlib_reader.RDR_GetTagDataReport(m_hr,
						rfid_def.RFID_SEEK_NEXT);
			}
		}
		this.btnStart.setEnabled(true);
		this.btnStop.setEnabled(false);
		this.btnClear.setEnabled(true);
		this.b_isGetReportRun = false;
	}


	// 增加一条记录
	private void AddNewReport(String sUid, String sDir, String sInsteadsta)
	{
		System.out.println("Add a new record!");
		Vector<String> vectorRow = new Vector<String>();
		vectorRow.addElement(new String(sUid));
		vectorRow.addElement(new String(sDir));
		vectorRow.addElement(new String(sInsteadsta));
		vRowData.addElement(vectorRow);
		TableModel.setDataVector(vRowData, vTitile);
		tableRecord.setModel(TableModel);
	}
}
