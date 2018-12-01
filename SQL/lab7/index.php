<?php

// start session 

session_start();

//include function files 

require_once('db_funct.php');
require_once('login.php');
require_once("post_funct.php");
require_once("output_fns.php");

//output header and message 

do_html_header($titl);

// set limit ot 0

if (!isset($_GET['limit']))
{
    $limit = 0;
}

// If you log out session is destroyed

if (isset($_POST['logout']) ) 
{
    session_destroy();
    $url = "index.php?" . $_SERVER['QUERY_STRING'];
    header("Location: $url");
}

//logout option function 

	logout();

// if user is not logged in, display login form

if (!isset($_SESSION['valid_user']))
{
    $url = "index.php?".$_SERVER['QUERY_STRING'];
    login_form($url);
}
//other log out also destroys seeeion 

if (isset($_POST['submit']))
{
    
    $u = $_POST['username']; $p = $_POST['password'];
	
    if ((isset($u) && !empty($u)) && (isset($p) && !empty($p))) 
	{
        if( login($u, $p))
        {
			
            echo "You are logged in <br>";
            $_SESSION['valid_user'] = $u;
            $url = "index.php?" . $_SERVER['QUERY_STRING'];
            header("Location: $url");
            // shows logout 
            echo "<form action method = 'post'>";
            echo "<font size ='3'>";
            echo "<input type='submit' name='logout' value='logout'>";
            echo "</font>";


            if (isset($_POST['logout'])) 
			{
                session_destroy();
                $url = "index.php?".$_SERVER['QUERY_STRING'];
            }

        }
		else
		{
            echo "Enter username and password!<br>";
        }
    }
}

//limit parameter for blocks of 5 posts 

if (!isset($_GET['limit']))
{
    $limit = 0;
}
    else
	{
        $limit = $_GET['limit'];
}
	//note the value after + or - can be changed depending on how many posts you want on a page 
	//also must be changed in get posts function 
    $limit_next = $limit+5;

    $limit_prev = $limit-5;

	
//output function adds new post 
	
	add_new_post();

// click next, get next 5 posts (all other pages except for the first one)

if ($limit > 0) 
{
    $posts = get_posts($limit);
	
    // get the next 5 posts 
    if (!empty($posts)) 
	{
        foreach ($posts as $row) 
		{
			//html out for posts 
			//put in "table" because i could not output it on one line otherwise 
            echo"</ br >";
            echo"<h1>$row[4] </h2> </ br></ br>";
			echo"<table>";
			echo"<tr>";
			echo"<td>";
			echo "<h2>$row[0]</h2>";
			echo "</td>";
			echo"<td>";
			echo"<p style='font-size:100%'>$row[3]</p>";
			echo"</td>";
			echo"</tr>";
			echo"</table>";
			echo"<p style='font-size:125%'>$row[1]</p>";
			

            // logged in, comments form shown 
            
            if (isset($_SESSION['valid_user'])) 
			{
                $url = "index.php?" . $_SERVER['QUERY_STRING'];
				//html form for comments 
                echo "</br>";
                echo "<form action = '$url' method = 'post'>";
                echo "<font size ='3'>";
                echo "</br>";
                echo "<input type='text' name='comment' value=''>";
                echo "<input type='submit' value='Add Comment'>";
                echo "</font>";
                echo "</form>";
				{
                if (isset($_POST['comment'])) 
				{
					//add comments 
                    echo "<br>Comment added! <br>";
                    add_comment($row[2]);
                }
				}
            }

            // Gets current limit
			
            $limit_cur = $_GET['limit'];
			
            echo "<a href = 'index.php?post_id=" . $row[2] . "&limit=" . $limit_cur . "'>Comments</a>";
            if (isset($_GET['post_id'])) 
			{
                // get comments for particular post 
				
                $post_id = $_GET['post_id'];
                $comments = get_comments($post_id);


                if (empty($comments)) 
				{
                    if ($post_id == $row[2]) 
					{
                        echo "<p> No comments.";
                    }
                }
				
                foreach ($comments as $r) 
				{
                    if ($row[2] == $post_id)
					{
						// html to show comments (with formating)
                        echo "<p style='font-size:100%'>$r[0]";
                        echo "<p style='font-size:100%'>$r[1]";
                    }
                }
            }
			
        }
		//links for prev and next pages 
        echo " <br></ br>";
        echo "<a href='index.php?limit=" . $limit_prev . "'><font size = '5'color = 'black'>5 Previous Posts</h1></a>";
		//non breaking spaces 
        echo "&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp";
        echo "<a href='index.php?limit=" . $limit_next . "'><font size = '5'color = 'black'>5 Next Posts</a>";
    }
	else 
	{
		//if there arent any more posts 
        echo "<p style='font-size:150%'> You have reached the end of posts!";
    }

    if (isset($_POST['submit']))
    {
		//other log out for next pages 
        $u = $_POST['username']; $p = $_POST['password'];
        if ((isset($u) && !empty($u)) && (isset($p) && !empty($p)))
		{
            if(login($u, $p))
            {
                $_SESSION['valid_user'] = $u;
                echo "Logged in!<br>";
                $_SESSION['valid_user'] = $u;
                echo "<form action method = 'post'>";
                echo "<font size ='3'>";
                echo "<input type='submit' name='logout' value='logout'>";
                echo "</font>";
                $url = "index.php?" . $_SERVER['QUERY_STRING'];
                header("Location: $url");

                if (isset($_POST['logout']))
				{
					//also destroys session 
                    session_destroy();
                    $url = "index.php?".$_SERVER['QUERY_STRING'];
                    login_form($url);
                }

            }
        }
		else
		{
            echo "Enter username and password! <br>";
        }
    }
}



else 
{
    // get first "page" of 5 posts 
	
    $posts = get_posts();
	// allows to print out posts, the comment links and forms (* side note: commenst got funky after i transfred to he db server)
    foreach ($posts as $row) 
	{
       
        	//html out for posts on first page 
			echo"</ br >";
            echo"<h1>$row[4] </h2> </ br></ br>";
			echo"<table>";
			echo"<tr>";
			echo"<td>";
			echo "<h2>$row[0]</h2>";
			echo "</td>";
			echo"<td>";
			echo"<p style='font-size:100%'>$row[3]</p>";
			echo"</td>";
			echo"</tr>";
			echo"</table>";
			echo"<p style='font-size:125%'>$row[1]</p>";
			

			// logged in, show comments link and add comments 

            if (isset($_SESSION['valid_user'])) 
			{
                $url = "index.php?" . $_SERVER['QUERY_STRING'];

                echo "</br>";
                echo "<form action = '$url' method = 'post'>";
                echo "<font size ='3' >";
                echo "<input type='text' name='comment'>";
                echo "<input type='submit' value='Add Comment'>";
                echo "</br>";
                echo "</font>";
                echo "</form>";
	
				if (isset($_POST['comment'])) 
				{
					//add comment (got funky)
                    echo "<br>Comment Added!<br>";
                    add_comment($row[2]);
                }
                
            }
        
	 
	  	//comments link to show comments 
            echo "<a href = 'index.php?post_id=". $row[2]. "'>Comments</a>";
            if(isset($_GET['post_id']))
			{
                $post_id = $_GET['post_id'];
				
                $comments = get_comments($post_id);
				
                if (empty($comments))
				{
                    if($post_id == $row[2])
					{
                    echo "No comments";
					}
                }
				
                foreach ($comments as $r) 
				{
                    if ($row[2] == $post_id)
					{
                    echo "<p style='font-size:100%'>$r[0]";
                    echo "<p style='font-size:100%;'>$r[1]";
					}
                }

            
        	}
			
			
    }
	//link for next block of posts 
    echo "<br></ br>";
	echo "<br></ br>";
	echo "<br></ br>";
	echo "<br></ br>";
    echo "<a href='index.php?limit=" . $limit_next . "'><font size = '5'color = 'black'>5 Next Posts</font></a>";
}

?>
//close php



