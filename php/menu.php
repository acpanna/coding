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

$string1 = "Eingeloggt als: ";
$string2 = "Suche";
$string3 = "Seriennummer";
$string4 = "Dateiname";
$string5 = "Maschinentyp";
$string6 = "Ausloggen";
$string7 = "Alte Downloads";

$string1_en = "Logged in as: ";
$string2_en = "Search";
$string3_en = "Serial number";
$string4_en = "File name";
$string5_en = "Machine type";
$string6_en = "Logout";
$string7_en = "Old downloads";

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
}

////////////////////////////////////////////////////////////////////////////////////////////////////


echo "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n";
echo "<html>\n";
echo "<head>\n";
echo "<title>SMB Schwede Maschinenbau GmbH -- Downloads</title>\n";
echo "<link rel=\"stylesheet\" type=\"text/css\" href=\"download.css\">\n";
echo "</head>\n";
echo "<body>\n";
echo "<center>\n";

// Lese die Datei "download/zugriff.txt" aus, und prüfe
// auf welche Maschinentypen, der eingeloggte Vertriebpartner, 
// zugreifen darf: Speichere die Maschinentypen in der Array-Variable $typ.
// Falls ein SMB-Login verwendet wurde, speichere ALLE Vertriebpartner und ALLE
// Maschinentypen in den Array-Variablen $vertrieb bzw. $typ.
$i = 0;
$lines = file('download/zugriff.txt');
foreach($lines as $line) {
	$spalte = explode(";", $line);

	// Zeilen, die mit einem '#' beginnen, werden ignoriert.
	if (substr(trim($line), 0, 1) != '#') {
		$partner = explode(",", $spalte[1]);
		for ($j=0; $j<count($partner); $j++)
			if (strtolower($_SESSION['user']) == 'smb'
					|| strtolower($partner[$j]) == strtolower($_SESSION['user'])) {
				$vertrieb[$i] = $partner[$j];
				$typ[$i] = $spalte[2];
				$i++;
			}
	}
}

// Sortiere die Vetriebspartner und Maschinentypen 
// alphabetisch und entferne Dubletten.
$vertrieb = array_unique($vertrieb);
$typ = array_unique($typ);
sort($vertrieb);
sort($typ);

// Präsentiere das Menü.
echo "<table>\n";
echo "<tr><th>" . $string1 . $_SESSION['user'];
echo "<font size=2>";
echo "<br><br><a href=\"logout.php\" target=\"_top\" class=\"log\">" . $string6 . "</a>";
echo "</font>";
echo "</th></tr>\n";
echo "<tr><td>";

// Gebe die Suchfelder mit den entsprechenden Radio-Buttons aus:
// Die Suche, bzw. ein ausgewählter Menüpunkt werden als GET-Variablen 
// an die Datei "download.php" weitergeleitet.
echo "<form target=\"download\" action=\"download.php\" method=\"GET\">\n";
echo "<input size=\"15\" maxlength=\"50\" type=\"text\" name=\"suche\">&nbsp;&nbsp;&nbsp;";
echo "<input type=\"submit\" name=\"submit\" value=\"" . $string2 . "\"><br>";
echo "<input type=\"radio\" name=\"suchart\" value=\"seriennr\" checked>" . $string3;
echo "<br><input type=\"radio\" name=\"suchart\" value=\"filename\">" . $string4;
echo "</form>\n";

echo "</td></tr>\n";
echo "<tr><td>";
echo "<hr>";
echo "</td></tr>\n";
echo "<tr align=center><td>";
echo $string5 . ":<br>";
echo "</td></tr>\n";
echo "<tr align=center><td>";

// Liste die Maschinentypen auf, 
// auf die Zugriff gestattet ist.
for ($i=0; $i<count($typ); $i++)
	echo "<a href=\"download.php?typ=$typ[$i]\" target=\"download\">$typ[$i]</a>" . "<br>";
echo "</td></tr>\n";

// Falls ein SMB-Login verwendet wurde, 
// liste zusätzlich alle Vertriebspartner auf. 
if (strtolower($_SESSION['user']) == 'smb') {
	echo "<tr><td>";
	echo "<hr>";
	echo "</td></tr>\n";
	echo "<tr align=center><td>";
	echo "Vertriebspartner:<br>";
	echo "</td></tr>\n";
	echo "<tr align=center><td>";
	for ($i=0; $i<count($vertrieb); $i++)
		echo "<a href=\"download.php?vertrieb=$vertrieb[$i]\" target=\"download\">$vertrieb[$i]</a>" . "<br>";
	echo "</td></tr>\n";
}

echo "</table>\n";

// Link auf die alten Downloads.
echo "<br><a href=\"browse.php?dir=.\" target=\"download\">$string7</a><br>";

echo "<br><a href=\"http://www.adobe.co.uk/products/acrobat/readstep2.html\" target=\"_blank\">";
echo "<img src=\"images/getacro.gif\" alt=\"Get Acrobat Reader\" border=0>";
echo "</a>\n";

echo "</center>\n";
echo "</body>\n";
echo "</html>\n";
