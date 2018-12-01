<?php

function do_html_header($title) {
  // print an HTML header
?>
  <html>
  <head>
    <title><?php echo $title;?></title>
    <style>
      body { font-family: Arial, Helvetica, sans-serif; font-size: 13px }
      li, td { font-family: Arial, Helvetica, sans-serif; font-size: 13px }
      hr { color: #3333cc; width=300; text-align=left}
      a { color: #000000 }
    </style>
  </head>
  <body>
  <img src="BlogMore2.jpg" alt="PHPbookmark logo" border="0"
       align="left" valign="bottom" height="70" width="170" />
  <h1>Welcome to blog!</h1>
  <hr />
<?php
  if($title) {
    do_html_heading($title);
  }
}

//function that adds new post, mostly html so it wa put here 
function add_new_post()
{


if (isset($_SESSION['valid_user'])) 
{
    $url = "index.php?" . $_SERVER['QUERY_STRING'];

    echo "</br><br>";
	echo"New Post:";
	echo "</br><br>";
    echo "<form action = '$url' method = 'post'>";
    echo "<font size ='3' >";
    echo"Title:";
    echo "<input type='text' name='title'>";
    echo "Body:";
    echo "<input type='text' name='new_post'>";
    echo "<input type='submit' value='Post'>";
    echo "</br>";
    echo "</font>";
    echo "</form>";
	
	
    if (isset($_POST['new_post']) && isset($_POST['title']))
	{
        $b = $_POST['new_post'];
        echo "<br>Posted!<br>";
        add_post($_POST['title']);
    }
	if(isset($_POST['submit']))
	{
        echo "<p> Info not entered correctly</p>";
    }
	
}

}
//logout function 
function logout()
{
	
    if (isset($_SESSION['valid_user'])) 
	{
        echo "<form action method = 'post'>";
        echo "<font size ='3' >";
        echo "logout";
        echo "<input type='submit' name='logout' value='logout'>";
        echo "</font>";
    }
}
?>