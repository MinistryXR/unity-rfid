Imports System.Text
Public Class MainFrm
    Private hreader As UIntPtr = UIntPtr.Zero
    Private htag As UIntPtr = UIntPtr.Zero
    Private Sub MainFrm_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        RFIDLIB.rfidlib_reader.RDR_LoadReaderDrivers("\Drivers") ' XXXX Verzeichnis

        Dim nCount As UInt32
        nCount = RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverCount()
        Dim i As Integer
        For i = 0 To nCount - 1
            Dim nSize As UInt32
            Dim strName As New StringBuilder()
            strName.Append(ControlChars.NullChar, 64)
            nSize = CType(strName.Capacity, UInt32)
            RFIDLIB.rfidlib_reader.RDR_GetLoadedReaderDriverOpt(i, "NAME", strName, nSize)
            ComboBoxReader.Items.Add(strName.ToString())
        Next
        ComboBoxReader.SelectedIndex = 0

        ComboBoxComm.Items.Add("COM")
        ComboBoxComm.Items.Add("NET")
        ComboBoxComm.Items.Add("USB")
        ComboBoxComm.SelectedIndex = 0

        ComboBoxBaud.Items.Add("38400")
        ComboBoxBaud.SelectedIndex = 0

        ComboBoxFrame.Items.Add("8E1")
        ComboBoxFrame.Items.Add("8O1")
        ComboBoxFrame.Items.Add("8N1")
        ComboBoxFrame.SelectedIndex = 0

        nCount = RFIDLIB.rfidlib_reader.COMPort_Enum()
        If nCount > 0 Then
            For i = 0 To nCount - 1
                Dim nSize As UInt32
                Dim nameBuf As New StringBuilder()
                nameBuf.Append(ControlChars.NullChar, 64)
                nSize = CType(nameBuf.Capacity, UInt32)
                RFIDLIB.rfidlib_reader.COMPort_GetEnumItem(i, nameBuf, nSize)
                ComboBoxCom.Items.Add(nameBuf.ToString)
            Next
            ComboBoxCom.SelectedIndex = 0
        End If

        ComboBoxReader.Enabled = True
        ComboBoxComm.Enabled = True
        ButtonOpen.Enabled = True
        ButtonClose.Enabled = False
        ComboBoxCom.Enabled = True
        ComboBoxBaud.Enabled = True
        ComboBoxFrame.Enabled = True
        TextBoxIpAddress.Enabled = True
        TextBoxPort.Enabled = True

        comboBoxUid.Enabled = False
        buttonInventory.Enabled = False
        buttonConnect.Enabled = False
        buttonDisconnect.Enabled = False
        textBoxUriAddress.Enabled = False
        buttonWriteUri.Enabled = False
        checkBoxLock.Enabled = False
        buttonReadUri.Enabled = False

    End Sub

    Private Sub ButtonOpen_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ButtonOpen.Click
        Dim iret As Integer
        Dim commTypeIdx As Integer = ComboBoxComm.SelectedIndex
        Dim readerDriverName As String = ComboBoxReader.Text
        Dim connstr As String = ""
        If commTypeIdx = 0 Then
            connstr = (Convert.ToString(RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=") & readerDriverName) + ";" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_COM + ";" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMNAME + "=" + ComboBoxCom.Text + ";" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMBARUD + "=" + ComboBoxBaud.Text + ";" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMFRAME + "=" + ComboBoxFrame.Text + ";" + RFIDLIB.rfidlib_def.CONNSTR_NAME_BUSADDR + "=" + "255"
        ElseIf commTypeIdx = 1 Then
            Dim ipAddr As String
            Dim port As UInt16
            ipAddr = TextBoxIpAddress.Text
            port = CType(Integer.Parse(TextBoxPort.Text), UInt16)
            connstr = (Convert.ToString((Convert.ToString(RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=") & readerDriverName) + ";" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_NET + ";" + RFIDLIB.rfidlib_def.CONNSTR_NAME_REMOTEIP + "=") & ipAddr) + ";" + RFIDLIB.rfidlib_def.CONNSTR_NAME_REMOTEPORT + "=" + port.ToString() + ";" + RFIDLIB.rfidlib_def.CONNSTR_NAME_LOCALIP + "=" + ""
        ElseIf commTypeIdx = 2 Then
            connstr = (Convert.ToString(RFIDLIB.rfidlib_def.CONNSTR_NAME_RDTYPE + "=") & readerDriverName) + ";" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE + "=" + RFIDLIB.rfidlib_def.CONNSTR_NAME_COMMTYPE_USB + ";" + RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDADDRMODE + "=" + "0" + ";" + RFIDLIB.rfidlib_def.CONNSTR_NAME_HIDSERNUM + "=" + ""
        End If
        iret = RFIDLIB.rfidlib_reader.RDR_Open(connstr, hreader)
        If iret = 0 Then
            ComboBoxReader.Enabled = False
            ComboBoxComm.Enabled = False
            ButtonOpen.Enabled = False
            ButtonClose.Enabled = True
            ComboBoxCom.Enabled = False
            ComboBoxBaud.Enabled = False
            ComboBoxFrame.Enabled = False
            TextBoxIpAddress.Enabled = False
            TextBoxPort.Enabled = False
            buttonConnect.Enabled = True
            buttonInventory.Enabled = True
            comboBoxUid.Enabled = True
        Else
            MessageBox.Show("Failed")
        End If
      
    End Sub

    Private Sub ButtonClose_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ButtonClose.Click
        If hreader <> 0 Then
            If htag <> UIntPtr.Zero Then
                MessageBox.Show("Please disconnect the tag first.")
                Return
            End If
            RFIDLIB.rfidlib_reader.RDR_Close(hreader)
            hreader = UIntPtr.Zero
            ComboBoxReader.Enabled = True
            ComboBoxComm.Enabled = True
            ButtonOpen.Enabled = True
            ButtonClose.Enabled = False
            ComboBoxCom.Enabled = True
            ComboBoxBaud.Enabled = True
            ComboBoxFrame.Enabled = True
            TextBoxIpAddress.Enabled = True
            TextBoxPort.Enabled = True

            comboBoxUid.Enabled = False
            buttonInventory.Enabled = False
            buttonConnect.Enabled = False
            buttonDisconnect.Enabled = False
            textBoxUriAddress.Enabled = False
            buttonWriteUri.Enabled = False
            checkBoxLock.Enabled = False
            buttonReadUri.Enabled = False
        End If
    End Sub
    Public Shared Function StringToByteArrayFastest(ByVal hex As String) As Byte()
        If hex.Length Mod 2 = 1 Then
            Throw New Exception("The binary key cannot have an odd number of digits")
        End If

        Dim len As Integer = hex.Length >> 1
        Dim arr As Byte() = New Byte(len - 1) {}

        For i As Integer = 0 To len - 1
            arr(i) = CByte((GetHexVal(hex(i << 1)) << 4) + (GetHexVal(hex((i << 1) + 1))))
        Next

        Return arr
    End Function

    Public Shared Function GetHexVal(ByVal hex As Char) As Integer
        Dim data As Integer = Val(hex.ToString)
        Dim str As String = hex.ToString

        If str = "0" Then
            data = 0
        ElseIf str = "1" Then
            data = 1
        ElseIf str = "2" Then
            data = 2
        ElseIf str = "3" Then
            data = 3
        ElseIf str = "4" Then
            data = 4
        ElseIf str = "5" Then
            data = 5
        ElseIf str = "6" Then
            data = 6
        ElseIf str = "7" Then
            data = 7
        ElseIf str = "8" Then
            data = 8
        ElseIf str = "9" Then
            data = 9
        ElseIf str = "a" Or str = "A" Then
            data = 10
        ElseIf str = "b" Or str = "B" Then
            data = 11
        ElseIf str = "c" Or str = "C" Then
            data = 12
        ElseIf str = "d" Or str = "D" Then
            data = 13
        ElseIf str = "e" Or str = "E" Then
            data = 14
        ElseIf str = "f" Or str = "F" Then
            data = 15
        Else
            data = -1
        End If
        Return data
    End Function
    Private Sub buttonConnect_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles buttonConnect.Click
        Dim idx As Integer = comboBoxUid.SelectedIndex
        Dim iret As Integer
        If idx < 0 Then
            MessageBox.Show("Please select a tag!")
        End If
        Dim tag As TagInfo = comboBoxUid.SelectedItem
        Dim uid As Byte() = StringToByteArrayFastest(tag.m_uid)
        If tag.aip_id = RFIDLIB.rfidlib_def.RFID_APL_ISO15693_ID Then
            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_Connect(hreader, tag.tag_id, 1, uid, htag)
            If iret <> 0 Then
                MessageBox.Show("failed!")
                Return
            End If
        ElseIf tag.aip_id = RFIDLIB.rfidlib_def.RFID_APL_ISO14443A_ID Then
            iret = RFIDLIB.rfidlib_aip_iso14443A.NTAG21x_Connect(hreader, uid, htag)
            If iret <> 0 Then
                MessageBox.Show("failed!")
                Return
            End If
        Else
            MessageBox.Show("failed!")
        End If
        buttonConnect.Enabled = False
        comboBoxUid.Enabled = False
        buttonInventory.Enabled = False
        buttonDisconnect.Enabled = True
        textBoxUriAddress.Enabled = True
        buttonWriteUri.Enabled = True
        checkBoxLock.Enabled = True
        buttonReadUri.Enabled = True
    End Sub

    Private Sub buttonDisconnect_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles buttonDisconnect.Click
        If htag <> 0 Then
            RFIDLIB.rfidlib_reader.RDR_TagDisconnect(hreader, htag)
            htag = UIntPtr.Zero
        End If
        buttonConnect.Enabled = True
        comboBoxUid.Enabled = True
        buttonInventory.Enabled = True
        buttonDisconnect.Enabled = False
        textBoxUriAddress.Enabled = False
        buttonWriteUri.Enabled = False
        checkBoxLock.Enabled = False
        buttonReadUri.Enabled = False
    End Sub

    Private Sub buttonInventory_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles buttonInventory.Click
        Dim iret As Integer = 0
        comboBoxUid.Items.Clear()
        Dim dnInvenParamList As UIntPtr = RFIDLIB.rfidlib_reader.RDR_CreateInvenParamSpecList()
        RFIDLIB.rfidlib_aip_iso15693.ISO15693_CreateInvenParam(dnInvenParamList, 0, 0, 0, 0)
        RFIDLIB.rfidlib_aip_iso14443A.ISO14443A_CreateInvenParam(dnInvenParamList, 0)
        iret = RFIDLIB.rfidlib_reader.RDR_TagInventory(hreader, RFIDLIB.rfidlib_def.AI_TYPE_NEW, 0, Nothing, dnInvenParamList)
        If iret <> 0 Then
            Return
        End If
        Dim TagDataReport As UIntPtr = UIntPtr.Zero
        TagDataReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_FIRST)
        While TagDataReport <> UIntPtr.Zero
            Dim aip_id As UInt32 = 0
            Dim tag_id As UInt32 = 0
            Dim ant_id As UInt32 = 0
            Dim dsfid As Byte = 0
            Dim uid As Byte() = New Byte(16) {}
            Dim uidLen As Byte = 0
            Dim strUid As String = ""

            iret = RFIDLIB.rfidlib_aip_iso15693.ISO15693_ParseTagDataReport(TagDataReport, aip_id, tag_id, ant_id, dsfid, uid)
            If iret = 0 Then
                strUid = BitConverter.ToString(uid, 0, 8).Replace("-", String.Empty)
                comboBoxUid.Items.Add(New TagInfo(strUid, aip_id, tag_id))
                GoTo NextTag
            End If

            iret = RFIDLIB.rfidlib_aip_iso14443A.ISO14443A_ParseTagDataReport(TagDataReport, aip_id, tag_id, ant_id, uid, uidLen)
            If iret = 0 Then
                strUid = BitConverter.ToString(uid, 0, uidLen).Replace("-", String.Empty)
                comboBoxUid.Items.Add(New TagInfo(strUid, aip_id, tag_id))
            End If

NextTag:
            TagDataReport = RFIDLIB.rfidlib_reader.RDR_GetTagDataReport(hreader, RFIDLIB.rfidlib_def.RFID_SEEK_NEXT)
        End While
        If dnInvenParamList <> UIntPtr.Zero Then
            RFIDLIB.rfidlib_reader.DNODE_Destroy(dnInvenParamList)
        End If

        If comboBoxUid.Items.Count > 0 Then
            comboBoxUid.SelectedIndex = 0
        End If
    End Sub

    Private Sub buttonWriteUri_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles buttonWriteUri.Click
        Dim nret As Integer = 0
        Dim ndef As UIntPtr = RFIDLIB.rfidlib_nfc.nfc_CreateUriNdef(textBoxUriAddress.Text, 0)
        Dim IsLock As Byte
        If checkBoxLock.Checked Then
            IsLock = 1
        Else
            IsLock = 0
        End If
        nret = RFIDLIB.rfidlib_nfc.nfc_WriteNdef(hreader, htag, ndef, IsLock)
        If nret <> 0 Then
            MessageBox.Show("Write uri failed!")
            GoTo EndExit
        End If
        MessageBox.Show("Write uri successfully!")
EndExit:
        If ndef <> UIntPtr.Zero Then
            RFIDLIB.rfidlib_reader.DNODE_Destroy(ndef)
        End If
    End Sub

    Private Sub buttonReadUri_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles buttonReadUri.Click
        Dim nret As Integer = 0
        Dim NedfType As Byte = 0
        Dim NetType As Byte = 0
        Dim Nedf As UIntPtr = UIntPtr.Zero
        Dim addr As StringBuilder = New StringBuilder()
        addr.Append(ControlChars.NullChar, 512)
        nret = RFIDLIB.rfidlib_nfc.nfc_ReadNdef(hreader, htag, Nedf, NedfType)
        If nret <> 0 Then
            GoTo EndExit
        End If

        nret = RFIDLIB.rfidlib_nfc.nfc_ParseNdefByUri(Nedf, addr, addr.Length, NetType)
        If nret <> 0 Then
            GoTo EndExit
        End If
        textBoxUriAddress.Text = addr.ToString()

EndExit:
        If Nedf <> UIntPtr.Zero Then
            RFIDLIB.rfidlib_reader.DNODE_Destroy(Nedf)
            Nedf = UIntPtr.Zero
        End If
    End Sub
End Class

Public Class TagInfo
    Public m_uid As String
    Public aip_id As UInt32 = 0
    Public tag_id As UInt32 = 0
    Public Sub New(ByVal uid As String, ByVal aip As UInt32, ByVal tagType As UInt32)
        m_uid = uid
        aip_id = aip
        tag_id = tagType
    End Sub
    Public Overrides Function ToString() As String
        Return m_uid.ToString()
    End Function

End Class