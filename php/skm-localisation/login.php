<?php

session_start();
require 'auth.php';

?>
<HTML>
	<HEAD>
		<TITLE>Sketchometry Localisation Project</TITLE>
		<LINK rel=stylesheet type="text/css" href="style.css">
	</HEAD>
<BODY>

<?php
if (isset($_SESSION['uname'])) {

	if (isset($_SESSION['edit_orig'])) {
		$_SESSION['edit'] = $_SESSION['edit_orig'];
		unset($_SESSION['edit_orig']);
	}

	if (isset($_GET['logout'])) {
		echo "<DIV class=\"border\" id=\"box\">";
		unset($_SESSION['uname']);
		echo "Successfully logged out!";
		echo "</DIV>";
		exit;
	}
}

if (!isset($_SESSION['uname'])) {
?>
<BR>

<DIV align="center">
	Please login to use the online translation tool.
	<P></P>

	<FORM action="login.php" method="POST">
	<TABLE>
	<TR><TD>Username:</td><td><input type="text" name="uname"></TD></TR>
	<TR><TD>Password:</td><td><input type="password" name="pwd"></TD></TR>
	</TABLE>
	<INPUT type="submit" value="Submit">
	</FORM>
</DIV>

</BODY>
</HTML>
<?php
	exit;
}

logged_in_as();

?>
<DIV align="center" class="pad-lr">
	<P>Please select the localisation you want to edit:</P>

	<FORM action="edit.php" method="POST">
	<SELECT name="language">
<?php

if ($_SESSION['edit'] != "all") {
	$query = "SELECT id, name FROM languages WHERE id IN ";
	$query.= "(" . $_SESSION['edit'] . ") ORDER BY id";
} else 
	$query = "SELECT id, name FROM languages ORDER BY id";

$dblink = @mysql_connect("dbnfs", "gast", "");

$result = mysql_db_query("skm_localisation", $query, $dblink);

while ($row = mysql_fetch_row($result))
	echo "<OPTION value=\"" . $row[0] . "\">" . $row[1] . "</OPTION>";

mysql_close($dblink);
?>
	</SELECT>
	<INPUT type="submit" value="Submit">
	</FORM>
</DIV>

</BODY>
</HTML>
