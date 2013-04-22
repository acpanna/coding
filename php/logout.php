<?php

// Lade die Session-Daten und speichere sie im Array $_SESSION.
session_start();
$_SESSION = array();

// Setze die Lebensdauer des Session-Cookies auf einen negativen wert --> Cookie wird ungültig 
setcookie(session_name(), '', -1, $CookieInfo['path'], $CookieInfo['domain'], $CookieInfo['secure']);

// Zerstöre die Session (bewirkt, dass die auf dem Server 
// gespeicherten Informationen zur Session gelöscht werden).
session_destroy();

// Sende Browserumleitung auf die Startseite des Downloadbereichs.
header("Location: http://" . $_SERVER['HTTP_HOST'] . "/docfiles.php");

?>
