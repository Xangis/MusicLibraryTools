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
using System.ComponentModel;

namespace ZTag_WMV
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Dictionary<String, List<String>> _genres;
        int songCount = 0;
        int noGenreCount = 0;

        public MainWindow()
        {
            _genres = new Dictionary<String, List<String>>();
            InitializeComponent();
            DependencyPropertyDescriptor dpd = DependencyPropertyDescriptor.FromProperty(ComboBox.TextProperty, typeof(ComboBox));
            dpd.AddValueChanged(lstGenres, btnFind_Click);
        }

        public void FindSongs()
        {
            songCount = 0;
            lstOutput.Items.Clear();
            try
            {
                if (_genres.Count == 0)
                {
                    noGenreCount = 0;
                    FindFiles(txtDirectory.Text);
                    RepopulateGenres();
                    lstOutput.Items.Add(noGenreCount.ToString() + "Note: " + noGenreCount + " songs had no genre information and were ignored.");
                }
                ShowSongs();
            }
            catch (Exception ex)
            {
                lstOutput.Items.Add("Error finding songs: " + ex.ToString());
            }
 
        }

        private void btnFind_Click(object sender, EventArgs e)
        {
            FindSongs();
        }

        private void btnAbout_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Genre Playlist Builder version 1.0\nCopyright (c) 2009-2010 Zeta Centauri, Inc.\nhttp://zetacentauri.com\nWritten by Jason Champion.\n\nTo use, browse for a directory using the 'browse' button and click 'index'.\n\rAfter indexing, you can just select an item from the genre list box to display songs found in that genre.\n\n\rTo generate a playlist from that genre, click the 'Create Playlist' button.");
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
                    String[] genres = tag.Tag.Genres;
                    if (genres.Length < 1)
                    {
                        ++noGenreCount;
                        continue;
                    }
                    foreach (String str in genres)
                    {
                        if (!_genres.ContainsKey(str))
                        {
                            _genres[str] = new List<String>();
                        }
                        _genres[str].Add(file.FullName);
                    }
                    ++songCount;
                    lblNumIndexed.Content = songCount.ToString();
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
            _genres.Clear();
            songCount = 0;
            noGenreCount = 0;
            FindFiles(txtDirectory.Text);
            RepopulateGenres();
            lstOutput.Items.Add("Note: " + noGenreCount + " songs had no genre information and were ignored.");
        }

        private void ShowSongs()
        {
            String genre = lstGenres.Text;
            if (_genres.ContainsKey(genre))
            {
                List<String> items = _genres[genre];
                foreach (String str in items)
                {
                    lstOutput.Items.Add(str);
                }
                lstOutput.Items.Add(items.Count.ToString() + " items found in genre " + genre + ".");
            }
        }

        private void RepopulateGenres()
        {
            lstGenres.Items.Clear();
            List<String> items = new List<String>();
            foreach (String key in _genres.Keys)
            {
                if (!items.Contains(key))
                    items.Add(key);
            }
            items.Sort();
            foreach (String item in items)
            {
                lstGenres.Items.Add(item);
            }
        }

        /// <summary>
        /// Creates a playlist file.
        /// TODO: Add support for WPL playlist generation: http://en.wikipedia.org/wiki/Windows_Media_Player_Playlist
        /// TODO: Add support for XSPF playlist generation: http://en.wikipedia.org/wiki/XSPF
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void btnCreatePlaylist_Click(object sender, RoutedEventArgs e)
        {
            String genre = lstGenres.Text;
            if (!_genres.ContainsKey(genre))
            {
                lstOutput.Items.Add("No songs found for genre " + lstGenres.Text + ".");
                return;
            }
            System.Windows.Forms.SaveFileDialog dlg = new System.Windows.Forms.SaveFileDialog();
            dlg.Filter = "M3U Playlist Files (*.m3u)|*.m3u";
            if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                string filename = dlg.FileName;
                FileInfo info = new FileInfo(filename);
                StreamWriter Tex = info.CreateText();
                Tex.WriteLine("# Playlist for genre " + genre + " generated with Genre Playlist Builder v1 by Zeta Centauri (http://zetacentauri.com)");
                Tex.WriteLine("# Playlist contains " + _genres[genre].Count() + " items.");
                foreach (string str in _genres[genre])
                {
                    Tex.WriteLine(str);
                }
                Tex.Flush();
                Tex.Close();
                lstOutput.Items.Add("Playlist file for genre " + genre + " has been saved to " + filename + ".");
            }
        }
    }
}
