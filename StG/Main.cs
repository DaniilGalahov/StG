using AESBridge;
using StGBridge;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace StG
{
    public partial class Main : Form
    {
        private string passwordRegexPattern = $"^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[^\\da-zA-Z]).{{8,}}$";

        public Main()
        {
            InitializeComponent();
            toolTip.SetToolTip(textBox_Embed_DataFilePath, "Path to file with data-to-hide");
            toolTip.SetToolTip(textBox_Embed_CarrierFilePath, "Path to .png image file in which you want to hide data");
            toolTip.SetToolTip(textBox_Embed_Password, "At least 8 symbols with string and capital letters, digits and special characters");
            toolTip.SetToolTip(textBox_Embed_StegoFilePath, "Path to result .png image file");

            toolTip.SetToolTip(textBox_Extract_StegoFilePath, "Path to .png image file containing hidden data");
            toolTip.SetToolTip(textBox_Extract_Password, "Same password you used on embedding");
            toolTip.SetToolTip(textBox_Extract_DataFilePath, "Path to result file with extracted data");
        }

        private void button_Embed_SelectDataFile_Click(object sender, EventArgs e)
        {
            if (openFileDialog_SelectDataFile.ShowDialog() == DialogResult.OK)
            {
                textBox_Embed_DataFilePath.Text = openFileDialog_SelectDataFile.FileName;
            }
        }

        private void button_Embed_SelectCarrierFile_Click(object sender, EventArgs e)
        {
            if(openFileDialog_SelectCarrierFile.ShowDialog() == DialogResult.OK)
            {
                textBox_Embed_CarrierFilePath.Text = openFileDialog_SelectCarrierFile.FileName;
            }
        }

        private void button_Embed_CreateStegoFile_Click(object sender, EventArgs e)
        {
            if (saveFileDialog_CreateStegoFile.ShowDialog() == DialogResult.OK)
            {
                if (File.Exists(saveFileDialog_CreateStegoFile.FileName))
                {
                    DialogResult confirmResult = MessageBox.Show
                    (
                        "Selected file already exists. Choose other file to save stego image.",
                        "Warning",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                    );

                    if (confirmResult == DialogResult.OK)
                    {
                        return;
                    }
                }

                textBox_Embed_StegoFilePath.Text = saveFileDialog_CreateStegoFile.FileName;
            }
        }

        private void button_Extract_SelectStegoFile_Click(object sender, EventArgs e)
        {
            if(openFileDialog_SelectStegoFile.ShowDialog()==DialogResult.OK)
            {
                textBox_Extract_StegoFilePath.Text = openFileDialog_SelectStegoFile.FileName;
            }
        }

        private void button_Extract_CreateDataFile_Click(object sender, EventArgs e)
        {
            if(saveFileDialog_CreateDataFile.ShowDialog()==DialogResult.OK)
            {
                if (File.Exists(saveFileDialog_CreateDataFile.FileName))
                {
                    DialogResult confirmResult = MessageBox.Show
                    (
                        "Selected file already exists. Choose other file to save extracted data.",
                        "Warning",
                        MessageBoxButtons.OK,
                        MessageBoxIcon.Error
                    );

                    if (confirmResult == DialogResult.OK)
                    {
                        return;
                    }
                }

                textBox_Extract_DataFilePath.Text = saveFileDialog_CreateDataFile.FileName;
            }
        }

        private void SetControlResponseTo(bool value)
        {
            tabMode.Enabled = value;
            
            textBox_Embed_DataFilePath.Enabled = value;
            button_Embed_SelectDataFile.Enabled = value;
            textBox_Embed_CarrierFilePath.Enabled = value;
            button_Embed_SelectCarrierFile.Enabled = value;
            textBox_Embed_Password.Enabled = value;
            comboBox_Embed_EncryptionMode.Enabled = value;
            textBox_Embed_StegoFilePath.Enabled = value;
            button_Embed_CreateStegoFile.Enabled = value;
            buttonEmbed.Enabled = value;

            textBox_Extract_StegoFilePath.Enabled = value;
            button_Extract_SelectStegoFile.Enabled = value;
            textBox_Extract_Password.Enabled = value;
            comboBox_Extract_EncryptionMode.Enabled = value;
            textBox_Extract_StegoFilePath.Enabled = value;
            button_Extract_CreateDataFile.Enabled = value;
            buttonExtract.Enabled = value;
        }

        private void DisableControls()
        {
            SetControlResponseTo(false);
        }

        private void EnableControls()
        {
            SetControlResponseTo(true);
        }

        void SetEmbedStatus(string status)
        {
            label_Embed_Status.Text = "Status: " + status;
        }

        void SetExtractStatus(string status)
        {
            label_Extract_Status.Text = "Status: " + status;
        }

        private bool EmbedFieldsReady()
        {
            if(!File.Exists(textBox_Embed_DataFilePath.Text))
            {
                SetEmbedStatus("Data file does not exist");
                return false;
            }

            if(!File.Exists(textBox_Embed_CarrierFilePath.Text))
            {
                SetEmbedStatus("Carrier image file does not exist");
                return false;
            }

            if (Path.GetExtension(textBox_Embed_CarrierFilePath.Text)!=".png")
            {
                SetEmbedStatus("Carrier image file extension incorrect");
                return false;
            }

            if (!Regex.IsMatch(textBox_Embed_Password.Text, passwordRegexPattern))
            {
                SetEmbedStatus("Password too weak");
                return false;
            }

            if((Mode)comboBox_Embed_EncryptionMode.SelectedIndex != Mode.AES128 
            && (Mode)comboBox_Embed_EncryptionMode.SelectedIndex != Mode.AES192
            && (Mode)comboBox_Embed_EncryptionMode.SelectedIndex != Mode.AES256)
            {
                SetEmbedStatus("Encryption mode incorrect");
                return false;
            }

            if (textBox_Embed_StegoFilePath.Text.Length == 0
            || !Directory.Exists(Path.GetDirectoryName(textBox_Embed_StegoFilePath.Text))
            || File.Exists(textBox_Embed_StegoFilePath.Text))
            {
                SetEmbedStatus("Stego image file path incorrect");
                return false;
            }

            return true;
        }

        private bool ExtractFieldsReady()
        {
            if (!File.Exists(textBox_Extract_StegoFilePath.Text))
            {
                SetExtractStatus("Stego image file does not exist");
                return false;
            }

            if (Path.GetExtension(textBox_Extract_StegoFilePath.Text) != ".png")
            {
                SetExtractStatus("Carrier image file extension incorrect");
                return false;
            }

            if (!Regex.IsMatch(textBox_Extract_Password.Text, passwordRegexPattern))
            {
                SetExtractStatus("Password format incorrect");
                return false;
            }

            if ((Mode)comboBox_Extract_EncryptionMode.SelectedIndex != Mode.AES128
            && (Mode)comboBox_Extract_EncryptionMode.SelectedIndex != Mode.AES192
            && (Mode)comboBox_Extract_EncryptionMode.SelectedIndex != Mode.AES256)
            {
                SetExtractStatus("Encryption mode incorrect");
                return false;
            }

            if (textBox_Extract_DataFilePath.Text.Length == 0
            || !Directory.Exists(Path.GetDirectoryName(textBox_Extract_DataFilePath.Text))
            || File.Exists(textBox_Extract_DataFilePath.Text))
            {
                SetExtractStatus("Data file path incorrect");
                return false;
            }

            return true;
        }

        private void buttonEmbed_Click(object sender, EventArgs e)
        {
            SetEmbedStatus("Waiting");

            if (EmbedFieldsReady())
            {
                DisableControls();

                SetEmbedStatus("Embedding data");

                Byte[] data = File.ReadAllBytes(textBox_Embed_DataFilePath.Text);
                Byte[] password = Encoding.UTF8.GetBytes(textBox_Embed_Password.Text);
                Mode mode = (Mode)comboBox_Embed_EncryptionMode.SelectedIndex;
                Byte[] encryptedData = AESBridge.AES.Encrypt(data, password, mode);

                Byte[] carrier = File.ReadAllBytes(textBox_Embed_CarrierFilePath.Text);

                try
                {
                    Byte[] stego = StGBridge.StG.Embed(carrier, encryptedData, password);
                    File.WriteAllBytes(textBox_Embed_StegoFilePath.Text, stego);
                    SetEmbedStatus("Ready");
                }
                catch (Exception ex)
                {
                    SetEmbedStatus(ex.Message);
                }

                EnableControls();
            }
        }

        private void buttonExtract_Click(object sender, EventArgs e)
        {
            SetExtractStatus("Waiting");

            if (ExtractFieldsReady())
            {
                DisableControls();

                SetExtractStatus("Extracting data");

                Byte[] stego = File.ReadAllBytes(textBox_Extract_StegoFilePath.Text);
                Byte[] password = Encoding.UTF8.GetBytes(textBox_Extract_Password.Text);
                Byte[] encryptedData = StGBridge.StG.Extract(stego, password);
                Byte[] data = AESBridge.AES.Decrypt(encryptedData, password, (Mode)comboBox_Extract_EncryptionMode.SelectedIndex);
                File.WriteAllBytes(textBox_Extract_DataFilePath.Text, data);

                SetExtractStatus("Ready");

                EnableControls();
            }
        }

        private void linkLabelHelp_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            try
            {
                var psi = new System.Diagnostics.ProcessStartInfo
                {
                    FileName = "https://github.com/DaniilGalahov/StG",
                    UseShellExecute = true
                };
                System.Diagnostics.Process.Start(psi);
            }
            catch (Exception ex)
            {
                MessageBox.Show("Cannot open link. " + ex.Message);
            }
        }
    }
}
