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
    public partial class Window1 : Window
    {
        int renameCount = 0;
        int failCount = 0;
        int notRenamed = 0;

        public Window1()
        {
            InitializeComponent();
        }

        public void RenameAll()
        {
            renameCount = 0;
            failCount = 0;
            notRenamed = 0;
            lstOutput.Items.Clear();
            try
            {
                RenameFiles(txtDirectory.Text);
            }
            catch (Exception ex)
            {
                lstOutput.Items.Add("Error renaming: " + ex.ToString());
            }
            lstOutput.Items.Add(renameCount.ToString() + " items renamed.");
            lstOutput.Items.Add(failCount.ToString() + " items failed to rename.");
            lstOutput.Items.Add(notRenamed.ToString() + " items already named properly.");
        }

        private void btnRenameAll_Click(object sender, RoutedEventArgs e)
        {
            RenameAll();
        }

        private void btnAbout_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("ZetaTag Auto-Renamer version 1.0\nCopyright (c) 2009 Zeta Centauri, Inc.\nhttp://www.zetacentauri.com\nWritten by Jason Champion.\n\nTo use, browse for a directory using the 'browse' button and click 'rename all'.\nYou can provide an optional directory separator character, such as '_' instead\nof the default ' - '.\n\nAll files in the selected directory and all subdirectories will be renamed to\nthe format:\n\nArtist - Album - Track Number - Track Name.ext");
        }

        private void btnBrowse_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Forms.FolderBrowserDialog dlg = new System.Windows.Forms.FolderBrowserDialog();
            if ( dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK )
            {
                txtDirectory.Text = dlg.SelectedPath;
            }
        }

        private void RenameFiles(string directory)
        {
            String separator = txtSeparator.Text;
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
                        lstOutput.Items.Add("Cannot read header information for file " + file.Name);
                        failCount++;
                        continue;
                    }

                    // Read some information.
                    string title = tag.Tag.Title;
                    uint track = tag.Tag.Track;
                    string album = tag.Tag.Album;
                    string[] artists = tag.Tag.Performers; // Remember, each song can have more than one artist.

                    if (artists.Length < 1)
                    {
                        lstOutput.Items.Add("Artist not present for file " + file.FullName);
                        failCount++;
                        continue;
                    }

                    if (String.IsNullOrEmpty(title))
                    {
                        lstOutput.Items.Add("Track title not present for file " + file.FullName);
                        failCount++;
                        continue;
                    }

                    if (track == 0)
                    {
                        lstOutput.Items.Add("Track number not present for file " + file.FullName);
                        failCount++;
                        continue;
                    }

                    if (string.IsNullOrEmpty(album))
                    {
                        lstOutput.Items.Add("Album title not present for file " + file.FullName);
                        failCount++;
                        continue;
                    }

                    string newName = String.Join(", ", artists) + separator + album + separator + String.Format("{0:00}", track) + separator + title + file.Extension;

                    // Remove invalid path characters, such as quotes.
                    newName = newName.Replace('\"', '\''); // Replace double quotes with single quotes.
                    newName = newName.Replace('\\', '-'); // Remove backslashes.
                    newName = newName.Replace('/', '-'); // Remove forward slashes.
                    newName = newName.Replace(":", ""); // Remove colons.
                    newName = newName.Replace("?", ""); // Remove question marks.
                    newName = newName.Replace("*", "-"); // Replace asterisks.
                    newName = newName.Replace(">", "-"); // Replace asterisks.
                    newName = newName.Replace("<", "-"); // Replace asterisks.

                    if (file.Name != newName)
                    {
                        lstOutput.Items.Add("Renaming " + file.Name + " to " + newName);
                        try
                        {
                            file.MoveTo(file.DirectoryName + "\\" + newName);
                            renameCount++;
                        }
                        catch (IOException ex)
                        {
                            lstOutput.Items.Add("Rename failed: " + ex.Message);
                            failCount++;
                        }
                        catch (Exception ex)
                        {
                            lstOutput.Items.Add("Rename failed: " + ex.ToString());
                            failCount++;
                        }
                    }
                    else
                    {
                        notRenamed++;
                    }
                }
            }
            foreach (String dir in Directory.GetDirectories(directory))
            {
                RenameFiles(dir);
            }
        }

        public static void DoEvents()
        {
            Application.Current.Dispatcher.Invoke(DispatcherPriority.Background, new ThreadStart(delegate { }));
        }
    }
}
