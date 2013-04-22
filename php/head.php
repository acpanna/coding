<?php

// Auslesen der Anfrage-Header, die vom Client-Browser 
// an den Web-Server geschickt wurden.
$headers = getallheaders(); 

///////////////////////////////////// Strings Deutsch-Englisch /////////////////////////////////////

$pic = "vertriebspartner.jpg";
$pic_en =" distributor.jpg";

// Falls die Anfrage des Clients an eine *.com-Adresse gerichtet ist,
// ersetze sämtliche vorkommenden Strings durch die entprechenden 
// englischen Übersetzungen.
if (ereg("\.com$", strtolower($headers[Host]))) 
	$pic = $pic_en;

////////////////////////////////////////////////////////////////////////////////////////////////////

echo "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Frameset//EN\" \"http://www.w3.org/TR/html4/frameset.dtd\">\n";
echo "<html>\n";
echo "<head>\n";
echo "<title>SMB Schwede Maschinenbau GmbH -- Downloads</title>\n";
echo "</head>\n";
echo "<body>\n";
echo "<center>\n";
echo "<table>\n";
echo "<tr><td><img src=\"images/smblogo.gif\" alt=\"SMB-Logo\"></td><td><img src=\"$pic\" alt=\"Vertriebspartner\"></td></tr>\n";
echo "</table>\n";
echo "</center>\n";
echo "</body>\n";
echo "</html>\n";

?>
