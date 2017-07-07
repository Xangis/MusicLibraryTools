# MusicLibraryTools

Miscellaneous music library tools for Windows, including ZetaTag Auto-Renamer, 
Song Length Finder, and Genre Playlist Builder. These programs were originally
available at http://zetacentauri.com and were downloaded over 40,000 times
before being open-sourced.

The ZetaTag Auto-Renamer analyzes your music collection and renames files to the
"One True Format" based on their tag information.

![ZetaTag Auto-Renamer Builder Screenshot](https://github.com/Xangis/MusicLibraryTools/blob/master/images/ZetaTag_Auto-Renamer.png)

The Song Length Finder lets you find songs in your music collection that are of
a specific length, or within a range of lengths.

![Song Length Finder Screenshot](https://github.com/Xangis/MusicLibraryTools/blob/master/images/SongLengthFinderScreenshot.png)

The Genre Playlist Builder lets you build playlists based on the genre of items
in your music collection.

![Genre Playlist Builder Screenshot](https://github.com/Xangis/MusicLibraryTools/blob/master/images/GenrePlaylistBuilderScreenshot.png)

Windows installers are available in the installer directory:

https://github.com/Xangis/MusicLibraryTools/blob/master/installer/GenrePlaylistBuilder1Setup.exe

https://github.com/Xangis/MusicLibraryTools/blob/master/installer/SongLengthFinder1Setup.exe

https://github.com/Xangis/MusicLibraryTools/blob/master/installer/ZetaTagAutoRenamer1Setup.exe

All three of these applications use Taglib-Sharp, which can be found here:

https://github.com/mono/taglib-sharp

The Taglib# version these applications was built with (2.0.3.2) is not the most
current version, but it is included in this repository because it is what they
were built and tested with.

# Development Status

These applications were originally written using C#. I'm in the process of porting
the application to C++, wxWidgets, and Tagib in order to make it run on multiple.

In addition, I'm working on unifying the three applications into a single app that
does everything the original programs did (and maybe more).

For now, you won't be able to do anything useful with the source code, so just install
the invididual apps.
