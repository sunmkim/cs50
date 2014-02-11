<?php

// configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // lookup stock
        $s = lookup($_POST["symbol"]);
        
        // make sure user entered correct stock symbol
        if ($s === false)
        {
            apologize("Stock not found. Enter another stock symbol");
        }
        
        else 
        {
            // render quote_template, where price is
            render("quote_template.php", ["title" => "Quote"]);
        }
    }
    
    else
    {   
        // render quote_form
        render("quote_form.php", ["title" => "Quote"]);
    }

?>
