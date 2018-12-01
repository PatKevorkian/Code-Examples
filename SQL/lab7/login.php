<?php



require_once('db_funct.php');


//login form 
function login_form($url)
{

    echo "<form action = '$url' method = \"post\">";
    echo "<font size ='3'>";
    echo "username:";
    echo       " <input type=\"text\" name=\"username\" value=\"\">";
    echo    "password:";
    echo " <input type=\"password\" name=\"password\" value=\"\">";
    echo " &nbsp&nbsp&nbsp&nbsp";
    echo "<input type=\"submit\" name=\"submit\" value=\"Submit\">";
    echo "  </font>";

    echo "   </form>";
    echo "    </html>";
}

//validates login info 

function login($username, $password) {
	
    $conn = db_connect();


    // check if username is unique
    $result = $conn->query("select * from users where username='".$username."'and password = sha1('".$password."')");
    if (!$result) {
        throw new Exception('Could not log you in.');
    }

    if ($result->num_rows>0) {
        return true;
    } else {
        throw new Exception('Could not log you in.');
    }

}

//checks if a session is goingan infroms user if the yare logged in of not 
function check_valid_user() {
    if (isset($_SESSION['valid_user']))  {
        echo "Logged in as ".$_SESSION['valid_user'].".<br />";
    } else {
        // they are not logged in
        do_html_heading('Problem:');
        echo 'You are not logged in.<br />';
        do_html_url('login.php', 'Login');
        do_html_footer();
        exit;
    }
}



