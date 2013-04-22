<?php 

include ('materialvariablen.inc');

/* Aufbauen einer MySQL-Datenbanksverbindung */
/****************************************/

$link = mysql_connect($mysql_host, $mysql_user, $mysql_pass)
	or die("Keine Verbindung m&ouml;glich: " . mysql_error());
mysql_select_db($mysql_db) 
	or die("Auswahl der Datenbank fehlgeschlagen");


/* Auslesen der Parameter */
/**********************/

/* Auslesen der Anfrage-URL */
$request = $GLOBALS['_REQUEST'];

/* Material-ID, z.B. mid=123 */
$mid = $request['mid'];

/* Globale Variable mit den Suchbegriffen */
$search = "";

/* Globale Variable mit der Verknuepfungsform */
$search_form = "";

/* Auswerten der Parameter */
/***********************/

/* Üperprüfen, ob der User Redaktions-Rechte besitzt, 
   um Einträge bearbeiten / löschen zu dürfen */

$usergroup = explode(",", $GLOBALS['TSFE']->fe_user->user['usergroup']);
$usergroups = count($usergroup);
$redakteur = false;

for ($i=0; $i<$usergroups; $i++) 
if ($usergroup[$i] == $redaktion_gid) {
	$redakteur = true;
	break;
}

/* Hier wird überprüft, ob ein Kommentar abgegeben wurde 
   und gegebenenfalls in die Datenbank eingetragen. */

if (isset($_POST['comment']) && trim($_POST['comment']) != "") {

	$query = "INSERT INTO comment VALUES('" 
		. $_POST['comment'] . "', '" 
		. $mid . "', '" 
		. date("Y-m-d") . "', '" 
		. $_POST['vorname'] . "', '" 
		. $_POST['name'] . "', '" 
		. $_POST['email'] . "')";

	mysql_wrap_query($query, $result);     
}

?>

<script type="text/javascript">
<!--

function hide(id) {
	var content = document.getElementById(id);
	var head = document.getElementById(id + '_head');
	var table = document.getElementById(id + '_table');

	if (content.className == "content_hidden") {
		table.className = "table_visible";
		head.className = "head_visible";
		content.className = "content_visible";
	} else {
		table.className = "table_hidden";
		head.className = "head_hidden";
		content.className = "content_hidden";
	}
}

function alpha_submit() {
	document.getElementsByName("searchlock")[0].value = "-1";
	document.forms.mat_suche.submit();
}

function locked_submit() {
	document.getElementsByName("searchlock")[0].value = "1";
	document.forms.mat_suche.submit();
}

function del_mat(mid) {
	check = confirm("Wollen Sie diesen Eintrag wirklich loeschen?");
	if (check == true)
		window.location = "<?php echo $upload_url ?>" + "&mid=" + mid + "&del";
}

-->
</script>

<?php

/* Ausgabe des Materialeintrags zur Material-ID */

if (isset($mid)) {

	$query = "SELECT material.*, typo3.fe_users.zone, " .
		"typo3.fe_users.email, typo3.fe_users.name " . 
		"FROM material LEFT JOIN typo3.fe_users " .
		"USING(uid) WHERE mid='" . $mid . "'";

	mysql_wrap_query($query, $result); 
	if (mysql_num_rows($result) == 0)
		return;

	$row = mysql_fetch_object($result);

	if ($redakteur == false && $row->unlocked == 0 
			&& $row->uid != $GLOBALS['TSFE']->fe_user->user['uid'])
		return;

	$allow_comments = $row->comment; 

	echo '<div class="download_titel">';
	if (trim($row->autor) != "")
		echo htmlentities($row->autor) . ": ";

	echo htmlentities($row->titel) . " (eingetragen am ";
	echo date_mysql2german($row->datum) . ")</div>"; 

	echo '<div class="download_bearbeiten">';
	if ($redakteur == true 
			|| ($row->uid == $GLOBALS['TSFE']->fe_user->user['uid'])) {
		echo '<a href="' . $upload_url . '&mid=' . $mid . '">';
		echo '(Eintrag bearbeiten)</a><br>';
	}

	if ($redakteur == true) {
		if ($row->unlocked == 0) {
			echo '<a href="' . $upload_url . '&mid=' . $mid . '&unlock=1">';
			echo '(Eintrag entsperren)</a><br>';
		} else {
			echo '<a href="' . $upload_url . '&mid=' . $mid . '&unlock=0">';
			echo '(Eintrag sperren)</a><br>';
		}
	} 

	if ($redakteur == true 
			|| $row->uid == $GLOBALS['TSFE']->fe_user->user['uid']) {
		echo '<a href=javascript:del_mat("' . $mid . '")>';
		echo '(Eintrag l&ouml;schen)</a></div>';
	}

	echo '</div>';

	if (trim($row->bild) != "") {
		echo '<div class="download_bild"><img src="';
		echo $upload_path . $row->mid . '/' . $row->bild . '">';
		if (trim($row->bildquelle) != "")
			echo '<br>' . $row->bildquelle;
		echo '</div>';
	}

	echo '<table id="wrd_table" class="table_hidden">';
	echo '<tr><td id="wrd_head" class="head_hidden">';
	echo '<a href=javascript:hide("wrd")>';
	echo 'Zugeh&ouml;rige Schlagworte &gt;&gt;</a></td></tr>';
	echo '<tr><td id="wrd" class="content_hidden">';

	echo nl2br(htmlentities($row->teaser));

	echo '</td></tr></table>';

	$query = "SELECT mid_cid.cid FROM mid_cid LEFT JOIN category ".
		"USING(cid) WHERE mid='" . $mid . "' AND pid!='0'";

	mysql_wrap_query($query, $result);  
	$cids = mysql_num_rows($result);

	$bid = array();
	$cid = array();

	for ($i=0; $i<$cids; $i++) {
		$row2 = mysql_fetch_object($result);
		$cid[$i] = $row2->cid;
	} 

	resolve_categories($cid, $bid);

	$bids = count($bid);
	$cids = count($cid);

	echo '<table id="cat_table" class="table_hidden">';
	echo '<tr><td id="cat_head" class="head_hidden">';
	echo '<a href=javascript:hide("cat")>';
	echo 'Zugeordnete Kategorien &gt;&gt;</a></td></tr>';
	echo '<tr><td id="cat" class="content_hidden">';

	for ($i=0; $i<$cids; $i++) 
		echo htmlentities($cid[$i]) . "<br>";

	echo '</td></tr></table>';
	echo '<br>';

	if ($bids > 0) {
		echo '<div class="download_bildungsstandard">';
		echo '<div class="download_caption">';
		echo 'Bezug zu den Bildungsstandards</div>';

		for ($i=0; $i<$bids; $i++) 
			echo htmlentities($bid[$i]) . "<br>";

		echo '</div>'; 
	}

	echo '<div class="download_beschreibung">';
	echo '<fieldset><legend>Beschreibung</legend>';
	echo nl2br(htmlentities($row->beschreibung)) . '</fieldset></div>'; 

	$query = "SELECT datei, info FROM file WHERE mid='" . $mid . "' " .
		"ORDER BY info,datei ASC";

	mysql_wrap_query($query, $result);     
	$results = mysql_num_rows($result);

	echo '<div class="download_dateien">';
	echo '<fieldset><legend>Zugeh&ouml;rige Materialien</legend>';

	for ($i=0; $i<$results; $i++) {
		$row = mysql_fetch_object($result);
		$link = '<a href="';
		$text = "";

		$size = human_filesize($upload_path . $mid . '/' . $row->datei);
		$text = htmlentities(trim(($row->info)));

		if ($size == 0) 
			$link = $link . $row->datei . '" target="_blank">' . str_stop($row->datei, 60);
		else {
			if ($text == "")
				$text = exec("file -bN " . $upload_path . $mid . "/" . $row->datei);

			$text .= ", " . $size; 
			$link = $link . $upload_path . $mid . '/' . $row->datei . '" target="_blank">' .  str_stop($row->datei, 60);
		}

		$link = $link . '</a>';

		if ($i != 0)
			echo '<br>';
		echo $link . '<br>';
		if ($text != "") 
			echo '('. $text . ')<br>';
	}

	echo "</fieldset></div>";
	echo '<br><div align="right"><a href="javascript:print()">';
	echo '<img src="fileadmin/design/images/icon-print.gif"  border="0">';
	echo 'Drucken</a></div>';
/*
	if ($allow_comments == 0)
		return;

	$query = "SELECT * FROM comment WHERE mid='" . $mid . "' ORDER BY datum DESC";
	mysql_wrap_query($query, $result);       
	$results = mysql_num_rows($result);

	echo '<div class="download_kommentare">'; 
	echo '<fieldset><legend>Kommentare</legend>';

	for ($i=0; $i<$results; $i++) {
		if ($i % 2 == 0)
			echo '<div class="download_kommentar1">';
		else
			echo '<div class="download_kommentar2">';   

		$row = mysql_fetch_object($result);
		echo nl2br(htmlentities($row->kommentar)) . "<br><br>(abgegeben ";

		if (trim($row->vorname) != "" || trim($row->name) != "")
			echo 'von <a href="mailto:' . $row->email . '">' . htmlentities($row->vorname) . ' ' . htmlentities($row->name) . '</a> ';
		echo 'am ' . date_mysql2german($row->datum) . ')</div>';
	}

	echo '</fieldset></div>';
	echo '<br><br><div class="upload_remark">Wie bewerten Sie diesen Materialeintrag? War die (Kurz-)Beschreibung aussagekr&auml;ftig genug, befand er sich in der richtigen Kategorie bzw. h&auml;tten Sie eine andere bevorzugt, ... Wir freuen uns &uuml;ber Kommentare aller Art!</div>'; 
	echo '<form name="kommentar" enctype="multipart/form-data" action="' . $download_url . '&mid=' . $mid . '" method="POST">';
*/
	echo '<style type="text/css">.download_remark { display: none; visible: none }</style>';
?>

<!--
<div class="upload_input">Vorname:<br>
<input name="vorname" type="text" size="25" maxlength="64"></div>
<div class="upload_input">Name:<br>
<input name="name" type="text" size="25" maxlength="64"></div>
<div class="upload_input">eMail:<br>
<input name="email" type="text" size="50" maxlength="128"></div>
<div class="upload_textarea">Kommentar (*):
<br><textarea name="comment" cols="50" rows="4"></textarea></div>
<input type="submit" value="Kommentar abgeben">
</form>
-->

<?php
} 

/* Starten des Suchvorgangs und Darstellung der Ergebnisse */

else if (isset($_POST['search_light']) || isset($_POST['search'])) {

	global $search, $search_form;

	if (trim($_POST['search']) != "") {
		$search = $_POST['search'];
		$search_form = $_POST['search_form'];
	} else {
		$search = $_POST['search_light'];
		$search_form = $_POST['search_light_form'];
	}
	
	$search = preg_replace('/\s+/', ' ', trim($search));

	$unlocked = 1;
	if ($redakteur == true && $_POST['searchlock'] == "1")
		$unlocked = 0;

	@mkdir("/tmp/sinus_search");
	if (isset($_POST['search_smart'])) 
		contact_server("SMART", "http://localhost/cgi-bin/smart/search.sh", "");
	if (isset($_POST['search_lehreronline'])) 
		contact_server("Lehrer-Online", "http://www.lehrer-online.de/dyn/516045.asp", "sinus-transfer");
	if (isset($_POST['search_learnline'])) 
		contact_learnline("Learnline-NRW", "http://db.learnline.de/angebote/materialdatenbank/ergebnissebayreuth.jsp");
	if (isset($_POST['search_problem'])) 
		contact_server("Problemloesenlernen.de", "http://www.problemloesenlernen.dvlp.de/sinus-transfer.html", "");

	$search_item = explode(" ", $search);
	$items = count($search_item);

	if (isset($_POST['cid']))
		$cids = count($_POST['cid']);
	else
		$cids = 0;

	$bid = array();
	$cid = $_POST['cid'];
	resolve_categories($cid, $bid);

	echo '<div align="right"><a href="' . $download_url . '">Neue Suche >></a> </div>';
	echo '<fieldset><legend>Durchsuchte Kategorien</legend>';

	for ($i=0; $i<$cids; $i++) 
		echo htmlentities($cid[$i]) . "<br>";

	echo "</fieldset></div>";
	echo "<fieldset><legend>Suchbegriffe</legend>";

	for ($i=0; $i<$items; $i++) {
		if ($i != 0)
			echo " " . $search_form . " ";
		echo $search_item[$i];
	}
	echo "</fieldset><fieldset><legend>Datum</legend>";

	/* ------------------------ Starte Suche ---------------------- */
	/* -------------------------  --------------------------------- */

	$search_start_time = time();

	// Bestimme alle Material-IDs, die im gewähltem Datumsbereich liegen 
	$query = "SELECT mid FROM material " . 
		"WHERE (unlocked='" . $unlocked .
		"' OR (unlocked='0' AND uid='" .
		$GLOBALS['TSFE']->fe_user->user['uid'] . "'))";

	if ($_POST['start_monat'] != 0 && $_POST['start_jahr'] != 0) {
		$query = $query . " AND datum>=";
		$query .= "'" .  $_POST['start_jahr'] . "-" . $_POST['start_monat'] . "-01'";
		echo $_POST['start_monat'] . "." . $_POST['start_jahr'] . " <= ";
	}

	if ($_POST['ende_monat'] != 0 && $_POST['ende_jahr'] != 0) {
		$query = $query . " AND datum<=";
		$query .= "'" .  $_POST['ende_jahr'] . "-" . $_POST['ende_monat'] . "-31'";

		if ($_POST['start_monat'] == 0 || $_POST['start_jahr'] == 0) 
			echo "<= ";

		echo $_POST['ende_monat'] . "." . $_POST['ende_jahr'];
	}

	echo "</fieldset>";
	echo "<br><fieldset><legend>Suchergebnis</legend>";

	mysql_wrap_query($query, $result);    
	$mids =  mysql_num_rows($result);
	$mid = array();

	for ($i=0; $i<$mids; $i++) {
		$row = mysql_fetch_object($result);
		$mid[$i] = $row->mid;
	}

	// Bestimme die PID fuer jede CID:

	$pid = array();
	for ($j=0; $j<$cids; $j++) {
		$query = "SELECT pid FROM category WHERE cid='" . $_POST['cid'][$j] . "'"; 
		mysql_wrap_query($query, $result);
		$k = mysql_num_rows($result);

		if ($k != 1) 
			die("Error: $k pids found for cid: " . $_POST['cid'][$j]);

		$row = mysql_fetch_object($result);
		$pid[$j] = $row->pid;

	}

	// Gruppiere die CIDs, die zur selben PID gehören

	$sorted_pid = $pid;
	sort($sorted_pid);
	$temp = array_unique($sorted_pid);
	$sorted_pid = array_values($temp);
	$sorted_pids = count($sorted_pid);

	$pid_cid = array();
	for ($j=0; $j<$sorted_pids; $j++) 
		$pid_cid[$sorted_pid[$j]] = array();


	for ($k=0; $k<$cids; $k++) {
		$h = count($pid_cid[$pid[$k]]);
		$pid_cid[$pid[$k]][$h] = $_POST['cid'][$k];
	}

	// Die CIDs sind nun edntprechend gruppiert

	// Bestimme die Material-IDs, die in ALLEN kombinierten Teilbäumen liegen
	for ($j=$sorted_pids-1; $j>=0; $j--) {
		if ($mids != 0) {

			// Bestimme die CIDs, die im SELBEN kombinierten Teilbaums liegen
			$len = count($pid_cid[$sorted_pid[$j]]);

			$cid = array();
			for ($h=0; $h<$len; $h++)
				$cid[$h] =  $pid_cid[$sorted_pid[$j]][$h];

			$i = $h-1;
			$h = 0;

			while (1) {
				$query = "SELECT cid FROM category WHERE pid='" . $cid[$h];
				$query = $query . "' OR pid='-" . $cid[$h] . "'"; 

				mysql_wrap_query($query, $result);
				$k = mysql_num_rows($result);
				if ($k) {
					while ($k) {
						$row = mysql_fetch_object($result);
						$i++;
						$cid[$i] = $row->cid;
						$k--;
					}
				}

				$h++; 

				if ($h > $i)
					break;
			}

			// Bestimme die MIDs, die einer Kategorie zugeordnet sind, 
			// die sich innerhalb der kombinierten Teilbäume befindet

			$k = $i;   

			$query = "SELECT mid FROM mid_cid WHERE (";
			for ($i=0; $i<=$k; $i++) {
				if ($i != 0)
					$query = $query . " OR ";
				$query = $query . "cid='" . $cid[$i] . "'";
			}
			$query = $query . ") AND (";

			for ($i=0; $i<$mids; $i++) {
				if ($i != 0)
					$query = $query . " OR ";
				$query = $query . "mid='" . $mid[$i] . "'";
			}

			$query = $query . ")";

			mysql_wrap_query($query, $result);
			$mids = mysql_num_rows($result);
			$mid = array();

			for ($i=0; $i<$mids; $i++) {
				$row = mysql_fetch_object($result);
				$mid[$i] = $row->mid;
			}
		}
	}

	$hits = 0;

	if ($mids != 0 && $items != 0) {
		$query = "SELECT DISTINCT " .
			"mat.mid, mat.autor, mat.titel, mat.beschreibung " . 
			"FROM material AS mat LEFT JOIN mid_cid USING(mid) " . 
//			"LEFT JOIN typo3.fe_users AS feu ON mat.uid=feu.uid " . 
//			"LEFT JOIN typo3.static_country_zones AS coz ON feu.zone=coz.zn_code " . 
			"LEFT JOIN file ON mat.mid=file.mid WHERE MATCH(mat.autor, mat.titel, mat.teaser, mat.beschreibung, mat.bild) ";

		$query = $query . "AGAINST('";

		if ($search_form == "AND")
			$search_link = "+";
		else
		        $search_link = "";

		for ($i=0; $i<$items; $i++) {
			if ($i != 0)
				$query = $query . " ";
			$query = $query . $search_link . $search_item[$i];
		}

		$query = $query . "' IN BOOLEAN MODE) GROUP BY mat.mid";

		if ($_POST['searchlock'] == "-1")
			$query .= " ORDER BY mat.titel ASC, mat.datum DESC";
		else
			$query .= " ORDER BY mat.datum DESC, mat.mid ASC";

//		echo "MySQL query: " . $query . "<br>";
		mysql_wrap_query($query, $result);    
		$rows = mysql_num_rows($result);

		$hits = 0;
		for ($i=0; $i<$rows; $i++) {
			$row = mysql_fetch_object($result);
			for ($j=0; $j<$mids; $j++) 
				if ($mid[$j] == $row->mid)
					break;
			if ($j >= $mids)
				continue;

			list_eintrag($row, $download_url);
			$hits++;
		} 

		if ($hits == 0) {
			$query = "SELECT DISTINCT " .
			  	 "mat.mid, mat.autor, mat.titel, mat.beschreibung " . 
 				 "FROM material AS mat LEFT JOIN mid_cid USING(mid) " . 
				 "LEFT JOIN file ON mat.mid=file.mid WHERE (";

			for ($i=0; $i<$mids; $i++) {
				if ($i != 0)
					$query = $query . " OR ";
				$query = $query . "mat.mid='" . $mid[$i] . "'";
			}

			$query = $query . ") AND (";

			for ($i=0; $i<$items; $i++) {
				if ($i != 0)
					$query = $query . " " . $search_form . " ";
				$query = $query . "CONCAT_WS(\" \", mat.autor, mat.titel, mat.teaser, mat.beschreibung, mat.bild, file.datei) LIKE '%" . $search_item[$i] . "%'";
			}

			$query = $query . ") GROUP BY mat.mid";

			if ($_POST['searchlock'] == "-1")
				$query .= " ORDER BY mat.titel ASC, mat.datum DESC";
			else
				$query .= " ORDER BY mat.datum DESC, mat.mid ASC";

//			echo "MySQL query: " . $query . "<br>";
			mysql_wrap_query($query, $result);    
			$hits = mysql_num_rows($result);

			for ($i=0; $i<$hits; $i++) {
				$row = mysql_fetch_object($result);
				list_eintrag($row, $download_url);
			} 

		}

	} 
		
	$search_end_time = time();

	echo "</fieldset>";
//	echo "&nbsp;&nbsp;$hits Treffer in " . ($search_end_time - $search_start_time) . " sec(s)<br>";
	
	/* ------------------------ Beende Suche ---------------------- */
	/* ------------------------------------------------------------ */

	if ($unlocked) {
		for ($i=0; $i<60; $i++) {
			$out = exec('COLUMNS=500 /bin/ps -e -f | /bin/grep curl | /bin/grep "' . $_SERVER['REMOTE_ADDR'] . '_' . $_SERVER['REMOTE_PORT'] . '" | /bin/grep -v grep');
			if (trim($out) == "")
				break;
			sleep(1); 
		}

		if (isset($_POST['search_smart'])) 
			print_result("SMART");
		if (isset($_POST['search_lehreronline'])) 
			print_result("Lehrer-Online");
		if (isset($_POST['search_learnline'])) 
			print_result("Learnline-NRW");
		if (isset($_POST['search_problem'])) 
			print_result("Problemloesenlernen.de");
	}

	echo '<br><div align="right"><a href="' . $download_url . '#top">Nach oben  >></a></div>';

	echo '<style type="text/css">.download_remark { display: none; visible: none }</style>';
} 

/* Ausgabe des Suchformulars */

else {
	echo '<form name="mat_suche" enctype="multipart/form-data" action="' . $download_url . '" method="POST">';

?>
	<div>
	<table>
	<tr><td colspan="3" align="left"><h3>Schlagwortsuche</h3></td></tr>
	<tr><td align="right"><nobr>Schlagworte </td>
	<td align="left"><input name="search_light" type="text" size="32" maxlength="64"></nobr></td>
	<td align="right"><nobr><input type="radio" name="search_light_form" value="AND" checked="checked">UND<input type="radio" name="search_light_form" value="OR">ODER</nobr></td>
	<tr><td align="right" rowspan="4">Kooperierende Materialserver <a href="javascript:alert('Bitte beachten Sie folgende Punkte bei einer Integration\nder kooperierenden Server:\n\n- Es kann zu Zeitverz&ouml;gerungen (maximal 60 Sekunden) kommen.\n- Es ist nur eine (UND / ODER) Schlagwortsuche m&ouml;glich.\n- Eingegebene Kategorien und Datumsangaben werden bei der\n   externen Suche nicht ber&uuml;cksichtigt.')">(Hinweis!)</a></td><td align="left"><nobr><input type="checkbox" name="search_smart">SMART</nobr></td><td></td></tr>
	<tr><td align="left"><nobr><input type="checkbox" name="search_lehreronline">Lehrer-Online</nobr></td><td></td></tr>
	<tr><td align="left"><nobr><input type="checkbox" name="search_learnline">Learnline-NRW</nobr></td><td></td></tr>
	<tr><td align="left"><nobr><input type="checkbox" name="search_problem">Problemloesenlernen.de</nobr></td><td align="right"><input type="submit" value="Suche starten"></td></tr>
	<tr><td colspan="3">&nbsp;</td></tr>
	<tr><td colspan="3">&nbsp;</td></tr>
	<tr><td colspan="3" align="left"><h3>Erweiterte Suche</h3></td></tr>
	<tr><td align="right"><nobr>Schlagworte </td>
	<td align="left"><input name="search" type="text" size="32" maxlength="64"></nobr></td>
	<td align="right"><nobr><input type="radio" name="search_form" value="AND" checked="checked">UND<input type="radio" name="search_form" value="OR">ODER</nobr></td>
	<tr><td align="right">Von </td>
	<td align="left"><select name="start_monat">
	<option value="0">Monat</option>
	<option value="1">Januar</option>
	<option value="2">Februar</option>
	<option value="3">M&auml;rz</option>
	<option value="4">April</option>
	<option value="5">Mai</option>
	<option value="6">Juni</option>
	<option value="7">Juli</option>
	<option value="8">August</option>
	<option value="9">September</option>
	<option value="10">Oktober</option>
	<option value="11">November</option>
	<option value="12">Dezember</option>
	</select>
	<select name="start_jahr">
	<option value="0">Jahr</option>
	<option value="2004">2004</option>
	<option value="2005">2005</option>
	<option value="2006">2006</option>
	<option value="2007">2007</option>
	</select></td>
	<td>&nbsp;</td></tr>
	<tr><td align="right">Bis </td>
	<td align="left"><select name="ende_monat">
	<option value="0">Monat</option>
	<option value="1">Januar</option>
	<option value="2">Februar</option>
	<option value="3">M&auml;rz</option>
	<option value="4">April</option>
	<option value="5">Mai</option>
	<option value="6">Juni</option>
	<option value="7">Juli</option>
	<option value="8">August</option>
	<option value="9">September</option>
	<option value="10">Oktober</option>
	<option value="11">November</option>
	<option value="12">Dezember</option>
	</select>
	<select name="ende_jahr">
	<option value="0">Jahr</option>
	<option value="2004">2004</option>
	<option value="2005">2005</option>
	<option value="2006">2006</option>
	<option value="2007">2007</option>
	</select></td>
	<td align="right"><input type="submit" value="Suche starten"></td></tr>
	</div>

<?php

echo '<tr><td colspan="2" align="center" width="465">';

$i = 0;

$result = array();
$results = array();

$query = "SELECT category.cid, category.titel, COUNT(*) AS count 
	FROM category LEFT JOIN mid_cid USING(cid) 
	WHERE pid='0' AND mid_cid.cid!='NULL'
	GROUP BY category.titel ORDER BY count DESC";

mysql_wrap_query($query, $result[0]);
$results[0] = mysql_num_rows($result[0]);

while ($i >= 0) {
	while ($results[$i] > 0) {
		$row = mysql_fetch_object($result[$i]);

		$query = "SELECT category.*, COUNT(*) AS count 
			FROM category LEFT JOIN mid_cid USING(cid) 
			WHERE pid=" . $row->cid . " OR pid=-" . $row->cid . "
			GROUP BY category.titel ORDER BY titel+0,titel ASC";

		mysql_wrap_query($query, $result[$i+1]);

		$results[$i+1] = mysql_num_rows($result[$i+1]);
		$results[$i]--;

		if ($results[$i+1] > 0) {
			echo '<table id="' . $row->cid . '_table" class="table_hidden">';

			if ($row->pid >= 0) {
				echo '<tr><td id="' . $row->cid . '_head" class="head_hidden">';
				if ($i != 0)
					echo '<input type="checkbox" name="cid[]" 
						value="' . $row->cid . '">';
				echo '<a href=javascript:hide("' . $row->cid . '")>';
				echo htmlentities($row->titel);

				if ($redakteur)
					echo ' (' .  $row->count . ')';

				echo '</a>';
				echo '</td></tr>';
			}

			echo '<tr>';

			if ($row->pid >= 0) 
				echo '<td id="' . $row->cid . '" class="content_hidden">';
			else 
				echo '<td id="' . $row->cid . '" class="content_visible">';

			$i++;

		} else {

			if ($row->pid >= 0) {
				echo '<nobr>';
				echo '<input type="checkbox" name="cid[]" value="' . $row->cid . '">' . htmlentities($row->titel);

				if ($redakteur)
					echo ' (' . $row->count . ')';
				echo '</nobr>';
				echo '<br>';
			}
		}
	}

	$i--;

	if ($i >= 0)
		echo '</td></tr></table>';
}

echo '</td><td valign="bottom" align="left"><input type="submit" value="Suche starten"></td></tr>';
echo '</form>';

?>

<tr><td colspan="3">&nbsp;</td></tr>
<tr><td colspan="3">&nbsp;</td></tr>
<tr><td colspan="3" align="left"><h3>Volltextsuche</h3></td></tr>
<FORM method=GET action="http://www.google.de/search" target="_blank">
<tr><td align="right"><nobr><A HREF="http://www.google.de">
<IMG SRC="http://www.google.de/logos/Logo_25wht.gif" border="0" 
ALT="Google" align="absmiddle"></A></td><td><INPUT TYPE="text" name="q" size="32" maxlength="64" value=""></nobr></td>
<INPUT TYPE="hidden" name="hl" value="de">
<INPUT TYPE="hidden" name="q" value="inurl:MaterialienDB">
<INPUT TYPE="hidden" name="ie" value="ISO-8859-1">
<INPUT TYPE="hidden" name="oe" value="ISO-8859-1">
<INPUT TYPE="hidden" name="domains" value="sinus-transfer.uni-bayreuth.de">
<INPUT TYPE="hidden" name="sitesearch" value="sinus-transfer.uni-bayreuth.de">
<td><INPUT TYPE="submit" name="btnG" VALUE="Suche starten"></td></tr>
</FORM>

<?php

echo '</table></div>';
echo '<input type="hidden" name="searchlock" value="0">';

if ($redakteur == true) {
	echo '<div align="center"><br><hr><br><input type="button" value= "Eintr&auml;ge alphabet. sortiert anzeigen" onclick="alpha_submit()"></div>';
	echo '<div align="center"><br><hr><br><input type="button" value="Gesperrte Eintr&auml;ge anzeigen" onclick="locked_submit()"></div>';
}

?>

</form>

<?php
}

/* Funktion um einen Materialeintrag aufzulisten */
function list_eintrag($row, $url) {
	echo '<div class="download_matlink">';
	echo '<a href="javascript:void(window.open(\'' . $url 
		. '&mid=' . $row->mid 
		. '\', \'material\', \'width=650, height=700, scrollbars=yes\'))">[' 
		. htmlentities($row->titel);

	if ($row->autor != "")
		echo ' (' . htmlentities(str_stop($row->autor, 30)) . ')';
	
	echo ']</a> ' . htmlentities(str_stop($row->beschreibung, 200));
	echo '</div>';
}

/* SQL-Query Wrapper Funktion */
function mysql_wrap_query(&$query, &$result) {
	if (is_resource($result)) 
		mysql_free_result($result); 

	$result = mysql_query($query) 
		or die("Anfrage fehlgeschlagen: " . mysql_error());
}


/* Funktion zum Umwandeln des MySQL-Datumsformats
   in das deutsche Datumsformat */
function date_mysql2german($datum) {
	list($jahr, $monat, $tag) = explode("-", $datum);
	return sprintf("%02d.%02d.%04d", $tag, $monat, $jahr);
}


/* Funktion zur Bestimmung von Dateigrössen */
function human_filesize($file)
{
	$size = filesize($file);
	$filesizename = array(" Bytes", " KB", " MB", " GB", " TB", " PB", " EB", " ZB", " YB");
	return round($size/pow(1024, ($i = floor(log($size, 1024)))), 2) . $filesizename[$i];
}


/* Funktion zum Kürzen eines Strings */
function str_stop($string, $max_length)
{
	if (strlen($string) > $max_length) {
		$string = substr($string, 0, $max_length);
		$pos = strrpos($string, " ");
		if ($pos === false) {
			return substr($string, 0, $max_length) . " ...";
		}

		return substr($string, 0, $pos) . " ...";
	} else 
		return $string;
}


/* Funktion zur Namensauflösung eines Kategorienpfads, 
   der in Form von Kategorien-IDs übergeben wird */
function resolve_categories(&$cid, &$bid)
{
	$cids = count($cid);
	if ($cids == 0)
		return;

	$query = "CREATE TEMPORARY TABLE c1 AS SELECT * FROM category WHERE ";

	for ($i=0; $i<$cids; $i++) {
		if ($i != 0) 
			$query = $query . " OR ";
		$query = $query . "cid='" . $cid[$i] . "'";
	}

	mysql_wrap_query($query, $result);  

	$query = "CREATE TEMPORARY TABLE c2 AS SELECT * FROM c1";
	mysql_wrap_query($query, $result);  

	$query = "SELECT c1.* FROM c1 LEFT JOIN c2 ON c1.cid=c2.pid 
		OR c1.cid=-c2.pid WHERE c2.pid IS NULL";

	mysql_wrap_query($query, $result);      
	$results = mysql_num_rows($result);

	$j = 0;
	$k = 0;

	$cid = array();
	$bid = array();

	for ($i=0; $i<$results; $i++) {
		$row = mysql_fetch_object($result);
		$row2 = $row;

		$category = " / " . $row->titel;
		$bildung = $category;

		while ($row2->pid != 0) {
			$query = "SELECT pid, titel FROM category WHERE cid=" . $row2->pid 
				. " OR cid=-" . $row2->pid;
			mysql_wrap_query($query, $result2);     
			$row2 = mysql_fetch_object($result2);

			if ($row2->pid >= 0)   
				$category = " / " . $row2->titel . $category;

			$bildung = " / " . $row2->titel . $bildung;
		}

		if ($bildung != $category) {
			$bid[$k] = str_replace("/ Fach / ", "", $bildung);
			$k++;
		} 
		if ($row->pid >= 0) {
			$cid[$j] = $category;
			$j++;
		}
	}

	sort($cid);
	sort($bid);
}


/* Funktion zur Durchführung einer Suche 
   auf kooperierenden Materialservern */
function contact_server($server_name, $server_url, $vorgabe, $search_tag = "STRING") 
{ 
	global $search, $search_form;

	if ($search_form == "OR" && $vorgabe != "") {
		$string = explode(" ", trim($search));

		for ($i=0; $i<count($string); $i++) {
			if ($string[$i] != "") 
				$string[$i] = strtr($vorgabe . " " . $string[$i], " ", "+");
			else 
				$string[$i] = strtr($vorgabe, " ", "+");

			$cmd = '(/usr/bin/curl -m 60 -f -A "" -e http://sinus-transfer.uni-bayreuth.de/materialien/materialdatenbank.html -d ' . $search_tag . '=' . $string[$i] . ' -d METHOD=AND ' . $server_url . ' -o /tmp/sinus_search/' . $server_name . '_' . $_SERVER['REMOTE_ADDR'] . '_' . $_SERVER['REMOTE_PORT'] . '_' . $i . ')';

			system($cmd . ' > /dev/null &'); 
		}
	} else {
	
		if ($search != "") 
			$string = strtr($vorgabe . " " . $search, " ", "+");
		else 
			$string = strtr($vorgabe, " ", "+");

		$cmd = '(/usr/bin/curl -m 60 -f -A "" -e http://sinus-transfer.uni-bayreuth.de/materialien/materialdatenbank.html -d ' . $search_tag . '=' . $string . ' -d METHOD=' . $search_form . ' ' . $server_url . ' -o /tmp/sinus_search/' . $server_name . '_' . $_SERVER['REMOTE_ADDR'] . '_' . $_SERVER['REMOTE_PORT'] . '_0)';

		system($cmd . ' > /dev/null &');
	}
}


/* Funktion zur Durchführung einer Suche auf LearnLine */
function contact_learnline($server_name, $server_url) 
{
	global $search, $search_form;
	
	$search_tag = "where=stichworte%20LIKE%20%27%25SINUS%20Projekt%25%27";
	$param_begin = "CONCAT_WS%28%22%20%22%2C%20titel%2C%20kurzbeschreibung%2C%20beschreibung%2C%20stichworte%29%20LIKE%20%27%25";
	$param_end = "%25%27";

	$string = explode(" ", trim($search));
	if ($string[0] != "") {
		for ($i=0; $i<count($string); $i++) {
			if ($i == 0)
				$search_tag = $search_tag . "%20AND%20%28";
			else
				$search_tag = $search_tag . "%20" . $search_form . "%20";

			$search_tag = $search_tag . $param_begin . $string[$i] . $param_end;
		}

		$search_tag = $search_tag . "%29";
	}

	$cmd = '(/usr/bin/curl -m 60 -f -A "" -e http://sinus-transfer.uni-bayreuth.de/materialien/materialdatenbank.html -d ' . $search_tag . ' ' . $server_url . ' -o /tmp/sinus_search/' . $server_name . '_' . $_SERVER['REMOTE_ADDR'] . '_' . $_SERVER['REMOTE_PORT'] . '_0)';
	
	system($cmd . ' > /dev/null &'); 
}


/* Funktion zur Darstellung der Suchergebnisse von
   kooperierenden Materialservern */
function print_result($server_name) 
{ 
	echo '<br><fieldset>';
	echo '<legend>Suchergebnis von ' . $server_name . '</legend>';

	$url_cache = array();     

	$i = 0;
	while (file_exists($file = '/tmp/sinus_search/' . $server_name . '_' . $_SERVER['REMOTE_ADDR'] . '_' . $_SERVER['REMOTE_PORT'] . '_' . $i)) {

		$handle = fopen($file, 'r');    
		while (!feof($handle)) {

			$zeile = fgets($handle);
			list($titel, $teaser, $url) = explode("|", $zeile);
			if (trim($url) == "" || ($i > 0 && in_array($url, $url_cache)))
				continue;

			array_push($url_cache, $url); 

			echo '<div class="download_matlink">';
			echo '<a href="' . $url . '" target="_blank">[' . htmlentities($titel);
			echo ' (' . $server_name . ')';
			echo ']</a> ' . htmlentities(str_stop($teaser, 200));
			echo '</div>';
		}
	
		fclose($handle);
		@unlink($file); 
		$i++;
	}
	
	echo '</fieldset>';
}

?>
