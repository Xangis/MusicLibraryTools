using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Threading;
using System.Windows.Threading;
using System.IO;

namespace ZTag_WMV
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        List<KeyValuePair<String, TimeSpan>> _files;
        int songCount = 0;

        public MainWindow()
        {
            _files = new List<KeyValuePair<String, TimeSpan>>();
            InitializeComponent();
        }

        public void FindSongs()
        {
            songCount = 0;
            lstOutput.Items.Clear();
            try
            {
                if (_files.Count == 0)
                {
                    FindFiles(txtDirectory.Text);
                }
                ShowSongs();
            }
            catch (Exception ex)
            {
                lstOutput.Items.Add("Error renaming: " + ex.ToString());
            }
            lstOutput.Items.Add(songCount.ToString() + " items found.");
        }

        private void btnRenameAll_Click(object sender, RoutedEventArgs e)
        {
            FindSongs();
        }

        private void btnAbout_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Song Length Finder version 1.0\nCopyright (c) 2009-2010 Zeta Centauri, Inc.\nhttp://zetacentauri.com\nWritten by Jason Champion.\n\nTo use, browse for a directory using the 'browse' button and click 'index'.\n\rAfter indexing, you can click 'find' to find songs within the selected time range.\n\rIf you have already indexed a set of folders, you can just change the time to search for and then click 'find' again without having to search directories.");
        }

        private void btnBrowse_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Forms.FolderBrowserDialog dlg = new System.Windows.Forms.FolderBrowserDialog();
            if ( dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK )
            {
                txtDirectory.Text = dlg.SelectedPath;
            }
        }

        private void FindFiles(string directory)
        {
            lstOutput.Items.Add("Reading directory: " + directory);
            foreach (String filename in Directory.GetFiles(directory))
            {
                FileInfo file = new FileInfo(filename);
                if (file.Extension == ".wma" || file.Extension == ".mp3" || file.Extension == ".ogg")
                {
                    DoEvents(); // Let the UI update.

                    TagLib.File tag;
                    try
                    {
                        tag = TagLib.File.Create(file.FullName);
                    }
                    catch (Exception)
                    {
                        continue;
                    }
                    _files.Add(new KeyValuePair<string, TimeSpan>(file.FullName, tag.Properties.Duration));
                    lblNumIndexed.Content = _files.Count.ToString();
                }
            }
            foreach (String dir in Directory.GetDirectories(directory))
            {
                FindFiles(dir);
            }
        }

        public static void DoEvents()
        {
            Application.Current.Dispatcher.Invoke(DispatcherPriority.Background, new ThreadStart(delegate { }));
        }

        private void btnIndex_Click(object sender, RoutedEventArgs e)
        {
            _files.Clear();
            FindFiles(txtDirectory.Text);
        }

        private void ShowSongs()
        {
            TimeSpan min = TimeSpan.Parse(txtMinLength.Text);
            TimeSpan max = TimeSpan.Parse(txtMaxLength.Text);
            foreach (KeyValuePair<String, TimeSpan> kvp in _files)
            {
                if (kvp.Value >= min && kvp.Value <= max)
                {
                    DateTime time = DateTime.MinValue;
                    time = time + kvp.Value;
                    lstOutput.Items.Add(kvp.Key + "  (" + time.ToString("H:mm:ss") + ")");
                    ++songCount;
                }
            }
        }
    }
}
