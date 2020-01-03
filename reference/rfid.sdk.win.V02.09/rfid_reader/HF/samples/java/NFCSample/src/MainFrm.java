import java.awt.Dimension;
import java.awt.Toolkit;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JComboBox;
import javax.swing.JButton;
import javax.swing.GroupLayout;
import javax.swing.JOptionPane;
import javax.swing.GroupLayout.Alignment;
import javax.swing.JPanel;
import javax.swing.border.LineBorder;

import java.awt.Color;

import javax.swing.LayoutStyle.ComponentPlacement;
import javax.swing.SwingConstants;
import javax.swing.JTextField;

import RFID.rfid_def;
import RFID.rfidlib_AIP_ISO15693;
import RFID.rfidlib_aip_iso14443A;
import RFID.rfidlib_nfc;
import RFID.rfidlib_reader;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.HashMap;
import java.util.Map;

import javax.swing.JCheckBox;

public class MainFrm extends JFrame
{
	private static final long serialVersionUID = 1L;
	private JTextField textFieldPort;
	private JTextField textFieldIP;
	private JTextField textFieldURL;

	private JComboBox<String> comboBoxReader = new JComboBox<String>();
	private JComboBox<String> comboBoxCommType = new JComboBox<String>();
	private JComboBox<String> comboBoxUID = new JComboBox<String>();
	private JComboBox<String> comboBoxCOM = new JComboBox<String>();
	private JComboBox<String> comboBoxBaud = new JComboBox<String>();
	private JComboBox<String> comboBoxFrame = new JComboBox<String>();
	private JButton btnOpen = new JButton("Open");
	private JButton btnClose = new JButton("Close");
	private JButton btnReadURL = new JButton("Read");
	private JButton btnWriteURL = new JButton("Write");
	private JButton btnInventory = new JButton("Inventory");
	private JButton btnConnect = new JButton("Connect");
	private JButton btnDisconnect = new JButton("Diconnect");
	private JCheckBox chckbxLock = new JCheckBox("Lock");

	private long m_hr = 0;// the reader handle
	private long m_tag = 0;//the tag handle

	private Map<String, Integer> mUidAip = new HashMap<String, Integer>();
	

	public MainFrm()
	{
		setResizable(false);
		setTitle("NFC DEMO");
		LoadLibrary();
		this.setTitle("NFC DEMO");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(650, 400);
		Dimension displaySize = Toolkit.getDefaultToolkit().getScreenSize();
		Dimension frameSize = getSize();
		if (frameSize.width > displaySize.width)
			frameSize.width = displaySize.width;
		setLocation((displaySize.width - frameSize.width) / 2,
				(displaySize.height - frameSize.height) / 2);

		JLabel lblReader = new JLabel("Reader:");
		lblReader.setHorizontalAlignment(SwingConstants.RIGHT);

		JLabel lblCommType = new JLabel("Type:");
		lblCommType.setHorizontalAlignment(SwingConstants.RIGHT);

		JPanel panel = new JPanel();
		panel.setBorder(new LineBorder(new Color(0, 0, 0)));

		JPanel panel_1 = new JPanel();
		panel_1.setBorder(new LineBorder(new Color(0, 0, 0)));

		JPanel panel_2 = new JPanel();
		panel_2.setBorder(new LineBorder(new Color(0, 0, 0)));
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
																groupLayout
																		.createSequentialGroup()
																		.addComponent(
																				panel_2,
																				GroupLayout.DEFAULT_SIZE,
																				624,
																				Short.MAX_VALUE)
																		.addContainerGap())
														.addGroup(
																groupLayout
																		.createSequentialGroup()
																		.addComponent(
																				lblReader,
																				GroupLayout.PREFERRED_SIZE,
																				54,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.UNRELATED)
																		.addGroup(
																				groupLayout
																						.createParallelGroup(
																								Alignment.LEADING)
																						.addGroup(
																								groupLayout
																										.createSequentialGroup()
																										.addGap(10)
																										.addComponent(
																												panel,
																												GroupLayout.PREFERRED_SIZE,
																												157,
																												GroupLayout.PREFERRED_SIZE))
																						.addGroup(
																								groupLayout
																										.createSequentialGroup()
																										.addComponent(
																												comboBoxReader,
																												GroupLayout.PREFERRED_SIZE,
																												93,
																												GroupLayout.PREFERRED_SIZE)
																										.addPreferredGap(
																												ComponentPlacement.RELATED,
																												66,
																												Short.MAX_VALUE)
																										.addComponent(
																												lblCommType,
																												GroupLayout.PREFERRED_SIZE,
																												54,
																												GroupLayout.PREFERRED_SIZE)))
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addGroup(
																				groupLayout
																						.createParallelGroup(
																								Alignment.LEADING)
																						.addGroup(
																								groupLayout
																										.createSequentialGroup()
																										.addComponent(
																												comboBoxCommType,
																												GroupLayout.PREFERRED_SIZE,
																												73,
																												GroupLayout.PREFERRED_SIZE)
																										.addGap(43)
																										.addComponent(
																												btnOpen,
																												GroupLayout.PREFERRED_SIZE,
																												93,
																												GroupLayout.PREFERRED_SIZE)
																										.addGap(33)
																										.addComponent(
																												btnClose,
																												GroupLayout.PREFERRED_SIZE,
																												93,
																												GroupLayout.PREFERRED_SIZE))
																						.addGroup(
																								groupLayout
																										.createSequentialGroup()
																										.addGap(92)
																										.addComponent(
																												panel_1,
																												GroupLayout.PREFERRED_SIZE,
																												217,
																												GroupLayout.PREFERRED_SIZE)))
																		.addGap(18)))));
		groupLayout
				.setVerticalGroup(groupLayout
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								groupLayout
										.createSequentialGroup()
										.addGap(7)
										.addGroup(
												groupLayout
														.createParallelGroup(
																Alignment.LEADING)
														.addGroup(
																groupLayout
																		.createParallelGroup(
																				Alignment.BASELINE)
																		.addComponent(
																				comboBoxReader,
																				GroupLayout.PREFERRED_SIZE,
																				GroupLayout.DEFAULT_SIZE,
																				GroupLayout.PREFERRED_SIZE)
																		.addComponent(
																				lblReader))
														.addGroup(
																groupLayout
																		.createParallelGroup(
																				Alignment.BASELINE)
																		.addComponent(
																				lblCommType)
																		.addComponent(
																				comboBoxCommType,
																				GroupLayout.PREFERRED_SIZE,
																				GroupLayout.DEFAULT_SIZE,
																				GroupLayout.PREFERRED_SIZE)
																		.addComponent(
																				btnOpen)
																		.addComponent(
																				btnClose)))
										.addPreferredGap(
												ComponentPlacement.UNRELATED)
										.addGroup(
												groupLayout
														.createParallelGroup(
																Alignment.LEADING)
														.addComponent(
																panel_1,
																GroupLayout.DEFAULT_SIZE,
																109,
																Short.MAX_VALUE)
														.addComponent(
																panel,
																GroupLayout.PREFERRED_SIZE,
																109,
																GroupLayout.PREFERRED_SIZE))
										.addGap(32)
										.addComponent(panel_2,
												GroupLayout.PREFERRED_SIZE,
												180, GroupLayout.PREFERRED_SIZE)
										.addContainerGap()));
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
				Close();
			}
		});
		panel_2.setLayout(null);

		JLabel lblUID = new JLabel("UID:");
		lblUID.setHorizontalAlignment(SwingConstants.RIGHT);
		lblUID.setBounds(10, 24, 33, 15);
		panel_2.add(lblUID);

		comboBoxUID.setBounds(53, 21, 158, 21);
		panel_2.add(comboBoxUID);
		btnInventory.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				Inventory();
			}
		});

		btnInventory.setBounds(253, 20, 93, 23);
		panel_2.add(btnInventory);
		btnConnect.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				Connect();
			}
		});

		btnConnect.setBounds(378, 20, 93, 23);
		panel_2.add(btnConnect);
		btnDisconnect.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				Disconnect();
			}
		});

		btnDisconnect.setBounds(499, 20, 93, 23);
		panel_2.add(btnDisconnect);

		JLabel lblURL = new JLabel("URL:");
		lblURL.setHorizontalAlignment(SwingConstants.RIGHT);
		lblURL.setBounds(10, 65, 33, 15);
		panel_2.add(lblURL);

		textFieldURL = new JTextField();
		textFieldURL.setText("https://www.baidu.com/");
		textFieldURL.setBounds(53, 62, 372, 21);
		panel_2.add(textFieldURL);
		textFieldURL.setColumns(10);
		btnReadURL.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				ReadURL();
			}
		});

		btnReadURL.setBounds(145, 132, 93, 23);
		panel_2.add(btnReadURL);
		btnWriteURL.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				WriteUrl();
			}
		});

		btnWriteURL.setBounds(411, 132, 93, 23);
		panel_2.add(btnWriteURL);
		panel_1.setLayout(null);

		chckbxLock.setBounds(449, 61, 103, 23);
		panel_2.add(chckbxLock);

		JLabel lblIp = new JLabel("IP:");
		lblIp.setHorizontalAlignment(SwingConstants.RIGHT);
		lblIp.setBounds(10, 33, 18, 15);
		panel_1.add(lblIp);

		JLabel lblPort = new JLabel("Port:");
		lblPort.setBounds(10, 61, 54, 15);
		panel_1.add(lblPort);

		textFieldPort = new JTextField();
		textFieldPort.setHorizontalAlignment(SwingConstants.LEFT);
		textFieldPort.setBounds(43, 58, 145, 21);
		panel_1.add(textFieldPort);
		textFieldPort.setColumns(10);

		textFieldIP = new JTextField();
		textFieldIP.setHorizontalAlignment(SwingConstants.LEFT);
		textFieldIP.setBounds(43, 30, 145, 21);
		panel_1.add(textFieldIP);
		textFieldIP.setColumns(10);
		panel.setLayout(null);

		JLabel lblNewLabel = new JLabel("COM:");
		lblNewLabel.setBounds(3, 12, 41, 15);
		lblNewLabel.setHorizontalAlignment(SwingConstants.RIGHT);
		panel.add(lblNewLabel);

		comboBoxCOM.setBounds(54, 9, 80, 21);
		panel.add(comboBoxCOM);

		JLabel lblBaud = new JLabel("Baud:");
		lblBaud.setHorizontalAlignment(SwingConstants.RIGHT);
		lblBaud.setBounds(-10, 43, 54, 15);
		panel.add(lblBaud);

		comboBoxBaud.setBounds(54, 40, 80, 21);
		panel.add(comboBoxBaud);

		JLabel lblFrame = new JLabel("Frame:");
		lblFrame.setHorizontalAlignment(SwingConstants.RIGHT);
		lblFrame.setBounds(-10, 74, 54, 15);
		panel.add(lblFrame);

		comboBoxFrame.setBounds(54, 74, 80, 21);
		panel.add(comboBoxFrame);
		getContentPane().setLayout(groupLayout);
		setVisible(true);

		comboBoxCommType.addItem("USB");
		comboBoxCommType.addItem("COM");
		comboBoxCommType.addItem("NET");
		comboBoxCommType.setSelectedIndex(0);

		int mComCnt = rfidlib_reader.COMPort_Enum();
		for (int i = 0; i < mComCnt; i++)
		{
			char[] nameBuf = new char[128];
			Integer nSize = new Integer(0);
			rfidlib_reader.COMPort_GetEnumItem(i, nameBuf, nSize);
			String comName = String.copyValueOf(nameBuf, 0, nSize);
			comboBoxCOM.addItem(comName);
		}

		comboBoxBaud.addItem("9600");
		comboBoxBaud.addItem("38400");
		comboBoxBaud.addItem("115200");
		comboBoxBaud.setSelectedIndex(1);

		comboBoxFrame.addItem("8N1");
		comboBoxFrame.addItem("8E1");
		comboBoxFrame.addItem("8O1");
		comboBoxFrame.setSelectedIndex(1);

		textFieldIP.setText("192.168.0.222");
		textFieldPort.setText("9909");

		comboBoxReader.setEnabled(true);
		comboBoxCommType.setEnabled(true);
		comboBoxCOM.setEnabled(true);
		comboBoxBaud.setEnabled(true);
		comboBoxFrame.setEnabled(true);
		textFieldIP.setEnabled(true);
		textFieldPort.setEnabled(true);
		comboBoxUID.setEnabled(false);

		btnOpen.setEnabled(true);
		btnClose.setEnabled(false);
		btnReadURL.setEnabled(false);
		btnWriteURL.setEnabled(false);
		btnInventory.setEnabled(false);
		btnConnect.setEnabled(false);
		btnDisconnect.setEnabled(false);
		textFieldURL.setEnabled(false);
		chckbxLock.setEnabled(false);
	}
	
	private void LoadLibrary()
	{
		int osType = 0;
		int arType = 0;
		String libPath = System.getProperty("user.dir");
		String osName = System.getProperty("os.name");
		String architecture = System.getProperty("os.arch");
		if (osName.equals("Linux"))
		{
			osType = rfid_def.VER_LINUX;
		}
		else if (osName.substring(0, 3).equals("Win"))
		{
			osType = rfid_def.VER_WINDOWS;
		}

		if (architecture.equals("i386") || architecture.equals("i686"))
		{
			arType = rfid_def.AR_X86;
		}
		else if (architecture.equals("amd64")
				|| architecture.equals("universal"))
		{
			arType = rfid_def.AR_X64;
		}

		rfidlib_reader.LoadLib(libPath, osType, arType);
		rfidlib_AIP_ISO15693.LoadLib(libPath, osType, arType);
		rfidlib_aip_iso14443A.LoadLib(libPath, osType, arType);
		rfidlib_nfc.LoadLib(libPath, osType, arType);
		
		
		int m_cnt = rfidlib_reader.RDR_GetLoadedReaderDriverCount();
		int nret = 0;
		for (int i = 0; i < m_cnt; i++)
		{
			char[] valueBuffer = new char[256];
			Integer nSize = new Integer(0);
			String sDes;
			nret = rfidlib_reader.RDR_GetLoadedReaderDriverOpt(i,
					rfid_def.LOADED_RDRDVR_OPT_CATALOG, valueBuffer, nSize);
			if (nret == 0)
			{
				sDes = String.copyValueOf(valueBuffer, 0, nSize);
				if (sDes.equals(rfid_def.RDRDVR_TYPE_READER))
				{
					rfidlib_reader
							.RDR_GetLoadedReaderDriverOpt(i,
									rfid_def.LOADED_RDRDVR_OPT_NAME,
									valueBuffer, nSize);
					sDes = String.copyValueOf(valueBuffer, 0, nSize);
					comboBoxReader.addItem(sDes);
				}
			}
		}
		if (m_cnt > 0)
		{
			comboBoxReader.setSelectedIndex(0);
		}
	}


	private void OpenDev()
	{
		String connstr = null;
		String sDevName = comboBoxReader.getItemAt(
				comboBoxReader.getSelectedIndex()).toString();
		int idx = comboBoxCommType.getSelectedIndex();
		switch (idx)
		{
		case 0:

			connstr = rfid_def.CONNSTR_NAME_RDTYPE + "=" + sDevName + ";"
					+ rfid_def.CONNSTR_NAME_COMMTYPE + "="
					+ rfid_def.CONNSTR_NAME_COMMTYPE_USB + ";"
					+ rfid_def.CONNSTR_NAME_HIDADDRMODE + "=" + "0" + ";"
					+ rfid_def.CONNSTR_NAME_HIDSERNUM + "=";
			break;
		case 1:
			String comNameString = comboBoxCOM.getItemAt(
					comboBoxCOM.getSelectedIndex()).toString();// ();
			connstr = rfid_def.CONNSTR_NAME_RDTYPE + "=" + sDevName + ";"
					+ rfid_def.CONNSTR_NAME_COMMTYPE + "="
					+ rfid_def.CONNSTR_NAME_COMMTYPE_COM + ";"
					+ rfid_def.CONNSTR_NAME_COMNAME + "=" + comNameString + ";"
					+ rfid_def.CONNSTR_NAME_COMBARUD + "=" + "38400" + ";"
					+ rfid_def.CONNSTR_NAME_COMFRAME + "=" + "8E1" + ";"
					+ rfid_def.CONNSTR_NAME_BUSADDR + "=" + "255";
			break;
		case 2:
			connstr = rfid_def.CONNSTR_NAME_RDTYPE + "=" + sDevName + ";"
					+ rfid_def.CONNSTR_NAME_COMMTYPE + "="
					+ rfid_def.CONNSTR_NAME_COMMTYPE_NET + ";"
					+ rfid_def.CONNSTR_NAME_REMOTEIP + "="
					+ textFieldIP.getText() + ";"
					+ rfid_def.CONNSTR_NAME_REMOTEPORT + "="
					+ textFieldPort.getText() + ";"
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

		comboBoxReader.setEnabled(false);
		comboBoxCommType.setEnabled(false);
		comboBoxCOM.setEnabled(false);
		comboBoxBaud.setEnabled(false);
		comboBoxFrame.setEnabled(false);
		textFieldIP.setEnabled(false);
		textFieldPort.setEnabled(false);
		comboBoxUID.setEnabled(true);

		btnOpen.setEnabled(false);
		btnClose.setEnabled(true);
		btnReadURL.setEnabled(false);
		btnWriteURL.setEnabled(false);
		btnInventory.setEnabled(true);
		btnConnect.setEnabled(true);
		btnDisconnect.setEnabled(false);
		textFieldURL.setEnabled(false);
		chckbxLock.setEnabled(false);
	}

	private void Close()
	{
		if (m_tag != 0)
		{
			JOptionPane.showMessageDialog(null,
					"Please disconnect the tag first!");
			return;
		}
		if (m_hr != 0)
		{
			rfidlib_reader.RDR_Close(m_hr);
			m_hr = 0;
		}

		comboBoxReader.setEnabled(true);
		comboBoxCommType.setEnabled(true);
		comboBoxCOM.setEnabled(true);
		comboBoxBaud.setEnabled(true);
		comboBoxFrame.setEnabled(true);
		textFieldIP.setEnabled(true);
		textFieldPort.setEnabled(true);
		comboBoxUID.setEnabled(false);

		btnOpen.setEnabled(true);
		btnClose.setEnabled(false);
		btnReadURL.setEnabled(false);
		btnWriteURL.setEnabled(false);
		btnInventory.setEnabled(false);
		btnConnect.setEnabled(false);
		btnDisconnect.setEnabled(false);
		textFieldURL.setEnabled(false);
		chckbxLock.setEnabled(false);
	}

	private void Inventory()
	{
		mUidAip.clear();
		comboBoxUID.removeAllItems();
		long InvenParamSpecList = rfidlib_reader.RDR_CreateInvenParamSpecList();
		rfidlib_AIP_ISO15693.ISO15693_CreateInvenParam(InvenParamSpecList,
				(byte) 0, (byte) 0x00, (byte) 0x00, (byte) 0);
		rfidlib_aip_iso14443A.ISO14443A_CreateInvenParam(InvenParamSpecList,
				(byte) 0x00);
		int nret = rfidlib_reader.RDR_TagInventory(m_hr, rfid_def.AI_TYPE_NEW,
				(byte) 0, null, InvenParamSpecList);
		long dnhReport = rfidlib_reader.RDR_GetTagDataReport(m_hr,
				rfid_def.RFID_SEEK_FIRST);
		while (dnhReport != 0)
		{
			Integer aip_id = new Integer(0);
			Integer tag_id = new Integer(0);
			Integer ant_id = new Integer(0);
			Byte dsfid = new Byte((byte) 0);
			byte[] uid = new byte[32];
			Byte uidlen = new Byte((byte) 0);
			// ISO15693 tag
			nret = rfidlib_AIP_ISO15693.ISO15693_ParseTagDataReport(dnhReport,
					aip_id, tag_id, ant_id, dsfid, uid);
			if (nret == 0)
			{
				String sUid = gFunction.encodeHexStr(uid, 8);
				comboBoxUID.addItem(sUid);
				mUidAip.put(sUid, rfid_def.RFID_APL_ISO15693_ID);
				dnhReport = rfidlib_reader.RDR_GetTagDataReport(m_hr,
						rfid_def.RFID_SEEK_NEXT);
				continue;
			}

			nret = rfidlib_aip_iso14443A.ISO14443A_ParseTagDataReport(
					dnhReport, aip_id, tag_id, ant_id, uid, uidlen); //
			if (nret == 0)
			{
				String sUid = gFunction.encodeHexStr(uid, uidlen);
				comboBoxUID.addItem(sUid);
				mUidAip.put(sUid, rfid_def.RFID_APL_ISO14443A_ID);
				dnhReport = rfidlib_reader.RDR_GetTagDataReport(m_hr,
						rfid_def.RFID_SEEK_NEXT);
				continue;
			}
		}

		if (InvenParamSpecList != 0)
		{
			rfidlib_reader.DNODE_Destroy(InvenParamSpecList);
		}
	}

	private void Connect()
	{
		if (comboBoxUID.getItemCount() <= 0)
		{
			return;
		}
		Long ht = new Long(0);
		byte[] m_uid = null;
		String sUid = comboBoxUID.getItemAt(comboBoxUID.getSelectedIndex());
		m_uid = gFunction.decodeHex(sUid);
		int nret = 0;
		if (mUidAip.get(sUid) == rfid_def.RFID_APL_ISO15693_ID)
		{
			nret = rfidlib_AIP_ISO15693.ISO15693_Connect(m_hr,
					rfid_def.RFID_ISO15693_PICC_ICODE_SLI_ID, (byte) 1, m_uid,
					ht);
		}
		else if (mUidAip.get(sUid) == rfid_def.RFID_APL_ISO14443A_ID)
		{
			nret = rfidlib_aip_iso14443A.NTAG21x_Connect(m_hr, m_uid, ht);// Á¬½ÓNTAG21X±êÇ©
		}
		else
		{
			return;
		}
		if (nret != 0)
		{
			JOptionPane.showMessageDialog(null, "Connect tag failed!err="
					+ nret);
			return;
		}
		m_tag = ht;

		btnReadURL.setEnabled(true);
		btnWriteURL.setEnabled(true);
		btnInventory.setEnabled(false);
		btnConnect.setEnabled(false);
		btnDisconnect.setEnabled(true);
		textFieldURL.setEnabled(true);
		chckbxLock.setEnabled(true);
	}

	private void Disconnect()
	{
		if (m_tag == 0)
		{
			return;
		}

		rfidlib_reader.RDR_TagDisconnect(m_hr, m_tag);
		m_tag = 0;

		btnReadURL.setEnabled(false);
		btnWriteURL.setEnabled(false);
		btnInventory.setEnabled(true);
		btnConnect.setEnabled(true);
		btnDisconnect.setEnabled(false);
		textFieldURL.setEnabled(false);
		chckbxLock.setEnabled(false);
	}

	private void WriteUrl()
	{
		long ndef = rfidlib_nfc.nfc_CreateUriNdef(textFieldURL.getText(),
				(byte) 0x00);
		Byte IsLock = (byte) (chckbxLock.isSelected() ? 1 : 0);
		int nret = rfidlib_nfc.nfc_WriteNdef(m_hr, m_tag, ndef, IsLock);
		if (nret!=0)
		{
			return;
		}
		
		//Destroy NDEF
		rfidlib_reader.DNODE_Destroy(ndef);
		if (nret != 0)
		{
			JOptionPane.showMessageDialog(null, "failed wite the URL.");
		}
		else {
			
			JOptionPane.showMessageDialog(null, "Write the URL successfully.");
		}
	}
	
	private void ReadURL()
	{
		Long ndef = new Long(0);
		Byte ndefType = new Byte((byte) 0);
		int iret = rfidlib_nfc.nfc_ReadNdef(m_hr, m_tag, ndef, ndefType);
		if (iret!=0)
		{
			if (ndef!=0)
			{
				rfidlib_reader.DNODE_Destroy(ndef);
			}
			
			JOptionPane.showMessageDialog(null, "failed read the URL.");
			return;
		}
		
		char urlAddr[] = new char[255];
		Byte netType = new Byte((byte) 0);
		iret = rfidlib_nfc.nfc_ParseNdefByUri(ndef, urlAddr, urlAddr.length, netType);
		
		if (ndef!=0)
		{
			rfidlib_reader.DNODE_Destroy(ndef);
		}
		
		if (iret!=0)
		{
			JOptionPane.showMessageDialog(null, "failed read the URL.");
			return;
		}
		
		String sURL = String.copyValueOf(urlAddr,0,urlAddr.length);
		textFieldURL.setText(sURL);
	}

	public static void main(String[] args)
	{
		new MainFrm();
	}
}
