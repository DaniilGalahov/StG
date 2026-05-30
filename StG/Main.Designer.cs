namespace StG
{
    partial class Main
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Main));
            this.tabMode = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.label_Embed_Status = new System.Windows.Forms.Label();
            this.buttonEmbed = new System.Windows.Forms.Button();
            this.button_Embed_CreateStegoFile = new System.Windows.Forms.Button();
            this.textBox_Embed_StegoFilePath = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.comboBox_Embed_EncryptionMode = new System.Windows.Forms.ComboBox();
            this.textBox_Embed_Password = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.button_Embed_SelectCarrierFile = new System.Windows.Forms.Button();
            this.textBox_Embed_CarrierFilePath = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.button_Embed_SelectDataFile = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.textBox_Embed_DataFilePath = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.label_Extract_Status = new System.Windows.Forms.Label();
            this.buttonExtract = new System.Windows.Forms.Button();
            this.button_Extract_CreateDataFile = new System.Windows.Forms.Button();
            this.textBox_Extract_DataFilePath = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.comboBox_Extract_EncryptionMode = new System.Windows.Forms.ComboBox();
            this.textBox_Extract_Password = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.button_Extract_SelectStegoFile = new System.Windows.Forms.Button();
            this.label12 = new System.Windows.Forms.Label();
            this.textBox_Extract_StegoFilePath = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.openFileDialog_SelectDataFile = new System.Windows.Forms.OpenFileDialog();
            this.openFileDialog_SelectCarrierFile = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog_CreateStegoFile = new System.Windows.Forms.SaveFileDialog();
            this.openFileDialog_SelectStegoFile = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog_CreateDataFile = new System.Windows.Forms.SaveFileDialog();
            this.linkLabel_Embed_Help = new System.Windows.Forms.LinkLabel();
            this.linkLabel_Extract_Help = new System.Windows.Forms.LinkLabel();
            this.tabMode.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabMode
            // 
            this.tabMode.Controls.Add(this.tabPage1);
            this.tabMode.Controls.Add(this.tabPage2);
            this.tabMode.Location = new System.Drawing.Point(2, 2);
            this.tabMode.Name = "tabMode";
            this.tabMode.SelectedIndex = 0;
            this.tabMode.Size = new System.Drawing.Size(600, 300);
            this.tabMode.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.linkLabel_Embed_Help);
            this.tabPage1.Controls.Add(this.label_Embed_Status);
            this.tabPage1.Controls.Add(this.buttonEmbed);
            this.tabPage1.Controls.Add(this.button_Embed_CreateStegoFile);
            this.tabPage1.Controls.Add(this.textBox_Embed_StegoFilePath);
            this.tabPage1.Controls.Add(this.label6);
            this.tabPage1.Controls.Add(this.label5);
            this.tabPage1.Controls.Add(this.comboBox_Embed_EncryptionMode);
            this.tabPage1.Controls.Add(this.textBox_Embed_Password);
            this.tabPage1.Controls.Add(this.label4);
            this.tabPage1.Controls.Add(this.button_Embed_SelectCarrierFile);
            this.tabPage1.Controls.Add(this.textBox_Embed_CarrierFilePath);
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Controls.Add(this.button_Embed_SelectDataFile);
            this.tabPage1.Controls.Add(this.label2);
            this.tabPage1.Controls.Add(this.textBox_Embed_DataFilePath);
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(592, 274);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Embed";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // label_Embed_Status
            // 
            this.label_Embed_Status.AutoSize = true;
            this.label_Embed_Status.Location = new System.Drawing.Point(9, 255);
            this.label_Embed_Status.Name = "label_Embed_Status";
            this.label_Embed_Status.Size = new System.Drawing.Size(79, 13);
            this.label_Embed_Status.TabIndex = 15;
            this.label_Embed_Status.Text = "Status: Waiting";
            // 
            // buttonEmbed
            // 
            this.buttonEmbed.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.buttonEmbed.Location = new System.Drawing.Point(268, 210);
            this.buttonEmbed.Name = "buttonEmbed";
            this.buttonEmbed.Size = new System.Drawing.Size(75, 23);
            this.buttonEmbed.TabIndex = 14;
            this.buttonEmbed.Text = "Embed";
            this.buttonEmbed.UseVisualStyleBackColor = true;
            this.buttonEmbed.Click += new System.EventHandler(this.buttonEmbed_Click);
            // 
            // button_Embed_CreateStegoFile
            // 
            this.button_Embed_CreateStegoFile.Location = new System.Drawing.Point(495, 168);
            this.button_Embed_CreateStegoFile.Name = "button_Embed_CreateStegoFile";
            this.button_Embed_CreateStegoFile.Size = new System.Drawing.Size(75, 23);
            this.button_Embed_CreateStegoFile.TabIndex = 13;
            this.button_Embed_CreateStegoFile.Text = "Browse";
            this.button_Embed_CreateStegoFile.UseVisualStyleBackColor = true;
            this.button_Embed_CreateStegoFile.Click += new System.EventHandler(this.button_Embed_CreateStegoFile_Click);
            // 
            // textBox_Embed_StegoFilePath
            // 
            this.textBox_Embed_StegoFilePath.Location = new System.Drawing.Point(9, 170);
            this.textBox_Embed_StegoFilePath.Name = "textBox_Embed_StegoFilePath";
            this.textBox_Embed_StegoFilePath.Size = new System.Drawing.Size(480, 20);
            this.textBox_Embed_StegoFilePath.TabIndex = 12;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(6, 154);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(85, 13);
            this.label6.TabIndex = 11;
            this.label6.Text = "Stego image file:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(446, 115);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(89, 13);
            this.label5.TabIndex = 10;
            this.label5.Text = "Encryption mode:";
            // 
            // comboBox_Embed_EncryptionMode
            // 
            this.comboBox_Embed_EncryptionMode.FormattingEnabled = true;
            this.comboBox_Embed_EncryptionMode.Items.AddRange(new object[] {
            "AES-128",
            "AES-192",
            "AES-256"});
            this.comboBox_Embed_EncryptionMode.Location = new System.Drawing.Point(449, 130);
            this.comboBox_Embed_EncryptionMode.Name = "comboBox_Embed_EncryptionMode";
            this.comboBox_Embed_EncryptionMode.Size = new System.Drawing.Size(121, 21);
            this.comboBox_Embed_EncryptionMode.TabIndex = 9;
            // 
            // textBox_Embed_Password
            // 
            this.textBox_Embed_Password.Location = new System.Drawing.Point(9, 131);
            this.textBox_Embed_Password.Name = "textBox_Embed_Password";
            this.textBox_Embed_Password.Size = new System.Drawing.Size(434, 20);
            this.textBox_Embed_Password.TabIndex = 8;
            this.textBox_Embed_Password.UseSystemPasswordChar = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 115);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(56, 13);
            this.label4.TabIndex = 7;
            this.label4.Text = "Password:";
            // 
            // button_Embed_SelectCarrierFile
            // 
            this.button_Embed_SelectCarrierFile.Location = new System.Drawing.Point(495, 90);
            this.button_Embed_SelectCarrierFile.Name = "button_Embed_SelectCarrierFile";
            this.button_Embed_SelectCarrierFile.Size = new System.Drawing.Size(75, 23);
            this.button_Embed_SelectCarrierFile.TabIndex = 6;
            this.button_Embed_SelectCarrierFile.Text = "Browse";
            this.button_Embed_SelectCarrierFile.UseVisualStyleBackColor = true;
            this.button_Embed_SelectCarrierFile.Click += new System.EventHandler(this.button_Embed_SelectCarrierFile_Click);
            // 
            // textBox_Embed_CarrierFilePath
            // 
            this.textBox_Embed_CarrierFilePath.Location = new System.Drawing.Point(9, 92);
            this.textBox_Embed_CarrierFilePath.Name = "textBox_Embed_CarrierFilePath";
            this.textBox_Embed_CarrierFilePath.Size = new System.Drawing.Size(480, 20);
            this.textBox_Embed_CarrierFilePath.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 76);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(87, 13);
            this.label3.TabIndex = 4;
            this.label3.Text = "Carrier image file:";
            // 
            // button_Embed_SelectDataFile
            // 
            this.button_Embed_SelectDataFile.Location = new System.Drawing.Point(495, 47);
            this.button_Embed_SelectDataFile.Name = "button_Embed_SelectDataFile";
            this.button_Embed_SelectDataFile.Size = new System.Drawing.Size(75, 23);
            this.button_Embed_SelectDataFile.TabIndex = 3;
            this.button_Embed_SelectDataFile.Text = "Browse";
            this.button_Embed_SelectDataFile.UseVisualStyleBackColor = true;
            this.button_Embed_SelectDataFile.Click += new System.EventHandler(this.button_Embed_SelectDataFile_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 33);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(49, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "Data file:";
            // 
            // textBox_Embed_DataFilePath
            // 
            this.textBox_Embed_DataFilePath.Location = new System.Drawing.Point(9, 49);
            this.textBox_Embed_DataFilePath.Name = "textBox_Embed_DataFilePath";
            this.textBox_Embed_DataFilePath.Size = new System.Drawing.Size(480, 20);
            this.textBox_Embed_DataFilePath.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 3);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(525, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Encrypt data file with given password and mode, embed it into carrier image file," +
    " save result to stego image file ";
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.linkLabel_Extract_Help);
            this.tabPage2.Controls.Add(this.label_Extract_Status);
            this.tabPage2.Controls.Add(this.buttonExtract);
            this.tabPage2.Controls.Add(this.button_Extract_CreateDataFile);
            this.tabPage2.Controls.Add(this.textBox_Extract_DataFilePath);
            this.tabPage2.Controls.Add(this.label8);
            this.tabPage2.Controls.Add(this.label9);
            this.tabPage2.Controls.Add(this.comboBox_Extract_EncryptionMode);
            this.tabPage2.Controls.Add(this.textBox_Extract_Password);
            this.tabPage2.Controls.Add(this.label10);
            this.tabPage2.Controls.Add(this.button_Extract_SelectStegoFile);
            this.tabPage2.Controls.Add(this.label12);
            this.tabPage2.Controls.Add(this.textBox_Extract_StegoFilePath);
            this.tabPage2.Controls.Add(this.label13);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(592, 274);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Extract";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // label_Extract_Status
            // 
            this.label_Extract_Status.AutoSize = true;
            this.label_Extract_Status.Location = new System.Drawing.Point(9, 255);
            this.label_Extract_Status.Name = "label_Extract_Status";
            this.label_Extract_Status.Size = new System.Drawing.Size(79, 13);
            this.label_Extract_Status.TabIndex = 31;
            this.label_Extract_Status.Text = "Status: Waiting";
            // 
            // buttonExtract
            // 
            this.buttonExtract.Anchor = System.Windows.Forms.AnchorStyles.Top;
            this.buttonExtract.Location = new System.Drawing.Point(268, 167);
            this.buttonExtract.Name = "buttonExtract";
            this.buttonExtract.Size = new System.Drawing.Size(75, 23);
            this.buttonExtract.TabIndex = 30;
            this.buttonExtract.Text = "Extract";
            this.buttonExtract.UseVisualStyleBackColor = true;
            this.buttonExtract.Click += new System.EventHandler(this.buttonExtract_Click);
            // 
            // button_Extract_CreateDataFile
            // 
            this.button_Extract_CreateDataFile.Location = new System.Drawing.Point(495, 125);
            this.button_Extract_CreateDataFile.Name = "button_Extract_CreateDataFile";
            this.button_Extract_CreateDataFile.Size = new System.Drawing.Size(75, 23);
            this.button_Extract_CreateDataFile.TabIndex = 29;
            this.button_Extract_CreateDataFile.Text = "Browse";
            this.button_Extract_CreateDataFile.UseVisualStyleBackColor = true;
            this.button_Extract_CreateDataFile.Click += new System.EventHandler(this.button_Extract_CreateDataFile_Click);
            // 
            // textBox_Extract_DataFilePath
            // 
            this.textBox_Extract_DataFilePath.Location = new System.Drawing.Point(9, 127);
            this.textBox_Extract_DataFilePath.Name = "textBox_Extract_DataFilePath";
            this.textBox_Extract_DataFilePath.Size = new System.Drawing.Size(480, 20);
            this.textBox_Extract_DataFilePath.TabIndex = 28;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(6, 111);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(49, 13);
            this.label8.TabIndex = 27;
            this.label8.Text = "Data file:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(446, 72);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(89, 13);
            this.label9.TabIndex = 26;
            this.label9.Text = "Encryption mode:";
            // 
            // comboBox_Extract_EncryptionMode
            // 
            this.comboBox_Extract_EncryptionMode.FormattingEnabled = true;
            this.comboBox_Extract_EncryptionMode.Items.AddRange(new object[] {
            "AES-128",
            "AES-192",
            "AES-256"});
            this.comboBox_Extract_EncryptionMode.Location = new System.Drawing.Point(449, 87);
            this.comboBox_Extract_EncryptionMode.Name = "comboBox_Extract_EncryptionMode";
            this.comboBox_Extract_EncryptionMode.Size = new System.Drawing.Size(121, 21);
            this.comboBox_Extract_EncryptionMode.TabIndex = 25;
            // 
            // textBox_Extract_Password
            // 
            this.textBox_Extract_Password.Location = new System.Drawing.Point(9, 88);
            this.textBox_Extract_Password.Name = "textBox_Extract_Password";
            this.textBox_Extract_Password.Size = new System.Drawing.Size(434, 20);
            this.textBox_Extract_Password.TabIndex = 24;
            this.textBox_Extract_Password.UseSystemPasswordChar = true;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(6, 72);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(56, 13);
            this.label10.TabIndex = 23;
            this.label10.Text = "Password:";
            // 
            // button_Extract_SelectStegoFile
            // 
            this.button_Extract_SelectStegoFile.Location = new System.Drawing.Point(495, 47);
            this.button_Extract_SelectStegoFile.Name = "button_Extract_SelectStegoFile";
            this.button_Extract_SelectStegoFile.Size = new System.Drawing.Size(75, 23);
            this.button_Extract_SelectStegoFile.TabIndex = 19;
            this.button_Extract_SelectStegoFile.Text = "Browse";
            this.button_Extract_SelectStegoFile.UseVisualStyleBackColor = true;
            this.button_Extract_SelectStegoFile.Click += new System.EventHandler(this.button_Extract_SelectStegoFile_Click);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(6, 33);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(85, 13);
            this.label12.TabIndex = 18;
            this.label12.Text = "Stego image file:";
            // 
            // textBox_Extract_StegoFilePath
            // 
            this.textBox_Extract_StegoFilePath.Location = new System.Drawing.Point(9, 49);
            this.textBox_Extract_StegoFilePath.Name = "textBox_Extract_StegoFilePath";
            this.textBox_Extract_StegoFilePath.Size = new System.Drawing.Size(480, 20);
            this.textBox_Extract_StegoFilePath.TabIndex = 17;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(6, 3);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(478, 13);
            this.label13.TabIndex = 16;
            this.label13.Text = "Extract data from stego image file, decrypt it with given password and mode, save" +
    " result into data file";
            // 
            // openFileDialog_SelectDataFile
            // 
            this.openFileDialog_SelectDataFile.Title = "Select data file";
            // 
            // openFileDialog_SelectCarrierFile
            // 
            this.openFileDialog_SelectCarrierFile.Filter = "PNG images (*.png)|*.png";
            this.openFileDialog_SelectCarrierFile.Title = "Select carrier image file";
            // 
            // saveFileDialog_CreateStegoFile
            // 
            this.saveFileDialog_CreateStegoFile.DefaultExt = "png";
            this.saveFileDialog_CreateStegoFile.Filter = "PNG images (*.png)|*.png";
            this.saveFileDialog_CreateStegoFile.Title = "Save stego image to file";
            // 
            // openFileDialog_SelectStegoFile
            // 
            this.openFileDialog_SelectStegoFile.Filter = "PNG images (*.png)|*.png";
            this.openFileDialog_SelectStegoFile.Title = "Select stego image file";
            // 
            // saveFileDialog_CreateDataFile
            // 
            this.saveFileDialog_CreateDataFile.Title = "Save data to file";
            // 
            // linkLabel_Embed_Help
            // 
            this.linkLabel_Embed_Help.AutoSize = true;
            this.linkLabel_Embed_Help.Location = new System.Drawing.Point(541, 255);
            this.linkLabel_Embed_Help.Name = "linkLabel_Embed_Help";
            this.linkLabel_Embed_Help.Size = new System.Drawing.Size(29, 13);
            this.linkLabel_Embed_Help.TabIndex = 16;
            this.linkLabel_Embed_Help.TabStop = true;
            this.linkLabel_Embed_Help.Text = "Help";
            this.linkLabel_Embed_Help.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabelHelp_LinkClicked);
            // 
            // linkLabel_Extract_Help
            // 
            this.linkLabel_Extract_Help.AutoSize = true;
            this.linkLabel_Extract_Help.Location = new System.Drawing.Point(541, 255);
            this.linkLabel_Extract_Help.Name = "linkLabel_Extract_Help";
            this.linkLabel_Extract_Help.Size = new System.Drawing.Size(29, 13);
            this.linkLabel_Extract_Help.TabIndex = 32;
            this.linkLabel_Extract_Help.TabStop = true;
            this.linkLabel_Extract_Help.Text = "Help";
            this.linkLabel_Extract_Help.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabelHelp_LinkClicked);
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(605, 307);
            this.Controls.Add(this.tabMode);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.Fixed3D;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "Main";
            this.Text = "StG";
            this.tabMode.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabMode;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBox_Embed_DataFilePath;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.OpenFileDialog openFileDialog_SelectDataFile;
        private System.Windows.Forms.Button button_Embed_SelectDataFile;
        private System.Windows.Forms.TextBox textBox_Embed_CarrierFilePath;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button button_Embed_SelectCarrierFile;
        private System.Windows.Forms.OpenFileDialog openFileDialog_SelectCarrierFile;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBox_Embed_Password;
        private System.Windows.Forms.ComboBox comboBox_Embed_EncryptionMode;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button button_Embed_CreateStegoFile;
        private System.Windows.Forms.TextBox textBox_Embed_StegoFilePath;
        private System.Windows.Forms.SaveFileDialog saveFileDialog_CreateStegoFile;
        private System.Windows.Forms.Button buttonEmbed;
        private System.Windows.Forms.Label label_Embed_Status;
        private System.Windows.Forms.Label label_Extract_Status;
        private System.Windows.Forms.Button buttonExtract;
        private System.Windows.Forms.Button button_Extract_CreateDataFile;
        private System.Windows.Forms.TextBox textBox_Extract_DataFilePath;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.ComboBox comboBox_Extract_EncryptionMode;
        private System.Windows.Forms.TextBox textBox_Extract_Password;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Button button_Extract_SelectStegoFile;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox textBox_Extract_StegoFilePath;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.OpenFileDialog openFileDialog_SelectStegoFile;
        private System.Windows.Forms.SaveFileDialog saveFileDialog_CreateDataFile;
        private System.Windows.Forms.LinkLabel linkLabel_Embed_Help;
        private System.Windows.Forms.LinkLabel linkLabel_Extract_Help;
    }
}

