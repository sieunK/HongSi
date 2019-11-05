<?php
    //$prevPage = $_SERVER['HTTP_REFERER'];
    $filename = "question.txt";
    $file = fopen($filename,"w") or die("Unable to open file!");
    if(isset($_GET["demo-name"])) {
        $question = $_GET["demo-name"];
        $question = iconv("UTF-8", "EUC-KR",  $question);
        fwrite($file, $question);
        fclose($file);
        system("..\Release\KLTaggerTC user $filename > output.txt");
        system("parser output.txt keywords.txt");

        $filename = "keywords.txt";
        $keyworldFile = fopen($filename,"r") or die("Unable to open file!");
        $keyword = fread($keyworldFile,filesize($filename));
        $command = "Iif-Manager \"";
        $command .= $keyword;
        $command .= "\"";
        $command .= " > final.txt";  
        system($command);
        fclose($keyworldFile);
        system("searchResult final.txt statues.txt");

        $statues = '<?xml version="1.0" encoding="UTF-8"?><data>';
        $filename = "statues.txt";
        $file = fopen($filename,"r") or die("Unable to open file!");
        while( !feof($file) ) {
            $doc_data = fgets($file);
            if($doc_data == "")
                continue;
            $doc_data = str_replace("\r\n", ".xml", $doc_data);
            $filename = "..\\data\\xml\\";
            $filename .= $doc_data;
            $statueFile = fopen($filename,"r") or die("Unable to open file!");
            $statue = fread($statueFile,filesize($filename));
            $statues .= $statue;
        }
        $statues .= '</data>';
        fclose($file);

        $file = fopen("..\\data\\test.xml","w") or die("Unable to open file!");
        fwrite($file, $statues);
        fclose($file);

        $filename = "ptxt.txt";
        $file = fopen($filename,"r") or die("Unable to open file!");
        $ptxt = fread($file,filesize($filename));
        fclose($file);

        $ptxt_file = "..\\..\\build\\#PTXT\\".$ptxt;
        // system("C:\\Users\\april\\Anaconda3\\python sentence_finder.py ..\\..\\build\\#PTXT\\95.ptxt 안전");
        // system("C:\\Users\\april\\Anaconda3\\python test.py");

        $url = 'http://164.125.36.45:5000/bert';
        $data = array('question' => 'question' , 'text' => '타워크레인을 자립고 이상의 높이로 설치하는 경우에는 건축물의 벽체에 지지하는 것을 원칙으로 한다.');

        // use key 'http' even if you send the request to https://...
        $options = array(
            'http' => array(
                'header'  => "Content-type: application/x-www-form-urlencoded\r\n",
                'method'  => 'GET',
                'content' => http_build_query($data)
            )
        );
        $context  = stream_context_create($options);
        $result = file_get_contents($url, false, $context);
        if ($result === FALSE) { 
            $file = fopen("log.txt","w") or die("Unable to open file!");
            fwrite($file, $result);
            fclose($file);
        }

        var_dump($result);
        //header('location:'.$prevPage);
    }
?>

