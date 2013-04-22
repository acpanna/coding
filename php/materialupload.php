<script type="text/javascript">
<!--
function new_cat(node) {
	node.value = prompt("Welche Art von Auswahl-/Eigenschaftskategorien vermissen Sie?", node.value);
}

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

function del_foto(node) {
	var user_id = document.getElementsByName("user_id");
	var copy = user_id[0].cloneNode(true);
	copy.name = "del_foto";
	copy.value = node.value;

	node.value = "";
	node.removeAttribute("disabled");
	node.type = "file";
	node.name = "foto";

	node.parentNode.removeChild(node.nextSibling);
	user_id[0].parentNode.insertBefore(copy, user_id[0]);
}

function add_datei() {
	var datei = document.getElementsByName("datei[]");
	var br = datei[0].parentNode.previousNode;
	var ref = datei[0].parentNode;
	var copy = ref.cloneNode(true);
	var div = datei[0].parentNode.parentNode;

	for (i=0; i<copy.childNodes.length-1; i++)
		copy.childNodes[i].value="";

	div.insertBefore(copy, ref);
	div.insertBefore(br, copy);
}

function del_datei(node) {
	var user_id = document.getElementsByName("user_id");
	var copy = user_id[0].cloneNode(true);
	var div = node.parentNode.parentNode;
	var ref = node.parentNode;

	copy.name = "del_datei[]";
	copy.value = node.value;

	div.removeChild(ref.previousSibling);
	div.removeChild(ref);
	user_id[0].parentNode.insertBefore(copy, user_id[0]);
}

function file_info(node) {
	node.value = prompt("Bitte geben Sie eine kurze Dateibeschreibung: ", node.value);
}

function trim(str)
{
	return str.replace(/^\s*|\s*$/g,"");
}

function check_sex() {
	var i, j, element, elements;
	elements = document.getElementsByTagName("input").length;

	for (i=0; i<elements; i++) {
		element = document.getElementsByTagName("input")[i];

		if (element.checked == true && element.value == 98) {
			for (j=0; j<elements; j++) {
				element = document.getElementsByTagName("input")[j];

				if (element.checked == true && element.value >= 1 
						&& element.value <= 11)
					break;
			}

			if (j < elements) {
				for (j=0; j<elements; j++) {
					element = document.getElementsByTagName("input")[j];

					if (element.checked == true && element.value >= 141 
							&& element.value <= 171)
						return true;
				}
			} 

			return false;
		}
	}

	return true;
}

function check_input() {
	var rep;
	var text = "\n";
	var file_attached = false;

	var uploaded_datei = document.getElementsByName("uploaded_datei[]");
	var datei = document.getElementsByName("datei[]");
	var link = document.getElementsByName("link[]");

	if (trim(document.getElementsByName("pass")[0].value) == "") 
		text = text + "\nPasswort";
	if (trim(document.getElementsByName("name")[0].value) == "") 
		text = text + "\nVollständiger Name";
	if (trim(document.getElementsByName("motto")[0].value) == "") 
		text = text + "\nLebensphilosphie / Motto";
	if (trim(document.getElementsByName("teaser")[0].value) == "") 
		text = text + "\nKurzbeschreibung";

	for (i=0; i<datei.length; i++) 
		if (trim(datei[i].value ) != "") {
			link[i].value = datei[i].value;
			file_attached = true;
		}

	if (file_attached == false && uploaded_datei.length == 0)
		text = text + "\nDateien";
	/*
		if (!check_sex()) {
		alert("Wenigstens Ihr Geschlecht müssen Sie preisgeben!");
		return false;
		}
	 */
	if (text != "\n") {
		alert("Bitte vervollständigen Sie folgende Felder:" + text);
		return false;
	}

	for (i=0; i<uploaded_datei.length; i++)
		uploaded_datei[i].removeAttribute("disabled");

	if (document.getElementsByName("uploaded_foto")[0])  document.getElementsByName("uploaded_foto")[0].removeAttribute("disabled");

	return true;
}   
-->
</script>





<?php 




/* Funktion zum rekursiven Löschen */
function rmdirr($dirname)
{
	if (!file_exists($dirname)) {
		return false;
	}

	if (is_file($dirname)) {
		return unlink($dirname);
	}

	$dir = dir($dirname);
	while (($entry = $dir->read()) !== false) {
		if ($entry == '.' || $entry == '..') 
			continue;
		rmdirr("$dirname/$entry");
	}

	$dir->close();
	return rmdir($dirname);
}


if ($id == "new_cat") {

	if (trim($_POST['new_cat']) != "") {
		mail($upload_email, "Kategorie-Vorschlag", "Der Benutzer " . 
				$_SESSION['login'] . " (Realname: " . 
				$_SESSION['name'] . " , user_id: " .                                                       
				$_SESSION['user_id'] . ", email: " .
				$_SESSION['email'] .
				") schlägt folgende neue Kategorie(n) vor: " . $_POST['new_cat'], 
				"Content-type: text/plain; " . 
				"charset=iso-8859-15\r\nContent-Transfer-Encoding: 8bit\r\n");
	}
}


if ($id == "profil") {

	// (begin) view profile code







	// (end) view profile code
	
	/* (Un)Lock eines Benutzer-Profils */

	if (isset($_GET['unlock'])) {
	
		if ($_SESSION['admin'] == true)
			$user_id = $_GET['user_id'];
		$user_id = $_SESSION['user_id'];

		$query = "UPDATE user SET unlocked='" . $_GET['unlock'] . "' " .
			"WHERE user_id='" . $user_id . "'";

		mysql_wrap_query($query, $result);

		echo '<div class="upload_ok">Das Profil wurde ';
		if ($_GET['unlock'] == 1)
			echo 'entsperrt!';
		else
			echo 'gesperrt!';
		echo '</div>';
		exit; 
	}

	/* Löschen eines Benutzer-Profils */

	if (isset($_GET['del'])) {
		$query = "DELETE FROM comment WHERE user_id='" . $user_id . "'";
		mysql_wrap_query($query, $result);
		$query = "DELETE FROM file WHERE user_id='" . $user_id . "'";
		mysql_wrap_query($query, $result);
		$query = "DELETE FROM user WHERE user_id='" . $user_id . "'";
		mysql_wrap_query($query, $result);
		$query = "DELETE FROM user_cat WHERE user_id='" . $user_id . "'";
		mysql_wrap_query($query, $result);
		rmdirr($upload_path . $user_id);

		echo '<div class="upload_ok">';
		echo 'Das Profil wurde gel&ouml;scht!</div>';
		exit;


	}

	/* Registrieren bzw. Bearbeiten eines Profils */

	if (isset($_GET['regedit'])) {
?>
			<div class="upload_remark">Hier k&ouml;nnen Sie Ihr Profil &auml;ndern/erstellen und anschliessend auf den Server hochladen. Um anderen Mitgliedern das Flirten zu erleichtern, bitten wir Sie dieses Formular m&ouml;glichst "ehrlich" auszuf&uuml;llen.
			Mit einem Stern (*) gekennzeichnete Eingabefelder sind Pflichtangaben. Bitte verwenden Sie keinen HTML-Code und achten Sie darauf, dass Dateinamen <b>keine Umlaute, Leer- oder Sonderzeichen</b> enthalten!</div>

			<?php

			if (isset($_GET['user_id'])) {
				$query = "SELECT login, pass, name, foto, foto_url, motto, teaser 
					FROM user WHERE user_id='" . $_GET['user_id'] . "'";

				mysql_wrap_query($query, $result);
				$row = mysql_fetch_object($result);

				$query = "SELECT cat_id FROM user_cat WHERE user_id='" . $_GET['user_id'] . "'";
				mysql_wrap_query($query, $result);
				$results = mysql_num_rows($result);
				$cat_id = array();

				for ($i=0; $i<$results; $i++) {
					$row2 = mysql_fetch_object($result);
					$cat_id[$i] = $row2->cat_id;
				} 
			}

		echo '<form name="upload" enctype="multipart/form-data" action="profil_save" method="POST" onsubmit="return check_input()">';

		echo '<div class="upload_image">Foto:';
		echo '<br>';

		if ($row->foto != "") {
			echo '<input name="uploaded_foto" type="text" size="25" value="' .
				$row->foto . '" disabled="disabled">';
			echo '<input type="button" value="L&ouml;schen" 
				onClick="del_foto(this.previousSibling)">';
			echo '<input name="foto_url" type="hidden" size="25" value="' . $row->foto_url . '">';
		} else {
			echo '<input name="foto" type="file" size="25">';
			echo '<input name="foto_url" type="hidden" size="25">';
		}
		echo '<input name="foto_copyright" type="button" value="Quelle" onClick="file_info(this.previousSibling)">';
		echo '</div>';

		echo '<div class="upload_textarea">Login:<br>';
		echo '<textarea name="login" cols="50" rows="1">';
		echo $row->login . '</textarea></div>';

		// 
		// cats: PLZ, Geb.datum Sternzeichen, Hobbies, Augen, Haarfarbe, Geburtsland (Wurzeln)
		//

		/*

			echo '<div class="upload_textarea">Herkunftsland des Benutzers:<br><select name="herkunft"><option name=""></option>';

			$query = "SELECT zn_code, zn_name_local FROM typo3.static_country_zones WHERE zn_country_iso_2='DE' ORDER BY zn_name_local";
			mysql_wrap_query($query, $result);

			while ($row2 = mysql_fetch_object($result)) {
			echo '<option name="' . $row2->zn_code . '"';
			if ($row2->zn_code == $row->herkunft)
			echo ' selected="selected"';
			echo '>' . $row2->zn_name_local . '</option>';
			}

			echo '</select></div>';
		 */

		echo '<div class="upload_textarea">Passwort: <br>';
		echo '<textarea name="pass" cols="50" rows="1" >' . $row->pass;
		echo '</textarea></div>';
		echo '<div class="upload_textarea">Vollständiger Name: <br>';
		echo '<textarea name="name" cols="50" rows="1" >' . $row->name;
		echo '</textarea></div>';
		echo '<div class="upload_textarea">Lebensphilosophie / Motto (*):<br>';
		echo '<textarea name="motto" cols="50" rows="4">' . $row->motto;
		echo '</textarea></div>';
		echo '<div class="upload_textarea">Wie würden Sie sich beschreiben:<br>';
		echo '<textarea name="teaser" cols="50" rows="8">';
		echo $row->teaser . '</textarea></div>';
		echo '<div class="upload_categories">Charakter / Eigenschaften: ';
		echo '<table><tr><td>';

		$i = 0;

		$result = array();
		$results = array();

		$query = "SELECT * FROM cat WHERE papa_id='0' ORDER BY name+0,name";
		mysql_wrap_query($query, $result[0]);
		$results[0] = mysql_num_rows($result[0]);

		while ($i >= 0) {
			while ($results[$i] > 0) {
				$row = mysql_fetch_object($result[$i]);

				$query = "SELECT * FROM cat WHERE papa_id='" . $row->cat_id 
					. "' OR papa_id=-'" . $row->cat_id . "' ORDER BY name+0,name";

				mysql_wrap_query($query, $result[$i+1]);

				$results[$i+1] = mysql_num_rows($result[$i+1]);
				$results[$i]--;

				if (is_array($cat_id) && in_array ($row->cat_id, $cat_id))
					$checked = ' checked="checked"';
				else
					$checked = '';

				if ($results[$i+1] > 0) {
					echo '<table id="' . $row->cat_id . '_table" class="table_hidden">';
					echo '<tr><td id="' . $row->cat_id . '_head" class="head_hidden">';
					echo '<nobr>';	    		

					if ($i != 0 && $row->papa_id > 0)
						echo '<input type="checkbox" name="cat_id[]" value="' . 
							$row->cat_id . '"' . $checked . '>';

					echo '<a href=javascript:hide("' . $row->cat_id . '")>' .
						htmlentities($row->name) . ' &gt;&gt;</a>';
					echo '</nobr>';
					echo '</td></tr>';
					echo '<tr><td id="' . $row->cat_id . '" class="content_hidden">';

					$i++;
				} else {
					echo '<nobr>';
					echo '<input type="checkbox" name="cat_id[]" value="' . 
						$row->cat_id . '"' . $checked . '>' . htmlentities($row->name);
					echo '</nobr>';
					echo '<br>';
				}
			}

			$i--;
			if ($i >= 0)
				echo '</td></tr></table>';
		}

		echo '</td></tr></table>';
		echo '<br><input name="new_cat" type="hidden" size="45">';
		echo '<input type="button" value="Neue Kategorie vorschlagen"   
			onClick="new_cat(this.previousSibling)"></div><br>';
		echo '<div class="upload_files">';
		echo 'Dateien (*): ';
		echo '<nobr><a href="javascript:add_datei()">';
		echo 'Eine weitere Datei hinzuf&uuml;gen &gt;&gt;</a></nobr>';

		if (isset($_GET['user_id'])) {
			$query = "SELECT datei, info FROM file WHERE user_id='" . $_GET['user_id'] . "'";

			mysql_wrap_query($query, $result);
			$results = mysql_num_rows($result);

			for ($i=0; $i<$results; $i++) {
				$row = mysql_fetch_object($result);
				echo '<br>';
				echo '<nobr>';
				echo '<input name="uploaded_datei[]" type="text" size="25" 
					value="' . $row->datei . '" disabled="disabled">';
				echo '<input name="uploaded_info[]" type="hidden" size="25" 
					value="' . $row->info . '">';
				echo '<input type="button" value="L&ouml;schen" 
					onClick="del_datei(this.previousSibling.previousSibling)">';
				echo '<input name="uploaded_add[]" type="button"  
					value="Dateibeschreibung"            
					onClick="file_info(this.previousSibling.previousSibling)">';
				echo '</nobr>';
			}
		}

		echo '<br>';
		echo '<nobr>';
		echo '<input name="datei[]" type="file" size="25">';
		echo '<input name="link[]" type="hidden" size="25">';
		echo '<input name="info[]" type="hidden" size="25">';
		echo '<input name="add[]" type="button" value="Dateibeschreibung"            
			onClick="file_info(this.previousSibling)">';
		echo '</nobr>';
		echo '</div>';

		$first_check = ' checked="checked"';
		$sec_check = '';

		if (isset($_GET['user_id'])) {
			$query = "SELECT comment FROM user " . 
				"WHERE user_id='" . $_GET['user_id'] . "'";
			mysql_wrap_query($query, $result);
			$row = mysql_fetch_object($result);

			if ($row->comment == 0) {
				$sec_check = $first_check;
				$first_check = '';
			}
		}


		echo 'Kommentare zulassen: ja<input name="comment" type="radio" value="1"' . $first_check . '> nein<input name="comment" type="radio" value="0"' . $sec_check . '>';
		echo '<input name="comment" type="hidden" value="0">';


		echo '<br><br>';
		echo '<input name="user_id" type="hidden" value="' . $_GET['user_id'] . '">';
		echo '<input type="reset" value="Formular l&ouml;schen">';
		echo '<input type="submit" value="Formular abschicken">';
		echo '</form>';
		echo '<br><br>';
	}


	if (isset($_GET(['save']))) {

		if (isset($_POST['uploaded_foto'])) 
			$foto = $_POST['uploaded_foto'];
		else    
			$foto = $_FILES['foto']['name'];

		$foto_url = $_POST['foto_url'];
		$files = count($_FILES['datei']['name']);
		for ($i=0; $i<$files; $i++) {
			if (strtolower(substr(trim($_POST['link'][$i]), 0, 7)) == "http://") 
				$_FILES['datei']['name'][$i] = $_POST['link'][$i];
		}

		if (isset($_SESSION['user_id'])) {
			$user_id = $_SESSION['user_id'];

			$query = "SELECT user_id, reg_date FROM user WHERE user_id='" . $user_id . "'";
			mysql_wrap_query($query, $result);
			$row = mysql_fetch_object($result);

			$reg_date = $row->reg_date; 

			$query = "DELETE FROM user WHERE user_id='" . $user_id . "'";
			mysql_wrap_query($query, $result);

		} else {
			$user_id = "";
			$reg_date = date("Y-m-d");
		} 

		$query = "INSERT INTO user VALUES('" . $user_id . "', '"
			. $_POST['login'] . "', '" 
			. $_POST['pass'] . "', '"
			. $_POST['name'] . "', '" 
			. $_POST['motto'] . "', '"
			. $_POST['teaser'] . "', '"
			. $foto . "', '"
			. $foto_url . "', '"
			. $reg_date . "', '" 
			. $_POST['comment'] . "', '1')";

		mysql_wrap_query($query, $result);
		$user_id = mysql_insert_id();

		$query = "DELETE FROM user_cat WHERE user_id='" . $user_id . "'";
		mysql_wrap_query($query, $result);
		$cat_ids = count($_POST['cat_id']);

		if ($cat_ids != 0) {
			$query = "INSERT INTO user_cat VALUES";
			for ($i=0; $i<$cat_ids; $i++) {
				if ($i != 0)
					$query = $query . ",";
				$query = $query . "('" . $user_id . "', '" .  $_POST['cat_id'][$i] . "')";
			}

			mysql_wrap_query($query, $result);
			$cat_id = $_POST['cat_id'];

			while ($cat_ids > 0) {
				$query = "SELECT DISTINCT papa_id FROM cat " . 
					"WHERE papa_id!='0' AND (";
				for ($i=0; $i<$cat_ids; $i++) {
					if ($i != 0)
						$query = $query . " OR ";
					$query = $query . "cat_id='" .  $cat_id[$i] . "'";
				}
				$query = $query . ")";

				mysql_wrap_query($query, $result);
				$cat_ids = mysql_num_rows($result);
				$cat_id = array();

				if ($cat_ids != 0) {       
					$query = "INSERT IGNORE INTO user_cat VALUES";
					for ($i=0; $i<$cat_ids; $i++) {
						if ($i != 0)
							$query = $query . ",";
						$row = mysql_fetch_object($result); 
						$query = $query . "('" . $user_id . "', '" .  $row->papa_id . "')";
						$cat_id[$i] = $row->papa_id;
					}

					mysql_wrap_query($query, $result);
				}
			}
		}

		$dir =  $upload_path . $user_id . "/";
		@mkdir($dir, 0755);

		if (isset($_POST['del_foto'])) 
			@unlink($dir . $_POST['del_foto']);

		@move_uploaded_file($_FILES['foto']['tmp_name'], 
				$dir . $_FILES['foto']['name']);

		system("/usr/bin/convert " . $dir . $_FILES['foto']['name'] 
				. " -resize 225x225\> " . $dir . $_FILES['foto']['name']);
		/*
			if ($_FILES['foto']['size'] > 100000)
			die("Die Gr&ouml;sse der Datei '" . $_FILES['foto']['name'] .
			"' &uuml;bersteigt 100 KB!");
		 */
		if (isset($_POST['del_datei'])) {
			$query = "DELETE FROM file WHERE user_id='" . $user_id . "' AND (";
			$del_dateien = count ($_POST['del_datei']);

			for ($i=0; $i<$del_dateien; $i++) {
				@unlink($dir . $_POST['del_datei'][$i]); 

				if ($i != 0)
					$query = $query . " OR ";
				$query = $query . "datei='" . $_POST['del_datei'][$i] . "'";
			}

			$query = $query . ")";
			mysql_wrap_query($query, $result);
		}

		for ($i=0; $i<$files; $i++) 
			if (trim($_FILES['datei']['name'][$i]) != "") {
				if (strtolower(substr(trim($_FILES['datei']['name'][$i]), 0, 7))  
						!= "http://") 
					@move_uploaded_file($_FILES['datei']['tmp_name'][$i],                                                                          
							$dir . $_FILES['datei']['name'][$i]);

				$query = "INSERT INTO file VALUES('" 
					. $_FILES['datei']['name'][$i] . "', '" 
					. $_POST['info'][$i] . "', '" 
					. $user_id . "')";

				mysql_wrap_query($query, $result);
			}

		$uploaded_dateien = count($_POST['uploaded_datei']);
		for ($i=0; $i<$uploaded_dateien; $i++) {
			$query = "UPDATE file SET info='" .$_POST['uploaded_info'][$i] .
				"' WHERE datei='" .  $_POST['uploaded_datei'][$i] . 
				"' AND user_id='" . $user_id . "'";

			mysql_wrap_query($query, $result);
		}

		echo '<div class="upload_ok">Ihr <a href="index.php?id=user&user_id=' . $user_id . '" target="main">Profil</a> ';
		echo 'wurde erfolgreich erstellt/geändert';

		// Den User einloggen, falls er sich frisch-registriert hat

		// d.h: einfach die SESSION-Variablen setzen (Cookie nüsste ja bereits gestzt sein);
		// Funktionalisiseren!

		exit; // return to main 
	}
}

