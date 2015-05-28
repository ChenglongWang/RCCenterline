using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

using Pluto;

namespace Plugin
{
	// メニューのサブカテゴリを指定する．
	[Category( "CL.Wang" )]
	[PluginType( PluginCategory.Filter )]
	public partial class CalixCenterlinePlugin : Form, ICommonPlugin, IMenuEx
	{
		#region コンストラクタ
		public CalixCenterlinePlugin( )
		{
			InitializeComponent( );
		}
		#endregion

		#region フィールド
		DataManager dataManager = null;
		IPluto iPluto = null;
		#endregion

		#region IPlugin メンバ
		string IPlugin.Author { get { return ( "PLUTO Development Team" ); } }

		string IPlugin.Text { get { return ( "RC_Centerline" ); } }

		string IPlugin.Comment { get { return ( "Get the centerline of renal calix." ); } }

		bool IPlugin.Initialize( DataManager data, IPluto pluto )
		{
			// DataManager および IPluto を取得する．
			dataManager = data;
			iPluto = pluto;

			return ( true );
		}
		#endregion

		#region ICommonPlugin メンバ
		object ICommonPlugin.Run( params object[] args )
		{
			// DataManager および IPluto の取得に失敗している．または，画像が選択されていない．
			if( dataManager == null || iPluto == null || dataManager.Active == null )
			{
				return ( null );
			}

			// 選択された画像を入力画像とする．
			Mist.MistArray ct = dataManager.Active;
			// 出力画像を入力画像と同じサイズで作成する．
			Mist.MistArray centerLine = new Mist.MistArray( ct.Size1, ct.Size2, ct.Size3, ct.Reso1, ct.Reso2, ct.Reso3 );

			// Form を表示する．
			if( this.ShowDialog( ) == DialogResult.OK )
			{
				int target = ( int )this.numericObject.Value;
                bool oppsite = ( bool )this.checkOppsite.Checked;

//				if( RCCenterlineCpp( ct.Image, centerLine.Image, target, oppsite) == false )
                if( ComputeConvexHull(ct.Image, target, centerLine.Image) == false)
				{
					return ( null );
				}

				// 出力画像を DataManager へ追加する．
				if( dataManager.Add( centerLine, false, true ) < 0 )
				{
					// 追加に失敗したら，出力画像のリソースを開放する．
					centerLine.Dispose( );
					return ( null );
				}
				else
				{
					return ( centerLine );
				}
			}

			return ( null );
		}  
		#endregion

		#region IMenuEx メンバ
		bool IMenuEx.Visible
		{
			get
			{
				// DataManager が設定されている場合は表示，されていない場合は非表示とする．
				return ( dataManager != null );
			}
		}

		bool IMenuEx.Enabled
		{
			get
			{
				if( dataManager == null )
				{
					// DataManager が設定されていない場合は無効とする．
					return ( false );
				}
				else
				{
					// Active なデータがある場合は有効，ない場合は無効とする．
					return ( dataManager.Active != null );
				}
			}
		}

		string IMenuEx.Category
		{
			get
			{
				return ( "CL.Wang" );
			}
		}
		#endregion

		#region イベント
		private void OnOK( object sender, EventArgs e )
		{
			this.DialogResult = DialogResult.OK;
		}

		private void OnCancel( object sender, EventArgs e )
		{
			this.DialogResult = DialogResult.Cancel;
		}
		#endregion

		[DllImport( "RCCenterline.dll", EntryPoint="Run", CallingConvention=CallingConvention.Cdecl)]
		internal static extern bool RCCenterlineCpp(IntPtr originImage, IntPtr centerline, int target, bool oppsite);

        [DllImport("RCCenterline.dll", EntryPoint = "ComputeConvexHull", CallingConvention = CallingConvention.Cdecl)]
        internal static extern bool ComputeConvexHull(IntPtr originImage, int target, IntPtr output);

	}
}