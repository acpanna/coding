<?php	

if (isset($_POST['uname']) && $_POST['uname'] != "") {
	
	$dblink = @mysql_connect("dbnfs", "gast", "");

	// The "gast" user has just (MySQL) SELECT permissions, 
	// so the POST input can be used unfiltered for the account 
	// verification ...
	 
	$query = "SELECT firstname, lastname, uname, password, edit, ref, id "; 
	$query.= "FROM users WHERE uname = '" . $_POST['uname'] . "'";

	$result = mysql_db_query("skm_localisation", $query, $dblink);

	$data = mysql_fetch_row($result);
	
	if ($data[2] == $_POST['uname'] && md5($_POST['pwd']) == $data[3]) {

		$_SESSION['firstname'] = $data[0];
		$_SESSION['lastname'] = $data[1];
		$_SESSION['uname'] = $data[2];
		$_SESSION['pwd'] = $data[3];
		$_SESSION['edit'] = $data[4];
		$_SESSION['ref'] = $data[5];
		$_SESSION['uid'] = $data[6];
	}

	mysql_close($dblink);
}

function logged_in_as() {
	echo "<DIV class=\"border\" id=\"logbox\">";
	echo "Logged in as: " . $_SESSION['firstname'] . " ";
	echo $_SESSION['lastname'] . " -- ";
	echo '<A href="login.php?logout=yes">Logout</a>';
	echo "</DIV>";
	echo "<BR clear=\"both\">";
}

?>
