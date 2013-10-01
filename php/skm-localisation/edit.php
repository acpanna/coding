<?php

session_start();
require 'auth.php';

if (!isset($_SESSION['uname'])) {
?>
<HTML>
	<HEAD>
		<TITLE>Sketchometry Localisation Project</TITLE>
		<LINK rel="stylesheet" type="text/css" href="style.css">
	</HEAD>
<BODY>
<?php
	echo "No existing session!";
?>
</BODY>
</HTML>
<?php
	exit;
}

function filter_user_input($str) {
	$str = str_replace("\n", "", $str);
	$str = str_replace("\r", "", $str);
/*	
	$str = str_replace("\n", "&#10", $str);
	$str = str_replace("\r", "&#13", $str);
*/
	/* Disable SQL Injection */
	
	$str = str_replace('"', "&#34", $str);
	$str = str_replace("'", "&#39", $str);
	$str = str_replace(";", "&#59", $str);

	return $str;
}

function restore_user_input($str, $maskApo, $maskQuot) {
/*	
	$str = str_replace("&#10", "\n", $str);
	$str = str_replace("&#13", "\r", $str);
 */
	if ($maskQuot)
		$str = str_replace("&#34", '\"', $str); 
	else
		$str = str_replace("&#34", '"', $str); 
	
	if ($maskApo)
		$str = str_replace("&#39", "\'", $str);
	else
		$str = str_replace("&#39", "'", $str);
	
	$str = str_replace("&#59", ";", $str);

	return $str;
}

/***********************/
$db = 'skm_localisation';
$user = 'localisation';
$passwd = 'skmmks';
/***********************/

if ($_POST['index']) {
	$index = $_POST['index'];

	$dblink = @mysql_connect("dbnfs", $user, $passwd);

	for ($i=1; $i<=$index; $i++) {

		$text = filter_user_input($_POST["e" . $i]); 

		if ($text == "")
			continue;

		// Insert the entry / Update the database ...
		
		$query = "INSERT INTO entries (var_id, language_id, text, author_id) ";
		$query .= "VALUES (" . $i . ", ". $_SESSION['edit'] . ", '";
		$query .= $text . "', " . $_SESSION['uid']  . ");";
		$result = mysql_db_query($db, $query, $dblink);

		if (!$result) {
		 	$query = "UPDATE entries SET text='" . $text . "', ";
			$query .= "author_id=" . $_SESSION['uid'] . " ";
			$query .= "WHERE var_id=$i AND ";
			$query .= "language_id=" . $_SESSION['edit'] . ";";
			$result = mysql_db_query($db, $query, $dblink);
		}
	}

	mysql_close($dblink);

	// Generate a lang(-dev).js file ...
	
	if (isset($_POST['generate'])) {

		$str = "/*\n";
		$str .= "      Copyright 2011 / 2012\n";
		$str .= "          Matthias Ehmann,\n";
		$str .= "          Michael Gerhaeuser,\n";
		$str .= "          Carsten Miller,\n";
		$str .= "          Heiko Vogel,\n";
		$str .= "          Alfred Wassermann\n";
		$str .= "\n";
		$str .= "      This file is part of the JSXGraph GUI project.\n";
		$str .= "      This code isn't licensed yet.\n";
		$str .= " */\n";
		$str .= "\n";
		$str .= "GUI.Lang = { };\n";
		$str .= "\n";
		$str .= "GUI.Lang.Map = [[ 'de', 'en', 'fr', 'es', 'pt', 'it' ], [ 'Deutsch', 'English', 'Français', 'Español', 'Português', 'Italiano' ]];\n";
		$str .= "\n";
		$str .= "GUI.Lang.strings = {\n";

		$dblink = @mysql_connect("dbnfs", "gast", "");

		$query = "SELECT MAX(ID) from vars";
		$result = mysql_db_query($db, $query, $dblink);

		$row = mysql_fetch_row($result);
		$maxid = $row[0];

		$query = "SELECT MAX(ID) from languages";
		$result = mysql_db_query($db, $query, $dblink);

		$row = mysql_fetch_row($result);
		$maxlang = $row[0];

		$query = "SELECT id, var FROM vars ORDER BY var";
		$result = mysql_db_query($db, $query, $dblink);

		for ($i=1; $i<=$maxid; $i++) {

			$row = mysql_fetch_row($result);

			if (!$row)
				continue;

			$id = $row[0];
			$ref = $row[1];

			$str .= "    '$ref': [ ";

			for ($l=1; $l<=$maxlang; $l++) {

				$query_ref = "SELECT text FROM entries WHERE var_id=" . $id;
				$query_ref .= " AND language_id=" . $l;

				$result_ref = mysql_db_query($db, $query_ref, $dblink);
				$row_ref = mysql_fetch_row($result_ref);
				
				$text = restore_user_input($row_ref[0], true, true);
				
				$str .= "'$text'";

				if ($l < $maxlang)
					$str .= ", ";
			}

			$str .= " ]";
			if ($i < $maxid)
				$str .= ",";
			$str .= "\n";
		}

		mysql_close($dblink);

		$str .= "};";
		
		$f = fopen("lang-dev.js", 'w');
		fwrite($f, $str);
		fclose($f);
	}
}

/***************************************************************/
?>
<HTML>
	<HEAD>
		<TITLE>Sketchometry Localisation Project</TITLE>
		<LINK rel=stylesheet type="text/css" href="style.css">
	</HEAD>
	
	<BODY>
	
		<A class="menu" href="login.php" 
			target="main">(Re-)Select Localisation</A>

		<A class="menu" href="http://beta.sketchometry.com/index.html?dev=1" 
			target="_blank">View Live-Changes</A>
<?php

logged_in_as();

if (isset($_GET['ref'])) { 

	$_SESSION['ref'] = $_GET['ref'];

	$dblink = @mysql_connect("dbnfs", "gast", "");

	$query_maxid = "SELECT MAX(ID) from vars";
	$result_maxid = mysql_db_query($db, $query_maxid, $dblink);

	echo "<SCRIPT language=\"JavaScript\">";

	$row = mysql_fetch_row($result_maxid);
	$maxid = $row[0];

	echo "function replaceRef(id, txt) {";
	echo "	var el = document.getElementById('ref' + id);";
	echo "	if (el) el.innerHTML = txt;";
	echo "}";

	for ($i=1; $i<=$maxid; $i++) {

		$query_ref = "SELECT text FROM entries WHERE var_id=" . $i;
		$query_ref .= " AND language_id=" . $_SESSION['ref'];

		$result_ref = mysql_db_query($db, $query_ref, $dblink);
		$row = mysql_fetch_row($result_ref);
	
		$ref_text = restore_user_input($row[0], true, false);

		echo "	replaceRef('" . $i . "', '" . $ref_text . "');";
	}

	echo "</SCRIPT>";
	
	mysql_close($dblink);
}

if (isset($_POST['language'])) { 
	$_SESSION['edit_orig'] = $_SESSION['edit'];
	$_SESSION['edit'] = filter_user_input($_POST['language']);
} 

if (!isset($_SESSION['edit'])) {
	$dblink = @mysql_connect("dbnfs", "gast", "");

	$query = "SELECT edit FROM users WHERE uname='" . $_SESSION['uname'] . "'";
	
	$result = mysql_db_query("skm_localisation", $query, $dblink);
	$data = mysql_fetch_row($result);

	if ($data[0] == "all")
		$_SESSION['edit'] = "3"; 
	else
		$_SESSION['edit'] = $data[0];

	mysql_close($dblink);
}

?>

<DIV align="center" style="max-width: 774px; min-width: 774px;">
	<DIV class="border pad-lr" style="float:left; width: 105px">

		<h3>Reference:</h3>
		<P>
			<TABLE>
<?php

$dblink = @mysql_connect("dbnfs", "gast", "");
$query = "SELECT id, name FROM languages ORDER BY name";

$result = mysql_db_query($db, $query, $dblink);
$rowno = mysql_num_rows($result);

while ($rowno--) {
	$row = mysql_fetch_row($result);

	$db_id = $row[0];
	$db_name = $row[1];

	echo "<TR><TD><FONT>" . $db_name . "</TD>";
	echo "<TD><INPUT type=\"radio\"";

	if ($db_id == $_SESSION['ref']) 
		echo " checked ";

	echo "onclick =\"location.href='edit.php?ref=" . $db_id . "'\">";
	echo "</TD></TR>";
}

mysql_close($dblink);
?>
			</TABLE>
		</P>
	</DIV>

	<DIV class="border pad-lr" style="float:right; width: 520px;">
		<FORM name="edit" method="POST" action="edit.php" onsubmit="convert();">
			<BR>
			<INPUT type="hidden" name="update" value="false">
<?php 

$dblink = @mysql_connect("dbnfs", "gast", "");

$query_maxid = "SELECT MAX(ID) from vars";
$result_maxid = mysql_db_query($db, $query_maxid, $dblink);

$row = mysql_fetch_row($result_maxid);
$maxid = $row[0];

echo "<INPUT type=\"hidden\" name=\"index\" value=\"" . $maxid . "\">";
echo "<TABLE>";

for ($i=1; $i<=$maxid; $i++) {

	$query_ref = "SELECT text FROM entries WHERE var_id=".$i;
	$query_ref .= " AND language_id=" . $_SESSION['ref'];

	$result_ref = mysql_db_query($db, $query_ref, $dblink);
	$row = mysql_fetch_row($result_ref);

	$ref_text = restore_user_input($row[0], false, true);

	if ($ref_text == "") {
		$query_ref = "SELECT var FROM vars WHERE id=". $i;
		$result_ref = mysql_db_query($db, $query_ref, $dblink);
		$row = mysql_fetch_row($result_ref);

		if (!$row)
			continue;

		$ref_text = "No ref. [ $row[0] ]";
	}

	$query_edit = "SELECT text FROM entries WHERE var_id=".$i;
	$query_edit .= " AND language_id=" . $_SESSION['edit'];

	$result_edit = mysql_db_query($db, $query_edit, $dblink);
	$row = mysql_fetch_row($result_edit);

	$edit_text = restore_user_input($row[0], false, true);

	$db_ref = str_replace(array("<", ">"), array("&lt;", "&gt;"), $ref_text);
	$db_edit = $edit_text;

	echo "<tr>";
	echo "	<td valign=top>" . $i . "</td>";
	echo "	<td valign=\"top\" id=\"ref" . $i . "\">$db_ref</td>";
	echo "	<td>";
	echo "	<textarea cols=30 name=\"e" . $i . "\">$db_edit</textarea>";
	echo "	</td>";
	echo "</tr>";
}

echo "</TABLE>";
?>
			<SCRIPT language="javascript">

			// TODO: Save the values of all e#idx textareas

			function convert() {
				// TODO: Check if sth. has been modified
				document.edit.update.value = true;
			}

			</SCRIPT>

			<DIV align="center" id="subbox" class="pad-lr"> 
				Editing language: 
				<P>
<?php
$dblink = @mysql_connect("dbnfs", "gast", "");

$query = "SELECT name FROM languages WHERE id='" . $_SESSION['edit'] . "';";
$result = mysql_db_query($db, $query, $dblink);
$row = mysql_fetch_row($result);

echo $row[0];

mysql_close($dblink);
?>
				</P>
				
				<INPUT type="hidden" id="gen" name="generate" value="1">
				<INPUT type="submit" value="Save Changes">

			</DIV>
		</FORM>
	</DIV>
</DIV>

</BODY>
</HTML>
