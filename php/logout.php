<?php

// Lade die Session-Daten und speichere sie im Array $_SESSION.
session_start();
$_SESSION = array();

// Setze die Lebensdauer des Session-Cookies auf einen negativen wert --> Cookie wird ung�ltig 
setcookie(session_name(), '', -1, $CookieInfo['path'], $CookieInfo['domain'], $CookieInfo['secure']);

// Zerst�re die Session (bewirkt, dass die auf dem Server 
// gespeicherten Informationen zur Session gel�scht werden).
session_destroy();

// Sende Browserumleitung auf die Startseite des Downloadbereichs.
header("Location: http://" . $_SERVER['HTTP_HOST'] . "/docfiles.php");

?>
