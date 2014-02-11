<?php

    // configuration
    require("../includes/config.php");

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // TODO       
        // check if valid username and password are given
        if ($_POST["username"] == NULL || $_POST["password"] == NULL) 
        {
            // apologize and inform of error
            apologize("Please submit a username and/or password");
        }
        
        // check if passwords and its confirmation match
        if ($_POST["password"] != $_POST["confirmation"])
        {
            apologize("Passwords do not match. Try again.");
        }
        
        // insert new user
        $result = query("INSERT INTO users (username, hash, cash) VALUES(?, ?, 10000.00)", $_POST["username"], crypt($_POST["password"]));
        
        // check if username is unique
        if ($result === false)
        {
            // apologize and inform of error
            apologize("That username has already been used. Please submit a different username.");
        }
         
        // log in user by finding out their id
        $rows = query("SELECT LAST_INSERT_ID() AS id");
        $id = $rows[0]["id"];
        
        // then store id in session
        $_SESSION["id"];
        redirect("index.php");
    }
    
    else
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

?>
