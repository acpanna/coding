<?php

// Überprüfen, ob der Kunde eingeloggt ist: 
//	Falls nein --> Abbruch
session_start();
if (!isset($_SESSION['user']))
	exit;	

// Wenn der SMB-Login verwendet wird, wechsle ins Verzeichnis "download_old"
else if (strtolower($_SESSION['user']) == 'smb')
	$root = realpath("download_old");
	
// Andernfalls wechsle ins Verzeichnis "download_old/$_SESSION['user']".
else 
	$root = realpath("download_old/" . strtolower($_SESSION['user']));

// Falls das Verzeichnis nicht existiert, beende das Script.
if (!@chdir($root))
	exit;

// Auslesen der Anfrage-Header, die vom Client-Browser 
// an den Web-Server geschickt wurden.
$headers = getallheaders();

///////////////////////////////////// Strings Deutsch-Englisch /////////////////////////////////////

$string1 = "Momentanes Verzeichnis";
$string2 = "Verzeichnisse";
$string3 = "Datei(en)";
$string4 = "Gefundene Datei(en)";
$string5 = "Datei-Suche";

$string1_en = "Current directory";
$string2_en = "directories";
$string3_en = "file(s)";
$string4_en = "File(s) found";
$string5_en = "File search";

// Falls die Anfrage des Clients an eine *.com-Adresse gerichtet ist,
// ersetze sämtliche vorkommenden Strings durch die entprechenden 
// englischen Übersetzungen.
if (ereg("\.com$", strtolower($headers[Host]))) {
	$string1 = $string1_en;
	$string2 = $string2_en;
	$string3 = $string3_en;
	$string4 = $string4_en;
	$string5 = $string5_en;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

// Auslesen der php-Datei mit den Funktionen:
// validate_browse_suche(), print_nomatch(), print_htmlbegin(), print_htmlend()
require($_SERVER["DOCUMENT_ROOT"] . "/functions.php");

// Lese die GET-Variablen aus, die an das Script übergeben wurden.
$dir = $_GET["dir"];
$suche = $_GET["suche"];

// Wenn der Pfad $dir NICHT unterhalb von $root liegt, bleibe in $root.
// Andernfalls mache aus $dir eine relative Pfadangabe.
if (!ereg("^" . $root, realpath($dir)))
	$dir = "./";
else
	$dir = str_replace($root, "./", realpath($dir)); 

if ($suche != '') {
	// Überprüfe den Suchbegriff. 
 	validate_browse_suche(); 

	$i = 1;
	$j = 0;
	
	// Beginne die Suche im aktuellen Verzeichnis
	$dirs[0] = $dir;

        // Lese alle Dateien aus, die sich im Verzeichnis $dirs[k] befinden.
	// Hänge alle gefundenen Verzeichnisse an das Array $dirs an, 
	// und alle regulären Dateien, die der Suche entprechen, an das Array $file.
	for ($k=0; $k<count($dirs); $k++) {
		$handler = opendir($dirs[$k]);
		while ($file = readdir($handler)) {
			if ($file != '.' && $file != '..') {
				$file = htmlspecialchars($file);
		
				if (is_dir("$dirs[$k]/$file")) {
					$dirs[$i] = "$dirs[$k]/$file";
					$i++;
				} else if (eregi($suche, $file)) {
					$files[$j] = "$dirs[$k]/$file"; 
					$j++;
				}
			}
		}
	}

	// Falls keine Files gefunden wurden
	// --> entprechende Meldung
	if (count($files) == 0)
		print_nomatch();
	else {
		// Andernfalls gebe die gefundenen Files 
		// in Form einer Tabelle aus.
		print_htmlbegin("standard");
	
		echo "<table>\n";
		echo "<th>" . $string4 . "</th>\n";
		sort($files);
		for ($i=0; $i<count($files); $i++) {
			echo "<tr><td align=\"center\">\n";
			echo "<a href=\"browse.php?dir=$files[$i]\">";
			echo basename($files[$i]);
			echo "</a>";
			echo "</td></tr>\n";
		}
	
		echo "<tr><td align=\"center\"><hr></td></tr>\n";
		echo "<tr><td>" . count($files). " $string3</td></tr>\n";
		echo "</table>\n";
	
		print_htmlend();
	}
	
} else {
	// Falls nicht gesucht wurde, 
	// dann wurde auf einen Verzeichnis- oder Dateinamen geklickt.
	// Falls auf ein Verzeichnis geklickt wurde, lese den Verzeichnisinhalt aus.
	if (is_dir($dir)) {
		print_htmlbegin("standard");

		$i = $j = 0;
		
		$handler = opendir($dir);
		while ($file = readdir($handler)) {
			if ($file != '.') {
	 			$file = htmlspecialchars($file);
		
				if (is_dir("$dir/$file")) {
					$dirs[$i] = $file;
					$i++;
				} else {
			 		$files[$j] = $file;
					$j++;
				}
			}
		}

		// Gebe den Verzeichnisinhalt aus 
		// und generiere entsprechende Links
		echo "<table>\n";
		echo "<th>$string1: $dir</th>\n";
	
		// Gebe die Unterverzeichnisse aus
		for ($i=0; $i<count($dirs); $i++) {
			echo "<tr><td align=\"center\">\n";
			echo "<a href=\"browse.php?dir=$dir/$dirs[$i]\" class=\"dir\">";
			echo $dirs[$i] . "/";
			echo "</a>";
			echo "</td></tr>\n";
		}
	
		// Gebe die regulären Files aus
		for ($i=0; $i<count($files); $i++) {
			echo "<tr><td align=\"center\">\n";
			echo "<a href=\"browse.php?dir=$dir/$files[$i]\">";
			echo $files[$i];
			echo "</a>";
			echo "</td></tr>\n";
		}
	
		// Gebe die Anzahl der gefunden Verzeichnisse/Files aus.
		echo "<tr><td align=\"center\"><hr></td></tr>\n";
		echo "<tr><td>" . count($dirs) . " $string2, " . count($files). " $string3</td></tr>\n";
		echo "</table>\n<br>\n";

		// Gebe Suchfeld aus.
		echo "<form target=\"download\" action=\"browse.php\" method=\"GET\">\n";
		echo "<input size=\"15\" maxlength=\"50\" type=\"text\" name=\"suche\">&nbsp;&nbsp;&nbsp;";
		echo "<input type=\"submit\" name=\"submit\" value=\"" . $string5 . "\"><br>";
		echo "<input type=\"hidden\" name=\"dir\" hidden value=\"$dir\">"; 

		print_htmlend();

	} else {
		// Falls auf eine reguläre Datei geklickt wurde,
		// bestimme den Typ der Datei.
		$fp = popen("/usr/bin/file -bin $dir", 'r');
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
		header("Content-Disposition: attachment; filename=" . basename($dir)); 
		header("Content-Transfer-Encoding: binary");   
		header("Content-Length: " . filesize($dir)); 
		header("Cache-Control: private");
		readfile("$dir"); 
	}
}

?>
