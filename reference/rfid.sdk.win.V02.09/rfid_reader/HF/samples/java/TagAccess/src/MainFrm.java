import javax.swing.JFrame;
import javax.swing.GroupLayout;
import javax.swing.JOptionPane;
import javax.swing.GroupLayout.Alignment;
import javax.swing.JLabel;
import javax.swing.JComboBox;
import javax.swing.LayoutStyle.ComponentPlacement;

import RFID.*;

import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.border.LineBorder;

import java.awt.Color;

import javax.swing.border.TitledBorder;
import javax.swing.table.DefaultTableModel;
import javax.swing.JTextField;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.util.Vector;

import javax.swing.JTable;
import javax.swing.UIManager;
import javax.swing.JCheckBox;

public class MainFrm extends JFrame implements Runnable
{
	private static final long serialVersionUID = 1L;
	private long m_hr = 0;// ¶Á¿¨Æ÷²Ù×÷¾ä±ú
	private long m_ht = 0;// ±êÇ©²Ù×÷¾ä±ú
	private JComboBox<String> cmbDevType = new JComboBox<String>();
	private JComboBox<String> cmbCommType = new JComboBox<String>();
	private JComboBox<String> cmbComName = new JComboBox<String>();
	private JComboBox<String> cmbAddrMode_iso15693 = new JComboBox<String>();
	private JButton btnGetRfidInfo = new JButton("Get Device Info");
	private JButton btnOpen = new JButton("Open");
	private JButton btnClose = new JButton("Close");
	private JTextField textIP = new JTextField();
	private JTextField textPort = new JTextField();
	private JTable tableInventory = new JTable();
	private JTextField textAFI = new JTextField();
	private JCheckBox checkEnable14443A = new JCheckBox("Enable14443A");
	private JCheckBox checkOnlyNew = new JCheckBox("Only new tag");
	private JCheckBox checkAfiMatch = new JCheckBox("Match AFI");
	private boolean b_inventoryFlg = false;
	private JButton btnStartInventory = new JButton("Start");
	private JButton btnStopInventory = new JButton("Stop");
	private JTextField textBlkData_iso15693 = new JTextField();
	private JTextField textAfiVal = new JTextField();
	private JTextField textDsfidVal = new JTextField();
	private JButton btnWriteDsfid = new JButton("Write DSFID");
	private JButton btnGetTagInfo_iso15693 = new JButton("Get Tag Info");
	private JButton btnEnableEAS = new JButton("Enable EAS");
	private JButton btnDisableEAS = new JButton("Disable EAS");
	private JButton btnEAScheck = new JButton("EAS Check");
	private JButton btnConnect_iso15693 = new JButton("Connect");
	private JButton btnDidconnect = new JButton("Disconnect");
	private JComboBox<String> cmbUid_iso15693 = new JComboBox<String>();
	private JComboBox<String> cmbBlkaddr_iso15693 = new JComboBox<String>();
	private JComboBox<String> cmbBlkNum_iso15693 = new JComboBox<String>();
	private JButton btnReadSigle_iso15693 = new JButton("ReadSingle");
	private JButton btnReadMul_iso15693 = new JButton("ReadMutiple");
	private JButton btnWriteMutiple_iso15693 = new JButton("WriteMutiple");
	private JButton btnGetsecState_iso15693 = new JButton("Get security state");
	private JButton btnWriteAfi = new JButton("Write AFI");
	private JPanel panel14443A = new JPanel();
	private JLabel lblUid_iso14443a = new JLabel("Uid:");
	private JComboBox<String> cmbUid_S50 = new JComboBox<String>();
	private JButton btnConnect_S50 = new JButton("Connect");
	private JButton btnDisconnect_S50 = new JButton("Disconnect");
	private JLabel lblBlkaddr_S50 = new JLabel("Block address:");
	private JComboBox<String> cmbBlkaddr_S50 = new JComboBox<String>();
	private JLabel lblKeyType = new JLabel("Key Type:");
	private JComboBox<String> cmbKeyType_S50 = new JComboBox<String>();
	private JLabel lblKey = new JLabel("Key:");
	private JTextField textKey_S50 = new JTextField();
	private JButton btnAuthenticate_S50 = new JButton("Authenticate");
	private JLabel lblBlkData_S50 = new JLabel("Block data:");
	private JTextField textBlkData_S50 = new JTextField();
	private JButton btnReadBlk_S50 = new JButton("Read block");
	private JButton btnWriteBlk_S50 = new JButton("Write Block");
	private JLabel lblVal_S50 = new JLabel("Value:");
	private JTextField textValue_S50 = new JTextField();
	private JButton btnFormateValBlk_S50 = new JButton("Format value block");
	private JButton btnIncrement_S50 = new JButton("Increment");
	private JButton btnDecrement_S50 = new JButton("Decrement");
	private JButton btnRestore_S50 = new JButton("Restore");

	private DefaultTableModel TableModel = new DefaultTableModel();
	Vector<String> vTitile = new Vector<String>();
	Vector<Object> vRowData = new Vector<Object>();
	private JTextField textField_Utralight;

	JComboBox<String> cmbUid_Ultralight;
	JButton btnConnect_Ultralight;
	JButton btnDisconnect_Ultralight;
	JComboBox<String> comboBoxAddr_Ultralight;
	JComboBox<String> comboBoxNum_Utralight;
	JButton btnWriteBlk_Utralight;
	JButton btnReadBlk_Utralight;

	public MainFrm()
	{
		textValue_S50.setColumns(10);
		textBlkData_S50.setText("00000000000000000000000000000000");
		textBlkData_S50.setColumns(10);
		textKey_S50.setText("FFFFFFFFFFFF");
		textKey_S50.setColumns(10);
		panel14443A.setBorder(new TitledBorder(null, "Mifare S50",
				TitledBorder.LEADING, TitledBorder.TOP, null, null));
		setResizable(false);
		setTitle("Rfid Reader Demo");

		JPanel panel = new JPanel();
		panel.setBorder(new LineBorder(new Color(0, 0, 0)));

		JPanel panelInventory = new JPanel();
		panelInventory.setBorder(new TitledBorder(null, "Inventory",
				TitledBorder.LEADING, TitledBorder.TOP, null, null));

		JPanel panelIcodeSli = new JPanel();
		panelIcodeSli.setBorder(new TitledBorder(null, "ICODE SLI",
				TitledBorder.LEADING, TitledBorder.TOP, null, null));

		JPanel panelUltralight = new JPanel();
		panelUltralight.setBorder(new TitledBorder(null, "Mifare Ultralight",
				TitledBorder.LEADING, TitledBorder.TOP, null, null));

		JLabel label = new JLabel("Uid:");

		cmbUid_Ultralight = new JComboBox<String>();
		cmbUid_Ultralight.setEnabled(false);

		btnConnect_Ultralight = new JButton("Connect");
		btnConnect_Ultralight.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				String sUid = cmbUid_Ultralight.getItemAt(cmbUid_Ultralight
						.getSelectedIndex());
				if (sUid == null)
				{
					return;
				}

				if (b_inventoryFlg)
				{
					JOptionPane.showMessageDialog(null,
							"Please stop inventory first!");
					return;
				}

				byte[] uid = gFunction.decodeHex(sUid);
				if (uid.length != 7)
				{
					JOptionPane
							.showMessageDialog(null, "The UID is not right!");
					return;
				}
				// ULTRALIGHT_Connect(long hr,byte[]uid/* 7 bytes */,Long ht)
				Long ht = new Long(0);
				int nret = rfidlib_aip_iso14443A.ULTRALIGHT_Connect(m_hr, uid,
						ht);
				if (nret != 0)
				{
					JOptionPane.showMessageDialog(null, "Connect tag failed!");
				}
				m_ht = ht;
				if (m_ht != 0)
				{
					EnableTagCtr(true);
				}
				else
				{
					JOptionPane.showMessageDialog(null, "Connect tag failed!");
				}
			}
		});
		btnConnect_Ultralight.setEnabled(false);

		btnDisconnect_Ultralight = new JButton("Disconnect");
		btnDisconnect_Ultralight.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				if (m_ht == 0)
				{
					return;
				}
				rfidlib_reader.RDR_TagDisconnect(m_hr, m_ht);
				m_ht = 0;
				EnableTagCtr(false);
			}
		});
		btnDisconnect_Ultralight.setEnabled(false);

		JLabel lblAddress = new JLabel("Address:");

		comboBoxAddr_Ultralight = new JComboBox<String>();
		for (int j = 0; j < 47; j++)
		{
			comboBoxAddr_Ultralight.addItem(j + "");
		}

		comboBoxAddr_Ultralight.setSelectedIndex(0);
		comboBoxAddr_Ultralight.setEnabled(false);

		JLabel label_4 = new JLabel("Block data:");

		textField_Utralight = new JTextField();
		textField_Utralight.setText("00000000");
		textField_Utralight.setEnabled(false);
		textField_Utralight.setColumns(10);

		btnWriteBlk_Utralight = new JButton("Write");
		btnWriteBlk_Utralight.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int blkAddr = comboBoxAddr_Ultralight.getSelectedIndex();
				int blkNum = comboBoxNum_Utralight.getSelectedIndex() + 1;
				String sBuffer = textField_Utralight.getText();
				byte[] newBlkData = gFunction.decodeHex(sBuffer);

				if (newBlkData.length % 4 != 0)
				{
					JOptionPane.showMessageDialog(null,
							"The data of block is not right!");
				}
				int nret = rfidlib_aip_iso14443A.ULTRALIGHT_WriteMultiplePages(
						m_hr, m_ht, (byte) blkAddr, (byte) blkNum, newBlkData,
						newBlkData.length);
				if (nret == 0)
				{
					JOptionPane.showMessageDialog(null, "Write block OK");
				}
				else
				{
					JOptionPane.showMessageDialog(null,
							"Write block failed!err = " + nret);
				}
				// JOptionPane.showMessageDialog(null,
				// "The address must be between 4 and 43.");
			}
		});
		btnWriteBlk_Utralight.setEnabled(false);

		btnReadBlk_Utralight = new JButton("Read");
		btnReadBlk_Utralight.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int blkAddr = comboBoxAddr_Ultralight.getSelectedIndex();
				int numOfBlksToRead = comboBoxNum_Utralight.getSelectedIndex() + 1;
				byte[] bufBlocks = null;
				bufBlocks = new byte[4 * numOfBlksToRead];
				Integer nSize = new Integer(0);
				int nret = rfidlib_aip_iso14443A.ULTRALIGHT_ReadMultiplePages(
						m_hr, m_ht, (byte) blkAddr, (byte) numOfBlksToRead,
						bufBlocks, nSize);
				if (nret != 0)
				{
					JOptionPane.showMessageDialog(null,
							"Read multi block failed!err=" + nret);
					return;
				}
				String sBlkDataString = gFunction.encodeHexStr(bufBlocks);// getHexString(bufBlocks);
				textField_Utralight.setText(sBlkDataString);
			}
		});
		btnReadBlk_Utralight.setEnabled(false);

		JLabel label_1 = new JLabel("Block num:");

		comboBoxNum_Utralight = new JComboBox<String>();
		for (int j = 1; j <= 47; j++)
		{
			comboBoxNum_Utralight.addItem(j + "");
		}
		comboBoxNum_Utralight.setSelectedIndex(0);
		comboBoxNum_Utralight.setEnabled(false);
		GroupLayout gl_panelUltralight = new GroupLayout(panelUltralight);
		gl_panelUltralight
				.setHorizontalGroup(gl_panelUltralight
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panelUltralight
										.createSequentialGroup()
										.addContainerGap()
										.addGroup(
												gl_panelUltralight
														.createParallelGroup(
																Alignment.LEADING)
														.addGroup(
																gl_panelUltralight
																		.createSequentialGroup()
																		.addComponent(
																				label)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				cmbUid_Ultralight,
																				GroupLayout.PREFERRED_SIZE,
																				105,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.UNRELATED)
																		.addComponent(
																				btnConnect_Ultralight)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				btnDisconnect_Ultralight))
														.addGroup(
																gl_panelUltralight
																		.createSequentialGroup()
																		.addComponent(
																				lblAddress)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				comboBoxAddr_Ultralight,
																				GroupLayout.PREFERRED_SIZE,
																				66,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				label_1,
																				GroupLayout.PREFERRED_SIZE,
																				60,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				comboBoxNum_Utralight,
																				GroupLayout.PREFERRED_SIZE,
																				50,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				label_4)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				textField_Utralight,
																				GroupLayout.PREFERRED_SIZE,
																				GroupLayout.DEFAULT_SIZE,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.UNRELATED)
																		.addComponent(
																				btnWriteBlk_Utralight)
																		.addGap(10)
																		.addComponent(
																				btnReadBlk_Utralight)))
										.addContainerGap(561, Short.MAX_VALUE)));
		gl_panelUltralight
				.setVerticalGroup(gl_panelUltralight
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panelUltralight
										.createSequentialGroup()
										.addContainerGap()
										.addGroup(
												gl_panelUltralight
														.createParallelGroup(
																Alignment.BASELINE)
														.addComponent(label)
														.addComponent(
																cmbUid_Ultralight,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE)
														.addComponent(
																btnConnect_Ultralight)
														.addComponent(
																btnDisconnect_Ultralight))
										.addPreferredGap(
												ComponentPlacement.RELATED)
										.addGroup(
												gl_panelUltralight
														.createParallelGroup(
																Alignment.BASELINE)
														.addComponent(label_4)
														.addComponent(
																lblAddress)
														.addComponent(
																comboBoxAddr_Ultralight,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE)
														.addComponent(
																textField_Utralight,
																GroupLayout.PREFERRED_SIZE,
																21,
																GroupLayout.PREFERRED_SIZE)
														.addComponent(
																btnWriteBlk_Utralight)
														.addComponent(
																btnReadBlk_Utralight)
														.addComponent(label_1)
														.addComponent(
																comboBoxNum_Utralight,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE))
										.addContainerGap(
												GroupLayout.DEFAULT_SIZE,
												Short.MAX_VALUE)));
		panelUltralight.setLayout(gl_panelUltralight);

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
																				panelUltralight,
																				GroupLayout.DEFAULT_SIZE,
																				1047,
																				Short.MAX_VALUE)
																		.addContainerGap())
														.addGroup(
																groupLayout
																		.createSequentialGroup()
																		.addComponent(
																				panelIcodeSli,
																				GroupLayout.PREFERRED_SIZE,
																				GroupLayout.DEFAULT_SIZE,
																				Short.MAX_VALUE)
																		.addContainerGap())
														.addGroup(
																groupLayout
																		.createSequentialGroup()
																		.addComponent(
																				panelInventory,
																				GroupLayout.PREFERRED_SIZE,
																				840,
																				GroupLayout.PREFERRED_SIZE)
																		.addContainerGap())
														.addGroup(
																groupLayout
																		.createSequentialGroup()
																		.addComponent(
																				panel,
																				GroupLayout.PREFERRED_SIZE,
																				852,
																				GroupLayout.PREFERRED_SIZE)
																		.addContainerGap(
																				218,
																				Short.MAX_VALUE))
														.addGroup(
																groupLayout
																		.createSequentialGroup()
																		.addComponent(
																				panel14443A,
																				GroupLayout.PREFERRED_SIZE,
																				1047,
																				Short.MAX_VALUE)
																		.addGap(23)))));
		groupLayout.setVerticalGroup(groupLayout.createParallelGroup(
				Alignment.LEADING).addGroup(
				groupLayout
						.createSequentialGroup()
						.addContainerGap()
						.addComponent(panel, GroupLayout.PREFERRED_SIZE,
								GroupLayout.DEFAULT_SIZE,
								GroupLayout.PREFERRED_SIZE)
						.addGap(18)
						.addComponent(panelInventory,
								GroupLayout.PREFERRED_SIZE, 146,
								GroupLayout.PREFERRED_SIZE)
						.addPreferredGap(ComponentPlacement.RELATED)
						.addComponent(panelIcodeSli, GroupLayout.DEFAULT_SIZE,
								125, Short.MAX_VALUE)
						.addPreferredGap(ComponentPlacement.UNRELATED)
						.addComponent(panel14443A, GroupLayout.DEFAULT_SIZE,
								126, Short.MAX_VALUE)
						.addPreferredGap(ComponentPlacement.UNRELATED)
						.addComponent(panelUltralight,
								GroupLayout.PREFERRED_SIZE, 109,
								GroupLayout.PREFERRED_SIZE).addGap(103)));
		GroupLayout gl_panel14443A = new GroupLayout(panel14443A);
		gl_panel14443A
				.setHorizontalGroup(gl_panel14443A
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panel14443A
										.createSequentialGroup()
										.addContainerGap()
										.addGroup(
												gl_panel14443A
														.createParallelGroup(
																Alignment.LEADING)
														.addGroup(
																gl_panel14443A
																		.createSequentialGroup()
																		.addComponent(
																				lblUid_iso14443a)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				cmbUid_S50,
																				GroupLayout.PREFERRED_SIZE,
																				105,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.UNRELATED)
																		.addComponent(
																				btnConnect_S50)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				btnDisconnect_S50)
																		.addPreferredGap(
																				ComponentPlacement.UNRELATED)
																		.addComponent(
																				lblBlkaddr_S50)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				cmbBlkaddr_S50,
																				GroupLayout.PREFERRED_SIZE,
																				66,
																				GroupLayout.PREFERRED_SIZE)
																		.addGap(18)
																		.addComponent(
																				lblKeyType)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				cmbKeyType_S50,
																				GroupLayout.PREFERRED_SIZE,
																				70,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.UNRELATED)
																		.addComponent(
																				lblKey)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				textKey_S50,
																				GroupLayout.PREFERRED_SIZE,
																				79,
																				GroupLayout.PREFERRED_SIZE)
																		.addGap(6)
																		.addComponent(
																				btnAuthenticate_S50))
														.addGroup(
																gl_panel14443A
																		.createSequentialGroup()
																		.addComponent(
																				lblBlkData_S50)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				textBlkData_S50,
																				GroupLayout.PREFERRED_SIZE,
																				212,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				btnWriteBlk_S50)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				btnReadBlk_S50))
														.addGroup(
																gl_panel14443A
																		.createSequentialGroup()
																		.addComponent(
																				lblVal_S50)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				textValue_S50,
																				GroupLayout.PREFERRED_SIZE,
																				GroupLayout.DEFAULT_SIZE,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				btnFormateValBlk_S50)
																		.addPreferredGap(
																				ComponentPlacement.UNRELATED)
																		.addComponent(
																				btnIncrement_S50)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				btnDecrement_S50)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				btnRestore_S50)))
										.addContainerGap(40, Short.MAX_VALUE)));

		gl_panel14443A
				.setVerticalGroup(gl_panel14443A
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panel14443A
										.createSequentialGroup()
										.addContainerGap()
										.addGroup(
												gl_panel14443A
														.createParallelGroup(
																Alignment.BASELINE)
														.addComponent(
																lblUid_iso14443a)
														.addComponent(
																cmbUid_S50,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE)
														.addComponent(
																btnConnect_S50)
														.addComponent(
																btnDisconnect_S50)
														.addComponent(
																lblBlkaddr_S50)
														.addComponent(
																cmbBlkaddr_S50,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE)
														.addComponent(
																lblKeyType)
														.addComponent(
																cmbKeyType_S50,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE)
														.addComponent(lblKey)
														.addComponent(
																textKey_S50,
																GroupLayout.PREFERRED_SIZE,
																21,
																GroupLayout.PREFERRED_SIZE)
														.addComponent(
																btnAuthenticate_S50))
										.addPreferredGap(
												ComponentPlacement.RELATED)
										.addGroup(
												gl_panel14443A
														.createParallelGroup(
																Alignment.BASELINE)
														.addComponent(
																lblBlkData_S50)
														.addComponent(
																textBlkData_S50,
																GroupLayout.PREFERRED_SIZE,
																21,
																GroupLayout.PREFERRED_SIZE)
														.addComponent(
																btnWriteBlk_S50)
														.addComponent(
																btnReadBlk_S50))
										.addPreferredGap(
												ComponentPlacement.RELATED)
										.addGroup(
												gl_panel14443A
														.createParallelGroup(
																Alignment.BASELINE)
														.addComponent(
																lblVal_S50)
														.addComponent(
																textValue_S50,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE)
														.addComponent(
																btnFormateValBlk_S50)
														.addComponent(
																btnIncrement_S50)
														.addComponent(
																btnDecrement_S50)
														.addComponent(
																btnRestore_S50))
										.addContainerGap(75, Short.MAX_VALUE)));
		btnFormateValBlk_S50.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				byte blkAddr = (byte) cmbBlkaddr_S50.getSelectedIndex();
				int initValue = Integer.parseInt(textValue_S50.getText());
				int nret = rfidlib_aip_iso14443A.MFCL_FormatValueBlock(m_hr,
						m_ht, blkAddr, initValue);
				if (nret == 0)
				{
					JOptionPane.showMessageDialog(null, "OK");
				}
				else
				{
					JOptionPane.showMessageDialog(null, "Failed!err=" + nret);
				}

			}
		});
		btnIncrement_S50.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				byte blkAddr = (byte) cmbBlkaddr_S50.getSelectedIndex();
				int val = Integer.parseInt(textValue_S50.getText());
				int nret = rfidlib_aip_iso14443A.MFCL_Increment(m_hr, m_ht,
						blkAddr, val);
				if (nret == 0)
				{
					JOptionPane.showMessageDialog(null, "OK!");
				}
				else
				{
					JOptionPane.showMessageDialog(null, "Failed!err=" + nret);
				}
			}
		});
		btnDecrement_S50.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				byte blkAddr = (byte) cmbBlkaddr_S50.getSelectedIndex();
				int val = Integer.parseInt(textValue_S50.getText());
				int nret = rfidlib_aip_iso14443A.MFCL_Decrement(m_hr, m_ht,
						blkAddr, val);
				if (nret == 0)
				{
					JOptionPane.showMessageDialog(null, "OK");
				}
				else
				{
					JOptionPane.showMessageDialog(null, "Failed!err=" + nret);
				}
			}
		});
		btnRestore_S50.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				byte blkAddr = (byte) cmbBlkaddr_S50.getSelectedIndex();
				int nret = rfidlib_aip_iso14443A.MFCL_Restore(m_hr, m_ht,
						blkAddr);
				if (nret == 0)
				{
					JOptionPane.showMessageDialog(null,
							"Restore block successfully!");
				}
				else
				{
					JOptionPane.showMessageDialog(null,
							"Failure to restore block!err=" + nret);
				}
			}
		});
		btnConnect_S50.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				String sUid = cmbUid_S50.getItemAt(cmbBlkaddr_S50
						.getSelectedIndex());
				if (sUid == null)
				{
					return;
				}

				if (b_inventoryFlg)
				{
					JOptionPane.showMessageDialog(null,
							"Please stop inventory first!");
					return;
				}

				byte[] uid = gFunction.decodeHex(sUid);
				if (uid.length != 4)
				{
					JOptionPane
							.showMessageDialog(null, "The UID is not right!");
					return;
				}
				Long ht = new Long(0);
				int nret = rfidlib_aip_iso14443A.MFCL_Connect(m_hr, (byte) 0,
						uid, ht);
				if (nret != 0)
				{
					JOptionPane.showMessageDialog(null, "Connect tag failed!");
				}
				m_ht = ht;
				if (m_ht != 0)
				{
					EnableTagCtr(true);
				}
				else
				{
					JOptionPane.showMessageDialog(null, "Connect tag failed!");
				}
			}
		});
		btnDisconnect_S50.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				if (m_ht == 0)
				{
					return;
				}
				rfidlib_reader.RDR_TagDisconnect(m_hr, m_ht);
				m_ht = 0;
				EnableTagCtr(false);
			}
		});
		btnAuthenticate_S50.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				byte blkAddr = (byte) cmbBlkaddr_S50.getSelectedIndex();
				byte keyType = (byte) cmbKeyType_S50.getSelectedIndex();
				byte[] key = gFunction.decodeHex(textKey_S50.getText());
				if (key.length != 6)
				{
					JOptionPane.showMessageDialog(null, "The key is ilegal!");
					return;
				}
				int nret = rfidlib_aip_iso14443A.MFCL_Authenticate(m_hr, m_ht,
						blkAddr, keyType, key);
				if (nret == 0)
				{
					JOptionPane.showMessageDialog(null, "Authenticate OK!");
				}
				else
				{
					JOptionPane.showMessageDialog(null,
							"Authenticate failed!err=" + nret);
				}
			}
		});
		btnReadBlk_S50.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				byte blkAddr = (byte) cmbBlkaddr_S50.getSelectedIndex();
				byte[] blkData = new byte[16];
				int nret = rfidlib_aip_iso14443A.MFCL_ReadBlock(m_hr, m_ht,
						blkAddr, blkData, 16);
				if (nret != 0)
				{
					JOptionPane.showMessageDialog(null,
							"Read block failed!err=" + nret);
					return;
				}
				textBlkData_S50.setText(gFunction.encodeHexStr(blkData));
			}
		});
		btnWriteBlk_S50.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				byte blkAddr = (byte) cmbBlkaddr_S50.getSelectedIndex();
				byte[] blkData = gFunction.decodeHex(textBlkData_S50.getText());
				if (blkData.length != 16)
				{
					JOptionPane.showMessageDialog(null,
							"The data is not right!");
					return;
				}
				int nret = rfidlib_aip_iso14443A.MFCL_WriteBlock(m_hr, m_ht,
						blkAddr, blkData);
				if (nret == 0)
				{
					JOptionPane.showMessageDialog(null, "Write Block OK!");
				}
				else
				{
					JOptionPane.showMessageDialog(null,
							"Write block failed!err=" + nret);
				}
			}
		});
		panel14443A.setLayout(gl_panel14443A);

		JLabel lblAddrmode15693 = new JLabel("Address mode:");
		JLabel lblUid_iso15693 = new JLabel("Uid:");
		JLabel lblBlkdata_iso15693 = new JLabel("Block data:");

		// textBlkData_iso15693 = new JTextField();
		textBlkData_iso15693.setColumns(10);
		JLabel lblBlkaddr_iso15693 = new JLabel("Block addr:");
		JLabel lblBlknum_iso15693 = new JLabel("Block num:");
		JLabel lblAfi = new JLabel("AFI(hex):");
		// textAfiVal = new JTextField();
		textAfiVal.setText("00");
		textAfiVal.setColumns(10);
		JLabel lblDsfid = new JLabel("DSFID(hex):");
		// textDsfidVal = new JTextField();
		textDsfidVal.setText("00");
		textDsfidVal.setColumns(10);

		GroupLayout gl_panelIcodeSli = new GroupLayout(panelIcodeSli);
		gl_panelIcodeSli
				.setHorizontalGroup(gl_panelIcodeSli
						.createParallelGroup(Alignment.TRAILING)
						.addGroup(
								gl_panelIcodeSli
										.createSequentialGroup()
										.addContainerGap()
										.addGroup(
												gl_panelIcodeSli
														.createParallelGroup(
																Alignment.LEADING)
														.addGroup(
																gl_panelIcodeSli
																		.createSequentialGroup()
																		.addGroup(
																				gl_panelIcodeSli
																						.createParallelGroup(
																								Alignment.LEADING)
																						.addGroup(
																								gl_panelIcodeSli
																										.createSequentialGroup()
																										.addComponent(
																												lblAddrmode15693)
																										.addPreferredGap(
																												ComponentPlacement.RELATED)
																										.addComponent(
																												cmbAddrMode_iso15693,
																												GroupLayout.PREFERRED_SIZE,
																												130,
																												GroupLayout.PREFERRED_SIZE)
																										.addGap(18)
																										.addComponent(
																												lblUid_iso15693)
																										.addPreferredGap(
																												ComponentPlacement.RELATED)
																										.addComponent(
																												cmbUid_iso15693,
																												GroupLayout.PREFERRED_SIZE,
																												126,
																												GroupLayout.PREFERRED_SIZE)
																										.addGap(29)
																										.addComponent(
																												btnConnect_iso15693))
																						.addGroup(
																								gl_panelIcodeSli
																										.createSequentialGroup()
																										.addGroup(
																												gl_panelIcodeSli
																														.createParallelGroup(
																																Alignment.LEADING)
																														.addGroup(
																																gl_panelIcodeSli
																																		.createSequentialGroup()
																																		.addGap(70)
																																		.addComponent(
																																				textBlkData_iso15693,
																																				GroupLayout.PREFERRED_SIZE,
																																				243,
																																				GroupLayout.PREFERRED_SIZE))
																														.addComponent(
																																lblBlkdata_iso15693))
																										.addPreferredGap(
																												ComponentPlacement.RELATED)
																										.addComponent(
																												lblBlkaddr_iso15693)
																										.addPreferredGap(
																												ComponentPlacement.RELATED)
																										.addComponent(
																												cmbBlkaddr_iso15693,
																												GroupLayout.PREFERRED_SIZE,
																												54,
																												GroupLayout.PREFERRED_SIZE)
																										.addPreferredGap(
																												ComponentPlacement.RELATED)
																										.addComponent(
																												lblBlknum_iso15693)))
																		.addGap(1)
																		.addGroup(
																				gl_panelIcodeSli
																						.createParallelGroup(
																								Alignment.LEADING)
																						.addGroup(
																								gl_panelIcodeSli
																										.createSequentialGroup()
																										.addComponent(
																												cmbBlkNum_iso15693,
																												GroupLayout.PREFERRED_SIZE,
																												50,
																												GroupLayout.PREFERRED_SIZE)
																										.addPreferredGap(
																												ComponentPlacement.RELATED)
																										.addComponent(
																												btnReadSigle_iso15693)
																										.addPreferredGap(
																												ComponentPlacement.RELATED)
																										.addComponent(
																												btnReadMul_iso15693)
																										.addPreferredGap(
																												ComponentPlacement.RELATED)
																										.addComponent(
																												btnWriteMutiple_iso15693)
																										.addPreferredGap(
																												ComponentPlacement.RELATED)
																										.addComponent(
																												btnGetsecState_iso15693,
																												GroupLayout.DEFAULT_SIZE,
																												151,
																												Short.MAX_VALUE))
																						.addGroup(
																								gl_panelIcodeSli
																										.createSequentialGroup()
																										.addComponent(
																												btnDidconnect)
																										.addPreferredGap(
																												ComponentPlacement.UNRELATED)
																										.addComponent(
																												btnGetTagInfo_iso15693))))
														.addGroup(
																gl_panelIcodeSli
																		.createSequentialGroup()
																		.addComponent(
																				lblAfi)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				textAfiVal,
																				GroupLayout.PREFERRED_SIZE,
																				29,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				btnWriteAfi)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				lblDsfid)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				textDsfidVal,
																				GroupLayout.PREFERRED_SIZE,
																				26,
																				GroupLayout.PREFERRED_SIZE)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				btnWriteDsfid)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				btnEnableEAS)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				btnDisableEAS)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				btnEAScheck)))
										.addContainerGap()));
		gl_panelIcodeSli
				.setVerticalGroup(gl_panelIcodeSli
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panelIcodeSli
										.createSequentialGroup()
										.addGroup(
												gl_panelIcodeSli
														.createParallelGroup(
																Alignment.LEADING)
														.addGroup(
																gl_panelIcodeSli
																		.createParallelGroup(
																				Alignment.BASELINE)
																		.addComponent(
																				cmbAddrMode_iso15693,
																				GroupLayout.PREFERRED_SIZE,
																				GroupLayout.DEFAULT_SIZE,
																				GroupLayout.PREFERRED_SIZE)
																		.addComponent(
																				lblUid_iso15693)
																		.addComponent(
																				cmbUid_iso15693,
																				GroupLayout.PREFERRED_SIZE,
																				GroupLayout.DEFAULT_SIZE,
																				GroupLayout.PREFERRED_SIZE)
																		.addComponent(
																				btnConnect_iso15693)
																		.addComponent(
																				btnDidconnect)
																		.addComponent(
																				btnGetTagInfo_iso15693))
														.addComponent(
																lblAddrmode15693))
										.addPreferredGap(
												ComponentPlacement.UNRELATED)
										.addGroup(
												gl_panelIcodeSli
														.createParallelGroup(
																Alignment.LEADING)
														.addGroup(
																gl_panelIcodeSli
																		.createParallelGroup(
																				Alignment.BASELINE)
																		.addComponent(
																				textBlkData_iso15693,
																				GroupLayout.PREFERRED_SIZE,
																				18,
																				GroupLayout.PREFERRED_SIZE)
																		.addComponent(
																				lblBlkaddr_iso15693)
																		.addComponent(
																				cmbBlkaddr_iso15693,
																				GroupLayout.PREFERRED_SIZE,
																				GroupLayout.DEFAULT_SIZE,
																				GroupLayout.PREFERRED_SIZE)
																		.addComponent(
																				lblBlknum_iso15693)
																		.addComponent(
																				cmbBlkNum_iso15693,
																				GroupLayout.PREFERRED_SIZE,
																				GroupLayout.DEFAULT_SIZE,
																				GroupLayout.PREFERRED_SIZE)
																		.addComponent(
																				btnReadSigle_iso15693)
																		.addComponent(
																				btnReadMul_iso15693)
																		.addComponent(
																				btnWriteMutiple_iso15693)
																		.addComponent(
																				btnGetsecState_iso15693,
																				GroupLayout.PREFERRED_SIZE,
																				23,
																				GroupLayout.PREFERRED_SIZE))
														.addComponent(
																lblBlkdata_iso15693))
										.addGap(9)
										.addGroup(
												gl_panelIcodeSli
														.createParallelGroup(
																Alignment.BASELINE)
														.addComponent(lblAfi)
														.addComponent(
																textAfiVal,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE)
														.addComponent(
																btnWriteAfi,
																GroupLayout.PREFERRED_SIZE,
																23,
																GroupLayout.PREFERRED_SIZE)
														.addComponent(lblDsfid)
														.addComponent(
																textDsfidVal,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE)
														.addComponent(
																btnWriteDsfid)
														.addComponent(
																btnEnableEAS)
														.addComponent(
																btnDisableEAS)
														.addComponent(
																btnEAScheck))
										.addContainerGap(51, Short.MAX_VALUE)));
		btnConnect_iso15693.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				byte addrMode = (byte) cmbAddrMode_iso15693.getSelectedIndex();
				String sUid = cmbUid_iso15693.getItemAt(cmbUid_iso15693
						.getSelectedIndex());
				if (sUid == null && addrMode != 0)
				{
					JOptionPane.showMessageDialog(null, "Please select a tag!");
					return;
				}
				if (b_inventoryFlg)
				{
					JOptionPane.showMessageDialog(null,
							"Please stop inventory first!");
					return;
				}
				Long ht = new Long(0);
				byte[] m_uid = null;
				if (addrMode != 0)
				{
					m_uid = gFunction.decodeHex(sUid);
				}
				else
				{
					m_uid = new byte[8];// ÎÞµØÖ·Ä£Ê½
				}
				int nret = rfidlib_AIP_ISO15693.ISO15693_Connect(m_hr,
						rfid_def.RFID_ISO15693_PICC_ICODE_SLI_ID, addrMode,
						m_uid, ht);
				if (nret != 0)
				{
					JOptionPane.showMessageDialog(null,
							"Connect tag failed!err=" + nret);
					return;
				}
				m_ht = ht;
				EnableTagCtr(true);
			}
		});
		btnDidconnect.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				rfidlib_reader.RDR_TagDisconnect(m_hr, m_hr);
				m_ht = 0;
				EnableTagCtr(false);
			}
		});
		btnGetTagInfo_iso15693.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{

				byte[] uid = new byte[8];
				Byte dsfid = new Byte((byte) 0);
				Byte afi = new Byte((byte) 0);
				Integer blkSize = new Integer(0);
				Integer numOfBloks = new Integer(0);
				Byte icRef = new Byte((byte) 0);

				int nret = rfidlib_AIP_ISO15693.ISO15693_GetSystemInfo(m_hr,
						m_ht, uid, dsfid, afi, blkSize, numOfBloks, icRef);
				if (nret == 0)
				{
					String sUid = gFunction.encodeHexStr(uid);
					/*
					 * String info = "uid:" + sUid + "\r\n" + "DSFID:" + dsfid +
					 * "\r\n" + "AFI:" + (afi&0xff) + "\r\n" + "Block size:" +
					 * blkSize + "\r\n" + "Num of block:" + numOfBloks + "\r\n"
					 * + "IcRef:" + icRef;
					 */
					String info = String
							.format("uid:%s\r\nDSFID:%02X\r\nAFI:%02X\r\nBlock size:%d\r\nNum of block:%d\r\nIcRef:%02x",
									sUid, dsfid, afi, blkSize, numOfBloks,
									icRef);
					JOptionPane.showMessageDialog(null, info);
				}
			}
		});
		btnReadSigle_iso15693.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int blkAddr = cmbBlkaddr_iso15693.getSelectedIndex();
				byte[] bufBlockData = new byte[4];
				Integer bytesBlkDatRead = new Integer(0);
				int nret = rfidlib_AIP_ISO15693.ISO15693_ReadSingleBlock(m_hr,
						m_ht, (byte) 0, blkAddr, bufBlockData,
						bufBlockData.length, bytesBlkDatRead);
				if (nret != 0)
				{
					JOptionPane.showMessageDialog(null, "Read single failed!");
					return;
				}
				String sBlkDataString = gFunction.encodeHexStr(bufBlockData);
				textBlkData_iso15693.setText(sBlkDataString);
			}
		});
		btnReadMul_iso15693.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int blkAddr = cmbBlkaddr_iso15693.getSelectedIndex();
				int numOfBlksToRead = cmbBlkNum_iso15693.getSelectedIndex() + 1;
				byte[] bufBlocks = null;
				bufBlocks = new byte[4 * numOfBlksToRead];
				Integer bytesBlkDatRead = new Integer(0);
				Integer numOfBlksRead = new Integer(0);
				int nret = rfidlib_AIP_ISO15693.ISO15693_ReadMultiBlocks(m_hr,
						m_ht, (byte) 0, blkAddr, numOfBlksToRead,
						numOfBlksRead, bufBlocks, bufBlocks.length,
						bytesBlkDatRead);
				if (nret != 0)
				{
					JOptionPane.showMessageDialog(null,
							"Read multi block failed!err=" + nret);
					return;
				}
				String sBlkDataString = gFunction.encodeHexStr(bufBlocks);// getHexString(bufBlocks);
				textBlkData_iso15693.setText(sBlkDataString);
			}
		});
		btnWriteMutiple_iso15693.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int blkAddr = cmbBlkaddr_iso15693.getSelectedIndex();
				int blkNum = cmbBlkNum_iso15693.getSelectedIndex() + 1;
				String sBuffer = textBlkData_iso15693.getText();
				byte[] newBlkData = gFunction.decodeHex(sBuffer);
				if (newBlkData.length % 4 != 0)
				{
					JOptionPane.showMessageDialog(null,
							"The data of block is not right!");
				}

				int nret = rfidlib_AIP_ISO15693.ISO15693_WriteMultipleBlocks(
						m_hr, m_ht, blkAddr, blkNum, newBlkData, 4 * blkNum);
				if (nret == 0)
				{
					JOptionPane.showMessageDialog(null, "Write block OK");
				}
				else
				{
					JOptionPane.showMessageDialog(null,
							"Write block failed!err = " + nret);
				}
			}
		});
		btnGetsecState_iso15693.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int blkAddr = cmbBlkaddr_iso15693.getSelectedIndex();
				int numOfBlks = cmbBlkNum_iso15693.getSelectedIndex() + 1;
				byte[] bufBlkSecs = new byte[numOfBlks];

				Integer BytesSecRead = new Integer(0);
				int ret = rfidlib_AIP_ISO15693.ISO15693_GetBlockSecStatus(m_hr,
						m_ht, blkAddr, numOfBlks, bufBlkSecs,
						bufBlkSecs.length, BytesSecRead);
				String info = gFunction.encodeHexStr(bufBlkSecs);
				if (ret == 0)
				{
					JOptionPane.showMessageDialog(null, info);
				}
				else
				{
					JOptionPane.showMessageDialog(null,
							"Get block sestatus failed!err=" + ret);
				}

			}
		});
		btnWriteDsfid.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int mTmp = Integer.parseInt(textDsfidVal.getText());
				byte dsfid = IntToByte(mTmp);
				int nret = rfidlib_AIP_ISO15693.ISO15693_WriteDSFID(m_hr, m_ht,
						dsfid);
				if (nret == 0)
				{
					JOptionPane.showMessageDialog(null, "Write DSFID ok!");
				}
				else
				{
					JOptionPane.showMessageDialog(null,
							"Write DSFID failed!err=" + nret);
				}
			}
		});
		btnWriteAfi.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int mTmp = Integer.parseInt(textAfiVal.getText());
				byte afi = IntToByte(mTmp);
				int nret = rfidlib_AIP_ISO15693.ISO15693_WriteAFI(m_hr, m_ht,
						afi);
				if (nret == 0)
				{
					JOptionPane.showMessageDialog(null, "Write AFI ok!");
				}
				else
				{
					JOptionPane.showMessageDialog(null,
							"Write AFI failed!err = " + nret);
				}
			}
		});
		btnEnableEAS.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int nret = rfidlib_AIP_ISO15693
						.NXPICODESLI_EableEAS(m_hr, m_ht);
				if (nret == 0)
				{
					JOptionPane.showMessageDialog(null, "Enable EAS OK!");
				}
				else
				{
					JOptionPane.showMessageDialog(null,
							"Enable EAS failed!err=" + nret);
				}
			}
		});
		btnDisableEAS.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int nret = rfidlib_AIP_ISO15693.NXPICODESLI_DisableEAS(m_hr,
						m_ht);
				if (nret == 0)
				{
					JOptionPane.showMessageDialog(null, "Disable EAS OK!");
				}
				else
				{
					JOptionPane.showMessageDialog(null,
							"Disable EAS failed!err = " + nret);
				}
			}
		});
		btnEAScheck.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				Byte EASStatus = new Byte((byte) 0);
				int nret = rfidlib_AIP_ISO15693.NXPICODESLI_EASCheck(m_hr,
						m_ht, EASStatus);
				if (nret != 0)
				{
					JOptionPane.showMessageDialog(null, "EAS check failed");
				}
				if (EASStatus > 0)
				{
					JOptionPane.showMessageDialog(null, "EAS open!");
				}
				else
				{
					JOptionPane.showMessageDialog(null, "EAS close!");
				}
			}
		});
		panelIcodeSli.setLayout(gl_panelIcodeSli);
		btnStartInventory.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				if (m_ht != 0)
				{
					JOptionPane.showMessageDialog(null,
							"Please disconnect the tag first!");
					return;
				}
				Thread m_inventory = new Thread(MainFrm.this);
				vRowData.clear();
				TableModel.setDataVector(vRowData, vTitile);
				cmbUid_iso15693.removeAllItems();
				cmbUid_S50.removeAllItems();
				cmbUid_Ultralight.removeAllItems();

				m_inventory.start();
				EnableInventoryCtr(true);
			}
		});

		btnStopInventory.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				rfidlib_reader.RDR_SetCommuImmeTimeout(MainFrm.this.m_hr);
				MainFrm.this.b_inventoryFlg = false;
			}
		});

		JPanel panelISO15693 = new JPanel();
		panelISO15693.setBorder(new TitledBorder(UIManager
				.getBorder("TitledBorder.border"), "ISO15693 inventory",
				TitledBorder.LEADING, TitledBorder.TOP, null, new Color(0, 70,
						213)));
		GroupLayout gl_panelInventory = new GroupLayout(panelInventory);
		gl_panelInventory
				.setHorizontalGroup(gl_panelInventory
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panelInventory
										.createSequentialGroup()
										.addContainerGap()
										.addComponent(tableInventory,
												GroupLayout.PREFERRED_SIZE,
												405, GroupLayout.PREFERRED_SIZE)
										.addGap(18)
										.addGroup(
												gl_panelInventory
														.createParallelGroup(
																Alignment.LEADING,
																false)
														.addComponent(
																btnStopInventory,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.DEFAULT_SIZE,
																Short.MAX_VALUE)
														.addComponent(
																btnStartInventory,
																GroupLayout.DEFAULT_SIZE,
																74,
																Short.MAX_VALUE))
										.addGap(32)
										.addComponent(panelISO15693,
												GroupLayout.PREFERRED_SIZE,
												173, GroupLayout.PREFERRED_SIZE)
										.addPreferredGap(
												ComponentPlacement.UNRELATED)
										.addComponent(checkEnable14443A)
										.addContainerGap(21, Short.MAX_VALUE)));
		gl_panelInventory
				.setVerticalGroup(gl_panelInventory
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panelInventory
										.createSequentialGroup()
										.addGroup(
												gl_panelInventory
														.createParallelGroup(
																Alignment.LEADING)
														.addGroup(
																gl_panelInventory
																		.createSequentialGroup()
																		.addContainerGap()
																		.addGroup(
																				gl_panelInventory
																						.createParallelGroup(
																								Alignment.BASELINE)
																						.addComponent(
																								tableInventory,
																								GroupLayout.DEFAULT_SIZE,
																								107,
																								Short.MAX_VALUE)
																						.addGroup(
																								gl_panelInventory
																										.createSequentialGroup()
																										.addComponent(
																												btnStartInventory)
																										.addGap(10)
																										.addComponent(
																												btnStopInventory))))
														.addComponent(
																panelISO15693,
																GroupLayout.PREFERRED_SIZE,
																111,
																GroupLayout.PREFERRED_SIZE))
										.addGap(25))
						.addGroup(
								gl_panelInventory.createSequentialGroup()
										.addGap(18)
										.addComponent(checkEnable14443A)
										.addContainerGap(101, Short.MAX_VALUE)));

		JLabel lblAFI = new JLabel("AFI(hex):");

		// textAFI = new JTextField();
		textAFI.setText("00");
		textAFI.setColumns(10);
		GroupLayout gl_panelISO15693 = new GroupLayout(panelISO15693);
		gl_panelISO15693
				.setHorizontalGroup(gl_panelISO15693
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panelISO15693
										.createSequentialGroup()
										.addContainerGap()
										.addGroup(
												gl_panelISO15693
														.createParallelGroup(
																Alignment.LEADING)
														.addComponent(
																checkOnlyNew)
														.addComponent(
																checkAfiMatch)
														.addGroup(
																gl_panelISO15693
																		.createSequentialGroup()
																		.addComponent(
																				lblAFI)
																		.addPreferredGap(
																				ComponentPlacement.RELATED)
																		.addComponent(
																				textAFI,
																				0,
																				0,
																				Short.MAX_VALUE)))
										.addContainerGap(54, Short.MAX_VALUE)));
		gl_panelISO15693
				.setVerticalGroup(gl_panelISO15693
						.createParallelGroup(Alignment.LEADING)
						.addGroup(
								gl_panelISO15693
										.createSequentialGroup()
										.addComponent(checkOnlyNew)
										.addPreferredGap(
												ComponentPlacement.UNRELATED)
										.addComponent(checkAfiMatch)
										.addPreferredGap(
												ComponentPlacement.UNRELATED)
										.addGroup(
												gl_panelISO15693
														.createParallelGroup(
																Alignment.BASELINE)
														.addComponent(lblAFI)
														.addComponent(
																textAFI,
																GroupLayout.PREFERRED_SIZE,
																GroupLayout.DEFAULT_SIZE,
																GroupLayout.PREFERRED_SIZE))
										.addContainerGap()));
		panelISO15693.setLayout(gl_panelISO15693);
		panelInventory.setLayout(gl_panelInventory);

		JLabel lblReaderType = new JLabel("Reader Type:");
		JLabel lblCommType = new JLabel("Communicate Type:");
		cmbCommType.addItem("COM");
		cmbCommType.addItem("USB");
		cmbCommType.addItem("TCP/IP");
		cmbCommType.setSelectedIndex(0);

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
				if (b_inventoryFlg)
				{
					JOptionPane.showMessageDialog(null,
							"Please stop inventory first!");
					return;
				}
				if (m_hr == 0)
				{
					return;
				}
				if (m_ht != 0)
				{
					JOptionPane.showMessageDialog(null,
							"Please disconnect tag first!");
					return;
				}
				rfidlib_reader.RDR_Close(m_hr);
				EnableAllCtr(false);
				m_hr = 0;
			}
		});

		btnGetRfidInfo.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent e)
			{
				int iret = 0;
				char[] buffer = new char[256];
				Integer nSize = new Integer(0);
				iret = rfidlib_reader.RDR_GetReaderInfor(m_hr, (byte) 0,
						buffer, nSize);

				if (iret == 0)
				{
					String sInfo = String.copyValueOf(buffer, 0, nSize);
					JOptionPane.showMessageDialog(null, sInfo);
				}
				else
				{
					String str = "Get device information failed!err = " + iret;
					JOptionPane.showMessageDialog(null, str);
				}
			}
		});

		JLabel lblComName = new JLabel("COM:");

		JLabel lblIpAddr = new JLabel("IP:");

		textIP.setText("192.168.0.222");
		textIP.setColumns(10);

		JLabel lblPort = new JLabel("Port:");

		textPort.setText("9909");
		textPort.setColumns(10);
		GroupLayout gl_panel = new GroupLayout(panel);
		gl_panel.setHorizontalGroup(gl_panel
				.createParallelGroup(Alignment.LEADING)
				.addGroup(
						gl_panel.createSequentialGroup()
								.addGap(47)
								.addGroup(
										gl_panel.createParallelGroup(
												Alignment.TRAILING)
												.addGroup(
														gl_panel.createSequentialGroup()
																.addComponent(
																		lblReaderType)
																.addGap(4))
												.addGroup(
														gl_panel.createSequentialGroup()
																.addComponent(
																		lblComName)
																.addPreferredGap(
																		ComponentPlacement.UNRELATED)))
								.addGroup(
										gl_panel.createParallelGroup(
												Alignment.LEADING)
												.addComponent(
														cmbComName,
														GroupLayout.PREFERRED_SIZE,
														113,
														GroupLayout.PREFERRED_SIZE)
												.addComponent(
														cmbDevType,
														GroupLayout.PREFERRED_SIZE,
														99,
														GroupLayout.PREFERRED_SIZE))
								.addGap(18)
								.addGroup(
										gl_panel.createParallelGroup(
												Alignment.TRAILING)
												.addComponent(lblIpAddr)
												.addComponent(lblCommType))
								.addPreferredGap(ComponentPlacement.RELATED)
								.addGroup(
										gl_panel.createParallelGroup(
												Alignment.LEADING)
												.addComponent(
														cmbCommType,
														GroupLayout.PREFERRED_SIZE,
														96,
														GroupLayout.PREFERRED_SIZE)
												.addComponent(
														textIP,
														GroupLayout.PREFERRED_SIZE,
														100,
														GroupLayout.PREFERRED_SIZE))
								.addGroup(
										gl_panel.createParallelGroup(
												Alignment.TRAILING)
												.addGroup(
														Alignment.LEADING,
														gl_panel.createSequentialGroup()
																.addGap(14)
																.addComponent(
																		btnOpen)
																.addGap(18)
																.addComponent(
																		btnClose)
																.addGap(18)
																.addComponent(
																		btnGetRfidInfo))
												.addGroup(
														Alignment.LEADING,
														gl_panel.createSequentialGroup()
																.addGap(31)
																.addComponent(
																		lblPort)
																.addPreferredGap(
																		ComponentPlacement.RELATED)
																.addComponent(
																		textPort,
																		GroupLayout.PREFERRED_SIZE,
																		39,
																		GroupLayout.PREFERRED_SIZE)))
								.addGap(344)));
		gl_panel.setVerticalGroup(gl_panel
				.createParallelGroup(Alignment.TRAILING)
				.addGroup(
						gl_panel.createSequentialGroup()
								.addContainerGap()
								.addGroup(
										gl_panel.createParallelGroup(
												Alignment.LEADING)
												.addGroup(
														gl_panel.createSequentialGroup()
																.addGap(3)
																.addGroup(
																		gl_panel.createParallelGroup(
																				Alignment.BASELINE)
																				.addComponent(
																						lblReaderType)
																				.addComponent(
																						cmbDevType,
																						GroupLayout.PREFERRED_SIZE,
																						GroupLayout.DEFAULT_SIZE,
																						GroupLayout.PREFERRED_SIZE)))
												.addGroup(
														gl_panel.createSequentialGroup()
																.addGap(3)
																.addGroup(
																		gl_panel.createParallelGroup(
																				Alignment.BASELINE)
																				.addComponent(
																						lblCommType)
																				.addComponent(
																						cmbCommType,
																						GroupLayout.PREFERRED_SIZE,
																						GroupLayout.DEFAULT_SIZE,
																						GroupLayout.PREFERRED_SIZE)
																				.addComponent(
																						btnOpen)
																				.addComponent(
																						btnClose)
																				.addComponent(
																						btnGetRfidInfo))))
								.addGap(18)
								.addGroup(
										gl_panel.createParallelGroup(
												Alignment.LEADING)
												.addGroup(
														gl_panel.createParallelGroup(
																Alignment.BASELINE)
																.addComponent(
																		lblIpAddr)
																.addComponent(
																		textIP,
																		GroupLayout.PREFERRED_SIZE,
																		GroupLayout.DEFAULT_SIZE,
																		GroupLayout.PREFERRED_SIZE)
																.addComponent(
																		lblPort)
																.addComponent(
																		textPort,
																		GroupLayout.PREFERRED_SIZE,
																		GroupLayout.DEFAULT_SIZE,
																		GroupLayout.PREFERRED_SIZE))
												.addGroup(
														gl_panel.createParallelGroup(
																Alignment.BASELINE)
																.addComponent(
																		cmbComName,
																		GroupLayout.PREFERRED_SIZE,
																		GroupLayout.DEFAULT_SIZE,
																		GroupLayout.PREFERRED_SIZE)
																.addComponent(
																		lblComName)))
								.addGap(21)));
		panel.setLayout(gl_panel);
		getContentPane().setLayout(groupLayout);

		cmbAddrMode_iso15693.addItem("None Address Mode");
		cmbAddrMode_iso15693.addItem("Addressed Mode");
		cmbAddrMode_iso15693.addItem("Select Mode");
		cmbAddrMode_iso15693.setSelectedIndex(1);

		for (int i = 0; i < 28; i++)
		{
			cmbBlkaddr_iso15693.addItem(i + "");
		}
		cmbBlkaddr_iso15693.setSelectedIndex(0);

		for (int i = 1; i <= 8; i++)
		{
			cmbBlkNum_iso15693.addItem(i + "");
		}
		cmbBlkNum_iso15693.setSelectedIndex(0);

		for (int i = 0; i < 16; i++)
		{
			cmbBlkaddr_S50.addItem(i + "");
		}
		cmbBlkaddr_S50.setSelectedIndex(0);

		cmbKeyType_S50.addItem("Key A");
		cmbKeyType_S50.addItem("Key B");
		cmbKeyType_S50.setSelectedIndex(0);

		vTitile.addElement("Tag type");
		vTitile.addElement("UID");

		TableModel.setDataVector(vRowData, vTitile);
		tableInventory.setModel(TableModel);

		LoadLibrary();
		ListAllCom();
		EnableAllCtr(false);

		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);
		this.setSize(1086, 780);
		this.setLocation(300, 50);
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
		rfidlib_AIP_ISO15693.LoadLib(libPath, osType, arType);
		rfidlib_aip_iso14443A.LoadLib(libPath, osType, arType);

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
					cmbDevType.addItem(sDes);
				}
			}
		}
		if (m_cnt > 0)
		{
			cmbDevType.setSelectedIndex(0);
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
			String comName = String.copyValueOf(buffer, 0, nSize);
			cmbComName.addItem(comName);
		}
		if (m_cnt > 0)
		{
			cmbComName.setSelectedIndex(0);
		}
	}

	private void OpenDev()
	{
		String connstr = null;
		String sDevName = cmbDevType.getItemAt(cmbDevType.getSelectedIndex())
				.toString();
		int idx = cmbCommType.getSelectedIndex();
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
					+ rfid_def.CONNSTR_NAME_COMMTYPE_USB + ";"
					+ rfid_def.CONNSTR_NAME_HIDADDRMODE + "=" + "0" + ";"
					+ rfid_def.CONNSTR_NAME_HIDSERNUM + "=";
			break;
		case 2:
			connstr = rfid_def.CONNSTR_NAME_RDTYPE + "=" + sDevName + ";"
					+ rfid_def.CONNSTR_NAME_COMMTYPE + "="
					+ rfid_def.CONNSTR_NAME_COMMTYPE_NET + ";"
					+ rfid_def.CONNSTR_NAME_REMOTEIP + "=" + textIP.getText()
					+ ";" + rfid_def.CONNSTR_NAME_REMOTEPORT + "="
					+ textPort.getText() + ";" + rfid_def.CONNSTR_NAME_LOCALIP
					+ "=" + "";
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
		EnableAllCtr(true);
		EnableInventoryCtr(false);
		EnableTagCtr(false);
	}

	public static void main(String[] args)
	{
		new MainFrm();
	}

	public void run()
	{
		// TODO Auto-generated method stub
		b_inventoryFlg = true;
		long InvenParamSpecList = rfidlib_reader.RDR_CreateInvenParamSpecList();
		boolean b_iso15693 = true;
		boolean b_iso14443a = checkEnable14443A.isSelected();
		if (InvenParamSpecList != 0)
		{
			byte AntennaID = 0;
			if (b_iso15693)
			{

				byte en_afi = 0;
				if (checkAfiMatch.isSelected())
				{
					en_afi = 1;
				}
				byte afi = (byte) Integer.parseInt(textAFI.getText());
				byte slot_type = 0;
				rfidlib_AIP_ISO15693.ISO15693_CreateInvenParam(
						InvenParamSpecList, AntennaID, en_afi, afi, slot_type);
			}
			if (b_iso14443a)
			{
				rfidlib_aip_iso14443A.ISO14443A_CreateInvenParam(
						InvenParamSpecList, AntennaID);
			}
		}
		byte newAI = rfid_def.AI_TYPE_NEW;
		int nret = 0;
		long dnhReport = 0;

		while (b_inventoryFlg)
		{
			byte[] AntennaIDs = new byte[64];
			nret = rfidlib_reader.RDR_TagInventory(m_hr, newAI, (byte) 0,
					AntennaIDs, InvenParamSpecList);
			if (nret != 0)
			{
				continue;
			}
			dnhReport = rfidlib_reader.RDR_GetTagDataReport(m_hr,
					rfid_def.RFID_SEEK_FIRST);
			while (dnhReport != 0)
			{
				newAI = rfid_def.AI_TYPE_NEW;
				if (checkOnlyNew.isSelected())
				{
					newAI = rfid_def.AI_TYPE_CONTINUE;
				}
				if (b_iso15693)
				{
					Integer aip_id = new Integer(0);
					Integer tag_id = new Integer(0);
					Integer ant_id = new Integer(0);
					Byte dsfid = new Byte((byte) 0);
					byte uid[] = new byte[8];
					nret = rfidlib_AIP_ISO15693.ISO15693_ParseTagDataReport(
							dnhReport, aip_id, tag_id, ant_id, dsfid, uid);
					if (nret == 0)
					{
						String sUid = gFunction.encodeHexStr(uid);
						AddTagToTable(aip_id, tag_id, sUid);
					}
				}
				if (b_iso14443a)
				{
					Integer aip_id = new Integer(0);
					Integer tag_id = new Integer(0);
					Integer ant_id = new Integer(0);
					byte[] uid = new byte[32];
					Byte uidlen = new Byte((byte) 0);

					nret = rfidlib_aip_iso14443A.ISO14443A_ParseTagDataReport(
							dnhReport, aip_id, tag_id, ant_id, uid, uidlen); //
					if (nret == 0)
					{

						String sUid = gFunction.encodeHexStr(uid, uidlen);
						AddTagToTable(aip_id, tag_id, sUid);
					}
				}
				dnhReport = rfidlib_reader.RDR_GetTagDataReport(m_hr,
						rfid_def.RFID_SEEK_NEXT);
			}
		}

		if (InvenParamSpecList != 0)
		{
			rfidlib_reader.DNODE_Destroy(InvenParamSpecList);
		}
		rfidlib_reader.RDR_ResetCommuImmeTimeout(m_hr);
		EnableInventoryCtr(false);
		b_inventoryFlg = false;
	}

	private String GetTagtypeName(int AIPType, int tagType)
	{
		String tagtypeName = "";
		if (AIPType == rfid_def.RFID_APL_ISO15693_ID
				&& tagType == rfid_def.RFID_ISO15693_PICC_ICODE_SLI_ID)
		{
			tagtypeName = "NXP ICODE SLI";
		}
		else if (AIPType == rfid_def.RFID_APL_ISO15693_ID
				&& tagType == rfid_def.RFID_ISO15693_PICC_TI_HFI_PLUS_ID)
		{
			tagtypeName = "Ti HF-I Plus";
		}
		else if (AIPType == rfid_def.RFID_APL_ISO15693_ID
				&& tagType == rfid_def.RFID_ISO15693_PICC_ST_M24LRXX_ID)
		{
			tagtypeName = "ST M24LRxx";
		}
		else if (AIPType == rfid_def.RFID_APL_ISO15693_ID
				&& tagType == rfid_def.RFID_ISO15693_PICC_FUJ_MB89R118C_ID)
		{
			tagtypeName = "Fujitsu MB89R118C";
		}
		else if (AIPType == rfid_def.RFID_APL_ISO15693_ID
				&& tagType == rfid_def.RFID_ISO15693_PICC_ST_M24LR64_ID)
		{
			tagtypeName = "ST M24LR64";
		}
		else if (AIPType == rfid_def.RFID_APL_ISO15693_ID
				&& tagType == rfid_def.RFID_ISO15693_PICC_ST_M24LR16E_ID)
		{
			tagtypeName = "ST M24LR16E";
		}
		else if (AIPType == rfid_def.RFID_APL_ISO15693_ID
				&& tagType == rfid_def.RFID_ISO15693_PICC_ICODE_SLIX_ID)
		{
			tagtypeName = "NXP ICODE SLIX";
		}
		else if (AIPType == rfid_def.RFID_APL_ISO15693_ID
				&& tagType == rfid_def.RFID_ISO15693_PICC_TIHFI_STANDARD_ID)
		{
			tagtypeName = "Ti HF-I Standard";
		}
		else if (AIPType == rfid_def.RFID_APL_ISO15693_ID
				&& tagType == rfid_def.RFID_ISO15693_PICC_TIHFI_PRO_ID)
		{
			tagtypeName = "Ti HF-I Pro";
		}
		else if (AIPType == rfid_def.RFID_APL_ISO14443A_ID
				&& tagType == rfid_def.RFID_ISO14443A_PICC_NXP_ULTRALIGHT_ID)
		{
			tagtypeName = "NXP Mifare Ultralight";
		}
		else if (AIPType == rfid_def.RFID_APL_ISO14443A_ID
				&& tagType == rfid_def.RFID_ISO14443A_PICC_NXP_MIFARE_S50_ID)
		{
			tagtypeName = "NXP Mifare S50";
		}
		else if (AIPType == rfid_def.RFID_APL_ISO14443A_ID
				&& tagType == rfid_def.RFID_ISO14443A_PICC_NXP_MIFARE_S70_ID)
		{
			tagtypeName = "NXP Mifare S70";
		}
		else
		{
			tagtypeName = "Unknown Tag";
		}
		return tagtypeName;
	}

	private void EnableAllCtr(boolean isOpen)
	{
		cmbDevType.setEnabled(!isOpen);
		cmbCommType.setEnabled(!isOpen);
		btnOpen.setEnabled(!isOpen);
		btnClose.setEnabled(isOpen);
		btnGetRfidInfo.setEnabled(isOpen);
		cmbComName.setEnabled(!isOpen);
		textIP.setEnabled(!isOpen);
		textPort.setEnabled(!isOpen);
		checkOnlyNew.setEnabled(isOpen);
		checkAfiMatch.setEnabled(isOpen);
		textAFI.setEnabled(isOpen);
		checkEnable14443A.setEnabled(isOpen);
		btnStartInventory.setEnabled(isOpen);
		btnStopInventory.setEnabled(isOpen);
		cmbAddrMode_iso15693.setEnabled(isOpen);
		cmbUid_iso15693.setEnabled(isOpen);
		btnConnect_iso15693.setEnabled(isOpen);
		btnDidconnect.setEnabled(isOpen);
		btnGetTagInfo_iso15693.setEnabled(isOpen);
		textBlkData_iso15693.setEnabled(isOpen);
		cmbBlkaddr_iso15693.setEnabled(isOpen);
		cmbBlkNum_iso15693.setEnabled(isOpen);
		btnReadSigle_iso15693.setEnabled(isOpen);
		btnReadMul_iso15693.setEnabled(isOpen);
		btnWriteMutiple_iso15693.setEnabled(isOpen);
		btnGetsecState_iso15693.setEnabled(isOpen);
		textAfiVal.setEnabled(isOpen);
		btnWriteAfi.setEnabled(isOpen);
		textDsfidVal.setEnabled(isOpen);
		btnWriteDsfid.setEnabled(isOpen);
		btnEnableEAS.setEnabled(isOpen);
		btnDisableEAS.setEnabled(isOpen);
		btnEAScheck.setEnabled(isOpen);
		cmbUid_S50.setEnabled(isOpen);
		btnConnect_S50.setEnabled(isOpen);
		btnDisconnect_S50.setEnabled(isOpen);
		cmbBlkaddr_S50.setEnabled(isOpen);
		cmbKeyType_S50.setEnabled(isOpen);
		textKey_S50.setEnabled(isOpen);
		btnAuthenticate_S50.setEnabled(isOpen);
		textBlkData_S50.setEnabled(isOpen);
		btnReadBlk_S50.setEnabled(isOpen);
		btnWriteBlk_S50.setEnabled(isOpen);
		textValue_S50.setEnabled(isOpen);
		btnFormateValBlk_S50.setEnabled(isOpen);
		btnIncrement_S50.setEnabled(isOpen);
		btnDecrement_S50.setEnabled(isOpen);
		btnRestore_S50.setEnabled(isOpen);

		btnConnect_Ultralight.setEnabled(isOpen);
		// btnDisconnect_Ultralight.setEnabled(isOpen);
		comboBoxAddr_Ultralight.setEnabled(isOpen);
		comboBoxNum_Utralight.setEnabled(isOpen);
		cmbUid_Ultralight.setEnabled(isOpen);
		btnWriteBlk_Utralight.setEnabled(isOpen);
		;
		btnReadBlk_Utralight.setEnabled(isOpen);
	}

	private void EnableTagCtr(boolean isConnect)
	{
		cmbAddrMode_iso15693.setEnabled(!isConnect);
		cmbUid_iso15693.setEnabled(!isConnect);
		btnConnect_iso15693.setEnabled(!isConnect);
		btnDidconnect.setEnabled(isConnect);
		btnGetTagInfo_iso15693.setEnabled(isConnect);
		textBlkData_iso15693.setEnabled(isConnect);
		cmbBlkaddr_iso15693.setEnabled(isConnect);
		cmbBlkNum_iso15693.setEnabled(isConnect);
		btnReadSigle_iso15693.setEnabled(isConnect);
		btnReadMul_iso15693.setEnabled(isConnect);
		btnWriteMutiple_iso15693.setEnabled(isConnect);
		btnGetsecState_iso15693.setEnabled(isConnect);
		textAfiVal.setEnabled(isConnect);
		btnWriteAfi.setEnabled(isConnect);
		textDsfidVal.setEnabled(isConnect);
		btnWriteDsfid.setEnabled(isConnect);
		btnEnableEAS.setEnabled(isConnect);
		btnDisableEAS.setEnabled(isConnect);
		btnEAScheck.setEnabled(isConnect);

		cmbUid_S50.setEnabled(!isConnect);
		btnConnect_S50.setEnabled(!isConnect);
		btnDisconnect_S50.setEnabled(isConnect);
		cmbBlkaddr_S50.setEnabled(isConnect);
		cmbKeyType_S50.setEnabled(isConnect);
		textKey_S50.setEnabled(isConnect);
		btnAuthenticate_S50.setEnabled(isConnect);
		textBlkData_S50.setEnabled(isConnect);
		btnWriteBlk_S50.setEnabled(isConnect);
		btnReadBlk_S50.setEnabled(isConnect);
		textValue_S50.setEnabled(isConnect);
		btnFormateValBlk_S50.setEnabled(isConnect);
		btnIncrement_S50.setEnabled(isConnect);
		btnDecrement_S50.setEnabled(isConnect);
		btnRestore_S50.setEnabled(isConnect);

		cmbUid_Ultralight.setEnabled(!isConnect);
		btnConnect_Ultralight.setEnabled(!isConnect);
		;
		btnDisconnect_Ultralight.setEnabled(isConnect);
		;
		comboBoxAddr_Ultralight.setEnabled(isConnect);
		;
		comboBoxNum_Utralight.setEnabled(isConnect);
		;
		btnWriteBlk_Utralight.setEnabled(isConnect);
		btnReadBlk_Utralight.setEnabled(isConnect);
		textField_Utralight.setEnabled(isConnect);
	}

	private void EnableInventoryCtr(boolean isInventory)
	{
		btnStartInventory.setEnabled(!isInventory);
		btnStopInventory.setEnabled(isInventory);
		checkOnlyNew.setEnabled(!isInventory);
		checkAfiMatch.setEnabled(!isInventory);
		textAFI.setEnabled(!isInventory);
		checkEnable14443A.setEnabled(!isInventory);
	}

	private byte IntToByte(int n)
	{
		int m_tmp = n % 100;
		return (byte) (((m_tmp / 10) << 4) | (m_tmp % 10));
	}

	private void AddTagToTable(int aip_id, int tag_id, String sUid)
	{
		String tagName = GetTagtypeName(aip_id, tag_id);
		for (int i = 0; i < tableInventory.getRowCount(); i++)
		{
			if (sUid.equals(tableInventory.getValueAt(i, 1).toString()))
			{
				return;
			}
		}
		Vector<String> vectorRow = new Vector<String>();
		vectorRow.addElement(new String(tagName));
		vectorRow.addElement(new String(sUid));
		vRowData.addElement(vectorRow);

		TableModel.setDataVector(vRowData, vTitile);
		tableInventory.setModel(TableModel);

		if (aip_id == rfid_def.RFID_APL_ISO15693_ID)
		{
			cmbUid_iso15693.addItem(sUid);
		}
		else if (aip_id == rfid_def.RFID_APL_ISO14443A_ID)
		{
			if (tag_id == rfid_def.RFID_ISO14443A_PICC_NXP_MIFARE_S50_ID
					|| tag_id == rfid_def.RFID_ISO14443A_PICC_NXP_MIFARE_S70_ID)
			{
				cmbUid_S50.addItem(sUid);
			}
			else if (tag_id == rfid_def.RFID_ISO14443A_PICC_NXP_ULTRALIGHT_ID)
			{
				cmbUid_Ultralight.addItem(sUid);
			}
		}
	}
}
