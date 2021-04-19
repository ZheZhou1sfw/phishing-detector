chrome.tabs.query({active: true, currentWindow:true}, function(tabs)
{
    // step 1: get the url
    let url = tabs[0].url;
    document.getElementById("url").innerHTML = url;
    // step 2: perform checks

    document.querySelector('button').addEventListener('click', function(e) {
        // capture screenshot
        // default current window, default format jpeg
        
        document.querySelector('button').innerHTML = 'in progress...';

        console.log('start checking');
        
        serverAddr = 'http://24.125.126.126:44444/';
        param = 'phishdetector?url=';
        urlToCheck = serverAddr + param + url;

        fetch(urlToCheck).then(r => r.text()).then(result => {
            // step 3: render result
            
            let message = '';
            if (result == 0) {
                message = 'marked phishing by verified source'
            } else if (result == 1) {
                message = 'marked safe by verified source'
            } else if (result == 2) {
                message = 'marked phishing by detector'
            } else if (result == 3) {
                message = 'marked safe by detector'
            } else {
                // something went wrong
                message = 'ops something went wrong';
            }
            document.getElementById("result").innerHTML = 'Result: ' + message;
            document.querySelector('button').innerHTML = 'done';
        }).catch((e) => {
            document.querySelector('button').innerHTML = 'done';
            console.log("error: " + e);
            document.getElementById("result").innerHTML = 'Result: ' + 'no connection to server';
        })
        
    });
});


