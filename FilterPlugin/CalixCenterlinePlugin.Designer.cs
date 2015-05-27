namespace Plugin
{
	partial class CalixCenterlinePlugin
	{
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		/// <param name="disposing">マネージ リソースが破棄される場合 true、破棄されない場合は false です。</param>
		protected override void Dispose( bool disposing )
		{
			if( disposing && ( components != null ) )
			{
				components.Dispose( );
			}
			base.Dispose( disposing );
		}

		#region Windows フォーム デザイナで生成されたコード

		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		private void InitializeComponent( )
		{
            this.buttonCancel = new System.Windows.Forms.Button();
            this.buttonOK = new System.Windows.Forms.Button();
            this.label = new System.Windows.Forms.Label();
            this.numericObject = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.numericObject)).BeginInit();
            this.SuspendLayout();
            // 
            // buttonCancel
            // 
            this.buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.buttonCancel.Location = new System.Drawing.Point(58, 32);
            this.buttonCancel.Name = "buttonCancel";
            this.buttonCancel.Size = new System.Drawing.Size(81, 23);
            this.buttonCancel.TabIndex = 21;
            this.buttonCancel.Text = "キャンセル(&C)";
            this.buttonCancel.UseVisualStyleBackColor = true;
            this.buttonCancel.Click += new System.EventHandler(this.OnCancel);
            // 
            // buttonOK
            // 
            this.buttonOK.Location = new System.Drawing.Point(8, 32);
            this.buttonOK.Name = "buttonOK";
            this.buttonOK.Size = new System.Drawing.Size(44, 23);
            this.buttonOK.TabIndex = 22;
            this.buttonOK.Text = "&OK";
            this.buttonOK.UseVisualStyleBackColor = true;
            this.buttonOK.Click += new System.EventHandler(this.OnOK);
            // 
            // label
            // 
            this.label.AutoSize = true;
            this.label.Location = new System.Drawing.Point(8, 11);
            this.label.Name = "label";
            this.label.Size = new System.Drawing.Size(40, 12);
            this.label.TabIndex = 20;
            this.label.Text = "Object:";
            // 
            // numericObject
            // 
            this.numericObject.Location = new System.Drawing.Point(63, 7);
            this.numericObject.Maximum = new decimal(new int[] {
            32767,
            0,
            0,
            0});
            this.numericObject.Minimum = new decimal(new int[] {
            32768,
            0,
            0,
            -2147483648});
            this.numericObject.Name = "numericObject";
            this.numericObject.Size = new System.Drawing.Size(75, 19);
            this.numericObject.TabIndex = 19;
            this.numericObject.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.numericObject.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // CalixCenterlinePlugin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(145, 63);
            this.ControlBox = false;
            this.Controls.Add(this.buttonCancel);
            this.Controls.Add(this.buttonOK);
            this.Controls.Add(this.label);
            this.Controls.Add(this.numericObject);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "CalixCenterlinePlugin";
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Window";
            ((System.ComponentModel.ISupportInitialize)(this.numericObject)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.Button buttonCancel;
		private System.Windows.Forms.Button buttonOK;
		private System.Windows.Forms.Label label;
		private System.Windows.Forms.NumericUpDown numericObject;
	}
}