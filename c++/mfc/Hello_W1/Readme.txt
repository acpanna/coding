========================================================================
       MICROSOFT FOUNDATION CLASS BIBLIOTHEK : Hello_W1
========================================================================


Diese Hello_W1-Anwendung hat der Klassen-Assistent f�r Sie erstellt. Diese Anwendung
zeigt nicht nur die prinzipielle Verwendung der Microsoft Foundation Classes, 
sondern dient auch als Ausgangspunkt f�r die Erstellung Ihrer eigenen DLLs.

Diese Datei enth�lt die Zusammenfassung der Bestandteile aller Dateien, die 
Ihre Hello_W1-Anwendung bilden.

Hello_W1.dsp
    Diese Datei (Projektdatei) enth�lt Informationen auf Projektebene und wird zur
    Erstellung eines einzelnen Projekts oder Teilprojekts verwendet. Andere Benutzer k�nnen
    die Projektdatei (.dsp) gemeinsam nutzen, sollten aber die Makefiles lokal exportieren.

Hello_W1.h
    Hierbei handelt es sich um die Haupt-Header-Datei der Anwendung. Diese enth�lt 
	andere projektspezifische Header (einschlie�lich Resource.h) und deklariert die
	Anwendungsklasse CHello_W1App.

Hello_W1.cpp
    Hierbei handelt es sich um die Haupt-Quellcodedatei der Anwendung. Diese enth�lt die
    Anwendungsklasse CHello_W1App.

Hello_W1.rc
	Hierbei handelt es sich um eine Auflistung aller Ressourcen von Microsoft Windows, die 
	vom Programm verwendet werden. Sie enth�lt die Symbole, Bitmaps und Cursors, die im 
	Unterverzeichnis RES abgelegt sind. Diese Datei l�sst sich direkt in Microsoft
	Visual C++ bearbeiten.

Hello_W1.clw
    Diese Datei enth�lt Informationen, die vom Klassen-Assistenten verwendet wird, um bestehende
    Klassen zu bearbeiten oder neue hinzuzuf�gen.  Der Klassen-Assistent verwendet diese Datei auch,
    um Informationen zu speichern, die zum Erstellen und Bearbeiten von Nachrichtentabellen und
    Dialogdatentabellen ben�tigt werden und um Prototyp-Member-Funktionen zu erstellen.

res\Hello_W1.ico
    Dies ist eine Symboldatei, die als Symbol f�r die Anwendung verwendet wird. Dieses 
	Symbol wird durch die Haupt-Ressourcendatei Hello_W1.rc eingebunden.

res\Hello_W1.rc2
    Diese Datei enth�lt Ressourcen, die nicht von Microsoft Visual C++ bearbeitet wurden.
	In diese Datei werden alle Ressourcen abgelegt, die vom Ressourcen-Editor nicht bearbeitet 
	werden k�nnen.



/////////////////////////////////////////////////////////////////////////////

F�r das Hauptfenster:

MainFrm.h, MainFrm.cpp
    	Diese Dateien enthalten die Frame-Klasse CMainFrame, die von
    	CFrameWnd abgeleitet wurde und alle SDI-Frame-Merkmale steuert.

res\Toolbar.bmp
    Diese Bitmap-Datei wird zum Erstellen unterteilter Bilder f�r die Symbolleiste verwendet.
    Die erste Symbol- und Statusleiste wird in der Klasse CMainFrame erstellt.
    Bearbeiten Sie diese Bitmap der Symbolleiste mit dem Ressourcen-Editor, und
    aktualisieren Sie IDR_MAINFRAME TOOLBAR in Hello_W1.rc, um Schaltfl�chen f�r die
    Symbolleiste hinzuzuf�gen.
/////////////////////////////////////////////////////////////////////////////

Der Klassen-Assistent erstellt einen Dokumenttyp und eine Ansicht(View):

Hello_W1Doc.h, Hello_W1Doc.cpp - das Dokument
    	Diese Dateien enthalten die Klasse CHello_W1Doc. Bearbeiten Sie diese Dateien,
  	um Ihre speziellen Dokumentdaten hinzuzuf�gen und das Speichern und Laden von 
	Dateien zu implementieren (mit Hilfe von CHello_W1Doc::Serialize).

Hello_W1View.h, Hello_W1View.cpp - die Ansicht des Dokuments
    	Diese Dateien enthalten die Klasse CHello_W1View.
    	CHello_W1View-Objekte werden verwendet, um CHello_W1Doc-Objekte anzuzeigen.



/////////////////////////////////////////////////////////////////////////////
Andere Standarddateien:

StdAfx.h, StdAfx.cpp
    	Mit diesen Dateien werden vorkompilierte Header-Dateien (PCH) mit der Bezeichnung 
	Hello_W1.pch und eine vorkompilierte Typdatei mit der Bezeichnung StdAfx.obj
	erstellt.

Resource.h
    	Dies ist die Standard-Header-Datei, die neue Ressourcen-IDs definiert.
    	Microsoft Visual C++ liest und aktualisiert diese Datei.

/////////////////////////////////////////////////////////////////////////////
Weitere Hinweise:

Der Klassen-Assistent f�gt "ZU ERLEDIGEN:" im Quellcode ein, um die Stellen anzuzeigen, 
an denen Sie Erweiterungen oder Anpassungen vornehmen k�nnen.

Wenn Ihre Anwendung die MFC in einer gemeinsam genutzten DLL verwendet und Ihre Anwendung
eine andere als die aktuell auf dem Betriebssystem eingestellte Sprache verwendet, muss 
die entsprechend lokalisierte Ressource MFC42XXX.DLL von der Microsoft Visual C++ CD-ROM 
in das Verzeichnis system oder system32 kopiert und in MFCLOC.DLL umbenannt werden ("XXX" 
steht f�r die Abk�rzung der Sprache. So enth�lt beispielsweise MFC42DEU.DLL die ins Deutsche 
�bersetzten Ressourcen). Anderenfalls erscheinen einige Oberfl�chenelemente Ihrer Anwendung 
in der Sprache des Betriebssystems.

/////////////////////////////////////////////////////////////////////////////
