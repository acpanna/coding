<?php

// Überprüfen, ob der Kunde eingeloggt ist: 
//	Falls nein --> Abbruch
session_start();
if (!isset($_SESSION['user'])) {
	exit;
}

// Auslesen der Anfrage-Header, die vom Client-Browser 
// an den Web-Server geschickt wurden.
$headers = getallheaders(); 

///////////////////////////////////// Strings Deutsch-Englisch /////////////////////////////////////

$string1 = "Zugriffsverletzung";
$string2 = "Der Zugriff auf diese Datei ist Ihnen nicht gestattet!";
$string3 = "Bitte wählen Sie den gewünschten Maschinentyp aus, oder geben Sie einen Teil des/der jeweiligen Dateinamens/Seriennummer in das Suchfeld ein.<br><br>Beachten Sie, dass ein Suchbegriff aus mindestens vier Zeichen bestehen muss. Die Suche selbst verläuft case-insensitive, d.h \"NP3.\" und \"np3.\" liefern dieselben Ergebnisse.<br><br>Falls es zu Problemen beim Download kommt, klicken Sie den entsprechenden Link mit der rechten Maustaste an und w&auml;hlen den Punkt  \"Link speichern unter...\" aus.<br><br>Das direkte Öffnen von Dokumenten mit dem Internet Explorer funktioniert nicht immer, speichern Sie in diesem Fall das Dokument zuerst und öffnen es dann lokal.";
$string4 = "Seriennummern";
$string5 = "Alles herunterladen";
$string6 = "Ihre Download-Anfrage wird bearbeitet -- Bitte gedulden Sie sich einen Moment!<br>Falls der Download 10MB &uuml;bersteigt, erfolgt eine Aufsplittung in Teilpakete.";
$string7 = "<br>Alle Teilpakete wurden generiert! Wir bedanken uns f&uuml;r Ihre Geduld!";
$string8 = "Teilpaket ";

$string[0] = "Seriennummer: ";
$string[2] = "Maschinentyp: ";
$string[3] = "Bedienungsanleitung";
$string[5] = "Ersatzteilkatalog";
$string[6] = "Schaltplan";
$string[7] = "Programmnummer";
$string[8] = "Terminalnummer";
$string[9] = "Montageprotokoll";
$string[10] = "CE - Konformit&auml;tserkl&auml;rung/<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;EG - Herstellererkl&auml;rung";
$string[14] = "Stand: ";

$string1_en = "Access violation";
$string2_en = "You are not allowed to access this file!";
$string3_en = "Please choose the desired machine type or put a substring of the wanted file name/serial number in the search field.<br><br>Notice that a search value must consist at least of four characters. The search is case-insensitive, that means \"NP3.\" and \"np3.\"  yield the same results.<br><br>If you encounter problems when downloading a file, click on the respective link with the right mouse button and select  \"Save link as...\".<br><br>Directly opening a document with the Internet Explorer does not always function properly, in this case save the document first and then open it locally.";
$string4_en = "Serial numbers";
$string5_en = "Download all";
$string6_en = "Your download is processed -- please have some patience!<br>If the download exceeds 10MB, it's splitted up in 10MB parts.";
$string7_en = "<br>All parts have been generated! Thank you very much for your patience!";
$string8_en = "Part ";


$string_en[0] = "Serial number: ";
$string_en[2] = "Machine type: ";
$string_en[3] = "Instruction manual";
$string_en[5] = "Spare parts catalog";
$string_en[6] = "Circuit diagram";
$string_en[7] = "Program number";
$string_en[8] = "Terminal number";
$string_en[9] = "Assembly protocol";
$string_en[10] = "CE - declaration of conformity/<br>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;EC - producer declaration";
$string_en[14] = "Issued: ";

// Falls die Anfrage des Clients an eine *.com-Adresse gerichtet ist,
// ersetze sämtliche vorkommenden Strings durch die entprechenden 
// englischen Übersetzungen.
if (ereg("\.com$", strtolower($headers[Host]))) {
	$string1 = $string1_en;
	$string2 = $string2_en;
	$string3 = $string3_en;
	$string4 = $string4_en;
	$string5 = $string5_en;
	$string6 = $string6_en;
	$string7 = $string7_en;
	$string8 = $string8_en;
	
	$string[0] = $string_en[0];
	$string[2] = $string_en[2];
	$string[3] = $string_en[3];
	$string[5] = $string_en[5];
	$string[6] = $string_en[6];
	$string[7] = $string_en[7];
	$string[8] = $string_en[8];
	$string[9] = $string_en[9];
	$string[10] = $string_en[10];
	$string[14] = $string_en[14];
}

////////////////////////////////////////////////////////////////////////////////////////////////////


// Auslesen der php-Datei mit den Funktionen:
// validate_download_suche(), print_nomatch(), print_htmlbegin(), print_htmlend()
require($_SERVER["DOCUMENT_ROOT"] . "/functions.php");

// Auslesen der GET-Variablen
$download = $_GET["get"]; 
$typ      = $_GET["typ"];
$vertrieb = $_GET["vertrieb"];
$suche    = $_GET["suche"];
$suchart  = $_GET["suchart"];
$pack 	  = $_GET["pack"];	

// Es wurde ein gezipptes Download-Paket angefordert.
// ("Alles herunterladen")
if ($pack != '') {

	// Generiere eindeutigen Dateinamen: "download_packed/smb_pack_dd-mm-YY_????"
	$tmpfname = tempnam("download_packed", "smb_pack_" . date("d-m-Y") . "_");
	
	// Lege die "Inhaltsverzeichnis"-Datei des Download-Pakets an. 
	$handle = fopen($tmpfname . ".txt", "w");
	fwrite($handle, $string[0] . "\"File1\", \"File2\", \"File3\", ...\r\n");
	
	$k = 0;
	
	// Durchlaufe die Liste der Seriennummern, 
	// die zum angeforderten Download-Paket gehört.
	for ($j=0; $j<count($_SESSION['liste']); $j++) {
	
		// Schreibe die Seriennummer ins Inhaltsverzeichnis. 
		fwrite($handle, "\r\n" . $_SESSION['liste'][$j] . ":");
		
		// Bestimme alle Dateien, die zur Seriennummer gehören 
		// und speichere die Namen in der Array-Variable $files.
		$lines = file('download/zugriff.txt');
		foreach($lines as $line) {
			
			$spalte = explode(";", $line);
			if ($spalte[0] == $_SESSION['liste'][$j]) {
				for ($i=3; $i<12; $i++) {
					if (trim($spalte[$i]) != '' && file_exists("download/" . $spalte[$i])) {
						$files[$k] = $spalte[$i];
						fwrite($handle, " \"" . $files[$k] . "\"");
						$k++;
					}
				}
			
				for ($i=15; $i<count($spalte); $i++) {
					if (trim($spalte[$i]) != '' && file_exists("download/" . $spalte[$i])) {
						$zusatz = explode("=", $spalte[$i]);
						$files[$k] = $zusatz[1];
						fwrite($handle, " \"" . $files[$k] . "\"");
						$k++;
					}
				}
			}
		}
	}

	fclose($handle);

	// Sortiere den Array mit den Dateinamen 
	// und lösche evtl. Dubletten.
	$files = array_unique($files);
	sort($files);

	// Hier wird dem Skript mitgeteilt, dass die Session-Variable
	// in den folgende Zeilen nicht mehr geändert wird.
	// (Dies ist notwendig, um einen Client das gleichzeitige Downloaden 
	//  mehrerer Files zu ermöglichen).
	session_write_close();

	print_htmlbegin("standard");
	
	echo "<center>";
	echo $string6 . "<br>";

	$part = 1;
	
	// Generiere das zip-File. 
	system("/usr/bin/zip -j -D -q " . $tmpfname . "-" . $part . ".zip " . $tmpfname . ".txt");
	
	// Füge sukzessive alle Dateien zum zip-File hinzu. 
	for ($k=0; $k<count($files); $k++) {
		system("/usr/bin/zip -j -D -g -q " . $tmpfname . "-" . $part . ".zip download/" . $files[$k]);
	
		// Bestimme die momentane Größe des zip-Files.
		$handle = popen("(/usr/bin/du -m " . $tmpfname . "-" . $part . ".zip | /usr/bin/cut -f 1) 2>/dev/null", "r");
	  	$size = fread($handle, 32);
    		pclose($handle);
     		
		// Wenn die Größe 10MB übersteigt, 
		// beginne mit einem neuen zip-File ($part++).
		if ($size > 10) {
			echo "<br><a href=\"$tmpfname-$part.zip\" target=\"_blank\">$string8 $part</a>";
			flush();
			$part++;
		} 
	}
	
	// Falls das Download-Paket nur aus einem zip-File (<= 10MB) besteht,
	// streiche den "$part"-Anteil aus dem Dateinamen.
	if ($part == 1) {
		system("/bin/mv $tmpfname-$part.zip $tmpfname.zip"); 
		echo "<br><a href=\"$tmpfname.zip\" target=\"_blank\">Download</a>";
	} else 
		echo "<br><a href=\"$tmpfname-$part.zip\" target=\"_blank\">$string8 $part</a>";
	echo "</center>";
	echo $string7;
	
	print_htmlend();

// Wenn die Download-Variable gesetzt ist, 
// dann wurde ein File ausgewählt, dass heruntergeladen werden soll:
} else if ($download != '') {
	$file_found = false;

	$lines = file('download/zugriff.txt');
	foreach($lines as $line) {
		$spalte = explode(";", $line);
	
		// Prüfe, ob der eingeloggte User 
		// auf das gewünschte File zugreifen darf.
		// (SMB-Login hat immer Zugriff)	
		if (strtolower($_SESSION['user']) == 'smb' || has_access($spalte[1], $_SESSION['user'])) {
			for ($i=3; $i<12; $i++) 
				if ($spalte[$i] == $download) 
					$file_found = true;

			for ($i=15; $i<count($spalte); $i++) 
				if ($spalte[$i] != '') {
					$zusatz = explode("=", $spalte[$i]);
					if ($zusatz[1] == $download) 
						$file_found = true;
				}
	
			// Falls das File gefunden wurde und der Zugriff gestattet ist,
			// wird zunächst der Datentyp der Datei festgestellt.
			if ($file_found == true) {
				$fp = popen("/usr/bin/file -bin download/$download", 'r');
				if (! $fp) 
					$contentType = "application/octet-stream";
				else {
					while($string = fgets($fp, 1024))
						$contentType .= $string;
       					pclose($fp);
				}
	
				// Hier wird dem Skript mitgeteilt, dass die Session-Variable
				// in den folgende Zeilen nicht mehr geändert wird.
				// (Dies ist notwendig, um einen Client das gleichzeitige Downloaden 
				//  mehrerer Files zu ermöglichen).
				session_write_close();
				
				// Die Datei wird an den Client geschickt.
				header("Content-Type: $contentType");
				header("Content-Disposition: attachment; filename=$download");
				header("Content-Transfer-Encoding: binary");
				header("Content-Length: " . filesize("download/$download"));
				header("Cache-Control: private");
	       			readfile("download/$download");

				// Beende das Script.
				exit;
			}
		}
	}

	// Wenn wir hier angelangen, dann wurde der Zugriff auf 
	// die gewünschte Datei verweigert --> Gebe Fehlermeldung aus.
	print_htmlbegin("standard");
	
	echo "<br>\n";
	echo $string1;
       	echo $string2;
	
	print_htmlend();

// Falls die Variable Typ gesetzt ist,
// werden alle zum Typ gehörigen Seriennummern aufgelistet, auf
// die der eingeloggte User zufgreifen darf:
} else if ($typ != '') {
	$seriennr = array();
	$lines = file('download/zugriff.txt');
	
	$i = 0;
		
	foreach($lines as $line) {
		$spalte = explode(";", $line);
			
		for ($j=0; $j<count($spalte); $j++) 
			$spalte[$j] = trim($spalte[$j]);
		
		// Prüfe, ob der eingeloggte User 
		// auf den gewünschten Typ zugreifen darf.
		// (SMB-Login hat immer Zugriff)	
		if (strtolower($spalte[2]) == strtolower($typ)) {
		   	
			// Falls die Variable $vertrieb gesetzt ist und der SMB-Login verwendet wird,
			// dann liste alle zu $typ gehörigen Seriennummern auf, auf die $vertrieb zugreifen darf.
			if ($vertrieb != '')  {
				if (strtolower($_SESSION['user']) == 'smb' 
						&& has_access($spalte[1], $vertrieb)) {
					$seriennr[$i] = $spalte[0];
					$record = $spalte;
					$i++;
				}
			
			// Falls die Variable $vertrieb nicht gesetzt ist, 
			// dann speichere alle zu $typ gehörigen Seriennummern, auf die der eingeloggte 
			// User/Vertriebspartner zugreifen darf, in der Array-Variablen $seriennr.
			// Der zuletzt gefundene Datensatz wird in $record gespeichert.
			} else {
				if (strtolower($_SESSION['user']) == 'smb' 
						|| has_access($spalte[1], $_SESSION['user'])) {
					$seriennr[$i] = $spalte[0];
					$record = $spalte;
					$i++;		
				}
			}
		}
	}

	// Sortiere die gefundenen Seriennummern alphabetisch und entferne Dubletten. 
	$seriennr = array_unique($seriennr);
	sort($seriennr);

	// Falls nur eine Seriennummer gefunden wurde,
	// gebe die Details zu dieser Seriennummer aus.
	if (count($seriennr) == 1) 
		print_seriennummer($record);
	
	// Falls mehrere Seriennummern gefunden wurden, 
	// gebe die Liste der Seriennummern aus.
	else if (count($seriennr) > 1) 
		print_list($seriennr); 

// Wenn der SMB-Login verwendet wird und die Varibale $vertrieb gesetzt ist, 
// dann liste alle Maschinentypen auf, die $vertrieb zugeordnet sind:
} else if ($vertrieb != '') {
	$typen = array();
	$lines = file('download/zugriff.txt');
	
	$i = 0;
	
	foreach($lines as $line) {
		$spalte = explode(";", $line);
			
		for ($j=0; $j<count($spalte); $j++) 
			$spalte[$j] = trim($spalte[$j]);
		
		// Speichere alle Maschinentypen, auf die Vertrieb zugreifen darf,
		// in der Array-Variablen $typen.
		if (strtolower($_SESSION['user']) == 'smb'
				&& has_access($spalte[1], $vertrieb)) {
			$typen[$i] = $spalte[2];
			$record = $spalte;
			$i++;
		}
	}

	// Sortiere die gefundenen Typen alphabetisch und entferne Dubletten. 
	$typen = array_unique($typen);
	sort($typen);

	// Falls dem Vertrieb bisher noch keine Typen zugeordnet sind, 
	// gebe entprechende Meldung aus.
	if (count($typen) == 0)
		print_nomatch();

	// Andernfalls gebe die Liste der gefunden Typen aus.
	else if (count($typen) >= 1) 
		print_list($typen); 

// Falls nach einer Seriennummer gesucht wurde:
} else if ($suchart == "seriennr") {
	// Prüfe, ob die Suche gewissen Anforderungen genügt.
	validate_download_suche($suche);
	
	$seriennr = array();
	$lines = file('download/zugriff.txt');
		
	$i = 0;
	
	foreach($lines as $line) {
		$spalte = explode(";", $line);
			
		for ($j=0; $j<count($spalte); $j++) 
			$spalte[$j] = trim($spalte[$j]);
				
		// Falls eine Seriennummer existiert, so dass $suche ein Sub-String dieser Seriennummer ist und der
		// eingeloggte User darauf zugreifen darf, dann speichere die Seriennummer im Array $seriennr.
		// Der zuletzt gefundene Datensatz wird in $record gespeichert.
		if (stristr($spalte[0], $suche) 
			&& (strtolower($_SESSION['user']) == 'smb' || has_access($spalte[1], $_SESSION['user'])) ) {
				$seriennr[$i] = $spalte[0];
				$record = $spalte;
				$i++;
		}
	}

	// Sortiere die gefundenen Seriennummern alphabetisch und entferne Dubletten. 
	$seriennr = array_unique($seriennr);
	sort($seriennr);

	// Falls die Suche nicht erfolgreich war, gebe entprechende Meldung aus.
	if (count($seriennr) == 0)
		print_nomatch();
		
	// Falls nur eine Seriennummer gefunden wurde,
	// gebe die Details zu dieser Seriennummer aus.
	else if (count($seriennr) == 1) 
		print_seriennummer($record);
	
	// Falls mehrere Seriennummern gefunden wurden, 
	// gebe die Liste der Seriennummern aus.
	else if (count($seriennr) > 1) 
		print_list($seriennr); 
	
// Falls nach einem Dateinamen gesucht wurde:
} else if ($suchart == "filename") {
	// Prüfe, ob die Suche gewissen Anforderungen genügt.
	validate_download_suche($suche);
		
	$seriennr = array();
	$lines = file('download/zugriff.txt');
	
	$i = 0;
		
	foreach($lines as $line) {
		$found = 0;
		$spalte = explode(";", $line);
		
		for ($j=0; $j<count($spalte); $j++) 
			$spalte[$j] = trim($spalte[$j]);
		
		// Falls eine Datei existiert, so dass $suche ein Sub-String dieses Dateinamens ist und der
		// eingeloggte User darauf zugreifen darf, dann speichere die zugehörige Seriennummer im Array $seriennr.
		// Der zuletzt gefundene Datensatz wird in $record gespeichert.
		if (strtolower($_SESSION['user']) == 'smb' || has_access($spalte[1], $_SESSION['user'])) {
			for ($j=3; $j<12; $j++) 
				if (stristr($spalte[$j], $suche)) {
					$found = 1;
					break;
				}
					
			for ($j=15; $j<count($spalte); $j++) 
				if ($spalte[$j] != '') {
					$zusatz = explode("=", $spalte[$j]);
					if (stristr($zusatz[1], $suche)) {
						$found = 1;
						break;
					}
				}

			if ($found == 1) {
				$seriennr[$i] = $spalte[0];
				$record = $spalte;
				$i++;
			}
		}
	}
		
	// Sortiere die gefundenen Seriennummern alphabetisch und entferne Dubletten. 
	$seriennr = array_unique($seriennr);
	sort($seriennr);
		
	// Falls die Suche nicht erfolgreich war, gebe entprechende Meldung aus.
	if (count($seriennr) == 0)
		print_nomatch();
	
	// Falls nur eine Seriennummer gefunden wurde,
	// gebe die Details zu dieser Seriennummer aus.
	else if (count($seriennr) == 1) 
		print_seriennummer($record);
	
	// Falls mehrere Seriennummern gefunden wurden, 
	// gebe die Liste der Seriennummern aus.
	else if (count($seriennr) > 1) 
		print_list($seriennr); 

// Gebe Hilfetext aus (Format der Suche, 
// Hinweise zum Internet Explorer, Abspeichern der Dateien)
} else 
	print_description();


// Funktion zum Ausgeben der Liste von Typen bzw. Seriennummern.
function print_list($liste) 
{	
	global $typ, $vertrieb, $string4, $string5, $string6, $string;
	
	// Falls $typ gesetzt ist, schreibe Standard-HTML Einleitungs-Tags 
	// und verwende als Hintergrundbild "$typ.jpg" 
	if ($typ != '') {
		print_htmlbegin(strtolower($typ));

		echo "<table>\n";
		echo "<tr>";
		echo "<th nowrap=\"nowrap\">";
	
		echo $string[2] . $typ;
	
	// Falls $vetrieb gesetzt ist, schreibe Standard-HTML Einleitungs-Tags
	// und verwende als Hintergrundbild "standard.jpg"
	} else if ($vertrieb != '') {
		print_htmlbegin("standard");
		
		echo "<table>\n";
		echo "<tr>";
		echo "<th nowrap=\"nowrap\">";
		echo "Vertriebspartner: $vertrieb"; 
		
	// Schreibe Standard-HTML Einleitungs-Tags
	// und verwende als Hintergrundbild "standard.jpg"
	} else {
		print_htmlbegin("standard");
		
		echo "<table>\n";
		echo "<tr>";
		echo "<th nowrap=\"nowrap\">";

		echo $string4;
	}

	echo "</th></tr>\n";
	
	// Hier wird die eigentliche Liste ausgegeben
	// und die Links entsprechend generiert.
	for ($i=0; $i<count($liste); $i++) {
		echo "<tr><td align=\"center\">";
		
		if ($typ != '')
			echo "<a href=\"download.php?suche=$liste[$i]&amp;suchart=seriennr\">$liste[$i]</a>";
		else if ($vertrieb != '') 
			echo "<a href=\"download.php?typ=$liste[$i]&amp;vertrieb=$vertrieb\">$liste[$i]</a>";
		else 
			echo "<a href=\"download.php?suche=$liste[$i]&amp;suchart=seriennr\">$liste[$i]</a>";
		
		echo "</td></tr>\n";
	}
				
	echo "</table>\n";

	// Speichere die Liste in der Variablen $_SESSION['liste'] und 
	// gebe den Link "Alles herunterladen" aus.
	// Ein Anklicken dieses Links hat zur Folge, 
	// dass die Variable $_GET['pack'] auf true gesetzt wird.
	if (!isset($vertrieb)) {
		$_SESSION['liste'] = $liste;
		
		echo "<hr width=\"75%\">";
		echo "<a href=\"download.php?pack=true\">" . $string5 . "</a>";
	}

	// Schreibe Standard-HTML Ende-Tags 
	print_htmlend();
}


// Funktion zum Ausgeben eines Datensatzes.
function print_seriennummer($record)
{
	global $string;

	// Schreibe Standard-HTML Einleitungs-Tags,
	// und verwende als Hintergrundbild 
	// das zum Typ der Seriennummer gehörige Bild. 
	print_htmlbegin(strtolower($record[2]));
	
	// Gebe den Datensatz mit den entprechenden Links 
	// in einer Tabelle aus.
	echo "<table>\n";
	echo "<tr><th colspan=\"2\" nowrap=\"nowrap\">" . $string[0] . $record[0] . "</th></tr>\n";
		
	// Gebe die Standardfelder aus, wenn sie nicht leer sind.
	if ($record[3] != '' || $record[4] != '') {
		echo "<tr>";
		echo "<td>" . $string[3] . "</td>";
		echo "<td>";
				
		if ($record[3] != '') 
			print_getlink($record[3], "$record[3] ($record[12])");
		
		if ($record[3] != '' && $record[4] != '')
			echo "<br>";
					
		if ($record[4] != '') 
			print_getlink($record[4], "$record[4] ($record[13])");
				
		echo "</td>";
		echo "</tr>\n";
	} 
	
	for ($i=5; $i<10; $i++) {
		// Programmnummer / Terminalnummer - Downloads sollen nur für SMB und Dynaric sichtbar sein
		if ($i == 7 || $i == 8)
			if (!(strtolower($_SESSION['user']) == 'smb' || strtolower($_SESSION['user']) == 'dynaric'))
				continue;
	
		if ($record[$i] != '') {
			echo "<tr>";
			echo "<td>" . $string[$i] . "</td>";
			echo "<td>";
		
			print_getlink($record[$i], $record[$i]);
			
			echo "</td>";
			echo "</tr>\n";
		}
	}
		
	if ($record[10] != '' || $record[11] != '') {
		echo "<tr>";
		echo "<td>" . $string[10] . "</td>";
		echo "<td>";
					
		if ($record[10] != '') 
			print_getlink($record[10], $record[10]);

		if ($record[10] != '' && $record[11] != '')
			echo "<br>";
						
		if ($record[11] != '') 
			print_getlink($record[11], $record[11]);
					
		echo "</td>";
		echo "</tr>\n";
	}

	// Gebe die Zusatzfelder aus.
	for ($i=15; $i<count($record); $i++) {
		if ($record[$i] != '') {
			$zusatz = explode("=", $record[$i]);
				
			echo "<tr>";
			echo "<td>$zusatz[0]</td>";
			echo "<td>";
			
			print_getlink($zusatz[1], $zusatz[1]);
			
			echo "</td>";
			echo "</tr>\n";
		}
	}
			
	echo "<tr><td colspan=\"2\"><hr></td></tr>\n";

	// Falls der SMB-Login verwendet wird, dann gebe am Ende der Tabelle aus, 
	// welchem Vertriebspartner der Datensatz zugeordnet ist.
	if (strtolower($_SESSION['user']) == 'smb') {
		echo "<tr>";
		echo "<td align=\"center\" colspan=\"2\">" . "Vertriebspartner: " . $record[1] . "</td>";
		echo "</tr>\n";
	}
	
	// Gebe den Stand/Änderungsdatum des Datensatz aus.
	echo "<tr>";
	echo "<td align=\"center\" colspan=\"2\">" . $string[14] . $record[14] . "</td>";
	echo "</tr>\n";
	echo "</table>\n";
	
	// Schreibe Standard-HTML Ende-Tags 
	print_htmlend();
}


// Funktion zum Ausgeben der Hilfetexte (Format der Suche, 
// Hinweise zum Internet Explorer, Abspeichern der Dateien)
function print_description()
{
	global $string3;
	
	print_htmlbegin("standard");
		
	echo "<table>\n";
	echo "<tr><td align=\"justify\">";	
	echo $string3;
	echo "</td></tr>\n";
	echo "</table>\n";
	
	print_htmlend();
}


// Funktion zum Überprüfen, ob $vertrieb auf den Datensatz zugreifen darf.
function has_access($comma_list, $vertrieb)
{
	$partner = explode(",", $comma_list);
	for ($j=0; $j<count($partner); $j++) 
		if (strtolower($vertrieb) == strtolower($partner[$j]))
			return true;
	return false;
}


// Funktion zum Überprüfen, ob der Link $link vorhanden ist. 
// Falls ja, wird ein anklickbarer Download-Link generiert, 
// andernfalls wird lediglich der Text $descr ausgegeben.
function print_getlink($link, $descr)
{
	if (file_exists("download/" . $link)) 
		echo "<a href=\"download.php?get=$link\">$descr</a>";
	else
		echo "$descr";
}

?>
