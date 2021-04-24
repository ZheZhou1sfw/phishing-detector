chrome.tabs.query({active: true, currentWindow:true}, function(tabs)
{

    // for UI testing purpose
    // document.getElementById("recommend_list_title").innerHTML = 'You may want to visit:';
    // document.getElementById("recommend_list_item").innerHTML = 'https://www.google.com' + '<br>';
    // document.getElementById("recommend_list_item").innerHTML = document.getElementById("recommend_list_item").innerHTML + 'https://www.facebook.com' + '<br>';
    // document.getElementById("recommend_list_item").innerHTML = document.getElementById("recommend_list_item").innerHTML + 'https://www.twitter.com' + '<br>';
    // document.getElementById("recommend_list_item").innerHTML = document.getElementById("recommend_list_item").innerHTML + 'https://www.google.com' + '<br>';
    // document.getElementById("recommend_list_item").innerHTML = document.getElementById("recommend_list_item").innerHTML + 'https://www.facebook.com' + '<br>';
    // document.getElementById("recommend_list_item").innerHTML = document.getElementById("recommend_list_item").innerHTML + 'https://www.twitter.com' + '<br>';
    // document.getElementById("recommend_list_item").innerHTML = document.getElementById("recommend_list_item").innerHTML + 'https://www.google.com' + '<br>';
    // document.getElementById("recommend_list_item").innerHTML = document.getElementById("recommend_list_item").innerHTML + 'https://www.facebook.com' + '<br>';
    // document.getElementById("recommend_list_item").innerHTML = document.getElementById("recommend_list_item").innerHTML + 'https://www.twitter.com';
   

   

    // step 1: get the url
    let url = tabs[0].url;
    document.getElementById("url").innerHTML = url;
    // step 2: perform checks

    document.querySelector('button').addEventListener('click', function(e) {
        // capture screenshot
        // default current window, default format jpeg
        console.log('123');
        // document.querySelector('button').className = 'btn btn-info col-12';
        document.querySelector('button').innerHTML = 'in progress...';


        console.log('start checking');
        
        serverAddr = 'http://24.125.126.126:44444/';
        param = 'phishdetector?url=';
        urlToCheck = serverAddr + param + url;

        fetch(urlToCheck).then(r => r.text()).then(result => {
            const resultObj = JSON.parse(result);
            const status = parseInt(resultObj['status']);
            // step 3: render result
            let dbMark = '';
            let imageMark = '';
            let message = 'Safe';
            if (status == 0) {
                dbMark = '&#10060';
                imageMark = 'Skipped';
                message = 'Phishing'
            } else if (status == 1) {
                dbMark = '&#9989';
                imageMark = 'Skipped';
                message = 'Safe';
            } else if (status == 2) {
                dbMark = 'Unknown';
                imageMark = '&#10060';
                message = 'Phishing';
                
                // special case, add recommend list to html
                document.getElementById("recommend_list_title").innerHTML = 'You may want to visit:';
                for (let i = 0; i < resultObj['recommend_list'].length; i++) {

                    document.getElementById("recommend_list_item").innerHTML = document.getElementById("recommend_list_ite").innerHTML + resultObj['recommend_list'][i];

                    if (i < resultObj['recommend_list'].length - 1) {
                        document.getElementById("recommend_list_item").innerHTML = document.getElementById("recommend_list_ite").innerHTML + '<br>';
                    }
                }

                

            } else if (status == 3) {
                dbMark = 'Unknown';
                imageMark = '&#10060';
                message = 'Safe';
            } else {
                dbMark = 'Unknown';
                imageMark = 'Unknown';
                message = 'No connection';
            }
            
            document.getElementById("result_img").innerHTML = document.getElementById("result_img").innerHTML + imageMark;
            document.getElementById("result_db").innerHTML = document.getElementById("result_db").innerHTML + dbMark;
            document.getElementById("result").innerHTML = 'Result: ' + message;

            document.querySelector('button').innerHTML = 'check';
        }).catch((e) => {
            document.querySelector('button').innerHTML = 'check';
            console.log("error: " + e);

            document.getElementById("result").innerHTML = 'Result: No connection';
        })
    });
});


