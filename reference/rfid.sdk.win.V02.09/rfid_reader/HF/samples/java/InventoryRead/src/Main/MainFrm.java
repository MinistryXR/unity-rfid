package Main;
import java.awt.*;
import java.awt.event.*;
import java.util.Vector;

import javax.swing.*;

import RFID.rfid_def;
import RFID.rfidlib_AIP_ISO15693;
import RFID.rfidlib_reader;

public class MainFrm extends JFrame implements ActionListener
{
	private static final long serialVersionUID = 1L;
	private static final String OPEN = "Open";
	private static final String CLOSE = "Close";
	private static final String START = "Start";
	private static final String STOP = "Stop";
	private static final String INFORMATION = "Info";
	private JLabel jlbReaderType;
	private JComboBox<String> jcmbReaderType;
	private JLabel jlbComList;
	private JComboBox<String> jcmbComList;
	private JButton jbOpen, jbClose, jbStart, jbStop, jbInformation;
	private JTable tbTagInfo;
	private Vector<Object> tagRowNames = new Vector<>();
	private Thread m_inventoryThrd = null;
	private boolean bThreadRun = false;
	private long m_reader = 0;
	
	private JLabel jlbBlkAddr;
	private JComboBox<String> jcmbBlkAddr;
	
	private JLabel jlbBlkNum;
	private JComboBox<String> jcmbBlkNum;
	
	private int mBlockAddr = 0;
	private int mBlockNumberToRead=1;

	public static void main(String[] args)
	{
		new MainFrm();
	}

	public MainFrm()
	{
		Vector<Object> columnNames = new Vector<>();
		columnNames.addElement("UID");
		columnNames.addElement("Block Data");
		//columnNames.addElement("Count");

		jlbReaderType = new JLabel("Communication:", JLabel.RIGHT);
		jcmbReaderType = new JComboBox<String>();

		jlbComList = new JLabel("Serial Port:", JLabel.RIGHT);
		jcmbComList = new JComboBox<String>();
		jbOpen = new JButton(OPEN);
		jbClose = new JButton(CLOSE);
		jbInformation = new JButton(INFORMATION);
		jbStart = new JButton(START);
		jbStop = new JButton(STOP);
		tbTagInfo = new JTable(tagRowNames, columnNames);
		jlbBlkAddr = new JLabel("Address:",JLabel.RIGHT);
		jcmbBlkAddr = new JComboBox<String>();
		jlbBlkNum = new JLabel("Block Num:",JLabel.RIGHT);
		jcmbBlkNum = new JComboBox<String>();
		this.setLayout(null);
		JScrollPane scrollPane = new JScrollPane(tbTagInfo);

		jlbReaderType.setBounds(15, 15, 120, 20);
		jcmbReaderType.setBounds(140, 15, 120, 20);
		jlbComList.setBounds(240, 15, 120, 20);
		jcmbComList.setBounds(370, 15, 120, 20);
		jbOpen.setBounds(80, 50, 100, 30);
		jbClose.setBounds(200, 50, 100, 30);
		jbInformation.setBounds(320, 50, 100, 30);
		jbStart.setBounds(20, 90, 100, 30);
		jbStop.setBounds(140, 90, 100, 30);
		jlbBlkAddr.setBounds(230, 90, 70, 30);
		jcmbBlkAddr.setBounds(310, 90, 55, 30);
		
		jlbBlkNum.setBounds(360, 90, 80, 30);
		jcmbBlkNum.setBounds(450, 90, 55, 30);
		
		scrollPane.setBounds(15, 130, 500, 390);
		getContentPane().add(scrollPane, BorderLayout.CENTER);
		this.add(jcmbReaderType);
		this.add(jlbReaderType);
		this.add(jlbComList);
		this.add(jcmbComList);
		this.add(jbOpen);
		this.add(jbClose);
		this.add(jbStart);
		this.add(jbStop);
		this.add(jbInformation);
		this.setTitle("TagInventory");
		this.add(jlbBlkAddr);
		this.add(jlbBlkNum);
		this.add(jcmbBlkAddr);
		this.add(jcmbBlkNum);
		this.setSize(530, 600);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setVisible(true);

		this.setResizable(false);
		jbOpen.addActionListener(this);
		jbClose.addActionListener(this);
		jbStart.addActionListener(this);
		jbStop.addActionListener(this);
		jbInformation.addActionListener(this);

		jcmbComList.setEnabled(true);
		jcmbReaderType.setEnabled(true);
		jbOpen.setEnabled(true);
		jbClose.setEnabled(false);
		jbStart.setEnabled(false);
		jbStop.setEnabled(false);
		jbInformation.setEnabled(false);
		jcmbBlkAddr.setEnabled(false);
		jcmbBlkNum.setEnabled(false);
		
		LoadLibrary();
		
		int comCnt = rfidlib_reader.COMPort_Enum();
		for (int i = 0; i < comCnt; i++)
		{
			String comName = rfidlib_reader.COMPort_GetEnumItem(i);
			jcmbComList.addItem(comName);
		}
		
		for (int i = 0; i < 28; i++)
		{
			jcmbBlkAddr.addItem(i+"");
		}
		for (int i = 1; i <= 8; i++)
		{
			jcmbBlkNum.addItem(i+"");
		}
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
		//rfidlib_aip_iso14443A.LoadLib(libPath, osType, arType);

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
					jcmbReaderType.addItem(sDes);
				}
			}
		}
		if (m_cnt > 0)
		{
			jcmbReaderType.setSelectedIndex(0);
		}
	}

	private void Open()
	{
		String strConn = "";
		strConn = String
				.format("RDType=RD5100;CommType=COM;COMName=%s;BaudRate=38400;Frame=8E1;BusAddr=255",
						jcmbComList.getSelectedItem().toString());
		Long hr = new Long(0);
		int iret = rfidlib_reader.RDR_Open(strConn, hr);
		if (iret == 0)
		{
			jcmbComList.setEnabled(false);
			jcmbReaderType.setEnabled(false);
			jbOpen.setEnabled(false);
			jbClose.setEnabled(true);
			jbStart.setEnabled(true);
			jbStop.setEnabled(false);
			jbInformation.setEnabled(true);
			jcmbBlkAddr.setEnabled(true);
			jcmbBlkNum.setEnabled(true);
			m_reader = hr;
		}
	}

	private void Close()
	{
		int iret = rfidlib_reader.RDR_Close(m_reader);
		if (iret == 0)
		{
			jcmbReaderType.setEnabled(true);
			jcmbComList.setEnabled(true);
			jbOpen.setEnabled(true);
			jbClose.setEnabled(false);
			jbStart.setEnabled(false);
			jbStop.setEnabled(false);
			jbInformation.setEnabled(false);
			jcmbBlkAddr.setEnabled(false);
			jcmbBlkNum.setEnabled(false);
		}
	}

	private void StartInventory()
	{
		jbClose.setEnabled(false);
		jbStart.setEnabled(false);
		jbStop.setEnabled(true);
		jbInformation.setEnabled(false);
		jcmbBlkAddr.setEnabled(false);
		jcmbBlkNum.setEnabled(false);
		mBlockAddr = jcmbBlkAddr.getSelectedIndex();
		mBlockNumberToRead = jcmbBlkNum.getSelectedIndex()+1;
		m_inventoryThrd = new Thread(new InventoryThrd());
		m_inventoryThrd.start();
	}

	private void StopInventory()
	{

		if (m_inventoryThrd != null && m_inventoryThrd.isAlive())
		{
			bThreadRun = false;
			rfidlib_reader.RDR_SetCommuImmeTimeout(m_reader);
			jbStop.setEnabled(false);
			rfidlib_reader.RDR_ResetCommuImmeTimeout(m_reader);
		}
	}

	private void GetInformation()
	{
		StringBuilder strinfo = new StringBuilder();
		int iret = rfidlib_reader.RDR_GetReaderInfor(m_reader,strinfo);
		if (iret == 0)
		{
			JOptionPane.showMessageDialog(null, strinfo.toString());
		}
		else
		{
			JOptionPane.showMessageDialog(null,
					"Failed to get the information.Err=" + iret, "",
					JOptionPane.ERROR_MESSAGE);
		}
	}

	@Override
	public void actionPerformed(ActionEvent e)
	{
		switch (e.getActionCommand())
		{
		case OPEN:
			Open();
			break;
		case CLOSE:
			Close();
			break;
		case START:
			StartInventory();
			break;
		case STOP:
			StopInventory();
			break;
		case INFORMATION:
			GetInformation();
			break;
		default:
			break;
		}
	}

	private void ShowTag(Vector<TagInfo> tags)
	{
		tagRowNames.clear();
		if (tags != null)
		{
			for (TagInfo t : tags)
			{
				boolean bNeedAdd = true;
				Vector<Object> tableValues = new Vector<>();
				if (bNeedAdd)
				{
					tableValues.add(t.uid);
					tableValues.add(t.blkData);
					tagRowNames.add(tableValues);
				}
			}
		}

		javax.swing.SwingUtilities.invokeLater(new Runnable()
		{
			public void run()
			{
				tbTagInfo.updateUI();
			}
		});

	}

	private void ThreadEndCallback()
	{
		javax.swing.SwingUtilities.invokeLater(new Runnable()
		{
			public void run()
			{
				jbClose.setEnabled(true);
				jbStart.setEnabled(true);
				jbStop.setEnabled(false);
				jbInformation.setEnabled(true);
				jcmbBlkAddr.setEnabled(true);
				jcmbBlkNum.setEnabled(true);
			}
		});
	}

	private class InventoryThrd implements Runnable
	{
		public void run()
		{
			int iret = -1;
			byte AntennaIDs[] = null;//{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			bThreadRun = true;
			long dnhReport = 0;
			long InvenParamSpecList = rfidlib_reader
					.RDR_CreateInvenParamSpecList();
			long hIso15693InvenParam = rfidlib_AIP_ISO15693.ISO15693_CreateInvenParam(InvenParamSpecList,
					(byte) 0, (byte) 0x00, (byte) 0x00, (byte) 0x00);
			if (hIso15693InvenParam<=0)
			{
				return ;
			}
			iret = rfidlib_AIP_ISO15693.ISO15693_SetInvenReadParam(hIso15693InvenParam,(byte) 0,mBlockAddr,mBlockNumberToRead);
			if (iret!=0)
			{
				return;
			}
			ShowTag(null);
			while (bThreadRun)
			{
				Vector<TagInfo> tags = new Vector<>();
				iret = rfidlib_reader.RDR_TagInventory(m_reader,
						rfid_def.AI_TYPE_NEW, (byte) (AntennaIDs==null?0:AntennaIDs.length),
						AntennaIDs, InvenParamSpecList);
				if (iret != 0)
				{
					continue;
				}
				dnhReport = rfidlib_reader.RDR_GetTagDataReport(m_reader,
						rfid_def.RFID_SEEK_FIRST);
				while (dnhReport != 0)
				{
					Integer numOfBlocks = new Integer(0);
					byte uid[] = new byte[8];
					byte blkData[] = new byte[5*mBlockNumberToRead];
					Integer nSize = new Integer(blkData.length);
					
					iret = rfidlib_AIP_ISO15693.ISO15693_ParseInventoryReadReport(dnhReport,
							uid,
							numOfBlocks,
							blkData,
							nSize);
					
					if (iret == 0)
					{
						String sUid = RFID.gFunction.encodeHexStr(uid);
						String sBlock = RFID.gFunction.encodeHexStr(blkData,nSize);
						TagInfo tag = new TagInfo();
						tag.uid = sUid;
						tag.blkData = sBlock;
						tags.add(tag);
					}
					dnhReport = rfidlib_reader.RDR_GetTagDataReport(m_reader,
							rfid_def.RFID_SEEK_NEXT);
				}
				ShowTag(tags);
			}
			if (InvenParamSpecList != 0)
			{
				rfidlib_reader.DNODE_Destroy(InvenParamSpecList);
			}
			ThreadEndCallback();
			bThreadRun = false;
		}

	}

	private class TagInfo
	{
		public String uid;
		public String blkData="";
	}
}
