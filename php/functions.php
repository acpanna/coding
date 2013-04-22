<?php

// Auslesen der Anfrage-Header, die vom Client-Browser 
// an den Web-Server geschickt wurden.
$headers = getallheaders(); 

///////////////////////////////////// Strings Deutsch-Englisch /////////////////////////////////////

$string1001 = "Zu viele Treffer! Bitte schränken Sie Ihre Suche ein!";
$string1002 = "Ihre Suche war leider nicht erfolgreich! Keine Treffer!";

$string1001_en = "Too much hits! Please narrow your search!";
$string1002_en = "Your search was not succesful! No hits!";

// Falls die Anfrage des Clients an eine *.com-Adresse gerichtet ist,
// ersetze sämtliche vorkommenden Strings durch die entprechenden 
// englischen Übersetzungen.
if (ereg("\.com$", strtolower($headers[Host]))) {
	$string1001 = $string1001_en;
	$string1002 = $string1002_en;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
	
// Funktion zum Überprüfen des Suchbegriffs
function validate_download_suche($suche) 
{
	global $string1001;
	$suche = strtolower(trim($suche));

	// Falls die Suche  mit "[buchstabe].irgendwas" beginnt, kürzer als 4 Zeichen,
	// oder gleich ".pdf", "_ce_" bzw. "_he_" ist, dann gebe Fehlermeldung aus
	// 	--> Suche ist zu allgemein!  
	if (preg_match("/^.\..*/", $suche) 
			|| $suche == ".pdf" || $suche == "_ce_" || $suche == "_he_" 
			|| strlen($suche) < 4) {
		
		print_htmlbegin("standard");
		
		echo "<table>\n";
		echo "<tr><td align=\"justify\">";	
		echo $string1001;
		echo "</td></tr>\n";
		echo "</table>\n";
		
		print_htmlend();
		exit;
	}
}		

function validate_browse_suche() 
{
	global $string1001, $suche;
	
	$suche2 = str_replace('*', '', $suche);
	if (preg_match("/^.\..*/", $suche) 
			|| $suche == ".pdf" || strlen($suche2) < 3) {
			
		print_htmlbegin("standard");

	        echo "<table>\n";
		echo "<tr><td align=\"justify\">";
		echo $string1001;
		echo "</td></tr>\n";
		echo "</table>\n";
   
   		print_htmlend();
		exit;
	}
	
	$suche = str_replace('.', '\.', $suche);
	$suche = str_replace('*', '.*', $suche);
}

// Diese Funktion gibt eine entsprechende Meldung aus,
// falls die Suche nicht erfolgreich war.
function print_nomatch() 
{
	global $string1002;
	
	print_htmlbegin("standard");
	
	echo "<table>\n";
	echo "<tr><td align=\"justify\">";	
	echo $string1002;
	echo "</td></tr>\n";
	echo "</table>\n";
		
	print_htmlend();
}


// Funktion, die die Standard-HTML Einleitungs-Tags
// und ein vorgegebenes Hintergrundbild ausgibt.
function print_htmlbegin($image)
{
	echo "<html>\n";
	echo "<head>\n";
	echo "<title>SMB Schwede Maschinenbau GmbH -- Downloads</title>\n";
	echo "<link rel=\"stylesheet\" type=\"text/css\" href=\"download.css\">\n";
	echo "</head>\n";
	
	if (file_exists("images/" . $image . ".jpg"))
		echo "<body background=\"images/" . $image . ".jpg\">\n";
	else
		echo "<body background=\"images/standard.jpg\">\n";

	echo "<center>\n";
}


// Funktion, zum Ausgeben der Standard-HTML Ende-Tags.
function print_htmlend()
{
	echo "</center>\n";
	echo "</body>\n";
	echo "</html>";
}

?>
